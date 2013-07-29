// BRAnyChatSDKDemo.h : main header file for the BRANYCHATSDKDEMO application
//

#if !defined(AFX_BRANYCHATSDKDEMO_H__32BBB796_C150_4691_8ED2_690092B9D056__INCLUDED_)
#define AFX_BRANYCHATSDKDEMO_H__32BBB796_C150_4691_8ED2_690092B9D056__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatSDKDemoApp:
// See BRAnyChatSDKDemo.cpp for the implementation of this class
//

class CBRAnyChatSDKDemoApp : public CWinApp
{
public:
	CBRAnyChatSDKDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBRAnyChatSDKDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBRAnyChatSDKDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRANYCHATSDKDEMO_H__32BBB796_C150_4691_8ED2_690092B9D056__INCLUDED_)
