// VideoPanelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BRAnyChatMeeting.h"
#include "VideoPanelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_REFRESH_SPEAKVOLUME	1		///< 更新发言音量显示定时器
#define TIMER_REFRESH_NETSTATUS		2		///< 刷新网络状态定时器

#define WM_REFRESH_BUTTON_STATE	WM_USER + 100	///< 刷新按钮状态消息
#define WM_REFRESH_VIDEO		WM_USER + 101	///< 刷新视频消息


CVideoPanelDlg::CVideoPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoPanelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoPanelDlg)
	//}}AFX_DATA_INIT
	m_dwUserId = INVALID_USERID;
}


void CVideoPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoPanelDlg)
	DDX_Control(pDX, IDC_BUTTON_VIDEOCTRL, m_btnVideoCtrl);
	DDX_Control(pDX, IDC_BUTTON_SNAPSHOT, m_btnSnapshot);
	DDX_Control(pDX, IDC_BUTTON_RECORD, m_btnRecord);
	DDX_Control(pDX, IDC_BUTTON_AUDIOCTRL, m_btnAudioCtrl);
	DDX_Control(pDX, IDC_PROGRESS_AUDIOVOLUME, m_ctrlAudioVolume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoPanelDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoPanelDlg)
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_VIDEOCTRL, OnButtonVideoControl)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOCTRL, OnButtonAudioControl)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOT, OnButtonSnapshot)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnButtonRecord)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_MESSAGE(WM_REFRESH_BUTTON_STATE,OnRefreshButtonState)
	ON_MESSAGE(WM_REFRESH_VIDEO,OnRefreshVideo)
	ON_MESSAGE(WM_EXIT_FULLSCREEN, OnExitFullScreen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoPanelDlg message handlers

BOOL CVideoPanelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	::InitializeCriticalSection(&m_hBufSection);
	m_pLastVideoBuf = NULL;
	m_dwLastVideoLen = 0;

	m_dwWidth = 320;
	m_dwHeight = 240;

	m_pFullScreenDlg = new CFullScreenDlg(this);
	if(m_pFullScreenDlg && m_pFullScreenDlg->Create(IDD_DIALOG_FULLSCREEN, this))
	{
		m_pFullScreenDlg->ShowWindow(SW_HIDE);
		m_pFullScreenDlg->SetNotifyWnd(m_hWnd);
	}
	else
	{
		delete m_pFullScreenDlg;
		m_pFullScreenDlg = NULL;
	}

#ifdef _HRC_USE_SKIN_
	skinppSetNoSkinHwnd(m_hWnd,FALSE);		// bChildNoSkin为TRUE，在Debug版本下，会有断言错误，应该是skin的bug
	skinppSetDialogEraseBkgnd(m_ctrlAudioVolume.GetSafeHwnd(),TRUE);
#endif
	
	m_bVideoState = FALSE;
	m_bAudioState = FALSE;

	m_vfTopLeftPic.Load(IDR_IMAGE_VIDEOFRAME_TOPLEFT);
	m_vfTopMiddlePic.Load(IDR_IMAGE_VIDEOFRAME_TOPMIDDLE);
	m_vfTopRightPic.Load(IDR_IMAGE_VIDEOFRAME_TOPRIGHT);
	m_vfLeftPic.Load(IDR_IMAGE_VIDEOFRAME_LEFT);
	m_vfRightPic.Load(IDR_IMAGE_VIDEOFRAME_RIGHT);
	m_vfBottomLeftPic.Load(IDR_IMAGE_VIDEOFRAME_BOTTOMLEFT);
	m_vfBottomMiddlePic.Load(IDR_IMAGE_VIDEOFRAME_BOTTOMMIDDLE);
	m_vfBottomRightPic.Load(IDR_IMAGE_VIDEOFRAME_BOTTOMRIGHT);

	m_NetStatusPic.Load(IDR_IMAGE_NETSTATUS_VERYGOOD);
	m_bkBrush.CreateSolidBrush(RGB(0,0,0));
	m_bNeedShowBkPic = TRUE;
	m_bRegualShowVideo = TRUE;
	GetClientRect(m_rcMainDisp);


	TCHAR szVideoBkPath[MAX_PATH] = {0};
	TCHAR szVideoBkFile[MAX_PATH] = {0};
	GetModuleFileName(NULL,szVideoBkPath,sizeof(szVideoBkPath)); 
	(strrchr(szVideoBkPath,'\\'))[1] = 0; 
	strcat(szVideoBkPath,SUB_PATH_SKINFILE);
	_snprintf(szVideoBkFile,sizeof(szVideoBkFile),"%s\\%s",szVideoBkPath,_T("videobk.jpg"));
	if(IsFileExist(szVideoBkFile))
		m_VideoBkPic.Load(szVideoBkFile);
	else
		m_VideoBkPic.Load(IDR_IMAGE_VIDEOBK);


	// 视频控制按钮
	InitSTButton(m_btnVideoCtrl,IDB_BITMAP_OPENVIDEO,"打开视频");
	// 语音控制按钮
	InitSTButton(m_btnAudioCtrl,IDB_BITMAP_OPENAUDIO,"打开语音");
	// 图像抓拍按钮
	InitSTButton(m_btnSnapshot,IDB_BITMAP_SNAPSHOT,"快照");
	// 录像按钮
//	InitSTButton(m_btnRecord,IDB_BITMAP_RECORDFILE,"录像");
	m_btnRecord.ShowWindow(SW_HIDE);

	// 初始化音量显示条控件
	m_ctrlAudioVolume.SetStartColor(RGB(0,255,0));
	m_ctrlAudioVolume.SetEndColor(RGB(255,0,0));
	m_ctrlAudioVolume.SetBkColor(RGB(255,255,255));
	m_ctrlAudioVolume.SetTextColor(RGB(255,255,0));
	m_ctrlAudioVolume.ShowPercent(FALSE);
	
	SetTimer(TIMER_REFRESH_SPEAKVOLUME,100,NULL);
	SetTimer(TIMER_REFRESH_NETSTATUS,2000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVideoPanelDlg::OnDestroy() 
{
	if(m_pLastVideoBuf)
	{
		free(m_pLastVideoBuf);
		m_pLastVideoBuf = NULL;
	}
	m_dwLastVideoLen = 0;

	if(m_pFullScreenDlg)
	{
		m_pFullScreenDlg->DestroyWindow();
		delete m_pFullScreenDlg;
		m_pFullScreenDlg = NULL;
	}

	::DeleteCriticalSection(&m_hBufSection);
	CDialog::OnDestroy();
}

HBRUSH CVideoPanelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	

	return hbr;
}

void CVideoPanelDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	RelocateControls();
}

void CVideoPanelDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// 发送消息刷新视频
//	PostMessage(WM_REFRESH_VIDEO,0,0);

	if(m_dwUserId != INVALID_USERID)
		BRAC_RepaintVideo(m_dwUserId,dc.GetSafeHdc());
}

BOOL CVideoPanelDlg::OnEraseBkgnd(CDC* pDC) 
{
	BOOL bReturnValue = CDialog::OnEraseBkgnd(pDC);
	
	CRect rc;
	GetClientRect(rc);
	
	// 画左上角
	m_vfTopLeftPic.Render(pDC,CRect(0,0,m_vfTopLeftPic.GetImageSize().cx,m_vfTopLeftPic.GetImageSize().cy));
	// 画上部中间
	m_vfTopMiddlePic.Render(pDC,CRect(m_vfTopLeftPic.GetImageSize().cx,0,rc.right-m_vfTopRightPic.GetImageSize().cx,m_vfTopMiddlePic.GetImageSize().cy));
	// 画右上角
	m_vfTopRightPic.Render(pDC,CRect(rc.right-m_vfTopRightPic.GetImageSize().cx,0,rc.right,m_vfTopRightPic.GetImageSize().cy));
	// 画左边框
	m_vfLeftPic.Render(pDC,CRect(0,m_vfTopLeftPic.GetImageSize().cy,m_vfLeftPic.GetImageSize().cx,rc.bottom-m_vfBottomLeftPic.GetImageSize().cy));
	// 画右边框
	m_vfRightPic.Render(pDC,CRect(rc.right-m_vfRightPic.GetImageSize().cx,m_vfTopRightPic.GetImageSize().cy,rc.right,rc.bottom-m_vfBottomRightPic.GetImageSize().cy));
	// 画左下角
	m_vfBottomLeftPic.Render(pDC,CRect(0,rc.bottom-m_vfBottomLeftPic.GetImageSize().cy,m_vfBottomLeftPic.GetImageSize().cx,rc.bottom));
	// 画底部中间
	m_vfBottomMiddlePic.Render(pDC,CRect(m_vfBottomLeftPic.GetImageSize().cx,rc.bottom-m_vfBottomLeftPic.GetImageSize().cy,rc.right-m_vfBottomRightPic.GetImageSize().cx,rc.bottom));
	// 画右下角
	m_vfBottomRightPic.Render(pDC,CRect(rc.right-m_vfBottomRightPic.GetImageSize().cx,rc.bottom-m_vfBottomRightPic.GetImageSize().cy,rc.right,rc.bottom));
	
	// 画网络状态
	if(m_dwUserId != INVALID_USERID)
		m_NetStatusPic.Render(pDC,m_rcNetStatus);

	// 画视频背景
	if(m_bNeedShowBkPic)
		m_VideoBkPic.Render(pDC,m_rcMainDisp);
	else
		pDC->FillRect(m_rcMainDisp,&m_bkBrush);
	
	// 绘制标题
	if(!m_strTitle.IsEmpty())
	{
		CMemDC dc(pDC, NULL,TRUE);
		dc.SetTextColor(RGB(255,255,255));
		dc.SetBkMode(TRANSPARENT);
		
		LOGFONT mLogFont = {0};
		mLogFont.lfHeight      = -12;
		mLogFont.lfWeight      = FW_NORMAL;
		mLogFont.lfQuality        = DRAFT_QUALITY;
		mLogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
		strcpy(mLogFont.lfFaceName, _T("新宋体"));
		
		HFONT mNewFont = CreateFontIndirect(&mLogFont);
		HFONT mOldFont = (HFONT)SelectObject(dc.m_hDC, mNewFont);
		
		SIZE titleStrSize = {0};
		GetTextExtentPoint32(dc.m_hDC, m_strTitle, strlen(m_strTitle.GetBuffer(0)), &titleStrSize);
		INT x = m_rcTitle.left + ((m_rcTitle.right - m_rcTitle.left) - titleStrSize.cx)/2;
		INT y = m_rcTitle.top + ((m_rcTitle.bottom - m_rcTitle.top) - titleStrSize.cy )/2;
		dc.TextOut(x,y,m_strTitle);
		
		SelectObject(dc.m_hDC, mOldFont);
		DeleteObject(mNewFont);
	}
	
	m_btnVideoCtrl.SetBk(pDC);
	m_btnAudioCtrl.SetBk(pDC);
	m_btnSnapshot.SetBk(pDC);
	m_btnRecord.SetBk(pDC);

	if(m_dwUserId != INVALID_USERID)
		BRAC_RepaintVideo(m_dwUserId, pDC->GetSafeHdc());
	
	return bReturnValue;
}

/**
 *	重新定位界面控件
 */
void CVideoPanelDlg::RelocateControls()
{
	CRect rc;
	GetClientRect(rc);

	// 重新定位标题显示控件，离左边14个像素，离右边14个像素，距顶部6个像素
	INT titleheight = 12;		///< 标题的高度
	SetRect(m_rcTitle,rc.left+15 , rc.top+6 , rc.right-14 , rc.top+6+titleheight);

	// 重新定位音量显示控件
	INT volumeheight = 4;		///< 音量显示插件的高度
	CRect rcVolume(rc.left+ 8, rc.bottom-5-volumeheight , rc.right-8 , rc.bottom-5);
	if(m_ctrlAudioVolume.m_hWnd)
		m_ctrlAudioVolume.MoveWindow(rcVolume);

	// 重新定位网络状态图标显示区域
	SetRect(m_rcNetStatus,rc.right-4-m_NetStatusPic.GetImageSize().cx,rc.bottom-12-m_NetStatusPic.GetImageSize().cy,rc.right-4,rc.bottom-12);

	// 重新计算视频显示区域
	SetRect(m_rcMainDisp,m_vfLeftPic.GetImageSize().cx,m_vfTopLeftPic.GetImageSize().cy,
		rc.right- m_vfRightPic.GetImageSize().cx,rc.bottom-m_vfBottomLeftPic.GetImageSize().cy);
	m_rcVideoDisp = m_rcMainDisp;
	if(m_bRegualShowVideo)
		AdjustVideoDispRect(m_rcVideoDisp);

	// 重新定位视频工具条控件
#define BUTTON_LEFTSIDE_VALUE	15			// 按钮距左边界间距
#define BUTTON_INTERVAL_VALUE	5			// 按钮之间的间距
#define BUTTON_WIDTH_VALUE		20
	DWORD dwIndex = 0;
	CRect btnrc;
	btnrc.bottom = rc.bottom - 10;
	btnrc.top = btnrc.bottom - BUTTON_WIDTH_VALUE;
	// 定位视频控制按钮
	btnrc.left = rc.left + BUTTON_LEFTSIDE_VALUE + (BUTTON_INTERVAL_VALUE + BUTTON_WIDTH_VALUE)*(dwIndex++);
	btnrc.right = btnrc.left + BUTTON_WIDTH_VALUE;
	if(m_btnVideoCtrl.m_hWnd)
		m_btnVideoCtrl.MoveWindow(btnrc);
	// 定位音频控制按钮
	btnrc.left = rc.left + BUTTON_LEFTSIDE_VALUE + (BUTTON_INTERVAL_VALUE + BUTTON_WIDTH_VALUE)*(dwIndex++);
	btnrc.right = btnrc.left + BUTTON_WIDTH_VALUE;
	if(m_btnAudioCtrl.m_hWnd)
		m_btnAudioCtrl.MoveWindow(btnrc);
	// 定位快照控制按钮
	btnrc.left = rc.left + BUTTON_LEFTSIDE_VALUE + (BUTTON_INTERVAL_VALUE + BUTTON_WIDTH_VALUE)*(dwIndex++);
	btnrc.right = btnrc.left + BUTTON_WIDTH_VALUE;
	if(m_btnSnapshot.m_hWnd)
		m_btnSnapshot.MoveWindow(btnrc);
	// 定位录像控制按钮
	btnrc.left = rc.left + BUTTON_LEFTSIDE_VALUE + (BUTTON_INTERVAL_VALUE + BUTTON_WIDTH_VALUE)*(dwIndex++);
	btnrc.right = btnrc.left + BUTTON_WIDTH_VALUE;
	if(m_btnRecord.m_hWnd)
		m_btnRecord.MoveWindow(btnrc);

	if(m_dwUserId != INVALID_USERID)
		BRAC_SetVideoPos(m_dwUserId,m_hWnd,m_rcVideoDisp.left,m_rcVideoDisp.top,m_rcVideoDisp.right,m_rcVideoDisp.bottom);
}

// 设置标题显示
void CVideoPanelDlg::SetPanelTitle(CString strTitle)
{
	m_strTitle = strTitle;
//	InvalidateRect(m_rcTitle);	外部会有刷新
}
// 初始化按钮
void CVideoPanelDlg::InitSTButton(CButtonST& btn, INT bitmapID, LPCTSTR lpTooltip)
{
	btn.SetBitmaps(bitmapID,RGB(255, 0, 255));
	btn.SetWindowText("");
	btn.EnableBalloonTooltip();
	btn.SetTooltipText(lpTooltip);
	btn.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	btn.SetPressedStyle(CButtonST::BTNST_PRESSED_TOPBOTTOM, FALSE);
	btn.DrawBorder(FALSE, FALSE);
	btn.DrawTransparent();
	btn.SizeToContent();
}

// 设置关联用户编号
void CVideoPanelDlg::SetRelateUserId(DWORD dwUserId)
{
	if(dwUserId != INVALID_USERID && m_dwUserId == INVALID_USERID)	// 重新关联到新的用户
	{
		// 默认打开音频与视频
		BRAC_UserSpeakControl(dwUserId,TRUE);
		BRAC_UserCameraControl(dwUserId,TRUE);
		BRAC_SetVideoPos(dwUserId,m_hWnd,m_rcVideoDisp.left,m_rcVideoDisp.top,m_rcVideoDisp.right,m_rcVideoDisp.bottom);

		m_bVideoState = TRUE;
		m_bAudioState = TRUE;
	}
	else if(m_dwUserId != INVALID_USERID && dwUserId == INVALID_USERID)	// 取消老用户的关联
	{
		BRAC_UserSpeakControl(m_dwUserId,FALSE);	// 取消关联时关闭音、视频的请求
		BRAC_UserCameraControl(m_dwUserId,FALSE);
		m_bVideoState = FALSE;
		m_bAudioState = FALSE;

		m_bNeedShowBkPic = TRUE;
		m_bRegualShowVideo = TRUE;
		// 清除老用户的视频缓冲区
		::EnterCriticalSection(&m_hBufSection);
		if(m_pLastVideoBuf)
		{
			free(m_pLastVideoBuf);
			m_pLastVideoBuf = NULL;
		}
		m_dwLastVideoLen = 0;
		::LeaveCriticalSection(&m_hBufSection);

		if(m_pFullScreenDlg)
			m_pFullScreenDlg->ShowWindow(SW_HIDE);
	}
	m_dwUserId = dwUserId;
	// 刷新按钮界面状态
	PostMessage(WM_REFRESH_BUTTON_STATE,0,0);
}

/**
 *	收到回调视频数据
 *	@param lpBuf 视频数据缓冲区
 *	@param dwLen 缓冲区大小
 *	@param bmiHeader 视频缓冲区的头信息，包含了视频的大小、颜色位数等信息
 */
void CVideoPanelDlg::OnRecvCallBackVideoData(LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader)
{
	if(m_bNeedShowBkPic)
	{
		m_bNeedShowBkPic = FALSE;
		Invalidate();
	}
	// 将视频数据保存下来
	::EnterCriticalSection(&m_hBufSection);
	if(!m_pLastVideoBuf || m_dwLastVideoLen < dwLen)
		m_pLastVideoBuf = (PCHAR)realloc(m_pLastVideoBuf,dwLen);

	if(m_pLastVideoBuf)
	{
		memcpy(m_pLastVideoBuf,lpBuf,dwLen);
		m_dwLastVideoLen = dwLen;
		memcpy(&m_bmiLastVideo,&bmiHeader,sizeof(BITMAPINFOHEADER));
		// 发送消息刷新视频
		PostMessage(WM_REFRESH_VIDEO,0,0);
	}
	::LeaveCriticalSection(&m_hBufSection);
}

LRESULT CVideoPanelDlg::OnRefreshVideo(WPARAM wParam, LPARAM lParam)
{
	if(!m_pLastVideoBuf || m_dwLastVideoLen == 0 || !m_bVideoState)
		return 0;
	::EnterCriticalSection(&m_hBufSection);

	CRect dispRect(m_rcVideoDisp);
	//构建Bitmap  
	BITMAPINFOHEADER  *lpbmi = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER)+m_dwLastVideoLen);  
	ZeroMemory(lpbmi,sizeof(BITMAPINFOHEADER)+m_dwLastVideoLen);
    memcpy((LPBYTE)lpbmi,&m_bmiLastVideo,sizeof(BITMAPINFOHEADER));
	memcpy(((LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER)),m_pLastVideoBuf,m_dwLastVideoLen);  
	
	HDC hdc = ::GetDC(m_hWnd);
	HDC dcMem = ::CreateCompatibleDC(hdc);  
	HBITMAP hBitmap = CreateDIBitmap(hdc,lpbmi,CBM_INIT,(LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER),(LPBITMAPINFO)lpbmi,DIB_RGB_COLORS);  
	//绘图  
	HBITMAP holdbm = (HBITMAP)SelectObject(dcMem,hBitmap);  
	::SetStretchBltMode(hdc,COLORONCOLOR);
	::StretchBlt(hdc,dispRect.left,dispRect.top,dispRect.Width(),dispRect.Height(),dcMem,0,0,m_bmiLastVideo.biWidth,m_bmiLastVideo.biHeight,SRCCOPY);
	
	SelectObject(dcMem,holdbm);  
	::DeleteDC(dcMem);
	::DeleteObject(hBitmap);
	::ReleaseDC(m_hWnd,hdc);
	free(lpbmi);
	lpbmi = NULL;
	::LeaveCriticalSection(&m_hBufSection);
	return 0;
}

void CVideoPanelDlg::OnButtonVideoControl() 
{
	if(m_dwUserId == INVALID_USERID)
		return;
	m_bVideoState = !m_bVideoState;
	BRAC_UserCameraControl(m_dwUserId,m_bVideoState);
	if(!m_bVideoState)
	{
		m_bNeedShowBkPic = TRUE;
		InvalidateRect(m_rcMainDisp);
	}
	PostMessage(WM_REFRESH_BUTTON_STATE,0,0);
}

void CVideoPanelDlg::OnButtonAudioControl() 
{
	if(m_dwUserId == INVALID_USERID)
		return;
	m_bAudioState = !m_bAudioState;
	BRAC_UserSpeakControl(m_dwUserId,m_bAudioState);
	PostMessage(WM_REFRESH_BUTTON_STATE,0,0);
}

void CVideoPanelDlg::OnButtonSnapshot() 
{
	if(m_dwUserId == INVALID_USERID)
		return;
	BRAC_SnapShot(m_dwUserId,0,0);
}

void CVideoPanelDlg::OnButtonRecord() 
{

	
}

BOOL CVideoPanelDlg::PreTranslateMessage(MSG* pMsg) 
{
	BOOL bNeedTranslate = TRUE;
	if(pMsg->message == WM_KEYDOWN)
    {
		switch(pMsg->wParam)
        {
        case VK_RETURN:
        case VK_SPACE:
		case VK_ESCAPE:
			bNeedTranslate = FALSE;
			break;
		default:
			break;
        }
	}
	return bNeedTranslate ? CDialog::PreTranslateMessage(pMsg) : TRUE;
}

// 规整视频显示区域，让视频按一定的比例显示
void CVideoPanelDlg::AdjustVideoDispRect(CRect& rc)
{
	float fCurRate = (float)rc.Width() / (float)rc.Height();
	float fStandardRate = (float)m_dwWidth / (float)m_dwHeight;
	if(fCurRate >= fStandardRate)		// 实际显示区域比较宽
	{
		DWORD dwNewWidth = (DWORD)(fStandardRate * rc.Height());
		DWORD dwRemainWidth = rc.Width() - dwNewWidth;
		rc.left += dwRemainWidth/2;
		rc.right -= dwRemainWidth/2;
	}
	else								// 实际显示区域比较窄
	{
		DWORD dwNewHeight = (DWORD)(rc.Width() / fStandardRate);
		DWORD dwRemainHeight = rc.Height() - dwNewHeight;
		rc.top += dwRemainHeight/2;
		rc.bottom -= dwRemainHeight/2;
	}
	// 最后将大小归整，变为偶数
	if(rc.Width() % 2)
		rc.right--;
	if(rc.Height() % 2)
		rc.bottom--;
}
/**
 *	用户左键双击视频面板，改变视频显示风格
 */
void CVideoPanelDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if(m_dwUserId == INVALID_USERID)
		return;
	if(m_bRegualShowVideo)
	{
		m_bRegualShowVideo = FALSE;
		m_rcVideoDisp = m_rcMainDisp;
		InvalidateRect(m_rcMainDisp);
	
		if(m_dwUserId != INVALID_USERID)
			BRAC_SetVideoPos(m_dwUserId,m_hWnd,m_rcVideoDisp.left,m_rcVideoDisp.top,m_rcVideoDisp.right,m_rcVideoDisp.bottom);
	}
	else
	{
		if(m_pFullScreenDlg)
		{
			m_pFullScreenDlg->ShowWindow(SW_MAXIMIZE);
			CRect rc;
			m_pFullScreenDlg->GetClientRect(rc);
			BRAC_SetVideoPos(m_dwUserId,m_pFullScreenDlg->GetSafeHwnd(),rc.left,rc.top,rc.right,rc.bottom);
		}
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CVideoPanelDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case TIMER_REFRESH_SPEAKVOLUME:
		if(m_dwUserId != INVALID_USERID)
		{
			DOUBLE fSpeakVolume = 0.0;
			BRAC_QueryUserState(m_dwUserId,BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume,sizeof(DOUBLE));
			m_ctrlAudioVolume.SetPos((INT)fSpeakVolume);
		}
		else
			m_ctrlAudioVolume.SetPos(0);
		break;
	case TIMER_REFRESH_NETSTATUS:
		if(m_dwUserId != INVALID_USERID)
		{
			DWORD dwNetStatus = 0;
			BRAC_QueryUserState(m_dwUserId,BRAC_USERSTATE_NETWORKSTATUS,(PCHAR)&dwNetStatus,sizeof(DWORD));
			switch(dwNetStatus)
			{
			case 0:	m_NetStatusPic.Load(IDR_IMAGE_NETSTATUS_VERYGOOD);	break;
			case 1:	m_NetStatusPic.Load(IDR_IMAGE_NETSTATUS_GOOD);		break;
			case 2:	m_NetStatusPic.Load(IDR_IMAGE_NETSTATUS_NORMAL);	break;
			case 3:	m_NetStatusPic.Load(IDR_IMAGE_NETSTATUS_BAD);		break;
			case 4:	m_NetStatusPic.Load(IDR_IMAGE_NETSTATUS_VERYBAD);	break;
			default:	break;
			}
			InvalidateRect(m_rcNetStatus);

			// 查询丢包率
			DWORD dwPackLossRate = 0;
			if(BRAC_QueryUserState(m_dwUserId, BRAC_USERSTATE_PACKLOSSRATE, (PCHAR)&dwPackLossRate, sizeof(DWORD)) == 0)
			{
				CString strNotify;
				strNotify.Format("快照(当前丢包率：%d%%)", dwPackLossRate==100 ? 0 : dwPackLossRate);
				m_btnSnapshot.SetTooltipText(strNotify);
			}
		}
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

LRESULT CVideoPanelDlg::OnRefreshButtonState(WPARAM wParam, LPARAM lParam)
{
	// 刷新视频控制按钮状态
	m_btnVideoCtrl.SetBitmaps(m_bVideoState ? IDB_BITMAP_OPENVIDEO : IDB_BITMAP_CLOSEVIDEO,RGB(255, 0, 255));
	m_btnVideoCtrl.SetTooltipText(m_bVideoState ? "关闭视频" : "打开视频");
	CRect rcVideoBtn;
	m_btnVideoCtrl.GetWindowRect(rcVideoBtn);
	ScreenToClient(rcVideoBtn);
	InvalidateRect(rcVideoBtn);
	// 刷新音频控制按钮状态
	m_btnAudioCtrl.SetBitmaps(m_bAudioState ? IDB_BITMAP_OPENAUDIO : IDB_BITMAP_CLOSEAUDIO,RGB(255, 0, 255));
	m_btnAudioCtrl.SetTooltipText(m_bVideoState ? "关闭语音" : "打开语音");
	CRect rcAudioBtn;
	m_btnAudioCtrl.GetWindowRect(rcAudioBtn);
	ScreenToClient(rcAudioBtn);
	InvalidateRect(rcAudioBtn);

	return 0;
}
// 退出全屏消息
LRESULT CVideoPanelDlg::OnExitFullScreen(WPARAM wParam, LPARAM lParam)
{
	// 隐藏全屏对话框
	if(m_pFullScreenDlg)
		m_pFullScreenDlg->ShowWindow(SW_HIDE);
	// 将视频显示在本地窗口
	m_bRegualShowVideo = TRUE;
	m_rcVideoDisp = m_rcMainDisp;
	AdjustVideoDispRect(m_rcVideoDisp);
	if(m_dwUserId != INVALID_USERID)
		BRAC_SetVideoPos(m_dwUserId,m_hWnd,m_rcVideoDisp.left,m_rcVideoDisp.top,m_rcVideoDisp.right,m_rcVideoDisp.bottom);
	Invalidate();
	return 0;
}
// 用户视频分辨率变化
void CVideoPanelDlg::OnVideoSizeChange(DWORD dwWidth, DWORD dwHeight)
{
	m_dwWidth = dwWidth;
	m_dwHeight = dwHeight;
}