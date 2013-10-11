// AnyChat for Web SDK

/********************************************
 *				常量定义部分				*
 *******************************************/

// 音频设备定义（API：BRAC_AudioGetVolume、BRAC_AudioSetVolume 传入参数）
var BRAC_AD_WAVEIN = 						0;	// 输入设备：Mic
var BRAC_AD_WAVEOUT = 						1;	// 输出设备：Wave

// 设备类型定义（API：BRAC_EnumDevices 传入参数）
var BRAC_DEVICE_VIDEOCAPTURE = 				1;	// 视频采集设备
var BRAC_DEVICE_AUDIOCAPTURE = 				2;	// 音频采集设备
var BRAC_DEVICE_AUDIOPLAYBACK = 			3;	// 音频播放设备

// 内核参数定义（API：BRAC_SetSDKOption、BRAC_GetSDKOption 传入参数）
var BRAC_SO_AUDIO_VADCTRL = 				1;	// 音频静音检测控制（参数为：int型：1打开，0关闭）
var BRAC_SO_AUDIO_NSCTRL = 					2;	// 音频噪音抑制控制（参数为：int型：1打开，0关闭）
var BRAC_SO_AUDIO_ECHOCTRL = 				3;	// 音频回音消除控制（参数为：int型：1打开，0关闭）
var BRAC_SO_AUDIO_AGCCTRL = 				4;	// 音频自动增益控制（参数为：int型：1打开，0关闭）
var BRAC_SO_AUDIO_CAPTUREMODE = 			5;	// 音频采集模式设置（参数为：int型：0 发言模式，1 放歌模式，2 卡拉OK模式，3 线路输入模式）
var BRAC_SO_AUDIO_MICBOOST = 				6;	// 音频采集Mic增强控制（参数为：int型：0 取消，1 选中，2 设备不存在[查询时返回值]）
var BRAC_SO_AUDIO_AUTOPARAM = 				7;	// 根据音频采集模式，自动选择合适的相关参数，包括编码器、采样参数、码率参数等（参数为int型：1 启用，0 关闭[默认]）
var BRAC_SO_AUDIO_MONOBITRATE = 			8;	// 设置单声道模式下音频编码目标码率（参数为：int型，单位：bps）
var BRAC_SO_AUDIO_STEREOBITRATE = 			9;	// 设置双声道模式下音频编码目标码率（参数为：int型，单位：bps）
var BRAC_SO_AUDIO_PLAYDRVCTRL = 			70;	// 音频播放驱动选择（参数为：int型，0默认驱动， 1 DSound驱动， 2 WaveOut驱动， 3 Java播放[Android平台使用]）
var BRAC_SO_AUDIO_CNGCTRL = 				71;	// 舒适噪音生成控制（参数为：int型：1打开，0关闭）
var BRAC_SO_AUDIO_CODECID = 				72;	// 本地音频编码器ID设置（参数为int型，-1表示默认，如果设置的编码器ID不存在，则内核会采用默认的编码器）
var BRAC_SO_AUDIO_SOFTVOLMODE = 			73;	// 设置软件音量模式控制（参数为int型，1打开，0关闭[默认]），使用软件音量模式，将不会改变系统的音量设置
var BRAC_SO_AUDIO_RECORDDRVCTRL = 			74;	// 音频采集驱动控制（参数为int型，0默认驱动， 1 DSound驱动， 2 WaveIn驱动， 3 Java采集[Android平台使用]）

var BRAC_SO_RECORD_VIDEOBR = 				10;	// 录像视频码率设置（参数为：int型，单位：bps）
var BRAC_SO_RECORD_AUDIOBR = 				11;	// 录像音频码率设置（参数为：int型，单位：bps）
var BRAC_SO_RECORD_TMPDIR = 				12;	// 录像文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
var BRAC_SO_SNAPSHOT_TMPDIR = 				13;	// 快照文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
var BRAC_SO_CORESDK_TMPDIR = 				14;	// 设置AnyChat Core SDK临时目录（参数为字符串TCHAR类型，必须是完整的绝对路径）
var BRAC_SO_CORESDK_MAGICADJUST = 			15;	// 内核调试参数
var BRAC_SO_CORESDK_LOADCODEC = 			16;	// 加载外部编解码器（参数为字符串TCHAR类型，必须是完整的绝对路径，包含文件名，或包含文件名的绝对路径）
var BRAC_SO_CORESDK_USEARMV6LIB = 			17;	// 强制使用ARMv6指令集的库，android平台使用（参数为：int型，1使用ARMv6指令集， 0内核自动判断[默认]）
var BRAC_SO_CORESDK_USEHWCODEC = 			18;	// 使用平台内置硬件编解码器（参数为int型，0 不使用硬件编解码器[默认]  1 使用内置硬件编解码器）
var BRAC_SO_CORESDK_REMOTEDEBUG = 			19;	// 远程调试（参数为int型，表示目标用户ID，复用参数长度为调试类型参数）

var BRAC_SO_CORESDK_PATH = 					20;	// 设置AnyChat Core SDK相关组件路径（参数为字符串TCHAR类型，必须是完整的绝对路径）
var BRAC_SO_CORESDK_DUMPCOREINFO = 			21;	// 输出内核信息到日志文件中，便于分析故障原因（参数为：int型：1 输出）
var BRAC_SO_CORESDK_MAINVERSION = 			22;	// 查询SDK主版本号号（参数为int型）
var BRAC_SO_CORESDK_SUBVERSION = 			23;	// 查询SDK从版本号（参数为int型）
var BRAC_SO_CORESDK_BUILDTIME = 			24;	// 查询SDK编译时间（参数为字符串TCHAR类型）
var BRAC_SO_CORESDK_ACTIVESTATE = 			25;	// 应用程序活动状态控制（参数为int型， 1 应用程序处于活动状态， 0 应用程序处于非活动状态），适用于iPhone等设备程序可后台运行的场合
var BRAC_SO_CORESDK_EXTVIDEOINPUT = 		26;	// 外部扩展视频输入控制（参数为int型， 0 关闭外部视频输入[默认]， 1 启用外部视频输入）
var BRAC_SO_CORESDK_EXTAUDIOINPUT = 		27;	// 外部扩展音频输入控制（参数为int型， 0 关闭外部音频输入[默认]， 1 启用外部音频输入）
var BRAC_SO_CORESDK_LOWDELAYCTRL = 			28;	// 低延迟模式控制（参数为int型，0 关闭低延迟模式[默认]， 1 启用低延迟模式）

var BRAC_SO_LOCALVIDEO_BITRATECTRL = 		30;	// 本地视频编码码率设置（参数为int型，单位bps，同服务器配置：VideoBitrate）
var BRAC_SO_LOCALVIDEO_QUALITYCTRL = 		31;	// 本地视频编码质量因子控制（参数为int型，同服务器配置：VideoQuality）
var BRAC_SO_LOCALVIDEO_GOPCTRL = 			32;	// 本地视频编码关键帧间隔控制（参数为int型，同服务器配置：VideoGOPSize）
var BRAC_SO_LOCALVIDEO_FPSCTRL = 			33;	// 本地视频编码帧率控制（参数为int型，同服务器配置：VideoFps）
var BRAC_SO_LOCALVIDEO_PRESETCTRL = 		34;	// 本地视频编码预设参数控制（参数为int型，1-5）
var BRAC_SO_LOCALVIDEO_APPLYPARAM = 		35;	// 应用本地视频编码参数，使得前述修改即时生效（参数为int型：1 使用新参数，0 使用默认参数）
var BRAC_SO_LOCALVIDEO_VIDEOSIZEPOLITIC = 	36;	// 本地视频采集分辩率控制策略（参数为int型，0 自动向下逐级匹配[默认]；1 使用采集设备默认分辩率），当配置的分辩率不被采集设备支持时有效
var BRAC_SO_LOCALVIDEO_DEINTERLACE = 		37;	// 本地视频反交织参数控制（参数为int型： 0 不进行反交织处理[默认]；1 反交织处理），当输入视频源是隔行扫描源（如电视信号）时通过反交织处理可以提高画面质量
var BRAC_SO_LOCALVIDEO_WIDTHCTRL = 			38;	// 本地视频采集分辨率宽度控制（参数为int型，同服务器配置：VideoWidth）
var BRAC_SO_LOCALVIDEO_HEIGHTCTRL = 		39;	// 本地视频采集分辨率高度控制（参数为int型，同服务器配置：VideoHeight）
var BRAC_SO_LOCALVIDEO_FOCUSCTRL = 			90;	// 本地视频摄像头对焦控制（参数为int型，1表示自动对焦， 0表示手动对焦）
var BRAC_SO_LOCALVIDEO_PIXFMTCTRL = 		91;	// 本地视频采集优先格式控制（参数为int型，-1表示智能匹配，否则优先采用指定格式，参考：BRAC_PixelFormat）
var BRAC_SO_LOCALVIDEO_OVERLAY = 			92;	// 本地视频采用Overlay模式（参数为int型，1表示采用Overlay模式， 0表示普通模式[默认]）
var BRAC_SO_LOCALVIDEO_CODECID = 			93;	// 本地视频编码器ID设置（参数为int型，-1表示默认，如果设置的编码器ID不存在，则内核会采用默认的编码器）
var BRAC_SO_LOCALVIDEO_ROTATECTRL = 		94;	// 本地视频旋转控制（参数为int型，0表示不进行旋转，1表示垂直翻转）
var BRAC_SO_LOCALVIDEO_CAPDRIVER = 			95;	// 本地视频采集驱动设置（参数为int型，0表示自动选择[默认]， 1 Video4Linux, 2 DirectShow, 3 Java采集[Android平台使用]）
var BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA = 		96;	// 修正视频采集颜色偏色（参数为int型，0表示关闭[默认]，1 开启）

var BRAC_SO_NETWORK_P2PPOLITIC = 			40;	// 本地网络P2P策略控制（参数为：int型：0 禁止本地P2P，1 服务器控制P2P[默认]，2 上层应用控制P2P连接，3 按需建立P2P连接）
var BRAC_SO_NETWORK_P2PCONNECT = 			41;	// 尝试与指定用户建立P2P连接（参数为int型，表示目标用户ID），连接建立成功后，会通过消息反馈给上层应用，P2P控制策略=2时有效
var BRAC_SO_NETWORK_P2PBREAK = 				42;	// 断开与指定用户的P2P连接（参数为int型，表示目标用户ID）[暂不支持，保留]
var BRAC_SO_NETWORK_TCPSERVICEPORT = 		43;	// 设置本地TCP服务端口（参数为int型），连接服务器之前设置有效
var BRAC_SO_NETWORK_UDPSERVICEPORT = 		44;	// 设置本地UDP服务端口（参数为int型），连接服务器之前设置有效
var BRAC_SO_NETWORK_MULTICASTPOLITIC = 		45;	// 组播策略控制（参数为int型：0 执行服务器路由策略，禁止组播发送[默认]， 1 忽略服务器路由策略，只向组播组广播媒体流， 2 执行服务器路由策略，同时组播）
var BRAC_SO_NETWORK_TRANSBUFMAXBITRATE = 	46;	// 传输缓冲区、文件最大码率控制（参数为int型，0 不限制，以最快速率传输[默认]， 否则表示限制码率，单位为：bps）

var BRAC_SO_PROXY_FUNCTIONCTRL = 			50;	// 本地用户代理功能控制，（参数为：int型，1启动代理，0关闭代理[默认]）
var BRAC_SO_PROXY_VIDEOCTRL = 				51;	// 本地用户代理视频控制，将本地视频变为指定用户的视频对外发布（参数为int型，表示其它用户的userid）
var BRAC_SO_PROXY_AUDIOCTRL = 				52;	// 本地用户代理音频控制，将本地音频变为指定用户的音频对外发布（参数同BRAC_SO_PROXY_VIDEOCTRL）

var BRAC_SO_STREAM_MAXBUFFERTIME = 			60;	// 最大流缓冲时间（参数为int型，单位：毫秒，取值范围：500 ~ 5000，默认：800），发言模式设置值，歌曲模式会自动增加一倍
var BRAC_SO_STREAM_SMOOTHPLAYMODE = 		61;	// 平滑播放模式（参数为int型，0 关闭[默认], 1 打开），打开状态下遇到视频丢帧时会继续播放（可能出现马赛克），不会卡住

var BRAC_SO_VIDEOSHOW_MODECTRL = 			80;	// 视频显示模式控制（参数为：int型，0 单画面显示，1 视频迭加显示）
var BRAC_SO_VIDEOSHOW_SETPRIMARYUSER = 		81;	// 设置主显示用户编号（参数为：int型，用户ID号）
var BRAC_SO_VIDEOSHOW_SETOVERLAYUSER = 		82;	// 设置迭加显示用户编号（参数为：int型，用户ID号）
var BRAC_SO_VIDEOSHOW_DRIVERCTRL = 			83;	// 视频显示驱动控制（参数为：int型，0 默认驱动， 1 Windows DirectShow，2 Windows GDI，3 SDL, 4 Android2X）


// 传输任务信息参数定义（API：BRAC_QueryTransTaskInfo 传入参数）
var BRAC_TRANSTASK_PROGRESS = 				1;	// 传输任务进度查询（参数为：DOUBLE型，返回值0.0 ~ 100.0， 或参数为：DWORD型，返回值0 ~ 100）
var BRAC_TRANSTASK_BITRATE = 				2;	// 传输任务当前传输码率（参数为：int型，单位：bps）
var BRAC_TRANSTASK_STATUS = 				3;	// 传输任务当前状态（参数为：int型）
var BRAC_TRANSTASK_SAVEASPATH = 			4;	// 文件传输任务另存为路径设置，含文件名（参数为字符串TCHAR类型）

// 录像功能标志定义（API：BRAC_StreamRecordCtrl 传入参数）
var BRAC_RECORD_FLAGS_VIDEO	=				1;	// 录制视频
var BRAC_RECORD_FLAGS_AUDIO	=				2;	// 录制音频
var BRAC_RECORD_FLAGS_SERVER =				4;	// 服务器端录制


// 用户状态标志定义（API：BRAC_QueryUserState 传入参数）
var BRAC_USERSTATE_CAMERA = 				1;	// 用户摄像头状态（参数为DWORD型）
var BRAC_USERSTATE_HOLDMIC = 				2;	// 用户音频设备状态（参数为DWORD型，返回值：0 音频采集关闭， 1 音频采集开启）
var BRAC_USERSTATE_SPEAKVOLUME = 			3;	// 用户当前说话音量（参数为DOUBLE类型（0.0 ~ 100.0））
var BRAC_USERSTATE_RECORDING = 				4;	// 用户录像（音）状态（参数为DWORD型）
var	BRAC_USERSTATE_LEVEL = 					5;	// 用户级别（参数为DWORD型）
var BRAC_USERSTATE_NICKNAME = 				6;	// 用户昵称（参数为字符串TCHAR类型）
var BRAC_USERSTATE_LOCALIP = 				7;	// 用户本地IP地址（内网，参数为字符串TCHAR类型）
var BRAC_USERSTATE_INTERNETIP = 			8;	// 用户互联网IP地址（参数为字符串TCHAR类型）
var BRAC_USERSTATE_VIDEOBITRATE = 			9;	// 用户当前的视频码率（参数为DWORD类型，Bps）
var BRAC_USERSTATE_AUDIOBITRATE = 			10;	// 用户当前的音频码率（参数为DWORD类型，Bps）
var BRAC_USERSTATE_P2PCONNECT = 			11;	// 查询本地用户与指定用户的当前P2P连接状态（参数为DWORD类型，返回值：0 P2P不通， 1 P2P连接成功[TCP]，2 P2P连接成功[UDP]，3 P2P连接成功[TCP、UDP]）
var BRAC_USERSTATE_NETWORKSTATUS = 			12;	// 查询指定用户的网络状态（参数为DWORD类型，返回值：0 优良，1 较好，2 一般，3 较差，4 非常差），注：查询间隔需要>1s
var BRAC_USERSTATE_VIDEOSIZE = 				13;	// 查询指定用户的视频分辨率（参数为DWORD类型，返回值：低16位表示宽度，高16位表示高度）
var BRAC_USERSTATE_PACKLOSSRATE = 			14;	// 查询指定用户的网络流媒体数据丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）
var BRAC_USERSTATE_DEVICETYPE =				15; // 查询指定用户的终端类型（参数为DWORD类型，返回值：0 Unknow， 1 Windows，2 Android，3 iOS，4 Web，5 Linux，6 Mac，7 Win Phone，8 WinCE）

// SDK消息定义（用于OnNotifyMessage事件中判断事件的类型）
var WM_GV = 0x0400 + 200;
var WM_GV_CONNECT			=	WM_GV + 1;		// 客户端连接服务器，wParam（BOOL）表示是否连接成功
var WM_GV_LOGINSYSTEM		=	WM_GV + 2;		// 客户端登录系统，wParam（INT）表示自己的用户ID号，lParam（INT）表示登录结果：0 成功，否则为出错代码，参考出错代码定义
var WM_GV_ENTERROOM			=	WM_GV + 3;		// 客户端进入房间，wParam（INT）表示所进入房间的ID号，lParam（INT）表示是否进入房间：0成功进入，否则为出错代码
var WM_GV_MICSTATECHANGE	=	WM_GV + 4;		// 用户的音频设备状态变化消息，wParam（INT）表示用户ID号，lParam（BOOL）表示该用户是否已打开音频采集设备
var WM_GV_USERATROOM		=	WM_GV + 5;		// 用户进入（离开）房间，wParam（INT）表示用户ID号，lParam（BOOL）表示该用户是进入（TRUE）或离开（FALSE）房间
var WM_GV_LINKCLOSE			=	WM_GV + 6;		// 网络连接已关闭，该消息只有在客户端连接服务器成功之后，网络异常中断之时触发，wParam（INT）表示连接断开的原因
var WM_GV_ONLINEUSER		=	WM_GV + 7;		// 收到当前房间的在线用户信息，进入房间后触发一次，wParam（INT）表示在线用户数（包含自己），lParam（INT）表示房间ID
var WM_GV_CAMERASTATE		=	WM_GV + 11;		// 用户摄像头状态发生变化，wParam（INT）表示用户ID号，lParam（INT）表示摄像头的当前状态，定义为：GV_CAMERA_STATE_XXXX
var WM_GV_CHATMODECHG		=	WM_GV + 12;		// 用户聊天模式发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的当前聊天模式
var WM_GV_ACTIVESTATE		=	WM_GV + 13;		// 用户活动状态发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的当前活动状态
var WM_GV_P2PCONNECTSTATE	=	WM_GV + 14;		// 本地用户与其它用户的P2P网络连接状态发生变化，wParam（INT）表示其它用户ID号，lParam（INT）表示本地用户与其它用户的当前P2P网络连接状态
var WM_GV_PRIVATEREQUEST	=	WM_GV + 21;		// 用户发起私聊请求，wParam（INT）表示发起者的用户ID号，lParam（INT）表示私聊请求编号，标识该请求
var WM_GV_PRIVATEECHO		=	WM_GV + 22;		// 用户回复私聊请求，wParam（INT）表示回复者的用户ID号，lParam（INT）为出错代码
var WM_GV_PRIVATEEXIT		=	WM_GV + 23;		// 用户退出私聊，wParam（INT）表示退出者的用户ID号，lParam（INT）为出错代码
var WM_GV_SDKWARNING      	=   WM_GV + 41;		// SDK警告信息，当SDK在运行过程中自检发现异常状态时，将向上层发送该消息，wParam（INT）表示警告代码，定义为：GV_ERR_WARNING_XXXX
var WM_GV_USERINFOUPDATE	=	WM_GV + 16;		// 用户信息更新通知，wParam（INT）表示用户ID号，lParam（INT）表示更新类别
var WM_GV_FRIENDSTATUS		=	WM_GV + 17;		// 好友在线状态变化，wParam（INT）表示好友用户ID号，lParam（INT）表示用户的当前活动状态：0 离线， 1 上线

// 视频呼叫事件类型定义（API：BRAC_VideoCallControl 传入参数、VideoCallEvent回调参数）
var BRAC_VIDEOCALL_EVENT_REQUEST =			1;	// 呼叫请求
var BRAC_VIDEOCALL_EVENT_REPLY =			2;	// 呼叫请求回复
var BRAC_VIDEOCALL_EVENT_START =			3;	// 视频呼叫会话开始事件
var BRAC_VIDEOCALL_EVENT_FINISH =			4;	// 挂断（结束）呼叫会话

// 视频呼叫标志定义（API：BRAC_VideoCallControl 传入参数）
var BRAC_VIDEOCALL_FLAGS_AUDIO =			1;	// 语音通话
var BRAC_VIDEOCALL_FLAGS_VIDEO =			2;	// 视频通话
var BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO =		16;	// 禁止源（呼叫端）音频
var BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO =		32;	// 禁止源（呼叫端）视频
var BRAC_VIDEOCALL_FLAGS_FBTARAUDIO =		64;	// 禁止目标（被呼叫端）音频
var BRAC_VIDEOCALL_FLAGS_FBTARVIDEO	=		128;// 禁止目标（被呼叫端）视频

// 出错代码定义
var GV_ERR_SUCCESS			=	0;				// 成功
var GV_ERR_PLUGINNOINSTALL	=	1010000;		// 插件没有安装
var GV_ERR_PLUGINOLDVERSION =	1010001;		// 插件版本太低


// 插件最低需求版本号
var MIN_ANYCHAT_PLUGIN_VER	=	"1.0.0.6";
var MIN_VIDEO_PLUGIN_VER	=	"1.0.0.2";

/********************************************
 *				方法定义部分				*
 *******************************************/
var anychat;									// AnyChat插件DMO对象，外部初始化

// 初始化SDK，返回出错代码
function BRAC_InitSDK(apilevel) {
	var anychatsdkdiv = "AnyChatSDKPluginDiv";
	try {
		// 创建AnyChat SDK插件
		var anychatobj = document.createElement("object")
	    anychatobj.id = "AnyChatSDKPlugin";
		anychatobj.width = "1 px";
		anychatobj.height = "1 px";
	    if (window.ActiveXObject)
	        anychatobj.classid = "clsid:91CC58C4-BA8A-400D-A176-856EDF42CB57";
	    else
	        anychatobj.type = "application/anychat-plugin";
	    // 创建视频显示插件
	    var videoobj = document.createElement("object")
	    videoobj.id = "AnyChatVideoPlugin";
	    if (window.ActiveXObject)
	        videoobj.classid = "clsid:B685A393-905F-45B5-B26E-FF199EEE2FD7";
	    else
	        videoobj.type = "application/anychat-video";
	    // 创建一个测试层
	    var insertdiv = document.createElement("div");
	    insertdiv.id = anychatsdkdiv;
		insertdiv.appendChild(anychatobj);
	    insertdiv.appendChild(videoobj);
	    document.body.appendChild(insertdiv);
	    // 测试插件是否安装
	    var anychatpluginver = anychatobj.GetVersion(0);
	    var videopluginver = videoobj.GetVersion(0);
	    // 判断插件的版本是否太旧
	    var bRightVersion = ((anychatpluginver >= MIN_ANYCHAT_PLUGIN_VER) && (videopluginver >= MIN_VIDEO_PLUGIN_VER));
		// 判断当前的API Level是否满足业务层的需要
		if(apilevel > anychatobj.GetVersion(2))
			bRightVersion = false;
		if(bRightVersion) {
			insertdiv.removeChild(videoobj);
			anychat = anychatobj;
			// 关联回调事件
			if(window.ActiveXObject) {
				anychat.attachEvent('OnNotifyMessage', OnAnyChatNotifyMessage);
				anychat.attachEvent('OnTextMessage', OnAnyChatTextMessage);
				anychat.attachEvent('OnTransBuffer', OnAnyChatTransBuffer);
				anychat.attachEvent('OnTransBufferEx', OnAnyChatTransBufferEx);
				anychat.attachEvent('OnTransFile', OnAnyChatTransFile);
				anychat.attachEvent('OnVolumeChange', OnAnyChatVolumeChange);
				anychat.attachEvent('OnSDKFilterData', OnAnyChatSDKFilterData);
				anychat.attachEvent('OnRecordSnapShot', OnAnyChatRecordSnapShot);
				anychat.attachEvent('OnVideoCallEvent', OnAnyChatVideoCallEvent);
			} else {
				anychat.OnNotifyMessage = OnAnyChatNotifyMessage;
				anychat.OnTextMessage = OnAnyChatTextMessage;
				anychat.OnTransBuffer = OnAnyChatTransBuffer;
				anychat.OnTransBufferEx = OnAnyChatTransBufferEx;
				anychat.OnTransFile = OnAnyChatTransFile;
				anychat.OnVolumeChange = OnAnyChatVolumeChange;
				anychat.OnSDKFilterData = OnAnyChatSDKFilterData;
				anychat.OnRecordSnapShot = OnAnyChatRecordSnapShot;
				anychat.OnVideoCallEvent = OnAnyChatVideoCallEvent;
			}
		} else {
			document.body.removeChild(insertdiv);
		}
		return bRightVersion ? GV_ERR_SUCCESS : GV_ERR_PLUGINOLDVERSION;
	}
	catch (e) {
	    var insertdiv = BRAC_GetDmoObject(anychatsdkdiv);
	    if (insertdiv)
	        document.body.removeChild(insertdiv);
	    return GV_ERR_PLUGINNOINSTALL;
	}
}

// 获取Web DMO对象
function BRAC_GetDmoObject(id) {
	if (document.getElementById) {
		return document.getElementById(id);
	} else if (window[id]) {
		return window[id];
	}
	return null;
}

// 设置视频显示位置
function BRAC_SetVideoPos(userid, parentobj, id) {
	var videoobj = BRAC_GetDmoObject(id);
	if(videoobj != null) {
		videoobj.SetIPCGuid(BRAC_GetIPCGuid());
		videoobj.SetUserId(userid);
	} else {
		// 创建视频显示插件
	    videoobj = document.createElement("object")
	    videoobj.id = id;
		videoobj.width = "100%";
		videoobj.height = "100%";
	    if (window.ActiveXObject)
	        videoobj.classid = "clsid:B685A393-905F-45B5-B26E-FF199EEE2FD7";
	    else
	        videoobj.type = "application/anychat-video";
		parentobj.appendChild(videoobj);
		// 关联到AnyChat SDK
		videoobj.SetIPCGuid(BRAC_GetIPCGuid());
		videoobj.SetUserId(userid);
	}	
}

// 获取版本号
function BRAC_GetVersion(type) {
	return anychat.GetVersion(type);
}

// 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
function BRAC_SetServerAuthPass(lpPassword) {
	return anychat.SetServerAuthPass(lpPassword);
}

// 连接服务器
function BRAC_Connect(lpServerAddr, dwPort) {
	return anychat.Connect(lpServerAddr, dwPort);
}
// 登录系统
function BRAC_Login(lpUserName, lpPassword, dwParam) {
	return anychat.Login(lpUserName, lpPassword, dwParam);
}
// 进入房间
function BRAC_EnterRoom(dwRoomid, lpRoomPass, dwParam) {
	return anychat.EnterRoom(dwRoomid, lpRoomPass, dwParam);
}
// 进入房间
function BRAC_EnterRoomEx(lpRoomName, lpRoomPass) {
	return anychat.EnterRoomEx(lpRoomName, lpRoomPass);
}
// 离开房间
function BRAC_LeaveRoom(dwRoomid) {
	return anychat.LeaveRoom(dwRoomid);
}
// 注销系统
function BRAC_Logout() {
	return anychat.Logout();
}

// 获取当前房间在线用户列表（返回一个userid的数组）
function BRAC_GetOnlineUser() {
	var idarray = new Array();
	var size = anychat.PrepareFetchRoomUsers();
	if(size)
	{
		var idx = 0;
		while(1)
		{
			var userid = anychat.FetchNextRoomUsers();
			if(userid == -1)
				break;
			idarray[idx++] = userid;
		}
	}
	return idarray;
}
// 查询用户摄像头的状态
function BRAC_GetCameraState(dwUserId) {
	return anychat.QueryUserStateInt(dwUserId, BRAC_USERSTATE_CAMERA);
}
// 查询用户发言状态
function BRAC_GetSpeakState(dwUserId) {
	return anychat.QueryUserStateInt(dwUserId, BRAC_USERSTATE_HOLDMIC);
}
// 查询用户级别
function BRAC_GetUserLevel(dwUserId) {
	return anychat.QueryUserStateInt(dwUserId, BRAC_USERSTATE_LEVEL);
}
// 查询用户名称
function BRAC_GetUserName(dwUserId) {
	return anychat.QueryUserStateString(dwUserId, BRAC_USERSTATE_NICKNAME);
}
// 查询指定用户相关状态（整型值状态）
function BRAC_QueryUserStateInt(dwUserId, infoname) {
	return anychat.QueryUserStateInt(dwUserId, infoname);
}
// 查询指定用户相关状态（字符串值状态）
function BRAC_QueryUserStateString(dwUserId, infoname) {
	return anychat.QueryUserStateString(dwUserId, infoname);
}

// 显示本地视频画面调节对话框
function BRAC_ShowLVProperty(szCaption) {
	return anychat.ShowLVProperty(szCaption);
}

// 枚举本地设备信息（返回设备名称数组）
function BRAC_EnumDevices(dwDeviceType) {
	var devicearray = new Array();
	var size = anychat.PrepareFetchDevices(dwDeviceType);
	for(var i=0; i<size; i++) {
		devicearray[i] = anychat.FetchNextDevice(dwDeviceType);
	}
	return devicearray;
}
// 选择指定的设备
function BRAC_SelectVideoCapture(dwDeviceType, szCaptureName) {
	return anychat.SelectDevice(dwDeviceType, szCaptureName);
}
// 获取当前使用的设备
function BRAC_GetCurrentDevice(dwDeviceType) {
	return anychat.GetCurrentDevice(dwDeviceType);
}

// 操作本地用户视频（或请求远程用户视频）
function BRAC_UserCameraControl(dwUserId, bOpen) {
	return anychat.UserCameraControl(dwUserId, bOpen);
}
// 操作本地用户语音（或请求远程用户语音）
function BRAC_UserSpeakControl(dwUserId, bOpen) {
	return anychat.UserSpeakControl(dwUserId, bOpen);
}

// 获取指定音频设备的当前音量
function BRAC_AudioGetVolume(device) {
	return anychat.AudioGetVolume(device);
}
// 设置指定音频设备的音量
function BRAC_AudioSetVolume(device, dwVolume) {
	return anychat.AudioSetVolume(device, dwVolume);
}

// 用户音、视频录制
function BRAC_StreamRecordCtrl(dwUserId, bStartRecord, dwFlags, dwParam) {
	return anychat.StreamRecordCtrl(dwUserId, bStartRecord, dwFlags, dwParam);
}
// 对用户的视频进行抓拍（快照）
function BRAC_SnapShot(dwUserId, dwFlags, dwParam) {
	return anychat.SnapShot(dwUserId, dwFlags, dwParam);
}

// 透明通道传送缓冲区
function BRAC_TransBuffer(dwUserId, lpBuf) {
	return anychat.TransBuffer(dwUserId, lpBuf, 0);
}
// 透明通道传送缓冲区扩展
function BRAC_TransBufferEx(dwUserId, lpBuf, wParam, lParam, dwFlags) {
	return anychat.TransBufferEx(dwUserId, lpBuf, 0, wParam, lParam, dwFlags);
}
// 传送文件
function BRAC_TransFile(dwUserId, lpLocalPathName, wParam, lParam, dwFlags) {
	return anychat.TransFile(dwUserId, lpLocalPathName, wParam, lParam, dwFlags);
}
// 查询传输任务相关信息
function BRAC_QueryTransTaskInfo(dwUserId, dwTaskId, infoname) {
	return anychat.QueryTransTaskInfo(dwUserId, dwTaskId, infoname);
}
// 取消传输任务
function BRAC_CancelTransTask(dwUserId, dwTaskId) {
	return anychat.CancelTransTask(dwUserId, dwTaskId);
}
// 传送文本消息
function BRAC_SendTextMessage(dwUserId, bSecret, lpMsgBuf) {
	return anychat.SendTextMessage(dwUserId, bSecret, lpMsgBuf, 0);
}
// 发送SDK Filter 通信数据
function BRAC_SendSDKFilterData(lpBuf) {
	return anychat.SendSDKFilterData(lpBuf, 0);
}

// 更改当前的聊天模式
function BRAC_ChangeChatMode(dwChatMode) {
	return anychat.ChangeChatMode(dwChatMode);
}
// 获取指定用户当前的聊天模式
function BRAC_GetUserChatMode(dwUserId) {
	return anychat.GetUserChatMode(dwUserId);
}
// 请求与对方私聊，向对方发起私聊请求
function BRAC_PrivateChatRequest(dwUserId) {
	return anychat.PrivateChatRequest(dwUserId);
}
// 回复对方的私聊请求
function BRAC_PrivateChatEcho(dwUserId, dwRequestId, bAccept) {
	return anychat.PrivateChatEcho(dwUserId, dwRequestId, bAccept);
}
// 回复对方的私聊请求（扩展，可以附带出错代码）
function BRAC_PrivateChatEchoEx(dwUserId, dwRequestId, dwErrorCode) {
	return anychat.PrivateChatEchoEx(dwUserId, dwRequestId, dwErrorCode);
}
// 退出与某用户的私聊，或者将某用户从自己的私聊列表中清除
function BRAC_PrivateChatExit(dwUserId) {
	return anychat.PrivateChatExit(dwUserId);
}

// SDK内核参数设置
function BRAC_SetSDKOption(optname, value) {
	if(isNaN(value))
		return anychat.SetSDKOptionString(optname, value);
	else
		return anychat.SetSDKOptionInt(optname, value);
}
// SDK内核参数状态查询（整形参数值）
function BRAC_GetSDKOptionInt(optname) {
	return anychat.GetSDKOptionInt(optname);
}
// SDK内核参数状态查询（字符串参数值）
function BRAC_GetSDKOptionString(optname) {
	return anychat.GetSDKOptionString(optname);
}

// 获取内部通信句柄
function BRAC_GetIPCGuid() {
	var ANYCHATWEB_SO_IPCGUID = 11000; 
	return anychat.GetSDKOptionString(ANYCHATWEB_SO_IPCGUID);
}

// 组播功能控制
function BRAC_MultiCastControl(lpMultiCastAddr, dwPort, lpNicAddr, dwTTL, dwFlags) {
	return anychat.MultiCastControl(lpMultiCastAddr, dwPort, lpNicAddr, dwTTL, dwFlags);
}

// 视频呼叫事件控制（请求、回复、挂断等）
function BRAC_VideoCallControl(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr) {
	return anychat.VideoCallControl(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr);
}

// 获取用户好友ID列表（返回一个userid的数组）
function BRAC_GetUserFriends() {
	var idarray = new Array();
	var size = anychat.PrepareFetchUserFriends();
	if(size) {
		var idx = 0;
		while(1) {
			var userid = anychat.FetchNextUserFriend();
			if(userid == -1)
				break;
			idarray[idx++] = userid;
		}
	}
	return idarray;
}

// 获取好友在线状态
function BRAC_GetFriendStatus(dwFriendUserId) {
	return anychat.GetFriendStatus(dwFriendUserId);
}

// 获取用户分组ID列表（返回一个GroupId的数组）
function BRAC_GetUserGroups() {
	var idarray = new Array();
	var size = anychat.PrepareFetchUserGroups();
	if(size) {
		var idx = 0;
		while(1) {
			var groupid = anychat.FetchNextUserGroup();
			if(groupid == -1)
				break;
			idarray[idx++] = groupid;
		}
	}
	return idarray;
}

// 获取分组下面的好友列表（返回一个userid的数组）
function BRAC_GetGroupFriends(dwGroupId) {
	var idarray = new Array();
	var size = anychat.PrepareFetchGroupFriends(dwGroupId);
	if(size) {
		var idx = 0;
		while(1) {
			var userid = anychat.FetchNextGroupFriend(dwGroupId);
			if(userid == -1)
				break;
			idarray[idx++] = userid;
		}
	}
	return idarray;
}

// 获取用户信息
function BRAC_GetUserInfo(dwUserId, dwInfoId) {
	return anychat.GetUserInfo(dwUserId, dwInfoId);
}

// 获取用户分组名称
function BRAC_GetGroupName(dwGroupId) {
	return anychat.GetGroupName(dwGroupId);
}

// 用户信息控制
function BRAC_UserInfoControl(dwUserId, dwCtrlCode, wParam, lParam, lpStrValue) {
	return anychat.UserInfoControl(dwUserId, dwCtrlCode, wParam, lParam, lpStrValue);
}





