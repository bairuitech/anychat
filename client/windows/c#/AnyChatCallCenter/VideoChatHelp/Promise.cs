using System;
using System.Collections.Generic;
using System.Text;

namespace VideoChatHelp
{
    public class Promise
    {
        #region 约定常量

        /// <summary>
        /// 请求会话
        /// </summary>
        public const int ICS_CMD_SESSIONREQUEST = 1;
        /// <summary>
        /// 开始会话
        /// </summary>
        public const int ICS_CMD_SESSIONSTART = 2;
        /// <summary>
        /// 会话结束
        /// </summary>
        public const int ICS_CMD_SESSIONFINISH = 3;
        /// <summary>
        /// 数据请求
        /// </summary>
        public const int ICS_CMD_DATAREQUEST = 4;
        /// <summary>
        /// 数据信息
        /// </summary>
        public const int ICS_CMD_DATAITEM = 5;
        /// <summary>
        /// 状态通知
        /// </summary>
        public const int ICS_CMD_STATUSNOTIFY = 6;
        /// <summary>
        /// 控制指令
        /// </summary>
        public const int ICS_CMD_CONTROL = 7;

        #endregion

        #region 请求数据类型定义

        /// <summary>
        /// 请求在线用户列表
        /// </summary>
        public const int ICS_DATATYPE_ONLINEUSERS = 1;

        #endregion

        #region 5.4状态

        /// <summary>
        /// 用户在线状态
        /// </summary>
        public const int ICS_STATUSTYPE_USERONLINE = 1;
        /// <summary>
        /// 离线
        /// </summary>
        public const int ICS_STATUSTYPE_USERONLINE_FONLINE = 0;

        #endregion


        #region 控制常量定义

        /// <summary>
        /// 数据发送完成
        /// </summary>
        public const int ICS_CONTROL_DATAFINISH = 1;
        /// <summary>
        /// 呼叫等待
        /// </summary>
        public const int ICS_CONTROL_SESSIONWAIT = 2;

        #endregion

        #region error

        public const int ICS_RETCODE_SESSION_SUCCESS = 0;
        /// <summary>
        /// 源用户主动放弃会话
        /// </summary>
        public const int ICS_RETCODE_SESSION_ABANDON = 100101;
        /// <summary>
        /// 对方用户已离线
        /// </summary>
        public const int ICS_RETCODE_SESSION_OFFLINE = 100102;
        /// <summary>
        /// 目标用户忙
        /// </summary>
        public const int ICS_RETCODE_SESSION_BUSY = 100103;
        /// <summary>
        /// 目标用户拒绝会话
        /// </summary>
        public const int ICS_RETCODE_SESSION_REJECT = 100104;
        /// <summary>
        /// 会话请求超时
        /// </summary>
        public const int ICS_RETCODE_SESSION_TIMEOUT = 100105;

        #endregion
    }
}
