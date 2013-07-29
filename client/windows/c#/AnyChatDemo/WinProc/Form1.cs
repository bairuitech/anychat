using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Platform;
namespace WinProc
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        void InitChat()
        {

            Platform.SystemSetting.Init(this.Handle);
            Platform.AnyChatCoreSDK.Connect("169.254.118.13",8906);
        }

        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
        }
    }
}
