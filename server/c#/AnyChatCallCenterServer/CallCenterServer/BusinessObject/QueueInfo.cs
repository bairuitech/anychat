using System;
using System.Collections.Generic;
using System.Text;

namespace BusinessObject
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

        /// <summary>
        /// 所属营业厅ID
        /// </summary>
        public int AreaID { get; set; }

        /// <summary>
        /// 队列优先级
        /// </summary>
        public int QueuePriority { get; set; }

        /// <summary>
        /// 队列业务类型
        /// </summary>
        public BusinessType businessType { get; set; }

        /// <summary>
        /// 整型标签
        /// </summary>
        public int intTag { get; set; }

        /// <summary>
        /// 字符串标签
        /// </summary>
        public string stringTag { get; set; }
    }
}
