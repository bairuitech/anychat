using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.IO;
using System.Xml;
using System.Threading;

namespace AnyChatCSharpDemo
{
    public partial class frmLogin : Form
    {

        #region 定义变量

        
        
        /// <summary>
        /// 用户登录账号
        /// </summary>
        public static string m_UserName = "";
        /// <summary>
        /// 用户密码
        /// </summary>
        public static string m_LoginPass = "";
        /// <summary>
        /// 视频服务器IP
        /// </summary>
        public static string m_VideoServerIP = "211.155.25.89";
       
        /// <summary>
        /// 本地视频采集宽度
        /// </summary>
        public static int m_LocalVideoWidth = 320;
        /// <summary>
        /// 本地视频采集高度
        /// </summary>
        public static int m_LocalVideoHeight = 240;
        /// <summary>
        /// 服务器TCP的IP
        /// </summary>
        public static int m_VideoTcpPort = 8906;//8906
        /// <summary>
        /// 应用ID
        /// </summary>
        public static string m_AppGuid = string.Empty;

        string mPath = Application.StartupPath + "/record.xml";

        XmlDocument mXmlDoc = new XmlDocument();
        /// <summary>
        /// 登录方式
        /// </summary>
        public static LoginType m_loginType = LoginType.Normal;
        /// <summary>
        /// 签名Url
        /// </summary>
        public static string m_SignUrl = string.Empty;

        #endregion

        #region 构造函数

        public frmLogin()
        {
            InitializeComponent();
        }

        #endregion

        #region 登录

        private void btn_login_Click(object sender, EventArgs e)
        {
            string m_User = txt_username.Text.Trim();

            if (m_User.Length == 0)
            {
                MessageBox.Show("账号不能为空", "提示");
                return;
            }


            if (m_UserName == "")
            {
                m_UserName = m_User;
            }

            m_VideoServerIP = txt_serverip.Text.Trim();
            m_LoginPass = txt_password.Text.Trim();
            m_AppGuid = txt_appGuid.Text.Trim();

            try
            {
                m_VideoTcpPort = Convert.ToInt32(tb_port.Text);
            }
            catch (Exception)
            {
                MessageBox.Show("端口号是整数");
            }

            if (rbtn_normal.Checked)
            {
                m_loginType = LoginType.Normal;
            }
            if (rbtn_sign.Checked)
            {
                m_loginType = LoginType.Sign;
            }

            this.Hide();
            frmRoom m_FR = new frmRoom();
            m_FR.Show();

            RecordLoginTrace();

        }

        #endregion

        #region 退出

        private void btn_canel_Click(object sender, EventArgs e)
        {
            System.Environment.Exit(0);
        }

        #endregion

       
        #region 窗体加载

        private void frmLogin_Load(object sender, EventArgs e)
        {
            lbl_status.Text = string.Empty;

            if (File.Exists(mPath))
            {
                mXmlDoc.Load(mPath);
                LoadRecordTrace();
            }
            else
            {
                rbtn_sign.Checked = true;
                txt_serverip.Text = "cloud.anychat.cn";
                tb_port.Text = "8906";
                txt_appGuid.Text = "fbe957d1-c25a-4992-9e75-d993294a5d56";
            }
        }

        #endregion


        #region 登录信息保存处理

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

                XmlElement rPreviousRecord = xmldoc.CreateElement("", "previousrecord", "");
                rPreviousRecord.IsEmpty = false;
                rMainNode.AppendChild(rPreviousRecord);

                xmldoc.Save(mPath);
            }
        }


        /// <summary>
        /// 保存登录信息
        /// </summary>
        private void RecordLoginTrace()
        {
            int loginType = 0;
            try
            {
                if (!File.Exists(mPath))
                {
                    CreateXMLDoc();
                    mXmlDoc.Load(mPath);
                }

                PreviousRecordValue("previousrecord", "ip", txt_serverip.Text);
                PreviousRecordValue("previousrecord", "port", tb_port.Text);
                PreviousRecordValue("previousrecord", "userName", txt_username.Text);
                PreviousRecordValue("previousrecord", "appGuid", txt_appGuid.Text);

                if (rbtn_sign.Checked) loginType = 1;
                if (rbtn_normal.Checked) loginType = 0;
                PreviousRecordValue("previousrecord", "loginType", loginType.ToString());

                if (String.IsNullOrEmpty(m_SignUrl))
                {
                    /**
                     * 默认的签名服务器地址，只针对默认的AppID进行签名，其他应用AppID的签名需要自己部署签名服务器
                     */
                    m_SignUrl = "http://demo.anychat.cn:8930/";
                    PreviousRecordValue("previousrecord", "signUrl", m_SignUrl);
                }
            }
            catch (Exception ex)
            {
                
            }
        }

        private void PreviousRecordValue(string rAttribute, string rN, string rValue)
        {
            XmlNode rMainNode = mXmlDoc.SelectSingleNode("settings");
            XmlNode rNode = rMainNode.SelectSingleNode(rAttribute);
            XmlNodeList rList = rNode.ChildNodes;
            bool bExists = false;
            XmlElement rElem = null;
            foreach (XmlNode x in rList)
            {
                rElem = (XmlElement)x;
                string rVal = rElem.GetAttribute("value");
                if (rElem.Name.Equals(rN))
                {
                    bExists = true;
                    break;
                }
            }
            if (bExists && rElem != null)
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

        private void LoadRecordTrace()
        {
            int loginType = 0;
            string[] record = getPreviousRecord("previousrecord");
            if (record != null)
            {
                txt_serverip.Text = record[0];
                tb_port.Text = record[1];
                txt_username.Text = record[2];
                txt_appGuid.Text = record[3];
                m_SignUrl = record[4];
                Int32.TryParse(record[5], out loginType);
                if (loginType == 1) rbtn_sign.Checked = true; else rbtn_normal.Checked = true;
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
                    case "appGuid":
                        record[3] = rVal;
                        break;
                    case "signUrl":
                        record[4] = rVal;
                        break;
                    case "loginType":
                        record[5] = rVal;
                        break;
                }
            }
            if (bExists)
                return record;
            return null;
        }



        #endregion

        private void rbtn_normal_Click(object sender, EventArgs e)
        {
            if (txt_serverip.Text.ToLower().Equals("cloud.anychat.cn") && rbtn_normal.Checked)
            {
                txt_serverip.Text = "demo.anychat.cn";
                tb_port.Text = "8906";
            }
        }

        private void rbtn_sign_Click(object sender, EventArgs e)
        {
            if (txt_serverip.Text.ToLower().Equals("demo.anychat.cn") && rbtn_sign.Checked)
            {
                txt_serverip.Text = "cloud.anychat.cn";
                tb_port.Text = "8906";
                if (string.IsNullOrEmpty(txt_appGuid.Text))
                    txt_appGuid.Text = "fbe957d1-c25a-4992-9e75-d993294a5d56";
            }
        }


    }
}