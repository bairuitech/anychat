namespace QueueClient
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
            this.lb_name = new System.Windows.Forms.Label();
            this.btn_login = new System.Windows.Forms.Button();
            this.lb_serveradd = new System.Windows.Forms.Label();
            this.lb_port = new System.Windows.Forms.Label();
            this.lbl_tipMessage = new System.Windows.Forms.Label();
            this.cbox_userIdentity = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.cbox_identityPriority = new System.Windows.Forms.ComboBox();
            this.cbox_serverIP = new System.Windows.Forms.ComboBox();
            this.cbox_port = new System.Windows.Forms.ComboBox();
            this.cbox_userName = new System.Windows.Forms.ComboBox();
            this.cbox_appGuid = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.rbtn_sign = new System.Windows.Forms.RadioButton();
            this.rbtn_normal = new System.Windows.Forms.RadioButton();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // lb_name
            // 
            this.lb_name.AutoSize = true;
            this.lb_name.Location = new System.Drawing.Point(42, 84);
            this.lb_name.Name = "lb_name";
            this.lb_name.Size = new System.Drawing.Size(68, 17);
            this.lb_name.TabIndex = 0;
            this.lb_name.Text = "用户身份：";
            // 
            // btn_login
            // 
            this.btn_login.Location = new System.Drawing.Point(158, 210);
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
            this.lb_serveradd.Location = new System.Drawing.Point(54, 19);
            this.lb_serveradd.Name = "lb_serveradd";
            this.lb_serveradd.Size = new System.Drawing.Size(56, 17);
            this.lb_serveradd.TabIndex = 3;
            this.lb_serveradd.Text = "服务器：";
            // 
            // lb_port
            // 
            this.lb_port.AutoSize = true;
            this.lb_port.Location = new System.Drawing.Point(66, 52);
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
            // cbox_userIdentity
            // 
            this.cbox_userIdentity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbox_userIdentity.FormattingEnabled = true;
            this.cbox_userIdentity.Items.AddRange(new object[] {
            "客户",
            "坐席"});
            this.cbox_userIdentity.Location = new System.Drawing.Point(116, 80);
            this.cbox_userIdentity.Name = "cbox_userIdentity";
            this.cbox_userIdentity.Size = new System.Drawing.Size(77, 25);
            this.cbox_userIdentity.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(54, 118);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 17);
            this.label1.TabIndex = 7;
            this.label1.Text = "用户名：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(204, 84);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 17);
            this.label2.TabIndex = 0;
            this.label2.Text = "优先级：";
            // 
            // cbox_identityPriority
            // 
            this.cbox_identityPriority.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbox_identityPriority.FormattingEnabled = true;
            this.cbox_identityPriority.Items.AddRange(new object[] {
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14"});
            this.cbox_identityPriority.Location = new System.Drawing.Point(258, 80);
            this.cbox_identityPriority.Name = "cbox_identityPriority";
            this.cbox_identityPriority.Size = new System.Drawing.Size(55, 25);
            this.cbox_identityPriority.TabIndex = 2;
            // 
            // cbox_serverIP
            // 
            this.cbox_serverIP.FormattingEnabled = true;
            this.cbox_serverIP.Location = new System.Drawing.Point(116, 15);
            this.cbox_serverIP.Name = "cbox_serverIP";
            this.cbox_serverIP.Size = new System.Drawing.Size(197, 25);
            this.cbox_serverIP.TabIndex = 10;
            // 
            // cbox_port
            // 
            this.cbox_port.FormattingEnabled = true;
            this.cbox_port.Location = new System.Drawing.Point(116, 48);
            this.cbox_port.Name = "cbox_port";
            this.cbox_port.Size = new System.Drawing.Size(197, 25);
            this.cbox_port.TabIndex = 11;
            // 
            // cbox_userName
            // 
            this.cbox_userName.FormattingEnabled = true;
            this.cbox_userName.Location = new System.Drawing.Point(116, 114);
            this.cbox_userName.Name = "cbox_userName";
            this.cbox_userName.Size = new System.Drawing.Size(197, 25);
            this.cbox_userName.TabIndex = 12;
            // 
            // cbox_appGuid
            // 
            this.cbox_appGuid.FormattingEnabled = true;
            this.cbox_appGuid.Location = new System.Drawing.Point(116, 145);
            this.cbox_appGuid.Name = "cbox_appGuid";
            this.cbox_appGuid.Size = new System.Drawing.Size(197, 25);
            this.cbox_appGuid.TabIndex = 14;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(54, 149);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 17);
            this.label3.TabIndex = 13;
            this.label3.Text = "应用ID：";
            // 
            // rbtn_sign
            // 
            this.rbtn_sign.AutoSize = true;
            this.rbtn_sign.Location = new System.Drawing.Point(239, 179);
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
            this.rbtn_normal.Location = new System.Drawing.Point(117, 179);
            this.rbtn_normal.Name = "rbtn_normal";
            this.rbtn_normal.Size = new System.Drawing.Size(74, 21);
            this.rbtn_normal.TabIndex = 19;
            this.rbtn_normal.TabStop = true;
            this.rbtn_normal.Text = "普通登录";
            this.rbtn_normal.UseVisualStyleBackColor = true;
            this.rbtn_normal.Click += new System.EventHandler(this.rbtn_normal_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(43, 181);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(68, 17);
            this.label4.TabIndex = 17;
            this.label4.Text = "登录方式：";
            // 
            // frmLogin
            // 
            this.AcceptButton = this.btn_login;
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 262);
            this.Controls.Add(this.rbtn_sign);
            this.Controls.Add(this.rbtn_normal);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.cbox_appGuid);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.cbox_userName);
            this.Controls.Add(this.cbox_port);
            this.Controls.Add(this.cbox_serverIP);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbox_identityPriority);
            this.Controls.Add(this.cbox_userIdentity);
            this.Controls.Add(this.lbl_tipMessage);
            this.Controls.Add(this.lb_port);
            this.Controls.Add(this.lb_serveradd);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btn_login);
            this.Controls.Add(this.lb_name);
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

        private System.Windows.Forms.Label lb_name;
        private System.Windows.Forms.Button btn_login;
        private System.Windows.Forms.Label lb_serveradd;
        private System.Windows.Forms.Label lb_port;
        private System.Windows.Forms.Label lbl_tipMessage;
        private System.Windows.Forms.ComboBox cbox_userIdentity;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cbox_identityPriority;
        private System.Windows.Forms.ComboBox cbox_serverIP;
        private System.Windows.Forms.ComboBox cbox_port;
        private System.Windows.Forms.ComboBox cbox_userName;
        private System.Windows.Forms.ComboBox cbox_appGuid;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.RadioButton rbtn_sign;
        private System.Windows.Forms.RadioButton rbtn_normal;
        private System.Windows.Forms.Label label4;
    }
}

