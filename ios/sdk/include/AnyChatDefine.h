#if !defined(_ANYCHAT_DEFINE_H__INCLUDE_)
#define _ANYCHAT_DEFINE_H__INCLUDE_

/**
 *	AnyChat SDK Client Const Define Include File
 */


// 视频图像格式定义
enum BRAC_PixelFormat{
	BRAC_PIX_FMT_RGB24 = 0,						///< Packed RGB 8:8:8, 24bpp, RGBRGB...（MEDIASUBTYPE_RGB24）
	BRAC_PIX_FMT_RGB32,							///< 对应于：MEDIASUBTYPE_RGB32，Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
	BRAC_PIX_FMT_YV12,							///< 对应于：MEDIASUBTYPE_YV12，Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	BRAC_PIX_FMT_YUY2,							///< 对应于：MEDIASUBTYPE_YUY2，Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
	BRAC_PIX_FMT_YUV420P,						///< Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	BRAC_PIX_FMT_RGB565,						///< 对应于：MEDIASUBTYPE_RGB565
	BRAC_PIX_FMT_RGB555,						///< 对应于：MEDIASUBTYPE_RGB555
	BRAC_PIX_FMT_NV12,							///< Planar YUV 4:2:0, 12bpp, Two arrays, one is all Y, the other is U and V
	BRAC_PIX_FMT_NV21,							///< Planar YUV 4:2:0, 12bpp, Two arrays, one is all Y, the other is V and U
	BRAC_PIX_FMT_NV16,							///< YUV422SP
	BRAC_PIX_FMT_BGR32,
	
	BRAC_PIX_FMT_MJPEG = 200,
	BRAC_PIX_FMT_H264,
};

// 音频设备定义
enum BRAC_AudioDevice{
	BRAC_AD_WAVEIN = 0,							///< 输入设备：Mic
	BRAC_AD_WAVEOUT,							///< 输出设备：Wave
};

// 视频显示驱动定义
enum BRAC_VideoShowDriver{
	BRAC_VSD_DEFAULT = 0,						///< 默认显示驱动
	BRAC_VSD_DIRECTSHOW,						///< DirectShow显示驱动
	BRAC_VSD_WINDOWSGDI,						///< Windows GDI驱动
};


// 功能模式定义（API：BRAC_InitSDK 传入参数）
#define BRAC_FUNC_VIDEO_CBDATA		0x00000001	///< 通过回调函数输出视频数据
#define BRAC_FUNC_VIDEO_AUTODISP	0x00000002	///< 由SDK包处理视频，将视频显示在指定的窗口上
#define BRAC_FUNC_AUDIO_CBDATA		0x00000004	///< 通过回调函数输出音频数据
#define BRAC_FUNC_AUDIO_AUTOPLAY	0x00000008	///< 由SDK包处理音频，直接播放
#define BRAC_FUNC_CONFIG_LOCALINI	0x00000010	///< 生成本地配置文件（AnyChatSDK.ini）
#define BRAC_FUNC_FIREWALL_OPEN		0x00000020	///< 允许SDK操作Windows防火墙，将当前应用程序加入防火墙访问列表（避免Windows提示用户是否阻止当前应用程序）
#define BRAC_FUNC_CHKDEPENDMODULE	0x00000040	///< 自动检查SDK所依赖的组件，并自动注册
#define BRAC_FUNC_AUDIO_VOLUMECALC	0x00000080	///< 由SDK自动计算语音的音量
#define BRAC_FUNC_AUDIO_AUTOVOLUME	0x00000100	///< 允许SDK自动控制Mic录音音量
#define BRAC_FUNC_NET_SUPPORTUPNP	0x00000200	///< 允许SDK打开用户网络中的UPNP设备，如果用户的路由器或是防火墙支持UPNP协议，则可提高P2P打洞的成功率
#define BRAC_FUNC_DISABLEDECODE		0x00000400	///< 禁止对收到的数据进行解码和播放，为了提高代理客户端的数据转发性能，可设置该标志，否则不能设置该标志
#define BRAC_FUNC_MAINTHREADCB		0x00000800	///< 主线程进行回调操作，默认是多线程环境下的数据回调
#define BRAC_FUNC_AUDIO_FORBIDCFGHW	0x00001000	///< 禁止修改音频硬件配置
#define BRAC_FUNC_CORE_FORBIDWINMSG	0x00002000	///< 禁止使用windows消息循环
#define BRAC_FUNC_AUDIO_LARGEBUFFER	0x00004000	///< 音频大缓冲区模式，适合音乐播放类应用
#define BRAC_FUNC_NET_LARGEDELAY	0x00010000	///< 网络高延迟模式，适用于卫星网络环境
#define BRAC_FUNC_DISABLEVIDEODEC	0x00020000	///< 禁止视频解码
#define BRAC_FUNC_DISABLEAUDIODEC	0x00040000	///< 禁止音频解码


// 内核参数定义（API：BRAC_SetSDKOption、BRAC_GetSDKOption 传入参数）
#define BRAC_SO_AUDIO_VADCTRL				1	///< 音频静音检测控制（参数为：int型：1打开，0关闭）
#define BRAC_SO_AUDIO_NSCTRL				2	///< 音频噪音抑制控制（参数为：int型：1打开，0关闭）
#define BRAC_SO_AUDIO_ECHOCTRL				3	///< 音频回音消除控制（参数为：int型：1打开，0关闭）
#define BRAC_SO_AUDIO_AGCCTRL				4	///< 音频自动增益控制（参数为：int型：1打开，0关闭）
#define BRAC_SO_AUDIO_CAPTUREMODE			5	///< 音频采集模式设置（参数为：int型：0 发言模式，1 放歌模式，2 卡拉OK模式，3 线路输入模式）
#define BRAC_SO_AUDIO_MICBOOST				6	///< 音频采集Mic增强控制（参数为：int型：0 取消，1 选中，2 设备不存在[查询时返回值]）
#define BRAC_SO_AUDIO_AUTOPARAM				7	///< 根据音频采集模式，自动选择合适的相关参数，包括编码器、采样参数、码率参数等（参数为int型：1 启用，0 关闭[默认]）
#define BRAC_SO_AUDIO_MONOBITRATE			8	///< 设置单声道模式下音频编码目标码率（参数为：int型，单位：bps）
#define BRAC_SO_AUDIO_STEREOBITRATE			9	///< 设置双声道模式下音频编码目标码率（参数为：int型，单位：bps）
#define BRAC_SO_AUDIO_PLAYDRVCTRL			70	///< 音频播放驱动选择（参数为：int型，0默认驱动， 1 DSound驱动， 2 WaveOut驱动， 3 Java播放[Android平台使用]）
#define BRAC_SO_AUDIO_CNGCTRL				71	///< 舒适噪音生成控制（参数为：int型：1打开，0关闭）
#define BRAC_SO_AUDIO_CODECID				72	///< 本地音频编码器ID设置（参数为int型，-1表示默认，如果设置的编码器ID不存在，则内核会采用默认的编码器）
#define BRAC_SO_AUDIO_SOFTVOLMODE			73	///< 设置软件音量模式控制（参数为int型，1打开[默认]，0关闭），使用软件音量模式，将不会改变系统的音量设置
#define BRAC_SO_AUDIO_RECORDDRVCTRL			74	///< 音频采集驱动控制（参数为int型，0默认驱动， 1 DSound驱动， 2 WaveIn驱动， 3 Java采集[Android平台使用]）
#define BRAC_SO_AUDIO_ECHODELAY				75	///< 音频回声消除延迟参数设置（参数为int型，单位：ms）
#define BRAC_SO_AUDIO_NSLEVEL				76	///< 音频噪音抑制水平参数设置（参数为int型，0 - 3，默认为2，值越大抑制水平越高，抑制噪音的能力越强）
#define BRAC_SO_AUDIO_CBCODEC				77	///< 音频数据回调编码器类型（参数为int型）
#define BRAC_SO_AUDIO_ECHOLEVEL				78	///< 音频回声消除水平参数设置（参数为int型，0 - 4，默认为4，值越大回声消除能力越强）
#define BRAC_SO_AUDIO_PLAYCAPTURE			79	///< 音频播放采集参数设置（参数为int型，0 关闭[默认]，1 开启）

#define BRAC_SO_RECORD_VIDEOBR				10	///< 录像视频码率设置（参数为：int型，单位：bps）
#define BRAC_SO_RECORD_AUDIOBR				11	///< 录像音频码率设置（参数为：int型，单位：bps）
#define BRAC_SO_RECORD_TMPDIR				12	///< 录像文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_SNAPSHOT_TMPDIR				13	///< 快照文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_RECORD_FILETYPE				140	///< 录制文件类型设置（参数为：int型， 0 MP4[默认], 1 WMV, 2 FLV, 3 MP3）
#define BRAC_SO_RECORD_WIDTH				141	///< 录制视频宽度设置（参数为：int型，如：320）
#define BRAC_SO_RECORD_HEIGHT				142	///< 录制文件高度设置（参数为：int型，如：240）
#define BRAC_SO_RECORD_FILENAMERULE			143	///< 录制文件名命名规则（参数为：int型）
#define BRAC_SO_RECORD_CLIPMODE				144	///< 录制视频裁剪模式（参数为：int型）
#define BRAC_SO_RECORD_DISABLEDATEDIR		145	///< 录制文件不按日期分目录保存，全部生成在指定文件夹中（参数为：int型， 0禁止[默认] 1 开启）
#define BRAC_SO_RECORD_INSERTIMAGE			146	///< 录制过程中插入图片，Json字符串参数

#define BRAC_SO_CORESDK_TMPDIR				14	///< 设置AnyChat Core SDK临时目录（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_CORESDK_MAGICADJUST			15	///< 内核调试参数
#define BRAC_SO_CORESDK_LOADCODEC			16	///< 加载外部编解码器（参数为字符串TCHAR类型，必须是完整的绝对路径，包含文件名，或包含文件名的绝对路径）
#define BRAC_SO_CORESDK_USEARMV6LIB			17	///< 强制使用ARMv6指令集的库，android平台使用（参数为：int型，1使用ARMv6指令集， 0内核自动判断[默认]）
#define BRAC_SO_CORESDK_USEHWCODEC			18	///< 使用平台内置硬件编解码器（参数为int型，0 不使用硬件编解码器[默认]  1 使用内置硬件编解码器）
#define BRAC_SO_CORESDK_REMOTEDEBUG			19	///< 远程调试（参数为int型，表示目标用户ID，复用参数长度为调试类型参数）

#define BRAC_SO_CORESDK_PATH				20	///< 设置AnyChat Core SDK相关组件路径（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_CORESDK_DUMPCOREINFO		21	///< 输出内核信息到日志文件中，便于分析故障原因（参数为：int型：1 输出）
#define BRAC_SO_CORESDK_MAINVERSION			22	///< 查询SDK主版本号号（参数为int型）
#define BRAC_SO_CORESDK_SUBVERSION			23	///< 查询SDK从版本号（参数为int型）
#define BRAC_SO_CORESDK_BUILDTIME			24	///< 查询SDK编译时间（参数为字符串TCHAR类型）
#define BRAC_SO_CORESDK_ACTIVESTATE			25	///< 应用程序活动状态控制（参数为int型， 1 应用程序处于活动状态， 0 应用程序处于非活动状态），适用于iPhone等设备程序可后台运行的场合
#define BRAC_SO_CORESDK_EXTVIDEOINPUT		26	///< 外部扩展视频输入控制（参数为int型， 0 关闭外部视频输入[默认]， 1 启用外部视频输入）
#define BRAC_SO_CORESDK_EXTAUDIOINPUT		27	///< 外部扩展音频输入控制（参数为int型， 0 关闭外部音频输入[默认]， 1 启用外部音频输入）
#define BRAC_SO_CORESDK_LOWDELAYCTRL		28	///< 低延迟模式控制（参数为int型，0 关闭低延迟模式[默认]， 1 启用低延迟模式）
#define BRAC_SO_CORESDK_NEWGUID				29	///< 产生新的GUID字符串

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
#define BRAC_SO_LOCALVIDEO_ROTATECTRL		94	///< 本地视频旋转控制（已失效，使用：BRAC_SO_LOCALVIDEO_CAMERAROTATION替代）
#define BRAC_SO_LOCALVIDEO_CAPDRIVER		95	///< 本地视频采集驱动设置（参数为int型，0表示自动选择[默认]， 1 Video4Linux, 2 DirectShow, 3 Java采集[Android平台使用]）
#define BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA	96	///< 修正视频采集颜色偏色（参数为int型，0表示关闭[默认]，1 开启）
#define BRAC_SO_LOCALVIDEO_ORIENTATION		97	///< 本地视频设备方向（参数为：int型，定义为常量：ANYCHAT_DEVICEORIENTATION_XXXX）
#define BRAC_SO_LOCALVIDEO_AUTOROTATION		98	///< 本地视频自动旋转控制（参数为int型， 0表示关闭， 1 开启[默认]，视频旋转时需要参考本地视频设备方向参数）
#define BRAC_SO_LOCALVIDEO_SURFACEROTATION	99	///< 设置本地视频预览显示旋转角度（参数为int型，角度）
#define BRAC_SO_LOCALVIDEO_CAMERAFACE		100	///< 本地摄像头方向（前置、后置）
#define BRAC_SO_LOCALVIDEO_CAMERAROTATION	101	///< 本地摄像头旋转角度
#define BRAC_SO_LOCALVIDEO_DEVICEROTATION	102	///< 设备旋转角度
#define BRAC_SO_LOCALVIDEO_DEVICEMODE		103	///< 设备类型
#define BRAC_SO_LOCALVIDEO_TVFORMAT			104	///< 视频采集制式设置（参数为：int型，定义为DirectShow::strmif.h::AnalogVideoStandard，默认为：AnalogVideo_PAL_B）
#define BRAC_SO_LOCALVIDEO_OVERLAYTIMESTAMP	105	///< 迭加时间戳到本地视频（参数为：int型， 0 不迭加[默认]， 1 迭加）
#define BRAC_SO_LOCALVIDEO_DEVICENAME		106	///< 本地视频采集设备名称，用于设置打开指定摄像头设备（参数为字符串类型）
#define BRAC_SO_LOCALVIDEO_CLIPMODE			107	///< 本地视频裁剪模式（参数为int型， 0 自动[默认]，禁止自动旋转时有效）
#define BRAC_SO_LOCALVIDEO_SCREENHWND		108	///< 屏幕采集窗口句柄
#define BRAC_SO_LOCALVIDEO_SCREENFLAGS		109	///< 屏幕采集标志（参数为int型）
#define BRAC_SO_LOCALVIDEO_VIRTUALBK		111 ///< 本地视频迭加虚拟背景（字符串类型，JSON格式，包括虚拟背景路径以及其它参数项，为NULL表示取消虚拟背景）
#define BRAC_SO_LOCALVIDEO_VIDEOCOLOR		112	///< 视频颜色控制（字符串类型，参数为JSON）

#define BRAC_SO_NETWORK_P2PPOLITIC			40	///< 本地网络P2P策略控制（参数为：int型：0 禁止本地P2P，1 服务器控制P2P[默认]，2 上层应用控制P2P连接，3 按需建立P2P连接）
#define BRAC_SO_NETWORK_P2PCONNECT			41	///< 尝试与指定用户建立P2P连接（参数为int型，表示目标用户ID），连接建立成功后，会通过消息反馈给上层应用，P2P控制策略=2时有效
#define BRAC_SO_NETWORK_P2PBREAK			42	///< 断开与指定用户的P2P连接（参数为int型，表示目标用户ID）[暂不支持，保留]
#define BRAC_SO_NETWORK_TCPSERVICEPORT		43	///< 设置本地TCP服务端口（参数为int型），连接服务器之前设置有效
#define BRAC_SO_NETWORK_UDPSERVICEPORT		44	///< 设置本地UDP服务端口（参数为int型），连接服务器之前设置有效
#define BRAC_SO_NETWORK_MULTICASTPOLITIC	45	///< 组播策略控制（参数为int型，定义为常量：BRAC_MCPOLITIC_XXXX）
#define BRAC_SO_NETWORK_TRANSBUFMAXBITRATE	46	///< 传输缓冲区、文件最大码率控制（参数为int型，0 不限制，以最快速率传输[默认]， 否则表示限制码率，单位为：bps）
#define BRAC_SO_NETWORK_AUTORECONNECT		47	///< 网络掉线自动重连功能控制（参数为int型，0 关闭， 1 开启[默认]）
#define BRAC_SO_NETWORK_MTUSIZE				48	///< 设置网络层MTU大小（参数为int型）
#define BRAC_SO_NETWORK_UDPSTATUS			49	///< UDP网络通信状态查询（参数为int型）
#define BRAC_SO_NETWORK_LARGEDELAY			53	///< 网络高延迟模式，适用于卫星网络环境（参数为int型）
#define BRAC_SO_NETWORK_IPV6DNS				54	///< IPv6域名解析控制（参数为int型，0 关闭， 1开启[默认]），传统网络（IPv4）下，禁用IPv6可提高域名解析速度

#define BRAC_SO_PROXY_FUNCTIONCTRL			50	///< 本地用户代理功能控制，（参数为：int型，1启动代理，0关闭代理[默认]）
#define BRAC_SO_PROXY_VIDEOCTRL				51	///< 本地用户代理视频控制，将本地视频变为指定用户的视频对外发布（参数为int型，表示其它用户的userid）
#define BRAC_SO_PROXY_AUDIOCTRL				52	///< 本地用户代理音频控制，将本地音频变为指定用户的音频对外发布（参数同BRAC_SO_PROXY_VIDEOCTRL）

#define BRAC_SO_STREAM_MAXBUFFERTIME		60	///< 最大流缓冲时间（参数为int型，单位：毫秒，取值范围：500 ~ 5000，默认：800），发言模式设置值，歌曲模式会自动增加一倍
#define BRAC_SO_STREAM_SMOOTHPLAYMODE		61	///< 平滑播放模式（参数为int型，0 关闭[默认], 1 打开），打开状态下遇到视频丢帧时会继续播放（可能出现马赛克），不会卡住

#define BRAC_SO_VIDEOSHOW_MODECTRL			80	///< 视频显示模式控制（参数为：int型，0 单画面显示，1 视频迭加显示）
#define BRAC_SO_VIDEOSHOW_SETPRIMARYUSER	81	///< 设置主显示用户编号（参数为：int型，用户ID号）
#define BRAC_SO_VIDEOSHOW_SETOVERLAYUSER	82	///< 设置迭加显示用户编号（参数为：int型，用户ID号）
#define BRAC_SO_VIDEOSHOW_DRIVERCTRL		83	///< 视频显示驱动控制（参数为：int型，0 默认驱动， 1 Windows DirectShow，2 Windows GDI，3 SDL, 4 Android2X, 5 Android Java）
#define BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER	84	///< 视频数据经过GPU直接渲染，将解码后的视频数据直接传输到GPU的物理地址（参数为：int型， 0 关闭[默认]， 1 打开），与硬件平台相关
#define BRAC_SO_VIDEOSHOW_AUTOROTATION		85	///< 远程视频显示自动旋转控制（参数为int型， 0表示关闭， 1 开启[默认]，视频旋转时需要参考本地视频设备方向参数）
#define BRAC_SO_VIDEOSHOW_CLIPMODE			86	///< 远程视频显示旋转裁剪模式（参数为int型， 0 自动[默认]）
#define BRAC_SO_VIDEOSHOW_CBPIXFMT			87	///< 视频数据回调格式（参数为int型）

#define BRAC_SO_CORESDK_TICKOUTUSER			110	///< 从服务器上踢掉指定用户（参数为int型，表示目标用户ID）

#define BRAC_SO_CORESDK_DEVICEMODE			130	///< 设备模式控制（局域网设备之间可以互相通信，不依赖服务器；参数为int型，0 关闭[默认]，1 开启）
#define BRAC_SO_CORESDK_SCREENCAMERACTRL	131	///< 桌面共享功能控制（参数为：int型， 0 关闭[默认]， 1 开启）
#define BRAC_SO_CORESDK_DATAENCRYPTION		132	///< 数据加密控制（参数为：int型， 0 关闭[默认]， 1 开启）
#define BRAC_SO_CORESDK_MEDIAUTILLIB		133	///< 获取brMediaUtil.dll的库加载句柄
#define BRAC_SO_CORESDK_UPLOADLOGINFO		134	///< 上传日志信息到服务器（参数为：int型，0 关闭[默认]， 1 开启）
#define BRAC_SO_CORESDK_WRITELOG			135	///< 写入调试信息到客户端日志文件中
#define BRAC_SO_CORESDK_NEWLOGFILE			136	///< 产生新的日志文件
#define BRAC_SO_CORESDK_SUPPORTSIP			137	///< 判断当前是否支持SIP通信
#define BRAC_SO_CORESDK_SUPPORTHTML5		138	///< 判断当前是否支持HTML5
#define BRAC_SO_CORESDK_DISABLELOGFILE		139	///< 禁止生成本地日志文件
#define BRAC_SO_CORESDK_SUPPORTVIDEOCODEC	210	///< 设置支持的视频编码器
#define BRAC_SO_CORESDK_SUPPORTAUDIOCODEC	211	///< 设置支持的音频编码器
#define BRAC_SO_CORESDK_DISABLEMEDIACONSUL	212	///< 禁止媒体协商
#define BRAC_SO_CORESDK_QUERYTIMEOUTTIME	213	///< 信息查询超时时间（参数为：int型，单位：ms，默认值1000）
#define BRAC_SO_CORESDK_REMOTEASSISTHWND	214	///< 远程协助窗口句柄
#define BRAC_SO_CORESDK_REMOTEASSISTXPOS	215	///< 远程协助窗口滚动条位置（X）
#define BRAC_SO_CORESDK_REMOTEASSISTYPOS	216	///< 远程协助窗口滚动条位置（Y）
#define BRAC_SO_CORESDK_FITTENCENTLIVE		217	///< 兼容腾讯视频直播SDK
#define BRAC_SO_CORESDK_DFCFLIVE			218
#define BRAC_SO_CORESDK_DISABLEDNSCONNECT	219	///< 屏蔽DNS寻址
#define BRAC_SO_CORESDK_LOGFILEROOTPATH		220	///< 日志文件保存根路径（日志重定向，参数为字符串，绝对路径）
#define BRAC_SO_CORESDK_LOGFILERULE			221	///< 客户端日志文件保存规则（参数为int型，0 自动覆盖[默认] 1 按日期保存，不覆盖）
#define BRAC_SO_CORESDK_FILEENCANDDEC		222	///< 文件加解密控制（参数为字符串类型，JSON格式）
#define BRAC_SO_CORESDK_PPTHELPERINIT		223	///< PPT播报环境初始化
#define BRAC_SO_CORESDK_PPTFILECTRL			224	///< PPT文件控制
#define BRAC_SO_CORESDK_CBMEDIASTREAM		225	///< 回调原始音视频流
#define BRAC_SO_CORESDK_CBVIDEOSTREAM		226	///< 回调原始视频流
#define BRAC_SO_CORESDK_CBAUDIOSTREAM		227 ///< 回调原始音频流
#define BRAC_SO_CORESDK_STREAMADAPTIVE		228	///< 流媒体自适应控制（参数为int型，0 关闭 1 开启[默认]）
#define BRAC_SO_CORESDK_MAXTRANSFILESIZE	229	///< 允许传输的最大文件大小（参数为int型，单位：MByte）
#define BRAC_SO_CORESDK_USESERVERTIME		230	///< 使用服务器时间戳（参数为int型，0 关闭[默认] 1 开启）
#define BRAC_SO_CORESDK_APPMONITORLIST		231	///< 应用程序列表，应用程序共享模块使用（参数为字符串）
#define BRAC_SO_CORESDK_SSLCERTCHAIN		232	///< SSL证书链
#define BRAC_SO_CORESDK_SETUSERAPPINFO		236	///< 设置用户APP信息
#define BRAC_SO_CORESDK_LASTERRORCODE		237	///< 获取最后的出错代码

#define BRAC_SO_UDPTRACE_MODE				160 ///< UDP数据包跟踪模式
#define BRAC_SO_UDPTRACE_PACKSIZE			161	///< UDP数据包跟踪的大小，单位：BYTE
#define BRAC_SO_UDPTRACE_BITRATE			162	///< UDP数据包跟踪的包速率，单位：bps
#define BRAC_SO_UDPTRACE_START				163	///< UDP数据包跟踪控制（参数为int型，1 启动， 0 停止）
#define BRAC_SO_UDPTRACE_LOCALRECVNUM		164 ///< UDP数据包跟踪本地接收包数量
#define BRAC_SO_UDPTRACE_SERVERRECVNUM		165	///< UDP数据包跟踪服务器接收包数量
#define BRAC_SO_UDPTRACE_SOURCESENDNUM		166	///< UDP数据包跟踪源发包数量
#define BRAC_SO_UDPTRACE_SENDUSERID			167	///< UDP数据包跟踪源用户ID
#define BRAC_SO_UDPTRACE_NETDELAY			168	///< UDP数据包网络延迟，单位：ms，-1表示未知

// 用户多媒体流参数定义（API：BRAC_GetUserStreamInfo 传入参数）
#define BRAC_STREAMINFO_VIDEOWIDTH			180 ///< 视频流宽度
#define BRAC_STREAMINFO_VIDEOHEIGHT			181	///< 视频流高度
#define BRAC_STREAMINFO_VIDEOFPS			182	///< 视频流帧率
#define BRAC_STREAMINFO_VIDEOBITRATE		183	///< 视频流码率，单位：bps
#define BRAC_STREAMINFO_VIDEOCODECID		184	///< 视频流编码器ID
#define BRAC_STREAMINFO_VIDEOPACKLOSSRATE	185	///< 视频流丢包率
#define BRAC_STREAMINFO_VIDEODEVICENAME		186	///< 视频采集设备名称
#define BRAC_STREAMINFO_AUDIOCHANNELS		190	///< 音频流通道数
#define BRAC_STREAMINFO_AUDIOSAMPLERATE		191	///< 音频流采样率
#define BRAC_STREAMINFO_AUDIOBITRATE		192	///< 音频流码率，单位：bps
#define BRAC_STREAMINFO_AUDIOCODECID		193	///< 音频流编码器ID
#define BRAC_STREAMINFO_AUDIOPACKLOSSRATE	194	///< 音频流丢包率
#define BRAC_STREAMINFO_AUDIODEVICENAME		195	///< 音频采集设备名称


#define BRAC_SO_OBJECT_INITFLAGS			200	///< 业务对象身份初始化

#define BRAC_SO_CLOUD_APPGUID				300	///< 云平台应用GUID（参数为：字符串类型，连接服务器之前设置）
#define BRAC_SO_CLOUD_ACCTYPE				301	///< 云平台应用集成账号类型
#define BRAC_SO_CLOUD_APPID3RD				302	///< 云平台应用集成时第三方平台的应用GUID


// 传输任务信息参数定义（API：BRAC_QueryTransTaskInfo 传入参数）
#define BRAC_TRANSTASK_PROGRESS				1	///< 传输任务进度查询（参数为：DWORD型，返回值0 ~ 100）
#define BRAC_TRANSTASK_BITRATE				2	///< 传输任务当前传输码率（参数为：DWORD型，单位：bps）
#define BRAC_TRANSTASK_STATUS				3	///< 传输任务当前状态（参数为：DWORD型）
#define BRAC_TRANSTASK_SAVEASPATH			4	///< 文件传输任务另存为路径设置，含文件名（参数为字符串TCHAR类型）
#define BRAC_TRANSTASK_SOURCEFILE			5	///< 源文件名（含路径，参数为字符串，TCHAR类型）
#define BRAC_TRANSTASK_JSONSTATUS			6	///< 传输任务状态，Json字符串

// 录像功能标志定义（API：BRAC_StreamRecordCtrl 传入参数）
#define BRAC_RECORD_FLAGS_VIDEO			0x00000001	///< 录制视频
#define BRAC_RECORD_FLAGS_AUDIO			0x00000002	///< 录制音频
#define BRAC_RECORD_FLAGS_SERVER		0x00000004	///< 服务器端录制
#define BRAC_RECORD_FLAGS_MIXAUDIO		0x00000010	///< 录制音频时，将其它人的声音混音后录制
#define BRAC_RECORD_FLAGS_MIXVIDEO		0x00000020	///< 录制视频时，将其它人的视频迭加后录制
#define BRAC_RECORD_FLAGS_ABREAST		0x00000100	///< 录制视频时，将其它人的视频并列录制
#define BRAC_RECORD_FLAGS_STEREO		0x00000200	///< 录制音频时，将其它人的声音混合为立体声后录制
#define BRAC_RECORD_FLAGS_SNAPSHOT		0x00000400	///< 拍照
#define BRAC_RECORD_FLAGS_LOCALCB		0x00000800	///< 触发本地回调
#define BRAC_RECORD_FLAGS_STREAM		0x00001000	///< 对视频流进行录制（效率高）
#define BRAC_RECORD_FLAGS_USERFILENAME	0x00002000	///< 用户自定义文件名


// 客户端、服务器端录制标志定义保持统一
#if !defined(ANYCHAT_RECORD_FLAGS_VIDEO)
#define ANYCHAT_RECORD_FLAGS_VIDEO			BRAC_RECORD_FLAGS_VIDEO
#define ANYCHAT_RECORD_FLAGS_AUDIO			BRAC_RECORD_FLAGS_AUDIO
#define ANYCHAT_RECORD_FLAGS_SERVER			BRAC_RECORD_FLAGS_SERVER
#define ANYCHAT_RECORD_FLAGS_MIXAUDIO		BRAC_RECORD_FLAGS_MIXAUDIO
#define ANYCHAT_RECORD_FLAGS_MIXVIDEO		BRAC_RECORD_FLAGS_MIXVIDEO
#define ANYCHAT_RECORD_FLAGS_ABREAST		BRAC_RECORD_FLAGS_ABREAST
#define ANYCHAT_RECORD_FLAGS_STEREO			BRAC_RECORD_FLAGS_STEREO
#define ANYCHAT_RECORD_FLAGS_SNAPSHOT		BRAC_RECORD_FLAGS_SNAPSHOT
#define ANYCHAT_RECORD_FLAGS_LOCALCB		BRAC_RECORD_FLAGS_LOCALCB
#define ANYCHAT_RECORD_FLAGS_STREAM			BRAC_RECORD_FLAGS_STREAM
#define ANYCHAT_RECORD_FLAGS_USERFILENAME	BRAC_RECORD_FLAGS_USERFILENAME
#define ANYCHAT_RECORD_FLAGS_ERRORCODE		0x00004000	///< 支持出错代码
#define ANYCHAT_RECORD_FLAGS_MULTISTREAM	0x00008000	///< 支持多路流的录制（拍照）
#define ANYCHAT_RECORD_FLAGS_CANCEL			0x00010000	///< 取消录像，删除录像文件
#define ANYCHAT_RECORD_FLAGS_BUFFERCB		0x00020000	///< 缓冲区数据回调
#define ANYCHAT_RECORD_FLAGS_FILEMD5		0x00040000	///< 计算录像文件的MD5值
#endif


// 组播策略定义
#define BRAC_MCPOLITIC_DISABLE				0	///< 执行服务器路由策略，禁止所有组播发送[默认]
#define BRAC_MCPOLITIC_ONLYLOCALMC			1	///< 忽略服务器路由策略，只向客户端本地组播组广播媒体流
#define BRAC_MCPOLITIC_SERVERANDLOCALMC		2	///< 执行服务器路由策略，同时在客户端本地发送组播数据
#define BRAC_MCPOLITIC_ONLYSERVERMC			3	///< 忽略服务器路由策略，只向服务器本地组播组广播媒体流
#define BRAC_MCPOLITIC_SERVERANDSERVERMC	4	///< 执行服务器路由策略，同时在服务器端发送组播数据

// 组播功能标志定义
#define BRAC_MCFLAGS_JOINGROUP		0x00000001	///< 加入多播组
#define BRAC_MCFLAGS_LEAVEGROUP		0x00000002	///< 离开多播组
#define BRAC_MCFLAGS_SENDDATA		0x00000010	///< 数据发送标志，指示该多播组用于发送数据
#define BRAC_MCFLAGS_RECVDATA		0x00000020	///< 数据接收标志，指示该多播组用于接收数据


// 用户状态标志定义（API：BRAC_QueryUserState 传入参数）
#define BRAC_USERSTATE_CAMERA				1	///< 用户摄像头状态（参数为DWORD型）
#define BRAC_USERSTATE_HOLDMIC				2	///< 用户音频设备状态（参数为DWORD型，返回值：0 音频采集关闭， 1 音频采集开启）
#define BRAC_USERSTATE_SPEAKVOLUME			3	///< 用户当前说话音量（参数为DWORD类型（0 ~ 100））
#define BRAC_USERSTATE_RECORDING			4	///< 用户录像（音）状态（参数为DWORD型）
#define	BRAC_USERSTATE_LEVEL				5	///< 用户级别（参数为DWORD型）
#define BRAC_USERSTATE_NICKNAME				6	///< 用户昵称（参数为字符串TCHAR类型）
#define BRAC_USERSTATE_LOCALIP				7	///< 用户本地IP地址（内网，参数为字符串TCHAR类型）
#define BRAC_USERSTATE_INTERNETIP			8	///< 用户互联网IP地址（参数为字符串TCHAR类型）
#define BRAC_USERSTATE_VIDEOBITRATE			9	///< 用户当前的视频码率（参数为DWORD类型，Bps）
#define BRAC_USERSTATE_AUDIOBITRATE			10	///< 用户当前的音频码率（参数为DWORD类型，Bps）
#define BRAC_USERSTATE_P2PCONNECT			11	///< 查询本地用户与指定用户的当前P2P连接状态（参数为DWORD类型，返回值：0 P2P不通， 1 P2P连接成功[TCP]，2 P2P连接成功[UDP]，3 P2P连接成功[TCP、UDP]）
#define BRAC_USERSTATE_NETWORKSTATUS		12	///< 查询指定用户的网络状态（参数为DWORD类型，返回值：0 优良，1 较好，2 一般，3 较差，4 非常差）
#define BRAC_USERSTATE_VIDEOSIZE			13	///< 查询指定用户的视频分辨率（参数为DWORD类型，返回值：低16位表示宽度，高16位表示高度）
#define BRAC_USERSTATE_PACKLOSSRATE			14	///< 查询指定用户的网络流媒体数据丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）
#define BRAC_USERSTATE_DEVICETYPE			15	///< 查询指定用户的终端类型（参数为DWORD类型，返回值：0 Unknow，1 Windows，2 Android，3 iOS，4 Web，5 Linux，6 Mac，7 Win Phone，8 WinCE）
#define BRAC_USERSTATE_SELFUSERSTATUS		16	///< 查询本地用户的当前状态（参数为DWORD类型，返回值：0 Unknow，1 Connected，2 Logined，3 In Room，4 Logouted，5 Link Closed）
#define BRAC_USERSTATE_SELFUSERID			17	///< 查询本地用户的ID（参数为DWORD类型，若用户登录成功，返回用户实际的userid，否则返回-1）
#define BRAC_USERSTATE_VIDEOROTATION		18	///< 查询指定用户的当前视频旋转角度（参数为DWORD类型，返回角度值）
#define BRAC_USERSTATE_VIDEOMIRRORED		19	///< 查询指定用户的视频是否需要镜像翻转
#define BRAC_USERSTATE_AUDIOCODECID			20	///< 查询指定用户的音频编码器ID
#define BRAC_USERSTATE_VIDEOCODECID			21	///< 查询指定用户的视频编码器ID
#define BRAC_USERSTATE_RESENDLOSSRATE		22	///< 丢包补偿后的丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）

// 房间状态标志定义（API：BRAC_QueryRoomState 传入参数）
#define BRAC_ROOMSTATE_ROOMNAME				1	///< 房间名称（参数为字符串TCHAR类型）
#define BRAC_ROOMSTATE_ONLINEUSERS			2	///< 房间在线用户数（参数为DWORD型，不包含自己）

// 视频呼叫事件类型定义（API：BRAC_VideoCallControl 传入参数、VideoCallEvent回调参数）
#define BRAC_VIDEOCALL_EVENT_REQUEST		1	///< 呼叫请求
#define BRAC_VIDEOCALL_EVENT_REPLY			2	///< 呼叫请求回复
#define BRAC_VIDEOCALL_EVENT_START			3	///< 视频呼叫会话开始事件
#define BRAC_VIDEOCALL_EVENT_FINISH			4	///< 挂断（结束）呼叫会话

// 视频呼叫标志定义（API：BRAC_VideoCallControl 传入参数）
#define BRAC_VIDEOCALL_FLAGS_AUDIO		0x0001	///< 语音通话
#define BRAC_VIDEOCALL_FLAGS_VIDEO		0x0002	///< 视频通话
#define BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO	0x0010	///< 禁止源（呼叫端）音频
#define BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO	0x0020	///< 禁止源（呼叫端）视频
#define BRAC_VIDEOCALL_FLAGS_FBTARAUDIO	0x0040	///< 禁止目标（被呼叫端）音频
#define BRAC_VIDEOCALL_FLAGS_FBTARVIDEO	0x0080	///< 禁止目标（被呼叫端）视频
#define BRAC_VIDEOCALL_FLAGS_ASSISTREQ	0x0100	///< 请求目标用户远程协助
#define BRAC_VIDEOCALL_FLAGS_CONTROLREQ	0x0200	///< 请求控制目标用户

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

// 回调函数类型定义（API：BRAC_SetCallBack 传入参数）
#define BRAC_CBTYPE_NOTIFYMESSAGE			1	///< 异步消息通知回调
#define BRAC_CBTYPE_VIDEODATA				2	///< 视频数据回调
#define BRAC_CBTYPE_VIDEODATAEX				3	///< 视频数据扩展回调
#define BRAC_CBTYPE_AUDIODATA				4	///< 音频数据回调
#define BRAC_CBTYPE_AUDIODATAEX				5	///< 音频数据扩展回调
#define BRAC_CBTYPE_TEXTMESSAGE				6	///< 文字消息回调
#define BRAC_CBTYPE_TRANSBUFFER				7	///< 透明通道数据回调
#define BRAC_CBTYPE_TRANSBUFFEREX			8	///< 透明通道数据扩展回调
#define BRAC_CBTYPE_TRANSFILE				9	///< 文件传输回调
#define BRAC_CBTYPE_VOLUMECHANGE			10	///< 音量变化回调
#define BRAC_CBTYPE_SDKFILTERDATA			11	///< SDK Filter通信数据回调
#define BRAC_CBTYPE_STREAMRECORD			12	///< 录像快照任务完成通知回调
#define BRAC_CBTYPE_STREAMRECORDEX			13	///< 录像快照任务完成通知扩展回调
#define BRAC_CBTYPE_VIDEOCALLEVENT			14	///< 视频通话消息通知回调
#define BRAC_CBTYPE_DATAENCDEC				15	///< 数据加密、解密回调
#define BRAC_CBTYPE_SCREENEVENT				16	///< 屏幕事件回调
#define BRAC_CBTYPE_NETWORKDATASEND			17	///< 网络数据回调
#define BRAC_CBTYPE_OBJECTEVENT				18	///< 业务对象事件通知
#define BRAC_CBTYPE_VIDEODATAEX2			19	///< 视频数据扩展回调（支持多路流）
#define BRAC_CBTYPE_AUDIODATAEX2			20	///< 音频数据扩展回调（支持多路流）
#define BRAC_CBTYPE_STREAMRECORDEX2			21	///< 录像快照任务完成通知扩展回调（支持出错代码）
#define BRAC_CBTYPE_TRANSFILEEX				22	///< 文件传输扩展回调（支持出错代码）
#define BRAC_CBTYPE_CORESDKEVENT			23	///< Core SDK事件回调（Json格式）
#define BRAC_CBTYPE_CORESDKDATA				24	///< Core SDK数据回调


// 视频裁剪模式定义
#define ANYCHAT_VIDEOCLIPMODE_UNKNOW		-1	///< 未知模式，不需要做裁剪时使用
#define ANYCHAT_VIDEOCLIPMODE_AUTO			0	///< 默认模式，以最大比例进行裁剪，然后再整体拉伸，画面保持比例，但被裁剪画面较大
#define ANYCHAT_VIDEOCLIPMODE_OVERLAP		1	///< 重叠模式，只取最大有效部分，对边缘进行裁剪
#define ANYCHAT_VIDEOCLIPMODE_SHRINK		2	///< 缩小模式，缩小到合适的比例，不进行裁剪
#define ANYCHAT_VIDEOCLIPMODE_STRETCH		3	///< 平铺模式，不进行裁剪，但可能导致画面不成比例
#define ANYCHAT_VIDEOCLIPMODE_DYNAMIC		4	///< 动态模式，由上层应用根据分辩率来调整显示表面，保持画面不变形


// 服务器信息查询常量定义（API：BRAC_QueryInfoFromServer 传入参数）
#define ANYCHAT_SERVERQUERY_USERIDBYNAME	1	///< 根据用户昵称查询用户ID
#define ANYCHAT_SERVERQUERY_USERIDBYSTRID	2	///< 根据字符串ID查询用户ID
#define ANYCHAT_SERVERQUERY_STRIDBYUSERID	3	///< 根据用户ID查询字符串ID
#define ANYCHAT_SERVERQUERY_NAMEBYUSERID	4	///< 根据用户ID查询用户名
#define ANYCHAT_SERVERQUERY_NAMEBYSTRID		5	///< 根据字符串ID查询用户名
#define ANYCHAT_SERVERQUERY_USERINFOBYID	6	///< 根据用户ID查询用户信息
#define ANYCHAT_SERVERQUERY_PPTFILEINFO		10	///< PPT文件信息
#define ANYCHAT_SERVERQUERY_QUEUEAGENTINFO	100	///< 查询指定队列的坐席服务信息
#define ANYCHAT_SERVERQUERY_RUNNINGSTATUS	200	///< 查询服务器运行状态
#define ANYCHAT_SERVERQUERY_ONLINEUSERS		201	///< 查询服务器在线用户数

// 外部音视频输入标志定义
#define ANYCHAT_INPUTMEDIAFLAGS_STREAM		0x01	///< 流输入
#define ANYCHAT_INPUTMEDIAFLAGS_KEYFRAME	0x02	///< 关键帧
#define ANYCHAT_INPUTMEDIAFLAGS_ROTATION	0x04	///< 合成视频方向标志
#define ANYCHAT_INPUTMEDIAFLAGS_MIXRECORD	0x08	///< 对流进行合成录制


// SDK控制常量定义（API：BRAC_SDKControl 传入参数）
#define ANYCHAT_SDKCTRL_BASE				1	///< 基本功能控制
#define ANYCHAT_SDKCTRL_SERVER				2	///< 服务器通信
#define ANYCHAT_SDKCTRL_USERBUFFER			3	///< 用户缓冲区传输控制
#define ANYCHAT_SDKCTRL_INVOKEEVENT			4	///< 触发异步事件
#define ANYCHAT_SDKCTRL_RECORD				5	///< 音视频录制
#define ANYCHAT_SDKCTRL_OBJECT				20	///< 对象操作
#define ANYCHAT_SDKCTRL_VIDEOCALL			30	///< 呼叫控制
#define ANYCHAT_SDKCTRL_USERINFO			40	///< 用户信息控制
#define ANYCHAT_SDKCTRL_STREAMPLAY			50	///< 流媒体播放
#define ANYCHAT_SDKCTRL_MEDIAPROCESS		51	///< 流媒体处理控制
#define ANYCHAT_SDKCTRL_NETWORK				60	///< 网络控制
#define ANYCHAT_SDKCTRL_MEDIA				70	///< 媒体控制
#define ANYCHAT_SDKCTRL_RECORDTAG			71	///< 录像标签
#define ANYCHAT_SDKCTRL_SCREENCAPPARAM		72	///< 屏幕采集参数设置
#define ANYCHAT_SDKCTRL_FILEDELETE			80	///< 删除文件
#define ANYCHAT_SDKCTRL_FILEINFO			81	///< 获取文件信息
#define ANYCHAT_SDKCTRL_DISKSIZE			82	///< 获取磁盘容量
#define ANYCHAT_SDKCTRL_FILEENCRYPT			83	///< 文件加解密控制
#define ANYCHAT_SDKCTRL_DELETEDIR			84	///< 删除目录
#define ANYCHAT_SDKCTRL_CREATEDIR			85	///< 创建目录
#define ANYCHAT_SDKCTRL_DIRCLEAN			86	///< 目录清理
#define ANYCHAT_SDKCTRL_FINDFILE			87	///< 查找文件
#define ANYCHAT_SDKCTRL_PPTHELPERINIT		90	///< PPT播报环境初始化
#define ANYCHAT_SDKCTRL_PPTFILECTRL			91	///< PPT文件控制
#define ANYCHAT_SDKCTRL_PPTFILEINFO			92	///< PPT文件信息
#define ANYCHAT_SDKCTRL_BUSINESS			95	///< 业务控制
#define ANYCHAT_SDKCTRL_MEDIAFILTERINIT		96	///< 媒体过滤器初始化
#define ANYCHAT_SDKCTRL_VIDEODEVICEINFO		97	///< 获取视频采集设备信息
#define ANYCHAT_SDKCTRL_UPDATERECUSERSTR	98	///< 更新录像用户参数
#define ANYCHAT_SDKCTRL_SYNCRECORD			99	///< 同步录像参数设置
#define ANYCHAT_SDKCTRL_BUSINESSBUFFER		100	///< 业务缓冲区控制
#define ANYCHAT_SDKCTRL_LIVESTREAM			101	///< 直播业务控制
#define ANYCHAT_SDKCTRL_AIABILITY			102	///< AI能力
#define ANYCHAT_SDKCTRL_APPBUFFER			103	///< APP自定义缓冲区
#define ANYCHAT_SDKCTRL_FACEEMOTIONCTRL		300	///< 微表情控制


// 媒体播放事件类型定义
#define ANYCHAT_STREAMPLAY_EVENT_START		3	///< 播放开始事件
#define ANYCHAT_STREAMPLAY_EVENT_FINISH		4	///< 播放结束事件

// 媒体播放标志定义（API：BRAC_StreamPlayInit 传入参数）
#define ANYCHAT_STREAMPLAY_FLAGS_REPLACEAUDIOINPUT	0x00000001	///< 播放音频流代替本地音频输入（Mic）
#define ANYCHAT_STREAMPLAY_FLAGS_REPLACEVIDEOINPUT	0x00000002	///< 播放视频流代替本地视频输入（Camera）
#define ANYCHAT_STREAMPLAY_FLAGS_CALLBACKDATA		0x00000010	///< 回调数据给上层
#define ANYCHAT_STREAMPLAY_FLAGS_PPTPLAY			0x00000080	///< 双录风险揭示PPT播放

// 媒体播放信息类型定义（API：BRAC_StreamPlayGetInfo 传入参数）
#define ANYCHAT_STREAMPLAY_INFO_JSONVALUE	1	///< 包含所有播放信息的Json字符串

// 媒体播放控制类型定义（API：BRAC_StreamPlayControl 传入参数）
#define ANYCHAT_STREAMPLAY_CTRL_START		1	///< 开始播放
#define ANYCHAT_STREAMPLAY_CTRL_PAUSE		2	///< 暂停播放
#define ANYCHAT_STREAMPLAY_CTRL_STOP		3	///< 停止播放
#define ANYCHAT_STREAMPLAY_CTRL_SEEK		4	///< 位置拖动
#define ANYCHAT_STREAMPLAY_CTRL_SPEEDCTRL	5	///< 速度调整
#define ANYCHAT_STREAMPLAY_CTRL_OPENLOOP	6	///< 打开循环播放
#define ANYCHAT_STREAMPLAY_CTRL_CLOSELOOP	7	///< 关闭循环播放


// CoreSDK事件类型定义（回调函数：BRAC_CoreSDKEvent_CallBack参数）
#define ANYCHAT_CORESDKEVENT_BASEEVENT		1	///< SDK基础事件
#define ANYCHAT_CORESDKEVENT_CONNECTHOLD	2	///< 连接保持事件
#define ANYCHAT_CORESDKEVENT_CAMERASTATE	10	///< 摄像头状态事件
#define ANYCHAT_CORESDKEVENT_MICSTATE		11	///< Mic状态事件
#define ANYCHAT_CORESDKEVENT_TRANSFILE		12	///< 文件传输事件
#define ANYCHAT_CORESDKEVENT_RECORDSTATUS	13	///< 录像状态事件
#define ANYCHAT_CORESDKEVENT_STREAMPLAY		30	///< 媒体播放事件
#define ANYCHAT_CORESDKEVENT_PPTHELPER		31	///< PPTHelper事件
#define ANYCHAT_CORESDKEVENT_BUSINESS		32	///< 业务事件
#define ANYCHAT_CORESDKEVENT_DEVICEFAIL		33	///< 设备失败事件
#define ANYCHAT_CORESDKEVENT_MEDIABUFFER	34	///< 媒体缓冲区事件
#define ANYCHAT_CORESDKEVENT_USERBUFFER		35	///< 用户缓冲区事件
#define ANYCHAT_CORESDKEVENT_MEDIAPROCESS	36	///< 媒体处理事件
#define ANYCHAT_CORESDKEVENT_FACEEMOTION	40	///< 微表情检测结果
#define ANYCHAT_CORESDKEVENT_REGEDITDATA	41	///< 数据接口返回数据
#define ANYCHAT_CORESDKEVENT_REQUESTEX		42	///< 扩展请求返回数据
#define ANYCHAT_CORESDKEVENT_BUSINESSBUFFER	100	///< 业务缓冲区事件
#define ANYCHAT_CORESDKEVENT_LIVESTREAM		101	///< 直播业务事件
#define ANYCHAT_CORESDKEVENT_AIABILITY		102	///< AI能力事件
#define ANYCHAT_CORESDKEVENT_APPBUFFER		103	///< APP自定义缓冲区事件
#define ANYCHAT_CORESDKEVENT_USERDEFINE		800	///< 用户自定义事件起始序号

// CoreSDK回调数据类型定义（回调函数：BRAC_CoreSDKData_CallBack参数）
#define ANYCHAT_CORESDKDATA_AUDIO			1	///< 音频数据
#define ANYCHAT_CORESDKDATA_VIDEO			2	///< 视频数据
#define ANYCHAT_CORESDKDATA_MESSAGE			3	///< 文字数据
#define ANYCHAT_CORESDKDATA_BUFFER			4	///< 缓冲区数据


#endif //_ANYCHAT_DEFINE_H__INCLUDE_
