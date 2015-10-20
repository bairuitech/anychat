#if !defined(AFX_HALLDLG_H__5C543137_12C1_46B0_B480_F6F7DB0BA607__INCLUDED_)
#define AFX_HALLDLG_H__5C543137_12C1_46B0_B480_F6F7DB0BA607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HallDlg.h : header file
//

#include "BRAnyChatMeetingDlg.h"

class CBRAnyChatMeetingDlg;

/**
 *	大厅界面显示类，用于显示登录成功之后的个人相关信息，以及房间信息
 */
class CHallDlg : public CDialog
{
// Construction
public:
	CHallDlg(CWnd* pParent);   // standard constructor


private:
	CBRAnyChatMeetingDlg*	m_pMainDlg;	
	BOOL	m_bWaitEnterRoom;		///< 是否正在等待进入房间，防止用户连续双击多个房间

public:
	// 更新界面用户信息
	void UpdateUserInfo(DWORD dwUserId);
	// 进入房间状态通知
	void OnEnterRoomNotify(DWORD dwRoomId, DWORD dwErrorCode);

private:
	// 初始化房间大厅列表
	void InitRoomListCtrl(void);
	// 填充大厅房间信息
	void FillRoomInfoToList(void);


// Dialog Data
	//{{AFX_DATA(CHallDlg)
	enum { IDD = IDD_DIALOG_HALL };
	CListCtrl	m_ctrlRoomList;
	int		m_iRoomId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnButtonExit();
	afx_msg void OnDblclkListRoom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonEnterRoom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HALLDLG_H__5C543137_12C1_46B0_B480_F6F7DB0BA607__INCLUDED_)
