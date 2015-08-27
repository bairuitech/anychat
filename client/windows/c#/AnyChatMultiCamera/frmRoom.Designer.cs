namespace AnyChatMultiCamera
{
    partial class frmRoom2
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmRoom2));
            this.panel_Center_Top = new System.Windows.Forms.Panel();
            this.groupBox_RemoteVideo = new System.Windows.Forms.GroupBox();
            this.panel_OtherVideoZone = new System.Windows.Forms.Panel();
            this.panel_Center = new System.Windows.Forms.Panel();
            this.panel_Center_Bottom = new System.Windows.Forms.Panel();
            this.groupBox_LocalVideo = new System.Windows.Forms.GroupBox();
            this.panel_OwnerVideoZone = new System.Windows.Forms.Panel();
            this.panel_Center_Bottom_Log = new System.Windows.Forms.Panel();
            this.txt_OutputMessage = new System.Windows.Forms.RichTextBox();
            this.panel_Center_Bottom_OptZone = new System.Windows.Forms.Panel();
            this.label_radio4 = new System.Windows.Forms.Label();
            this.label_radio3 = new System.Windows.Forms.Label();
            this.label_radio2 = new System.Windows.Forms.Label();
            this.label_radio1 = new System.Windows.Forms.Label();
            this.btnSetting = new System.Windows.Forms.Button();
            this.btnLeaveRoom = new System.Windows.Forms.Button();
            this.panel_Left = new System.Windows.Forms.Panel();
            this.dgv_onlineuser = new System.Windows.Forms.DataGridView();
            this.gvc_character = new System.Windows.Forms.DataGridViewImageColumn();
            this.gvc_userID = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.gvc_username = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.gvc_audio = new System.Windows.Forms.DataGridViewImageColumn();
            this.gvc_video = new System.Windows.Forms.DataGridViewImageColumn();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.panel_Center_Top.SuspendLayout();
            this.groupBox_RemoteVideo.SuspendLayout();
            this.panel_Center.SuspendLayout();
            this.panel_Center_Bottom.SuspendLayout();
            this.groupBox_LocalVideo.SuspendLayout();
            this.panel_Center_Bottom_Log.SuspendLayout();
            this.panel_Center_Bottom_OptZone.SuspendLayout();
            this.panel_Left.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_onlineuser)).BeginInit();
            this.SuspendLayout();
            // 
            // panel_Center_Top
            // 
            this.panel_Center_Top.Controls.Add(this.groupBox_RemoteVideo);
            this.panel_Center_Top.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel_Center_Top.Location = new System.Drawing.Point(0, 0);
            this.panel_Center_Top.Name = "panel_Center_Top";
            this.panel_Center_Top.Size = new System.Drawing.Size(757, 282);
            this.panel_Center_Top.TabIndex = 2;
            // 
            // groupBox_RemoteVideo
            // 
            this.groupBox_RemoteVideo.Controls.Add(this.panel_OtherVideoZone);
            this.groupBox_RemoteVideo.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox_RemoteVideo.Location = new System.Drawing.Point(0, 0);
            this.groupBox_RemoteVideo.Name = "groupBox_RemoteVideo";
            this.groupBox_RemoteVideo.Size = new System.Drawing.Size(757, 282);
            this.groupBox_RemoteVideo.TabIndex = 2;
            this.groupBox_RemoteVideo.TabStop = false;
            this.groupBox_RemoteVideo.Text = "远程视频显示区域";
            // 
            // panel_OtherVideoZone
            // 
            this.panel_OtherVideoZone.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel_OtherVideoZone.Location = new System.Drawing.Point(3, 17);
            this.panel_OtherVideoZone.Name = "panel_OtherVideoZone";
            this.panel_OtherVideoZone.Size = new System.Drawing.Size(751, 262);
            this.panel_OtherVideoZone.TabIndex = 2;
            // 
            // panel_Center
            // 
            this.panel_Center.Controls.Add(this.panel_Center_Bottom);
            this.panel_Center.Controls.Add(this.panel_Center_Top);
            this.panel_Center.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel_Center.Location = new System.Drawing.Point(251, 0);
            this.panel_Center.Name = "panel_Center";
            this.panel_Center.Size = new System.Drawing.Size(757, 730);
            this.panel_Center.TabIndex = 1;
            // 
            // panel_Center_Bottom
            // 
            this.panel_Center_Bottom.Controls.Add(this.groupBox_LocalVideo);
            this.panel_Center_Bottom.Controls.Add(this.panel_Center_Bottom_Log);
            this.panel_Center_Bottom.Controls.Add(this.panel_Center_Bottom_OptZone);
            this.panel_Center_Bottom.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel_Center_Bottom.Location = new System.Drawing.Point(0, 282);
            this.panel_Center_Bottom.Name = "panel_Center_Bottom";
            this.panel_Center_Bottom.Size = new System.Drawing.Size(757, 448);
            this.panel_Center_Bottom.TabIndex = 3;
            // 
            // groupBox_LocalVideo
            // 
            this.groupBox_LocalVideo.Controls.Add(this.panel_OwnerVideoZone);
            this.groupBox_LocalVideo.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox_LocalVideo.Location = new System.Drawing.Point(0, 0);
            this.groupBox_LocalVideo.Name = "groupBox_LocalVideo";
            this.groupBox_LocalVideo.Size = new System.Drawing.Size(609, 315);
            this.groupBox_LocalVideo.TabIndex = 4;
            this.groupBox_LocalVideo.TabStop = false;
            this.groupBox_LocalVideo.Text = "本地视频显示区域";
            // 
            // panel_OwnerVideoZone
            // 
            this.panel_OwnerVideoZone.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel_OwnerVideoZone.Location = new System.Drawing.Point(3, 17);
            this.panel_OwnerVideoZone.Name = "panel_OwnerVideoZone";
            this.panel_OwnerVideoZone.Size = new System.Drawing.Size(603, 295);
            this.panel_OwnerVideoZone.TabIndex = 5;
            // 
            // panel_Center_Bottom_Log
            // 
            this.panel_Center_Bottom_Log.Controls.Add(this.txt_OutputMessage);
            this.panel_Center_Bottom_Log.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel_Center_Bottom_Log.Location = new System.Drawing.Point(0, 315);
            this.panel_Center_Bottom_Log.Name = "panel_Center_Bottom_Log";
            this.panel_Center_Bottom_Log.Size = new System.Drawing.Size(609, 133);
            this.panel_Center_Bottom_Log.TabIndex = 3;
            // 
            // txt_OutputMessage
            // 
            this.txt_OutputMessage.BackColor = System.Drawing.Color.White;
            this.txt_OutputMessage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txt_OutputMessage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txt_OutputMessage.Location = new System.Drawing.Point(0, 0);
            this.txt_OutputMessage.Name = "txt_OutputMessage";
            this.txt_OutputMessage.Size = new System.Drawing.Size(609, 133);
            this.txt_OutputMessage.TabIndex = 1;
            this.txt_OutputMessage.Text = "";
            // 
            // panel_Center_Bottom_OptZone
            // 
            this.panel_Center_Bottom_OptZone.Controls.Add(this.label_radio4);
            this.panel_Center_Bottom_OptZone.Controls.Add(this.label_radio3);
            this.panel_Center_Bottom_OptZone.Controls.Add(this.label_radio2);
            this.panel_Center_Bottom_OptZone.Controls.Add(this.label_radio1);
            this.panel_Center_Bottom_OptZone.Controls.Add(this.btnSetting);
            this.panel_Center_Bottom_OptZone.Controls.Add(this.btnLeaveRoom);
            this.panel_Center_Bottom_OptZone.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel_Center_Bottom_OptZone.Location = new System.Drawing.Point(609, 0);
            this.panel_Center_Bottom_OptZone.Name = "panel_Center_Bottom_OptZone";
            this.panel_Center_Bottom_OptZone.Size = new System.Drawing.Size(148, 448);
            this.panel_Center_Bottom_OptZone.TabIndex = 0;
            // 
            // label_radio4
            // 
            this.label_radio4.AutoSize = true;
            this.label_radio4.Location = new System.Drawing.Point(8, 305);
            this.label_radio4.Name = "label_radio4";
            this.label_radio4.Size = new System.Drawing.Size(77, 12);
            this.label_radio4.TabIndex = 3;
            this.label_radio4.Tag = "3";
            this.label_radio4.Text = "label_radio4";
            // 
            // label_radio3
            // 
            this.label_radio3.AutoSize = true;
            this.label_radio3.Location = new System.Drawing.Point(8, 279);
            this.label_radio3.Name = "label_radio3";
            this.label_radio3.Size = new System.Drawing.Size(77, 12);
            this.label_radio3.TabIndex = 3;
            this.label_radio3.Tag = "3";
            this.label_radio3.Text = "label_radio3";
            // 
            // label_radio2
            // 
            this.label_radio2.AutoSize = true;
            this.label_radio2.Location = new System.Drawing.Point(8, 254);
            this.label_radio2.Name = "label_radio2";
            this.label_radio2.Size = new System.Drawing.Size(77, 12);
            this.label_radio2.TabIndex = 2;
            this.label_radio2.Tag = "2";
            this.label_radio2.Text = "label_radio2";
            // 
            // label_radio1
            // 
            this.label_radio1.AutoSize = true;
            this.label_radio1.Location = new System.Drawing.Point(8, 225);
            this.label_radio1.Name = "label_radio1";
            this.label_radio1.Size = new System.Drawing.Size(77, 12);
            this.label_radio1.TabIndex = 1;
            this.label_radio1.Tag = "1";
            this.label_radio1.Text = "label_radio1";
            // 
            // btnSetting
            // 
            this.btnSetting.Location = new System.Drawing.Point(16, 111);
            this.btnSetting.Name = "btnSetting";
            this.btnSetting.Size = new System.Drawing.Size(120, 36);
            this.btnSetting.TabIndex = 0;
            this.btnSetting.Text = "高级设置";
            this.btnSetting.UseVisualStyleBackColor = true;
            this.btnSetting.Click += new System.EventHandler(this.btnSetting_Click);
            // 
            // btnLeaveRoom
            // 
            this.btnLeaveRoom.Location = new System.Drawing.Point(16, 44);
            this.btnLeaveRoom.Name = "btnLeaveRoom";
            this.btnLeaveRoom.Size = new System.Drawing.Size(120, 36);
            this.btnLeaveRoom.TabIndex = 0;
            this.btnLeaveRoom.Text = "返回";
            this.btnLeaveRoom.UseVisualStyleBackColor = true;
            this.btnLeaveRoom.Click += new System.EventHandler(this.btnLeaveRoom_Click);
            // 
            // panel_Left
            // 
            this.panel_Left.Controls.Add(this.dgv_onlineuser);
            this.panel_Left.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel_Left.Location = new System.Drawing.Point(0, 0);
            this.panel_Left.Name = "panel_Left";
            this.panel_Left.Size = new System.Drawing.Size(251, 730);
            this.panel_Left.TabIndex = 0;
            // 
            // dgv_onlineuser
            // 
            this.dgv_onlineuser.AllowUserToAddRows = false;
            this.dgv_onlineuser.AllowUserToDeleteRows = false;
            this.dgv_onlineuser.AllowUserToResizeColumns = false;
            this.dgv_onlineuser.AllowUserToResizeRows = false;
            this.dgv_onlineuser.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dgv_onlineuser.BackgroundColor = System.Drawing.Color.White;
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle5.BackColor = System.Drawing.Color.LightSeaGreen;
            dataGridViewCellStyle5.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle5.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle5.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle5.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle5.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dgv_onlineuser.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle5;
            this.dgv_onlineuser.ColumnHeadersHeight = 30;
            this.dgv_onlineuser.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.gvc_character,
            this.gvc_userID,
            this.gvc_username,
            this.gvc_audio,
            this.gvc_video});
            this.dgv_onlineuser.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgv_onlineuser.Location = new System.Drawing.Point(0, 0);
            this.dgv_onlineuser.MultiSelect = false;
            this.dgv_onlineuser.Name = "dgv_onlineuser";
            this.dgv_onlineuser.ReadOnly = true;
            this.dgv_onlineuser.RowHeadersVisible = false;
            this.dgv_onlineuser.RowHeadersWidth = 30;
            this.dgv_onlineuser.RowTemplate.DefaultCellStyle.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.dgv_onlineuser.RowTemplate.Height = 30;
            this.dgv_onlineuser.RowTemplate.ReadOnly = true;
            this.dgv_onlineuser.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgv_onlineuser.Size = new System.Drawing.Size(251, 730);
            this.dgv_onlineuser.TabIndex = 6;
            this.dgv_onlineuser.Click += new System.EventHandler(this.dgv_onlineuser_Click);
            // 
            // gvc_character
            // 
            this.gvc_character.FillWeight = 20F;
            this.gvc_character.HeaderText = "";
            this.gvc_character.ImageLayout = System.Windows.Forms.DataGridViewImageCellLayout.Zoom;
            this.gvc_character.Name = "gvc_character";
            this.gvc_character.ReadOnly = true;
            this.gvc_character.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.gvc_character.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.gvc_character.Width = 34;
            // 
            // gvc_userID
            // 
            this.gvc_userID.HeaderText = "ID";
            this.gvc_userID.Name = "gvc_userID";
            this.gvc_userID.ReadOnly = true;
            this.gvc_userID.Visible = false;
            // 
            // gvc_username
            // 
            this.gvc_username.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            this.gvc_username.DefaultCellStyle = dataGridViewCellStyle6;
            this.gvc_username.HeaderText = "账号";
            this.gvc_username.Name = "gvc_username";
            this.gvc_username.ReadOnly = true;
            // 
            // gvc_audio
            // 
            this.gvc_audio.HeaderText = "音频";
            this.gvc_audio.Name = "gvc_audio";
            this.gvc_audio.ReadOnly = true;
            this.gvc_audio.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.gvc_audio.ToolTipText = "音频";
            this.gvc_audio.Width = 40;
            // 
            // gvc_video
            // 
            this.gvc_video.HeaderText = "视频";
            this.gvc_video.Name = "gvc_video";
            this.gvc_video.ReadOnly = true;
            this.gvc_video.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.gvc_video.ToolTipText = "视频";
            this.gvc_video.Width = 40;
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // frmRoom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 730);
            this.Controls.Add(this.panel_Center);
            this.Controls.Add(this.panel_Left);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "frmRoom";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "多路音视频输入示例程序";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.frmRoom_FormClosed);
            this.Load += new System.EventHandler(this.frmRoom_Load);
            this.Shown += new System.EventHandler(this.frmRoom_Shown);
            this.panel_Center_Top.ResumeLayout(false);
            this.groupBox_RemoteVideo.ResumeLayout(false);
            this.panel_Center.ResumeLayout(false);
            this.panel_Center_Bottom.ResumeLayout(false);
            this.groupBox_LocalVideo.ResumeLayout(false);
            this.panel_Center_Bottom_Log.ResumeLayout(false);
            this.panel_Center_Bottom_OptZone.ResumeLayout(false);
            this.panel_Center_Bottom_OptZone.PerformLayout();
            this.panel_Left.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgv_onlineuser)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel_Center;
        private System.Windows.Forms.Panel panel_Left;
        private System.Windows.Forms.Panel panel_Center_Top;
        private System.Windows.Forms.DataGridView dgv_onlineuser;
        private System.Windows.Forms.DataGridViewImageColumn gvc_character;
        private System.Windows.Forms.DataGridViewTextBoxColumn gvc_userID;
        private System.Windows.Forms.DataGridViewTextBoxColumn gvc_username;
        private System.Windows.Forms.DataGridViewImageColumn gvc_audio;
        private System.Windows.Forms.DataGridViewImageColumn gvc_video;
        private System.Windows.Forms.Panel panel_Center_Bottom;
        private System.Windows.Forms.Panel panel_Center_Bottom_OptZone;
        private System.Windows.Forms.Button btnSetting;
        private System.Windows.Forms.Button btnLeaveRoom;
        private System.Windows.Forms.Panel panel_Center_Bottom_Log;
        private System.Windows.Forms.RichTextBox txt_OutputMessage;
        private System.Windows.Forms.Label label_radio3;
        private System.Windows.Forms.Label label_radio2;
        private System.Windows.Forms.Label label_radio1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label label_radio4;
        private System.Windows.Forms.GroupBox groupBox_RemoteVideo;
        private System.Windows.Forms.Panel panel_OtherVideoZone;
        private System.Windows.Forms.GroupBox groupBox_LocalVideo;
        private System.Windows.Forms.Panel panel_OwnerVideoZone;
    }
}