// AnyChat for Web SDK
// 不要对该文件进行任何修改，当升级SDK时，新版本将会直接覆盖旧版本

/********************************************
 *			业务对象常量定义				*
 *******************************************/

 
 // 对象类型定义
var ANYCHAT_OBJECT_TYPE_AREA		=	4;		// 服务区域
var ANYCHAT_OBJECT_TYPE_QUEUE		=	5;		// 队列对象
var ANYCHAT_OBJECT_TYPE_AGENT		=	6;		// 客服对象
var ANYCHAT_OBJECT_TYPE_CLIENTUSER	=	8;		// 客户端用户对象，用于与服务器交换数据
var ANYCHAT_OBJECT_TYPE_SKILL		=	9;		// 业务技能对象
var ANYCHAT_OBJECT_TYPE_QUEUEGROUP	=	10;		// 队列分组对象

// 通用标识定义
var ANYCHAT_OBJECT_FLAGS_CLIENT			=	0;		// 普通客户
var ANYCHAT_OBJECT_FLAGS_AGENT			=	2;		// 坐席用户
var ANYCHAT_OBJECT_FLAGS_MANANGER		=	4;		// 管理用户
var ANYCHAT_OBJECT_FLAGS_AUTOMODE		=	16;		// 自动服务模式
var ANYCHAT_OBJECT_FLAGS_GUESTLOGIN		=	32;		// 游客登录方式
var ANYCHAT_OBJECT_FLAGS_GLOBAL			=	64;		// 全局服务
var ANYCHAT_OBJECT_FLAGS_CONNECT		=	128;	// 网络连接对象
var ANYCHAT_OBJECT_FLAGS_MULTICHANNEL	=	256;	// 多通道模式
var ANYCHAT_OBJECT_FLAGS_QUEUEUSERLIST	=	512;	// 通知队列用户列表
var ANYCHAT_OBJECT_FLAGS_AREAUSERINFO	=	1024;	// 营业厅用户详细信息
var ANYCHAT_OBJECT_FLAGS_MANUALSYNCAREA =	2048;	// 手工同步营业厅数据（禁止自动）
var ANYCHAT_OBJECT_FLAGS_ONLYSYNCNEED	=	4096;	// 只需要同步关联的数据


var ANYCHAT_INVALID_OBJECT_ID		=	-1;		// 无效的对象ID
var ANYCHAT_MAX_OBJECT_CHANNELS		=	36	    // 最大对象服务通道数

// 坐席服务状态定义
var ANYCHAT_AGENT_STATUS_CLOSEED	=	0;		// 关闭，不对外提供服务
var ANYCHAT_AGENT_STATUS_WAITTING	=	1;		// 等待中，可随时接受用户服务
var ANYCHAT_AGENT_STATUS_WORKING	=	2;		// 工作中，正在为用户服务
var ANYCHAT_AGENT_STATUS_PAUSED		=	3;		// 暂停服务
var ANYCHAT_AGENT_STATUS_OFFLINE	=	10;		// 离线



/**
 *	对象属性定义
 */

// 对象公共信息类型定义
var ANYCHAT_OBJECT_INFO_FLAGS		=	7;		// 对象属性标志
var ANYCHAT_OBJECT_INFO_NAME		=	8;		// 对象名称
var ANYCHAT_OBJECT_INFO_PRIORITY	=	9;		// 对象优先级
var ANYCHAT_OBJECT_INFO_ATTRIBUTE	=	10;		// 对象业务属性
var ANYCHAT_OBJECT_INFO_DESCRIPTION	=	11;		// 对象描述
var ANYCHAT_OBJECT_INFO_INTTAG		=	12;		// 对象标签，整型，上层应用自定义
var ANYCHAT_OBJECT_INFO_STRINGTAG	=	13;		// 对象标签，字符串，上层应用自定义
var ANYCHAT_OBJECT_INFO_GUID		=	14;		// 对象GUID
var ANYCHAT_OBJECT_INFO_STATUSJSON	=	15;		// 对象状态属性集合
var ANYCHAT_OBJECT_INFO_STRINGID	=	16;		// 对象字符串ID
var ANYCHAT_OBJECT_INFO_STATISTICS	=	17;		// 对象统计数据


// 服务区域信息类型定义
var ANYCHAT_AREA_INFO_AGENTCOUNT	=	401;	// 服务区域客服用户数
var ANYCHAT_AREA_INFO_GUESTCOUNT	=	402;	// 服务区域内访客的用户数（没有排入队列的用户）
var ANYCHAT_AREA_INFO_QUEUEUSERCOUNT=	403;	// 服务区域内排队的用户数
var ANYCHAT_AREA_INFO_QUEUECOUNT	=	404;	// 服务区域内队列的数量
var ANYCHAT_AREA_INFO_AGENTIDLIST	=	405;	// 服务区域客服ID列表
var ANYCHAT_AREA_INFO_IDLEAGENTCOUNT=	406;	// 服务区域空闲坐席数量
var ANYCHAT_AREA_INFO_STATUSJSON	=	407;	// 服务区域状态信息，返回Json数据
var ANYCHAT_AREA_INFO_WAITINGCOUNT	=	408;	// 服务区域内等候服务用户数（出了队列，但没有坐席服务的用户）
var ANYCHAT_AREA_INFO_WORKAGENTCOUNT=	409;	// 服务区域工作坐席数量
var ANYCHAT_AREA_INFO_BUSYAGENTCOUNT=	410;	// 服务区域示忙坐席数量

// 队列状态信息类型定义
var ANYCHAT_QUEUE_INFO_MYSEQUENCENO	=	501;	// 自己在该队列中的序号
var ANYCHAT_QUEUE_INFO_BEFOREUSERNUM=	502;	// 排在自己前	面的用户数
var ANYCHAT_QUEUE_INFO_MYENTERQUEUETIME=503;	// 进入队列的时间
var ANYCHAT_QUEUE_INFO_LENGTH		=	504;	// 队列长度（有多少人在排队），整型
var ANYCHAT_QUEUE_INFO_WAITTIMESECOND=	508;	// 自己在队列中的等待时间（排队时长），单位：秒
var ANYCHAT_QUEUE_INFO_AGENTINFO	=	509;	// 服务当前队列的坐席信息，返回Json数据
var ANYCHAT_QUEUE_INFO_USERIDLIST	=	510;	// 队列用户ID列表
var ANYCHAT_QUEUE_INFO_WAITINGTIMELIST=	511;	// 队列用户等待时间列表(单位：秒)
var ANYCHAT_QUEUE_INFO_USERINFOLIST	=	512;	// 队列用户信息列表

// 客服状态信息类型定义
var ANYCHAT_AGENT_INFO_SERVICESTATUS=	601;	// 服务状态，整型
var ANYCHAT_AGENT_INFO_SERVICEUSERID=	602;	// 当前服务的用户ID，整型
var ANYCHAT_AGENT_INFO_SERVICEBEGINTIME=603;	// 当前服务的开始时间，整型
var ANYCHAT_AGENT_INFO_SERVICETOTALTIME=604;	// 累计服务时间，整型，单位：秒
var ANYCHAT_AGENT_INFO_SERVICETOTALNUM=	605;	// 累计服务的用户数，整型
var ANYCHAT_AGENT_INFO_SERVICEUSERINFO=	606;	// 当前服务用户信息，字符串
var ANYCHAT_AGENT_INFO_RELATEQUEUES	=	607;	// 关联队列List，字符串
var ANYCHAT_AGENT_INFO_SERVICEFAILNUM=	608;	// 服务失败用户数
var ANYCHAT_AGENT_INFO_MAXCHANNELNUM=	609;	// 最大服务通道数，整型




/**
 *	对象方法定义
 */

// 对象公共参数控制常量定义
var ANYCHAT_OBJECT_CTRL_CREATE		=	2;		// 创建一个对象
var ANYCHAT_OBJECT_CTRL_SYNCDATA	=	3;		// 同步对象数据给指定用户，dwObjectId=-1，表示同步该类型的所有对象
var ANYCHAT_OBJECT_CTRL_DEBUGOUTPUT	=	4;		// 对象调试信息输出
var ANYCHAT_OBJECT_CTRL_DELETE		=	5;		// 删除对象
var ANYCHAT_OBJECT_CTRL_MODIFY		=	6;		// 修改对象信息

// 服务区域控制常量定义
var ANYCHAT_AREA_CTRL_USERENTER		=	401;	// 进入服务区域
var ANYCHAT_AREA_CTRL_USERLEAVE		=	402;	// 离开服务区域

// 队列参数控制常量定义
var ANYCHAT_QUEUE_CTRL_USERENTER	=	501;	// 进入队列
var ANYCHAT_QUEUE_CTRL_USERLEAVE	=	502;	// 离开队列

// 客服参数控制常量定义
var ANYCHAT_AGENT_CTRL_SERVICESTATUS=	601;	// 坐席服务状态控制（暂停服务、工作中、关闭）
var ANYCHAT_AGENT_CTRL_SERVICEREQUEST=	602;	// 服务请求
var ANYCHAT_AGENT_CTRL_STARTSERVICE	=	603;	// 开始服务，wParam为用户userid
var ANYCHAT_AGENT_CTRL_FINISHSERVICE=	604;	// 结束服务
var ANYCHAT_AGENT_CTRL_EVALUATION	=	605;	// 服务评价，wParam为客服userid，lParam为评分，lpStrValue为留言






/**
 *	对象异步事件定义
 */

// 对象公共事件常量定义
var ANYCHAT_OBJECT_EVENT_UPDATE		=	1;		// 对象数据更新
var ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH=2;		// 对象数据同步结束
var ANYCHAT_OBJECT_EVENT_STATISTICS	=	3;		// 对象统计数据更新

// 服务区域事件常量定义
var ANYCHAT_AREA_EVENT_STATUSCHANGE	=	401;	// 服务区域状态变化
var ANYCHAT_AREA_EVENT_ENTERRESULT	=	402;	// 进入服务区域结果
var ANYCHAT_AREA_EVENT_USERENTER	=	403;	// 用户进入服务区域
var ANYCHAT_AREA_EVENT_USERLEAVE	=	404;	// 用户离开服务区域
var ANYCHAT_AREA_EVENT_LEAVERESULT	=	405;	// 离开服务区域结果


// 队列事件常量定义
var ANYCHAT_QUEUE_EVENT_STATUSCHANGE=	501;	// 队列状态变化
var ANYCHAT_QUEUE_EVENT_ENTERRESULT	=	502;	// 进入队列结果
var ANYCHAT_QUEUE_EVENT_USERENTER	=	503;	// 用户进入队列
var ANYCHAT_QUEUE_EVENT_USERLEAVE	=	504;	// 用户离开队列
var ANYCHAT_QUEUE_EVENT_LEAVERESULT	=	505;	// 离开队列结果
var ANYCHAT_QUEUE_EVENT_STARTSERVICE=	506;	// 用户开始被服务
var ANYCHAT_QUEUE_EVENT_USERINFOLISTCHG=507;	// 队列用户列表更新


// 坐席事件常量定义
var ANYCHAT_AGENT_EVENT_STATUSCHANGE=	601;	// 坐席状态变化
var ANYCHAT_AGENT_EVENT_SERVICENOTIFY=	602;	// 坐席服务通知（哪个用户到哪个客服办理业务）
var ANYCHAT_AGENT_EVENT_WAITINGUSER	=	603;	// 暂时没有客户，请等待
var ANYCHAT_AGENT_EVENT_ISREADY		=	604;	// 坐席准备好，可以发起呼叫


