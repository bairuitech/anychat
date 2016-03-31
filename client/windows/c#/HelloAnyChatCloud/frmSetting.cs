using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ANYCHATAPI;
using System.Threading;

namespace ANYCHATAPI
{
    public partial class frmSetting : Form
    {
        public List<ComboBoxItem> VideoDeviceItemList = new List<ComboBoxItem>();
        private int m_myUserID = 0;
        public frmSetting()
        {
            InitializeComponent();
        }

        public frmSetting(List<ComboBoxItem> videoDeviceItemList, int userID)
        {
            VideoDeviceItemList = videoDeviceItemList;

            InitializeComponent();

            displayComboBoxControl(false);

            m_myUserID = userID;

        }

        private void initVideoDeviceItem()
        {
            for (int idx = 0; idx < VideoDeviceItemList.Count; idx++)
            {
                comboBox_videoDeviceList.Items.Add(VideoDeviceItemList[idx]);
            }

            comboBox_videoDeviceList.SelectedIndex = 0;
        }

        /// <summary>
        /// 初始化视频帧率选项
        /// </summary>
        private void initVideoFPSItem()
        {
            ComboBoxItem item1 = new ComboBoxItem();
            item1.Text = "5 FPS";
            item1.Value = 5;
            comboBox_VideoFPS.Items.Add(item1);

            ComboBoxItem item2 = new ComboBoxItem();
            item2.Text = "8 FPS";
            item2.Value = 8;
            comboBox_VideoFPS.Items.Add(item2);

            ComboBoxItem item3 = new ComboBoxItem();
            item3.Text = "12 FPS";
            item3.Value = 12;
            comboBox_VideoFPS.Items.Add(item3);

            ComboBoxItem item4 = new ComboBoxItem();
            item4.Text = "15 FPS";
            item4.Value = 15;
            comboBox_VideoFPS.Items.Add(item4);

            ComboBoxItem item5 = new ComboBoxItem();
            item5.Text = "20 FPS";
            item5.Value = 20;
            comboBox_VideoFPS.Items.Add(item5);

            ComboBoxItem item6 = new ComboBoxItem();
            item6.Text = "25 FPS";
            item6.Value = 25;
            comboBox_VideoFPS.Items.Add(item6);

            ComboBoxItem item7 = new ComboBoxItem();
            item7.Text = "30 FPS";
            item7.Value = 30;
            comboBox_VideoFPS.Items.Add(item7);

            comboBox_VideoFPS.SelectedIndex = 0;

        }

        /// <summary>
        /// 初始化视频码率选项
        /// </summary>
        private void initVideoBitrateItem()
        {
            ComboBoxItem item1 = new ComboBoxItem();
            item1.Text = "质量模式";
            item1.Value = 0;
            comboBox_VideoBitrate.Items.Add(item1);

            ComboBoxItem item2 = new ComboBoxItem();
            item2.Text = "40Kbps";
            item2.Value = 40000;
            comboBox_VideoBitrate.Items.Add(item2);

            ComboBoxItem item3 = new ComboBoxItem();
            item3.Text = "60Kbps";
            item3.Value = 60000;
            comboBox_VideoBitrate.Items.Add(item3);

            ComboBoxItem item4 = new ComboBoxItem();
            item4.Text = "100Kbps";
            item4.Value = 100000;
            comboBox_VideoBitrate.Items.Add(item4);

            ComboBoxItem item5 = new ComboBoxItem();
            item5.Text = "150Kbps";
            item5.Value = 150000;
            comboBox_VideoBitrate.Items.Add(item5);

            ComboBoxItem item6 = new ComboBoxItem();
            item6.Text = "200Kbps";
            item6.Value = 200000;
            comboBox_VideoBitrate.Items.Add(item6);

            ComboBoxItem item7 = new ComboBoxItem();
            item7.Text = "300Kbps";
            item7.Value = 300000;
            comboBox_VideoBitrate.Items.Add(item7);

            ComboBoxItem item8 = new ComboBoxItem();
            item8.Text = "400Kbps";
            item8.Value = 400000;
            comboBox_VideoBitrate.Items.Add(item8);

            ComboBoxItem item9 = new ComboBoxItem();
            item9.Text = "500Kbps";
            item9.Value = 500000;
            comboBox_VideoBitrate.Items.Add(item9);

            ComboBoxItem item10 = new ComboBoxItem();
            item10.Text = "600Kbps";
            item10.Value = 600000;
            comboBox_VideoBitrate.Items.Add(item10);

            ComboBoxItem item11 = new ComboBoxItem();
            item11.Text = "800Kbps";
            item11.Value = 800000;
            comboBox_VideoBitrate.Items.Add(item11);

            ComboBoxItem item12 = new ComboBoxItem();
            item12.Text = "1000Kbps";
            item12.Value = 1000000;
            comboBox_VideoBitrate.Items.Add(item12);

            ComboBoxItem item13 = new ComboBoxItem();
            item13.Text = "1200Kbps";
            item13.Value = 1200000;
            comboBox_VideoBitrate.Items.Add(item13);

            ComboBoxItem item14 = new ComboBoxItem();
            item14.Text = "1500Kbps";
            item14.Value = 1500000;
            comboBox_VideoBitrate.Items.Add(item14);

            comboBox_VideoBitrate.SelectedIndex = 0;

        }

        /// <summary>
        /// 初始化视频分辨率选项
        /// </summary>
        private void initVideoVideoResolution()
        {
            ComboBoxItem item1 = new ComboBoxItem();
            item1.Text = "320x240";
            item1.Value = "320x240";
            comboBox_VideoResolution.Items.Add(item1);

            ComboBoxItem item2 = new ComboBoxItem();
            item2.Text = "352x288";
            item2.Value = "352x288";
            comboBox_VideoResolution.Items.Add(item2);

            ComboBoxItem item3 = new ComboBoxItem();
            item3.Text = "640x480";
            item3.Value = "640x480";
            comboBox_VideoResolution.Items.Add(item3);

            ComboBoxItem item4 = new ComboBoxItem();
            item4.Text = "800x600";
            item4.Value = "800x600";
            comboBox_VideoResolution.Items.Add(item4);

            ComboBoxItem item5 = new ComboBoxItem();
            item5.Text = "1280x720";
            item5.Value = "1280x720";
            comboBox_VideoResolution.Items.Add(item5);

            ComboBoxItem item6 = new ComboBoxItem();
            item6.Text = "1280x1024";
            item6.Value = "1280x1024";
            comboBox_VideoResolution.Items.Add(item6);

            ComboBoxItem item7 = new ComboBoxItem();
            item7.Text = "1920x1080";
            item7.Value = "1920x1080";
            comboBox_VideoResolution.Items.Add(item7);

            comboBox_VideoResolution.SelectedIndex = 0;
        }

        private void displayComboBoxControl(bool isDisplay)
        {
            comboBox_VideoResolution.Enabled = isDisplay;
            comboBox_VideoBitrate.Enabled = isDisplay;
            comboBox_VideoFPS.Enabled = isDisplay;
        }

        private void frmSetting_Load(object sender, EventArgs e)
        {
            initVideoDeviceItem();

            initVideoFPSItem();
            initVideoBitrateItem();
            initVideoVideoResolution();

            GetSetting();
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            displayComboBoxControl(!checkBox_serverConfig.Checked);
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (!checkBox_serverConfig.Checked)
            {
                ApplySetting();
            }
        }

        /// <summary>
        /// 应用设置
        /// </summary>
        private void ApplySetting()
        {
            int retCode = 0;
            int streamIdx = Int32.Parse((comboBox_videoDeviceList.SelectedItem as ComboBoxItem).Value.ToString());
            //streamIdx = streamIdx + 1;

            //设置码率
            int videoBitrate = 0;
            videoBitrate = Int32.Parse((comboBox_VideoBitrate.SelectedItem as ComboBoxItem).Value.ToString());
            //retCode = AnyChatCoreSDK.SetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_BITRATECTRL, ref videoBitrate, sizeof(int));
            retCode = AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_BITRATECTRL, ref videoBitrate, sizeof(int));


            //设置分辨率
            string videoResolution = string.Empty;
            videoResolution = (comboBox_VideoResolution.SelectedItem as ComboBoxItem).Value.ToString();
            string[] resolutionArray = videoResolution.Split('x');
            int videoWidth = Int32.Parse(resolutionArray[0]);
            int videoHeigth = Int32.Parse(resolutionArray[1]);
            //retCode = AnyChatCoreSDK.SetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_WIDTHCTRL, ref videoWidth, sizeof(int));
            retCode = AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_WIDTHCTRL, ref videoWidth, sizeof(int));
            //retCode = AnyChatCoreSDK.SetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, ref videoHeigth, sizeof(int));
            retCode = AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, ref videoHeigth, sizeof(int));

            //设置帧率
            int videoFPS = 0;
            videoFPS = Int32.Parse((comboBox_VideoFPS.SelectedItem as ComboBoxItem).Value.ToString());
            //retCode = AnyChatCoreSDK.SetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_FPSCTRL, ref videoFPS, sizeof(int));
            retCode = AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_FPSCTRL, ref videoFPS, sizeof(int));


            //让视频设置参数生效
            int isApply = 1;
            //retCode = AnyChatCoreSDK.SetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_APPLYPARAM, ref isApply, sizeof(int));
            retCode = AnyChatCoreSDK.SetSDKOption(AnyChatCoreSDK.BRAC_SO_LOCALVIDEO_APPLYPARAM, ref isApply, sizeof(int));

            //AnyChatCoreSDK.UserCameraControlEx(-1, false, streamIdx, 0, string.Empty);  
            //Thread.Sleep(500);
            //Application.DoEvents();
            //AnyChatCoreSDK.UserCameraControlEx(-1, true, streamIdx, 0, string.Empty);
        }


        private void GetSetting()
        {
            int retCode = 0;
            int streamIdx = Int32.Parse((comboBox_videoDeviceList.SelectedItem as ComboBoxItem).Value.ToString());
            //streamIdx = streamIdx + 1;

            AnyChatCoreSDK.SelectVideoCapture((comboBox_videoDeviceList.SelectedItem as ComboBoxItem).Text);

            int videoBitrate = 0;
            if (streamIdx == 100)
            {
                retCode = AnyChatCoreSDK.QueryUserState(-1, AnyChatCoreSDK.BRAC_USERSTATE_VIDEOBITRATE, ref videoBitrate, sizeof(int));
            }
            else
            {
                retCode = AnyChatCoreSDK.GetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_STREAMINFO_VIDEOBITRATE, ref videoBitrate, sizeof(int));
            }
            for (int idx = 0; idx < comboBox_VideoBitrate.Items.Count; idx++)
            {
                if ((videoBitrate >= Int32.Parse((comboBox_VideoBitrate.Items[idx] as ComboBoxItem).Value.ToString())) &&
                    (videoBitrate <= Int32.Parse((comboBox_VideoBitrate.Items[idx + 1] as ComboBoxItem).Value.ToString())))
                {
                    comboBox_VideoBitrate.SelectedIndex = idx;
                    break;
                }
            }

            //分辨率
            int videoWidth = 0;
            int videoHeigth = 0;
            retCode = AnyChatCoreSDK.GetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_STREAMINFO_VIDEOWIDTH, ref videoWidth, sizeof(int));
            retCode = AnyChatCoreSDK.GetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_STREAMINFO_VIDEOHEIGHT, ref videoHeigth, sizeof(int));
            string resolution = videoWidth.ToString() + "x" + videoHeigth;
            lblVideoResolution.Text = "(当前分辨率：	" + resolution +")";
            for (int idx = 0; idx < comboBox_VideoResolution.Items.Count; idx++)
            {
                if (resolution == (comboBox_VideoResolution.Items[idx] as ComboBoxItem).Text.ToString())
                {
                    comboBox_VideoResolution.SelectedIndex = idx;
                    break;
                }
            }


            //帧率
            int videoFPS = 0;
            //videoFPS = Int32.Parse((comboBox_VideoFPS.SelectedItem as ComboBoxItem).Value.ToString());
            retCode = AnyChatCoreSDK.GetUserStreamInfo(-1, streamIdx, AnyChatCoreSDK.BRAC_STREAMINFO_VIDEOFPS, ref videoFPS, sizeof(int));
            for (int idx = 0; idx < comboBox_VideoFPS.Items.Count; idx++ )
            {
                if (videoFPS.ToString() == (comboBox_VideoFPS.Items[idx] as ComboBoxItem).Value.ToString())
                {
                    comboBox_VideoFPS.SelectedIndex = idx;
                    break;
                }
            }

        }

        private void comboBox_videoDeviceList_SelectedIndexChanged(object sender, EventArgs e)
        {
            GetSetting();
        }
    }
}
