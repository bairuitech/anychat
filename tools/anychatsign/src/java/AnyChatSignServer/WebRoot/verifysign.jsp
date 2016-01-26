<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="com.bairuitech.anychat.*"%>
<%@ page import="java.util.*"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>验证签名</title>
	<meta charset="utf-8">
	<meta content="IE=edge,chrome=1" http-equiv="X-UA-Compatible">
	<link rel="stylesheet" href="bootstrap-3.3.5-dist/css/bootstrap.min.css">    
  </head>
  <%  
	  int userId = Integer.valueOf(request.getParameter("userId"));
  	  String sign = new String(request.getParameter("sign"));
	  int timestamp = Integer.valueOf(request.getParameter("timestamp"));
	  
      int result = AnyChatSignUtils.verifySign(userId, sign, timestamp);
      String resultStr="签名验证失败，错误码为:"+result;
      
      if (result == 0) {
      	 resultStr="签名验证成功!";
      }
  %>
  <body>
	<div class="container">
	<div class="page-header">
    	<h1>验证用户签名</h1>
	</div>
	<div class="alert alert-info"><%=resultStr %></div>
		
	<a class="btn btn-default" href="index.jsp" role="button">返回首页</a>
	</div>
	
  </body>
</html>
