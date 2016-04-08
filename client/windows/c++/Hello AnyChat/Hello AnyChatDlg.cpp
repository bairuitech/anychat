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

// 视频数据回调函数
void CALLBACK VideoData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue)
{
	CHelloAnyChatDlg* pDemoDlg = (CHelloAnyChatDlg*)lpUserValue;
	if (pDemoDlg)
		pDemoDlg->DrawUserVideo(dwUserid,lpBuf,dwLen,bmiHeader);
}

// 音频数据回调函数
void CALLBACK AudioData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue)
{
	CHelloAnyChatDlg*	pDemoDlg = (CHelloAnyChatDlg*)lpUserValue;
	if(pDemoDlg)
	{
		// do something ...
	}
}

/**
 *	音量更改回调函数
 */
void CALLBACK VolumeChange_CallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue)
{
}

void CHelloAnyChatDlg::initUI()
{
	// 初始化视频参数设置
	mVideoSetDlg = new VideoSetDlg();
	mbAudioSwitch = 0;

	m_iUserID[0] = -1;
	m_iUserID[1] = -1;

	// 初始化登录数据(通过读取文件)
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

	// 获取SDK的版本信息
	CString strSDKVer;
	DWORD dwMainVer;
	DWORD dwSubVer;
	CHAR szCompileTime[100] = {0};
	BRAC_GetSDKVersion(dwMainVer,dwSubVer,szCompileTime,sizeof(szCompileTime));
	strSDKVer.Format("AnyChat Core SDK Version:%d.%d(%s)",dwMainVer,dwSubVer,szCompileTime);
	SetDlgItemText(IDC_STATIC_SDKVER, strSDKVer);

	//初始化视频显示信息
	GetDlgItem(IDC_STATIC_SELFVIEW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SELFVIEW)->GetClientRect(m_UserRect[0]);
	GetDlgItem(IDC_STATIC_SELFVIEW)->ClientToScreen(m_UserRect[0]);
	ScreenToClient(m_UserRect[0]);
	
	GetDlgItem(IDC_STATIC_REMOTEVIEW)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_REMOTEVIEW)->GetClientRect(m_UserRect[1]);
	GetDlgItem(IDC_STATIC_REMOTEVIEW)->ClientToScreen(m_UserRect[1]);
	ScreenToClient(m_UserRect[1]);

	// 初始化m_userList风格
	m_userList.ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL);
	m_userList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_userList.InsertColumn(0, "姓名", LVCFMT_CENTER,110);
	m_userList.InsertColumn(1, "ID", LVCFMT_CENTER,188); 
	SetDlgItemText(IDC_EDIT_APPID, "fbe957d1-c25a-4992-9e75-d993294a5d56");

	UpdateData(FALSE);
}

void CHelloAnyChatDlg::initSDK()
{
	// 打开（关闭）SDK的日志记录功能
	BRAC_ActiveCallLog(TRUE);

	// 设置SDK核心组件所在目录（注：demo程序只是设置为当前目录，项目中需要设置为实际路径）
	CHAR szCoreSDKPath[MAX_PATH] = {0};
	GetModuleFileName(NULL,szCoreSDKPath,sizeof(szCoreSDKPath));
	(strrchr(szCoreSDKPath,'\\'))[1] = 0; 
	BRAC_SetSDKOption(BRAC_SO_CORESDK_PATH,szCoreSDKPath,strlen(szCoreSDKPath));
	int playModeIndex = 0;
	BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, (PCHAR)&playModeIndex, sizeof(playModeIndex));

	// 根据BRAC_InitSDK的第二个参数：dwFuncMode，来告诉SDK该如何处理相关的任务（详情请参考开发文档）
	DWORD dwFuncMode = BRAC_FUNC_VIDEO_AUTODISP | BRAC_FUNC_AUDIO_AUTOPLAY | BRAC_FUNC_CHKDEPENDMODULE | 
		BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
		BRAC_FUNC_AUDIO_AUTOVOLUME| BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_CONFIG_LOCALINI;
	BRAC_InitSDK(this->GetSafeHwnd(), dwFuncMode);
	BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_RGB24,VideoData_CallBack,this);
	BRAC_SetAudioDataCallBack(AudioData_CallBack,this);
	BRAC_SetVolumeChangeCallBack(VolumeChange_CallBack,this);

	UpdateData(TRUE);
	// 设置服务器认证密码
	BRAC_SetServerAuthPass("BaiRuiTech");		// 需要与服务器配置项“SDKAuthPass”相同（大小写敏感），SDK才能正常连接到服务器
}

/**
 *	绘制用户视频
 *	数据来源于回调函数
 *	@param dwUserid 用户ID号
 *	@param lpBuf 视频数据缓冲区
 *	@param dwLen 缓冲区大小
 *	@param bmiHeader 视频缓冲区的头信息，包含了视频的大小、颜色位数等信息
 */
void CHelloAnyChatDlg::DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader)
{
	//根据用户ID找到合适的显示区域
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
	//构建Bitmap
	BITMAPINFOHEADER* pBMI = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER) + dwLen);
	ZeroMemory(pBMI, sizeof(BITMAPINFOHEADER) + dwLen);
	memcpy((LPBYTE)pBMI, &bmiHeader, sizeof(bmiHeader));
	memcpy(((LPBYTE)pBMI + sizeof(BITMAPINFOHEADER)), lpBuf, dwLen);  

	HDC hdc = ::GetDC(m_hWnd);
	HDC dcMem = ::CreateCompatibleDC(hdc);  
	HBITMAP hBitmap = CreateDIBitmap(hdc,pBMI,CBM_INIT,(LPBYTE)pBMI+sizeof(BITMAPINFOHEADER),(LPBITMAPINFO)pBMI,DIB_RGB_COLORS);  
	//绘图  
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

		CInternetSession session;//建立会话
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
			//服务器不接受请求  
			session.Close();  
			delete pConnection;
			pConnection = NULL;  
			delete pF;
			pF = NULL;  
			return;  
		}  
		else
			OutputDebugStr("请求成功");

		CString szData,szAllData;
		while(pF->ReadString(szData))
		{
			//读取文件
			szAllData+="\r\n";
			szAllData+=szData;
		}

		session.Close();
		pConnection->Close();
		delete pConnection;
		pF->Close();
		delete pF;
		OutputDebugStr("获取数据成功");

		// 此处解析json数据
		OutputDebugStr(szAllData);
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
		strLogMsg.Format("获取数据失败");
	}
}

void CHelloAnyChatDlg::OnLogin() 
{
	initSDK();
	UpdateData(TRUE);
	CString strServerIP; // IP
	CString strUserName; // 名字
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
	if(1 == state)	///< 签名登录
	{
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_APPID);
		GetDlgItemText(IDC_EDIT_APPID, strAppID);
		if(strAppID.IsEmpty())
		{
			AfxMessageBox("Must input appid for login system!");
			return;
		}

		CString strServerUrl = "demo.anychat.cn";		///< 签名服务器地址
		CString strUserId = "33";						///< 用户编码
		SignLogin(strServerUrl, strAppID, strUserId, strServerIP, m_port, strUserName);
	}
	else	///< 普通登录
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
 *	收到消息：客户端连接服务器
 *	@param wParam （BOOL）表示是否连接成功
 */
LRESULT CHelloAnyChatDlg::OnGVClientConnect(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

/**
 *	收到消息：客户端登录系统
 *	@param wParam （INT）表示自己的用户ID号
 *	@param lParam （INT）表示登录结果：0 成功，否则为出错代码，参考出错代码定义
 */
LRESULT CHelloAnyChatDlg::OnGVClientLogin(WPARAM wParam, LPARAM lParam)
{
	CString strLogMsg;
	DWORD dwUserID = wParam;
	if (lParam == 0)
	{
		CHAR userName[USERNAMELENGTH_MAX] = {0};
		BRAC_GetUserName(dwUserID, userName, sizeof(userName));
		// 登录服务器成功
		strLogMsg.Format("登录服务器成功，自己的用户编号为：%d(%s)",wParam,userName);
		m_iUserID[0] = dwUserID;
		mbAudioSwitch = 0;

		SetDlgItemText(IDC_STATIC_LINKMSG, "Connect to the server success.");
		EnterRoom();

		//登录服务器成功后，把登录相关信息保存到文件中
		writeLoginDataFile();
	}
	else
	{
		strLogMsg.Format("登录失败，errorCode：%d", lParam);
		// 登录服务器失败
		SetDlgItemText(IDC_STATIC_LINKMSG, strLogMsg);
		
		//d登录服务器成功，进入房间
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
 *	收到消息：客户端进入房间
 *	@param wParam （INT）表示所进入房间的ID号
 *	@param lParam （INT）表示是否进入房间：0成功进入，否则为出错代码
 */
LRESULT CHelloAnyChatDlg::OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam)
{
	CString strLogMsg;
	INT roomID = (INT)wParam;
	if (lParam == 0)
	{
		BRAC_UserCameraControl(-1,TRUE);
		BRAC_UserSpeakControl(-1,TRUE);
		strLogMsg.Format("成功进入编号为：%d的房间", roomID);
		BRAC_SetVideoPos(-1,m_hWnd,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].right,m_UserRect[0].bottom);

		//进入房间后, 才设置音频和视频按钮可点击
		SetDlgItemText(IDC_BUTTON_AUDIOCTRL, "打开音频");
		SetDlgItemText(IDC_BUTTON_VIDEOCTRL, "打开视频");

		m_audioBtn.EnableWindow(TRUE);
		m_videoBtn.EnableWindow(TRUE);
	}
	else
	{
		strLogMsg.Format("申请进入房间失败，出错代码为：%d", lParam);
	}

	SetDlgItemText(IDC_STATIC_LINKMSG, strLogMsg);
	UpdateData(FALSE);

	return 0;
}

/**
 *	收到当前房间的在线用户信息
 *	进入房间后触发一次
 *	@param wParam （INT）表示在线用户数（不包含自己）
 *	@param lParam （INT）表示房间ID
 */
LRESULT CHelloAnyChatDlg::OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam)
{
	CString strLogMsg;
	INT onLineNum = (INT)wParam;
	strLogMsg.Format("用户列表(共%d位在线用户)", onLineNum);
	SetDlgItemText(IDC_STATIC_USERLISTTITLE, strLogMsg);
	UpdateData(FALSE);

	// 自己显示在第一个位置
	CUserMsg userMsg;
	BRAC_GetUserName(m_iUserID[0], userMsg.userName, sizeof(userMsg.userName));
	sprintf(userMsg.userName, "%s(自己)", userMsg.userName);
	userMsg.uerID = m_iUserID[0];
	m_vecAllUser.push_back(userMsg);

	DWORD dwUserNum = 0;
	BRAC_GetOnlineUser(NULL, dwUserNum);	//< 首先获取房间内在线人数
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

		// 进去后默认第1个用户为对话对象
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
 *	收到消息：用户进入（离开）房间
 *	@param wParam （INT）表示用户ID号
 *	@param lParam （BOOL）表示该用户是进入（TRUE）或离开（FALSE）房间
 */
LRESULT CHelloAnyChatDlg::OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam)
{
	INT userID = (INT)wParam;
	BOOL bEnter = (BOOL)lParam;

	// 新进来的
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
		
		// 移除离开的
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
 *	收到消息：网络连接已关闭
 *	该消息只有在客户端连接服务器成功之后，网络异常中断之时触发
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
	
	SetDlgItemText(IDC_STATIC_LINKMSG, "网络连接已关闭（断开）");

	return 0;
}

// 刷新用户列表
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

	// 刷新用户列表标题
	CString strLogMsg;
	strLogMsg.Format("用户列表(共%d位在线用户)", m_vecAllUser.size());
	SetDlgItemText(IDC_STATIC_USERLISTTITLE, strLogMsg);
}

// 用户列表点击函数
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
		SetDlgItemText(IDC_BUTTON_VIDEOCTRL, "关闭视频");
	}
	else
	{
		BRAC_UserCameraControl(-1, TRUE);
		SetDlgItemText(IDC_BUTTON_VIDEOCTRL, "打开视频");
	}
}

void CHelloAnyChatDlg::OnButtonAudioCtrl() 
{
	//测试
    DWORD returnValue;
	if (mbAudioSwitch == 0)
	{
		returnValue = BRAC_UserSpeakControl(-1, FALSE);
		SetDlgItemText(IDC_BUTTON_AUDIOCTRL, "关闭音频");
		mbAudioSwitch = 1;
	}
	else
	{
		returnValue = BRAC_UserSpeakControl(-1, TRUE);
		SetDlgItemText(IDC_BUTTON_AUDIOCTRL, "打开音频");
		mbAudioSwitch = 0;
	}	
}


// 写入登录数据
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
	// TODO: 在此添加控件通知处理程序代码
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
