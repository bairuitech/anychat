#ifndef ANYCHATCORESDK_H
#define ANYCHATCORESDK_H

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "BRAnyChatCoreSDK.h"

// 初始化系统
BRAC_API DWORD BRAC_InitSDK(HWND hWnd, DWORD dwFuncMode);
typedef DWORD (_cdecl * BRAC_InitSDK_Func)(HWND hWnd, DWORD dwFuncMode);

// 获取SDK版本信息
BRAC_API DWORD BRAC_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, LPSTR lpCompileTime, DWORD dwBufLen);
typedef DWORD(_cdecl * BRAC_GetSDKVersion_Func)(DWORD& dwMainVer, DWORD& dwSubVer, LPSTR lpCompileTime, DWORD dwBufLen);

// 激活（关闭）SDK调用日志
BRAC_API DWORD BRAC_ActiveCallLog(BOOL bActive);
typedef DWORD(_cdecl * BRAC_ActiveCallLog_Func)(BOOL bActive);

// SDK内核参数设置
BRAC_API DWORD BRAC_SetSDKOption(int optname, const char FAR* optval, int optlen);
typedef DWORD(_cdecl * BRAC_SetSDKOption_Func)(int optname, const char FAR* optval, int optlen);

// 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
BRAC_API DWORD BRAC_SetServerAuthPass(LPCTSTR lpPassword);
typedef DWORD(_cdecl * BRAC_SetServerAuthPass_Func)(LPCTSTR lpPassword);


// 设置视频数据回调函数
BRAC_API DWORD BRAC_SetVideoDataCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetVideoDataCallBack_Func)(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue);
// 设置音频数据回调函数
BRAC_API DWORD BRAC_SetAudioDataCallBack(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetAudioDataCallBack_Func)(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue);
// 设置音量变化回调函数
BRAC_API DWORD BRAC_SetVolumeChangeCallBack(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetVolumeChangeCallBack_Func)(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue);
// 设置透明通道数据扩展回调函数
BRAC_API DWORD BRAC_SetTransBufferExCallBack(BRAC_TransBufferEx_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetTransBufferExCallBack_Func)(BRAC_TransBufferEx_CallBack lpFunction, LPVOID lpUserValue);
// 设置透明通道数据回调函数
BRAC_API DWORD BRAC_SetTransBufferCallBack(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetTransBufferCallBack_Func)(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue);
// 设置文件传输回调函数
BRAC_API DWORD BRAC_SetTransFileCallBack(BRAC_TransFile_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetTransFileCallBack_Func)(BRAC_TransFile_CallBack lpFunction, LPVOID lpUserValue);
// 设置录像快照任务完成通知回调函数
BRAC_API DWORD BRAC_SetRecordSnapShotCallBack(BRAC_RecordSnapShot_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetRecordSnapShotCallBack_Func)(BRAC_RecordSnapShot_CallBack lpFunction, LPVOID lpUserValue);
// 设置SDK Filter通信数据回调函数定义
BRAC_API DWORD BRAC_SetSDKFilterDataCallBack(BRAC_SDKFilterData_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetSDKFilterDataCallBack_Func)(BRAC_SDKFilterData_CallBack lpFunction, LPVOID lpUserValue);
// 设置异步消息通知回调函数
BRAC_API DWORD BRAC_SetNotifyMessageCallBack(BRAC_NotifyMessage_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetNotifyMessageCallBack_Func)(BRAC_NotifyMessage_CallBack lpFunction, LPVOID lpUserValue);
// 设置文字消息回调函数
BRAC_API DWORD BRAC_SetTextMessageCallBack(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue);
typedef DWORD(_cdecl * BRAC_SetTextMessageCallBack_Func)(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue);




// 连接服务器
BRAC_API DWORD BRAC_Connect(LPCTSTR lpServerAddr, DWORD dwPort);
typedef DWORD(_cdecl * BRAC_Connect_Func)(LPCTSTR lpServerAddr, DWORD dwPort);
// 登录系统
BRAC_API DWORD BRAC_Login(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType);
typedef DWORD(_cdecl * BRAC_Login_Func)(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType);
// 进入房间
BRAC_API DWORD BRAC_EnterRoom(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType);
typedef DWORD(_cdecl * BRAC_EnterRoom_Func)(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType);
// 进入房间
BRAC_API DWORD BRAC_EnterRoomEx(LPCTSTR lpRoomName, LPCTSTR lpRoomPass);
typedef DWORD(_cdecl * BRAC_EnterRoomEx_Func)(LPCTSTR lpRoomName, LPCTSTR lpRoomPass);
// 离开房间
BRAC_API DWORD BRAC_LeaveRoom(DWORD dwRoomid);
typedef DWORD(_cdecl * BRAC_LeaveRoom_Func)(DWORD dwRoomid);
// 注销系统
BRAC_API DWORD BRAC_Logout(VOID);
typedef DWORD(_cdecl * BRAC_Logout_Func)(VOID);


// 操作用户视频
BRAC_API DWORD BRAC_UserCameraControl(DWORD dwUserid, BOOL bOpen);
typedef DWORD(_cdecl * BRAC_UserCameraControl_Func)(DWORD dwUserid, BOOL bOpen);
// 操作用户语音
BRAC_API DWORD BRAC_UserSpeakControl(DWORD dwUserid, BOOL bOpen);
typedef DWORD(_cdecl * BRAC_UserSpeakControl_Func)(DWORD dwUserid, BOOL bOpen);
// 设置视频显示位置
BRAC_API DWORD BRAC_SetVideoPos(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom);
typedef DWORD(_cdecl * BRAC_SetVideoPos_Func)(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom);
// 获取指定音频设备的当前音量
BRAC_API DWORD BRAC_AudioGetVolume(BRAC_AudioDevice device, DWORD& dwVolume);
typedef DWORD(_cdecl * BRAC_AudioGetVolume_Func)(BRAC_AudioDevice device, DWORD& dwVolume);
// 设置指定音频设备的音量
BRAC_API DWORD BRAC_AudioSetVolume(BRAC_AudioDevice device, DWORD dwVolume);
typedef DWORD(_cdecl * BRAC_AudioSetVolume_Func)(BRAC_AudioDevice device, DWORD dwVolume);

// 获取当前房间在线用户列表
BRAC_API DWORD BRAC_GetOnlineUser(LPDWORD lpUserIDArray, DWORD& dwUserNum);
typedef DWORD(_cdecl * BRAC_GetOnlineUser_Func)(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// 查询用户摄像头的状态
BRAC_API DWORD BRAC_GetCameraState(DWORD dwUserid, DWORD& dwState);
typedef DWORD(_cdecl * BRAC_GetCameraState_Func)(DWORD dwUserid, DWORD& dwState);
// 查询用户名称
BRAC_API DWORD BRAC_GetUserName(DWORD dwUserid, CHAR* lpUserName, DWORD dwLen);
typedef DWORD(_cdecl * BRAC_GetUserName_Func)(DWORD dwUserid, CHAR* lpUserName, DWORD dwLen);
// 查询房间名称
BRAC_API DWORD BRAC_GetRoomName(DWORD dwRoomId, CHAR* lpRoomName, DWORD dwLen);
typedef DWORD(_cdecl * BRAC_GetRoomName_Func)(DWORD dwRoomId, CHAR* lpRoomName, DWORD dwLen);
// 显示本地视频画面调节对话框
BRAC_API DWORD BRAC_ShowLVProperty(HWND hParent, LPCTSTR szCaption, DWORD dwX ,DWORD dwY);
typedef DWORD(_cdecl * BRAC_ShowLVProperty_Func)(HWND hParent, LPCTSTR szCaption, DWORD dwX ,DWORD dwY);

// 枚举本地视频采集设备
BRAC_API DWORD BRAC_EnumVideoCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum);
typedef DWORD(_cdecl * BRAC_EnumVideoCapture_Func)(CHAR** lpDeviceName, DWORD& dwDeviceNum);
// 枚举本地音频采集设备
BRAC_API DWORD BRAC_EnumAudioCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum);
typedef DWORD(_cdecl * BRAC_EnumAudioCapture_Func)(CHAR** lpDeviceName, DWORD& dwDeviceNum);
// 选择指定的视频采集设备
BRAC_API DWORD BRAC_SelectVideoCapture(LPCTSTR szCaptureName);
typedef DWORD(_cdecl *BRAC_SelectVideoCapture_Func)(LPCTSTR szCaptureName);
// 选择指定的音频采集设备
BRAC_API DWORD BRAC_SelectAudioCapture(LPCTSTR szCaptureName);
typedef DWORD(_cdecl * BRAC_SelectAudioCapture_Func)(LPCTSTR szCaptureName);
// 获取当前使用的视频采集设备
BRAC_API DWORD BRAC_GetCurVideoCapture(CHAR* lpDeviceName, DWORD dwLen);
typedef DWORD(_cdecl * BRAC_GetCurVideoCapture_Func)(CHAR* lpDeviceName, DWORD dwLen);
// 获取当前使用的音频采集设备
BRAC_API DWORD BRAC_GetCurAudioCapture(CHAR* lpDeviceName, DWORD dwLen);
typedef DWORD(_cdecl * BRAC_GetCurAudioCapture_Func)(CHAR* lpDeviceName, DWORD dwLen);

// 用户音、视频录制
BRAC_API DWORD BRAC_StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam);
typedef DWORD(_cdecl* BRAC_StreamRecordCtrl_Func)(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam);
// 对用户的视频进行抓拍（快照）
BRAC_API DWORD BRAC_SnapShot(DWORD dwUserId, DWORD dwFlags, DWORD dwParam);
typedef DWORD(_cdecl* BRAC_SnapShot_Func)(DWORD dwUserId, DWORD dwFlags, DWORD dwParam);

// 透明通道传送缓冲区
BRAC_API DWORD BRAC_TransBuffer(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
typedef DWORD(_cdecl * BRAC_TransBuffer_Func)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
// 透明通道传送缓冲区扩展
BRAC_API DWORD BRAC_TransBufferEx(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
typedef DWORD(_cdecl * BRAC_TransBufferEx_Func)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// 传送文件
BRAC_API DWORD BRAC_TransFile(DWORD dwUserid, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
typedef DWORD(_cdecl * BRAC_TransFile_Func)(DWORD dwUserid, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// 取消传输任务
BRAC_API DWORD BRAC_CancelTransTask(DWORD dwUserid, DWORD dwTaskId);
typedef DWORD(_cdecl * BRAC_CancelTransTask_Func)(DWORD dwUserid, DWORD dwTaskId);
// 传送文本消息
BRAC_API DWORD BRAC_SendTextMessage(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
typedef DWORD(_cdecl * BRAC_SendTextMessage_Func)(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
// 查询传输任务相关信息
BRAC_API DWORD BRAC_QueryTransTaskInfo(DWORD dwUserid, DWORD dwTaskId, int infoname, char FAR* infoval, int infolen);
typedef DWORD(_cdecl * BRAC_QueryTransTaskInfo_Func)(DWORD dwUserid, DWORD dwTaskId, int infoname, char FAR* infoval, int infolen);
// 发送SDK Filter 通信数据
BRAC_API DWORD BRAC_SendSDKFilterData(LPBYTE lpBuf, DWORD dwLen);
typedef DWORD(_cdecl * BRAC_SendSDKFilterData_Func)(LPBYTE lpBuf, DWORD dwLen);

// 查询指定用户相关状态
BRAC_API DWORD BRAC_QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);
typedef DWORD(_cdecl * BRAC_QueryUserState_Func)(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);

// 释放所有资源
BRAC_API DWORD BRAC_Release(VOID);
typedef DWORD(_cdecl * BRAC_Release_Func)(VOID);


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

        static HINSTANCE  g_BRACModule=NULL;
        static DWORD	g_dwBRACModule_Count = 0;

        static BRAC_InitSDK_Func					g_BRAC_InitSDK_Func = NULL;
        static BRAC_GetSDKVersion_Func				g_BRAC_GetSDKVersion_Func = NULL;
        static BRAC_ActiveCallLog_Func				g_BRAC_ActiveCallLog_Func = NULL;
        static BRAC_SetSDKOption_Func				g_BRAC_SetSDKOption_Func = NULL;
        static BRAC_SetVideoDataCallBack_Func		g_BRAC_SetVideoDataCallBack_Func = NULL;
        static BRAC_SetAudioDataCallBack_Func		g_BRAC_SetAudioDataCallBack_Func = NULL;
        static BRAC_SetVolumeChangeCallBack_Func    g_BRAC_SetVolumeChangeCallBack_Func = NULL;
        static BRAC_SetTransBufferExCallBack_Func	g_BRAC_SetTransBufferExCallBack_Func = NULL;
        static BRAC_SetTransBufferCallBack_Func		g_BRAC_SetTransBufferCallBack_Func = NULL;
        static BRAC_SetTransFileCallBack_Func		g_BRAC_SetTransFileCallBack_Func = NULL;
        static BRAC_SetRecordSnapShotCallBack_Func  g_BRAC_SetRecordSnapShotCallBack_Func = NULL;
        static BRAC_SetSDKFilterDataCallBack_Func   g_BRAC_SetSDKFilterDataCallBack_Func = NULL;
        static BRAC_AudioGetVolume_Func				g_BRAC_AudioGetVolume_Func = NULL;
        static BRAC_SetServerAuthPass_Func			g_BRAC_SetServerAuthPass_Func = NULL;
        static BRAC_Connect_Func					g_BRAC_Connect_Func = NULL;
        static BRAC_Login_Func						g_BRAC_Login_Func = NULL;
        static BRAC_SetNotifyMessageCallBack_Func	g_BRAC_SetNotifyMessageCallBack_Func = NULL;
        static BRAC_SetTextMessageCallBack_Func		g_BRAC_SetTextMessageCallBack_Func = NULL;
        static BRAC_GetUserName_Func				g_BRAC_GetUserName_Func = NULL;
        static BRAC_GetRoomName_Func				g_BRAC_GetRoomName_Func = NULL;
        static BRAC_EnterRoom_Func					g_BRAC_EnterRoom_Func = NULL;
        static BRAC_SetVideoPos_Func				g_BRAC_SetVideoPos_Func = NULL;
        static BRAC_UserCameraControl_Func			g_BRAC_UserCameraControl_Func = NULL;
        static BRAC_UserSpeakControl_Func			g_BRAC_UserSpeakControl_Func = NULL;
        static BRAC_AudioSetVolume_Func				g_BRAC_AudioSetVolume_Func = NULL;
        static BRAC_Release_Func					g_BRAC_Release_Func = NULL;
        static BRAC_EnterRoomEx_Func				g_BRAC_EnterRoomEx_Func = NULL;
        static BRAC_LeaveRoom_Func					g_BRAC_LeaveRoom_Func = NULL;
        static BRAC_GetOnlineUser_Func				g_BRAC_GetOnlineUser_Func = NULL;
        static BRAC_GetCameraState_Func				g_BRAC_GetCameraState_Func = NULL;
        static BRAC_Logout_Func						g_BRAC_Logout_Func = NULL;
        static BRAC_TransFile_Func					g_BRAC_TransFile_Func = NULL;
        static BRAC_QueryTransTaskInfo_Func			g_BRAC_QueryTransTaskInfo_Func = NULL;
        static BRAC_QueryUserState_Func				g_BRAC_QueryUserState_Func = NULL;
        static BRAC_TransBufferEx_Func				g_BRAC_TransBufferEx_Func = NULL;
        static BRAC_TransBuffer_Func				g_BRAC_TransBuffer_Func = NULL;
        static BRAC_CancelTransTask_Func			g_BRAC_CancelTransTask_Func = NULL;
        static BRAC_SendTextMessage_Func			g_BRAC_SendTextMessage_Func = NULL;
        static BRAC_ShowLVProperty_Func				g_BRAC_ShowLVProperty_Func = NULL;
        static BRAC_SelectVideoCapture_Func			g_BRAC_SelectVideoCapture_Func = NULL;
        static BRAC_SelectAudioCapture_Func			g_BRAC_SelectAudioCapture_Func = NULL;
        static BRAC_EnumVideoCapture_Func			g_BRAC_EnumVideoCapture_Func = NULL;
        static BRAC_GetCurVideoCapture_Func			g_BRAC_GetCurVideoCapture_Func = NULL;
        static BRAC_EnumAudioCapture_Func			g_BRAC_EnumAudioCapture_Func = NULL;
        static BRAC_GetCurAudioCapture_Func			g_BRAC_GetCurAudioCapture_Func = NULL;
        static BRAC_SendSDKFilterData_Func			g_BRAC_SendSDKFilterData_Func = NULL;
        static BRAC_StreamRecordCtrl_Func			g_BRAC_StreamRecordCtrl_Func = NULL;
        static BRAC_SnapShot_Func					g_BRAC_SnapShot_Func = NULL;



#ifdef WIN32
    #define BRAC_DLL_ASSIGN(_Name) \
    g_BRAC_##_Name##_Func = (BRAC_##_Name##_Func)GetProcAddress(g_BRACModule,"BRAC_"#_Name); \
        if (g_BRAC_##_Name##_Func == NULL) Errors++;
#else
    #define BRAC_DLL_ASSIGN(_Name) \
    g_BRAC_##_Name##_Func = (BRAC_##_Name##_Func)dlsym(g_BRACModule,"BRAC_"#_Name); \
        if (g_BRAC_##_Name##_Func == NULL) Errors++;
#endif

        static BOOL BRAC_DLL_Load(LPCTSTR szPathName)
        {
                if (g_dwBRACModule_Count > 0)
                {
                        g_dwBRACModule_Count++;
                        return TRUE;
                }

                /* Load library */
#ifdef WIN32
                g_BRACModule = LoadLibraryEx(szPathName,NULL,LOAD_WITH_ALTERED_SEARCH_PATH);
#else
        g_BRACModule = dlopen(szPathName,RTLD_NOW);
#endif
                if (!g_BRACModule)
                {
                        CHAR szErrorMsg[1024] = {0};
#ifdef WIN32
                        _snprintf(szErrorMsg,sizeof(szErrorMsg),"LoadLibrary %s Error:%d",szPathName,GetLastError());
#else
                        _snprintf(szErrorMsg,sizeof(szErrorMsg),"LoadLibrary %s Error:%s",szPathName,dlerror());
#endif
//...			TRACE(szErrorMsg);
                        return FALSE;
                }

                DWORD Errors=0;
                BRAC_DLL_ASSIGN(InitSDK);
                BRAC_DLL_ASSIGN(GetSDKVersion);
                BRAC_DLL_ASSIGN(ActiveCallLog);
                BRAC_DLL_ASSIGN(SetSDKOption);
                BRAC_DLL_ASSIGN(SetVideoDataCallBack);
                BRAC_DLL_ASSIGN(SetAudioDataCallBack);
                BRAC_DLL_ASSIGN(SetVolumeChangeCallBack);
                BRAC_DLL_ASSIGN(SetTransBufferExCallBack);
                BRAC_DLL_ASSIGN(SetTransBufferCallBack);
                BRAC_DLL_ASSIGN(SetTransFileCallBack);
                BRAC_DLL_ASSIGN(SetRecordSnapShotCallBack);
                BRAC_DLL_ASSIGN(SetSDKFilterDataCallBack);
                BRAC_DLL_ASSIGN(AudioGetVolume);
                BRAC_DLL_ASSIGN(SetServerAuthPass);
                BRAC_DLL_ASSIGN(Connect);
                BRAC_DLL_ASSIGN(Login);
                BRAC_DLL_ASSIGN(SetNotifyMessageCallBack);
                BRAC_DLL_ASSIGN(SetTextMessageCallBack);
                BRAC_DLL_ASSIGN(GetUserName);
                BRAC_DLL_ASSIGN(GetRoomName);
                BRAC_DLL_ASSIGN(EnterRoom);
                BRAC_DLL_ASSIGN(SetVideoPos);
                BRAC_DLL_ASSIGN(UserCameraControl);
                BRAC_DLL_ASSIGN(UserSpeakControl);
                BRAC_DLL_ASSIGN(AudioSetVolume);
                BRAC_DLL_ASSIGN(Release);
                BRAC_DLL_ASSIGN(EnterRoomEx);
                BRAC_DLL_ASSIGN(LeaveRoom);
                BRAC_DLL_ASSIGN(GetOnlineUser);
                BRAC_DLL_ASSIGN(GetCameraState);
                BRAC_DLL_ASSIGN(Logout);
                BRAC_DLL_ASSIGN(TransFile);
                BRAC_DLL_ASSIGN(QueryTransTaskInfo);
                BRAC_DLL_ASSIGN(QueryUserState);
                BRAC_DLL_ASSIGN(TransBufferEx);
                BRAC_DLL_ASSIGN(TransBuffer);
                BRAC_DLL_ASSIGN(CancelTransTask);
                BRAC_DLL_ASSIGN(SendTextMessage);
                BRAC_DLL_ASSIGN(ShowLVProperty);
                BRAC_DLL_ASSIGN(SelectVideoCapture);
                BRAC_DLL_ASSIGN(SelectAudioCapture);
                BRAC_DLL_ASSIGN(EnumVideoCapture);
                BRAC_DLL_ASSIGN(GetCurVideoCapture);
                BRAC_DLL_ASSIGN(EnumAudioCapture);
                BRAC_DLL_ASSIGN(GetCurAudioCapture);
                BRAC_DLL_ASSIGN(SendSDKFilterData);
                BRAC_DLL_ASSIGN(StreamRecordCtrl);
                BRAC_DLL_ASSIGN(SnapShot);

                if(Errors>0)
					return FALSE;

                g_dwBRACModule_Count++;
                return TRUE;
        }

        static BOOL BRAC_DLL_IsLoaded()
        {
                return g_BRACModule ? TRUE : FALSE;
        }

        static void BRAC_DLL_UnLoad()
        {
                g_dwBRACModule_Count--;
                if (g_dwBRACModule_Count > 0)
                        return;
#ifdef WIN32
                FreeLibrary(g_BRACModule);
#else
				dlclose(g_BRACModule);
#endif
                g_BRACModule=NULL;
        }

#ifdef __cplusplus
}
#endif /*__cplusplus*/


#ifdef __cplusplus


#define BRAC_TEST_VOID \
        if (!IsReady()) return
#define BRAC_TEST_INT \
        if (!IsReady()) return -1
#define BRAC_TEST_BOOL \
        if (!IsReady()) return FALSE


class CAnyChatCoreSDK
{
public:
        CAnyChatCoreSDK()
        {
			m_bSuccessLoadDll = FALSE;
        }
        CAnyChatCoreSDK(LPCTSTR szPathName)
        {
			m_bSuccessLoadDll = BRAC_DLL_Load(szPathName);
        }
        ~CAnyChatCoreSDK()
        {
            BRAC_TEST_VOID;
            BRAC_DLL_UnLoad();
            m_bSuccessLoadDll = FALSE;
        }
        BOOL LoadFilterDll(LPCTSTR szPathName)
        {
			return (m_bSuccessLoadDll = BRAC_DLL_Load(szPathName));
        }
        BOOL IsReady()
        {
			return m_bSuccessLoadDll;
        }

        // 初始化系统
        DWORD InitSDK(HWND hWnd, DWORD dwFuncMode)
        {
			BRAC_TEST_INT;
            return g_BRAC_InitSDK_Func(hWnd, dwFuncMode);
        }
        // 获取版本信息
        DWORD GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, LPSTR lpCompileTime, DWORD dwBufLen)
        {
            BRAC_TEST_INT;
            return g_BRAC_GetSDKVersion_Func(dwMainVer, dwSubVer, lpCompileTime, dwBufLen);
        }
        // 激活（关闭）SDK调用日志
        DWORD ActiveCallLog(BOOL bActive)
        {
			BRAC_TEST_INT;
            return g_BRAC_ActiveCallLog_Func(bActive);
        }
        // SDK内核参数设置
        DWORD SetSDKOption(int optname, const char FAR* optval, int optlen)
        {
			BRAC_TEST_INT;
            return g_BRAC_SetSDKOption_Func(optname, optval, optlen);
        }
        // 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
        DWORD SetServerAuthPass(LPCTSTR lpPassword)
        {
			BRAC_TEST_INT;
            return g_BRAC_SetServerAuthPass_Func(lpPassword);
        }

        // 设置视频数据回调函数
        DWORD SetVideoDataCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue)
        {
			BRAC_TEST_INT;
            return g_BRAC_SetVideoDataCallBack_Func(pixFmt, lpFunction, lpUserValue);
        }
        // 设置音频数据回调函数
        DWORD SetAudioDataCallBack(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue)
        {
			BRAC_TEST_INT;
            return g_BRAC_SetAudioDataCallBack_Func(lpFunction, lpUserValue);
        }
        // 设置音量变化回调函数
        DWORD SetVolumeChangeCallBack(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue)
        {
			BRAC_TEST_INT;
            return g_BRAC_SetVolumeChangeCallBack_Func(lpFunction, lpUserValue);
        }
        // 设置透明通道数据扩展回调函数
       DWORD SetTransBufferExCallBack(BRAC_TransBufferEx_CallBack lpFunction, LPVOID lpUserValue)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SetTransBufferExCallBack_Func(lpFunction, lpUserValue);
       }
       //设置透明通道数据回调函数
       DWORD SetTransBufferCallBack(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SetTransBufferCallBack_Func(lpFunction, lpUserValue);
       }
       // 设置文件传输回调函数
       DWORD SetTransFileCallBack(BRAC_TransFile_CallBack lpFunction, LPVOID lpUserValue)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SetTransFileCallBack_Func(lpFunction, lpUserValue);
       }
       // 设置录像快照任务完成通知回调函数
       DWORD SetRecordSnapShotCallBack(BRAC_RecordSnapShot_CallBack lpFunction, LPVOID lpUserValue)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SetRecordSnapShotCallBack_Func(lpFunction, lpUserValue);
       }
       // 设置SDK Filter通信数据回调函数定义
       DWORD SetSDKFilterDataCallBack(BRAC_SDKFilterData_CallBack lpFunction, LPVOID lpUserValue)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SetSDKFilterDataCallBack_Func(lpFunction, lpUserValue);
       }
       // 设置异步消息通知回调函数
       DWORD SetNotifyMessageCallBack(BRAC_NotifyMessage_CallBack lpFunction, LPVOID lpUserValue)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SetNotifyMessageCallBack_Func(lpFunction, lpUserValue);
       }
       // 设置文字消息回调函数
       DWORD SetTextMessageCallBack(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SetTextMessageCallBack_Func(lpFunction, lpUserValue);
       }


       // 连接服务器
       DWORD Connect(LPCTSTR lpServerAddr, DWORD dwPort)
       {
		   BRAC_TEST_INT;
           return g_BRAC_Connect_Func(lpServerAddr, dwPort);
       }
       // 登录系统
       DWORD Login(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType)
       {
		   BRAC_TEST_INT;
           return g_BRAC_Login_Func(lpUserName, lpPassword, dwPassEncType);
       }
       // 进入房间
       DWORD EnterRoom(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType)
       {
		   BRAC_TEST_INT;
           return g_BRAC_EnterRoom_Func(dwRoomid, lpRoomPass, dwPassEncType);
       }
       // 进入房间
       DWORD EnterRoomEx(LPCTSTR lpRoomName, LPCTSTR lpRoomPass)
       {
		   BRAC_TEST_INT;
           return g_BRAC_EnterRoomEx_Func(lpRoomName, lpRoomPass);
       }
       // 离开房间
       DWORD LeaveRoom(DWORD dwRoomid)
       {
		   BRAC_TEST_INT;
           return g_BRAC_LeaveRoom_Func(dwRoomid);
       }
       // 注销系统
       DWORD Logout(VOID)
       {
		   BRAC_TEST_INT;
           return g_BRAC_Logout_Func();
       }

       // 操作用户视频
       DWORD UserCameraControl(DWORD dwUserid, BOOL bOpen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_UserCameraControl_Func(dwUserid, bOpen);
       }
       // 操作用户语音
       DWORD UserSpeakControl(DWORD dwUserid, BOOL bOpen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_UserSpeakControl_Func(dwUserid, bOpen);
       }
       // 设置视频显示位置
       DWORD SetVideoPos(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SetVideoPos_Func(dwUserid, hWnd, dwLeft, dwTop, dwRight,dwBottom);
       }
       // 获取指定音频设备的当前音量
       DWORD AudioGetVolume(BRAC_AudioDevice device, DWORD& dwVolume)
       {
		   BRAC_TEST_INT;
           return g_BRAC_AudioGetVolume_Func(device, dwVolume);
       }
       // 设置指定音频设备的音量
       DWORD AudioSetVolume(BRAC_AudioDevice device, DWORD dwVolume)
       {
		   BRAC_TEST_INT;
           return g_BRAC_AudioSetVolume_Func(device,dwVolume);
       }

       // 枚举本地视频采集设备
       DWORD EnumVideoCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum)
       {
		   BRAC_TEST_INT;
           return g_BRAC_EnumVideoCapture_Func(lpDeviceName, dwDeviceNum);
       }
       // 枚举本地音频采集设备
       DWORD EnumAudioCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum)
       {
		   BRAC_TEST_INT;
           return g_BRAC_EnumAudioCapture_Func(lpDeviceName, dwDeviceNum);
       }
       // 选择指定的视频采集设备
       DWORD SelectVideoCapture(LPCTSTR szCaptureName)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SelectVideoCapture_Func(szCaptureName);
       }
       // 选择指定的音频采集设备
       DWORD SelectAudioCapture(LPCTSTR szCaptureName)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SelectAudioCapture_Func(szCaptureName);
       }
       // 获取当前使用的视频采集设备
       DWORD GetCurVideoCapture(CHAR* lpDeviceName, DWORD dwLen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_GetCurVideoCapture_Func(lpDeviceName, dwLen);
       }
       // 获取当前使用的音频采集设备
       DWORD GetCurAudioCapture(CHAR* lpDeviceName, DWORD dwLen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_GetCurAudioCapture_Func(lpDeviceName, dwLen);
       }

       // 获取当前房间在线用户列表
       DWORD GetOnlineUser(LPDWORD lpUserIDArray, DWORD& dwUserNum)
       {
		   BRAC_TEST_INT;
           return g_BRAC_GetOnlineUser_Func(lpUserIDArray, dwUserNum);
       }
       // 查询用户摄像头的状态
       DWORD GetCameraState(DWORD dwUserid, DWORD& dwState)
       {
		   BRAC_TEST_INT;
           return g_BRAC_GetCameraState_Func(dwUserid, dwState);
       }
       // 查询用户名称
       DWORD GetUserName(DWORD dwUserid, CHAR* lpUserName, DWORD dwLen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_GetUserName_Func(dwUserid, lpUserName, dwLen);
       }
       // 查询房间名称
       DWORD GetRoomName(DWORD dwRoomId, CHAR* lpRoomName, DWORD dwLen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_GetRoomName_Func(dwRoomId, lpRoomName, dwLen);
       }
       // 显示本地视频画面调节对话框
       DWORD ShowLVProperty(HWND hParent, LPCTSTR szCaption, DWORD dwX ,DWORD dwY)
       {
		   BRAC_TEST_INT;
           return g_BRAC_ShowLVProperty_Func(hParent, szCaption, dwX, dwY);
       }

       // 用户音、视频录制
       DWORD StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam)
       {
		   BRAC_TEST_INT;
           return g_BRAC_StreamRecordCtrl_Func(dwUserId, bStartRecord, dwFlags, dwParam);
       }
       // 对用户的视频进行抓拍（快照）
       DWORD SnapShot(DWORD dwUserId, DWORD dwFlags, DWORD dwParam)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SnapShot_Func(dwUserId, dwFlags, dwParam);
       }

       // 透明通道传送缓冲区
       DWORD TransBuffer(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_TransBuffer_Func(dwUserid, lpBuf, dwLen);
       }
       // 透明通道传送缓冲区扩展
       DWORD TransBufferEx(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId)
       {
		   BRAC_TEST_INT;
           return g_BRAC_TransBufferEx_Func(dwUserid, lpBuf, dwLen, wParam, lParam, dwFlags, dwTaskId);
       }
       // 传送文件
       DWORD TransFile(DWORD dwUserid, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId)
       {
		   BRAC_TEST_INT;
           return g_BRAC_TransFile_Func(dwUserid, lpLocalPathName, wParam, lParam, dwFlags, dwTaskId);
       }
       // 取消传输任务
       DWORD  CancelTransTask(DWORD dwUserid, DWORD dwTaskId)
       {
		   BRAC_TEST_INT;
           return g_BRAC_CancelTransTask_Func(dwUserid, dwTaskId);
       }
       // 传送文本消息
       DWORD SendTextMessage(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SendTextMessage_Func(dwUserid, bSecret, lpMsgBuf, dwLen);
       }
       // 查询传输任务相关信息
       DWORD QueryTransTaskInfo(DWORD dwUserid, DWORD dwTaskId, int infoname, char FAR* infoval, int infolen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_QueryTransTaskInfo_Func(dwUserid, dwTaskId, infoname, infoval, infolen);
       }
       // 发送SDK Filter 通信数据
       DWORD SendSDKFilterData(LPBYTE lpBuf, DWORD dwLen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_SendSDKFilterData_Func(lpBuf, dwLen);
       }

       // 查询指定用户相关状态
       DWORD QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen)
       {
		   BRAC_TEST_INT;
           return g_BRAC_QueryUserState_Func(dwUserId, infoname, infoval, infolen);
       }

       // 释放所有资源
       DWORD Release(VOID)
       {
		   BRAC_TEST_INT;
           return g_BRAC_Release_Func();
       }

private:
        BOOL	m_bSuccessLoadDll;
};




#endif /*__cplusplus*/






#endif // ANYCHATCORESDK_H
