// BRAnyChatSDKDemoDlg.h : header file
//

#if !defined(AFX_BRANYCHATSDKDEMODLG_H__4BC5D2FC_57F3_4D5E_B580_BCA7C03DFEC4__INCLUDED_)
#define AFX_BRANYCHATSDKDEMODLG_H__4BC5D2FC_57F3_4D5E_B580_BCA7C03DFEC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <BRAnyChatCoreSDK.h>
#include <GVMessageDefine.h>
#pragma comment(lib,"BRAnyChatCore.lib")

#define DEMO_SHOW_USER_NUM		4						///< 定义在demo程序中显示用户面板的数量



class CBRAnyChatSDKDemoDlg : public CDialog
{
// Construction
public:
	CBRAnyChatSDKDemoDlg(CWnd* pParent = NULL);	// standard constructor

	CString		m_strLogInfo;			///< 保存日志信息
	CRect					m_UserRect[DEMO_SHOW_USER_NUM];				///< 用户显示位置
	INT						m_iUserID[DEMO_SHOW_USER_NUM];				///< 用户ID号


	DWORD		m_dwTransTaskId;		///< 传输任务编号

public:
	// 显示日志信息
	void AppendLogString(CString logstr);
	// 绘制用户视频
	void DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader);
	// 录音的音量发生改变
	void OnWaveInVolumeChange(DWORD dwVolume);
	// 放音的音量发生改变
	void OnWaveOutVolumeChange(DWORD dwVolume);




// Dialog Data
	//{{AFX_DATA(CBRAnyChatSDKDemoDlg)
	enum { IDD = IDD_BRANYCHATSDKDEMO_DIALOG };
	CProgressCtrl	m_ctrlSpeakVolume0;
	CProgressCtrl	m_ctrlSpeakVolume1;
	CProgressCtrl	m_ctrlSpeakVolume2;
	CProgressCtrl	m_ctrlSpeakVolume3;
	CSliderCtrl	m_ctrlOutVolume;
	CSliderCtrl	m_ctrlInVolume;
	CComboBox	m_cbVideoCapture;
	CComboBox	m_cbAudioCapture;
	CEdit	m_ctrlEditLog;
	BOOL	m_bEnableAGC;
	BOOL	m_bEnableEcho;
	BOOL	m_bEnableNS;
	BOOL	m_bEnableVAD;
	UINT	m_iPort;
	int		m_iRoomId;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBRAnyChatSDKDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBRAnyChatSDKDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnButtonInit();
	afx_msg LRESULT OnGVClientConnect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientLogin(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientMicStateChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientLinkClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGVClientChatModeChange(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonEnterRoom();
	afx_msg void OnButtonLeaveRoom();
	afx_msg void OnButtonVideoproperty();
	afx_msg void OnButtonRefreshCapture();
	afx_msg void OnSelchangeComboVideoCapture();
	afx_msg void OnSliderOutVolumeChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOnSliderInVolumeChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelChangeComboAudioCapture();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonSendFile();
	afx_msg void OnCheckVad();
	afx_msg void OnCheckAgc();
	afx_msg void OnCheckEcho();
	afx_msg void OnCheckNs();
	afx_msg void OnButtonTransbuf();
	afx_msg void OnButtonRelease();
	afx_msg void OnButtonVideoctrl0();
	afx_msg void OnButtonVideoctrl1();
	afx_msg void OnButtonVideoctrl2();
	afx_msg void OnButtonVideoctrl3();
	afx_msg void OnButtonAudioctrl0();
	afx_msg void OnButtonAudioctrl1();
	afx_msg void OnButtonAudioctrl2();
	afx_msg void OnButtonAudioctrl3();
	afx_msg void OnButtonRecordctrl0();
	afx_msg void OnButtonRecordctrl1();
	afx_msg void OnButtonRecordctrl2();
	afx_msg void OnButtonRecordctrl3();
	afx_msg void OnButtonSnapshotctrl0();
	afx_msg void OnButtonSnapshotctrl1();
	afx_msg void OnButtonSnapshotctrl2();
	afx_msg void OnButtonSnapshotctrl3();
	afx_msg void OnButtonLogin();
	afx_msg void OnButtonLogout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRANYCHATSDKDEMODLG_H__4BC5D2FC_57F3_4D5E_B580_BCA7C03DFEC4__INCLUDED_)
