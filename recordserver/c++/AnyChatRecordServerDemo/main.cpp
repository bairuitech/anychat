#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "sdk/anychatrecordserversdk.h"

#if defined(WIN32)
#pragma comment(lib,"sdk/anychatrecordserversdk.lib")
#endif

using namespace std;

#if !defined(WIN32)
#define _snprintf	snprintf
#endif


void OutputLogStr(const char* str)
{
    fprintf(stdout, "%s\r\n", str);
}

// 服务器应用程序消息回调函数
void CALLBACK OnServerAppMessageCallBack(DWORD dwMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue)
{
	if(dwMsg == BRRS_SERVERAPPMSG_CONNECTED)
	{
		OutputLogStr("Success connected with anychatcoreserver...");
	}
	else if(dwMsg == BRRS_SERVERAPPMSG_DISCONNECT)
	{
		CHAR szString[100] = {0};
		_snprintf(szString, sizeof(szString), "ERROR: Disconnected from the anychatcoreserver, errorcode:%d", wParam);
		OutputLogStr(szString);
	}
	else
	{
		CHAR szString[100] = {0};
		_snprintf(szString, sizeof(szString), "OnServerAppMessageCallBack(dwMsg:%d, wParam:%d, lParam:%d)", dwMsg, wParam, lParam);
		OutputLogStr(szString);
	}
}

// 开始录像事件回调函数
DWORD CALLBACK OnRecordStartCallBack(DWORD dwUserId, LPVOID lpUserValue)
{
	CHAR szNickName[100] = {0};
	BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_NICKNAME, szNickName, sizeof(szNickName));

	CHAR szString[100] = {0};
	_snprintf(szString, sizeof(szString), "OnAnyChatRecordStartCallBack(dwUserId:%d, szNickName:%s)", dwUserId, szNickName);
	OutputLogStr(szString);

	// 判断是否有视频流信息
	int videocodec = 0;
	BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_VCODEC, (CHAR*)&videocodec, sizeof(DWORD));
	if(videocodec != 0) {
		// videoCodec=1，H.264编码
		int width, height, fps;
		BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_WIDTH, (CHAR*)&width, sizeof(DWORD));
		BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_HEIGHT, (CHAR*)&height, sizeof(DWORD));
		BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_FRAMERATE, (CHAR*)&fps, sizeof(DWORD));

		_snprintf(szString, sizeof(szString), "\tvideo info: codec=%s, wxh=%dx%d, fps=%d", videocodec==1 ? "H264" : "Unknow Codec", width, height, fps);
		OutputLogStr(szString);
	}

	// 判断是否有音频流信息
	int audioCodec = 0;
	BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_ACODEC, (CHAR*)&audioCodec, sizeof(DWORD));
	if(audioCodec != 0) {
		// audioCodec=11，AMR_WB编码
		int samplerate, channels, samplebits;
		BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_SAMPLERATE, (CHAR*)&samplerate, sizeof(DWORD));
		BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_CHANNELS, (CHAR*)&channels, sizeof(DWORD));
		BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_SAMPLEBITS, (CHAR*)&samplebits, sizeof(DWORD));

		_snprintf(szString, sizeof(szString), "\taudio info: codec=%s, samplerate=%d, channels=%d, samplebits=%d", audioCodec==11 ? "AMR_WB" : "Unknow Codec", samplerate, channels, samplebits);
		OutputLogStr(szString);
	}
	return 0;
}

/**
 *	录像数据事件回调函数
 *	上层应用可根据需要将数据写入文件中
 */
DWORD CALLBACK OnRecordBufferCallBack(DWORD dwUserId, CHAR* lpBuf, DWORD dwSize, DWORD dwTimeStamp, DWORD dwFlags, LPVOID lpUserValue)
{
	if((dwFlags & BRRS_RECORD_FLAGS_VIDEO) != 0)
	{
		// 视频流编码数据
		CHAR szString[200] = {0};
		_snprintf(szString, sizeof(szString), "OnAnyChatRecordBufferCallBack(dwUserId:%d, video, bKeyFrame:%d, size:%d, timestamp:%d)", dwUserId, !!(dwFlags & BRRS_RECORD_FLAGS_KEYFRAME), dwSize, dwTimeStamp);
		OutputLogStr(szString);
	}
	else if((dwFlags & BRRS_RECORD_FLAGS_AUDIO) != 0)
	{
		// 音频流编码数据
		CHAR szString[200] = {0};
		_snprintf(szString, sizeof(szString), "OnAnyChatRecordBufferCallBack(dwUserId:%d, audio, bSilence:%d, size:%d, timestamp:%d)", dwUserId, !!(dwFlags & BRRS_RECORD_FLAGS_SILENCE), dwSize, dwTimeStamp);
		OutputLogStr(szString);
	}
	else if((dwFlags & BRRS_RECORD_FLAGS_BUFFER) != 0)
	{
		// 数据流数据（业务服务器调用API：TransBuffer2RecordServer发送）
		CHAR szString[200] = {0};
		_snprintf(szString, sizeof(szString), "OnAnyChatRecordBufferCallBack(dwUserId:%d, buffer, size:%d, timestamp:%d)", dwUserId, dwSize, dwTimeStamp);
		OutputLogStr(szString);
	}
	return 0;
}

// 结束录像事件回调函数
DWORD CALLBACK OnRecordFinishCallBack(DWORD dwUserId, CHAR* lpFileName, DWORD dwSize, DWORD* lpRecordSeconds, LPVOID lpUserValue)
{
	CHAR szNickName[100] = {0};
	BRRS_QueryUserInfo(dwUserId, BRRS_USERINFO_TYPE_NICKNAME, szNickName, sizeof(szNickName));
	// 关闭录像文件
	// ......

	// 录像结束后，必须返回录像文件名、录像时长参数，AnyChat内核会通知给业务服务器
	_snprintf(lpFileName, dwSize, "d:\\record\\%s_%d.record", szNickName, rand());		// 模拟一个文件名
	*lpRecordSeconds = 10;

	CHAR szString[100] = {0};
	_snprintf(szString, sizeof(szString), "OnRecordFinishCallBack(dwUserId:%d)", dwUserId);
	OutputLogStr(szString);
	return 0;
}

int main()
{
	// 获取SDK的版本信息
	DWORD dwMainVer;
	DWORD dwSubVer;
	CHAR szCompileTime[100] = {0};
	BRRS_GetSDKVersion(dwMainVer, dwSubVer, szCompileTime, sizeof(szCompileTime));
	CHAR strVersion[100] = {0};
	_snprintf(strVersion, sizeof(strVersion), "AnyChat Record Server SDK V%d.%d(Build time:%s)",dwMainVer,dwSubVer,szCompileTime);
	OutputLogStr(strVersion);

	// 设置服务器应用程序消息回调函数
	BRRS_SetOnServerAppMessageCallBack(OnServerAppMessageCallBack, NULL);
	// 设置开始录像事件回调函数
	BRRS_SetOnRecordStartCallBack(OnRecordStartCallBack, NULL);
	// 设置录像数据事件回调函数
	BRRS_SetOnRecordBufferCallBack(OnRecordBufferCallBack, NULL);
	// 设置录像完成事件回调函数
	BRRS_SetOnRecordFinishCallBack(OnRecordFinishCallBack, NULL);

	BRRS_InitSDK(0);

    while(TRUE)
    {
        fprintf(stdout, "Press 'q' to exit!\r\n");
        if(getchar() == 'q')
            break;
    }
    BRRS_Release();
    return 0;
}
