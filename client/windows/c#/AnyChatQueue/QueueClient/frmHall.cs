using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using QueueHelp;
using ANYCHATAPI;
using System.Runtime.InteropServices;
using System.Media;
using System.Threading;

namespace QueueClient
{
    public partial class frmHall : Form
    {
        #region 变量定义

        int m_UserId = -1;
        string m_UserName = "";
        int intCallTimer = 0;
        private List<UserInfo> users = new List<UserInfo>();
        public const int AC_ERROR_VIDEOCALL_CANCEL = 100101;       ///  源用户主动放弃会话
        public const int AC_ERROR_VIDEOCALL_OFFLINE = 100102;      ///< 目标用户不在线
        public const int AC_ERROR_VIDEOCALL_BUSY = 100103;       ///< 目标用户忙
        public const int AC_ERROR_VIDEOCALL_REJECT = 100104;       ///< 目标用户拒绝会话
        public const int AC_ERROR_VIDEOCALL_TIMEOUT = 100105;       ///< 会话请求超时
        public const int AC_ERROR_VIDEOCALL_DISCONNECT = 100106;       ///< 网络断线
        public const int USERDATA_USERNAME = 1;       ///< 用户姓名
        public const int USERDATA_USERADRESSIP = 2;       ///< 用户地址
        public const int USER_OFFLINE = 0; ///< 用户离线                                                  ///
        public const int USER_ONLINE = 1; ///< 用户上线
        public bool bReleased = false;
        /// <summary>
        /// 当前会话
        /// </summary>
        private ConversationInfo ConversationMode = null;

        /// <summary>
        /// 用户身份标识
        /// </summary>
        public UserIdentityType m_userIdentity = UserIdentityType.Client;
        /// <summary>
        /// 身份优先级
        /// </summary>
        public int m_identityPriority = 10;

        /// <summary>
        /// 保存被隐藏的登录窗口
        /// </summary>
        public frmLogin m_loginForm = null;

        /// <summary>
        /// 当前的业务功能
        /// </summary>
        public BusinessFuncType currentBusinessFunc = BusinessFuncType.None;
        /// <summary>
        /// 当前被选择的营业厅
        /// </summary>
        public AreaInfo selectedArea = null;
        /// <summary>
        /// 当前被选择的队列
        /// </summary>
        public QueueInfo selectedQueue = null;
        /// <summary>
        /// 是否进入营业厅
        /// </summary>
        public bool isEnterArea = false;


        string replaceWaitingTime = string.Empty;
        string replaceTotalCount = string.Empty;
        string replaceQueuePosition = string.Empty;
        /// <summary>
        /// 进入队列后排队等待信息
        /// </summary>
        private string enterQueueWaitingMessage = "当前排队人数共：{0} 人  您现在排在第 {1} 位 " + Environment.NewLine +"已等待时间：{2}";

        private int mTargetUserId = 0;

        /// <summary>
        /// 营业厅列表
        /// </summary>
        private List<AreaInfo> areaList = new List<AreaInfo>();
        /// <summary>
        /// 队列列表
        /// </summary>
        private List<QueueInfo> queueList = new List<QueueInfo>();

        #endregion

        #region 构造函数

        public frmHall()
        {
            InitializeComponent();
        }

        public frmHall(int r_UserId, string r_UserName)
        {
            m_UserId = r_UserId;
            m_UserName = r_UserName;

            //this.loginForm = loginForm;
            InitializeComponent();
        }

        public frmHall(int r_UserId, string r_UserName, UserIdentityType r_userIdentityType, int r_identityPriority, frmLogin loginForm)
        {
            m_UserId = r_UserId;
            m_UserName = r_UserName;
            m_userIdentity = r_userIdentityType;
            m_identityPriority = r_identityPriority;

            //this.loginForm = loginForm;
            this.m_loginForm = loginForm;

            InitializeComponent();
        }

        #endregion

        #region 初始化及界面操作方法

        //窗体加载
        private void Hall_Load(object sender, EventArgs e)
        {

            SystemSetting.VideoCallEvent_Handler = new SystemSetting.VideoCallEventCallBack(VideoCallEvent_CallBack);
            SystemSetting.AnyChatObjectEvent_Handler = new SystemSetting.AnyChatObjectEventCallBack(ObjectEvent_CallBack);

            lbl_agent_remoteUser.Text = string.Empty;
        }

        //窗体关闭
        private void Hall_FormClosed(object sender, FormClosedEventArgs e)
        {

            AnyChatCoreSDK.Logout();
            AnyChatCoreSDK.Release();
            Application.Exit();
            bReleased = true;
        }

        /// <summary>
        /// 隐藏所有的Panel
        /// </summary>
        private void HideAllPanel()
        {
            panel_queue.Hide();
            panel_area.Hide();
            panel_call.Hide();
            panel_users.Hide();

            panel_userVedioCall.Hide();
            panel_agentVedioCall.Hide();

            panel_conversation.Hide();
            panel_waitingMessage.Hide();
        }


        /// <summary>
        /// 提示等待消息
        /// </summary>
        /// <param name="bit"></param>
        /// <param name="str"></param>

        private void ShowWaitingMessage(Bitmap bit, string str)
        {
            //pan_conversation.Hide();
            //pan_users.Hide();
            HideAllPanel();
            panel_waitingMessage.Dock = DockStyle.Fill;
            panel_waitingMessage.Show();
            picBox_waiting.Image = bit;
            lbl_waitingMessage.Text = str;
            //if (intCallTimer > 1)
            //    lb_call.Text += intCallTimer.ToString();
            lbl_waitingMessage.Tag = str;
            lbl_waitingTime.Text = string.Empty;

            picBox_waiting.Location = new Point(panel_waitingMessage.Width / 2 - (picBox_waiting.Width + lbl_waitingMessage.Width) / 2, panel_waitingMessage.Height / 2 - picBox_waiting.Height / 2 - 50 / 2);
            lbl_waitingMessage.Location = new Point(picBox_waiting.Location.X + picBox_waiting.Width, picBox_waiting.Location.Y + picBox_waiting.Height - lbl_waitingMessage.Height - 15);
            lbl_waitingTime.Location = new Point(picBox_waiting.Location.X + picBox_waiting.Width, picBox_waiting.Location.Y + picBox_waiting.Height - lbl_waitingTime.Height);

            //lbl_waitingMessage.Text = string.Empty;

        }

        /// <summary>
        /// 返回按钮是否显示
        /// </summary>
        /// <param name="isShow"></param>
        private void isShowReturnButton(bool isShow)
        {
            if (isShow)
                btn_return.Show();
            else
                btn_return.Hide();
        }

        private void Hall_Shown(object sender, EventArgs e)
        {
            InitClientObjectInfo(m_UserId, m_userIdentity, m_identityPriority);

            //HideAllPanel();

            InitAreaPanel();

        }

        /// <summary>
        /// 初始化客户端对象
        /// </summary>
        /// <param name="mSelfUserId">用户id</param>
        /// <param name="userIdentityType">用户身份类型</param>
        /// <param name="userPriority">用户优先级</param>
        public void InitClientObjectInfo(int mSelfUserId, UserIdentityType userIdentityType, int userPriority = 10)
        {
            //int userIdentity;
            int objectFlag = 0;
            switch (userIdentityType)
            {
                case UserIdentityType.Client:                    
                    objectFlag = AnyChatCoreSDK.ANYCHAT_OBJECT_FLAGS_CLIENT;
                    break;
                case UserIdentityType.Agent:                   
                    objectFlag = AnyChatCoreSDK.ANYCHAT_OBJECT_FLAGS_AGENT;
                    break;
                default:                    
                    objectFlag = AnyChatCoreSDK.ANYCHAT_OBJECT_FLAGS_CLIENT;
                    break;
            }

            //业务对象身份初始化
            AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_OBJECT_INITFLAGS, ref objectFlag, sizeof(int));
            //用户对象优先级
            AnyChatCoreSDK.BRAC_ObjectSetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_CLIENTUSER, mSelfUserId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_PRIORITY, ref userPriority, sizeof(int));
            //对象属性赋值
            int userAttribute = -1;
            AnyChatCoreSDK.BRAC_ObjectSetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_CLIENTUSER, mSelfUserId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_ATTRIBUTE, ref userAttribute, sizeof(int));

            //发送服务区域数据同步请求指令
            AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, AnyChatCoreSDK.ANYCHAT_INVALID_OBJECT_ID, AnyChatCoreSDK.ANYCHAT_OBJECT_CTRL_SYNCDATA,
                                            mSelfUserId, 0, 0, 0, string.Empty);

            ShowWaitingMessage(Properties.Resources._15, "正在进入营业厅，请稍候......");
        }

        private void btnStopService_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("你确定结束当前的视频服务吗？", "提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information, MessageBoxDefaultButton.Button2) == System.Windows.Forms.DialogResult.OK)
            {
                AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_FINISH, mTargetUserId, 0, 0, 0, ""); 	// 挂断
                //btn_return.Enabled = true;
            }
        }

        private void btnStartService_Click(object sender, EventArgs e)
        {
            //客服开始服务
            AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_CTRL_SERVICEREQUEST, 0, 0, 0, 0, "");

            btn_return.Enabled = false;
            btnStartService.Enabled = false;
            btnStopService.Enabled = true;
        }

        /// <summary>
        /// 显示坐席服务界面
        /// </summary>
        private void showAgentServiceFace()
        {
            HideAllPanel();

            panel_agentVedioCall.Dock = DockStyle.Fill;
            if (!panel_agentVedioCall.Visible) panel_agentVedioCall.Show();

            btnStopService.Enabled = false;
            btnStartService.Enabled = true;
            btn_return.Enabled = btnStartService.Enabled;
            if (!btnStartService.Enabled) btnStartService.Enabled = true;
            isShowReturnButton(true);

        }

        /// <summary>
        /// 显示客户视频界面
        /// </summary>
        private void showClientVideoFace()
        {
            HideAllPanel();

            panel_conversation.Dock = DockStyle.Fill;
            if (!panel_userVedioCall.Visible) panel_userVedioCall.Show();
            if (!panel_conversation.Visible) panel_conversation.Show();

        }

        /// <summary>
        /// 显示队列列表
        /// </summary>
        private void showQueueListFace()
        {
            HideAllPanel();
            lbl_tipMessage.Text = selectedArea.AreaName + " 队列列表";
            if (!panel_queue.Visible) panel_queue.Show();
            if (!btn_return.Visible) btn_return.Visible = true;
        }

        /// <summary>
        /// 移出提示界面中动态生成的按钮
        /// </summary>
        private void RemoveWaitingMessageButton()
        {
            foreach (Control c in panel_waitingMessage.Controls)
            {
                if (c.Tag != null)
                {
                    if (c.Tag.ToString() == "btn")
                    {
                        panel_waitingMessage.Controls.Remove(c);

                        break;
                    }
                }
            }
        }

        private void refreshAgentServiceInfo()
        {
            if (m_userIdentity == UserIdentityType.Agent)
            {
                //队列数量
                int queueCount = 0;
                AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, selectedArea.AreaID, AnyChatCoreSDK.ANYCHAT_AREA_INFO_QUEUECOUNT, ref queueCount);

                //队列总用户数
                int queuesUserCount = 0;
                AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, selectedArea.AreaID, AnyChatCoreSDK.ANYCHAT_AREA_INFO_QUEUEUSERCOUNT, ref queuesUserCount);

                //在营业厅未进入队列人数
                int atAreaUserCount = 0;
                AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, selectedArea.AreaID, AnyChatCoreSDK.ANYCHAT_AREA_INFO_GUESTCOUNT, ref atAreaUserCount);


                //累计服务的用户数
                int servicedUserCount = 0;
                AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_INFO_SERVICETOTALNUM, ref servicedUserCount);

                lbl_agent_queueNumber.Text = "当前服务的队列数量为： " + queueCount + " 个";
                lbl_agent_currentTotalUserCount.Text = "当前排队的用户总数为： " + queuesUserCount + " 人";
                lbl_agent_servicedUserCount.Text = "已服务人数为： " + servicedUserCount + " 人";
                lbl_agent_atAreaUserCount.Text = "未进入队列用户数为：" + atAreaUserCount + " 人";
            }
        }

        private void refreshServicedUserInfo(int userID)
        {
            int serviceUserID = 0;
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_INFO_SERVICEUSERID, ref serviceUserID);

            StringBuilder sbUserName = new StringBuilder(100);

            AnyChatCoreSDK.GetUserName(userID, sbUserName, 100);
            if (userID == -1)
            {
                lbl_agent_remoteUser.Text = string.Empty;
            }
            else
            {
                lbl_agent_remoteUser.Text = "当前服务用户ID：" + userID + "，用户名为：" + sbUserName.ToString();
            }
        }

        private void btn_return_Click(object sender, EventArgs e)
        {
            switch (currentBusinessFunc)
            {
                case BusinessFuncType.SelectAreaFunc:
                    //退出营业厅
                    int iAreaID = selectedArea.AreaID;
                    AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, iAreaID, AnyChatCoreSDK.ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, string.Empty);
                    ShowWaitingMessage(Properties.Resources._15, "正在退出营业厅，请稍候......");
                    break;

                case BusinessFuncType.SelectQueueFunc:
                    btnCancel_Click(sender, e);

                    break;

                case BusinessFuncType.ServiceUserFunc:
                    break;

                default:
                    this.Hide();
                    this.m_loginForm.Show();
                    break;
            }
        }

        private void panel_area_VisibleChanged(object sender, EventArgs e)
        {
            if (((Panel)sender).Visible) lbl_tipMessage.Text = "营业厅列表";
        }



        #endregion
        
        #region 视频呼叫业务实际处理

        //呼叫等待
        private void VideoCall_WaitCall_Handler()
        {
            try
            {
                intCallTimer = 60;
                ShowCallMessage(Properties.Resources._15, "呼叫请求中，等待用户响应...");
                //timer_call.Start();
                timer_call.Stop();//关闭计时器，确认状态
                Button btn_cancall = new Button();
                btn_cancall.Font = new Font("微软雅黑", 20);
                btn_cancall.Size = new Size(140, 50);
                btn_cancall.Location = new Point(panel_call.Width / 2 - btn_cancall.Width / 2, pic_call.Top + pic_call.Height + 30);
                btn_cancall.Text = "取消";
                btn_cancall.Tag = "btn";
                btn_cancall.BackColor = Color.Red;
                btn_cancall.ForeColor = Color.White;
                btn_cancall.Click += new EventHandler(btn_cancall_Click);
                panel_call.Controls.Add(btn_cancall);
                SoundPlayer Player = new SoundPlayer();
                Player.Stream = Properties.Resources.ring;
                Player.Play();
                Player.Dispose();
            }
            catch (Exception ex)
            {
                Log.SetLog("QueueClient.Hall.WaitCall       WaitCall：" + ex.Message.ToString());
            }
        }

        //单击取消呼叫
        void btn_cancall_Click(object sender, EventArgs e)
        {

            CanCall();

        }
        //取消呼叫
        private void CanCall()
        {

            //发送视频呼叫回复指令，dwErrcode=100101
            AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REPLY, ConversationMode.TuserId, AC_ERROR_VIDEOCALL_CANCEL, 0, 0, "");
            ConversationMode = null;
            InitFaceAfterEndCall(Properties.Resources._20, "已经取消呼叫");


            refreshServicedUserInfo(-1);

            showAgentServiceFace();

        }
        //接收到视频呼叫请求处理

        private void VideoCall_Request_Handler(int dwUserId, int dwParam, string lpUserStr)
        {

            if (this.WindowState == FormWindowState.Minimized)
                this.WindowState = FormWindowState.Normal;
            timer_call.Stop();//关闭计时器，确认状态

            timer_queueWaiting.Stop();
            ConversationMode = new ConversationInfo();
            ConversationMode.SuserId = dwUserId;
            ConversationMode.TuserId = m_UserId;
            UserInfo userItem = GetUserInfoByUserId(dwUserId);
            if (userItem != null)
            {
                btn_return.Visible = false;

                ShowCallMessage(Properties.Resources._14, userItem.Name + "向您发起视频会话邀请...");

                Button btn_accepted = new Button();
                btn_accepted.Font = new Font("微软雅黑", 20);
                btn_accepted.Size = new Size(140, 50);
                btn_accepted.Location = new Point(panel_call.Width / 2 - btn_accepted.Width - 10, pic_call.Top + pic_call.Height + 30);
                btn_accepted.Text = "接受";
                btn_accepted.Tag = "btn";
                btn_accepted.BackColor = Color.Lime;
                btn_accepted.ForeColor = Color.White;
                btn_accepted.Click += new EventHandler(btn_accepted_Click);
                panel_call.Controls.Add(btn_accepted);

                Button btn_refuse = new Button();
                btn_refuse.Font = new Font("微软雅黑", 20);
                btn_refuse.Size = new Size(140, 50);
                btn_refuse.Location = new Point(panel_call.Width / 2 + 10, pic_call.Top + pic_call.Height + 30);
                btn_refuse.Text = "拒绝";
                btn_refuse.Tag = "btn";
                btn_refuse.BackColor = Color.Red;
                btn_refuse.ForeColor = Color.White;
                btn_refuse.Click += new EventHandler(btn_refuse_Click);
                panel_call.Controls.Add(btn_refuse);

                SoundPlayer Player = new SoundPlayer();
                Player.Stream = Properties.Resources.ring;
                Player.Play();
                Player.Dispose();
            }
        }


        //开始会话
        private void VideoCall_SessionStart_Handler(int roomId)
        {
            //界面切换
            HideAllPanel();
            lbl_tipMessage.Text = "服务窗口";

            switch (m_userIdentity)
            {
                case UserIdentityType.Agent:
                    showAgentServiceFace();
                    break;
            }
            AnyChatCoreSDK.EnterRoom(roomId, "", 0);
            SoundPlayer Player = new SoundPlayer();
            Player.Stream = Properties.Resources.system;
            Player.Play();
            Player.Dispose();

        }

        //接受视频呼叫邀请
        void btn_accepted_Click(object sender, EventArgs e)
        {
            //发送视频呼叫回复指令，dwErrcode=0
            AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REPLY, ConversationMode.SuserId, 0, 0, 0, "");
       }

        // 拒绝视频呼叫邀请
        void btn_refuse_Click(object sender, EventArgs e)
        {

            //发送视频呼叫回复指令，dwErrcode=100104
            AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REPLY, ConversationMode.SuserId, AC_ERROR_VIDEOCALL_REJECT, 0, 0, "");
            ConversationMode = null;
            InitFaceAfterEndCall(Properties.Resources._5, "已经拒绝会话...");

            showQueueListFace();
        }


        /// <summary>
        /// 进入房间成功
        /// </summary>
        public void EnterRoomSuccess()
        {
            switch (m_userIdentity)
            {
                case UserIdentityType.Agent:
                    btnStopService.Enabled = true;
                    btnStartService.Enabled = false;
                    break;
            }
            btn_return.Visible = false;

            timer_call.Stop();
            Bitmap bit = Properties.Resources._28;
            bit.RotateFlip(RotateFlipType.Rotate180FlipY);
            //pic_suser.Image = bit;
            UserInfo tUserItem = GetUserInfoByUserId(getOtherInSession());
            
            if (tUserItem != null)
            {
                lbl_client_remoteUserName.Text = tUserItem.Name;
                lbl_client_localUserName.Text = m_UserName;
                OpenCameraAndSpeak(m_UserId, true);//打开自己的音视频
                //panel_users.Hide();
                //panel_call.Hide();

            }

        }
        //操作双方音视频设备
        public void OpenCameraAndSpeak(int userId, bool isopen)
        {

            if (isopen)
            {

                //打开呼叫者音视频
                AnyChatCoreSDK.UserCameraControl(userId, true);
                AnyChatCoreSDK.UserSpeakControl(userId, true);

                switch (m_userIdentity)
                {
                    case UserIdentityType.Agent:
                        if (userId == m_UserId)
                            //显示坐席端本地音视频
                            AnyChatCoreSDK.SetVideoPos(userId, picBox_agent_localVideo.Handle, 0, 0, picBox_agent_localVideo.Width, picBox_agent_localVideo.Height);
                        else
                            AnyChatCoreSDK.SetVideoPos(userId, picBox_agent_remoteVideo.Handle, 0, 0, picBox_agent_remoteVideo.Width, picBox_agent_remoteVideo.Height);

                        break;

                    case UserIdentityType.Client:
                        if (userId == m_UserId)
                            //显示本地音视频
                            AnyChatCoreSDK.SetVideoPos(userId, picBox_client_localVideo.Handle, 0, 0, picBox_client_localVideo.Width, picBox_client_localVideo.Height);
                        else
                            AnyChatCoreSDK.SetVideoPos(userId, picBox_client_remoteVideo.Handle, 0, 0, picBox_client_remoteVideo.Width, picBox_client_remoteVideo.Height);

                        showClientVideoFace();

                        break;
                }

            }
            else
            {
                AnyChatCoreSDK.UserCameraControl(userId, false);
                AnyChatCoreSDK.UserSpeakControl(userId, false);
            }

            //音量刷新
            timer_speak.Enabled = isopen;

        }

        //视频呼叫回复
        private void VideoCall_Reply_Handler(int userId, int dwErrorCode, int wParam, string lpStr)
        {

            if (this.WindowState == FormWindowState.Minimized)
                this.WindowState = FormWindowState.Normal;
            RemoveCallButton();
            intCallTimer = 3;
            //ShowCallMessage(Properties.Resources._18, "会话已结束...");
            ConversationMode = null;
            switch (dwErrorCode)
            {
                case 0:
                    ConversationMode = new ConversationInfo();
                    ConversationMode.SuserId = m_UserId;
                    ConversationMode.TuserId = userId;
                    VideoCall_WaitCall_Handler();
                    break;
                case AC_ERROR_VIDEOCALL_CANCEL:
                    ShowCallMessage(Properties.Resources._20, "对方取消呼叫...");
                    break;
                case AC_ERROR_VIDEOCALL_REJECT:
                    ShowCallMessage(Properties.Resources._5, "对方拒绝会话...");
                    break;
                case AC_ERROR_VIDEOCALL_BUSY:
                    ShowCallMessage(Properties.Resources._8, "目标用户正忙,请稍后重试...");
                    break;
                case AC_ERROR_VIDEOCALL_OFFLINE:
                    ShowCallMessage(Properties.Resources._18, "对方已离线...");
                    break;
                case AC_ERROR_VIDEOCALL_TIMEOUT:
                    ShowCallMessage(Properties.Resources._1, "会话请求已超时...");
                    break;
                case AC_ERROR_VIDEOCALL_DISCONNECT:
                    ShowCallMessage(Properties.Resources._18, "对方网络断开...");
                    break;
            }
            if (dwErrorCode != 0)
            {
                timer_call.Start();
                btnStartService.Enabled = true;
                btn_return.Enabled = true;

                switch(m_userIdentity)
                {
                    case UserIdentityType.Agent:
                        showAgentServiceFace();

                        refreshServicedUserInfo(-1);
                        break;
                    case UserIdentityType.Client:

                        showQueueListFace();
                        break;
                 }
            }

            Log.SetLog("VideoCall_Reply_Handler" + dwErrorCode);
           
        }

        //视频呼叫结束
        private void VideoCall_Finished_Handler(Bitmap bit, string strMsg)
        {


            OpenCameraAndSpeak(-1, false);
            OpenCameraAndSpeak(getOtherInSession(), false);
            AnyChatCoreSDK.LeaveRoom(-1);
            InitFaceAfterEndCall(bit, strMsg);

            switch (m_userIdentity)
            {
                case UserIdentityType.Agent:
                    refreshAgentServiceInfo();
                    refreshServicedUserInfo(-1);
                    
                    picBox_agent_remoteVideo.BackgroundImage = QueueClient.Properties.Resources.videobk;
                    picBox_agent_localVideo.BackgroundImage = QueueClient.Properties.Resources.videobk_agent_local;

                    btnStartService.Enabled = true;
                    btnStopService.Enabled = false;
                    btn_return.Enabled = true;

                    showAgentServiceFace();

                    break;

                case UserIdentityType.Client:

                    showQueueListFace();

                    break;
            }

        }

        //呼叫结束后初始化界面
        private void InitFaceAfterEndCall(Bitmap bit, string strMsg)
        {


            if (this.WindowState == FormWindowState.Minimized)
                this.WindowState = FormWindowState.Normal;
            RemoveCallButton();
            intCallTimer = 3;
            ShowCallMessage(bit, strMsg);
            timer_call.Start();

        }

        //移除呼叫流程按钮
        private void RemoveCallButton()
        {

            foreach (Control c in panel_call.Controls)
            {
                if (c.Tag != null)
                {
                    if (c.Tag.ToString() == "btn")
                    {
                        panel_call.Controls.Remove(c);
                        RemoveCallButton();
                        break;
                    }
                }
            }

        }

        //提示呼叫消息
        private void ShowCallMessage(Bitmap bit, string str)
        {
            HideAllPanel();

            panel_call.Dock = DockStyle.Fill;
            if (!panel_call.Visible) panel_call.Show();
            pic_call.Image = bit;
            lb_call.Text = str;
            //if (intCallTimer > 1)
            //    lb_call.Text += intCallTimer.ToString();
            lb_call.Tag = str;

            pic_call.Location = new Point(panel_call.Width / 2 - (pic_call.Width + lb_call.Width) / 2, panel_call.Height / 2 - pic_call.Height / 2 - 50 / 2);
            lb_call.Location = new Point(pic_call.Location.X + pic_call.Width, pic_call.Location.Y + pic_call.Height - lb_call.Height - 15);

        }


        //音量刷新计时器
        int intSuserSpeakValue = 0;//主动方音量
        int intTuserSpeakValue = 0;//被动方音量
        private void timer_speak_Tick(object sender, EventArgs e)
        {
            if (ConversationMode != null)
            {
                int value = 0;
                AnyChatCoreSDK.QueryUserState(ConversationMode.SuserId, AnyChatCoreSDK.BRAC_USERSTATE_SPEAKVOLUME, ref value, sizeof(int));
                intSuserSpeakValue = value;

                AnyChatCoreSDK.QueryUserState(ConversationMode.TuserId, AnyChatCoreSDK.BRAC_USERSTATE_SPEAKVOLUME, ref value, sizeof(int));
                intTuserSpeakValue = value;

                pic_tuserSound.Invalidate();
                pic_suserSound.Invalidate();
            }
        }

        //被动者音量条重绘
        private void pic_tuserSound_Paint(object sender, PaintEventArgs e)
        {

            Graphics g = e.Graphics;
            int width = intTuserSpeakValue * pic_tuserSound.Width / 100;
            g.FillRectangle(new SolidBrush(Color.SteelBlue), new Rectangle(new Point(0, 0), new Size(width, pic_tuserSound.Height)));

        }

        //主动者音量条重绘
        private void pic_suserSound_Paint(object sender, PaintEventArgs e)
        {

            Graphics g = e.Graphics;
            int width = intSuserSpeakValue * pic_tuserSound.Width / 100;
            g.FillRectangle(new SolidBrush(Color.SteelBlue), new Rectangle(new Point(0, 0), new Size(width, pic_tuserSound.Height)));

        }

        //发送视频呼叫结束指令，挂断会话
        private void btn_hungUp_Click(object sender, EventArgs e)
        {

            //发送视频呼叫回复指令，dwErrcode=100104
            AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_FINISH, getOtherInSession(), AC_ERROR_VIDEOCALL_REJECT, 0, 0, "");

        }

        #endregion

        #region 视频呼叫事件处理
        private void VideoCallEvent_CallBack(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, string lpUserStr)
        {
            switch (dwEventType)
            {
                //呼叫请求事件
                case AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REQUEST:
                    VideoCall_Request_Handler(dwUserId, dwParam, lpUserStr);
                    break;
                //呼叫回复事件
                case AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REPLY:
                    VideoCall_Reply_Handler(dwUserId, dwErrorCode, dwParam, lpUserStr);
                    break;
                //呼叫开始事件
                case AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_START:
                    VideoCall_SessionStart_Handler(dwParam);
                    break;
                //呼叫结束事件
                case AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_FINISH:
                    VideoCall_Finished_Handler(Properties.Resources._18, "会话已结束...");
                    break;
            }
        }
        #endregion

        #region 业务对象事件处理
        private void ObjectEvent_CallBack(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam)
        {
            switch (dwEventType)
            {
                case AnyChatCoreSDK.ANYCHAT_OBJECT_EVENT_UPDATE:
                    AnyChatObjectEventUpdate_Handler(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, strParam);
                    break;
                case AnyChatCoreSDK.ANYCHAT_AREA_EVENT_ENTERRESULT:
                    AnyChatEnterAreaResult_Handler(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, strParam);
                    break;
                case AnyChatCoreSDK.ANYCHAT_AREA_EVENT_LEAVERESULT:
                    AnyChatLeaveAreaResult_Handler(dwObjectType, dwObjectId, dwParam1);
                    break;
                case AnyChatCoreSDK.ANYCHAT_AREA_EVENT_STATUSCHANGE:
                    AnyChatAreaStatusChange_Handler(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, strParam);
                    break;
                case AnyChatCoreSDK.ANYCHAT_QUEUE_EVENT_ENTERRESULT:
                    AnyChatEnterQueueResult_Handler(dwObjectType, dwObjectId, dwParam1);
                    break;
                case AnyChatCoreSDK.ANYCHAT_QUEUE_EVENT_USERENTER:
                    AnyChatUserEnterQueue_Handler(dwObjectType, dwObjectId, dwParam1);
                    break;
                case AnyChatCoreSDK.ANYCHAT_QUEUE_EVENT_LEAVERESULT:
                    AnyChatLeaveQueueResult_Handler(dwObjectType, dwObjectId, dwParam1);
                    break;
                case AnyChatCoreSDK.ANYCHAT_QUEUE_EVENT_USERLEAVE:
                    AnyChatUserLeaveQueue_Handler(dwObjectType, dwObjectId, dwParam1);
                    break;
                case AnyChatCoreSDK.ANYCHAT_QUEUE_EVENT_STATUSCHANGE:
                    AnyChatQueueStatusChange_Handler(dwObjectType, dwObjectId);
                    break;
                case AnyChatCoreSDK.ANYCHAT_AGENT_EVENT_STATUSCHANGE:
                    AnyChatAgentStatusChange_Handler(dwObjectType, dwObjectId, dwParam1);
                    break;
                case AnyChatCoreSDK.ANYCHAT_AGENT_EVENT_SERVICENOTIFY:
                    AnyChatAgentServiceNotify_Handler(dwParam1, dwParam2);
                    break;
                case AnyChatCoreSDK.ANYCHAT_AGENT_EVENT_WAITINGUSER:
                    AnyChatAgentWaitingUser_Handler();
                    break;

            }
        }

        /// <summary>
        /// 对象更新事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        private void AnyChatObjectEventUpdate_Handler(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam)
        {
            try
            {
                switch (dwObjectType)
                {
                    case AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA:

                        if (isEnterArea) return;

                        //HideAllPanel();
                        if (panel_waitingMessage.Visible) panel_waitingMessage.Hide();

                        panel_area.Dock = DockStyle.Fill;
                        if (!panel_area.Visible) panel_area.Show();

                        //增加服务区域显示
                        AreaInfo area = new AreaInfo();
                        area.AreaID = dwObjectId;
                        StringBuilder sbAreaName = new StringBuilder(100);
                        AnyChatCoreSDK.BRAC_ObjectGetValue(dwObjectType, dwObjectId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_NAME, sbAreaName);
                        area.AreaName = sbAreaName.ToString();

                        StringBuilder sbAreaDesc = new StringBuilder(200);
                        AnyChatCoreSDK.BRAC_ObjectGetValue(dwObjectType, dwObjectId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_DESCRIPTION, sbAreaDesc);
                        area.AreaDescription = sbAreaDesc.ToString();

                        AddAreaToForm(area);

                        break;
                }
            }
            catch (Exception exp)
            {
                Log.SetLog("AnyChatObjectEventUpdate_Handler 异常：" + exp.Message);

            }
        }

        /// <summary>
        /// 进入服务区域结果通知事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatEnterAreaResult_Handler(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam)
        {
            StringBuilder sbAreaName = new StringBuilder(100);
            AnyChatCoreSDK.BRAC_ObjectGetValue(dwObjectType, dwObjectId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_NAME, sbAreaName);

            if (dwParam1 != 0)
                return;

            currentBusinessFunc = BusinessFuncType.SelectAreaFunc;

            switch (m_userIdentity)
            {
                //显示营业厅的队列
                case UserIdentityType.Client:
                    InitQueuePanel(sbAreaName.ToString());

                    int idx = 0;
                    //获取营业厅内的队列信息
                    AnyChatCoreSDK.BRAC_ObjectGetIdList(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, null, ref idx);
                    int[] queueIds = new int[idx];
                    AnyChatCoreSDK.BRAC_ObjectGetIdList(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueIds, ref idx);
                    for (int i = 0; i < queueIds.Length; i++)
                    {
                        int queueID = queueIds[i];
                        QueueInfo queue = new QueueInfo();
                        queue.QueueID = queueID;

                        StringBuilder sbQueueName = new StringBuilder();
                        AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_NAME, sbQueueName);
                        queue.QueueName = sbQueueName.ToString();

                        StringBuilder sbQueueDesc = new StringBuilder();
                        AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_DESCRIPTION, sbQueueDesc);
                        queue.QueueDescription = sbQueueDesc.ToString();

                        int queueUserCount = 0;
                        AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_LENGTH, ref queueUserCount);
                        queue.inQueueClientCount = queueUserCount;

                        AddQueueToForm(queue);
                    }

                    panel_queue.Show();

                    break;

                case UserIdentityType.Agent:
                    lbl_tipMessage.Text = "坐席服务窗口";

                    showAgentServiceFace();

                    refreshAgentServiceInfo();
                    break;
            }
        }

        /// <summary>
        /// 离开服务区域结果通知事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatLeaveAreaResult_Handler(int dwObjectType, int dwObjectId, int dwErrorCode)
        {
            currentBusinessFunc = BusinessFuncType.None ;
            selectedArea = null;

            if (panel_waitingMessage.Visible) panel_waitingMessage.Hide();
            if (!panel_area.Visible) panel_area.Show();
        }

        /// <summary>
        /// 营业厅状态变化事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwEventType"></param>
        /// <param name="dwParam1"></param>
        /// <param name="dwParam2"></param>
        /// <param name="dwParam3"></param>
        /// <param name="dwParam4"></param>
        /// <param name="strParam"></param>
        private void AnyChatAreaStatusChange_Handler(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam)
        {
            switch(m_userIdentity)
            {
                case UserIdentityType.Agent:
                    refreshAgentServiceInfo();
                    break;
            }
        }

        /// <summary>
        /// 进入队列结果通知事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatEnterQueueResult_Handler(int dwObjectType, int dwObjectId, int dwErrorCode)
        {
            //currentBusinessFunc = BusinessFuncType.None;
            //selectedArea = null;

            if (selectedQueue.QueueID == dwObjectId)
            {
                timer_queueWaiting.Start();

                replaceQueuePosition = "";
                replaceTotalCount = "";
                replaceWaitingTime = "";

                isShowReturnButton(false);

                refreshUserWaitingInfo(dwObjectId);

                HideAllPanel();
                if (!panel_waitingMessage.Visible) panel_waitingMessage.Show();

                lbl_tipMessage.Text = "服务等待";

            }

        }

        /// <summary>
        /// 离开队列结果通知事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatLeaveQueueResult_Handler(int dwObjectType, int dwObjectId, int dwErrorCode)
        {
            if (dwErrorCode == 0 || dwErrorCode == 751)
            {
                timer_queueWaiting.Stop();
                currentBusinessFunc = BusinessFuncType.SelectAreaFunc;
                //selectedQueue = null;               

                //离开队列后显示队列列表界面
                RemoveWaitingMessageButton();

                showQueueListFace();

            }
        }

        /// <summary>
        /// 其他用户进入队列
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatUserEnterQueue_Handler(int dwObjectType, int dwObjectId, int dwErrorCode)
        {
            //refreshAgentServiceInfo();
        }

        /// <summary>
        /// 其他用户离开队列
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatUserLeaveQueue_Handler(int dwObjectType, int dwObjectId, int dwErrorCode)
        {
            //refreshAgentServiceInfo();
        }

        /// <summary>
        /// 队列状态变化结果通知事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        private void AnyChatQueueStatusChange_Handler(int dwObjectType, int dwObjectId)
        {
            if (dwObjectType == AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE)
            {
                if (selectedQueue != null)
                    if (selectedQueue.QueueID == dwObjectId)
                        refreshUserWaitingInfo(dwObjectId);

                switch (m_userIdentity)
                {
                    case UserIdentityType.Agent:
                        refreshAgentServiceInfo();
                        break;
                }

                QueueInfo q = getQueueInfoByQueueID(dwObjectId);
                refreshQueueInfoDisplay(q);
            }
        }

        /// <summary>
        /// 坐席状态变化结果通知事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwParam1"></param>
        private void AnyChatAgentStatusChange_Handler(int dwObjectType, int dwObjectId, int dwParam1)
        {
            if (dwObjectType == AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT && m_UserId == dwObjectId)
            {
                if (dwParam1 == AnyChatCoreSDK.ANYCHAT_AGENT_STATUS_WAITTING)
                {
                    refreshAgentServiceInfo();

                    refreshServicedUserInfo(-1);
                    //startServiceTag = false;
                    btn_return.Enabled = true;
                    btnStartService.Enabled = true;
                    btnStopService.Enabled = false;

                    showAgentServiceFace();
                }
            }
        }

        /// <summary>
        /// 坐席服务通知事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatAgentServiceNotify_Handler(int dwAgentId, int clientId)
        {
            if (m_userIdentity ==  UserIdentityType.Agent && m_UserId == dwAgentId)
            {
                refreshServicedUserInfo(clientId);

                //发送视频呼叫，最后两个参数为自定义参数
                AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REQUEST, clientId, 0, 0, 0, m_UserName);
                intCallTimer = 10;
                mTargetUserId = clientId;
                ShowCallMessage(Properties.Resources._23, "正在发起视频呼叫请求...");
                timer_call.Start();

            }

        }

        /// <summary>
        /// 坐席等待用户通知事件
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatAgentWaitingUser_Handler()
        {
            MessageBox.Show("队列中已没有客户！");
            btn_return.Enabled = true;
            btnStartService.Enabled = true;
            btnStopService.Enabled = false;
        }

        #endregion

        #region 帮助函数

        /// <summary>
        /// 根据ID获取用户对象(不能获取自己的)
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        private UserInfo GetUserInfoByUserId(int id)
        {
            UserInfo mode = new UserInfo();
            StringBuilder sbUserName = new StringBuilder(100);
            AnyChatCoreSDK.GetUserName(id, sbUserName, 100);
            mode.Id = id;
            mode.Name = sbUserName.ToString();
            return mode;
        }

        /// <summary>
        /// 获取通话中的另外一方
        /// </summary>
        /// <returns>通话中另外一方的userid</returns>
        public int getOtherInSession()
        {
            if (ConversationMode != null)
            {
                if (ConversationMode.SuserId == m_UserId)
                    return ConversationMode.TuserId;
                else
                    return ConversationMode.SuserId;
            }
            return 0;
        }

        /// <summary>
        /// 格式化秒为“分:秒”形式
        /// </summary>
        /// <param name="second"></param>
        /// <returns></returns>
        private string formatSeconds(int second)
        {

            string retVal = string.Empty;

            int s = second;
            int min = 0;// 分
            if (s > 60)
            {
                min = s / 60;
                s = s % 60;
                if (min > 60)
                {
                    min = min % 60;
                }
            }

            retVal = "" + s + "秒";
            if (min > 0)
            {
                retVal = "" + min + "分" + retVal;
            }

            return retVal;

        }

        #endregion

        #region 计时器控制呼叫过程界面显示

        private void timer_call_Tick(object sender, EventArgs e)
        {
            try
            {
                if (intCallTimer != 1)
                {
                    intCallTimer -= 1;
                    lb_call.Text = lb_call.Tag.ToString();
                }
                else
                {

                    panel_call.Hide();
                    panel_conversation.Hide();
                    //panel_users.Show();
                    timer_call.Stop();
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("QueueClient.Hall.timer_call_Tick       timer_call_Tick：" + ex.Message.ToString());
            }
        }
        #endregion

        #region 营业厅数据处理

        /// <summary>
        /// 每个营业厅之间的间隔
        /// </summary>
        int areaInterval = 30;
        int intAreaLeft = 0;
        int intAreaTop = 30;

        /// <summary>
        /// 初始化装载营业厅数据的panel
        /// </summary>
        private void InitAreaPanel()
        {

            intAreaLeft = 0;
            intAreaTop = 30;
            //pan_users.Controls.Clear();
            panel_area.Controls.Clear();

            panel_area.Show();
            lbl_tipMessage.Text = "营业厅列表";
        }

        /// <summary>
        /// 添加营业厅到界面中
        /// </summary>
        /// <param name="mode"></param>
        private void AddAreaToForm(AreaInfo mode)
        {
            PictureBox areaBox = new PictureBox();
            areaBox.Name = "area" + mode.AreaID;
            areaBox.Tag = mode;
            //每个areaBox的宽度为300、高度为120
            areaBox.Size = new Size(300, 120);
            if (intAreaLeft < areaBox.Width * 3 + areaInterval * 2)
                intAreaLeft += areaInterval;
            else
            {
                intAreaLeft = areaInterval;
                intAreaTop += areaInterval + areaBox.Height;
            }
            areaBox.Location = new Point(intAreaLeft, intAreaTop);
            intAreaLeft += 300;
            //areaBox.BackColor = mode.Id == m_UserId ? Color.DarkSeaGreen : Color.LightSteelBlue;
            areaBox.BackColor = Color.LightSteelBlue;
            areaBox.Paint += new PaintEventHandler(area_Paint);
            areaBox.MouseEnter += new EventHandler(area_MouseEnter);
            areaBox.MouseLeave += new EventHandler(area_MouseLeave);
            areaBox.MouseHover += new EventHandler(area_MouseHover);
            areaBox.MouseMove += new MouseEventHandler(area_MouseHover);
            areaBox.Click += new EventHandler(area_Click);
            panel_area.Controls.Add(areaBox);


        }
        
        /// <summary>
        /// 鼠标离开营业厅
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void area_MouseLeave(object sender, EventArgs e)
        {

            PictureBox mode = sender as PictureBox;
            AreaInfo umode = mode.Tag as AreaInfo;
            mode.BackColor = Color.LightSteelBlue;

            Cursor.Current = Cursors.Default;

        }

        /// <summary>
        /// 鼠标进入营业厅
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void area_MouseEnter(object sender, EventArgs e)
        {
            Cursor.Current = Cursors.Hand;
            PictureBox mode = sender as PictureBox;
            AreaInfo umode = mode.Tag as AreaInfo;
            mode.BackColor = Color.DarkSeaGreen;


        }

        void area_MouseHover(object sender, EventArgs e)
        {
            Cursor.Current = Cursors.Hand;
        }
        

        /// <summary>
        /// 绘制营业厅图标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void area_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                AreaInfo mode = (sender as PictureBox).Tag as AreaInfo;
                Graphics g = e.Graphics;
                g.DrawImage(Properties.Resources.area, new Point(5, ((sender as PictureBox).Height - Properties.Resources.area.Height)/2));
                g.DrawString(mode.AreaName, new Font("微软雅黑", 16), new SolidBrush(Color.White), new RectangleF(new PointF(Properties.Resources.area.Width + 20, 20), new SizeF(170, 50)));
                g.DrawString("编号：" + mode.AreaID, new Font("微软雅黑", 12), new SolidBrush(Color.White), new RectangleF(new PointF(Properties.Resources.area.Width + 20, 75), new SizeF(170, 35)));
                //g.DrawString(mode.AreaDescription, new Font("微软雅黑", 12), new SolidBrush(Color.White), new RectangleF(new PointF(Properties.Resources.area.Width + 5, 85), new SizeF(170, 35)));
            }
            catch (Exception ex)
            {
                Log.SetLog("QueueClient.Hall.area_Paint       area_Paint：" + ex.Message.ToString());
            }
        }

        /// <summary>
        /// 单击营业厅
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void area_Click(object sender, EventArgs e)
        {
            try
            {
                isEnterArea = true;

                PictureBox area = sender as PictureBox;
                AreaInfo mode = area.Tag as AreaInfo;
                int tAreaID = mode.AreaID;

                queueList.Clear();

                //进入营业厅
                int retCode = AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, tAreaID, AnyChatCoreSDK.ANYCHAT_AREA_CTRL_USERENTER, 0, 0, 0, 0, string.Empty);

                selectedArea = mode;
            }
            catch (Exception exp)
            {
                Log.SetLog("QueueClient.Hall.area_Click       area_Click：" + exp.Message.ToString());

            }
        }

        #endregion

        #region 队列数据处理
        /// <summary>
        /// 每个队列之间的间隔
        /// </summary>
        int queueInterval = 50;
        int intQueueLeft = 0;
        int intQueueTop = 30;

        /// <summary>
        /// 初始化装载队列数据的panel
        /// </summary>
        private void InitQueuePanel(string areaName)
        {

            intQueueLeft = 0;
            intQueueTop = 30;
            //pan_users.Controls.Clear();
            panel_queue.Controls.Clear();

            //panel_area.Hide();
            if (panel_area.Visible) panel_area.Hide();

            lbl_tipMessage.Text = areaName +" 队列列表";

            panel_queue.Dock = DockStyle.Fill;
        }

        /// <summary>
        /// 添加队列到界面中
        /// </summary>
        /// <param name="mode"></param>
        private void AddQueueToForm(QueueInfo mode)
        {
            PictureBox queueBox = new PictureBox();
            queueBox.Name = "queue" + mode.QueueID;
            queueBox.Tag = mode;
            //每个areaBox的宽度为440、高度为150
            queueBox.Size = new Size(440, 150);
            if (intQueueLeft < queueBox.Width * 2 + queueInterval * 2)
                intQueueLeft += queueInterval;
            else
            {
                intQueueLeft = queueInterval;
                intQueueTop += queueInterval + queueBox.Height;
            }
            queueBox.Location = new Point(intQueueLeft, intQueueTop);
            intQueueLeft += 440;
            //areaBox.BackColor = mode.Id == m_UserId ? Color.DarkSeaGreen : Color.LightSteelBlue;
            queueBox.BackColor = Color.DarkSeaGreen;
            queueBox.Paint += new PaintEventHandler(queue_Paint);
            queueBox.MouseEnter += new EventHandler(queue_MouseEnter);
            queueBox.MouseLeave += new EventHandler(queue_MouseLeave);
            queueBox.MouseHover += new EventHandler(queue_MouseHover);
            queueBox.MouseMove += new MouseEventHandler(queue_MouseHover);
            queueBox.Click += new EventHandler(queue_Click);
            panel_queue.Controls.Add(queueBox);
            mode.bindedOjbect = queueBox;

            queueList.Add(mode);

        }

        /// <summary>
        /// 鼠标离开队列
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void queue_MouseLeave(object sender, EventArgs e)
        {

            PictureBox mode = sender as PictureBox;
            QueueInfo umode = mode.Tag as QueueInfo;
            mode.BackColor = Color.DarkSeaGreen;

            //Cursor.Current = Cursors.Default;

        }

        /// <summary>
        /// 鼠标进入队列
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void queue_MouseEnter(object sender, EventArgs e)
        {
            //Cursor.Current = Cursors.Hand;
            PictureBox mode = sender as PictureBox;
            QueueInfo umode = mode.Tag as QueueInfo;
            mode.BackColor = Color.LightSteelBlue;


        }

        void queue_MouseHover(object sender, EventArgs e)
        {
            Cursor.Current = Cursors.Hand;
        }


        /// <summary>
        /// 绘制队列图标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void queue_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                QueueInfo mode = (sender as PictureBox).Tag as QueueInfo;

                //int queueLength = AnyChatCoreSDK.GetObjectValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_INFO_LENGTH);

                Graphics g = e.Graphics;
                //g.DrawImage(Properties.Resources.area, new Point(0, ((sender as PictureBox).Height - Properties.Resources.area.Height) / 2));
                int queueXPoint = 10;

                g.DrawString(mode.QueueName+"("+ "编号：" + mode.QueueID +")", new Font("微软雅黑", 16), new SolidBrush(Color.White), new RectangleF(new PointF(queueXPoint + 20, 20), new SizeF(350, 50)));                
                g.DrawString(mode.QueueDescription + "(当前排队人数：" + mode.inQueueClientCount + "人)", new Font("微软雅黑", 12), new SolidBrush(Color.White), new RectangleF(new PointF(queueXPoint + 50, 85), new SizeF(380, 40)));
            }
            catch (Exception ex)
            {
                Log.SetLog("QueueClient.Hall.area_Paint       area_Paint：" + ex.Message.ToString());
            }
        }

        /// <summary>
        /// 单击队列
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void queue_Click(object sender, EventArgs e)
        {

            PictureBox area = sender as PictureBox;
            QueueInfo mode = area.Tag as QueueInfo;
            int tQueueID = mode.QueueID;
            selectedQueue = mode;

            currentBusinessFunc = BusinessFuncType.SelectQueueFunc;

            switch (m_userIdentity)
            {
                case UserIdentityType.Client:
                    //进入队列

                    EnterQueueWaitingProcess();

                    AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, selectedQueue.QueueID, AnyChatCoreSDK.ANYCHAT_QUEUE_CTRL_USERENTER, 0, 0, 0, 0, "");
                    break;

                case UserIdentityType.Agent:
                    //显示坐席视频呼叫界面

                    break;
            }

        }

        /// <summary>
        /// 用户进入队列后等待处理
        /// </summary>
        private void EnterQueueWaitingProcess()
        {
            try
            {
                ShowWaitingMessage(Properties.Resources._15, enterQueueWaitingMessage);
                lbl_waitingMessage.Text = string.Empty;

                //timer_call.Start();
                //timer_call.Stop();//关闭计时器，确认状态
                Button btnCancel = new Button();
                btnCancel.Font = new Font("微软雅黑", 20);
                btnCancel.Size = new Size(140, 50);
                btnCancel.Location = new Point(panel_waitingMessage.Width / 2 - btnCancel.Width / 2, picBox_waiting.Top + picBox_waiting.Height + 40);
                btnCancel.Text = "取消";
                btnCancel.Tag = "btn";
                btnCancel.BackColor = Color.Red;
                btnCancel.ForeColor = Color.White;
                btnCancel.Click += new EventHandler(btnCancel_Click);
                panel_waitingMessage.Controls.Add(btnCancel);
                //SoundPlayer Player = new SoundPlayer();
                //Player.Stream = Properties.Resources.ring;
                //Player.Play();
                //Player.Dispose();
            }
            catch (Exception ex)
            {
                timer_queueWaiting.Stop();

                Log.SetLog("QueueClient.Hall.EnterQueueWaitingProcess       EnterQueueWaitingProcess：" + ex.Message.ToString());
            }
        }

        /// <summary>
        /// 单击取消排队
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void btnCancel_Click(object sender, EventArgs e)
        {

            //离开队列
            AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, selectedQueue.QueueID, AnyChatCoreSDK.ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");
            
            
        }

        //刷新用户进入队列后，排队等待时的显示信息
        private void refreshUserWaitingInfo(int queueID) {
            int queueUserNum = 0; //当前队列人数
            int beforeUserNum = 0; //排在自己前面的队列人数

            //获取当前队列人数
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_LENGTH, ref queueUserNum);

            //获取排在自己前面的用户数
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_BEFOREUSERNUM, ref beforeUserNum);
            beforeUserNum = beforeUserNum < 0 ? 0 : beforeUserNum;
            beforeUserNum++;

            lbl_waitingMessage.Text = "当前排队人数共：" + queueUserNum.ToString() + " 人，您现在排在第 " + beforeUserNum.ToString() + " 位";
        }

        /// <summary>
        /// 排队等待时间触发处理
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer_queueWaiting_Tick(object sender, EventArgs e)
        {
            int second = 0;

            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, selectedQueue.QueueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_WAITTIMESECOND, ref second);
            string strTime = formatSeconds(second);

            lbl_waitingTime.Text = "已等待时间：" + strTime;
        }


        private QueueInfo getQueueInfoByQueueID(int queueID)
        {
            QueueInfo queueInfo = new QueueInfo();

            foreach (QueueInfo q in queueList)
            {
                if (q.QueueID == queueID)
                {
                    //mode = u;
                    queueInfo = q;
                    break;
                }
            }

            return queueInfo;
        }

        /// <summary>
        /// 刷新队列显示信息（如队列人数）
        /// </summary>
        /// <param name="queueID"></param>
        private void refreshQueueInfoDisplay(QueueInfo queueID)
        {
            int queueUserNum = 0;
            //获取当前队列人数
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID.QueueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_LENGTH, ref queueUserNum);
            queueID.inQueueClientCount = queueUserNum;

            PictureBox picBox = queueID.bindedOjbect as PictureBox;
            picBox.Refresh();

        }

        #endregion
        
    }
}
