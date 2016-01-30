namespace VideoChatClient
{
    partial class Login
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Login));
            this.lb_name = new System.Windows.Forms.Label();
            this.btn_login = new System.Windows.Forms.Button();
            this.lb_serveradd = new System.Windows.Forms.Label();
            this.lb_port = new System.Windows.Forms.Label();
            this.lb_message = new System.Windows.Forms.Label();
            this.tb_serveradd = new System.Windows.Forms.ComboBox();
            this.tb_port = new System.Windows.Forms.ComboBox();
            this.tb_name = new System.Windows.Forms.ComboBox();
            this.tb_appGuid = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.rbtn_normal = new System.Windows.Forms.RadioButton();
            this.rbtn_sign = new System.Windows.Forms.RadioButton();
            this.SuspendLayout();
            // 
            // lb_name
            // 
            this.lb_name.AutoSize = true;
            this.lb_name.Location = new System.Drawing.Point(58, 96);
            this.lb_name.Name = "lb_name";
            this.lb_name.Size = new System.Drawing.Size(56, 17);
            this.lb_name.TabIndex = 0;
            this.lb_name.Text = "用户名：";
            // 
            // btn_login
            // 
            this.btn_login.Location = new System.Drawing.Point(154, 196);
            this.btn_login.Name = "btn_login";
            this.btn_login.Size = new System.Drawing.Size(75, 23);
            this.btn_login.TabIndex = 4;
            this.btn_login.Text = "登录";
            this.btn_login.UseVisualStyleBackColor = true;
            this.btn_login.Click += new System.EventHandler(this.btn_login_Click);
            // 
            // lb_serveradd
            // 
            this.lb_serveradd.AutoSize = true;
            this.lb_serveradd.Location = new System.Drawing.Point(58, 35);
            this.lb_serveradd.Name = "lb_serveradd";
            this.lb_serveradd.Size = new System.Drawing.Size(56, 17);
            this.lb_serveradd.TabIndex = 3;
            this.lb_serveradd.Text = "服务器：";
            // 
            // lb_port
            // 
            this.lb_port.AutoSize = true;
            this.lb_port.Location = new System.Drawing.Point(70, 67);
            this.lb_port.Name = "lb_port";
            this.lb_port.Size = new System.Drawing.Size(44, 17);
            this.lb_port.TabIndex = 5;
            this.lb_port.Text = "端口：";
            // 
            // lb_message
            // 
            this.lb_message.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.lb_message.Location = new System.Drawing.Point(0, 245);
            this.lb_message.Name = "lb_message";
            this.lb_message.Size = new System.Drawing.Size(384, 17);
            this.lb_message.TabIndex = 6;
            this.lb_message.Text = "message";
            this.lb_message.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lb_message.Visible = false;
            // 
            // tb_serveradd
            // 
            this.tb_serveradd.FormattingEnabled = true;
            this.tb_serveradd.Location = new System.Drawing.Point(120, 30);
            this.tb_serveradd.Name = "tb_serveradd";
            this.tb_serveradd.Size = new System.Drawing.Size(197, 25);
            this.tb_serveradd.TabIndex = 0;
            // 
            // tb_port
            // 
            this.tb_port.FormattingEnabled = true;
            this.tb_port.Location = new System.Drawing.Point(120, 62);
            this.tb_port.Name = "tb_port";
            this.tb_port.Size = new System.Drawing.Size(197, 25);
            this.tb_port.TabIndex = 1;
            // 
            // tb_name
            // 
            this.tb_name.FormattingEnabled = true;
            this.tb_name.Location = new System.Drawing.Point(120, 92);
            this.tb_name.Name = "tb_name";
            this.tb_name.Size = new System.Drawing.Size(197, 25);
            this.tb_name.TabIndex = 2;
            // 
            // tb_appGuid
            // 
            this.tb_appGuid.FormattingEnabled = true;
            this.tb_appGuid.Location = new System.Drawing.Point(120, 125);
            this.tb_appGuid.Name = "tb_appGuid";
            this.tb_appGuid.Size = new System.Drawing.Size(197, 25);
            this.tb_appGuid.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(58, 129);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 17);
            this.label3.TabIndex = 15;
            this.label3.Text = "应用ID：";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(47, 162);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 17);
            this.label1.TabIndex = 15;
            this.label1.Text = "登录方式：";
            // 
            // rbtn_normal
            // 
            this.rbtn_normal.AutoSize = true;
            this.rbtn_normal.Checked = true;
            this.rbtn_normal.Location = new System.Drawing.Point(121, 160);
            this.rbtn_normal.Name = "rbtn_normal";
            this.rbtn_normal.Size = new System.Drawing.Size(74, 21);
            this.rbtn_normal.TabIndex = 16;
            this.rbtn_normal.TabStop = true;
            this.rbtn_normal.Text = "普通登录";
            this.rbtn_normal.UseVisualStyleBackColor = true;
            this.rbtn_normal.Click += new System.EventHandler(this.rbtn_normal_Click);
            // 
            // rbtn_sign
            // 
            this.rbtn_sign.AutoSize = true;
            this.rbtn_sign.Location = new System.Drawing.Point(243, 160);
            this.rbtn_sign.Name = "rbtn_sign";
            this.rbtn_sign.Size = new System.Drawing.Size(74, 21);
            this.rbtn_sign.TabIndex = 16;
            this.rbtn_sign.Text = "签名登录";
            this.rbtn_sign.UseVisualStyleBackColor = true;
            this.rbtn_sign.Click += new System.EventHandler(this.rbtn_sign_Click);
            // 
            // Login
            // 
            this.AcceptButton = this.btn_login;
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(384, 262);
            this.Controls.Add(this.rbtn_sign);
            this.Controls.Add(this.rbtn_normal);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tb_appGuid);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.tb_name);
            this.Controls.Add(this.tb_port);
            this.Controls.Add(this.tb_serveradd);
            this.Controls.Add(this.lb_message);
            this.Controls.Add(this.lb_port);
            this.Controls.Add(this.lb_serveradd);
            this.Controls.Add(this.btn_login);
            this.Controls.Add(this.lb_name);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximumSize = new System.Drawing.Size(400, 300);
            this.MinimumSize = new System.Drawing.Size(400, 300);
            this.Name = "Login";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "登录";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Login_FormClosed);
            this.Load += new System.EventHandler(this.Login_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lb_name;
        private System.Windows.Forms.Button btn_login;
        private System.Windows.Forms.Label lb_serveradd;
        private System.Windows.Forms.Label lb_port;
        private System.Windows.Forms.Label lb_message;
        private System.Windows.Forms.ComboBox tb_serveradd;
        private System.Windows.Forms.ComboBox tb_port;
        private System.Windows.Forms.ComboBox tb_name;
        private System.Windows.Forms.ComboBox tb_appGuid;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RadioButton rbtn_normal;
        private System.Windows.Forms.RadioButton rbtn_sign;
    }
}

