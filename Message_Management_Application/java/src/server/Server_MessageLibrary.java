package ser321.assign6.xhuan127.java.server;

import java.io.*;
import org.json.JSONString;
import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONTokener;

import java.util.Hashtable;
import java.util.Iterator;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Vector;
import java.util.Enumeration;

import java.io.IOException;

/**
 * Copyright (c) 2019 Tim Lindquist, Xiaolou Huang
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose:
 * A class implementing the operations for MessageLibrary management using TCP/IP.
 * <p/>
 *
 * Ser321 Principles of Distributed Software Systems
 * @see <a href="http://pooh.poly.asu.edu/Ser321">Ser321 Home Page</a>
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering
 *                       Ira Fulton Schools of Engineering, ASU Polytechnic
 * @author Xiaaolou Huang (xhuan127@asu.edu) CISSEe - Sfotware Engineering
 * @file    MessageLibrary.java
 * @date    April, 2019
 * @license See above
 * @see ser321.serialize.Message
 */
public class Server_MessageLibrary extends Object implements Server_MessageLibraryInterface {

    // Serial version UID is defined below. Its only needed if you want
    // to make changes to the class and still deserialize artifacts
    // generated from prior versions. Obtain this definition with:
    // serialver -classpath classes:lib/json.jar ser321.serialize.MessageLibrary
    private static final long serialVersionUID = 6982142948226029575L;
    private String name; // the name of this MessageLibrary
    private Hashtable<String, Vector<Message>> database; // stores all the messages for all the users
    //private Vector<Message> messages; // the members of this MessageLibrary

    /**
    * Constructor1
    */
    public Server_MessageLibrary() {
        this.name = "unknown";
    }

    /**
    * Constructor2 takes a JSON file (that stores all the messages for many users) and
    * extract each user and its corresponding messages.
    * 
    * @para fileName the JSON file that stores all the messages for all the users.
    */
    public Server_MessageLibrary(String fileName) {
        try{
            FileInputStream in = new FileInputStream(fileName);
            JSONObject obj = new JSONObject(new JSONTokener(in)); // obj that contains all the objects
            String [] names = JSONObject.getNames(obj); // 'names' contains all the user names
            System.out.println("");
            name = obj.getString("name"); // get the name of the JSON file

            // DEBUG, print out the users
            System.out.println("name = " + name);
            System.out.print("Exsiting users are: ");
            for(int j=0; j< names.length; j++){
                if (!names[j].equals("name")) {
                    System.out.print(names[j]+"  ");
                }
            } 
            System.out.println();
            // end of DEBUG

            database = new Hashtable<String, Vector<Message>>(); // initialize 'database'
            for(int j=0; j< names.length; j++){
                if (!names[j].equals("name")) {
                    Vector<Message> messages = new Vector<Message>();
                    JSONArray objArr = new JSONArray();
                    // get an array of message objects from current user
                    objArr = obj.getJSONArray(names[j]);
                    // put info into message vector
                    for (int i = 0; i < objArr.length(); i++) {
                        Message aMessage = new Message(objArr.getJSONObject(i));
                        messages.add(aMessage);
                    }
                    database.put(names[j], messages);
                }
            }

            in.close();
        }catch (Exception ex) {
            System.out.println("Exception importing from json: "+ex.getMessage());
        }
    }

    /* Not using for now */
    public String toJSONString(){
        //        String ret;
        //        JSONObject obj = new JSONObject();
        //        obj.put("name",name);
        //        for (Enumeration<Message> e = messages.elements(); e.hasMoreElements();) {
        //            Message usr = (Message)e.nextElement();
        //            obj.put(usr.getId(),usr.toJSONObject()); // add every Messsage type usr to JSONObject // need to change getId() #################
        //        }
        //        ret = obj.toString();
        //        //System.out.println("MessageLibrary tojsonstring returning string: "+ret);
        return "";
    }

    /*
    public String getName(){
        return name;
    }

    public void setName(String aName){
        name = aName;
    }
    */

    // get all the emails that belongs to the user who requires it
    public String[] getMail(String userName) {
        String[] headerArr = this.getMessageFromHeaders(userName);
        System.out.println("getMail() is called by " + userName);
        return headerArr;
    }

    // receive clear text from client use java RMI, server will store the message for
    // the corresponding receiver, and delete the message from sender
    public boolean sendClearText(Message aMessage, String toUser) {
        if (database.containsKey(toUser)) {
            Vector<Message> messagesReceiver = database.get(toUser);
            messagesReceiver.add(aMessage);
            System.out.println("Successfully send message to " + toUser + " from " + aMessage.getMessageFrom());
            return true;
        }
        System.out.println("sendClearText failed, user does not exist.");
        return false;
    }

    // not using in Assign3.
    public boolean sendCipher(Message aMessage, String fromUser) {
        return false;
    }

    // getMessageFromHeaders returns a string array of message headers being sent to toAUserName.
    // Headers returned are of the form: (from user name @ server and message date)
    // e.g., a message from J Buffett with header: Jimmy.Buffet  Tue 18 Dec 5:32:29 2018
    public String[] getMessageFromHeaders(String userName) {
        String[] headerArr;
        int len = 0;
        Vector<Message> messages = database.get(userName);

        //get the length for what the 'headerArr' needs to be
        for (int i = 0; i < messages.size(); i++) {
            if (messages.get(i).findMessageTo(userName)) {
                len++;   
            }
        }
        // store the formatted header strings to 'headerArr'
        headerArr = new String[len];
        int j = 0;
        for (int i = 0; i < messages.size(); i++) {
            if (messages.get(i).findMessageTo(userName)) {
                headerArr[j] = messages.get(i).getMessageFrom() + "  " + messages.get(i).getMessageDate();
                j++;
            }
        }
        return headerArr;
    }

    // getMessage returns the Message having the corresponding header. Assume headers are unique. The header has includes (from user name - server and message date).
    public Message getMessage(String header, String userName) {
        Message msg = new Message();
        String[] headerSplit = header.split("  ", 2); // split header into two tokens
        Vector<Message> messages = database.get(userName);

        // find the matching MessageFrom and MessageDate
        for (int i = 0; i < messages.size(); i++) {
            if (headerSplit[0].equals(messages.get(i).getMessageFrom())) {
                if (headerSplit[1].equals(messages.get(i).getMessageDate())) {
                    msg = messages.get(i);
                }
            }
        }
        return msg;
    }

    // deletes the message for this user
    public boolean deleteMessage(String header, String userName) {
        if (!database.containsKey(userName)) {
            System.out.println("Fail to delete the message, user: " + userName + " does not exist.");
            return false;
        }

        Vector<Message> messages = database.get(userName); 
        String[] headerSplit = header.split("  ", 2); // split header into two tokens
        // find the matching MessageFrom and MessageDate
        for (int i = 0; i < messages.size(); i++) {
            if (headerSplit[0].equals(messages.get(i).getMessageFrom())) {
                if (headerSplit[1].equals(messages.get(i).getMessageDate())) {
                    messages.remove(i);
                    System.out.println("Successfully delete message for " + userName + ".");
                    return true;
                }
            }
        }
        System.out.println("Fail to delete the message, " + userName + " does not contain this message.");
        return false;
    }

}