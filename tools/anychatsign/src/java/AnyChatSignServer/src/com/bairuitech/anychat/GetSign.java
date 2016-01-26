package com.bairuitech.anychat;

import java.io.IOException;
import java.io.PrintWriter;

import javax.json.Json;
import javax.json.JsonObject;
import javax.servlet.ServletException;
import javax.servlet.http.*;

public class GetSign extends HttpServlet {

    private static final long serialVersionUID = 2668913382477220913L;

    public GetSign() {
        super();
    }


    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        int userId = Integer.valueOf(request.getParameter("userId"));
        
        SignResult signResult = AnyChatSignUtils.getRsaSign(userId);       
        
        response.setCharacterEncoding("utf8");
        response.setContentType("application/json;charset=UTF-8"); 
        response.addHeader("Access-Control-Allow-Origin", "*");
        JsonObject obj = Json.createObjectBuilder()
                        .add("errorcode", signResult.getErrorcode())
                        .add("timestamp", signResult.getTimestamp())
                        .add("sigStr", signResult.getSigStr())
                        .build();
                
        PrintWriter out = response.getWriter();
        
        System.out.println(obj.toString());
        out.write(obj.toString());
        out.flush();
        out.close();

    }

}
