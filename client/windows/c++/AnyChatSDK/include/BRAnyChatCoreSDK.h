#if !defined(BR_ANYCHAT_CORE_SDK_H__INCLUDED_)
#define BR_ANYCHAT_CORE_SDK_H__INCLUDED_

#include <mmsystem.h>
#include <wingdi.h>
#include "AnyChatDefine.h"
#include "AnyChatObjectDefine.h"
#include "GVErrorCodeDefine.h"
#include "GVMessageDefine.h"


/**
 *	AnyChat Core SDK Include File
 */



#define BRAC_API extern "C" __declspec(dllexport)


// 视频数据回调函数定义
typedef void (CALLBACK * BRAC_VideoData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue);
// 视频数据扩展回调函数定义（增加时间戳）
typedef void (CALLBACK * BRAC_VideoDataEx_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, DWORD dwTimeStamp, LPVOID lpUserValue);
// 视频数据扩展回调函数定义（增加时间戳，支持多路流）
typedef void (CALLBACK * BRAC_VideoDataEx2_CallBack)(DWORD dwUserid, DWORD dwStreamIndex, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, DWORD dwTimeStamp, LPVOID lpUserValue);
// 音频数据回调函数定义
typedef void (CALLBACK * BRAC_AudioData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue);
// 音频数据扩展回调函数定义（增加时间戳）
typedef void (CALLBACK * BRAC_AudioDataEx_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, DWORD dwTimeStamp, LPVOID lpUserValue);
// 音频数据扩展回调函数定义（增加时间戳，支持多路流）
typedef void (CALLBACK * BRAC_AudioDataEx2_CallBack)(DWORD dwUserid, DWORD dwStreamIndex, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, DWORD dwTimeStamp, LPVOID lpUserValue);
// 文字消息回调函数定义
typedef void (CALLBACK * BRAC_TextMessage_CallBack)(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue);
// 透明通道数据回调函数定义
typedef void (CALLBACK * BRAC_TransBuffer_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// 透明通道数据扩展回调函数定义
typedef void (CALLBACK * BRAC_TransBufferEx_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// 文件传输回调函数定义
typedef void (CALLBACK * BRAC_TransFile_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// 文件传输回调函数定义（扩展）
typedef void (CALLBACK * BRAC_TransFileEx_CallBack)(DWORD dwUserid, DWORD dwErrorCode, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD dwFlags, CHAR* lpTaskGuid, LPCTSTR lpUserStr, LPVOID lpUserValue);
// 音量变化回调函数定义
typedef void (CALLBACK * BRAC_VolumeChange_CallBack)(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue);
// SDK Filter 通信数据回调函数定义
typedef void (CALLBACK * BRAC_SDKFilterData_CallBack)(LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// 录像、快照任务完成回调函数定义
typedef void (CALLBACK * BRAC_RecordSnapShot_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType, LPVOID lpUserValue);
// 录像、快照任务完成扩展回调函数定义
typedef void (CALLBACK * BRAC_RecordSnapShotEx_CallBack)(DWORD dwUserId, LPCTSTR lpFileName, DWORD dwElapse, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);
// 录像、快照任务完成扩展回调函数定义
typedef void (CALLBACK * BRAC_RecordSnapShotEx2_CallBack)(DWORD dwUserId, DWORD dwErrorCode, LPCTSTR lpFileName, DWORD dwElapse, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);
// 异步消息通知回调函数定义
typedef void (CALLBACK* BRAC_NotifyMessage_CallBack)(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
// 视频屏幕事件回调函数定义
typedef void (CALLBACK * BRAC_VideoScreenEvent_CallBack)(DWORD dwUserid, DWORD type, DWORD key, DWORD dwFlags, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
// 视频通话消息通知回调函数定义
typedef void (CALLBACK * BRAC_VideoCallEvent_CallBack)(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);
// 数据加密、解密回调函数定义
typedef DWORD (CALLBACK * BRAC_DataEncDec_CallBack)(DWORD dwUserId, DWORD dwFlags, LPBYTE lpInBuf, DWORD dwInSize, LPBYTE lpOutBuf, LPDWORD lpOutSize, LPVOID lpUserValue);
// 网络数据发送回调函数定义
typedef DWORD (CALLBACK * BRAC_NetworkDataSend_CallBack)(DWORD hSocket, DWORD dwFlags, CHAR* lpBuf, DWORD dwSize, DWORD dwTargetAddr, DWORD dwTargetPort, LPVOID lpUserValue);
// 业务对象事件通知回调函数定义
typedef void (CALLBACK * BRAC_ObjectEventNotify_CallBack)(DWORD dwObjectType, DWORD dwObjectId, DWORD dwEventType, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3, DWORD dwParam4, LPCTSTR lpStrParam, LPVOID lpUserValue);
// Core SDK事件通知（Json格式）
typedef void (CALLBACK * BRAC_CoreSDKEvent_CallBack)(DWORD dwEventType, LPCTSTR lpEventJsonStr, LPVOID lpUserValue);
// Core SDK数据流回调
typedef void (CALLBACK * BRAC_CoreSDKData_CallBack)(DWORD dwDataType, LPVOID lpBuf, DWORD dwLen, LPCTSTR lpJsonStr, LPVOID lpUserValue);

/**
 *	API方法定义
 */

// 获取SDK版本信息
BRAC_API DWORD BRAC_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, TCHAR* lpCompileTime, DWORD dwBufLen);
// 激活（关闭）SDK调用日志
BRAC_API DWORD BRAC_ActiveCallLog(BOOL bActive);

// 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
BRAC_API DWORD BRAC_SetServerAuthPass(LPCTSTR lpPassword);
// 初始化系统
BRAC_API DWORD BRAC_InitSDK(HWND hWnd, DWORD dwFuncMode);

// 设置视频数据回调函数
BRAC_API DWORD BRAC_SetVideoDataCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置视频数据扩展回调函数（增加时间戳）
BRAC_API DWORD BRAC_SetVideoDataExCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoDataEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置音频数据回调函数
BRAC_API DWORD BRAC_SetAudioDataCallBack(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置音频数据回调扩展函数（增加时间戳）
BRAC_API DWORD BRAC_SetAudioDataExCallBack(BRAC_AudioDataEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置文字消息回调函数
BRAC_API DWORD BRAC_SetTextMessageCallBack(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置透明通道数据回调函数
BRAC_API DWORD BRAC_SetTransBufferCallBack(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置透明通道数据扩展回调函数
BRAC_API DWORD BRAC_SetTransBufferExCallBack(BRAC_TransBufferEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置文件传输回调函数
BRAC_API DWORD BRAC_SetTransFileCallBack(BRAC_TransFile_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置音量变化回调函数
BRAC_API DWORD BRAC_SetVolumeChangeCallBack(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置SDK Filter通信数据回调函数定义
BRAC_API DWORD BRAC_SetSDKFilterDataCallBack(BRAC_SDKFilterData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置录像快照任务完成通知回调函数
BRAC_API DWORD BRAC_SetRecordSnapShotCallBack(BRAC_RecordSnapShot_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置异步消息通知回调函数
BRAC_API DWORD BRAC_SetNotifyMessageCallBack(BRAC_NotifyMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置视频屏幕事件回调函数
BRAC_API DWORD BRAC_SetScreenEventCallBack(BRAC_VideoScreenEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置视频通话消息通知回调函数
BRAC_API DWORD BRAC_SetVideoCallEventCallBack(BRAC_VideoCallEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置数据加密、解密回调函数
BRAC_API DWORD BRAC_SetDataEncDecCallBack(BRAC_DataEncDec_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置回调函数句柄
BRAC_API DWORD BRAC_SetCallBack(DWORD dwCBType, LPVOID lpFunction, LPVOID lpUserValue=NULL);

// 连接服务器
BRAC_API DWORD BRAC_Connect(LPCTSTR lpServerAddr, DWORD dwPort);
// 登录系统
BRAC_API DWORD BRAC_Login(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType);
// 登录系统（扩展）
BRAC_API DWORD BRAC_LoginEx(LPCTSTR lpNickName, DWORD dwUserId, LPCTSTR lpStrUserId=NULL, LPCTSTR lpAppId=NULL, DWORD dwTimeStamp=0, LPCTSTR lpSigStr=NULL, LPCTSTR lpStrParam=NULL);
// 进入房间
BRAC_API DWORD BRAC_EnterRoom(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType);
// 进入房间
BRAC_API DWORD BRAC_EnterRoomEx(LPCTSTR lpRoomName, LPCTSTR lpRoomPass);
// 离开房间
BRAC_API DWORD BRAC_LeaveRoom(DWORD dwRoomid);
// 注销系统
BRAC_API DWORD BRAC_Logout(VOID);

// 释放所有资源
BRAC_API DWORD BRAC_Release(VOID);

// 获取当前房间在线用户列表（推荐使用：BRAC_GetRoomOnlineUsers）
BRAC_API DWORD BRAC_GetOnlineUser(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// 获取指定房间在线用户列表
BRAC_API DWORD BRAC_GetRoomOnlineUsers(DWORD dwRoomId, LPDWORD lpUserIDArray, DWORD& dwUserNum);
// 查询用户摄像头的状态
BRAC_API DWORD BRAC_GetCameraState(DWORD dwUserid, DWORD& dwState);
// 查询用户发言状态
BRAC_API DWORD BRAC_GetSpeakState(DWORD dwUserid, DWORD& dwState);
// 查询用户级别
BRAC_API DWORD BRAC_GetUserLevel(DWORD dwUserid, DWORD& dwLevel);
// 查询用户名称
BRAC_API DWORD BRAC_GetUserName(DWORD dwUserid, TCHAR* lpUserName, DWORD dwLen);
// 查询房间名称
BRAC_API DWORD BRAC_GetRoomName(DWORD dwRoomId, TCHAR* lpRoomName, DWORD dwLen);
// 显示本地视频画面调节对话框
BRAC_API DWORD BRAC_ShowLVProperty(HWND hParent, LPCTSTR szCaption=NULL, DWORD dwX=0, DWORD dwY=0);

// 查询指定用户相关状态
BRAC_API DWORD BRAC_QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);
// 查询指定房间相关状态
BRAC_API DWORD BRAC_QueryRoomState(DWORD dwRoomId, int infoname, char FAR* infoval, int infolen);

// 枚举本地视频采集设备
BRAC_API DWORD BRAC_EnumVideoCapture(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// 选择指定的视频采集设备
BRAC_API DWORD BRAC_SelectVideoCapture(LPCTSTR szCaptureName);
// 获取当前使用的视频采集设备
BRAC_API DWORD BRAC_GetCurVideoCapture(TCHAR* lpDeviceName, DWORD dwLen);
// 枚举本地音频采集设备
BRAC_API DWORD BRAC_EnumAudioCapture(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// 选择指定的音频采集设备
BRAC_API DWORD BRAC_SelectAudioCapture(LPCTSTR szCaptureName);
// 获取当前使用的音频采集设备
BRAC_API DWORD BRAC_GetCurAudioCapture(TCHAR* lpDeviceName, DWORD dwLen);
// 枚举本地音频播放设备
BRAC_API DWORD BRAC_EnumAudioPlayback(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// 选择指定的音频播放设备
BRAC_API DWORD BRAC_SelectAudioPlayback(LPCTSTR szDeviceName);
// 获取当前使用的音频播放设备
BRAC_API DWORD BRAC_GetCurAudioPlayback(TCHAR* lpDeviceName, DWORD dwLen);

// 操作用户视频
BRAC_API DWORD BRAC_UserCameraControl(DWORD dwUserid, BOOL bOpen);
// 操作用户视频（扩展）
BRAC_API DWORD BRAC_UserCameraControlEx(DWORD dwUserid, BOOL bOpen, DWORD dwStreamIndex=0, DWORD dwFlags=0, LPCTSTR lpStrParam=NULL);
// 操作用户语音
BRAC_API DWORD BRAC_UserSpeakControl(DWORD dwUserid, BOOL bOpen);
// 操作用户语音（扩展）
BRAC_API DWORD BRAC_UserSpeakControlEx(DWORD dwUserid, BOOL bOpen, DWORD dwStreamIndex=0, DWORD dwFlags=0, LPCTSTR lpStrParam=NULL);
// 设置视频显示位置
BRAC_API DWORD BRAC_SetVideoPos(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom);
// 设置视频显示位置（扩展）
BRAC_API DWORD BRAC_SetVideoPosEx(DWORD dwUserid, HWND hWnd, DWORD dwLeft=0, DWORD dwTop=0, DWORD dwRight=0, DWORD dwBottom=0, DWORD dwStreamIndex=0, DWORD dwFlags=0);
// 重绘指定用户的视频
BRAC_API DWORD BRAC_RepaintVideo(DWORD dwUserId, HDC hDC);
// 设置指定用户音视频流相关参数（主要针对本地用户）
BRAC_API DWORD BRAC_SetUserStreamInfo(DWORD dwUserId, DWORD dwStreamIndex, int infoname, char FAR* infoval, int infolen);
// 获取指定用户音视频流相关参数
BRAC_API DWORD BRAC_GetUserStreamInfo(DWORD dwUserId, DWORD dwStreamIndex, int infoname, char FAR* infoval, int infolen);


// 获取指定音频设备的当前音量
BRAC_API DWORD BRAC_AudioGetVolume(BRAC_AudioDevice device, DWORD& dwVolume);
// 设置指定音频设备的音量
BRAC_API DWORD BRAC_AudioSetVolume(BRAC_AudioDevice device, DWORD dwVolume);

// 用户音、视频录制（推荐使用API：BRAC_StreamRecordCtrlEx）
BRAC_API DWORD BRAC_StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam);
// 用户音、视频录制（扩展）
BRAC_API DWORD BRAC_StreamRecordCtrlEx(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr);
// 对用户的视频进行抓拍（快照）
BRAC_API DWORD BRAC_SnapShot(DWORD dwUserId, DWORD dwFlags, DWORD dwParam);

// 透明通道传送缓冲区
BRAC_API DWORD BRAC_TransBuffer(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
// 透明通道传送缓冲区扩展
BRAC_API DWORD BRAC_TransBufferEx(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// 传送文件
BRAC_API DWORD BRAC_TransFile(DWORD dwUserid, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// 查询传输任务相关信息
BRAC_API DWORD BRAC_QueryTransTaskInfo(DWORD dwUserid, DWORD dwTaskId, int infoname, char FAR* infoval, int infolen);
// 取消传输任务
BRAC_API DWORD BRAC_CancelTransTask(DWORD dwUserid, DWORD dwTaskId);

// 传送文件（扩展）
BRAC_API DWORD BRAC_TransFileEx(CHAR* lpTaskGuid, DWORD dwUserId, LPCTSTR lpLocalPathName, DWORD dwFlags, CHAR* lpUserString);
// 查询传输任务相关信息（扩展）
BRAC_API DWORD BRAC_QueryTransTaskInfoEx(CHAR* lpTaskGuid, int infoname, char FAR* infoval, int infolen);
// 取消传输任务（扩展）
BRAC_API DWORD BRAC_CancelTransTaskEx(CHAR* lpTaskGuid, DWORD dwFlags, DWORD dwErrorCode);

// 传送文本消息
BRAC_API DWORD BRAC_SendTextMessage(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
// 发送SDK Filter 通信数据
BRAC_API DWORD BRAC_SendSDKFilterData(LPBYTE lpBuf, DWORD dwLen);

// 更改当前的聊天模式
BRAC_API DWORD BRAC_ChangeChatMode(DWORD dwChatMode);
// 获取指定用户当前的聊天模式
BRAC_API DWORD BRAC_GetUserChatMode(DWORD dwUserid, DWORD& dwChatMode);
// 请求与对方私聊，向对方发起私聊请求
BRAC_API DWORD BRAC_PrivateChatRequest(DWORD dwUserid);
// 回复对方的私聊请求
BRAC_API DWORD BRAC_PrivateChatEcho(DWORD dwUserid, DWORD dwRequestid,BOOL bAccept);
// 回复对方的私聊请求（扩展，可以附带出错代码）
BRAC_API DWORD BRAC_PrivateChatEchoEx(DWORD dwUserid, DWORD dwRequestid,DWORD dwErrorCode);
// 退出与某用户的私聊，或者将某用户从自己的私聊列表中清除
BRAC_API DWORD BRAC_PrivateChatExit(DWORD dwUserid);

// SDK内核参数设置
BRAC_API DWORD BRAC_SetSDKOption(int optname, const char FAR* optval, int optlen);
// SDK内核参数状态查询
BRAC_API DWORD BRAC_GetSDKOption(int optname, char FAR* optval, int optlen);

// 组播功能控制
BRAC_API DWORD BRAC_MultiCastControl(LPCTSTR lpMultiCastAddr, DWORD dwPort, LPCTSTR lpNicAddr, DWORD dwTTL, DWORD dwFlags);

// 设置外部输入视频格式
BRAC_API DWORD BRAC_SetInputVideoFormat(BRAC_PixelFormat pixFmt, DWORD dwWidth, DWORD dwHeight, DWORD dwFps, DWORD dwFlags);
// 设置外部输入视频格式（扩展）
BRAC_API DWORD BRAC_SetInputVideoFormatEx(DWORD dwStreamIndex, DWORD dwCodecId, DWORD pixFmt, DWORD dwWidth, DWORD dwHeight, DWORD dwFps, DWORD dwFlags);
// 外部视频数据输入
BRAC_API DWORD BRAC_InputVideoData(LPBYTE lpVideoFrame, DWORD dwSize, DWORD dwTimeStamp);
// 外部视频数据输入（扩展）
BRAC_API DWORD BRAC_InputVideoDataEx(DWORD dwStreamIndex, LPBYTE lpVideoFrame, DWORD dwSize, DWORD dwTimeStamp, DWORD dwFlags);
// 设置外部输入音频格式
BRAC_API DWORD BRAC_SetInputAudioFormat(DWORD dwChannels, DWORD dwSamplesPerSec, DWORD dwBitsPerSample, DWORD dwFlags);
// 设置外部输入音频格式（扩展）
BRAC_API DWORD BRAC_SetInputAudioFormatEx(DWORD dwStreamIndex, DWORD dwCodecId, DWORD dwChannels, DWORD dwSamplesPerSec, DWORD dwBitsPerSample, DWORD dwFlags);
// 外部音频数据输入
BRAC_API DWORD BRAC_InputAudioData(LPBYTE lpSamples, DWORD dwSize, DWORD dwTimeStamp);
// 外部音频数据输入（扩展）
BRAC_API DWORD BRAC_InputAudioDataEx(DWORD dwStreamIndex, LPBYTE lpSamples, DWORD dwSize, DWORD dwTimeStamp, DWORD dwFlags);

// 获取音频播放数据
BRAC_API DWORD BRAC_FetchAudioPlayBuffer(LPBYTE lpSamples, DWORD dwSize, DWORD wParam);

// 向服务器动态查询相关信息
BRAC_API DWORD BRAC_QueryInfoFromServer(DWORD dwInfoName, TCHAR* lpInParam, DWORD dwInSize, TCHAR* lpResult, DWORD& dwOutSize, DWORD dwFlags=0);
// SDK控制
BRAC_API DWORD BRAC_SDKControl(DWORD dwCtrlCode, CHAR* lpInParam, CHAR* lpResult, DWORD dwBufSize);

// 视频呼叫事件控制（请求、回复、挂断等）
BRAC_API DWORD BRAC_VideoCallControl(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags=0, DWORD dwParam=0, LPCTSTR lpUserStr=NULL);

// 获取用户好友ID列表
BRAC_API DWORD BRAC_GetUserFriends(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// 获取好友在线状态
BRAC_API DWORD BRAC_GetFriendStatus(DWORD dwFriendUserId, DWORD& dwStatus);
// 获取用户分组ID列表
BRAC_API DWORD BRAC_GetUserGroups(LPDWORD lpGroupIDArray, DWORD& dwGroupNum);
// 获取分组下面的好友列表
BRAC_API DWORD BRAC_GetGroupFriends(DWORD dwGroupId, LPDWORD lpUserIDArray, DWORD& dwUserNum);
// 获取用户信息
BRAC_API DWORD BRAC_GetUserInfo(DWORD dwUserId, DWORD dwInfoId, TCHAR* lpInfoValue, DWORD dwLen);
// 获取用户分组名称
BRAC_API DWORD BRAC_GetGroupName(DWORD dwGroupId, TCHAR* lpGroupName, DWORD dwLen);
// 用户信息控制
BRAC_API DWORD BRAC_UserInfoControl(DWORD dwUserId, DWORD dwCtrlCode, DWORD wParam=0, DWORD lParam=0, LPCTSTR lpStrValue=NULL);

// 获取对象ID列表
BRAC_API DWORD BRAC_ObjectGetIdList(DWORD dwObjectType, LPDWORD lpIdArray, DWORD& dwIdNum);
// 获取对象属性值
BRAC_API DWORD BRAC_ObjectGetValue(DWORD dwObjectType, DWORD dwObjectId, DWORD dwInfoName, TCHAR* lpInfoValue, DWORD dwLen);
// 设置对象属性值
BRAC_API DWORD BRAC_ObjectSetValue(DWORD dwObjectType, DWORD dwObjectId, DWORD dwInfoName, TCHAR* lpInfoValue, DWORD dwLen);
// 对象参数控制
BRAC_API DWORD BRAC_ObjectControl(DWORD dwObjectType, DWORD dwObjectId, DWORD dwCtrlCode, DWORD dwParam1=0, DWORD dwParam2=0, DWORD dwParam3=0, DWORD dwParam4=0, LPCTSTR lpStrValue=NULL);

// 流媒体播放初始化
BRAC_API DWORD BRAC_StreamPlayInit(CHAR* lpTaskGuid, CHAR* lpStreamPath, DWORD dwFlags=0, CHAR* lpStrParam=NULL);
// 流媒体播放控制
BRAC_API DWORD BRAC_StreamPlayControl(CHAR* lpTaskGuid, DWORD dwCtrlCode, DWORD dwParam=0, DWORD dwFlags=0, CHAR* lpStrParam=NULL);
// 流媒体播放设置视频显示位置
BRAC_API DWORD BRAC_StreamPlaySetVideoPos(CHAR* lpTaskGuid, HWND hWnd, DWORD dwLeft=0, DWORD dwTop=0, DWORD dwRight=0, DWORD dwBottom=0);
// 流媒体播放获取参数信息
BRAC_API DWORD BRAC_StreamPlayGetInfo(CHAR* lpTaskGuid, DWORD dwInfoName, CHAR* infoValue, DWORD dwSize);
// 流媒体播放释放资源
BRAC_API DWORD BRAC_StreamPlayDestroy(CHAR* lpTaskGuid, DWORD dwFlags=0);


#endif //BR_ANYCHAT_CORE_SDK_H__INCLUDED_
