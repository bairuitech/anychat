using System;
using System.Collections.Generic;
using System.Text;

namespace ANYCHATAPI
{
    /// <summary>
    /// 下拉列表Item类
    /// </summary>
    public class ComboBoxItem
    {
        /// <summary>
        /// 显示文字
        /// </summary>
        public string Text { get; set; }
        /// <summary>
        /// item对应值
        /// </summary>
        public object Value { get; set; }

        public override string ToString()
        {
            return Text;
        }
    }
}
