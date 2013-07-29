// SDKFilterPlus.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>


#define BRFP_API extern "C" __declspec(dllexport)

#define BRFP_VERSION	"2.0"

// SDK Filter Plus 数据传输回调函数定义（服务器会将缓冲区内的数据传输给指定的用户）
typedef void (CALLBACK * BRFP_FilterDataCallBack)(DWORD dwUserId, DWORD dwHandle, LPCSTR lpBuf, DWORD dwLen, LPVOID lpUserValue);

BRFP_FilterDataCallBack	g_fnSendFilterData = NULL;
LPVOID	g_lpFilterUserData = NULL;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

/**
 *	获取SDK插件版本信息
 *	@param lpVersion 返回插件的版本信息
 *	@param dwVSLen 版本信息缓冲区长度
 */
BRFP_API void BRFP_GetVersion(OUT LPTSTR lpVersion,IN DWORD dwVSLen)
{
#if(_MFC_VER >= 0x0700)
	_snprintf_s(lpVersion,dwVSLen,_TRUNCATE,"%s",BRFP_VERSION);
#else
	_snprintf(lpVersion,dwVSLen,"%s",BRFP_VERSION);
#endif
}


/**
 *	初始化SDK Filter
 *	可以在该方法中读取相关的配置参数，建立数据库连接等初始化工作
 *	@param lpFunc 回调函数地址，SDK Filter有数据需要发送时，则通过该回调函数传递给应用层
 *	@param lpUserValue 回调函数附带参数
 *	@return 初始化成功返回TRUE，否则返回FALSE
 */
BRFP_API BOOL BRFP_InitFilter(BRFP_FilterDataCallBack lpFunc, LPVOID lpUserValue)
{
	g_fnSendFilterData = lpFunc;
	g_lpFilterUserData = lpUserValue;
	return TRUE;
}

/**
 *	验证用户身份
 *	@param lpUserName 输入用户名
 *	@param lpPassword 输入用户密码
 *	@param lpUserID 输出该用户的ID号（注意：该ID号必须唯一，不能重复）
 *	@param lpUserLevel 输出该用户的级别
 *	@param lpNickName 输出该用户的昵称
 *	@param dwNCLen 保存用户昵称缓冲区的长度
 *	@return 返回出错码，成功返回 GV_ERR_SUCCESS，否则返回对应的错误代码
 */
BRFP_API DWORD BRFP_VerifyUser(IN LPCTSTR lpUserName,IN LPCTSTR lpPassword, OUT LPDWORD lpUserID, OUT LPDWORD lpUserLevel, OUT LPTSTR lpNickName,IN DWORD dwNCLen)
{
	static DWORD dwUserIdSeed = 0;
	DWORD dwCurrentId = ++dwUserIdSeed;
	*lpUserID = dwCurrentId;
	*lpUserLevel = 0;
	
#if(_MFC_VER >= 0x0700)
	_snprintf_s(lpNickName,dwNCLen,_TRUNCATE,"DemoUser_%d",dwCurrentId);
#else
	_snprintf(lpNickName,dwNCLen,"DemoUser_%d",dwCurrentId);
#endif

	return 0;
}

/**
 *	用户进入房间请求
 *	SDK Filter需要判断该请求的合法性，服务器根据返回值决定是否让用户进入房间
 *	当客户端调用BRAC_EnterRoom（根据房间ID进入房间）进入房间时，dwRoomId与lpPassword参数有效
 *	当客户端调用BRAC_EnterRoomEx（根据房间名进入房间）进入房间时，lpRoomName与lpPassword参数有效，些时的dwRoomId是由服务器自动分配的
 *	@param dwUserId 请求者用户ID
 *	@param dwRoomId 请求进入的房间编号
 *	@param lpRoomName 请求进入的房间名
 *	@param lpPassword 房间密码
 *	@return  返回出错码，成功（允许进入房间）返回GV_ERR_SUCCESS，否则返回对应的错误代码
 */
BRFP_API DWORD BRFP_PrepareEnterRoom(DWORD dwUserId, DWORD dwRoomId, LPCTSTR lpRoomName,LPCTSTR lpPassword)
{
	return 0;
}


/**
 *	用户登录动作
 *	用户登录系统成功之后，服务器会调用该方法，通知SDK Filter有用户登录
 */
BRFP_API void BRFP_OnUserLoginAction(DWORD dwUserId, LPCTSTR szUserName, DWORD dwLevel, LPCTSTR szIpAddr, DWORD dwHandle)
{
	// 这儿需要保存dwUserId与dwHandle的对应关系，因为向用户发送数据（使用回调函数句柄）时需要传入该参数


	// 作为演示，当用户登录时，发送一条欢迎信息给用户
	CHAR szWelcomeMsg[] = "Welcome to use BaiRuiTech products!";
	if(g_fnSendFilterData)
		g_fnSendFilterData(dwUserId,dwHandle,szWelcomeMsg,strlen(szWelcomeMsg),g_lpFilterUserData);
}


/**
 *	用户注销动作
 *	用户从系统注销，或是网络断开之时，服务器会调用该方法，通知SDK Filter有用户离开系统
 */
BRFP_API void BRFP_OnUserLogoutAction(DWORD dwUserId)
{

}


/**
 *	用户进入房间动作
 *	用户进入房间成功之后，服务器会调用该方法，通知SDK Filter有用户进入房间
 */
BRFP_API void BRFP_OnUserEnterRoomAction(DWORD dwUserId, DWORD dwRoomId)
{

}


/**
 *	用户离开房间动作
 *	用户从房间离开之时，服务器会调用该方法，通知SDK Filter有用户离开房间
 */
BRFP_API void BRFP_OnUserLeaveRoomAction(DWORD dwUserId, DWORD dwRoomId)
{

}


/**
 *	收到用户发送过来的通信数据包
 */
BRFP_API void BRFP_OnRecvUserFilterData(DWORD dwUserId, LPCSTR lpBuf, DWORD dwLen)
{

}
/**
 *	收到用户文字聊天通信数据
 */
BRFP_API void BRFP_OnRecvUserTextMsg(DWORD dwRoomId, DWORD dwSrcUserId, DWORD dwTarUserId, BOOL bSecret, LPCTSTR lpTextMessage, DWORD dwLen)
{

}


/**
 *	释放SDK Filter资源
 *	在服务器退出时调用
 */
BRFP_API void BRFP_ReleaseFilter(void)
{
	g_fnSendFilterData = NULL;
	g_lpFilterUserData = NULL;
}
