// FullScreenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BRAnyChatMeeting.h"
#include "FullScreenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDlg dialog


CFullScreenDlg::CFullScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFullScreenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFullScreenDlg)
	m_hNotifyWnd = NULL;
	//}}AFX_DATA_INIT
}


void CFullScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFullScreenDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFullScreenDlg, CDialog)
	//{{AFX_MSG_MAP(CFullScreenDlg)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDlg message handlers

void CFullScreenDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	::PostMessage(m_hNotifyWnd,WM_EXIT_FULLSCREEN, 0, 0);
	CDialog::OnLButtonDblClk(nFlags, point);
}

BOOL CFullScreenDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN)
    {
		switch(pMsg->wParam)
        {
        case VK_RETURN:
        case VK_SPACE:
		case VK_ESCAPE:
			::PostMessage(m_hNotifyWnd,WM_EXIT_FULLSCREEN, 0, 0);
			break;
		default:
			break;
        }
	}
	return CDialog::PreTranslateMessage(pMsg);
}
