该目录下均为业务服务器程序示例代码（调用AnyChat Server SDK，Java语言），需与核心服务器配合才能正常工作。

1、AnyChatBussinessServer	调用AnyChat Server SDK的演示程序，有GUI界面，编译打包好的程序在bin\serversdk目录下，可以通过脚本：./runbusinessserver.sh启动

2、AnyChatSampleServer		调用AnyChat Server SDK的演示程序，没有GUI界面，编译打包好的程序在bin\serversdk目录下，可以通过脚本：./runsampleserver.sh启动

3、AnyChatCallCenterServer	视频呼叫中心业务服务器，实现了视频呼叫和大厅好友等功能，没有GUI界面，编译打包好的程序在bin\serversdk目录下，可以通过脚本：./runcallcenterserver.sh启动

4、AnyChat4SpringMVC		展示如何将AnyChat Server SDK部署到Java Web容器中

5、AnyChatCallCenter4SpringMVC	展示如何将AnyChat Server SDK部署到Java Web容器中，同时集成了视频呼叫、在线好友等业务逻辑


参考资料：
	有关AnyChat平台用户身份验证与第三方平台集成的问题
	http://bbs.anychat.cn/forum.php?mod=viewthread&tid=12&extra=page%3D1

	AnyChat使用攻略之独立部署Linux视频服务器
	http://bbs.anychat.cn/forum.php?mod=viewthread&tid=10&extra=page%3D1
	
	AnyChat业务服务器部署到Java Web容器（Tomcat）详细流程
	http://bbs.anychat.cn/forum.php?mod=viewthread&tid=335&extra=page%3D1
	
	AnyChat视频呼叫中心系统（AnyChatCallCenter）
	http://bbs.anychat.cn/forum.php?mod=viewthread&tid=13&extra=page%3D1

