using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ANYCHATAPI;

namespace AnyChatBussiness
{
    public partial class MainForm : Form
    {
        //用户登录成功回调函数
        public static SystemSettingServer.OnUserLoginAction_Received UserLoginActionReceived_main = null;
        // 用户申请进入房间回调函数
        public static SystemSettingServer.OnPrepareEnterRoom_Received OnPrepareEnterRoom_Received_main = null;
        //用户进入房间回调函数定义
        public static SystemSettingServer.OnUserEnterRoomAction_Received OnUserEnterRoomAction_Received_main = null;
        // 用户离开房间回调函数定义
        public static SystemSettingServer.OnUserLeaveRoomAction_Received OnUserLeaveRoomAction_Received_main = null;
        // 用户注销回调函数定义  
        public static SystemSettingServer.OnUserLogoutAction_Received OnUserLogoutAction_Received_main = null;
        // 服务器应用程序消息回调函数定义
        public static SystemSettingServer.OnServerAppMessage_Received OnServerAppMessage_Received_main = null;

        public MainForm()
        {
            InitializeComponent();

        }

        // 服务器应用程序消息回调函数定义
        void OnServerAppMessageCallBack(int msg, int userValue)
        {
            OnServerAppMessage_Received_main = new SystemSettingServer.OnServerAppMessage_Received(OnServerAppMessageCallBack_main);
            this.rtb_message.Invoke(OnServerAppMessage_Received_main, msg, userValue);
        }

        // 服务器应用程序消息回调函数定义
        void OnServerAppMessageCallBack_main(int msg, int userValue)
        {
            this.rtb_message.AppendText("服务器应用程序消息:OnServerAppMessage(" + "msg:" + msg.ToString() + ",userValue:" + userValue.ToString() + ")\n");
        }

        // 用户登录成功回调函数
        void OnUserLoginAction_CallBack(int userId, string userName, int level, string addr, int userValue)
        {
            UserLoginActionReceived_main = new SystemSettingServer.OnUserLoginAction_Received(OnUserLoginAction_CallBack_main);
            rtb_message.Invoke(UserLoginActionReceived_main, userId, userName, level, addr, userValue);
        }

        // 用户登录成功回调委托主线程操作界面的函数定义
        void OnUserLoginAction_CallBack_main(int userId, string userName, int level, string addr, int userValue)
        {
            this.rtb_message.AppendText("用户登录成功:OnUserLoginAction(" + "userId:" + userId.ToString() + ",userName:" + userName.ToString()
                 + ",level:" + level.ToString() + ",addr:" + addr + ",userValue:" + userValue.ToString() + ")\n");
        }

        // 用户申请进入房间回调函数定义
        int OnPrepareEnterRoomCallBack(int userId, int roomId, string roomName, string password, int userValue)
        {
            OnPrepareEnterRoom_Received_main = new SystemSettingServer.OnPrepareEnterRoom_Received(OnPrepareEnterRoomCallBack_main);
            this.rtb_message.Invoke(OnPrepareEnterRoom_Received_main, userId, roomId, roomName, password, userValue);
            return 0;
        }

        // 用户申请进入房间回调函数定义
        int OnPrepareEnterRoomCallBack_main(int userId, int roomId, string roomName, string password, int userValue)
        {
            this.rtb_message.AppendText("用户申请进入房间:OnPrepareEnterRoom(" + "userId:" + userId.ToString() + ",roomId:" + roomId.ToString()
                 + ",roomName:" + roomName.ToString() + ")\n");
            return 0;
        }

        //用户进入房间回调函数定义
        void OnUserEnterRoomActionCallBack(int userId, int roomId, int userValue)
        {
            OnUserEnterRoomAction_Received_main = new SystemSettingServer.OnUserEnterRoomAction_Received(OnUserEnterRoomActionCallBack_main);
            this.rtb_message.Invoke(OnUserEnterRoomAction_Received_main, userId, roomId, userValue);
        }

        //用户进入房间回调函数定义
        void OnUserEnterRoomActionCallBack_main(int userId, int roomId, int userValue)
        {
            this.rtb_message.AppendText("用户进入房间:OnUserEnterRoomAction(" + "userId:" + userId.ToString() + ",roomId:" + roomId.ToString() + ",userValue:" + userValue.ToString() + ")\n");
        }

        // 用户离开房间回调函数定义
        void OnUserLeaveRoomActionCallBack(int userId, int roomId, int userValue)
        {
            OnUserLeaveRoomAction_Received_main = new SystemSettingServer.OnUserLeaveRoomAction_Received(OnUserLeaveRoomActionCallBack_main);
            this.rtb_message.Invoke(OnUserLeaveRoomAction_Received_main,userId,roomId,userValue);
        }

        // 用户离开房间回调函数定义
        void OnUserLeaveRoomActionCallBack_main(int userId, int roomId, int userValue)
        {
            this.rtb_message.AppendText("用户离开房间:OnUserLeaveRoomAction(" + "userId:" + userId.ToString() + ",roomId:" + roomId.ToString()
     + ",userValue:" + userValue.ToString() + ")\n");
        }

        // 用户注销回调函数定义  
        void OnUserLogoutActionCallBack(int userId, int userValue)
        {
            OnUserLogoutAction_Received_main = new SystemSettingServer.OnUserLogoutAction_Received(OnUserLogoutActionCallBack_main);
            this.rtb_message.Invoke(OnUserLogoutAction_Received_main, userId, userValue);
        }

        // 用户注销回调函数定义  
        void OnUserLogoutActionCallBack_main(int userId, int userValue)
        {
            this.rtb_message.AppendText("用户注销:OnUserLogoutAction(" + "userId:" + userId.ToString() + ",userValue:" + userValue.ToString() + ")\n");
        }

        //窗体加载
        private void MainForm_Load(object sender, EventArgs e)
        {
            // 服务器应用程序消息回调函数定义
            SystemSettingServer.OnServerAppMessageReceived = new SystemSettingServer.OnServerAppMessage_Received(OnServerAppMessageCallBack);
            //用户登录成功回调函数
            SystemSettingServer.OnUserLoginActionReceived = new SystemSettingServer.OnUserLoginAction_Received(OnUserLoginAction_CallBack);
            //用户登录成功回调函数
            SystemSettingServer.OnPrepareEnterRoomReceived = new SystemSettingServer.OnPrepareEnterRoom_Received(OnPrepareEnterRoomCallBack);
            //用户进入房间回调函数定义
            SystemSettingServer.OnUserEnterRoomActionReceived = new SystemSettingServer.OnUserEnterRoomAction_Received(OnUserEnterRoomActionCallBack);
            // 用户离开房间回调函数定义
            SystemSettingServer.OnUserLeaveRoomActionReceived = new SystemSettingServer.OnUserLeaveRoomAction_Received(OnUserLeaveRoomActionCallBack);
            // 用户注销回调函数定义 
            SystemSettingServer.OnUserLogoutActionReceived = new SystemSettingServer.OnUserLogoutAction_Received(OnUserLogoutActionCallBack);

            SystemSettingServer.Init();

            AnyChatServerSDK.BRAS_InitSDK(0);

            int mainVer = -1;
            int subVer = -1;
            StringBuilder buildertime = new StringBuilder(100);
            AnyChatServerSDK.BRAS_GetSDKVersion(ref mainVer, ref subVer, buildertime, 100);
            rtb_message.AppendText("AnyChat Sever SDK Version:" + mainVer + "." + subVer + "  (" + buildertime.ToString() + ")\n");
        }
    }
}
