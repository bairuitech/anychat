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
            this.lbl_statue = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txt_hospitalip = new System.Windows.Forms.TextBox();
            this.tb_port = new System.Windows.Forms.TextBox();
            this.lb_port = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // txt_username
            // 
            this.txt_username.Location = new System.Drawing.Point(122, 96);
            this.txt_username.Name = "txt_username";
            this.txt_username.Size = new System.Drawing.Size(202, 21);
            this.txt_username.TabIndex = 0;
            this.txt_username.Text = "guest001";
            // 
            // txt_password
            // 
            this.txt_password.Location = new System.Drawing.Point(122, 139);
            this.txt_password.Name = "txt_password";
            this.txt_password.PasswordChar = '*';
            this.txt_password.Size = new System.Drawing.Size(202, 21);
            this.txt_password.TabIndex = 1;
            this.txt_password.Text = "guest001";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(49, 100);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "账号";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(49, 143);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "密码";
            // 
            // btn_login
            // 
            this.btn_login.Location = new System.Drawing.Point(77, 213);
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
            this.btn_canel.Location = new System.Drawing.Point(174, 213);
            this.btn_canel.Name = "btn_canel";
            this.btn_canel.Size = new System.Drawing.Size(75, 23);
            this.btn_canel.TabIndex = 3;
            this.btn_canel.Text = "退出";
            this.btn_canel.UseVisualStyleBackColor = true;
            this.btn_canel.Click += new System.EventHandler(this.btn_canel_Click);
            // 
            // lbl_statue
            // 
            this.lbl_statue.Location = new System.Drawing.Point(32, 271);
            this.lbl_statue.Name = "lbl_statue";
            this.lbl_statue.Size = new System.Drawing.Size(270, 23);
            this.lbl_statue.TabIndex = 4;
            this.lbl_statue.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(49, 59);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "服务器";
            // 
            // txt_hospitalip
            // 
            this.txt_hospitalip.Location = new System.Drawing.Point(122, 56);
            this.txt_hospitalip.Name = "txt_hospitalip";
            this.txt_hospitalip.Size = new System.Drawing.Size(101, 21);
            this.txt_hospitalip.TabIndex = 7;
            this.txt_hospitalip.Text = "demo.anychat.cn";
            // 
            // tb_port
            // 
            this.tb_port.Location = new System.Drawing.Point(256, 56);
            this.tb_port.Name = "tb_port";
            this.tb_port.Size = new System.Drawing.Size(68, 21);
            this.tb_port.TabIndex = 8;
            this.tb_port.Text = "8906";
            // 
            // lb_port
            // 
            this.lb_port.AutoSize = true;
            this.lb_port.Location = new System.Drawing.Point(229, 59);
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
            this.ClientSize = new System.Drawing.Size(359, 303);
            this.Controls.Add(this.tb_port);
            this.Controls.Add(this.txt_hospitalip);
            this.Controls.Add(this.lbl_statue);
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
        private System.Windows.Forms.Label lbl_statue;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txt_hospitalip;
        private TextBox tb_port;
        private Label lb_port;
    }
}