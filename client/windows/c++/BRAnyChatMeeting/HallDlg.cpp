// HallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BRAnyChatMeeting.h"
#include "HallDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHallDlg dialog


CHallDlg::CHallDlg(CWnd* pParent)
	: CDialog(CHallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHallDlg)
	m_pMainDlg = (CBRAnyChatMeetingDlg*)pParent;
	m_bWaitEnterRoom = FALSE;
	m_iRoomId = 0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CHallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHallDlg)
	DDX_Control(pDX, IDC_LIST_ROOM, m_ctrlRoomList);
	DDX_Text(pDX, IDC_EDIT_ROOMID, m_iRoomId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHallDlg, CDialog)
	//{{AFX_MSG_MAP(CHallDlg)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ROOM, OnDblclkListRoom)
	ON_BN_CLICKED(IDC_BUTTON_ENTERROOM, OnButtonEnterRoom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHallDlg message handlers

BOOL CHallDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	InitRoomListCtrl();
	FillRoomInfoToList();

	CHAR szConfigFile[MAX_PATH] = {0};
	::GetModuleFileName(NULL,szConfigFile,_MAX_PATH);
	(strrchr(szConfigFile,'\\'))[1] = 0; 
	strcat(szConfigFile,DEFAULT_CONFIG_FILENAME);

	TCHAR szTempStr[200] = {0};
	// 读产品名称
	if(::GetPrivateProfileString(DEFAULT_CONFIG_SECTION,_T("ProductName"),NULL,szTempStr,sizeof(szTempStr),szConfigFile))
	{
		strcat(szTempStr, " — 大厅");
		SetWindowText(szTempStr);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHallDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

/**
 *	初始化房间大厅列表
 */
void CHallDlg::InitRoomListCtrl(void)
{
	DWORD dwStyle = 0;
	dwStyle = LVS_EX_FULLROWSELECT | LVS_SHAREIMAGELISTS | LVS_REPORT|LVS_EX_FLATSB;
	
	m_ctrlRoomList.SetExtendedStyle(dwStyle);
	m_ctrlRoomList.ModifyStyle(0, LVS_REPORT);
	m_ctrlRoomList.ModifyStyle(0, WS_EX_CLIENTEDGE);
	
	m_ctrlRoomList.InsertColumn(0,_T("ID"),LVCFMT_CENTER,50);
	m_ctrlRoomList.InsertColumn(1,_T("房间名"),LVCFMT_CENTER,140);
	m_ctrlRoomList.InsertColumn(2,_T("在线人数"),LVCFMT_CENTER,80);
	m_ctrlRoomList.InsertColumn(3,_T("房间状态"),LVCFMT_CENTER,80);
}

/**
 *	填充大厅房间信息
 *	AnyChat SDK自身没有提供获取房间信息的相关接口，实际使用过程中，可以通过“SDK Filter Plus + 自定义缓冲区”的模式由SDK Filter将房间信息传给应用程序
 *	房间在线人数也可以通过SDK Filter动态的更新给应用程序
 */
void CHallDlg::FillRoomInfoToList(void)
{
	for (int i=0; i<MAX_DEMO_ROOM_NUM; i++)		// 这儿为了简单，直接填充固定的房间信息
	{
		DWORD dwRoomId = i+1;
		CHAR szRoomId[10] = {0};
		_snprintf(szRoomId,sizeof(szRoomId),"%d",dwRoomId);

		LVITEM lvi;
		lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
		lvi.iItem = dwRoomId;
		lvi.iSubItem = 0;
		lvi.iImage = 0;	
		lvi.pszText = szRoomId;
		
		INT itemno = m_ctrlRoomList.InsertItem(&lvi);
		m_ctrlRoomList.SetItemData(itemno,dwRoomId);
		
		CHAR szRoomName[20] = {0};
		_snprintf(szRoomName,sizeof(szRoomName),"%d#演示房间",dwRoomId);
		m_ctrlRoomList.SetItemText(itemno,1,szRoomName);
		m_ctrlRoomList.SetItemText(itemno,2,"未知");		// 可通过SDK Filter Plus插件来实现房间在线人数的动态更新
		m_ctrlRoomList.SetItemText(itemno,3,"开放");
	}
}

void CHallDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage (WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));	
	CDialog::OnLButtonDown(nFlags, point);
}

void CHallDlg::OnClose() 
{
	if(m_pMainDlg)
		m_pMainDlg->OnUserExitSystem();
//	CDialog::OnClose();
}

void CHallDlg::OnButtonExit() 
{
	if(m_pMainDlg)
		m_pMainDlg->OnUserExitSystem();
}

/**
 *	更新界面用户信息
 *	@param dwUserId 自己的用户编号
 */
void CHallDlg::UpdateUserInfo(DWORD dwUserId)
{
	CHAR szUserId[10] = {0};
	_snprintf(szUserId,sizeof(szUserId),"%d",(INT)dwUserId);
	GetDlgItem(IDC_STATIC_USERID)->SetWindowText(szUserId);

	CHAR szNickName[100] = {0};
	BRAC_QueryUserState(dwUserId,BRAC_USERSTATE_NICKNAME,szNickName,sizeof(szNickName));
	GetDlgItem(IDC_STATIC_NICKNAME)->SetWindowText(szNickName);

	DWORD dwLevel = 0;
	CHAR szLevel[10] = {0};
	BRAC_QueryUserState(dwUserId,BRAC_USERSTATE_LEVEL,(PCHAR)&dwLevel,sizeof(dwLevel));
	_snprintf(szLevel,sizeof(szLevel),"%d",(INT)dwLevel);
	GetDlgItem(IDC_STATIC_USERLEVEL)->SetWindowText(szLevel);

	CHAR szInternetIP[100] = {0};
	BRAC_QueryUserState(dwUserId,BRAC_USERSTATE_INTERNETIP,szInternetIP,sizeof(szInternetIP));
	GetDlgItem(IDC_STATIC_INTERNETIP)->SetWindowText(szInternetIP);
}
/**
 *	用户双击房间名，请求进入房间
 */
void CHallDlg::OnDblclkListRoom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	INT itemno = pNMListView->iItem;
	if(itemno >= 0 && !m_bWaitEnterRoom)
	{
		m_bWaitEnterRoom = TRUE;
		DWORD dwRoomId = m_ctrlRoomList.GetItemData(itemno);
		BRAC_EnterRoom(dwRoomId,"",0);
	}
	*pResult = 0;
}

// 进入房间状态通知
void CHallDlg::OnEnterRoomNotify(DWORD dwRoomId, DWORD dwErrorCode)
{
	m_bWaitEnterRoom = FALSE;	// 不论进入房间是否成功，等待状态已经结束
	// 如果进入房间失败，则提示用户
	if(dwErrorCode != GV_ERR_SUCCESS)
	{
		CHAR szNotify[100] = {0};
		_snprintf(szNotify,sizeof(szNotify),"进入房间%d失败(出错代码:%d)!",dwRoomId,dwErrorCode);
		GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(szNotify);
	}
	else
	{
		GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText("(温馨提示：双击房间名进入房间)");
	}
}
/**
 *	用户点击进入房间按钮，进入自定义的房间
 */
void CHallDlg::OnButtonEnterRoom() 
{
	UpdateData(TRUE);
	if(m_iRoomId == 0)
		return;
	BRAC_EnterRoom(m_iRoomId,"",0);
}
