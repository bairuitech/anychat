#if !defined(AFX_FULLSCREENDLG_H__8C7DE0E2_43D2_4FAA_B603_6DF6E785F043__INCLUDED_)
#define AFX_FULLSCREENDLG_H__8C7DE0E2_43D2_4FAA_B603_6DF6E785F043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FullScreenDlg.h : header file
//

#define WM_EXIT_FULLSCREEN		WM_USER + 201			// 退出全屏消息

class CFullScreenDlg : public CDialog
{
// Construction
public:
	CFullScreenDlg(CWnd* pParent = NULL);   // standard constructor


private:
	HWND	m_hNotifyWnd;


public:
	// 设置消息通知句柄
	void SetNotifyWnd(HWND hWnd)	{	m_hNotifyWnd = hWnd;	}

// Dialog Data
	//{{AFX_DATA(CFullScreenDlg)
	enum { IDD = IDD_DIALOG_FULLSCREEN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFullScreenDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFullScreenDlg)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLSCREENDLG_H__8C7DE0E2_43D2_4FAA_B603_6DF6E785F043__INCLUDED_)
