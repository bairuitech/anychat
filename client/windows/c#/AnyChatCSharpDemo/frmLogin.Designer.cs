using System.Windows.Forms;


namespace AnyChatCSharpDemo
{
    partial class frmLogin : Form
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
            this.txt_username = new System.Windows.Forms.TextBox();
            this.txt_password = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btn_login = new System.Windows.Forms.Button();
            this.btn_canel = new System.Windows.Forms.Button();
            this.lbl_status = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txt_serverip = new System.Windows.Forms.TextBox();
            this.tb_port = new System.Windows.Forms.TextBox();
            this.lb_port = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // txt_username
            // 
            this.txt_username.Location = new System.Drawing.Point(113, 71);
            this.txt_username.Name = "txt_username";
            this.txt_username.Size = new System.Drawing.Size(211, 21);
            this.txt_username.TabIndex = 0;
            this.txt_username.Text = "guest001";
            // 
            // txt_password
            // 
            this.txt_password.Location = new System.Drawing.Point(113, 99);
            this.txt_password.Name = "txt_password";
            this.txt_password.PasswordChar = '*';
            this.txt_password.Size = new System.Drawing.Size(211, 21);
            this.txt_password.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(49, 75);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "账号";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(49, 103);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "密码";
            // 
            // btn_login
            // 
            this.btn_login.Location = new System.Drawing.Point(92, 151);
            this.btn_login.Name = "btn_login";
            this.btn_login.Size = new System.Drawing.Size(75, 23);
            this.btn_login.TabIndex = 2;
            this.btn_login.Text = "登录";
            this.btn_login.UseVisualStyleBackColor = true;
            this.btn_login.Click += new System.EventHandler(this.btn_login_Click);
            // 
            // btn_canel
            // 
            this.btn_canel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.btn_canel.Location = new System.Drawing.Point(199, 151);
            this.btn_canel.Name = "btn_canel";
            this.btn_canel.Size = new System.Drawing.Size(75, 23);
            this.btn_canel.TabIndex = 3;
            this.btn_canel.Text = "退出";
            this.btn_canel.UseVisualStyleBackColor = true;
            this.btn_canel.Click += new System.EventHandler(this.btn_canel_Click);
            // 
            // lbl_status
            // 
            this.lbl_status.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.lbl_status.Location = new System.Drawing.Point(0, 209);
            this.lbl_status.Name = "lbl_status";
            this.lbl_status.Size = new System.Drawing.Size(372, 12);
            this.lbl_status.TabIndex = 4;
            this.lbl_status.Text = "message";
            this.lbl_status.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(49, 47);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "服务器";
            // 
            // txt_serverip
            // 
            this.txt_serverip.Location = new System.Drawing.Point(113, 44);
            this.txt_serverip.Name = "txt_serverip";
            this.txt_serverip.Size = new System.Drawing.Size(113, 21);
            this.txt_serverip.TabIndex = 7;
            this.txt_serverip.Text = "demo.anychat.cn";
            // 
            // tb_port
            // 
            this.tb_port.Location = new System.Drawing.Point(276, 44);
            this.tb_port.Name = "tb_port";
            this.tb_port.Size = new System.Drawing.Size(48, 21);
            this.tb_port.TabIndex = 8;
            this.tb_port.Text = "8906";
            // 
            // lb_port
            // 
            this.lb_port.AutoSize = true;
            this.lb_port.Location = new System.Drawing.Point(241, 47);
            this.lb_port.Name = "lb_port";
            this.lb_port.Size = new System.Drawing.Size(29, 12);
            this.lb_port.TabIndex = 1;
            this.lb_port.Text = "端口";
            // 
            // frmLogin
            // 
            this.AcceptButton = this.btn_login;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(230)))), ((int)(((byte)(230)))), ((int)(((byte)(230)))));
            this.CancelButton = this.btn_canel;
            this.ClientSize = new System.Drawing.Size(372, 221);
            this.Controls.Add(this.tb_port);
            this.Controls.Add(this.txt_serverip);
            this.Controls.Add(this.lbl_status);
            this.Controls.Add(this.btn_canel);
            this.Controls.Add(this.btn_login);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lb_port);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txt_password);
            this.Controls.Add(this.txt_username);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "frmLogin";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "登录";
            this.Load += new System.EventHandler(this.frmLogin_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_username;
        private System.Windows.Forms.TextBox txt_password;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btn_login;
        private System.Windows.Forms.Button btn_canel;
        private System.Windows.Forms.Label lbl_status;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txt_serverip;
        private TextBox tb_port;
        private Label lb_port;
    }
}