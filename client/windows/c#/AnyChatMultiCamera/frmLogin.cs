using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ANYCHATAPI;
using System.Runtime.InteropServices;
using System.Xml;
using System.Threading;
using System.IO;

namespace AnyChatMultiCamera
{
    public partial class frmLogin : Form
    {

        #region 构造函数

        public frmLogin()
        {
            InitializeComponent();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
        }

        #endregion

        #region 定义

        /// <summary>
        /// 本地用户ID
        /// </summary>
        public int m_userId = -1;
        /// <summary>
        /// 本地用户名
        /// </summary>
        public string m_userName = "AnyChatDemo";
        /// <summary>
        /// 用户密码
        /// </summary>
        public string m_userPassword = string.Empty;
        /// <summary>
        /// 房间号
        /// </summary>
        private int m_roomNumber;
        /// <summary>
        /// 应用ID
        /// </summary>
        private string m_appGuid;

        frmRoom2 RoomForm;   //进入房间

        string mPath = Application.StartupPath + "/record.xml";

        XmlDocument mXmlDoc = new XmlDocument();

        /// <summary>
        /// 签名Url
        /// </summary>
        public string signUrl = string.Empty;

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
                    cbox_serverIP.Text = "demo.anychat.cn";
                    cbox_port.Text = "8906";
                    cbox_roomNumber.SelectedIndex = 5;
                }

                //初始化log日志文件
                if (File.Exists(Log.logPath))
                {
                    File.Delete(Log.logPath);
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("AnyChatMultiCamera.Login.Login_Load       Login_Load：" + ex.Message.ToString());
            }
        }

        #endregion

        #region 登录及界面操作

        //单击登录
        private void btn_login_Click(object sender, EventArgs e)
        {
            try
            {
                if (cbox_userName.Text != "")
                {
                    string addr = "";
                    int port = 8906;
                    try
                    {
                        addr = cbox_serverIP.Text;
                        port = Convert.ToInt32(cbox_port.Text);

                        m_userName = cbox_userName.Text;
                        m_userPassword = txt_password.Text;
                        m_roomNumber = Int32.Parse(cbox_roomNumber.Text);
                        m_appGuid = cbox_appGuid.Text;
                    }
                    catch (Exception)
                    {
                        ShowMessage("输入的登录设置项有误，请检查！");
                    }

                    if (RoomForm != null && !RoomForm.bReleased)
                    {
                        AnyChatCoreSDK.Logout();
                        AnyChatCoreSDK.Release();
                    }

                    RecordLoginTrace();

                    ConnectInfo connInfo = new ConnectInfo();
                    connInfo.ServerIP = addr;
                    connInfo.Port = port;
                    connInfo.UserName = m_userName;
                    connInfo.UserPassword = m_userPassword;
                    connInfo.RoomID = m_roomNumber;
                    connInfo.isOpenRemoteDesktop = checkBox_RemoteDesktop.Checked;
                    connInfo.AppGuid = m_appGuid;
                    if (rbtn_normal.Checked)
                        connInfo.loginType = LoginType.Normal;
                    if (rbtn_sign.Checked)
                        connInfo.loginType = LoginType.Sign;
                    connInfo.signServerUrl = signUrl;

                    RoomForm = null;
                    //hallForm = new Hall(m_userId, cbox_userIdentity.Text);
                    RoomForm = new frmRoom2(connInfo, this);
                    RoomForm.Show();

                    this.Hide();

                    //if (RoomForm != null && !RoomForm.bReleased)
                    //{
                    //    AnyChatCoreSDK.Logout();
                    //    AnyChatCoreSDK.Release();
                      
                    //}
                    //SystemSetting.Init(this.Handle);
                    //AnyChatCoreSDK.Connect(addr, port);
                }
                else
                    ShowMessage("用户名不能为空");
            }
            catch (Exception ex)
            {
                Log.SetLog("AnyChatMultiCamera.Login.btn_login_Click       btn_login_Click：" + ex.Message.ToString());
                ShowMessage(ex.Message.ToString());
            }
        }

        //提示消息
        private void ShowMessage(string str)
        {
            try
            {
                lbl_tipMessage.Text = str;
                lbl_tipMessage.Left = this.Width / 2 - lbl_tipMessage.Width / 2;
                lbl_tipMessage.Show();
            }
            catch (Exception ex)
            {
                Log.SetLog("AnyChatMultiCamera.Login.ShowMessage       ShowMessage：" + ex.Message.ToString());
            }
        }

        //窗体关闭
        private void Login_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                AnyChatCoreSDK.Logout();
                AnyChatCoreSDK.Release();
            }
            catch (Exception ex)
            {
                Log.SetLog("AnyChatMultiCamera.Login.Login_FormClosed       Login_FormClosed：" + ex.Message.ToString());
            }
        }

        private void frmLogin_VisibleChanged(object sender, EventArgs e)
        {
            if (this.Visible)
                lbl_tipMessage.Text = string.Empty;
        }

        #endregion

        #region 登录信息保存处理

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
                RecordValue("ipList", "ip", cbox_serverIP.Text);
                RecordValue("portList", "port", cbox_port.Text);
                RecordValue("userNameList", "userName", cbox_userName.Text);
                //RecordValue("roomNumberList", "roomNumber", cbox_roomNumber.Text);
                RecordValue("appGuidList", "appGuid", cbox_appGuid.Text);

                PreviousRecordValue("previousrecord", "ip", cbox_serverIP.Text);
                PreviousRecordValue("previousrecord", "port", cbox_port.Text);
                PreviousRecordValue("previousrecord", "userName", cbox_userName.Text);
                PreviousRecordValue("previousrecord", "roomNumber", cbox_roomNumber.Text);
                PreviousRecordValue("previousrecord", "appGuid", cbox_appGuid.Text);

                if (String.IsNullOrEmpty(signUrl))
                {
                    PreviousRecordValue("previousrecord", "signUrl", signUrl);
                }   
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
                        if (rVal == cbox_serverIP.Text)
                            i = 1;
                        break;
                    case "portList":
                        if (rVal == cbox_port.Text)
                            i = 1;
                        break;
                    case "userNameList":
                        if (rVal == cbox_userName.Text)
                            i = 1;
                        break;
                    case "roomNumberList":
                        if (rVal == cbox_roomNumber.Text)
                            i = 1;
                        break;
                    case "appGuidList":
                        if (rVal == cbox_appGuid.Text)
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

            DisplayVal(cbox_serverIP, "ipList");
            DisplayVal(cbox_port, "portList");
            DisplayVal(cbox_userName, "userNameList");
            //DisplayVal(cbox_roomNumber, "roomNumberList");
            DisplayVal(cbox_appGuid, "appGuidList");

            string[] record = getPreviousRecord("previousrecord");
            if (record != null)
            {
                cbox_serverIP.Text = record[0];
                cbox_port.Text = record[1];
                cbox_userName.Text = record[2];
                cbox_roomNumber.Text = record[3];
                cbox_appGuid.Text = record[4];
                signUrl = record[5];
            }
          
        }
        private String[] getPreviousRecord(string rAttribute)
        {
            string[] record = new string[6];
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
                    case "roomNumber":
                        record[3] = rVal;
                        break;
                    case "appGuid":
                        record[4] = rVal;
                        break;
                    case "signUrl":
                        record[5] = rVal;
                        break;
                }
            }
            if (bExists)
                return record;
            return null;
        }

        private void DisplayVal(Control controlCompenent,string rAttribute)
        {
            XmlNode rMainNode = mXmlDoc.SelectSingleNode("settings");

            XmlNode rNode = rMainNode.SelectSingleNode(rAttribute);
            XmlNodeList rList = rNode.ChildNodes;
            foreach (XmlNode r in rList)
            {
                XmlElement rElem = (XmlElement)r;
                if (controlCompenent is ComboBox)
                {
                    ((ComboBox)controlCompenent).Items.Add(rElem.GetAttribute("value"));

                    //if (String.IsNullOrEmpty(rElem.GetAttribute("value")))
                    //    ((ComboBox)controlCompenent).SelectedIndex = 0;
                    //else
                    //    ((ComboBox)controlCompenent).SelectedIndex = Int32.Parse(rElem.GetAttribute("value"));
                }
                else
                {
                    if (controlCompenent is TextBox)
                    {
                        ((TextBox)controlCompenent).Text = rElem.GetAttribute("value");
                    }
                }

            }

            if ((controlCompenent is ComboBox) && (((ComboBox)controlCompenent).Items.Count > 0))
                ((ComboBox)controlCompenent).SelectedIndex = 0;
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

                XmlElement rUserName = xmldoc.CreateElement("", "userNameList", "");
                rUserName.IsEmpty = false;
                rMainNode.AppendChild(rUserName);

                //XmlElement rRoomNumber = xmldoc.CreateElement("", "roomNumberList", "");
                //rRoomNumber.IsEmpty = false;
                //rMainNode.AppendChild(rRoomNumber);

                XmlElement rAppGuid = xmldoc.CreateElement("", "appGuidList", "");
                rAppGuid.IsEmpty = false;
                rMainNode.AppendChild(rAppGuid);

                //XmlElement rIdentityPriority = xmldoc.CreateElement("", "identityPriority", "");
                //rUserIdentity.IsEmpty = false;
                //rMainNode.AppendChild(rIdentityPriority);

                XmlElement rPreviousRecord = xmldoc.CreateElement("", "previousrecord", "");
                rPreviousRecord.IsEmpty = false;
                rMainNode.AppendChild(rPreviousRecord);

                xmldoc.Save(mPath);
            }
        }

        #endregion

        private void rbtn_sign_Click(object sender, EventArgs e)
        {
            if (cbox_serverIP.Text.ToLower().Equals("demo.anychat.cn") && rbtn_sign.Checked)
            {
                cbox_port.Text = "8912";
            }
        }

        private void rbtn_normal_CheckedChanged(object sender, EventArgs e)
        {
            if (cbox_serverIP.Text.ToLower().Equals("demo.anychat.cn") && rbtn_normal.Checked)
            {
                cbox_port.Text = "8906";
            }
        }
    }
}
