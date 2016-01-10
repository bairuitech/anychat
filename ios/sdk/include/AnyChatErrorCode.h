//
//  AnyChatErrorCode.h
//  AnyChat Platform Core SDK for iPhone
//
//  Created by bairuitech on 11-8-2.
//  Copyright 2011 BaiRuiTech. All rights reserved.
//
#if !defined(_ANYCHAT_ERRORCODE_H_INCLUDEDED_)
#define _ANYCHAT_ERRORCODE_H_INCLUDEDED_

#pragma once

#define GV_ERR_SUCCESS				0		///< 成功
#define AC_ERROR_SUCCESS            0    	///< 成功


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

#define AC_ERROR_FUNCNOTALLOW		20		///< 函数功能不允许
#define AC_ERROR_FUNCOPTERROR       21      ///< function parameters error
#define AC_ERROR_DEVICEOPENFAIL     22      ///< device open failed or device no install
#define AC_ERROR_NOENOUGHRESOURCE	23		///< 没有足够的资源
#define AC_ERROR_PIXFMTNOTSUPPORT	24		///< 指定的格式不能被显示设备所支持
#define AC_ERROR_NOTMULTICASTADDR	25		///< 指定的IP地址不是有效的组播地址
#define AC_ERROR_VERSIONNOTMATCH	32		///< 版本不匹配

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
#define	AC_ERROR_CONNECT_DEVICELIMIT 109	///< 嵌入式设备连接限制（没有授权）
#define AC_ERROR_CONNECT_PAUSED		110		///< 服务已被暂停
#define AC_ERROR_CONNECT_IPFORBID	113		///< IP被禁止连接
#define AC_ERROR_CONNECT_TYPEWRONG	114		///< 连接类型错误，服务器不支持当前类型的连接
#define AC_ERROR_CONNECT_ERRORIP	115		///< 服务器IP地址不正确
#define AC_ERROR_CONNECT_SELFCLOSE	116		///< 连接被主动关闭
#define AC_ERROR_CONNECT_NOSVRLIST	117		///< 没有获取到服务器列表
#define AC_ERROR_CONNECT_LBTIMEOUT	118		///< 连接负载均衡服务器超时
#define AC_ERROR_CONNECT_NOTWORK	119		///< 服务器不在工作状态
#define AC_ERROR_CONNECT_OFFLINE	120		///< 服务器不在线


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
#define AC_ERROR_PUBLICKEYEMPTY		214		///< 签名验证公钥为空
#define AC_ERROR_SIGSTREMPTY		215		///< 签名信息为空，禁止登录
#define AC_ERROR_SIGVERIFYFAIL		216		///< 签名验证失败

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


//修改昵称
#define AC_ERROR_NAMECHG_ONUSE		600		///< 该昵称已被使用，请换用其它的昵称

// 传输部分
#define AC_ERROR_TRANSBUF_CREATEFAIL	700	///< 创建任务失败
#define AC_ERROR_TRANSBUF_NOTASK		701	///< 没有该任务，或是任务已完成

#define AC_ERROR_TRANSFILE_OPENFAIL	710		///< 打开文件出错
#define AC_ERROR_TRANSFILE_ZEROLEN	711		///< 文件长度为0
#define AC_ERROR_TRANSFILE_TOOLARGE	712		///< 文件长度太大
#define AC_ERROR_TRANSFILE_READFAIL	713		///< 读文件出错
#define AC_ERROR_TRANSFILE_DOWNLOADING 714	///< 文件正在下载中

// 录像部分
#define AC_ERROR_RECORD_NOTASK		720		///< 没有录像任务
#define AC_ERROR_RECORD_CREATEFAIL	721		///< 创建录像任务失败
#define AC_ERROR_RECORD_WAITINFO	722		///< 等待用户相关信息，暂时不能录像

// 队列部分
#define AC_ERROR_QUEUE_INVALID			750	///< 无效的队列ID
#define AC_ERROR_QUEUE_PREPARESERVICE	751	///< 准备接受服务，离开队列

// SDK警告
#define AC_ERROR_WARNING_UDPFAIL		800	///< 与服务器的UDP通信异常，流媒体服务将不能正常工作
#define AC_ERROR_WARNING_MISCUTILFAIL	801	///< SDK加载brMiscUtil.dll动态库失败，部分功能将失效
#define AC_ERROR_WARNING_MEDIAUTILFAIL	802	///< SDK加载brMediaUtil.dll动态库失败，部分功能将失效
#define AC_ERROR_WARNING_MEDIACOREFAIL	803	///< SDK加载brMediaCore.dll动态库失败，部分功能将失效
#define AC_ERROR_WARNING_MEDIASHOWFAIL	804	///< SDK加载brMediaShow.dll动态库失败，部分功能将失效

// 授权证书
#define AC_ERROR_CERTFILE_URLVERIFYFAIL	840	///< 域名解析验证失败
#define AC_ERROR_CERTFILE_DOMAINFAIL	860	///< 域名信息错误
#define AC_ERROR_CERTFILE_UKEYFAIL		861	///< UKey信息错误
#define AC_ERROR_CERTFILE_IPADDRFAIL	862	///< IP地址错误

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


#endif //_ANYCHAT_ERRORCODE_H_INCLUDEDED_
