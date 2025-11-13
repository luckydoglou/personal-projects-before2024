package ser321.assign6.xhuan127.java.server;

//import java.rmi.*;
//import java.util.Vector;

/**
 * Copyright (c) 2019 Xiaolou Huang,
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
 * Purpose: demonstrate using the RMI API
 * remote interface for the message server.
 * 
 * Ser321 Principles of Distributed Software Systems
 * @author Xiaolou Huang, xhuan127@asu.edu - Software Engineering
 *                       Ira Fulton Schools of Engineering, ASU Polytechnic
 * @date    February, 2019
 * @license See above
 */
public interface Server_MessageLibraryInterface {

    // getMessageFromHeaders returns a string array of message headers being sent to toAUserName.
    // Headers returned are of the form: (from user name @ server and message date)
    // e.g., a message from J Buffett with header: Jimmy.Buffet  Tue 18 Dec 5:32:29 2018 
    public String[] getMessageFromHeaders(String userName);

    // getMessage returns the Message having the corresponding header. Assume headers are unique.
    // As above, the header has includes (from user name - server and message date)
    public Message getMessage(String header, String userName);

    // deletes the message having the header (from user name - server and message date)
    public boolean deleteMessage(String header, String userName);

    // send clear text to RMI server.
    public boolean sendClearText(Message aMessage, String fromUser);

    // get all the emails that belongs to the user who requires it
    public String[] getMail(String userName);

}




