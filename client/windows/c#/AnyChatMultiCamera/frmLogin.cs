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

        frmRoom2 RoomForm;   //进入房间

        string mPath = Application.StartupPath + "/record.xml";

        XmlDocument mXmlDoc = new XmlDocument();

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
                RecordValue("ip", "ip", cbox_serverIP.Text);
                RecordValue("port", "port", cbox_port.Text);
                RecordValue("userName", "userName", cbox_userName.Text);
                RecordValue("roomNumber", "roomNumber", cbox_roomNumber.Text);
                //RecordValue("userIdentity", "userIdentity", cbox_userIdentity.SelectedIndex.ToString());
                //RecordValue("identityPriority", "identityPriority", cbox_identityPriority.SelectedIndex.ToString());

                PreviousRecordValue("previousreocrd", "ip", cbox_serverIP.Text);
                PreviousRecordValue("previousreocrd", "port", cbox_port.Text);
                PreviousRecordValue("previousreocrd", "userName", cbox_userName.Text);
                PreviousRecordValue("previousreocrd", "roomNumber", cbox_roomNumber.Text);
                              
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
                    case "ip":
                        if (rVal == cbox_serverIP.Text)
                            i = 1;
                        break;
                    case "port":
                        if (rVal == cbox_port.Text)
                            i = 1;
                        break;
                    case "userName":
                        if (rVal == cbox_userName.Text)
                            i = 1;
                        break;
                    case "roomNumber":
                        if (rVal == cbox_roomNumber.Text)
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

            DisplayVal(cbox_serverIP, "ip");
            DisplayVal(cbox_port, "port");
            DisplayVal(cbox_userName, "userName");
            DisplayVal(cbox_roomNumber, "roomNumber");

            string[] record = getPreviousRecord("previousreocrd");
            if (record != null)
            {
                cbox_serverIP.Text = record[0];
                cbox_port.Text = record[1];
                cbox_userName.Text = record[2];
                cbox_roomNumber.Text = record[3];
            }
          
        }
        private String[] getPreviousRecord(string rAttribute)
        {
            string[] record = new string[5];
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

                XmlElement rIp = xmldoc.CreateElement("", "ip", "");
                rIp.IsEmpty = false;
                rMainNode.AppendChild(rIp);

                XmlElement rPort = xmldoc.CreateElement("", "port", "");
                rPort.IsEmpty = false;
                rMainNode.AppendChild(rPort);

                XmlElement rUserName = xmldoc.CreateElement("", "userName", "");
                rUserName.IsEmpty = false;
                rMainNode.AppendChild(rUserName);

                XmlElement rRoomNumber = xmldoc.CreateElement("", "roomNumber", "");
                rRoomNumber.IsEmpty = false;
                rMainNode.AppendChild(rRoomNumber);

                //XmlElement rIdentityPriority = xmldoc.CreateElement("", "identityPriority", "");
                //rUserIdentity.IsEmpty = false;
                //rMainNode.AppendChild(rIdentityPriority);

                XmlElement rPreviousRecord = xmldoc.CreateElement("", "previousreocrd", "");
                rPreviousRecord.IsEmpty = false;
                rMainNode.AppendChild(rPreviousRecord);

                xmldoc.Save(mPath);
            }
        }

        #endregion
    }
}
