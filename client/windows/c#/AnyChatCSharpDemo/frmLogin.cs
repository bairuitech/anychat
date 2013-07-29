using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net;

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
        public static int m_VideoTcpPort = 8906;//佰锐8906，


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
            string m_Pass = txt_password.Text.Trim();
            if (m_User.Length == 0)
            {
                MessageBox.Show("账号不能为空", "提示");
                return;
            }


            if (m_UserName == "")
            {
                m_UserName = m_User;
            }
            m_VideoServerIP = txt_hospitalip.Text.Trim();


            try
            {
                m_VideoTcpPort = Convert.ToInt32(tb_port.Text);
            }
            catch (Exception)
            {
                MessageBox.Show("端口号是整数");
            }

            this.Hide();
            frmRoom m_FR = new frmRoom();
            m_FR.Show();
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


        }

        #endregion

        

    }
}