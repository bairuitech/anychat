using System;
using System.Collections.Generic;
using System.Text;

namespace VideoChatHelp
{
    public class ParamInfo
    {
        public ParamInfo(string name, string value)
        {
            this.name = name;
            this.value = value;
        }

        private string name;
        /// <summary>
        /// 参数名
        /// </summary>
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        private string value;
        /// <summary>
        /// 参数值
        /// </summary>
        public string Value
        {
            get { return this.value; }
            set { this.value = value; }
        }
    }
}
