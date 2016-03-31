namespace AnyChatCSharpDemo
{
    partial class frmRoom
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmRoom));
            this.txt_Accept = new System.Windows.Forms.RichTextBox();
            this.pnl_video = new System.Windows.Forms.Panel();
            this.pnl_local = new System.Windows.Forms.Panel();
            this.pnl_userlist = new System.Windows.Forms.Panel();
            this.dgv_onlineuser = new System.Windows.Forms.DataGridView();
            this.gvc_character = new System.Windows.Forms.DataGridViewImageColumn();
            this.gvc_username = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.gvc_audio = new System.Windows.Forms.DataGridViewImageColumn();
            this.gvc_video = new System.Windows.Forms.DataGridViewImageColumn();
            this.menu_user = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.menu_item_video = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_audio = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_item_status = new System.Windows.Forms.ToolStripMenuItem();
            this.pic_userlistdisp = new System.Windows.Forms.PictureBox();
            this.rtxt_sendtxt = new System.Windows.Forms.RichTextBox();
            this.btn_sendtxt = new System.Windows.Forms.Button();
            this.menu_sendtxt = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.ment_item_ctrlenter = new System.Windows.Forms.ToolStripMenuItem();
            this.ment_item_enter = new System.Windows.Forms.ToolStripMenuItem();
            this.lbl_touser = new System.Windows.Forms.Label();
            this.cmb_font = new System.Windows.Forms.ComboBox();
            this.pal_wordcolor = new System.Windows.Forms.Panel();
            this.cmb_fontsize = new System.Windows.Forms.ComboBox();
            this.btn_transfile = new System.Windows.Forms.Button();
            this.lbl_progress = new System.Windows.Forms.Label();
            this.tmr_receivefile = new System.Windows.Forms.Timer(this.components);
            this.lbl_speed = new System.Windows.Forms.Label();
            this.pnl_word = new System.Windows.Forms.Panel();
            this.pnl_visableword = new System.Windows.Forms.Panel();
            this.chk_localvideo = new System.Windows.Forms.CheckBox();
            this.chk_localaudio = new System.Windows.Forms.CheckBox();
            this.lbl_v_speed = new System.Windows.Forms.Label();
            this.lbl_a_speed = new System.Windows.Forms.Label();
            this.lb_fbl = new System.Windows.Forms.Label();
            this.cbb_fbl = new System.Windows.Forms.ComboBox();
            this.btnSetting = new System.Windows.Forms.Button();
            this.pnl_userlist.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_onlineuser)).BeginInit();
            this.menu_user.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pic_userlistdisp)).BeginInit();
            this.menu_sendtxt.SuspendLayout();
            this.pnl_word.SuspendLayout();
            this.SuspendLayout();
            // 
            // txt_Accept
            // 
            this.txt_Accept.BackColor = System.Drawing.Color.White;
            this.txt_Accept.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.txt_Accept.Location = new System.Drawing.Point(10, 3);
            this.txt_Accept.Name = "txt_Accept";
            this.txt_Accept.Size = new System.Drawing.Size(307, 474);
            this.txt_Accept.TabIndex = 0;
            this.txt_Accept.Text = "";
            // 
            // pnl_video
            // 
            this.pnl_video.BackColor = System.Drawing.Color.Gainsboro;
            this.pnl_video.Location = new System.Drawing.Point(169, 23);
            this.pnl_video.Name = "pnl_video";
            this.pnl_video.Size = new System.Drawing.Size(480, 384);
            this.pnl_video.TabIndex = 1;
            // 
            // pnl_local
            // 
            this.pnl_local.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.pnl_local.Location = new System.Drawing.Point(3, 471);
            this.pnl_local.Name = "pnl_local";
            this.pnl_local.Size = new System.Drawing.Size(167, 140);
            this.pnl_local.TabIndex = 2;
            this.pnl_local.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.pnl_local_MouseDoubleClick);
            // 
            // pnl_userlist
            // 
            this.pnl_userlist.Controls.Add(this.dgv_onlineuser);
            this.pnl_userlist.Controls.Add(this.pic_userlistdisp);
            this.pnl_userlist.Location = new System.Drawing.Point(0, 22);
            this.pnl_userlist.Name = "pnl_userlist";
            this.pnl_userlist.Size = new System.Drawing.Size(170, 443);
            this.pnl_userlist.TabIndex = 4;
            // 
            // dgv_onlineuser
            // 
            this.dgv_onlineuser.AllowUserToAddRows = false;
            this.dgv_onlineuser.AllowUserToDeleteRows = false;
            this.dgv_onlineuser.BackgroundColor = System.Drawing.Color.White;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.Color.LightSeaGreen;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dgv_onlineuser.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dgv_onlineuser.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgv_onlineuser.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.gvc_character,
            this.gvc_username,
            this.gvc_audio,
            this.gvc_video});
            this.dgv_onlineuser.ContextMenuStrip = this.menu_user;
            this.dgv_onlineuser.Location = new System.Drawing.Point(0, 1);
            this.dgv_onlineuser.MultiSelect = false;
            this.dgv_onlineuser.Name = "dgv_onlineuser";
            this.dgv_onlineuser.ReadOnly = true;
            this.dgv_onlineuser.RowHeadersVisible = false;
            this.dgv_onlineuser.RowTemplate.Height = 23;
            this.dgv_onlineuser.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgv_onlineuser.Size = new System.Drawing.Size(167, 439);
            this.dgv_onlineuser.TabIndex = 5;
            this.dgv_onlineuser.SelectionChanged += new System.EventHandler(this.dgv_onlineuser_SelectionChanged);
            this.dgv_onlineuser.Click += new System.EventHandler(this.dgv_onlineuser_Click);
            // 
            // gvc_character
            // 
            this.gvc_character.FillWeight = 20F;
            this.gvc_character.HeaderText = "";
            this.gvc_character.ImageLayout = System.Windows.Forms.DataGridViewImageCellLayout.Stretch;
            this.gvc_character.Name = "gvc_character";
            this.gvc_character.ReadOnly = true;
            this.gvc_character.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.gvc_character.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.gvc_character.Width = 20;
            // 
            // gvc_username
            // 
            this.gvc_username.HeaderText = "账号";
            this.gvc_username.Name = "gvc_username";
            this.gvc_username.ReadOnly = true;
            // 
            // gvc_audio
            // 
            this.gvc_audio.HeaderText = "音";
            this.gvc_audio.ImageLayout = System.Windows.Forms.DataGridViewImageCellLayout.Stretch;
            this.gvc_audio.Name = "gvc_audio";
            this.gvc_audio.ReadOnly = true;
            this.gvc_audio.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.gvc_audio.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            this.gvc_audio.ToolTipText = "音";
            this.gvc_audio.Width = 20;
            // 
            // gvc_video
            // 
            this.gvc_video.HeaderText = "视";
            this.gvc_video.ImageLayout = System.Windows.Forms.DataGridViewImageCellLayout.Stretch;
            this.gvc_video.Name = "gvc_video";
            this.gvc_video.ReadOnly = true;
            this.gvc_video.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.gvc_video.ToolTipText = "视";
            this.gvc_video.Width = 20;
            // 
            // menu_user
            // 
            this.menu_user.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_item_video,
            this.menu_item_audio,
            this.menu_item_status});
            this.menu_user.Name = "menu_user";
            this.menu_user.Size = new System.Drawing.Size(101, 70);
            // 
            // menu_item_video
            // 
            this.menu_item_video.CheckOnClick = true;
            this.menu_item_video.Name = "menu_item_video";
            this.menu_item_video.Size = new System.Drawing.Size(100, 22);
            this.menu_item_video.Text = "视频";
            this.menu_item_video.Click += new System.EventHandler(this.menu_item_video_Click);
            // 
            // menu_item_audio
            // 
            this.menu_item_audio.CheckOnClick = true;
            this.menu_item_audio.Name = "menu_item_audio";
            this.menu_item_audio.Size = new System.Drawing.Size(100, 22);
            this.menu_item_audio.Text = "语音";
            // 
            // menu_item_status
            // 
            this.menu_item_status.Name = "menu_item_status";
            this.menu_item_status.Size = new System.Drawing.Size(100, 22);
            this.menu_item_status.Text = "状态";
            this.menu_item_status.Click += new System.EventHandler(this.menu_item_status_Click);
            // 
            // pic_userlistdisp
            // 
            this.pic_userlistdisp.BackColor = System.Drawing.Color.Green;
            this.pic_userlistdisp.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pic_userlistdisp.Dock = System.Windows.Forms.DockStyle.Left;
            this.pic_userlistdisp.Location = new System.Drawing.Point(0, 0);
            this.pic_userlistdisp.Name = "pic_userlistdisp";
            this.pic_userlistdisp.Size = new System.Drawing.Size(25, 443);
            this.pic_userlistdisp.TabIndex = 4;
            this.pic_userlistdisp.TabStop = false;
            this.pic_userlistdisp.Visible = false;
            this.pic_userlistdisp.Click += new System.EventHandler(this.pic_userlistdisp_Click);
            // 
            // rtxt_sendtxt
            // 
            this.rtxt_sendtxt.Location = new System.Drawing.Point(171, 504);
            this.rtxt_sendtxt.Name = "rtxt_sendtxt";
            this.rtxt_sendtxt.Size = new System.Drawing.Size(480, 107);
            this.rtxt_sendtxt.TabIndex = 5;
            this.rtxt_sendtxt.Text = "";
            this.rtxt_sendtxt.KeyDown += new System.Windows.Forms.KeyEventHandler(this.rtxt_sendtxt_KeyDown);
            this.rtxt_sendtxt.KeyUp += new System.Windows.Forms.KeyEventHandler(this.rtxt_sendtxt_KeyUp);
            // 
            // btn_sendtxt
            // 
            this.btn_sendtxt.ContextMenuStrip = this.menu_sendtxt;
            this.btn_sendtxt.Location = new System.Drawing.Point(576, 624);
            this.btn_sendtxt.Name = "btn_sendtxt";
            this.btn_sendtxt.Size = new System.Drawing.Size(75, 23);
            this.btn_sendtxt.TabIndex = 6;
            this.btn_sendtxt.Text = "发送";
            this.btn_sendtxt.UseVisualStyleBackColor = true;
            this.btn_sendtxt.Click += new System.EventHandler(this.btn_sendtxt_Click);
            // 
            // menu_sendtxt
            // 
            this.menu_sendtxt.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ment_item_ctrlenter,
            this.ment_item_enter});
            this.menu_sendtxt.Name = "menu_sendtxt";
            this.menu_sendtxt.Size = new System.Drawing.Size(136, 48);
            // 
            // ment_item_ctrlenter
            // 
            this.ment_item_ctrlenter.Name = "ment_item_ctrlenter";
            this.ment_item_ctrlenter.Size = new System.Drawing.Size(135, 22);
            this.ment_item_ctrlenter.Text = "Ctlr+Enter";
            this.ment_item_ctrlenter.Click += new System.EventHandler(this.ment_item_ctrlenter_Click);
            // 
            // ment_item_enter
            // 
            this.ment_item_enter.Name = "ment_item_enter";
            this.ment_item_enter.Size = new System.Drawing.Size(135, 22);
            this.ment_item_enter.Text = "Enter";
            this.ment_item_enter.Click += new System.EventHandler(this.ment_item_enter_Click);
            // 
            // lbl_touser
            // 
            this.lbl_touser.AutoSize = true;
            this.lbl_touser.Location = new System.Drawing.Point(174, 476);
            this.lbl_touser.Name = "lbl_touser";
            this.lbl_touser.Size = new System.Drawing.Size(95, 12);
            this.lbl_touser.TabIndex = 8;
            this.lbl_touser.Text = "我 对 大家 说：";
            // 
            // cmb_font
            // 
            this.cmb_font.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmb_font.FormattingEnabled = true;
            this.cmb_font.Location = new System.Drawing.Point(297, 471);
            this.cmb_font.Name = "cmb_font";
            this.cmb_font.Size = new System.Drawing.Size(78, 20);
            this.cmb_font.TabIndex = 13;
            // 
            // pal_wordcolor
            // 
            this.pal_wordcolor.BackColor = System.Drawing.Color.Black;
            this.pal_wordcolor.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pal_wordcolor.Location = new System.Drawing.Point(432, 471);
            this.pal_wordcolor.Name = "pal_wordcolor";
            this.pal_wordcolor.Size = new System.Drawing.Size(20, 20);
            this.pal_wordcolor.TabIndex = 15;
            // 
            // cmb_fontsize
            // 
            this.cmb_fontsize.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmb_fontsize.FormattingEnabled = true;
            this.cmb_fontsize.Location = new System.Drawing.Point(378, 471);
            this.cmb_fontsize.Name = "cmb_fontsize";
            this.cmb_fontsize.Size = new System.Drawing.Size(52, 20);
            this.cmb_fontsize.TabIndex = 14;
            // 
            // btn_transfile
            // 
            this.btn_transfile.Location = new System.Drawing.Point(458, 471);
            this.btn_transfile.Name = "btn_transfile";
            this.btn_transfile.Size = new System.Drawing.Size(75, 23);
            this.btn_transfile.TabIndex = 16;
            this.btn_transfile.Text = "传送文件";
            this.btn_transfile.UseVisualStyleBackColor = true;
            this.btn_transfile.Click += new System.EventHandler(this.btn_transfile_Click);
            // 
            // lbl_progress
            // 
            this.lbl_progress.AutoSize = true;
            this.lbl_progress.Location = new System.Drawing.Point(554, 476);
            this.lbl_progress.Name = "lbl_progress";
            this.lbl_progress.Size = new System.Drawing.Size(0, 12);
            this.lbl_progress.TabIndex = 17;
            // 
            // tmr_receivefile
            // 
            this.tmr_receivefile.Enabled = true;
            this.tmr_receivefile.Interval = 1000;
            this.tmr_receivefile.Tick += new System.EventHandler(this.tmr_receivefile_Tick);
            // 
            // lbl_speed
            // 
            this.lbl_speed.AutoSize = true;
            this.lbl_speed.Location = new System.Drawing.Point(593, 479);
            this.lbl_speed.Name = "lbl_speed";
            this.lbl_speed.Size = new System.Drawing.Size(0, 12);
            this.lbl_speed.TabIndex = 19;
            // 
            // pnl_word
            // 
            this.pnl_word.BackColor = System.Drawing.Color.Transparent;
            this.pnl_word.Controls.Add(this.pnl_visableword);
            this.pnl_word.Controls.Add(this.txt_Accept);
            this.pnl_word.Location = new System.Drawing.Point(655, 23);
            this.pnl_word.Name = "pnl_word";
            this.pnl_word.Size = new System.Drawing.Size(322, 480);
            this.pnl_word.TabIndex = 20;
            // 
            // pnl_visableword
            // 
            this.pnl_visableword.BackgroundImage = global::AnyChatCSharpDemo.Properties.Resources.隐藏发送面板;
            this.pnl_visableword.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pnl_visableword.Cursor = System.Windows.Forms.Cursors.Hand;
            this.pnl_visableword.Location = new System.Drawing.Point(1, 216);
            this.pnl_visableword.Name = "pnl_visableword";
            this.pnl_visableword.Size = new System.Drawing.Size(7, 45);
            this.pnl_visableword.TabIndex = 1;
            this.pnl_visableword.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pnl_visableword_MouseDown);
            this.pnl_visableword.MouseEnter += new System.EventHandler(this.pnl_visableword_MouseEnter);
            this.pnl_visableword.MouseLeave += new System.EventHandler(this.pnl_visableword_MouseLeave);
            this.pnl_visableword.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pnl_visableword_MouseUp);
            // 
            // chk_localvideo
            // 
            this.chk_localvideo.AutoSize = true;
            this.chk_localvideo.BackColor = System.Drawing.Color.Transparent;
            this.chk_localvideo.Location = new System.Drawing.Point(7, 654);
            this.chk_localvideo.Name = "chk_localvideo";
            this.chk_localvideo.Size = new System.Drawing.Size(48, 16);
            this.chk_localvideo.TabIndex = 21;
            this.chk_localvideo.Text = "视频";
            this.chk_localvideo.UseVisualStyleBackColor = false;
            this.chk_localvideo.CheckedChanged += new System.EventHandler(this.chk_localvideo_CheckedChanged);
            // 
            // chk_localaudio
            // 
            this.chk_localaudio.AutoSize = true;
            this.chk_localaudio.Location = new System.Drawing.Point(61, 654);
            this.chk_localaudio.Name = "chk_localaudio";
            this.chk_localaudio.Size = new System.Drawing.Size(48, 16);
            this.chk_localaudio.TabIndex = 21;
            this.chk_localaudio.Text = "音频";
            this.chk_localaudio.UseVisualStyleBackColor = true;
            this.chk_localaudio.CheckedChanged += new System.EventHandler(this.chk_localaudio_CheckedChanged);
            // 
            // lbl_v_speed
            // 
            this.lbl_v_speed.AutoSize = true;
            this.lbl_v_speed.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_v_speed.ForeColor = System.Drawing.Color.LimeGreen;
            this.lbl_v_speed.Location = new System.Drawing.Point(115, 655);
            this.lbl_v_speed.Name = "lbl_v_speed";
            this.lbl_v_speed.Size = new System.Drawing.Size(98, 12);
            this.lbl_v_speed.TabIndex = 22;
            this.lbl_v_speed.Text = "视频码率：0B/S";
            // 
            // lbl_a_speed
            // 
            this.lbl_a_speed.AutoSize = true;
            this.lbl_a_speed.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_a_speed.ForeColor = System.Drawing.Color.LimeGreen;
            this.lbl_a_speed.Location = new System.Drawing.Point(251, 655);
            this.lbl_a_speed.Name = "lbl_a_speed";
            this.lbl_a_speed.Size = new System.Drawing.Size(98, 12);
            this.lbl_a_speed.TabIndex = 22;
            this.lbl_a_speed.Text = "音频码率：0B/S";
            // 
            // lb_fbl
            // 
            this.lb_fbl.AutoSize = true;
            this.lb_fbl.Location = new System.Drawing.Point(5, 624);
            this.lb_fbl.Name = "lb_fbl";
            this.lb_fbl.Size = new System.Drawing.Size(77, 12);
            this.lb_fbl.TabIndex = 23;
            this.lb_fbl.Text = "视频质量设置";
            // 
            // cbb_fbl
            // 
            this.cbb_fbl.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbb_fbl.FormattingEnabled = true;
            this.cbb_fbl.Items.AddRange(new object[] {
            "服务器默认",
            "本地设置"});
            this.cbb_fbl.Location = new System.Drawing.Point(88, 621);
            this.cbb_fbl.Name = "cbb_fbl";
            this.cbb_fbl.Size = new System.Drawing.Size(82, 20);
            this.cbb_fbl.TabIndex = 24;
            this.cbb_fbl.SelectedIndexChanged += new System.EventHandler(this.cbb_fbl_SelectedIndexChanged);
            // 
            // btnSetting
            // 
            this.btnSetting.Location = new System.Drawing.Point(458, 624);
            this.btnSetting.Name = "btnSetting";
            this.btnSetting.Size = new System.Drawing.Size(85, 23);
            this.btnSetting.TabIndex = 25;
            this.btnSetting.Text = "高级设置";
            this.btnSetting.UseVisualStyleBackColor = true;
            this.btnSetting.Click += new System.EventHandler(this.btnSetting_Click);
            // 
            // frmRoom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(230)))), ((int)(((byte)(230)))), ((int)(((byte)(230)))));
            this.ClientSize = new System.Drawing.Size(984, 682);
            this.Controls.Add(this.btnSetting);
            this.Controls.Add(this.lb_fbl);
            this.Controls.Add(this.lbl_a_speed);
            this.Controls.Add(this.cbb_fbl);
            this.Controls.Add(this.lbl_v_speed);
            this.Controls.Add(this.chk_localaudio);
            this.Controls.Add(this.chk_localvideo);
            this.Controls.Add(this.pnl_word);
            this.Controls.Add(this.pnl_video);
            this.Controls.Add(this.pnl_userlist);
            this.Controls.Add(this.lbl_speed);
            this.Controls.Add(this.btn_transfile);
            this.Controls.Add(this.lbl_touser);
            this.Controls.Add(this.lbl_progress);
            this.Controls.Add(this.pnl_local);
            this.Controls.Add(this.pal_wordcolor);
            this.Controls.Add(this.cmb_font);
            this.Controls.Add(this.rtxt_sendtxt);
            this.Controls.Add(this.cmb_fontsize);
            this.Controls.Add(this.btn_sendtxt);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "frmRoom";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "HelloAnyChatCloud";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmRoom_FormClosing);
            this.Load += new System.EventHandler(this.frmRoom_Load);
            this.pnl_userlist.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgv_onlineuser)).EndInit();
            this.menu_user.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pic_userlistdisp)).EndInit();
            this.menu_sendtxt.ResumeLayout(false);
            this.pnl_word.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox txt_Accept;
        private System.Windows.Forms.Panel pnl_video;
        private System.Windows.Forms.Panel pnl_local;
        private System.Windows.Forms.Panel pnl_userlist;
        private System.Windows.Forms.PictureBox pic_userlistdisp;
        private System.Windows.Forms.RichTextBox rtxt_sendtxt;
        private System.Windows.Forms.Button btn_sendtxt;
        private System.Windows.Forms.ContextMenuStrip menu_sendtxt;
        private System.Windows.Forms.ToolStripMenuItem ment_item_ctrlenter;
        private System.Windows.Forms.ToolStripMenuItem ment_item_enter;
        private System.Windows.Forms.Label lbl_touser;
        private System.Windows.Forms.DataGridView dgv_onlineuser;
        private System.Windows.Forms.ComboBox cmb_font;
        private System.Windows.Forms.Panel pal_wordcolor;
        private System.Windows.Forms.ComboBox cmb_fontsize;
        private System.Windows.Forms.DataGridViewImageColumn gvc_character;
        private System.Windows.Forms.DataGridViewTextBoxColumn gvc_username;
        private System.Windows.Forms.DataGridViewImageColumn gvc_audio;
        private System.Windows.Forms.DataGridViewImageColumn gvc_video;
        private System.Windows.Forms.ContextMenuStrip menu_user;
        private System.Windows.Forms.ToolStripMenuItem menu_item_video;
        private System.Windows.Forms.ToolStripMenuItem menu_item_audio;
        private System.Windows.Forms.Button btn_transfile;
        private System.Windows.Forms.Label lbl_progress;
        private System.Windows.Forms.Timer tmr_receivefile;
        private System.Windows.Forms.ToolStripMenuItem menu_item_status;
        private System.Windows.Forms.Label lbl_speed;
        private System.Windows.Forms.Panel pnl_word;
        private System.Windows.Forms.Panel pnl_visableword;
        private System.Windows.Forms.CheckBox chk_localvideo;
        private System.Windows.Forms.CheckBox chk_localaudio;
        private System.Windows.Forms.Label lbl_v_speed;
        private System.Windows.Forms.Label lbl_a_speed;
        private System.Windows.Forms.Label lb_fbl;
        private System.Windows.Forms.ComboBox cbb_fbl;
        private System.Windows.Forms.Button btnSetting;
    }
}