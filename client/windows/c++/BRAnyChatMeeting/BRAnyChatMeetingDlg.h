// BRAnyChatMeetingDlg.h : header file
//

#if !defined(AFX_BRANYCHATMEETINGDLG_H__C55CF205_B790_49C7_B91F_6035C8EFC030__INCLUDED_)
#define AFX_BRANYCHATMEETINGDLG_H__C55CF205_B790_49C7_B91F_6035C8EFC030__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LoginDlg.h"
#include "hallDlg.h"
#include "VideoPanelDlg.h"
#include "SettingsDlg.h"
#include <BRAnyChatSDKProc.h>

class CLoginDlg;
class CHallDlg;
class CVideoPanelDlg;
class CSettingsDlg;

class CBRAnyChatMeetingDlg : public CDialog,
							 public CBRAnyChatSDKProc
{
// Construction
public:
	CBRAnyChatMeetingDlg(CWnd* pParent = NULL);	// standard constructor


public:
	CLoginDlg*	m_pLoginDlg;			///< 登录对话框界面
	CHallDlg*	m_pHallDlg;				///< 房间大厅对话框界面
	CSettingsDlg*	m_pSettingsDlg;		///< 高级设置对话框界面

	CVideoPanelDlg*	m_pSelfVideoDlg;	///< 本地视频对话框对象
	CVideoPanelDlg*	m_pPanelObjectArray[MAX_VIDEOPANEL_NUM];		///< 其他用户视频面板显示对象数组


	DWORD		m_dwSelfUserId;			///< 自己的用户编号

private:
	CImageList	m_UserStateImageList;	///< 用户状态图标
	CString		m_strTextOutput;		///< 保存输出信息
	CPicture	m_LogoPic;				///< 主界面Logo图片

private:
	// 初始化AnyChat SDK
	void InitAnyChatSDK(void);
	// 初始化在线用户列表控件
	void InitUserListCtrl(void);
	// 刷新在线用户数显示
	void RefreshOnlineUserNum(void);
	// 刷新指定列表项状态
	void RefreshListItemState(DWORD dwItemNo, DWORD dwUserId);
	// 增加新的用户到列表中
	void AddNewUserToList(DWORD dwUserId);

	// 根据分屏数定位视频面板显示位置
	void RelocateVideoPanel(DWORD dwSplitNum);
	// 刷新视频显示面板
	void RefreshVideoPanel(void);
	// 获取一个空闲的显示面板序号
	DWORD GetEmptyVideoPanelIndex(void);
	// 判断指定用户的视频面板是否已显示出来
	BOOL IsUserVideoPanelShow(DWORD dwUserId);
	// 绑定用户与视频面板
	void BindUserAndVideoPanel(DWORD dwUserId, CVideoPanelDlg* lpVideoPanelDlg);
	// 取消视频面板与用户的绑定
	void CleanVideoPanelBind(CVideoPanelDlg* lpVideoPanelDlg, BOOL bErase=TRUE);

	// 向文字消息输出框插入信息
	void InsertStringToTextOutput(CString strMsg);

public:
	// 用户关闭系统
	void OnUserExitSystem(void);


protected:		// 重载CBRAnyChatSDKProc类的虚函数

	// 连接服务器消息
	virtual void OnAnyChatConnectMessage(BOOL bSuccess, DWORD dwErrorCode);
	// 用户登陆消息
	virtual void OnAnyChatLoginMessage(DWORD dwUserId, DWORD dwErrorCode);
	// 用户进入房间消息
	virtual void OnAnyChatEnterRoomMessage(DWORD dwRoomId, DWORD dwErrorCode);
	// 房间在线用户消息
	virtual void OnAnyChatOnlineUserMessage(DWORD dwUserNum, DWORD dwRoomId);
	// 用户得到/释放mic消息
	virtual void OnAnyChatMicStateChgMessage(DWORD dwUserId, BOOL bGetMic);
	// 用户进入/退出房间消息
	virtual void OnAnyChatUserAtRoomMessage(DWORD dwUserId, BOOL bEnter);
	//网络断开消息
	virtual void OnAnyChatLinkCloseMessage(DWORD dwReason, DWORD dwErrorCode);
	
	// 用户摄像头状态改变消息
	virtual void OnAnyChatCameraStateChgMessage(DWORD dwUserId, DWORD dwState);
	// 用户聊天模式改变消息
	virtual void OnAnyChatChatModeChgMessage(DWORD dwUserId, BOOL bPublicChat);
	// 用户活动状态发生变化消息
	virtual void OnAnyChatActiveStateChgMessage(DWORD dwUserId, DWORD dwState);
	// P2P连接状态变化消息
	virtual void OnAnyChatP2PConnectStateMessage(DWORD dwUserId, DWORD dwState);
	// 用户视频分辨率改变消息
	virtual void OnAnyChatVideoSizeChgMessage(DWORD dwUserId, DWORD dwWidth, DWORD dwHeight);
	
	// 用户私聊请求消息
	virtual void OnAnyChatPrivateRequestMessage(DWORD dwUserId, DWORD dwRequestId);
	// 用户私聊请求回复消息
	virtual void OnAnyChatPrivateEchoMessage(DWORD dwUserId, DWORD dwErrorCode);
	// 用户退出私聊消息
	virtual void OnAnyChatPrivateExitMessage(DWORD dwUserId, DWORD dwErrorCode);
	
	// SDK警告消息
	virtual void OnAnyChatSDKWarningMessage(DWORD dwErrorCode, DWORD dwReserved);
	
	// 视频数据回调
	virtual void OnAnyChatVideoDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPBITMAPINFOHEADER lpbmiHeader);
	// 音频数据回调
	virtual void OnAnyChatAudioDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPWAVEFORMATEX lpWaveFormatEx);
	// 发送文字的回调函数
	virtual void OnAnyChatTextMsgCallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
	// 透明通道回调函数
	virtual void OnAnyChatTransBufferCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
	// 透明通道数据扩展回调函数
	virtual void OnAnyChatTransBufferExCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId);
	// 文件传输回调函数
	virtual void OnAnyChatTransFileCallBack(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId);
	// 音量变化回调函数
	virtual void OnAnyChatVolumeChangeCallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume);
	// SDK Filter 通信数据回调函数
	virtual void OnAnyChatSDKFilterDataCallBack(LPBYTE lpBuf, DWORD dwLen);
	// 录像、快照任务完成回调函数
	virtual void OnAnyChatRecordSnapShotCallBack(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType);
	// 异步消息通知回调函数
	virtual void OnAnyChatNotifyMessageCallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam);


// Dialog Data
	//{{AFX_DATA(CBRAnyChatMeetingDlg)
	enum { IDD = IDD_DIALOG_MEETING };
	CEdit	m_ctrlTextOutput;
	CComboBox	m_ctrlDispNumCombo;
	CListCtrl	m_ctrlUserList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBRAnyChatMeetingDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBRAnyChatMeetingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSelchangeComboDispNum();
	afx_msg void OnDblclkListUser(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonSendText();
	afx_msg void OnButtonAdvSet();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRANYCHATMEETINGDLG_H__C55CF205_B790_49C7_B91F_6035C8EFC030__INCLUDED_)
