#if !defined(_ANYCHAT_OBJECTDEFINE_H_INCLUDED_)
#define _ANYCHAT_OBJECTDEFINE_H_INCLUDED_

// 对象类型定义
#define ANYCHAT_OBJECT_TYPE_AREA			4	///< 服务区域
#define ANYCHAT_OBJECT_TYPE_QUEUE			5	///< 队列对象
#define ANYCHAT_OBJECT_TYPE_AGENT			6	///< 客服对象
#define ANYCHAT_OBJECT_TYPE_CLIENTUSER		8	///< 客户端用户对象，用于与服务器交换数据

// 通用标识定义
#define ANYCHAT_OBJECT_FLAGS_CLIENT		0x00	///< 普通客户
#define ANYCHAT_OBJECT_FLAGS_AGENT		0x02	///< 坐席用户
#define ANYCHAT_OBJECT_FLAGS_MANANGER	0x04	///< 管理用户
#define ANYCHAT_OBJECT_FLAGS_AUTOMODE	0x10	///< 自动服务模式

#define ANYCHAT_INVALID_OBJECT_ID           -1	///< 无效的对象ID

// 坐席服务状态定义
#define ANYCHAT_AGENT_STATUS_CLOSEED		0	///< 关闭，不对外提供服务
#define ANYCHAT_AGENT_STATUS_WAITTING		1	///< 等待中，可随时接受用户服务
#define ANYCHAT_AGENT_STATUS_WORKING		2	///< 工作中，正在为用户服务
#define ANYCHAT_AGENT_STATUS_PAUSED			3	///< 暂停服务




/**
 *	对象属性定义
 */

// 对象公共信息类型定义
#define ANYCHAT_OBJECT_INFO_FLAGS			7	///< 对象属性标志
#define ANYCHAT_OBJECT_INFO_NAME			8	///< 对象名称
#define ANYCHAT_OBJECT_INFO_PRIORITY		9	///< 对象优先级
#define ANYCHAT_OBJECT_INFO_ATTRIBUTE		10	///< 对象业务属性
#define ANYCHAT_OBJECT_INFO_DESCRIPTION		11	///< 对象描述
#define ANYCHAT_OBJECT_INFO_INTTAG			12	///< 对象标签，整型，上层应用自定义
#define ANYCHAT_OBJECT_INFO_STRINGTAG		13	///< 对象标签，字符串，上层应用自定义


// 服务区域信息类型定义
#define ANYCHAT_AREA_INFO_AGENTCOUNT		401	///< 服务区域客服用户数
#define ANYCHAT_AREA_INFO_GUESTCOUNT		402	///< 服务区域内访客的用户数（没有排入队列的用户）
#define ANYCHAT_AREA_INFO_QUEUEUSERCOUNT	403	///< 服务区域内排队的用户数
#define ANYCHAT_AREA_INFO_QUEUECOUNT		404	///< 服务区域内队列的数量

// 队列状态信息类型定义
#define ANYCHAT_QUEUE_INFO_MYSEQUENCENO		501	///< 自己在该队列中的序号
#define ANYCHAT_QUEUE_INFO_BEFOREUSERNUM	502	///< 排在自己前	面的用户数
#define ANYCHAT_QUEUE_INFO_MYENTERQUEUETIME	503	///< 进入队列的时间
#define ANYCHAT_QUEUE_INFO_LENGTH			504	///< 队列长度（有多少人在排队），整型
#define ANYCHAT_QUEUE_INFO_WAITTIMESECOND	508	///< 自己在队列中的等待时间（排队时长），单位：秒


// 客服状态信息类型定义
#define ANYCHAT_AGENT_INFO_SERVICESTATUS	601	///< 服务状态，整型
#define ANYCHAT_AGENT_INFO_SERVICEUSERID	602	///< 当前服务的用户ID，整型
#define ANYCHAT_AGENT_INFO_SERVICEBEGINTIME	603	///< 当前服务的开始时间，整型
#define ANYCHAT_AGENT_INFO_SERVICETOTALTIME	604	///< 累计服务时间，整型，单位：秒
#define ANYCHAT_AGENT_INFO_SERVICETOTALNUM	605	///< 累计服务的用户数，整型




/**
 *	对象方法定义
 */

// 对象公共参数控制常量定义
#define ANYCHAT_OBJECT_CTRL_CREATE			2	///< 创建一个对象
#define ANYCHAT_OBJECT_CTRL_SYNCDATA		3	///< 同步对象数据给指定用户，dwObjectId=-1，表示同步该类型的所有对象
#define ANYCHAT_OBJECT_CTRL_DEBUGOUTPUT		4	///< 对象调试信息输出

// 服务区域控制常量定义
#define ANYCHAT_AREA_CTRL_USERENTER			401	///< 进入服务区域
#define ANYCHAT_AREA_CTRL_USERLEAVE			402	///< 离开服务区域

// 队列参数控制常量定义
#define ANYCHAT_QUEUE_CTRL_USERENTER		501	///< 进入队列
#define ANYCHAT_QUEUE_CTRL_USERLEAVE		502	///< 离开队列

// 客服参数控制常量定义
#define ANYCHAT_AGENT_CTRL_SERVICESTATUS	601	///< 坐席服务状态控制（暂停服务、工作中、关闭）
#define ANYCHAT_AGENT_CTRL_SERVICEREQUEST	602	///< 服务请求
#define ANYCHAT_AGENT_CTRL_FINISHSERVICE	604	///< 结束服务
#define ANYCHAT_AGENT_CTRL_EVALUATION		605	///< 服务评价，wParam为客服userid，lParam为评分，lpStrValue为留言






/**
 *	对象异步事件定义
 */

// 对象公共事件常量定义
#define ANYCHAT_OBJECT_EVENT_UPDATE			1	///< 对象数据更新
#define ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH	2	///< 对象数据同步结束

// 服务区域事件常量定义
#define ANYCHAT_AREA_EVENT_STATUSCHANGE		401	///< 服务区域状态变化
#define ANYCHAT_AREA_EVENT_ENTERRESULT		402	///< 进入服务区域结果
#define ANYCHAT_AREA_EVENT_USERENTER		403	///< 用户进入服务区域
#define ANYCHAT_AREA_EVENT_USERLEAVE		404	///< 用户离开服务区域
#define ANYCHAT_AREA_EVENT_LEAVERESULT		405	///< 离开服务区域结果


// 队列事件常量定义
#define ANYCHAT_QUEUE_EVENT_STATUSCHANGE	501	///< 队列状态变化
#define ANYCHAT_QUEUE_EVENT_ENTERRESULT		502	///< 进入队列结果
#define ANYCHAT_QUEUE_EVENT_USERENTER		503	///< 用户进入队列
#define ANYCHAT_QUEUE_EVENT_USERLEAVE		504	///< 用户离开队列
#define ANYCHAT_QUEUE_EVENT_LEAVERESULT		505	///< 离开队列结果


// 坐席事件常量定义
#define ANYCHAT_AGENT_EVENT_STATUSCHANGE	601	///< 坐席状态变化
#define ANYCHAT_AGENT_EVENT_SERVICENOTIFY	602	///< 坐席服务通知（哪个用户到哪个客服办理业务）
#define ANYCHAT_AGENT_EVENT_WAITINGUSER		603	///< 暂时没有客户，请等待




#endif // !defined(_ANYCHAT_OBJECTDEFINE_H_INCLUDED_)