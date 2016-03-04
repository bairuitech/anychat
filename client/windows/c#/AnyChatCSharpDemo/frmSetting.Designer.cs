namespace ANYCHATAPI
{
    partial class frmSetting
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
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.checkBox_serverConfig = new System.Windows.Forms.CheckBox();
            this.comboBox_VideoResolution = new System.Windows.Forms.ComboBox();
            this.comboBox_VideoFPS = new System.Windows.Forms.ComboBox();
            this.comboBox_VideoBitrate = new System.Windows.Forms.ComboBox();
            this.comboBox_videoDeviceList = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnClose = new System.Windows.Forms.Button();
            this.lblVideoResolution = new System.Windows.Forms.Label();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(2, 3);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(439, 232);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.checkBox_serverConfig);
            this.tabPage1.Controls.Add(this.comboBox_VideoResolution);
            this.tabPage1.Controls.Add(this.comboBox_VideoFPS);
            this.tabPage1.Controls.Add(this.comboBox_VideoBitrate);
            this.tabPage1.Controls.Add(this.comboBox_videoDeviceList);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.lblVideoResolution);
            this.tabPage1.Controls.Add(this.label6);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(431, 206);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "视频参数设置";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // checkBox_serverConfig
            // 
            this.checkBox_serverConfig.AutoSize = true;
            this.checkBox_serverConfig.Checked = true;
            this.checkBox_serverConfig.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox_serverConfig.Location = new System.Drawing.Point(27, 46);
            this.checkBox_serverConfig.Name = "checkBox_serverConfig";
            this.checkBox_serverConfig.Size = new System.Drawing.Size(132, 16);
            this.checkBox_serverConfig.TabIndex = 2;
            this.checkBox_serverConfig.Text = "服务器配置参数优先";
            this.checkBox_serverConfig.UseVisualStyleBackColor = true;
            this.checkBox_serverConfig.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // comboBox_VideoResolution
            // 
            this.comboBox_VideoResolution.DropDownHeight = 120;
            this.comboBox_VideoResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_VideoResolution.FormattingEnabled = true;
            this.comboBox_VideoResolution.IntegralHeight = false;
            this.comboBox_VideoResolution.ItemHeight = 12;
            this.comboBox_VideoResolution.Location = new System.Drawing.Point(279, 74);
            this.comboBox_VideoResolution.Name = "comboBox_VideoResolution";
            this.comboBox_VideoResolution.Size = new System.Drawing.Size(123, 20);
            this.comboBox_VideoResolution.TabIndex = 1;
            // 
            // comboBox_VideoFPS
            // 
            this.comboBox_VideoFPS.DropDownHeight = 120;
            this.comboBox_VideoFPS.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_VideoFPS.FormattingEnabled = true;
            this.comboBox_VideoFPS.IntegralHeight = false;
            this.comboBox_VideoFPS.ItemHeight = 12;
            this.comboBox_VideoFPS.Location = new System.Drawing.Point(72, 98);
            this.comboBox_VideoFPS.Name = "comboBox_VideoFPS";
            this.comboBox_VideoFPS.Size = new System.Drawing.Size(123, 20);
            this.comboBox_VideoFPS.TabIndex = 1;
            // 
            // comboBox_VideoBitrate
            // 
            this.comboBox_VideoBitrate.DropDownHeight = 120;
            this.comboBox_VideoBitrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_VideoBitrate.FormattingEnabled = true;
            this.comboBox_VideoBitrate.IntegralHeight = false;
            this.comboBox_VideoBitrate.ItemHeight = 12;
            this.comboBox_VideoBitrate.Location = new System.Drawing.Point(72, 74);
            this.comboBox_VideoBitrate.Name = "comboBox_VideoBitrate";
            this.comboBox_VideoBitrate.Size = new System.Drawing.Size(123, 20);
            this.comboBox_VideoBitrate.TabIndex = 1;
            // 
            // comboBox_videoDeviceList
            // 
            this.comboBox_videoDeviceList.DropDownHeight = 120;
            this.comboBox_videoDeviceList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_videoDeviceList.FormattingEnabled = true;
            this.comboBox_videoDeviceList.IntegralHeight = false;
            this.comboBox_videoDeviceList.ItemHeight = 12;
            this.comboBox_videoDeviceList.Location = new System.Drawing.Point(120, 14);
            this.comboBox_videoDeviceList.Name = "comboBox_videoDeviceList";
            this.comboBox_videoDeviceList.Size = new System.Drawing.Size(261, 20);
            this.comboBox_videoDeviceList.TabIndex = 1;
            this.comboBox_videoDeviceList.SelectedIndexChanged += new System.EventHandler(this.comboBox_videoDeviceList_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(25, 101);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 0;
            this.label3.Text = "帧率：";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(220, 77);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 0;
            this.label6.Text = "分辨率：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(25, 77);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "码率：";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(25, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(89, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "选择视频设备：";
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(431, 206);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "音频参数设置";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // btnSave
            // 
            this.btnSave.Location = new System.Drawing.Point(115, 258);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 1;
            this.btnSave.Text = "保存";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(230, 258);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 23);
            this.btnClose.TabIndex = 1;
            this.btnClose.Text = "关闭";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // lblVideoResolution
            // 
            this.lblVideoResolution.AutoSize = true;
            this.lblVideoResolution.Location = new System.Drawing.Point(222, 101);
            this.lblVideoResolution.Name = "lblVideoResolution";
            this.lblVideoResolution.Size = new System.Drawing.Size(131, 12);
            this.lblVideoResolution.TabIndex = 0;
            this.lblVideoResolution.Text = "(当前分辨率：\t800x600)";
            // 
            // frmSetting
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(443, 307);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "frmSetting";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "frmSetting";
            this.Load += new System.EventHandler(this.frmSetting_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.ComboBox comboBox_videoDeviceList;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox checkBox_serverConfig;
        private System.Windows.Forms.ComboBox comboBox_VideoResolution;
        private System.Windows.Forms.ComboBox comboBox_VideoFPS;
        private System.Windows.Forms.ComboBox comboBox_VideoBitrate;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblVideoResolution;
    }
}