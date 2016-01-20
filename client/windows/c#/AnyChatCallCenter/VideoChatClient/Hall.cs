using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using VideoChatHelp;
using ANYCHATAPI;
using System.Runtime.InteropServices;
using System.Media;
using System.Threading;

namespace VideoChatClient
{
    public partial class Hall : Form
    {
        #region 变量定义
        int m_UserId = -1;
        string m_UserName = "";
        int intCallTimer = 0;
        private List<UserInfo> users = new List<UserInfo>();
        public const int AC_ERROR_VIDEOCALL_CANCEL = 100101;       ///  源用户主动放弃会话
        public const int AC_ERROR_VIDEOCALL_OFFLINE=100102;      ///< 目标用户不在线
        public const int AC_ERROR_VIDEOCALL_BUSY=100103;       ///< 目标用户忙
        public const int AC_ERROR_VIDEOCALL_REJECT=100104;       ///< 目标用户拒绝会话
        public const int AC_ERROR_VIDEOCALL_TIMEOUT=100105;       ///< 会话请求超时
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
        #endregion

        #region 构造函数

        public Hall()
        {
            InitializeComponent();
        }

        public Hall(int r_UserId, string r_UserName)
        {
            m_UserId = r_UserId;
            m_UserName = r_UserName;

            //this.loginForm = loginForm;
            InitializeComponent();
        }

        #endregion

        #region 初始化

        //窗体加载
        private void Hall_Load(object sender, EventArgs e)
        {
           
                SystemSetting.VideoCallEvent_Handler = new SystemSetting.VideoCallEventCallBack(VideoCallEvent_CallBack);
                pan_users.Dock = DockStyle.Fill;

          
        }

        //窗体关闭
        private void Hall_FormClosed(object sender, FormClosedEventArgs e)
        {
          
                AnyChatCoreSDK.Logout();
                AnyChatCoreSDK.Release();
                Application.Exit();
                bReleased = true;
                //Login loginForm = new Login();
                //loginForm.Close();
            
           
        }

        #endregion

        #region 用户

        int intg = 30;
        int intUserLeft = 0;
        int intUserTop = 30;

        //界面添加用户
        private void AddUser(UserInfo mode)
        {
                PictureBox user = new PictureBox();
                user.Name = "user" + mode.Id.ToString();
                user.Tag = mode;
                user.Size = new Size(300, 120);
                if (intUserLeft < user.Width * 3 + intg * 2)
                    intUserLeft += intg;
                else
                {
                    intUserLeft = intg;
                    intUserTop += intg + user.Height;
                }
                user.Location = new Point(intUserLeft, intUserTop);
                intUserLeft += 300;
                user.BackColor = mode.Id == m_UserId ? Color.DarkSeaGreen : Color.LightSteelBlue;
                user.Paint += new PaintEventHandler(user_Paint);
                user.MouseEnter += new EventHandler(user_MouseEnter);
                user.MouseLeave += new EventHandler(user_MouseLeave);
                user.DoubleClick += new EventHandler(user_DoubleClick);
                pan_users.Controls.Add(user);
                
          
        }
        //界面移除用户
        private void RemoveUser(UserInfo mode)
        {
           
                //移除用户
                foreach (Control c in pan_users.Controls)
                {
                    UserInfo u = c.Tag as UserInfo;
                    if (u.Id == mode.Id)
                    {
                        pan_users.Controls.Remove(c);
                        break;
                    }
                }


                //整理其他用户坐标
                intUserLeft = 0;
                intUserTop = 30;
                foreach (Control c in pan_users.Controls)
                {
                    if (intUserLeft < 300 * 3 + 30 * 2)
                        intUserLeft += intg;
                    else
                    {
                        intUserLeft = intg;
                        intUserTop += intg + 120;
                    }
                    c.Location = new Point(intUserLeft, intUserTop);
                    intUserLeft += 300;
                }
          
        }

        //鼠标离开
        void user_MouseLeave(object sender, EventArgs e)
        {
            
                PictureBox mode = sender as PictureBox;
                UserInfo umode = mode.Tag as UserInfo;
                mode.BackColor = umode.Id == m_UserId ? Color.DarkSeaGreen : Color.LightSteelBlue;
           
        }
        //鼠标进入
        void user_MouseEnter(object sender, EventArgs e)
        {
           
                PictureBox mode = sender as PictureBox;
                UserInfo umode = mode.Tag as UserInfo;
                mode.BackColor = umode.Id == m_UserId ? Color.DarkSeaGreen : Color.SteelBlue;
           
            
        }
        //绘制图标
        void user_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                UserInfo mode = (sender as PictureBox).Tag as UserInfo;
                Graphics g = e.Graphics;
                g.DrawImage(Properties.Resources._10, new Point(0, 0));
                g.DrawString(mode.Name, new Font("微软雅黑", 18), new SolidBrush(Color.White), new RectangleF(new PointF(Properties.Resources._10.Width, 20), new SizeF(170, 65)));
                g.DrawString("IP : " + mode.Ip, new Font("微软雅黑", 12), new SolidBrush(Color.White), new RectangleF(new PointF(Properties.Resources._10.Width, 55), new SizeF(170, 35)));
                g.DrawString("ID : " + mode.Id, new Font("微软雅黑", 12), new SolidBrush(Color.White), new RectangleF(new PointF(Properties.Resources._10.Width, 85), new SizeF(170, 35)));
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.user_Paint       user_Paint：" + ex.Message.ToString());
            }
        }

        //用户在线状态改变
        public void OnUserOnlineStatusChange(int userId,int onlienStatus)
        {
           
                UserInfo userItem = GetUserInfoByUserId(userId);
              
                if (onlienStatus == USER_OFFLINE)//用户离线
                {
                    if (userItem != null)
                    {
                        RemoveUser(userItem);
                        users.Remove(userItem);
                    }
                }
            
           
        }
        #endregion

        #region 视频呼叫业务实际处理

        //双击视频呼叫
        void user_DoubleClick(object sender, EventArgs e)
        {
           
                PictureBox user = sender as PictureBox;
                UserInfo mode = user.Tag as UserInfo;
                int tUserId=mode.Id;
                if (tUserId != m_UserId)
                {
                    //发送视频呼叫，最后两个参数为自定义参数
                    AnyChatCoreSDK.VideoCallControl(AnyChatCoreSDK.BRAC_VIDEOCALL_EVENT_REQUEST,tUserId,0,0,0,m_UserName);
                    intCallTimer = 10;
                    ShowCallMessage(Properties.Resources._23, "正在发起呼叫请求...");
                    timer_call.Start();
                }
           
        }
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
                btn_cancall.Location = new Point(pan_call.Width / 2 - btn_cancall.Width / 2, pic_call.Top + pic_call.Height + 30);
                btn_cancall.Text = "取消";
                btn_cancall.Tag = "btn";
                btn_cancall.BackColor = Color.Red;
                btn_cancall.ForeColor = Color.White;
                btn_cancall.Click += new EventHandler(btn_cancall_Click);
                pan_call.Controls.Add(btn_cancall);
                SoundPlayer Player = new SoundPlayer();
                Player.Stream = Properties.Resources.ring;
                Player.Play();
                Player.Dispose();
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.WaitCall       WaitCall：" + ex.Message.ToString());
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
           
        }
        //接收到视频呼叫请求处理
       
        private void VideoCall_Request_Handler(int dwUserId, int dwParam, string lpUserStr)
        {
           
                if (this.WindowState == FormWindowState.Minimized)
                    this.WindowState = FormWindowState.Normal;
                timer_call.Stop();//关闭计时器，确认状态
                ConversationMode = new ConversationInfo();
                ConversationMode.SuserId = dwUserId;
                ConversationMode.TuserId = m_UserId;
                UserInfo userItem = GetUserInfoByUserId(dwUserId);
                if (userItem != null)
                {
                    ShowCallMessage(Properties.Resources._14, userItem.Name + "向您发起视频会话邀请...");

                    Button btn_accepted = new Button();
                    btn_accepted.Font = new Font("微软雅黑", 20);
                    btn_accepted.Size = new Size(140, 50);
                    btn_accepted.Location = new Point(pan_call.Width / 2 - btn_accepted.Width - 10, pic_call.Top + pic_call.Height + 30);
                    btn_accepted.Text = "接受";
                    btn_accepted.Tag = "btn";
                    btn_accepted.BackColor = Color.Lime;
                    btn_accepted.ForeColor = Color.White;
                    btn_accepted.Click += new EventHandler(btn_accepted_Click);
                    pan_call.Controls.Add(btn_accepted);

                    Button btn_refuse = new Button();
                    btn_refuse.Font = new Font("微软雅黑", 20);
                    btn_refuse.Size = new Size(140, 50);
                    btn_refuse.Location = new Point(pan_call.Width / 2 + 10, pic_call.Top + pic_call.Height + 30);
                    btn_refuse.Text = "拒绝";
                    btn_refuse.Tag = "btn";
                    btn_refuse.BackColor = Color.Red;
                    btn_refuse.ForeColor = Color.White;
                    btn_refuse.Click += new EventHandler(btn_refuse_Click);
                    pan_call.Controls.Add(btn_refuse);

                    SoundPlayer Player = new SoundPlayer();
                    Player.Stream = Properties.Resources.ring;
                    Player.Play();
                    Player.Dispose();
                }
        }

     
        //开始会话
        private void VideoCall_SessionStart_Handler(int roomId)
        {
          
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
          
        }
     

        //进入房间成功
        public void EnterRoomSuccess()
        {
           
                timer_call.Stop();
                Bitmap bit = Properties.Resources._28;
                bit.RotateFlip(RotateFlipType.Rotate180FlipY);
                //pic_suser.Image = bit;
                UserInfo tUserItem = GetUserInfoByUserId(getOtherInSession());
                if (tUserItem != null)
                {
                    lb_tuserName.Text = tUserItem.Name;
                    lb_suserName.Text = m_UserName;
                    OpenCameraAndSpeak(m_UserId, true);//打开自己的音视频
                    pan_users.Hide();
                    pan_call.Hide();
                    pan_conversation.Dock = DockStyle.Fill;
                    pan_conversation.Show();
                }
         
        }
        //操作双方音视频设备
        public void OpenCameraAndSpeak(int userId,bool isopen)
        {
           
                if (isopen)
                {
                    #region 打开屏幕共享功能的逻辑代码
                    /*
                    //本人
                    if (userId == m_UserId)
                    {
                        int deviceNum = 0;
                        AnyChatCoreSDK.EnumVideoCapture(null, ref deviceNum);
                        IntPtr[] deviceList = new IntPtr[deviceNum];                        

                        AnyChatCoreSDK.EnumVideoCapture(deviceList, ref deviceNum);
                        for (int idx = 0; idx < deviceNum; idx++)
                        {
                            IntPtr intPtr = deviceList[idx];
                            int len = 100;
                            byte[] byteArray = new byte[len];
                            Marshal.Copy(intPtr, byteArray, 0, len);
                            string m_DeviceName = Encoding.Default.GetString(byteArray);
                            m_DeviceName = m_DeviceName.Substring(0, m_DeviceName.IndexOf('\0'));

                            if (m_DeviceName.IndexOf("Native Screen Camera") > 0)
                            {
                                AnyChatCoreSDK.SelectVideoCapture(m_DeviceName);

                                //设置视频参数
                                int screenWidth = 1920;
                                int screenHeight = 1080;
                                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_WIDTHCTRL, ref screenWidth, sizeof(int));
                                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, ref screenHeight, sizeof(int));

                                int bitrateCtrl = 0;
                                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_BITRATECTRL, ref bitrateCtrl, sizeof(int));

                                int fpsCtrl = 15;
                                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_FPSCTRL, ref fpsCtrl, sizeof(int));

                                int gopCtrol = 60;
                                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_GOPCTRL, ref gopCtrol, sizeof(int));

                                int presetCtrl = 3;
                                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_PRESETCTRL, ref presetCtrl, sizeof(int));

                                int qualityCtrl = 3;
                                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_QUALITYCTRL, ref qualityCtrl, sizeof(int));

                                int m_AppLocal = 1;
                                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_APPLYPARAM, ref m_AppLocal, sizeof(int));

                                break;
                            }
                        }
                    }
                    */
                    #endregion

                    //打开呼叫者音视频
                    AnyChatCoreSDK.UserCameraControl(userId, true);
                    AnyChatCoreSDK.UserSpeakControl(userId, true);


                    if (userId == m_UserId)
                    {                        
                        AnyChatCoreSDK.SetVideoPos(userId, pic_suserVideo.Handle, 0, 0, pic_suserVideo.Width, pic_suserVideo.Height);
                    }
                    else
                        AnyChatCoreSDK.SetVideoPos(userId, pic_tuserVideo.Handle, 0, 0, pic_tuserVideo.Width, pic_tuserVideo.Height);
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
        private void VideoCall_Reply_Handler(int userId,int dwErrorCode,int wParam,string lpStr)
        {
          
                if (this.WindowState == FormWindowState.Minimized)
                    this.WindowState = FormWindowState.Normal;
                RemoveCallButton();
                intCallTimer = 3;
                ShowCallMessage(Properties.Resources._18, "会话已结束...");
                ConversationMode = null;
                switch(dwErrorCode)
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
                if(dwErrorCode!=0)
                     timer_call.Start();
                Log.SetLog("VideoCall_Reply_Handler" + dwErrorCode);
          
          
     

           
        }

        //视频呼叫结束
        private void VideoCall_Finished_Handler(Bitmap bit,string strMsg)
        {


                OpenCameraAndSpeak(-1, false);
                OpenCameraAndSpeak(getOtherInSession(),false);
                AnyChatCoreSDK.LeaveRoom(-1);
                InitFaceAfterEndCall(bit, strMsg);
          
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
          
                foreach (Control c in pan_call.Controls)
                {
                    if (c.Tag != null)
                    {
                        if (c.Tag.ToString() == "btn")
                        {
                            pan_call.Controls.Remove(c);
                            RemoveCallButton();
                            break;
                        }
                    }
                }
        
        }

        //提示呼叫消息
        private void ShowCallMessage(Bitmap bit, string str)
        {
           
                pan_conversation.Hide();
                pan_users.Hide();
                pan_call.Dock = DockStyle.Fill;
                pan_call.Show();
                pic_call.Image = bit;
                lb_call.Text = str;
                //if (intCallTimer > 1)
                //    lb_call.Text += intCallTimer.ToString();
                lb_call.Tag = str;

                pic_call.Location = new Point(pan_call.Width / 2 - (pic_call.Width + lb_call.Width) / 2, pan_call.Height / 2 - pic_call.Height / 2 - 50 / 2);
                lb_call.Location = new Point(pic_call.Location.X + pic_call.Width, pic_call.Location.Y + pic_call.Height - lb_call.Height - 15);
          
        }
     

        //音量刷新计时器
        int intSuserSpeakValue = 0;//主动方音量
        int intTuserSpeakValue = 0;//被动方音量
        private void timer_speak_Tick(object sender, EventArgs e)
        {
          
                if(ConversationMode!=null)
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

        #region 透明通道

        //透明通道回调函数
        public void TransBuffer_CallBack(int userId, IntPtr buf, int len, int userValue)
        {
            
          
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
                    VideoCall_Reply_Handler(dwUserId,dwErrorCode, dwParam, lpUserStr);
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

        #region 帮助函数

        /// <summary>
        /// 发送透明通道
        /// </summary>
        /// <param name="tuserid">目标ID</param>
        /// <param name="cmd">指令ID</param>
        /// <param name="os">参数</param>
        /// <returns>调用结果</returns>
        internal int TranBuff(int tuserid, int cmd, params ParamInfo[] os)
        {
            int ret = -1;
            try
            {
                string strCmd = CommandHelp.GenerateCommand(cmd, os);
                byte[] buff = Encoding.Default.GetBytes(strCmd);
                AnyChatCoreSDK.TransBuffer(tuserid, buff, buff.Length);
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.TranBuff       TranBuff：" + ex.Message.ToString());
            }
            return ret;
        }

        /// <summary>
        /// 根据ID获取用户对象(不能获取自己的)
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        private UserInfo GetUserInfoByUserId(int id)
        {
            UserInfo mode = null;
            if (id == m_UserId)
            {
                mode = new UserInfo();
                mode.Id = id;
                mode.Name = m_UserName;
            }

            foreach (UserInfo u in users)
            {
                if (u.Id == id)
                {
                    mode = u;
                    break;
                }
            }          
            return mode;
        }

        /// <summary>
        /// 获取通话中的另外一方
        /// </summary>
        /// <returns>通话中另外一方的userid</returns>
       public int getOtherInSession()
       {
           if(ConversationMode!=null)
           {
               if (ConversationMode.SuserId == m_UserId)
                   return ConversationMode.TuserId;
               else
                   return ConversationMode.SuserId;
           }
           return 0;
       }
       /// <summary>
       /// 获取在线好友数据
       /// </summary>
        public void getOnlineFriendInfos()
        {
            users.Clear();
            InitUserPanl();
            UserInfo selfUserItem = new UserInfo();
            selfUserItem.Id = m_UserId;
            selfUserItem.Name = m_UserName;
            StringBuilder str = new StringBuilder();
            AnyChatCoreSDK.QueryUserState(selfUserItem.Id, AnyChatCoreSDK.BRAC_USERSTATE_INTERNETIP, str, 15);
            selfUserItem.Ip = str.ToString();
            AddUser(selfUserItem);
            int num=0;
            AnyChatCoreSDK.GetUserFriends(null,ref num);
            int[] friendIds = new int[num];
            AnyChatCoreSDK.GetUserFriends(friendIds, ref num);
            for (int i = 0; i < friendIds.Length;i++ )
            {
                int onlineStatus = 0;
                int friendId = friendIds[i];
                AnyChatCoreSDK.GetFriendStatus(friendId, ref onlineStatus);
                Log.SetLog("GetFriendStatus: " + "用户id:" + friendId + "在线状态:" + onlineStatus);
                if(onlineStatus==USER_OFFLINE)
                {
                    continue;
                }
                UserInfo userItem = new UserInfo();
                StringBuilder friendInfo = new StringBuilder(30);
                int lenth = 30;
                userItem.Id = friendId;
                AnyChatCoreSDK.GetUserInfo(friendId, USERDATA_USERNAME, friendInfo, lenth);
                string userName = friendInfo.ToString();
                userItem.Name = friendInfo.ToString();
                AnyChatCoreSDK.GetUserInfo(friendId, USERDATA_USERADRESSIP, friendInfo, lenth);
                string userIp = friendInfo.ToString();
                userItem.Ip = friendInfo.ToString();
                bool ishave = false;
                foreach (UserInfo u in users)
                {
                    if (u.Id == userItem.Id)
                    {
                        ishave = true;
                        break;
                    }
                }
                if (!ishave)
                    users.Add(userItem);
                AddUser(userItem);

            }


        }
        /// <summary>
        /// 初始化装载用户数据的panl
        /// </summary>
        private void InitUserPanl()
        {

            intUserLeft = 0;
            intUserTop = 30;
            pan_users.Controls.Clear();
           
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
                 
                   pan_call.Hide();
                   pan_conversation.Hide();
                   pan_users.Show();
                   timer_call.Stop();
               }
           }
           catch (Exception ex)
           {
               Log.SetLog("VideoChat.Hall.timer_call_Tick       timer_call_Tick：" + ex.Message.ToString());
           }
       }
    }
     #endregion
}
