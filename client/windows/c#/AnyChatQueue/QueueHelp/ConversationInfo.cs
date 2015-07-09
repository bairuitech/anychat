using System;
using System.Collections.Generic;
using System.Text;

namespace QueueHelp
{
    public class ConversationInfo
    {
        private int suserId;
        /// <summary>
        /// 呼叫发起者
        /// </summary>
        public int SuserId
        {
            get { return suserId; }
            set { suserId = value; }
        }
        private int tuserId;
        /// <summary>
        /// 被呼叫者
        /// </summary>
        public int TuserId
        {
            get { return tuserId; }
            set { tuserId = value; }
        }
    }
}
