using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ANYCHATAPI;

namespace QueueServer
{
    public partial class frmTest : Form
    {
        public frmTest()
        {
            InitializeComponent();
        }

        private void btnGetRoomIdList_Click(object sender, EventArgs e)
        {
            int[] roomIDArray;

            int roomCount = 0;

            AnyChatServerSDK.BRAS_GetRoomIdList(null, ref roomCount);

            if (roomCount == 0)
            {

                this.rtxtBox_message.AppendText("未动态创建房间。\n");
                return;
            }

            roomIDArray = new int[roomCount];
            AnyChatServerSDK.BRAS_GetRoomIdList(roomIDArray,ref roomCount);

            for (int idx = 0; idx < roomCount; idx++)
            {
                this.rtxtBox_message.AppendText("房间ID为：" + roomIDArray[idx] + "\n");
            }

        }

        private void btnGetOnlineUsers_Click(object sender, EventArgs e)
        {
            int roomID = 0;
            int[] userIDArray;

            int userCount = 0;

            if (string.IsNullOrEmpty(txtBoxRoomID.Text))
            {
                this.rtxtBox_message.AppendText("房间号输入框不能为空！\n");
                return;
            }
            try
            {
                roomID = Int32.Parse(txtBoxRoomID.Text);
            }
            catch(Exception exp)
            {
                this.rtxtBox_message.AppendText("房间号转换出错：" + exp.Message + "\n");
                return;
            }

            AnyChatServerSDK.BRAS_GetOnlineUsers(roomID, null, ref userCount);
            if (userCount ==0)
            {
            
                this.rtxtBox_message.AppendText("没有用户登录系统。\n");
                return;
            }

            userIDArray = new int[userCount];

            AnyChatServerSDK.BRAS_GetOnlineUsers(roomID, userIDArray, ref  userCount);


            for (int idx = 0; idx < userCount; idx++)
            {
                this.rtxtBox_message.AppendText("用户ID为：" + userIDArray[idx] + "\n");
            }
        }

        private void btnClearLog_Click(object sender, EventArgs e)
        {
            rtxtBox_message.Clear();
        }

        private void btnQueryInfoFromServer_Click(object sender, EventArgs e)
        {
            StringBuilder sbInParams = new StringBuilder(512);
            StringBuilder sbResult = new StringBuilder(512);
            int outSize = 0;

            int errorcode = AnyChatServerSDK.BRAS_QueryInfoFromServer(0, sbInParams, 0, sbResult, ref outSize, 0);

            if (errorcode == 0)
            {
                this.rtxtBox_message.AppendText("调用BRAS_QueryInfoFromServer接口成功！\n");

            }
            else
            {
                this.rtxtBox_message.AppendText("调用BRAS_QueryInfoFromServer接口失败，返回值为：" + errorcode +"\n");

            }
        }
    }
}
