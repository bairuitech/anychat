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
        #region ��������

        int m_UserId = -1;
        string m_UserName = "";
        int intCallTimer = 0;
        private List<UserInfo> users = new List<UserInfo>();
        public const int AC_ERROR_VIDEOCALL_CANCEL = 100101;       ///  Դ�û����������Ự
        public const int AC_ERROR_VIDEOCALL_OFFLINE = 100102;      ///< Ŀ���û�������
        public const int AC_ERROR_VIDEOCALL_BUSY = 100103;       ///< Ŀ���û�æ
        public const int AC_ERROR_VIDEOCALL_REJECT = 100104;       ///< Ŀ���û��ܾ��Ự
        public const int AC_ERROR_VIDEOCALL_TIMEOUT = 100105;       ///< �Ự����ʱ
        public const int AC_ERROR_VIDEOCALL_DISCONNECT = 100106;       ///< �������
        public const int USERDATA_USERNAME = 1;       ///< �û�����
        public const int USERDATA_USERADRESSIP = 2;       ///< �û���ַ
        public const int USER_OFFLINE = 0; ///< �û�����                                                  ///
        public const int USER_ONLINE = 1; ///< �û�����
        public bool bReleased = false;
        /// <summary>
        /// ��ǰ�Ự
        /// </summary>
        private ConversationInfo ConversationMode = null;

        /// <summary>
        /// �û���ݱ�ʶ
        /// </summary>
        public UserIdentityType m_userIdentity = UserIdentityType.Client;
        /// <summary>
        /// ������ȼ�
        /// </summary>
        public int m_identityPriority = 10;
        /// <summary>
        /// ·�ɱ�ʶ
        /// </summary>
        public bool m_router = true;
        /// <summary>
        /// ��ϯӵ�еļ���
        /// </summary>
        public int m_skill = 0;
        /// <summary>
        /// ���汻���صĵ�¼����
        /// </summary>
        public frmLogin m_loginForm = null;

        /// <summary>
        /// ��ǰ��ҵ����
        /// </summary>
        public BusinessFuncType currentBusinessFunc = BusinessFuncType.None;
        /// <summary>
        /// ��ǰ��ѡ���Ӫҵ��
        /// </summary>
        public AreaInfo selectedArea = null;
        /// <summary>
        /// ��ǰ��ѡ��Ķ���
        /// </summary>
        public QueueInfo selectedQueue = null;
        /// <summary>
        /// �Ƿ����Ӫҵ��
        /// </summary>
        public bool isEnterArea = false;


        string replaceWaitingTime = string.Empty;
        string replaceTotalCount = string.Empty;
        string replaceQueuePosition = string.Empty;
        /// <summary>
        /// ������к��Ŷӵȴ���Ϣ
        /// </summary>
        private string enterQueueWaitingMessage = "��ǰ�Ŷ���������{0} ��  ���������ڵ� {1} λ " + Environment.NewLine +"�ѵȴ�ʱ�䣺{2}";

        private int mTargetUserId = 0;

        /// <summary>
        /// Ӫҵ���б�
        /// </summary>
        private List<AreaInfo> areaList = new List<AreaInfo>();
        /// <summary>
        /// �����б�
        /// </summary>
        private List<QueueInfo> queueList = new List<QueueInfo>();

        #endregion

        #region ���캯��

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

        public frmHall(int r_UserId, string r_UserName, UserIdentityType r_userIdentityType, int r_identityPriority, bool r_router, frmLogin loginForm)
        {
            m_UserId = r_UserId;
            m_UserName = r_UserName;
            m_userIdentity = r_userIdentityType;
            m_identityPriority = r_identityPriority;
            m_router = r_router;
            //this.loginForm = loginForm;
            this.m_loginForm = loginForm;

            InitializeComponent();
        }

        public frmHall(LoginInfo loginUserInfo, frmLogin loginForm)
        {
            m_UserId = loginUserInfo.userID;
            m_UserName = loginUserInfo.userName;
            m_userIdentity = loginUserInfo.userIdType;
            m_identityPriority = loginUserInfo.userPriority;
            m_router = loginUserInfo.isRouterMode;
            m_skill = loginUserInfo.userSkills;

            //this.loginForm = loginForm;
            this.m_loginForm = loginForm;

            InitializeComponent();
        }
        #endregion

        #region ��ʼ���������������

        //�������
        private void Hall_Load(object sender, EventArgs e)
        {

            SystemSetting.VideoCallEvent_Handler = new SystemSetting.VideoCallEventCallBack(VideoCallEvent_CallBack);
            SystemSetting.AnyChatObjectEvent_Handler = new SystemSetting.AnyChatObjectEventCallBack(ObjectEvent_CallBack);

            lbl_agent_remoteUser.Text = string.Empty;
        }

        //����ر�
        private void Hall_FormClosed(object sender, FormClosedEventArgs e)
        {

            AnyChatCoreSDK.Logout();
            AnyChatCoreSDK.Release();
            Application.Exit();
            bReleased = true;
        }

        /// <summary>
        /// �������е�Panel
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
        /// ��ʾ�ȴ���Ϣ
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
        /// ���ذ�ť�Ƿ���ʾ
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
        /// ��ʼ���ͻ��˶���
        /// </summary>
        /// <param name="mSelfUserId">�û�id</param>
        /// <param name="userIdentityType">�û��������</param>
        /// <param name="userPriority">�û����ȼ�</param>
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
                    if (m_router)
                        objectFlag = AnyChatCoreSDK.ANYCHAT_OBJECT_FLAGS_AGENT + AnyChatCoreSDK.ANYCHAT_OBJECT_FLAGS_AUTOMODE;
                    else
                        objectFlag = AnyChatCoreSDK.ANYCHAT_OBJECT_FLAGS_AGENT;
                    break;
                default:                    
                    objectFlag = AnyChatCoreSDK.ANYCHAT_OBJECT_FLAGS_CLIENT;
                    break;
            }

            //ҵ�������ݳ�ʼ��
            AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_OBJECT_INITFLAGS, ref objectFlag, sizeof(int));
            //�û��������ȼ�
            AnyChatCoreSDK.BRAC_ObjectSetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_CLIENTUSER, mSelfUserId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_PRIORITY, ref userPriority, sizeof(int));
            //�������Ը�ֵ
            if (userIdentityType == UserIdentityType.Agent)
                AnyChatCoreSDK.BRAC_ObjectSetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_CLIENTUSER, mSelfUserId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_ATTRIBUTE, ref m_skill, sizeof(int));
            else
            {
                int userAttribute = -1;
                AnyChatCoreSDK.BRAC_ObjectSetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_CLIENTUSER, mSelfUserId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_ATTRIBUTE, ref userAttribute, sizeof(int));
            }

            //���ͷ�����������ͬ������ָ��
            AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, AnyChatCoreSDK.ANYCHAT_INVALID_OBJECT_ID, AnyChatCoreSDK.ANYCHAT_OBJECT_CTRL_SYNCDATA,
                                            mSelfUserId, 0, 0, 0, string.Empty);

            ShowWaitingMessage(Properties.Resources._15, "���ڼ���Ӫҵ�������Ժ�......");
        }

        private void btnStopService_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("��ȷ��������ǰ����Ƶ������", "��ʾ", MessageBoxButtons.OKCancel, MessageBoxIcon.Information, MessageBoxDefaultButton.Button2) == System.Windows.Forms.DialogResult.OK)
            {
                AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_FINISH, mTargetUserId, 0, 0, 0, ""); 	// �Ҷ�
                //btn_return.Enabled = true;
            }
        }

        private void btnStartService_Click(object sender, EventArgs e)
        {
            //�ͷ���ʼ����
            AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_CTRL_SERVICEREQUEST, 0, 0, 0, 0, "");

            btn_return.Enabled = false;
            btnStartService.Enabled = false;
            btnStopService.Enabled = true;
        }

        /// <summary>
        /// ��ʾ��ϯ�������
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
        /// ��ʾ�ͻ���Ƶ����
        /// </summary>
        private void showClientVideoFace()
        {
            HideAllPanel();

            panel_conversation.Dock = DockStyle.Fill;
            if (!panel_userVedioCall.Visible) panel_userVedioCall.Show();
            if (!panel_conversation.Visible) panel_conversation.Show();

        }

        /// <summary>
        /// ��ʾ�����б�
        /// </summary>
        private void showQueueListFace()
        {
            HideAllPanel();
            lbl_tipMessage.Text = selectedArea.AreaName + " �����б�";
            if (!panel_queue.Visible) panel_queue.Show();
            if (!btn_return.Visible) btn_return.Visible = true;
        }

        /// <summary>
        /// �Ƴ���ʾ�����ж�̬���ɵİ�ť
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
                //��������
                int queueCount = 0;
                AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, selectedArea.AreaID, AnyChatCoreSDK.ANYCHAT_AREA_INFO_QUEUECOUNT, ref queueCount);

                //�������û���
                int queuesUserCount = 0;
                AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, selectedArea.AreaID, AnyChatCoreSDK.ANYCHAT_AREA_INFO_QUEUEUSERCOUNT, ref queuesUserCount);

                //��Ӫҵ��δ�����������
                int atAreaUserCount = 0;
                AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, selectedArea.AreaID, AnyChatCoreSDK.ANYCHAT_AREA_INFO_GUESTCOUNT, ref atAreaUserCount);


                //�ۼƷ�����û���
                int servicedUserCount = 0;
                int retCode = AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_INFO_SERVICETOTALNUM, ref servicedUserCount);                
                    
                lbl_agent_queueNumber.Text = "��ǰ����Ķ�������Ϊ�� " + queueCount + " ��";
                lbl_agent_currentTotalUserCount.Text = "��ǰ�Ŷӵ��û�����Ϊ�� " + queuesUserCount + " ��";
                lbl_agent_servicedUserCount.Text = "�ѷ�������Ϊ�� " + servicedUserCount + " ��";
                lbl_agent_atAreaUserCount.Text = "δ��������û���Ϊ��" + atAreaUserCount + " ��";
            }
        }

        private void refreshServicedUserInfo(int userID)
        {
            int serviceUserID = 0;
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_INFO_SERVICEUSERID, ref serviceUserID);
            
            byte[] userNameByte = new byte[255];
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_CLIENTUSER, userID, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_NAME, ref userNameByte[0]);
            string userName = byteToString(userNameByte);

            if (userID == -1)
                lbl_agent_remoteUser.Text = string.Empty;
            else
                lbl_agent_remoteUser.Text = "��ǰ�����û�ID��" + userID + "���û���Ϊ��" + userName.ToString();
        }

        private void btn_return_Click(object sender, EventArgs e)
        {
            switch (currentBusinessFunc)
            {
                case BusinessFuncType.SelectAreaFunc:
                    //�˳�Ӫҵ��
                    int iAreaID = selectedArea.AreaID;
                    AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, iAreaID, AnyChatCoreSDK.ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, string.Empty);
                    ShowWaitingMessage(Properties.Resources._15, "�����˳�Ӫҵ�������Ժ�......");
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
            if (((Panel)sender).Visible) lbl_tipMessage.Text = "Ӫҵ���б�";
        }



        #endregion
        
        #region ��Ƶ����ҵ��ʵ�ʴ���

        //���еȴ�
        private void VideoCall_WaitCall_Handler()
        {
            try
            {
                intCallTimer = 60;
                ShowCallMessage(Properties.Resources._15, "���������У��ȴ��û���Ӧ...");
                //timer_call.Start();
                timer_call.Stop();//�رռ�ʱ����ȷ��״̬
                Button btn_cancall = new Button();
                btn_cancall.Font = new Font("΢���ź�", 20);
                btn_cancall.Size = new Size(140, 50);
                btn_cancall.Location = new Point(panel_call.Width / 2 - btn_cancall.Width / 2, pic_call.Top + pic_call.Height + 30);
                btn_cancall.Text = "ȡ��";
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
                Log.SetLog("QueueClient.Hall.WaitCall       WaitCall��" + ex.Message.ToString());
            }
        }

        //����ȡ������
        void btn_cancall_Click(object sender, EventArgs e)
        {

            CanCall();

        }
        //ȡ������
        private void CanCall()
        {
            //������Ƶ���лظ�ָ�dwErrcode=100101
            AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REPLY, ConversationMode.TuserId, AC_ERROR_VIDEOCALL_CANCEL, 0, 0, "");
            ConversationMode = null;
            InitFaceAfterEndCall(Properties.Resources._20, "�Ѿ�ȡ������");

            AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_CTRL_FINISHSERVICE, 0, 0, 0, 0, "");	
            refreshServicedUserInfo(-1);

            showAgentServiceFace();

        }
        //���յ���Ƶ����������

        private void VideoCall_Request_Handler(int dwUserId, int dwParam, string lpUserStr)
        {

            if (this.WindowState == FormWindowState.Minimized)
                this.WindowState = FormWindowState.Normal;
            timer_call.Stop();//�رռ�ʱ����ȷ��״̬

            timer_queueWaiting.Stop();
            ConversationMode = new ConversationInfo();
            ConversationMode.SuserId = dwUserId;
            ConversationMode.TuserId = m_UserId;
            UserInfo userItem = GetUserInfoByUserId(dwUserId);
            if (userItem != null)
            {
                btn_return.Visible = false;

                ShowCallMessage(Properties.Resources._14, "��" + userItem.Name + "������������Ƶ�Ự����...");

                Button btn_accepted = new Button();
                btn_accepted.Font = new Font("΢���ź�", 20);
                btn_accepted.Size = new Size(140, 50);
                btn_accepted.Location = new Point(panel_call.Width / 2 - btn_accepted.Width - 10, pic_call.Top + pic_call.Height + 30);
                btn_accepted.Text = "����";
                btn_accepted.Tag = "btn";
                btn_accepted.BackColor = Color.Lime;
                btn_accepted.ForeColor = Color.White;
                btn_accepted.Click += new EventHandler(btn_accepted_Click);
                panel_call.Controls.Add(btn_accepted);

                Button btn_refuse = new Button();
                btn_refuse.Font = new Font("΢���ź�", 20);
                btn_refuse.Size = new Size(140, 50);
                btn_refuse.Location = new Point(panel_call.Width / 2 + 10, pic_call.Top + pic_call.Height + 30);
                btn_refuse.Text = "�ܾ�";
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


        //��ʼ�Ự
        private void VideoCall_SessionStart_Handler(int roomId)
        {
            //�����л�
            HideAllPanel();

            switch (m_userIdentity)
            {
                case UserIdentityType.Agent:
                    showAgentServiceFace();
                    break;
                case UserIdentityType.Client:
                    lbl_tipMessage.Text = selectedQueue.QueueName + " - ���񴰿�";
                    break;
            }

            AnyChatCoreSDK.EnterRoom(roomId, "", 0);
            //AnyChatCoreSDK.EnterRoomEx(roomId, "", 0);
            SoundPlayer Player = new SoundPlayer();
            Player.Stream = Properties.Resources.system;
            Player.Play();
            Player.Dispose();

        }

        //������Ƶ��������
        void btn_accepted_Click(object sender, EventArgs e)
        {
            //������Ƶ���лظ�ָ�dwErrcode=0
            AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REPLY, ConversationMode.SuserId, 0, 0, 0, "");
       }

        // �ܾ���Ƶ��������
        void btn_refuse_Click(object sender, EventArgs e)
        {

            //������Ƶ���лظ�ָ�dwErrcode=100104
            AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REPLY, ConversationMode.SuserId, AC_ERROR_VIDEOCALL_REJECT, 0, 0, "");
            ConversationMode = null;
            InitFaceAfterEndCall(Properties.Resources._5, "�Ѿ��ܾ��Ự...");

            showQueueListFace();
        }


        /// <summary>
        /// ���뷿��ɹ�
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
                lbl_client_remoteUserName.Text = tUserItem.Name + "(��ϯ)";
                lbl_client_localUserName.Text = m_UserName + "(�Լ�)";
                OpenCameraAndSpeak(m_UserId, true);//���Լ�������Ƶ
                //panel_users.Hide();
                //panel_call.Hide();

            }

        }
        //����˫������Ƶ�豸
        public void OpenCameraAndSpeak(int userId, bool isopen)
        {

            if (isopen)
            {

                //�򿪺���������Ƶ
                AnyChatCoreSDK.UserCameraControl(userId, true);
                AnyChatCoreSDK.UserSpeakControl(userId, true);

                switch (m_userIdentity)
                {
                    case UserIdentityType.Agent:
                        if (userId == m_UserId)
                            //��ʾ��ϯ�˱�������Ƶ
                            AnyChatCoreSDK.SetVideoPos(userId, picBox_agent_localVideo.Handle, 0, 0, picBox_agent_localVideo.Width, picBox_agent_localVideo.Height);
                        else
                            AnyChatCoreSDK.SetVideoPos(userId, picBox_agent_remoteVideo.Handle, 0, 0, picBox_agent_remoteVideo.Width, picBox_agent_remoteVideo.Height);

                        break;

                    case UserIdentityType.Client:
                        if (userId == m_UserId)
                            //��ʾ��������Ƶ
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

            //����ˢ��
            timer_speak.Enabled = isopen;

        }

        //��Ƶ���лظ�
        private void VideoCall_Reply_Handler(int userId, int dwErrorCode, int wParam, string lpStr)
        {

            if (this.WindowState == FormWindowState.Minimized)
                this.WindowState = FormWindowState.Normal;
            RemoveCallButton();
            intCallTimer = 3;
            //ShowCallMessage(Properties.Resources._18, "�Ự�ѽ���...");
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
                    ShowCallMessage(Properties.Resources._20, "�Է�ȡ������...");
                    break;
                case AC_ERROR_VIDEOCALL_REJECT:
                    ShowCallMessage(Properties.Resources._5, "�Է��ܾ��Ự...");
                    break;
                case AC_ERROR_VIDEOCALL_BUSY:
                    ShowCallMessage(Properties.Resources._8, "Ŀ���û���æ,���Ժ�����...");
                    break;
                case AC_ERROR_VIDEOCALL_OFFLINE:
                    ShowCallMessage(Properties.Resources._18, "�Է�������...");
                    break;
                case AC_ERROR_VIDEOCALL_TIMEOUT:
                    ShowCallMessage(Properties.Resources._1, "�Ự�����ѳ�ʱ...");
                    break;
                case AC_ERROR_VIDEOCALL_DISCONNECT:
                    ShowCallMessage(Properties.Resources._18, "�Է�����Ͽ�...");
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

                AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_FINISH, getOtherInSession(), 0, 0, 0, "");                
            }

            Log.SetLog("VideoCall_Reply_Handler" + dwErrorCode);
           
        }

        //��Ƶ���н���
        private void VideoCall_Finished_Handler(Bitmap bit, string strMsg)
        {


            OpenCameraAndSpeak(-1, false);
            OpenCameraAndSpeak(getOtherInSession(), false);
            AnyChatCoreSDK.LeaveRoom(-1);
            InitFaceAfterEndCall(bit, strMsg);

            switch (m_userIdentity)
            {
                case UserIdentityType.Agent:

                    AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_CTRL_FINISHSERVICE, 0, 0, 0, 0, "");	

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

        //���н������ʼ������
        private void InitFaceAfterEndCall(Bitmap bit, string strMsg)
        {


            if (this.WindowState == FormWindowState.Minimized)
                this.WindowState = FormWindowState.Normal;
            RemoveCallButton();
            intCallTimer = 3;
            ShowCallMessage(bit, strMsg);
            timer_call.Start();

        }

        //�Ƴ��������̰�ť
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

        //��ʾ������Ϣ
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


        //����ˢ�¼�ʱ��
        int intSuserSpeakValue = 0;//����������
        int intTuserSpeakValue = 0;//����������
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

        //�������������ػ�
        private void pic_tuserSound_Paint(object sender, PaintEventArgs e)
        {

            Graphics g = e.Graphics;
            int width = intTuserSpeakValue * pic_tuserSound.Width / 100;
            g.FillRectangle(new SolidBrush(Color.SteelBlue), new Rectangle(new Point(0, 0), new Size(width, pic_tuserSound.Height)));

        }

        //�������������ػ�
        private void pic_suserSound_Paint(object sender, PaintEventArgs e)
        {

            Graphics g = e.Graphics;
            int width = intSuserSpeakValue * pic_tuserSound.Width / 100;
            g.FillRectangle(new SolidBrush(Color.SteelBlue), new Rectangle(new Point(0, 0), new Size(width, pic_tuserSound.Height)));

        }

        //������Ƶ���н���ָ��ҶϻỰ
        private void btn_hungUp_Click(object sender, EventArgs e)
        {

            //������Ƶ���лظ�ָ�dwErrcode=100104
            AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_FINISH, getOtherInSession(), 0, 0, 0, "");

        }

        /// <summary>
        /// ��ʾ��������
        /// </summary>
        private void showServiceArea()
        {

        }

        #endregion

        #region ��Ƶ�����¼�����
        private void VideoCallEvent_CallBack(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, string lpUserStr)
        {
            switch (dwEventType)
            {
                //���������¼�
                case AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REQUEST:
                    VideoCall_Request_Handler(dwUserId, dwParam, lpUserStr);
                    break;
                //���лظ��¼�
                case AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REPLY:
                    VideoCall_Reply_Handler(dwUserId, dwErrorCode, dwParam, lpUserStr);
                    break;
                //���п�ʼ�¼�
                case AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_START:
                    VideoCall_SessionStart_Handler(dwParam);
                    break;
                //���н����¼�
                case AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_FINISH:
                    VideoCall_Finished_Handler(Properties.Resources._18, "�Ự�ѽ���...");
                    break;
            }
        }
        #endregion

        #region ҵ������¼�����
        private void ObjectEvent_CallBack(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue)
        {
            switch (dwEventType)
            {
                case AnyChatCoreSDK.ANYCHAT_OBJECT_EVENT_UPDATE:
                    AnyChatObjectEventUpdate_Handler(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, strParam, lpUserValue);
                    break;
                case AnyChatCoreSDK.ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH:
                    AnyChatObjectSyncDataFinish_Handler(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, strParam, lpUserValue);
                    break;
                case AnyChatCoreSDK.ANYCHAT_AREA_EVENT_ENTERRESULT:
                    AnyChatEnterAreaResult_Handler(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, strParam, lpUserValue);
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
                    AnyChatAgentServiceNotify_Handler(dwParam1, dwParam2, dwParam3);
                    break;
                case AnyChatCoreSDK.ANYCHAT_AGENT_EVENT_WAITINGUSER:
                    AnyChatAgentWaitingUser_Handler();
                    break;

            }
            
        }

        /// <summary>
        /// ��������¼�
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        private void AnyChatObjectEventUpdate_Handler(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue)
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

                        //���ӷ���������ʾ
                        AreaInfo area = new AreaInfo();
                        area.AreaID = dwObjectId;
                        StringBuilder sbAreaName = new StringBuilder();                                                
                        //AnyChatCoreSDK.BRAC_ObjectGetValue(dwObjectType, dwObjectId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_NAME, sbAreaName);
                        //area.AreaName = sbAreaName.ToString();

                        byte[] areaNameByte = new byte[255];
                        AnyChatCoreSDK.BRAC_ObjectGetValue(dwObjectType, dwObjectId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_NAME, ref areaNameByte[0]);
                        area.AreaName = byteToString(areaNameByte);

                        byte[] areaDescByte = new byte[255];
                        AnyChatCoreSDK.BRAC_ObjectGetValue(dwObjectType, dwObjectId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_DESCRIPTION, ref areaDescByte[0]);
                        area.AreaDescription = byteToString(areaDescByte);

                        AddAreaToForm(area);

                        break;
                }
            }
            catch (Exception exp)
            {
                Log.SetLog("AnyChatObjectEventUpdate_Handler �쳣��" + exp.Message);

            }
        }

        private void AnyChatObjectSyncDataFinish_Handler(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue)
        {

        }

        /// <summary>
        /// �������������֪ͨ�¼�
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatEnterAreaResult_Handler(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam, int lpUserValue)
        {
            string areaName = string.Empty;

            byte[] areaNameByte = new byte[255];
            AnyChatCoreSDK.BRAC_ObjectGetValue(dwObjectType, dwObjectId, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_NAME, ref areaNameByte[0]);
            areaName = byteToString(areaNameByte);

            if (dwParam1 != 0)
                return;

            currentBusinessFunc = BusinessFuncType.SelectAreaFunc;

            switch (m_userIdentity)
            {
                //��ʾӪҵ���Ķ���
                case UserIdentityType.Client:
                    InitQueuePanel(areaName);

                    int idx = 0;
                    //��ȡӪҵ���ڵĶ�����Ϣ
                    AnyChatCoreSDK.BRAC_ObjectGetIdList(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, null, ref idx);
                    int[] queueIds = new int[idx];
                    AnyChatCoreSDK.BRAC_ObjectGetIdList(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueIds, ref idx);
                    for (int i = 0; i < queueIds.Length; i++)
                    {
                        int queueID = queueIds[i];
                        QueueInfo queue = new QueueInfo();
                        queue.QueueID = queueID;

                        byte[] queueNameByte = new byte[255];
                        AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_NAME, ref queueNameByte[0]);
                        queue.QueueName = byteToString(queueNameByte); ;

                        byte[] queueDescByte = new byte[255];
                        AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_DESCRIPTION, ref queueDescByte[0]);
                        queue.QueueDescription = byteToString(queueDescByte);

                        int queueUserCount = 0;
                        AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_LENGTH, ref queueUserCount);
                        queue.inQueueClientCount = queueUserCount;

                        AddQueueToForm(queue);
                    }


                    panel_queue.Show();

                    break;

                case UserIdentityType.Agent:
                    lbl_tipMessage.Text = "��ϯ���񴰿�";

                    comboBox_AgentStatus.SelectedIndex = 0;

                    showAgentServiceFace();

                    refreshAgentServiceInfo();
                    break;
            }

            panel_waitingMessage.Hide();
        }

        /// <summary>
        /// �뿪����������֪ͨ�¼�
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
        /// Ӫҵ��״̬�仯�¼�
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
        /// ������н��֪ͨ�¼�
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

                lbl_tipMessage.Text = selectedQueue.QueueName +  " - �Ŷӵȴ���";

            }

        }

        /// <summary>
        /// �뿪���н��֪ͨ�¼�
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

                //�뿪���к���ʾ�����б����
                RemoveWaitingMessageButton();

                showQueueListFace();

            }
        }

        /// <summary>
        /// �����û��������
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatUserEnterQueue_Handler(int dwObjectType, int dwObjectId, int dwErrorCode)
        {

        }

        /// <summary>
        /// �����û��뿪����
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatUserLeaveQueue_Handler(int dwObjectType, int dwObjectId, int dwErrorCode)
        {

        }

        /// <summary>
        /// ����״̬�仯���֪ͨ�¼�
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
        /// ��ϯ״̬�仯���֪ͨ�¼�
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwParam1"></param>
        private void AnyChatAgentStatusChange_Handler(int dwObjectType, int dwObjectId, int dwParam1)
        {
            var statusText = "��ϯ��ǰ״̬��";
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
                    lbl_CurrentStatus.Text = statusText + "����";
                    showAgentServiceFace();
                    comboBox_AgentStatus.Enabled = true;
                }
                if (dwParam1 == AnyChatCoreSDK.ANYCHAT_AGENT_STATUS_WORKING)
                {
                    lbl_CurrentStatus.Text = statusText + "æ";
                    comboBox_AgentStatus.Enabled = false;
                }
                if (dwParam1 == AnyChatCoreSDK.ANYCHAT_AGENT_STATUS_PAUSED)
                {
                    lbl_CurrentStatus.Text = statusText + "��ͣ";
                    comboBox_AgentStatus.Enabled = true;
                }
                if (dwParam1 == AnyChatCoreSDK.ANYCHAT_AGENT_STATUS_CLOSEED)
                {
                    lbl_CurrentStatus.Text = statusText + "�ر�";
                    comboBox_AgentStatus.Enabled = true;
                }
            }
        }

        /// <summary>
        /// ��ϯ����֪ͨ�¼�
        /// </summary>
        /// <param name="dwAgentId">��ϯId</param>
        /// <param name="clientId">����Ŀͻ�Id</param>
        /// <param name="dwQueueId">�ͻ����ڶ���Id</param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatAgentServiceNotify_Handler(int dwAgentId, int clientId, int dwQueueId)
        {
            if (m_userIdentity ==  UserIdentityType.Agent && m_UserId == dwAgentId)
            {
                refreshServicedUserInfo(clientId);

                //������Ƶ���У������������Ϊ�Զ������
                AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REQUEST, clientId, 0, 0, 0, m_UserName);
                intCallTimer = 10;
                mTargetUserId = clientId;
                ShowCallMessage(Properties.Resources._23, "���ڷ�����Ƶ��������...");
                timer_call.Start();
            }

        }

        /// <summary>
        /// ��ϯ�ȴ��û�֪ͨ�¼�
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwErrorCode"></param>
        private void AnyChatAgentWaitingUser_Handler()
        {
            MessageBox.Show("��������û�пͻ���");
            btn_return.Enabled = true;
            btnStartService.Enabled = true;
            btnStopService.Enabled = false;
        }

        #endregion

        #region ��������

        /// <summary>
        /// ����ID��ȡ�û�����(���ܻ�ȡ�Լ���)
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        private UserInfo GetUserInfoByUserId(int id)
        {
            UserInfo mode = new UserInfo();

            byte[] userNameByte = new byte[255];
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_CLIENTUSER, id, AnyChatCoreSDK.ANYCHAT_OBJECT_INFO_NAME, ref userNameByte[0]);
            mode.Id = id;
            mode.Name = byteToString(userNameByte);
            return mode;
        }

        /// <summary>
        /// ��ȡͨ���е�����һ��
        /// </summary>
        /// <returns>ͨ��������һ����userid</returns>
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
        /// ��ʽ����Ϊ����:�롱��ʽ
        /// </summary>
        /// <param name="second"></param>
        /// <returns></returns>
        private string formatSeconds(int second)
        {

            string retVal = string.Empty;

            int s = second;
            int min = 0;// ��
            if (s > 60)
            {
                min = s / 60;
                s = s % 60;
                if (min > 60)
                {
                    min = min % 60;
                }
            }

            retVal = "" + s + "��";
            if (min > 0)
            {
                retVal = "" + min + "��" + retVal;
            }

            return retVal;

        }

        #endregion

        #region ��ʱ�����ƺ��й��̽�����ʾ

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
                Log.SetLog("QueueClient.Hall.timer_call_Tick       timer_call_Tick��" + ex.Message.ToString());
            }
        }
        #endregion

        #region Ӫҵ�����ݴ���

        /// <summary>
        /// ÿ��Ӫҵ��֮��ļ��
        /// </summary>
        int areaInterval = 30;
        int intAreaLeft = 0;
        int intAreaTop = 30;

        /// <summary>
        /// ��ʼ��װ��Ӫҵ�����ݵ�panel
        /// </summary>
        private void InitAreaPanel()
        {

            intAreaLeft = 0;
            intAreaTop = 30;
            //pan_users.Controls.Clear();
            panel_area.Controls.Clear();

            panel_area.Show();
            lbl_tipMessage.Text = "Ӫҵ���б�";
        }

        /// <summary>
        /// ���Ӫҵ����������
        /// </summary>
        /// <param name="mode"></param>
        private void AddAreaToForm(AreaInfo mode)
        {
            PictureBox areaBox = new PictureBox();
            areaBox.Name = "area" + mode.AreaID;
            areaBox.Tag = mode;
            //ÿ��areaBox�Ŀ��Ϊ300���߶�Ϊ120
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
        /// ����뿪Ӫҵ��
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
        /// ������Ӫҵ��
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
        /// ����Ӫҵ��ͼ��
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
                g.DrawString(mode.AreaName, new Font("΢���ź�", 16), new SolidBrush(Color.White), new RectangleF(new PointF(Properties.Resources.area.Width + 20, 20), new SizeF(170, 50)));
                g.DrawString("��ţ�" + mode.AreaID, new Font("΢���ź�", 12), new SolidBrush(Color.White), new RectangleF(new PointF(Properties.Resources.area.Width + 20, 75), new SizeF(170, 35)));
                //g.DrawString(mode.AreaDescription, new Font("΢���ź�", 12), new SolidBrush(Color.White), new RectangleF(new PointF(Properties.Resources.area.Width + 5, 85), new SizeF(170, 35)));
            }
            catch (Exception ex)
            {
                Log.SetLog("QueueClient.Hall.area_Paint       area_Paint��" + ex.Message.ToString());
            }
        }

        /// <summary>
        /// ����Ӫҵ��
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void area_Click(object sender, EventArgs e)
        {
            try
            {
                ShowWaitingMessage(Properties.Resources._15, "���ڽ���Ӫҵ�������Ժ�......");

                isEnterArea = true;

                PictureBox area = sender as PictureBox;
                AreaInfo mode = area.Tag as AreaInfo;
                int tAreaID = mode.AreaID;

                queueList.Clear();

                //����Ӫҵ��
                int retCode = AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AREA, tAreaID, AnyChatCoreSDK.ANYCHAT_AREA_CTRL_USERENTER, 0, 0, 0, 0, string.Empty);

                selectedArea = mode;
            }
            catch (Exception exp)
            {
                Log.SetLog("QueueClient.Hall.area_Click       area_Click��" + exp.Message.ToString());

            }
        }

        #endregion

        #region �������ݴ���
        /// <summary>
        /// ÿ������֮��ļ��
        /// </summary>
        int queueInterval = 50;
        int intQueueLeft = 0;
        int intQueueTop = 30;

        /// <summary>
        /// ��ʼ��װ�ض������ݵ�panel
        /// </summary>
        private void InitQueuePanel(string areaName)
        {

            intQueueLeft = 0;
            intQueueTop = 30;
            //pan_users.Controls.Clear();
            panel_queue.Controls.Clear();

            //panel_area.Hide();
            if (panel_area.Visible) panel_area.Hide();

            lbl_tipMessage.Text = areaName +" �����б�";

            panel_queue.Dock = DockStyle.Fill;
        }

        /// <summary>
        /// ��Ӷ��е�������
        /// </summary>
        /// <param name="mode"></param>
        private void AddQueueToForm(QueueInfo mode)
        {
            PictureBox queueBox = new PictureBox();
            queueBox.Name = "queue" + mode.QueueID;
            queueBox.Tag = mode;
            //ÿ��areaBox�Ŀ��Ϊ440���߶�Ϊ150
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
        /// ����뿪����
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
        /// ���������
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
        /// ���ƶ���ͼ��
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

                g.DrawString(mode.QueueName+"("+ "��ţ�" + mode.QueueID +")", new Font("΢���ź�", 16), new SolidBrush(Color.White), new RectangleF(new PointF(queueXPoint + 20, 20), new SizeF(350, 50)));                
                g.DrawString(mode.QueueDescription + "(��ǰ�Ŷ�������" + mode.inQueueClientCount + "��)", new Font("΢���ź�", 12), new SolidBrush(Color.White), new RectangleF(new PointF(queueXPoint + 50, 85), new SizeF(380, 40)));
            }
            catch (Exception ex)
            {
                Log.SetLog("QueueClient.Hall.area_Paint       area_Paint��" + ex.Message.ToString());
            }
        }

        /// <summary>
        /// ��������
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
                    //�������

                    EnterQueueWaitingProcess();

                    AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, selectedQueue.QueueID, AnyChatCoreSDK.ANYCHAT_QUEUE_CTRL_USERENTER, 0, 0, 0, 0, "");
                    break;

                case UserIdentityType.Agent:
                    //��ʾ��ϯ��Ƶ���н���

                    break;
            }

        }

        /// <summary>
        /// �û�������к�ȴ�����
        /// </summary>
        private void EnterQueueWaitingProcess()
        {
            try
            {
                ShowWaitingMessage(Properties.Resources._15, enterQueueWaitingMessage);
                lbl_waitingMessage.Text = string.Empty;

                //timer_call.Start();
                //timer_call.Stop();//�رռ�ʱ����ȷ��״̬
                Button btnCancel = new Button();
                btnCancel.Font = new Font("΢���ź�", 20);
                btnCancel.Size = new Size(140, 50);
                btnCancel.Location = new Point(panel_waitingMessage.Width / 2 - btnCancel.Width / 2, picBox_waiting.Top + picBox_waiting.Height + 40);
                btnCancel.Text = "ȡ��";
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

                Log.SetLog("QueueClient.Hall.EnterQueueWaitingProcess       EnterQueueWaitingProcess��" + ex.Message.ToString());
            }
        }

        /// <summary>
        /// ����ȡ���Ŷ�
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void btnCancel_Click(object sender, EventArgs e)
        {

            //�뿪����
            AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, selectedQueue.QueueID, AnyChatCoreSDK.ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");
            
            
        }

        //ˢ���û�������к��Ŷӵȴ�ʱ����ʾ��Ϣ
        private void refreshUserWaitingInfo(int queueID) {
            int queueUserNum = 0; //��ǰ��������
            int beforeUserNum = 0; //�����Լ�ǰ��Ķ�������

            //��ȡ��ǰ��������
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_LENGTH, ref queueUserNum);

            //��ȡ�����Լ�ǰ����û���
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_BEFOREUSERNUM, ref beforeUserNum);
            beforeUserNum = beforeUserNum < 0 ? 0 : beforeUserNum;
            beforeUserNum++;

            lbl_waitingMessage.Text = "��ǰ�Ŷ���������" + queueUserNum.ToString() + " �ˣ����������ڵ� " + beforeUserNum.ToString() + " λ";
        }

        /// <summary>
        /// �Ŷӵȴ�ʱ�䴥������
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer_queueWaiting_Tick(object sender, EventArgs e)
        {
            int second = 0;

            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, selectedQueue.QueueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_WAITTIMESECOND, ref second);
            string strTime = formatSeconds(second);

            lbl_waitingTime.Text = "�ѵȴ�ʱ�䣺" + strTime;
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
        /// ˢ�¶�����ʾ��Ϣ�������������
        /// </summary>
        /// <param name="queueID"></param>
        private void refreshQueueInfoDisplay(QueueInfo queueID)
        {
            int queueUserNum = 0;
            //��ȡ��ǰ��������
            AnyChatCoreSDK.BRAC_ObjectGetValue(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_QUEUE, queueID.QueueID, AnyChatCoreSDK.ANYCHAT_QUEUE_INFO_LENGTH, ref queueUserNum);
            queueID.inQueueClientCount = queueUserNum;

            PictureBox picBox = queueID.bindedOjbect as PictureBox;
            picBox.Refresh();

        }

        #endregion

        private void comboBox_AgentStatus_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBox_AgentStatus.SelectedIndex){
                case 0:
                    AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_CTRL_SERVICESTATUS, AnyChatCoreSDK.ANYCHAT_AGENT_STATUS_WAITTING, 0, 0, 0, "");	
                    break;
                case 1:
                    break;
                case 2:
                    AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_CTRL_SERVICESTATUS, AnyChatCoreSDK.ANYCHAT_AGENT_STATUS_PAUSED, 0, 0, 0, "");	
                    break;
                case 3:
                    AnyChatCoreSDK.BRAC_ObjectControl(AnyChatCoreSDK.ANYCHAT_OBJECT_TYPE_AGENT, m_UserId, AnyChatCoreSDK.ANYCHAT_AGENT_CTRL_SERVICESTATUS, AnyChatCoreSDK.ANYCHAT_AGENT_STATUS_CLOSEED, 0, 0, 0, "");
                    break;
            }

        }

        /// <summary>
        /// �ֽ�ת�ַ���
        /// </summary>
        /// <param name="byteStr">�ֽ�����</param>
        /// <returns>ת������ַ���</returns>
        public string byteToString(byte[] byteStr)
        {
            string retVal = "";
            try
            {
                retVal = System.Text.Encoding.GetEncoding("GB18030").GetString(byteStr, 0, byteStr.Length);
            }
            catch(Exception exp)
            {
                Console.Write(exp.Message);
            }
            return retVal.TrimEnd('\0');
        }

    }
}
