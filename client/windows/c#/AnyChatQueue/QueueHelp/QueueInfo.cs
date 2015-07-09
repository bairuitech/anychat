using System;
using System.Collections.Generic;
using System.Text;

namespace QueueHelp
{
    /// <summary>
    /// 队列信息类
    /// </summary>
    public class QueueInfo
    {
        /// <summary>
        /// 队列ID
        /// </summary>
        public int QueueID { get; set; }
        /// <summary>
        /// 队列名称
        /// </summary>
        public string QueueName { get; set; }
        /// <summary>
        /// 队列描述
        /// </summary>
        public string QueueDescription { get; set; }
        /// <summary>
        /// 队列中排队客户人数
        /// </summary>
        public int inQueueClientCount { get; set; }

        /// <summary>
        /// 队列对象绑定的控件
        /// </summary>
        public object bindedOjbect;
    }
}
