// AnyChatInputVideo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AnyChatInputVideo.h"
#include "AnyChatInputVideoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnyChatInputVideoApp

BEGIN_MESSAGE_MAP(CAnyChatInputVideoApp, CWinApp)
	//{{AFX_MSG_MAP(CAnyChatInputVideoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnyChatInputVideoApp construction

CAnyChatInputVideoApp::CAnyChatInputVideoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAnyChatInputVideoApp object

CAnyChatInputVideoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAnyChatInputVideoApp initialization

BOOL CAnyChatInputVideoApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CAnyChatInputVideoDlg dlg;
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
