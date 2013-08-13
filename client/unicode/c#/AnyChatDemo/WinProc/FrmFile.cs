using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WinProc
{
    public partial class FrmFile : Form
    {
        public FrmFile()
        {
            InitializeComponent();
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            if (this.openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                this.tbxPath.Text = "";
                this.tbxPath.Text = openFileDialog1.FileName;
            }
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            string filepath = this.tbxPath.Text;
            try
            {
                if (filepath != "" && System.IO.File.Exists(filepath))
                {
                     FileInfo fileinfo = new FileInfo(filepath);
                    if (fileinfo.Length < 1024 * 1024 * 10)
                    {
                        
                    }
                    else
                    {
                        
                        MessageBox.Show("不允许发送大于10M的文件！",
                        "提示！", MessageBoxButtons.OK, MessageBoxIcon.Information);                  
                        return;
                    }
                    DialogResult = DialogResult.OK;
                    this.tbxPath.Clear();
                }
                else
                {
                    MessageBox.Show("不能没有文件！", "提示！", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private void btnCanCel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }
    }
}
