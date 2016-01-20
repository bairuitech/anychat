using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ANYCHATAPI;
using VideoChatHelp;
using System.Runtime.InteropServices;
using System.Xml;
using System.Threading;
using System.IO;

namespace VideoChatClient
{
    public partial class Login : Form
    {

        #region 构造函数

        public Login()
        {
            InitializeComponent();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
        }

        #endregion

        #region 定义

        public int m_userId = -1;//本地ID
        public string m_userName = "AnyChatDemo";//本地用户名

        Hall hallForm;//大厅

        string mPath = Application.StartupPath + "/record.xml";

        XmlDocument mXmlDoc = new XmlDocument();

        /// <summary>
        /// 应用ID
        /// </summary>
        public string m_appGuid = "";

        #endregion

        #region 初始化

        //加载窗体
        private void Login_Load(object sender, EventArgs e)
        {
            try
            {
                if (File.Exists(mPath))
                {
                    mXmlDoc.Load(mPath);
                    Thread rThr = new Thread(new ThreadStart(LoadRecordTrace));
                    rThr.Start();
                }
                else
                {
                    tb_serveradd.Text = "demo.anychat.cn";
                    tb_port.Text = "8906";
                }

                //初始化log日志文件
                if (File.Exists(Log.logPath))
                {
                    File.Delete(Log.logPath);
                }

                //初始化AnyChat
                SystemSetting.Init(this.Handle);
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Login.Login_Load       Login_Load：" + ex.Message.ToString());
            }
        }

        #endregion

        #region 登录

        //单击登录
        private void btn_login_Click(object sender, EventArgs e)
        {
            try
            {
                if (tb_name.Text != "")
                {
                    string addr = "";
                    int port = 8906;
                    try
                    {
                        addr = tb_serveradd.Text;
                        port = Convert.ToInt32(tb_port.Text);
                        m_userName = tb_name.Text;
                        m_appGuid = tb_appGuid.Text;
                    }
                    catch (Exception)
                    {
                        ShowMessage("配置有误");
                    }
                    if (hallForm != null && !hallForm.bReleased)
                    {
                        AnyChatCoreSDK.Logout();
                        AnyChatCoreSDK.Release();
                      
                    }
                    SystemSetting.Init(this.Handle);

                    if (!string.IsNullOrEmpty(m_appGuid))
                    {
                        AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_CLOUD_APPGUID, m_appGuid, m_appGuid.Length);
                    }
                    AnyChatCoreSDK.Connect(addr, port);
                }
                else
                    ShowMessage("用户名不能为空");
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Login.btn_login_Click       btn_login_Click：" + ex.Message.ToString());
            }
        }

        //提示消息
        private void ShowMessage(string str)
        {
            try
            {
                lb_message.Text = str;
                lb_message.Left = this.Width / 2 - lb_message.Width / 2;
                lb_message.Show();
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Login.ShowMessage       ShowMessage：" + ex.Message.ToString());
            }
        }

        //窗体关闭
        private void Login_FormClosed(object sender, FormClosedEventArgs e)
        {
            //try
            //{
            //    AnyChatCoreSDK.Logout();
            //    AnyChatCoreSDK.Release();
            //}
            //catch (Exception ex)
            //{
            //    Log.SetLog("VideoChat.Login.Login_FormClosed       Login_FormClosed：" + ex.Message.ToString());
            //}
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
                        //透明通道回调
                        SystemSetting.TransBuffer_OnReceive = new TransBufferReceivedHandler(TransBuffer_CallBack);
                        int ret = AnyChatCoreSDK.Login(m_userName, "123", 0);//登录系统
                        ShowMessage("连接AnyChat服务器成功,正在登录系统...");
                    }
                    else
                    {
                        ShowMessage("连接AnyChat服务器失败");
                        Log.SetLog("WM_GV_CONNECT      连接AnyChat服务器失败");
                    }
                
                
            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_LOGINSYSTEM)
            {
             
                    ///登录系统
                    if (m.LParam.ToInt32() == 0)
                    {
                        ShowMessage("登录AnyChat系统成功");
                        m_userId = m.WParam.ToInt32();//保存当前ID
                        RecordLoginTrace();
                        hallForm = null;
                        hallForm = new Hall(m_userId, tb_name.Text);
                        this.Hide();
                        hallForm.Show();
                    }
                    else
                    {
                        ShowMessage("登录失败：Error=" + m.LParam.ToString());
                        Log.SetLog("WM_GV_LOGINSYSTEM          登录失败：Error=" + m.LParam.ToString());
                    }
               
            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_ENTERROOM)
            {
            
                    //进入房间
                    int lparam = m.LParam.ToInt32();
                    if (lparam == 0)
                    {
                         hallForm.EnterRoomSuccess();//通知大厅进入房间成功
                    }
                    else
                    {
                        Log.SetLog("WM_GV_ENTERROOM                进入房间，失败，Error：" + lparam.ToString());
                    }
              
            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_ONLINEUSER)
            {

                     hallForm.OpenCameraAndSpeak(hallForm.getOtherInSession(),true);//打开视频呼叫对象的视频

            
            }
            //用户进入或者离开房间
            else if (m.Msg == AnyChatCoreSDK.WM_GV_USERATROOM)
            {
              
                    int lparam = m.LParam.ToInt32();
                    int wparam = m.WParam.ToInt32();
                    if (lparam == 0)
                    {
                        hallForm.OpenCameraAndSpeak(hallForm.getOtherInSession(),false);//关闭视频呼叫对象的视频
                        Log.SetLog("WM_GV_USERATROOM           用户" + wparam.ToString() + "离开房间");
                    }
                    else
                    {
                        hallForm.OpenCameraAndSpeak(hallForm.getOtherInSession(), true);//打开视频呼叫对象的视频
                        Log.SetLog("WM_GV_USERATROOM           用户" + wparam.ToString() + "进入房间");
                    }
                
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
                    ShowMessage("网络断开，ErrorCode：" + wparam.ToString());
                    hallForm.Hide();
                    this.Show();
                    Log.SetLog("WM_GV_LINKCLOSE            响应网络断开,errorcode:=" + lparam );
            }
            //好友用户在线状态变化
            else if (m.Msg == AnyChatCoreSDK.WM_GV_FRIENDSTATUS)
            {
                int userId = m.WParam.ToInt32();
                int onlineStatus = m.LParam.ToInt32();
                hallForm.OnUserOnlineStatusChange(userId, onlineStatus);
                string strOnlineStatus=onlineStatus>=1? "上线":"下线";
                Log.SetLog("WM_GV_FRIENDSTATUS:  useId: " + userId + "onlineStatus:  " + strOnlineStatus);
            }
            //好友数据更新变化通知
            else if (m.Msg == AnyChatCoreSDK.WM_GV_USERINFOUPDATE)
            {
                int userId=m.WParam.ToInt32();
                int type=m.LParam.ToInt32();
                if(userId==0&&type==0)
                {
                    hallForm.getOnlineFriendInfos();

                }
                Log.SetLog("WM_GV_FRIENDSTATUS:  useId: " + userId + "type:  " + type);
            }
            base.WndProc(ref m);
        }

        #endregion

        #region 透明通道(指令相关)

        //透明通道回调函数
        public void TransBuffer_CallBack(int userId, IntPtr buf, int len, int userValue)
        {
            try
            {
                if (hallForm != null)
                    hallForm.TransBuffer_CallBack(userId, buf, len, userValue);
            }
            catch (Exception ex)
            {
                Log.SetLog("VideoChat.Login.TransBuffer_CallBack       TransBuffer_CallBack：" + ex.Message.ToString());
            }
        }

        #endregion

        /// <summary>
        /// 保存登录信息
        /// </summary>
        private void RecordLoginTrace()
        {
            try
            {
                if (!File.Exists(mPath))
                {
                    CreateXMLDoc();
                    mXmlDoc.Load(mPath);
                }
                RecordValue("ipList", "ip", tb_serveradd.Text);
                RecordValue("portList", "port", tb_port.Text);
                RecordValue("userNameList", "userName", tb_name.Text);
                RecordValue("appGuidList", "appGuid", tb_appGuid.Text);
                PreviousRecordValue("previousrecord", "ip", tb_serveradd.Text);
                PreviousRecordValue("previousrecord", "port", tb_port.Text);
                PreviousRecordValue("previousrecord", "userName", tb_name.Text);
                PreviousRecordValue("previousrecord", "appGuid", tb_appGuid.Text);
                
              
            }
            catch (Exception ex)
            {
            }
        }
        private void RecordValue(string rAttribute, string rN, string rValue)
        {
            XmlNode rMainNode = mXmlDoc.SelectSingleNode("settings");
            XmlNode rNode = rMainNode.SelectSingleNode(rAttribute);
            XmlNodeList rList = rNode.ChildNodes;
            int i = 0;
            foreach (XmlNode x in rList)
            {
                XmlElement rElem = (XmlElement)x;
                string rVal = rElem.GetAttribute("value");
                switch (rAttribute)
                {
                    case "ipList":
                        if (rVal == tb_serveradd.Text)
                            i = 1;
                        break;
                    case "portList":
                        if (rVal == tb_port.Text)
                            i = 1;
                        break;
                    case "userNameList":
                        if (rVal == tb_name.Text)
                            i = 1;
                        break;
                    case "appGuidList":
                        if (rVal == tb_appGuid.Text)
                            i = 1;
                        break;
                }
                if (i == 1) break;
            }
            if (i == 0)
            {
                rNode = rMainNode.SelectSingleNode(rAttribute);
                XmlElement rElement = mXmlDoc.CreateElement(rN);
                rElement.SetAttribute("value", rValue);
                rNode.AppendChild(rElement);
                mXmlDoc.Save(mPath);
            }
        }
        private void PreviousRecordValue(string rAttribute, string rN, string rValue)
        {
            XmlNode rMainNode = mXmlDoc.SelectSingleNode("settings");
            XmlNode rNode = rMainNode.SelectSingleNode(rAttribute);
            XmlNodeList rList = rNode.ChildNodes;
            bool bExists=false;
            XmlElement rElem=null;
            foreach (XmlNode x in rList)
            {
                rElem = (XmlElement)x;
                string rVal = rElem.GetAttribute("value");
                if (rElem.Name.Equals(rN))
                {
                    bExists=true;
                    break;
                }
            }
            if (bExists && rElem!=null)
            {

                rElem.SetAttribute("value", rValue);
            }
            else
            {
                XmlElement rElement = mXmlDoc.CreateElement(rN);
                rElement.SetAttribute("value", rValue);
                rNode.AppendChild(rElement);
            }
           
            mXmlDoc.Save(mPath); 
        }


        private int ValueExists(string rAttribute)
        {
            XmlNode rMainNode = mXmlDoc.SelectSingleNode("settings");

            XmlNode rNode = rMainNode.SelectSingleNode(rAttribute);
            XmlNodeList rList = rNode.ChildNodes;
            return rList.Count;
        }

        private void LoadRecordTrace()
        {

            DisplayVal(tb_serveradd, "ipList");
            DisplayVal(tb_port, "portList");
            DisplayVal(tb_name, "userNameList");
            DisplayVal(tb_appGuid, "appGuidList");
            string[] record = getPreviousRecord("previousrecord");
            if (record != null)
            {
                tb_serveradd.Text = record[0];
                tb_port.Text = record[1];
                tb_name.Text = record[2];
                tb_appGuid.Text = record[3];
            }
            

        }
        private String[] getPreviousRecord(string rAttribute)
        {
            string[] record = new string[4];
            XmlNode rMainNode = mXmlDoc.SelectSingleNode("settings");
            XmlNode rNode = rMainNode.SelectSingleNode(rAttribute);
            XmlNodeList rList = rNode.ChildNodes;
            bool bExists = false;
            XmlElement rElem = null;
            foreach (XmlNode x in rList)
            {
                bExists = true;
                rElem = (XmlElement)x;
                string rVal = rElem.GetAttribute("value");
                switch (rElem.Name)
                {
                    case "ip":
                        record[0] = rVal;
                        break;
                    case "port":
                        record[1] = rVal;
                        break;
                    case "userName":
                        record[2] = rVal;
                        break;
                    case "appGuid":
                        record[3] = rVal;
                        break;
                }
            }
            if (bExists)
                return record;
            return null;
        }

        private void DisplayVal(ComboBox rCBB,string rAttribute)
        {
            XmlNode rMainNode = mXmlDoc.SelectSingleNode("settings");

            XmlNode rNode = rMainNode.SelectSingleNode(rAttribute);
            XmlNodeList rList = rNode.ChildNodes;
            foreach (XmlNode r in rList)
            {
                XmlElement rElem = (XmlElement)r;
                rCBB.Items.Add(rElem.GetAttribute("value"));
            }

            if (rCBB.Items.Count > 0)
                rCBB.SelectedIndex = 0;
        }

        /// <summary>
        /// 配置文件缺失时自动生成文件
        /// </summary>
        public void CreateXMLDoc()
        {
            if (!File.Exists(mPath))
            {
                XmlDocument xmldoc = new XmlDocument();
                //加入XML的声明段落
                xmldoc.AppendChild(xmldoc.CreateXmlDeclaration("1.0", "UTF-8", null));
                XmlElement rMainNode = xmldoc.CreateElement("", "settings", "");
                rMainNode.IsEmpty = false;
                xmldoc.AppendChild(rMainNode);

                XmlElement rIp = xmldoc.CreateElement("", "ipList", "");
                rIp.IsEmpty = false;
                rMainNode.AppendChild(rIp);

                XmlElement rPort = xmldoc.CreateElement("", "portList", "");
                rPort.IsEmpty = false;
                rMainNode.AppendChild(rPort);

                XmlElement rName = xmldoc.CreateElement("", "userNameList", "");
                rName.IsEmpty = false;
                rMainNode.AppendChild(rName);

                XmlElement rAppGuid = xmldoc.CreateElement("", "appGuidList", "");
                rAppGuid.IsEmpty = false;
                rMainNode.AppendChild(rAppGuid);

                XmlElement rPreviousRecord = xmldoc.CreateElement("", "previousrecord", "");
                rPreviousRecord.IsEmpty = false;
                rMainNode.AppendChild(rPreviousRecord);

                xmldoc.Save(mPath);
            }
        }
    }
}
