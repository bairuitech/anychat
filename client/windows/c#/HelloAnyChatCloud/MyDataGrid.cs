using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace AnyChatCSharpDemo
{
    class MyDataGrid : DataGridView
    {
        protected override void PaintBackground(Graphics graphics, Rectangle clipBounds, Rectangle gridBounds)
        {
            graphics.DrawImageUnscaledAndClipped(this.BackgroundImage, gridBounds);
        }

        protected override void OnCellPainting(DataGridViewCellPaintingEventArgs e)
        {
            if (e.RowIndex == -1 || e.ColumnIndex == -1)
            {
                return;

            }
            Rectangle newRect = new Rectangle(e.CellBounds.X + 1,
                e.CellBounds.Y + 1, e.CellBounds.Width - 4,
                e.CellBounds.Height - 4);

            using (
                Brush gridBrush = new SolidBrush(this.GridColor),
                backColorBrush = new SolidBrush(e.CellStyle.BackColor),

                selectedColorBrush = new SolidBrush(e.CellStyle.SelectionBackColor))
            {
                using (Pen gridLinePen = new Pen(gridBrush))
                {
                    if (this.Rows[e.RowIndex].Selected)
                    {
                        e.Graphics.FillRectangle(selectedColorBrush, e.CellBounds);
                    }
                    else
                    {
                        e.Graphics.FillRectangle(backColorBrush, e.CellBounds);
                    }
                    if (e.Value != null)
                    {
                        e.Graphics.DrawString((String)e.Value, e.CellStyle.Font,
                            Brushes.Black, e.CellBounds.X + 2,
                            e.CellBounds.Y + 2, StringFormat.GenericDefault);
                    }
                }
                e.Handled = true;
            }
        }
    }
}
