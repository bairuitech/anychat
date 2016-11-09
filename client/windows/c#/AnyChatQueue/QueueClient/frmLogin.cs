using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ANYCHATAPI;
using QueueHelp;
using System.Runtime.InteropServices;
using System.Xml;
using System.Threading;
using System.IO;
using System.Net;
using System.Runtime.Serialization;
//using System.Runtime.Serialization.Json;


namespace QueueClient
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

        frmHall hallForm;//大厅

        string mPath = Application.StartupPath + "/record.xml";

        XmlDocument mXmlDoc = new XmlDocument();

        /// <summary>
        /// 用户身份标识
        /// </summary>
        public UserIdentityType m_userIdentity = UserIdentityType.Client;
        /// <summary>
        /// 身份优先级
        /// </summary>
        public int m_identityPriority = 10;
        /// <summary>
        /// 应用ID
        /// </summary>
        public string m_appGuid = "";

        /// <summary>
        /// 签名Url
        /// </summary>
        public string signUrl = string.Empty;

        /// <summary>
        /// 自动路由标识
        /// </summary>
        public bool m_isAutoRouter = true;

        /// <summary>
        /// 技能值，默认三个技能相加（1 + 2 + 4）
        /// </summary>
        public int m_skillsValue = 7;

        #endregion

        #region 初始化

        //加载窗体
        private void Login_Load(object sender, EventArgs e)
        {
            try
            {
                cmbBox_Router.SelectedIndex = 1;
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

                    cbox_userIdentity.SelectedIndex = 0;
                    cbox_identityPriority.SelectedIndex = 5;
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
                Log.SetLog("QueueClient.Login.Login_Load       Login_Load：" + ex.Message.ToString());
            }
        }

        #endregion

        #region 登录及界面操作

        //单击登录
        private void btn_login_Click(object sender, EventArgs e)
        {
            try
            {
                if (cbox_userIdentity.Text != "")
                {
                    string addr = "";
                    int port = 8906;
                    try
                    {
                        addr = cbox_serverIP.Text;
                        port = Convert.ToInt32(cbox_port.Text);
                        m_userName = cbox_userName.Text;
                        m_userIdentity = (UserIdentityType)cbox_userIdentity.SelectedIndex;
                        m_identityPriority = Int32.Parse(cbox_identityPriority.Text);
                        if (m_userIdentity == UserIdentityType.Agent)
                        {
                            if (cmbBox_Router.SelectedIndex == 1)
                            {
                                m_isAutoRouter = true;
                            }
                            else
                            {
                                m_isAutoRouter = false;
                            }
                            
                        }
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

                    /* AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
                     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
                     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
                     */
                    AnyChatCoreSDK.Connect(addr, port);

                    /*
                     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，
                     * 详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
                     */
                    int ret = AnyChatCoreSDK.Login(m_userName, "123", 0);//登录系统

                    RecordLoginTrace();

                }
                else
                    ShowMessage("用户名不能为空");
            }
            catch (Exception ex)
            {
                Log.SetLog("QueueClient.Login.btn_login_Click       btn_login_Click：" + ex.Message.ToString());
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
                Log.SetLog("QueueClient.Login.ShowMessage       ShowMessage：" + ex.Message.ToString());
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
                Log.SetLog("QueueClient.Login.Login_FormClosed       Login_FormClosed：" + ex.Message.ToString());
            }
        }

        private void frmLogin_VisibleChanged(object sender, EventArgs e)
        {
            if (this.Visible)
                lbl_tipMessage.Text = string.Empty;
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
                        hallForm = null;
                        //hallForm = new Hall(m_userId, cbox_userIdentity.Text);
                        LoginInfo loginInfo = new LoginInfo();
                        loginInfo.userID = m_userId;
                        loginInfo.userName = m_userName;
                        loginInfo.userIdType = m_userIdentity;
                        loginInfo.userPriority = m_identityPriority;
                        loginInfo.isRouterMode = m_isAutoRouter;
                        loginInfo.userSkills = m_skillsValue;

                        hallForm = new frmHall(loginInfo, this);
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
                    if (hallForm != null)
                        hallForm.Hide();
                    this.Show();
                    Log.SetLog("WM_GV_LINKCLOSE            响应网络断开,errorcode:=" + lparam );
            }
            base.WndProc(ref m);
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
                //RecordValue("userIdentity", "userIdentity", cbox_userIdentity.SelectedIndex.ToString());
                //RecordValue("identityPriority", "identityPriority", cbox_identityPriority.SelectedIndex.ToString());

                PreviousRecordValue("previousrecord", "ip", cbox_serverIP.Text);
                PreviousRecordValue("previousrecord", "port", cbox_port.Text);
                PreviousRecordValue("previousrecord", "userName", cbox_userName.Text);                
                PreviousRecordValue("previousrecord", "userIdentity", cbox_userIdentity.Text);
                PreviousRecordValue("previousrecord", "identityPriority", cbox_identityPriority.Text);

                if (String.IsNullOrEmpty(signUrl))
                {
                    PreviousRecordValue("previousrecord", "signUrl", signUrl);
                }
            }
            catch (Exception ex)
            {
                Log.SetLog("QueueClient.Login.RecordLoginTrace       RecordLoginTrace：" + ex.Message.ToString());
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
            //DisplayVal(cbox_userIdentity, "userIdentity");
            //DisplayVal(cbox_identityPriority, "identityPriority");

            string[] record = getPreviousRecord("previousrecord");
            if (record != null)
            {
                cbox_serverIP.Text = record[0];
                cbox_port.Text = record[1];
                cbox_userName.Text = record[2];
                cbox_userIdentity.Text = record[3];
                cbox_identityPriority.Text = record[4];
            }
          
        }
        private String[] getPreviousRecord(string rAttribute)
        {
            string[] record = new string[7];
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
                    case "userIdentity":
                        record[3] = rVal;
                        break;
                    case "identityPriority":
                        record[4] = rVal;
                        break;
                    case "appGuid":
                        record[5] = rVal;
                        break;
                    case "signUrl":
                        record[6] = rVal;
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

                //XmlElement rUserIdentity = xmldoc.CreateElement("", "userIdentity", "");
                //rUserIdentity.IsEmpty = false;
                //rMainNode.AppendChild(rUserIdentity);

                //XmlElement rIdentityPriority = xmldoc.CreateElement("", "identityPriority", "");
                //rUserIdentity.IsEmpty = false;
                //rMainNode.AppendChild(rIdentityPriority);

                XmlElement rAppGuid = xmldoc.CreateElement("", "appGuidList", "");
                rAppGuid.IsEmpty = false;
                rMainNode.AppendChild(rAppGuid);

                XmlElement rPreviousRecord = xmldoc.CreateElement("", "previousrecord", "");
                rPreviousRecord.IsEmpty = false;
                rMainNode.AppendChild(rPreviousRecord);

                xmldoc.Save(mPath);
            }
        }

        #endregion
        
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

        private void cbox_userIdentity_SelectedValueChanged(object sender, EventArgs e)
        {
            if (cbox_userIdentity.SelectedIndex == 1)
            {               
                pnl_AutoRouter.Show();
                pnl_selectSkill.Show();
            }
            else
            {
                pnl_AutoRouter.Hide();
                pnl_selectSkill.Hide();
            }
        }

        private void chkBox_skill_cash_CheckedChanged(object sender, EventArgs e)
        {
            if (chkBox_skill_cash.Checked)
            {
                m_skillsValue = m_skillsValue + 1;
            }else{
                m_skillsValue = m_skillsValue - 1;
            }

        }

        private void chkBox_skill_finance_CheckedChanged(object sender, EventArgs e)
        {
            if (chkBox_skill_finance.Checked)
            {
                m_skillsValue = m_skillsValue + 2;
            }
            else
            {
                m_skillsValue = m_skillsValue - 2;
            }
        }

        private void chkBox_skill_loan_CheckedChanged(object sender, EventArgs e)
        {
            if (chkBox_skill_loan.Checked)
            {
                m_skillsValue = m_skillsValue + 4;
            }
            else
            {
                m_skillsValue = m_skillsValue - 4;
            }
        }
    }   


}
