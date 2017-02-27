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
            this.pnl_selectSkill = new System.Windows.Forms.Panel();
            this.chkBox_skill_loan = new System.Windows.Forms.CheckBox();
            this.chkBox_skill_finance = new System.Windows.Forms.CheckBox();
            this.chkBox_skill_cash = new System.Windows.Forms.CheckBox();
            this.label3 = new System.Windows.Forms.Label();
            this.pnl_AutoRouter = new System.Windows.Forms.Panel();
            this.lbl_router = new System.Windows.Forms.Label();
            this.cmbBox_Router = new System.Windows.Forms.ComboBox();
            this.pnl_selectSkill.SuspendLayout();
            this.pnl_AutoRouter.SuspendLayout();
            this.SuspendLayout();
            // 
            // lb_name
            // 
            this.lb_name.AutoSize = true;
            this.lb_name.Location = new System.Drawing.Point(42, 88);
            this.lb_name.Name = "lb_name";
            this.lb_name.Size = new System.Drawing.Size(68, 17);
            this.lb_name.TabIndex = 0;
            this.lb_name.Text = "用户身份：";
            // 
            // btn_login
            // 
            this.btn_login.Location = new System.Drawing.Point(153, 184);
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
            this.lbl_tipMessage.Location = new System.Drawing.Point(0, 227);
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
            this.cbox_userIdentity.Location = new System.Drawing.Point(116, 84);
            this.cbox_userIdentity.Name = "cbox_userIdentity";
            this.cbox_userIdentity.Size = new System.Drawing.Size(77, 25);
            this.cbox_userIdentity.TabIndex = 2;
            this.cbox_userIdentity.SelectedValueChanged += new System.EventHandler(this.cbox_userIdentity_SelectedValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(54, 120);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 17);
            this.label1.TabIndex = 7;
            this.label1.Text = "用户名：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(211, 56);
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
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10"});
            this.cbox_identityPriority.Location = new System.Drawing.Point(265, 52);
            this.cbox_identityPriority.Name = "cbox_identityPriority";
            this.cbox_identityPriority.Size = new System.Drawing.Size(55, 25);
            this.cbox_identityPriority.TabIndex = 2;
            // 
            // cbox_serverIP
            // 
            this.cbox_serverIP.FormattingEnabled = true;
            this.cbox_serverIP.Location = new System.Drawing.Point(116, 15);
            this.cbox_serverIP.Name = "cbox_serverIP";
            this.cbox_serverIP.Size = new System.Drawing.Size(204, 25);
            this.cbox_serverIP.TabIndex = 10;
            // 
            // cbox_port
            // 
            this.cbox_port.FormattingEnabled = true;
            this.cbox_port.Location = new System.Drawing.Point(116, 48);
            this.cbox_port.Name = "cbox_port";
            this.cbox_port.Size = new System.Drawing.Size(77, 25);
            this.cbox_port.TabIndex = 11;
            // 
            // cbox_userName
            // 
            this.cbox_userName.FormattingEnabled = true;
            this.cbox_userName.Location = new System.Drawing.Point(116, 116);
            this.cbox_userName.Name = "cbox_userName";
            this.cbox_userName.Size = new System.Drawing.Size(204, 25);
            this.cbox_userName.TabIndex = 12;
            // 
            // pnl_selectSkill
            // 
            this.pnl_selectSkill.Controls.Add(this.chkBox_skill_loan);
            this.pnl_selectSkill.Controls.Add(this.chkBox_skill_finance);
            this.pnl_selectSkill.Controls.Add(this.chkBox_skill_cash);
            this.pnl_selectSkill.Controls.Add(this.label3);
            this.pnl_selectSkill.Location = new System.Drawing.Point(35, 145);
            this.pnl_selectSkill.Name = "pnl_selectSkill";
            this.pnl_selectSkill.Size = new System.Drawing.Size(285, 31);
            this.pnl_selectSkill.TabIndex = 13;
            // 
            // chkBox_skill_loan
            // 
            this.chkBox_skill_loan.AutoSize = true;
            this.chkBox_skill_loan.Checked = true;
            this.chkBox_skill_loan.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkBox_skill_loan.Location = new System.Drawing.Point(230, 5);
            this.chkBox_skill_loan.Name = "chkBox_skill_loan";
            this.chkBox_skill_loan.Size = new System.Drawing.Size(51, 21);
            this.chkBox_skill_loan.TabIndex = 0;
            this.chkBox_skill_loan.Text = "贷款";
            this.chkBox_skill_loan.UseVisualStyleBackColor = true;
            this.chkBox_skill_loan.CheckedChanged += new System.EventHandler(this.chkBox_skill_loan_CheckedChanged);
            // 
            // chkBox_skill_finance
            // 
            this.chkBox_skill_finance.AutoSize = true;
            this.chkBox_skill_finance.Checked = true;
            this.chkBox_skill_finance.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkBox_skill_finance.Location = new System.Drawing.Point(156, 5);
            this.chkBox_skill_finance.Name = "chkBox_skill_finance";
            this.chkBox_skill_finance.Size = new System.Drawing.Size(51, 21);
            this.chkBox_skill_finance.TabIndex = 0;
            this.chkBox_skill_finance.Text = "理财";
            this.chkBox_skill_finance.UseVisualStyleBackColor = true;
            this.chkBox_skill_finance.CheckedChanged += new System.EventHandler(this.chkBox_skill_finance_CheckedChanged);
            // 
            // chkBox_skill_cash
            // 
            this.chkBox_skill_cash.AutoSize = true;
            this.chkBox_skill_cash.Checked = true;
            this.chkBox_skill_cash.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkBox_skill_cash.Location = new System.Drawing.Point(81, 6);
            this.chkBox_skill_cash.Name = "chkBox_skill_cash";
            this.chkBox_skill_cash.Size = new System.Drawing.Size(51, 21);
            this.chkBox_skill_cash.TabIndex = 0;
            this.chkBox_skill_cash.Text = "现金";
            this.chkBox_skill_cash.UseVisualStyleBackColor = true;
            this.chkBox_skill_cash.CheckedChanged += new System.EventHandler(this.chkBox_skill_cash_CheckedChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 6);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(68, 17);
            this.label3.TabIndex = 7;
            this.label3.Text = "选择技能：";
            // 
            // pnl_AutoRouter
            // 
            this.pnl_AutoRouter.Controls.Add(this.cmbBox_Router);
            this.pnl_AutoRouter.Controls.Add(this.lbl_router);
            this.pnl_AutoRouter.Location = new System.Drawing.Point(191, 84);
            this.pnl_AutoRouter.Name = "pnl_AutoRouter";
            this.pnl_AutoRouter.Size = new System.Drawing.Size(151, 27);
            this.pnl_AutoRouter.TabIndex = 14;
            // 
            // lbl_router
            // 
            this.lbl_router.AutoSize = true;
            this.lbl_router.Location = new System.Drawing.Point(8, 4);
            this.lbl_router.Name = "lbl_router";
            this.lbl_router.Size = new System.Drawing.Size(68, 17);
            this.lbl_router.TabIndex = 5;
            this.lbl_router.Text = "自动路由：";
            // 
            // cmbBox_Router
            // 
            this.cmbBox_Router.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbBox_Router.FormattingEnabled = true;
            this.cmbBox_Router.Items.AddRange(new object[] {
            "关闭",
            "开启"});
            this.cmbBox_Router.Location = new System.Drawing.Point(74, 1);
            this.cmbBox_Router.Name = "cmbBox_Router";
            this.cmbBox_Router.Size = new System.Drawing.Size(55, 25);
            this.cmbBox_Router.TabIndex = 6;
            // 
            // frmLogin
            // 
            this.AcceptButton = this.btn_login;
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 244);
            this.Controls.Add(this.cbox_userIdentity);
            this.Controls.Add(this.pnl_AutoRouter);
            this.Controls.Add(this.pnl_selectSkill);
            this.Controls.Add(this.cbox_userName);
            this.Controls.Add(this.cbox_port);
            this.Controls.Add(this.cbox_serverIP);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbox_identityPriority);
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
            this.pnl_selectSkill.ResumeLayout(false);
            this.pnl_selectSkill.PerformLayout();
            this.pnl_AutoRouter.ResumeLayout(false);
            this.pnl_AutoRouter.PerformLayout();
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
        private System.Windows.Forms.Panel pnl_selectSkill;
        private System.Windows.Forms.CheckBox chkBox_skill_loan;
        private System.Windows.Forms.CheckBox chkBox_skill_finance;
        private System.Windows.Forms.CheckBox chkBox_skill_cash;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Panel pnl_AutoRouter;
        private System.Windows.Forms.ComboBox cmbBox_Router;
        private System.Windows.Forms.Label lbl_router;
    }
}

