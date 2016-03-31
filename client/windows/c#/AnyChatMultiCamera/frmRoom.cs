using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using ANYCHATAPI;
using System.IO;
using System.Net;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;


namespace AnyChatMultiCamera
{
    public partial class frmRoom2 : Form
    {
        #region 变量定义区域

        /// <summary>
        /// 视频放大宽度
        /// </summary>
        private int m_VideoWidthMax = 800;
        /// <summary>
        /// 视频放大高度
        /// </summary>
        private int m_VideoHeightMax = 600;

        /// <summary>
        /// 保存被隐藏的登录窗口
        /// </summary>
        public frmLogin m_loginForm = null;
        /// <summary>
        /// 资源释放标志
        /// </summary>
        public bool bReleased = false;
        /// <summary>
        /// 房间ID
        /// </summary>
        private int m_RoomID = 0;
        /// <summary>
        /// 用户ID（系统自动分配）
        /// </summary>
        private int m_myUserID = -1;
        /// <summary>
        /// 用户名
        /// </summary>
        private string m_myUserName = string.Empty;
        /// <summary>
        /// 用户密码
        /// </summary>
        private string m_userPassword = string.Empty;
        /// <summary>
        /// 服务器IP
        /// </summary>
        private string m_serverIP = string.Empty;
        /// <summary>
        /// 端口
        /// </summary>
        private int m_port = 0;
        private bool m_isOpenRemoteDesktop = false;
        /// <summary>
        /// 房间用户列表（不包括自己），开发包自带
        /// </summary>
        private List<int> m_others = new List<int>();
        /// <summary>
        /// 在线用户列表
        /// </summary>
        private List<OnlineUserInfo> m_OnlineUserInfoList = new List<OnlineUserInfo>();
        /// <summary>
        /// 视频设备列表
        /// </summary>
        private List<ComboBoxItem> m_videoDeviceList = new List<ComboBoxItem>();
        private frmSetting settingForm = null;
        /// <summary>
        /// 几列视频窗口(横着几个视频窗口)
        /// </summary>
        private int m_ColUserVideo = 4;
        /// <summary>
        /// 应用ID
        /// </summary>
        private string m_appGuid = string.Empty;
        /// <summary>
        /// 当前选定的远程用户ID
        /// </summary>
        private int currentRemoteUserID = 0;
        /// <summary>
        /// 登录方式
        /// </summary>
        private LoginType m_loginType = LoginType.Normal;
        /// <summary>
        /// 签名Url
        /// </summary>
        public string m_signUrl = string.Empty;
        /// <summary>
        /// 远程用户Id
        /// </summary>
        public int remoteUserID = 0;
        /// <summary>
        /// 是否在录像的标志
        /// </summary>
        public bool isRecord = false;

        #endregion

        #region 构造函数
        public frmRoom2()
        {
            InitializeComponent();
        }

        public frmRoom2(ConnectInfo connInfo, frmLogin loginForm)
        {
            m_myUserName = connInfo.UserName;
            m_RoomID = connInfo.RoomID;
            m_userPassword = connInfo.UserPassword;
            m_serverIP = connInfo.ServerIP;
            m_port = connInfo.Port;
            m_isOpenRemoteDesktop = connInfo.isOpenRemoteDesktop;
            m_appGuid = connInfo.AppGuid;
            m_loginType = connInfo.loginType;
            m_signUrl = connInfo.signServerUrl;

            this.m_loginForm = loginForm;

            InitializeComponent();
        }
        #endregion

        #region 窗体事件

        private void frmRoom_FormClosed(object sender, FormClosedEventArgs e)
        {
            AnyChatCoreSDK.LeaveRoom(m_RoomID);
            AnyChatCoreSDK.Logout();
            AnyChatCoreSDK.Release();
            Application.Exit();
            bReleased = true;
        }

        private void btnLeaveRoom_Click(object sender, EventArgs e)
        {
            AnyChatCoreSDK.LeaveRoom(m_RoomID);
            AnyChatCoreSDK.Logout();
            AnyChatCoreSDK.Release();

            this.Hide();
            this.m_loginForm.Show();
        }

        private void frmRoom_Load(object sender, EventArgs e)
        {
            SystemSetting.Init(this.Handle);
            int screenCameraCtrl = 0;
            if (m_isOpenRemoteDesktop)
            {
                screenCameraCtrl = 1;
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_CORESDK_SCREENCAMERACTRL, ref screenCameraCtrl, sizeof(int));
            }

            SystemSetting.AnyChatRecordSnapShot_Handler = new SystemSetting.AnyChatRecordSnapShotCallBack(RecordSnapShot);
            SystemSetting.AnyChatRecordSnapShotEx_Handler = new SystemSetting.AnyChatRecordSnapShotExCallBack(RecordSnapShotEx);
            SystemSetting.AnyChatVideoScreenEvent_Handler = new SystemSetting.AnyChatVideoScreenEventCallBack(VideoScreenEvent);

            cmbBoxSelectVideo.SelectedIndex = 0;
        }

        private void frmRoom_Shown(object sender, EventArgs e)
        {
            /* AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
             * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
             * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
             */
            int ret = AnyChatCoreSDK.Connect(m_serverIP, m_port);

            createRemoteVideoDisplayZone();

            /*
             * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，
             * 详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
             */
            ret = AnyChatCoreSDK.Login(m_myUserName, m_userPassword, 0);

            label_radio1.Text = string.Empty;
            label_radio2.Text = string.Empty;
            label_radio3.Text = string.Empty;
            label_radio4.Text = string.Empty;
        }

        #endregion

        #region 重载WndProc

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == AnyChatCoreSDK.WM_GV_CONNECT)
            {

                ///连接
                int succed = m.WParam.ToInt32();
                int ret = -1;
                if (succed == 1)
                {
                    addLog("连接AnyChat服务器成功,正在登录系统...", LogType.LOG_TYPE_NORMAL);
                }
                else
                {
                    addLog("连接AnyChat服务器失败, returnCode = " + ret, LogType.LOG_TYPE_ERROR);
                    Log.SetLog("WM_GV_CONNECT      连接AnyChat服务器失败");
                }


            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_LOGINSYSTEM)
            {

                ///登录系统
                if (m.LParam.ToInt32() == 0)
                {
                    addLog("登录AnyChat系统成功", LogType.LOG_TYPE_NORMAL);
                    m_myUserID = m.WParam.ToInt32();//保存当前ID

                    AnyChatCoreSDK.EnterRoom(m_RoomID, "", 0);

                }
                else
                {
                    addLog("登录失败：Error= " + m.LParam.ToString(), LogType.LOG_TYPE_ERROR);
                    Log.SetLog("WM_GV_LOGINSYSTEM          登录失败：Error=" + m.LParam.ToString());
                }

            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_ENTERROOM)
            {

                //进入房间
                int lparam = m.LParam.ToInt32();
                if (lparam == 0)
                {
                    int roomid = m.WParam.ToInt32();
                    addLog("进入房间成功,房间编号为：" + roomid.ToString(), LogType.LOG_TYPE_NORMAL);
                    m_RoomID = roomid;

                    openLocalVideo(getLocalVideoDeivceName());

                    //int ret = AnyChatCoreSDK.SetVideoPos(-1, panel_OwnerVideoZone.Handle, 0, 0, panel_OwnerVideoZone.Width, panel_OwnerVideoZone.Height);
                    //ret = AnyChatCoreSDK.UserCameraControl(-1, true);
                    //ret = AnyChatCoreSDK.UserSpeakControl(-1, true);
                    //string deviceName = "1-WebCam SC-10HDD12636N";
                    //AnyChatCoreSDK.SetUserStreamInfo(-1, 0, AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_DEVICENAME, deviceName, deviceName.ToCharArray().Length);
                    //int ret = AnyChatCoreSDK.SetVideoPosEx(-1, panel_OwnerVideoZone.Handle, 0, 0, panel_OwnerVideoZone.Width, panel_OwnerVideoZone.Height, 0, 0);
                    //ret = AnyChatCoreSDK.UserCameraControlEx(-1, true, 0, 0, "");
                    //ret = AnyChatCoreSDK.UserSpeakControlEx(-1, true, 0, 0, "");

                }
                else
                {
                    addLog("进入房间失败，Error = " + m.LParam.ToString(), LogType.LOG_TYPE_ERROR);
                    Log.SetLog("WM_GV_ENTERROOM                进入房间，失败，Error：" + lparam.ToString());
                }

            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_ONLINEUSER)
            {
                ///目前在房间的用户列表
                int usrcnt = m.WParam.ToInt32();
                addLog("在编号为：" + m.LParam.ToInt32() + " 的房间共有" + usrcnt + "位在线用户", LogType.LOG_TYPE_NORMAL);

                int cnt = 0;//在线用户数量
                AnyChatCoreSDK.GetOnlineUser(null, ref cnt);//获取在线用户数量
                int[] userID = new int[cnt];//在线用户ID
                AnyChatCoreSDK.GetOnlineUser(userID, ref cnt);//获取在线用户ID数组

                if (userID.Length >= 1)
                {
                    for (int i = 0; i < userID.Length; i++)
                    {
                        m_others.Add(userID[i]);//存入在线用户列表中（开发包带的用户在线ＩＤ数组）
                        UpdateUserList(userID[i], i);//添加到在线用户列表（自定义，带用户属性结构）
                    }
                    UpdateOnlineUser();
                }
                else
                {
                    dgv_onlineuser.Rows.Clear();

                    DataGridViewRow dgvr = new DataGridViewRow();
                    dgv_onlineuser.Rows.Add(dgvr);
                    dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
                    dgvr.Cells["gvc_username"].Value = m_myUserName + "（自己）";
                    dgvr.Cells["gvc_userID"].Value = m_myUserID;
                    dgvr.Cells["gvc_character"].Value = AnyChatMultiCamera.Properties.Resources.主持人_浅灰;
                    dgvr.Cells["gvc_audio"].Value = AnyChatMultiCamera.Properties.Resources.麦克;
                    dgvr.Cells["gvc_video"].Value = AnyChatMultiCamera.Properties.Resources.摄像头;
                }
            }
            //用户进入或者离开房间
            else if (m.Msg == AnyChatCoreSDK.WM_GV_USERATROOM)
            {

                ///新用户加入或退出房间
                int userID = m.WParam.ToInt32();
                int boEntered = m.LParam.ToInt32();

                if (boEntered == 1)
                {
                    if (userID != m_myUserID)
                    {
                        m_others.Add(userID);

                        UpdateUserList(userID, m_others.Count - 1);
                        addLog("用户：" + GetUserNameByID(userID) + " 进入房间", LogType.LOG_TYPE_NORMAL);
                    }
                }
                else
                {
                    m_others.Remove(userID);
                    for (int i = 0; i < m_OnlineUserInfoList.Count; i++)
                    {
                        if (m_OnlineUserInfoList[i].m_UserID == userID)
                        {
                            m_OnlineUserInfoList.RemoveAt(i);
                            break;
                        }
                    }
                    addLog("用户：" + GetUserNameByID(userID) + " 离开房间", LogType.LOG_TYPE_NORMAL);
                }
                UpdateOnlineUser();//更新用户列表
                this.Invalidate();//重绘界面，防止界面假死
            }
            //摄像头打开状态
            else if (m.Msg == AnyChatCoreSDK.WM_GV_CAMERASTATE)
            {

            }
            //网络断开
            else if (m.Msg == AnyChatCoreSDK.WM_GV_LINKCLOSE)
            {

                AnyChatCoreSDK.LeaveRoom(-1);
                int wparam = m.WParam.ToInt32();
                int lparam = m.LParam.ToInt32();
                addLog("网络断开，ErrorCode = " + wparam.ToString(), LogType.LOG_TYPE_ERROR);
                this.Hide();
                m_loginForm.Show();
                Log.SetLog("WM_GV_LINKCLOSE            响应网络断开,errorcode:=" + lparam);
            }
            base.WndProc(ref m);
        }

        #endregion

        #region 日志输出

        /// <summary>
        /// 日志类型
        /// </summary>
        public enum LogType
        {
            /// <summary>
            /// 一般类型日志
            /// </summary>
            LOG_TYPE_NORMAL = 0,

            /// <summary>
            /// API接口调用日志
            /// </summary>
            LOG_TYPE_API = 1,

            /// <summary>
            /// 事件日志
            /// </summary>
            LOG_TYPE_EVENT = 2,

            /// <summary>
            /// 错误日志
            /// </summary>
            LOG_TYPE_ERROR = 3
        }

        /// <summary>
        /// 显示系统信息
        /// </summary>
        /// <param name="m_Msg"></param>
        private void outputMessage(string m_Msg)
        {
            string m_SysInfo = "[系统信息] ";
            m_Msg += "\r\n\r\n";
            ShowText(m_SysInfo, txt_OutputMessage.TextLength, m_SysInfo.Length, Color.Red, new Font("黑体", 9, FontStyle.Bold));
            ShowText(m_Msg, txt_OutputMessage.TextLength, m_Msg.Length, Color.Black, new Font("黑体", 9));
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
            txt_OutputMessage.AppendText(sText);
            txt_OutputMessage.Select(nStart, nLength);    // 需要修改颜色的部分
            txt_OutputMessage.SelectionColor = color;     // 颜色
            txt_OutputMessage.SelectionFont = font;       // 字体
            txt_OutputMessage.ScrollToCaret();
            txt_OutputMessage.Select(txt_OutputMessage.Text.Length, 0);
        }

        private void addLog(string logText, LogType logType)
        {
            Color logColor = new Color();
            switch (logType)
            {
                case LogType.LOG_TYPE_NORMAL:
                    //color = Color.FromArgb(51, 51, 51);
                    logColor = Color.Gray;
                    break;
                case LogType.LOG_TYPE_API:
                    logColor = Color.Green;
                    break;
                case LogType.LOG_TYPE_EVENT:
                    logColor = Color.Yellow;
                    break;
                case LogType.LOG_TYPE_ERROR:
                    logColor = Color.Red;
                    break;
            }

            string curTime = string.Empty;
            curTime = "【" + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "】";
            var currentLen = txt_OutputMessage.TextLength;

            txt_OutputMessage.AppendText(curTime + logText + "\r\n");
            txt_OutputMessage.Select(currentLen, logText.Length);    // 需要修改颜色的部分
            txt_OutputMessage.SelectionColor = logColor;       // 颜色
            txt_OutputMessage.ScrollToCaret();
            //txt_OutputMessage.Select(txt_OutputMessage.Text.Length, 0);

        }

        #endregion

        #region 增加或减少用户

        private void UpdateUserList(int m_UserID, int m_Index)
        {
            OnlineUserInfo m_TempOnlineUserInfo = new OnlineUserInfo();//创建用户在线列表（自定义，包含用户属性）
            StringBuilder m_TempName = new StringBuilder(30);
            int ret = AnyChatCoreSDK.GetUserName(m_UserID, m_TempName, 30);//获取用户账号
            m_TempOnlineUserInfo.m_UserName = m_TempName.ToString();
            m_TempOnlineUserInfo.m_UserID = m_UserID;
            m_TempOnlineUserInfo.m_Index = m_Index;
            m_TempOnlineUserInfo.m_Permission = new int[] { 0, 0, 0 };//用户权限
            m_OnlineUserInfoList.Add(m_TempOnlineUserInfo);//添加到在线用户列表
        }
        /// <summary>
        /// 通过用户ID获得用户账号
        /// </summary>
        /// <param name="m_UserID"></param>
        /// <returns></returns>
        private string GetUserNameByID(int m_UserID)
        {
            StringBuilder m_TempName = new StringBuilder(30);
            int ret = AnyChatCoreSDK.GetUserName(m_UserID, m_TempName, 30);//获取用户账号
            return m_TempName.ToString();
        }
        /// <summary>
        /// 通过用户账号获得用户ID
        /// </summary>
        /// <param name="m_UserNameTemp"></param>
        /// <returns></returns>
        private int GetUserIDByName(string m_UserNameTemp)
        {
            int m_TempUserID = -1;
            for (int i = 0; i < m_OnlineUserInfoList.Count; i++)
            {
                if (m_OnlineUserInfoList[i].m_UserName == m_UserNameTemp)
                {
                    m_TempUserID = m_OnlineUserInfoList[i].m_UserID;
                    break;
                }
            }
            return m_TempUserID;
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
            //pnl_video.Controls.Clear();//清空所有视频窗口
            dgvr = new DataGridViewRow();
            dgv_onlineuser.Rows.Add(dgvr);
            dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
            dgvr.Cells["gvc_username"].Value = m_myUserName + "（自己）";
            dgvr.Cells["gvc_userID"].Value = m_myUserID;
            dgvr.Cells["gvc_character"].Value = AnyChatMultiCamera.Properties.Resources.主持人_浅灰;
            dgvr.Cells["gvc_audio"].Value = AnyChatMultiCamera.Properties.Resources.麦克;
            dgvr.Cells["gvc_video"].Value = AnyChatMultiCamera.Properties.Resources.摄像头;
            //显示自己
            for (int i = 0; i < m_OnlineUserInfoList.Count; i++)
            {
                dgvr = new DataGridViewRow();
                dgv_onlineuser.Rows.Add(dgvr);
                dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
                dgvr.Cells["gvc_username"].Value = m_OnlineUserInfoList[i].m_UserName;
                dgvr.Cells["gvc_userID"].Value = m_OnlineUserInfoList[i].m_UserID;
                dgvr.Cells["gvc_audio"].Value = AnyChatMultiCamera.Properties.Resources.麦克;
                dgvr.Cells["gvc_video"].Value = AnyChatMultiCamera.Properties.Resources.摄像头;
                dgvr.Cells["gvc_character"].Value = AnyChatMultiCamera.Properties.Resources.普通人_浅灰;
                //CreateUserVideo(m_OnlineUserInfoList[i].m_UserID);
                if (m_TempUserName == m_OnlineUserInfoList[i].m_UserName)
                {
                    m_DGVSelectRow = i + 1;
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

        #region 创建用户视频窗口

        //private void CreateUserVideo(int m_UserID)
        //{
        //    //用户视频横列显示规则
        //    int userCount = GetUserCount();
        //    if (userCount > 0 && userCount <= 1) m_ColUserVideo = 1;
        //    else if (userCount > 1 && userCount <= 4) m_ColUserVideo = 2;
        //    else if (userCount > 4) m_ColUserVideo = 3;

        //    int m_PnlCount = pnl_video.Controls.Count;
        //    Panel m_ShowWnd = new Panel();
        //    m_ShowWnd.Name = m_UserID.ToString();
        //    m_ShowWnd.Width = (pnl_video.Width) / m_ColUserVideo;
        //    m_ShowWnd.Height = m_ShowWnd.Width * 4 / 5;
        //    m_ShowWnd.Top = m_PnlCount / m_ColUserVideo * m_ShowWnd.Height + m_PnlCount / m_ColUserVideo * 5;
        //    m_ShowWnd.Left = m_PnlCount % m_ColUserVideo * m_ShowWnd.Width + m_PnlCount % m_ColUserVideo * 5;
        //    m_ShowWnd.BackColor = Color.Black;
        //    m_ShowWnd.DoubleClick += new EventHandler(ShowWnd_DoubleClick);
        //    m_ShowWnd.MouseEnter += new EventHandler(m_ShowWnd_MouseEnter);
        //    m_ShowWnd.MouseLeave += new EventHandler(m_ShowWnd_MouseLeave);
        //    pnl_video.Controls.Add(m_ShowWnd);
        //    AnyChatCoreSDK.SetVideoPos(m_UserID, m_ShowWnd.Handle, 0, 0, m_ShowWnd.Width, m_ShowWnd.Height);
        //    AnyChatCoreSDK.UserCameraControl(m_UserID, true);
        //    AnyChatCoreSDK.UserSpeakControl(m_UserID, true);

        //}

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

        private void openLocalVideo(string[] videoDeviceName)
        {
            int streamIndex = 0;
            
            int panelHeight = panel_OwnerVideoZone.Height;
            int panelWidth = panel_OwnerVideoZone.Width;

            int videoDeviceNum = videoDeviceName.Length;

            //int perPanelVideoWidth = panelWidth / videoDeviceNum;
            int perPanelVideoWidth = panelHeight * 4 / 3;
            panel_OwnerVideoZone.Controls.Clear();

            for (int idx = 0; idx < videoDeviceNum; idx++)
            {
                streamIndex = idx;
                int m_PnlCount = panel_OwnerVideoZone.Controls.Count;
                Panel m_ShowWnd = new Panel();
                m_ShowWnd.Name = idx.ToString();
                m_ShowWnd.Width = panelWidth / videoDeviceNum;
                m_ShowWnd.Height = m_ShowWnd.Width * 4 / 5;
                if (m_ShowWnd.Height > panelHeight)
                {
                    m_ShowWnd.Width = panelHeight * 4 / 3;
                    m_ShowWnd.Height = panelHeight;

                }
                m_ShowWnd.Top = m_PnlCount / videoDeviceNum * m_ShowWnd.Height + m_PnlCount / videoDeviceNum * 5;
                m_ShowWnd.Left = m_PnlCount % videoDeviceNum * m_ShowWnd.Width + m_PnlCount % videoDeviceNum * 5;
                m_ShowWnd.BackColor = Color.Black;
                //m_ShowWnd.DoubleClick += new EventHandler(ShowWnd_DoubleClick);
                //m_ShowWnd.MouseEnter += new EventHandler(m_ShowWnd_MouseEnter);
                //m_ShowWnd.MouseLeave += new EventHandler(m_ShowWnd_MouseLeave);
                panel_OwnerVideoZone.Controls.Add(m_ShowWnd);


                AnyChatCoreSDK.SetUserStreamInfo(-1, streamIndex, AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_DEVICENAME, videoDeviceName[idx], videoDeviceName[idx].ToCharArray().Length);
                addLog("SetUserStreamInfo(-1," + streamIndex + ", AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_DEVICENAME," + videoDeviceName[idx] + ", " + videoDeviceName[idx].ToCharArray().Length + ")", LogType.LOG_TYPE_API);
                AnyChatCoreSDK.SetVideoPosEx(-1, m_ShowWnd.Handle, 0, 0, m_ShowWnd.Width, m_ShowWnd.Height, streamIndex, 0);
                addLog("SetVideoPosEx(-1," + m_ShowWnd.Handle + ", 0, 0," + m_ShowWnd.Width + ", " + m_ShowWnd.Height + ", " + streamIndex + ", 0)", LogType.LOG_TYPE_API);
                AnyChatCoreSDK.UserCameraControlEx(-1, true, streamIndex, 0, string.Empty);
                addLog("UserCameraControlEx(-1, true, " + streamIndex + ", 0, " + string.Empty + ")", LogType.LOG_TYPE_API);
                AnyChatCoreSDK.UserSpeakControlEx(-1, true, streamIndex, 0, string.Empty);
                addLog("UserSpeakControlEx(-1, true, " + streamIndex + ", 0, " + string.Empty + ")", LogType.LOG_TYPE_API);


            }

            timer1.Enabled = true;
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

                addLog("获取的第" + (idx + 1) + "个视频设备为：" + m_DeviceName, LogType.LOG_TYPE_NORMAL);
                retVal[idx] = m_DeviceName;

                ComboBoxItem item = new ComboBoxItem();
                item.Text = m_DeviceName;
                item.Value = idx;
                m_videoDeviceList.Add(item);
            }

            return retVal;

        }

        /// <summary>
        /// 控制远程用户音视频
        /// </summary>
        /// <param name="remoteUserID">远程用户ID</param>
        /// <param name="controlFlag">控制开关，true表示打开、false表示关闭</param>
        private void controlRemoteVideo(int remoteUserID, bool controlFlag)
        {
            int streamIndex = 0;

            int panelWidth = panel_OtherVideoZone.Width;
            int videoDeviceNum = 4;

            int perPanelVideoWidth = panelWidth / videoDeviceNum;
            //panel_OtherVideoZone.Controls.Clear();

            for (int idx = 0; idx < videoDeviceNum; idx++)
            {
                streamIndex = idx;
                int m_PnlCount = panel_OtherVideoZone.Controls.Count;
                Panel m_ShowWnd = new Panel();

                for (int iCount = 0; iCount < m_PnlCount; iCount++)
                {
                    m_ShowWnd = panel_OtherVideoZone.Controls[iCount] as Panel;
                    if (m_ShowWnd.Name == streamIndex.ToString())
                        break;
                }
                
                int videoCodecID = 0;
                int retCode = -1;
                retCode = AnyChatCoreSDK.GetUserStreamInfo(remoteUserID, streamIndex, AnyChatCoreSDK.BRAC_STREAMINFO_VIDEOCODECID, ref videoCodecID, sizeof(int));
                retCode = 0;
                if (retCode == 0)
                {
                    //AnyChatCoreSDK.SetVideoPos(remoteUserID, m_ShowWnd.Handle, 0, 0, m_ShowWnd.Width, m_ShowWnd.Height);
                    if (controlFlag)
                    {
                        retCode = AnyChatCoreSDK.SetVideoPosEx(remoteUserID, m_ShowWnd.Handle, 0, 0, m_ShowWnd.Width, m_ShowWnd.Height, streamIndex, 0);
                        addLog("SetVideoPosEx(" + remoteUserID + "," + m_ShowWnd.Handle + ", 0, 0," + m_ShowWnd.Width + ", " + m_ShowWnd.Height + ", " + streamIndex + ", 0)", LogType.LOG_TYPE_API);
                    }
                    //AnyChatCoreSDK.UserCameraControl(remoteUserID, true);
                    retCode = AnyChatCoreSDK.UserCameraControlEx(remoteUserID, controlFlag, streamIndex, 0, string.Empty);
                    addLog("UserCameraControlEx(" + remoteUserID + ", " + controlFlag + ", " + streamIndex + ", 0, " + string.Empty + ")", LogType.LOG_TYPE_API);
                    //AnyChatCoreSDK.UserSpeakControl(remoteUserID, true);
                    retCode = AnyChatCoreSDK.UserSpeakControlEx(remoteUserID, controlFlag, streamIndex, 0, string.Empty);
                    addLog("UserSpeakControlEx(" + remoteUserID + ", " + controlFlag + ", " + streamIndex + ", 0, " + string.Empty + ")", LogType.LOG_TYPE_API);
                }
            } 
        }

        private void dgv_onlineuser_Click(object sender, EventArgs e)
        {
            try
            {
                if (dgv_onlineuser.SelectedRows.Count == 0) return;

                DataGridViewRow dgvr = dgv_onlineuser.SelectedRows[0];

                remoteUserID = Int32.Parse(dgvr.Cells["gvc_userID"].Value.ToString());
                string remoteUserName = dgvr.Cells["gvc_username"].Value.ToString();

                if (remoteUserID == m_myUserID || remoteUserID == currentRemoteUserID) return;

                //关闭上一个远程用户的视频
                controlRemoteVideo(currentRemoteUserID, false);

                currentRemoteUserID = remoteUserID;
                controlRemoteVideo(remoteUserID, true);

                groupBox_RemoteVideo.Text = "远程视频显示区域" + "（用户：" + remoteUserName + "）";
            }
            catch (Exception ex) { }

        }

        private void btnSetting_Click(object sender, EventArgs e)
        {
            settingForm = new frmSetting(m_videoDeviceList, m_myUserID);

            settingForm.ShowDialog();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            int retCode = 0;
            int streamIdx = 0;
            int devcNum = m_videoDeviceList.Count;

            for (int idx = 0; idx < devcNum; idx++)
            {
                streamIdx = idx;
                int videoBitrate = 0;

                //retCode = AnyChatCoreSDK.QueryUserState(-1, AnyChatCoreSDK.BRAC_USERSTATE_VIDEOBITRATE, ref videoBitrate, sizeof(int));
                retCode = AnyChatCoreSDK.GetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_STREAMINFO_VIDEOBITRATE, ref videoBitrate, sizeof(int));

                string m_AVSpeed = videoBitrate.ToString()+"B/S";
                if (videoBitrate > 1000)
                {
                    try
                    {
                        double m_AVTemp = (double)videoBitrate / 1000.0;
                        m_AVSpeed = m_AVTemp.ToString();
                        m_AVSpeed = m_AVSpeed.Substring(0, m_AVSpeed.Length - 2) + "KB/S";
                    }
                    catch { }
                }

                switch (idx)
                {
                    case 0:
                        label_radio1.Text = "0路视频流码率：" + m_AVSpeed;

                        break;
                    case 1:
                        label_radio2.Text = "1路视频流码率：" + m_AVSpeed;

                        break;
                    case 2:
                        label_radio3.Text = "2路视频流码率：" + m_AVSpeed;

                        break;

                    case 4:
                        label_radio4.Text = "3路视频流码率：" + m_AVSpeed;

                        break;

                }
            }
        }

        /// <summary>
        /// 动态创建视频显示区域
        /// </summary>
        private void createRemoteVideoDisplayZone()
        {
            int streamIndex = 0;

            int panelWidth = panel_OtherVideoZone.Width;
            int videoDeviceNum = 4;

            int perPanelVideoWidth = panelWidth / videoDeviceNum;
            panel_OtherVideoZone.Controls.Clear();

            for (int idx = 0; idx < videoDeviceNum; idx++)
            {
                streamIndex = idx;
                int m_PnlCount = panel_OtherVideoZone.Controls.Count;
                Panel m_ShowWnd = new Panel();
                m_ShowWnd.Name = idx.ToString();
                m_ShowWnd.Width = panelWidth / videoDeviceNum;
                m_ShowWnd.Height = m_ShowWnd.Width * 3 / 4;
                m_ShowWnd.Top = m_PnlCount / videoDeviceNum * m_ShowWnd.Height + m_PnlCount / videoDeviceNum * 4;
                m_ShowWnd.Left = m_PnlCount % videoDeviceNum * m_ShowWnd.Width + m_PnlCount % videoDeviceNum * 4;
                //m_ShowWnd.BackColor = Color.Black;
                switch (streamIndex)
                {
                    case 0:
                        m_ShowWnd.BackgroundImage = Properties.Resources.videobk1;
                        m_ShowWnd.BackgroundImageLayout = ImageLayout.Zoom;
                        break;
                    case 1:
                        m_ShowWnd.BackgroundImage = Properties.Resources.videobk2;
                        m_ShowWnd.BackgroundImageLayout = ImageLayout.Zoom;
                        break;
                    case 2:
                        m_ShowWnd.BackgroundImage = Properties.Resources.videobk3;
                        m_ShowWnd.BackgroundImageLayout = ImageLayout.Zoom;

                        break;
                    case 3:
                        m_ShowWnd.BackgroundImage = Properties.Resources.videobk4;
                        m_ShowWnd.BackgroundImageLayout = ImageLayout.Zoom;

                        break;
                }
                //m_ShowWnd.DoubleClick += new EventHandler(ShowWnd_DoubleClick);
                //m_ShowWnd.MouseEnter += new EventHandler(m_ShowWnd_MouseEnter);
                //m_ShowWnd.MouseLeave += new EventHandler(m_ShowWnd_MouseLeave);
                panel_OtherVideoZone.Controls.Add(m_ShowWnd);
            }
        }

        #region 双击用户视频窗口

        private void ShowWnd_DoubleClick(object sender, EventArgs e)
        {
            Control ShowWnd = (Control)sender;
            if (ShowWnd.Width != m_VideoWidthMax)
            {
                foreach (Control C in panel_OtherVideoZone.Controls)
                {
                    if (C.Name != ShowWnd.Name)
                    {
                        C.Visible = false;
                    }
                }
                ShowWnd.Top = (panel_OtherVideoZone.Height - m_VideoHeightMax) / 2;
                ShowWnd.Left = (panel_OtherVideoZone.Width - m_VideoWidthMax) / 2; ;
                ShowWnd.Width = m_VideoWidthMax;
                ShowWnd.Height = m_VideoHeightMax;

            }
            else
            {
                int streamIndex = 0;

                int panelWidth = panel_OtherVideoZone.Width;
                int videoDeviceNum = 4;

                int perPanelVideoWidth = panelWidth / videoDeviceNum;

                foreach (Control C in panel_OtherVideoZone.Controls)
                {
                    if (C.Name != ShowWnd.Name)
                    {
                        C.Visible = true;
                    }
                }

                int m_PnlCount = Int32.Parse(ShowWnd.Name.ToString()) + 1;
                ShowWnd.Width = panelWidth / videoDeviceNum;
                ShowWnd.Height = ShowWnd.Width * 3 / 4;
                ShowWnd.Top = m_PnlCount / videoDeviceNum * ShowWnd.Height + m_PnlCount / videoDeviceNum * 4;
                ShowWnd.Left = m_PnlCount % videoDeviceNum * ShowWnd.Width + m_PnlCount % videoDeviceNum * 4;


            }
            AnyChatCoreSDK.SetVideoPos(Convert.ToInt32(ShowWnd.Name), ShowWnd.Handle, 0, 0, ShowWnd.Width, ShowWnd.Height);
        }

        #endregion

        private void dgv_onlineuser_RowLeave(object sender, DataGridViewCellEventArgs e)
        {

            if (dgv_onlineuser.SelectedRows.Count > 0)
            {
                DataGridViewRow dgvr = dgv_onlineuser.SelectedRows[0];
                int leaveUserID = Int32.Parse(dgvr.Cells["gvc_userID"].Value.ToString());

                if (leaveUserID == m_myUserID) return;
                if (leaveUserID == currentRemoteUserID)
                {
                    //controlRemoteVideo(leaveUserID, false);
                }
            }
        }

        #region 本地视频窗口双击事件

        //private void pnl_local_MouseDoubleClick(object sender, MouseEventArgs e)
        //{
        //    Control ShowWnd = (Control)sender;
        //    if (ShowWnd.Width != m_VideoWidthMax)
        //    {
        //        foreach (Control C in pnl_video.Controls)
        //        {
        //            if (C.Name != ShowWnd.Name)
        //            {
        //                C.Visible = false;
        //            }
        //        }
        //        ShowWnd.Top = (pnl_video.Height - m_VideoHeightMax) / 2;
        //        ShowWnd.Left = (pnl_video.Width - m_VideoWidthMax) / 2; ;
        //        ShowWnd.Width = m_VideoWidthMax;
        //        ShowWnd.Height = m_VideoHeightMax;
        //        pnl_video.Controls.Add(ShowWnd);

        //    }
        //    else
        //    {
        //        foreach (Control C in pnl_video.Controls)
        //        {
        //            if (C.Name != ShowWnd.Name)
        //            {
        //                C.Visible = true;
        //            }
        //        }
        //        ShowWnd.Width = 167;
        //        ShowWnd.Height = 140;
        //        ShowWnd.Top = 471;
        //        ShowWnd.Left = 3;
        //        this.Controls.Add(ShowWnd);

        //    }
        //    //AnyChatCoreSDK.SetVideoPos(Convert.ToInt32(ShowWnd.Name), ShowWnd.Handle, 0, 0, ShowWnd.Width, ShowWnd.Height);
        //    int ret = AnyChatCoreSDK.SetVideoPos(-1, pnl_local.Handle, 0, 0, ShowWnd.Width, ShowWnd.Height);
        //}

        #endregion

        /// <summary>
        /// 将Json字符串转化成对象
        /// </summary>
        /// <typeparam name="T">转换的对象类型</typeparam>
        /// <param name="output">json字符串</param>
        /// <returns></returns>
        public static T ToClass<T>(string output)
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
        public static string HttpPost(string Url, string postDataStr)
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
                Log.SetLog("HttpPost has exception, message: " + ex.Message);
            }
            return retVal;
        }

        private void btnRecord_Click(object sender, EventArgs e)
        {
            int recordUserId = -1;
            int recordFlags = AnyChatCoreSDK.BRAC_RECORD_FLAGS_SERVER + AnyChatCoreSDK.BRAC_RECORD_FLAGS_VIDEO + AnyChatCoreSDK.BRAC_RECORD_FLAGS_AUDIO + 
                                AnyChatCoreSDK.BRAC_RECORD_FLAGS_MIXAUDIO + AnyChatCoreSDK.BRAC_RECORD_FLAGS_MIXVIDEO + AnyChatCoreSDK.BRAC_RECORD_FLAGS_STEREO +
                                AnyChatCoreSDK.BRAC_RECORD_FLAGS_ABREAST + AnyChatCoreSDK.BRAC_RECORD_FLAGS_STREAM + AnyChatCoreSDK.ANYCHAT_RECORD_FLAGS_LOCALCB;
            if (!isRecord)
            {
                //设置录制参数
                int record_width = 1280;
                int record_height = 960;
                int VADCtrol = 0;
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_RECORD_WIDTH, ref record_width, sizeof(int));
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_RECORD_HEIGHT, ref record_height, sizeof(int));
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_AUDIO_VADCTRL, ref VADCtrol, sizeof(int)); 
                
                //开始录像
                AnyChatCoreSDK.StreamRecordCtrl(recordUserId, true, recordFlags, 0);
                addLog("StreamRecordCtrl(" + recordUserId + ", " + true + ", " + recordFlags + ", 0 " + string.Empty + ")", LogType.LOG_TYPE_API);
                isRecord = true;
                btnRecord.Text = "结束录像";
            }
            else
            {
                //结束录像
                AnyChatCoreSDK.StreamRecordCtrl(recordUserId, false, recordFlags, 0);
                addLog("StreamRecordCtrl(" + recordUserId + ", " + false + ", " + recordFlags + ", 0 " + string.Empty + ")", LogType.LOG_TYPE_API);
                isRecord = false;
                btnRecord.Text = "开始录像";
                int VADCtrol = 1;
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_AUDIO_VADCTRL, ref VADCtrol, sizeof(int)); 
            }

        }


        private void btnSnapshot_Click(object sender, EventArgs e)
        {
            if (remoteUserID == 0) remoteUserID = -1;

            int snapshotFlags = AnyChatCoreSDK.BRAC_RECORD_FLAGS_SNAPSHOT + AnyChatCoreSDK.BRAC_RECORD_FLAGS_SERVER + AnyChatCoreSDK.BRAC_RECORD_FLAGS_LOCALCB +
                                AnyChatCoreSDK.BRAC_RECORD_FLAGS_MULTISTREAM;

            AnyChatCoreSDK.StreamRecordCtrlEx(remoteUserID, true, snapshotFlags, cmbBoxSelectVideo.SelectedIndex, "snapshot");
            addLog("StreamRecordCtrlEx(" + remoteUserID + ", " + true + ", " + snapshotFlags + "," + cmbBoxSelectVideo.SelectedIndex + "," + string.Empty + ")", LogType.LOG_TYPE_API);

            //AnyChatCoreSDK.SnapShot(remoteUserID, snapshotFlags, cmbBoxSelectVideo.SelectedIndex);
            //addLog("SnapShot(" + remoteUserID + ", " + snapshotFlags + "," + cmbBoxSelectVideo.SelectedIndex + ")", LogType.LOG_TYPE_API);
        }

        /// <summary>
        /// 录像和拍照
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="fileName"></param>
        /// <param name="param"></param>
        /// <param name="recordType"></param>
        /// <param name="userValue"></param>
        private void RecordSnapShot(int userId, string fileName, int param, bool recordType, int userValue)
        {
            MessageBox.Show(fileName);
        }

        /// <summary>
        /// 录像和拍照
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="fileName"></param>
        /// <param name="param"></param>
        /// <param name="recordType"></param>
        /// <param name="userValue"></param>
        private void RecordSnapShotEx(int userId, string fileName, int elapse, int flags, int param, string userStr, int userValue)
        {
            int recordFlags = AnyChatCoreSDK.BRAC_RECORD_FLAGS_SERVER + AnyChatCoreSDK.BRAC_RECORD_FLAGS_VIDEO + AnyChatCoreSDK.BRAC_RECORD_FLAGS_AUDIO +
                                AnyChatCoreSDK.BRAC_RECORD_FLAGS_MIXAUDIO + AnyChatCoreSDK.BRAC_RECORD_FLAGS_MIXVIDEO + AnyChatCoreSDK.BRAC_RECORD_FLAGS_STEREO +
                                AnyChatCoreSDK.BRAC_RECORD_FLAGS_ABREAST + AnyChatCoreSDK.BRAC_RECORD_FLAGS_STREAM + AnyChatCoreSDK.ANYCHAT_RECORD_FLAGS_LOCALCB;
            int snapshotFlags = AnyChatCoreSDK.BRAC_RECORD_FLAGS_SNAPSHOT + AnyChatCoreSDK.BRAC_RECORD_FLAGS_SERVER + AnyChatCoreSDK.BRAC_RECORD_FLAGS_LOCALCB +
                                AnyChatCoreSDK.BRAC_RECORD_FLAGS_MULTISTREAM;
            string logHeader = "生成录像文件为：";

            if (flags == snapshotFlags)
                logHeader = "生成拍照文件为：";

            addLog(logHeader + fileName + "，时长" + elapse + "秒", LogType.LOG_TYPE_NORMAL);
        }

        private void VideoScreenEvent(int userId, int type, int key, int flags, int wParam, int lParam, int userValue)
        {

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
