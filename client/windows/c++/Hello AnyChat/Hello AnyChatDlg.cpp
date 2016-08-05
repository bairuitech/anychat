// Hello AnyChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include <WINSOCK2.H>
#include <afxinet.h>
#include "Hello AnyChat.h"
#include "Hello AnyChatDlg.h"
#include "VideoSetDlg.h"

#include <iostream>
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelloAnyChatDlg dialog

CHelloAnyChatDlg::CHelloAnyChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelloAnyChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelloAnyChatDlg)
	m_port = 0;
	m_iRoomID = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHelloAnyChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelloAnyChatDlg)
	DDX_Control(pDX, IDC_BUTTON_VIDEOCTRL, m_videoBtn);
	DDX_Control(pDX, IDC_BUTTON_AUDIOCTRL, m_audioBtn);
	DDX_Control(pDX, IDC_LIST_USERMSG, m_userList);
	DDX_Control(pDX, IDLOGOUT, m_logoutBtn);
	DDX_Control(pDX, IDLOGIN, m_loginBtn);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_ROOM, m_iRoomID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHelloAnyChatDlg, CDialog)
	//{{AFX_MSG_MAP(CHelloAnyChatDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_GV_CONNECT,OnGVClientConnect)
	ON_MESSAGE(WM_GV_LOGINSYSTEM,OnGVClientLogin)
	ON_MESSAGE(WM_GV_ENTERROOM,OnGVClientEnterRoom)
	ON_MESSAGE(WM_GV_ONLINEUSER,OnGVClientOnlineUser)
	ON_MESSAGE(WM_GV_USERATROOM,OnGVClientUserAtRoom)
	ON_MESSAGE(WM_GV_LINKCLOSE,OnGVClientLinkClose)
	ON_BN_CLICKED(IDLOGIN, OnLogin)
	ON_BN_CLICKED(IDLOGOUT, OnLogout)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USERMSG, OnClickListUserList)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, OnButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOCTRL, OnButtonVideoCtrl)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOCTRL, OnButtonAudioCtrl)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK1, &CHelloAnyChatDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelloAnyChatDlg message handlers

BOOL CHelloAnyChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	initUI();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHelloAnyChatDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHelloAnyChatDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ��Ƶ���ݻص�����
void CALLBACK VideoData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue)
{
	CHelloAnyChatDlg* pDemoDlg = (CHelloAnyChatDlg*)lpUserValue;
	if (pDemoDlg)
		pDemoDlg->DrawUserVideo(dwUserid,lpBuf,dwLen,bmiHeader);
}

// ��Ƶ���ݻص�����
void CALLBACK AudioData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue)
{
	CHelloAnyChatDlg*	pDemoDlg = (CHelloAnyChatDlg*)lpUserValue;
	if(pDemoDlg)
	{
		// do something ...
	}
}

/**
 *	�������Ļص�����
 */
void CALLBACK VolumeChange_CallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue)
{
}

void CHelloAnyChatDlg::initUI()
{
	// ��ʼ����Ƶ��������
	mVideoSetDlg = new VideoSetDlg();
	mbAudioSwitch = 0;

	m_iUserID[0] = -1;
	m_iUserID[1] = -1;

	// ��ʼ����¼����(ͨ����ȡ�ļ�)
	CHAR sIPAddress[32] = {0};
	CHAR sName[32] = {0};
	CHAR sPortNum[16] = {0};
	CHAR sRoomID[16] = {0};
	ifstream inFile;
	inFile.open("AnyChatLoginData.txt");
	if (inFile.is_open())
	{
		inFile>>sIPAddress;
		inFile>>sName;
		inFile>>sPortNum;
		inFile>>sRoomID;
	}

	SetDlgItemText(IDC_EDIT_IP, sIPAddress);
	SetDlgItemText(IDC_EDIT_NAME, sName);
	m_port = atoi(sPortNum);
	m_iRoomID = atoi(sRoomID);

	// ��ȡSDK�İ汾��Ϣ
	CString strSDKVer;
	DWORD dwMainVer;
	DWORD dwSubVer;
	CHAR szCompileTime[100] = {0};
	BRAC_GetSDKVersion(dwMainVer,dwSubVer,szCompileTime,sizeof(szCompileTime));
	strSDKVer.Format("AnyChat Core SDK Version:%d.%d(%s)",dwMainVer,dwSubVer,szCompileTime);
	SetDlgItemText(IDC_STATIC_SDKVER, strSDKVer);

	//��ʼ����Ƶ��ʾ��Ϣ
	GetDlgItem(IDC_STATIC_SELFVIEW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SELFVIEW)->GetClientRect(m_UserRect[0]);
	GetDlgItem(IDC_STATIC_SELFVIEW)->ClientToScreen(m_UserRect[0]);
	ScreenToClient(m_UserRect[0]);
	
	GetDlgItem(IDC_STATIC_REMOTEVIEW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_REMOTEVIEW)->GetClientRect(m_UserRect[1]);
	GetDlgItem(IDC_STATIC_REMOTEVIEW)->ClientToScreen(m_UserRect[1]);
	ScreenToClient(m_UserRect[1]);

	// ��ʼ��m_userList���
	m_userList.ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
	m_userList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_userList.InsertColumn(0, "����", LVCFMT_CENTER,110);
	m_userList.InsertColumn(1, "ID", LVCFMT_CENTER,188); 
	SetDlgItemText(IDC_EDIT_APPID, "fbe957d1-c25a-4992-9e75-d993294a5d56");

	UpdateData(FALSE);
}

void CHelloAnyChatDlg::initSDK()
{
	// �򿪣��رգ�SDK����־��¼����
	BRAC_ActiveCallLog(TRUE);

	// ����SDK�����������Ŀ¼��ע��demo����ֻ������Ϊ��ǰĿ¼����Ŀ����Ҫ����Ϊʵ��·����
	CHAR szCoreSDKPath[MAX_PATH] = {0};
	GetModuleFileName(NULL,szCoreSDKPath,sizeof(szCoreSDKPath));
	(strrchr(szCoreSDKPath,'\\'))[1] = 0; 
	BRAC_SetSDKOption(BRAC_SO_CORESDK_PATH,szCoreSDKPath,strlen(szCoreSDKPath));
	int playModeIndex = 0;
	BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, (PCHAR)&playModeIndex, sizeof(playModeIndex));

	// ����BRAC_InitSDK�ĵڶ���������dwFuncMode��������SDK����δ�����ص�����������ο������ĵ���
	DWORD dwFuncMode = BRAC_FUNC_VIDEO_AUTODISP | BRAC_FUNC_AUDIO_AUTOPLAY | BRAC_FUNC_CHKDEPENDMODULE | 
		BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
		BRAC_FUNC_AUDIO_AUTOVOLUME| BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_CONFIG_LOCALINI;
	BRAC_InitSDK(this->GetSafeHwnd(), dwFuncMode);
	BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_RGB24,VideoData_CallBack,this);
	BRAC_SetAudioDataCallBack(AudioData_CallBack,this);
	BRAC_SetVolumeChangeCallBack(VolumeChange_CallBack,this);

	UpdateData(TRUE);
	// ���÷�������֤����
	BRAC_SetServerAuthPass("BaiRuiTech");		// ��Ҫ������������SDKAuthPass����ͬ����Сд���У���SDK�����������ӵ�������
}

/**
 *	�����û���Ƶ
 *	������Դ�ڻص�����
 *	@param dwUserid �û�ID��
 *	@param lpBuf ��Ƶ���ݻ�����
 *	@param dwLen ��������С
 *	@param bmiHeader ��Ƶ��������ͷ��Ϣ����������Ƶ�Ĵ�С����ɫλ������Ϣ
 */
void CHelloAnyChatDlg::DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader)
{
	//�����û�ID�ҵ����ʵ���ʾ����
	DWORD dwSite = -1;
	if (m_iUserID[0] == (INT)dwUserid)
	{
		dwSite = 0;
	}
	if (m_iUserID[1] == (INT) dwUserid)
	{
		dwSite = 1;
	}

	if (dwSite == -1)
		return;
	
	CRect dispRect = m_UserRect[dwSite];
	//����Bitmap
	BITMAPINFOHEADER* pBMI = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER) + dwLen);
	ZeroMemory(pBMI, sizeof(BITMAPINFOHEADER) + dwLen);
	memcpy((LPBYTE)pBMI, &bmiHeader, sizeof(bmiHeader));
	memcpy(((LPBYTE)pBMI + sizeof(BITMAPINFOHEADER)), lpBuf, dwLen);  

	HDC hdc = ::GetDC(m_hWnd);
	HDC dcMem = ::CreateCompatibleDC(hdc);  
	HBITMAP hBitmap = CreateDIBitmap(hdc,pBMI,CBM_INIT,(LPBYTE)pBMI+sizeof(BITMAPINFOHEADER),(LPBITMAPINFO)pBMI,DIB_RGB_COLORS);  
	//��ͼ  
	HBITMAP holdbm = (HBITMAP)SelectObject(dcMem,hBitmap);  
	::SetStretchBltMode(hdc,COLORONCOLOR);
	::StretchBlt(hdc,dispRect.left,dispRect.top,dispRect.Width(),dispRect.Height(),dcMem,0,0,bmiHeader.biWidth,bmiHeader.biHeight,SRCCOPY);
	
	SelectObject(dcMem,holdbm);  
	::DeleteDC(dcMem);
	::DeleteObject(hBitmap);
	::ReleaseDC(m_hWnd,hdc);
	free(pBMI);
	pBMI = NULL;
}

// 
void CHelloAnyChatDlg::SignLogin(CString serverUrl, CString strAppId, CString strUserId, CString strServerIP, DWORD dwPort, CString strUserName)
{
	CString strLogMsg;
	try
	{
		if(serverUrl.IsEmpty())
			return;
		if(strAppId.IsEmpty())
			return;

		CInternetSession session;//�����Ự
		CString strObject;
		CHttpConnection* pConnection = session.GetHttpConnection(serverUrl, 0, 8930, NULL, NULL);
		if(pConnection == NULL)
		{
			session.Close();
			return;	
		}
		CHttpFile *pF = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject, NULL, 1, 
																	NULL, TEXT("HTTP/1.1"), INTERNET_FLAG_NO_COOKIES);
		if(pF == NULL)
		{
			session.Close();
			delete pConnection;
			pConnection = NULL;
			return;
		}

		CString head_appid("appid=");
		CString head_userid("userid=");
		CString head_strUserid("strUserid=");
		CString str_userid_value("");
		CString head_add("&");
		CString content_data=head_appid + strAppId + head_add + head_userid + strUserId + head_add + head_strUserid + str_userid_value;
		DWORD contentLeng = content_data.GetLength();

		CString strHeaders_add("\r\n");
		CString strContentType("Content-Type: application/json");
		CString strContentLength("Content-Length: ");
		char szContentLeng[16] = {0};
		_snprintf(szContentLeng, sizeof(szContentLeng), "%d", contentLeng);
		CString strLeng(szContentLeng);
		CString strHeaders = strContentType + strHeaders_add + strContentLength + strLeng + + strHeaders_add;
		
		DWORD dwRet;
		pF->SendRequest(strHeaders, (LPVOID)(LPCTSTR)content_data, contentLeng);
		pF->QueryInfoStatusCode(dwRet);  
		if (dwRet != HTTP_STATUS_OK)  
		{  
			//����������������  
			session.Close();  
			delete pConnection;
			pConnection = NULL;  
			delete pF;
			pF = NULL;  
			return;  
		}

		CString szData,szAllData;
		while(pF->ReadString(szData))
		{
			//��ȡ�ļ�
			szAllData+="\r\n";
			szAllData+=szData;
		}

		session.Close();
		pConnection->Close();
		delete pConnection;
		pF->Close();
		delete pF;

		// �˴�����json����
		szAllData.TrimLeft("\r\n");		
		DWORD dwAllDataSize = szAllData.GetLength();
 		char* alldata = new char[dwAllDataSize+1];
		if(!alldata)
			return;
 		memset(alldata, '\0', dwAllDataSize+1);
 		_snprintf(alldata, dwAllDataSize+1, "%s", szAllData);

		string param1Value, param2Value, param3Value;
		if(alldata[0] == '{' && alldata[dwAllDataSize-1] == '}')
		{
			std::string data = std::string(alldata).substr(1, dwAllDataSize-2);
			char temp[1024] = {0};
			strcat(temp, data.c_str());
			char* p = strtok(temp, ","); 
			while(p != NULL)
			{
				string keyvalue = std::string(p);
				size_t pos = keyvalue.find(":");
				string keyWord = keyvalue.substr(0, pos);
				if(strcmp(keyWord.c_str(),"\"errorcode\"") == 0)
					param1Value = keyvalue.substr(pos+1);
				else if(strcmp(keyWord.c_str(), "\"timestamp\"") == 0)
					param2Value = keyvalue.substr(pos+1);
				else
					param3Value = keyvalue.substr(pos+1);

				p = strtok(NULL,",");
			}
		}

		BRAC_Connect(strServerIP.GetBuffer(0), dwPort);
		BRAC_LoginEx(strUserName.GetBuffer(0), 33, 0, strAppId, atoi(param2Value.c_str()), param3Value.c_str());

		if(alldata)
			delete[] alldata;
	}
	catch(CException *e)
	{
		strLogMsg.Format("��ȡ����ʧ��");
	}
}

void CHelloAnyChatDlg::OnLogin() 
{
	initSDK();
	UpdateData(TRUE);
	CString strServerIP; // IP
	CString strUserName; // ����
	GetDlgItemText(IDC_EDIT_IP, strServerIP);
	GetDlgItemText(IDC_EDIT_NAME, strUserName);

	if (strServerIP.IsEmpty() || m_port <= 0)
	{
		AfxMessageBox("Invalid  server ip address or port!");
		return;
	}

	if (strUserName.IsEmpty())
	{
		AfxMessageBox("Must input username for login system!");
		return;
	}

	if (m_iRoomID <=0)
	{
		AfxMessageBox("Invalid RoomID");
		return;
	}

	CString strAppID;	// APPID
	CButton* pCheckBox = (CButton *)GetDlgItem(IDC_CHECK1);
	int state = pCheckBox->GetCheck();
	if(1 == state)	///< ǩ����¼
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_APPID);
		GetDlgItemText(IDC_EDIT_APPID, strAppID);
		if(strAppID.IsEmpty())
		{
			AfxMessageBox("Must input appid for login system!");
			return;
		}

		CString strServerUrl = "demo.anychat.cn";		///< ǩ����������ַ
		CString strUserId = "33";						///< �û�����
		SignLogin(strServerUrl, strAppID, strUserId, strServerIP, m_port, strUserName);
	}
	else	///< ��ͨ��¼
	{
		BRAC_Connect(strServerIP.GetBuffer(0), m_port);
		BRAC_Login(strUserName.GetBuffer(0), "", 0);
	}
}

void CHelloAnyChatDlg::OnLogout() 
{
	BRAC_Release();
	BRAC_Logout();
	BRAC_LeaveRoom(-1);
	m_iUserID[0] = -1;
	m_iUserID[1] = -1;
	m_vecAllUser.clear();
	m_userList.DeleteAllItems();
	
	SetDlgItemText(IDC_STATIC_LINKMSG, "No connnect to the server!");
}

/**
 *	�յ���Ϣ���ͻ������ӷ�����
 *	@param wParam ��BOOL����ʾ�Ƿ����ӳɹ�
 */
LRESULT CHelloAnyChatDlg::OnGVClientConnect(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

/**
 *	�յ���Ϣ���ͻ��˵�¼ϵͳ
 *	@param wParam ��INT����ʾ�Լ����û�ID��
 *	@param lParam ��INT����ʾ��¼�����0 �ɹ�������Ϊ������룬�ο�������붨��
 */
LRESULT CHelloAnyChatDlg::OnGVClientLogin(WPARAM wParam, LPARAM lParam)
{
	CString strLogMsg;
	DWORD dwUserID = wParam;
	if (lParam == 0)
	{
		CHAR userName[USERNAMELENGTH_MAX] = {0};
		BRAC_GetUserName(dwUserID, userName, sizeof(userName));
		// ��¼�������ɹ�
		strLogMsg.Format("��¼�������ɹ����Լ����û����Ϊ��%d(%s)",wParam,userName);
		m_iUserID[0] = dwUserID;
		mbAudioSwitch = 0;

		SetDlgItemText(IDC_STATIC_LINKMSG, "Connect to the server success.");
		EnterRoom();

		//��¼�������ɹ��󣬰ѵ�¼�����Ϣ���浽�ļ���
		writeLoginDataFile();
	}
	else
	{
		strLogMsg.Format("��¼ʧ�ܣ�errorCode��%d", lParam);
		// ��¼������ʧ��
		SetDlgItemText(IDC_STATIC_LINKMSG, strLogMsg);
		
		//d��¼�������ɹ������뷿��
		EnterRoom();
	}

	UpdateData(FALSE);
	return 0;
}

void CHelloAnyChatDlg::EnterRoom()
{
	UpdateData(TRUE);
	BRAC_EnterRoom(m_iRoomID, "", 0);
}

/**
 *	�յ���Ϣ���ͻ��˽��뷿��
 *	@param wParam ��INT����ʾ�����뷿���ID��
 *	@param lParam ��INT����ʾ�Ƿ���뷿�䣺0�ɹ����룬����Ϊ�������
 */
LRESULT CHelloAnyChatDlg::OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam)
{
	CString strLogMsg;
	INT roomID = (INT)wParam;
	if (lParam == 0)
	{
		BRAC_UserCameraControl(-1,TRUE);
		BRAC_UserSpeakControl(-1,TRUE);
		strLogMsg.Format("�ɹ�������Ϊ��%d�ķ���", roomID);
		BRAC_SetVideoPos(-1,m_hWnd,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].right,m_UserRect[0].bottom);

		//���뷿���, ��������Ƶ����Ƶ��ť�ɵ��
		SetDlgItemText(IDC_BUTTON_AUDIOCTRL, "����Ƶ");
		SetDlgItemText(IDC_BUTTON_VIDEOCTRL, "����Ƶ");

		m_audioBtn.EnableWindow(TRUE);
		m_videoBtn.EnableWindow(TRUE);
	}
	else
	{
		strLogMsg.Format("������뷿��ʧ�ܣ��������Ϊ��%d", lParam);
	}

	SetDlgItemText(IDC_STATIC_LINKMSG, strLogMsg);
	UpdateData(FALSE);

	return 0;
}

/**
 *	�յ���ǰ����������û���Ϣ
 *	���뷿��󴥷�һ��
 *	@param wParam ��INT����ʾ�����û������������Լ���
 *	@param lParam ��INT����ʾ����ID
 */
LRESULT CHelloAnyChatDlg::OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam)
{
	CString strLogMsg;
	INT onLineNum = (INT)wParam;
	strLogMsg.Format("�û��б�(��%dλ�����û�)", onLineNum);
	SetDlgItemText(IDC_STATIC_USERLISTTITLE, strLogMsg);
	UpdateData(FALSE);

	// �Լ���ʾ�ڵ�һ��λ��
	CUserMsg userMsg;
	BRAC_GetUserName(m_iUserID[0], userMsg.userName, sizeof(userMsg.userName));
	sprintf(userMsg.userName, "%s(�Լ�)", userMsg.userName);
	userMsg.uerID = m_iUserID[0];
	m_vecAllUser.push_back(userMsg);

	DWORD dwUserNum = 0;
	BRAC_GetOnlineUser(NULL, dwUserNum);	//< ���Ȼ�ȡ��������������
	if(dwUserNum > 0)
	{
		LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD)*dwUserNum);
		BRAC_GetOnlineUser(lpdwUserList, dwUserNum);

		for (INT index = 0; index < (INT)dwUserNum; ++index)
		{
			DWORD userID = lpdwUserList[index];
			CUserMsg userMsgTemp;
			BRAC_GetUserName(userID, userMsgTemp.userName, sizeof(userMsgTemp.userName));
			userMsgTemp.uerID = userID;
			m_vecAllUser.push_back(userMsgTemp);
		}

		// ��ȥ��Ĭ�ϵ�1���û�Ϊ�Ի�����
		m_iUserID[1] = lpdwUserList[0];

		BRAC_SetVideoPos(m_iUserID[1], m_hWnd, m_UserRect[1].left,m_UserRect[1].top,m_UserRect[1].right,m_UserRect[1].bottom);
		BRAC_UserCameraControl(m_iUserID[1],TRUE);
		BRAC_UserSpeakControl(m_iUserID[1],TRUE);
		
		free(lpdwUserList);
	}
	
	updateUserList();

	return 0;
}

/**
 *	�յ���Ϣ���û����루�뿪������
 *	@param wParam ��INT����ʾ�û�ID��
 *	@param lParam ��BOOL����ʾ���û��ǽ��루TRUE�����뿪��FALSE������
 */
LRESULT CHelloAnyChatDlg::OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam)
{
	INT userID = (INT)wParam;
	BOOL bEnter = (BOOL)lParam;

	// �½�����
	if(bEnter)
	{
		CUserMsg userMsg;
		BRAC_GetUserName(userID, userMsg.userName, sizeof(userMsg.userName));
		userMsg.uerID = userID;
		m_vecAllUser.push_back(userMsg);

		if(m_iUserID[1] == -1)
		{
			BRAC_SetVideoPos(userID,m_hWnd,m_UserRect[1].left,m_UserRect[1].top,m_UserRect[1].right,m_UserRect[1].bottom);
			BRAC_UserCameraControl(userID,TRUE);
			BRAC_UserSpeakControl(userID,TRUE);
			m_iUserID[1] = userID;
		}

		updateUserList();
	}
	else
	{
		if(userID == m_iUserID[1])
		{
			BRAC_UserCameraControl(userID, FALSE);
			BRAC_UserSpeakControl(userID, FALSE);
			m_iUserID[1] = -1;
		}
		
		// �Ƴ��뿪��
		vector<CUserMsg>::iterator itr = m_vecAllUser.begin();
		for (; itr != m_vecAllUser.end(); ++itr)
		{
			if (itr->uerID == userID)
			{
				m_vecAllUser.erase(itr);

				updateUserList();
				break;
			}
		}
	}

	return 0;
}

/**
 *	�յ���Ϣ�����������ѹر�
 *	����Ϣֻ���ڿͻ������ӷ������ɹ�֮�������쳣�ж�֮ʱ����
 */
LRESULT CHelloAnyChatDlg::OnGVClientLinkClose(WPARAM wParam, LPARAM lParam)
{
	BRAC_Release();
	BRAC_Logout();
	BRAC_LeaveRoom(-1);
	m_iUserID[0] = -1;
	m_iUserID[1] = -1;
	m_vecAllUser.clear();
	m_userList.DeleteAllItems();
	
	SetDlgItemText(IDC_STATIC_LINKMSG, "���������ѹرգ��Ͽ���");

	return 0;
}

// ˢ���û��б�
void CHelloAnyChatDlg::updateUserList()
{
	m_userList.DeleteAllItems();

	int nIndex = 0;
	for(int i=0; i< (int)m_vecAllUser.size(); i++)
	{
		CHAR strUserID[USERNAMELENGTH_MAX] = {0};
		sprintf(strUserID, "%d", m_vecAllUser[i].uerID);
		nIndex = m_userList.InsertItem(i, m_vecAllUser[i].userName);
		m_userList.SetItemText(nIndex,1, strUserID);

		if (m_vecAllUser[i].uerID == m_iUserID[1])
			m_userList.SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	}

	// ˢ���û��б����
	CString strLogMsg;
	strLogMsg.Format("�û��б�(��%dλ�����û�)", m_vecAllUser.size());
	SetDlgItemText(IDC_STATIC_USERLISTTITLE, strLogMsg);
}

// �û��б�������
void CHelloAnyChatDlg::OnClickListUserList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString str = "";
	for (int index = 0; index < (int)m_vecAllUser.size(); ++index)
	{
		if (m_userList.GetItemState(index, LVIS_SELECTED) == LVIS_SELECTED)
		{
			str.Format("select:%d", index);
			if (m_iUserID[1] == m_vecAllUser[index].uerID || index == 0)
				return;

			if (m_iUserID[1] != -1)
			{
				BRAC_UserCameraControl(m_iUserID[1], FALSE);
				BRAC_UserSpeakControl(m_iUserID[1], FALSE);
			}

			BRAC_SetVideoPos(m_vecAllUser[index].uerID, m_hWnd, m_UserRect[1].left, m_UserRect[1].top,
				m_UserRect[1].right, m_UserRect[1].bottom);
			BRAC_UserCameraControl(m_vecAllUser[index].uerID,TRUE);
			BRAC_UserSpeakControl(m_vecAllUser[index].uerID,TRUE);
			m_iUserID[1] = m_vecAllUser[index].uerID;
		}
	}
	
	*pResult = 0;
}

void CHelloAnyChatDlg::OnButtonSetting() 
{
	mVideoSetDlg->DoModal();
}

void CHelloAnyChatDlg::OnButtonVideoCtrl() 
{
	DWORD state = 0;
	BRAC_GetCameraState(-1, state);
	if (state == 2)
	{
		BRAC_UserCameraControl(-1, FALSE);
		SetDlgItemText(IDC_BUTTON_VIDEOCTRL, "�ر���Ƶ");
	}
	else
	{
		BRAC_UserCameraControl(-1, TRUE);
		SetDlgItemText(IDC_BUTTON_VIDEOCTRL, "����Ƶ");
	}
}

void CHelloAnyChatDlg::OnButtonAudioCtrl() 
{
	//����
    DWORD returnValue;
	if (mbAudioSwitch == 0)
	{
		returnValue = BRAC_UserSpeakControl(-1, FALSE);
		SetDlgItemText(IDC_BUTTON_AUDIOCTRL, "�ر���Ƶ");
		mbAudioSwitch = 1;
	}
	else
	{
		returnValue = BRAC_UserSpeakControl(-1, TRUE);
		SetDlgItemText(IDC_BUTTON_AUDIOCTRL, "����Ƶ");
		mbAudioSwitch = 0;
	}	
}


// д���¼����
void CHelloAnyChatDlg::writeLoginDataFile()
{
	ofstream outFile;
	outFile.open("AnyChatLoginData.txt");
	CString strIPAddress;
	CString strName;
	CString strPortNum;
	CString strRoomID;
	CHAR sIPAddress[32] = {0};
	CHAR sName[32] = {0};
	CHAR sPortNum[16] = {0};
	CHAR sRoomID[16] = {0};
	GetDlgItemText(IDC_EDIT_IP, strIPAddress);
	GetDlgItemText(IDC_EDIT_NAME, strName);
	GetDlgItemText(IDC_EDIT_PORT, strPortNum);
	GetDlgItemText(IDC_EDIT_ROOM, strRoomID);
	
	memcpy(sIPAddress, strIPAddress, strIPAddress.GetLength());
	memcpy(sName, strName, strName.GetLength());
	memcpy(sPortNum, strPortNum, strPortNum.GetLength());
	memcpy(sRoomID, strRoomID, strRoomID.GetLength());

	outFile<<sIPAddress<<endl;
	outFile<<sName<<endl;
	outFile<<sPortNum<<endl;
	outFile<<sRoomID<<endl;
	
	outFile.close();
}

void CHelloAnyChatDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton* pCheckBox = (CButton *)GetDlgItem(IDC_CHECK1);
	if(pCheckBox->GetCheck())
	{
		GetDlgItem(IDC_EDIT_APPID)->EnableWindow(TRUE);
	}  
	else
	{
		GetDlgItem(IDC_EDIT_APPID)->EnableWindow(FALSE);
	}	
}
