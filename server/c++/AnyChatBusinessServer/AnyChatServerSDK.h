#if !defined(BR_ANYCHAT_SERVER_SDK_H__INCLUDED_)
#define BR_ANYCHAT_SERVER_SDK_H__INCLUDED_


/**
 *	AnyChat Server SDK Include File
 */


#pragma once


#define BRAS_API extern "C" __declspec(dllexport)

#define BRAS_SERVERAPPMSG_CONNECTED		1		///< 连接AnyChat服务器成功
#define BRAS_SERVERAPPMSG_DISCONNECT	2		///< 与AnyChat服务器断开连接

// 视频呼叫事件类型定义（API：BRAS_VideoCallControl 传入参数、OnVideoCallEvent回调参数）
#define BRAS_VIDEOCALL_EVENT_REQUEST    1        ///< 呼叫请求
#define BRAS_VIDEOCALL_EVENT_REPLY      2        ///< 呼叫请求回复
#define BRAS_VIDEOCALL_EVENT_START      3        ///< 视频呼叫会话开始事件
#define BRAS_VIDEOCALL_EVENT_FINISH     4        ///< 挂断（结束）呼叫会话

// 用户信息控制类型定义（API：BRAS_UserInfoControl 传入参数、OnUserInfoControl回调参数）
#define BRAS_USERINFO_CTRLCODE_KICKOUT		1	///< 将指定用户从系统中踢掉
#define BRAS_USERINFO_CTRLCODE_SYNCDATA		2	///< 将指定用户的数据同步给客户端
#define BRAS_USERINFO_CTRLCODE_FUNCCTRL		3	///< 客户端功能控制，wParam为功能参数组合
#define BRAS_USERINFO_CTRLCODE_BLOCKIP		4	///< 阻止IP地址连接服务器，lpStrValue为IP地址字符串，支持通配符“*”
#define BRAS_USERINFO_CTRLCODE_UNBLOCKIP	5	///< 允许IP地址连接服务器，lpStrValue为IP地址字符串，支持通配符“*”

#define BRAS_USERINFO_CTRLCODE_ADDGROUP		20	///< 添加用户分组，wParam为分组Id，lpStrValue为分组名称
#define BRAS_USERINFO_CTRLCODE_DELGROUP		21	///< 删除用户分组，wParam为分组Id
#define BRAS_USERINFO_CTRLCODE_ADDFRIEND	22	///< 添加用户好友，wParam为好友Id
#define BRAS_USERINFO_CTRLCODE_DELFRIEND	23	///< 删除用户好友，wParam为好友Id
#define BRAS_USERINFO_CTRLCODE_SETGROUPRELATION	24	///< 设置好友与分组的关联关系，wParam为分组Id，lParam为好友Id，表示好友属于某个分组

#define BRAS_USERINFO_CTRLCODE_APPDEFINE	100	///< 应用层自定义起始指令


// 服务器应用程序消息回调函数定义
typedef void (CALLBACK* BRAS_OnServerAppMessage_CallBack)(DWORD dwMsg, LPVOID lpUserValue);
// SDK定时器回调函数定义（上层应用可以在该回调中处理定时任务，而不需要额外开启线程，或是定时器）
typedef void (CALLBACK* BRAS_OnTimerEvent_CallBack)(LPVOID lpUserValue);

// 用户身份验证回调函数定义
typedef DWORD (CALLBACK* BRAS_VerifyUser_CallBack)(IN LPCTSTR lpUserName,IN LPCTSTR lpPassword, OUT LPDWORD lpUserID, OUT LPDWORD lpUserLevel, OUT LPTSTR lpNickName,IN DWORD dwNCLen, LPVOID lpUserValue);
// 用户申请进入房间回调函数定义
typedef DWORD (CALLBACK* BRAS_PrepareEnterRoom_CallBack)(DWORD dwUserId, DWORD dwRoomId, LPCTSTR lpRoomName,LPCTSTR lpPassword, LPVOID lpUserValue);
// 用户登录成功回调函数定义
typedef void (CALLBACK* BRAS_OnUserLoginAction_CallBack)(DWORD dwUserId, LPCTSTR szUserName, DWORD dwLevel, LPCTSTR szIpAddr, LPVOID lpUserValue);
// 用户注销回调函数定义
typedef void (CALLBACK* BRAS_OnUserLogoutAction_CallBack)(DWORD dwUserId, LPVOID lpUserValue);
// 用户进入房间回调函数定义
typedef void (CALLBACK* BRAS_OnUserEnterRoomAction_CallBack)(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue);
// 用户离开房间回调函数定义
typedef void (CALLBACK* BRAS_OnUserLeaveRoomAction_CallBack)(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue);
// 上层业务自定义数据回调函数定义
typedef void (CALLBACK* BRAS_OnRecvUserFilterData_CallBack)(DWORD dwUserId, BYTE* lpBuf, DWORD dwLen, LPVOID lpUserValue);
// 收到用户文字聊天通信数据回调函数定义
typedef void (CALLBACK* BRAS_OnRecvUserTextMsg_CallBack)(DWORD dwRoomId, DWORD dwSrcUserId, DWORD dwTarUserId, BOOL bSecret, LPCTSTR lpTextMessage, DWORD dwLen, LPVOID lpUserValue);
// 透明通道数据回调函数定义
typedef void (CALLBACK * BRAS_OnTransBuffer_CallBack)(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// 透明通道数据扩展回调函数定义
typedef void (CALLBACK * BRAS_OnTransBufferEx_CallBack)(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// 文件传输回调函数定义
typedef void (CALLBACK * BRAS_OnTransFile_CallBack)(DWORD dwUserId, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// 服务器录像回调函数定义
typedef void (CALLBACK * BRAS_OnServerRecord_CallBack)(DWORD dwUserId, DWORD dwParam, DWORD dwRecordServerId, DWORD dwElapse, LPCTSTR lpRecordFileName, LPVOID lpUserValue);
// 视频通话消息通知回调函数定义
typedef DWORD (CALLBACK * BRAS_OnVideoCallEvent_CallBack)(DWORD dwEventType, DWORD dwSrcUserId, DWORD dwTarUserId, DWORD dwErrorCode, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);
// 用户信息控制回调函数定义
typedef DWORD (CALLBACK * BRAS_OnUserInfoControl_CallBack)(DWORD dwSendUserId, DWORD dwUserId, DWORD dwCtrlCode, DWORD wParam, DWORD lParam, LPCTSTR lpStrValue, LPVOID lpUserValue); 

/**
 *	API 方法定义
 */
// 设置服务器应用程序消息回调函数
BRAS_API DWORD BRAS_SetOnServerAppMessageCallBack(BRAS_OnServerAppMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置SDK定时器回调函数（dwElapse：定时器间隔，单位：ms）
BRAS_API DWORD BRAS_SetTimerEventCallBack(DWORD dwElapse, BRAS_OnTimerEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);

// 设置用户身份验证回调函数
BRAS_API DWORD BRAS_SetVerifyUserCallBack(BRAS_VerifyUser_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置用户申请进入房间回调函数
BRAS_API DWORD BRAS_SetPrepareEnterRoomCallBack(BRAS_PrepareEnterRoom_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置用户登录成功回调函数
BRAS_API DWORD BRAS_SetOnUserLoginActionCallBack(BRAS_OnUserLoginAction_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置用户注销回调函数
BRAS_API DWORD BRAS_SetOnUserLogoutActionCallBack(BRAS_OnUserLogoutAction_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置用户进入房间回调函数
BRAS_API DWORD BRAS_SetOnUserEnterRoomActionCallBack(BRAS_OnUserEnterRoomAction_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置用户离开房间回调函数
BRAS_API DWORD BRAS_SetOnUserLeaveRoomActionCallBack(BRAS_OnUserLeaveRoomAction_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置用户上层业务自定义数据回调函数
BRAS_API DWORD BRAS_SetOnRecvUserFilterDataCallBack(BRAS_OnRecvUserFilterData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置用户文字聊天通信数据回调函数
BRAS_API DWORD BRAS_SetOnRecvUserTextMsgCallBack(BRAS_OnRecvUserTextMsg_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置透明通道数据回调函数
BRAS_API DWORD BRAS_SetOnTransBufferCallBack(BRAS_OnTransBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置透明通道数据扩展回调函数
BRAS_API DWORD BRAS_SetOnTransBufferExCallBack(BRAS_OnTransBufferEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置文件传输回调函数
BRAS_API DWORD BRAS_SetOnTransFileCallBack(BRAS_OnTransFile_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置服务器录像通知回调函数
BRAS_API DWORD BRAS_SetOnServerRecordCallBack(BRAS_OnServerRecord_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置视频通话消息通知回调函数
BRAS_API DWORD BRAS_SetOnVideoCallEventCallBack(BRAS_OnVideoCallEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置用户信息控制回调函数
BRAS_API DWORD BRAS_SetOnUserInfoControlCallBack(BRAS_OnUserInfoControl_CallBack lpFunction, LPVOID lpUserValue=NULL);


// 获取SDK版本信息
BRAS_API DWORD BRAS_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, TCHAR* lpCompileTime, DWORD dwBufLen);
// 初始化SDK
BRAS_API DWORD BRAS_InitSDK(DWORD dwReserved);
// 释放资源
BRAS_API DWORD BRAS_Release(void);

// 向指定用户发送数据
BRAS_API DWORD BRAS_SendBufToUser(DWORD dwUserId, LPCTSTR lpBuf, DWORD dwLen);
// 向指定房间的所有用户发送数据
BRAS_API DWORD BRAS_SendBufToRoom(DWORD dwRoomId, LPCTSTR lpBuf, DWORD dwLen);

// 向指定用户发送透明通道数据
BRAS_API DWORD BRAS_TransBuffer(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen);
// 向指定用户发送扩展缓冲区数据
BRAS_API DWORD BRAS_TransBufferEx(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// 向指定用户发送文件
BRAS_API DWORD BRAS_TransFile(DWORD dwUserId, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);

// 中心端录像控制
BRAS_API DWORD BRAS_StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam, DWORD dwRecordServerId);

// 视频呼叫事件控制（请求、回复、挂断等）
BRAS_API DWORD BRAS_VideoCallControl(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags=0, DWORD dwParam=0, LPCTSTR lpUserStr=NULL);

// 设置用户的详细信息
BRAS_API DWORD BRAS_SetUserInfo(DWORD dwUserId, DWORD dwInfoId, LPCTSTR lpInfoValue, DWORD dwFlags=0);
// 获取用户的详细信息
BRAS_API DWORD BRAS_GetUserInfo(DWORD dwUserId, DWORD dwInfoId, TCHAR* lpInfoValue, DWORD dwSize);
// 用户信息控制
BRAS_API DWORD BRAS_UserInfoControl(DWORD dwUserId, DWORD dwCtrlCode, DWORD wParam=0, DWORD lParam=0, LPCTSTR lpStrValue=NULL);

// SDK内核参数设置
BRAS_API DWORD BRAS_SetSDKOption(DWORD optname, CHAR* optval, DWORD optlen);



#endif //BR_ANYCHAT_SERVER_SDK_H__INCLUDED_