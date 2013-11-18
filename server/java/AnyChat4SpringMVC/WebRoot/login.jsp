<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
  </head>
  
  <body>
  <form action="${pageContext.request.contextPath }/login.do" method="post">
 	用户名：<input type="text" name="uname" /><br/>
 	密码：<input type="password" name="upass"/><br/>
 	<input type="submit" value="提交" />
  </form>
  </body>
</html>
