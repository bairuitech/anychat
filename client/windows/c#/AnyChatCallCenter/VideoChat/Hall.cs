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

namespace VideoChat
{
    public partial class Hall : Form
    {
        int m_UserId = -1;
        string m_UserName = "";

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

        #region 定义

        //private Login loginForm;

        private List<UserInfo> users = new List<UserInfo>();

        #endregion

        #region 初始化

        //窗体加载
        private void Hall_Load(object sender, EventArgs e)
        {
            try
            {
                pan_users.Dock = DockStyle.Fill;

                UserInfo mode = new UserInfo();
                mode.Id = m_UserId;
                mode.Name = m_UserName;

                StringBuilder str = new StringBuilder();
                AnyChatCoreSDK.QueryUserState(mode.Id, AnyChatCoreSDK.BRAC_USERSTATE_INTERNETIP, str, 15);
                mode.Ip = str.ToString();

                AddUser(mode);

                //请求当前在线用户数据
                TranBuff(0, Promise.ICS_CMD_DATAREQUEST,
                    new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), m_UserId.ToString()),
                    new ParamInfo(CommandHelp.ParamEnum.DATATYPE.ToString(), Promise.ICS_DATATYPE_ONLINEUSERS.ToString()));
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.Hall_Load       Hall_Load：" + ex.Message.ToString());
            }
        }

        //窗体关闭
        private void Hall_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                AnyChatCoreSDK.Logout();
                AnyChatCoreSDK.Release();
                Application.Exit();
                //Login loginForm = new Login();
                //loginForm.Close();
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.Hall_FormClosed       Hall_FormClosed：" + ex.Message.ToString());
            }
        }

        #endregion

        #region 用户

        int intg = 30;
        int intUserLeft = 0;
        int intUserTop = 30;

        //界面添加用户
        private void AddUser(UserInfo mode)
        {
            try
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
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.AddUser       AddUser：" + ex.Message.ToString());
            }
        }
        //界面移除用户
        private void RemoveUser(UserInfo mode)
        {
            try
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
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.RemoveUser       RemoveUser：" + ex.Message.ToString());
            }
        }

        //鼠标离开
        void user_MouseLeave(object sender, EventArgs e)
        {
            try
            {
                PictureBox mode = sender as PictureBox;
                UserInfo umode = mode.Tag as UserInfo;
                mode.BackColor = umode.Id == m_UserId ? Color.DarkSeaGreen : Color.LightSteelBlue;
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.user_MouseLeave       user_MouseLeave：" + ex.Message.ToString());
            }
        }
        //鼠标进入
        void user_MouseEnter(object sender, EventArgs e)
        {
            try
            {
                PictureBox mode = sender as PictureBox;
                UserInfo umode = mode.Tag as UserInfo;
                mode.BackColor = umode.Id == m_UserId ? Color.DarkSeaGreen : Color.SteelBlue;
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.user_MouseEnter       user_MouseEnter：" + ex.Message.ToString());
            }
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

        //其他用户登录
        private void UserLogin(List<ParamInfo> os)
        {
            try
            {
                UserInfo mode = new UserInfo();
                mode.Id = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.DATA_USERID.ToString()).Value);
                mode.Name = CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.DATA_USERNAME.ToString()).Value;
                mode.Ip = CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.DATA_USERIP.ToString()).Value;
                bool ishave = false;
                foreach (UserInfo u in users)
                {
                    if (u.Id == mode.Id)
                    {
                        ishave = true;
                        break;
                    }
                }
                if (!ishave)
                    users.Add(mode);
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.UserLogin       UserLogin：" + ex.Message.ToString());
            }
        }

        //用户状态改变
        private void UserStatus(List<ParamInfo> os)
        {
            try
            {
                int status = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.WPARAM.ToString()).Value);
                int userid = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.OBJECTID.ToString()).Value);
                if (status == Promise.ICS_STATUSTYPE_USERONLINE)//用户上线
                {
                    UserInfo mode = GetUserInfoById(userid);
                    if (mode != null)
                    {
                        foreach (Control c in pan_users.Controls)
                        {
                            UserInfo u = c.Tag as UserInfo;
                            if (u.Id == mode.Id)
                            {
                                pan_users.Controls.Remove(c);
                                break;
                            }
                        }
                        AddUser(mode);
                    }
                }
                else if (status == Promise.ICS_STATUSTYPE_USERONLINE_FONLINE)//用户离线
                {
                    UserInfo mode = GetUserInfoById(userid);
                    if (mode != null)
                    {
                        RemoveUser(mode);
                        users.Remove(mode);
                    }
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.UserStatus       UserStatus：" + ex.Message.ToString());
            }
        }

        //数据接收完成
        private void DataFinish(List<ParamInfo> os)
        {
            try
            {
                string wparam = CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.WPARAM.ToString()).Value;
                if (wparam == Promise.ICS_DATATYPE_ONLINEUSERS.ToString())//请求在线用户数据结束时
                {
                    foreach (UserInfo u in users)
                    {
                        AddUser(u);
                    }
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.DataFinish       DataFinish：" + ex.Message.ToString());
            }
        }

        #endregion

        #region 1对1会话

        //双击呼叫
        void user_DoubleClick(object sender, EventArgs e)
        {
            try
            {
                PictureBox user = sender as PictureBox;
                UserInfo mode = user.Tag as UserInfo;
                if (mode.Id != m_UserId)
                {
                    //请求会话
                    TranBuff(0, Promise.ICS_CMD_SESSIONREQUEST,
        new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), m_UserId.ToString()),
        new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), mode.Id.ToString()));
                    intCallTimer = 10;
                    ShowCallMessage(Properties.Resources._23, "正在发起呼叫请求...");
                    timer_call.Start();
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.user_DoubleClick       user_DoubleClick：" + ex.Message.ToString());
            }
        }
        //呼叫等待
        bool isHangUp = false;//是否挂断
        private void WaitCall(List<ParamInfo> os)
        {
            try
            {
                isHangUp = true;
                intCallTimer = 60;
                ShowCallMessage(Properties.Resources._15, "呼叫请求中，等待用户响应...");
                timer_call.Start();

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
            try
            {
                CanCall();
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.btn_cancall_Click       btn_cancall_Click：" + ex.Message.ToString());
            }
        }
        //取消呼叫
        private void CanCall()
        {
            try
            {
                //重置状态
                isHangUp = false;
                //发送取消呼叫指令
                TranBuff(0, Promise.ICS_CMD_SESSIONFINISH,
                        new ParamInfo(CommandHelp.ParamEnum.RETCODE.ToString(), Promise.ICS_RETCODE_SESSION_ABANDON.ToString()));
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.CanCall       CanCall：" + ex.Message.ToString());
            }
        }
        //被其他用户呼叫
        private void UserCall(int userId, List<ParamInfo> os)
        {
            try
            {
                if (this.WindowState == FormWindowState.Minimized)
                    this.WindowState = FormWindowState.Normal;
                timer_call.Stop();//关闭计时器，确认状态
                int sid = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.SUSERID.ToString()).Value);
                UserInfo smode = GetUserInfoById(sid);
                if (smode != null)
                {
                    ShowCallMessage(Properties.Resources._14, smode.Name + "向您发起视频会话邀请...");

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
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.UserCall       UserCall：" + ex.Message.ToString());
            }
        }

        /// <summary>
        /// 当前会话
        /// </summary>
        private ConversationInfo ConversationMode = new ConversationInfo();
        //开始会话
        private void StartConversation(int userId, List<ParamInfo> os)
        {
            try
            {
                //重置状态
                isHangUp = false;
                int roomid = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.ROOMID.ToString()).Value);
                ConversationMode.SuserId = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.SUSERID.ToString()).Value);
                ConversationMode.TuserId = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.TUSERID.ToString()).Value);
                AnyChatCoreSDK.LeaveRoom(-1);
                AnyChatCoreSDK.EnterRoom(roomid, "", 0);

                SoundPlayer Player = new SoundPlayer();
                Player.Stream = Properties.Resources.system;
                Player.Play();
                Player.Dispose();
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.StartConversation       StartConversation：" + ex.Message.ToString());
            }
        }

        //接受邀请
        void btn_accepted_Click(object sender, EventArgs e)
        {
            try
            {
                TranBuff(0, Promise.ICS_CMD_SESSIONSTART);
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.btn_accepted_Click       btn_accepted_Click：" + ex.Message.ToString());
            }
        }

        // 拒绝邀请
        void btn_refuse_Click(object sender, EventArgs e)
        {
            try
            {
                //发送呼叫超时指令
                TranBuff(0, Promise.ICS_CMD_SESSIONFINISH,
                        new ParamInfo(CommandHelp.ParamEnum.RETCODE.ToString(), Promise.ICS_RETCODE_SESSION_REJECT.ToString()));
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.btn_refuse_Click       btn_refuse_Click：" + ex.Message.ToString());
            }
        }
        //呼叫超时
        private void TimeoutCall()
        {
            try
            {
                //重置状态
                isHangUp = false;
                //发送呼叫超时指令
                TranBuff(0, Promise.ICS_CMD_SESSIONFINISH,
                        new ParamInfo(CommandHelp.ParamEnum.RETCODE.ToString(), Promise.ICS_RETCODE_SESSION_TIMEOUT.ToString()));
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.TimeoutCall       TimeoutCall：" + ex.Message.ToString());
            }
        }

        //进入房间成功
        public void EnterRoomSuccess()
        {
            try
            {
                timer_call.Stop();

                Bitmap bit = Properties.Resources._28;
                bit.RotateFlip(RotateFlipType.Rotate180FlipY);
                //pic_suser.Image = bit;

                UserInfo smode = GetUserInfoById(ConversationMode.SuserId);
                UserInfo tmode = GetUserInfoById(ConversationMode.TuserId);

                if (smode != null && tmode != null)
                {
                    lb_tuserName.Text = tmode.Name;
                    lb_suserName.Text = smode.Name;

                    OpenCameraAndSpeak(true);

                    pan_users.Hide();
                    pan_call.Hide();
                    pan_conversation.Dock = DockStyle.Fill;
                    pan_conversation.Show();
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.EnterRoomSuccess       EnterRoomSuccess：" + ex.Message.ToString());
            }
        }
        //打开双方音视频设备
        public void OpenCameraAndSpeak(bool isopen)
        {
            try
            {
                //打开呼叫者音视频
                AnyChatCoreSDK.UserCameraControl(ConversationMode.SuserId, isopen);
                AnyChatCoreSDK.UserSpeakControl(ConversationMode.SuserId, isopen);
                AnyChatCoreSDK.SetVideoPos(ConversationMode.SuserId, pic_suserVideo.Handle, 0, 0, pic_suserVideo.Width, pic_suserVideo.Height);
                //打开目标用户音视频
                AnyChatCoreSDK.UserCameraControl(ConversationMode.TuserId, isopen);
                AnyChatCoreSDK.UserSpeakControl(ConversationMode.TuserId, isopen);
                AnyChatCoreSDK.SetVideoPos(ConversationMode.TuserId, pic_tuserVideo.Handle, 0, 0, pic_tuserVideo.Width, pic_tuserVideo.Height);

                //音量刷新
                timer_speak.Enabled = isopen;
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.OpenCameraAndSpeak       OpenCameraAndSpeak：" + ex.Message.ToString());
            }
        }

        //通话结束
        private void EndCall(List<ParamInfo> os)
        {
            try
            {
                if (this.WindowState == FormWindowState.Minimized)
                    this.WindowState = FormWindowState.Normal;
                int sid = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.SUSERID.ToString()).Value);
                int tid = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.TUSERID.ToString()).Value);
                int err = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.RETCODE.ToString()).Value);

                RemoveCallButton();
                intCallTimer = 3;

                if (err == Promise.ICS_RETCODE_SESSION_BUSY)//目标用户忙碌中
                {
                    ShowCallMessage(Properties.Resources._8, "目标用户正忙,请稍后重试...");

                }
                else if (err == Promise.ICS_RETCODE_SESSION_ABANDON)//取消呼叫
                {
                    if (sid == m_UserId)//取消成功
                        ShowCallMessage(Properties.Resources._20, "呼叫已取消...");
                    else
                        ShowCallMessage(Properties.Resources._7, "呼叫请求已被挂断...");
                }
                else if (err == Promise.ICS_RETCODE_SESSION_OFFLINE)//用户离线
                {
                    ShowCallMessage(Properties.Resources._18, "对方已离线...");
                    AnyChatCoreSDK.LeaveRoom(-1);
                }
                else if (err == Promise.ICS_RETCODE_SESSION_REJECT)//拒绝会话
                {
                    if (sid == m_UserId)
                        ShowCallMessage(Properties.Resources._5, "对方拒绝会话...");
                    else
                        ShowCallMessage(Properties.Resources._19, "呼叫已拒绝...");
                }
                else if (err == Promise.ICS_RETCODE_SESSION_TIMEOUT)//会话超时
                {
                    if (sid == m_UserId)
                        ShowCallMessage(Properties.Resources._1, "会话请求已超时...");
                    else
                        ShowCallMessage(Properties.Resources._0, "会话请求已超时...");
                }
                else if (err == Promise.ICS_RETCODE_SESSION_SUCCESS)//会话结束
                {
                    ShowCallMessage(Properties.Resources._18, "会话已结束...");
                }

                timer_call.Start();
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.EndCall       EndCall：" + ex.Message.ToString());
            }
        }

        //移除呼叫流程按钮
        private void RemoveCallButton()
        {
            try
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
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.RemoveCallButton       RemoveCallButton：" + ex.Message.ToString());
            }
        }

        //提示呼叫消息
        private void ShowCallMessage(Bitmap bit, string str)
        {
            try
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
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.ShowCallMessage       ShowCallMessage：" + ex.Message.ToString());
            }
        }
        int intCallTimer = 0;
        //呼叫计时器
        private void timer_call_Tick(object sender, EventArgs e)
        {
            try
            {
                if (intCallTimer != 1)
                {
                    intCallTimer -= 1;
                    lb_call.Text = lb_call.Tag.ToString() ;
                }
                else
                {
                    if (isHangUp)
                        TimeoutCall();
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

        //音量刷新计时器
        int intSuserSpeakValue = 0;//主动方音量
        int intTuserSpeakValue = 0;//被动方音量
        private void timer_speak_Tick(object sender, EventArgs e)
        {
            try
            {
                int value = 0;
                AnyChatCoreSDK.QueryUserState(ConversationMode.SuserId, AnyChatCoreSDK.BRAC_USERSTATE_SPEAKVOLUME, ref value, sizeof(int));
                intSuserSpeakValue = value;

                AnyChatCoreSDK.QueryUserState(ConversationMode.TuserId, AnyChatCoreSDK.BRAC_USERSTATE_SPEAKVOLUME, ref value, sizeof(int));
                intTuserSpeakValue = value;

                pic_tuserSound.Invalidate();
                pic_suserSound.Invalidate();
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.timer_speak_Tick       timer_speak_Tick：" + ex.Message.ToString());
            }
        }
        //被动者音量条重绘
        private void pic_tuserSound_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                Graphics g = e.Graphics;
                int width = intTuserSpeakValue * pic_tuserSound.Width / 100;
                g.FillRectangle(new SolidBrush(Color.SteelBlue), new Rectangle(new Point(0, 0), new Size(width, pic_tuserSound.Height)));
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.pic_tuserSound_Paint       pic_tuserSound_Paint：" + ex.Message.ToString());
            }
        }
        //主动者音量条重绘
        private void pic_suserSound_Paint(object sender, PaintEventArgs e)
        {
            try
            {
                Graphics g = e.Graphics;
                int width = intSuserSpeakValue * pic_tuserSound.Width / 100;
                g.FillRectangle(new SolidBrush(Color.SteelBlue), new Rectangle(new Point(0, 0), new Size(width, pic_tuserSound.Height)));
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.pic_suserSound_Paint       pic_suserSound_Paint：" + ex.Message.ToString());
            }
        }

        //挂断会话
        private void btn_hungUp_Click(object sender, EventArgs e)
        {
            try
            {
                AnyChatCoreSDK.LeaveRoom(-1);
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.btn_hungUp_Click       btn_hungUp_Click：" + ex.Message.ToString());
            }
        }

        //用户离开房间
        public void UserLeaveRoom(int id)
        {
            try
            {
                if (id == ConversationMode.SuserId || id == ConversationMode.TuserId)
                {
                    AnyChatCoreSDK.LeaveRoom(-1);
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.UserLeaveRoom       UserLeaveRoom：" + ex.Message.ToString());
            }
        }

        #endregion

        #region 透明通道

        //透明通道回调函数
        public void TransBuffer_CallBack(int userId, IntPtr buf, int len, int userValue)
        {
            try
            {
                string str = Marshal.PtrToStringAnsi(buf);                          //获取命令字符串
                int cmd = Convert.ToInt32(CommandHelp.ResolveCommand(str));        //解析命令字符串头部
                List<ParamInfo> os = CommandHelp.ResolveCommand(cmd, str);      //根据头部命令解析命令内容(得到参数)
                switch (cmd)
                {
                    //数据信息
                    case Promise.ICS_CMD_DATAITEM:
                        if (CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.DATATYPE.ToString()).Value == Promise.ICS_DATATYPE_ONLINEUSERS.ToString())//在线用户数据
                            UserLogin(os);
                        break;
                    //状态通知
                    case Promise.ICS_CMD_STATUSNOTIFY:
                        if (CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.STATUS.ToString()).Value == Promise.ICS_STATUSTYPE_USERONLINE.ToString())//用户状态变化
                            UserStatus(os);
                        break;
                    //控制指令
                    case Promise.ICS_CMD_CONTROL:
                        if (CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.CTRLCODE.ToString()).Value == Promise.ICS_CONTROL_DATAFINISH.ToString())//数据发送完毕
                            DataFinish(os);
                        //呼叫等待
                        else if (CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.CTRLCODE.ToString()).Value == Promise.ICS_CONTROL_SESSIONWAIT.ToString())//呼叫等待
                            WaitCall(os);
                        break;
                    //请求会话
                    case Promise.ICS_CMD_SESSIONREQUEST:
                        UserCall(userId, os);
                        break;
                    //会话结束
                    case Promise.ICS_CMD_SESSIONFINISH:
                        EndCall(os);
                        break;
                    //开始会话
                    case Promise.ICS_CMD_SESSIONSTART:
                        StartConversation(userId, os);
                        break;

                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.TransBuffer_CallBack       TransBuffer_CallBack：" + ex.Message.ToString());
            }
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
        private UserInfo GetUserInfoById(int id)
        {
            UserInfo mode = null;
            try
            {
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
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Hall.GetUserInfoById       GetUserInfoById：" + ex.Message.ToString());
            }
            return mode;
        }

        #endregion
    }
}
