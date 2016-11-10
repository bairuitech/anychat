using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;//DLLImport
using System.IO;
using ANYCHATAPI;
using System.Net;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;

namespace AnyChatCSharpDemo
{
    public partial class frmRoom : Form
    {

        #region 定义窗体委托

        delegate void AsyncTransFileStatus(int m_UserID, int m_TaskID);
        delegate void AsyncTransSetFileProgress(string m_Progress);


        #endregion

        #region 定义控件

        //用户视频信息提示Label
        Label lbl_user = new System.Windows.Forms.Label();

        #endregion

        #region 文件传输变量定义

        int m_ReceiveUserID = -1;
        int m_ReceiveTaskID = -1;
        /// <summary>
        /// 传输方式
        /// </summary>
        TransType transType = TransType.TextMessage;

        /// <summary>
        /// 是否选择自己
        /// </summary>
        bool chooseMyself = false;
        #endregion

        #region 调用WIN的API

        /// <summary>
        /// 调节声音大小
        /// </summary>
        /// <param name="deviceID"></param>
        /// <param name="Volume"></param>
        /// <returns></returns>
        [DllImport("winmm.dll", EntryPoint = "waveOutSetVolume", CharSet = CharSet.Auto)]
        public static extern long waveOutSetVolume(long deviceID, long Volume); 

        #endregion

        #region 窗体信息定义

        /// <summary>
        /// 字体名称
        /// </summary>
        public string[] m_AllFontSizeName ={ "8", "9", "10", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72", "初号", "小初", "一号", "小一", "二号", "小二", "三号", "小三", "四号", "小四", "五号", "小五", "六号", "小六", "七号", "八号" };
        /// <summary>
        /// 字号
        /// </summary>
        public float[] m_AllFontSize ={ 8, 9, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72, 42, 36, 26, 24, 22, 18, 16, 15, 14, 12, 10.5F, 9, 7.5F, 6.5F, 5.5F, 5 };
        //1=160*120；2=176*144； 3=320*240； 4=352*288； 5=528*384； 6=640*480； 7=704*576
        /// <summary>
        /// 视频放大宽度
        /// </summary>
        private int m_VideoWidthMax = 480;
        /// <summary>
        /// 视频放大高度
        /// </summary>
        private int m_VideoHeightMax = 384;
        /// <summary>
        /// 本地视频状态，true为发送本地视频，false为不发送
        /// </summary>
        private bool m_LocalVideoStatue = true;
        /// <summary>
        /// 本地音频状态，true为发送本地音频，false为不发送
        /// </summary>
        private bool m_LocalAudioStatue = true;

        #endregion

        #region 房间信息定义

        /// <summary>
        /// 几列视频窗口(横着几个视频窗口)
        /// </summary>
        private int m_ColUserVideo = 3;
        /// <summary>
        /// 房间ID
        /// </summary>
        private int m_RoomID = 1;
        /// <summary>
        /// 用户ID（系统自动分配）
        /// </summary>
        private int m_myUserID = -1;
        /// <summary>
        /// 房间用户列表（不包括自己），开发包自带
        /// </summary>
        private List<int> m_others = new List<int>();
        /// <summary>
        /// 用户列表（包含用户结构属性）
        /// </summary>
        private List<clsMemberList.MemberItem> m_MemberItem=new List<clsMemberList.MemberItem>();

        #endregion

        #region 构造函数

        public frmRoom()
        {
            InitializeComponent();
        }

        #endregion

        #region 初始化房间

        void InitChat()
        {
            //应用签名
            string signStr = string.Empty;
            //签名时间戳
            int signTimestamp = 0;

            string path = Application.StartupPath;
            SystemSetting.Text_OnReceive = new TextReceivedHandler(Received_Text);//文本回调涵数
            SystemSetting.TransBuffer_OnReceive = new TransBufferReceivedHandler(Received_TransBuffer);//透明通道传输回调
            SystemSetting.TransBufferEx_OnReceive = new TransBufferExReceivedHandler(Received_TransBufferEx);  //透明通道传输回调
            SystemSetting.TransFile_Received = new TransFileReceivedHandler(Received_TransFile);//文件传输回调
            AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_CORESDK_PATH, path, path.Length);
         
            SystemSetting.Init(this.Handle);

            ////设置视频分辨率
            //int m_Refw = AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_WIDTHCTRL, ref frmLogin.m_LocalVideoWidth, sizeof(int));
            //int m_Refh = AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, ref frmLogin.m_LocalVideoHeight, sizeof(int));
            ////应用本地视频编码参数，使得前述修改即时生效（参数为int型：1 使用新参数，0 使用默认参数）
            //int m_AppLocal = 1;
            //AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_APPLYPARAM, ref m_AppLocal, sizeof(int));

            //StringBuilder m_ServerKey = new StringBuilder();
            //m_ServerKey.Append("d");
            //int retkey = AnyChatCoreSDK.SetServerAuthPass(m_ServerKey);

            /* AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
             * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
             * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
             */
            int ret = AnyChatCoreSDK.Connect(frmLogin.m_VideoServerIP, frmLogin.m_VideoTcpPort);

            /*
             * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，
             * 详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
             */
            ret = AnyChatCoreSDK.Login(frmLogin.m_UserName, frmLogin.m_LoginPass, 0);

            comboBox_TransType.SelectedIndex = (int)TransType.TextMessage;
            transType = TransType.TextMessage;
        }

        #endregion

        #region 文件传输

        #region 显示文件传输状态

        private void Receive_GransFileStatus(int m_UserID, int m_TaskID)
        {
            m_ReceiveUserID = m_UserID;
            m_ReceiveTaskID = m_TaskID;
            //MessageBox.Show("U:" + m_ReceiveUserID.ToString() + "T:" + m_ReceiveTaskID.ToString());
            //txt_2.BeginInvoke(new AsyncTransSetFileProgress(SetTxtValue), m_ReceiveUserID.ToString() + ":" + m_ReceiveTaskID.ToString());
        }

        #endregion

        #region 每秒更新文件进度

        private void tmr_receivefile_Tick(object sender, EventArgs e)
        {
            //每秒更新视频码率

            int m_AVInfoval = 0;
            int avret = AnyChatCoreSDK.QueryUserState(-1, AnyChatCoreSDK.BRAC_USERSTATE_VIDEOBITRATE, ref m_AVInfoval, sizeof(int));
            string m_AVSpeed = m_AVInfoval.ToString()+"B/S";
            if (m_AVInfoval > 1000)
            {
                try
                {
                    double m_AVTemp = (double)m_AVInfoval / 1000.0;
                    m_AVSpeed = m_AVTemp.ToString();
                    m_AVSpeed = m_AVSpeed.Substring(0, m_AVSpeed.Length - 2) + "KB/S";
                }
                catch { }
            }
            lbl_v_speed.BeginInvoke(new AsyncTransSetFileProgress(SetVideoSpeed), m_AVSpeed);

            //每秒更新音频码率
            avret = AnyChatCoreSDK.QueryUserState(-1, AnyChatCoreSDK.BRAC_USERSTATE_AUDIOBITRATE, ref m_AVInfoval, sizeof(int));
            m_AVSpeed = m_AVInfoval.ToString() + "B/S";
            if (m_AVInfoval > 1000)
            {
                try
                {
                    double m_AVTemp = (double)m_AVInfoval / 1000.0;
                    m_AVSpeed = m_AVTemp.ToString();
                    m_AVSpeed = m_AVSpeed.Substring(0, m_AVSpeed.Length - 2) + "KB/S";
                }
                catch { }
            }
            lbl_a_speed.BeginInvoke(new AsyncTransSetFileProgress(SetAudioSpeed), m_AVSpeed);


            //StringBuilder m_InfoVal = new StringBuilder(300);
            //int ret = AnyChatCoreSDK.QueryTransTaskInfo(m_ReceiveUserID, m_ReceiveTaskID, 1, m_InfoVal, 300);
            //double m_InfoVal = 0.0;
            //int ret = AnyChatCoreSDK.QueryTransTaskInfo(m_ReceiveUserID, m_ReceiveTaskID, 1, ref m_InfoVal, 300);
            //lbl_progress.BeginInvoke(new AsyncTransSetFileProgress(SetTransFileProgress), ret.ToString()+":"+m_InfoVal.ToString());
            //int m_InfoVal = 0;
            double m_InfoVal = 0.0;
            int ret = AnyChatCoreSDK.QueryTransTaskInfo(m_ReceiveUserID, m_ReceiveTaskID, 1, ref m_InfoVal, sizeof(double));
			if(ret != 0)
				return;
            string m_BFB = m_InfoVal.ToString();
            try
            {
                m_BFB = m_BFB.Substring(0, m_BFB.IndexOf(".") + 3);
            }
            catch { }
            m_BFB += "%";
            lbl_progress.BeginInvoke(new AsyncTransSetFileProgress(SetTransFileProgress),  "进度:" + m_BFB);

            int m_InfoValSpeed = 1;
            int rett = AnyChatCoreSDK.QueryTransTaskInfo(m_ReceiveUserID, m_ReceiveTaskID, 2, ref m_InfoValSpeed, sizeof(int));
            string m_VSpeed = "";
            double m_Templv = 0.0;
            m_VSpeed = m_InfoValSpeed.ToString() + "B/S";
            if (m_InfoValSpeed > 1000)
            {
                m_Templv = (double)m_InfoValSpeed / 1000.0;
                m_VSpeed = m_Templv.ToString();
                try
                {
                    m_VSpeed = m_VSpeed.Substring(0, m_VSpeed.IndexOf(".") + 2);
                }
                catch { }
                m_VSpeed =m_VSpeed+ "KB/S";
            }
            if (m_InfoValSpeed > 1000000)
            {
                m_Templv = (double)m_InfoValSpeed / 1000000.0;
                m_VSpeed = m_Templv.ToString();
                try
                {
                    m_VSpeed = m_VSpeed.Substring(0, m_VSpeed.IndexOf(".") + 2);
                }
                catch { }
                m_VSpeed = m_VSpeed + "MB/S";
            }
            lbl_speed.BeginInvoke(new AsyncTransSetFileProgress(SetTransFileSpeed), "速率:" + m_VSpeed);
        }

        #endregion

        #region 异步设置文件进度

        private void SetTransFileProgress(string m_Progress)
        {
            lbl_progress.Text = m_Progress;
        }

        private void SetTransFileSpeed(string m_Speed)
        {
            lbl_speed.Text = m_Speed;
        }

        #endregion

        #region 异步设置文本框值

        private void SetTxtValue(string m_Txt)
        {
            //txt_2.Text = m_Txt;
        }

        #endregion

        #region 异步设置视频码率

        private void SetVideoSpeed(string m_VSpeed)
        {
            lbl_v_speed.Text = "视频码率：" + m_VSpeed;
        }

        #endregion

        #region 异步设置音频码率

        private void SetAudioSpeed(string m_ASpeed)
        {
            lbl_a_speed.Text = "音频码率：" + m_ASpeed;
        }

        #endregion

        #endregion

        #region 显示文本

        /// <summary>
        /// 显示聊天文本
        /// </summary>
        /// <param name="fromUID"></param>
        /// <param name="toUID"></param>
        /// <param name="m_Text"></param>
        /// <param name="isserect"></param>
        void Received_Text(int fromUID, int toUID, string m_Text, bool isserect)
        {
            string m_FromName = GetUserNameByID(fromUID);
            string m_ToName = GetUserNameByID(toUID);
            if (toUID == -1) m_ToName = "大家";
            string m_DispMsg = m_FromName + " To " + m_ToName + " ";
            ShowText(m_DispMsg, txt_Accept.TextLength, m_DispMsg.Length, Color.Green, new Font("黑体", 9, FontStyle.Bold));
            ShowText(DateTime.Now.ToString(), txt_Accept.TextLength, DateTime.Now.ToString().Length, Color.Green, new Font("黑体", 9, FontStyle.Bold));
            ShowText("\r\n", txt_Accept.TextLength, 4, Color.Blue, new Font("宋体", 12));
            ShowText("    ", txt_Accept.TextLength, 4, Color.Blue, new Font("宋体", 12));
            ShowText(m_Text, txt_Accept.TextLength, m_Text.Length, Color.Black, new Font("黑体", 9));
            ShowText("\r\n\r\n", txt_Accept.TextLength, 8, Color.Blue, new Font("宋体", 12));
        }
        /// <summary>
        /// 显示系统信息
        /// </summary>
        /// <param name="m_Msg"></param>
        void Print(string m_Msg)
        {
            string m_SysInfo = "[系统信息] ";
            m_Msg += "\r\n\r\n";
            ShowText(m_SysInfo, txt_Accept.TextLength, m_SysInfo.Length, Color.Red, new Font("黑体", 9,FontStyle.Bold));
            ShowText(m_Msg, txt_Accept.TextLength, m_Msg.Length, Color.Black, new Font("黑体", 9));
        }
        /// <summary>
        /// 向RichTextBox添加文本
        /// </summary>
        /// <param name="sText"></param>
        /// <param name="nStart"></param>
        /// <param name="nLength"></param>
        /// <param name="color"></param>
        /// <param name="font"></param>
        private void ShowText(string sText, int nStart, int nLength, Color color, Font font)
        {
            txt_Accept.AppendText(sText);
            txt_Accept.Select(nStart, nLength);    // 需要修改颜色的部分
            txt_Accept.SelectionColor = color;     // 颜色
            txt_Accept.SelectionFont = font;       // 字体
            txt_Accept.ScrollToCaret();
            txt_Accept.Select(txt_Accept.Text.Length, 0); 
        }

        #endregion

        #region 重载WndProc

        protected override void WndProc(ref Message m)
        {

            if (m.Msg == AnyChatCoreSDK.WM_GV_CONNECT)
            {
                ///连接
                int succed = m.WParam.ToInt32();
                if (succed == 1)
                {
                    Print("连接成功!");
                }
                else
                {
                    Print("连接失败,错误号:" + m.LParam.ToInt32());
                }
            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_LOGINSYSTEM)
            {
                ///登录系统
                int userid = m.WParam.ToInt32();
                if (m.LParam.ToInt32() == 0)
                {
                    //Print("登录服务器成功，自己的用户编号为：" + userid.ToString());
                    Print("登录服务器成功，自己的用户账号为：" + frmLogin.m_UserName);
                    m_myUserID = userid;

                    //StringBuilder userName = new StringBuilder(30);
                    //int ret = AnyChatCoreSDK.GetUserName(userid, userName, 30);

                    AnyChatCoreSDK.EnterRoom(m_RoomID, "", 0);
                }
                else
                {
                    Print("登录服务器失败，代码出错为：" + m.LParam.ToInt32());
                }
            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_ENTERROOM)
            {
                ///进入房间
                if (m.LParam.ToInt32() == 0)
                {
                    int roomid = m.WParam.ToInt32();
                    Print("进入房间成功,房间编号为：" + roomid.ToString());
                    m_RoomID = roomid;

                    getLocalVideoDeivceName();

                    int ret = AnyChatCoreSDK.SetVideoPos(-1, pnl_local.Handle, 0, 0, pnl_local.Width, pnl_local.Height);
                    ret = AnyChatCoreSDK.UserCameraControl(-1, true);
                    ret = AnyChatCoreSDK.UserSpeakControl(-1, true);
                }
                else
                {
                    Print("申请进入房间失败，出错代码为：" + m.LParam.ToInt32());
                }
            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_ONLINEUSER)
            {
                ///目前在房间的用户列表
                int usrcnt = m.WParam.ToInt32();
                Print("在编号为：" + m.LParam.ToInt32() + " 的房间共有" + usrcnt + "位在线用户");
                Print("当前时间：" + DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss"));

                int cnt = 0;//在线用户数量
                AnyChatCoreSDK.GetOnlineUser(null, ref cnt);//获取在线用户数量
                int[] userArr = new int[cnt];//在线用户ＩＤ
                AnyChatCoreSDK.GetOnlineUser(userArr, ref cnt);//获取在线用户ＩＤ数组

                if (userArr.Length >= 1)
                {
                    for (int i = 0; i < userArr.Length; i++)
                    {
                        m_others.Add(userArr[i]);//存入在线用户列表中（开发包带的用户在线ＩＤ数组）
                        UpdateUserList(userArr[i], i);//添加到在线用户列表（自定义，带用户属性结构）
                    }
                    UpdateOnlineUser();
                }
                else
                {
                    dgv_onlineuser.Rows.Clear();
                    DataGridViewRow dgvr = new DataGridViewRow();
                    dgv_onlineuser.Rows.Add(dgvr);
                    dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
                    dgvr.Cells["gvc_username"].Value = "大家";
                    dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.深灰背景;
                    dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.深灰背景;
                    dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.深灰背景;
                    dgvr = new DataGridViewRow();
                    dgv_onlineuser.Rows.Add(dgvr);
                    dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
                    dgvr.Cells["gvc_username"].Value = frmLogin.m_UserName; ;
                    dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.主持人_浅灰;
                    dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.麦克;
                    dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.摄像头;
                }

            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_USERATROOM)
            {
                ///新用户加入或退出房间
                int userID = m.WParam.ToInt32();
                int boEntered = m.LParam.ToInt32();

                if (boEntered == 1)
                {
                    m_others.Add(userID);
                    UpdateUserList(userID, m_others.Count - 1);
                    Print("用户：" + GetUserNameByID(userID) + " 进入房间");
                }
                else
                {
                    m_others.Remove(userID);
                    for (int i = 0; i < m_MemberItem.Count; i++)
                    {
                        if (m_MemberItem[i].m_UserID == userID)
                        {
                            m_MemberItem.RemoveAt(i);
                            break;
                        }
                    }
                    Print("用户：" + GetUserNameByID(userID) + " 离开房间");
                }
                UpdateOnlineUser();//更新用户列表
                this.Invalidate();//重绘界面，防止界面假死
            }
            base.WndProc(ref m);
        }

        #endregion

        #region 刷新用户列表

        private void UpdateOnlineUser()
        {
            DataGridViewRow dgvr = new DataGridViewRow();
            //保存原选择用户
            string m_TempUserName = "";
            int m_DGVSelectRow = -1;
            if (dgv_onlineuser.SelectedRows.Count > 0)
            {
                dgvr = dgv_onlineuser.SelectedRows[0];
                m_TempUserName = dgvr.Cells["gvc_username"].Value.ToString();
            }
            dgv_onlineuser.Rows.Clear();//清空用户列表
            pnl_video.Controls.Clear();//清空所有视频窗口
            //显示大家
            dgvr = new DataGridViewRow();
            dgv_onlineuser.Rows.Add(dgvr);
            dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
            dgvr.Cells["gvc_username"].Value = "大家";
            dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.深灰背景;
            dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.深灰背景;
            dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.深灰背景;
            dgvr = new DataGridViewRow();
            dgv_onlineuser.Rows.Add(dgvr);
            dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
            dgvr.Cells["gvc_username"].Value = frmLogin.m_UserName; ;
            dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.主持人_浅灰;
            dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.麦克;
            dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.摄像头;
            //显示自己
            for (int i = 0; i < m_MemberItem.Count; i++)
            {
                dgvr = new DataGridViewRow();
                dgv_onlineuser.Rows.Add(dgvr);
                dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
                dgvr.Cells["gvc_username"].Value = m_MemberItem[i].m_UserName;
                dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.麦克 ;
                dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.摄像头;
                dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.普通人_浅灰;
                CreateUserVideo(m_MemberItem[i].m_UserID);
                if (m_TempUserName == m_MemberItem[i].m_UserName)
                {
                    m_DGVSelectRow = i+1;
                }
            }
            if (m_TempUserName != "" && m_DGVSelectRow > -1)
            {
                dgv_onlineuser.Rows[m_DGVSelectRow].Selected = true;
            }
            else
            {
                dgv_onlineuser.Rows[0].Selected = true;
            }
            
        }

        #endregion

        #region 增加或减少用户

        private void UpdateUserList(int m_UserID,int m_Index)
        {
            clsMemberList.MemberItem m_TempItem = new clsMemberList.MemberItem();//创建用户在线列表（自定义，包含用户属性）
            
            StringBuilder m_TempName = new StringBuilder(30);

            byte[] userNameByte = new byte[255];
            int ret = AnyChatCoreSDK.GetUserName(m_UserID, ref userNameByte[0], 30);//获取用户账号

            m_TempItem.m_UserName = byteToString(userNameByte);
            m_TempItem.m_UserID = m_UserID;
            m_TempItem.m_Index = m_Index;
            m_TempItem.m_Permission = new int[] { 0, 0, 0 };//用户权限
            m_MemberItem.Add(m_TempItem);//添加到在线用户列表
        }
        /// <summary>
        /// 通过用户ID获得用户账号
        /// </summary>
        /// <param name="m_UserID"></param>
        /// <returns></returns>
        private string GetUserNameByID(int m_UserID)
        {
            byte[] userNameByte = new byte[255];
            int ret = AnyChatCoreSDK.GetUserName(m_UserID, ref userNameByte[0], 30);//获取用户账号
            return byteToString(userNameByte);
        }
        /// <summary>
        /// 通过用户账号获得用户ID
        /// </summary>
        /// <param name="m_UserNameTemp"></param>
        /// <returns></returns>
        private int GetUserIDByName(string m_UserNameTemp)
        {
            int m_TempUserID = -1;
            for (int i = 0; i < m_MemberItem.Count; i++)
            {
                if (m_MemberItem[i].m_UserName == m_UserNameTemp)
                {
                    m_TempUserID = m_MemberItem[i].m_UserID;
                    break;
                }
            }
            return m_TempUserID;
        }

        #endregion

        #region 用户视频窗口操作

        #region 创建用户视频窗口

        private void CreateUserVideo(int m_UserID)
        {
            //用户视频横列显示规则
            int userCount = GetUserCount();
            if (userCount > 0 && userCount <= 1) m_ColUserVideo = 1;
            else if (userCount > 1 && userCount <= 4) m_ColUserVideo = 2;
            else if (userCount > 4) m_ColUserVideo = 3;

            int m_PnlCount = pnl_video.Controls.Count;
            Panel m_ShowWnd = new Panel();
            m_ShowWnd.Name = m_UserID.ToString();
            m_ShowWnd.Width = (pnl_video.Width) / m_ColUserVideo;
            m_ShowWnd.Height = m_ShowWnd.Width * 4 / 5;
            m_ShowWnd.Top = m_PnlCount / m_ColUserVideo * m_ShowWnd.Height + m_PnlCount / m_ColUserVideo * 5;
            m_ShowWnd.Left = m_PnlCount % m_ColUserVideo * m_ShowWnd.Width + m_PnlCount % m_ColUserVideo * 5;
            m_ShowWnd.BackColor = Color.Black;
            m_ShowWnd.DoubleClick += new EventHandler(ShowWnd_DoubleClick);
            m_ShowWnd.MouseEnter += new EventHandler(m_ShowWnd_MouseEnter);
            m_ShowWnd.MouseLeave += new EventHandler(m_ShowWnd_MouseLeave);
            pnl_video.Controls.Add(m_ShowWnd);
            AnyChatCoreSDK.SetVideoPos(m_UserID, m_ShowWnd.Handle, 0, 0, m_ShowWnd.Width, m_ShowWnd.Height);
            AnyChatCoreSDK.UserCameraControl(m_UserID, true);
            AnyChatCoreSDK.UserSpeakControl(m_UserID, true);
            
        }

        /// <summary>
        /// 获取在线用户数量（不包括自己）
        /// </summary>
        /// <returns>在线用户数量</returns>
        private int GetUserCount()
        {
            int userCount = 0;
            //int[] ids = new int[] { };
            AnyChatCoreSDK.GetOnlineUser(null, ref userCount);
            return userCount;
        }

        #endregion

        #region 鼠标进入用户视频窗口

        void m_ShowWnd_MouseEnter(object sender, EventArgs e)
        {
            Control ShowWnd = (Control)sender;
            string userName = GetUserNameByID(Convert.ToInt32(ShowWnd.Name));

            // lbl_user初始化 
            lbl_user.AutoSize = true;
            lbl_user.BackColor = System.Drawing.Color.White;
            lbl_user.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            lbl_user.Name = "lbl_user";
            lbl_user.Location = new System.Drawing.Point(176, 503);
            lbl_user.Size = new System.Drawing.Size(55, 14);
            this.Controls.Add(lbl_user);

            lbl_user.Text = userName;
            lbl_user.Parent = pnl_video;
            lbl_user.Left = ShowWnd.Left + ShowWnd.Width - lbl_user.Width;
            lbl_user.Top = ShowWnd.Top + ShowWnd.Height - lbl_user.Height;
            lbl_user.BringToFront();
            lbl_user.Visible = true;
        }

        #endregion

        #region 鼠标离开用户视频窗口

        void m_ShowWnd_MouseLeave(object sender, EventArgs e)
        {
            lbl_user.Visible = false;
        }

        #endregion

        #region 双击用户视频窗口

        private void ShowWnd_DoubleClick(object sender, EventArgs e)
        {
            Control ShowWnd = (Control)sender;
            if (ShowWnd.Width != m_VideoWidthMax)
            {
                foreach (Control C in pnl_video.Controls)
                {
                    if (C.Name != ShowWnd.Name)
                    {
                        C.Visible = false;
                    }
                }
                ShowWnd.Top = (pnl_video.Height - m_VideoHeightMax) / 2;
                ShowWnd.Left = (pnl_video.Width - m_VideoWidthMax) / 2; ;
                ShowWnd.Width = m_VideoWidthMax;
                ShowWnd.Height = m_VideoHeightMax;
                
            }
            else
            {
                foreach (Control C in pnl_video.Controls)
                {
                    if (C.Name != ShowWnd.Name)
                    {
                        C.Visible = true;
                    }
                }
                int m_TempIndex = 0;
                for (int i = 0; i < m_MemberItem.Count; i++)
                {
                    if (ShowWnd.Name == m_MemberItem[i].m_UserID.ToString())
                    {
                        m_TempIndex=m_MemberItem[i].m_Index;
                        break;
                    }
                }
                ShowWnd.Width = (pnl_video.Width) / m_ColUserVideo;
                ShowWnd.Height = ShowWnd.Width * 4 / 5;
                ShowWnd.Top = m_TempIndex / m_ColUserVideo * ShowWnd.Height + m_TempIndex / m_ColUserVideo * 5;
                ShowWnd.Left = m_TempIndex % m_ColUserVideo * ShowWnd.Width + m_TempIndex % m_ColUserVideo * 5;
                
            }
            AnyChatCoreSDK.SetVideoPos(Convert.ToInt32(ShowWnd.Name), ShowWnd.Handle, 0, 0, ShowWnd.Width, ShowWnd.Height);
        }

        #endregion

        #region 本地视频窗口双击事件

        private void pnl_local_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            Control ShowWnd = (Control)sender;
            if (ShowWnd.Width != m_VideoWidthMax)
            {
                foreach (Control C in pnl_video.Controls)
                {
                    if (C.Name != ShowWnd.Name)
                    {
                        C.Visible = false;
                    }
                }
                ShowWnd.Top = (pnl_video.Height - m_VideoHeightMax) / 2;
                ShowWnd.Left = (pnl_video.Width - m_VideoWidthMax) / 2; ;
                ShowWnd.Width = m_VideoWidthMax;
                ShowWnd.Height = m_VideoHeightMax;
                pnl_video.Controls.Add(ShowWnd);

            }
            else
            {
                foreach (Control C in pnl_video.Controls)
                {
                    if (C.Name != ShowWnd.Name)
                    {
                        C.Visible = true;
                    }
                }
                ShowWnd.Width = 167;
                ShowWnd.Height = 140;
                ShowWnd.Top = 471;
                ShowWnd.Left = 3;
                this.Controls.Add(ShowWnd);

            }
            //AnyChatCoreSDK.SetVideoPos(Convert.ToInt32(ShowWnd.Name), ShowWnd.Handle, 0, 0, ShowWnd.Width, ShowWnd.Height);
            int ret = AnyChatCoreSDK.SetVideoPos(-1, pnl_local.Handle, 0, 0, ShowWnd.Width, ShowWnd.Height);
        }

        #endregion

        #endregion

        #region 窗体加载关闭

        #region 窗体加载

        private void frmRoom_Load(object sender, EventArgs e)
        {
            InitChat();//初始化
            //InitUserPanel();//初始化用户面版
            //初始化发送按钮右建菜单
            ment_item_ctrlenter.Image = null;
            ment_item_enter.Image = AnyChatCSharpDemo.Properties.Resources.duihao;
            //初始化字体字号
            InitFont();
            //m_VideoWidthMax = frmLogin.m_LocalVideoWidth;
            //m_VideoHeightMax = frmLogin.m_LocalVideoHeight;
            //m_VideoWidthMax = 640;
            //m_VideoHeightMax = 480;

            //音视频状态
            chk_localvideo.Checked = m_LocalVideoStatue ;
            chk_localaudio.Checked = m_LocalAudioStatue;

            //cbox_video.SelectedIndex = 5;//视频最大化尺寸

            #region 采集分辨率

            //1=160*120；2=176*144； 3=320*240； 4=352*288； 5=528*384； 6=640*480； 7=704*576
            //int m_SelectIndex=0;
            //switch (frmLogin.m_LocalVideoWidth)
            //{
            //    case 160 :
            //        m_SelectIndex=0;
            //        break;
            //    case 176 :
            //        m_SelectIndex=1;
            //        break;
            //    case 320 :
            //        m_SelectIndex=2;
            //        break;
            //    case 352:
            //        m_SelectIndex = 3;
            //        break;
            //    case 528:
            //        m_SelectIndex = 4;
            //        break;
            //    case 640:
            //        m_SelectIndex = 5;
            //        break;
            //    case 704:
            //        m_SelectIndex = 6;
            //        break;
            //}
            //cbox_caiji.SelectedIndex = m_SelectIndex;

            #endregion

        }

        #endregion

        #region 窗体关闭

        private void frmRoom_FormClosing(object sender, FormClosingEventArgs e)
        {
            AnyChatCoreSDK.LeaveRoom(m_RoomID);
            AnyChatCoreSDK.Logout();
            System.Environment.Exit(0);
        }

        #endregion

        #endregion

        #region 文本发送

        /// <summary>
        /// 发送按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btn_sendtxt_Click(object sender, EventArgs e)
        {
            string m_Message = rtxt_sendtxt.Text;
            if (m_Message.Length == 0)
            {
                MessageBox.Show("发送内容不能为空","提示");
                return;
            }

            int length = UnicodeEncoding.Default.GetBytes(m_Message).Length;
            int m_TempUserID = -1;
            string m_TempUserName = "大家";
            if (dgv_onlineuser.SelectedRows.Count != 0)
            {
                DataGridViewRow dgvr = dgv_onlineuser.SelectedRows[0];
                m_TempUserName = dgvr.Cells["gvc_username"].Value.ToString();
                for (int i = 0; i < m_MemberItem.Count; i++)
                {
                    if (m_MemberItem[i].m_UserName == m_TempUserName)
                    {
                        m_TempUserID = m_MemberItem[i].m_UserID;
                        break;
                    }
                }

            }
            if (transType == TransType.TransBuffer || transType == TransType.TransBuffer)
            {
                if (m_TempUserID == -1 && !chooseMyself)
                {
                    MessageBox.Show("请选择目标用户！", "提示");
                    return;
                }
                if (chooseMyself) m_TempUserID = 0;
            }
            bool m_Secret = false;
            if (m_TempUserID != -1) m_Secret = true;
            int ret = -1;
            byte[] buffer = UnicodeEncoding.Default.GetBytes(m_Message);
            int taskId = 0;
            switch (transType)
            {
                case TransType.TextMessage:
                    ret = AnyChatCoreSDK.SendTextMessage(m_TempUserID, m_Secret, m_Message, length);
                    break;
                case TransType.TransBuffer:

                    ret = AnyChatCoreSDK.TransBuffer(m_TempUserID, buffer, length);
                    break;
                case TransType.TransBufferEx:

                    ret = AnyChatCoreSDK.TransBufferEx(m_TempUserID, buffer, length, 0, 0, 0, ref taskId);
                    break;
            }


            //显示聊天内容
            string m_DispMsg = "我 To   " + m_TempUserName+" ";
            ShowText(m_DispMsg, txt_Accept.TextLength, m_DispMsg.Length, Color.Green, new Font("黑体", 9, FontStyle.Bold));
            ShowText(DateTime.Now.ToString(), txt_Accept.TextLength, DateTime.Now.ToString().Length, Color.Green, new Font("黑体", 9, FontStyle.Bold));
            ShowText("\r\n", txt_Accept.TextLength, 4, Color.Blue, new Font("宋体", 12));
            ShowText("    ", txt_Accept.TextLength, 4, Color.Blue, new Font("宋体", 12));            
            if (transType == TransType.TransBufferEx)
            {
                ShowText(m_Message + ",taskId：" + taskId, txt_Accept.TextLength, m_Message.Length, Color.Black, new Font("黑体", 9));
            }
            else
            {
                ShowText(m_Message, txt_Accept.TextLength, m_Message.Length, Color.Black, new Font("黑体", 9));
            }
            ShowText("\r\n\r\n", txt_Accept.TextLength, 8, Color.Blue, new Font("宋体", 12));
            rtxt_sendtxt.Text = "";
        }

        /// <summary>
        /// 键盘按下组合键
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void rtxt_sendtxt_KeyDown(object sender, KeyEventArgs e)
        {
            if (ment_item_ctrlenter.Image != null)//Ctrl+Enter
            {
                if (e.Control == true && e.KeyCode == Keys.Enter)
                {
                    btn_sendtxt_Click(null, null);
                }
            }
            else//Enter
            {
                if (e.KeyCode == Keys.Enter)
                {
                    btn_sendtxt_Click(null, null);
                }
            }
        }
        /// <summary>
        /// 键盘释放组合键
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void rtxt_sendtxt_KeyUp(object sender, KeyEventArgs e)
        {
            if (ment_item_ctrlenter.Image != null)//Ctrl+Enter
            {
                if (e.Control == true && e.KeyCode == Keys.Enter)
                {
                    rtxt_sendtxt.Text = "";
                }
            }
            else//Enter
            {
                if (e.KeyCode == Keys.Enter)
                {
                    rtxt_sendtxt.Text = "";
                }
            }
        }
        /// <summary>
        /// 发送按钮右建菜单（Ctrl+Enter)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ment_item_ctrlenter_Click(object sender, EventArgs e)
        {
            ment_item_ctrlenter.Image = AnyChatCSharpDemo.Properties.Resources.duihao;
            ment_item_enter.Image = null;
        }
        /// <summary>
        /// 发送按钮右建菜单（Enter)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ment_item_enter_Click(object sender, EventArgs e)
        {
            ment_item_enter.Image = AnyChatCSharpDemo.Properties.Resources.duihao;
            ment_item_ctrlenter.Image = null;
        }
        /// <summary>
        /// 初始化字体,字号
        /// </summary>
        private void InitFont()
        {
            int m_SelectIndex = 0;
            int m_Index = 0;
            System.Drawing.Text.InstalledFontCollection m_ObjFont = new System.Drawing.Text.InstalledFontCollection();
            foreach (System.Drawing.FontFamily m_Font in m_ObjFont.Families)
            {
                cmb_font.Items.Add(m_Font.Name.ToString());

                if (m_Font.Name == "黑体")
                    m_SelectIndex = m_Index;
                m_Index++;
            }
            cmb_font.SelectedIndex = m_SelectIndex;

            foreach (string m_FontSize in m_AllFontSizeName)
            {
                cmb_fontsize.Items.Add(m_FontSize);
            }
            cmb_fontsize.SelectedItem = "小五";
        }

        #endregion

        #region 初始化用户列表面版

        private void InitUserPanel()
        {
            pnl_userlist.Width = 285;
            pnl_userlist.Height = 400;
            pnl_userlist.Top = (this.Height - 30 - pnl_userlist.Height) / 2;
            pnl_userlist.Left = this.Width - 41;
        }
        /// <summary>
        /// 显示与隐藏用户面版
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pic_userlistdisp_Click(object sender, EventArgs e)
        {
            if (pic_userlistdisp.BackColor == Color.Green)
            {
                pic_userlistdisp.BackColor = Color.Blue;
                pnl_userlist.Left = this.Width - 291;
            }
            else
            {
                pic_userlistdisp.BackColor = Color.Green;
                pnl_userlist.Left = this.Width - 41;
            }
        }

        #endregion

        #region 单击用户列表

        private void dgv_onlineuser_Click(object sender, EventArgs e)
        {
            try
            {
                if (dgv_onlineuser.SelectedRows.Count == 0) return;
                DataGridViewRow dgvr = dgv_onlineuser.SelectedRows[0];
                string m_TempUserName = dgvr.Cells["gvc_username"].Value.ToString();
                if (m_TempUserName == frmLogin.m_UserName)
                {
                    chooseMyself = true;
                    return;
                }
                else
                {
                    chooseMyself = false;
                }
                
                lbl_touser.Text = "我 对 " + m_TempUserName + " 说：";
            }
            catch (Exception ex) { }
        }

        private void dgv_onlineuser_SelectionChanged(object sender, EventArgs e)
        {
            dgv_onlineuser_Click(null, null);
        }

        #endregion

        #region 权限设置

        #region 单击视频权限

        /// <summary>
        /// 单击视频权限
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void menu_item_video_Click(object sender, EventArgs e)
        {
            try
            {
                if (dgv_onlineuser.SelectedRows.Count == 0) return;
                DataGridViewRow dgvr = dgv_onlineuser.SelectedRows[0];
                string m_TempUserName = dgvr.Cells["gvc_username"].Value.ToString();
                if (m_TempUserName == frmLogin.m_UserName || m_TempUserName=="大家") return;
                int m_TempUserID = GetUserIDByName(m_TempUserName);
                AnyChatCoreSDK.UserCameraControl(m_TempUserID, menu_item_video.Checked);
            }
            catch (Exception ex) { }
        }

        #endregion

        #region 用户状态

        private void menu_item_status_Click(object sender, EventArgs e)
        {
            try
            {
                //if (dgv_onlineuser.SelectedRows.Count == 0) return;
                //DataGridViewRow dgvr = dgv_onlineuser.SelectedRows[0];
                //string m_TempUserName = dgvr.Cells["gvc_username"].Value.ToString();
                //if (m_TempUserName == frmLogin.m_UserName || m_TempUserName == "大家") return;
                //int m_TempUserID = GetUserIDByName(m_TempUserName);
                //int m_InfoName = Convert.ToInt32(txt_1.Text.Trim());
                //MessageBox.Show(m_TempUserID.ToString());
                //int m_Infoval = -1;
                //int ret = AnyChatCoreSDK.QueryUserState(m_TempUserID, m_InfoName, ref m_Infoval, 1000);
                //StringBuilder m_Infoval = new StringBuilder(100);
                //IntPtr m_Infoval =(IntPtr)0;
                //byte[] m_Infoval = new byte[100];
                //int result = Init_com(ref m_Infoval.ToCharArray());
                //int m_Infoval = 10;
                //int ret = AnyChatCoreSDK.QueryUserState(m_TempUserID, m_InfoName, ref m_Infoval, sizeof(int));
                //int len = 100;
                //byte[] buff = new byte[len];
                //Marshal.Copy(m_Infoval, buff, 0, len);
                //string m_Command = Encoding.Default.GetString(buff);
                //txt_2.Text = ret.ToString() + ":" + m_Infoval.ToString();
                //txt_2.Text = ret.ToString();

            }
            catch (Exception ex)
            {
                //txt_2.Text = ex.Message;
            }
        }

        #endregion

        #endregion

        #region 显示隐藏文本聊天区

        private void pnl_visableword_MouseEnter(object sender, EventArgs e)
        {
            if (pnl_word.Left == 658)//显示文本区状态
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.隐藏放上;
            }
            else
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.取消隐藏放上;
            }
        }

        private void pnl_visableword_MouseDown(object sender, MouseEventArgs e)
        {
            if (pnl_word.Left == 658)//显示文本区状态
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.隐藏按下;
            }
            else
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.取消隐藏按下;
            }
        }

        private void pnl_visableword_MouseUp(object sender, MouseEventArgs e)
        {
            if (pnl_word.Left == 658)//显示文本区状态
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.隐藏放上;
                pnl_word.Left = this.Width - 17-6;
                pnl_video.Width = 640;
            }
            else
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.取消隐藏放上;
                pnl_word.Left = 658;
                pnl_video.Width = 480;
            }
        }

        private void pnl_visableword_MouseLeave(object sender, EventArgs e)
        {
            if (pnl_word.Left == 658)//显示文本区状态
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.隐藏发送面板;
            }
            else
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.显示发送面板;
            }
        }

        #endregion

        #region 设置音视频状态

        /// <summary>
        /// 设置视频状态
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chk_localvideo_CheckedChanged(object sender, EventArgs e)
        {

            int ret = AnyChatCoreSDK.UserCameraControl(-1, chk_localvideo.Checked);
        }
        /// <summary>
        /// 设置音频状态
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chk_localaudio_CheckedChanged(object sender, EventArgs e)
        {
            int ret = AnyChatCoreSDK.UserSpeakControl(-1, chk_localaudio.Checked);
        }

        #endregion

        #region 视频最大化显示尺寸

        #endregion

        #region 重新设置视频分辨率

        private void cbb_fbl_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cbb_fbl.SelectedIndex == 0)
            {
                int bUseAppParam = 0;
                //应用本地视频编码参数，使得前述修改即时生效（参数为int型：1 使用新参数，0 使用默认参数）
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_APPLYPARAM, ref bUseAppParam, sizeof(int));
            }
            else
            {
                int bitrate = 0;  //0表示质量模式
                //设置本地视频编码的码率 
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_BITRATECTRL, ref bitrate, sizeof(int));
                int keyframe = 60;
                //设置本地视频编码的关键帧间隔
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_GOPCTRL, ref keyframe, sizeof(int));
                int framerate = 15;
                //设置本地视频编码的帧率
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_FPSCTRL, ref framerate, sizeof(int));
                int defaultParam = 3;
                // 设置本地视频编码的预设参数 
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_PRESETCTRL, ref defaultParam, sizeof(int));
                int videoWidth = 1920;
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_WIDTHCTRL, ref videoWidth, sizeof(int));
                int vedioHeight = 1080;
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, ref vedioHeight, sizeof(int));

                int bUseAppParam = 1;
                //应用本地视频编码参数，使得前述修改即时生效（参数为int型：1 使用新参数，0 使用默认参数）
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_APPLYPARAM, ref bUseAppParam, sizeof(int));
            }
        }

        #endregion

        #region 调节声音

        #region 调节滑块



        #endregion

        #endregion

        #region 传输文件及透明通道演示

        string sendPath;        //发送文件地址
        string receivePath;     //接收文件地址

        #region 接收文件

        private void Received_TransFile(int userId, string fileName, string filePath, int fileLength, int wParam, int lParam, int taskId, int userValue)
        {
            //这里用1作为接收标记
            if (wParam == 1)
            {
                FileInfo fi = new FileInfo(filePath);
                fi.MoveTo(receivePath +"\\"+ fi.Name);
                Print(receivePath + "\\" + fi.Name + "文件接收成功");
            }
        }

        #endregion

        #region 透明通道数据

        private void Received_TransBuffer(int userId, IntPtr buf, int len, int userValue)
        {
            //过滤信息（）
            string m_Command = Marshal.PtrToStringAnsi(buf);
            try
            {
                if (m_Command.Length > 3)
                {
                    string[] m_Packet = m_Command.Split(":".ToCharArray());
                    if (m_Packet.Length > 0){
                        //选择是否接收文件
                        if (m_Packet[0] == "003" && m_Packet[3] == "file")
                        {
                            int m_TempUserID = Convert.ToInt32(m_Packet[1]);
                            string m_pacName = GetUserNameByID(m_TempUserID);
                            DialogResult r = MessageBox.Show("文件名：" + m_Packet[2].ToString() + "，是否接收？", m_pacName + "发送文件请求", MessageBoxButtons.YesNo);
                            if (r == System.Windows.Forms.DialogResult.Yes)
                            {
                                FolderBrowserDialog fbd = new FolderBrowserDialog();
                                if (fbd.ShowDialog() == DialogResult.OK)
                                {
                                    receivePath = fbd.SelectedPath;
                                    string m_Message = "003:" + m_myUserID.ToString() + ":" + "fileisok:";
                                    byte[] buffer = Encoding.Default.GetBytes(m_Message);
                                    int rett = AnyChatCoreSDK.TransBuffer(m_TempUserID, buffer, buffer.Length);
                                }
                            }
                            else
                            { 
                            
                                string m_Message = "003:" + m_myUserID.ToString() + ":" + "fileisno:"+m_Packet[2].ToString();
                                byte[] buffer = Encoding.Default.GetBytes(m_Message);
                                int rett = AnyChatCoreSDK.TransBuffer(m_TempUserID, buffer, buffer.Length);
                            }
                        }
                        //发送文件
                        else if (m_Packet[0] == "003" && m_Packet[2] == "fileisok")
                        {
                            int taskId = 0;
                            int m_TempUserID = Convert.ToInt32(m_Packet[1]);
                            int flag = AnyChatCoreSDK.TransFile(m_TempUserID, sendPath, 1, 0, 0, ref taskId);
                            Print("成功发送" + sendPath + "文件");
                        }
                        else if (m_Packet[0] == "003" && m_Packet[2] == "fileisno")
                        {
                            string m_tempName = GetUserNameByID(Convert.ToInt32(m_Packet[1]));
                            Print(m_tempName + "拒绝接收文件" + m_Packet[3].ToString());
                        }
                        else
                        {
                            string m_UserName = GetUserNameByID(userId);
                            Print("用户：" + m_UserName + " 发来信息：" + m_Command);
                        }
                    }
                }
                else
                {
                    string m_UserName = GetUserNameByID(userId);
                    Print("用户：" + m_UserName + " 发来信息：" + m_Command);
                }                
            }
            catch (Exception ex)
            {

            }
        }

        private void Received_TransBufferEx(int userId, IntPtr buf, int len, int wParam, int lParam, int taskId, int userValue)
        {
            //过滤信息（）
            string m_Command = Marshal.PtrToStringAnsi(buf);
            try
            {
                string m_UserName = GetUserNameByID(userId);
                Print("用户：" + m_UserName + " 发来信息：" + m_Command + "，taskId：" + taskId);
            }
            catch (Exception ex)
            {

            }
        }

        #endregion

        #region 请求发送

        private void btn_transfile_Click(object sender, EventArgs e)
        {
            if (dgv_onlineuser.SelectedRows.Count == 0)
            {
                Print("文件发送失败，请选择目标用户");
                return;
            }
            else
            {
                DataGridViewRow dgvr = dgv_onlineuser.SelectedRows[0];
                string m_TempUserName = dgvr.Cells["gvc_username"].Value.ToString();
                if (m_TempUserName == frmLogin.m_UserName || m_TempUserName == "大家")
                {
                    Print("文件发送失败，请选择目标用户");
                    return;
                }
                else
                {
                    OpenFileDialog dlgopenFile = new OpenFileDialog();
                    dlgopenFile.Title = "选择需要发送的文件";
                    DialogResult dr = dlgopenFile.ShowDialog();

                    if (dr == DialogResult.OK)
                    {
                        if (File.Exists(dlgopenFile.FileName))
                        {
                            sendPath = dlgopenFile.FileName;
                            //int taskId = 0;
                            int m_TempUserID = GetUserIDByName(m_TempUserName);
                            //发送命令
                            FileInfo fi = new FileInfo(dlgopenFile.FileName);
                            string m_Message = "003:" + m_myUserID.ToString() + ":" + fi.Name + ":" + "file";
                            byte[] buffer = Encoding.Default.GetBytes(m_Message);
                            int rett = AnyChatCoreSDK.TransBuffer(m_TempUserID, buffer, buffer.Length);
                            Print("向" + m_TempUserName + "发送文件，等待接收...");
                        }
                    }
                    dlgopenFile.Dispose();
                    dlgopenFile = null;
                }
            }
        }

        #endregion

        #endregion

        /// <summary>
        /// 视频设备列表
        /// </summary>
        private List<ComboBoxItem> m_videoDeviceList = new List<ComboBoxItem>();
        private frmSetting settingForm = null;
        private void btnSetting_Click(object sender, EventArgs e)
        {
            settingForm = new frmSetting(m_videoDeviceList, m_myUserID);

            settingForm.ShowDialog();
        }

        private string[] getLocalVideoDeivceName()
        {
            string[] retVal = null;

            int deviceNum = 0;
            AnyChatCoreSDK.EnumVideoCapture(null, ref deviceNum);
            IntPtr[] deviceList = new IntPtr[deviceNum];
            retVal = new string[deviceNum];

            AnyChatCoreSDK.EnumVideoCapture(deviceList, ref deviceNum);
            for (int idx = 0; idx < deviceNum; idx++)
            {
                IntPtr intPtr = deviceList[idx];
                int len = 100;
                byte[] byteArray = new byte[len];
                Marshal.Copy(intPtr, byteArray, 0, len);
                string m_DeviceName = Encoding.Default.GetString(byteArray);
                m_DeviceName = m_DeviceName.Substring(0, m_DeviceName.IndexOf('\0'));

                //addLog("获取的第" + (idx + 1) + "个视频设备为：" + m_DeviceName, LogType.LOG_TYPE_NORMAL);
                retVal[idx] = m_DeviceName;

                ComboBoxItem item = new ComboBoxItem();
                item.Text = m_DeviceName;
                item.Value = idx;
                m_videoDeviceList.Add(item);
            }
            return retVal;

        }

        /// <summary>
        /// 将Json字符串转化成对象
        /// </summary>
        /// <typeparam name="T">转换的对象类型</typeparam>
        /// <param name="output">json字符串</param>
        /// <returns></returns>
        public T ToClass<T>(string output)
        {
            object result;
            DataContractJsonSerializer outDs = new DataContractJsonSerializer(typeof(T));
            using (MemoryStream outMs = new MemoryStream(Encoding.UTF8.GetBytes(output)))
            {
                result = outDs.ReadObject(outMs);
            }
            return (T)result;
        }

        /// <summary>  
        /// POST请求与获取结果  
        /// </summary>  
        public string HttpPost(string Url, string postDataStr)
        {
            string retVal = string.Empty;
            try
            {
                HttpWebRequest request = (HttpWebRequest)WebRequest.Create(Url);
                request.Method = "POST";
                request.ContentType = "application/x-www-form-urlencoded";
                StreamWriter writer = new StreamWriter(request.GetRequestStream(), Encoding.ASCII);
                writer.Write(postDataStr);
                writer.Flush();

                HttpWebResponse response = (HttpWebResponse)request.GetResponse();
                string encoding = response.ContentEncoding;
                if (encoding == null || encoding.Length < 1)
                {
                    encoding = "UTF-8"; //默认编码  
                }
                StreamReader reader = new StreamReader(response.GetResponseStream(), Encoding.GetEncoding(encoding));
                retVal = reader.ReadToEnd();
            }
            catch (Exception ex)
            {
                Print("HttpPost has exception, message: " + ex.Message);
            }
            return retVal;
        }

        private void comboBox_TransType_SelectedIndexChanged(object sender, EventArgs e)
        {
            transType = (TransType)comboBox_TransType.SelectedIndex;
        }

        /// <summary>
        /// 字节转字符串
        /// </summary>
        /// <param name="byteStr">字节数组</param>
        /// <returns>转换后的字符串</returns>
        public string byteToString(byte[] byteStr)
        {
            string retVal = "";
            try
            {
                retVal = System.Text.Encoding.GetEncoding("GB18030").GetString(byteStr, 0, byteStr.Length);
            }
            catch (Exception exp)
            {
                Console.Write(exp.Message);
            }
            return retVal.TrimEnd('\0');
        }
    }

    /// <summary>
    /// 签名信息类
    /// </summary>
    [DataContract]
    class JsonObject
    {
        [DataMember]
        public int errorcode { get; set; }
        [DataMember]
        public int timestamp { get; set; }
        [DataMember]
        public string sigStr { get; set; }
    }

}