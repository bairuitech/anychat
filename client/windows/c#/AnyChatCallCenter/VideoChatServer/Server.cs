using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ANYCHATAPI;
using VideoChatHelp;
using System.IO;
using System.Runtime.InteropServices;


namespace VideoChatServer
{
    public partial class Server : Form
    {
        #region 构造函数

        public Server()
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
        /// 会话场次集合
        /// </summary>
        List<ConversationInfo> converstations = new List<ConversationInfo>();
        /// <summary>
        /// 已占用的房间集合
        /// </summary>
        List<RoomInfo> rooms = new List<RoomInfo>();

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
        public static SystemSettingServer.OnServerAppMessage_Received OnServerAppMessage_Received_main = null;

        string[] str;                       //用户信息集(业务服务器在线列表显示)

        // 服务器应用程序消息回调函数定义
        void OnServerAppMessageCallBack(int msg, int userValue)
        {
            try
            {
                OnServerAppMessage_Received_main = new SystemSettingServer.OnServerAppMessage_Received(OnServerAppMessageCallBack_main);
                this.rtb_message.Invoke(OnServerAppMessage_Received_main, msg, userValue);
            }
            catch (Exception ex)
            {
                Log.SetLog("OnServerAppMessageCallBack                 " + ex.Message.ToString());
            }
        }
        // 服务器应用程序消息回调函数定义
        void OnServerAppMessageCallBack_main(int msg, int userValue)
        {
            try
            {
                this.rtb_message.AppendText("服务器应用程序消息:OnServerAppMessage(" + "msg:" + msg.ToString() + ",userValue:" + userValue.ToString() + ")\n");
                if (msg == 1)
                {
                    //显示版本
                    string version = GetVersion();
                    lb_version.Text = "与SDK核心服务器连接成功";
                    lb_version.ForeColor = Color.Green;
                }
                else if (msg == 2)
                {
                    //清空在线用户列表中的项
                    lv_onlineUsers.Items.Clear();
                    lb_version.Text = "与SDK核心服务器断开连接";
                    lb_version.ForeColor = Color.Red;
                }
                Log.SetLog(lb_version.Text);

                rtb_message.Focus();
                rtb_message.SelectionStart = rtb_message.TextLength;
            }
            catch (Exception ex)
            {
                Log.SetLog("OnServerAppMessageCallBack         服务器应用程序消息" + ex.Message.ToString());
            }
        }

        // 用户登录成功回调函数
        void OnUserLoginAction_CallBack(int userId, string userName, int level, string addr, int userValue)
        {
            try
            {
                //加入用户对象集合
                UserInfo mode = new UserInfo();
                mode.Id = userId;
                mode.Name = userName;
                mode.Ip = addr;
                SendNowOnlineUsers(mode);//通知其他在线用户
                users.Add(mode);

                str = new string[] { userId.ToString(), userName, "游客", addr.ToString(), DateTime.Now.ToShortDateString() };
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
                EnterRoomInfoHandle(roomId);//房间分配处理(进入部分)
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
            try
            {
                OutRoomInfoHandle(roomId);//房间分配处理(离开部分)
                RemoveConversationInfoByUserId(userId, Promise.ICS_RETCODE_SESSION_SUCCESS);//离开会话，移除会话场次
                OnUserLeaveRoomAction_Received_main = new SystemSettingServer.OnUserLeaveRoomAction_Received(OnUserLeaveRoomActionCallBack_main);
                this.rtb_message.Invoke(OnUserLeaveRoomAction_Received_main, userId, roomId, userValue);
            }
            catch (Exception ex)
            {
                Log.SetLog("OnUserLeaveRoomActionCallBack          用户离开房间回调函数，错误：" + ex.Message.ToString());
            }
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
                //从会话场次中移除
                RemoveConversationInfoByUserId(userId, Promise.ICS_RETCODE_SESSION_OFFLINE);

                //从用户对象集中移除
                foreach (UserInfo u in users)
                {
                    if (u.Id == userId)
                    {
                        users.Remove(u);
                        break;
                    }
                }

                foreach (UserInfo u in users)
                {
                    //发送指令通知其他用户注销登录
                   TranBuff(u.Id, Promise.ICS_CMD_STATUSNOTIFY,
                        new ParamInfo(CommandHelp.ParamEnum.DATATYPE.ToString(), Promise.ICS_DATATYPE_ONLINEUSERS.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.OBJECTID.ToString(), userId.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.STATUS.ToString(), Promise.ICS_STATUSTYPE_USERONLINE.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.WPARAM.ToString(), Promise.ICS_STATUSTYPE_USERONLINE_FONLINE.ToString()));//用户离线
                }

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

        //透明通道回调函数
        public void TransBuffer_CallBack(int userId, IntPtr buf, int len, int userValue)
        {
            try
            {
                string str = Marshal.PtrToStringAnsi(buf);                                  //获取命令字符串
                int cmd = Convert.ToInt32(CommandHelp.ResolveCommand(str));        //解析命令字符串头部
                List<ParamInfo> os = CommandHelp.ResolveCommand(cmd, str);      //根据头部命令解析命令内容(得到参数)
                switch (cmd)
                {
                    //请求数据
                    case Promise.ICS_CMD_DATAREQUEST:
                        GetUsersData(userId, os);
                        break;
                    //请求会话
                    case Promise.ICS_CMD_SESSIONREQUEST:
                        UserCall(userId, os);
                        break;
                    //会话结束
                    case Promise.ICS_CMD_SESSIONFINISH:
                        EndCall(userId, os);
                        break;
                    //接受邀请(开始会话)
                    case Promise.ICS_CMD_SESSIONSTART:
                        StartConversation(userId);
                        break;
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatServer.Server.TransBuffer_CallBack       TransBuffer_CallBack：" + ex.Message.ToString());
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
                SystemSettingServer.OnUserLogoutActionExReceived = new SystemSettingServer.OnUserLogoutActionEx_Received(OnUserLogoutActionExCallBack);
                // 透明通道数据回调函数定义
                SystemSettingServer.OnTransBufferReceived = new SystemSettingServer.OnTransBuffer_Received(TransBuffer_CallBack);
                // 用户身份验证回调函数定义
                SystemSettingServer.OnVerifyUserReceived = new SystemSettingServer.OnVerifyUser_Received(OnVerifyUserCallBack);
                // 收到用户文字聊天通信数据回调函数定义
                SystemSettingServer.OnRecvUserTextMsgReceived = new SystemSettingServer.OnRecvUserTextMsg_Received(OnRecvUserTextMsgCallBack);
                //文件传输回调函数
                SystemSettingServer.OnTransFileReceived = new SystemSettingServer.OnTransFile_Received(OnTransFileCallBack);

                lb_version.Text = "与SDK核心服务器连接失败";
                lb_version.ForeColor = Color.Red;

                //初始化SDK
                SystemSettingServer.Init();
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

        #endregion

        #region 登录

        /// <summary>
        /// 登录成功时
        /// 向当前在线用户发送该用户的数据
        /// </summary>
        /// <param name="id"></param>
        private void SendNowOnlineUsers(UserInfo userMode)
        {
            try
            {
                foreach (UserInfo u in users)
                {
                    //向当前在线用户发送该用户的数据
                    TranBuff(u.Id, Promise.ICS_CMD_DATAITEM,
                        new ParamInfo(CommandHelp.ParamEnum.DATATYPE.ToString(), Promise.ICS_DATATYPE_ONLINEUSERS.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.DATA.ToString(), CommandHelp.GenerateMarkCommand(
                            new ParamInfo(CommandHelp.ParamEnum.DATA_USERID.ToString(), userMode.Id.ToString()),
                            new ParamInfo(CommandHelp.ParamEnum.DATA_USERIP.ToString(), userMode.Ip),
                            new ParamInfo(CommandHelp.ParamEnum.DATA_USERNAME.ToString(), userMode.Name)
                            )));
                    //发送指令通知其他用户该用户上线
                    TranBuff(u.Id, Promise.ICS_CMD_STATUSNOTIFY,
                        new ParamInfo(CommandHelp.ParamEnum.DATATYPE.ToString(), Promise.ICS_DATATYPE_ONLINEUSERS.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.OBJECTID.ToString(), userMode.Id.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.STATUS.ToString(), Promise.ICS_STATUSTYPE_USERONLINE.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.WPARAM.ToString(), Promise.ICS_STATUSTYPE_USERONLINE.ToString()));//用户上线
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("SendNowOnlineUsers             登录成功时：向当前在线用户发送该用户的数据;  发生错误：" + ex.Message.ToString());
            }
        }

        #endregion

        #region 呼叫

        //某用户申请呼叫
        private void UserCall(int userId, List<ParamInfo> os)
        {
            try
            {
                int tid = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.TUSERID.ToString()).Value);//目标用户ID
                bool isOnline = false;//是否在线

                foreach (UserInfo u in users)
                {
                    if (u.Id == tid)
                    {
                        isOnline = true;
                        bool isBusy = false;
                        foreach (ConversationInfo c in converstations)
                        {
                            if (c.SuserId == tid || c.TuserId == tid)//不在会话场景中
                            {
                                isBusy = true;
                                break;
                            }
                        }
                        if (isBusy)//用户正忙
                        {
                            TranBuff(userId, Promise.ICS_CMD_SESSIONFINISH,
                                new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), userId.ToString()),
                                new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), tid.ToString()),
                                new ParamInfo(CommandHelp.ParamEnum.RETCODE.ToString(), Promise.ICS_RETCODE_SESSION_BUSY.ToString()));//目标用户忙
                        }
                        else
                        {
                            //请求成功
                            ConversationInfo mode = new ConversationInfo();
                            mode.SuserId = userId;
                            mode.TuserId = tid;
                            converstations.Add(mode);
                            //通知被呼叫用户
                            TranBuff(tid, Promise.ICS_CMD_SESSIONREQUEST,
                                new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), userId.ToString()),
                                new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), tid.ToString()));

                            //请求回复-呼叫等待
                            TranBuff(userId, Promise.ICS_CMD_CONTROL,
        new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), userId.ToString()),
        new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), tid.ToString()),
        new ParamInfo(CommandHelp.ParamEnum.CTRLCODE.ToString(), Promise.ICS_CONTROL_SESSIONWAIT.ToString()),
        new ParamInfo(CommandHelp.ParamEnum.WPARAM.ToString(), tid.ToString()));
                        }
                        break;
                    }
                }
                if (!isOnline)
                {
                    TranBuff(userId, Promise.ICS_CMD_SESSIONFINISH,
                        new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), userId.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), tid.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.RETCODE.ToString(), Promise.ICS_RETCODE_SESSION_OFFLINE.ToString()));//目标用户不在线
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatServer.Server.UserCall       UserCall：" + ex.Message.ToString());
            }
        }

        /// <summary>
        /// 根据用户ID移除会话场次
        /// </summary>
        private void RemoveConversationInfoByUserId(int userid,int error)
        {
            try
            {
                foreach (ConversationInfo c in converstations)
                {
                    if (c.SuserId == userid || c.TuserId == userid)
                    {
                        //通知用户会话解散
                        TranBuff(c.SuserId, Promise.ICS_CMD_SESSIONFINISH,
                                    new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), c.SuserId.ToString()),
                                    new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), c.TuserId.ToString()),
                                    new ParamInfo(CommandHelp.ParamEnum.RETCODE.ToString(), error.ToString()));
                        TranBuff(c.TuserId, Promise.ICS_CMD_SESSIONFINISH,
                                    new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), c.SuserId.ToString()),
                                    new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), c.TuserId.ToString()),
                                    new ParamInfo(CommandHelp.ParamEnum.RETCODE.ToString(), error.ToString()));
                        converstations.Remove(c);
                        RemoveConversationInfoByUserId(userid, error);
                        break;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatServer.Server.RemoveConversationInfoByUserId       RemoveConversationInfoByUserId：" + ex.Message.ToString());
            }
        }

        //通话结束
        private void EndCall(int userId, List<ParamInfo> os)
        {
            try
            {
                int error = Convert.ToInt32(CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.RETCODE.ToString()).Value);
                RemoveConversationInfoByUserId(userId, error);
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatServer.Server.EndCall       EndCall：" + ex.Message.ToString());
            }
        }

        //接受邀请(开始会话)
        private void StartConversation(int userId)
        {
            try
            {
                bool isOnline = false;
                foreach (ConversationInfo c in converstations)
                {
                    if (c.SuserId == userId || c.TuserId == userId)
                    {
                        UserInfo smode = GetUserInfoById(c.SuserId);
                        UserInfo tmode = GetUserInfoById(c.TuserId);

                        if (smode != null && tmode != null)
                        {
                            isOnline = true;
                            int roomid = GetRoomId(1);

                            //通知双方用户开始会话
                            TranBuff(c.SuserId, Promise.ICS_CMD_SESSIONSTART,
                            new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), c.SuserId.ToString()),
                            new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), c.TuserId.ToString()),
                            new ParamInfo(CommandHelp.ParamEnum.ROOMID.ToString(), roomid.ToString()));
                            TranBuff(c.TuserId, Promise.ICS_CMD_SESSIONSTART,
                            new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), c.SuserId.ToString()),
                            new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), c.TuserId.ToString()),
                            new ParamInfo(CommandHelp.ParamEnum.ROOMID.ToString(), roomid.ToString()));

                            break;
                        }
                    }
                }
                if (!isOnline)
                {
                    RemoveConversationInfoByUserId(userId, Promise.ICS_RETCODE_SESSION_OFFLINE);
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChatServer.Server.StartConversation       StartConversation：" + ex.Message.ToString());
            }
        }

        #endregion

        #region 数据请求

        //请求数据
        public void GetUsersData(int sid, List<ParamInfo> os)
        {
            try
            {
                if (CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.DATATYPE.ToString()).Value == Promise.ICS_DATATYPE_ONLINEUSERS.ToString())//请求在线用户数据
                {
                    foreach (UserInfo u in users)
                    {
                        if (u.Id != sid)
                        {
                            TranBuff(sid, Promise.ICS_CMD_DATAITEM,
                        new ParamInfo(CommandHelp.ParamEnum.DATATYPE.ToString(), Promise.ICS_DATATYPE_ONLINEUSERS.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.DATA.ToString(), CommandHelp.GenerateMarkCommand(
                        new ParamInfo(CommandHelp.ParamEnum.DATA_USERID.ToString(), u.Id.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.DATA_USERIP.ToString(), u.Ip.ToString()),
                        new ParamInfo(CommandHelp.ParamEnum.DATA_USERNAME.ToString(), u.Name)
                        )));//向该用户发送当前在线用户的数据
                        }
                    }
                }

                TranBuff(sid, Promise.ICS_CMD_CONTROL,
                    new ParamInfo(CommandHelp.ParamEnum.SUSERID.ToString(), "0"),
                    new ParamInfo(CommandHelp.ParamEnum.TUSERID.ToString(), sid.ToString()),
                    new ParamInfo(CommandHelp.ParamEnum.CTRLCODE.ToString(), Promise.ICS_CONTROL_DATAFINISH.ToString()),
                    new ParamInfo(CommandHelp.ParamEnum.WPARAM.ToString(), CommandHelp.GetParamInfoByParams(os, CommandHelp.ParamEnum.DATATYPE.ToString()).Value));//回复结束指令
            }
            catch (Exception ex)
            {
                Log.SetLog("GetUsersData             请求用户数据（C-S），  发生错误：" + ex.Message.ToString());
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

        //分配房间
        private int GetRoomId(int roomid)
        {
            try
            {
                foreach (RoomInfo r in rooms)
                {
                    if (r.Id == roomid)
                    {
                        roomid++;
                        roomid = GetRoomId(roomid);
                        break;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("GetRoomId                      分配房间，错误：" + ex.Message.ToString());
            }
            return roomid;
        }
        //进入房间分配处理
        void EnterRoomInfoHandle(int roomId)
        {
            try
            {
                bool isHave = false;//房间是否已经被分配
                foreach (RoomInfo r in rooms)
                {
                    if (r.Id == roomId)
                    {
                        isHave = true;
                        r.Count++;
                        break;
                    }
                }
                if (!isHave)//房间未被分配
                {
                    RoomInfo room = new RoomInfo();
                    room.Id = roomId;
                    room.Count = 1;
                    rooms.Add(room);
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("EnterRoomInfoHandle                        进入房间分配处理，错误：" + ex.Message.ToString());
            }
        }
        //离开房间分配处理
        private void OutRoomInfoHandle(int roomId)
        {
            try
            {
                foreach (RoomInfo r in rooms)
                {
                    if (r.Id == roomId)
                    {
                        r.Count--;
                        if (r.Count == 0)
                        {
                            rooms.Remove(r);
                        }
                        break;
                    }
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("OutRoomInfoHandle                  离开房间分配处理，错误：" + ex.Message.ToString());
            }
        }

        #endregion
    }
}
