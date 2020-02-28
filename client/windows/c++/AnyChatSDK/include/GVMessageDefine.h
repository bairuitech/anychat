// GVMessageDefine.h: interface for the SDK Message.
//
//////////////////////////////////////////////////////////////////////

#if !defined(GV_MESSAGE_DEFINE__)
#define GV_MESSAGE_DEFINE__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WM_USER
#define WM_USER     0x0400
#endif

#define	WM_GV	WM_USER + 200

#define WM_GV_CONNECT				WM_GV + 1		///< �ͻ������ӷ�������wParam��BOOL����ʾ�Ƿ����ӳɹ�
#define WM_GV_LOGINSYSTEM			WM_GV + 2		///< �ͻ��˵�¼ϵͳ��wParam��INT����ʾ�Լ����û�ID�ţ�lParam��INT����ʾ��¼�����0 �ɹ�������Ϊ������룬�ο�������붨��
#define WM_GV_ENTERROOM				WM_GV + 3		///< �ͻ��˽��뷿�䣬wParam��INT����ʾ�����뷿���ID�ţ�lParam��INT����ʾ�Ƿ���뷿�䣺0�ɹ����룬����Ϊ�������
#define WM_GV_MICSTATECHANGE		WM_GV + 4		///< �û�����Ƶ�豸״̬�仯��Ϣ��wParam��INT����ʾ�û�ID�ţ�lParam��BOOL����ʾ���û��Ƿ��Ѵ���Ƶ�ɼ��豸
#define WM_GV_USERATROOM			WM_GV + 5		///< �û����루�뿪�����䣬wParam��INT����ʾ�û�ID�ţ�lParam��BOOL����ʾ���û��ǽ��루TRUE�����뿪��FALSE������
#define WM_GV_LINKCLOSE				WM_GV + 6		///< ���������ѹرգ�����Ϣֻ���ڿͻ������ӷ������ɹ�֮�������쳣�ж�֮ʱ������wParam��INT����ʾ���ӶϿ���ԭ��
#define WM_GV_ONLINEUSER			WM_GV + 7		///< �յ���ǰ����������û���Ϣ�����뷿��󴥷�һ�Σ�wParam��INT����ʾ�����û����������Լ�����lParam��INT����ʾ����ID
#define WM_GV_FORTUNEMENU			WM_GV + 8		///< �û�ѡ����һ��Ƹ��˵��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�Ƹ��˵���ǣ�ָʾ��ѡ������һ��˵�
#define WM_GV_ROOMWAITQUEUE			WM_GV + 9		///< �û��յ���ǰ����ȴ�������Ϣ��wParam��INT����ʾ�û�ǰ��Ķ��г��ȣ�lParam��INT����ʾ��ǰ�����ܵĵȴ����г���
#define WM_GV_ENTERREQUEST			WM_GV + 10		///< �û�������뷿����Ϣ��wParam��INT����ʾ�û�ID�ţ�lParam��BOOL����ʾ���û���������루TRUE��������뿪��FALSE������ȴ�����

#define WM_GV_CAMERASTATE			WM_GV + 11		///< �û�����ͷ״̬�����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ����ͷ�ĵ�ǰ״̬������Ϊ��GV_CAMERA_STATE_XXXX
#define WM_GV_CHATMODECHG			WM_GV + 12		///< �û�����ģʽ�����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�û��ĵ�ǰ����ģʽ
#define WM_GV_ACTIVESTATE			WM_GV + 13		///< �û��״̬�����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�û��ĵ�ǰ�״̬
#define WM_GV_P2PCONNECTSTATE		WM_GV + 14		///< �����û��������û���P2P��������״̬�����仯��wParam��INT����ʾ�����û�ID�ţ�lParam��INT����ʾ�����û��������û��ĵ�ǰP2P��������״̬
#define WM_GV_VIDEOSIZECHG			WM_GV + 15		///< �û���Ƶ�ֱ��ʷ����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�û�����Ƶ�ֱ������ֵ����16λ��ʾ��ȣ���16λ��ʾ�߶ȣ�
#define WM_GV_USERINFOUPDATE		WM_GV + 16		///< �û���Ϣ����֪ͨ��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�������
#define WM_GV_FRIENDSTATUS			WM_GV + 17		///< ��������״̬�仯��wParam��INT����ʾ�����û�ID�ţ�lParam��INT����ʾ�û��ĵ�ǰ�״̬��0 ���ߣ� 1 ����
#define WM_GV_OBJECTEVENT			WM_GV + 18		///< �����¼�֪ͨ��wParam��INT����ʾ�������ͣ�lParam��INT����ʾ����ID
#define WM_GV_SESSIONKEEP			WM_GV + 19		///< �Ự�����¼���wParam��INT����ʾ�Ự����״̬��0 �Ự���ֿ�ʼ�� 1 �Ự���ֽ�����lParam��INT����ʾ�������

#define WM_GV_PRIVATEREQUEST		WM_GV + 21		///< �û�����˽������wParam��INT����ʾ�����ߵ��û�ID�ţ�lParam��INT����ʾ˽�������ţ���ʶ������
#define WM_GV_PRIVATEECHO			WM_GV + 22		///< �û��ظ�˽������wParam��INT����ʾ�ظ��ߵ��û�ID�ţ�lParam��INT��Ϊ�������
#define WM_GV_PRIVATEEXIT			WM_GV + 23		///< �û��˳�˽�ģ�wParam��INT����ʾ�˳��ߵ��û�ID�ţ�lParam��INT��Ϊ�������
#define WM_GV_SERVERCFGUPDATE		WM_GV + 24		///< ���������ò�������

#define WM_GV_EXTENDBTNPRESS		WM_GV + 31		///< �û�������չ��ť��wParam��INT����ʾ��ť����Ӧ���û�ID�ţ�lParam��DWORD��ָʾ��ť�����½ǣ�������Ļλ��(x,y)���û��������øò�����ʾ�˵���
#define WM_GV_VIDEOFULLSCREEN		WM_GV + 32		///< �û���Ƶȫ��֪ͨ��wParam��INT����ʾ�û�ID��lParam(DWORD)��ʾ��ǰ��Ƶ�Ƿ�ȫ����ʾ

#define WM_GV_SDKWARNING			WM_GV + 41		///< SDK������Ϣ����SDK�����й������Լ췢���쳣״̬ʱ�������ϲ㷢�͸���Ϣ��wParam��INT����ʾ������룬����Ϊ��GV_ERR_WARNING_XXXX

#define WM_GV_AUDIOPLAYCTRL			WM_GV + 100		///< ��Ƶ�����豸���ƣ�wParam:1 �򿪲������� 0 �رղ������� lParam��profile��androidƽ̨�ڲ�ʹ��
#define WM_GV_AUDIORECCTRL			WM_GV + 101		///< ��Ƶ¼���豸���ƣ�wParam:1 ����Ƶ�ɼ��豸��0 �ر���Ƶ�ɼ��豸
#define WM_GV_VIDEOCAPCTRL			WM_GV + 102		///< ��Ƶ�ɼ����ƣ�wParam: 1 ��ʼ�ɼ��� 0 �رղɼ�

#endif // !defined(GV_MESSAGE_DEFINE__)
