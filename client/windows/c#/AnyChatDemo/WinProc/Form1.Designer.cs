namespace WinProc
{
    partial class Form1
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
            this.tabcontrol1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.LvwUserList = new System.Windows.Forms.ListView();
            this.LvwMeeting = new System.Windows.Forms.ListView();
            this.tabcontrol1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabcontrol1
            // 
            this.tabcontrol1.Controls.Add(this.tabPage1);
            this.tabcontrol1.Controls.Add(this.tabPage2);
            this.tabcontrol1.Location = new System.Drawing.Point(3, 3);
            this.tabcontrol1.Name = "tabcontrol1";
            this.tabcontrol1.SelectedIndex = 0;
            this.tabcontrol1.Size = new System.Drawing.Size(223, 440);
            this.tabcontrol1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.LvwUserList);
            this.tabPage1.Location = new System.Drawing.Point(4, 21);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(215, 415);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "在线用户";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.LvwMeeting);
            this.tabPage2.Location = new System.Drawing.Point(4, 21);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(215, 415);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "会议室";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // LvwUserList
            // 
            this.LvwUserList.Location = new System.Drawing.Point(5, 3);
            this.LvwUserList.Name = "LvwUserList";
            this.LvwUserList.Size = new System.Drawing.Size(207, 412);
            this.LvwUserList.TabIndex = 0;
            this.LvwUserList.UseCompatibleStateImageBehavior = false;
            // 
            // LvwMeeting
            // 
            this.LvwMeeting.Location = new System.Drawing.Point(3, 6);
            this.LvwMeeting.Name = "LvwMeeting";
            this.LvwMeeting.Size = new System.Drawing.Size(209, 403);
            this.LvwMeeting.TabIndex = 0;
            this.LvwMeeting.UseCompatibleStateImageBehavior = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(224, 443);
            this.Controls.Add(this.tabcontrol1);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "音视频会商";
            this.tabcontrol1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabcontrol1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.ListView LvwUserList;
        private System.Windows.Forms.ListView LvwMeeting;
    }
}

