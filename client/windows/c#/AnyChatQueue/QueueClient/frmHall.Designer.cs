namespace QueueClient
{
    partial class frmHall
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmHall));
            this.lbl_tipMessage = new System.Windows.Forms.Label();
            this.panel_top = new System.Windows.Forms.Panel();
            this.btn_return = new System.Windows.Forms.Button();
            this.panel_users = new System.Windows.Forms.Panel();
            this.panel_call = new System.Windows.Forms.Panel();
            this.lb_call = new System.Windows.Forms.Label();
            this.pic_call = new System.Windows.Forms.PictureBox();
            this.panel_conversation = new System.Windows.Forms.Panel();
            this.btn_hungUp = new System.Windows.Forms.Button();
            this.panel_userVedioCall = new System.Windows.Forms.Panel();
            this.picBox_client_remoteVideo = new System.Windows.Forms.PictureBox();
            this.pic_tuserSound = new System.Windows.Forms.PictureBox();
            this.pic_suserSound = new System.Windows.Forms.PictureBox();
            this.lbl_client_localUserName = new System.Windows.Forms.Label();
            this.picBox_client_localVideo = new System.Windows.Forms.PictureBox();
            this.lbl_client_remoteUserName = new System.Windows.Forms.Label();
            this.timer_speak = new System.Windows.Forms.Timer(this.components);
            this.timer_call = new System.Windows.Forms.Timer(this.components);
            this.panel_area = new System.Windows.Forms.Panel();
            this.panel_queue = new System.Windows.Forms.Panel();
            this.panel_waitingMessage = new System.Windows.Forms.Panel();
            this.lbl_waitingTime = new System.Windows.Forms.Label();
            this.lbl_waitingMessage = new System.Windows.Forms.Label();
            this.picBox_waiting = new System.Windows.Forms.PictureBox();
            this.timer_queueWaiting = new System.Windows.Forms.Timer(this.components);
            this.panel_agentVedioCall = new System.Windows.Forms.Panel();
            this.comboBox_AgentStatus = new System.Windows.Forms.ComboBox();
            this.lbl_CurrentStatus = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btnStopService = new System.Windows.Forms.Button();
            this.btnStartService = new System.Windows.Forms.Button();
            this.lbl_agent_atAreaUserCount = new System.Windows.Forms.Label();
            this.lbl_agent_servicedUserCount = new System.Windows.Forms.Label();
            this.lbl_agent_currentTotalUserCount = new System.Windows.Forms.Label();
            this.lbl_agent_queueNumber = new System.Windows.Forms.Label();
            this.picBox_agent_localVideo = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.lbl_agent_remoteUser = new System.Windows.Forms.Label();
            this.picBox_agent_remoteVideo = new System.Windows.Forms.PictureBox();
            this.btnRecord = new System.Windows.Forms.Button();
            this.lbl_recordFileName = new System.Windows.Forms.Label();
            this.panel_top.SuspendLayout();
            this.panel_call.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pic_call)).BeginInit();
            this.panel_conversation.SuspendLayout();
            this.panel_userVedioCall.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_client_remoteVideo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_tuserSound)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_suserSound)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_client_localVideo)).BeginInit();
            this.panel_waitingMessage.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_waiting)).BeginInit();
            this.panel_agentVedioCall.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_agent_localVideo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_agent_remoteVideo)).BeginInit();
            this.SuspendLayout();
            // 
            // lbl_tipMessage
            // 
            this.lbl_tipMessage.AutoSize = true;
            this.lbl_tipMessage.Font = new System.Drawing.Font("微软雅黑", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_tipMessage.ForeColor = System.Drawing.Color.White;
            this.lbl_tipMessage.Location = new System.Drawing.Point(12, 9);
            this.lbl_tipMessage.Name = "lbl_tipMessage";
            this.lbl_tipMessage.Size = new System.Drawing.Size(275, 38);
            this.lbl_tipMessage.TabIndex = 0;
            this.lbl_tipMessage.Text = "AnyChat排队Demo";
            // 
            // panel_top
            // 
            this.panel_top.BackColor = System.Drawing.Color.SteelBlue;
            this.panel_top.Controls.Add(this.btn_return);
            this.panel_top.Controls.Add(this.lbl_tipMessage);
            this.panel_top.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel_top.Location = new System.Drawing.Point(0, 0);
            this.panel_top.Name = "panel_top";
            this.panel_top.Size = new System.Drawing.Size(1041, 70);
            this.panel_top.TabIndex = 1;
            // 
            // btn_return
            // 
            this.btn_return.Location = new System.Drawing.Point(921, 13);
            this.btn_return.Name = "btn_return";
            this.btn_return.Size = new System.Drawing.Size(97, 43);
            this.btn_return.TabIndex = 1;
            this.btn_return.Text = "返回";
            this.btn_return.UseVisualStyleBackColor = true;
            this.btn_return.Click += new System.EventHandler(this.btn_return_Click);
            // 
            // panel_users
            // 
            this.panel_users.AutoScroll = true;
            this.panel_users.BackColor = System.Drawing.Color.White;
            this.panel_users.Location = new System.Drawing.Point(17, 80);
            this.panel_users.Name = "panel_users";
            this.panel_users.Size = new System.Drawing.Size(270, 204);
            this.panel_users.TabIndex = 2;
            // 
            // panel_call
            // 
            this.panel_call.Controls.Add(this.lb_call);
            this.panel_call.Controls.Add(this.pic_call);
            this.panel_call.Location = new System.Drawing.Point(6, 628);
            this.panel_call.Name = "panel_call";
            this.panel_call.Size = new System.Drawing.Size(389, 204);
            this.panel_call.TabIndex = 3;
            this.panel_call.Visible = false;
            // 
            // lb_call
            // 
            this.lb_call.AutoSize = true;
            this.lb_call.Font = new System.Drawing.Font("微软雅黑", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lb_call.Location = new System.Drawing.Point(163, 86);
            this.lb_call.Name = "lb_call";
            this.lb_call.Size = new System.Drawing.Size(120, 46);
            this.lb_call.TabIndex = 0;
            this.lb_call.Tag = "message";
            this.lb_call.Text = "label1";
            // 
            // pic_call
            // 
            this.pic_call.Location = new System.Drawing.Point(3, 41);
            this.pic_call.Name = "pic_call";
            this.pic_call.Size = new System.Drawing.Size(128, 128);
            this.pic_call.TabIndex = 1;
            this.pic_call.TabStop = false;
            // 
            // panel_conversation
            // 
            this.panel_conversation.Controls.Add(this.btn_hungUp);
            this.panel_conversation.Controls.Add(this.panel_userVedioCall);
            this.panel_conversation.Location = new System.Drawing.Point(446, 112);
            this.panel_conversation.Name = "panel_conversation";
            this.panel_conversation.Size = new System.Drawing.Size(270, 204);
            this.panel_conversation.TabIndex = 4;
            this.panel_conversation.Visible = false;
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
            // panel_userVedioCall
            // 
            this.panel_userVedioCall.BackgroundImage = global::QueueClient.Properties.Resources._03;
            this.panel_userVedioCall.Controls.Add(this.picBox_client_remoteVideo);
            this.panel_userVedioCall.Controls.Add(this.pic_tuserSound);
            this.panel_userVedioCall.Controls.Add(this.pic_suserSound);
            this.panel_userVedioCall.Controls.Add(this.lbl_client_localUserName);
            this.panel_userVedioCall.Controls.Add(this.picBox_client_localVideo);
            this.panel_userVedioCall.Controls.Add(this.lbl_client_remoteUserName);
            this.panel_userVedioCall.Location = new System.Drawing.Point(12, 12);
            this.panel_userVedioCall.Name = "panel_userVedioCall";
            this.panel_userVedioCall.Size = new System.Drawing.Size(1017, 450);
            this.panel_userVedioCall.TabIndex = 10;
            // 
            // picBox_client_remoteVideo
            // 
            this.picBox_client_remoteVideo.BackColor = System.Drawing.Color.Orange;
            this.picBox_client_remoteVideo.BackgroundImage = global::QueueClient.Properties.Resources.videobk;
            this.picBox_client_remoteVideo.Location = new System.Drawing.Point(24, 19);
            this.picBox_client_remoteVideo.Name = "picBox_client_remoteVideo";
            this.picBox_client_remoteVideo.Size = new System.Drawing.Size(473, 344);
            this.picBox_client_remoteVideo.TabIndex = 0;
            this.picBox_client_remoteVideo.TabStop = false;
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
            // lbl_client_localUserName
            // 
            this.lbl_client_localUserName.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lbl_client_localUserName.AutoSize = true;
            this.lbl_client_localUserName.BackColor = System.Drawing.Color.Transparent;
            this.lbl_client_localUserName.Font = new System.Drawing.Font("微软雅黑", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_client_localUserName.Location = new System.Drawing.Point(525, 381);
            this.lbl_client_localUserName.Name = "lbl_client_localUserName";
            this.lbl_client_localUserName.Size = new System.Drawing.Size(195, 46);
            this.lbl_client_localUserName.TabIndex = 8;
            this.lbl_client_localUserName.Text = "自己用户名";
            // 
            // picBox_client_localVideo
            // 
            this.picBox_client_localVideo.BackColor = System.Drawing.Color.Orange;
            this.picBox_client_localVideo.BackgroundImage = global::QueueClient.Properties.Resources.videobk;
            this.picBox_client_localVideo.Location = new System.Drawing.Point(521, 19);
            this.picBox_client_localVideo.Name = "picBox_client_localVideo";
            this.picBox_client_localVideo.Size = new System.Drawing.Size(471, 344);
            this.picBox_client_localVideo.TabIndex = 1;
            this.picBox_client_localVideo.TabStop = false;
            // 
            // lbl_client_remoteUserName
            // 
            this.lbl_client_remoteUserName.AutoSize = true;
            this.lbl_client_remoteUserName.BackColor = System.Drawing.Color.Transparent;
            this.lbl_client_remoteUserName.Font = new System.Drawing.Font("微软雅黑", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_client_remoteUserName.Location = new System.Drawing.Point(27, 381);
            this.lbl_client_remoteUserName.Name = "lbl_client_remoteUserName";
            this.lbl_client_remoteUserName.Size = new System.Drawing.Size(195, 46);
            this.lbl_client_remoteUserName.TabIndex = 7;
            this.lbl_client_remoteUserName.Text = "对方用户名";
            // 
            // timer_speak
            // 
            this.timer_speak.Interval = 50;
            this.timer_speak.Tick += new System.EventHandler(this.timer_speak_Tick);
            // 
            // timer_call
            // 
            this.timer_call.Interval = 500;
            this.timer_call.Tick += new System.EventHandler(this.timer_call_Tick);
            // 
            // panel_area
            // 
            this.panel_area.AutoScroll = true;
            this.panel_area.BackColor = System.Drawing.Color.White;
            this.panel_area.Location = new System.Drawing.Point(6, 112);
            this.panel_area.Name = "panel_area";
            this.panel_area.Size = new System.Drawing.Size(270, 204);
            this.panel_area.TabIndex = 5;
            this.panel_area.VisibleChanged += new System.EventHandler(this.panel_area_VisibleChanged);
            // 
            // panel_queue
            // 
            this.panel_queue.AutoScroll = true;
            this.panel_queue.BackColor = System.Drawing.Color.White;
            this.panel_queue.Location = new System.Drawing.Point(11, 95);
            this.panel_queue.Name = "panel_queue";
            this.panel_queue.Size = new System.Drawing.Size(270, 204);
            this.panel_queue.TabIndex = 6;
            // 
            // panel_waitingMessage
            // 
            this.panel_waitingMessage.Controls.Add(this.lbl_waitingTime);
            this.panel_waitingMessage.Controls.Add(this.lbl_waitingMessage);
            this.panel_waitingMessage.Controls.Add(this.picBox_waiting);
            this.panel_waitingMessage.Location = new System.Drawing.Point(6, 322);
            this.panel_waitingMessage.Name = "panel_waitingMessage";
            this.panel_waitingMessage.Size = new System.Drawing.Size(515, 204);
            this.panel_waitingMessage.TabIndex = 11;
            this.panel_waitingMessage.Visible = false;
            // 
            // lbl_waitingTime
            // 
            this.lbl_waitingTime.AutoSize = true;
            this.lbl_waitingTime.Font = new System.Drawing.Font("微软雅黑", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_waitingTime.Location = new System.Drawing.Point(137, 124);
            this.lbl_waitingTime.Name = "lbl_waitingTime";
            this.lbl_waitingTime.Size = new System.Drawing.Size(160, 46);
            this.lbl_waitingTime.TabIndex = 0;
            this.lbl_waitingTime.Tag = "message";
            this.lbl_waitingTime.Text = "等待时长";
            // 
            // lbl_waitingMessage
            // 
            this.lbl_waitingMessage.AutoSize = true;
            this.lbl_waitingMessage.Font = new System.Drawing.Font("微软雅黑", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_waitingMessage.Location = new System.Drawing.Point(137, 71);
            this.lbl_waitingMessage.Name = "lbl_waitingMessage";
            this.lbl_waitingMessage.Size = new System.Drawing.Size(348, 46);
            this.lbl_waitingMessage.TabIndex = 0;
            this.lbl_waitingMessage.Tag = "message";
            this.lbl_waitingMessage.Text = "正在处理，请稍候......";
            // 
            // picBox_waiting
            // 
            this.picBox_waiting.Location = new System.Drawing.Point(3, 41);
            this.picBox_waiting.Name = "picBox_waiting";
            this.picBox_waiting.Size = new System.Drawing.Size(128, 128);
            this.picBox_waiting.TabIndex = 1;
            this.picBox_waiting.TabStop = false;
            // 
            // timer_queueWaiting
            // 
            this.timer_queueWaiting.Interval = 1000;
            this.timer_queueWaiting.Tick += new System.EventHandler(this.timer_queueWaiting_Tick);
            // 
            // panel_agentVedioCall
            // 
            this.panel_agentVedioCall.Controls.Add(this.lbl_recordFileName);
            this.panel_agentVedioCall.Controls.Add(this.btnRecord);
            this.panel_agentVedioCall.Controls.Add(this.comboBox_AgentStatus);
            this.panel_agentVedioCall.Controls.Add(this.lbl_CurrentStatus);
            this.panel_agentVedioCall.Controls.Add(this.label2);
            this.panel_agentVedioCall.Controls.Add(this.btnStopService);
            this.panel_agentVedioCall.Controls.Add(this.btnStartService);
            this.panel_agentVedioCall.Controls.Add(this.lbl_agent_atAreaUserCount);
            this.panel_agentVedioCall.Controls.Add(this.lbl_agent_servicedUserCount);
            this.panel_agentVedioCall.Controls.Add(this.lbl_agent_currentTotalUserCount);
            this.panel_agentVedioCall.Controls.Add(this.lbl_agent_queueNumber);
            this.panel_agentVedioCall.Controls.Add(this.picBox_agent_localVideo);
            this.panel_agentVedioCall.Controls.Add(this.pictureBox2);
            this.panel_agentVedioCall.Controls.Add(this.pictureBox3);
            this.panel_agentVedioCall.Controls.Add(this.label1);
            this.panel_agentVedioCall.Controls.Add(this.lbl_agent_remoteUser);
            this.panel_agentVedioCall.Controls.Add(this.picBox_agent_remoteVideo);
            this.panel_agentVedioCall.Location = new System.Drawing.Point(47, 74);
            this.panel_agentVedioCall.Name = "panel_agentVedioCall";
            this.panel_agentVedioCall.Size = new System.Drawing.Size(994, 548);
            this.panel_agentVedioCall.TabIndex = 11;
            // 
            // comboBox_AgentStatus
            // 
            this.comboBox_AgentStatus.FormattingEnabled = true;
            this.comboBox_AgentStatus.Items.AddRange(new object[] {
            "空闲",
            "忙",
            "暂停",
            "关闭"});
            this.comboBox_AgentStatus.Location = new System.Drawing.Point(485, 480);
            this.comboBox_AgentStatus.Name = "comboBox_AgentStatus";
            this.comboBox_AgentStatus.Size = new System.Drawing.Size(108, 25);
            this.comboBox_AgentStatus.TabIndex = 16;
            this.comboBox_AgentStatus.SelectedIndexChanged += new System.EventHandler(this.comboBox_AgentStatus_SelectedIndexChanged);
            // 
            // lbl_CurrentStatus
            // 
            this.lbl_CurrentStatus.AutoSize = true;
            this.lbl_CurrentStatus.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_CurrentStatus.ForeColor = System.Drawing.SystemColors.HotTrack;
            this.lbl_CurrentStatus.Location = new System.Drawing.Point(482, 514);
            this.lbl_CurrentStatus.Name = "lbl_CurrentStatus";
            this.lbl_CurrentStatus.Size = new System.Drawing.Size(68, 17);
            this.lbl_CurrentStatus.TabIndex = 15;
            this.lbl_CurrentStatus.Text = "坐席状态：";
            this.lbl_CurrentStatus.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(411, 483);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(68, 17);
            this.label2.TabIndex = 15;
            this.label2.Text = "坐席状态：";
            // 
            // btnStopService
            // 
            this.btnStopService.Location = new System.Drawing.Point(740, 470);
            this.btnStopService.Name = "btnStopService";
            this.btnStopService.Size = new System.Drawing.Size(97, 43);
            this.btnStopService.TabIndex = 14;
            this.btnStopService.Text = "结束服务";
            this.btnStopService.UseVisualStyleBackColor = true;
            this.btnStopService.Click += new System.EventHandler(this.btnStopService_Click);
            // 
            // btnStartService
            // 
            this.btnStartService.Location = new System.Drawing.Point(615, 472);
            this.btnStartService.Name = "btnStartService";
            this.btnStartService.Size = new System.Drawing.Size(97, 43);
            this.btnStartService.TabIndex = 13;
            this.btnStartService.Text = "开始服务";
            this.btnStartService.UseVisualStyleBackColor = true;
            this.btnStartService.Click += new System.EventHandler(this.btnStartService_Click);
            // 
            // lbl_agent_atAreaUserCount
            // 
            this.lbl_agent_atAreaUserCount.AutoSize = true;
            this.lbl_agent_atAreaUserCount.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_agent_atAreaUserCount.Location = new System.Drawing.Point(77, 174);
            this.lbl_agent_atAreaUserCount.Name = "lbl_agent_atAreaUserCount";
            this.lbl_agent_atAreaUserCount.Size = new System.Drawing.Size(267, 28);
            this.lbl_agent_atAreaUserCount.TabIndex = 9;
            this.lbl_agent_atAreaUserCount.Text = "未进入队列用户数为： 0 人";
            // 
            // lbl_agent_servicedUserCount
            // 
            this.lbl_agent_servicedUserCount.AutoSize = true;
            this.lbl_agent_servicedUserCount.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_agent_servicedUserCount.Location = new System.Drawing.Point(77, 211);
            this.lbl_agent_servicedUserCount.Name = "lbl_agent_servicedUserCount";
            this.lbl_agent_servicedUserCount.Size = new System.Drawing.Size(204, 28);
            this.lbl_agent_servicedUserCount.TabIndex = 9;
            this.lbl_agent_servicedUserCount.Text = "已服务人数为： 0 人";
            // 
            // lbl_agent_currentTotalUserCount
            // 
            this.lbl_agent_currentTotalUserCount.AutoSize = true;
            this.lbl_agent_currentTotalUserCount.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_agent_currentTotalUserCount.Location = new System.Drawing.Point(77, 137);
            this.lbl_agent_currentTotalUserCount.Name = "lbl_agent_currentTotalUserCount";
            this.lbl_agent_currentTotalUserCount.Size = new System.Drawing.Size(288, 28);
            this.lbl_agent_currentTotalUserCount.TabIndex = 9;
            this.lbl_agent_currentTotalUserCount.Text = "当前排队的用户总数为： 0 人";
            // 
            // lbl_agent_queueNumber
            // 
            this.lbl_agent_queueNumber.AutoSize = true;
            this.lbl_agent_queueNumber.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_agent_queueNumber.Location = new System.Drawing.Point(77, 94);
            this.lbl_agent_queueNumber.Name = "lbl_agent_queueNumber";
            this.lbl_agent_queueNumber.Size = new System.Drawing.Size(282, 28);
            this.lbl_agent_queueNumber.TabIndex = 9;
            this.lbl_agent_queueNumber.Text = "当前服务的队列数量为：0 个";
            // 
            // picBox_agent_localVideo
            // 
            this.picBox_agent_localVideo.BackColor = System.Drawing.Color.Orange;
            this.picBox_agent_localVideo.BackgroundImage = global::QueueClient.Properties.Resources.videobk_agent_local;
            this.picBox_agent_localVideo.Location = new System.Drawing.Point(81, 263);
            this.picBox_agent_localVideo.Name = "picBox_agent_localVideo";
            this.picBox_agent_localVideo.Size = new System.Drawing.Size(300, 225);
            this.picBox_agent_localVideo.TabIndex = 0;
            this.picBox_agent_localVideo.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Location = new System.Drawing.Point(81, 492);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(300, 5);
            this.pictureBox2.TabIndex = 4;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox3
            // 
            this.pictureBox3.Location = new System.Drawing.Point(490, 442);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(471, 5);
            this.pictureBox3.TabIndex = 6;
            this.pictureBox3.TabStop = false;
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(53, 40);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(305, 42);
            this.label1.TabIndex = 8;
            this.label1.Text = "服务信息";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lbl_agent_remoteUser
            // 
            this.lbl_agent_remoteUser.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lbl_agent_remoteUser.BackColor = System.Drawing.Color.Transparent;
            this.lbl_agent_remoteUser.Font = new System.Drawing.Font("微软雅黑", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_agent_remoteUser.Location = new System.Drawing.Point(467, 58);
            this.lbl_agent_remoteUser.Name = "lbl_agent_remoteUser";
            this.lbl_agent_remoteUser.Size = new System.Drawing.Size(471, 28);
            this.lbl_agent_remoteUser.TabIndex = 8;
            this.lbl_agent_remoteUser.Text = "当前服务用户：";
            this.lbl_agent_remoteUser.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // picBox_agent_remoteVideo
            // 
            this.picBox_agent_remoteVideo.BackColor = System.Drawing.Color.Orange;
            this.picBox_agent_remoteVideo.BackgroundImage = global::QueueClient.Properties.Resources.videobk;
            this.picBox_agent_remoteVideo.Location = new System.Drawing.Point(490, 94);
            this.picBox_agent_remoteVideo.Name = "picBox_agent_remoteVideo";
            this.picBox_agent_remoteVideo.Size = new System.Drawing.Size(471, 344);
            this.picBox_agent_remoteVideo.TabIndex = 1;
            this.picBox_agent_remoteVideo.TabStop = false;
            // 
            // btnRecord
            // 
            this.btnRecord.Location = new System.Drawing.Point(864, 470);
            this.btnRecord.Name = "btnRecord";
            this.btnRecord.Size = new System.Drawing.Size(97, 43);
            this.btnRecord.TabIndex = 17;
            this.btnRecord.Text = "开始录像";
            this.btnRecord.UseVisualStyleBackColor = true;
            this.btnRecord.Click += new System.EventHandler(this.btnRecord_Click);
            // 
            // lbl_recordFileName
            // 
            this.lbl_recordFileName.AutoSize = true;
            this.lbl_recordFileName.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_recordFileName.ForeColor = System.Drawing.SystemColors.HotTrack;
            this.lbl_recordFileName.Location = new System.Drawing.Point(22, 514);
            this.lbl_recordFileName.Name = "lbl_recordFileName";
            this.lbl_recordFileName.Size = new System.Drawing.Size(0, 17);
            this.lbl_recordFileName.TabIndex = 18;
            this.lbl_recordFileName.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // frmHall
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(1041, 689);
            this.Controls.Add(this.panel_agentVedioCall);
            this.Controls.Add(this.panel_waitingMessage);
            this.Controls.Add(this.panel_call);
            this.Controls.Add(this.panel_area);
            this.Controls.Add(this.panel_queue);
            this.Controls.Add(this.panel_conversation);
            this.Controls.Add(this.panel_users);
            this.Controls.Add(this.panel_top);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.Name = "frmHall";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "AnyChat智能排队示例程序";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Hall_FormClosed);
            this.Load += new System.EventHandler(this.Hall_Load);
            this.Shown += new System.EventHandler(this.Hall_Shown);
            this.panel_top.ResumeLayout(false);
            this.panel_top.PerformLayout();
            this.panel_call.ResumeLayout(false);
            this.panel_call.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pic_call)).EndInit();
            this.panel_conversation.ResumeLayout(false);
            this.panel_userVedioCall.ResumeLayout(false);
            this.panel_userVedioCall.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_client_remoteVideo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_tuserSound)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_suserSound)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_client_localVideo)).EndInit();
            this.panel_waitingMessage.ResumeLayout(false);
            this.panel_waitingMessage.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_waiting)).EndInit();
            this.panel_agentVedioCall.ResumeLayout(false);
            this.panel_agentVedioCall.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_agent_localVideo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picBox_agent_remoteVideo)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label lbl_tipMessage;
        private System.Windows.Forms.Panel panel_top;
        private System.Windows.Forms.Panel panel_users;
        private System.Windows.Forms.Panel panel_call;
        private System.Windows.Forms.Label lb_call;
        private System.Windows.Forms.PictureBox pic_call;
        private System.Windows.Forms.Panel panel_conversation;
        private System.Windows.Forms.PictureBox picBox_client_localVideo;
        private System.Windows.Forms.PictureBox picBox_client_remoteVideo;
        private System.Windows.Forms.PictureBox pic_suserSound;
        private System.Windows.Forms.PictureBox pic_tuserSound;
        private System.Windows.Forms.Label lbl_client_localUserName;
        private System.Windows.Forms.Label lbl_client_remoteUserName;
        private System.Windows.Forms.Button btn_hungUp;
        private System.Windows.Forms.Timer timer_speak;
        private System.Windows.Forms.Panel panel_userVedioCall;
        private System.Windows.Forms.Timer timer_call;
        private System.Windows.Forms.Panel panel_area;
        private System.Windows.Forms.Panel panel_queue;
        private System.Windows.Forms.Panel panel_waitingMessage;
        private System.Windows.Forms.Label lbl_waitingMessage;
        private System.Windows.Forms.PictureBox picBox_waiting;
        private System.Windows.Forms.Button btn_return;
        private System.Windows.Forms.Timer timer_queueWaiting;
        private System.Windows.Forms.Panel panel_agentVedioCall;
        private System.Windows.Forms.PictureBox picBox_agent_localVideo;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.Label lbl_agent_remoteUser;
        private System.Windows.Forms.PictureBox picBox_agent_remoteVideo;
        private System.Windows.Forms.Label lbl_agent_servicedUserCount;
        private System.Windows.Forms.Label lbl_agent_currentTotalUserCount;
        private System.Windows.Forms.Label lbl_agent_queueNumber;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnStopService;
        private System.Windows.Forms.Button btnStartService;
        private System.Windows.Forms.Label lbl_waitingTime;
        private System.Windows.Forms.Label lbl_agent_atAreaUserCount;
        private System.Windows.Forms.ComboBox comboBox_AgentStatus;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lbl_CurrentStatus;
        private System.Windows.Forms.Button btnRecord;
        private System.Windows.Forms.Label lbl_recordFileName;
    }
}