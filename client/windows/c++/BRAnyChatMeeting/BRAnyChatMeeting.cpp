// BRAnyChatMeeting.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BRAnyChatMeeting.h"
#include "BRAnyChatMeetingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatMeetingApp

BEGIN_MESSAGE_MAP(CBRAnyChatMeetingApp, CWinApp)
	//{{AFX_MSG_MAP(CBRAnyChatMeetingApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatMeetingApp construction

CBRAnyChatMeetingApp::CBRAnyChatMeetingApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBRAnyChatMeetingApp object

CBRAnyChatMeetingApp theApp;

CBRAnyChatMeetingDlg*	g_lpMeetingDlg = NULL;

BOOL CBRAnyChatMeetingApp::InitInstance()
{
	AfxEnableControlContainer();

	AfxSocketInit();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

#ifdef _HRC_USE_SKIN_
	TCHAR szSkinPath[MAX_PATH] = {0};
	TCHAR szSkinFile[MAX_PATH] = {0};
	GetModuleFileName(NULL,szSkinPath,sizeof(szSkinPath)); 
	(strrchr(szSkinPath,'\\'))[1] = 0; 
	strcat(szSkinPath,SUB_PATH_SKINFILE);
	_snprintf(szSkinFile,sizeof(szSkinFile),"%s\\%s",szSkinPath,DEFAULT_SKIN_FILENAME);
	
	skinppLoadSkin(szSkinFile);
#endif

	g_lpMeetingDlg = new CBRAnyChatMeetingDlg;
	m_pMainWnd = g_lpMeetingDlg;
	return g_lpMeetingDlg->Create(IDD_DIALOG_MEETING,NULL);
/*
	CBRAnyChatMeetingDlg dlg;
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
*/
}

int CBRAnyChatMeetingApp::ExitInstance() 
{
	if(g_lpMeetingDlg)
	{
		g_lpMeetingDlg->DestroyWindow();
		delete g_lpMeetingDlg;
		g_lpMeetingDlg = NULL;
	}
	return CWinApp::ExitInstance();
}
