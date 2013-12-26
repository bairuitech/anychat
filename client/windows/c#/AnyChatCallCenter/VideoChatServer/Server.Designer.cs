namespace VideoChatServer
{
    partial class Server
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
            this.lb_version = new System.Windows.Forms.Label();
            this.gb_serverLogs = new System.Windows.Forms.GroupBox();
            this.rtb_message = new System.Windows.Forms.RichTextBox();
            this.gb_onlineEquipment = new System.Windows.Forms.GroupBox();
            this.lv_onlineUsers = new System.Windows.Forms.ListView();
            this.ch_id = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ch_department = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ch_name = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ch_addr = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ch_time = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.gb_serverLogs.SuspendLayout();
            this.gb_onlineEquipment.SuspendLayout();
            this.SuspendLayout();
            // 
            // lb_version
            // 
            this.lb_version.AutoSize = true;
            this.lb_version.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lb_version.Location = new System.Drawing.Point(790, 499);
            this.lb_version.Name = "lb_version";
            this.lb_version.Size = new System.Drawing.Size(52, 17);
            this.lb_version.TabIndex = 6;
            this.lb_version.Text = "Version";
            // 
            // gb_serverLogs
            // 
            this.gb_serverLogs.Controls.Add(this.rtb_message);
            this.gb_serverLogs.Location = new System.Drawing.Point(534, 12);
            this.gb_serverLogs.Name = "gb_serverLogs";
            this.gb_serverLogs.Size = new System.Drawing.Size(413, 474);
            this.gb_serverLogs.TabIndex = 3;
            this.gb_serverLogs.TabStop = false;
            this.gb_serverLogs.Text = "Server Logs";
            // 
            // rtb_message
            // 
            this.rtb_message.Location = new System.Drawing.Point(6, 20);
            this.rtb_message.Name = "rtb_message";
            this.rtb_message.ReadOnly = true;
            this.rtb_message.Size = new System.Drawing.Size(401, 448);
            this.rtb_message.TabIndex = 0;
            this.rtb_message.Text = "";
            // 
            // gb_onlineEquipment
            // 
            this.gb_onlineEquipment.Controls.Add(this.lv_onlineUsers);
            this.gb_onlineEquipment.Location = new System.Drawing.Point(12, 12);
            this.gb_onlineEquipment.Name = "gb_onlineEquipment";
            this.gb_onlineEquipment.Size = new System.Drawing.Size(516, 474);
            this.gb_onlineEquipment.TabIndex = 4;
            this.gb_onlineEquipment.TabStop = false;
            this.gb_onlineEquipment.Text = "Online Devices";
            // 
            // lv_onlineUsers
            // 
            this.lv_onlineUsers.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.ch_id,
            this.ch_department,
            this.ch_name,
            this.ch_addr,
            this.ch_time});
            this.lv_onlineUsers.Location = new System.Drawing.Point(6, 20);
            this.lv_onlineUsers.Name = "lv_onlineUsers";
            this.lv_onlineUsers.Size = new System.Drawing.Size(504, 448);
            this.lv_onlineUsers.TabIndex = 0;
            this.lv_onlineUsers.UseCompatibleStateImageBehavior = false;
            this.lv_onlineUsers.View = System.Windows.Forms.View.Details;
            // 
            // ch_id
            // 
            this.ch_id.Text = "ID";
            this.ch_id.Width = 33;
            // 
            // ch_department
            // 
            this.ch_department.Text = "用户名";
            this.ch_department.Width = 80;
            // 
            // ch_name
            // 
            this.ch_name.Text = "身份";
            this.ch_name.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.ch_name.Width = 100;
            // 
            // ch_addr
            // 
            this.ch_addr.Text = "IP地址";
            this.ch_addr.Width = 100;
            // 
            // ch_time
            // 
            this.ch_time.Text = "连接时间";
            this.ch_time.Width = 120;
            // 
            // Server
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(964, 522);
            this.Controls.Add(this.lb_version);
            this.Controls.Add(this.gb_serverLogs);
            this.Controls.Add(this.gb_onlineEquipment);
            this.MaximumSize = new System.Drawing.Size(980, 560);
            this.MinimumSize = new System.Drawing.Size(980, 560);
            this.Name = "Server";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "VideoChatServer";
            this.Load += new System.EventHandler(this.Server_Load);
            this.gb_serverLogs.ResumeLayout(false);
            this.gb_onlineEquipment.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lb_version;
        private System.Windows.Forms.GroupBox gb_serverLogs;
        private System.Windows.Forms.RichTextBox rtb_message;
        private System.Windows.Forms.GroupBox gb_onlineEquipment;
        private System.Windows.Forms.ListView lv_onlineUsers;
        private System.Windows.Forms.ColumnHeader ch_id;
        private System.Windows.Forms.ColumnHeader ch_department;
        private System.Windows.Forms.ColumnHeader ch_name;
        private System.Windows.Forms.ColumnHeader ch_addr;
        private System.Windows.Forms.ColumnHeader ch_time;
    }
}

