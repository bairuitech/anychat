// AnyChatCallCenterServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AnyChatCallCenterServer.h"
#include "AnyChatCallCenterServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnyChatCallCenterServerApp

BEGIN_MESSAGE_MAP(CAnyChatCallCenterServerApp, CWinApp)
	//{{AFX_MSG_MAP(CAnyChatCallCenterServerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnyChatCallCenterServerApp construction

CAnyChatCallCenterServerApp::CAnyChatCallCenterServerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAnyChatCallCenterServerApp object

CAnyChatCallCenterServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAnyChatCallCenterServerApp initialization

BOOL CAnyChatCallCenterServerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

	CAnyChatCallCenterServerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
