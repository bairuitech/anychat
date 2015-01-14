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

#define BRAC_SO_RECORD_VIDEOBR				10	///< 录像视频码率设置（参数为：int型，单位：bps）
#define BRAC_SO_RECORD_AUDIOBR				11	///< 录像音频码率设置（参数为：int型，单位：bps）
#define BRAC_SO_RECORD_TMPDIR				12	///< 录像文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_SNAPSHOT_TMPDIR				13	///< 快照文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_RECORD_FILETYPE				140	///< 录制文件类型设置（参数为：int型， 0 MP4[默认], 1 WMV, 2 FLV, 3 MP3）
#define BRAC_SO_RECORD_WIDTH				141	///< 录制视频宽度设置（参数为：int型，如：320）
#define BRAC_SO_RECORD_HEIGHT				142	///< 录制文件高度设置（参数为：int型，如：240）
#define BRAC_SO_RECORD_FILENAMERULE			143	///< 录制文件名命名规则（参数为：int型）
#define BRAC_SO_RECORD_CLIPMODE				144	///< 录制视频裁剪模式（参数为：int型）

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
#define BRAC_SO_LOCALVIDEO_ROTATECTRL		94	///< 本地视频旋转控制（参数为int型，0表示不进行旋转，1表示垂直翻转）
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

#define BRAC_SO_NETWORK_P2PPOLITIC			40	///< 本地网络P2P策略控制（参数为：int型：0 禁止本地P2P，1 服务器控制P2P[默认]，2 上层应用控制P2P连接，3 按需建立P2P连接）
#define BRAC_SO_NETWORK_P2PCONNECT			41	///< 尝试与指定用户建立P2P连接（参数为int型，表示目标用户ID），连接建立成功后，会通过消息反馈给上层应用，P2P控制策略=2时有效
#define BRAC_SO_NETWORK_P2PBREAK			42	///< 断开与指定用户的P2P连接（参数为int型，表示目标用户ID）[暂不支持，保留]
#define BRAC_SO_NETWORK_TCPSERVICEPORT		43	///< 设置本地TCP服务端口（参数为int型），连接服务器之前设置有效
#define BRAC_SO_NETWORK_UDPSERVICEPORT		44	///< 设置本地UDP服务端口（参数为int型），连接服务器之前设置有效
#define BRAC_SO_NETWORK_MULTICASTPOLITIC	45	///< 组播策略控制（参数为int型，定义为常量：BRAC_MCPOLITIC_XXXX）
#define BRAC_SO_NETWORK_TRANSBUFMAXBITRATE	46	///< 传输缓冲区、文件最大码率控制（参数为int型，0 不限制，以最快速率传输[默认]， 否则表示限制码率，单位为：bps）
#define BRAC_SO_NETWORK_AUTORECONNECT		47	///< 网络掉线自动重连功能控制（参数为int型，0 关闭， 1 开启[默认]）
#define BRAC_SO_NETWORK_MTUSIZE				48	///< 设置网络层MTU大小（参数为int型）

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

#define BRAC_SO_CORESDK_TICKOUTUSER			110	///< 从服务器上踢掉指定用户（参数为int型，表示目标用户ID）

#define BRAC_SO_CORESDK_DEVICEMODE			130	///< 设备模式控制（局域网设备之间可以互相通信，不依赖服务器；参数为int型，0 关闭[默认]，1 开启）
#define BRAC_SO_CORESDK_SCREENCAMERACTRL	131	///< 桌面共享功能控制（参数为：int型， 0 关闭[默认]， 1 开启）
#define BRAC_SO_CORESDK_DATAENCRYPTION		132	///< 数据加密控制（参数为：int型， 0 关闭[默认]， 1 开启）
#define BRAC_SO_CORESDK_MEDIAUTILLIB		133	///< 获取brMediaUtil.dll的库加载句柄
#define BRAC_SO_CORESDK_UPLOADLOGINFO		134	///< 上传日志信息到服务器（参数为：int型，0 关闭[默认]， 1 开启）
#define BRAC_SO_CORESDK_WRITELOG			135	///< 写入调试信息到客户端日志文件中



// 传输任务信息参数定义（API：BRAC_QueryTransTaskInfo 传入参数）
#define BRAC_TRANSTASK_PROGRESS				1	///< 传输任务进度查询（参数为：DWORD型，返回值0 ~ 100）
#define BRAC_TRANSTASK_BITRATE				2	///< 传输任务当前传输码率（参数为：DWORD型，单位：bps）
#define BRAC_TRANSTASK_STATUS				3	///< 传输任务当前状态（参数为：DWORD型）
#define BRAC_TRANSTASK_SAVEASPATH			4	///< 文件传输任务另存为路径设置，含文件名（参数为字符串TCHAR类型）

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
#define BRAC_USERSTATE_NETWORKSTATUS		12	///< 查询指定用户的网络状态（参数为DWORD类型，返回值：0 优良，1 较好，2 一般，3 较差，4 非常差），注：查询间隔需要>1s
#define BRAC_USERSTATE_VIDEOSIZE			13	///< 查询指定用户的视频分辨率（参数为DWORD类型，返回值：低16位表示宽度，高16位表示高度）
#define BRAC_USERSTATE_PACKLOSSRATE			14	///< 查询指定用户的网络流媒体数据丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）
#define BRAC_USERSTATE_DEVICETYPE			15	///< 查询指定用户的终端类型（参数为DWORD类型，返回值：0 Unknow，1 Windows，2 Android，3 iOS，4 Web，5 Linux，6 Mac，7 Win Phone，8 WinCE）
#define BRAC_USERSTATE_SELFUSERSTATUS		16	///< 查询本地用户的当前状态（参数为DWORD类型，返回值：0 Unknow，1 Connected，2 Logined，3 In Room，4 Logouted，5 Link Closed）
#define BRAC_USERSTATE_SELFUSERID			17	///< 查询本地用户的ID（参数为DWORD类型，若用户登录成功，返回用户实际的userid，否则返回-1）
#define BRAC_USERSTATE_VIDEOROTATION		18	///< 查询指定用户的当前视频旋转角度（参数为DWORD类型，返回角度值）
#define BRAC_USERSTATE_VIDEOMIRRORED		19	///< 查询指定用户的视频是否需要镜像翻转

// 房间状态标志定义（API：BRAC_QueryRoomState 传入参数）
#define BRAC_ROOMSTATE_ROOMNAME				1	///< 房间名称（参数为字符串TCHAR类型）
#define BRAC_ROOMSTATE_ONLINEUSERS			2	///< 房间在线用户数（参数为DWORD型，不包含自己）

// 视频呼叫事件类型定义（API：BRAC_VideoCallControl 传入参数、VideoCallEvent回调参数）
#define BRAC_VIDEOCALL_EVENT_REQUEST		1	///< 呼叫请求
#define BRAC_VIDEOCALL_EVENT_REPLY			2	///< 呼叫请求回复
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
#define BRAC_USERINFO_CTRLCODE_DEBUGLOG		9	///< 输出本地用户的调试日志，wParam为调试日志类型
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
#define BRAC_CBTYPE_AUDIODATAEX				5	///< 音频数据回调扩展回调
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





#endif //_ANYCHAT_DEFINE_H__INCLUDE_
