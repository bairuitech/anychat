using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ANYCHATAPI;
using BusinessObject;

namespace AnyChatServer
{
    public partial class frmMain : Form
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
        public static SystemSettingServer.OnUserLogoutActionEx_Received OnUserLogoutActionEx_Received_main = null;
        // 服务器应用程序消息回调函数定义
        public static SystemSettingServer.OnServerAppMessageEx_Received OnServerAppMessageEx_Received_main = null;

        public frmMain()
        {
            InitializeComponent();

        }

        // 服务器应用程序消息回调函数定义
        void OnServerAppMessageExCallBack(int msg, int wParam, int lParam, int userValue)
        {
            OnServerAppMessageEx_Received_main = new SystemSettingServer.OnServerAppMessageEx_Received(OnServerAppMessageExCallBack_main);
            this.rtb_message.Invoke(OnServerAppMessageEx_Received_main, msg, wParam, lParam, userValue);
        }

        // 服务器应用程序消息回调函数定义
        void OnServerAppMessageExCallBack_main(int msg, int wParam, int lParam, int userValue)
        {
            if(msg == ANYCHATAPI.AnyChatServerSDK.BRAS_MESSAGE_CORESERVERCONN)
            {
                if (wParam == 0)
                {
                    this.rtb_message.AppendText("与AnyChat核心服务器连接成功\n");
                    initBusinessQueue();
                }
                else
                    this.rtb_message.AppendText("与AnyChat核心服务器连接失败(errorcode:" + wParam.ToString() + ")\n");
            }
            else if(msg == ANYCHATAPI.AnyChatServerSDK.BRAS_MESSAGE_RECORDSERVERCONN)
            {
                if (wParam == 0)
                    this.rtb_message.AppendText("与AnyChat录像服务器连接成功(serverid:" + lParam.ToString() + ")\n");
                else
                    this.rtb_message.AppendText("与AnyChat录像服务器连接失败(errorcode:" + wParam.ToString() + ")\n");
            }
            else
               this.rtb_message.AppendText("服务器应用程序消息:OnServerAppMessageEx(" + "msg:" + msg.ToString() + ",wParam:" + wParam.ToString() + ",lParam:" + lParam.ToString() + ")\n");
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

            showOnlineUserCount();
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
        void OnUserLogoutActionExCallBack(int userId, int errorcode, int userValue)
        {
            OnUserLogoutActionEx_Received_main = new SystemSettingServer.OnUserLogoutActionEx_Received(OnUserLogoutActionExCallBack_main);
            this.rtb_message.Invoke(OnUserLogoutActionEx_Received_main, userId, errorcode, userValue);
        }

        // 用户注销回调函数定义  
        void OnUserLogoutActionExCallBack_main(int userId, int errorcode, int userValue)
        {
            this.rtb_message.AppendText("用户注销:OnUserLogoutAction(" + "userId:" + userId.ToString() + ",errorcode:" + errorcode.ToString() + ")\n");
            showOnlineUserCount();
        }

        /// <summary>
        /// 业务对象事件通知回调定义
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwEventType"></param>
        /// <param name="dwParam1"></param>
        /// <param name="dwParam2"></param>
        /// <param name="dwParam3"></param>
        /// <param name="dwParam4"></param>
        /// <param name="strParam"></param>
        /// <param name="lpUserValue"></param>
        public void OnObjectEventNotify(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue)
        {
            switch (dwEventType)
            {
                default:
                    break;

            }
        }


        //窗体加载
        private void MainForm_Load(object sender, EventArgs e)
        {
            try
            {

                // 服务器应用程序消息回调函数定义
                SystemSettingServer.OnServerAppMessageExReceived = new SystemSettingServer.OnServerAppMessageEx_Received(OnServerAppMessageExCallBack);
                //用户登录成功回调函数
                SystemSettingServer.OnUserLoginActionReceived = new SystemSettingServer.OnUserLoginAction_Received(OnUserLoginAction_CallBack);
                //用户准备进入房间回调函数
                SystemSettingServer.OnPrepareEnterRoomReceived = new SystemSettingServer.OnPrepareEnterRoom_Received(OnPrepareEnterRoomCallBack);
                //用户进入房间回调函数定义
                SystemSettingServer.OnUserEnterRoomActionReceived = new SystemSettingServer.OnUserEnterRoomAction_Received(OnUserEnterRoomActionCallBack);
                // 用户离开房间回调函数定义
                SystemSettingServer.OnUserLeaveRoomActionReceived = new SystemSettingServer.OnUserLeaveRoomAction_Received(OnUserLeaveRoomActionCallBack);
                // 用户注销回调函数定义 
                SystemSettingServer.OnUserLogoutActionExReceived = new SystemSettingServer.OnUserLogoutActionEx_Received(OnUserLogoutActionExCallBack);
                //业务对象消息通知回调函数定义
                SystemSettingServer.OnObjectEventNotify = new SystemSettingServer.OnObjectEventNotifyCallBack(OnObjectEventNotify);

                SystemSettingServer.Init(this.Handle);

                AnyChatServerSDK.BRAS_InitSDK(0);

                int mainVer = -1;
                int subVer = -1;
                StringBuilder buildertime = new StringBuilder(100);
                AnyChatServerSDK.BRAS_GetSDKVersion(ref mainVer, ref subVer, buildertime, 100);
                rtb_message.AppendText("AnyChat Sever SDK Version:" + mainVer + "." + subVer + "  (" + buildertime.ToString() + ")\n");
            }
            catch (Exception ex)
            {
                Log.SetLog("OnServerAppMessageExCallBack                 " + ex.Message.ToString());
                rtb_message.AppendText(ex.Message.ToString() + "\n");
            }

        }

        /// <summary>
        /// 创建营业厅
        /// </summary>
        /// <param name="areaID">营业厅编号</param>
        /// <param name="areaName">营业厅名称</param>
        /// <param name="areaDesc">营业厅描述</param>
        /// <returns></returns>
        private int createArea(AreaInfo areaInfo)
        {
            int retVal = 0;

            retVal = AnyChatServerSDK.BRAS_ObjectControl(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_AREA, areaInfo.AreaID, AnyChatServerSDK.ANYCHAT_OBJECT_CTRL_CREATE, 0, 0, 0, 0, "");

            retVal = AnyChatServerSDK.BRAS_ObjectSetValue(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_AREA, areaInfo.AreaID, AnyChatServerSDK.ANYCHAT_OBJECT_INFO_NAME, areaInfo.AreaName, areaInfo.AreaName.ToCharArray().Length);

            retVal = AnyChatServerSDK.BRAS_ObjectSetValue(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_AREA, areaInfo.AreaID, AnyChatServerSDK.ANYCHAT_OBJECT_INFO_DESCRIPTION, areaInfo.AreaDescription, areaInfo.AreaDescription.ToCharArray().Length);

            return retVal;
        }

        /// <summary>
        /// 创建队列
        /// </summary>
        /// <param name="queueInfo"></param>
        /// <returns></returns>
        private int createQueue(QueueInfo queueInfo)
        {
            int retVal = 0;

            retVal = AnyChatServerSDK.BRAS_ObjectControl(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueInfo.QueueID, AnyChatServerSDK.ANYCHAT_OBJECT_CTRL_CREATE, queueInfo.AreaID, 0, 0, 0, "");

            retVal = AnyChatServerSDK.BRAS_ObjectSetValue(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueInfo.QueueID, AnyChatServerSDK.ANYCHAT_OBJECT_INFO_NAME, queueInfo.QueueName, queueInfo.QueueName.ToCharArray().Length);

            retVal = AnyChatServerSDK.BRAS_ObjectSetValue(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueInfo.QueueID, AnyChatServerSDK.ANYCHAT_OBJECT_INFO_DESCRIPTION, queueInfo.QueueDescription, queueInfo.QueueDescription.ToCharArray().Length);

            int queuePriority = queueInfo.QueuePriority;
            retVal = AnyChatServerSDK.BRAS_ObjectSetValue(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueInfo.QueueID, AnyChatServerSDK.ANYCHAT_OBJECT_INFO_PRIORITY, ref queuePriority, sizeof(int));

            int businessType = (int)queueInfo.businessType;
            retVal = AnyChatServerSDK.BRAS_ObjectSetValue(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueInfo.QueueID, AnyChatServerSDK.ANYCHAT_OBJECT_INFO_ATTRIBUTE, ref businessType, sizeof(int));

            int intTag = queueInfo.intTag;
            retVal = AnyChatServerSDK.BRAS_ObjectSetValue(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueInfo.QueueID, AnyChatServerSDK.ANYCHAT_OBJECT_INFO_INTTAG, ref intTag, sizeof(int));

            if (!string.IsNullOrEmpty(queueInfo.stringTag))
            {
                retVal = AnyChatServerSDK.BRAS_ObjectSetValue(AnyChatServerSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueInfo.QueueID, AnyChatServerSDK.ANYCHAT_OBJECT_INFO_STRINGTAG, queueInfo.stringTag, queueInfo.stringTag.ToCharArray().Length);

            }

            return retVal;

        }


        /// <summary>
        /// 初始化智能排队数据
        /// </summary>
        private void initBusinessQueue()
        {
            AreaInfo areaInfo = new AreaInfo();
            areaInfo.AreaID = 10001;
            areaInfo.AreaName = "科韵路营业厅";
            areaInfo.AreaDescription = "位于广州市科韵路，服务超级棒！";
            createArea(areaInfo);

            QueueInfo queueInfo = new QueueInfo();
            queueInfo.QueueID = 101;
            queueInfo.QueueName = "个人业务队列";
            queueInfo.QueueDescription = "办理开户、挂失、转帐业务";
            queueInfo.businessType = BusinessType.PersonalBusiness;
            queueInfo.QueuePriority = 0;
            queueInfo.intTag = 2;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            queueInfo.QueueID = 102;
            queueInfo.QueueName = "个人业务队列(VIP)";
            queueInfo.QueueDescription = "办理开户、挂失、转帐业务";
            queueInfo.businessType = BusinessType.PersonalBusiness;
            queueInfo.QueuePriority = 10;
            queueInfo.intTag = 2;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            queueInfo.QueueID = 103;
            queueInfo.QueueName = "对公业务队列";
            queueInfo.QueueDescription = "办理支票、回单、基本户业务";
            queueInfo.businessType = BusinessType.CompanyBusiness;
            queueInfo.QueuePriority = 0;
            queueInfo.intTag = 3;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);


            areaInfo.AreaID = 10002;
            areaInfo.AreaName = "天河路营业厅";
            areaInfo.AreaDescription = "七星级旗舰店，高端客户首选！";
            createArea(areaInfo);

            queueInfo.QueueID = 201;
            queueInfo.QueueName = "投资理财业务队列";
            queueInfo.QueueDescription = "办理基金、理财产品、贵金属业务";
            queueInfo.businessType = BusinessType.PersonalBusiness;
            queueInfo.QueuePriority = 0;
            queueInfo.intTag = 2;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            queueInfo.QueueID = 202;
            queueInfo.QueueName = "商业贷款业务队列";
            queueInfo.QueueDescription = "办理房贷、车贷业务";
            queueInfo.businessType = BusinessType.PersonalBusiness;
            queueInfo.QueuePriority = 10;
            queueInfo.intTag = 3;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);


            this.rtb_message.AppendText("成功初化始智能排队业务数据\n");

        }

        /// <summary>
        /// 显示在线用户数量
        /// </summary>
        private void showOnlineUserCount()
        {
            int onlineUsersCount = 0;
            AnyChatServerSDK.BRAS_GetOnlineUsers(-1, null, ref onlineUsersCount);
            lbl_onlineUserCount.Text = "在线用户数：" + onlineUsersCount;
        }
    }
}
