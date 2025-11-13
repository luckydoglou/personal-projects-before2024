package ser321.assign6.xhuan127.java.server;

import java.io.Serializable;
import org.json.JSONObject;

/**
 * Copyright (c) 2019 Tim Lindquist, Xiaolou Huang
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * 
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * 
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * 
 * Purpose:
 * An class defining json serializable Message objects.
 * 
 * Ser321 Principles of Distributed Software Systems
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering
 *                       Ira Fulton Schools of Engineering, ASU Polytechnic
 * @author Xiaolou Huang (xhuan127@asu.edu) CIDSE - Software Engineering
 * @file    Message.java
 * @date    February, 2019
 * @license See above
 */
public class Message extends Object implements Serializable {

    // Serial version UID is defined below. Its only needed if you want
    // to make changes to the class and still deserialize artifacts
    // generated from prior versions. Obtain this definition with:
    // serialver -classpath classes:lib/json.jar ser321.serialize.Message
    private static final long serialVersionUID = 3415902006212375222L;
    private String MessageTo, MessageFrom, MessageSubject, MessageDate, MessageContent;

    /* Constructor with nothing paseed in */
    public Message() {
        MessageTo = "unknow";
        MessageFrom = "unknow";
        MessageSubject = "unknow";
        MessageDate = "unknow";
        MessageContent = "unknow";
    }

    /* Constructor that store all the fields */
    public Message(String to, String from, String subject, String date, String content) {
        MessageTo = to;
        MessageFrom = from;
        MessageSubject = subject;
        MessageDate = date;
        MessageContent = content;
    }

    /* Constructor that extract fields from a JSON object  */
    public Message(JSONObject obj){
        MessageTo = obj.getString("MessageTo");
        MessageFrom = obj.getString("MessageFrom");
        MessageSubject = obj.getString("MessageSubject");
        MessageDate = obj.getString("MessageDate");
        MessageContent = obj.getString("MessageContent");
    }

    /* Constructor that extract fields from a JSON string */
    public Message(String jsonString) {
        try {
            JSONObject obj = new JSONObject(jsonString);
            MessageTo = obj.getString("MessageTo");
            MessageFrom = obj.getString("MessageFrom");
            MessageSubject = obj.getString("MessageSubject");
            MessageDate = obj.getString("MessageDate");
            MessageContent = obj.getString("MessageContent");
        } catch (Exception ex) {
            System.out.println(this.getClass().getSimpleName() + ": error converting from JSON string");
        }
    }

    /* Write to JSON object */
    public JSONObject toJSONObject(){
        JSONObject obj = new JSONObject();
        obj.put("MessageTo",MessageTo);
        obj.put("MessageFrom",MessageFrom);
        obj.put("MessageSubject",MessageSubject); 
        obj.put("MessageDate",MessageDate);
        obj.put("MessageContent",MessageContent);
        return obj;
    }

    /* Write to JSON String*/
    public String toJSONString() {
        String ret = "";
        try {
            ret = this.toJSONObject().toString();
        } catch (Exception ex) {
            System.out.println(this.getClass().getSimpleName() + ": error converting to JSON string");
        }
        return ret;
    }

    /* Check if the messageTo matches the input 'to' */
    public boolean findMessageTo(String to) {
        if (MessageTo.equals(to)) {
            return true;
        }
        return false;
    }

    /* Get MessageTo string */
    public String getMessageTo() {
        return MessageTo;
    }

    /* Get MessageFrom string */
    public String getMessageFrom() {
        return MessageFrom;
    }

    /* Get MessageSubject string */
    public String getMessageSubject() {
        return MessageSubject;
    }

    /* Get MessageDate string */
    public String getMessageDate() {
        return MessageDate;
    }

    /* Get MessageContent string */
    public String getMessageContent() {
        return MessageContent;
    }

    /* Set MessageContent string to a given string */
    public void setMessageContent(String content) {
        MessageContent = content;
    }

    /* Set MessageTo string to a given string */
    public void setMessageTo(String to) {
        MessageTo = to;
    }

    /* Set MessageFrom string to a given string */
    public void setMessageFrom(String from) {
        MessageFrom = from;
    }

    /* Set MessageSubject string to a given string */
    public void setMessageSubject(String subject) {
        MessageSubject = subject;
    }

    /* Set MessageDate string to a given string */
    public void setMessageDate(String date) {
        MessageDate = date;
    }

    /* toString() */
    public String toString() {
        String str = "";
        str += "To: " + MessageTo + "\n";
        str += "From: " + MessageFrom + "\n";
        str += "Subject: " + MessageSubject + "\n";
        str += "Date: " + MessageDate + "\n";
        str += "Content: " + MessageContent + "\n";
        return str;
    }

}

