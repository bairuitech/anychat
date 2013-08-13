// AnyChatBusinessServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AnyChatBusinessServer.h"
#include "AnyChatBusinessServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnyChatBusinessServerApp

BEGIN_MESSAGE_MAP(CAnyChatBusinessServerApp, CWinApp)
	//{{AFX_MSG_MAP(CAnyChatBusinessServerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnyChatBusinessServerApp construction

CAnyChatBusinessServerApp::CAnyChatBusinessServerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAnyChatBusinessServerApp object

CAnyChatBusinessServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAnyChatBusinessServerApp initialization

BOOL CAnyChatBusinessServerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

	CAnyChatBusinessServerDlg dlg;
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
