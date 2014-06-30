#include "afxwin.h"
#if !defined(AFX_CONFIGDLG_H__D42D21BA_B726_42C3_A210_05208E3BDEE9__INCLUDED_)
#define AFX_CONFIGDLG_H__D42D21BA_B726_42C3_A210_05208E3BDEE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_DIALOG_CONFIG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_szServer;
	int m_iPort;
	CString m_szUserName;
	CString m_szPassword;
	int m_iBitrate;
	int m_iFrameRate;
	CComboBox m_VideoSizeCombo;
	int m_iRoomId;
	BOOL m_bAudioMix;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__D42D21BA_B726_42C3_A210_05208E3BDEE9__INCLUDED_)
