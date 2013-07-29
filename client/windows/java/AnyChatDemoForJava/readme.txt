运行时需要相关的SDK库支持，在AnyChat for Windows SDK包的：bin\client目录下，部署方法可参考FAQ：
http://www.anychat.cn/faq/index.php?action=artikel&cat=7&id=242&artlang=zh

编译好的应用程序在SDK包的：bin\demo\AnyChatDemoForJava.jar，可直接运行

建议目录结构：

|--------应用程序.jar
|
|--------anychatcore4java.dll	(JNI封装，调用BRAnyChatCore)
|
|--------BRAnyChatCore.dll	AnyChat核心库
|
|--------video
|            |
|            |--------brMediaCore.dll
|            |--------brMediaShow.dll
|            ……