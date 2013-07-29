// BRAnyChatSDKDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BRAnyChatSDKDemo.h"
#include "BRAnyChatSDKDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatSDKDemoApp

BEGIN_MESSAGE_MAP(CBRAnyChatSDKDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CBRAnyChatSDKDemoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatSDKDemoApp construction

CBRAnyChatSDKDemoApp::CBRAnyChatSDKDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBRAnyChatSDKDemoApp object

CBRAnyChatSDKDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatSDKDemoApp initialization

BOOL CBRAnyChatSDKDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

	CBRAnyChatSDKDemoDlg dlg;
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
