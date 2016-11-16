namespace AnyChatServer
{
    partial class frmMain
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
            this.rtb_message = new System.Windows.Forms.RichTextBox();
            this.lbl_onlineUserCount = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // rtb_message
            // 
            this.rtb_message.Location = new System.Drawing.Point(12, 32);
            this.rtb_message.Name = "rtb_message";
            this.rtb_message.Size = new System.Drawing.Size(713, 379);
            this.rtb_message.TabIndex = 0;
            this.rtb_message.Text = "";
            // 
            // lbl_onlineUserCount
            // 
            this.lbl_onlineUserCount.AutoSize = true;
            this.lbl_onlineUserCount.Location = new System.Drawing.Point(12, 9);
            this.lbl_onlineUserCount.Name = "lbl_onlineUserCount";
            this.lbl_onlineUserCount.Size = new System.Drawing.Size(83, 12);
            this.lbl_onlineUserCount.TabIndex = 1;
            this.lbl_onlineUserCount.Text = "在线用户数：0";
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(751, 434);
            this.Controls.Add(this.lbl_onlineUserCount);
            this.Controls.Add(this.rtb_message);
            this.Name = "frmMain";
            this.Text = "AnyChat Server SDK示例";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox rtb_message;
        private System.Windows.Forms.Label lbl_onlineUserCount;



    }
}

