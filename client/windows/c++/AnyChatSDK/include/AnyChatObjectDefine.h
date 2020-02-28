#if !defined(_ANYCHAT_OBJECTDEFINE_H_INCLUDED_)
#define _ANYCHAT_OBJECTDEFINE_H_INCLUDED_

// �������Ͷ���
#define ANYCHAT_OBJECT_TYPE_AREA			4	///< ��������
#define ANYCHAT_OBJECT_TYPE_QUEUE			5	///< ���ж���
#define ANYCHAT_OBJECT_TYPE_AGENT			6	///< �ͷ�����
#define ANYCHAT_OBJECT_TYPE_CLIENTUSER		8	///< �ͻ����û������������������������
#define ANYCHAT_OBJECT_TYPE_SKILL			9	///< ҵ���ܶ���
#define ANYCHAT_OBJECT_TYPE_QUEUEGROUP		10	///< ���з������

// ͨ�ñ�ʶ����
#define ANYCHAT_OBJECT_FLAGS_CLIENT			0x0000	///< ��ͨ�ͻ�
#define ANYCHAT_OBJECT_FLAGS_AGENT			0x0002	///< ��ϯ�û�
#define ANYCHAT_OBJECT_FLAGS_MANANGER		0x0004	///< �����û�
#define ANYCHAT_OBJECT_FLAGS_AUTOMODE		0x0010	///< �Զ�����ģʽ
#define ANYCHAT_OBJECT_FLAGS_GUESTLOGIN		0x0020	///< �ο͵�¼��ʽ
#define ANYCHAT_OBJECT_FLAGS_GLOBAL			0x0040	///< ȫ�ַ���
#define ANYCHAT_OBJECT_FLAGS_CONNECT		0x0080	///< �������Ӷ���
#define ANYCHAT_OBJECT_FLAGS_MULTICHANNEL	0x0100	///< ��ͨ��ģʽ
#define ANYCHAT_OBJECT_FLAGS_QUEUEUSERLIST	0x0200	///< ֪ͨ�����û��б�
#define ANYCHAT_OBJECT_FLAGS_AREAUSERINFO	0x0400	///< Ӫҵ���û���ϸ��Ϣ
#define ANYCHAT_OBJECT_FLAGS_MANUALSYNCAREA	0x0800	///< �ֹ�ͬ��Ӫҵ�����ݣ���ֹ�Զ���

#define ANYCHAT_INVALID_OBJECT_ID	((DWORD)-1)	///< ��Ч�Ķ���ID
#define ANYCHAT_MAX_OBJECT_CHANNELS			36	///< ���������ͨ����

// ��ϯ����״̬����
#define ANYCHAT_AGENT_STATUS_CLOSEED		0	///< �رգ��������ṩ����׼����
#define ANYCHAT_AGENT_STATUS_WAITTING		1	///< �ȴ��У�����ʱ�����û�����ʾ�У�
#define ANYCHAT_AGENT_STATUS_WORKING		2	///< �����У�����Ϊ�û�����
#define ANYCHAT_AGENT_STATUS_PAUSED			3	///< ��ͣ����ʾæ��
#define ANYCHAT_AGENT_STATUS_OFFLINE		10	///< ����


/**
 *	�������Զ���
 */

// ���󹫹���Ϣ���Ͷ���
#define ANYCHAT_OBJECT_INFO_FLAGS			7	///< �������Ա�־
#define ANYCHAT_OBJECT_INFO_NAME			8	///< ��������
#define ANYCHAT_OBJECT_INFO_PRIORITY		9	///< �������ȼ�
#define ANYCHAT_OBJECT_INFO_ATTRIBUTE		10	///< ����ҵ������
#define ANYCHAT_OBJECT_INFO_DESCRIPTION		11	///< ��������
#define ANYCHAT_OBJECT_INFO_INTTAG			12	///< �����ǩ�����ͣ��ϲ�Ӧ���Զ���
#define ANYCHAT_OBJECT_INFO_STRINGTAG		13	///< �����ǩ���ַ������ϲ�Ӧ���Զ���
#define ANYCHAT_OBJECT_INFO_GUID			14	///< ����GUID
#define ANYCHAT_OBJECT_INFO_STATUSJSON		15	///< ����״̬���Լ���
#define ANYCHAT_OBJECT_INFO_STRINGID		16	///< �����ַ���ID
#define ANYCHAT_OBJECT_INFO_STATISTICS		17	///< ����ͳ������


// ����������Ϣ���Ͷ���
#define ANYCHAT_AREA_INFO_AGENTCOUNT		401	///< ��������ͷ��û���
#define ANYCHAT_AREA_INFO_GUESTCOUNT		402	///< ���������ڷÿ͵��û�����û��������е��û���
#define ANYCHAT_AREA_INFO_QUEUEUSERCOUNT	403	///< �����������Ŷӵ��û���
#define ANYCHAT_AREA_INFO_QUEUECOUNT		404	///< ���������ڶ��е�����
#define ANYCHAT_AREA_INFO_AGENTIDLIST		405	///< ��������ͷ�ID�б�
#define ANYCHAT_AREA_INFO_IDLEAGENTCOUNT	406	///< �������������ϯ����
#define ANYCHAT_AREA_INFO_STATUSJSON		407	///< ��������״̬��Ϣ������Json����
#define ANYCHAT_AREA_INFO_WAITINGCOUNT		408	///< ���������ڵȺ�����û��������˶��У���û����ϯ������û���
#define ANYCHAT_AREA_INFO_WORKAGENTCOUNT	409	///< ������������ϯ����
#define ANYCHAT_AREA_INFO_BUSYAGENTCOUNT	410	///< ��������ʾæ��ϯ����

// ����״̬��Ϣ���Ͷ���
#define ANYCHAT_QUEUE_INFO_MYSEQUENCENO		501	///< �Լ��ڸö����е����
#define ANYCHAT_QUEUE_INFO_BEFOREUSERNUM	502	///< �����Լ�ǰ	����û���
#define ANYCHAT_QUEUE_INFO_MYENTERQUEUETIME	503	///< ������е�ʱ��
#define ANYCHAT_QUEUE_INFO_QUEUELENGTH		504	///< ���г��ȣ��ж��������Ŷӣ�������
#define ANYCHAT_QUEUE_INFO_WAITTIMESECOND	508	///< �Լ��ڶ����еĵȴ�ʱ�䣨�Ŷ�ʱ��������λ����
#define ANYCHAT_QUEUE_INFO_AGENTINFO		509	///< ����ǰ���е���ϯ��Ϣ������Json����
#define ANYCHAT_QUEUE_INFO_USERIDLIST		510	///< �����û�ID�б�
#define ANYCHAT_QUEUE_INFO_WAITINGTIMELIST	511	///< �����û��ȴ�ʱ���б�(��λ����)
#define ANYCHAT_QUEUE_INFO_USERINFOLIST		512	///< �����û���Ϣ�б�


// �ͷ�״̬��Ϣ���Ͷ���
#define ANYCHAT_AGENT_INFO_SERVICESTATUS	601	///< ����״̬������
#define ANYCHAT_AGENT_INFO_SERVICEUSERID	602	///< ��ǰ������û�ID������
#define ANYCHAT_AGENT_INFO_SERVICEBEGINTIME	603	///< ��ǰ����Ŀ�ʼʱ�䣬����
#define ANYCHAT_AGENT_INFO_SERVICETOTALTIME	604	///< �ۼƷ���ʱ�䣬���ͣ���λ����
#define ANYCHAT_AGENT_INFO_SERVICETOTALNUM	605	///< �ۼƷ�����û���������
#define ANYCHAT_AGENT_INFO_SERVICEUSERINFO	606	///< ��ǰ�����û���Ϣ���ַ���
#define ANYCHAT_AGENT_INFO_RELATEQUEUES		607	///< ��������List���ַ���
#define ANYCHAT_AGENT_INFO_SERVICEFAILNUM	608	///< ����ʧ���û���
#define ANYCHAT_AGENT_INFO_MAXCHANNELNUM	609	///< ������ͨ����������



/**
 *	���󷽷�����
 */

// ���󹫹��������Ƴ�������
#define ANYCHAT_OBJECT_CTRL_CREATE			2	///< ����һ������
#define ANYCHAT_OBJECT_CTRL_SYNCDATA		3	///< ͬ���������ݸ�ָ���û���dwObjectId=-1����ʾͬ�������͵����ж���
#define ANYCHAT_OBJECT_CTRL_DEBUGOUTPUT		4	///< ���������Ϣ���
#define ANYCHAT_OBJECT_CTRL_DELETE			5	///< ɾ������
#define ANYCHAT_OBJECT_CTRL_MODIFY			6	///< �޸Ķ�����Ϣ

// ����������Ƴ�������
#define ANYCHAT_AREA_CTRL_USERENTER			401	///< �����������
#define ANYCHAT_AREA_CTRL_USERLEAVE			402	///< �뿪��������

// ���в������Ƴ�������
#define ANYCHAT_QUEUE_CTRL_USERENTER		501	///< �������
#define ANYCHAT_QUEUE_CTRL_USERLEAVE		502	///< �뿪����

// �ͷ��������Ƴ�������
#define ANYCHAT_AGENT_CTRL_SERVICESTATUS	601	///< ��ϯ����״̬���ƣ���ͣ���񡢹����С��رգ�
#define ANYCHAT_AGENT_CTRL_SERVICEREQUEST	602	///< ��������
#define ANYCHAT_AGENT_CTRL_STARTSERVICE		603	///< ��ʼ����wParamΪ�û�userid
#define ANYCHAT_AGENT_CTRL_FINISHSERVICE	604	///< ��������
#define ANYCHAT_AGENT_CTRL_EVALUATION		605	///< �������ۣ�wParamΪ�ͷ�userid��lParamΪ���֣�lpStrValueΪ����






/**
 *	�����첽�¼�����
 */

// ���󹫹��¼���������
#define ANYCHAT_OBJECT_EVENT_UPDATE			1	///< �������ݸ���
#define ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH	2	///< ��������ͬ������
#define ANYCHAT_OBJECT_EVENT_STATISTICS		3	///< ����ͳ�����ݸ���

// ���������¼���������
#define ANYCHAT_AREA_EVENT_STATUSCHANGE		401	///< ��������״̬�仯
#define ANYCHAT_AREA_EVENT_ENTERRESULT		402	///< �������������
#define ANYCHAT_AREA_EVENT_USERENTER		403	///< �û������������
#define ANYCHAT_AREA_EVENT_USERLEAVE		404	///< �û��뿪��������
#define ANYCHAT_AREA_EVENT_LEAVERESULT		405	///< �뿪����������


// �����¼���������
#define ANYCHAT_QUEUE_EVENT_STATUSCHANGE	501	///< ����״̬�仯
#define ANYCHAT_QUEUE_EVENT_ENTERRESULT		502	///< ������н��
#define ANYCHAT_QUEUE_EVENT_USERENTER		503	///< �û��������
#define ANYCHAT_QUEUE_EVENT_USERLEAVE		504	///< �û��뿪����
#define ANYCHAT_QUEUE_EVENT_LEAVERESULT		505	///< �뿪���н��
#define ANYCHAT_QUEUE_EVENT_STARTSERVICE	506	///< �û���ʼ������
#define ANYCHAT_QUEUE_EVENT_USERINFOLISTCHG	507	///< �����û��б����


// ��ϯ�¼���������
#define ANYCHAT_AGENT_EVENT_STATUSCHANGE	601	///< ��ϯ״̬�仯
#define ANYCHAT_AGENT_EVENT_SERVICENOTIFY	602	///< ��ϯ����֪ͨ���ĸ��û����ĸ��ͷ�����ҵ��
#define ANYCHAT_AGENT_EVENT_WAITINGUSER		603	///< ��ʱû�пͻ�����ȴ�
#define ANYCHAT_AGENT_EVENT_ISREADY			604	///< ��ϯ׼���ã����Է������




#endif // !defined(_ANYCHAT_OBJECTDEFINE_H_INCLUDED_)
