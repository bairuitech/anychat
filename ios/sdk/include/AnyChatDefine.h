//
//  AnyChatDefine.h
//  AnyChat Platform Core SDK for iPhone
//
//  Created by bairuitech on 11-8-2.
//  Copyright 2011 BaiRuiTech. All rights reserved.
//

#if !defined(_ANYCHAT_DEFINE_H_INCLUDEDED_)
#define _ANYCHAT_DEFINE_H_INCLUDEDED_


/**
 *	异步消息常量定义
 */
#define	WM_GV	0x0400 + 200

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

#define WM_GV_PRIVATEREQUEST		WM_GV + 21		///< 用户发起私聊请求，wParam（INT）表示发起者的用户ID号，lParam（INT）表示私聊请求编号，标识该请求
#define WM_GV_PRIVATEECHO			WM_GV + 22		///< 用户回复私聊请求，wParam（INT）表示回复者的用户ID号，lParam（INT）为出错代码
#define WM_GV_PRIVATEEXIT			WM_GV + 23		///< 用户退出私聊，wParam（INT）表示退出者的用户ID号，lParam（INT）为出错代码

#define WM_GV_EXTENDBTNPRESS		WM_GV + 31		///< 用户按下扩展按钮，wParam（INT）表示按钮所对应的用户ID号，lParam（DWORD）指示按钮（左下角）所在屏幕位置(x,y)，用户可以利用该参数显示菜单等

#define WM_GV_SDKWARNING			WM_GV + 41		///< SDK警告信息，当SDK在运行过程中自检发现异常状态时，将向上层发送该消息，wParam（INT）表示警告代码，定义为：GV_ERR_WARNING_XXXX


// 功能模式定义
#define BRAC_FUNC_VIDEO_CBDATA		0x00000001L	///< 通过回调函数输出视频数据
#define BRAC_FUNC_VIDEO_AUTODISP	0x00000002L	///< 由SDK包处理视频，将视频显示在指定的窗口上
#define BRAC_FUNC_AUDIO_CBDATA		0x00000004L	///< 通过回调函数输出音频数据
#define BRAC_FUNC_AUDIO_AUTOPLAY	0x00000008L	///< 由SDK包处理音频，直接播放
#define BRAC_FUNC_CONFIG_LOCALINI	0x00000010L	///< 生成本地配置文件（AnyChatSDK.ini）
#define BRAC_FUNC_FIREWALL_OPEN		0x00000020L	///< 允许SDK操作Windows防火墙，将当前应用程序加入防火墙访问列表（避免Windows提示用户是否阻止当前应用程序）
#define BRAC_FUNC_CHKDEPENDMODULE	0x00000040L	///< 自动检查SDK所依赖的组件，并自动注册
#define BRAC_FUNC_AUDIO_VOLUMECALC	0x00000080L	///< 由SDK自动计算语音的音量
#define BRAC_FUNC_AUDIO_AUTOVOLUME	0x00000100L	///< 允许SDK自动控制Mic录音音量
#define BRAC_FUNC_NET_SUPPORTUPNP	0x00000200L	///< 允许SDK打开用户网络中的UPNP设备，如果用户的路由器或是防火墙支持UPNP协议，则可提高P2P打洞的成功率
#define BRAC_FUNC_DISABLEDECODE		0x00000400L	///< 禁止对收到的数据进行解码和播放，为了提高代理客户端的数据转发性能，可设置该标志，否则不能设置该标志


// 内核参数定义
#define BRAC_SO_AUDIO_VADCTRL				1	///< 音频静音检测控制（参数为：int型：1打开，0关闭）
#define BRAC_SO_AUDIO_NSCTRL				2	///< 音频噪音抑制控制（参数为：int型：1打开，0关闭）
#define BRAC_SO_AUDIO_ECHOCTRL				3	///< 音频回音消除控制（参数为：int型：1打开，0关闭）
#define BRAC_SO_AUDIO_AGCCTRL				4	///< 音频自动增益控制（参数为：int型：1打开，0关闭）
#define BRAC_SO_AUDIO_CPATUREMODE			5	///< 音频采集模式设置（参数为：int型：0 发言模式，1 放歌模式，2 卡拉OK模式，3 线路输入模式）
#define BRAC_SO_AUDIO_MICBOOST				6	///< 音频采集Mic增强控制（参数为：int型：0 取消，1 选中，2 设备不存在[查询时返回值]）
#define BRAC_SO_AUDIO_AUTOPARAM				7	///< 根据音频采集模式，自动选择合适的相关参数，包括编码器、采样参数、码率参数等（参数为int型：1 启用，0 关闭[默认]）
#define BRAC_SO_AUDIO_MONOBITRATE			8	///< 设置单声道模式下音频编码目标码率（参数为：int型，单位：bps）
#define BRAC_SO_AUDIO_STEREOBITRATE			9	///< 设置双声道模式下音频编码目标码率（参数为：int型，单位：bps）
#define BRAC_SO_AUDIO_PLAYDRVCTRL			70	///< 音频播放驱动选择（参数为：int型，0默认驱动， 1 DSound驱动， 2 WaveOut驱动）

#define BRAC_SO_RECORD_VIDEOBR				10	///< 录像视频码率设置（参数为：int型，单位：bps）
#define BRAC_SO_RECORD_AUDIOBR				11	///< 录像音频码率设置（参数为：int型，单位：bps）
#define BRAC_SO_RECORD_TMPDIR				12	///< 录像文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_SNAPSHOT_TMPDIR				13	///< 快照文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_RECORD_FILETYPE				140	///< 录制文件类型设置（参数为：int型， 0 MP4[默认], 1 WMV, 2 FLV, 3 MP3）
#define BRAC_SO_RECORD_WIDTH				141	///< 录制视频宽度设置（参数为：int型，如：320）
#define BRAC_SO_RECORD_HEIGHT				142	///< 录制文件高度设置（参数为：int型，如：240）
#define BRAC_SO_RECORD_FILENAMERULE			143	///< 录制文件名命名规则（参数为：int型）

#define BRAC_SO_CORESDK_TMPDIR				14	///< 设置AnyChat Core SDK临时目录（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_CORESDK_PATH				20	///< 设置AnyChat Core SDK相关组件路径（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_CORESDK_DUMPCOREINFO		21	///< 输出内核信息到日志文件中，便于分析故障原因（参数为：int型：1 输出）
#define BRAC_SO_CORESDK_MAINVERSION			22	///< 查询SDK主版本号号（参数为int型）
#define BRAC_SO_CORESDK_SUBVERSION			23	///< 查询SDK从版本号（参数为int型）
#define BRAC_SO_CORESDK_BUILDTIME			24	///< 查询SDK编译时间（参数为字符串TCHAR类型）
#define BRAC_SO_CORESDK_ACTIVESTATE			25	///< 应用程序活动状态控制（参数为int型， 1 应用程序处于活动状态， 0 应用程序处于非活动状态），适用于iPhone等设备程序可后台运行的场合
#define BRAC_SO_CORESDK_EXTVIDEOINPUT		26	///< 外部扩展视频输入控制（参数为int型， 0 关闭外部视频输入[默认]， 1 启用外部视频输入）
#define BRAC_SO_CORESDK_EXTAUDIOINPUT		27	///< 外部扩展音频输入控制（参数为int型， 0 关闭外部音频输入[默认]， 1 启用外部音频输入）

#define BRAC_SO_LOCALVIDEO_BITRATECTRL		30	///< 本地视频编码码率设置（参数为int型，单位bps，同服务器配置：VideoBitrate）
#define BRAC_SO_LOCALVIDEO_QUALITYCTRL		31	///< 本地视频编码质量因子控制（参数为int型，同服务器配置：VideoQuality）
#define BRAC_SO_LOCALVIDEO_GOPCTRL			32	///< 本地视频编码关键帧间隔控制（参数为int型，同服务器配置：VideoGOPSize）
#define BRAC_SO_LOCALVIDEO_FPSCTRL			33	///< 本地视频编码帧率控制（参数为int型，同服务器配置：VideoFps）
#define BRAC_SO_LOCALVIDEO_PRESETCTRL		34	///< 本地视频编码预设参数控制（参数为int型，1-5）
#define BRAC_SO_LOCALVIDEO_APPLYPARAM		35	///< 应用本地视频编码参数，使得前述修改即时生效（参数为int型：1 使用新参数，0 使用默认参数）
#define BRAC_SO_LOCALVIDEO_VIDEOSIZEPOLITIC	36	///< 本地视频采集分辩率控制策略（参数为int型，0 自动向下逐级匹配[默认]；1 使用采集设备默认分辩率），当配置的分辩率不被采集设备支持时有效
#define BRAC_SO_LOCALVIDEO_DEINTERLACE		37	///< 本地视频反交织参数控制（参数为int型： 0 不进行反交织处理[默认]；1 反交织处理），当输入视频源是隔行扫描源（如电视信号）时通过反交织处理可以提高画面质量
#define BRAC_SO_LOCALVIDEO_WIDTHCTRL		38	///< 本地视频采集分辨率宽度控制（参数为int型，同服务器配置：VideoWidth）
#define BRAC_SO_LOCALVIDEO_HEIGHTCTRL		39	///< 本地视频采集分辨率高度控制（参数为int型，同服务器配置：VideoHeight）
#define BRAC_SO_LOCALVIDEO_FOCUSCTRL		90	///< 本地视频摄像头对焦控制（参数为int型，1表示自动对焦， 0表示手动对焦）
#define BRAC_SO_LOCALVIDEO_PIXFMTCTRL		91	///< 本地视频采集优先格式控制（参数为int型，-1表示智能匹配，否则优先采用指定格式，参考：BRAC_PixelFormat）
#define BRAC_SO_LOCALVIDEO_OVERLAY			92	///< 本地视频采用Overlay模式（参数为int型，1表示采用Overlay模式， 0表示普通模式[默认]）
#define BRAC_SO_LOCALVIDEO_CODECID			93	///< 本地视频编码器ID设置（参数为int型，-1表示默认，如果设置的编码器ID不存在，则内核会采用默认的编码器）
#define BRAC_SO_LOCALVIDEO_ORIENTATION		97	///< 本地视频设备方向（参数为：int型，定义为常量：ANYCHAT_DEVICEORIENTATION_XXXX）
#define BRAC_SO_LOCALVIDEO_AUTOROTATION		98	///< 本地视频自动旋转控制（参数为int型， 0表示关闭， 1 开启[默认]，视频旋转时需要参考本地视频设备方向参数）

#define BRAC_SO_NETWORK_P2PPOLITIC			40	///< 本地网络P2P策略控制（参数为：int型：0 禁止本地P2P，1 服务器控制P2P[默认]，2 上层应用控制P2P连接，3 按需建立P2P连接）
#define BRAC_SO_NETWORK_P2PCONNECT			41	///< 尝试与指定用户建立P2P连接（参数为int型，表示目标用户ID），连接建立成功后，会通过消息反馈给上层应用，P2P控制策略=2时有效
#define BRAC_SO_NETWORK_P2PBREAK			42	///< 断开与指定用户的P2P连接（参数为int型，表示目标用户ID）[暂不支持，保留]
#define BRAC_SO_NETWORK_TCPSERVICEPORT		43	///< 设置本地TCP服务端口（参数为int型），连接服务器之前设置有效
#define BRAC_SO_NETWORK_UDPSERVICEPORT		44	///< 设置本地UDP服务端口（参数为int型），连接服务器之前设置有效
#define BRAC_SO_NETWORK_MULTICASTPOLITIC	45	///< 组播策略控制（参数为int型：0 执行服务器路由策略，禁止组播发送[默认]， 1 忽略服务器路由策略，只向组播组广播媒体流， 2 执行服务器路由策略，同时组播）
#define BRAC_SO_NETWORK_TRANSBUFMAXBITRATE	46	///< 传输缓冲区、文件最大码率控制（参数为int型，0 不限制，以最快速率传输[默认]， 否则表示限制码率，单位为：bps）
#define BRAC_SO_NETWORK_AUTORECONNECT		47	///< 网络掉线自动重连功能控制（参数为int型，0 关闭， 1 开启[默认]）

#define BRAC_SO_PROXY_FUNCTIONCTRL			50	///< 本地用户代理功能控制，（参数为：int型，1启动代理，0关闭代理[默认]）
#define BRAC_SO_PROXY_VIDEOCTRL				51	///< 本地用户代理视频控制，将本地视频变为指定用户的视频对外发布（参数为int型，表示其它用户的userid）
#define BRAC_SO_PROXY_AUDIOCTRL				52	///< 本地用户代理音频控制，将本地音频变为指定用户的音频对外发布（参数同BRAC_SO_PROXY_VIDEOCTRL）

#define BRAC_SO_STREAM_BUFFERTIME			60	///< 流缓冲时间（参数为int型，单位：毫秒，取值范围：500 ~ 5000，默认：800）

#define BRAC_SO_VIDEOSHOW_MODECTRL			80	///< 视频显示模式控制（参数为：int型，0 单画面显示，1 视频迭加显示）
#define BRAC_SO_VIDEOSHOW_SETPRIMARYUSER	81	///< 设置主显示用户编号（参数为：int型，用户ID号）
#define BRAC_SO_VIDEOSHOW_SETOVERLAYUSER	82	///< 设置迭加显示用户编号（参数为：int型，用户ID号）
#define BRAC_SO_VIDEOSHOW_DRIVERCTRL		83	///< 视频显示驱动控制（参数为：int型，0 默认驱动， 1 Windows DirectShow，2 Windows GDI，3 SDL）
#define BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER	84	///< 视频数据经过GPU直接渲染，将解码后的视频数据直接传输到GPU的物理地址（参数为：int型， 0 关闭[默认]， 1 打开），与硬件平台相关
#define BRAC_SO_VIDEOSHOW_AUTOROTATION		85	///< 远程视频显示自动旋转控制（参数为int型， 0表示关闭， 1 开启[默认]，视频旋转时需要参考本地视频设备方向参数）

#define BRAC_SO_CORESDK_DEVICEMODE			130	///< 设备模式控制（局域网设备之间可以互相通信，不依赖服务器；参数为int型，0 关闭[默认]，1 开启）
#define BRAC_SO_CORESDK_DATAENCRYPTION		132	///< 数据加密控制（参数为：int型， 0 关闭[默认]， 1 开启）
#define BRAC_SO_CORESDK_UPLOADLOGINFO		134	///< 上传日志信息到客户端（参数为：int型，0 关闭[默认]， 1 开启）

// 传输任务信息参数定义
#define BRAC_TRANSTASK_PROGRESS				1	///< 传输任务进度查询（参数为：DOUBLE型（0.0 ~ 100.0））
#define BRAC_TRANSTASK_BITRATE				2	///< 传输任务当前传输码率（参数为：int型，单位：bps）
#define BRAC_TRANSTASK_STATUS				3	///< 传输任务当前状态（参数为：int型）


// 录像功能标志定义（API：BRAC_StreamRecordCtrl 传入参数）
#define BRAC_RECORD_FLAGS_VIDEO		0x00000001	///< 录制视频
#define BRAC_RECORD_FLAGS_AUDIO		0x00000002	///< 录制音频
#define BRAC_RECORD_FLAGS_SERVER	0x00000004	///< 服务器端录制
#define BRAC_RECORD_FLAGS_MIXAUDIO	0x00000010	///< 录制音频时，将其它人的声音混音后录制
#define BRAC_RECORD_FLAGS_MIXVIDEO	0x00000020	///< 录制视频时，将其它人的视频迭加后录制
#define BRAC_RECORD_FLAGS_ABREAST	0x00000100	///< 录制视频时，将其它人的视频并列录制
#define BRAC_RECORD_FLAGS_STEREO	0x00000200	///< 录制音频时，将其它人的声音混合为立体声后录制
#define BRAC_RECORD_FLAGS_SNAPSHOT	0x00000400	///< 拍照
#define BRAC_RECORD_FLAGS_LOCALCB	0x00000800	///< 触发本地回调
#define BRAC_RECORD_FLAGS_STREAM	0x00001000	///< 对视频流进行录制（效率高，但可能存在视频方向旋转的问题）

// 客户端、服务器端录制标志定义保持统一
#define ANYCHAT_RECORD_FLAGS_VIDEO		BRAC_RECORD_FLAGS_VIDEO
#define ANYCHAT_RECORD_FLAGS_AUDIO		BRAC_RECORD_FLAGS_AUDIO
#define ANYCHAT_RECORD_FLAGS_SERVER		BRAC_RECORD_FLAGS_SERVER
#define ANYCHAT_RECORD_FLAGS_MIXAUDIO	BRAC_RECORD_FLAGS_MIXAUDIO
#define ANYCHAT_RECORD_FLAGS_MIXVIDEO	BRAC_RECORD_FLAGS_MIXVIDEO
#define ANYCHAT_RECORD_FLAGS_ABREAST	BRAC_RECORD_FLAGS_ABREAST
#define ANYCHAT_RECORD_FLAGS_STEREO		BRAC_RECORD_FLAGS_STEREO
#define ANYCHAT_RECORD_FLAGS_SNAPSHOT	BRAC_RECORD_FLAGS_SNAPSHOT
#define ANYCHAT_RECORD_FLAGS_LOCALCB	BRAC_RECORD_FLAGS_LOCALCB
#define ANYCHAT_RECORD_FLAGS_STREAM		BRAC_RECORD_FLAGS_STREAM

// 组播功能标志定义
#define BRAC_MCFLAGS_JOINGROUP		0x00000001L	///< 加入多播组
#define BRAC_MCFLAGS_LEAVEGROUP		0x00000002L	///< 离开多播组
#define BRAC_MCFLAGS_SENDDATA		0x00000010L	///< 数据发送标志，指示该多播组用于发送数据
#define BRAC_MCFLAGS_RECVDATA		0x00000020L	///< 数据接收标志，指示该多播组用于接收数据


// 用户状态标志定义（API：BRAC_QueryUserState 传入参数）
#define BRAC_USERSTATE_CAMERA				1	///< 用户摄像头状态（参数为DWORD型）
#define BRAC_USERSTATE_HOLDMIC				2	///< 用户音频设备状态（参数为DWORD型，返回值：0 音频采集关闭， 1 音频采集开启）
#define BRAC_USERSTATE_SPEAKVOLUME			3	///< 用户当前说话音量（参数为DOUBLE类型（0.0 ~ 100.0））
#define BRAC_USERSTATE_RECORDING			4	///< 用户录像（音）状态（参数为DWORD型）
#define	BRAC_USERSTATE_LEVEL				5	///< 用户级别（参数为DWORD型）
#define BRAC_USERSTATE_NICKNAME				6	///< 用户昵称（参数为字符串TCHAR类型）
#define BRAC_USERSTATE_LOCALIP				7	///< 用户本地IP地址（内网，参数为字符串TCHAR类型）
#define BRAC_USERSTATE_INTERNETIP			8	///< 用户互联网IP地址（参数为字符串TCHAR类型）
#define BRAC_USERSTATE_VIDEOBITRATE			9	///< 用户当前的视频码率（参数为DWORD类型，Bps）
#define BRAC_USERSTATE_AUDIOBITRATE			10	///< 用户当前的音频码率（参数为DWORD类型，Bps）
#define BRAC_USERSTATE_P2PCONNECT			11	///< 查询本地用户与指定用户的当前P2P连接状态（参数为DWORD类型，返回值：0 P2P不通， 1 P2P连接成功[TCP]，2 P2P连接成功[UDP]，3 P2P连接成功[TCP、UDP]）
#define BRAC_USERSTATE_NETWORKSTATUS		12	///< 查询指定用户的网络状态（参数为DWORD类型，返回值：0 优良，1 较好，2 一般，3 较差，4 非常差），注：查询间隔需要>1s
#define BRAC_USERSTATE_VIDEOSIZE			13	///< 查询指定用户的视频分辨率（参数为DWORD类型，返回值：低16位表示宽度，高16位表示高度）
#define BRAC_USERSTATE_PACKLOSSRATE			14	///< 查询指定用户的网络流媒体数据丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）
#define BRAC_USERSTATE_DEVICETYPE			15	///< 查询指定用户的终端类型（参数为DWORD类型，返回值：0 Unknow，1 Windows，2 Android，3 iOS，4 Web，5 Linux，6 Mac，7 Win Phone，8 WinCE）
#define BRAC_USERSTATE_SELFUSERSTATUS		16	///< 查询本地用户的当前状态（参数为DWORD类型，返回值：0 Unknow，1 Connected，2 Logined，3 In Room，4 Logouted，5 Link Closed）
#define BRAC_USERSTATE_SELFUSERID			17	///< 查询本地用户的ID（参数为DWORD类型，若用户登录成功，返回用户实际的userid，否则返回-1）

// 视频呼叫事件类型定义（API：BRAC_VideoCallControl 传入参数、VideoCallEvent回调参数）
#define BRAC_VIDEOCALL_EVENT_REQUEST		1	///< 呼叫请求
#define BRAC_VIDEOCALL_EVENT_REPLY			2	///< 呼叫请求回复J
#define BRAC_VIDEOCALL_EVENT_START			3	///< 视频呼叫会话开始事件
#define BRAC_VIDEOCALL_EVENT_FINISH			4	///< 挂断（结束）呼叫会话

// 视频呼叫标志定义（API：BRAC_VideoCallControl 传入参数）
#define BRAC_VIDEOCALL_FLAGS_AUDIO		0x01	///< 语音通话
#define BRAC_VIDEOCALL_FLAGS_VIDEO		0x02	///< 视频通话
#define BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO	0x10	///< 禁止源（呼叫端）音频
#define BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO	0x20	///< 禁止源（呼叫端）视频
#define BRAC_VIDEOCALL_FLAGS_FBTARAUDIO	0x40	///< 禁止目标（被呼叫端）音频
#define BRAC_VIDEOCALL_FLAGS_FBTARVIDEO	0x80	///< 禁止目标（被呼叫端）视频

// 远程视频方向修正标志定义
#define BRAC_ROTATION_FLAGS_MIRRORED	0x1000	///< 图像需要镜像翻转
#define BRAC_ROTATION_FLAGS_ROTATION90	0x2000	///< 顺时针旋转90度
#define BRAC_ROTATION_FLAGS_ROTATION180	0x4000	///< 顺时针旋转180度
#define BRAC_ROTATION_FLAGS_ROTATION270	0x8000	///< 顺时针旋转270度

// 用户信息控制类型定义（API：BRAC_UserInfoControl 传入参数）
#define BRAC_USERINFO_CTRLCODE_ROTATION		8	///< 让指定的用户视频在显示时旋转，wParam为旋转角度参数
#define BRAC_USERINFO_CTRLCODE_DEBUGLOG		9	///< 输出本地用户的调试日志，wParam为调试日志类型，lParam为是否开启
#define BRAC_USERINFO_CTRLCODE_LVORIENTFIX	10	///< 本地视频采集方向修正，wParam为方向参数，lParam为修正角度

// 数据加（解）密标志定义（DataEncDec回调参数）
#define BRAC_DATAENCDEC_FLAGS_ENCMODE	0x01	///< 加密模式
#define BRAC_DATAENCDEC_FLAGS_DECMODE	0x02	///< 解密模式
#define BRAC_DATAENCDEC_FLAGS_AUDIO		0x10	///< 音频编码数据
#define BRAC_DATAENCDEC_FLAGS_VIDEO		0x20	///< 视频编码数据
#define BRAC_DATAENCDEC_FLAGS_BUFFER	0x40	///< 透明通道数据
#define BRAC_DATAENCDEC_FLAGS_TXTMSG	0x80	///< 文字聊天数据




#endif //_ANYCHAT_DEFINE_H_INCLUDEDED_
