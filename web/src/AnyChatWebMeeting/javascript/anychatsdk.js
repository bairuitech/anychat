// AnyChat for Web SDK
// 不要对该文件进行任何修改，当升级SDK时，新版本将会直接覆盖旧版本


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
var BRAC_SO_AUDIO_ECHODELAY	=				75;	// 音频回声消除延迟参数设置（参数为int型，单位：ms）
var BRAC_SO_AUDIO_NSLEVEL	=				76;	// 音频噪音抑制水平参数设置（参数为int型，0 - 3，默认为2，值越大抑制水平越高，抑制噪音的能力越强）
var BRAC_SO_AUDIO_CBCODEC	=				77;	// 音频数据回调编码器类型（参数为int型）
var BRAC_SO_AUDIO_ECHOLEVEL	=				78;	// 音频回声消除水平参数设置（参数为int型，0 - 4，默认为4，值越大回声消除能力越强）
var BRAC_SO_AUDIO_PLAYCAPTURE	=			79;	// 音频播放采集参数设置（参数为int型，0 关闭[默认]，1 开启）


var BRAC_SO_RECORD_VIDEOBR = 				10;	// 录像视频码率设置（参数为：int型，单位：bps）
var BRAC_SO_RECORD_AUDIOBR = 				11;	// 录像音频码率设置（参数为：int型，单位：bps）
var BRAC_SO_RECORD_TMPDIR = 				12;	// 录像文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
var BRAC_SO_SNAPSHOT_TMPDIR = 				13;	// 快照文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
var BRAC_SO_RECORD_FILETYPE	=				140;// 录制文件类型设置（参数为：int型， 0 MP4[默认], 1 WMV, 2 FLV, 3 MP3）
var BRAC_SO_RECORD_WIDTH	=				141;// 录制视频宽度设置（参数为：int型，如：320）
var BRAC_SO_RECORD_HEIGHT	=				142;// 录制文件高度设置（参数为：int型，如：240）
var BRAC_SO_RECORD_FILENAMERULE	=			143;// 录制文件名命名规则（参数为：int型）
var BRAC_SO_RECORD_CLIPMODE	=				144;// 录制视频裁剪模式（参数为：int型）
var BRAC_SO_RECORD_DISABLEDATEDIR =			145;// 录制文件不按日期分目录保存，全部生成在指定文件夹中（参数为：int型， 0禁止[默认] 1 开启）
var BRAC_SO_RECORD_INSERTIMAGE	=			146;// 录制过程中插入图片，Json字符串参数

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
var BRAC_SO_CORESDK_NEWGUID	=				29;	// 产生新的GUID字符串

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
var BRAC_SO_LOCALVIDEO_TVFORMAT	=			104;// 视频采集制式设置（参数为：int型，定义为DirectShow::strmif.h::AnalogVideoStandard，默认为：AnalogVideo_PAL_B）
var BRAC_SO_LOCALVIDEO_OVERLAYTIMESTAMP	=	105;// 迭加时间戳到本地视频（参数为：int型， 0 不迭加[默认]， 1 迭加）
var BRAC_SO_LOCALVIDEO_DEVICENAME =			106;// 本地视频采集设备名称，用于设置打开指定摄像头设备（参数为字符串类型）
var BRAC_SO_LOCALVIDEO_CLIPMODE	=			107;// 本地视频裁剪模式（参数为int型， 0 自动[默认]，禁止自动旋转时有效）
var BRAC_SO_LOCALVIDEO_SCREENHWND	=		108;// 屏幕采集窗口句柄
var BRAC_SO_LOCALVIDEO_SCREENFLAGS	=		109;// 屏幕采集标志（参数为int型）
var BRAC_SO_LOCALVIDEO_VIRTUALBK	=		111;// 本地视频迭加虚拟背景（字符串类型，JSON格式，包括虚拟背景路径、是否开启以及其它参数项）
var BRAC_SO_LOCALVIDEO_VIDEOCOLOR	=		112;// 视频颜色控制（字符串类型，参数为JSON）

var BRAC_SO_NETWORK_P2PPOLITIC = 			40;	// 本地网络P2P策略控制（参数为：int型：0 禁止本地P2P，1 服务器控制P2P[默认]，2 上层应用控制P2P连接，3 按需建立P2P连接）
var BRAC_SO_NETWORK_P2PCONNECT = 			41;	// 尝试与指定用户建立P2P连接（参数为int型，表示目标用户ID），连接建立成功后，会通过消息反馈给上层应用，P2P控制策略=2时有效
var BRAC_SO_NETWORK_P2PBREAK = 				42;	// 断开与指定用户的P2P连接（参数为int型，表示目标用户ID）[暂不支持，保留]
var BRAC_SO_NETWORK_TCPSERVICEPORT = 		43;	// 设置本地TCP服务端口（参数为int型），连接服务器之前设置有效
var BRAC_SO_NETWORK_UDPSERVICEPORT = 		44;	// 设置本地UDP服务端口（参数为int型），连接服务器之前设置有效
var BRAC_SO_NETWORK_MULTICASTPOLITIC = 		45;	// 组播策略控制（参数为int型，定义为常量：BRAC_MCPOLITIC_XXXX）
var BRAC_SO_NETWORK_TRANSBUFMAXBITRATE = 	46;	// 传输缓冲区、文件最大码率控制（参数为int型，0 不限制，以最快速率传输[默认]， 否则表示限制码率，单位为：bps）
var BRAC_SO_NETWORK_AUTORECONNECT	=		47;	// 网络掉线自动重连功能控制（参数为int型，0 关闭， 1 开启[默认]）
var BRAC_SO_NETWORK_MTUSIZE			=		48;	// 设置网络层MTU大小（参数为int型）
var BRAC_SO_NETWORK_UDPSTATUS		=		49;	// UDP网络通信状态查询（参数为int型）
var BRAC_SO_NETWORK_LARGEDELAY		=		53;	// 网络高延迟模式，适用于卫星网络环境（参数为int型）
var BRAC_SO_NETWORK_IPV6DNS			=		54;	// IPv6域名解析控制（参数为int型，0 关闭， 1开启[默认]），传统网络（IPv4）下，禁用IPv6可提高域名解析速度


var BRAC_SO_PROXY_FUNCTIONCTRL = 			50;	// 本地用户代理功能控制，（参数为：int型，1启动代理，0关闭代理[默认]）
var BRAC_SO_PROXY_VIDEOCTRL = 				51;	// 本地用户代理视频控制，将本地视频变为指定用户的视频对外发布（参数为int型，表示其它用户的userid）
var BRAC_SO_PROXY_AUDIOCTRL = 				52;	// 本地用户代理音频控制，将本地音频变为指定用户的音频对外发布（参数同BRAC_SO_PROXY_VIDEOCTRL）

var BRAC_SO_STREAM_MAXBUFFERTIME = 			60;	// 最大流缓冲时间（参数为int型，单位：毫秒，取值范围：500 ~ 5000，默认：800），发言模式设置值，歌曲模式会自动增加一倍
var BRAC_SO_STREAM_SMOOTHPLAYMODE = 		61;	// 平滑播放模式（参数为int型，0 关闭[默认], 1 打开），打开状态下遇到视频丢帧时会继续播放（可能出现马赛克），不会卡住

var BRAC_SO_VIDEOSHOW_MODECTRL = 			80;	// 视频显示模式控制（参数为：int型，0 单画面显示，1 视频迭加显示）
var BRAC_SO_VIDEOSHOW_SETPRIMARYUSER = 		81;	// 设置主显示用户编号（参数为：int型，用户ID号）
var BRAC_SO_VIDEOSHOW_SETOVERLAYUSER = 		82;	// 设置迭加显示用户编号（参数为：int型，用户ID号）
var BRAC_SO_VIDEOSHOW_DRIVERCTRL = 			83;	// 视频显示驱动控制（参数为：int型，0 默认驱动， 1 Windows DirectShow，2 Windows GDI，3 SDL, 4 Android2X）
var BRAC_SO_VIDEOSHOW_CLIPMODE =			86;	// 远程视频显示旋转裁剪模式（参数为int型， 0 自动[默认]）
var BRAC_SO_VIDEOSHOW_CBPIXFMT	=			87;	// 视频数据回调格式（参数为int型）

var BRAC_SO_CORESDK_TICKOUTUSER	=			110;// 从服务器上踢掉指定用户（参数为int型，表示目标用户ID）

var BRAC_SO_CORESDK_DEVICEMODE	=			130;// 设备模式控制（局域网设备之间可以互相通信，不依赖服务器；参数为int型，0 关闭[默认]，1 开启）
var BRAC_SO_CORESDK_SCREENCAMERACTRL =		131;// 桌面共享功能控制（参数为：int型， 0 关闭[默认]， 1 开启）
var BRAC_SO_CORESDK_UPLOADLOGINFO =			134;// 上传日志信息到服务器（参数为：int型，0 关闭[默认]， 1 开启）
var BRAC_SO_CORESDK_WRITELOG	=			135;// 写入调试信息到本地日志文件中
var BRAC_SO_CORESDK_NEWLOGFILE	=			136;// 产生新的日志文件
var BRAC_SO_CORESDK_SUPPORTSIP	=			137;// 判断当前是否支持SIP通信
var BRAC_SO_CORESDK_SUPPORTHTML5	=		138;// 判断当前是否支持HTML5
var BRAC_SO_CORESDK_DISABLELOGFILE	=		139;// 禁止生成本地日志文件
var BRAC_SO_CORESDK_SUPPORTVIDEOCODEC =		210;// 设置支持的视频编码器
var BRAC_SO_CORESDK_SUPPORTAUDIOCODEC =		211;// 设置支持的音频编码器
var BRAC_SO_CORESDK_DISABLEMEDIACONSUL =	212;// 禁止媒体协商
var BRAC_SO_CORESDK_QUERYTIMEOUTTIME =		213;// 信息查询超时时间（参数为：int型，单位：ms，默认值1000）
var BRAC_SO_CORESDK_REMOTEASSISTHWND =		214;// 远程协助窗口句柄
var BRAC_SO_CORESDK_REMOTEASSISTXPOS =		215;// 远程协助窗口滚动条位置（X）
var BRAC_SO_CORESDK_REMOTEASSISTYPOS =		216;// 远程协助窗口滚动条位置（Y）
var BRAC_SO_CORESDK_DISABLEDNSCONNECT=		219;// 屏蔽DNS寻址
var BRAC_SO_CORESDK_LOGFILEROOTPATH	=		220;// 日志文件保存根路径（日志重定向，参数为字符串，绝对路径）
var BRAC_SO_CORESDK_LOGFILERULE	=			221;// 客户端日志文件保存规则（参数为int型，0 自动覆盖[默认] 1 按日期保存，不覆盖）
var BRAC_SO_CORESDK_FILEENCANDDEC	=		222;// 文件加解密控制（参数为字符串类型，JSON格式）
var BRAC_SO_CORESDK_PPTHELPERINIT	=		223;// PPT播报环境初始化
var BRAC_SO_CORESDK_PPTFILECTRL		=		224;// PPT文件控制
var BRAC_SO_CORESDK_CBMEDIASTREAM	=		225;// 回调原始音视频流
var BRAC_SO_CORESDK_CBVIDEOSTREAM	=		226;// 回调原始视频流
var BRAC_SO_CORESDK_CBAUDIOSTREAM	=		227;// 回调原始音频流
var BRAC_SO_CORESDK_STREAMADAPTIVE	=		228;// 流媒体自适应控制（参数为int型，0 关闭 1 开启[默认]）
var BRAC_SO_CORESDK_MAXTRANSFILESIZE=		229;// 允许传输的最大文件大小（参数为int型，单位：MByte）
var BRAC_SO_CORESDK_USESERVERTIME	=		230;// 使用服务器时间戳（参数为int型，0 关闭[默认] 1 开启）
var BRAC_SO_CORESDK_APPMONITORLIST	=		231;// 应用程序列表，应用程序共享模块使用（参数为字符串）
var BRAC_SO_CORESDK_SSLCERTCHAIN	=		232;// SSL证书链
var BRAC_SO_CORESDK_SUPPORTMEDIACODEC=		233;// 本地支持的编码器信息，用于编码协商
var BRAC_SO_CORESDK_SETUSERAPPINFO	=		236;// 设置用户APP信息
var BRAC_SO_CORESDK_LASTERRORCODE	=		237;// 获取最后的出错代码



var BRAC_SO_UDPTRACE_MODE		=			160;// UDP数据包跟踪模式
var BRAC_SO_UDPTRACE_PACKSIZE	=			161;// UDP数据包跟踪的大小，单位：BYTE
var BRAC_SO_UDPTRACE_BITRATE	=			162;// UDP数据包跟踪的包速率，单位：bps
var BRAC_SO_UDPTRACE_START		=			163;// UDP数据包跟踪控制（参数为int型，1 启动， 0 停止）
var BRAC_SO_UDPTRACE_LOCALRECVNUM	=		164;// UDP数据包跟踪本地接收包数量
var BRAC_SO_UDPTRACE_SERVERRECVNUM	=		165;// UDP数据包跟踪服务器接收包数量
var BRAC_SO_UDPTRACE_SOURCESENDNUM	=		166;// UDP数据包跟踪源发包数量
var BRAC_SO_UDPTRACE_SENDUSERID	=			167;// UDP数据包跟踪源用户ID
var BRAC_SO_UDPTRACE_NETDELAY	=			168;// UDP数据包网络延迟，单位：ms，-1表示未知


// 用户多媒体流参数定义（API：BRAC_GetUserStreamInfo 传入参数）
var BRAC_STREAMINFO_VIDEOWIDTH	=			180;// 视频流宽度
var BRAC_STREAMINFO_VIDEOHEIGHT	=			181;// 视频流高度
var BRAC_STREAMINFO_VIDEOFPS	=			182;// 视频流帧率
var BRAC_STREAMINFO_VIDEOBITRATE=			183;// 视频流码率，单位：bps
var BRAC_STREAMINFO_VIDEOCODECID=			184;// 视频流编码器ID
var BRAC_STREAMINFO_VIDEOPACKLOSSRATE=		185;// 视频流丢包率
var BRAC_STREAMINFO_VIDEODEVICENAME	=		186;// 视频采集设备名称
var BRAC_STREAMINFO_AUDIOCHANNELS	=		190;// 音频流通道数
var BRAC_STREAMINFO_AUDIOSAMPLERATE	=		191;// 音频流采样率
var BRAC_STREAMINFO_AUDIOBITRATE	=		192;// 音频流码率，单位：bps
var BRAC_STREAMINFO_AUDIOCODECID	=		193;// 音频流编码器ID
var BRAC_STREAMINFO_AUDIOPACKLOSSRATE=		194;// 音频流丢包率
var BRAC_STREAMINFO_AUDIODEVICENAME	=		195;// 音频采集设备名称

var BRAC_SO_OBJECT_INITFLAGS	=			200;// 业务对象身份初始化
var BRAC_SO_CLOUD_APPGUID		=			300;// 云平台应用GUID（参数为：字符串类型，连接服务器之前设置）
var BRAC_SO_CLOUD_ACCTYPE		=			301;// 云平台应用集成账号类型
var BRAC_SO_CLOUD_APPID3RD		=			302;// 云平台应用集成时第三方平台的应用GUID

var BRAC_SO_ENABLEWEBSERVICE 	=			11002;	// 启动本地Web服务
var BRAC_SO_LOCALPATH2URL		=			11003;	// 将本地路径转换为URL地址
var BRAC_SO_GETTASKPATHNAME		=			11004;	// 根据传输任务ID获取文件路径
var BRAC_SO_VIDEOBKIMAGE		=			11006;	// 设置视频背景图片
var ANYCHATWEB_SO_STRBASE64MODE = 			11007;	// 字符串 base64 模式（仅web 端生效，前端 base64 编码后入参；回调函数插件也 base64 编码后出参）
var ANYCHATWEB_SO_ASYNCMSGNOTIFY=			11008;  // 异步消息通知（解决部分老Chrome浏览器事件通知会导致崩溃的问题）
var ANYCHATWEB_SO_ACTIVEMSG     =			11009;   // js 主动获取回调消息(解决插件回调导致的插件卡死问题)
var ANYCHATWEB_SO_SUPPORTACTIVEMSG =     	11010;	// 是否支持主动获取回调消息0

// 传输任务信息参数定义（API：BRAC_QueryTransTaskInfo 传入参数）
var BRAC_TRANSTASK_PROGRESS		= 			1;	// 传输任务进度查询（参数为：DOUBLE型，返回值0.0 ~ 100.0， 或参数为：DWORD型，返回值0 ~ 100）
var BRAC_TRANSTASK_BITRATE		= 			2;	// 传输任务当前传输码率（参数为：int型，单位：bps）
var BRAC_TRANSTASK_STATUS		= 			3;	// 传输任务当前状态（参数为：int型）
var BRAC_TRANSTASK_SAVEASPATH	= 			4;	// 文件传输任务另存为路径设置，含文件名（参数为字符串TCHAR类型）
var BRAC_TRANSTASK_SOURCEFILE	=			5;	// 源文件名（含路径，参数为字符串，TCHAR类型）
var BRAC_TRANSTASK_JSONSTATUS	=			6;	// 传输任务状态，Json字符串

// 录像功能标志定义（API：BRAC_StreamRecordCtrl 传入参数）
var BRAC_RECORD_FLAGS_VIDEO		=	0x00000001;	// 录制视频
var BRAC_RECORD_FLAGS_AUDIO		=	0x00000002;	// 录制音频
var BRAC_RECORD_FLAGS_SERVER	=	0x00000004;	// 服务器端录制
var BRAC_RECORD_FLAGS_MIXAUDIO 	=	0x00000010;	// 录制音频时，将其它人的声音混音后录制
var BRAC_RECORD_FLAGS_MIXVIDEO	=	0x00000020;	// 录制视频时，将其它人的视频迭加后录制
var BRAC_RECORD_FLAGS_ABREAST	=	0x00000100;	// 录制视频时，将其它人的视频并列录制
var BRAC_RECORD_FLAGS_STEREO	=	0x00000200;	// 录制音频时，将其它人的声音混合为立体声后录制
var BRAC_RECORD_FLAGS_SNAPSHOT	=	0x00000400;	// 拍照
var BRAC_RECORD_FLAGS_LOCALCB	=	0x00000800;	// 触发本地回调
var BRAC_RECORD_FLAGS_STREAM	=	0x00001000;	// 对视频流进行录制（效率高，但可能存在视频方向旋转的问题）
var BRAC_RECORD_FLAGS_USERFILENAME=	0x00002000;	// 用户自定义文件名
var BRAC_RECORD_FLAGS_FILEMD5 	=	0x00040000;	// 计算录像文件的MD5值

// 客户端、服务器端录制标志定义保持统一
var ANYCHAT_RECORD_FLAGS_VIDEO	=	BRAC_RECORD_FLAGS_VIDEO;
var ANYCHAT_RECORD_FLAGS_AUDIO	=	BRAC_RECORD_FLAGS_AUDIO;
var ANYCHAT_RECORD_FLAGS_SERVER	=	BRAC_RECORD_FLAGS_SERVER;
var ANYCHAT_RECORD_FLAGS_MIXAUDIO =	BRAC_RECORD_FLAGS_MIXAUDIO;
var ANYCHAT_RECORD_FLAGS_MIXVIDEO =	BRAC_RECORD_FLAGS_MIXVIDEO;
var ANYCHAT_RECORD_FLAGS_ABREAST =	BRAC_RECORD_FLAGS_ABREAST;
var ANYCHAT_RECORD_FLAGS_STEREO	=	BRAC_RECORD_FLAGS_STEREO;
var ANYCHAT_RECORD_FLAGS_SNAPSHOT =	BRAC_RECORD_FLAGS_SNAPSHOT;
var ANYCHAT_RECORD_FLAGS_LOCALCB =	BRAC_RECORD_FLAGS_LOCALCB;
var ANYCHAT_RECORD_FLAGS_STREAM =	BRAC_RECORD_FLAGS_STREAM;
var ANYCHAT_RECORD_FLAGS_USERFILENAME = BRAC_RECORD_FLAGS_USERFILENAME;
var ANYCHAT_RECORD_FLAGS_ERRORCODE =	0x00004000;	// 支持出错代码
var ANYCHAT_RECORD_FLAGS_MULTISTREAM=	0x00008000;	// 支持多路流的录制（拍照）
var ANYCHAT_RECORD_FLAGS_CANCEL	=		0x00010000;	// 取消录像，删除录像文件
var ANYCHAT_RECORD_FLAGS_BUFFERCB =		0x00020000;	// 缓冲区数据回调
var ANYCHAT_RECORD_FLAGS_FILEMD5 =		0x00040000;	// 计算录像文件的MD5值

// 视频裁剪模式定义
var ANYCHAT_VIDEOCLIPMODE_UNKNOW	=		-1;	// 未知模式，不需要做裁剪时使用
var ANYCHAT_VIDEOCLIPMODE_AUTO		=		0;	// 默认模式，以最大比例进行裁剪，然后再整体拉伸，画面保持比例，但被裁剪画面较大
var ANYCHAT_VIDEOCLIPMODE_OVERLAP	=		1;	// 重叠模式，只取最大有效部分，对边缘进行裁剪
var ANYCHAT_VIDEOCLIPMODE_SHRINK	=		2;	// 缩小模式，缩小到合适的比例，不进行裁剪
var ANYCHAT_VIDEOCLIPMODE_STRETCH	=		3;	// 平铺模式，不进行裁剪，但可能导致画面不成比例
var ANYCHAT_VIDEOCLIPMODE_DYNAMIC	=		4;	// 动态模式，由上层应用根据分辩率来调整显示表面，保持画面不变形

// 组播策略定义
var BRAC_MCPOLITIC_DISABLE			=		0;	// 执行服务器路由策略，禁止所有组播发送[默认]
var BRAC_MCPOLITIC_ONLYLOCALMC		=		1;	// 忽略服务器路由策略，只向客户端本地组播组广播媒体流
var BRAC_MCPOLITIC_SERVERANDLOCALMC	=		2;	// 执行服务器路由策略，同时在客户端本地发送组播数据
var BRAC_MCPOLITIC_ONLYSERVERMC		=		3;	// 忽略服务器路由策略，只向服务器本地组播组广播媒体流
var BRAC_MCPOLITIC_SERVERANDSERVERMC=		4;	// 执行服务器路由策略，同时在服务器端发送组播数据

// 组播功能标志定义
var BRAC_MCFLAGS_JOINGROUP		=	0x00000001;	// 加入多播组
var BRAC_MCFLAGS_LEAVEGROUP		=	0x00000002;	// 离开多播组
var BRAC_MCFLAGS_SENDDATA		=	0x00000010;	// 数据发送标志，指示该多播组用于发送数据
var BRAC_MCFLAGS_RECVDATA		=	0x00000020;	// 数据接收标志，指示该多播组用于接收数据

// 用户状态标志定义（API：BRAC_QueryUserState 传入参数）
var BRAC_USERSTATE_CAMERA 		= 			1;	// 用户摄像头状态（参数为DWORD型）
var BRAC_USERSTATE_HOLDMIC 		= 			2;	// 用户音频设备状态（参数为DWORD型，返回值：0 音频采集关闭， 1 音频采集开启）
var BRAC_USERSTATE_SPEAKVOLUME 	= 			3;	// 用户当前说话音量（参数为DOUBLE类型（0.0 ~ 100.0））
var BRAC_USERSTATE_RECORDING 	= 			4;	// 用户录像（音）状态（参数为DWORD型）
var	BRAC_USERSTATE_LEVEL 		= 			5;	// 用户级别（参数为DWORD型）
var BRAC_USERSTATE_NICKNAME 	= 			6;	// 用户昵称（参数为字符串TCHAR类型）
var BRAC_USERSTATE_LOCALIP 		= 			7;	// 用户本地IP地址（内网，参数为字符串TCHAR类型）
var BRAC_USERSTATE_INTERNETIP 	= 			8;	// 用户互联网IP地址（参数为字符串TCHAR类型）
var BRAC_USERSTATE_VIDEOBITRATE = 			9;	// 用户当前的视频码率（参数为DWORD类型，Bps）
var BRAC_USERSTATE_AUDIOBITRATE = 			10;	// 用户当前的音频码率（参数为DWORD类型，Bps）
var BRAC_USERSTATE_P2PCONNECT 	= 			11;	// 查询本地用户与指定用户的当前P2P连接状态（参数为DWORD类型，返回值：0 P2P不通， 1 P2P连接成功[TCP]，2 P2P连接成功[UDP]，3 P2P连接成功[TCP、UDP]）
var BRAC_USERSTATE_NETWORKSTATUS= 			12;	// 查询指定用户的网络状态（参数为DWORD类型，返回值：0 优良，1 较好，2 一般，3 较差，4 非常差），注：查询间隔需要>1s
var BRAC_USERSTATE_VIDEOSIZE 	= 			13;	// 查询指定用户的视频分辨率（参数为DWORD类型，返回值：低16位表示宽度，高16位表示高度）
var BRAC_USERSTATE_PACKLOSSRATE = 			14;	// 查询指定用户的网络流媒体数据丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）
var BRAC_USERSTATE_DEVICETYPE 	=			15; // 查询指定用户的终端类型（参数为DWORD类型，返回值：0 Unknow， 1 Windows，2 Android，3 iOS，4 Web，5 Linux，6 Mac，7 Win Phone，8 WinCE）
var BRAC_USERSTATE_SELFUSERSTATUS=			16;	// 查询本地用户的当前状态（参数为DWORD类型，返回值：0 Unknow，1 Connected，2 Logined，3 In Room，4 Logouted，5 Link Closed）
var BRAC_USERSTATE_SELFUSERID	=			17;	// 查询本地用户的ID（参数为DWORD类型，若用户登录成功，返回用户实际的userid，否则返回-1）
var BRAC_USERSTATE_VIDEOROTATION=			18;	// 查询指定用户的当前视频旋转角度（参数为DWORD类型，返回角度值）
var BRAC_USERSTATE_VIDEOMIRRORED=			19;	// 查询指定用户的视频是否需要镜像翻转
var BRAC_USERSTATE_AUDIOCODECID	=			20;	// 查询指定用户的音频编码器ID
var BRAC_USERSTATE_VIDEOCODECID	=			21;	// 查询指定用户的视频编码器ID
var BRAC_USERSTATE_RESENDLOSSRATE=			22;// 丢包补偿后的丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）


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
var WM_GV_VIDEOSIZECHG		=	WM_GV + 15;		// 用户视频分辩率发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的视频分辨率组合值（低16位表示宽度，高16位表示高度）
var WM_GV_USERINFOUPDATE	=	WM_GV + 16;		// 用户信息更新通知，wParam（INT）表示用户ID号，lParam（INT）表示更新类别
var WM_GV_FRIENDSTATUS		=	WM_GV + 17;		// 好友在线状态变化，wParam（INT）表示好友用户ID号，lParam（INT）表示用户的当前活动状态：0 离线， 1 上线
var WM_GV_OBJECTEVENT		=	WM_GV + 18;		// 对象事件通知，wParam（INT）表示对象类型，lParam（INT）表示对象ID
var WM_GV_SESSIONKEEP		=	WM_GV + 19;		// 会话保持事件，wParam（INT）表示会话保持状态：0 会话保持开始， 1 会话保持结束，lParam（INT）表示出错代码

var WM_GV_PRIVATEREQUEST	=	WM_GV + 21;		// 用户发起私聊请求，wParam（INT）表示发起者的用户ID号，lParam（INT）表示私聊请求编号，标识该请求
var WM_GV_PRIVATEECHO		=	WM_GV + 22;		// 用户回复私聊请求，wParam（INT）表示回复者的用户ID号，lParam（INT）为出错代码
var WM_GV_PRIVATEEXIT		=	WM_GV + 23;		// 用户退出私聊，wParam（INT）表示退出者的用户ID号，lParam（INT）为出错代码
var WM_GV_SERVERCFGUPDATE	=	WM_GV + 24;		// 服务器配置参数更新

var WM_GV_EXTENDBTNPRESS	=	WM_GV + 31;		// 用户按下扩展按钮，wParam（INT）表示按钮所对应的用户ID号，lParam（DWORD）指示按钮（左下角）所在屏幕位置(x,y)，用户可以利用该参数显示菜单等
var WM_GV_VIDEOFULLSCREEN	=	WM_GV + 32;		// 用户视频全屏通知，wParam（INT）表示用户ID，lParam(DWORD)表示当前视频是否全屏显示

var WM_GV_SDKWARNING      	=   WM_GV + 41;		// SDK警告信息，当SDK在运行过程中自检发现异常状态时，将向上层发送该消息，wParam（INT）表示警告代码，定义为：GV_ERR_WARNING_XXXX

var WM_GV_AUDIOPLAYCTRL		=	WM_GV + 100;	// 音频播放设备控制，wParam:1 打开播放器， 0 关闭播放器， lParam：profile，android平台内部使用
var WM_GV_AUDIORECCTRL		=	WM_GV + 101;	// 音频录音设备控制，wParam:1 打开音频采集设备，0 关闭音频采集设备
var WM_GV_VIDEOCAPCTRL		=	WM_GV + 102;	// 视频采集控制，wParam: 1 开始采集， 0 关闭采集

// 房间状态标志定义（API：BRAC_QueryRoomState 传入参数）
var BRAC_ROOMSTATE_ROOMNAME		=			1;	// 房间名称（参数为字符串TCHAR类型）
var BRAC_ROOMSTATE_ONLINEUSERS	=			2;	// 房间在线用户数（参数为DWORD型，不包含自己

// 视频呼叫事件类型定义（API：BRAC_VideoCallControl 传入参数、VideoCallEvent回调参数）
var BRAC_VIDEOCALL_EVENT_REQUEST=			1;	// 呼叫请求
var BRAC_VIDEOCALL_EVENT_REPLY 	=			2;	// 呼叫请求回复
var BRAC_VIDEOCALL_EVENT_START 	=			3;	// 视频呼叫会话开始事件
var BRAC_VIDEOCALL_EVENT_FINISH =			4;	// 挂断（结束）呼叫会话

// 视频呼叫标志定义（API：BRAC_VideoCallControl 传入参数）
var BRAC_VIDEOCALL_FLAGS_AUDIO		=	0x0001;	// 语音通话
var BRAC_VIDEOCALL_FLAGS_VIDEO		=	0x0002;	// 视频通话
var BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO	=	0x0010;	// 禁止源（呼叫端）音频
var BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO	=	0x0020;	// 禁止源（呼叫端）视频
var BRAC_VIDEOCALL_FLAGS_FBTARAUDIO	=	0x0040;	// 禁止目标（被呼叫端）音频
var BRAC_VIDEOCALL_FLAGS_FBTARVIDEO	=	0x0080;	// 禁止目标（被呼叫端）视频
var BRAC_VIDEOCALL_FLAGS_ASSISTREQ	=	0x0100;	// 请求目标用户远程协助
var BRAC_VIDEOCALL_FLAGS_CONTROLREQ	=	0x0200;	// 请求控制目标用户

// 出错代码定义
var GV_ERR_SUCCESS			=	0;				// 成功
var GV_ERR_PLUGINNOINSTALL	=	1010000;		// 插件没有安装
var GV_ERR_PLUGINOLDVERSION =	1010001;		// 插件版本太低
var GV_ERR_SESSION_QUIT		= 	100101;			// 源用户主动放弃会话
var GV_ERR_SESSION_OFFLINE	= 	100102;			// 目标用户不在线
var GV_ERR_SESSION_BUSY		= 	100103;			// 目标用户忙
var GV_ERR_SESSION_REFUSE	= 	100104;			// 目标用户拒绝会话
var GV_ERR_SESSION_TIMEOUT	= 	100105;			// 会话请求超时
var GV_ERR_SESSION_DISCONNECT=	100106;			// 网络断线

// 远程视频方向修正标志定义
var BRAC_ROTATION_FLAGS_MIRRORED	=	0x1000;	// 图像需要镜像翻转
var BRAC_ROTATION_FLAGS_ROTATION90	=	0x2000;	// 顺时针旋转90度
var BRAC_ROTATION_FLAGS_ROTATION180	=	0x4000;	// 顺时针旋转180度
var BRAC_ROTATION_FLAGS_ROTATION270	=	0x8000;	// 顺时针旋转270度

// 用户信息控制类型定义（API：BRAC_UserInfoControl 传入参数）
var BRAC_USERINFO_CTRLCODE_ROTATION	=		8;	// 让指定的用户视频在显示时旋转，wParam为旋转角度参数
var BRAC_USERINFO_CTRLCODE_DEBUGLOG	=		9;	// 输出本地用户的调试日志，wParam为调试日志类型
var BRAC_USERINFO_CTRLCODE_LVORIENTFIX	=	10;	// 本地视频采集方向修正，wParam为方向参数，lParam为修正角度

// 服务器信息查询常量定义（API：BRAC_QueryInfoFromServer 传入参数）
var ANYCHAT_SERVERQUERY_USERIDBYNAME	=	1;	// 根据用户昵称查询用户ID
var ANYCHAT_SERVERQUERY_USERIDBYSTRID	=	2;	// 根据字符串ID查询用户ID
var ANYCHAT_SERVERQUERY_STRIDBYUSERID	=	3;	// 根据用户ID查询字符串ID
var ANYCHAT_SERVERQUERY_NAMEBYUSERID	=	4;	// 根据用户ID查询用户名
var ANYCHAT_SERVERQUERY_NAMEBYSTRID		=	5;	// 根据字符串ID查询用户名
var ANYCHAT_SERVERQUERY_USERINFOBYID	=	6;	// 根据用户ID查询用户信息
var ANYCHAT_SERVERQUERY_PPTFILEINFO		=	10;	// PPT文件信息
var ANYCHAT_SERVERQUERY_QUEUEAGENTINFO	=	100;// 查询指定队列的坐席服务信息
var ANYCHAT_SERVERQUERY_RUNNINGSTATUS	=	200;// 查询服务器运行状态
var ANYCHAT_SERVERQUERY_ONLINEUSERS		=	201;// 查询服务器在线用户数

///////////////////////////////

/**
 *
 * AI能力
 */
var ANYCHAT_AI_CTRL_ROBOT_INIT	               =  1	     //< 初始化AI能力机器人
var ANYCHAT_AI_CTRL_ROBOT_RELEASE              =  2	     //< 释放AI能力机器人
var ANYCHAT_AI_CTRL_ROBOT_ACTIVETEST           =  3	     //< 机器人心跳检测
var ANYCHAT_AI_CTRL_ABILITY_INVOKE             =  4	     //< AI能力调用
var ANYCHAT_AI_CTRL_ABILITY_REQUEST            =  5	     //< 请求AI能力
var ANYCHAT_AI_CTRL_ABILITY_RELEASE            =  6	     //< 释放AI能力
var ANYCHAT_AI_CTRL_ABILITY_ACTIVETEST         =  7	     //< AI能力心跳检测
var ANYCHAT_AI_CTRL_GETOPTION                  =  8      //< 参数查询
var ANYCHAT_AI_CTRL_SETOPTION                  =  9      //< 参数设置

//AI返回事件类型
var ANYCHAT_AI_EVENT_ROBOT_INITRESULT          =  1       //< 机器人初始化结果
var ANYCHAT_AI_EVENT_ROBOT_STATUS              =  2	      //< 机器人状态通知
var ANYCHAT_AI_EVENT_ROBOT_ACTIVERET           =  3       //< 机器人心跳检测结果
var ANYCHAT_AI_EVENT_ABILITY_RESULT            =  4       //< AI能力执行结果
var ANYCHAT_AI_EVENT_ABILITY_STATUS            =  5       //< AI能力状态通知
var ANYCHAT_AI_EVENT_ABILITY_ACTIVERET         =  6       //< AI能力心跳检测结果

//机器人状态
var ANYCHAT_AIROBOT_STATUS_UNKNOW              =  0;      //< 未知状态
var ANYCHAT_AIROBOT_STATUS_OFFLINE             =  1;      //< 离线状态
var ANYCHAT_AIROBOT_STATUS_PREPARE             =  2;      //< 准备状态
var ANYCHAT_AIROBOT_STATUS_ONLINE              =  3;      //< 在线状态
var ANYCHAT_AIROBOT_STATUS_PAUSE               =  4;      //< 暂停状态

//AI能力状态
var ANYCHAT_AIABILITY_STATUS_PREPARE           =  1;      //< 准备状态
var ANYCHAT_AIABILITY_STATUS_PROCESS           =  2;      //< 执行状态
var ANYCHAT_AIABILITY_STATUS_FINISH            =  3;      //< 完成状态
//ASR能力相关定义
//文本类型
var ANYCHAT_OCRTYPE_NUMBER                     =  1;      //< 数字
var ANYCHAT_OCRTYPE_CHINESE                    =  2;      //< 汉语普通话
//AI能力类型定义
var ANYCHAT_AI_TYPE_ASR		                   =  1	      //< 语音识别
var ANYCHAT_AI_TYPE_TTS		                   =  2	      //< 语音合成
var ANYCHAT_AI_TYPE_VPR		                   =  3	      //< 声纹识别
var ANYCHAT_AI_TYPE_AFR		                   =  4	      //< 人脸识别
var ANYCHAT_AI_TYPE_OCR		                   =  5	      //< 文字识别
var ANYCHAT_AI_TYPE_HWR		                   =  6	      //< 手写识别
var ANYCHAT_AI_TYPE_NLU		                   =  7	      //< 语义理解
var ANYCHAT_AI_TYPE_FPR		                   =  8	      //< 指纹识别
var ANYCHAT_AI_TYPE_AIR		                   =  9	      //< 图像识别
var ANYCHAT_AI_TYPE_AIC		                   =  100     //< 自动照片捕获
//工作模式
var ANYCHAT_ASRMODE_FILESTREAM                 =  1;	  //< 对录音文件进行语音识别
var ANYCHAT_ASRMODE_LIVESTREAM                 =  2;	  //< 对实时流进行语音识别
var ANYCHAT_ASRMODE_TAGRECORD                  =  3;	  //< 对录像文件加标签进行语音识别
var ANYCHAT_ASRMODE_KEYWORDRECOGNITION         =  4;	  //< 语音关键字识别

//语句标志
var ANYCHAT_ASR_SENTENCE_STARTED               =  1;	  //< 语句开始
var ANYCHAT_ASR_SENTENCE_CHANGED               =  2;      //< 语句改变
var ANYCHAT_ASR_SENTENCE_ENDED                 =  3;	  //< 语句结束

//TTS能力相关定义
//人声类型
var ANYCHAT_TTSTYPE_MENVOICE                   =   1;	  //< TTS男声
var ANYCHAT_TTSTYPE_WOMENVOICE                 =   2;	  //< TTS女声
//AFR能力相关定义
//工作模式
var ANYCHAT_AFRMODE_IMAGEFACEDETECT            =   1;	  //< 照片人脸检测：检测指定照片中是否存在人脸，并返回人脸位置
var ANYCHAT_AFRMODE_STREAMFACEDETECT           =   2;	  //< 视频流人脸检测：检测指定用户的视频流是否存在人脸，并返回人脸位置
var ANYCHAT_AFRMODE_IMAGEFACECOMPARE           =   3;	  //< 照片人脸比对：比较两张照片中的人脸是否相似，返回相似度及人脸位置
var ANYCHAT_AFRMODE_STREAMFACECOMPARE          =   4;	  //< 视频流人脸比对：比较视频流中的人脸和给定照片的人脸是否相似，返回相似度及人脸位置
var ANYCHAT_AFRMODE_IMAGEFACEREC               =   5;	  //< 照片人脸识别：识别照片中的人脸是谁
var ANYCHAT_AFRMODE_STREAMFACEREC              =   6;	  //< 视频流人脸识别：识别视频流中的人脸是谁
var ANYCHAT_AFRMODE_IMAGETWOPERSONCOMPARE      =   7;	  //< 照片两人人脸比对：一张含两人的图片与两张两个人单独的图片比对
var ANYCHAT_AFRMODE_STREAMTWOPERSONCOMPARE     =   8;	  //< 视频流两人人脸比对：一张含两人的图片与一张视频截图和一张人脸图片比对
var ANYCHAT_AFRMODE_IMAGEFACEPOSTUREDETECT     =   9;	  //< 图片人脸姿势检测（正脸、侧脸）
var ANYCHAT_AFRMODE_STREAMFACEPOSTUREDETECT    =   10;	  //< 视频流人脸姿势检测（正脸、侧脸）
//OCR能力相关定义
//文档类型
var ANYCHAT_OCRTYPE_UNKNOW                     =   0;	  //< 未知文档
var ANYCHAT_OCRTYPE_NORMALDOC                  =   1;	  //< 标准文档
var ANYCHAT_OCRTYPE_IDCARDFRONT                =   2;	  //< 身份证正面
var ANYCHAT_OCRTYPE_IDCARDBACK                 =   3;	  //< 身份证背面
var ANYCHAT_OCRTYPE_BINKCARD                   =   4;	  //< 银行卡
//AIR能力相关定义
//工作模式
var ANYCHAT_AIRMODE_SCENELOGOREC               =   1;	  //< 场景logo识别
//AIC能力相关定义
//工作模式
var ANYCHAT_AICMODE_FACECAPTURE                =   1;	  //< 自动抓拍人脸，人脸位置居中检测
var ANYCHAT_AICMODE_FACECOMPARE                =   2;	  //< 抓拍时进行人脸比对，和指令中的"content"数据进行比对
var ANYCHAT_AICMODE_IDCARDFRONTOCR             =   3;	  //< 抓拍时进行身份证正面的OCR识别
var ANYCHAT_AICMODE_IDCARDBACKOCR              =   4;	  //< 抓拍时进行身份证背面的OCR识别
var ANYCHAT_AICMODE_BANKCARDOCR                =   5;	  //< 抓拍时进行银行卡的OCR识别
var ANYCHAT_AICMODE_NORMALDOCOCR               =   6;	  //< 抓拍时进行标准文档OCR识别

//////////////////////

// SDK控制常量定义（API：BRAC_SDKControl 传入参数）
var ANYCHAT_SDKCTRL_BASE				=	1;	// 基本功能控制
var ANYCHAT_SDKCTRL_USERBUFFER			=	3;	// 用户缓冲区传输控制
var ANYCHAT_SDKCTRL_INVOKEEVENT			=	4;	// 触发异步事件
var ANYCHAT_SDKCTRL_RECORD				=	5;	// 音视频录制
var ANYCHAT_SDKCTRL_OBJECT				=	20;	// 对象操作
var ANYCHAT_SDKCTRL_VIDEOCALL			=	30;	// 呼叫控制
var ANYCHAT_SDKCTRL_USERINFO			=	40;	// 用户信息控制
var ANYCHAT_SDKCTRL_STREAMPLAY			=	50;	// 流媒体播放
var ANYCHAT_SDKCTRL_MEDIAPROCESS		=	51;	// 流媒体处理控制
var ANYCHAT_SDKCTRL_NETWORK				=	60;	// 网络控制
var ANYCHAT_SDKCTRL_MEDIA				=	70;	// 媒体控制
var ANYCHAT_SDKCTRL_RECORDTAG			=	71;	// 录像标签
var ANYCHAT_SDKCTRL_SCREENCAPPARAM		=	72;	// 屏幕采集参数设置
var ANYCHAT_SDKCTRL_VIRTUALSTUDIO		=	73;	// 虚拟演播室
var ANYCHAT_SDKCTRL_FILEDELETE			=	80;	// 删除文件
var ANYCHAT_SDKCTRL_FILEINFO			=	81;	// 获取文件信息
var ANYCHAT_SDKCTRL_DISKSIZE			=	82;	// 获取磁盘容量
var ANYCHAT_SDKCTRL_FILEENCRYPT			=	83;	// 文件加解密控制
var ANYCHAT_SDKCTRL_DELETEDIR			=	84;	// 删除目录
var ANYCHAT_SDKCTRL_CREATEDIR			=	85;	// 创建目录
var ANYCHAT_SDKCTRL_DIRCLEAN			=	86;	// 目录清理
var ANYCHAT_SDKCTRL_FINDFILE			=	87;	// 查找文件
var ANYCHAT_SDKCTRL_PPTHELPERINIT		=	90;	// PPT播报环境初始化
var ANYCHAT_SDKCTRL_PPTFILECTRL			=	91;	// PPT文件控制
var ANYCHAT_SDKCTRL_PPTFILEINFO			=	92;	// PPT文件信息
var ANYCHAT_SDKCTRL_BUSINESS			=	95;	// 业务控制
var ANYCHAT_SDKCTRL_MEDIAFILTERINIT		=	96;	// 媒体过滤器初始化
var ANYCHAT_SDKCTRL_VIDEODEVICEINFO		=	97;	// 获取视频采集设备信息
var ANYCHAT_SDKCTRL_UPDATERECUSERSTR	=	98;	// 更新录像用户参数
var ANYCHAT_SDKCTRL_SYNCRECORD			=	99;	// 同步录像参数设置
var ANYCHAT_SDKCTRL_BUSINESSBUFFER		=	100;// 业务缓冲区控制
var ANYCHAT_SDKCTRL_LIVESTREAM			=	101;// 直播业务控制
var ANYCHAT_SDKCTRL_AIABILITY			=	102;// AI能力
var ANYCHAT_SDKCTRL_APPBUFFER			=	103;// APP自定义缓冲区
var ANYCHAT_SDKCTRL_FACEEMOTIONCTRL		=	300;// 微表情控制


// 媒体播放事件类型定义
var ANYCHAT_STREAMPLAY_EVENT_START		=	3;	// 播放开始事件
var ANYCHAT_STREAMPLAY_EVENT_FINISH		=	4;	// 播放结束事件

// 媒体播放标志定义（API：BRAC_StreamPlayInit 传入参数）
var ANYCHAT_STREAMPLAY_FLAGS_REPLACEAUDIOINPUT 	= 0x00000001;	// 播放音频流代替本地音频输入（Mic）
var ANYCHAT_STREAMPLAY_FLAGS_REPLACEVIDEOINPUT 	= 0x00000002;	// 播放视频流代替本地视频输入（Camera）
var ANYCHAT_STREAMPLAY_FLAGS_CALLBACKDATA		= 0x00000010;	// 回调数据给上层
var ANYCHAT_STREAMPLAY_FLAGS_PPTPLAY			= 0x00000080;	// 双录风险揭示PPT播放


// 媒体播放信息类型定义（API：BRAC_StreamPlayGetInfo 传入参数）
var ANYCHAT_STREAMPLAY_INFO_JSONVALUE	=	1;	// 包含所有播放信息的Json字符串

// 媒体播放控制类型定义（API：BRAC_StreamPlayControl 传入参数）
var ANYCHAT_STREAMPLAY_CTRL_START		=	1;	// 开始播放
var ANYCHAT_STREAMPLAY_CTRL_PAUSE		=	2;	// 暂停播放
var ANYCHAT_STREAMPLAY_CTRL_STOP		=	3;	// 停止播放
var ANYCHAT_STREAMPLAY_CTRL_SEEK		=	4;	// 位置拖动
var ANYCHAT_STREAMPLAY_CTRL_SPEEDCTRL	=	5;	// 速度调整
var ANYCHAT_STREAMPLAY_CTRL_OPENLOOP	=	6;	// 打开循环播放
var ANYCHAT_STREAMPLAY_CTRL_CLOSELOOP	=	7;	// 关闭循环播放


// CoreSDK事件类型定义（回调函数：BRAC_CoreSDKEvent_CallBack参数）
var ANYCHAT_CORESDKEVENT_BASEEVENT		=	1;	// SDK基础事件
var ANYCHAT_CORESDKEVENT_CONNECTHOLD	=	2;	// 连接保持事件
var ANYCHAT_CORESDKEVENT_CAMERASTATE	=	10;	// 摄像头状态事件
var ANYCHAT_CORESDKEVENT_MICSTATE		=	11;	// Mic状态事件
var ANYCHAT_CORESDKEVENT_TRANSFILE		=	12;	// 文件传输事件
var ANYCHAT_CORESDKEVENT_RECORDSTATUS	=	13;	// 录像状态事件
var ANYCHAT_CORESDKEVENT_STREAMPLAY		=	30;	// 媒体播放事件
var ANYCHAT_CORESDKEVENT_PPTHELPER		=	31;	// PPTHelper事件
var ANYCHAT_CORESDKEVENT_BUSINESS		=	32;	// 业务事件
var ANYCHAT_CORESDKEVENT_DEVICEFAIL		=	33;	// 设备失败事件
var ANYCHAT_CORESDKEVENT_MEDIABUFFER	=	34;	// 媒体缓冲区事件
var ANYCHAT_CORESDKEVENT_USERBUFFER		=	35;	// 用户缓冲区事件
var ANYCHAT_CORESDKEVENT_MEDIAPROCESS	=	36;	// 媒体处理事件
var ANYCHAT_CORESDKEVENT_FACEEMOTION	=	40;	// 微表情检测结果
var ANYCHAT_CORESDKEVENT_REGEDITDATA	=	41;	// 数据接口返回数据
var ANYCHAT_CORESDKEVENT_REQUESTEX		=	42;	// 扩展请求返回数据
var ANYCHAT_CORESDKEVENT_BUSINESSBUFFER	=	100;// 业务缓冲区事件
var ANYCHAT_CORESDKEVENT_LIVESTREAM		=	101;// 直播业务事件
var ANYCHAT_CORESDKEVENT_AIABILITY		=	102;// AI能力事件
var ANYCHAT_CORESDKEVENT_APPBUFFER		=	103;// APP自定义缓冲区事件
var ANYCHAT_CORESDKEVENT_USERDEFINE		=	800;// 用户自定义事件起始序号

// 视频显示插件设置参数
var ANYCHATWEB_VIDEO_SO_OVERLAY		=		8;	// 在视频上迭加文字、图片等内容
var ANYCHATWEB_VIDEO_SO_DISABLEFULLSCREEN = 9;	// 禁止双击视频全屏显示
var ANYCHATWEB_VIDEO_SO_EXTENDEDSCREEN	=	10;	// 扩展屏显示视频
var ANYCHATWEB_VIDEO_SO_VIDEODISPMODE	=	11;	// 视频显示模式
var ANYCHATWEB_VIDEO_SO_REMOTEASSIST	=	12;	// 远程协助窗口
var ANYCHATWEB_VIDEO_SO_PLAYTASKGUID	=	20;	// 播放任务ID

// 业务缓冲区标志定义
var ANYCHAT_BUSINESSBUF_FLAGS_SYNC		=	0x01;// 同步操作

//文件控制命令定义常量：
var BRPPT_FILECTRL_DOWNLOAD = 0x01; 			// 下载文件
var BRPPT_FILECTRL_CANCEL = 0x02;				// 取消下载
var BRPPT_FILECTRL_DELETE = 0x04;				// 删除文件

//文件信息查询定义常量：
var BRPPT_FILEINFO_DOWNLOAD_STATUS = 0x01;		// 下载状态
var BRPPT_FILEINFO_PPTDETAILS = 0x02;			// PPT详情

// 远程桌面控制参数定义
var ANYCHAT_SCREENSOURCE_FLAGS_DISABLECURSOR  =   0x01;                // 禁止采集鼠标光标
var ANYCHAT_SCREENSOURCE_FLAGS_DISABLEBORDER  =   0x02;                // 禁止边框显示
var ANYCHAT_SCREENSOURCE_FLAGS_DISABLETRACE   =   0x04;                // 禁止鼠标追踪

//回调MessageType 定义
var JAVASCRIPT_CALLBACK_ANYCHATCORESDKEVENT	="OnAnyChatCoreSDKEvent";
var JAVASCRIPT_CALLBACK_NOTIFYMESSAGE		="OnNotifyMessage";
var JAVASCRIPT_CALLBACK_TEXTMESSAGE			="OnTextMessage";
var JAVASCRIPT_CALLBACK_TRANSBUFFER			="OnTransBuffer";
var JAVASCRIPT_CALLBACK_TRANSBUFFEREX		="OnTransBufferEx";
var JAVASCRIPT_CALLBACK_TRANSFILE			="OnTransFile";
var JAVASCRIPT_CALLBACK_VOLUMECHANGE		="OnVolumeChange";
var JAVASCRIPT_CALLBACK_SDKFILTERDATA		="OnSDKFilterData";
var JAVASCRIPT_CALLBACK_RECORDSNAPSHOT		="OnRecordSnapShot";
var JAVASCRIPT_CALLBACK_RECORDSNAPSHOTEX	="OnRecordSnapShotEx";
var JAVASCRIPT_CALLBACK_RECORDSNAPSHOTEX2	="OnRecordSnapShotEx2";
var JAVASCRIPT_CALLBACK_VIDEOCALLEVENT		="OnVideoCallEvent";
var JAVASCRIPT_CALLBACK_OBJECTEVENT			="OnObjectEvent";

// 插件最低需求版本号
var MIN_ANYCHAT_PLUGIN_VER	=	"1.0.0.6";
var MIN_VIDEO_PLUGIN_VER	=	"1.0.0.4";
var CUR_ANYCHAT_PLUGIN_VAR = "";

/********************************************
 *				方法定义部分				*
 *******************************************/
var anychat = null;								// AnyChat插件DMO对象，外部初始化
var bSupportStreamRecordCtrlEx = false;			// 是否支持录像扩展API接口
var bSupportObjectBusiness = false;				// 是否支持业务对象API接口
var bSupportMultiStream = false;				// 是否支持多路流（多摄像头）API接口
var bSupportScriptObject = false;				// 是否支持JavaScript对象
var bSupportCluster = false;					// 是否支持集群系统
var bSupportParamBase64 = false;				// 是否支持参数base64加密
var base64TranFuc = new Base64();
var msgtimer=null;								//定时器实例
function MessageLoop() {
	var msg = BRAC_GetMessage();
	if (msg.length != 0) {
		var jsonmsg = JSON.parse(msg);
		switch (jsonmsg.MessageType) {
			case JAVASCRIPT_CALLBACK_ANYCHATCORESDKEVENT:
				if(typeof(OnAnyChatKernelCoreSDKEvent) == "function")
					OnAnyChatKernelCoreSDKEvent(jsonmsg.MessageData.dwEventType, jsonmsg.MessageData.lpEventJsonStr);
				break;
			case JAVASCRIPT_CALLBACK_NOTIFYMESSAGE:
				if(typeof(OnAnyChatNotifyMessage) == "function")
					OnAnyChatNotifyMessage(jsonmsg.MessageData.dwNotifyMsg, jsonmsg.MessageData.wParam, jsonmsg.MessageData.lParam);
				break;
			case JAVASCRIPT_CALLBACK_TEXTMESSAGE:
				if(typeof(OnAnyChatKernelTextMessage) == "function")
					OnAnyChatKernelTextMessage(jsonmsg.MessageData.dwFromUserid, jsonmsg.MessageData.dwToUserid, jsonmsg.MessageData.bSecret, jsonmsg.MessageData.lpMsgBuf, jsonmsg.MessageData.dwLen);
				break;
			case JAVASCRIPT_CALLBACK_TRANSBUFFER:
				if(typeof(OnAnyChatTransBuffer) == "function")
				{
					var lpbuf = base64TranFuc.decode(jsonmsg.MessageData.lpBuf)
					OnAnyChatTransBuffer(jsonmsg.MessageData.dwUserid, lpbuf, lpbuf.length);
				}
				break;
			case JAVASCRIPT_CALLBACK_TRANSBUFFEREX:
				if(typeof(OnAnyChatTransBufferEx) == "function")
				{
					var lpbuf = base64TranFuc.decode(jsonmsg.MessageData.lpBuf)
					OnAnyChatTransBufferEx(jsonmsg.MessageData.dwUserid, lpbuf, lpbuf.length, jsonmsg.MessageData.wParam, jsonmsg.MessageData.lParam, jsonmsg.MessageData.dwTaskId);
				}
				break;
			case JAVASCRIPT_CALLBACK_TRANSFILE:
				if(typeof(OnAnyChatTransFile) == "function")
					OnAnyChatTransFile(jsonmsg.MessageData.dwUserid, jsonmsg.MessageData.lpFileName, jsonmsg.MessageData.lpTempFilePath, jsonmsg.MessageData.dwFileLength, jsonmsg.MessageData.wParam, jsonmsg.MessageData.lParam, jsonmsg.MessageData.dwTaskId);
				break;
			case JAVASCRIPT_CALLBACK_VOLUMECHANGE:
				if(typeof(OnAnyChatVolumeChange) == "function")
					OnAnyChatVolumeChange(jsonmsg.MessageData.device, jsonmsg.MessageData.dwCurrentVolume);
				break;
			case JAVASCRIPT_CALLBACK_SDKFILTERDATA:
				if(typeof(OnAnyChatSDKFilterData) == "function")
					OnAnyChatSDKFilterData(jsonmsg.MessageData.dwEventType, jsonmsg.MessageData.lpEventJsonStr);
				break;
			case JAVASCRIPT_CALLBACK_RECORDSNAPSHOT:
				if(typeof(OnAnyChatRecordSnapShot) == "function")
					OnAnyChatRecordSnapShot(jsonmsg.MessageData.dwUserId, jsonmsg.MessageData.lpFileName, jsonmsg.MessageData.dwParam, jsonmsg.MessageData.dwFlags);
				break;
			case JAVASCRIPT_CALLBACK_RECORDSNAPSHOTEX:
				if(typeof(OnAnyChatKernelRecordSnapShotEx) == "function")
					OnAnyChatKernelRecordSnapShotEx(jsonmsg.MessageData.dwUserId, jsonmsg.MessageData.lpFileName, jsonmsg.MessageData.dwElapse, jsonmsg.MessageData.dwFlags, jsonmsg.MessageData.dwParam, jsonmsg.MessageData.lpUserStr);
				break;
			case JAVASCRIPT_CALLBACK_RECORDSNAPSHOTEX2:
				if(typeof(OnAnyChatKernelRecordSnapShotEx2) == "function")
					OnAnyChatKernelRecordSnapShotEx2(jsonmsg.MessageData.dwUserId,jsonmsg.MessageData.dwErrorCode, jsonmsg.MessageData.lpFileName, jsonmsg.MessageData.dwElapse, jsonmsg.MessageData.dwFlags, jsonmsg.MessageData.dwParam, jsonmsg.MessageData.lpUserStr);
				break;
			case JAVASCRIPT_CALLBACK_VIDEOCALLEVENT:
				if(typeof(OnAnyChatKernelVideoCallEvent) == "function")
					OnAnyChatKernelVideoCallEvent(jsonmsg.MessageData.dwEventType, jsonmsg.MessageData.dwUserId, jsonmsg.MessageData.dwErrorCode, jsonmsg.MessageData.dwFlags, jsonmsg.MessageData.dwParam, jsonmsg.MessageData.lpUserStr);
				break;
			case JAVASCRIPT_CALLBACK_OBJECTEVENT:
				if(typeof(OnAnyChatObjectEvent) == "function")	
					OnAnyChatObjectEvent(jsonmsg.MessageData.dwObjectType, jsonmsg.MessageData.dwObjectId, jsonmsg.MessageData.dwEventType, jsonmsg.MessageData.dwParam1, jsonmsg.MessageData.dwParam2, jsonmsg.MessageData.dwParam3, jsonmsg.MessageData.dwParam4, jsonmsg.MessageData.lpStrParam);
				break;
			default:
				break;
		}
	}
}
function starttimer(){
    MessageLoop();
    msgtimer=setTimeout("starttimer()",200);    
}
// 初始化SDK，返回出错代码
function BRAC_InitSDK(apilevel) {	
	var anychatsdkdiv = "AnyChatSDKPluginDiv";
	try {
		// 创建AnyChat SDK插件
		var anychatobj = document.createElement("object")
	    if (window.ActiveXObject  || "ActiveXObject" in window)
	        anychatobj.classid = "clsid:91CC58C4-BA8A-400D-A176-856EDF42CB57";
	    else
	        anychatobj.type = "application/anychat-plugin";
		anychatobj.id = "AnyChatSDKPlugin";
		
	    // 创建视频显示插件
	    var videoobj = document.createElement("object")

	    if (window.ActiveXObject || "ActiveXObject" in window)
	        videoobj.classid = "clsid:B685A393-905F-45B5-B26E-FF199EEE2FD7";
	    else
	        videoobj.type = "application/anychat-video";
		videoobj.id = "AnyChatVideoPlugin";		
	    // 创建一个测试层
	    var insertdiv = document.createElement("div");
	    insertdiv.id = anychatsdkdiv;
		insertdiv.appendChild(anychatobj);
	    insertdiv.appendChild(videoobj);
	    document.body.appendChild(insertdiv);
		anychatobj.width = "1 px";
		anychatobj.height = "1 px";
	    // 测试插件是否安装
	    CUR_ANYCHAT_PLUGIN_VAR = anychatobj.GetVersion(0);
	    var videopluginver = videoobj.GetVersion(0);
	    // 判断插件的版本是否太旧
	    var bRightVersion = ((CUR_ANYCHAT_PLUGIN_VAR >= MIN_ANYCHAT_PLUGIN_VER) && (videopluginver >= MIN_VIDEO_PLUGIN_VER));
		// 判断插件是否支持录像扩展API接口
		bSupportStreamRecordCtrlEx = (CUR_ANYCHAT_PLUGIN_VAR >= "1.0.1.0");
		// 判断插件是否支持业务对象API接口
		bSupportObjectBusiness = (CUR_ANYCHAT_PLUGIN_VAR >= "1.0.2.3");
		// 判断插件是否支持多路流API接口
		bSupportMultiStream = (CUR_ANYCHAT_PLUGIN_VAR >= "1.0.3.1");
		// 判断插件是否支持集群系统
		bSupportCluster = (CUR_ANYCHAT_PLUGIN_VAR >= "1.0.4.0");
		// 判断当前的API Level是否满足业务层的需要
		if(apilevel > anychatobj.GetVersion(2))
			bRightVersion = false;
		if(bRightVersion) {
			insertdiv.removeChild(videoobj);
			anychat = anychatobj;
			// 关联回调事件
			if(typeof(OnAnyChatNotifyMessage) == "function")
				BRAC_RegisterCallBack(anychat, 'OnNotifyMessage', 	OnAnyChatNotifyMessage);
			if(typeof(OnAnyChatTextMessage) == "function")
				BRAC_RegisterCallBack(anychat, 'OnTextMessage', 	OnAnyChatKernelTextMessage);
			if(typeof(OnAnyChatTransBuffer) == "function")
				BRAC_RegisterCallBack(anychat, 'OnTransBuffer', 	OnAnyChatTransBuffer);
			if(typeof(OnAnyChatTransBufferEx) == "function")
				BRAC_RegisterCallBack(anychat, 'OnTransBufferEx', 	OnAnyChatTransBufferEx);
			if(typeof(OnAnyChatTransFile) == "function")
				BRAC_RegisterCallBack(anychat, 'OnTransFile', 		OnAnyChatTransFile);
			if(typeof(OnAnyChatVolumeChange) == "function")
				BRAC_RegisterCallBack(anychat, 'OnVolumeChange', 	OnAnyChatVolumeChange);
			if(typeof(OnAnyChatSDKFilterData) == "function")
				BRAC_RegisterCallBack(anychat, 'OnSDKFilterData', 	OnAnyChatSDKFilterData);
			if(typeof(OnAnyChatVideoCallEvent) == "function")
				BRAC_RegisterCallBack(anychat, 'OnVideoCallEvent', 	OnAnyChatKernelVideoCallEvent);
			if(typeof(OnAnyChatRecordSnapShot) == "function")
				BRAC_RegisterCallBack(anychat, 'OnRecordSnapShot', 	OnAnyChatRecordSnapShot);
			if(typeof(OnAnyChatRecordSnapShotEx) == "function" && bSupportStreamRecordCtrlEx)
				BRAC_RegisterCallBack(anychat, 'OnRecordSnapShotEx', OnAnyChatKernelRecordSnapShotEx);
			if(typeof(OnAnyChatRecordSnapShotEx2) == "function" && bSupportCluster)
				BRAC_RegisterCallBack(anychat, 'OnRecordSnapShotEx2', OnAnyChatKernelRecordSnapShotEx2);
			if(typeof(OnAnyChatObjectEvent) == "function" && bSupportObjectBusiness)
				BRAC_RegisterCallBack(anychat, 'OnObjectEvent', OnAnyChatObjectEvent);
			if(typeof(OnAnyChatCoreSDKEvent) == "function" && CUR_ANYCHAT_PLUGIN_VAR >= "1.0.6.0")
				BRAC_RegisterCallBack(anychat, 'OnAnyChatCoreSDKEvent', OnAnyChatKernelCoreSDKEvent);	
		} else {
			document.body.removeChild(insertdiv);
		}
		// 判断是否支持base64参数加密
		var base64Flag = BRAC_SetSDKOption(ANYCHATWEB_SO_STRBASE64MODE,1)
		if(base64Flag == 0 && BRAC_GetSDKOptionInt(ANYCHATWEB_SO_STRBASE64MODE) == 1)
			bSupportParamBase64 = true;
		return bRightVersion ? GV_ERR_SUCCESS : GV_ERR_PLUGINOLDVERSION;
	}
	catch (e) {
	    var insertdiv = BRAC_GetDmoObject(anychatsdkdiv);
	    if (insertdiv)
	        document.body.removeChild(insertdiv);
	    return GV_ERR_PLUGINNOINSTALL;
	}
}
//视频呼叫
function OnAnyChatKernelVideoCallEvent(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr){
	szUserStr = bSupportParamBase64?base64TranFuc.decode(szUserStr):szUserStr;
	OnAnyChatVideoCallEvent(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr)
}
//业务缓冲区（业务透明通道）
function OnAnyChatKernelCoreSDKEvent(dwEventType,lpEventJsonStr){
	lpEventJsonStr = (dwEventType==ANYCHAT_SDKCTRL_BUSINESSBUFFER && bSupportParamBase64)?base64TranFuc.decode(lpEventJsonStr):lpEventJsonStr;
	OnAnyChatCoreSDKEvent(dwEventType,lpEventJsonStr)
}
//录制回调
function OnAnyChatKernelRecordSnapShotEx(dwUserId, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr){
	lpUserStr = bSupportParamBase64?base64TranFuc.decode(lpUserStr):lpUserStr;
	OnAnyChatRecordSnapShotEx(dwUserId, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr)
}
//收到房间消息回调
function OnAnyChatKernelTextMessage (dwFromUserId, dwToUserId, bSecret, lpMsgBuf, dwLen){
	lpMsgBuf = bSupportParamBase64?base64TranFuc.decode(lpMsgBuf):lpMsgBuf;
	OnAnyChatTextMessage(dwFromUserId, dwToUserId, bSecret, lpMsgBuf, dwLen)
}
//录制回调
function OnAnyChatKernelRecordSnapShotEx2(dwUserId, dwErrorCode, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr){
	lpUserStr = bSupportParamBase64?base64TranFuc.decode(lpUserStr):lpUserStr;
	OnAnyChatRecordSnapShotEx2(dwUserId, dwErrorCode, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr)
}

// 注册回调事件
function BRAC_RegisterCallBack(obj, name, proc) {
	if(typeof(proc) != "function")
		return;
	if(window.ActiveXObject || "ActiveXObject" in window) {
		if(window.ActiveXObject && obj.attachEvent) {
			obj.attachEvent(name, proc);
		} else {
			BRAC_AttachIE11Event(obj, name, proc);
		}
	} else {
		obj[name] = proc;
	}
}

// 生成GUID
function BRAC_NewGuid() {
	return BRAC_GetSDKOptionString(BRAC_SO_CORESDK_NEWGUID);
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

function BRAC_AttachIE11Event(obj, _strEventId, _functionCallback) {
	var nameFromToStringRegex = /^function\s?([^\s(]*)/;
	var paramsFromToStringRegex = /\(\)|\(.+\)/;
	var params = _functionCallback.toString().match(paramsFromToStringRegex)[0];
	var functionName = _functionCallback.name || _functionCallback.toString().match(nameFromToStringRegex)[1];
	var handler;
	try {
		handler = document.createElement("script");
		handler.setAttribute("for", obj.id);
	} catch(ex) {
		handler = document.createElement('<script for="' + obj.id + '">');
	}
	handler.event = _strEventId + params;
	handler.appendChild(document.createTextNode(functionName + params + ";"));
	document.body.appendChild(handler);
}

// 创建视频显示插件
function BRAC_NativeCreateVideoPlugin(userid, parentobj, id, streamindex) {
	try{
		var videoobj = BRAC_GetDmoObject(id);
		if(videoobj != null) {
			videoobj.SetIPCGuid(BRAC_GetIPCGuid());
			videoobj.SetUserId(userid);
			if(bSupportMultiStream)
				videoobj.SetStreamIndex(streamindex);
		} else {
			// 创建视频显示插件
			videoobj = document.createElement("object")
			if (window.ActiveXObject || "ActiveXObject" in window)
				videoobj.classid = "clsid:B685A393-905F-45B5-B26E-FF199EEE2FD7";
			else
				videoobj.type = "application/anychat-video";
			videoobj.id = id;
			parentobj.appendChild(videoobj);
			videoobj.width = "100%";
			videoobj.height = "100%";
			// 关联到AnyChat SDK
			videoobj.SetIPCGuid(BRAC_GetIPCGuid());
			videoobj.SetUserId(userid);
			if(bSupportMultiStream)
				videoobj.SetStreamIndex(streamindex);
		}			
	}catch(e){
		console.log("CreateVideoPlugin function has exception：" + e);
	}
}

// 设置视频显示位置
function BRAC_SetVideoPos(userid, parentobj, id) {
	if(bSupportScriptObject)
		return anychat.SetVideoPos(userid, parentobj, id);
	else
		return BRAC_NativeCreateVideoPlugin(userid, parentobj, id, 0);
}

// 设置视频显示位置（扩展，支持多路流）
function BRAC_SetVideoPosEx(userid, parentobj, id, streamindex) {
	return BRAC_NativeCreateVideoPlugin(userid, parentobj, id, streamindex);
}

// 获取版本号
function BRAC_GetVersion(type) {
	return anychat.GetVersion(type);
}
//获取消息
function BRAC_GetMessage(){
	return anychat.BRGetMessage();
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
	return anychat.Login(bSupportParamBase64?base64TranFuc.encode(lpUserName) : lpUserName, lpPassword, dwParam);
}
// 登录系统（扩展）
function BRAC_LoginEx(lpNickName, dwUserId, lpStrUserId, lpAppId, dwTimeStamp, lpSigStr, lpStrParam) {
	if(!bSupportCluster)
		return GV_ERR_PLUGINOLDVERSION;
		return anychat.LoginEx(bSupportParamBase64?base64TranFuc.encode(lpNickName) : lpNickName, parseInt(dwUserId),lpStrUserId, lpAppId, parseInt(dwTimeStamp), lpSigStr, bSupportParamBase64?base64TranFuc.encode(lpStrParam) : lpStrParam);
}
// 进入房间
function BRAC_EnterRoom(dwRoomid, lpRoomPass, dwParam) {
	return anychat.EnterRoom(parseInt(dwRoomid), lpRoomPass, dwParam);
}
// 进入房间
function BRAC_EnterRoomEx(lpRoomName, lpRoomPass) {
	return anychat.EnterRoomEx(lpRoomName, lpRoomPass);
}
// 离开房间
function BRAC_LeaveRoom(dwRoomid) {
	return anychat.LeaveRoom(parseInt(dwRoomid));
}
// 注销系统
function BRAC_Logout() {
	return anychat.Logout();
}

// 获取当前房间在线用户列表（返回一个userid的数组）
function BRAC_GetOnlineUser() {
	if(bSupportScriptObject) {
		return anychat.GetRoomOnlineUsers(-1);
	}
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

// 获取指定房间在线用户列表（返回一个userid的数组）
function BRAC_GetRoomOnlineUsers(dwRoomId) {
	if(bSupportScriptObject) {
		return anychat.GetRoomOnlineUsers(dwRoomId);
	}
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
	return bSupportParamBase64?base64TranFuc.decode(anychat.QueryUserStateString(dwUserId, BRAC_USERSTATE_NICKNAME)) : anychat.QueryUserStateString(dwUserId, BRAC_USERSTATE_NICKNAME);
}
// 查询指定用户相关状态（整型值状态）
function BRAC_QueryUserStateInt(dwUserId, infoname) {
	return anychat.QueryUserStateInt(dwUserId, infoname);
}
// 查询指定用户相关状态（字符串值状态）
function BRAC_QueryUserStateString(dwUserId, infoname) {
	return bSupportParamBase64?base64TranFuc.decode(anychat.QueryUserStateString(dwUserId, infoname)) : anychat.QueryUserStateString(dwUserId, infoname);
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

// 操作本地用户视频扩展（或请求远程用户视频）
function BRAC_UserCameraControlEx(dwUserId, bOpen, dwStreamIndex, dwFlags, szStrParam) {
	if(bSupportMultiStream)
		return anychat.UserCameraControlEx(dwUserId, bOpen, dwStreamIndex, dwFlags, szStrParam);
	else if(dwStreamIndex == 0)
		return anychat.UserCameraControl(dwUserId, bOpen);
	else
		return -1;
}

// 操作本地用户语音（或请求远程用户语音）
function BRAC_UserSpeakControl(dwUserId, bOpen) {
	return anychat.UserSpeakControl(dwUserId, bOpen);
}

// 操作本地用户语音扩展（或请求远程用户语音）
function BRAC_UserSpeakControlEx(dwUserId, bOpen, dwStreamIndex, dwFlags, szStrParam) {
	if(bSupportMultiStream)
		return anychat.UserSpeakControlEx(dwUserId, bOpen, dwStreamIndex, dwFlags, szStrParam);
	else if(dwStreamIndex == 0)
		return anychat.UserSpeakControl(dwUserId, bOpen);
	else
		return -1;
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
// 用户音、视频录制（扩展）
function BRAC_StreamRecordCtrlEx(dwUserId, bStartRecord, dwFlags, dwParam, lpUserStr) {
	if(bSupportStreamRecordCtrlEx)
		return anychat.StreamRecordCtrlEx(dwUserId, bStartRecord, dwFlags, dwParam, bSupportParamBase64?base64TranFuc.encode(lpUserStr):lpUserStr );
	else
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
	return anychat.TransBufferEx(dwUserId, lpBuf, wParam, lParam, dwFlags);
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
	return anychat.SendTextMessage(dwUserId, bSecret, bSupportParamBase64?base64TranFuc.encode(lpMsgBuf) : lpMsgBuf, 0);
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
	if (typeof value == "string")
		return anychat.SetSDKOptionString(optname, value);
	else {
		if (ANYCHATWEB_SO_ACTIVEMSG == optname) {
			if (value == 1) {
				if (BRAC_GetSDKOptionInt(ANYCHATWEB_SO_SUPPORTACTIVEMSG)) {
					msgtimer && clearTimeout(msgtimer);
					msgtimer = null;
					setTimeout("starttimer()", 20);
				}
			} else {
				msgtimer&&clearTimeout(msgtimer);
				msgtimer=null;
			}

		}
		return anychat.SetSDKOptionInt(optname, value);
	}
	
}
// SDK内核参数状态查询（整形参数值）
function BRAC_GetSDKOptionInt(optname) {
	return anychat.GetSDKOptionInt(optname);
}
// SDK内核参数状态查询（字符串参数值）
function BRAC_GetSDKOptionString(optname) {
	return anychat.GetSDKOptionString(optname);
}
// SDK内核参数状态查询（字符串参数值，扩展）
function BRAC_GetSDKOptionStringEx(optname, strValue, dwFlags) {
	return anychat.GetSDKOptionStringEx(optname, strValue, dwFlags);
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
	return anychat.VideoCallControl(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, bSupportParamBase64?base64TranFuc.encode(szUserStr):szUserStr);
}

// 获取用户好友ID列表（返回一个userid的数组）
function BRAC_GetUserFriends() {
	if(bSupportScriptObject) {
		return anychat.GetUserFriends();
	}
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
	if(bSupportScriptObject) {
		return anychat.GetUserGroups();
	}
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
	if(bSupportScriptObject) {
		return anychat.GetGroupFriends(dwGroupId);
	}
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

// 获取业务对象ID列表（返回一个ObjectId的数组）
function BRAC_ObjectGetIdList(dwObjectType) {
	if(bSupportScriptObject) {
		return anychat.ObjectGetIdList(dwObjectType);
	}
	var idarray = new Array();
	if(!bSupportObjectBusiness)
		return idarray;
	var size = anychat.PrepareFetchObjectIds(dwObjectType);
	if(size) {
		var idx = 0;
		while(1) {
			var objectid = anychat.FetchNextObjectId(dwObjectType);
			if(objectid == -1)
				break;
			idarray[idx++] = objectid;
		}
	}
	return idarray;
}

// 获取业务对象参数值（整形值）
function BRAC_ObjectGetIntValue(dwObjectType, dwObjectId, dwInfoName) {
	if(!bSupportObjectBusiness)
		return -1;
	return anychat.GetObjectIntValue(dwObjectType, dwObjectId, dwInfoName);
}

// 获取业务对象参数值（字符串）
function BRAC_ObjectGetStringValue(dwObjectType, dwObjectId, dwInfoName) {
	if(!bSupportObjectBusiness)
		return -1;
	return bSupportParamBase64?base64TranFuc.decode(anychat.GetObjectStringValue(dwObjectType, dwObjectId, dwInfoName)) : anychat.GetObjectStringValue(dwObjectType, dwObjectId, dwInfoName);
}

// 设置业务对象参数值
function BRAC_ObjectSetValue(dwObjectType, dwObjectId, dwInfoName, value) {
	if(!bSupportObjectBusiness)
		return -1;
	if(typeof value == "string")
		return anychat.SetObjectStringValue(dwObjectType, dwObjectId, dwInfoName, bSupportParamBase64?base64TranFuc.encode(value) :value);
	else
		return anychat.SetObjectIntValue(dwObjectType, dwObjectId, dwInfoName, value);
}

// 业务对象控制指令
function BRAC_ObjectControl(dwObjectType, dwObjectId, dwCtrlCode, dwParam1, dwParam2, dwParam3, dwParam4, strParam) {
	if(!bSupportObjectBusiness)
		return -1;
	return anychat.ObjectControl(dwObjectType, dwObjectId, dwCtrlCode, dwParam1, dwParam2, dwParam3, dwParam4, strParam);
}

// 设置指定用户音视频流相关参数（主要针对本地用户）
function BRAC_SetUserStreamInfo(dwUserId, dwStreamIndex, infoname, value) {
	if(!bSupportMultiStream)
		return -1;
	if(typeof value == "string")
		return anychat.SetUserStreamInfoString(dwUserId, dwStreamIndex, infoname, value);
	else
		return anychat.SetUserStreamInfoInt(dwUserId, dwStreamIndex, infoname, value);
}

// 获取指定用户音视频流相关参数（整形参数值）
function BRAC_GetUserStreamInfoInt(dwUserId, dwStreamIndex, infoname) {
	if(!bSupportMultiStream)
		return 0;
	return anychat.GetUserStreamInfoInt(dwUserId, dwStreamIndex, infoname);
}

// 获取指定用户音视频流相关参数（字符串参数值）
function BRAC_GetUserStreamInfoString(dwUserId, dwStreamIndex, infoname) {
	if(!bSupportMultiStream)
		return "";
	return anychat.GetUserStreamInfoString(dwUserId, dwStreamIndex, infoname);
}

// 向服务器动态查询相关信息
function BRAC_QueryInfoFromServer(dwInfoName, lpInParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.5.0")
		return "";
		return bSupportParamBase64?base64TranFuc.decode(anychat.QueryInfoFromServer(dwInfoName, lpInParam)) : anychat.QueryInfoFromServer(dwInfoName, lpInParam);
}

// SDK控制
function BRAC_SDKControl(dwCtrlCode, lpInParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.7.0")
		return JSON.stringify({"errorcode":32});
	return anychat.SDKControl(dwCtrlCode, (dwCtrlCode==ANYCHAT_SDKCTRL_BUSINESSBUFFER && bSupportParamBase64)?base64TranFuc.encode(lpInParam):lpInParam);
}

// 文件传输扩展接口
function BRAC_TransFileEx(lpTaskGuid, dwUserId, lpLocalPathName, dwFlags, lpStrParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.TransFileEx(lpTaskGuid, dwUserId, lpLocalPathName, dwFlags, lpStrParam);
}

// 传输任务查询扩展接口
function BRAC_QueryTransTaskInfoEx(lpTaskGuid, dwInfoName) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.QueryTransTaskInfoEx(lpTaskGuid, dwInfoName);
}

// 取消传输任务扩展接口
function BRAC_CancelTransTaskEx(lpTaskGuid, dwFlags, dwErrorCode) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.CancelTransTaskEx(lpTaskGuid, dwFlags, dwErrorCode);
}

// 流媒体播放初始化
function BRAC_StreamPlayInit(lpTaskGuid, lpStreamPath, dwFlags, lpStrParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.StreamPlayInit(lpTaskGuid, lpStreamPath, dwFlags, lpStrParam);
}

// 流媒体播放控制
function BRAC_StreamPlayControl(lpTaskGuid, dwCtrlCode, dwParam, dwFlags, lpStrParam) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.StreamPlayControl(lpTaskGuid, dwCtrlCode, dwParam, dwFlags, lpStrParam);
}

// 设置流媒体播放视频显示位置
function BRAC_StreamPlaySetVideoPos(lpTaskGuid, parentobj, id) {
	try {
		BRAC_NativeCreateVideoPlugin(0, parentobj, id, 0);
		BRAC_GetDmoObject(id).SetSDKOptionString(ANYCHATWEB_VIDEO_SO_PLAYTASKGUID, lpTaskGuid);
	} catch(ex) {
		
	}
}

// 流媒体播放获取参数信息
function BRAC_StreamPlayGetInfo(lpTaskGuid, dwInfoName) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return "";
	return anychat.StreamPlayGetInfo(lpTaskGuid, dwInfoName);
}

// 流媒体播放释放资源
function BRAC_StreamPlayDestroy(lpTaskGuid, dwFlags) {
	if(CUR_ANYCHAT_PLUGIN_VAR < "1.0.6.0")
		return 0;
	return anychat.StreamPlayDestroy(lpTaskGuid, dwFlags);
}

// 释放插件
function BRAC_Release() {
	var _anychatSDKDiv = BRAC_GetDmoObject("AnyChatSDKPluginDiv");
	if (_anychatSDKDiv) {
		if (getBrowser() == "IE") {
			anychat = null;
			_anychatSDKDiv.parentNode.removeChild(_anychatSDKDiv);
			_anychatSDKDiv = null;
			var objectPlugins = document.getElementsByTagName("object");
			while (objectPlugins.length > 0 &&
				objectPlugins[0].classid == "clsid:B685A393-905F-45B5-B26E-FF199EEE2FD7") {
				objectPlugins[0].parentNode.removeChild(objectPlugins[0]);
			}
			setTimeout(CollectGarbage, 1);
			return;
		}
		document.body.removeChild(_anychatSDKDiv);
		msgtimer&&clearTimeout(msgtimer);
		msgtimer=null;
	}
}

// 获取当前浏览器
function getBrowser(){
	var browser = "unknown browser";	
	var ua = navigator.userAgent.toLowerCase();
	
	var info = {
		ie: /msie/.test(ua) && !/opera/.test(ua),
		op: !/msie/.test(ua) && /opera/.test(ua),
		sa: /version.*safari/.test(ua),
		ch: /chrome/.test(ua) && window.navigator.webkitPersistentStorage,
		ff: /firefox/.test(ua),
		qh360: /chrome/.test(ua) && !window.navigator.webkitPersistentStorage,
		qq: /qqbrowser/.test(ua),
        sg: /metasr/.test(ua)        
	};	
	
	if (info.ch){
		browser = "Chrome";
	}else if (info.ie || (!!window.ActiveXObject || "ActiveXObject" in window)){
		browser = "IE";
	}else if (info.ff){
		browser = "Firefox";
	}else if (info.sa){
		browser = "Safari";
	}else if (info.qh360){
		browser = "360浏览器";
	}else if (info.op){
		browser = "Opera";
	}else if (info.qq){
		browser = "QQ浏览器";
	}else if (info.sg){
		browser = "搜狗浏览器";
	}
	
	return browser;
}

function Base64() {
	    // private property  
	    _keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
	    // public method for encoding  
	    this.encode = function(input) {
	        var output = "";
	        var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
	        var i = 0;
	        input = _utf8_encode(input);
	        while (i < input.length) {
	            chr1 = input.charCodeAt(i++);
	            chr2 = input.charCodeAt(i++);
	            chr3 = input.charCodeAt(i++);
	            enc1 = chr1 >> 2;
	            enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
	            enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
	            enc4 = chr3 & 63;
	            if (isNaN(chr2)) {
	                enc3 = enc4 = 64;
	            } else if (isNaN(chr3)) {
	                enc4 = 64;
	            }
	            output = output +
	                _keyStr.charAt(enc1) + _keyStr.charAt(enc2) +
	                _keyStr.charAt(enc3) + _keyStr.charAt(enc4);
	        }
	        return output;
	    }
	    // public method for decoding  
	    this.decode = function(input) {
	        var output = "";
	        var chr1, chr2, chr3;
	        var enc1, enc2, enc3, enc4;
	        var i = 0;
	        input = input.replace(/[^A-Za-z0-9\+\/\=]/g, "");
	        while (i < input.length) {
	            enc1 = _keyStr.indexOf(input.charAt(i++));
	            enc2 = _keyStr.indexOf(input.charAt(i++));
	            enc3 = _keyStr.indexOf(input.charAt(i++));
	            enc4 = _keyStr.indexOf(input.charAt(i++));
	            chr1 = (enc1 << 2) | (enc2 >> 4);
	            chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
	            chr3 = ((enc3 & 3) << 6) | enc4;
	            output = output + String.fromCharCode(chr1);
	            if (enc3 != 64) {
	                output = output + String.fromCharCode(chr2);
	            }
	            if (enc4 != 64) {
	                output = output + String.fromCharCode(chr3);
	            }
	        }
	        output = _utf8_decode(output);
	        return output;
	    }
	    // private method for UTF-8 encoding  
	    _utf8_encode = function(string) {
	        string = string.replace(/\r\n/g, "\n");
	        var utftext = "";
	        for (var n = 0; n < string.length; n++) {
	            var c = string.charCodeAt(n);
	            if (c < 128) {
	                utftext += String.fromCharCode(c);
	            } else if ((c > 127) && (c < 2048)) {
	                utftext += String.fromCharCode((c >> 6) | 192);
	                utftext += String.fromCharCode((c & 63) | 128);
	            } else {
	                utftext += String.fromCharCode((c >> 12) | 224);
	                utftext += String.fromCharCode(((c >> 6) & 63) | 128);
	                utftext += String.fromCharCode((c & 63) | 128);
	            }

	        }
	        return utftext;
	    }
	    // private method for UTF-8 decoding  
	    _utf8_decode = function(utftext) {
	        var string = "";
	        var i = 0;
	        var c = c1 = c2 = 0;
	        while (i < utftext.length) {
	            c = utftext.charCodeAt(i);
	            if (c < 128) {
	                string += String.fromCharCode(c);
	                i++;
	            } else if ((c > 191) && (c < 224)) {
	                c2 = utftext.charCodeAt(i + 1);
	                string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));
	                i += 2;
	            } else {
	                c2 = utftext.charCodeAt(i + 1);
	                c3 = utftext.charCodeAt(i + 2);
	                string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
	                i += 3;
	            }
	        }
	        return string;
	    }
	}
