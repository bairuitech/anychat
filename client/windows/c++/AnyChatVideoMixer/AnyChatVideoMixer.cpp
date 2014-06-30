// AnyChatVideoMixer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AnyChatVideoMixer.h"
#include "AnyChatVideoMixerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnyChatVideoMixerApp

BEGIN_MESSAGE_MAP(CAnyChatVideoMixerApp, CWinApp)
	//{{AFX_MSG_MAP(CAnyChatVideoMixerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnyChatVideoMixerApp construction

CAnyChatVideoMixerApp::CAnyChatVideoMixerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAnyChatVideoMixerApp object

CAnyChatVideoMixerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAnyChatVideoMixerApp initialization

BOOL CAnyChatVideoMixerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

	CAnyChatVideoMixerDlg dlg;
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
