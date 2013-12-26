namespace VideoChatClient
{
    partial class Hall
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Hall));
            this.lb_name = new System.Windows.Forms.Label();
            this.pan_top = new System.Windows.Forms.Panel();
            this.pan_users = new System.Windows.Forms.Panel();
            this.pan_call = new System.Windows.Forms.Panel();
            this.lb_call = new System.Windows.Forms.Label();
            this.pic_call = new System.Windows.Forms.PictureBox();
            this.timer_call = new System.Windows.Forms.Timer(this.components);
            this.pan_conversation = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.pic_tuserVideo = new System.Windows.Forms.PictureBox();
            this.pic_tuserSound = new System.Windows.Forms.PictureBox();
            this.pic_suserSound = new System.Windows.Forms.PictureBox();
            this.lb_suserName = new System.Windows.Forms.Label();
            this.pic_suserVideo = new System.Windows.Forms.PictureBox();
            this.lb_tuserName = new System.Windows.Forms.Label();
            this.btn_hungUp = new System.Windows.Forms.Button();
            this.timer_speak = new System.Windows.Forms.Timer(this.components);
            this.pan_top.SuspendLayout();
            this.pan_call.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pic_call)).BeginInit();
            this.pan_conversation.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pic_tuserVideo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_tuserSound)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_suserSound)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_suserVideo)).BeginInit();
            this.SuspendLayout();
            // 
            // lb_name
            // 
            this.lb_name.AutoSize = true;
            this.lb_name.Font = new System.Drawing.Font("微软雅黑", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lb_name.ForeColor = System.Drawing.Color.White;
            this.lb_name.Location = new System.Drawing.Point(12, 9);
            this.lb_name.Name = "lb_name";
            this.lb_name.Size = new System.Drawing.Size(337, 38);
            this.lb_name.TabIndex = 0;
            this.lb_name.Text = "AnyChat音视频呼叫中心";
            // 
            // pan_top
            // 
            this.pan_top.BackColor = System.Drawing.Color.SteelBlue;
            this.pan_top.Controls.Add(this.lb_name);
            this.pan_top.Dock = System.Windows.Forms.DockStyle.Top;
            this.pan_top.Location = new System.Drawing.Point(0, 0);
            this.pan_top.Name = "pan_top";
            this.pan_top.Size = new System.Drawing.Size(1041, 70);
            this.pan_top.TabIndex = 1;
            // 
            // pan_users
            // 
            this.pan_users.AutoScroll = true;
            this.pan_users.BackColor = System.Drawing.Color.White;
            this.pan_users.Location = new System.Drawing.Point(12, 76);
            this.pan_users.Name = "pan_users";
            this.pan_users.Size = new System.Drawing.Size(270, 204);
            this.pan_users.TabIndex = 2;
            // 
            // pan_call
            // 
            this.pan_call.Controls.Add(this.lb_call);
            this.pan_call.Controls.Add(this.pic_call);
            this.pan_call.Location = new System.Drawing.Point(568, 76);
            this.pan_call.Name = "pan_call";
            this.pan_call.Size = new System.Drawing.Size(270, 204);
            this.pan_call.TabIndex = 3;
            this.pan_call.Visible = false;
            // 
            // lb_call
            // 
            this.lb_call.AutoSize = true;
            this.lb_call.Font = new System.Drawing.Font("微软雅黑", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lb_call.Location = new System.Drawing.Point(149, 87);
            this.lb_call.Name = "lb_call";
            this.lb_call.Size = new System.Drawing.Size(120, 46);
            this.lb_call.TabIndex = 0;
            this.lb_call.Tag = "message";
            this.lb_call.Text = "label1";
            // 
            // pic_call
            // 
            this.pic_call.Location = new System.Drawing.Point(3, 73);
            this.pic_call.Name = "pic_call";
            this.pic_call.Size = new System.Drawing.Size(128, 128);
            this.pic_call.TabIndex = 1;
            this.pic_call.TabStop = false;
            // 
            // timer_call
            // 
            this.timer_call.Interval = 500;
            this.timer_call.Tick += new System.EventHandler(this.timer_call_Tick);
            // 
            // pan_conversation
            // 
            this.pan_conversation.Controls.Add(this.panel1);
            this.pan_conversation.Controls.Add(this.btn_hungUp);
            this.pan_conversation.Location = new System.Drawing.Point(288, 76);
            this.pan_conversation.Name = "pan_conversation";
            this.pan_conversation.Size = new System.Drawing.Size(270, 204);
            this.pan_conversation.TabIndex = 4;
            this.pan_conversation.Visible = false;
            // 
            // panel1
            // 
            this.panel1.BackgroundImage = global::VideoChatClient.Properties.Resources._03;
            this.panel1.Controls.Add(this.pic_tuserVideo);
            this.panel1.Controls.Add(this.pic_tuserSound);
            this.panel1.Controls.Add(this.pic_suserSound);
            this.panel1.Controls.Add(this.lb_suserName);
            this.panel1.Controls.Add(this.pic_suserVideo);
            this.panel1.Controls.Add(this.lb_tuserName);
            this.panel1.Location = new System.Drawing.Point(12, 23);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1017, 450);
            this.panel1.TabIndex = 10;
            // 
            // pic_tuserVideo
            // 
            this.pic_tuserVideo.BackColor = System.Drawing.Color.Orange;
            this.pic_tuserVideo.BackgroundImage = global::VideoChatClient.Properties.Resources.videobk;
            this.pic_tuserVideo.Location = new System.Drawing.Point(24, 19);
            this.pic_tuserVideo.Name = "pic_tuserVideo";
            this.pic_tuserVideo.Size = new System.Drawing.Size(473, 344);
            this.pic_tuserVideo.TabIndex = 0;
            this.pic_tuserVideo.TabStop = false;
            // 
            // pic_tuserSound
            // 
            this.pic_tuserSound.Location = new System.Drawing.Point(24, 367);
            this.pic_tuserSound.Name = "pic_tuserSound";
            this.pic_tuserSound.Size = new System.Drawing.Size(473, 5);
            this.pic_tuserSound.TabIndex = 4;
            this.pic_tuserSound.TabStop = false;
            this.pic_tuserSound.Paint += new System.Windows.Forms.PaintEventHandler(this.pic_tuserSound_Paint);
            // 
            // pic_suserSound
            // 
            this.pic_suserSound.Location = new System.Drawing.Point(521, 367);
            this.pic_suserSound.Name = "pic_suserSound";
            this.pic_suserSound.Size = new System.Drawing.Size(471, 5);
            this.pic_suserSound.TabIndex = 6;
            this.pic_suserSound.TabStop = false;
            this.pic_suserSound.Paint += new System.Windows.Forms.PaintEventHandler(this.pic_suserSound_Paint);
            // 
            // lb_suserName
            // 
            this.lb_suserName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lb_suserName.AutoSize = true;
            this.lb_suserName.BackColor = System.Drawing.Color.Transparent;
            this.lb_suserName.Font = new System.Drawing.Font("微软雅黑", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lb_suserName.Location = new System.Drawing.Point(525, 381);
            this.lb_suserName.Name = "lb_suserName";
            this.lb_suserName.Size = new System.Drawing.Size(254, 46);
            this.lb_suserName.TabIndex = 8;
            this.lb_suserName.Text = "lb_suserName";
            // 
            // pic_suserVideo
            // 
            this.pic_suserVideo.BackColor = System.Drawing.Color.Orange;
            this.pic_suserVideo.BackgroundImage = global::VideoChatClient.Properties.Resources.videobk;
            this.pic_suserVideo.Location = new System.Drawing.Point(521, 19);
            this.pic_suserVideo.Name = "pic_suserVideo";
            this.pic_suserVideo.Size = new System.Drawing.Size(471, 344);
            this.pic_suserVideo.TabIndex = 1;
            this.pic_suserVideo.TabStop = false;
            // 
            // lb_tuserName
            // 
            this.lb_tuserName.AutoSize = true;
            this.lb_tuserName.BackColor = System.Drawing.Color.Transparent;
            this.lb_tuserName.Font = new System.Drawing.Font("微软雅黑", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lb_tuserName.Location = new System.Drawing.Point(27, 381);
            this.lb_tuserName.Name = "lb_tuserName";
            this.lb_tuserName.Size = new System.Drawing.Size(251, 46);
            this.lb_tuserName.TabIndex = 7;
            this.lb_tuserName.Text = "lb_tuserName";
            // 
            // btn_hungUp
            // 
            this.btn_hungUp.BackColor = System.Drawing.Color.Red;
            this.btn_hungUp.Font = new System.Drawing.Font("微软雅黑", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_hungUp.ForeColor = System.Drawing.Color.White;
            this.btn_hungUp.Location = new System.Drawing.Point(836, 497);
            this.btn_hungUp.Name = "btn_hungUp";
            this.btn_hungUp.Size = new System.Drawing.Size(160, 70);
            this.btn_hungUp.TabIndex = 9;
            this.btn_hungUp.Text = "挂断";
            this.btn_hungUp.UseVisualStyleBackColor = false;
            this.btn_hungUp.Click += new System.EventHandler(this.btn_hungUp_Click);
            // 
            // timer_speak
            // 
            this.timer_speak.Interval = 50;
            this.timer_speak.Tick += new System.EventHandler(this.timer_speak_Tick);
            // 
            // Hall
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1041, 689);
            this.Controls.Add(this.pan_conversation);
            this.Controls.Add(this.pan_call);
            this.Controls.Add(this.pan_users);
            this.Controls.Add(this.pan_top);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.Name = "Hall";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "大厅";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Hall_FormClosed);
            this.Load += new System.EventHandler(this.Hall_Load);
            this.pan_top.ResumeLayout(false);
            this.pan_top.PerformLayout();
            this.pan_call.ResumeLayout(false);
            this.pan_call.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pic_call)).EndInit();
            this.pan_conversation.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pic_tuserVideo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_tuserSound)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_suserSound)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_suserVideo)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label lb_name;
        private System.Windows.Forms.Panel pan_top;
        private System.Windows.Forms.Panel pan_users;
        private System.Windows.Forms.Panel pan_call;
        private System.Windows.Forms.Label lb_call;
        private System.Windows.Forms.PictureBox pic_call;
        private System.Windows.Forms.Timer timer_call;
        private System.Windows.Forms.Panel pan_conversation;
        private System.Windows.Forms.PictureBox pic_suserVideo;
        private System.Windows.Forms.PictureBox pic_tuserVideo;
        private System.Windows.Forms.PictureBox pic_suserSound;
        private System.Windows.Forms.PictureBox pic_tuserSound;
        private System.Windows.Forms.Label lb_suserName;
        private System.Windows.Forms.Label lb_tuserName;
        private System.Windows.Forms.Button btn_hungUp;
        private System.Windows.Forms.Timer timer_speak;
        private System.Windows.Forms.Panel panel1;
    }
}