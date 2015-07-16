using System;
using System.Collections.Generic;
using System.Text;

namespace QueueHelp
{
    /// <summary>
    /// 业务功能类型
    /// </summary>
    public enum BusinessFuncType
    {
        /// <summary>
        /// 未定义功能
        /// </summary>
        None,
        /// <summary>
        /// 选择营业厅功能
        /// </summary>
        SelectAreaFunc,
        /// <summary>
        /// 选择队列功能
        /// </summary>
        SelectQueueFunc,
        /// <summary>
        /// 服务用户功能
        /// </summary>
        ServiceUserFunc
    }
}
