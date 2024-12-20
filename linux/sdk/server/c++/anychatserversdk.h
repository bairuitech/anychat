#if !defined(BR_ANYCHAT_SERVER_SDK_H__INCLUDED_)
#define BR_ANYCHAT_SERVER_SDK_H__INCLUDED_

#include "typedef.h"

/**
 *	AnyChat Server SDK Include File
 */


#pragma once


#define BRAS_API extern "C"


#define BRAS_SERVERAPPMSG_CONNECTED			1	///< 连接AnyChat服务器成功
#define BRAS_SERVERAPPMSG_DISCONNECT		2	///< 与AnyChat服务器断开连接

// 服务器消息类型定义（回调事件：BRAS_OnServerAppMessageEx_CallBack 参数）
#define BRAS_MESSAGE_CORESERVERCONN			10	///< 与核心服务器的连接消息，wParam为errorcode
#define BRAS_MESSAGE_RECORDSERVERCONN		11	///< 与录像服务器的连接消息，wParam为errorcode，lParam为recordserverid
#define BRAS_MESSAGE_LOGINSERVERCONN		12	///< 与登录服务器的连接消息，wParam为errorcode，lParam为loginserverid
#define BRAS_MESSAGE_ROOMSERVERCONN			13	///< 与房间服务器的连接消息，wParam为errorcode，lParam为roomserverid
#define BRAS_MESSAGE_MEDIASERVERCONN		14	///< 与流媒体服务器的连接消息，wParam为errorcode，lParam为mediaserverid

// 视频呼叫事件类型定义（API：BRAS_VideoCallControl 传入参数、OnVideoCallEvent回调参数）
#define BRAS_VIDEOCALL_EVENT_REQUEST		1	///< 呼叫请求
#define BRAS_VIDEOCALL_EVENT_REPLY			2	///< 呼叫请求回复
#define BRAS_VIDEOCALL_EVENT_START			3	///< 视频呼叫会话开始事件
#define BRAS_VIDEOCALL_EVENT_FINISH			4	///< 挂断（结束）呼叫会话

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

// 内核参数设置常量定义（API：BRAS_SetSDKOption 传入参数）
#define BRAS_SO_GETTRANSBUFTIMESTAMP		1	///< 获取透明通道时间戳
#define BRAS_SO_RECORD_VIDEOBR				2	///< 录像视频码率设置（参数为：int型，单位：bps）
#define BRAS_SO_RECORD_AUDIOBR				3	///< 录像音频码率设置（参数为：int型，单位：bps）
#define BRAS_SO_RECORD_FILETYPE				4	///< 录制文件类型设置（参数为：int型， 0 MP4[默认], 1 WMV, 2 FLV, 3 MP3）
#define BRAS_SO_RECORD_WIDTH				5	///< 录制视频宽度设置（参数为：int型，如：320）
#define BRAS_SO_RECORD_HEIGHT				6	///< 录制文件高度设置（参数为：int型，如：240）
#define BRAS_SO_RECORD_FILENAMERULE			7	///< 录制文件名命名规则（参数为：int型）

// 初始化标志（API：BRAS_InitSDK 传入参数）
#define BRAS_INITFLAGS_MULTITHREADS		0x01	///< 多线程模式

// 回调函数类型定义（API：BRAS_SetCallBack 传入参数）
#define BRAS_CBTYPE_APPMESSAGE				1	///< 服务器应用程序消息回调
#define BRAS_CBTYPE_APPMESSAGEEX			2	///< 服务器应用程序消息（扩展）回调
#define BRAS_CBTYPE_ONTIMER					3	///< SDK定时器回调
#define BRAS_CBTYPE_VERIFYUSER				4	///< 用户身份验证回调
#define BRAS_CBTYPE_PERPAREENTERROOM		5	///< 用户申请进入房间回调
#define BRAS_CBTYPE_USERLOGIN				6	///< 用户登录成功回调
#define BRAS_CBTYPE_USERLOGOUT				7	///< 用户注销回调
#define BRAS_CBTYPE_USERLOGOUTEX			8	///< 用户注销（扩展）回调
#define BRAS_CBTYPE_USERENTERROOM			9	///< 用户进入房间回调
#define BRAS_CBTYPE_USERLEAVEROOM			10	///< 用户离开房间回调
#define BRAS_CBTYPE_FILTERDATA				11	///< 上层业务自定义数据回调
#define BRAS_CBTYPE_TEXTMESSAGE				12	///< 文字聊天通信数据回调
#define BRAS_CBTYPE_TRANSBUFFER				13	///< 透明通道数据回调
#define BRAS_CBTYPE_TRANSBUFFEREX			14	///< 透明通道数据扩展回调
#define BRAS_CBTYPE_TRANSFILE				15	///< 文件传输回调函数
#define BRAS_CBTYPE_SERVERRECORD			16	///< 服务器录像回调
#define BRAS_CBTYPE_SERVERRECORDEX			17	///< 服务器录像（扩展）回调
#define BRAS_CBTYPE_VIDEOCALL				18	///< 视频通话消息通知回调
#define BRAS_CBTYPE_USERINFOCTRL			19	///< 用户信息控制回调


// 录像功能标志定义（API：BRAS_StreamRecordCtrl 传入参数）
#define ANYCHAT_RECORD_FLAGS_VIDEO		0x00000001	///< 录制视频
#define ANYCHAT_RECORD_FLAGS_AUDIO		0x00000002	///< 录制音频
#define ANYCHAT_RECORD_FLAGS_SERVER		0x00000004	///< 服务器端录制
#define ANYCHAT_RECORD_FLAGS_MIXAUDIO	0x00000010	///< 录制音频时，将其它人的声音混音后录制
#define ANYCHAT_RECORD_FLAGS_MIXVIDEO	0x00000020	///< 录制视频时，将其它人的视频迭加后录制
#define ANYCHAT_RECORD_FLAGS_ABREAST	0x00000100	///< 录制视频时，将其它人的视频并列录制
#define ANYCHAT_RECORD_FLAGS_STEREO		0x00000200	///< 录制音频时，将其它人的声音混合为立体声后录制
#define ANYCHAT_RECORD_FLAGS_SNAPSHOT	0x00000400	///< 拍照
#define ANYCHAT_RECORD_FLAGS_LOCALCB	0x00000800	///< 触发本地回调
#define ANYCHAT_RECORD_FLAGS_STREAM		0x00001000	///< 对视频流进行录制（效率高，但可能存在视频方向旋转的问题）


// 服务器应用程序消息回调函数定义
typedef void (CALLBACK* BRAS_OnServerAppMessage_CallBack)(DWORD dwMsg, LPVOID lpUserValue);
// 服务器应用程序消息（扩展）回调函数定义
typedef void (CALLBACK* BRAS_OnServerAppMessageEx_CallBack)(DWORD dwNotifyMessage, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
// SDK定时器回调函数定义（上层应用可以在该回调中处理定时任务，而不需要额外开启线程，或是定时器）
typedef void (CALLBACK* BRAS_OnTimerEvent_CallBack)(LPVOID lpUserValue);

// 用户身份验证回调函数定义
typedef DWORD (CALLBACK* BRAS_VerifyUser_CallBack)(LPCTSTR lpUserName,LPCTSTR lpPassword, LPDWORD lpUserID, LPDWORD lpUserLevel, LPTSTR lpNickName,DWORD dwNCLen, LPVOID lpUserValue);
// 用户申请进入房间回调函数定义
typedef DWORD (CALLBACK* BRAS_PrepareEnterRoom_CallBack)(DWORD dwUserId, DWORD dwRoomId, LPCTSTR lpRoomName,LPCTSTR lpPassword, LPVOID lpUserValue);
// 用户登录成功回调函数定义
typedef void (CALLBACK* BRAS_OnUserLoginAction_CallBack)(DWORD dwUserId, LPCTSTR szUserName, DWORD dwLevel, LPCTSTR szIpAddr, LPVOID lpUserValue);
// 用户注销回调函数定义
typedef void (CALLBACK* BRAS_OnUserLogoutAction_CallBack)(DWORD dwUserId, LPVOID lpUserValue);
// 用户注销扩展回调函数定义（增加注销的错误代码）
typedef void (CALLBACK* BRAS_OnUserLogoutActionEx_CallBack)(DWORD dwUserId, DWORD dwErrorCode, LPVOID lpUserValue);
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
// 服务器录像回调函数定义（扩展）
typedef void (CALLBACK * BRAS_OnServerRecordEx_CallBack)(DWORD dwUserId, LPCTSTR lpFileName, DWORD dwElapse, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, DWORD dwRecordServerId, LPVOID lpUserValue);
// 视频通话消息通知回调函数定义
typedef DWORD (CALLBACK * BRAS_OnVideoCallEvent_CallBack)(DWORD dwEventType, DWORD dwSrcUserId, DWORD dwTarUserId, DWORD dwErrorCode, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);


/**
 *	API 方法定义
 */
// 设置服务器应用程序消息回调函数
BRAS_API DWORD BRAS_SetOnServerAppMessageCallBack(BRAS_OnServerAppMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置服务器应用程序消息（扩展）回调函数
BRAS_API DWORD BRAS_SetOnServerAppMessageExCallBack(BRAS_OnServerAppMessageEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
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
// 设置用户注销扩展回调函数
BRAS_API DWORD BRAS_SetOnUserLogoutActionExCallBack(BRAS_OnUserLogoutActionEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
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
// 设置回调函数
BRAS_API DWORD BRAS_SetCallBack(DWORD dwCBType, LPVOID lpFunction, LPVOID lpUserValue=NULL);


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
// 中心端录像控制（扩展）
BRAS_API DWORD BRAS_StreamRecordCtrlEx(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr=NULL, DWORD dwRecordServerId=-1);
// 发送透明通道数据给录像服务器
BRAS_API DWORD BRAS_TransBuffer2RecordServer(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, DWORD dwParam, DWORD dwRecordServerId);

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
