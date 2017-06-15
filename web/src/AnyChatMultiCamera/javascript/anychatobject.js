// AnyChat for Web SDK
// ��Ҫ�Ը��ļ������κ��޸ģ�������SDKʱ���°汾����ֱ�Ӹ��Ǿɰ汾

/********************************************
 *			ҵ�����������				*
 *******************************************/

 
 // �������Ͷ���
var ANYCHAT_OBJECT_TYPE_AREA		=	4;		// ��������
var ANYCHAT_OBJECT_TYPE_QUEUE		=	5;		// ���ж���
var ANYCHAT_OBJECT_TYPE_AGENT		=	6;		// �ͷ�����
var ANYCHAT_OBJECT_TYPE_CLIENTUSER	=	8;		// �ͻ����û������������������������
var ANYCHAT_OBJECT_TYPE_SKILL		=	9;		// ҵ���ܶ���
var ANYCHAT_OBJECT_TYPE_QUEUEGROUP	=	10;		// ���з������

// ͨ�ñ�ʶ����
var ANYCHAT_OBJECT_FLAGS_CLIENT		=	0;		// ��ͨ�ͻ�
var ANYCHAT_OBJECT_FLAGS_AGENT		=	2;		// ��ϯ�û�
var ANYCHAT_OBJECT_FLAGS_MANANGER	=	4;		// �����û�
var ANYCHAT_OBJECT_FLAGS_AUTOMODE	=	16;		// �Զ�����ģʽ

var ANYCHAT_INVALID_OBJECT_ID		=	-1;		// ��Ч�Ķ���ID

// ��ϯ����״̬����
var ANYCHAT_AGENT_STATUS_CLOSEED	=	0;		// �رգ��������ṩ����
var ANYCHAT_AGENT_STATUS_WAITTING	=	1;		// �ȴ��У�����ʱ�����û�����
var ANYCHAT_AGENT_STATUS_WORKING	=	2;		// �����У�����Ϊ�û�����
var ANYCHAT_AGENT_STATUS_PAUSED		=	3;		// ��ͣ����
var ANYCHAT_AGENT_STATUS_OFFLINE	=	10;		// ����



/**
 *	�������Զ���
 */

// ���󹫹���Ϣ���Ͷ���
var ANYCHAT_OBJECT_INFO_FLAGS		=	7;		// �������Ա�־
var ANYCHAT_OBJECT_INFO_NAME		=	8;		// ��������
var ANYCHAT_OBJECT_INFO_PRIORITY	=	9;		// �������ȼ�
var ANYCHAT_OBJECT_INFO_ATTRIBUTE	=	10;		// ����ҵ������
var ANYCHAT_OBJECT_INFO_DESCRIPTION	=	11;		// ��������
var ANYCHAT_OBJECT_INFO_INTTAG		=	12;		// �����ǩ�����ͣ��ϲ�Ӧ���Զ���
var ANYCHAT_OBJECT_INFO_STRINGTAG	=	13;		// �����ǩ���ַ������ϲ�Ӧ���Զ���
var ANYCHAT_OBJECT_INFO_GUID		=	14;		// ����GUID
var ANYCHAT_OBJECT_INFO_STATUSJSON	=	15;		// ����״̬���Լ���


// ����������Ϣ���Ͷ���
var ANYCHAT_AREA_INFO_AGENTCOUNT	=	401;	// ��������ͷ��û���
var ANYCHAT_AREA_INFO_GUESTCOUNT	=	402;	// ���������ڷÿ͵��û�����û��������е��û���
var ANYCHAT_AREA_INFO_QUEUEUSERCOUNT=	403;	// �����������Ŷӵ��û���
var ANYCHAT_AREA_INFO_QUEUECOUNT	=	404;	// ���������ڶ��е�����
var ANYCHAT_AREA_INFO_AGENTIDLIST	=	405;	// ��������ͷ�ID�б�
var ANYCHAT_AREA_INFO_IDLEAGENTCOUNT=	406;	// �������������ϯ����
var ANYCHAT_AREA_INFO_STATUSJSON	=	407;	// ��������״̬��Ϣ������Json����
var ANYCHAT_AREA_INFO_WAITINGCOUNT	=	408;	// ���������ڵȺ�����û��������˶��У���û����ϯ������û���

// ����״̬��Ϣ���Ͷ���
var ANYCHAT_QUEUE_INFO_MYSEQUENCENO	=	501;	// �Լ��ڸö����е����
var ANYCHAT_QUEUE_INFO_BEFOREUSERNUM=	502;	// �����Լ�ǰ	����û���
var ANYCHAT_QUEUE_INFO_MYENTERQUEUETIME=503;	// ������е�ʱ��
var ANYCHAT_QUEUE_INFO_LENGTH		=	504;	// ���г��ȣ��ж��������Ŷӣ�������
var ANYCHAT_QUEUE_INFO_WAITTIMESECOND=	508;	// �Լ��ڶ����еĵȴ�ʱ�䣨�Ŷ�ʱ��������λ����
var ANYCHAT_QUEUE_INFO_AGENTINFO	=	509;	// ����ǰ���е���ϯ��Ϣ������Json����

// �ͷ�״̬��Ϣ���Ͷ���
var ANYCHAT_AGENT_INFO_SERVICESTATUS=	601;	// ����״̬������
var ANYCHAT_AGENT_INFO_SERVICEUSERID=	602;	// ��ǰ������û�ID������
var ANYCHAT_AGENT_INFO_SERVICEBEGINTIME=603;	// ��ǰ����Ŀ�ʼʱ�䣬����
var ANYCHAT_AGENT_INFO_SERVICETOTALTIME=604;	// �ۼƷ���ʱ�䣬���ͣ���λ����
var ANYCHAT_AGENT_INFO_SERVICETOTALNUM=	605;	// �ۼƷ�����û���������
var ANYCHAT_AGENT_INFO_SERVICEUSERINFO=	606;	// ��ǰ�����û���Ϣ���ַ���
var ANYCHAT_AGENT_INFO_RELATEQUEUES	=	607;	// ��������List���ַ���




/**
 *	���󷽷�����
 */

// ���󹫹��������Ƴ�������
var ANYCHAT_OBJECT_CTRL_CREATE		=	2;		// ����һ������
var ANYCHAT_OBJECT_CTRL_SYNCDATA	=	3;		// ͬ���������ݸ�ָ���û���dwObjectId=-1����ʾͬ�������͵����ж���
var ANYCHAT_OBJECT_CTRL_DEBUGOUTPUT	=	4;		// ���������Ϣ���
var ANYCHAT_OBJECT_CTRL_DELETE		=	5;		// ɾ������
var ANYCHAT_OBJECT_CTRL_MODIFY		=	6;		// �޸Ķ�����Ϣ

// ����������Ƴ�������
var ANYCHAT_AREA_CTRL_USERENTER		=	401;	// �����������
var ANYCHAT_AREA_CTRL_USERLEAVE		=	402;	// �뿪��������

// ���в������Ƴ�������
var ANYCHAT_QUEUE_CTRL_USERENTER	=	501;	// �������
var ANYCHAT_QUEUE_CTRL_USERLEAVE	=	502;	// �뿪����

// �ͷ��������Ƴ�������
var ANYCHAT_AGENT_CTRL_SERVICESTATUS=	601;	// ��ϯ����״̬���ƣ���ͣ���񡢹����С��رգ�
var ANYCHAT_AGENT_CTRL_SERVICEREQUEST=	602;	// ��������
var ANYCHAT_AGENT_CTRL_FINISHSERVICE=	604;	// ��������
var ANYCHAT_AGENT_CTRL_EVALUATION	=	605;	// �������ۣ�wParamΪ�ͷ�userid��lParamΪ���֣�lpStrValueΪ����






/**
 *	�����첽�¼�����
 */

// ���󹫹��¼���������
var ANYCHAT_OBJECT_EVENT_UPDATE		=	1;		// �������ݸ���
var ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH=2;		// ��������ͬ������

// ���������¼���������
var ANYCHAT_AREA_EVENT_STATUSCHANGE	=	401;	// ��������״̬�仯
var ANYCHAT_AREA_EVENT_ENTERRESULT	=	402;	// �������������
var ANYCHAT_AREA_EVENT_USERENTER	=	403;	// �û������������
var ANYCHAT_AREA_EVENT_USERLEAVE	=	404;	// �û��뿪��������
var ANYCHAT_AREA_EVENT_LEAVERESULT	=	405;	// �뿪����������


// �����¼���������
var ANYCHAT_QUEUE_EVENT_STATUSCHANGE=	501;	// ����״̬�仯
var ANYCHAT_QUEUE_EVENT_ENTERRESULT	=	502;	// ������н��
var ANYCHAT_QUEUE_EVENT_USERENTER	=	503;	// �û��������
var ANYCHAT_QUEUE_EVENT_USERLEAVE	=	504;	// �û��뿪����
var ANYCHAT_QUEUE_EVENT_LEAVERESULT	=	505;	// �뿪���н��


// ��ϯ�¼���������
var ANYCHAT_AGENT_EVENT_STATUSCHANGE=	601;	// ��ϯ״̬�仯
var ANYCHAT_AGENT_EVENT_SERVICENOTIFY=	602;	// ��ϯ����֪ͨ���ĸ��û����ĸ��ͷ�����ҵ��
var ANYCHAT_AGENT_EVENT_WAITINGUSER	=	603;	// ��ʱû�пͻ�����ȴ�
var ANYCHAT_AGENT_EVENT_ISREADY		=	604;	// ��ϯ׼���ã����Է������


