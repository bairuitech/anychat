using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace AnyChatCSharpDemo
{
    public partial class frmHall : Form
    {
        public frmHall()
        {
            InitializeComponent();
            //richtextbox
            this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.UserPaint | ControlStyles.OptimizedDoubleBuffer, true);
            

            //datagridview
            this.dataGridView1.BackgroundImage = Image.FromFile("e:\\123.jpg");
            this.dataGridView1.DefaultCellStyle.BackColor = Color.FromArgb(128, Color.White);
            this.dataGridView1.DefaultCellStyle.SelectionBackColor = Color.FromArgb(128, Color.Blue);

           

        }

        
    }
}