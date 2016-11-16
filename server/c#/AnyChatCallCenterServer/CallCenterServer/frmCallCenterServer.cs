using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ANYCHATAPI;
using BusinessObject;
using System.IO;
using System.Runtime.InteropServices;


namespace QueueServer
{
    public partial class frmCallCenterServer : Form
    {
        #region 构造函数

        public frmCallCenterServer()
        {
            InitializeComponent();
        }

        #endregion

        #region 定义

        /// <summary>
        /// 用户对象集合
        /// </summary>
        List<UserInfo> users = new List<UserInfo>();
        /// <summary>

        #endregion

        #region 回调函数

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

        string[] str;                       //用户信息集(业务服务器在线列表显示)

        // 服务器应用程序消息回调函数定义
        void OnServerAppMessageExCallBack(int msg, int wParam, int lParam, int userValue)
        {
            try
            {
                OnServerAppMessageEx_Received_main = new SystemSettingServer.OnServerAppMessageEx_Received(OnServerAppMessageExCallBack_main);
                this.rtb_message.Invoke(OnServerAppMessageEx_Received_main, msg, wParam, lParam, userValue);
            }
            catch (Exception ex)
            {
                Log.SetLog("OnServerAppMessageExCallBack                 " + ex.Message.ToString());
            }
        }
        // 服务器应用程序消息回调函数定义
        void OnServerAppMessageExCallBack_main(int msg, int wParam, int lParam, int userValue)
        {
            try
            {
                if (msg == ANYCHATAPI.AnyChatServerSDK.BRAS_MESSAGE_CORESERVERCONN)
                {
                    if (wParam == 0)
                    {
                        //显示版本
                        string version = GetVersion();
                        lb_version.Text = "与AnyChat核心服务器连接成功";
                        lb_version.ForeColor = Color.Green;
                        this.rtb_message.AppendText("与AnyChat核心服务器连接成功\n");

                        initBusinessQueue();

                    }
                    else
                    {
                        lb_version.Text = "与AnyChat核心服务器连接失败";
                        lb_version.ForeColor = Color.Red;
                        this.rtb_message.AppendText("与AnyChat核心服务器连接失败(errorcode:" + wParam.ToString() + ")\n");
                    }
                    Log.SetLog(lb_version.Text);
                    //清空在线用户列表中的项
                    lv_onlineUsers.Items.Clear();
                }
                else if (msg == ANYCHATAPI.AnyChatServerSDK.BRAS_MESSAGE_RECORDSERVERCONN)
                {
                    if (wParam == 0)
                        this.rtb_message.AppendText("与AnyChat录像服务器连接成功(serverid:" + lParam.ToString() + ")\n");
                    else
                        this.rtb_message.AppendText("与AnyChat录像服务器连接失败(errorcode:" + wParam.ToString() + ")\n");
                }
                else
                    this.rtb_message.AppendText("服务器应用程序消息:OnServerAppMessageEx(" + "msg:" + msg.ToString() + ",wParam:" + wParam.ToString() + ",lParam:" + lParam.ToString() + ")\n");

                rtb_message.Focus();
                rtb_message.SelectionStart = rtb_message.TextLength;
            }
            catch (Exception ex)
            {
                Log.SetLog("OnServerAppMessageExCallBack         服务器应用程序消息" + ex.Message.ToString());
            }
        }

        // 用户登录成功回调函数
        void OnUserLoginAction_CallBack(int userId, string userName, int level, string addr, int userValue)
        {
            try
            {
                 // 添加用户分组
                int iGroupId = 1;
                AnyChatServerSDK.BRAS_UserInfoControl(userId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_ADDGROUP, iGroupId, 0, "我的好友");
                iGroupId= 2;
                AnyChatServerSDK.BRAS_UserInfoControl(userId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_ADDGROUP, iGroupId, 0, "在线游客");
                // 将当前所有在线用户添加为自己的好友
                foreach (UserInfo userInfo in users)
                {
                    int iUserId = userInfo.Id;
                    AnyChatServerSDK.BRAS_UserInfoControl(userId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_ADDFRIEND, iUserId, 0, "");
                }
                // 设置好友与分组的关系（即好友属于哪一个分组）
                iGroupId = 1;
                foreach (UserInfo userInfo in users)
                {
                    int iUserId = userInfo.Id;
                    iGroupId = (iUserId > 0) ? 1 : 2;		// 游客密码为空，userid由核心服务器分配，为负数
                    AnyChatServerSDK.BRAS_UserInfoControl(userId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_SETGROUPRELATION, iGroupId, iUserId, "");
                }
                // 设置当前用户信息（用户资料，客户端可以通过API：BRAC_GetUserInfo来获取这些信息）
                int iInfoId = 1;	// InfoId由业务层自己定义
                AnyChatServerSDK.BRAS_SetUserInfo(userId, iInfoId, userName, 0);
                iInfoId = 2;	// InfoId由业务层自己定义
                AnyChatServerSDK.BRAS_SetUserInfo(userId, iInfoId, addr, 0);
                iInfoId = 3;	// InfoId由业务层自己定义
                AnyChatServerSDK.BRAS_SetUserInfo(userId, iInfoId, "我的签名", 0);
                iInfoId = 4;	// InfoId由业务层自己定义
                AnyChatServerSDK.BRAS_SetUserInfo(userId, iInfoId, Convert.ToString(userId%10 + 1), 0);// 随机分配一个图像ID
                // 将本地用户添加为其它用户的好友列表中
                foreach (UserInfo userInfo in users)
                {
                    int otherUserid = userInfo.Id;
                    AnyChatServerSDK.BRAS_UserInfoControl(otherUserid, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_ADDFRIEND, userId, 0, "");
                    // 关联好友分组
			        iGroupId = (userId > 0) ? 1 : 2;
                    AnyChatServerSDK.BRAS_UserInfoControl(otherUserid, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_SETGROUPRELATION, iGroupId, userId, "");
                    // 下发同步指令，将新设置的好友同步给客户端
                     AnyChatServerSDK.BRAS_UserInfoControl(otherUserid, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_SYNCDATA, 0, 0, "");
                }
                // 下发同步指令，将前面设置的资料同步给当前客户端
                AnyChatServerSDK.BRAS_UserInfoControl(userId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_SYNCDATA, 0, 0, "");
                //加入用户对象集合
                UserInfo mode = new UserInfo();
                mode.Id = userId;
                mode.Name = userName;
                mode.Ip = addr;
                users.Add(mode);

                str = new string[] { userId.ToString(), userName, "游客", addr.ToString(), DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") };
                UserLoginActionReceived_main = new SystemSettingServer.OnUserLoginAction_Received(OnUserLoginAction_CallBack_main);
                rtb_message.Invoke(UserLoginActionReceived_main, userId, userName, level, addr, userValue);
            }
            catch (Exception ex)
            {
                Log.SetLog("OnUserLoginAction_CallBack             用户登录成功错误：" + ex.Message.ToString());
            }
        }
        // 用户登录成功回调委托主线程操作界面的函数定义
        void OnUserLoginAction_CallBack_main(int userId, string userName, int level, string addr, int userValue)
        {
            try
            {
                lv_onlineUsers.Items.Add(new ListViewItem(str));
                this.rtb_message.AppendText("用户登录成功:OnUserLoginAction(" + "userId:" + userId.ToString() + ",userName:" + userName.ToString()
                     + ",level:" + level.ToString() + ",addr:" + addr + ",userValue:" + userValue.ToString() + ")\n");
                rtb_message.Focus();
                rtb_message.SelectionStart = rtb_message.TextLength;

                showOnlineUserCount();
            }
            catch (Exception ex)
            {
                Log.SetLog("OnUserLoginAction_CallBack_main         用户登录成功错误：" + ex.Message.ToString());
            }
        }

        // 用户申请进入房间回调函数定义
        int OnPrepareEnterRoomCallBack(int userId, int roomId, string roomName, string password, int userValue)
        {
            try
            {
                OnPrepareEnterRoom_Received_main = new SystemSettingServer.OnPrepareEnterRoom_Received(OnPrepareEnterRoomCallBack_main);
                this.rtb_message.Invoke(OnPrepareEnterRoom_Received_main, userId, roomId, roomName, password, userValue);
            }
            catch (Exception ex)
            {
                Log.SetLog("OnPrepareEnterRoomCallBack             用户申请进入房间回调函数定义，错误：" + ex.Message.ToString());
            }
            return 0;
        }
        // 用户申请进入房间回调函数定义
        int OnPrepareEnterRoomCallBack_main(int userId, int roomId, string roomName, string password, int userValue)
        {
            try
            {
                this.rtb_message.AppendText("用户申请进入房间:OnPrepareEnterRoom(" + "userId:" + userId.ToString() + ",roomId:" + roomId.ToString()
             + ",roomName:" + roomName.ToString() + ")\n");
                rtb_message.Focus();
                rtb_message.SelectionStart = rtb_message.TextLength;
            }
            catch (Exception ex)
            {
                Log.SetLog("OnPrepareEnterRoomCallBack_main            用户申请进入房间回调函数定义，错误：" + ex.Message.ToString());
            }
            return 0;
        }

        //用户进入房间回调函数定义
        void OnUserEnterRoomActionCallBack(int userId, int roomId, int userValue)
        {
            try
            {
                OnUserEnterRoomAction_Received_main = new SystemSettingServer.OnUserEnterRoomAction_Received(OnUserEnterRoomActionCallBack_main);
                this.rtb_message.Invoke(OnUserEnterRoomAction_Received_main, userId, roomId, userValue);
            }
            catch (Exception ex)
            {
                Log.SetLog("OnUserEnterRoomActionCallBack              用户进入房间回调函数定义,错误：" + ex.Message.ToString());
            }
        }
        //用户进入房间回调函数定义
        void OnUserEnterRoomActionCallBack_main(int userId, int roomId, int userValue)
        {
            try
            {
            }
            catch (Exception ex)
            {
                Log.SetLog("OnUserEnterRoomActionCallBack_main         用户进入房间回调函数，错误：" + ex.Message.ToString());
            }
        }

        // 用户离开房间回调函数定义
        void OnUserLeaveRoomActionCallBack(int userId, int roomId, int userValue)
        {
          
                OnUserLeaveRoomAction_Received_main = new SystemSettingServer.OnUserLeaveRoomAction_Received(OnUserLeaveRoomActionCallBack_main);
                this.rtb_message.Invoke(OnUserLeaveRoomAction_Received_main, userId, roomId, userValue);
         
        }
        // 用户离开房间回调函数定义
        void OnUserLeaveRoomActionCallBack_main(int userId, int roomId, int userValue)
        {
            try
            {
                this.rtb_message.AppendText("用户离开房间:OnUserLeaveRoomAction(" + "userId:" + userId.ToString() + ",roomId:" + roomId.ToString()
 + ",userValue:" + userValue.ToString() + ")\n");
                rtb_message.Focus();
                rtb_message.SelectionStart = rtb_message.TextLength;
            }
            catch (Exception ex)
            {
                Log.SetLog("OnUserLeaveRoomActionCallBack_main         用户离开房间回调函数，错误：" + ex.Message.ToString());
            }
        }

        // 用户注销回调函数定义
        void OnUserLogoutActionExCallBack(int userId, int errorcode, int userValue)
        {
            try
            {
             
                //从用户对象集中移除
                foreach (UserInfo u in users)
                {
                    if (u.Id == userId)
                    {
                        users.Remove(u);
                        break;
                    }
                }
                // 核心服务器会通知其它用户（如果是好友），提示好友下线，不需要业务服务器干预
                OnUserLogoutActionEx_Received_main = new SystemSettingServer.OnUserLogoutActionEx_Received(OnUserLogoutActionExCallBack_main);
                this.rtb_message.Invoke(OnUserLogoutActionEx_Received_main, userId, errorcode, userValue);
            }
            catch (Exception ex)
            {
                Log.SetLog("OnUserLogoutActionCallBack         用户注销错误：" + ex.Message.ToString());
            }
        }
        // 用户注销回调函数定义  
        void OnUserLogoutActionExCallBack_main(int userId, int errorcode, int userValue)
        {
            try
            {
                //移除在线成员列表中的项
                foreach (ListViewItem item in lv_onlineUsers.Items)
                {
                    if (Convert.ToInt32(item.SubItems[0].Text) == userId)
                    {
                        lv_onlineUsers.Items.Remove(item);
                    }
                }
                this.rtb_message.AppendText("用户注销:OnUserLogoutAction(" + "userId:" + userId.ToString() + ",userValue:" + userValue.ToString() + ")\n");
                rtb_message.Focus();
                rtb_message.SelectionStart = rtb_message.TextLength;
                showOnlineUserCount();
            }
            catch (Exception ex)
            {
                Log.SetLog("OnUserLogoutActionCallBack_main            用户注销回调函数定义，错误：" + ex.Message.ToString());
            }
        }

        // 用户身份验证回调函数定义
        // 根据函数返回值决定是否验证身份成功，当返回0时，必须分配一个唯一的userid
        int uid = 1;
        int OnVerifyUserCallBack(string userName, string password, ref int userID, ref int userLevel, IntPtr nickName, int len, int userValue)
        {
            try
            {
                userID = uid;
                uid++;
            }
            catch (Exception ex)
            {
                Log.SetLog("OnVerifyUserCallBack       用户身份验证错误：" + ex.Message.ToString());
            }
            return 0;
        }

        // 收到用户文字聊天通信数据回调函数定义
        void OnRecvUserTextMsgCallBack(int roomId, int srcUserId, int tarUserId, bool bSecret, string textMessage, int len, int userValue)
        {

        }

        // 文件传输回调函数定义
        public void OnTransFileCallBack(int dwUserId, string lpFileName, string lpTempFilePath, int dwFileLength, int wParam, int lParam, int dwTaskId, int lpUserValue)
        {
        }
        public int OnVideoCall_Received(int dwEventType, int dwSrcUserId, int dwTarUserId, int dwErrorCode, int dwFlags, int dwParam, string lpUserStr, int lpUserValue)
        {
            return 0;
        }

        //透明通道回调函数
        public void TransBuffer_CallBack(int userId, IntPtr buf, int len, int userValue)
        {
                string str = Marshal.PtrToStringAnsi(buf);                                  //获取命令字符串
              
        }

        public void OnObjectEventNotify(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue)
        {
            switch (dwEventType)
            {
                default:
                    break;

            }
        }

        #endregion

        #region 初始化

        //窗体加载
        private void Server_Load(object sender, EventArgs e)
        {
            try
            {
                //初始化log日志文件
                if (File.Exists(Log.logPath))
                {
                    File.Delete(Log.logPath);
                }

                // 服务器应用程序消息回调函数定义
                SystemSettingServer.OnServerAppMessageExReceived = new SystemSettingServer.OnServerAppMessageEx_Received(OnServerAppMessageExCallBack);
                //用户登录成功回调函数
                SystemSettingServer.OnUserLoginActionReceived = new SystemSettingServer.OnUserLoginAction_Received(OnUserLoginAction_CallBack);
                //用户登录成功回调函数
                SystemSettingServer.OnPrepareEnterRoomReceived = new SystemSettingServer.OnPrepareEnterRoom_Received(OnPrepareEnterRoomCallBack);
                //用户进入房间回调函数定义
                SystemSettingServer.OnUserEnterRoomActionReceived = new SystemSettingServer.OnUserEnterRoomAction_Received(OnUserEnterRoomActionCallBack);
                // 用户离开房间回调函数定义
                SystemSettingServer.OnUserLeaveRoomActionReceived = new SystemSettingServer.OnUserLeaveRoomAction_Received(OnUserLeaveRoomActionCallBack);
                // 用户注销回调函数定义 
                SystemSettingServer.OnUserLogoutActionExReceived = new SystemSettingServer.OnUserLogoutActionEx_Received(OnUserLogoutActionExCallBack);
                // 透明通道数据回调函数定义
                SystemSettingServer.OnTransBufferReceived = new SystemSettingServer.OnTransBuffer_Received(TransBuffer_CallBack);
                // 用户身份验证回调函数定义
                SystemSettingServer.OnVerifyUserReceived = new SystemSettingServer.OnVerifyUser_Received(OnVerifyUserCallBack);
                // 收到用户文字聊天通信数据回调函数定义
                SystemSettingServer.OnRecvUserTextMsgReceived = new SystemSettingServer.OnRecvUserTextMsg_Received(OnRecvUserTextMsgCallBack);
                //文件传输回调函数
                SystemSettingServer.OnTransFileReceived = new SystemSettingServer.OnTransFile_Received(OnTransFileCallBack);
                //视频呼叫回调函数
                SystemSettingServer.OnVideoCallReceived = new SystemSettingServer.OnVideoCall_Received(OnVideoCall_Received);
                SystemSettingServer.OnObjectEventNotify = new SystemSettingServer.OnObjectEventNotifyCallBack(OnObjectEventNotify);

                lb_version.Text = "与AnyChat核心服务器连接失败";
                lb_version.ForeColor = Color.Red;

                // 显示版本信息
                this.rtb_message.AppendText(GetVersion()+"\n");

                //初始化SDK
                SystemSettingServer.Init(this.Handle);
                AnyChatServerSDK.BRAS_InitSDK(0);

            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatServer.Server.Server_Load       Server_Load：" + ex.Message.ToString());
            }
        }

        //获取版本字符串
        private string GetVersion()
        {
            string version = "";
            try
            {
                int mainVer = -1;
                int subVer = -1;
                StringBuilder strbl = new StringBuilder(100);
                AnyChatServerSDK.BRAS_GetSDKVersion(ref mainVer, ref subVer, strbl, 100);
                version = "AnyChat Server SDK Version:" + mainVer + "." + subVer + "  (" + strbl.ToString() + ")";
            }
            catch (Exception ex)
            {
                Log.SetLog("GetVersion         获取版本错误：" + ex.Message.ToString());
            }
            return version;
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
            queueInfo.QueueName = "现金业务队列";
            queueInfo.QueueDescription = "办理开户、提现、转帐业务";
            queueInfo.businessType = BusinessType.CashBusiness;
            queueInfo.QueuePriority = 0;
            queueInfo.intTag = 2;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            queueInfo.QueueID = 102;
            queueInfo.QueueName = "现金业务队列(VIP)";
            queueInfo.QueueDescription = "办理开户、提现、转帐业务";
            queueInfo.businessType = BusinessType.CashBusiness;
            queueInfo.QueuePriority = 10;
            queueInfo.intTag = 2;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            queueInfo.QueueID = 103;
            queueInfo.QueueName = "投资理财业务队列";
            queueInfo.QueueDescription = "办理投资、理财业务";
            queueInfo.businessType = BusinessType.FinancialBusiness;
            queueInfo.QueuePriority = 0;
            queueInfo.intTag = 3;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            queueInfo.QueueID = 104;
            queueInfo.QueueName = "投资理财业务队列(VIP)";
            queueInfo.QueueDescription = "办理投资、理财业务";
            queueInfo.businessType = BusinessType.FinancialBusiness;
            queueInfo.QueuePriority = 8;
            queueInfo.intTag = 3;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            areaInfo.AreaID = 10002;
            areaInfo.AreaName = "天河路营业厅";
            areaInfo.AreaDescription = "七星级旗舰店，高端客户首选！";
            createArea(areaInfo);

            queueInfo.QueueID = 201;
            queueInfo.QueueName = "现金业务队列";
            queueInfo.QueueDescription = "办理开户、提现、转帐业务";
            queueInfo.businessType = BusinessType.CashBusiness;
            queueInfo.QueuePriority = 0;
            queueInfo.intTag = 2;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            queueInfo.QueueID = 202;
            queueInfo.QueueName = "投资理财业务队列(VIP)";
            queueInfo.QueueDescription = "办理投资、理财业务";
            queueInfo.businessType = BusinessType.FinancialBusiness;
            queueInfo.QueuePriority = 0;
            queueInfo.intTag = 2;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            queueInfo.QueueID = 203;
            queueInfo.QueueName = "现金业务队列(VIP)";
            queueInfo.QueueDescription = "办理开户、提现、转帐业务";
            queueInfo.businessType = BusinessType.CashBusiness;
            queueInfo.QueuePriority = 10;
            queueInfo.intTag = 3;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            queueInfo.QueueID = 204;
            queueInfo.QueueName = "理财业务队列(VIP)";
            queueInfo.QueueDescription = "办理投资、理财业务";
            queueInfo.businessType = BusinessType.FinancialBusiness;
            queueInfo.QueuePriority = 10;
            queueInfo.intTag = 3;
            queueInfo.AreaID = areaInfo.AreaID;
            createQueue(queueInfo);

            this.rtb_message.AppendText("成功初化始智能排队业务数据\n");

        }
        #endregion

        #region Help

        /// <summary>
        /// 发送透明通道
        /// </summary>
        /// <param name="tuserid">目标ID</param>
        /// <param name="cmd">指令ID</param>
        /// <param name="os">参数</param>
        /// <returns>调用结果</returns>
        internal static int TranBuff(int tuserid, int cmd, params ParamInfo[] os)
        {
            int ret = -1;
            try
            {
                string strCmd = CommandHelp.GenerateCommand(cmd, os);
                byte[] buff = Encoding.Default.GetBytes(strCmd);
                AnyChatServerSDK.BRAS_TransBuffer(tuserid, buff, buff.Length);
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatServer.Server.TranBuff       TranBuff：" + ex.Message.ToString());
            }
            return ret;
        }

        /// <summary>
        /// 根据ID获取用户对象
        /// </summary>
        private UserInfo GetUserInfoById(int id)
        {
            UserInfo mode = null;
            try
            {
                foreach (UserInfo u in users)
                {
                    if (u.Id == id)
                    {
                        mode = u;
                        break;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatServer.Server.GetUserInfoById       GetUserInfoById：" + ex.Message.ToString());
            }
            return mode;
        }
        #endregion

        private void lb_version_DoubleClick(object sender, EventArgs e)
        {
            //new frmTest().Show();
        }

        /// <summary>
        /// 显示在线用户数量
        /// </summary>
        private void showOnlineUserCount()
        {
            int onlineUsersCount = 0;
            AnyChatServerSDK.BRAS_GetOnlineUsers(-1, null, ref onlineUsersCount);
            gb_onlineEquipment.Text = "在线用户数：" + onlineUsersCount;
        }
    }
}
