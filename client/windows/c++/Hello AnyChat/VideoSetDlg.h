#if !defined(AFX_VIDEOSETDLG_H__664275CD_D25D_4617_BDF9_55BBFFF58C78__INCLUDED_)
#define AFX_VIDEOSETDLG_H__664275CD_D25D_4617_BDF9_55BBFFF58C78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VideoSetDlg dialog

class VideoSetDlg : public CDialog
{
// Construction
public:
	void initDlg();
	void refreshDevice();
	VideoSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(VideoSetDlg)
	enum { IDD = IDD_DIALOG_VIDEOSET };
	CComboBox	m_playDevice;
	CComboBox	m_videoDevice;
	CComboBox	m_resolution;
	CComboBox	m_quality;
	CComboBox	m_preparam;
	CComboBox	m_frameRate;
	CComboBox	m_bitRate;
	CComboBox	m_audioMode;
	CComboBox	m_audioDevice;
	BOOL	m_enableAGC;
	BOOL	m_enableEcho;
	BOOL	m_enableNS;
	BOOL	m_enableVAD;
	BOOL	m_serverPriority;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VideoSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VideoSetDlg)
	afx_msg void OnCheckAGC();
	afx_msg void OnCheckEcho();
	afx_msg void OnCheckNS();
	afx_msg void OnCheckVAD();
	afx_msg void OnCheckServerPriority();
	afx_msg void OnSelAudioDevice();
	afx_msg void OnSelAudioMode();
	afx_msg void OnSelBitRate();
	afx_msg void OnSelFrameRate();
	afx_msg void OnSelPreParam();
	afx_msg void OnSelVideoQuality();
	afx_msg void OnSelResolution();
	afx_msg void OnSelVideodevice();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelPlayDevice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOSETDLG_H__664275CD_D25D_4617_BDF9_55BBFFF58C78__INCLUDED_)
