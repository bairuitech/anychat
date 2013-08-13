using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace AnyChatCSharpDemo
{
    class TransparentRichTextBox : RichTextBox
    {
        public TransparentRichTextBox()
        {
            //base.ScrollBars = RichTextBoxScrollBars.None ;
        }

        override protected CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.ExStyle |= 0x20;
                return cp;
            }
        }
 
    }
}
