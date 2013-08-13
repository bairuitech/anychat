using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ANYCHATAPI;
namespace WinProc
{
    public partial class FrmP2P : Form
    {
        public FrmP2P()
        {
            InitializeComponent();
        }
        private int m_RoomID = 1;
        private int m_myUserID = -1;
        private int m_tempUserID = -1;
        private bool videoOpenTag = false;

        private List<int> m_others = new List<int>();
        void InitChat()
        {

            string path = Application.StartupPath;
            SystemSetting.Text_OnReceive = new TextReceivedHandler(Received_Text);
            SystemSetting.TransFile_Received = new TransFileReceivedHandler(Received_TransFile);
            AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_CORESDK_PATH, path, path.Length);
            SystemSetting.Init(this.Handle);

            int ret = AnyChatCoreSDK.Connect("demo.anychat.cn", 8906);

            ret=AnyChatCoreSDK.Login("user2", "", 0);
        }

        void Print(string msg)
        {
            TbxAccept.Text += msg+"\r\n";
            TbxAccept.ScrollToCaret();
        }
        protected override void WndProc(ref Message m)
        {

            if (m.Msg == ANYCHATAPI.AnyChatCoreSDK.WM_GV_CONNECT)
            {
                ///连接
                int succed=m.WParam.ToInt32();
                if (succed == 1)
                {
                    Print("连接成功!");
                }
                else
                {
                    Print("连接失败,错误号:"+m.LParam.ToInt32());
                }
            }
            else if (m.Msg == ANYCHATAPI.AnyChatCoreSDK.WM_GV_LOGINSYSTEM)
            {
                ///登录系统
                int userid=m.WParam.ToInt32();
                if (m.LParam.ToInt32() == 0)
                {
                     Print("登录服务器成功，自己的用户编号为：" + userid.ToString());
                    m_myUserID = userid;
                    StringBuilder userName = new StringBuilder(30);

                    int ret = AnyChatCoreSDK.GetUserName(userid, userName, 30);
                   
                    AnyChatCoreSDK.EnterRoom(m_RoomID, "", 0);
                }
                else
                {
                    Print("登录服务器失败，代码出错为：" + m.LParam.ToInt32());
                }
            }
            else if (m.Msg == ANYCHATAPI.AnyChatCoreSDK.WM_GV_ENTERROOM)
            {
                ///进入房间
                if (m.LParam.ToInt32() == 0)
                {
                    int roomid = m.WParam.ToInt32();
                    Print("进入房间成功,房间编号为：" + roomid.ToString());
                    m_RoomID = roomid;
                    int ret = ANYCHATAPI.AnyChatCoreSDK.SetVideoPos(-1, pictureBox2.Handle, 0, 0, pictureBox2.Width, pictureBox2.Height);
                    ret = ANYCHATAPI.AnyChatCoreSDK.UserCameraControl(-1, true);
                    ret = ANYCHATAPI.AnyChatCoreSDK.UserSpeakControl(-1, true);
                }
                else
                {
                    Print("申请进入房间失败，出错代码为：" + m.LParam.ToInt32());
                }
            }
            else if (m.Msg == ANYCHATAPI.AnyChatCoreSDK.WM_GV_ONLINEUSER)
            {
                ///目前在房间的用户列表
                int usrcnt=m.WParam.ToInt32();
                Print("在编号为：" + m.LParam.ToInt32() + " 的房间共有" + usrcnt + "位在线用户");
                int cnt = 0;

                ANYCHATAPI.AnyChatCoreSDK.GetOnlineUser(null, ref cnt);

                int [] userArr=new int[cnt];
                ANYCHATAPI.AnyChatCoreSDK.GetOnlineUser(userArr, ref cnt);

                if (userArr.Length >= 1 && !videoOpenTag)
                {
                    m_tempUserID = userArr[0];
                    int ret = ANYCHATAPI.AnyChatCoreSDK.SetVideoPos(userArr[0], 
                        pictureBox1.Handle, 0, 0, 
                        pictureBox1.Width, pictureBox1.Height);
                    ret = ANYCHATAPI.AnyChatCoreSDK.UserCameraControl(userArr[0], true);
                    ret = ANYCHATAPI.AnyChatCoreSDK.UserSpeakControl(userArr[0], true);
                    if (ret == 0)
                    {
                        videoOpenTag = true;
                    }
                }
            }
            else if (m.Msg == ANYCHATAPI.AnyChatCoreSDK.WM_GV_USERATROOM)
            {
                ///新用户加入或退出房间
                int userID = m.WParam.ToInt32();
                int boEntered = m.LParam.ToInt32();
                
                if (boEntered == 1 && !videoOpenTag)
                {
                    int ret = -1;
                    m_others.Add(userID);
                    Print("用户编号为：" + userID + " 进入房间");
                    m_tempUserID = userID;
                    ret = AnyChatCoreSDK.SetVideoPos(userID, this.pictureBox1.Handle, 0, 0, pictureBox1.Width, pictureBox1.Height);
                    ret = AnyChatCoreSDK.UserCameraControl(userID, true);
                    ret = AnyChatCoreSDK.UserSpeakControl(userID, true);
                    if (ret == 0)
                    {
                        videoOpenTag = true;
                    }
                }
                else
                {
                    m_others.Remove(userID);
                    Print("用户编号为：" + userID + " 离开房间");
                }
            }
            
            base.WndProc(ref m);
        }

        private void BtnSend_Click(object sender, EventArgs e)
        {
            if (TbxSend.Text.Trim() == "")
            {
                MessageBox.Show("发送的消息内容不可以为空！");
            }
            else
            {
                string message=TbxSend.Text;
                int length = UnicodeEncoding.Default.GetBytes(message).Length;
                int ret= AnyChatCoreSDK.SendTextMessage(-1, false, message, length);
            }

            Print("我说:" + TbxSend.Text);
            TbxSend.Text = "";
        }


        void Received_Text(int fromUID,int toUID,string Text,bool isserect)
        {
            Print(string.Format("用户：{0},发送给{1}:\t{2}", new string[3] { ""+fromUID, ""+toUID, Text }));
        }
        protected override void OnClosed(EventArgs e)
        {
            SystemSetting.Release(m_RoomID);
            base.OnClosed(e);
        }
        private void FrmP2P_Load(object sender, EventArgs e)
        {
            InitChat();
        }

        //文件接收回调
        void Received_TransFile(int userId, string fileName, string filePath, int fileLength, int wParam, int lParam, int taskId, int userValue)
        {
            Print("成功接收用户" + userId.ToString() + "的文件" + filePath);
        }

        //发送文件
        private void btnSendFile_Click(object sender, EventArgs e)
        {
            if (m_tempUserID == -1)
            {
                Print("没有目标用户");
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
                        int taskId = -1;
                        if (AnyChatCoreSDK.TransFile(m_tempUserID, dlgopenFile.FileName, 1, 0, 0, ref taskId) == 0)
                        {
                            Print("文件" + dlgopenFile.FileName + "发送成功");
                        }
                    }
                }
                dlgopenFile.Dispose();
                dlgopenFile = null;
            }
        }

    }
}
