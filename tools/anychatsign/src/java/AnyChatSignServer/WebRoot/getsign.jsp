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
    
    <title>获取签名</title>
	<meta charset="utf-8">
	<meta content="IE=edge,chrome=1" http-equiv="X-UA-Compatible">
	<link rel="stylesheet" href="bootstrap-3.3.5-dist/css/bootstrap.min.css">    
  </head>
  <%  
	  int userId = Integer.valueOf(request.getParameter("userId"));
  	  String password = new String(request.getParameter("password"));

      SignResult signResult = AnyChatSignUtils.getRsaSign(userId); 	  

      int timestamp = 0;
      String outSignStr = "";
      
      String resultStr="获取签名失败，错误码为:"+signResult.getErrorcode();
      
      if (signResult.getErrorcode() == 0) {
      	 resultStr="获取签名成功！";
      	 timestamp = signResult.getTimestamp();
      	 outSignStr = signResult.getSigStr();
      }
  %>
  <body>
	<div class="container">
	<div class="page-header">
    	<h1>获取用户签名</h1>
	</div>

	<div class="alert alert-info"><%=resultStr %></div>
		
	<form class="form-horizontal" action=verifysign.jsp method=post>
		<div class="form-group">
	      <label for="name" class="col-sm-2 control-label">用户ID:</label>
	      <div class="col-sm-8">
	         <input type="text" readonly="readonly" class="form-control" id="userId" name="userId" value="<%=userId%>">
	      </div>
	   </div>
	   <div class="form-group">
	      <label for="sign" class="col-sm-2 control-label">签名:</label>
	      <div class="col-sm-8">
	      	<textarea readonly="readonly" class="form-control" id="sign" rows="6" name="sign"><%=outSignStr%></textarea>  	
	      </div>
	   </div>
		<div class="form-group">
	      <label for="timestamp" class="col-sm-2 control-label">签发时间:</label>
	      <div class="col-sm-8">
	         <input type="text" readonly="readonly" class="form-control" id="timestamp" name="timestamp" value="<%=timestamp%>">
	      </div>
	   </div>
	   <div class="form-group">
	      <div class="col-sm-offset-2 col-sm-10">
	         <button type="submit" class="btn btn-default">验证签名</button>
	      </div>
	   </div>
	</form>
	</div>
  </body>
</html>
