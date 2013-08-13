// AnyChatBusinessServerDlg.h : header file
//

#if !defined(AFX_ANYCHATBUSINESSSERVERDLG_H__69ADA4B7_BCD7_435B_A14D_20271C905BA1__INCLUDED_)
#define AFX_ANYCHATBUSINESSSERVERDLG_H__69ADA4B7_BCD7_435B_A14D_20271C905BA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAnyChatBusinessServerDlg dialog

class CAnyChatBusinessServerDlg : public CDialog
{
// Construction
public:
	CAnyChatBusinessServerDlg(CWnd* pParent = NULL);	// standard constructor


public:
	CString		m_strLogInfo;			///< 保存日志信息


	// 显示日志信息
 	void AppendLogString(CString logstr);

// Dialog Data
	//{{AFX_DATA(CAnyChatBusinessServerDlg)
	enum { IDD = IDD_ANYCHATBUSINESSSERVER_DIALOG };
	CEdit	m_ctrlEditLog;
	CComboBox	m_ComboStyle;
	int		m_iTargetId;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnyChatBusinessServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAnyChatBusinessServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnButtonSendbuf();
	afx_msg void OnButtonTransFile();
	afx_msg void OnButtonTransBufferEx();
	afx_msg void OnButtonTransBuffer();
	afx_msg void OnButtonStartRecord();
	afx_msg void OnButtonStopRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANYCHATBUSINESSSERVERDLG_H__69ADA4B7_BCD7_435B_A14D_20271C905BA1__INCLUDED_)
