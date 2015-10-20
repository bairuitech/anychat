// AnyChatInputVideoDlg.h : header file
//

#if !defined(AFX_ANYCHATINPUTVIDEODLG_H__22D1A46B_6920_4001_8435_9CAC7F4FCA7C__INCLUDED_)
#define AFX_ANYCHATINPUTVIDEODLG_H__22D1A46B_6920_4001_8435_9CAC7F4FCA7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <BRAnyChatSDKProc.h>

#pragma comment(lib, "BRAnyChatCore.lib")


class CAnyChatInputVideoDlg : public CDialog,
							  public CBRAnyChatSDKProc
{
// Construction
public:
	CAnyChatInputVideoDlg(CWnd* pParent = NULL);	// standard constructor


public:
	CString		m_strLog;
	BOOL		m_bSuccessEnterRoom;
	DWORD		m_dwRemoteUserId;

	BYTE*		m_lpVideoBuf;


public:
	// 连接服务器消息
	virtual void OnAnyChatConnectMessage(BOOL bSuccess);
	// 用户登陆消息
	virtual void OnAnyChatLoginMessage(DWORD dwUserId, DWORD dwErrorCode);
	// 用户进入房间消息
	virtual void OnAnyChatEnterRoomMessage(DWORD dwRoomId, DWORD dwErrorCode);
	//网络断开消息
	virtual void OnAnyChatLinkCloseMessage(DWORD dwErrorCode);

	// 房间在线用户消息
	virtual void OnAnyChatOnlineUserMessage(DWORD dwUserNum, DWORD dwRoomId);
	// 用户进入/退出房间消息
	virtual void OnAnyChatUserAtRoomMessage(DWORD dwUserId, BOOL bEnter);

	// 视频数据回调
	virtual void OnAnyChatVideoDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPBITMAPINFOHEADER lpbmiHeader);

	// 记录日志到列表
	void AppendLogString(CString str);


// Dialog Data
	//{{AFX_DATA(CAnyChatInputVideoDlg)
	enum { IDD = IDD_ANYCHATINPUTVIDEO_DIALOG };
	CEdit	m_ctrlEditLog;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnyChatInputVideoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAnyChatInputVideoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInit();
	afx_msg void OnDestroy();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonConnect();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANYCHATINPUTVIDEODLG_H__22D1A46B_6920_4001_8435_9CAC7F4FCA7C__INCLUDED_)
