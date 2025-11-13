package ser321.assign6.xhuan127.java.server;

import java.net.*;
import java.io.*;
import java.util.*;
import org.json.*;
import org.json.JSONObject;
import org.json.JSONArray;

/**
 * Copyright 2019 Tim Lindquist, Xiaolou Huang
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
 * A class for client-server connections with a threaded server.
 * The Message collection server creates a server socket.
 * When a client request arrives, which should be a JsonRPC request, a new
 * thread is created to service the call and create the appropriate response.
 * Byte arrays are used for communication to support multiple langs.
 *
 * @author Tim Lindquist ASU Polytechnic Department of Engineering
 * @author Xiaolou Huang xhuan127@asu.edu, Software Engineering
 * @version April 2019
 */
public class Server_TcpProxy extends Object {

    private static final boolean debugOn = false;
    Server_MessageLibraryInterface messageLib;

    public Server_TcpProxy(Server_MessageLibraryInterface messageLib) {
        this.messageLib = messageLib;
    }

    private void debug(String message) {
        if (debugOn)
            System.out.println("debug: "+message);
    }

    public String callMethod(String request) {
        JSONObject result = new JSONObject();
        try {
            JSONObject theCall = new JSONObject(request);
            debug("Request is: "+theCall.toString());
            String method = theCall.getString("method");
            JSONArray params = null;
            if(!theCall.isNull("params")){
                params = theCall.getJSONArray("params");
            }
            result.put("jsonrpc","2.0");
            if(method.equals("getMessageFromHeaders")) { // getMessageFromHeaders()
                String userNameJsonStr = params.getString(0);
                String[] headers = messageLib.getMessageFromHeaders(userNameJsonStr);
                JSONArray headersJsonArr = new JSONArray();
                for (int i = 0; i < headers.length; i++) {
                    headersJsonArr.put(headers[i]);
                }
                debug("method getMessageFromHeader() called ");
                result.put("result", headersJsonArr);
            } else if (method.equals("getMessage")) { // getMessage()
                String header = params.getString(0);
                String userName = params.getString(1);
                Message msg = messageLib.getMessage(header, userName);
                debug("method getMessage() called ");
                result.put("result",msg.toJSONString());
            } else if (method.equals("deleteMessage")) { // deleteMessage()
                String header = params.getString(0);
                String userName = params.getString(1);
                boolean isDeleted = messageLib.deleteMessage(header, userName);
                debug("method deleteMessage() is called ");
                result.put("result",isDeleted);
            } else if (method.equals("sendClearText")) { // sendClearText()
                JSONObject msgJsonObj = params.getJSONObject(0);
                String fromUser = params.getString(1);
                Message msg = new Message(msgJsonObj);
                boolean isSent = messageLib.sendClearText(msg, fromUser);
                debug("method sendClearText() is called ");
                result.put("result",isSent);
            } else if (method.equals("getMail")) { // getMail();
                String userName = params.getString(0);
                String[] headers = messageLib.getMail(userName);
                JSONArray headersJsonArr = new JSONArray();
                for (int i = 0; i < headers.length; i++) {
                    headersJsonArr.put(headers[i]);
                }
                debug("method getMail() is called ");
                result.put("result",headersJsonArr);
            } else {
                debug("Unable to match method: " + method + ". Returning 0.");
                result.put("result",0.0);
            }
        } catch (Exception ex) {
            System.out.println("exception in callMethod: " + ex.getMessage());
        }
        return result.toString();
    }
}