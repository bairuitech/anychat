using System;
using System.Collections.Generic;
using System.Text;

namespace VideoChatHelp
{
    public class RoomInfo
    {
        private int id;
        /// <summary>
        /// 房间ID
        /// </summary>
        public int Id
        {
            get { return id; }
            set { id = value; }
        }
        private int count;
        /// <summary>
        /// 房间人数
        /// </summary>
        public int Count
        {
            get { return count; }
            set { count = value; }
        }
    }
}
