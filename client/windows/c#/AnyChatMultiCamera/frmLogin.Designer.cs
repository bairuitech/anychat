namespace AnyChatMultiCamera
{
    partial class frmLogin
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmLogin));
            this.btn_login = new System.Windows.Forms.Button();
            this.lb_serveradd = new System.Windows.Forms.Label();
            this.lb_port = new System.Windows.Forms.Label();
            this.lbl_tipMessage = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cbox_roomNumber = new System.Windows.Forms.ComboBox();
            this.cbox_serverIP = new System.Windows.Forms.ComboBox();
            this.cbox_port = new System.Windows.Forms.ComboBox();
            this.cbox_userName = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txt_password = new System.Windows.Forms.TextBox();
            this.checkBox_RemoteDesktop = new System.Windows.Forms.CheckBox();
            this.cbox_appGuid = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.rbtn_sign = new System.Windows.Forms.RadioButton();
            this.rbtn_normal = new System.Windows.Forms.RadioButton();
            this.label5 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btn_login
            // 
            this.btn_login.Location = new System.Drawing.Point(158, 207);
            this.btn_login.Name = "btn_login";
            this.btn_login.Size = new System.Drawing.Size(75, 23);
            this.btn_login.TabIndex = 3;
            this.btn_login.Text = "登录";
            this.btn_login.UseVisualStyleBackColor = true;
            this.btn_login.Click += new System.EventHandler(this.btn_login_Click);
            // 
            // lb_serveradd
            // 
            this.lb_serveradd.AutoSize = true;
            this.lb_serveradd.Location = new System.Drawing.Point(55, 20);
            this.lb_serveradd.Name = "lb_serveradd";
            this.lb_serveradd.Size = new System.Drawing.Size(56, 17);
            this.lb_serveradd.TabIndex = 3;
            this.lb_serveradd.Text = "服务器：";
            // 
            // lb_port
            // 
            this.lb_port.AutoSize = true;
            this.lb_port.Location = new System.Drawing.Point(67, 52);
            this.lb_port.Name = "lb_port";
            this.lb_port.Size = new System.Drawing.Size(44, 17);
            this.lb_port.TabIndex = 5;
            this.lb_port.Text = "端口：";
            // 
            // lbl_tipMessage
            // 
            this.lbl_tipMessage.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.lbl_tipMessage.Location = new System.Drawing.Point(0, 245);
            this.lbl_tipMessage.Name = "lbl_tipMessage";
            this.lbl_tipMessage.Size = new System.Drawing.Size(384, 17);
            this.lbl_tipMessage.TabIndex = 6;
            this.lbl_tipMessage.Text = "message";
            this.lbl_tipMessage.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lbl_tipMessage.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(55, 84);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 17);
            this.label1.TabIndex = 7;
            this.label1.Text = "用户名：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(205, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 17);
            this.label2.TabIndex = 0;
            this.label2.Text = "房间号：";
            // 
            // cbox_roomNumber
            // 
            this.cbox_roomNumber.FormattingEnabled = true;
            this.cbox_roomNumber.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4"});
            this.cbox_roomNumber.Location = new System.Drawing.Point(259, 49);
            this.cbox_roomNumber.Name = "cbox_roomNumber";
            this.cbox_roomNumber.Size = new System.Drawing.Size(55, 25);
            this.cbox_roomNumber.TabIndex = 2;
            // 
            // cbox_serverIP
            // 
            this.cbox_serverIP.FormattingEnabled = true;
            this.cbox_serverIP.Location = new System.Drawing.Point(117, 16);
            this.cbox_serverIP.Name = "cbox_serverIP";
            this.cbox_serverIP.Size = new System.Drawing.Size(197, 25);
            this.cbox_serverIP.TabIndex = 10;
            // 
            // cbox_port
            // 
            this.cbox_port.FormattingEnabled = true;
            this.cbox_port.Location = new System.Drawing.Point(117, 48);
            this.cbox_port.Name = "cbox_port";
            this.cbox_port.Size = new System.Drawing.Size(77, 25);
            this.cbox_port.TabIndex = 11;
            // 
            // cbox_userName
            // 
            this.cbox_userName.FormattingEnabled = true;
            this.cbox_userName.Location = new System.Drawing.Point(117, 80);
            this.cbox_userName.Name = "cbox_userName";
            this.cbox_userName.Size = new System.Drawing.Size(197, 25);
            this.cbox_userName.TabIndex = 12;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(67, 116);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 17);
            this.label3.TabIndex = 7;
            this.label3.Text = "密码：";
            // 
            // txt_password
            // 
            this.txt_password.Location = new System.Drawing.Point(117, 113);
            this.txt_password.Name = "txt_password";
            this.txt_password.PasswordChar = '*';
            this.txt_password.Size = new System.Drawing.Size(77, 23);
            this.txt_password.TabIndex = 13;
            // 
            // checkBox_RemoteDesktop
            // 
            this.checkBox_RemoteDesktop.AutoSize = true;
            this.checkBox_RemoteDesktop.Location = new System.Drawing.Point(225, 116);
            this.checkBox_RemoteDesktop.Name = "checkBox_RemoteDesktop";
            this.checkBox_RemoteDesktop.Size = new System.Drawing.Size(99, 21);
            this.checkBox_RemoteDesktop.TabIndex = 14;
            this.checkBox_RemoteDesktop.Text = "打开屏幕共享";
            this.checkBox_RemoteDesktop.UseVisualStyleBackColor = true;
            // 
            // cbox_appGuid
            // 
            this.cbox_appGuid.FormattingEnabled = true;
            this.cbox_appGuid.Location = new System.Drawing.Point(117, 145);
            this.cbox_appGuid.Name = "cbox_appGuid";
            this.cbox_appGuid.Size = new System.Drawing.Size(197, 25);
            this.cbox_appGuid.TabIndex = 16;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(55, 149);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(57, 17);
            this.label4.TabIndex = 15;
            this.label4.Text = "应用ID：";
            // 
            // rbtn_sign
            // 
            this.rbtn_sign.AutoSize = true;
            this.rbtn_sign.Location = new System.Drawing.Point(240, 178);
            this.rbtn_sign.Name = "rbtn_sign";
            this.rbtn_sign.Size = new System.Drawing.Size(74, 21);
            this.rbtn_sign.TabIndex = 18;
            this.rbtn_sign.Text = "签名登录";
            this.rbtn_sign.UseVisualStyleBackColor = true;
            this.rbtn_sign.Click += new System.EventHandler(this.rbtn_sign_Click);
            // 
            // rbtn_normal
            // 
            this.rbtn_normal.AutoSize = true;
            this.rbtn_normal.Checked = true;
            this.rbtn_normal.Location = new System.Drawing.Point(117, 178);
            this.rbtn_normal.Name = "rbtn_normal";
            this.rbtn_normal.Size = new System.Drawing.Size(74, 21);
            this.rbtn_normal.TabIndex = 19;
            this.rbtn_normal.TabStop = true;
            this.rbtn_normal.Text = "普通登录";
            this.rbtn_normal.UseVisualStyleBackColor = true;
            this.rbtn_normal.CheckedChanged += new System.EventHandler(this.rbtn_normal_CheckedChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(43, 180);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(68, 17);
            this.label5.TabIndex = 17;
            this.label5.Text = "登录方式：";
            // 
            // frmLogin
            // 
            this.AcceptButton = this.btn_login;
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 262);
            this.Controls.Add(this.rbtn_sign);
            this.Controls.Add(this.rbtn_normal);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.cbox_appGuid);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.checkBox_RemoteDesktop);
            this.Controls.Add(this.txt_password);
            this.Controls.Add(this.cbox_userName);
            this.Controls.Add(this.cbox_port);
            this.Controls.Add(this.cbox_serverIP);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbox_roomNumber);
            this.Controls.Add(this.lbl_tipMessage);
            this.Controls.Add(this.lb_port);
            this.Controls.Add(this.lb_serveradd);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btn_login);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(400, 300);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(400, 300);
            this.Name = "frmLogin";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "登录";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Login_FormClosed);
            this.Load += new System.EventHandler(this.Login_Load);
            this.VisibleChanged += new System.EventHandler(this.frmLogin_VisibleChanged);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_login;
        private System.Windows.Forms.Label lb_serveradd;
        private System.Windows.Forms.Label lb_port;
        private System.Windows.Forms.Label lbl_tipMessage;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cbox_roomNumber;
        private System.Windows.Forms.ComboBox cbox_serverIP;
        private System.Windows.Forms.ComboBox cbox_port;
        private System.Windows.Forms.ComboBox cbox_userName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txt_password;
        private System.Windows.Forms.CheckBox checkBox_RemoteDesktop;
        private System.Windows.Forms.ComboBox cbox_appGuid;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.RadioButton rbtn_sign;
        private System.Windows.Forms.RadioButton rbtn_normal;
        private System.Windows.Forms.Label label5;
    }
}

