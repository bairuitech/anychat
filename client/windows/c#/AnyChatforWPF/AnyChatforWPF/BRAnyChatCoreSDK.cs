using System;
using System.Text;
using System.Runtime.InteropServices;

namespace ANYCHATAPI
{
    /********************************************************************************
    * ** AnyChat Platform Core SDK
    * *********************************************************************************/
    public class AnyChatCoreSDK
    {
		public const string AnyChatCoreSDKDll = "BRAnyChatCore.dll";
		
        #region AnyChat Platform Core SDK 常量定义
        // 内核参数定义，API：BRAC_SetSDKOption、BRAC_GetSDKOption 传入参数
        public const int BRAC_SO_AUDIO_VADCTRL			=	1;	// 音频静音检测控制（参数为：int型：1打开，0关闭）
        public const int BRAC_SO_AUDIO_NSCTRL			=	2;	// 音频噪音抑制控制（参数为：int型：1打开，0关闭）
        public const int BRAC_SO_AUDIO_ECHOCTRL			=	3;	// 音频回音消除控制（参数为：int型：1打开，0关闭）
        public const int BRAC_SO_AUDIO_AGCCTRL			=	4;	// 音频自动增益控制（参数为：int型：1打开，0关闭）
        public const int BRAC_SO_AUDIO_CPATUREMODE		=	5;	// 音频采集模式设置（参数为：int型：0 发言模式，1 放歌模式，2 卡拉OK模式，3 线路输入模式）
        public const int BRAC_SO_AUDIO_MICBOOST			=	6;	// 音频采集Mic增强控制（参数为：int型：0 取消，1 选中，2 设备不存在[查询时返回值]）
		public const int BRAC_SO_AUDIO_AUTOPARAM		=	7;	// 根据音频采集模式，自动选择合适的相关参数，包括编码器、采样参数、码率参数等（参数为int型：1 启用，0 关闭[默认]）
		public const int BRAC_SO_AUDIO_MONOBITRATE		=	8;	// 设置单声道模式下音频编码目标码率（参数为：int型，单位：bps）
		public const int BRAC_SO_AUDIO_STEREOBITRATE	=	9;	// 设置双声道模式下音频编码目标码率（参数为：int型，单位：bps）
		public const int BRAC_SO_AUDIO_PLAYDRVCTRL		=	70;	// 音频播放驱动选择（参数为：int型，0默认驱动， 1 DSound驱动， 2 WaveOut驱动）
		public const int BRAC_SO_AUDIO_SOFTVOLMODE		=	73;	// 设置软件音量模式控制（参数为int型，1打开，0关闭[默认]），使用软件音量模式，将不会改变系统的音量设置
		public const int BRAC_SO_AUDIO_RECORDDRVCTRL	=	74;	// 音频采集驱动控制（参数为int型，0默认驱动， 1 DSound驱动， 2 WaveIn驱动， 3 Java采集[Android平台使用]）

        public const int BRAC_SO_RECORD_VIDEOBR			=	10;	// 录像视频码率设置（参数为：int型，单位：bps）
        public const int BRAC_SO_RECORD_AUDIOBR			=	11;	// 录像音频码率设置（参数为：int型，单位：bps）
        public const int BRAC_SO_RECORD_TMPDIR			=	12;	// 录像文件临时目录设置（参数为字符串PCHAR类型，必须是完整的绝对路径）
        public const int BRAC_SO_SNAPSHOT_TMPDIR		=	13;	// 快照文件临时目录设置（参数为字符串PCHAR类型，必须是完整的绝对路径）
        public const int BRAC_SO_CORESDK_TMPDIR			=	14;	// 设置AnyChat Core SDK临时目录（参数为字符串PCHAR类型，必须是完整的绝对路径）
        public const int BRAC_SO_CORESDK_PATH			=	20;	// 设置AnyChat Core SDK相关组件路径（参数为字符串PCHAR类型，必须是完整的绝对路径）
		public const int BRAC_SO_CORESDK_DUMPCOREINFO	=	21;	// 输出内核信息到日志文件中，便于分析故障原因（参数为：int型：1 输出）
		public const int BRAC_SO_CORESDK_EXTVIDEOINPUT	=	26;	// 外部扩展视频输入控制（参数为int型， 0 关闭外部视频输入[默认]， 1 启用外部视频输入）
		public const int BRAC_SO_CORESDK_EXTAUDIOINPUT	=	27;	// 外部扩展音频输入控制（参数为int型， 0 关闭外部音频输入[默认]， 1 启用外部音频输入）
		
        public const int BRAC_SO_LOCALVIDEO_BITRATECTRL	=	30;	// 本地视频编码码率设置（参数为int型，单位bps，同服务器配置：VideoBitrate）
        public const int BRAC_SO_LOCALVIDEO_QUALITYCTRL	=	31;	// 本地视频编码质量因子控制（参数为int型，同服务器配置：VideoQuality）
        public const int BRAC_SO_LOCALVIDEO_GOPCTRL		=	32;	// 本地视频编码关键帧间隔控制（参数为int型，同服务器配置：VideoGOPSize）
        public const int BRAC_SO_LOCALVIDEO_FPSCTRL		=	33;	// 本地视频编码帧率控制（参数为int型，同服务器配置：VideoFps）
        public const int BRAC_SO_LOCALVIDEO_PRESETCTRL	=	34;	// 本地视频编码预设参数控制（参数为int型，1-5）
        public const int BRAC_SO_LOCALVIDEO_APPLYPARAM	=	35;	// 应用本地视频编码参数，使得前述修改即时生效（参数为int型：1 使用新参数，0 使用默认参数）
        public const int BRAC_SO_LOCALVIDEO_VIDEOSIZEPOLITIC=36;// 本地视频采集分辩率控制策略（参数为int型，0 自动向下逐级匹配[默认]；1 使用采集设备默认分辩率），当配置的分辩率不被采集设备支持时有效
        public const int BRAC_SO_LOCALVIDEO_DEINTERLACE	=	37;	// 本地视频反交织参数控制（参数为int型： 0 不进行反交织处理[默认]；1 反交织处理），当输入视频源是隔行扫描源（如电视信号）时通过反交织处理可以提高画面质量
		public const int BRAC_SO_LOCALVIDEO_WIDTHCTRL	=	38;	// 本地视频采集分辨率宽度控制（参数为int型，同服务器配置：VideoWidth）
		public const int BRAC_SO_LOCALVIDEO_HEIGHTCTRL	=	39;	// 本地视频采集分辨率高度控制（参数为int型，同服务器配置：VideoHeight）
		public const int BRAC_SO_LOCALVIDEO_FOCUSCTRL	=	90;	// 本地视频摄像头对焦控制（参数为int型，1表示自动对焦， 0表示手动对焦）
		public const int BRAC_SO_LOCALVIDEO_PIXFMTCTRL	=	91;	// 本地视频采集优先格式控制（参数为int型，-1表示智能匹配，否则优先采用指定格式，参考：BRAC_PixelFormat）
		public const int BRAC_SO_LOCALVIDEO_TVFORMAT	=	104;// 视频采集制式设置（参数为：int型，定义为DirectShow::strmif.h::AnalogVideoStandard，默认为：AnalogVideo_PAL_B）
		
        public const int BRAC_SO_NETWORK_P2PPOLITIC		=	40;	// 本地网络P2P策略控制（参数为：int型：0 禁止本地P2P，1 服务器控制P2P[默认]，2 上层应用控制P2P连接，3 按需建立P2P连接）
        public const int BRAC_SO_NETWORK_P2PCONNECT		=	41;	// 尝试与指定用户建立P2P连接（参数为int型，表示目标用户ID），连接建立成功后，会通过消息反馈给上层应用，P2P控制策略=2时有效
        public const int BRAC_SO_NETWORK_P2PBREAK       =   42;	// 断开与指定用户的P2P连接（参数为int型，表示目标用户ID）[暂不支持，保留]
		public const int BRAC_SO_NETWORK_TCPSERVICEPORT	=	43;	// 设置本地TCP服务端口（参数为int型），连接服务器之前设置有效
		public const int BRAC_SO_NETWORK_UDPSERVICEPORT	=	44;	// 设置本地UDP服务端口（参数为int型），连接服务器之前设置有效
		public const int BRAC_SO_NETWORK_MULTICASTPOLITIC=	45;	// 组播策略控制（参数为int型：0 执行服务器路由策略，禁止组播发送[默认]， 1 忽略服务器路由策略，只向组播组广播媒体流， 2 执行服务器路由策略，同时组播）
		public const int BRAC_SO_NETWORK_TRANSBUFMAXBITRATE=46;	// 传输缓冲区、文件最大码率控制（参数为int型，0 不限制，以最快速率传输[默认]， 否则表示限制码率，单位为：bps）
		
		public const int BRAC_SO_STREAM_MAXBUFFERTIME	=	60;	// 最大流缓冲时间（参数为int型，单位：毫秒，取值范围：500 ~ 5000，默认：800），发言模式设置值，歌曲模式会自动增加一倍
		public const int BRAC_SO_STREAM_SMOOTHPLAYMODE	=	61;	// 平滑播放模式（参数为int型，0 关闭[默认], 1 打开），打开状态下遇到视频丢帧时会继续播放（可能出现马赛克），不会卡住
		
		public const int BRAC_SO_VIDEOSHOW_MODECTRL		=	80;	// 视频显示模式控制（参数为：int型，0 单画面显示，1 视频迭加显示）
		public const int BRAC_SO_VIDEOSHOW_SETPRIMARYUSER=	81;	// 设置主显示用户编号（参数为：int型，用户ID号）
		public const int BRAC_SO_VIDEOSHOW_SETOVERLAYUSER=	82;	// 设置迭加显示用户编号（参数为：int型，用户ID号）
		public const int BRAC_SO_VIDEOSHOW_DRIVERCTRL	=	83;	// 视频显示驱动控制（参数为：int型，0 默认驱动， 1 Windows DirectShow，2 Windows GDI，3 SDL）
		
        // 用户状态标志定义，API：BRAC_QueryUserState 传入参数
        public const int BRAC_USERSTATE_CAMERA		    =	1;	// 用户摄像头状态（参数为DWORD型）
        public const int BRAC_USERSTATE_HOLDMIC		    =	2;	// 用户音频设备状态（参数为DWORD型，返回值：0 音频采集关闭， 1 音频采集开启）
        public const int BRAC_USERSTATE_SPEAKVOLUME	    =	3;	// 用户当前说话音量（参数为DOUBLE类型（0.0 ~ 100.0））
        public const int BRAC_USERSTATE_RECORDING	    =	4;	// 用户录像（音）状态（参数为DWORD型）
        public const int BRAC_USERSTATE_LEVEL		    =	5;	// 用户级别（参数为DWORD型）
        public const int BRAC_USERSTATE_NICKNAME	    =	6;	// 用户昵称（参数为字符串PCHAR类型）
        public const int BRAC_USERSTATE_LOCALIP		    =	7;	// 用户本地IP地址（内网，参数为字符串PCHAR类型）
        public const int BRAC_USERSTATE_INTERNETIP	    =	8;	// 用户互联网IP地址（参数为字符串PCHAR类型）
        public const int BRAC_USERSTATE_VIDEOBITRATE    =	9;	// 用户当前的视频码率（参数为DWORD类型，Bps）
        public const int BRAC_USERSTATE_AUDIOBITRATE    =	10;	// 用户当前的音频码率（参数为DWORD类型，Bps）
        public const int BRAC_USERSTATE_P2PCONNECT	    =	11;	// 查询本地用户与指定用户的当前P2P连接状态（参数为DWORD类型，返回值：0 P2P不通， 1 P2P连接成功[TCP]，2 P2P连接成功[UDP]，3 P2P连接成功[TCP、UDP]）
        public const int BRAC_USERSTATE_NETWORKSTATUS   =   12;	// 查询指定用户的网络状态（参数为DWORD类型，返回值：0 优良，1 较好，2 一般，3 较差，4 非常差），注：查询间隔需要>1s
		public const int BRAC_USERSTATE_VIDEOSIZE		=	13;	// 查询指定用户的视频分辨率（参数为DWORD类型，返回值：低16位表示宽度，高16位表示高度）
		public const int BRAC_USERSTATE_PACKLOSSRATE	=	14;	// 查询指定用户的网络流媒体数据丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）
		public const int BRAC_USERSTATE_DEVICETYPE		=	15; // 查询指定用户的终端类型（参数为DWORD类型，返回值：0 Unknow， 1 Windows，2 Android，3 iOS，4 Web，5 Linux，6 Mac，7 Win Phone，8 WinCE）
		public const int BRAC_USERSTATE_SELFUSERSTATUS	=	16;	// 查询本地用户的当前状态（参数为DWORD类型，返回值：0 Unknow，1 Connected，2 Logined，3 In Room，4 Logouted，5 Link Closed）
		public const int BRAC_USERSTATE_SELFUSERID		=	17;	// 查询本地用户的ID（参数为DWORD类型，若用户登录成功，返回用户实际的userid，否则返回-1）
		
		// 组播功能标志定义（API：BRAC_MultiCastControl 传入参数）
		public const int BRAC_MCFLAGS_JOINGROUP	= 0x00000001;	// 加入多播组
		public const int BRAC_MCFLAGS_LEAVEGROUP= 0x00000002;	// 离开多播组
		public const int BRAC_MCFLAGS_SENDDATA	= 0x00000010;	// 数据发送标志，指示该多播组用于发送数据
		public const int BRAC_MCFLAGS_RECVDATA	= 0x00000020;	// 数据接收标志，指示该多播组用于接收数据
		
		// 传输任务信息参数定义（API：BRAC_QueryTransTaskInfo 传入参数）
		public const int BRAC_TRANSTASK_PROGRESS		=	1;	// 传输任务进度查询（参数为：DOUBLE型，返回值0.0 ~ 100.0， 或参数为：DWORD型，返回值0 ~ 100）
		public const int BRAC_TRANSTASK_BITRATE			=	2;	// 传输任务当前传输码率（参数为：int型，单位：bps）
		public const int BRAC_TRANSTASK_STATUS			=	3;	// 传输任务当前状态（参数为：int型）
		public const int BRAC_TRANSTASK_SAVEASPATH		=	4;	// 文件传输任务另存为路径设置（参数为字符串TCHAR类型）
		
		// 录像功能标志定义（API：BRAC_StreamRecordCtrl 传入参数）
		public const int BRAC_RECORD_FLAGS_VIDEO		= 0x01;	// 录制视频
		public const int BRAC_RECORD_FLAGS_AUDIO		= 0x02;	// 录制音频
		public const int BRAC_RECORD_FLAGS_SERVER		= 0x04;	// 服务器端录制
		public const int BRAC_RECORD_FLAGS_MIXAUDIO		= 0x10;	// 录制音频时，将其它人的声音混音后录制
		public const int BRAC_RECORD_FLAGS_MIXVIDEO		= 0x20;	// 录制视频时，将其它人的视频迭加后录制
		
		// 视频呼叫事件类型定义（API：BRAC_VideoCallControl 传入参数、VideoCallEvent回调参数）
		public const int BRAC_VIDEOCALL_EVENT_REQUEST	=	1;	// 呼叫请求
		public const int BRAC_VIDEOCALL_EVENT_REPLY		=	2;	// 呼叫请求回复
		public const int BRAC_VIDEOCALL_EVENT_START		=	3;	// 视频呼叫会话开始事件
		public const int BRAC_VIDEOCALL_EVENT_FINISH	=	4;	// 挂断（结束）呼叫会话

		// 视频呼叫标志定义（API：BRAC_VideoCallControl 传入参数）
		public const int BRAC_VIDEOCALL_FLAGS_AUDIO		=0x01;	// 语音通话
		public const int BRAC_VIDEOCALL_FLAGS_VIDEO		=0x02;	// 视频通话
		public const int BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO=0x10;	// 禁止源（呼叫端）音频
		public const int BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO=0x20;	// 禁止源（呼叫端）视频
		public const int BRAC_VIDEOCALL_FLAGS_FBTARAUDIO=0x40;	// 禁止目标（被呼叫端）音频
		public const int BRAC_VIDEOCALL_FLAGS_FBTARVIDEO=0x80;	// 禁止目标（被呼叫端）视频
		
		// 远程视频方向修正标志定义
		public const int BRAC_ROTATION_FLAGS_MIRRORED	=0x1000;// 图像需要镜像翻转
		public const int BRAC_ROTATION_FLAGS_ROTATION90	=0x2000;// 顺时针旋转90度
		public const int BRAC_ROTATION_FLAGS_ROTATION180=0x4000;// 顺时针旋转180度
		public const int BRAC_ROTATION_FLAGS_ROTATION270=0x8000;// 顺时针旋转270度

		// 用户信息控制类型定义（API：BRAC_UserInfoControl 传入参数）
		public const int BRAC_USERINFO_CTRLCODE_ROTATION=	8;	// 让指定的用户视频在显示时旋转，wParam为旋转角度参数

        // SDK消息定义
        public const int WM_GV = 0x0400 + 200;
        public const int WM_GV_CONNECT			=	WM_GV + 1;	// 客户端连接服务器，wParam（BOOL）表示是否连接成功
        public const int WM_GV_LOGINSYSTEM		=	WM_GV + 2;	// 客户端登录系统，wParam（INT）表示自己的用户ID号，lParam（INT）表示登录结果：0 成功，否则为出错代码，参考出错代码定义
        public const int WM_GV_ENTERROOM		=	WM_GV + 3;	// 客户端进入房间，wParam（INT）表示所进入房间的ID号，lParam（INT）表示是否进入房间：0成功进入，否则为出错代码
        public const int WM_GV_MICSTATECHANGE	=	WM_GV + 4;	// 用户的音频设备状态变化消息，wParam（INT）表示用户ID号，lParam（BOOL）表示该用户是否已打开音频采集设备
        public const int WM_GV_USERATROOM		=	WM_GV + 5;	// 用户进入（离开）房间，wParam（INT）表示用户ID号，lParam（BOOL）表示该用户是进入（TRUE）或离开（FALSE）房间
        public const int WM_GV_LINKCLOSE		=	WM_GV + 6;	// 网络连接已关闭，该消息只有在客户端连接服务器成功之后，网络异常中断之时触发，wParam（INT）表示连接断开的原因
        public const int WM_GV_ONLINEUSER		=	WM_GV + 7;	// 收到当前房间的在线用户信息，进入房间后触发一次，wParam（INT）表示在线用户数（包含自己），lParam（INT）表示房间ID
        public const int WM_GV_FORTUNEMENU		=	WM_GV + 8;	// 用户选择了一项财富菜单项，wParam（INT）表示用户ID号，lParam（INT）表示财富菜单标记，指示是选择了哪一项菜单
        public const int WM_GV_ROOMWAITQUEUE	=	WM_GV + 9;	// 用户收到当前房间等待队列消息，wParam（INT）表示用户前面的队列长度，lParam（INT）表示当前房间总的等待队列长度
        public const int WM_GV_ENTERREQUEST		=	WM_GV + 10;	// 用户申请进入房间消息，wParam（INT）表示用户ID号，lParam（BOOL）表示该用户是申请进入（TRUE）房间或离开（FALSE）房间等待队列
        public const int WM_GV_CAMERASTATE		=	WM_GV + 11;	// 用户摄像头状态发生变化，wParam（INT）表示用户ID号，lParam（INT）表示摄像头的当前状态，定义为：GV_CAMERA_STATE_XXXX
        public const int WM_GV_CHATMODECHG		=	WM_GV + 12;	// 用户聊天模式发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的当前聊天模式
        public const int WM_GV_ACTIVESTATE		=	WM_GV + 13;	// 用户活动状态发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的当前活动状态
        public const int WM_GV_P2PCONNECTSTATE	=	WM_GV + 14;	// 本地用户与其它用户的P2P网络连接状态发生变化，wParam（INT）表示其它用户ID号，lParam（INT）表示本地用户与其它用户的当前P2P网络连接状态
		public const int WM_GV_VIDEOSIZECHG		=	WM_GV + 15;	// 用户视频分辩率发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的视频分辨率组合值（低16位表示宽度，高16位表示高度）
		public const int WM_GV_USERINFOUPDATE	=	WM_GV + 16;	// 用户信息更新通知，wParam（INT）表示用户ID号，lParam（INT）表示更新类别
		public const int WM_GV_FRIENDSTATUS		=	WM_GV + 17;	// 好友在线状态变化，wParam（INT）表示好友用户ID号，lParam（INT）表示用户的当前活动状态：0 离线， 1 上线
        public const int WM_GV_PRIVATEREQUEST	=	WM_GV + 21;	// 用户发起私聊请求，wParam（INT）表示发起者的用户ID号，lParam（INT）表示私聊请求编号，标识该请求
        public const int WM_GV_PRIVATEECHO		=	WM_GV + 22;	// 用户回复私聊请求，wParam（INT）表示回复者的用户ID号，lParam（INT）为出错代码
        public const int WM_GV_PRIVATEEXIT		=	WM_GV + 23;	// 用户退出私聊，wParam（INT）表示退出者的用户ID号，lParam（INT）为出错代码
        public const int WM_GV_EXTENDBTNPRESS	=	WM_GV + 31;	// 用户按下扩展按钮，wParam（INT）表示按钮所对应的用户ID号，lParam（DWORD）指示按钮（左下角）所在屏幕位置(x,y)，用户可以利用该参数显示菜单等
        public const int WM_GV_SDKWARNING       =   WM_GV + 41;	// SDK警告信息，当SDK在运行过程中自检发现异常状态时，将向上层发送该消息，wParam（INT）表示警告代码，定义为：GV_ERR_WARNING_XXXX

        // SDK出错代码定义，其它代码请参考：C++ SDK目录中的GVErrorCodeDefine.h文件
        public const int GV_ERR_SUCCESS			=   0;	        // 成功

        // SDK功能模式参数定义，应用于BRAC_InitSDK API
        public const ulong BRAC_FUNC_VIDEO_CBDATA	=	0x00000001L;    // 通过回调函数输出视频数据
        public const ulong BRAC_FUNC_VIDEO_AUTODISP	=   0x00000002L;    // 由SDK包处理视频，将视频显示在指定的窗口上
        public const ulong BRAC_FUNC_AUDIO_CBDATA	=	0x00000004L;	// 通过回调函数输出音频数据
        public const ulong BRAC_FUNC_AUDIO_AUTOPLAY	=   0x00000008L;    // 由SDK包处理音频，直接播放
        public const ulong BRAC_FUNC_CONFIG_LOCALINI=   0x00000010L;    // 生成本地配置文件（AnyChatSDK.ini）
        public const ulong BRAC_FUNC_FIREWALL_OPEN	=	0x00000020L;	// 允许SDK操作Windows防火墙，将当前应用程序加入防火墙访问列表（避免Windows提示用户是否阻止当前应用程序）
        public const ulong BRAC_FUNC_CHKDEPENDMODULE=   0x00000040L;    // 自动检查SDK所依赖的组件，并自动注册
        public const ulong BRAC_FUNC_AUDIO_VOLUMECALC=	0x00000080L;	// 由SDK自动计算语音的音量
        public const ulong BRAC_FUNC_AUDIO_AUTOVOLUME=	0x00000100L;	// 允许SDK自动控制Mic录音音量
        public const ulong BRAC_FUNC_NET_SUPPORTUPNP=   0x00000200L;    // 允许SDK打开用户网络中的UPNP设备，如果用户的路由器或是防火墙支持UPNP协议，则可提高P2P打洞的成功率
        public const ulong BRAC_FUNC_DISABLEDECODE =    0x00000400L;    // 禁止对收到的数据进行解码和播放，为了提高代理客户端的数据转发性能，可设置该标志，否则不能设置该标志

        // 音频设备枚举定义
        public enum AudioDevice
        {
            BRAC_AD_WAVEIN  = 0,		                        // 输入设备：Mic
            BRAC_AD_WAVEOUT	= 1				                    // 输出设备：Wave
        }

        public enum PixelFormat{
	        BRAC_PIX_FMT_RGB24 = 0,						///< Packed RGB 8:8:8, 24bpp, RGBRGB...（MEDIASUBTYPE_RGB24）
	        BRAC_PIX_FMT_RGB32,							///< 对应于：MEDIASUBTYPE_RGB32，Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
	        BRAC_PIX_FMT_YV12,							///< 对应于：MEDIASUBTYPE_YV12，Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	        BRAC_PIX_FMT_YUY2,							///< 对应于：MEDIASUBTYPE_YUY2，Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
			BRAC_PIX_FMT_YUV420P,						///< Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
			BRAC_PIX_FMT_RGB565,						///< 对应于：MEDIASUBTYPE_RGB565
			BRAC_PIX_FMT_RGB555,						///< 对应于：MEDIASUBTYPE_RGB555
        }
		
		// 视频显示驱动定义
		public enum VideoShowDriver{
			BRAC_VSD_DEFAULT = 0,						///< 默认显示驱动
			BRAC_VSD_DIRECTSHOW,						///< DirectShow显示驱动
			BRAC_VSD_WINDOWSGDI,						///< Windows GDI驱动
		}

        [StructLayout(LayoutKind.Sequential)]          
        //BitmapInfoHeader   定义了位图的头部信息          
        public struct BITMAPINFOHEADER          
        {              
            [MarshalAs(UnmanagedType.I4)]              
            public Int32 biSize;              
            [MarshalAs(UnmanagedType.I4)]              
            public Int32 biWidth;              
            [MarshalAs(UnmanagedType.I4)]              
            public Int32 biHeight;              
            [MarshalAs(UnmanagedType.I2)]              
            public short biPlanes;              
            [MarshalAs(UnmanagedType.I2)]              
            public short biBitCount;              
            [MarshalAs(UnmanagedType.I4)]              
            public Int32 biCompression;              
            [MarshalAs(UnmanagedType.I4)]              
            public Int32 biSizeImage;              
            [MarshalAs(UnmanagedType.I4)]              
            public Int32 biXPelsPerMeter;              
            [MarshalAs(UnmanagedType.I4)]              
            public Int32 biYPelsPerMeter;              
            [MarshalAs(UnmanagedType.I4)]              
            public Int32 biClrUsed;              
            [MarshalAs(UnmanagedType.I4)]              
            public Int32 biClrImportant;          
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct WaveFormat
        {
            public short wFormatTag;
            public short nChannels;
            public uint nSamplesPerSec;
            public uint nAvgBytesPerSec;
            public short nBlockAlign;
            public short wBitsPerSample;
            public short cbSize;
        } 
        #endregion

        #region AnyChat Platform Core SDK 功能函数API接口封装
        /// <summary>
        /// 透明通道数据回调函数定义
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="buf">缓冲区</param>
        /// <param name="len">缓冲区长度</param>
        /// <param name="userValue">附带信息</param>
        public delegate void TransBufferCallBack(int userId, IntPtr buf, int len, int userValue);

        /// <summary>
        /// 透明通道扩展回调函数定义
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="buf">缓冲区</param>
        /// <param name="len">缓冲区长度</param>
        /// <param name="wParam">缓冲区附带信息1</param>
        /// <param name="lParam">缓冲区附带信息2</param>
        /// <param name="taskId">传输任务编号</param>
        /// <param name="userValue">自定义参数</param>
        public delegate void TransBufferCallBackEx(int userId, IntPtr buf, int len,int wParam,int lParam,int taskId, int userValue);

        /// <summary>
        /// 传输文件回调函数定义
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="fileName">文件名</param>
        /// <param name="filePath">文件接收后保存在本地的路径</param>
        /// <param name="fileLength">文件长度</param>
        /// <param name="wParam">附带信息1</param>
        /// <param name="lParam">附带信息2</param>
        /// <param name="taskId">传输任务编号</param>
        /// <param name="userValue">自定义参数</param>
        public delegate void TransFileCallBack(int userId, string fileName, string filePath, int fileLength, int wParam, int lParam, int taskId, int userValue);

        /// <summary>
        /// 音量变化回调函数定义
        /// </summary>
        /// <param name="device">音频设备</param>
        /// <param name="currentVolume">当前音量</param>
        /// <param name="lpUserValue">附带信息</param>
        public delegate void VolumeChangeCallBack(AudioDevice device, int currentVolume, int userValue);

        public delegate void SDKFilterDataCallBack(IntPtr buf,int len,int userValue);

        /// <summary>
        /// 录像回调函数
        /// </summary>
        /// <param name="userId">用户id</param>
        /// <param name="filePath">录像保存路径</param>
        /// <param name="param">参数</param>
        /// <param name="recordType">录像类型,1录像,0拍照</param>
        /// <param name="userValue">用户参数</param>
        public delegate void RecordCallBack(int userId, string filePath, int param, bool recordType,int userValue);

        /// <summary>
        /// 视频回调函数
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="bitMap"></param>
        /// <param name="userValue"></param>
        public delegate void VideoData_CallBack(int userId, IntPtr buf, int len, BITMAPINFOHEADER bitMap, int userValue);

        /// <summary>
        /// 声音回调
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="buf"></param>
        /// <param name="len"></param>
        /// <param name="format"></param>
        /// <param name="userValue"></param>
        public delegate void AudioData_CallBack(int userId,IntPtr buf,int len,WaveFormat format,int userValue);

        /// <summary>
        /// 消息接收回调
        /// </summary>
        /// <param name="fromuserId"></param>
        /// <param name="touserId"></param>
        /// <param name="isserect"></param>
        /// <param name="message"></param>
        /// <param name="len"></param>
        /// <param name="userValue"></param>
        public delegate void TextMessage_CallBack(int fromuserId, int touserId, bool isserect, 
            string message, int len, int userValue);

		/// <summary>
        /// 异步消息通知回调函数定义
        /// </summary>
        /// <param name="dwNotifyMsg"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <param name="userValue"></param>
        public delegate void NotifyMessage_CallBack(int dwNotifyMsg, int wParam, int lParam, int userValue);
		
		/// <summary>
        /// 视频通话消息通知回调函数定义
        /// </summary>
        /// <param name="dwEventType"></param>
        /// <param name="dwUserId"></param>
        /// <param name="dwErrorCode"></param>
		/// <param name="dwFlags"></param>
		/// <param name="dwParam"></param>
		/// <param name="lpUserStr"></param>
        /// <param name="userValue"></param>
        public delegate void VideoCallEvent_CallBack(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, string lpUserStr, int lpUserValue);

			
        /// <summary>
        /// 视频事件注册
        /// </summary>
        /// <param name="format"></param>
        /// <param name="function"></param>
        /// <param name="userValue"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetVideoDataCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetVideoDataCallBack(PixelFormat format, VideoData_CallBack function,int userValue);

        /// <summary>
        /// SDK Filter 注册回调
        /// </summary>
        /// <param name="function"></param>
        /// <param name="userValue"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetSDKFilterDataCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetSDKFilterDataCallBack(SDKFilterDataCallBack function, int userValue);

      
        /// <summary>
        /// 声音事件注册
        /// </summary>
        /// <param name="function"></param>
        /// <param name="userValue"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetAudioDataCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetAudioDataCallBack(AudioData_CallBack function, int userValue);


        /// <summary>
        /// 注册文字消息回调
        /// </summary>
		/// <param name="function"></param>
        /// <param name="userValue"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetTextMessageCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetTextMessageCallBack(TextMessage_CallBack function, int userValue);

		/// <summary>
        /// 注册异步消息通知回调函数
        /// </summary>
		/// <param name="function"></param>
        /// <param name="userValue"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetNotifyMessageCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetNotifyMessageCallBack(NotifyMessage_CallBack function, int userValue);
		
		/// <summary>
        /// 设置视频通话消息通知回调函数
        /// </summary>
		/// <param name="function"></param>
        /// <param name="userValue"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetVideoCallEventCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetVideoCallEventCallBack(VideoCallEvent_CallBack function, int userValue);
		
		
		/// <summary>
        /// 设置服务器验证密码
        /// </summary>
		/// <param name="key"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetServerAuthPass", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetServerAuthPass(StringBuilder key);
		
		
        /// <summary>
        /// 发送消息
        /// </summary>
        /// <param name="userID">－1为所有人</param>
        /// <param name="isSerect">仅用户id 不为－1时有效</param>
        /// <param name="msg">消息内容</param>
        /// <param name="len"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SendTextMessage", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SendTextMessage(int userID,bool isSerect,string msg,int len);
        
        /// <summary>
        /// 获取用户名
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="userName">用户名</param>
        /// <param name="bufLen">缓冲区长度</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetUserName", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetUserName(int userId, StringBuilder userName, int bufLen);

        /// <summary>
        /// 初始化系统
        /// </summary>
        /// <param name="hWnd">接收消息窗口句柄，可为空</param>
        /// <param name="funcMode">功能模式</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_InitSDK", CallingConvention = CallingConvention.Cdecl)]
        public static extern int InitSDK(IntPtr hWnd, ulong funcMode);

        /// <summary>
        /// 设置透明通道数据回调函数
        /// </summary>
        /// <param name="function">回调函数</param>
        /// <param name="userValue">附带信息</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetTransBufferCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetTransBufferCallBack(TransBufferCallBack function, int userValue);

        /// <summary>
        /// 设置透明通道扩展回调函数
        /// </summary>
        /// <param name="function">回调函数</param>
        /// <param name="userValue">附带信息</param>
        /// <returns>0为成功，否则失败</param>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetTransBufferExCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetTransBufferExCallBack(TransBufferCallBackEx function, int userValue);

        /// <summary>
        /// 设置文件传输回调函数
        /// </summary>
        /// <param name="function">回调函数</param>
        /// <param name="userValue">附带信息</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetTransFileCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetTransFileCallBack(TransFileCallBack function, int userValue);

        /// <summary>
        /// 设置音量变化回调函数
        /// </summary>
        /// <param name="function">回调函数</param>
        /// <param name="userValue">附带信息</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetVolumeChangeCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetVolumeChangeCallBack(VolumeChangeCallBack function, int userValue);

        /// <summary>
        /// 设置录像回调函数
        /// </summary>
        /// <param name="function"></param>
        /// <param name="userValue"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetRecordSnapShotCallBack", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetRecordCallBack(RecordCallBack function, int userValue);

        /// <summary>
        /// 连接服务器
        /// </summary>
        /// <param name="serverAddr">服务器地址</param>
        /// <param name="port">端口号</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_Connect", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Connect(string serverAddr, int port);

        /// <summary>
        /// 登录系统
        /// </summary>
        /// <param name="userName">用户名</param>
        /// <param name="password">密码</param>
        /// <param name="passEncType">是否加密</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_Login", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Login(string userName, string password, int passEncType);

        /// <summary>
        /// 进入房间
        /// </summary>
        /// <param name="roomid">房间号</param>
        /// <param name="roomPass">房间密码</param>
        /// <param name="passEncType">是否加密</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_EnterRoom", CallingConvention = CallingConvention.Cdecl)]
        public static extern int EnterRoom(int roomid, string roomPass, int passEncType);

        /// <summary>
        /// 离开房间
        /// </summary>
        /// <param name="roomid">房间号</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_LeaveRoom", CallingConvention = CallingConvention.Cdecl)]
        public static extern int LeaveRoom(int roomid);

        /// <summary>
        /// 注销系统
        /// </summary>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_Logout", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Logout();

        /// <summary>
        /// 释放所有资源
        /// </summary>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_Release", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Release();

        /// <summary>
        /// 获取当前房间在线用户列表
        /// </summary>
        /// <param name="userIDArray">用户列表</param>
        /// <param name="userNum">用户数量</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetOnlineUser", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetOnlineUser(int[] userIDArray, ref int userNum);

        /// <summary>
        /// 查询用户摄像头的状态
        /// </summary>
        /// <param name="userid">用户ID</param>
        /// <param name="state">当前状态，0为没有摄像头，1为有但没打开，2为已打开</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetCameraState", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetCameraState(int userid, ref int state);

        /// <summary>
        /// 查询用户发言状态
        /// </summary>
        /// <param name="userid">用户ID</param>
        /// <param name="state">0为没说话，1为正在说话</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetSpeakState", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetSpeakState(int userid, ref int state);

        /// <summary>
        /// 查询指定用户相关状态（非字符串类型）
        /// </summary>
        /// <param name="userid">用户编号</param>
        /// <param name="infoname">参数名，参考常量定义：BRAC_USERSTATE_XXXX</param>
        /// <param name="infoval">参数地址</param>
        /// <param name="infolen">参数长度</param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_QueryUserState", CallingConvention = CallingConvention.Cdecl)]
        public static extern int QueryUserState(int userid, int infoname, ref int infoval, int infolen);
        // BRAC_API DWORD BRAC_QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);

        /// <summary>
        /// 查询指定用户相关状态（字符串类型）
        /// </summary>
        /// <param name="userid">用户编号</param>
        /// <param name="infoname">参数名，参考常量定义：BRAC_USERSTATE_XXXX</param>
        /// <param name="infoval">参数地址</param>
        /// <param name="infolen">参数长度</param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_QueryUserState", CallingConvention = CallingConvention.Cdecl)]
        public static extern int QueryUserState(int userid, int infoname, StringBuilder infoval, int infolen);
        // BRAC_API DWORD BRAC_QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);

        /// <summary>
        /// 显示本地视频画面调节对话框
        /// </summary>
        /// <param name="parent">父窗体句柄</param>
        /// <param name="caption">窗体标题</param>
        /// <param name="dwX">X位置</param>
        /// <param name="dwY">Y位置</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_ShowLVProperty", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ShowLVProperty(IntPtr parent, string caption, int dwX, int dwY);

        /// <summary>
        /// 操作用户视频
        /// </summary>
        /// <param name="userid">用户ID</param>
        /// <param name="open">是否打开</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_UserCameraControl", CallingConvention = CallingConvention.Cdecl)]
        public static extern int UserCameraControl(int userid, bool open);

        /// <summary>
        /// 操作用户语音
        /// </summary>
        /// <param name="userid">用户ID</param>
        /// <param name="open">是否打开</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_UserSpeakControl", CallingConvention = CallingConvention.Cdecl)]
        public static extern int UserSpeakControl(int userid, bool open);

        /// <summary>
        /// 设置视频显示位置
        /// </summary>
        /// <param name="userid">用户ID</param>
        /// <param name="hWnd">窗口句柄</param>
        /// <param name="left">左位置</param>
        /// <param name="top">上位置</param>
        /// <param name="right">右位置</param>
        /// <param name="bottom">底位置</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetVideoPos", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetVideoPos(int userid, IntPtr hWnd, int left, int top, int right, int bottom);
		
		/// <summary>
		/// 重绘指定用户的视频
		/// </summary>
		/// <param name="userid">用户ID</param>
		/// <param name="hDC">画布句柄，可为NULL</param>
		/// <returns>0为成功，否则失败</returns>
		[DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_RepaintVideo", CallingConvention = CallingConvention.Cdecl)]
        public static extern int RepaintVideo(int userid, IntPtr hDC);
		// BRAC_API DWORD BRAC_RepaintVideo(DWORD dwUserId, HDC hDC);

        /// <summary>
        /// 获取指定音频设备的当前音量
        /// </summary>
        /// <param name="device">音频设备</param>
        /// <param name="volume">音量</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_AudioGetVolume", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AudioGetVolume(AudioDevice device, ref int volume);

        /// <summary>
        /// 设置指定音频设备的音量
        /// </summary>
        /// <param name="device">音频设备</param>
        /// <param name="volume">音量</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_AudioSetVolume", CallingConvention = CallingConvention.Cdecl)]
        public static extern int AudioSetVolume(AudioDevice device, int volume);

        /// <summary>
        /// 利用透明通道传送数据
        /// </summary>
        /// <param name="userid">用户ID</param>
        /// <param name="buf">缓冲区</param>
        /// <param name="len">缓冲区长度</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_TransBuffer", CallingConvention = CallingConvention.Cdecl)]
        public static extern int TransBuffer(int userid, byte[] buf, int len);

        /// <summary>
        /// 利用扩展透明通道传送数据
        /// </summary>
        /// <param name="userid">用户ID</param>
        /// <param name="buf">缓冲区</param>
        /// <param name="len">缓冲区长度</param>
        /// <param name="wParam">附带信息1</param>
        /// <param name="lParam">附带信息2</param>
        /// <param name="flag">特殊标志，默认为0</param>
        /// <param name="taskId">任务ID，添加任务后系统自动生成</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_TransBufferEx", CallingConvention = CallingConvention.Cdecl)]
        public static extern int TransBufferEx(int userid, byte[] buf, int len, int wParam, int lParam, int flag, ref int taskId);

        /// <summary>
        /// SDK Filter 发送数据到服务器端
        /// </summary>
        /// <param name="buf">缓冲区地址</param>
        /// <param name="len">缓冲区长度</param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SendSDKFilterData", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SendSDKFilterData(byte[] buf, int len);
		
        /// <summary>
        /// 传送文件
        /// </summary>
        /// <param name="userid">用户ID</param>
        /// <param name="localFilePath">本地文件路径</param>
        /// <param name="wParam">附带信息1</param>
        /// <param name="lParam">附带信息2</param>
        /// <param name="flag">特殊标志</param>
        /// <param name="taskId">任务ID</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_TransFile", CallingConvention = CallingConvention.Cdecl)]
        public static extern int TransFile(int userid, string localFilePath, int wParam, int lParam, int flag, ref int taskId);

		/// <summary>
        /// 查询传输任务相关信息
        /// </summary>
        /// <returns></returns>
		[DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_QueryTransTaskInfo", CallingConvention = CallingConvention.Cdecl)]
        public static extern int QueryTransTaskInfo(int userid, int taskid, int infoname, StringBuilder infoval, int infolen);
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_QueryTransTaskInfo", CallingConvention = CallingConvention.Cdecl)]
        public static extern int QueryTransTaskInfo(int userid, int taskid, int infoname, ref double infoval, int infolen);
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_QueryTransTaskInfo", CallingConvention = CallingConvention.Cdecl)]
        public static extern int QueryTransTaskInfo(int userid, int taskid, int infoname, ref int infoval, int infolen);
		
		/// <summary>
        /// 取消传输任务
        /// </summary>
		/// <param name="userid">用户ID</param>
        /// <param name="taskId">任务ID</param>
        /// <returns>0为成功，否则失败</returns>
		[DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_CancelTransTask", CallingConvention = CallingConvention.Cdecl)]
        public static extern int CancelTransTask(int userid, int taskid);
		
		
        /// <summary>
        /// 开启或关闭录像
        /// </summary>
        /// <param name="userId">用户id</param>
        /// <param name="startRecord">是否开启录像</param>
        /// <param name="flags">标志,0为录制视频音频</param>
        /// <param name="param">参数</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_StreamRecordCtrl", CallingConvention = CallingConvention.Cdecl)]
        public static extern int StreamRecordCtrl(int userId, bool startRecord, ulong flags, int param);

        /// <summary>
        /// 抓取视频，对指定用户进行拍照
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="flags"></param>
        /// <param name="param"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SnapShot", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SnapShot(int userId, ulong flags, int param);

        /// <summary>
        /// 是否打开SDK日记
        /// </summary>
        /// <param name="isOpen">是否打开</param>
        /// <returns>0为成功，否则失败</returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_ActiveCallLog", CallingConvention = CallingConvention.Cdecl)]
        public static extern int ActiveCallLog(bool isOpen);

        /// <summary>
        /// 设置SDK内核参数（字符串类型）
        /// </summary>
        /// <param name="optName">参数名</param>
        /// <param name="optval">参数值</param>
        /// <param name="optlen">参数长度</param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetSDKOption", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetSDKOption(int optName, string optval, int optlen);

        /// <summary>
        /// 设置SDK内核参数（非字符串类型，INT、BOOL类型）
        /// </summary>
        /// <param name="optName">参数名，参考常量定义：BRAC_SO_XXXX</param>
        /// <param name="optval">参数地址</param>
        /// <param name="optlen">参数长度</param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetSDKOption", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetSDKOption(int optName, ref int optval, int optlen);

        /// <summary>
        /// 获取SDK内核参数
        /// </summary>
        /// <param name="optName">参数名，参考常量定义：BRAC_SO_XXXX</param>
        /// <param name="optval">保存参数值的缓冲区地址</param>
        /// <param name="optlen">参数缓冲区大小</param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetSDKOption", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetSDKOption(int optName, ref int optval, int optlen);

        /// <summary>
        /// 枚举视频设备
        /// </summary>
        /// <param name="deviceName"></param>
        /// <param name="deviceNum"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_EnumVideoCapture", CallingConvention = CallingConvention.Cdecl)]
        public static extern int EnumVideoCapture(IntPtr[] deviceName, ref int deviceNum);

        /// <summary>
        /// 指定特定视频设备
        /// </summary>
        /// <param name="deviceName"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SelectVideoCapture", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SelectVideoCapture(string deviceName);

        /// <summary>
        /// 获取当前视频设备
        /// </summary>
        /// <param name="deviceName"></param>
        /// <param name="length"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetCurVideoCapture", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetCurVideoCapture(StringBuilder deviceName, int length);

        /// <summary>
        /// 枚举音频录音设备
        /// </summary>
        /// <param name="deviceName"></param>
        /// <param name="deviceNum"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_EnumAudioCapture", CallingConvention = CallingConvention.Cdecl)]
        public static extern int EnumAudioCapture(IntPtr[] deviceName, ref int deviceNum);

        /// <summary>
        /// 指定特定音频录音设备
        /// </summary>
        /// <param name="deviceName"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SelectAudioCapture", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SelectAudioCapture(string deviceName);

        /// <summary>
        /// 获取当前音频录音设备
        /// </summary>
        /// <param name="deviceName"></param>
        /// <param name="length"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetCurAudioCapture", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetCurAudioCapture(StringBuilder deviceName, int length);
		
		/// <summary>
        /// 枚举音频播放设备
        /// </summary>
        /// <param name="deviceName"></param>
        /// <param name="deviceNum"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_EnumAudioPlayback", CallingConvention = CallingConvention.Cdecl)]
        public static extern int EnumAudioPlayback(IntPtr[] deviceName, ref int deviceNum);

        /// <summary>
        /// 指定特定音频播放设备
        /// </summary>
        /// <param name="deviceName"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SelectAudioPlayback", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SelectAudioPlayback(string deviceName);

        /// <summary>
        /// 获取当前音频播放设备
        /// </summary>
        /// <param name="deviceName"></param>
        /// <param name="length"></param>
        /// <returns></returns>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetCurAudioPlayback", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetCurAudioPlayback(StringBuilder deviceName, int length);
		
		/// <summary>
        /// 组播功能控制
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_MultiCastControl", CallingConvention = CallingConvention.Cdecl)]
        public static extern int MultiCastControl(string lpMultiCastAddr, int dwPort, string lpNicAddr, int dwTTL, int dwFlags);

		/// <summary>
        /// 设置外部输入视频格式
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetInputVideoFormat", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetInputVideoFormat(PixelFormat pixFmt, int dwWidth, int dwHeight, int dwFps, int dwFlags);
		
		/// <summary>
        /// 外部视频数据输入
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_InputVideoData", CallingConvention = CallingConvention.Cdecl)]
        public static extern int InputVideoData(IntPtr lpVideoFrame, int dwSize, int dwTimeStamp);
		
		/// <summary>
        /// 设置外部输入音频格式
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_SetInputAudioFormat", CallingConvention = CallingConvention.Cdecl)]
        public static extern int SetInputAudioFormat(int dwChannels, int dwSamplesPerSec, int dwBitsPerSample, int dwFlags);
		
		/// <summary>
        /// 外部音频数据输入
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_InputAudioData", CallingConvention = CallingConvention.Cdecl)]
        public static extern int InputAudioData(IntPtr lpSamples, int dwSize, int dwTimeStamp);
		
		/// <summary>
        /// 视频呼叫事件控制（请求、回复、挂断等）
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_VideoCallControl", CallingConvention = CallingConvention.Cdecl)]
        public static extern int VideoCallControl(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, string lpUserStr);
		
		/// <summary>
        /// 获取用户好友ID列表
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetUserFriends", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetUserFriends(int[] lpUserIDArray, ref int dwUserNum);

		/// <summary>
        /// 获取好友在线状态
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetFriendStatus", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetFriendStatus(int dwFriendUserId, ref int dwStatus);

		/// <summary>
        /// 获取用户分组ID列表
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetUserGroups", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetUserGroups(int[] lpGroupIDArray, ref int dwGroupNum);

		/// <summary>
        /// 获取分组下面的好友列表
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetGroupFriends", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetGroupFriends(int dwGroupId, int[] lpUserIDArray, ref int dwUserNum);
		
		/// <summary>
        /// 获取用户信息
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetUserInfo", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetUserInfo(int dwUserId, int dwInfoId, StringBuilder lpInfoValue, int dwLen);
		
		/// <summary>
        /// 获取用户分组名称
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_GetGroupName", CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetGroupName(int dwGroupId, StringBuilder lpGroupName, int dwLen);

		/// <summary>
        /// 用户信息控制
        /// </summary>
        [DllImport(AnyChatCoreSDKDll, EntryPoint = "BRAC_UserInfoControl", CallingConvention = CallingConvention.Cdecl)]
        public static extern int UserInfoControl(int dwUserId, int dwCtrlCode, int wParam, int lParam, string lpStrValue);

        #endregion
    }
}
