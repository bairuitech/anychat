本示例程序是对AnyChat的应用接入到SDK平台进行应用签名的服务器示例程序。该程序为命令行程序，运行后将提供HTTP服务，接受POST请求的参数生成应用签名。

如何运行
1. 双击“AnyChatSignServer.exe”程序或在命令行中运行“AnyChatSignServer.exe”；
2. 通过http post工具或客户端，访问http://ip:port/，例如如下的ajax访问

$.ajax( {
    url : "http://127.0.0.1:8980/",
    dataType : "json", //传参的数据类型
    type : "post", //传参方式，get 或post
    data : {
        userId : 10001,
	strUserId : "",
	appId : DAA47245-6BB5-4BE7-AAA1-6E33EF9826BA
    },
    error : function(data) { //若Ajax处理失败后返回的信息
    },
    success : function(data) { //若Ajax处理成功后返回的信息
    }
});


常见问题
1.如何判断服务器程序是否已正常运行？
在Chrome、Firefox等浏览器中访问Http://ip:port/，会在页面中提示“Welcome to AnyChatSignServer!”

2.运行“AnyChatSignServer.exe”程序后，不能成功启动，会显示“拒绝访问”的输出，该如何操作？
2.1、首先“以管理员身份运行”命令行程序（cmd）；
2.2、在命令行中输入“netsh http add urlacl url=http://IP:Port/ user=Tester”,注：IP、Port改为服务器的IP和端口(如：8980)；Tester 即计算机名
2.3、在命令行中输入“AnyChatSignServer.exe”，运行服务器签名程序。
  会输出：已启动HTTP服务，URL为：http://IP:Port/ 
          =============按字母“Q”键退出！============= 
  注：IP、Port为服务器的IP和端口


