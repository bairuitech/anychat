<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>登录</title>
	<meta charset="utf-8">
	<meta content="IE=edge,chrome=1" http-equiv="X-UA-Compatible">

	<link rel="stylesheet" href="bootstrap-3.3.5-dist/css/bootstrap.min.css">
  </head>
  
  <body>
    
	<div class="container">
		<div class="page-header">
	    	<h1>身份认证</h1>
		</div>
		<form class="form-horizontal" action=getsign.jsp method=post>
		   <div class="form-group">
		      <label for="userId" class="col-sm-2 control-label">用户ID:</label>
		      <div class="col-sm-8">
		         <input type="text" class="form-control" id="userId" 
		            name="userId" placeholder="请输入用户ID">
		      </div>
		   </div>
		   <div class="form-group">
		      <label for="password" class="col-sm-2 control-label">密码:</label>
		      <div class="col-sm-8">
		         <input type="password" class="form-control" id="password" 
		            name="password" placeholder="请输入密码">
		      </div>
		   </div>
		   <div class="form-group">
		      <div class="col-sm-offset-2 col-sm-10">
		         <button type="submit" class="btn btn-default">登录</button>
		      </div>
		   </div>
		</form>
		
		<div class="alert alert-info">
			用户输入用户名密码进行登录，登录服务器首先认证登录者身份的合法性，只有身份认证成功才能获取签名。
			本示例程序主要目的是演示签名获取和认证过程，将不做用户名密码的鉴权
		</div>
	</div>
  </body>
</html>
