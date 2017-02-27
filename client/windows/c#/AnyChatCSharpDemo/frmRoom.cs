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

        #region ���崰��ί��

        delegate void AsyncTransFileStatus(int m_UserID, int m_TaskID);
        delegate void AsyncTransSetFileProgress(string m_Progress);


        #endregion

        #region ����ؼ�

        //�û���Ƶ��Ϣ��ʾLabel
        Label lbl_user = new System.Windows.Forms.Label();

        #endregion

        #region �ļ������������

        int m_ReceiveUserID = -1;
        int m_ReceiveTaskID = -1;
        /// <summary>
        /// ���䷽ʽ
        /// </summary>
        TransType transType = TransType.TextMessage;

        /// <summary>
        /// �Ƿ�ѡ���Լ�
        /// </summary>
        bool chooseMyself = false;
        #endregion

        #region ����WIN��API

        /// <summary>
        /// ����������С
        /// </summary>
        /// <param name="deviceID"></param>
        /// <param name="Volume"></param>
        /// <returns></returns>
        [DllImport("winmm.dll", EntryPoint = "waveOutSetVolume", CharSet = CharSet.Auto)]
        public static extern long waveOutSetVolume(long deviceID, long Volume); 

        #endregion

        #region ������Ϣ����

        /// <summary>
        /// ��������
        /// </summary>
        public string[] m_AllFontSizeName ={ "8", "9", "10", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72", "����", "С��", "һ��", "Сһ", "����", "С��", "����", "С��", "�ĺ�", "С��", "���", "С��", "����", "С��", "�ߺ�", "�˺�" };
        /// <summary>
        /// �ֺ�
        /// </summary>
        public float[] m_AllFontSize ={ 8, 9, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72, 42, 36, 26, 24, 22, 18, 16, 15, 14, 12, 10.5F, 9, 7.5F, 6.5F, 5.5F, 5 };
        //1=160*120��2=176*144�� 3=320*240�� 4=352*288�� 5=528*384�� 6=640*480�� 7=704*576
        /// <summary>
        /// ��Ƶ�Ŵ���
        /// </summary>
        private int m_VideoWidthMax = 480;
        /// <summary>
        /// ��Ƶ�Ŵ�߶�
        /// </summary>
        private int m_VideoHeightMax = 384;
        /// <summary>
        /// ������Ƶ״̬��trueΪ���ͱ�����Ƶ��falseΪ������
        /// </summary>
        private bool m_LocalVideoStatue = true;
        /// <summary>
        /// ������Ƶ״̬��trueΪ���ͱ�����Ƶ��falseΪ������
        /// </summary>
        private bool m_LocalAudioStatue = true;

        #endregion

        #region ������Ϣ����

        /// <summary>
        /// ������Ƶ����(���ż�����Ƶ����)
        /// </summary>
        private int m_ColUserVideo = 3;
        /// <summary>
        /// ����ID
        /// </summary>
        private int m_RoomID = 1;
        /// <summary>
        /// �û�ID��ϵͳ�Զ����䣩
        /// </summary>
        private int m_myUserID = -1;
        /// <summary>
        /// �����û��б��������Լ������������Դ�
        /// </summary>
        private List<int> m_others = new List<int>();
        /// <summary>
        /// �û��б������û��ṹ���ԣ�
        /// </summary>
        private List<clsMemberList.MemberItem> m_MemberItem=new List<clsMemberList.MemberItem>();

        #endregion

        #region ���캯��

        public frmRoom()
        {
            InitializeComponent();
        }

        #endregion

        #region ��ʼ������

        void InitChat()
        {
            //Ӧ��ǩ��
            string signStr = string.Empty;
            //ǩ��ʱ���
            int signTimestamp = 0;

            string path = Application.StartupPath;
            SystemSetting.Text_OnReceive = new TextReceivedHandler(Received_Text);//�ı��ص�����
            SystemSetting.TransBuffer_OnReceive = new TransBufferReceivedHandler(Received_TransBuffer);//͸��ͨ������ص�
            SystemSetting.TransBufferEx_OnReceive = new TransBufferExReceivedHandler(Received_TransBufferEx);  //͸��ͨ������ص�
            SystemSetting.TransFile_Received = new TransFileReceivedHandler(Received_TransFile);//�ļ�����ص�
            AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_CORESDK_PATH, path, path.Length);
         
            SystemSetting.Init(this.Handle);

            ////������Ƶ�ֱ���
            //int m_Refw = AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_WIDTHCTRL, ref frmLogin.m_LocalVideoWidth, sizeof(int));
            //int m_Refh = AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, ref frmLogin.m_LocalVideoHeight, sizeof(int));
            ////Ӧ�ñ�����Ƶ���������ʹ��ǰ���޸ļ�ʱ��Ч������Ϊint�ͣ�1 ʹ���²�����0 ʹ��Ĭ�ϲ�����
            //int m_AppLocal = 1;
            //AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_APPLYPARAM, ref m_AppLocal, sizeof(int));

            //StringBuilder m_ServerKey = new StringBuilder();
            //m_ServerKey.Append("d");
            //int retkey = AnyChatCoreSDK.SetServerAuthPass(m_ServerKey);

            /* AnyChat����������������ķ�������Ҳ��������AnyChat��Ƶ��ƽ̨��
             * ������������������ĵ�ַΪ����ķ�����IP��ַ���������˿ڣ�
             * ����AnyChat��Ƶ��ƽ̨�ķ�������ַΪ��cloud.anychat.cn���˿�Ϊ��8906
             */
            int ret = AnyChatCoreSDK.Connect(frmLogin.m_VideoServerIP, frmLogin.m_VideoTcpPort);

            /*
             * AnyChat֧�ֶ����û������֤��ʽ����������ȫ��ǩ����¼��
             * ������ο���http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
             */
            ret = AnyChatCoreSDK.Login(frmLogin.m_UserName, frmLogin.m_LoginPass, 0);

            comboBox_TransType.SelectedIndex = (int)TransType.TextMessage;
            transType = TransType.TextMessage;
        }

        #endregion

        #region �ļ�����

        #region ��ʾ�ļ�����״̬

        private void Receive_GransFileStatus(int m_UserID, int m_TaskID)
        {
            m_ReceiveUserID = m_UserID;
            m_ReceiveTaskID = m_TaskID;
            //MessageBox.Show("U:" + m_ReceiveUserID.ToString() + "T:" + m_ReceiveTaskID.ToString());
            //txt_2.BeginInvoke(new AsyncTransSetFileProgress(SetTxtValue), m_ReceiveUserID.ToString() + ":" + m_ReceiveTaskID.ToString());
        }

        #endregion

        #region ÿ������ļ�����

        private void tmr_receivefile_Tick(object sender, EventArgs e)
        {
            //ÿ�������Ƶ����

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

            //ÿ�������Ƶ����
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
            lbl_progress.BeginInvoke(new AsyncTransSetFileProgress(SetTransFileProgress),  "����:" + m_BFB);

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
            lbl_speed.BeginInvoke(new AsyncTransSetFileProgress(SetTransFileSpeed), "����:" + m_VSpeed);
        }

        #endregion

        #region �첽�����ļ�����

        private void SetTransFileProgress(string m_Progress)
        {
            lbl_progress.Text = m_Progress;
        }

        private void SetTransFileSpeed(string m_Speed)
        {
            lbl_speed.Text = m_Speed;
        }

        #endregion

        #region �첽�����ı���ֵ

        private void SetTxtValue(string m_Txt)
        {
            //txt_2.Text = m_Txt;
        }

        #endregion

        #region �첽������Ƶ����

        private void SetVideoSpeed(string m_VSpeed)
        {
            lbl_v_speed.Text = "��Ƶ���ʣ�" + m_VSpeed;
        }

        #endregion

        #region �첽������Ƶ����

        private void SetAudioSpeed(string m_ASpeed)
        {
            lbl_a_speed.Text = "��Ƶ���ʣ�" + m_ASpeed;
        }

        #endregion

        #endregion

        #region ��ʾ�ı�

        /// <summary>
        /// ��ʾ�����ı�
        /// </summary>
        /// <param name="fromUID"></param>
        /// <param name="toUID"></param>
        /// <param name="m_Text"></param>
        /// <param name="isserect"></param>
        void Received_Text(int fromUID, int toUID, string m_Text, bool isserect)
        {
            string m_FromName = GetUserNameByID(fromUID);
            string m_ToName = GetUserNameByID(toUID);
            if (toUID == -1) m_ToName = "���";
            string m_DispMsg = m_FromName + " To " + m_ToName + " ";
            ShowText(m_DispMsg, txt_Accept.TextLength, m_DispMsg.Length, Color.Green, new Font("����", 9, FontStyle.Bold));
            ShowText(DateTime.Now.ToString(), txt_Accept.TextLength, DateTime.Now.ToString().Length, Color.Green, new Font("����", 9, FontStyle.Bold));
            ShowText("\r\n", txt_Accept.TextLength, 4, Color.Blue, new Font("����", 12));
            ShowText("    ", txt_Accept.TextLength, 4, Color.Blue, new Font("����", 12));
            ShowText(m_Text, txt_Accept.TextLength, m_Text.Length, Color.Black, new Font("����", 9));
            ShowText("\r\n\r\n", txt_Accept.TextLength, 8, Color.Blue, new Font("����", 12));
        }
        /// <summary>
        /// ��ʾϵͳ��Ϣ
        /// </summary>
        /// <param name="m_Msg"></param>
        void Print(string m_Msg)
        {
            string m_SysInfo = "[ϵͳ��Ϣ] ";
            m_Msg += "\r\n\r\n";
            ShowText(m_SysInfo, txt_Accept.TextLength, m_SysInfo.Length, Color.Red, new Font("����", 9,FontStyle.Bold));
            ShowText(m_Msg, txt_Accept.TextLength, m_Msg.Length, Color.Black, new Font("����", 9));
        }
        /// <summary>
        /// ��RichTextBox����ı�
        /// </summary>
        /// <param name="sText"></param>
        /// <param name="nStart"></param>
        /// <param name="nLength"></param>
        /// <param name="color"></param>
        /// <param name="font"></param>
        private void ShowText(string sText, int nStart, int nLength, Color color, Font font)
        {
            txt_Accept.AppendText(sText);
            txt_Accept.Select(nStart, nLength);    // ��Ҫ�޸���ɫ�Ĳ���
            txt_Accept.SelectionColor = color;     // ��ɫ
            txt_Accept.SelectionFont = font;       // ����
            txt_Accept.ScrollToCaret();
            txt_Accept.Select(txt_Accept.Text.Length, 0); 
        }

        #endregion

        #region ����WndProc

        protected override void WndProc(ref Message m)
        {

            if (m.Msg == AnyChatCoreSDK.WM_GV_CONNECT)
            {
                ///����
                int succed = m.WParam.ToInt32();
                if (succed == 1)
                {
                    Print("���ӳɹ�!");
                }
                else
                {
                    Print("����ʧ��,�����:" + m.LParam.ToInt32());
                }
            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_LOGINSYSTEM)
            {
                ///��¼ϵͳ
                int userid = m.WParam.ToInt32();
                if (m.LParam.ToInt32() == 0)
                {
                    //Print("��¼�������ɹ����Լ����û����Ϊ��" + userid.ToString());
                    Print("��¼�������ɹ����Լ����û��˺�Ϊ��" + frmLogin.m_UserName);
                    m_myUserID = userid;

                    //StringBuilder userName = new StringBuilder(30);
                    //int ret = AnyChatCoreSDK.GetUserName(userid, userName, 30);

                    AnyChatCoreSDK.EnterRoom(m_RoomID, "", 0);
                }
                else
                {
                    Print("��¼������ʧ�ܣ��������Ϊ��" + m.LParam.ToInt32());
                }
            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_ENTERROOM)
            {
                ///���뷿��
                if (m.LParam.ToInt32() == 0)
                {
                    int roomid = m.WParam.ToInt32();
                    Print("���뷿��ɹ�,������Ϊ��" + roomid.ToString());
                    m_RoomID = roomid;

                    getLocalVideoDeivceName();

                    int ret = AnyChatCoreSDK.SetVideoPos(-1, pnl_local.Handle, 0, 0, pnl_local.Width, pnl_local.Height);
                    ret = AnyChatCoreSDK.UserCameraControl(-1, true);
                    ret = AnyChatCoreSDK.UserSpeakControl(-1, true);
                }
                else
                {
                    Print("������뷿��ʧ�ܣ��������Ϊ��" + m.LParam.ToInt32());
                }
            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_ONLINEUSER)
            {
                ///Ŀǰ�ڷ�����û��б�
                int usrcnt = m.WParam.ToInt32();
                Print("�ڱ��Ϊ��" + m.LParam.ToInt32() + " �ķ��乲��" + usrcnt + "λ�����û�");
                Print("��ǰʱ�䣺" + DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss"));

                int cnt = 0;//�����û�����
                AnyChatCoreSDK.GetOnlineUser(null, ref cnt);//��ȡ�����û�����
                int[] userArr = new int[cnt];//�����û��ɣ�
                AnyChatCoreSDK.GetOnlineUser(userArr, ref cnt);//��ȡ�����û��ɣ�����

                if (userArr.Length >= 1)
                {
                    for (int i = 0; i < userArr.Length; i++)
                    {
                        m_others.Add(userArr[i]);//���������û��б��У������������û����ߣɣ����飩
                        UpdateUserList(userArr[i], i);//��ӵ������û��б��Զ��壬���û����Խṹ��
                    }
                    UpdateOnlineUser();
                }
                else
                {
                    dgv_onlineuser.Rows.Clear();
                    DataGridViewRow dgvr = new DataGridViewRow();
                    dgv_onlineuser.Rows.Add(dgvr);
                    dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
                    dgvr.Cells["gvc_username"].Value = "���";
                    dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.��ұ���;
                    dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.��ұ���;
                    dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.��ұ���;
                    dgvr = new DataGridViewRow();
                    dgv_onlineuser.Rows.Add(dgvr);
                    dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
                    dgvr.Cells["gvc_username"].Value = frmLogin.m_UserName; ;
                    dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.������_ǳ��;
                    dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.���;
                    dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.����ͷ;
                }

            }
            else if (m.Msg == AnyChatCoreSDK.WM_GV_USERATROOM)
            {
                ///���û�������˳�����
                int userID = m.WParam.ToInt32();
                int boEntered = m.LParam.ToInt32();

                if (boEntered == 1)
                {
                    m_others.Add(userID);
                    UpdateUserList(userID, m_others.Count - 1);
                    Print("�û���" + GetUserNameByID(userID) + " ���뷿��");
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
                    Print("�û���" + GetUserNameByID(userID) + " �뿪����");
                }
                UpdateOnlineUser();//�����û��б�
                this.Invalidate();//�ػ���棬��ֹ�������
            }
            base.WndProc(ref m);
        }

        #endregion

        #region ˢ���û��б�

        private void UpdateOnlineUser()
        {
            DataGridViewRow dgvr = new DataGridViewRow();
            //����ԭѡ���û�
            string m_TempUserName = "";
            int m_DGVSelectRow = -1;
            if (dgv_onlineuser.SelectedRows.Count > 0)
            {
                dgvr = dgv_onlineuser.SelectedRows[0];
                m_TempUserName = dgvr.Cells["gvc_username"].Value.ToString();
            }
            dgv_onlineuser.Rows.Clear();//����û��б�
            pnl_video.Controls.Clear();//���������Ƶ����
            //��ʾ���
            dgvr = new DataGridViewRow();
            dgv_onlineuser.Rows.Add(dgvr);
            dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
            dgvr.Cells["gvc_username"].Value = "���";
            dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.��ұ���;
            dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.��ұ���;
            dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.��ұ���;
            dgvr = new DataGridViewRow();
            dgv_onlineuser.Rows.Add(dgvr);
            dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
            dgvr.Cells["gvc_username"].Value = frmLogin.m_UserName; ;
            dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.������_ǳ��;
            dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.���;
            dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.����ͷ;
            //��ʾ�Լ�
            for (int i = 0; i < m_MemberItem.Count; i++)
            {
                dgvr = new DataGridViewRow();
                dgv_onlineuser.Rows.Add(dgvr);
                dgvr = dgv_onlineuser.Rows[dgv_onlineuser.Rows.Count - 1];
                dgvr.Cells["gvc_username"].Value = m_MemberItem[i].m_UserName;
                dgvr.Cells["gvc_audio"].Value = AnyChatCSharpDemo.Properties.Resources.��� ;
                dgvr.Cells["gvc_video"].Value = AnyChatCSharpDemo.Properties.Resources.����ͷ;
                dgvr.Cells["gvc_character"].Value = AnyChatCSharpDemo.Properties.Resources.��ͨ��_ǳ��;
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

        #region ���ӻ�����û�

        private void UpdateUserList(int m_UserID,int m_Index)
        {
            clsMemberList.MemberItem m_TempItem = new clsMemberList.MemberItem();//�����û������б��Զ��壬�����û����ԣ�
            
            StringBuilder m_TempName = new StringBuilder(30);

            byte[] userNameByte = new byte[255];
            int ret = AnyChatCoreSDK.GetUserName(m_UserID, ref userNameByte[0], 30);//��ȡ�û��˺�

            m_TempItem.m_UserName = byteToString(userNameByte);
            m_TempItem.m_UserID = m_UserID;
            m_TempItem.m_Index = m_Index;
            m_TempItem.m_Permission = new int[] { 0, 0, 0 };//�û�Ȩ��
            m_MemberItem.Add(m_TempItem);//��ӵ������û��б�
        }
        /// <summary>
        /// ͨ���û�ID����û��˺�
        /// </summary>
        /// <param name="m_UserID"></param>
        /// <returns></returns>
        private string GetUserNameByID(int m_UserID)
        {
            byte[] userNameByte = new byte[255];
            int ret = AnyChatCoreSDK.GetUserName(m_UserID, ref userNameByte[0], 30);//��ȡ�û��˺�
            return byteToString(userNameByte);
        }
        /// <summary>
        /// ͨ���û��˺Ż���û�ID
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

        #region �û���Ƶ���ڲ���

        #region �����û���Ƶ����

        private void CreateUserVideo(int m_UserID)
        {
            //�û���Ƶ������ʾ����
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
        /// ��ȡ�����û��������������Լ���
        /// </summary>
        /// <returns>�����û�����</returns>
        private int GetUserCount()
        {
            int userCount = 0;
            //int[] ids = new int[] { };
            AnyChatCoreSDK.GetOnlineUser(null, ref userCount);
            return userCount;
        }

        #endregion

        #region �������û���Ƶ����

        void m_ShowWnd_MouseEnter(object sender, EventArgs e)
        {
            Control ShowWnd = (Control)sender;
            string userName = GetUserNameByID(Convert.ToInt32(ShowWnd.Name));

            // lbl_user��ʼ�� 
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

        #region ����뿪�û���Ƶ����

        void m_ShowWnd_MouseLeave(object sender, EventArgs e)
        {
            lbl_user.Visible = false;
        }

        #endregion

        #region ˫���û���Ƶ����

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

        #region ������Ƶ����˫���¼�

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

        #region ������عر�

        #region �������

        private void frmRoom_Load(object sender, EventArgs e)
        {
            InitChat();//��ʼ��
            //InitUserPanel();//��ʼ���û����
            //��ʼ�����Ͱ�ť�ҽ��˵�
            ment_item_ctrlenter.Image = null;
            ment_item_enter.Image = AnyChatCSharpDemo.Properties.Resources.duihao;
            //��ʼ�������ֺ�
            InitFont();
            //m_VideoWidthMax = frmLogin.m_LocalVideoWidth;
            //m_VideoHeightMax = frmLogin.m_LocalVideoHeight;
            //m_VideoWidthMax = 640;
            //m_VideoHeightMax = 480;

            //����Ƶ״̬
            chk_localvideo.Checked = m_LocalVideoStatue ;
            chk_localaudio.Checked = m_LocalAudioStatue;

            //cbox_video.SelectedIndex = 5;//��Ƶ��󻯳ߴ�

            #region �ɼ��ֱ���

            //1=160*120��2=176*144�� 3=320*240�� 4=352*288�� 5=528*384�� 6=640*480�� 7=704*576
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

        #region ����ر�

        private void frmRoom_FormClosing(object sender, FormClosingEventArgs e)
        {
            AnyChatCoreSDK.LeaveRoom(m_RoomID);
            AnyChatCoreSDK.Logout();
            System.Environment.Exit(0);
        }

        #endregion

        #endregion

        #region �ı�����

        /// <summary>
        /// ���Ͱ�ť
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btn_sendtxt_Click(object sender, EventArgs e)
        {
            string m_Message = rtxt_sendtxt.Text;
            if (m_Message.Length == 0)
            {
                MessageBox.Show("�������ݲ���Ϊ��","��ʾ");
                return;
            }

            int length = UnicodeEncoding.Default.GetBytes(m_Message).Length;
            int m_TempUserID = -1;
            string m_TempUserName = "���";
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
                    MessageBox.Show("��ѡ��Ŀ���û���", "��ʾ");
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


            //��ʾ��������
            string m_DispMsg = "�� To   " + m_TempUserName+" ";
            ShowText(m_DispMsg, txt_Accept.TextLength, m_DispMsg.Length, Color.Green, new Font("����", 9, FontStyle.Bold));
            ShowText(DateTime.Now.ToString(), txt_Accept.TextLength, DateTime.Now.ToString().Length, Color.Green, new Font("����", 9, FontStyle.Bold));
            ShowText("\r\n", txt_Accept.TextLength, 4, Color.Blue, new Font("����", 12));
            ShowText("    ", txt_Accept.TextLength, 4, Color.Blue, new Font("����", 12));            
            if (transType == TransType.TransBufferEx)
            {
                ShowText(m_Message + ",taskId��" + taskId, txt_Accept.TextLength, m_Message.Length, Color.Black, new Font("����", 9));
            }
            else
            {
                ShowText(m_Message, txt_Accept.TextLength, m_Message.Length, Color.Black, new Font("����", 9));
            }
            ShowText("\r\n\r\n", txt_Accept.TextLength, 8, Color.Blue, new Font("����", 12));
            rtxt_sendtxt.Text = "";
        }

        /// <summary>
        /// ���̰�����ϼ�
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
        /// �����ͷ���ϼ�
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
        /// ���Ͱ�ť�ҽ��˵���Ctrl+Enter)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ment_item_ctrlenter_Click(object sender, EventArgs e)
        {
            ment_item_ctrlenter.Image = AnyChatCSharpDemo.Properties.Resources.duihao;
            ment_item_enter.Image = null;
        }
        /// <summary>
        /// ���Ͱ�ť�ҽ��˵���Enter)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ment_item_enter_Click(object sender, EventArgs e)
        {
            ment_item_enter.Image = AnyChatCSharpDemo.Properties.Resources.duihao;
            ment_item_ctrlenter.Image = null;
        }
        /// <summary>
        /// ��ʼ������,�ֺ�
        /// </summary>
        private void InitFont()
        {
            int m_SelectIndex = 0;
            int m_Index = 0;
            System.Drawing.Text.InstalledFontCollection m_ObjFont = new System.Drawing.Text.InstalledFontCollection();
            foreach (System.Drawing.FontFamily m_Font in m_ObjFont.Families)
            {
                cmb_font.Items.Add(m_Font.Name.ToString());

                if (m_Font.Name == "����")
                    m_SelectIndex = m_Index;
                m_Index++;
            }
            cmb_font.SelectedIndex = m_SelectIndex;

            foreach (string m_FontSize in m_AllFontSizeName)
            {
                cmb_fontsize.Items.Add(m_FontSize);
            }
            cmb_fontsize.SelectedItem = "С��";
        }

        #endregion

        #region ��ʼ���û��б����

        private void InitUserPanel()
        {
            pnl_userlist.Width = 285;
            pnl_userlist.Height = 400;
            pnl_userlist.Top = (this.Height - 30 - pnl_userlist.Height) / 2;
            pnl_userlist.Left = this.Width - 41;
        }
        /// <summary>
        /// ��ʾ�������û����
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

        #region �����û��б�

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
                
                lbl_touser.Text = "�� �� " + m_TempUserName + " ˵��";
            }
            catch (Exception ex) { }
        }

        private void dgv_onlineuser_SelectionChanged(object sender, EventArgs e)
        {
            dgv_onlineuser_Click(null, null);
        }

        #endregion

        #region Ȩ������

        #region ������ƵȨ��

        /// <summary>
        /// ������ƵȨ��
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
                if (m_TempUserName == frmLogin.m_UserName || m_TempUserName=="���") return;
                int m_TempUserID = GetUserIDByName(m_TempUserName);
                AnyChatCoreSDK.UserCameraControl(m_TempUserID, menu_item_video.Checked);
            }
            catch (Exception ex) { }
        }

        #endregion

        #region �û�״̬

        private void menu_item_status_Click(object sender, EventArgs e)
        {
            try
            {
                //if (dgv_onlineuser.SelectedRows.Count == 0) return;
                //DataGridViewRow dgvr = dgv_onlineuser.SelectedRows[0];
                //string m_TempUserName = dgvr.Cells["gvc_username"].Value.ToString();
                //if (m_TempUserName == frmLogin.m_UserName || m_TempUserName == "���") return;
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

        #region ��ʾ�����ı�������

        private void pnl_visableword_MouseEnter(object sender, EventArgs e)
        {
            if (pnl_word.Left == 658)//��ʾ�ı���״̬
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.���ط���;
            }
            else
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.ȡ�����ط���;
            }
        }

        private void pnl_visableword_MouseDown(object sender, MouseEventArgs e)
        {
            if (pnl_word.Left == 658)//��ʾ�ı���״̬
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.���ذ���;
            }
            else
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.ȡ�����ذ���;
            }
        }

        private void pnl_visableword_MouseUp(object sender, MouseEventArgs e)
        {
            if (pnl_word.Left == 658)//��ʾ�ı���״̬
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.���ط���;
                pnl_word.Left = this.Width - 17-6;
                pnl_video.Width = 640;
            }
            else
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.ȡ�����ط���;
                pnl_word.Left = 658;
                pnl_video.Width = 480;
            }
        }

        private void pnl_visableword_MouseLeave(object sender, EventArgs e)
        {
            if (pnl_word.Left == 658)//��ʾ�ı���״̬
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.���ط������;
            }
            else
            {
                pnl_visableword.BackgroundImage = AnyChatCSharpDemo.Properties.Resources.��ʾ�������;
            }
        }

        #endregion

        #region ��������Ƶ״̬

        /// <summary>
        /// ������Ƶ״̬
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chk_localvideo_CheckedChanged(object sender, EventArgs e)
        {

            int ret = AnyChatCoreSDK.UserCameraControl(-1, chk_localvideo.Checked);
        }
        /// <summary>
        /// ������Ƶ״̬
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void chk_localaudio_CheckedChanged(object sender, EventArgs e)
        {
            int ret = AnyChatCoreSDK.UserSpeakControl(-1, chk_localaudio.Checked);
        }

        #endregion

        #region ��Ƶ�����ʾ�ߴ�

        #endregion

        #region ����������Ƶ�ֱ���

        private void cbb_fbl_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cbb_fbl.SelectedIndex == 0)
            {
                int bUseAppParam = 0;
                //Ӧ�ñ�����Ƶ���������ʹ��ǰ���޸ļ�ʱ��Ч������Ϊint�ͣ�1 ʹ���²�����0 ʹ��Ĭ�ϲ�����
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_APPLYPARAM, ref bUseAppParam, sizeof(int));
            }
            else
            {
                int bitrate = 0;  //0��ʾ����ģʽ
                //���ñ�����Ƶ��������� 
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_BITRATECTRL, ref bitrate, sizeof(int));
                int keyframe = 60;
                //���ñ�����Ƶ����Ĺؼ�֡���
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_GOPCTRL, ref keyframe, sizeof(int));
                int framerate = 15;
                //���ñ�����Ƶ�����֡��
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_FPSCTRL, ref framerate, sizeof(int));
                int defaultParam = 3;
                // ���ñ�����Ƶ�����Ԥ����� 
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_PRESETCTRL, ref defaultParam, sizeof(int));
                int videoWidth = 1920;
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_WIDTHCTRL, ref videoWidth, sizeof(int));
                int vedioHeight = 1080;
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, ref vedioHeight, sizeof(int));

                int bUseAppParam = 1;
                //Ӧ�ñ�����Ƶ���������ʹ��ǰ���޸ļ�ʱ��Ч������Ϊint�ͣ�1 ʹ���²�����0 ʹ��Ĭ�ϲ�����
                AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_APPLYPARAM, ref bUseAppParam, sizeof(int));
            }
        }

        #endregion

        #region ��������

        #region ���ڻ���



        #endregion

        #endregion

        #region �����ļ���͸��ͨ����ʾ

        string sendPath;        //�����ļ���ַ
        string receivePath;     //�����ļ���ַ

        #region �����ļ�

        private void Received_TransFile(int userId, string fileName, string filePath, int fileLength, int wParam, int lParam, int taskId, int userValue)
        {
            //������1��Ϊ���ձ��
            if (wParam == 1)
            {
                FileInfo fi = new FileInfo(filePath);
                fi.MoveTo(receivePath +"\\"+ fi.Name);
                Print(receivePath + "\\" + fi.Name + "�ļ����ճɹ�");
            }
        }

        #endregion

        #region ͸��ͨ������

        private void Received_TransBuffer(int userId, IntPtr buf, int len, int userValue)
        {
            //������Ϣ����
            string m_Command = Marshal.PtrToStringAnsi(buf);
            try
            {
                if (m_Command.Length > 3)
                {
                    string[] m_Packet = m_Command.Split(":".ToCharArray());
                    if (m_Packet.Length > 0){
                        //ѡ���Ƿ�����ļ�
                        if (m_Packet[0] == "003" && m_Packet[3] == "file")
                        {
                            int m_TempUserID = Convert.ToInt32(m_Packet[1]);
                            string m_pacName = GetUserNameByID(m_TempUserID);
                            DialogResult r = MessageBox.Show("�ļ�����" + m_Packet[2].ToString() + "���Ƿ���գ�", m_pacName + "�����ļ�����", MessageBoxButtons.YesNo);
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
                        //�����ļ�
                        else if (m_Packet[0] == "003" && m_Packet[2] == "fileisok")
                        {
                            int taskId = 0;
                            int m_TempUserID = Convert.ToInt32(m_Packet[1]);
                            int flag = AnyChatCoreSDK.TransFile(m_TempUserID, sendPath, 1, 0, 0, ref taskId);
                            Print("�ɹ�����" + sendPath + "�ļ�");
                        }
                        else if (m_Packet[0] == "003" && m_Packet[2] == "fileisno")
                        {
                            string m_tempName = GetUserNameByID(Convert.ToInt32(m_Packet[1]));
                            Print(m_tempName + "�ܾ������ļ�" + m_Packet[3].ToString());
                        }
                        else
                        {
                            string m_UserName = GetUserNameByID(userId);
                            Print("�û���" + m_UserName + " ������Ϣ��" + m_Command);
                        }
                    }
                }
                else
                {
                    string m_UserName = GetUserNameByID(userId);
                    Print("�û���" + m_UserName + " ������Ϣ��" + m_Command);
                }                
            }
            catch (Exception ex)
            {

            }
        }

        private void Received_TransBufferEx(int userId, IntPtr buf, int len, int wParam, int lParam, int taskId, int userValue)
        {
            //������Ϣ����
            string m_Command = Marshal.PtrToStringAnsi(buf);
            try
            {
                string m_UserName = GetUserNameByID(userId);
                Print("�û���" + m_UserName + " ������Ϣ��" + m_Command + "��taskId��" + taskId);
            }
            catch (Exception ex)
            {

            }
        }

        #endregion

        #region ������

        private void btn_transfile_Click(object sender, EventArgs e)
        {
            if (dgv_onlineuser.SelectedRows.Count == 0)
            {
                Print("�ļ�����ʧ�ܣ���ѡ��Ŀ���û�");
                return;
            }
            else
            {
                DataGridViewRow dgvr = dgv_onlineuser.SelectedRows[0];
                string m_TempUserName = dgvr.Cells["gvc_username"].Value.ToString();
                if (m_TempUserName == frmLogin.m_UserName || m_TempUserName == "���")
                {
                    Print("�ļ�����ʧ�ܣ���ѡ��Ŀ���û�");
                    return;
                }
                else
                {
                    OpenFileDialog dlgopenFile = new OpenFileDialog();
                    dlgopenFile.Title = "ѡ����Ҫ���͵��ļ�";
                    DialogResult dr = dlgopenFile.ShowDialog();

                    if (dr == DialogResult.OK)
                    {
                        if (File.Exists(dlgopenFile.FileName))
                        {
                            sendPath = dlgopenFile.FileName;
                            //int taskId = 0;
                            int m_TempUserID = GetUserIDByName(m_TempUserName);
                            //��������
                            FileInfo fi = new FileInfo(dlgopenFile.FileName);
                            string m_Message = "003:" + m_myUserID.ToString() + ":" + fi.Name + ":" + "file";
                            byte[] buffer = Encoding.Default.GetBytes(m_Message);
                            int rett = AnyChatCoreSDK.TransBuffer(m_TempUserID, buffer, buffer.Length);
                            Print("��" + m_TempUserName + "�����ļ����ȴ�����...");
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
        /// ��Ƶ�豸�б�
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

                //addLog("��ȡ�ĵ�" + (idx + 1) + "����Ƶ�豸Ϊ��" + m_DeviceName, LogType.LOG_TYPE_NORMAL);
                retVal[idx] = m_DeviceName;

                ComboBoxItem item = new ComboBoxItem();
                item.Text = m_DeviceName;
                item.Value = idx;
                m_videoDeviceList.Add(item);
            }
            return retVal;

        }

        /// <summary>
        /// ��Json�ַ���ת���ɶ���
        /// </summary>
        /// <typeparam name="T">ת���Ķ�������</typeparam>
        /// <param name="output">json�ַ���</param>
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
        /// POST�������ȡ���  
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
                    encoding = "UTF-8"; //Ĭ�ϱ���  
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
        /// �ֽ�ת�ַ���
        /// </summary>
        /// <param name="byteStr">�ֽ�����</param>
        /// <returns>ת������ַ���</returns>
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
    /// ǩ����Ϣ��
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