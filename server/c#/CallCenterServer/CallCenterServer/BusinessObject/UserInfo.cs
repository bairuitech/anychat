using System;
using System.Collections.Generic;
using System.Text;

namespace BusinessObject
{
    public class UserInfo
    {
        private int id;
        /// <summary>
        /// 编号
        /// </summary>
        public int Id
        {
            get { return id; }
            set { id = value; }
        }
        private string name;
        /// <summary>
        /// 用户名
        /// </summary>
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        private string ip;
        /// <summary>
        /// 外网IP
        /// </summary>
        public string Ip
        {
            get { return ip; }
            set { ip = value; }
        }

    }
}
