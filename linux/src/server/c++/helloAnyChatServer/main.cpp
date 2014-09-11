#include <iostream>
#include "anychatserversdk.h"


using namespace std;


void OutputLogStr(const char* str)
{
    fprintf(stdout, "%s\r\n", str);
}

DWORD g_dwOnlineUsers = 0;

// 服务器应用程序消息（扩展）回调函数定义
void CALLBACK OnServerAppMessageExCallBack(DWORD dwNotifyMessage, DWORD wParam, DWORD lParam, LPVOID lpUserValue)
{
    	if(dwNotifyMessage == BRAS_MESSAGE_CORESERVERCONN)
	{
		g_dwOnlineUsers = 0;
		if(wParam == 0)
			OutputLogStr("Success connected with AnyChatCoreServer...");
		else
			OutputLogStr("Disconnected from the AnyChatCoreServer");
	}
	else if(dwNotifyMessage == BRAS_MESSAGE_RECORDSERVERCONN)
	{
		if(wParam == 0)
		{
			CHAR szMessage[100] = {0};
			snprintf(szMessage, sizeof(szMessage), "Success connected with AnyChatRecordServer...(serverid:%d)", lParam);
			OutputLogStr(szMessage);
		}
		else
		{
			CHAR szMessage[100] = {0};
			snprintf(szMessage, sizeof(szMessage), "Disconnected from the AnyChatRecordServer...(errorcode:%d, serverid:%d)", wParam, lParam);
			OutputLogStr(szMessage);
		}
	}
	else
	{
		CHAR szMessage[100] = {0};
		snprintf(szMessage, sizeof(szMessage), "OnServerAppMessageExCallBack(dwNotifyMessage:%d, wParam:%d, lParam:%d)", dwNotifyMessage, wParam, lParam);
		OutputLogStr(szMessage);
	}
}

/**
 *	SDK定时器回调函数定义，上层应用可以在该回调中处理定时任务，而不需要额外开启线程，或是定时器
 *	如果单独开启线程，或是注册Windows定时器，则必须考虑多线程同步的问题
 *	而使用SDK的TimerEvent回调，则不需要考虑，因为定时器回调和别的回调函数均是顺序触发的
 */
void CALLBACK OnTimerEventCallBack(LPVOID lpUserValue)
{
//		OutputLogStr("定时器事件");
}

/**
 *	用户身份验证回调函数定义
 *	@param lpUserName	客户端调用API：BRAC_Login所传入的username参数
 *	@param lpPassword	客户端调用API：BRAC_Login所传入的password参数
 *	@param lpUserId		保存用户ID的地址
 *	@return 通过身份验证返回0，否则返回errorcode，表示验证失败
 */
DWORD CALLBACK VerifyUserCallBack(LPCTSTR lpUserName, LPCTSTR lpPassword, LPDWORD lpUserID, LPDWORD lpUserLevel, LPTSTR lpNickName, DWORD dwNCLen, LPVOID lpUserValue)
{
	static DWORD dwUserIdSeed = 1;
	// 将服务器分配的userid返回给客户端，示例代码为了简洁，采用递增的方式来分配UserId
	// 实际应用时可以通过数据库，根据username、password等信息返回一个固定的userid
	*lpUserID = dwUserIdSeed++;

    CHAR szMessage[100] = {0};
	snprintf(szMessage, sizeof(szMessage), "VerifyUser(%s - %s) --> userid(%d)",lpUserName,lpPassword,(int)*lpUserID);
	OutputLogStr(szMessage);

	return 0;
}
// 用户申请进入房间回调函数定义
DWORD CALLBACK PrepareEnterRoomCallBack(DWORD dwUserId, DWORD dwRoomId, LPCTSTR lpRoomName,LPCTSTR lpPassword, LPVOID lpUserValue)
{
	CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "PrepareEnterRoom(dwUserId:%d - dwRoomId:%d)",(int)dwUserId,(int)dwRoomId);
	OutputLogStr(szMessage);
	return 0;
}
// 用户登录成功回调函数定义
void CALLBACK OnUserLoginActionCallBack(DWORD dwUserId, LPCTSTR szUserName, DWORD dwLevel, LPCTSTR szIpAddr, LPVOID lpUserValue)
{
    g_dwOnlineUsers++;
    CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnUserLoginAction(dwUserId:%d - Name:%s)",(int)dwUserId, szUserName);
    OutputLogStr(szMessage);
}

// 用户注销扩展回调函数定义（增加注销的错误代码）
void CALLBACK OnUserLogoutActionExCallBack(DWORD dwUserId, DWORD dwErrorCode, LPVOID lpUserValue)
{
    g_dwOnlineUsers--;
    CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnUserLogoutAction(dwUserId:%d, dwErrorCode:%d)",(int)dwUserId, dwErrorCode);
    OutputLogStr(szMessage);
}

// 用户进入房间回调函数定义
void CALLBACK OnUserEnterRoomActionCallBack(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue)
{
    CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnUserEnterRoomAction(dwUserId:%d - dwRoomId:%d)",(int)dwUserId,(int)dwRoomId);
    OutputLogStr(szMessage);
}
// 用户离开房间回调函数定义
void CALLBACK OnUserLeaveRoomActionCallBack(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue)
{
    CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnUserLeaveRoomAction(dwUserId:%d - dwRoomId:%d)",(int)dwUserId,(int)dwRoomId);
    OutputLogStr(szMessage);
}
// 上层业务自定义数据回调函数定义
void CALLBACK OnRecvUserFilterDataCallBack(DWORD dwUserId, BYTE* lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
    CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnRecvUserFilterData(dwUserId:%d - Buf:%s)",(int)dwUserId,lpBuf);
    OutputLogStr(szMessage);
}

// 收到用户文字聊天通信数据回调函数定义
void CALLBACK OnRecvUserTextMsgCallBack(DWORD dwRoomId, DWORD dwSrcUserId, DWORD dwTarUserId, BOOL bSecret, LPCTSTR lpTextMessage, DWORD dwLen, LPVOID lpUserValue)
{
    CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnRecvUserTextMsg(dwRoomId:%d, dwSrcUserId:%d, dwTarUserId:%d - Buf:%s)",(int)dwRoomId,(int)dwSrcUserId,(int)dwTarUserId,lpTextMessage);
    OutputLogStr(szMessage);
}

// 透明通道数据回调函数定义
void CALLBACK OnTransBufferCallBack(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
    CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnTransBufferCallBack(dwUserId:%d - BufLen:%d)",(int)dwUserId,dwLen);
    OutputLogStr(szMessage);
}

// 透明通道数据扩展回调函数定义
void CALLBACK OnTransBufferExCallBack(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
    CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnTransBufferExCallBack(dwUserId:%d - BufLen:%d - wParam:%d - lParam:%d - dwTaskId:%d)",(int)dwUserId,dwLen, wParam, lParam, dwTaskId);
    OutputLogStr(szMessage);
}
// 文件传输回调函数定义
void CALLBACK OnTransFileCallBack(DWORD dwUserId, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
    CHAR szMessage[100] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnTransFileCallBack(dwUserId:%d, PathName:%s - wParam:%d - lParam:%d - dwTaskId:%d)",(int)dwUserId, lpFileName, wParam, lParam, dwTaskId);
    OutputLogStr(szMessage);
}

// 服务器录像回调函数定义
void CALLBACK OnServerRecordCallBack(DWORD dwUserId, DWORD dwParam, DWORD dwRecordServerId, DWORD dwElapse, LPCTSTR lpRecordFileName, LPVOID lpUserValue)
{
    CHAR szMessage[1024] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnServerRecordCallBack(dwUserId:%d, dwParam:%d, dwElapse:%d, FileName:%s)",(int)dwUserId, dwParam, dwElapse, lpRecordFileName);
    OutputLogStr(szMessage);
}
// 视频通话消息通知回调函数定义
DWORD CALLBACK OnVideoCallEventCallBack(DWORD dwEventType, DWORD dwSrcUserId, DWORD dwTarUserId, DWORD dwErrorCode, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue)
{
    CHAR szMessage[1024] = {0};
    snprintf(szMessage, sizeof(szMessage), "OnVideoCallEventCallBack(dwEventType:%d, dwSrcUserId:%d, dwTarUserId:%d, dwErrorCode:%d, dwFlags:%d, dwParam:%d, lpUserStr:%s)",
              dwEventType, (int)dwSrcUserId, (int)dwTarUserId, dwErrorCode, dwFlags, dwParam, lpUserStr);
    OutputLogStr(szMessage);
    return 0;
}


int main()
{
    // 获取SDK的版本信息
	DWORD dwMainVer,dwSubVer;
	CHAR szCompileTime[100] = {0};
	BRAS_GetSDKVersion(dwMainVer,dwSubVer,szCompileTime,sizeof(szCompileTime));
	CHAR strVersion[100] = {0};
	snprintf(strVersion, sizeof(strVersion), "AnyChat Server SDK V%d.%d(Build time:%s)",dwMainVer,dwSubVer,szCompileTime);
	OutputLogStr(strVersion);

    // 设置服务器应用程序消息（扩展）回调函数
    BRAS_SetOnServerAppMessageExCallBack(OnServerAppMessageExCallBack, NULL);
	// 设置SDK定时器回调函数
	BRAS_SetTimerEventCallBack(1000,OnTimerEventCallBack,NULL);
	// 设置用户身份验证回调函数
	BRAS_SetVerifyUserCallBack(VerifyUserCallBack,NULL);
	// 设置用户申请进入房间回调函数
	BRAS_SetPrepareEnterRoomCallBack(PrepareEnterRoomCallBack, NULL);
	// 设置用户登录成功回调函数
	BRAS_SetOnUserLoginActionCallBack(OnUserLoginActionCallBack, NULL);
	// 设置用户注销扩展回调函数
    BRAS_SetOnUserLogoutActionExCallBack(OnUserLogoutActionExCallBack, NULL);
	// 设置用户进入房间回调函数
	BRAS_SetOnUserEnterRoomActionCallBack(OnUserEnterRoomActionCallBack, NULL);
	// 设置用户离开房间回调函数
	BRAS_SetOnUserLeaveRoomActionCallBack(OnUserLeaveRoomActionCallBack, NULL);
	// 设置用户上层业务自定义数据回调函数
	BRAS_SetOnRecvUserFilterDataCallBack(OnRecvUserFilterDataCallBack, NULL);
	// 用户文字聊天通信数据回调函数
	BRAS_SetOnRecvUserTextMsgCallBack(OnRecvUserTextMsgCallBack,NULL);
	// 设置透明通道数据回调函数
	BRAS_SetOnTransBufferCallBack(OnTransBufferCallBack, NULL);
	// 设置透明通道数据扩展回调函数
	BRAS_SetOnTransBufferExCallBack(OnTransBufferExCallBack, NULL);
	// 设置文件传输回调函数
	BRAS_SetOnTransFileCallBack(OnTransFileCallBack, NULL);
	// 设置服务器录像通知回调函数
    BRAS_SetOnServerRecordCallBack(OnServerRecordCallBack, NULL);
    // 设置视频通话消息通知回调函数
    BRAS_SetOnVideoCallEventCallBack(OnVideoCallEventCallBack, NULL);

	BRAS_InitSDK(0);


    while(TRUE)
    {
        fprintf(stdout, "Total online users:%d, Press 'q' to exit!\r\n", g_dwOnlineUsers);
        if(getchar() == 'q')
            break;
        usleep(100*1000);
    }
    BRAS_Release();
    return 0;
}

