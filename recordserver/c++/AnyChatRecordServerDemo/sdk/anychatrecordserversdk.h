#if !defined(BR_ANYCHAT_RECORDSERVER_SDK_H__INCLUDED_)
#define BR_ANYCHAT_RECORDSERVER_SDK_H__INCLUDED_

#include "typedef.h"

/**
 *	AnyChat Record Server SDK Include File
 */


#pragma once


#define BRRS_API extern "C"

#define BRRS_SERVERAPPMSG_CONNECTED		1		///< 连接AnyChat服务器成功
#define BRRS_SERVERAPPMSG_DISCONNECT	2		///< 与AnyChat服务器断开连接

// 查询信息类型定义（API：BRRS_QueryUserInfo 传入参数）
#define BRRS_USERINFO_TYPE_NICKNAME		1		///< 用户名
#define BRRS_USERINFO_TYPE_VCODEC		10		///< 视频编码器
#define BRRS_USERINFO_TYPE_WIDTH		11		///< 视频宽度
#define BRRS_USERINFO_TYPE_HEIGHT		12		///< 视频高度
#define BRRS_USERINFO_TYPE_FRAMERATE	13		///< 视频帧率
#define BRRS_USERINFO_TYPE_ACODEC		20		///< 音频编码器
#define BRRS_USERINFO_TYPE_SAMPLERATE	21		///< 音频采样率
#define BRRS_USERINFO_TYPE_CHANNELS		22		///< 音频采样通道数
#define BRRS_USERINFO_TYPE_SAMPLEBITS	23		///< 音频采样位数

// 参数设置类型定义（API：BRRS_SetSDKOption 传入参数）
#define BRRS_SO_USESERVERTIMESTAMP		1		///< 使用服务器时间戳

// 数据类型标志（回调函数：OnAnyChatRecordBufferCallBack 参数）
#define BRRS_RECORD_FLAGS_AUDIO			0x01	///< 音频数据
#define BRRS_RECORD_FLAGS_VIDEO			0x02	///< 音频数据
#define BRRS_RECORD_FLAGS_BUFFER		0x04	///< 透明通道缓冲区数据
#define BRRS_RECORD_FLAGS_BUFFEREX		0x08	///< 透明通道扩展缓冲区
#define BRRS_RECORD_FLAGS_KEYFRAME		0x10	///< 视频关键帧
#define BRRS_RECORD_FLAGS_SILENCE		0x20	///< 音频静音帧


// 服务器应用程序消息回调函数定义
typedef void (CALLBACK* BRRS_OnServerAppMessage_CallBack)(DWORD dwMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
// 开始录像事件回调函数定义
typedef DWORD (CALLBACK* BRRS_OnRecordStart_CallBack)(DWORD dwUserId, LPVOID lpUserValue);
// 录像数据事件回调函数定义
typedef DWORD (CALLBACK* BRRS_OnRecordBuffer_CallBack)(DWORD dwUserId, CHAR* lpBuf, DWORD dwSize, DWORD dwTimeStamp, DWORD dwFlags, LPVOID lpUserValue);
// 结束录像事件回调函数定义
typedef DWORD (CALLBACK* BRRS_OnRecordFinish_CallBack)(DWORD dwUserId, CHAR* lpFileName, DWORD dwSize, DWORD* lpRecordSeconds, LPVOID lpUserValue);

/**
 *	API 方法定义
 */
// 设置服务器应用程序消息回调函数
BRRS_API DWORD BRRS_SetOnServerAppMessageCallBack(BRRS_OnServerAppMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置开始录像事件回调函数
BRRS_API DWORD BRRS_SetOnRecordStartCallBack(BRRS_OnRecordStart_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置录像数据事件回调函数
BRRS_API DWORD BRRS_SetOnRecordBufferCallBack(BRRS_OnRecordBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置录像完成事件回调函数
BRRS_API DWORD BRRS_SetOnRecordFinishCallBack(BRRS_OnRecordFinish_CallBack lpFunction, LPVOID lpUserValue=NULL);

// 获取SDK版本信息
BRRS_API DWORD BRRS_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, TCHAR* lpCompileTime, DWORD dwBufLen);
// 初始化SDK
BRRS_API DWORD BRRS_InitSDK(DWORD dwReserved);
// 释放资源
BRRS_API DWORD BRRS_Release(void);


// 查询用户信息
BRRS_API DWORD BRRS_QueryUserInfo(DWORD dwUserId, DWORD dwInfoName, CHAR* lpValue, DWORD dwSize);
// SDK内核参数设置
BRRS_API DWORD BRRS_SetSDKOption(DWORD optname, CHAR* optval, DWORD optlen);




#endif //BR_ANYCHAT_RECORDSERVER_SDK_H__INCLUDED_
