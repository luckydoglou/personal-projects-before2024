package ser321.assign6.xhuan127.java.client;

import ser321.assign2.lindquis.client.*;
import ser321.assign6.xhuan127.java.client.Client_TcpProxy;
import ser321.assign6.xhuan127.java.server.*;

import java.io.*;
import java.util.*;
import java.net.URL;
import org.json.JSONObject;
import org.json.JSONArray;
import javax.swing.*;
import javax.swing.DefaultListModel;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import java.awt.Cursor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.util.Vector;
import java.util.Date;
import java.text.SimpleDateFormat;

/*
 * Copyright 2019 Xiaolou Huang, Tim Lindquist,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Purpose: demonstrate use of MessageGui class for students to use as a
 * basis for solving Ser321 Spring 2019 Homework Problems.
 * The class SampleClient can be used by students in constructing their 
 * controller for solving homework problems. The view class is MessageGui.
 *
 * This problem set uses a swing user interface to implement (secure) messaging.
 * Messages are communicated to/from message clients, via a common well-known.
 * server.
 * Messages can be sent in clear text, or using password based encryption 
 * (last assignment). For secure messages, the message receiver must enter
 * the password (encrypted).
 * The Message tab has two panes. left pane contains a JList of messages
 * for the user. The right pane is a JTextArea, which can display the
 * contents of a selected message. This pane is also used to compose
 * messages that are to be sent.
 *
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist Tim.Lindquist@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @author Xiaolou Huang xhuan127@asu.edu
 * @version February 2019
 */
public class Client extends MessageGui
                           implements ActionListener, ListSelectionListener {

    private String userId;   // originator of all message sent by this client.
    private String hostId; // will be 192.168.2.2 or 192.168.3.2
    private String regPort; // such as lindquisrpi.local:8080
    private static final String patt = "EEE MMM d K:mm:ss yyyy";
    private String[] msgHeaders;
    private Server_MessageLibraryInterface server; // server instance
    private Client_TcpProxy clientTcpProxy;

    static final boolean debugOn = false;
    private static void debug(String message) {
      if (debugOn)
         System.out.println("debug: "+message);
   }

    public Client(String userId, String hostId, String regPort) {
        super("Xiaolou Huang", userId); // pass the user name to MessageGui
        this.userId = userId;
        this.hostId = hostId;
        this.regPort = regPort;
        
        String url = "http://" + hostId + ":" + regPort + "/";
        System.out.println("Opening connection to: " + url);
        clientTcpProxy = (Client_TcpProxy)new Client_TcpProxy(hostId, Integer.parseInt(regPort));

        // add this object as an action listener for all menu items.
        for(int j = 0; j < userMenuItems.length; j++){
            for(int i=0; i<userMenuItems[j].length; i++){
                userMenuItems[j][i].addActionListener(this);
            }
        }

        // add this object as an action listener for the view buttons
        deleteJB.addActionListener(this);
        replyJB.addActionListener(this);
        sendTextJB.addActionListener(this);
        sendCipherJB.addActionListener(this);

        // listen for the user to select a row in the list of messages.
        // When a selection is made, the method valueChanged will be called.
        messageListJL.addListSelectionListener(this);

        // display inital messages for current user
        try {
            msgHeaders = clientTcpProxy.getMessageFromHeaders(userId);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        DefaultListModel<String> dlm = (DefaultListModel<String>)messageListJL.getModel();
        for (int i = 0; i < msgHeaders.length; i++) { // add all the headers to messageListJL
            dlm.addElement(msgHeaders[i]);
        }

        setVisible(true);
    }

    public void valueChanged(ListSelectionEvent e) {
        // If you do something (in here or anywhere) that takes lots of time, you may want
        // to change the cursor to hourglass (waitcursor) while you're doing it. See
        // the setCursor calls in the actionPerformed method. Really, though you
        // should use a javax.swing.SwingWorker class to perform any long-lasting
        // operations in the background, so the UI is not frozen while a network
        // or other long lasting operation is performed.

        // the call to getvalueisadjusting determines whether we're being called
        // for the last in a sequence of related (event-generating) user actions.
        // we generally don't want to redo handling multiple times.
        setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

        if (!e.getValueIsAdjusting()){
            // If the action event is selecting the message, populate message to corresponding fields
            if (messageListJL.getSelectedIndex() > -1) {
                // use msgHeader to get the "Message" and write fields to the GUI
                DefaultListModel<String> dlm = (DefaultListModel<String>)messageListJL.getModel();
                try {
                    Message msg = clientTcpProxy.getMessage(dlm.getElementAt(messageListJL.getSelectedIndex()), userId);

                    fromJTF.setText(msg.getMessageFrom()); // get the Message from user selection in left panel of GUI
                    toJTF.setText(msg.getMessageTo());
                    subjectJTF.setText(msg.getMessageSubject());
                    dateJTF.setText(msg.getMessageDate());
                    messageContentJTA.setText(msg.getMessageContent());
                    System.out.println("You selected messageList item: " + messageListJL.getSelectedIndex());
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
            // Else the action event is deleting the message, do following
            else {
                messageContentJTA.setText("You selected messageList item: " + messageListJL.getSelectedIndex());
                System.out.println("You selected messageList item: " + messageListJL.getSelectedIndex());

                Date today = new Date();
                SimpleDateFormat form = new SimpleDateFormat(patt);
                String todayStr = form.format(today);
                dateJTF.setText(todayStr);
            }
        }

        // get rid of the waiting cursor
        setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }

    public void actionPerformed(ActionEvent e) {
        // the actions in this method do NOT reflect what has to be done in handling
        // these different actions, but are designed to demonstrate how to access the
        // view objects.

        // If you do something (in here or anywhere) that takes lots of time, you may want
        // to change the cursor to an hourglass (waitcursor) while you're doing it. Really
        // though, you should use a javax.swing.SwingWorker class to perform any long-lasting
        // operations in the background, so the UI is not frozen while a network
        // or other long lasting operation is performed. Users don't like non-responsive apps.
        setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

        if(e.getActionCommand().equals("Exit")) {
            System.exit(0);
        } 

        else if(e.getActionCommand().equals("Reply")) {
            DefaultListModel<String> dlm = (DefaultListModel<String>)messageListJL.getModel();
            Date today = new Date();
            SimpleDateFormat form = new SimpleDateFormat(patt);
            String todayStr = form.format(today);

            // Switches the right panel fields from display to compose. Swaps the to and
            // from fields, pre-pends Re: to the Subject field and modifies the message
            // content text area to allow new text to be entered before the old message.
            try {
                Message msg = clientTcpProxy.getMessage(dlm.getElementAt(messageListJL.getSelectedIndex()), userId);

                fromJTF.setText(userId);
                toJTF.setText(msg.getMessageFrom());
                subjectJTF.setText("Re: " + msg.getMessageSubject());
                dateJTF.setText(todayStr);
                messageContentJTA.setText("Re:\n\n\n\n\n-----------------------------\n" + msg.getMessageContent());

            } catch (Exception ex) {
                ex.printStackTrace();
            }

            // update the message content
            //System.out.print("#####\n" + messageContentJTA.getText());
            messageStatusJTA.setText(" *(Insecure, sent as clear text.)*");
        }

        else if(e.getActionCommand().equals("Delete")) {
            DefaultListModel dlm = (DefaultListModel)messageListJL.getModel(); // get the left panel list
            int selected = messageListJL.getSelectedIndex();

            Date today = new Date();
            SimpleDateFormat form = new SimpleDateFormat(patt);
            String todayStr = form.format(today);

            // remove the message from 'Messages' vector
            try {
                if (clientTcpProxy.deleteMessage(msgHeaders[selected], userId)) {
                    System.out.println("successfully deleted from server");
                } else {
                    System.out.println("Cannot delete the message from server, user or message does not exist");
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }

            String fromNDateStr = selected>-1 ? (String)dlm.getElementAt(selected) : "no selection";
            System.out.println("request to delete message index: "+selected+" text: "+fromNDateStr);

            // delete the message header from messageListJL (dlm)
            if(selected > -1){
                dlm.removeElementAt(selected);
            }

            //dlm.clear(); //use this to clear the entire list.
            fromJTF.setText(userId);
            toJTF.setText("");
            subjectJTF.setText("");
            dateJTF.setText(todayStr);
            messageContentJTA.setText("");
            messageStatusJTA.setText("");
        }
        else if (e.getActionCommand().equals("Send Text")) {
            // when send text has been called, it will find the current header that is selected, 
            // and find the corresponding message object; read the content from 
            // messageContentJTA.getText(), and store it in message; finally, send the message
            // to server.
            DefaultListModel<String> dlm = (DefaultListModel<String>)messageListJL.getModel();
            int selected = messageListJL.getSelectedIndex();

            Date today = new Date();
            SimpleDateFormat form = new SimpleDateFormat(patt);
            String todayStr = form.format(today);

            // step 1, delete from server
            try {
                Message msg = clientTcpProxy.getMessage(dlm.getElementAt(messageListJL.getSelectedIndex()), userId);
                clientTcpProxy.deleteMessage(msgHeaders[selected], userId);

                // step 2, update message fields
                msg.setMessageFrom(fromJTF.getText());
                msg.setMessageTo(toJTF.getText());
                msg.setMessageDate(dateJTF.getText());
                msg.setMessageSubject(subjectJTF.getText());
                msg.setMessageContent(messageContentJTA.getText()); // update the message content
                //msg.setMessageStatus(messageStatusJTA.getText());

                // step 3, delete the message header from messageListJL (dlm)
                if(selected > -1){
                    dlm.removeElementAt(selected);
                    System.out.println("Send Text: successfully delete from local");
                }

                // step 4, send Messsage object to server
                boolean isSent = clientTcpProxy.sendClearText(msg, msg.getMessageTo());
                if (isSent) {
                    System.out.println("Sucessfully send to server.");
                } else {
                    System.out.println("Fail send to server.");
                }

            } catch (Exception ex) {
                ex.printStackTrace();
            }
            messageStatusJTA.setText(" *(Insecure, sent as clear text.)*");
        }

        else if (e.getActionCommand().equals("Get Mail")) {
            try {
                msgHeaders = clientTcpProxy.getMail(userId);
                // repaint the gui, update messageListJL, dislay new messages
                DefaultListModel<String> dlm = (DefaultListModel<String>)messageListJL.getModel();
                dlm.clear();
                for (int i = 0; i < msgHeaders.length; i++) { // add all the headers to messageListJL
                    dlm.addElement(msgHeaders[i]);
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        else if (e.getActionCommand().equals("Send Cipher")) {

        }

        // get rid of the waiting cursor
        setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }

    public static void main(String args[]) {
        System.out.println("=============================================");
        try{
            String userId = "Xiaolou.Huang";
            String hostId = "localhost";
            String regPort = "8080";
            if (args.length >= 2) {
                userId = args[0];
                hostId = args[1];
                regPort = args[2];
            }
            Client client = new Client(userId, hostId, regPort);
        } catch (Exception ex){
            ex.printStackTrace();
        }
    }
}

