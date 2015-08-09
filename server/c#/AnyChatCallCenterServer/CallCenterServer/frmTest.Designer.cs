namespace QueueServer
{
    partial class frmTest
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnQueryInfoFromServer = new System.Windows.Forms.Button();
            this.btnClearLog = new System.Windows.Forms.Button();
            this.txtBoxRoomID = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnGetOnlineUsers = new System.Windows.Forms.Button();
            this.btnGetRoomIdList = new System.Windows.Forms.Button();
            this.gb_serverLogs = new System.Windows.Forms.GroupBox();
            this.rtxtBox_message = new System.Windows.Forms.RichTextBox();
            this.groupBox1.SuspendLayout();
            this.gb_serverLogs.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnQueryInfoFromServer);
            this.groupBox1.Controls.Add(this.btnClearLog);
            this.groupBox1.Controls.Add(this.txtBoxRoomID);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.btnGetOnlineUsers);
            this.groupBox1.Controls.Add(this.btnGetRoomIdList);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Left;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(328, 465);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "功能测试";
            // 
            // btnQueryInfoFromServer
            // 
            this.btnQueryInfoFromServer.Location = new System.Drawing.Point(14, 102);
            this.btnQueryInfoFromServer.Name = "btnQueryInfoFromServer";
            this.btnQueryInfoFromServer.Size = new System.Drawing.Size(138, 23);
            this.btnQueryInfoFromServer.TabIndex = 4;
            this.btnQueryInfoFromServer.Text = "向服务器动态查询信息";
            this.btnQueryInfoFromServer.UseVisualStyleBackColor = true;
            this.btnQueryInfoFromServer.Click += new System.EventHandler(this.btnQueryInfoFromServer_Click);
            // 
            // btnClearLog
            // 
            this.btnClearLog.Location = new System.Drawing.Point(164, 20);
            this.btnClearLog.Name = "btnClearLog";
            this.btnClearLog.Size = new System.Drawing.Size(140, 23);
            this.btnClearLog.TabIndex = 3;
            this.btnClearLog.Text = "清空日志";
            this.btnClearLog.UseVisualStyleBackColor = true;
            this.btnClearLog.Click += new System.EventHandler(this.btnClearLog_Click);
            // 
            // txtBoxRoomID
            // 
            this.txtBoxRoomID.Location = new System.Drawing.Point(69, 62);
            this.txtBoxRoomID.Name = "txtBoxRoomID";
            this.txtBoxRoomID.Size = new System.Drawing.Size(83, 21);
            this.txtBoxRoomID.TabIndex = 2;
            this.txtBoxRoomID.Text = "-1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 67);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "房间号：";
            // 
            // btnGetOnlineUsers
            // 
            this.btnGetOnlineUsers.Location = new System.Drawing.Point(164, 62);
            this.btnGetOnlineUsers.Name = "btnGetOnlineUsers";
            this.btnGetOnlineUsers.Size = new System.Drawing.Size(140, 23);
            this.btnGetOnlineUsers.TabIndex = 0;
            this.btnGetOnlineUsers.Text = "获取房间在线用户列表";
            this.btnGetOnlineUsers.UseVisualStyleBackColor = true;
            this.btnGetOnlineUsers.Click += new System.EventHandler(this.btnGetOnlineUsers_Click);
            // 
            // btnGetRoomIdList
            // 
            this.btnGetRoomIdList.Location = new System.Drawing.Point(12, 20);
            this.btnGetRoomIdList.Name = "btnGetRoomIdList";
            this.btnGetRoomIdList.Size = new System.Drawing.Size(140, 23);
            this.btnGetRoomIdList.TabIndex = 0;
            this.btnGetRoomIdList.Text = "获取房间ID列表";
            this.btnGetRoomIdList.UseVisualStyleBackColor = true;
            this.btnGetRoomIdList.Click += new System.EventHandler(this.btnGetRoomIdList_Click);
            // 
            // gb_serverLogs
            // 
            this.gb_serverLogs.Controls.Add(this.rtxtBox_message);
            this.gb_serverLogs.Dock = System.Windows.Forms.DockStyle.Fill;
            this.gb_serverLogs.Location = new System.Drawing.Point(328, 0);
            this.gb_serverLogs.Name = "gb_serverLogs";
            this.gb_serverLogs.Size = new System.Drawing.Size(410, 465);
            this.gb_serverLogs.TabIndex = 6;
            this.gb_serverLogs.TabStop = false;
            this.gb_serverLogs.Text = "Server Logs";
            // 
            // rtxtBox_message
            // 
            this.rtxtBox_message.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rtxtBox_message.Location = new System.Drawing.Point(3, 17);
            this.rtxtBox_message.Name = "rtxtBox_message";
            this.rtxtBox_message.ReadOnly = true;
            this.rtxtBox_message.Size = new System.Drawing.Size(404, 445);
            this.rtxtBox_message.TabIndex = 0;
            this.rtxtBox_message.Text = "";
            // 
            // frmTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(738, 465);
            this.Controls.Add(this.gb_serverLogs);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmTest";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "测试窗口（内测使用）";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.gb_serverLogs.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox txtBoxRoomID;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnGetOnlineUsers;
        private System.Windows.Forms.Button btnGetRoomIdList;
        private System.Windows.Forms.GroupBox gb_serverLogs;
        private System.Windows.Forms.RichTextBox rtxtBox_message;
        private System.Windows.Forms.Button btnClearLog;
        private System.Windows.Forms.Button btnQueryInfoFromServer;
    }
}