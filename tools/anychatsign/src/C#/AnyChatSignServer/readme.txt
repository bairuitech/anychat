��ʾ�������Ƕ�AnyChat��Ӧ�ý��뵽SDKƽ̨����Ӧ��ǩ���ķ�����ʾ�����򡣸ó���Ϊ�����г������к��ṩHTTP���񣬽���POST����Ĳ�������Ӧ��ǩ����

������к�ʹ��
1. ��Ӧ�ã�ͨ����ƽ̨�����ȺWeb����̨������Ӧ�ã���˽Կ�ļ����Ƶ������Ŀ¼����������Ϊ��private_rsa.pem��
2. ˫����AnyChatSignServer.exe��������������������С�AnyChatSignServer.exe����
3. ͨ��http post���߻�ͻ��ˣ�����http://ip:port/���������µ�ajax����

$.ajax( {
    url : "http://127.0.0.1:8980/",
    dataType : "json", //���ε���������
    type : "post", //���η�ʽ��get ��post
    data : {
        userId : 10001,
	strUserId : "",
	appId : DAA47245-6BB5-4BE7-AAA1-6E33EF9826BA
    },
    error : function(data) { //��Ajax����ʧ�ܺ󷵻ص���Ϣ
    },
    success : function(data) { //��Ajax����ɹ��󷵻ص���Ϣ
    }
});



��������
1.����жϷ����������Ƿ����������У�
��Chrome��Firefox��������з���Http://ip:port/������ҳ������ʾ��Welcome to AnyChatSignServer!��

2.���С�AnyChatSignServer.exe������󣬲��ܳɹ�����������ʾ���ܾ����ʡ������������β�����
2.1�����ȡ��Թ���Ա������С������г���cmd����
2.2���������������롰netsh http add urlacl url=http://IP:Port/ user=Tester��,ע��IP��Port��Ϊ��������IP�Ͷ˿�(�磺8980)��Tester ���������
2.3���������������롰AnyChatSignServer.exe�������з�����ǩ������
  �������������HTTP����URLΪ��http://IP:Port/ 
          =============����ĸ��Q�����˳���============= 
  ע��IP��PortΪ��������IP�Ͷ˿�


