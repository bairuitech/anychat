using System;
using System.Text;
using System.Runtime.InteropServices;

namespace ANYCHATAPI
{
 /***********************************************************************************
    * ** AnyChat Platform Server SDK
    * *********************************************************************************/
    public class AnyChatServerSDK
    {
        public const string AnyChatServerSDKDll = "AnyChatServerSDKU.dll";

        // #define BRAS_SERVERAPPMSG_CONNECTED		1		///< 连接AnyChat服务器成功
		public const int BRAS_SERVERAPPMSG_CONNECTED = 1;
        //#define BRAS_SERVERAPPMSG_DISCONNECT		2		///< 与AnyChat服务器断开连接
		public const int BRAS_SERVERAPPMSG_DISCONNECT = 2;
		
		// 服务器消息类型定义（回调事件：BRAS_OnServerAppMessageEx_CallBack 参数）
		// #define BRAS_MESSAGE_CORESERVERCONN		10		///< 与核心服务器的连接消息，wParam为errorcode
		public const int BRAS_MESSAGE_CORESERVERCONN	= 10;
		// #define BRAS_MESSAGE_RECORDSERVERCONN	11		///< 与录像服务器的连接消息，wParam为errorcode，lParam为recordserverid
		public const int BRAS_MESSAGE_RECORDSERVERCONN	= 11;
		// #define BRAS_MESSAGE_LOGINSERVERCONN		12		///< 与登录服务器的连接消息，wParam为errorcode，lParam为loginserverid
		public const int BRAS_MESSAGE_LOGINSERVERCONN	= 12;
		// #define BRAS_MESSAGE_ROOMSERVERCONN		13		///< 与房间服务器的连接消息，wParam为errorcode，lParam为roomserverid
		public const int BRAS_MESSAGE_ROOMSERVERCONN	= 13;
		// #define BRAS_MESSAGE_MEDIASERVERCONN		14		///< 与流媒体服务器的连接消息，wParam为errorcode，lParam为mediaserverid
		public const int BRAS_MESSAGE_MEDIASERVERCONN	= 14;
		
		// 视频呼叫事件类型定义（API：BRAS_VideoCallControl 传入参数、OnVideoCallEvent回调参数）
		//#define BRAS_VIDEOCALL_EVENT_REQUEST    1        ///< 呼叫请求
		public const int BRAS_VIDEOCALL_EVENT_REQUEST 	= 1;
		//#define BRAS_VIDEOCALL_EVENT_REPLY      2        ///< 呼叫请求回复
		public const int BRAS_VIDEOCALL_EVENT_REPLY 	= 2;
		//#define BRAS_VIDEOCALL_EVENT_START      3        ///< 视频呼叫会话开始事件
		public const int BRAS_VIDEOCALL_EVENT_START 	= 3;
		//#define BRAS_VIDEOCALL_EVENT_FINISH     4        ///< 挂断（结束）呼叫会话
		public const int BRAS_VIDEOCALL_EVENT_FINISH 	= 4;
		
		// 初始化标志（API：BRAS_InitSDK 传入参数）
		public const int BRAS_INITFLAGS_MULTITHREADS	= 1;	///< 多线程模式

        /**
		 *    回调函数定义
		 */

        // 服务器应用程序消息回调函数定义
        //typedef void (CALLBACK* BRAS_OnServerAppMessage_CallBack)(DWORD dwMsg, LPVOID lpUserValue);
        public delegate void OnServerAppMessageCallBack(int msg, int userValue);
		
		// 服务器应用程序消息（扩展）回调函数定义
        //typedef void (CALLBACK* BRAS_OnServerAppMessageEx_CallBack)(DWORD dwNotifyMessage, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
        public delegate void OnServerAppMessageExCallBack(int dwNotifyMessage, int wParam, int lParam, int userValue);

		// SDK定时器回调函数定义（上层应用可以在该回调中处理定时任务，而不需要额外开启线程，或是定时器）
		//typedef void (CALLBACK* BRAS_OnTimerEvent_CallBack)(LPVOID lpUserValue);
        public delegate void OnTimerEventCallBack(int userValue);

		// 用户身份验证回调函数定义
		// typedef DWORD (CALLBACK* BRAS_VerifyUser_CallBack)(IN LPCTSTR lpUserName,IN LPCTSTR lpPassword, OUT LPDWORD lpUserID, OUT LPDWORD lpUserLevel, OUT LPTSTR lpNickName,IN DWORD dwNCLen, LPVOID lpUserValue);
        public delegate int VerifyUserCallBack([MarshalAs(UnmanagedType.LPWStr)] string userName, [MarshalAs(UnmanagedType.LPWStr)] string password, ref int userID, ref int userLevel, IntPtr nickName, int len, int userValue);

        // 用户申请进入房间回调函数定义
        //typedef DWORD (CALLBACK* BRAS_PrepareEnterRoom_CallBack)(DWORD dwUserId, DWORD dwRoomId, LPCTSTR lpRoomName,LPCTSTR lpPassword, LPVOID lpUserValue);
        public delegate int PrepareEnterRoomCallBack(int userId, int roomId, [MarshalAs(UnmanagedType.LPWStr)] string roomName, [MarshalAs(UnmanagedType.LPWStr)] string password, int userValue);

        // 用户登录成功回调函数定义
        //typedef void (CALLBACK* BRAS_OnUserLoginAction_CallBack)(DWORD dwUserId, LPCTSTR szUserName, DWORD dwLevel, LPCTSTR szIpAddr, LPVOID lpUserValue);
        public delegate void OnUserLoginActionCallBack(int userId, [MarshalAs(UnmanagedType.LPWStr)] string userName, int level, string addr, int userValue);

        // 用户注销回调函数定义
        //typedef void (CALLBACK* BRAS_OnUserLogoutAction_CallBack)(DWORD dwUserId, LPVOID lpUserValue);
        public delegate void OnUserLogoutActionCallBack(int userId, int userValue);
		
		// 用户注销回调函数定义（扩展）
        //typedef void (CALLBACK* BRAS_OnUserLogoutActionEx_CallBack)(DWORD dwUserId, DWORD dwErrorCode, LPVOID lpUserValue);
        public delegate void OnUserLogoutActionExCallBack(int userId, int errorcode, int userValue);

        // 用户进入房间回调函数定义
        //typedef void (CALLBACK* BRAS_OnUserEnterRoomAction_CallBack)(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue);
        public delegate void OnUserEnterRoomActionCallBack(int userId, int roomId, int userValue);

        // 用户离开房间回调函数定义
        //typedef void (CALLBACK* BRAS_OnUserLeaveRoomAction_CallBack)(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue);
        public delegate void OnUserLeaveRoomActionCallBack(int userId, int roomId, int userValue);

        // 上层业务自定义数据回调函数定义
        //typedef void (CALLBACK* BRAS_OnRecvUserFilterData_CallBack)(DWORD dwUserId, LPCTSTR lpBuf, DWORD dwLen, LPVOID lpUserValue);
        public delegate void OnRecvUserFilterDataCallBack(int userId, IntPtr buf, int len, int userValue);

        // 收到用户文字聊天通信数据回调函数定义
        //typedef void (CALLBACK* BRAS_OnRecvUserTextMsg_CallBack)(DWORD dwRoomId, DWORD dwSrcUserId, DWORD dwTarUserId, BOOL bSecret, LPCTSTR lpTextMessage, DWORD dwLen, LPVOID lpUserValue);
        public delegate void OnRecvUserTextMsgCallBack(int roomId, int srcUserId, int tarUserId, bool bSecret, string textMessage, int len, int userValue);

		// 透明通道数据回调函数定义
		//typedef void (CALLBACK * BRAS_OnTransBuffer_CallBack)(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
		public delegate void OnTransBufferCallBack(int dwUserId, IntPtr lpBuf, int dwLen, int lpUserValue);
		
		// 透明通道数据扩展回调函数定义
		//typedef void (CALLBACK * BRAS_OnTransBufferEx_CallBack)(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
		public delegate void OnTransBufferExCallBack(int dwUserId, IntPtr lpBuf, int dwLen, int wParam, int lParam, int dwTaskId, int lpUserValue);
		
		// 文件传输回调函数定义
		//typedef void (CALLBACK * BRAS_OnTransFile_CallBack)(DWORD dwUserId, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
        public delegate void OnTransFileCallBack(int dwUserId, [MarshalAs(UnmanagedType.LPWStr)] string lpFileName, string lpTempFilePath, int dwFileLength, int wParam, int lParam, int dwTaskId, int lpUserValue);

		// 服务器录像回调函数定义
		//typedef void (CALLBACK * BRAS_OnServerRecord_CallBack)(DWORD dwUserId, DWORD dwParam, DWORD dwRecordServerId, DWORD dwElapse, LPCTSTR lpRecordFileName, LPVOID lpUserValue);
        public delegate void OnServerRecordCallBack(int dwUserId, int dwParam, int dwRecordServerId, int dwElapse, [MarshalAs(UnmanagedType.LPWStr)] string lpRecordFileName, int lpUserValue);
		
		// 视频通话消息通知回调函数定义
		//typedef DWORD (CALLBACK * BRAS_OnVideoCallEvent_CallBack)(DWORD dwEventType, DWORD dwSrcUserId, DWORD dwTarUserId, DWORD dwErrorCode, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);
		public delegate int OnVideoCallEventCallBack(int dwEventType, int dwSrcUserId, int dwTarUserId, int dwErrorCode, int dwFlags, int dwParam, [MarshalAs(UnmanagedType.LPWStr)] string lpUserStr, int lpUserValue);

		/**
		*    API 方法定义
		*/

        // 设置服务器应用程序消息回调函数
        //BRAS_API DWORD BRAS_SetOnServerAppMessageCallBack(BRAS_OnServerAppMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnServerAppMessageCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetOnServerAppMessageCallBack(OnServerAppMessageCallBack function, int userValue);
		
		// 设置服务器应用程序消息（扩展）回调函数
        //BRAS_API DWORD BRAS_SetOnServerAppMessageExCallBack(BRAS_OnServerAppMessageEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnServerAppMessageExCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetOnServerAppMessageExCallBack(OnServerAppMessageExCallBack function, int userValue);

        // 设置SDK定时器回调函数（dwElapse：定时器间隔，单位：ms）
        // BRAS_API DWORD BRAS_SetTimerEventCallBack(DWORD dwElapse, BRAS_OnTimerEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetTimerEventCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetTimerEventCallBack(int elapse, OnTimerEventCallBack function, int userValue);

        // 设置用户身份验证回调函数
        //BRAS_API DWORD BRAS_SetVerifyUserCallBack(BRAS_VerifyUser_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetVerifyUserCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetVerifyUserCallBack(VerifyUserCallBack function, int userValue);

        // 设置用户申请进入房间回调函数
        // BRAS_API DWORD BRAS_SetPrepareEnterRoomCallBack(BRAS_PrepareEnterRoom_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetPrepareEnterRoomCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetPrepareEnterRoomCallBack(PrepareEnterRoomCallBack function, int userValue);

        // 设置用户登录成功回调函数
        //BRAS_API DWORD BRAS_SetOnUserLoginActionCallBack(BRAS_OnUserLoginAction_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnUserLoginActionCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetOnUserLoginActionCallBack(OnUserLoginActionCallBack function, int userValue);

        // 设置用户注销回调函数
        //BRAS_API DWORD BRAS_SetOnUserLogoutActionCallBack(BRAS_OnUserLogoutAction_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnUserLogoutActionCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetOnUserLogoutActionCallBack(OnUserLogoutActionCallBack function, int userValue);
		
		// 设置用户注销回调函数（扩展）
        //BRAS_API DWORD BRAS_SetOnUserLogoutActionExCallBack(BRAS_OnUserLogoutActionEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnUserLogoutActionExCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetOnUserLogoutActionExCallBack(OnUserLogoutActionExCallBack function, int userValue);

        // 设置用户进入房间回调函数
        //BRAS_API DWORD BRAS_SetOnUserEnterRoomActionCallBack(BRAS_OnUserEnterRoomAction_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnUserEnterRoomActionCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetOnUserEnterRoomActionCallBack(OnUserEnterRoomActionCallBack function, int userValue);

        // 设置用户离开房间回调函数
        //BRAS_API DWORD BRAS_SetOnUserLeaveRoomActionCallBack(BRAS_OnUserLeaveRoomAction_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnUserLeaveRoomActionCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetOnUserLeaveRoomActionCallBack(OnUserLeaveRoomActionCallBack function, int userValue);

        // 设置用户上层业务自定义数据回调函数
        // BRAS_API DWORD BRAS_SetOnRecvUserFilterDataCallBack(BRAS_OnRecvUserFilterData_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnRecvUserFilterDataCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetOnRecvUserFilterDataCallBack(OnRecvUserFilterDataCallBack function, int userValue);

        // 设置用户文字聊天通信数据回调函数
        //BRAS_API DWORD BRAS_SetOnRecvUserTextMsgCallBack(BRAS_OnRecvUserTextMsg_CallBack lpFunction, LPVOID lpUserValue=NULL);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnRecvUserTextMsgCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SetOnRecvUserTextMsgCallBack(OnRecvUserTextMsgCallBack function, int userValue);
		
		
		// 设置透明通道数据回调函数
		//BRAS_API DWORD BRAS_SetOnTransBufferCallBack(BRAS_OnTransBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnTransBufferCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		public static extern int BRAS_SetOnTransBufferCallBack(OnTransBufferCallBack function, int lpUserValue);
		
		// 设置透明通道数据扩展回调函数
		//BRAS_API DWORD BRAS_SetOnTransBufferExCallBack(BRAS_OnTransBufferEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnTransBufferExCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		public static extern int BRAS_SetOnTransBufferExCallBack(OnTransBufferExCallBack function, int lpUserValue);
		
		// 设置文件传输回调函数
		//BRAS_API DWORD BRAS_SetOnTransFileCallBack(BRAS_OnTransFile_CallBack lpFunction, LPVOID lpUserValue=NULL);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnTransFileCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		public static extern int BRAS_SetOnTransFileCallBack(OnTransFileCallBack function, int lpUserValue);
		
		// 设置服务器录像通知回调函数
		//BRAS_API DWORD BRAS_SetOnServerRecordCallBack(BRAS_OnServerRecord_CallBack lpFunction, LPVOID lpUserValue=NULL);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnServerRecordCallBack", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		public static extern int BRAS_SetOnServerRecordCallBack(OnServerRecordCallBack function, int lpUserValue);
		
		// 设置视频通话消息通知回调函数
		//BRAS_API DWORD BRAS_SetOnVideoCallEventCallBack(BRAS_OnVideoCallEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SetOnVideoCallEventCallBack", CallingConvention = CallingConvention.Cdecl)]
		public static extern int BRAS_SetOnVideoCallEventCallBack(OnVideoCallEventCallBack function, int lpUserValue);

		
		// 获取SDK版本信息
		//BRAS_API DWORD BRAS_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, TCHAR* lpCompileTime, DWORD dwBufLen);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_GetSDKVersion", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_GetSDKVersion(ref int dwMainVer, ref int dwSubVer, StringBuilder lpCompileTime, int bufLen);
		
        // 初始化SDK
        //BRAS_API DWORD BRAS_InitSDK(DWORD dwReserved);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_InitSDK", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_InitSDK(int reserved);

        // 释放资源
        //BRAS_API DWORD BRAS_Release(void);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_Release", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_Release();

        // 向指定用户发送数据
        //BRAS_API DWORD BRAS_SendBufToUser(DWORD dwUserId, LPCTSTR lpBuf, DWORD dwLen);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SendBufToUser", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SendBufToUser(int userId, byte[] buf, int len);

        // 向指定房间的所有用户发送数据
        //BRAS_API DWORD BRAS_SendBufToRoom(DWORD dwRoomId, LPCTSTR lpBuf, DWORD dwLen);
        [DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_SendBufToRoom", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        public static extern int BRAS_SendBufToRoom(int dwRoomId, byte[] lpBuf, int dwLen);
		
		// 向指定用户发送透明通道数据
		//BRAS_API DWORD BRAS_TransBuffer(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_TransBuffer", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		public static extern int BRAS_TransBuffer(int dwUserId, byte[] lpBuf, int dwLen);
		
		// 向指定用户发送扩展缓冲区数据
		//BRAS_API DWORD BRAS_TransBufferEx(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_TransBufferEx", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		public static extern int BRAS_TransBufferEx(int dwUserId, byte[] lpBuf, int dwLen, int wParam, int lParam, int dwFlags, ref int dwTaskId);
		
		// 向指定用户发送文件
		//BRAS_API DWORD BRAS_TransFile(DWORD dwUserId, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_TransFile", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		public static extern int BRAS_TransFile(int dwUserId, string lpLocalPathName, int wParam, int lParam, int dwFlags, ref int dwTaskId);
		
		// 中心端录像控制
		//BRAS_API DWORD BRAS_StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam, DWORD dwRecordServerId);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_StreamRecordCtrl", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		public static extern int BRAS_StreamRecordCtrl(int dwUserId, int bStartRecord, int dwFlags, int dwParam, int dwRecordServerId);
		
		// 发送透明通道数据给录像服务器
		//BRAS_API DWORD BRAS_TransBuffer2RecordServer(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, DWORD dwParam, DWORD dwRecordServerId);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_TransBuffer2RecordServer", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		public static extern int BRAS_TransBuffer2RecordServer(int dwUserId, byte[] lpBuf, int dwLen, int dwParam, int dwRecordServerId);
		
		// 视频呼叫事件控制（请求、回复、挂断等）
		//BRAS_API DWORD BRAS_VideoCallControl(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags=0, DWORD dwParam=0, LPCTSTR lpUserStr=NULL);
		[DllImport(AnyChatServerSDKDll, EntryPoint = "BRAS_VideoCallControl", CallingConvention = CallingConvention.Cdecl)]
		public static extern int BRAS_VideoCallControl(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, string lpUserStr);
		
    }
}