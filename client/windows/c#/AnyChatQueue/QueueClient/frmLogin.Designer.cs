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
            this.btn_login.Location = new System.Drawing.Point(158, 164);
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
            this.lbl_tipMessage.Location = new System.Drawing.Point(0, 214);
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
            // frmLogin
            // 
            this.AcceptButton = this.btn_login;
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 231);
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
            this.MinimizeBox = false;
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
    }
}

