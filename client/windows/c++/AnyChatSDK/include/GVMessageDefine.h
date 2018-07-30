// GVMessageDefine.h: interface for the SDK Message.
//
//////////////////////////////////////////////////////////////////////

#if !defined(GV_MESSAGE_DEFINE__)
#define GV_MESSAGE_DEFINE__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef WM_USER
#define WM_USER     0x0400
#endif

#define	WM_GV	WM_USER + 200

#define WM_GV_CONNECT				WM_GV + 1		///< 客户端连接服务器，wParam（BOOL）表示是否连接成功
#define WM_GV_LOGINSYSTEM			WM_GV + 2		///< 客户端登录系统，wParam（INT）表示自己的用户ID号，lParam（INT）表示登录结果：0 成功，否则为出错代码，参考出错代码定义
#define WM_GV_ENTERROOM				WM_GV + 3		///< 客户端进入房间，wParam（INT）表示所进入房间的ID号，lParam（INT）表示是否进入房间：0成功进入，否则为出错代码
#define WM_GV_MICSTATECHANGE		WM_GV + 4		///< 用户的音频设备状态变化消息，wParam（INT）表示用户ID号，lParam（BOOL）表示该用户是否已打开音频采集设备
#define WM_GV_USERATROOM			WM_GV + 5		///< 用户进入（离开）房间，wParam（INT）表示用户ID号，lParam（BOOL）表示该用户是进入（TRUE）或离开（FALSE）房间
#define WM_GV_LINKCLOSE				WM_GV + 6		///< 网络连接已关闭，该消息只有在客户端连接服务器成功之后，网络异常中断之时触发，wParam（INT）表示连接断开的原因
#define WM_GV_ONLINEUSER			WM_GV + 7		///< 收到当前房间的在线用户信息，进入房间后触发一次，wParam（INT）表示在线用户数（包含自己），lParam（INT）表示房间ID
#define WM_GV_FORTUNEMENU			WM_GV + 8		///< 用户选择了一项财富菜单项，wParam（INT）表示用户ID号，lParam（INT）表示财富菜单标记，指示是选择了哪一项菜单
#define WM_GV_ROOMWAITQUEUE			WM_GV + 9		///< 用户收到当前房间等待队列消息，wParam（INT）表示用户前面的队列长度，lParam（INT）表示当前房间总的等待队列长度
#define WM_GV_ENTERREQUEST			WM_GV + 10		///< 用户申请进入房间消息，wParam（INT）表示用户ID号，lParam（BOOL）表示该用户是申请进入（TRUE）房间或离开（FALSE）房间等待队列

#define WM_GV_CAMERASTATE			WM_GV + 11		///< 用户摄像头状态发生变化，wParam（INT）表示用户ID号，lParam（INT）表示摄像头的当前状态，定义为：GV_CAMERA_STATE_XXXX
#define WM_GV_CHATMODECHG			WM_GV + 12		///< 用户聊天模式发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的当前聊天模式
#define WM_GV_ACTIVESTATE			WM_GV + 13		///< 用户活动状态发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的当前活动状态
#define WM_GV_P2PCONNECTSTATE		WM_GV + 14		///< 本地用户与其它用户的P2P网络连接状态发生变化，wParam（INT）表示其它用户ID号，lParam（INT）表示本地用户与其它用户的当前P2P网络连接状态
#define WM_GV_VIDEOSIZECHG			WM_GV + 15		///< 用户视频分辩率发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的视频分辨率组合值（低16位表示宽度，高16位表示高度）
#define WM_GV_USERINFOUPDATE		WM_GV + 16		///< 用户信息更新通知，wParam（INT）表示用户ID号，lParam（INT）表示更新类别
#define WM_GV_FRIENDSTATUS			WM_GV + 17		///< 好友在线状态变化，wParam（INT）表示好友用户ID号，lParam（INT）表示用户的当前活动状态：0 离线， 1 上线
#define WM_GV_OBJECTEVENT			WM_GV + 18		///< 对象事件通知，wParam（INT）表示对象类型，lParam（INT）表示对象ID
#define WM_GV_SESSIONKEEP			WM_GV + 19		///< 会话保持事件，wParam（INT）表示会话保持状态：0 会话保持开始， 1 会话保持结束，lParam（INT）表示出错代码

#define WM_GV_PRIVATEREQUEST		WM_GV + 21		///< 用户发起私聊请求，wParam（INT）表示发起者的用户ID号，lParam（INT）表示私聊请求编号，标识该请求
#define WM_GV_PRIVATEECHO			WM_GV + 22		///< 用户回复私聊请求，wParam（INT）表示回复者的用户ID号，lParam（INT）为出错代码
#define WM_GV_PRIVATEEXIT			WM_GV + 23		///< 用户退出私聊，wParam（INT）表示退出者的用户ID号，lParam（INT）为出错代码
#define WM_GV_SERVERCFGUPDATE		WM_GV + 24		///< 服务器配置参数更新

#define WM_GV_EXTENDBTNPRESS		WM_GV + 31		///< 用户按下扩展按钮，wParam（INT）表示按钮所对应的用户ID号，lParam（DWORD）指示按钮（左下角）所在屏幕位置(x,y)，用户可以利用该参数显示菜单等
#define WM_GV_VIDEOFULLSCREEN		WM_GV + 32		///< 用户视频全屏通知，wParam（INT）表示用户ID，lParam(DWORD)表示当前视频是否全屏显示

#define WM_GV_SDKWARNING			WM_GV + 41		///< SDK警告信息，当SDK在运行过程中自检发现异常状态时，将向上层发送该消息，wParam（INT）表示警告代码，定义为：GV_ERR_WARNING_XXXX

#define WM_GV_AUDIOPLAYCTRL			WM_GV + 100		///< 音频播放设备控制，wParam:1 打开播放器， 0 关闭播放器， lParam：profile，android平台内部使用
#define WM_GV_AUDIORECCTRL			WM_GV + 101		///< 音频录音设备控制，wParam:1 打开音频采集设备，0 关闭音频采集设备
#define WM_GV_VIDEOCAPCTRL			WM_GV + 102		///< 视频采集控制，wParam: 1 开始采集， 0 关闭采集

#endif // !defined(GV_MESSAGE_DEFINE__)
