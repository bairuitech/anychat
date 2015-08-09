using System;
using System.Collections.Generic;
using System.Text;
using ANYCHATAPI;
using System.Runtime.InteropServices;

namespace AnyChatServer
{
    public class SystemSettingServer
    {

        public static void Init(IntPtr hWnd)
        {
            // 设置服务器应用程序消息回调函数
            AnyChatServerSDK.BRAS_SetOnServerAppMessageExCallBack(mServerAppMessageExCallBack, 0);
            // 设置SDK定时器回调函数
            AnyChatServerSDK.BRAS_SetTimerEventCallBack(1000, mTimerEventCallBack, 0);
            // 设置用户身份验证回调函数
            AnyChatServerSDK.BRAS_SetVerifyUserCallBack(mVerifyUserCallBack, 0);
            // 设置用户申请进入房间回调函数
            AnyChatServerSDK.BRAS_SetPrepareEnterRoomCallBack(mPrepareEnterRoomCallBack, 0);
            // 设置用户登录成功回调函数
            AnyChatServerSDK.BRAS_SetOnUserLoginActionCallBack(mUserLoginActionCallBack, 0);
            // 设置用户注销回调函数
            AnyChatServerSDK.BRAS_SetOnUserLogoutActionExCallBack(mUserLogoutActionExCallBack, 0);
            // 设置用户进入房间回调函数
            AnyChatServerSDK.BRAS_SetOnUserEnterRoomActionCallBack(mUserEnterRoomActionCallBack, 0);
            // 设置用户离开房间回调函数
            AnyChatServerSDK.BRAS_SetOnUserLeaveRoomActionCallBack(mUserLeaveRoomActionCallBack, 0);
            // 设置用户上层业务自定义数据回调函数
            AnyChatServerSDK.BRAS_SetOnRecvUserFilterDataCallBack(mRecvUserFilterDataCallBack, 0);
            // 用户文字聊天通信数据回调函数
            AnyChatServerSDK.BRAS_SetOnRecvUserTextMsgCallBack(mRecvUserTextMsgCallBack, 0);
            // 设置透明通道数据回调函数
            AnyChatServerSDK.BRAS_SetOnTransBufferCallBack(mTransBufferCallBack, 0);
            // 设置透明通道数据扩展回调函数
            AnyChatServerSDK.BRAS_SetOnTransBufferExCallBack(mTransBufferExCallBack, 0);
            // 设置文件传输回调函数
            AnyChatServerSDK.BRAS_SetOnTransFileCallBack(mTransFileCallBack, 0);


            //设置业务对象事件通知回调函数
            AnyChatServerSDK.BRAS_SetCallBack(AnyChatServerSDK.BRAS_CBTYPE_OBJECTEVENT, Marshal.GetFunctionPointerForDelegate(mObjectEventNotifyCallBack), hWnd);

        }

        // 服务器应用程序消息回调函数定义
        private static AnyChatServerSDK.OnServerAppMessageExCallBack mServerAppMessageExCallBack = OnServerAppMessageExCallBack;
        // SDK定时器回调函数定义（上层应用可以在该回调中处理定时任务，而不需要额外开启线程，或是定时器）
        private static AnyChatServerSDK.OnTimerEventCallBack mTimerEventCallBack = OnTimerEventCallBack;
        // 用户身份验证回调函数定义
        private static AnyChatServerSDK.VerifyUserCallBack mVerifyUserCallBack = OnVerifyUserCallBack;
        // 用户申请进入房间回调函数定义
        private static AnyChatServerSDK.PrepareEnterRoomCallBack mPrepareEnterRoomCallBack = OnPrepareEnterRoomCallBack;
        // 用户登录成功回调函数定义
        private static AnyChatServerSDK.OnUserLoginActionCallBack mUserLoginActionCallBack = OnUserLoginActionCallBack;
        // 用户注销回调函数定义
        private static AnyChatServerSDK.OnUserLogoutActionExCallBack mUserLogoutActionExCallBack = OnUserLogoutActionExCallBack;
        // 用户进入房间回调函数定义
        private static AnyChatServerSDK.OnUserEnterRoomActionCallBack mUserEnterRoomActionCallBack = OnUserEnterRoomActionCallBack;
        // 用户离开房间回调函数定义
        private static AnyChatServerSDK.OnUserLeaveRoomActionCallBack mUserLeaveRoomActionCallBack = OnUserLeaveRoomActionCallBack;
        // 上层业务自定义数据回调函数定义
        private static AnyChatServerSDK.OnRecvUserFilterDataCallBack mRecvUserFilterDataCallBack = OnRecvUserFilterDataCallBack;
        // 收到用户文字聊天通信数据回调函数定义
        private static AnyChatServerSDK.OnRecvUserTextMsgCallBack mRecvUserTextMsgCallBack = OnRecvUserTextMsgCallBack;
        // 透明通道数据回调函数定义
        private static AnyChatServerSDK.OnTransBufferCallBack mTransBufferCallBack = OnTransBufferCallBack;
        // 透明通道数据扩展回调函数定义
        private static AnyChatServerSDK.OnTransBufferExCallBack mTransBufferExCallBack = OnTransBufferExCallBack;
        // 文件传输回调函数定义
        private static AnyChatServerSDK.OnTransFileCallBack mTransFileCallBack = OnTransFileCallBack;
        /// <summary>
        /// 业务对象回调函数定义
        /// </summary>
        private static AnyChatServerSDK.ObjectEventNotifyCallBack mObjectEventNotifyCallBack = onObjectEventNotifyCallBack;


        // 服务器应用程序消息回调函数定义
        public delegate void OnServerAppMessageEx_Received(int msg, int wParam, int lParam, int userValue);
        // SDK定时器回调函数定义（上层应用可以在该回调中处理定时任务，而不需要额外开启线程，或是定时器）
        public delegate void OnTimerEvent_Received(int userValue);
        // 用户身份验证回调函数定义
        public delegate void OnVerifyUser_Received(string userName, string password, ref int userID, ref int userLevel, IntPtr nickName, int len, int userValue);
        // 用户申请进入房间回调函数定义
        public delegate int OnPrepareEnterRoom_Received(int userId, int roomId, string roomName, string password, int userValue);
        // 用户登录成功回调函数定义
        public delegate void OnUserLoginAction_Received(int userId, string userName, int level, string addr, int userValue);
        // 用户注销回调函数定义  
        public delegate void OnUserLogoutActionEx_Received(int userId, int errorcode, int userValue);
        //用户进入房间回调函数定义
        public delegate void OnUserEnterRoomAction_Received(int userId, int roomId, int userValue);
        // 用户离开房间回调函数定义
        public delegate void OnUserLeaveRoomAction_Received(int userId, int roomId, int userValue);
        // 上层业务自定义数据回调函数定义
        public delegate void OnRecvUserFilterData_Received(int userId, IntPtr buf, int len, int userValue);
        // 收到用户文字聊天通信数据回调函数定义
        public delegate void OnRecvUserTextMsg_Received(int roomId, int srcUserId, int tarUserId, bool bSecret, string textMessage, int len, int userValue);
        // 透明通道数据回调函数定义
        public delegate void OnTransBuffer_Received(int dwUserId, IntPtr lpBuf, int dwLen, int lpUserValue);
        // 透明通道数据扩展回调函数定义
        public delegate void OnTransBufferEx_Received(int dwUserId, IntPtr lpBuf, int dwLen, int wParam, int lParam, int dwTaskId, int lpUserValue);
        // 文件传输回调函数定义
        public delegate void OnTransFile_Received(int dwUserId, string lpFileName, string lpTempFilePath, int dwFileLength, int wParam, int lParam, int dwTaskId, int lpUserValue);

        /// <summary>
        /// 业务对象事件通知回调函数定义
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwEventType"></param>
        /// <param name="dwParam1"></param>
        /// <param name="dwParam2"></param>
        /// <param name="dwParam3"></param>
        /// <param name="dwParam4"></param>
        /// <param name="strParam"></param>
        /// <returns></returns>
        public delegate void OnObjectEventNotifyCallBack(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue);


        public static OnServerAppMessageEx_Received OnServerAppMessageExReceived = null;
        // 服务器应用程序消息回调函数定义
        public static void OnServerAppMessageExCallBack(int msg, int wParam, int lParam, int userValue)
        {
            if (OnServerAppMessageExReceived != null)
            {
                OnServerAppMessageExReceived(msg, wParam, lParam, userValue);
            }
        }

        public static OnTimerEvent_Received OnTimerEventReceived = null;
        // SDK定时器回调函数定义（上层应用可以在该回调中处理定时任务，而不需要额外开启线程，或是定时器）
        public static void OnTimerEventCallBack(int userValue)
        {

        }

        public static OnVerifyUser_Received OnVerifyUserReceived = null;
        static int id = 1;
        // 用户身份验证回调函数定义
        // 根据函数返回值决定是否验证身份成功，当返回0时，必须分配一个唯一的userid
        public static int OnVerifyUserCallBack(string userName, string password, ref int userID, ref int userLevel, IntPtr nickName, int len, int userValue)
        {
            userID = id;
            id = id + 1;
			// 返回一个用户的昵称，若为空，则核心服务器会用userName来替代
			//string trueName = "返回的昵称";
            //byte[] toBytes = Encoding.Convert(Encoding.UTF8, Encoding.GetEncoding("gb2312"), Encoding.UTF8.GetBytes(trueName));
            //Marshal.Copy(toBytes, 0, nickName, toBytes.Length); 
            return 0;
        }

        public static OnPrepareEnterRoom_Received OnPrepareEnterRoomReceived = null;
        // 用户申请进入房间回调函数定义
        public static int OnPrepareEnterRoomCallBack(int userId, int roomId, string roomName, string password, int userValue)
        {
            int ret = 0;
            if (OnPrepareEnterRoomReceived != null)
            {
                ret=OnPrepareEnterRoomReceived(userId, roomId, roomName, password, userValue);
            }
            return ret;
        }


        public static OnUserLoginAction_Received OnUserLoginActionReceived = null;
        // 用户登录成功回调函数定义
        public static void OnUserLoginActionCallBack(int userId, string userName, int level, string addr, int userValue)
        {
            if (OnUserLoginActionReceived != null)
            {
                OnUserLoginActionReceived(userId, userName, level, addr, userValue);
            }
        }

        public static OnUserLogoutActionEx_Received OnUserLogoutActionExReceived = null;
        // 用户注销回调函数定义  
        public static void OnUserLogoutActionExCallBack(int userId, int errorcode, int userValue)
        {
            if (OnUserLogoutActionExReceived != null)
            {
                OnUserLogoutActionExReceived(userId, errorcode, userValue);
            }
        }

        public static OnUserEnterRoomAction_Received OnUserEnterRoomActionReceived = null;
        //用户进入房间回调函数定义
        public static void OnUserEnterRoomActionCallBack(int userId, int roomId, int userValue)
        {
            if (OnUserEnterRoomActionReceived != null)
            {
                OnUserEnterRoomActionReceived(userId, roomId, userValue);
            }
        }

        public static OnUserLeaveRoomAction_Received OnUserLeaveRoomActionReceived = null;
        // 用户离开房间回调函数定义
        public static void OnUserLeaveRoomActionCallBack(int userId, int roomId, int userValue)
        {
            if (OnUserLeaveRoomActionReceived != null)
            {
                OnUserLeaveRoomActionReceived(userId, roomId, userValue);
            }
        }

        public static OnRecvUserFilterData_Received OnRecvUserFilterDataReceived = null;
        // 上层业务自定义数据回调函数定义
        public static void OnRecvUserFilterDataCallBack(int userId, IntPtr buf, int len, int userValue)
        {

        }

        public static OnRecvUserTextMsg_Received OnRecvUserTextMsgReceived = null;
        // 收到用户文字聊天通信数据回调函数定义
        public static void OnRecvUserTextMsgCallBack(int roomId, int srcUserId, int tarUserId, bool bSecret, string textMessage, int len, int userValue)
        {

        }

        public static OnTransBuffer_Received OnTransBufferReceived = null;
        // 透明通道数据回调函数定义
        public static void OnTransBufferCallBack(int dwUserId, IntPtr lpBuf, int dwLen, int lpUserValue)
        {

        }

        public static OnTransBufferEx_Received OnTransBufferExReceived = null;
        // 透明通道数据扩展回调函数定义
        public static void OnTransBufferExCallBack(int dwUserId, IntPtr lpBuf, int dwLen, int wParam, int lParam, int dwTaskId, int lpUserValue)
        {

        }

        public static OnTransFile_Received OnTransFileReceived = null;
        // 文件传输回调函数定义
        public static void OnTransFileCallBack(int dwUserId, string lpFileName, string lpTempFilePath, int dwFileLength, int wParam, int lParam, int dwTaskId, int lpUserValue)
        {

        }

        public static OnObjectEventNotifyCallBack OnObjectEventNotify;
        private static void onObjectEventNotifyCallBack(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue)
        {
            if (OnObjectEventNotify != null)
            {
                OnObjectEventNotify(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, strParam, lpUserValue);
            }
        }

    }
}
