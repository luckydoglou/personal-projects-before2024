package ser321.assign6.xhuan127.java.client;

import ser321.assign6.xhuan127.java.server.Message;
import ser321.assign6.xhuan127.java.server.Server_MessageLibraryInterface;
import java.net.*;
import java.io.*;
import java.util.ArrayList;
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
 * The student collection client proxy implements the server methods
 * by marshalling/unmarshalling parameters and results and using a TCP
 * connection to request the method be executed on the server.
 * Byte arrays are used for communication to support multiple langs.
 *
 * @author Tim Lindquist ASU Polytechnic Department of Engineering
 * @author Xiaolou Huang xhuan127@asu.edu, Software Engineering
 * @version April 2019
 */
public class Client_TcpProxy extends Object implements Server_MessageLibraryInterface {

    private static final boolean debugOn = false;
    private static final int buffSize = 4096;
    private static int id = 0;
    private String host;
    private int port;

    public Client_TcpProxy (String host, int port){
        this.host = host;
        this.port = port;
    }

    private void debug(String message) {
        if (debugOn)
            System.out.println("debug: "+message);
    }

    public String callMethod(String method, Object[] params) {
        JSONObject theCall = new JSONObject();
        String ret = "{}";
        try {
            debug("Request is: "+theCall.toString());
            theCall.put("method",method);
            //theCall.put("id",id);
            theCall.put("jsonrpc","2.0");
            ArrayList<Object> al = new ArrayList();
            for (int i=0; i < params.length; i++) {
                al.add(params[i]);
            }
            JSONArray paramsJson = new JSONArray(al);
            theCall.put("params",paramsJson);
            Socket sock = new Socket(host, port);
            OutputStream os = sock.getOutputStream();
            InputStream is = sock.getInputStream();
            int numBytesReceived;
            int bufLen = 1024;
            String strToSend = theCall.toString();
            byte bytesReceived[] = new byte[buffSize];
            byte bytesToSend[] = strToSend.getBytes();
            os.write(bytesToSend,0,bytesToSend.length);
            numBytesReceived = is.read(bytesReceived,0,bufLen);
            ret = new String(bytesReceived,0,numBytesReceived);
            debug("callMethod received from server: "+ret);
            os.close();
            is.close();
            sock.close();
        } catch(Exception ex) {
            System.out.println("exception in callMethod: "+ex.getMessage());
        }
        return ret;
    }

//    public boolean saveToJsonFile() {
//        boolean ret = false;
//        String result = callMethod("saveToJsonFile", new Object[]{});
//        JSONObject res = new JSONObject(result);
//        ret = res.optBoolean("result",false);
//        return ret;
//    }

//    public boolean resetFromJsonFile() {
//        boolean ret = false;
//        String result = callMethod("resetFromJsonFile", new Object[]{});
//        JSONObject res = new JSONObject(result);
//        ret = res.optBoolean("result",false);
//        return ret;
//    }

    public String[] getMessageFromHeaders(String userName) {
        String result = callMethod("getMessageFromHeaders", new Object[] {userName});
        JSONObject res = new JSONObject(result);
        JSONArray headerArr = res.optJSONArray("result");
        String[] headers = new String[headerArr.length()];
        for (int i = 0; i < headerArr.length(); i++) {
            headers[i] = headerArr.get(i).toString();
        }
        return headers;
    }
    
    public Message getMessage(String header, String userName) {
        String result = callMethod("getMessage", new Object[] {header, userName});
        JSONObject res = new JSONObject(result);
        String msgJsonStr = res.optString("result");
        Message msg = new Message(msgJsonStr);
        return msg;
    }

    public boolean deleteMessage(String header, String userName) {
        String result = callMethod("deleteMessage", new Object[] {header, userName});
        JSONObject res = new JSONObject(result);
        boolean isDeleted = res.getBoolean("result");
        return isDeleted;
    }
    
    public boolean sendClearText(Message aMessage, String fromUser) {
        String result = callMethod("sendClearText", new Object[] {aMessage.toJSONObject(), fromUser});
        JSONObject res = new JSONObject(result);
        boolean isSent = res.getBoolean("result");
        return isSent;
    }

    public String[] getMail(String userName) {
        String result = callMethod("getMail", new Object[] {userName});
        JSONObject res = new JSONObject(result);
        JSONArray headerArr = res.optJSONArray("result");
        String[] headers = new String[headerArr.length()];
        for (int i = 0; i < headerArr.length(); i++) {
            headers[i] = headerArr.get(i).toString();
        }
        return headers;
    }
    
}