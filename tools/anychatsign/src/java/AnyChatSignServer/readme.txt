
本示例程序的目的是演示AnyChat接入签名的获取与认证。

环境配置：
1. 将文件anychatsign.dll放到环境变量“Path”指定的任意一个路径中
2. 在代码AnyChatSignUtils.java中配置应用ID，应用私钥，应用公钥
3. 配置java jdk环境，将本示例程序部署到web容器中

如何运行
1. 在浏览器中打开http://ip:port/AnyChatSignDemo/index.jsp,本页面通过jsp的方式演示签名的获取与认证
2. 通过http post工具或客户端，访问http://ip:port/AnyChatSignDemo/json/getSign，例如如下的ajax访问

$.ajax( {
    url : "http://127.0.0.1:9010/AnyChatSignDemo/json/getSign",
    dataType : "json", //传参的数据类型
    type : "post", //传参方式，get 或post
    data : {
        userId : 123456
    },
    error : function(data) { //若Ajax处理失败后返回的信息
    },
    success : function(data) { //若Ajax处理成功后返回的信息
    }
});  