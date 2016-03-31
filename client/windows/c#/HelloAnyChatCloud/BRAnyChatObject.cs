using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace ANYCHATAPI
{
    /// <summary>
    /// AnyChat SDK业务对象定义
    /// </summary>
    public class BRAnyChatObject
    {
        public const string AnyChatCoreSDKDll = "BRAnyChatCore.dll";

        #region AnyChat业务对象常量定义

        #region 对象类型定义

        /// <summary>
        /// 服务区域
        /// </summary>
        public const int ANYCHAT_OBJECT_TYPE_AREA = 4;
        /// <summary>
        /// 队列对象
        /// </summary>
        public const int ANYCHAT_OBJECT_TYPE_QUEUE = 5;
        /// <summary>
        /// 客服对象
        /// </summary>
        public const int ANYCHAT_OBJECT_TYPE_AGENT = 6;
        /// <summary>
        /// 客户端用户对象
        /// </summary>
        public const int ANYCHAT_OBJECT_TYPE_CLIENTUSER = 8;

        #endregion

        #region 通用标识常量定义

        /// <summary>
        /// 普通客户
        /// </summary>
        public const int ANYCHAT_OBJECT_FLAGS_CLIENT = 0;
        /// <summary>
        /// 坐席用户
        /// </summary>
        public const int ANYCHAT_OBJECT_FLAGS_AGENT = 2;
        /// <summary>
        /// 管理用户
        /// </summary>
        public const int ANYCHAT_OBJECT_FLAGS_MANANGER = 4;
        /// <summary>
        /// 无效的对象ID
        /// </summary>
        public const int ANYCHAT_INVALID_OBJECT_ID = -1;
        /// <summary>
        /// 业务对象身份初始化
        /// </summary>
        public const int BRAC_SO_OBJECT_INITFLAGS = 200; 

        #endregion

        #region 对象属性定义_对象公共

        /// <summary>
        /// 对象属性标志
        /// </summary>
        public const int ANYCHAT_OBJECT_INFO_FLAGS = 7;
        /// <summary>
        /// 对象名称
        /// </summary>
        public const int ANYCHAT_OBJECT_INFO_NAME = 8;
        /// <summary>
        /// 对象优先级
        /// </summary>
        public const int ANYCHAT_OBJECT_INFO_PRIORITY = 9;
        /// <summary>
        /// 对象业务属性
        /// </summary>
        public const int ANYCHAT_OBJECT_INFO_ATTRIBUTE = 10;
        /// <summary>
        /// 对象描述
        /// </summary>
        public const int ANYCHAT_OBJECT_INFO_DESCRIPTION = 11;
        /// <summary>
        /// 对象标签，整型，上层应用自定义
        /// </summary>
        public const int ANYCHAT_OBJECT_INFO_INTTAG = 12;
        /// <summary>
        /// 对象标签，字符串，上层应用自定义
        /// </summary>
        public const int ANYCHAT_OBJECT_INFO_STRINGTAG = 13;

        #endregion

        #region 对象属性定义_服务区域

        /// <summary>
        /// 服务区域客服（坐席）数量
        /// </summary>
        public const int ANYCHAT_AREA_INFO_AGENTCOUNT = 401;
        /// <summary>
        /// 服务区域内访客的用户数（没有排入队列的用户）
        /// </summary>
        public const int ANYCHAT_AREA_INFO_GUESTCOUNT = 402;
        /// <summary>
        /// 服务区域内排队的用户数
        /// </summary>
        public const int ANYCHAT_AREA_INFO_QUEUEUSERCOUNT = 403;
        /// <summary>
        /// 服务区域内队列的数量
        /// </summary>
        public const int ANYCHAT_AREA_INFO_QUEUECOUNT = 404;
        
        #endregion

        #region 对象属性定义_业务队列

        /// <summary>
        /// 自己在该队列中的序号
        /// </summary>
        public const int ANYCHAT_QUEUE_INFO_MYSEQUENCENO = 501;
        /// <summary>
        /// 排在自己前面的用户数
        /// </summary>
        public const int ANYCHAT_QUEUE_INFO_BEFOREUSERNUM = 502;
        /// <summary>
        /// 进入队列的时间
        /// </summary>
        public const int ANYCHAT_QUEUE_INFO_MYENTERQUEUETIME = 503;
        /// <summary>
        /// 业务队列长度（有多少人在排队）
        /// </summary>
        public const int ANYCHAT_QUEUE_INFO_LENGTH = 504;
        /// <summary>
        /// 自己在队列中的等待时间（单位：秒）
        /// </summary>
        public const int ANYCHAT_QUEUE_INFO_WAITTIMESECOND = 508;

        #endregion

        #region 对象属性定义_客服（坐席）

        /// <summary>
        /// 服务状态
        /// </summary>
        public const int ANYCHAT_AGENT_INFO_SERVICESTATUS = 601;
        /// <summary>
        /// 当前服务的用户ID
        /// </summary>
        public const int ANYCHAT_AGENT_INFO_SERVICEUSERID = 602;
        /// <summary>
        /// 当前服务的开始时间
        /// </summary>
        public const int ANYCHAT_AGENT_INFO_SERVICEBEGINTIME = 603;
        /// <summary>
        /// 累计服务时间（单位：秒）
        /// </summary>
        public const int ANYCHAT_AGENT_INFO_SERVICETOTALTIME = 604;
        /// <summary>
        /// 累计服务的用户数
        /// </summary>
        public const int ANYCHAT_AGENT_INFO_SERVICETOTALNUM = 605;

        #endregion

        #region 客服（坐席）服务状态

        /// <summary>
        /// 关闭，不对外提供服务
        /// </summary>
        public const int ANYCHAT_AGENT_STATUS_CLOSEED = 0;
        /// <summary>
        /// 等待中，可随时接受用户服务
        /// </summary>
        public const int ANYCHAT_AGENT_STATUS_WAITTING = 1;
        /// <summary>
        /// 工作中，正在为用户服务
        /// </summary>
        public const int ANYCHAT_AGENT_STATUS_WORKING = 2;
        /// <summary>
        /// 暂停服务
        /// </summary>
        public const int ANYCHAT_AGENT_STATUS_PAUSED = 3;

        #endregion

        #endregion

        #region AnyChat业务方法常量定义

        #region 方法常量定义—公共参数

        /// <summary>
        /// 创建一个对象
        /// </summary>
        public const int ANYCHAT_OBJECT_CTRL_CREATE = 2;
        /// <summary>
        /// 同步对象数据给指定用户
        /// </summary>
        public const int ANYCHAT_OBJECT_CTRL_SYNCDATA = 3;
        /// <summary>
        /// 对象调试信息输出
        /// </summary>
        public const int ANYCHAT_OBJECT_CTRL_DEBUGOUTPUT = 4;

        #endregion

        #region 方法常量定义—服务区域

        /// <summary>
        /// 进入服务区域
        /// </summary>
        public const int ANYCHAT_AREA_CTRL_USERENTER = 401;
        /// <summary>
        /// 离开服务区域
        /// </summary>
        public const int ANYCHAT_AREA_CTRL_USERLEAVE = 402;

        #endregion

        #region 方法常量定义—业务队列

        /// <summary>
        /// 进入业务队列
        /// </summary>
        public const int ANYCHAT_QUEUE_CTRL_USERENTER = 501;
        /// <summary>
        /// 离开业务队列
        /// </summary>
        public const int ANYCHAT_QUEUE_CTRL_USERLEAVE = 502;

        #endregion

        #region 方法常量定义—客服（坐席）

        /// <summary>
        /// 坐席服务状态控制
        /// </summary>
        public const int ANYCHAT_AGENT_CTRL_SERVICESTATUS = 601;
        /// <summary>
        /// 服务请求
        /// </summary>
        public const int ANYCHAT_AGENT_CTRL_SERVICEREQUEST = 602;
        /// <summary>
        /// 结束服务
        /// </summary>
        public const int ANYCHAT_AGENT_CTRL_FINISHSERVICE = 604;
        /// <summary>
        /// 服务评价
        /// </summary>
        public const int ANYCHAT_AGENT_CTRL_EVALUATION = 605;

        #endregion

        #endregion

        #region AnyChat业务异步事件常量定义

        #region 异步事件常量定义—公共事件

        /// <summary>
        /// 对象数据更新
        /// </summary>
        public const int ANYCHAT_OBJECT_EVENT_UPDATE = 1;
        /// <summary>
        /// 对象数据同步结束
        /// </summary>
        public const int ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH = 2;

        #endregion

        #region 异步事件常量定义—服务区域

        /// <summary>
        /// 服务区域状态变化
        /// </summary>
        public const int ANYCHAT_AREA_EVENT_STATUSCHANGE = 401;
        /// <summary>
        /// 进入服务区域结果
        /// </summary>
        public const int ANYCHAT_AREA_EVENT_ENTERRESULT = 402;
        /// <summary>
        /// 用户进入服务区域
        /// </summary>
        public const int ANYCHAT_AREA_EVENT_USERENTER = 403;
        /// <summary>
        /// 用户离开服务区域
        /// </summary>
        public const int ANYCHAT_AREA_EVENT_USERLEAVE = 404;
        /// <summary>
        /// 离开服务区域结果
        /// </summary>
        public const int ANYCHAT_AREA_EVENT_LEAVERESULT = 405;

        #endregion

        #region 异步事件常量定义—业务队列

        /// <summary>
        /// 业务队列状态变化
        /// </summary>
        public const int ANYCHAT_QUEUE_EVENT_STATUSCHANGE = 501;
        /// <summary>
        /// 进入业务队列结果
        /// </summary>
        public const int ANYCHAT_QUEUE_EVENT_ENTERRESULT = 502;
        /// <summary>
        /// 用户进入业务队列
        /// </summary>
        public const int ANYCHAT_QUEUE_EVENT_USERENTER = 503;
        /// <summary>
        /// 用户离开业务队列
        /// </summary>
        public const int ANYCHAT_QUEUE_EVENT_USERLEAVE = 504;
        /// <summary>
        /// 离开业务队列结果
        /// </summary>
        public const int ANYCHAT_QUEUE_EVENT_LEAVERESULT = 505;

        #endregion

        #region 异步事件常量定义—客服（坐席）

        /// <summary>
        /// 坐席状态变化
        /// </summary>
        public const int ANYCHAT_AGENT_EVENT_STATUSCHANGE = 601;
        /// <summary>
        /// 坐席服务通知（哪个用户到哪个坐席办理业务）
        /// </summary>
        public const int ANYCHAT_AGENT_EVENT_SERVICENOTIFY = 602;
        /// <summary>
        /// 暂时没有客户，请等待
        /// </summary>
        public const int ANYCHAT_AGENT_EVENT_WAITINGUSER = 603;

        #endregion

        #endregion

        #region 回调函数定义

        /// <summary>
        /// 业务对象事件通知回调函数定义
        /// </summary>
        /// <param name="dwObjectType"></param>
        /// <param name="dwObjectId"></param>
        /// <param name="dwEventType"></param>
        /// <param name="dwParam1"></param>
        /// <param name="dwParam2"></param>
        /// <param name="dwParam3"></param>
        /// <param name="dwParam4"></param>
        /// <param name="strParam"></param>
        /// <returns></returns>
        public delegate void OnObjectEventNotifyCallBack(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam);

        #endregion

        #region API 方法定义

        /// <summary>
        /// 返回某对象类型的对象ID数组
        /// <param name="dwObjectType">对象类型</param>
        /// <param name="objIDArray">对象ID数组</param>
        /// <param name="objNumber">对象长度</param>
        /// <returns></returns>
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_ObjectGetIdList", CallingConvention = CallingConvention.Cdecl)]
        public static extern int BRAC_ObjectGetIdList(int dwObjectType, int[] objIDArray, ref int objNumber);

        /// <summary>
        /// 获取对象的属性值(整型)
        /// <param name="dwObjectType">对象类型</param>
        /// <param name="dwObjectId">对象ID</param>
        /// <param name="dwInfoName">属性名</param>
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_ObjectGetValue", CallingConvention = CallingConvention.Cdecl)]
        public static extern int BRAC_ObjectGetValue(int dwObjectType, int dwObjectId, int dwInfoName, ref int value);

        /// <summary>
        /// 获取对象的属性值(字符串)
        /// <param name="dwObjectType">对象类型</param>
        /// <param name="dwObjectId">对象ID</param>
        /// <param name="dwInfoName">属性名</param>
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_ObjectGetValue", CallingConvention = CallingConvention.Cdecl)]
        public static extern int BRAC_ObjectGetValue(int dwObjectType, int dwObjectId, int dwInfoName, StringBuilder value);

        /// <summary>
        /// 设置对象的属性值(整型)
        /// <param name="dwObjectType">对象类型</param>
        /// <param name="dwObjectId">对象ID</param>
        /// <param name="dwInfoName">属性名</param>
        /// <param name="value">属性值</param>
        /// </summary>
        //[DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_ObjectSetIntValue", CallingConvention = CallingConvention.Cdecl)]
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_ObjectSetValue", CallingConvention = CallingConvention.Cdecl)]
        public static extern int BRAC_ObjectSetValue(int dwObjectType, int dwObjectId, int dwInfoName, ref int value, int optlen);

        /// <summary>
        /// 设置对象的属性值(字符串)
        /// <param name="dwObjectType">对象类型</param>
        /// <param name="dwObjectId">对象ID</param>
        /// <param name="dwInfoName">属性名</param>
        /// <param name="value">属性值</param>
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_ObjectSetValue", CallingConvention = CallingConvention.Cdecl)]
        public static extern int BRAC_ObjectSetValue(int dwObjectType, int dwObjectId, int dwInfoName, string value, int optlen);

        /// <summary>
        /// 业务对象控制指令
        /// <param name="dwObjectType">对象类型</param>
        /// <param name="dwObjectId">对象ID</param>
        /// <param name="dwCtrlCode">控制方法指令</param>
        /// <param name="dwParam1"></param>
        /// <param name="dwParam2"></param>
        /// <param name="dwParam3"></param>
        /// <param name="dwParam4"></param>
        /// <param name="strParam"></param>
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_ObjectControl", CallingConvention = CallingConvention.Cdecl)]
        public static extern int BRAC_ObjectControl(int dwObjectType, int dwObjectId, int dwCtrlCode, int dwParam1, int dwParam2, int dwParam3, int dwParam4, string strParam);

        #endregion

    }
}
