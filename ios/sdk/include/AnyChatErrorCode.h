#ifndef ANYCHAT_ERRORCODE_H_INCLUDED
#define ANYCHAT_ERRORCODE_H_INCLUDED

#pragma once

#define GV_ERR_SUCCESS				0		///< 成功
#define AC_ERROR_SUCCESS			0		///< no error


// system error code define
#define AC_ERROR_DB_ERROR			1		///< 数据库错误
#define AC_ERROR_NOTINIT			2		///< 系统没有初始化
#define	AC_ERROR_NOTINROOM			3		///< 还未进入房间
#define AC_ERROR_MEMORYFAIL			4       ///< not enough memory
#define AC_ERROR_EXCEPTION			5		///< 出现异常
#define AC_ERROR_CANCEL				6		///< 操作被取消
#define AC_ERROR_PROTOCOLFAIL		7		///< 通信协议出错
#define AC_ERROR_SESSIONNOTEXIST	8		///< 会话不存在
#define AC_ERROR_DATANOTEXIST		9		///< 数据不存在
#define AC_ERROR_DATAEXIST			10		///< 数据已经存在
#define AC_ERROR_INVALIDGUID		11		///< 无效GUID
#define AC_ERROR_RESOURCERECOVER	12		///< 资源被回收
#define AC_ERROR_RESOURCEUSED		13		///< 资源被占用
#define AC_ERROR_JSONFAIL			14		///< Json解析出错
#define AC_ERROR_OBJECTDELETE		15		///< 对象被删除
#define AC_ERROR_SESSIONEXIST		16		///< 会话已存在
#define AC_ERROR_SESSIONNOTINIT		17		///< 会话没有初始化
#define AC_ERROR_DATANOTPREPARE		18		///< 数据没有准备好
#define AC_ERROR_SIGTERM			19		///< 收到SIGTERM信号（kill指令）
#define AC_ERROR_FUNCNOTALLOW		20		///< 函数功能不允许
#define AC_ERROR_FUNCOPTERROR       21      ///< function parameters error
#define AC_ERROR_DEVICEOPENFAIL     22      ///< device open failed or device no install
#define AC_ERROR_NOENOUGHRESOURCE	23		///< 没有足够的资源
#define AC_ERROR_PIXFMTNOTSUPPORT	24		///< 指定的格式不能被显示设备所支持
#define AC_ERROR_NOTMULTICASTADDR	25		///< 指定的IP地址不是有效的组播地址
#define AC_ERROR_MULTIRUNERROR		26		///< 不支持多实例运行
#define AC_ERROR_FILETRUSTFAILED	27		///< 文件签名验证失败
#define AC_ERROR_CERTVERIFYFAILED	28		///< 授权验证失败
#define AC_ERROR_CERTUSERFAILED		29		///< 授权证书用户数验证失败
#define AC_ERROR_MASTERISSLAVE		30		///< 所指定的主服务器是热备服务器，不支持再次热备
#define AC_ERROR_MASTERNOTCREDIT	31		///< 主服务器没有经过授权认证，不支持热备
#define AC_ERROR_VERSIONNOTMATCH	32		///< 版本不匹配
#define AC_ERROR_CERTFAILSECOND		33		///< 第二次授权验证失败
#define AC_ERROR_SERVERVERIFYFAIL	34		///< 服务器安全验证失败
#define AC_ERROR_CLIENTCERTFAILED	35		///< 客户端授权验证失败
#define AC_ERROR_CERTSUMFAILED		36		///< 授权功能校验失败
#define AC_ERROR_REMOTECTRL			37		///< 远程控制
#define AC_ERROR_DUPLICATESERVICEID	38		///< ServiceGuid重复
#define AC_ERROR_DIRENTERROR		39		///< 目录错误
#define AC_ERROR_EXTRACTFILEERROR	40		///< 解压文件失败
#define AC_ERROR_STARTPROCESSFAILED	41		///< 启动进程失败
#define AC_ERROR_SERVICEISRUNNING	42		///< 服务已启动
#define AC_ERROR_DISKSPACELIMITED	43		///< 磁盘空间不足
#define AC_ERROR_REQUESTFAILED		44		///< 业务服务发送请求失败
#define AC_ERROR_INVALIDMACHINE		45		///< 无效的物理机对象
#define AC_ERROR_GETCERTINFOFAILED	46		///< 获取授权信息失败
#define AC_ERROR_CLUSTERNOTMATCH	47		///< 集群属性不匹配
#define AC_ERROR_NONECLUSTERID		48		///< 集群ID为空
#define AC_ERROR_CREATESERVICE_MORE	49		///< 同台物理机创建多个相同服务，一类服务暂时不允许创建多个
#define AC_ERROR_COPYFILEFAILED		50		///< 拷贝文件失败
#define AC_ERROR_CLOUDNATIVEDBFAIL	51		///< 云平台内部数据库出错
#define AC_ERROR_CLOUDOSSUPLOADFAIL	52		///< 云平台OSS文件上传失败
#define AC_ERROR_SERVICEBINDCHANGE	53		///< 服务绑定关系变化
#define AC_ERROR_SERVICENOTBIND		54		///< 服务没有被绑定
#define AC_ERROR_SERVICEBINDFAIL	55		///< 服务绑定失败
#define AC_ERROR_PIPELINEUSERFAIL	56		///< PipeLine通信用户ID出错
#define AC_ERROR_PIPELINESESSFAIL	57		///< PipeLine通信会话出错
#define AC_ERROR_SERVICECLOSED		58		///< 服务被关闭
#define AC_ERROR_FILEENCRYPTED		59		///< 文件已被加密过
#define AC_ERROR_FILEHEADINVAILD	60		///< 解密无效（文件校验不通过）
#define AC_ERROR_FILEDECODE_PASSERR	61		///< 解密失败，可能密码错误
#define AC_ERROR_OVERFLOW			62		///< 缓冲区太长
#define AC_ERROR_OLDSERVER			63		///< 服务器版本太旧
#define AC_ERROR_UNSUPPORTFILETYPE	64		///< 不支持的文件类型
#define AC_ERROR_FILECONTENTFAIL	65		///< 文件内容出错
#define AC_ERROR_KEYVERIFYFAILED	66		///< 密钥校验失败
#define AC_ERROR_NOCERTCHAIN		67		///< 缺少证书链
#define AC_ERROR_CERTVERIFYFAIL		68		///< 证书校验失败
#define AC_ERROR_CERTDATEFAIL		69		///< 证书日期校验失败
#define AC_ERROR_CERTURLFAIL		70		///< 证书URL地址校验失败
#define AC_ERROR_CERTPUBLICKEYFAIL	71		///< 缺少公钥
#define AC_ERROR_CERTPRIVATEKEYFAIL	72		///< 服务器没有配置SSL证书所对应的私钥
#define AC_ERROR_CERTFILENOTCONFIG	73		///< 服务器没有配置SSL证书
#define AC_ERROR_CERTHIGHSECURITY	74		///< 安全级别限制，不允许连接
#define AC_ERROR_SECURITYBREAK		75		///< 安全协商失败
#define AC_ERROR_CERTALGORITHMFAIL	76		///< 算法协商失败
#define AC_ERROR_LOSSCERTHELPER		77		///< 缺少CertHelper库文件
#define AC_ERROR_SECURITYTIMEOUT	78		///< 安全协商超时
#define AC_ERROR_MEMORYTOOSMALL		79		///< 准备的缓冲区太小
#define AC_ERROR_UNSUPPORTCODEC		80		///< 不支持的编码器
#define AC_ERROR_APPTYPEOVERFLOW	81		///< 指定应用类型连接数已满

//连接部分
#define AC_ERROR_CONNECT_TIMEOUT	100		///< 连接服务器超时
#define AC_ERROR_CONNECT_ABORT		101		///< 与服务器的连接中断
#define AC_ERROR_CONNECT_AUTHFAIL	102		///< 连接服务器认证失败（服务器设置了认证密码）
#define AC_ERROR_CONNECT_DNSERROR	103		///< 域名解析失败
#define AC_ERROR_CONNECT_OVERFLOW	104		///< 超过授权用户数
#define	AC_ERROR_CONNECT_FUNCLIMIT	105		///< 服务器功能受限制（演示模式）
#define	AC_ERROR_CONNECT_INTRANET	106		///< 只能在内网使用
#define	AC_ERROR_CONNECT_OLDVERSION	107		///< 版本太旧，不允许连接
#define AC_ERROR_CONNECT_SOCKETERR	108		///< Socket出错
#define	AC_ERROR_CONNECT_DEVICELIMIT 109	///< 设备连接限制（没有授权）
#define AC_ERROR_CONNECT_PAUSED		110		///< 服务已被暂停
#define AC_ERROR_CONNECT_HOTSERVER	111		///< 热备服务器不支持连接（主服务在启动状态）
#define AC_ERROR_CONNECT_ERRCERUSER	112		///< 授权用户数校验出错，可能内存被修改
#define AC_ERROR_CONNECT_IPFORBID	113		///< IP被禁止连接
#define AC_ERROR_CONNECT_TYPEWRONG	114		///< 连接类型错误，服务器不支持当前类型的连接
#define AC_ERROR_CONNECT_ERRORIP	115		///< 服务器IP地址不正确
#define AC_ERROR_CONNECT_SELFCLOSE	116		///< 连接被主动关闭
#define AC_ERROR_CONNECT_NOSVRLIST	117		///< 没有获取到服务器列表
#define AC_ERROR_CONNECT_LBTIMEOUT	118		///< 连接负载均衡服务器超时
#define AC_ERROR_CONNECT_NOTWORK	119		///< 服务器不在工作状态
#define AC_ERROR_CONNECT_OFFLINE	120		///< 服务器不在线
#define AC_ERROR_CONNECT_NETLIMITED	121		///< 网络带宽受限
#define AC_ERROR_CONNECT_LOWTRAFFIC	122		///< 网络流量不足
#define AC_ERROR_CONNECT_IPV6FAIL	123		///< 不支持IPv6 Only网络
#define AC_ERROR_CONNECT_NOMASTER	124		///< 没有Master服务器在线
#define AC_ERROR_CONNECT_NOSTATUS	125		///< 没有上报工作状态
#define AC_ERROR_CONNECT_DATAPREPARE 126	///< 数据还没准备好
#define AC_ERROR_COLDSTANDBY_SLEEP	127		///< 冷备休眠状态

//登录部分
#define AC_ERROR_CERTIFY_FAIL		200		///< 认证失败，用户名或密码有误
#define AC_ERROR_ALREADY_LOGIN		201		///< 该用户已登录
#define AC_ERROR_ACCOUNT_LOCK		202		///< 帐户已被暂时锁定
#define AC_ERROR_IPADDR_LOCK		203		///< IP地址已被暂时锁定
#define AC_ERROR_VISITOR_DENY		204		///< 游客登录被禁止（登录时没有输入密码）
#define AC_ERROR_INVALID_USERID		205		///< 无效的用户ID（用户不存在）
#define AC_ERROR_SERVERSDK_FAIL		206		///< 与业务服务器连接失败，认证功能失效
#define AC_ERROR_SERVERSDK_TIMEOUT	207		///< 业务服务器执行任务超时
#define AC_ERROR_NOTLOGIN			208		///< 没有登录
#define	AC_ERROR_LOGIN_NEWLOGIN		209		///< 该用户在其它计算机上登录
#define AC_ERROR_LOGIN_EMPTYNAME	210		///< 用户名为空
#define AC_ERROR_KICKOUT			211		///< 被服务器踢掉
#define AC_ERROR_SERVER_RESTART		212		///< 业务服务器重启
#define AC_ERROR_FORBIDDEN			213		///< 操作被禁止，没有权限
#define AC_ERROR_SIGSTREMPTY		214		///< 签名信息为空，禁止登录
#define AC_ERROR_SIGVERIFYFAIL		215		///< 签名验证失败
#define AC_ERROR_SIGPUBLICKEYEMPTY	216		///< 签名验证公钥为空
#define AC_ERROR_SIGPRIVATEKEYEMPTY	217		///< 签名私钥为空
#define AC_ERROR_SIGPARAMEMPTY		218		///< 签名参数为空
#define AC_ERROR_SIGPARAMFAIL		219		///< 签名参数出错
#define AC_ERROR_SIGTIMEFAILURE		220		///< 签名时间失效
#define AC_ERROR_APPNOTACTIVE		221		///< 应用没有被激活
#define AC_ERROR_APPPAUSED			222		///< 应用被用户暂停
#define AC_ERROR_APPLOCKED			223		///< 应用被用户锁定
#define AC_ERROR_APPEXPIRED			224		///< 应用已过期
#define AC_ERROR_APPUNKNOWSTATUS	225		///< 应用未知状态
#define AC_ERROR_SIGALREADYUSED		226		///< 签名已经被使用
#define AC_ERROR_USERROLE_FAIL		227		///< 获取用户角色失败
#define AC_ERROR_INVALID_AGENT		228		///< 坐席无效(不存在)
#define AC_ERROR_SERVERSIGFAIL		229		///< 客户端校验服务器签名失败

//进入房间
#define AC_ERROR_ROOM_LOCK			300		///< 房间已被锁住，禁止进入
#define AC_ERROR_ROOM_PASSERR		301		///< 房间密码错误，禁止进入
#define AC_ERROR_ROOM_FULLUSER		302		///< 房间已满员，不能进入
#define AC_ERROR_ROOM_INVALID		303		///< 房间不存在
#define AC_ERROR_ROOM_EXPIRE		304		///< 房间服务时间已到期
#define AC_ERROR_ROOM_REJECT		305		///< 房主拒绝进入
#define AC_ERROR_ROOM_OWNERBEOUT	306		///< 房主不在，不能进入房间
#define AC_ERROR_ROOM_ENTERFAIL		307		///< 不能进入房间
#define AC_ERROR_ROOM_ALREADIN		308		///< 已经在房间里面了，本次进入房间请求忽略
#define AC_ERROR_ROOM_NOTIN			309		///< 不在房间中，对房间相关的API操作失败

// 数据流
#define AC_ERROR_STREAM_OLDPACK		350		///< 过期数据包
#define AC_ERROR_STREAM_SAMEPAK		351		///< 相同的数据包
#define AC_ERROR_STREAM_PACKLOSS	352		///< 数据包丢失
#define AC_ERROR_STREAM_MISTAKE		353		///< 数据包出错，帧序号存在误差
#define AC_ERROR_STREAM_LACKBUFFER	354		///< 媒体流缓冲时间不足

//私聊
#define AC_ERROR_ROOM_PRINULL		401		///< 用户已经离开房间
#define AC_ERROR_ROOM_REJECTPRI		402		///< 用户拒绝了私聊邀请
#define AC_ERROR_ROOM_PRIDENY		403		///< 不允许与该用户私聊，或是用户禁止私聊

#define AC_ERROR_ROOM_PRIREQIDERR	420		///< 私聊请求ID号错误，或请求不存在
#define AC_ERROR_ROOM_PRIALRCHAT	421		///< 已经在私聊列表中

#define AC_ERROR_ROOM_PRITIMEOUT	431		///< 私聊请求超时
#define AC_ERROR_ROOM_PRICHATBUSY	432		///< 对方正在私聊中，繁忙状态
#define AC_ERROR_ROOM_PRIUSERCLOSE	433		///< 对方用户关闭私聊
#define AC_ERROR_ROOM_PRISELFCLOSE	434		///< 用户自己关闭私聊
#define AC_ERROR_ROOM_PRIREQCANCEL	435		///< 私聊请求被取消

// 视频呼叫
#define AC_ERROR_VIDEOCALL_INCHAT	440		///< 正在通话中

//Mic控制权
#define	AC_ERROR_MICLOSE_TIMEOUT	500		///< 说话时间太长，请休息一下
#define AC_ERROR_MICLOSE_HIGHUSER	501		///< 有高级别用户需要发言，请休息一下


// 集群总线
#define AC_ERROR_COMMBUS_SELFMASTER		610	///< 本地总线为Master状态
#define AC_ERROR_COMMBUS_OTHERMASTER	611	///< 有其它总线存在
#define AC_ERROR_COMMBUS_LOWPRIORITY	612 ///< 优先级不够

// 传输部分
#define AC_ERROR_TRANSBUF_CREATEFAIL	700	///< 创建任务失败
#define AC_ERROR_TRANSBUF_NOTASK		701	///< 没有该任务，或是任务已完成

#define AC_ERROR_TRANSFILE_OPENFAIL		710	///< 打开文件出错
#define AC_ERROR_TRANSFILE_ZEROLEN		711	///< 文件长度为0
#define AC_ERROR_TRANSFILE_TOOLARGE		712	///< 文件长度太大
#define AC_ERROR_TRANSFILE_READFAIL		713	///< 读文件出错
#define AC_ERROR_TRANSFILE_DOWNLOADING	714	///< 文件正在下载中
#define AC_ERROR_TRANSFILE_FAILED		715	///< 文件下载失败
#define AC_ERROR_TRANSFILE_NOTASK		716	///< 没有该任务，或是任务已完成

// 录像部分
#define AC_ERROR_RECORD_NOTASK			720	///< 没有录像任务
#define AC_ERROR_RECORD_CREATEFAIL		721	///< 创建录像任务失败
#define AC_ERROR_RECORD_WAITINFO		722	///< 等待用户相关信息，暂时不能录像

// 队列部分
#define AC_ERROR_QUEUE_INVALID			750	///< 无效的队列ID
#define AC_ERROR_QUEUE_PREPARESERVICE	751	///< 准备接受服务，离开队列

// SDK警告
#define AC_ERROR_WARNING_UDPFAIL		780	///< 与服务器的UDP通信异常，流媒体服务将不能正常工作
#define AC_ERROR_WARNING_MISCUTILFAIL	781	///< SDK加载brMiscUtil.dll动态库失败，部分功能将失效
#define AC_ERROR_WARNING_MEDIAUTILFAIL	782	///< SDK加载brMediaUtil.dll动态库失败，部分功能将失效
#define AC_ERROR_WARNING_MEDIACOREFAIL	783	///< SDK加载brMediaCore.dll动态库失败，部分功能将失效
#define AC_ERROR_WARNING_MEDIASHOWFAIL	784	///< SDK加载brMediaShow.dll动态库失败，部分功能将失效

// 授权证书
#define AC_ERROR_CERTFILE_GETINFOFAILED	800	///< 获取授权信息失败
#define AC_ERROR_CERTFILE_EXPIRED		801	///< 授权已过期
#define AC_ERROR_CERTFILE_DECODEFAIL	802	///< 证书解码失败
#define AC_ERROR_CERTFILE_HDSIGFAIL		810	///< 解析硬件特征码失败（可能是证书存在问题）
#define AC_ERROR_CERTFILE_CPUNUMFAIL	811 ///< CPU特征码不匹配（CPU数量）
#define AC_ERROR_CERTFILE_CPUFREQFAIL	812 ///< CPU特征码不匹配（CPU主频）
#define AC_ERROR_CERTFILE_RAMSIZEFAIL	813 ///< 内存特征码不匹配（内存容量）
#define AC_ERROR_CERTFILE_MACADDRFAIL	814 ///< 网卡特征码不匹配（MAC地址）
#define AC_ERROR_CERTFILE_CPUMODELFAIL	815 ///< CPU特征码不匹配（CPU型号）
#define AC_ERROR_CERTFILE_DRIVERIDFAIL	816 ///< 硬盘特征码不匹配（磁盘ID）
#define AC_ERROR_CERTFILE_UKEYSIGFAIL	830	///< UKey信息不正常
#define AC_ERROR_CERTFILE_UKEYNOTFOUND	831	///< 没有查询到UKey设备
#define AC_ERROR_CERTFILE_UKEYREADERR	832	///< 获取UKey信息特征码失败
#define AC_ERROR_CERTFILE_UKEYNOTMATCH	833	///< 绑定的UKey和当前插入的UKey不匹配
#define AC_ERROR_CERTFILE_UKEYDLLFAIL	834	///< 加载UKey动态库失败
#define AC_ERROR_CERTFILE_URLVERIFYFAIL	840	///< 域名解析验证失败
#define AC_ERROR_CERTFILE_DNSFAIL		842	///< 域名解析失败
#define AC_ERROR_CERTFILE_BINDIPFAIL	850	///< 绑定的IP地址和服务器本地IP地址不匹配
#define AC_ERROR_CERTFILE_DOMAINFAIL	860	///< 域名信息错误
#define AC_ERROR_CERTFILE_UKEYFAIL		861	///< UKey信息错误
#define AC_ERROR_CERTFILE_IPADDRFAIL	862	///< IP地址错误

// video device error code define
#define AC_ERROR_VIDEO_OPENFAIL         10001       //  Open video device fail
#define AC_ERROR_VIDEO_UNKNOWFMT        10002       //  Unknow output video pix format
#define AC_ERROR_VIDEO_VIDIOC_G_FMT     10003       //   Driver Not supported VIDIOC_G_FMT
#define AC_ERROR_VIDEO_VIDIOC_S_FMT     10004       //   Driver Not supported VIDIOC_S_FMT
#define AC_ERROR_VIDEO_VIDIOC_G_PARM    10005       //   Driver Not supported VIDIOC_G_PARM
#define AC_ERROR_VIDEO_VIDIOC_S_PARM    10006       //   Driver Not supported VIDIOC_S_PARM
#define AC_ERROR_VIDEO_VIDIOC_QUERYCAP  10007       //  Driver Not supported VIDIOC_QUERYCAP
#define AC_ERROR_VIDEO_V4L2_CAP_VIDEO   10008       //   This is not a capture video device
#define AC_ERROR_VIDEO_PREP_CAPBUFFER_FALL   10009         //   For acquisition error
#define AC_ERROR_VIDEO_VIDIOC_REQBUFS        10010          //  Device Not supported for mmap and usermap mode
#define AC_ERROR_VIDEO_VIDIOC_QUERYBUF       10011          //  get physaddr to block fail
#define AC_ERROR_VIDEO_MAP_FAILED            10012                 //   physaddr map to viraddr fail
#define AC_ERROR_VIDEO_VIDIOC_QBUF           10013              //  QBUF fail
#define AC_ERROR_VIDEO_PREPBUF               10013               // video prepbuff fail
#define AC_ERROR_VIDEO_GETVIDEO_FAIL         10014         // get video fail
#define AC_ERROR_VIDEO_VIDIOC_DQBUF          10015              // QBUF fail
#define AC_ERROR_VIDEO_VIDIOC_STREAMON       10016       // VIDIOC_STREAMON fail
#define AC_ERROR_VIDEO_VIDIOC_STREAMOFF      10017      // VIDIOC_STREAMOFF fail
#define AC_ERROR_VIDEO_CAMERA_EBUSY     10018          // May be camera is used by other progress now
#define AC_ERROR_VIDEO_UNSUPPORTMODE    10019       // unsupport video capture mode
#define AC_ERROR_VIDEO_CAMERA_EINVAL    10020          //    the requested buffer type not supported, or VIDIOC_TRY_FMT was called and is not supported with this buffer type.

// Audio device error code define
#define AC_ERROR_AUDIO_OPENFAIL          10500               //  Open Audio device fail
#define AC_ERROR_AUDIO_ALLOCHWPARAMS     10501          //  alloc hwparams fail
#define AC_ERROR_AUDIO_INTERLEAVED       10502          //  set interleaved mode fail
#define AC_ERROR_AUDIO_FORMAT            10503          //  set wBitsPerSample  fail
#define AC_ERROR_AUDIO_SAMPLESPERSEC     10504          //  set SamplesPerSec   fail
#define AC_ERROR_AUDIO_CHANNELS          10505          //  set channels fail
#define AC_ERROR_AUDIO_PERIODS           10506          //  set periods  fail
#define AC_ERROR_AUDIO_BUFFERSIZE        10507          //set buffer size fail
#define AC_ERROR_AUDIO_PARAMS            10508          // function :snd_pcm_hw_params fail
#define AC_ERROR_AUDIO_BUFFERTIME        10509          //  set rebuffer time fail
#define AC_ERROR_AUDIO_BUFFERFRAME       10510          //  get rebuffer frames fail
#define AC_ERROR_AUDIO_PERIODTIME        10511           //  get period time fail
#define AC_ERROR_AUDIO_PERIODFRAME       10512           //  get period time fail
#define AC_ERROR_AUDIO_ALLOCSWPARAMS     10513           //  alloc swparams fail
#define AC_ERROR_AUDIO_START_THRESHOID   10514           //  set start threshoid fail
#define AC_ERROR_AUDIO_START_AVAIL_MIN   10515           //  set start avail min fail
#define AC_ERROR_AUDIO_PCMPREPARE        10516           //  function snd_pcm_prepare fail
#define AC_ERROR_AUDIO_READFAIL          10517           //  function read fail
#define AC_ERROR_AUDIO_CAPMODE           10518


#define AC_ERROR_PLAY_INVALIDSTREAM			20000

#define AC_ERROR_STREAM_SESSIONFAILED		30000		///< 创建会话失败

// 视频呼叫
#define AC_ERROR_VIDEOCALL_CANCEL			100101		///< 源用户主动放弃会话
#define AC_ERROR_VIDEOCALL_OFFLINE			100102		///< 目标用户不在线
#define	AC_ERROR_VIDEOCALL_BUSY				100103		///< 目标用户忙
#define AC_ERROR_VIDEOCALL_REJECT			100104		///< 目标用户拒绝会话
#define AC_ERROR_VIDEOCALL_TIMEOUT			100105		///< 会话请求超时
#define AC_ERROR_VIDEOCALL_DISCONNECT		100106		///< 网络断线
#define AC_ERROR_VIDEOCALL_NOTINCALL		100107		///< 用户不在呼叫状态
// 视频呼叫（兼容早期的宏定义）
#define GV_ERR_VIDEOCALL_CANCEL				AC_ERROR_VIDEOCALL_CANCEL
#define GV_ERR_VIDEOCALL_OFFLINE			AC_ERROR_VIDEOCALL_OFFLINE
#define	GV_ERR_VIDEOCALL_BUSY				AC_ERROR_VIDEOCALL_BUSY
#define GV_ERR_VIDEOCALL_REJECT				AC_ERROR_VIDEOCALL_REJECT
#define GV_ERR_VIDEOCALL_TIMEOUT			AC_ERROR_VIDEOCALL_TIMEOUT
#define GV_ERR_VIDEOCALL_DISCONNECT			AC_ERROR_VIDEOCALL_DISCONNECT
#define GV_ERR_VIDEOCALL_NOTINCALL			AC_ERROR_VIDEOCALL_NOTINCALL

// 业务对象
#define AC_ERROR_OBJECT_EXISTAREA			100201		///< 已经进入一个服务区域
#define AC_ERROR_OBJECT_EXISTQUEUE			100202		///< 已经进入一个服务队列


// 应用ID
#define AC_ERROR_APPID_DEFAULTNOTSUPPORT	100300		///< 默认的应用ID（空）不被支持
#define AC_ERROR_APPID_SIGNEED				100301		///< 应用登录需要签名
#define AC_ERROR_APPID_SIGFAILED			100302		///< 应用签名校验失败
#define AC_ERROR_APPID_NOTEXIST				100303		///< 应用ID不存在
#define AC_ERROR_APPID_SYSLOCK				100304		///< 应用ID被系统锁定
#define AC_ERROR_APPID_NOTMATCH				100305		///< 应用ID与当前服务不匹配
#define AC_ERROR_APPID_NOTCLOUDSERVER		100306		///< 连接的服务器不是云平台地址
#define AC_ERROR_APPID_CHARGEMACHINELACK	100307		///< 应用所对应的计费服务器不足
#define AC_ERROR_APPID_CHARGEMODECHANGE		100308		///< 应用计费模式改变

// 创建用户
#define AC_ERROR_USERCFG_PASSWDLEN_SMALL	100400		///< 用户密码长度过短
#define AC_ERROR_USERCFG_USERNAME_SAME		100401		///< 用户名重名
#define AC_ERROR_USERCFG_ACCESSLIMIT		100402		///< 权限受限	
#define AC_ERROR_USERCFG_USERNAME_LIMIT		100403		///< 不允许创建该用户名

// 升级服务过程
#define AC_ERROR_LIVEUPDATE_BEGIN					100500		///< 升级服务开始
#define AC_ERROR_LIVEUPDATE_STOPING					100501		///< 升级服务，正在停止当前服务...
#define AC_ERROR_LIVEUPDATE_BACKUPING				100502		///< 升级服务，正在备份当前服务...
#define AC_ERROR_LIVEUPDATE_DELETEING				100503		///< 升级服务，正在删除当前服务...
#define AC_ERROR_LIVEUPDATE_COPYING					100504		///< 升级服务，正在拷贝新服务...
#define AC_ERROR_LIVEUPDATE_STARTING				100505		///< 升级服务，正在启动新服务...
#define AC_ERROR_LIVEUPDATE_RECOVERING				100506		///< 升级服务，正在恢复老版本...
#define AC_ERROR_LIVEUPDATE_ISTAGVER				100507		///< 升级服务，已经是目标版本
#define AC_ERROR_LIVEUPDATE_SERVICENEEDSTOP			100508		///< 升级服务，当前服务需要停止，才能执行升级操作
#define AC_ERROR_LIVEUPDATE_BACKUPFAIL				100509		///< 升级服务，备份失败
#define AC_ERROR_LIVEUPDATE_DELETEFAIL				100510		///< 升级服务，删除失败
#define AC_ERROR_LIVEUPDATE_COPYFAIL				100511		///< 升级服务，拷贝失败
#define AC_ERROR_LIVEUPDATE_RECOVERYFAIL			100512		///< 升级服务，恢复老版本失败
#define AC_ERROR_LIVEUPDATE_BRIDGENOTREGISTER 		100513		///< 升级服务，通讯桥未注册
#define AC_ERROR_LIVEUPDATE_WRITECONFIGFILEFAILED	100514		///< 升级服务，写入配置文件失败
#define AC_ERROR_LIVEUPDATE_CANTGETBACKUPDIR		100515		///< 升级服务，获取备份文件夹失败
#define AC_ERROR_LIVEUPDATE_FINISH					100516		///< 升级服务结束
#define AC_ERROR_LIVEUPDATE_UNABLETOGETMAINTAINIFO	100517		///< 无法获取维护信息
#define AC_ERROR_LIVEUPDATE_NOTRENAMEDIR			100518		///< 不能重命名文件夹

// 停止进程过程
#define AC_ERROR_STOPPROCESS_TIMEOUT				100600		///< 停止进程，超时
#define AC_ERROR_STOPPROCESS_FAIL					100601		///< 停止进程，失败(被回复失败)
#define AC_ERROR_STOPPROCESS_FORCEFAIL				100602		///< 停止进程，强行杀死失败

// 启动进程
#define AC_ERROR_STARTPROCESS_TIMEOUT				100603		///< 启动进程,规定时间内没有收到通讯桥通知

#define AC_ERROR_SERVICE_CONTROLLED					100604		///< service 正在被控制中(e.g 正在执行升级任务的时候，还收到了其他控制命令)
#define AC_ERROR_SERVICE_EXISTELSEVER				100605		///< 在启动或解压之前，发现除目标之外还存在其他版本
#define AC_ERROR_SERVICE_NOTSUPPORT					100606		///< 不支持此操作（e.g 对PMServer下达挂起命令等 ）
#define AC_ERROR_NONEXISTENCE_THE_VERSION			100607		///< 不存在该版本的升级包
#define AC_ERROR_NONEXISTENCE_THE_SERVICE			100608		///< 升级包中不存在该服务
#define AC_ERROR_ILLEGAL_EXTRA_CONFIG				100609		///< 扩展的配置参数非法（e.g LUServer 的 serviceBaseInfo 的扩展参数解析错误） 
#define AC_ERROR_MOVETEMPFILE_FAIL					100610		///< 移动临时文件到升级目录时失败
#define AC_ERROR_INCOMPATIBLE_CURRENT_PLATFORM		100611		///< 不兼容当前OS平台
#define AC_ERROR_GETROOT_CONNECT_FAIL				100612		///< 获取 rootserverconnect 失败

// 业务服务器错误代码
#define AC_ERROR_BUSINESS_PARAM_INVALID				100701		///< 无效参数
#define AC_ERROR_BUSINESS_APPID_NOTEXIST			100702		///< 应用ID不存在
#define AC_ERROR_BUSINESS_BODY_INVALID				100703		///< Body无效
#define AC_ERROR_BUSINESS_SIGVERIFYFAIL				100704		///< 签名验证失败
#define AC_ERROR_BUSINESS_SIGTIMEINVALID			100705		///< 签名时间戳无效
#define AC_ERROR_BUSINESS_MEMORYFAIL				100706		///< not enough memory
#define AC_ERROR_BUSINESS_EXCEPTION					100707		///< 出现异常
#define AC_ERROR_BUSINESS_PROTOCOLFAIL				100708		///< 通信协议出错
#define AC_ERROR_BUSINESS_TIMEOUT					100709		///< 业务服务器执行任务超时
#define AC_ERROR_BUSINESS_FILENOEXIST				100710		///< 文件不存在


// 数据库服务器错误代码
#define AC_ERROR_DB_EXECUTE_ERROR					100801		///< 数据库执行错误
#define AC_ERROR_DB_SELECT_NODATA					100802		///< 数据库查询不到数据
#define AC_ERROR_DB_FETCH_ERROR						100803		///< 数据库读取行数据错误
#define AC_ERROR_DB_EXCEPTION						100804		///< 出现异常
#define AC_ERROR_DB_CONNECT_ERROR					100805		///< 连接异常


#endif // ANYCHAT_ERRORCODE_H_INCLUDED

