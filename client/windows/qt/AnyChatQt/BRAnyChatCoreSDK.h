#if !defined(BR_ANYCHAT_CORE_SDK_H__INCLUDED_)
#define BR_ANYCHAT_CORE_SDK_H__INCLUDED_

#include <windows.h>

/**
 *	AnyChat Core SDK Include File
 */


#pragma once

#include "GVSDK.h"

#define BRAC_API extern "C" __declspec(dllexport)

// 视频图像格式定义
enum BRAC_PixelFormat{
	BRAC_PIX_FMT_RGB24 = 0,						///< Packed RGB 8:8:8, 24bpp, RGBRGB...（MEDIASUBTYPE_RGB24）
	BRAC_PIX_FMT_RGB32,							///< 对应于：MEDIASUBTYPE_RGB32，Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
	BRAC_PIX_FMT_YV12,							///< 对应于：MEDIASUBTYPE_YV12，Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	BRAC_PIX_FMT_YUY2,							///< 对应于：MEDIASUBTYPE_YUY2，Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
};

// 音频设备定义
enum BRAC_AudioDevice{
	BRAC_AD_WAVEIN = 0,							///< 输入设备：Mic
	BRAC_AD_WAVEOUT,							///< 输出设备：Wave
};

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
#define BRAC_FUNC_AUDIO_FORBIDCFGHW	0x00001000L	///< 禁止修改音频硬件配置
#define BRAC_FUNC_CORE_FORBIDWINMSG	0x00002000L	///< 禁止使用windows消息循环
#define BRAC_FUNC_AUDIO_LARGEBUFFER	0x00004000L	///< 音频大缓冲区模式，适合音乐播放类应用
#define BRAC_FUNC_NET_LARGEDELAY	0x00010000L	///< 网络高延迟模式，适用于卫星网络环境


// 内核参数定义
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

#define BRAC_SO_RECORD_VIDEOBR				10	///< 录像视频码率设置（参数为：int型，单位：bps）
#define BRAC_SO_RECORD_AUDIOBR				11	///< 录像音频码率设置（参数为：int型，单位：bps）
#define BRAC_SO_RECORD_TMPDIR				12	///< 录像文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_SNAPSHOT_TMPDIR				13	///< 快照文件临时目录设置（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_CORESDK_TMPDIR				14	///< 设置AnyChat Core SDK临时目录（参数为字符串TCHAR类型，必须是完整的绝对路径）
#define BRAC_SO_CORESDK_LOADCODEC			16	///< 加载外部编解码器（参数为字符串TCHAR类型，必须是完整的绝对路径，包含文件名，或包含文件名的绝对路径）
#define BRAC_SO_CORESDK_USEARMV6LIB			17	///< 强制使用ARMv6指令集的库，android平台使用（参数为：int型，1使用ARMv6指令集， 0内核自动判断[默认]）
#define BRAC_SO_CORESDK_USEHWCODEC			18	///< 使用平台内置硬件编解码器（参数为int型，0 不使用硬件编解码器[默认]  1 使用内置硬件编解码器）

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

#define BRAC_SO_NETWORK_P2PPOLITIC			40	///< 本地网络P2P策略控制（参数为：int型：0 禁止本地P2P，1 服务器控制P2P[默认]，2 上层应用控制P2P连接，3 按需建立P2P连接）
#define BRAC_SO_NETWORK_P2PCONNECT			41	///< 尝试与指定用户建立P2P连接（参数为int型，表示目标用户ID），连接建立成功后，会通过消息反馈给上层应用，P2P控制策略=2时有效
#define BRAC_SO_NETWORK_P2PBREAK			42	///< 断开与指定用户的P2P连接（参数为int型，表示目标用户ID）[暂不支持，保留]
#define BRAC_SO_NETWORK_TCPSERVICEPORT		43	///< 设置本地TCP服务端口（参数为int型），连接服务器之前设置有效
#define BRAC_SO_NETWORK_UDPSERVICEPORT		44	///< 设置本地UDP服务端口（参数为int型），连接服务器之前设置有效
#define BRAC_SO_NETWORK_MULTICASTPOLITIC	45	///< 组播策略控制（参数为int型：0 执行服务器路由策略，禁止组播发送[默认]， 1 忽略服务器路由策略，只向组播组广播媒体流， 2 执行服务器路由策略，同时组播）
#define BRAC_SO_NETWORK_TRANSBUFMAXBITRATE	46	///< 传输缓冲区、文件最大码率控制（参数为int型，0 不限制，以最快速率传输[默认]， 否则表示限制码率，单位为：bps）

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

#define BRAC_SO_CORESDK_TICKOUTUSER			110	///< 从服务器上踢掉指定用户（参数为int型，表示目标用户ID）

#define BRAC_SO_CORESDK_DEVICEMODE			130	///< 设备模式控制（局域网设备之间可以互相通信，不依赖服务器；参数为int型，0 关闭[默认]，1 开启）


// 传输任务信息参数定义（API：BRAC_QueryTransTaskInfo 传入参数）
#define BRAC_TRANSTASK_PROGRESS				1	///< 传输任务进度查询（参数为：DWORD型，返回值0 ~ 100）
#define BRAC_TRANSTASK_BITRATE				2	///< 传输任务当前传输码率（参数为：DWORD型，单位：bps）
#define BRAC_TRANSTASK_STATUS				3	///< 传输任务当前状态（参数为：DWORD型）
#define BRAC_TRANSTASK_SAVEASPATH			4	///< 文件传输任务另存为路径设置，含文件名（参数为字符串TCHAR类型）

// 录像功能标志定义（API：BRAC_StreamRecordCtrl 传入参数）
#define BRAC_RECORD_FLAGS_VIDEO		0x00000001L	///< 录制视频
#define BRAC_RECORD_FLAGS_AUDIO		0x00000002L	///< 录制音频
#define BRAC_RECORD_FLAGS_SERVER	0x00000004L	///< 服务器端录制
#define BRAC_RECORD_FLAGS_MIXAUDIO	0x00000010L	///< 录制音频时，将其它人的声音混音后录制
#define BRAC_RECORD_FLAGS_MIXVIDEO	0x00000020L	///< 录制视频时，将其它人的视频迭加后录制

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
#define BRAC_USERSTATE_VIDEOROTATION		18	///< 查询指定用户的当前视频旋转角度（参数为DWORD类型，返回角度值）
#define BRAC_USERSTATE_VIDEOMIRRORED		19	///< 查询指定用户的视频是否需要镜像翻转

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


// 视频数据回调函数定义
typedef void (CALLBACK * BRAC_VideoData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue);
// 视频数据扩展回调函数定义（增加时间戳）
typedef void (CALLBACK * BRAC_VideoDataEx_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, DWORD dwTimeStamp, LPVOID lpUserValue);
// 音频数据回调函数定义
typedef void (CALLBACK * BRAC_AudioData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue);
// 音频数据扩展回调函数定义（增加时间戳）
typedef void (CALLBACK * BRAC_AudioDataEx_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, DWORD dwTimeStamp, LPVOID lpUserValue);
// 文字消息回调函数定义
typedef void (CALLBACK * BRAC_TextMessage_CallBack)(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue);
// 透明通道数据回调函数定义
typedef void (CALLBACK * BRAC_TransBuffer_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// 透明通道数据扩展回调函数定义
typedef void (CALLBACK * BRAC_TransBufferEx_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// 文件传输回调函数定义
typedef void (CALLBACK * BRAC_TransFile_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// 音量变化回调函数定义
typedef void (CALLBACK * BRAC_VolumeChange_CallBack)(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue);
// SDK Filter 通信数据回调函数定义
typedef void (CALLBACK * BRAC_SDKFilterData_CallBack)(LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// 录像、快照任务完成回调函数定义
typedef void (CALLBACK * BRAC_RecordSnapShot_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType, LPVOID lpUserValue);
// 异步消息通知回调函数定义
typedef void (CALLBACK* BRAC_NotifyMessage_CallBack)(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
// 视频通话消息通知回调函数定义
typedef void (CALLBACK * BRAC_VideoCallEvent_CallBack)(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);


/**
 *	API方法定义
 */

// 获取SDK版本信息
BRAC_API DWORD BRAC_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, TCHAR* lpCompileTime, DWORD dwBufLen);
// 激活（关闭）SDK调用日志
BRAC_API DWORD BRAC_ActiveCallLog(BOOL bActive);

// 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
BRAC_API DWORD BRAC_SetServerAuthPass(LPCTSTR lpPassword);
// 初始化系统
BRAC_API DWORD BRAC_InitSDK(HWND hWnd, DWORD dwFuncMode);

// 设置视频数据回调函数
BRAC_API DWORD BRAC_SetVideoDataCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置视频数据扩展回调函数（增加时间戳）
BRAC_API DWORD BRAC_SetVideoDataExCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoDataEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置音频数据回调函数
BRAC_API DWORD BRAC_SetAudioDataCallBack(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置音频数据回调扩展函数（增加时间戳）
BRAC_API DWORD BRAC_SetAudioDataExCallBack(BRAC_AudioDataEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置文字消息回调函数
BRAC_API DWORD BRAC_SetTextMessageCallBack(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置透明通道数据回调函数
BRAC_API DWORD BRAC_SetTransBufferCallBack(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置透明通道数据扩展回调函数
BRAC_API DWORD BRAC_SetTransBufferExCallBack(BRAC_TransBufferEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置文件传输回调函数
BRAC_API DWORD BRAC_SetTransFileCallBack(BRAC_TransFile_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置音量变化回调函数
BRAC_API DWORD BRAC_SetVolumeChangeCallBack(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置SDK Filter通信数据回调函数定义
BRAC_API DWORD BRAC_SetSDKFilterDataCallBack(BRAC_SDKFilterData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置录像快照任务完成通知回调函数
BRAC_API DWORD BRAC_SetRecordSnapShotCallBack(BRAC_RecordSnapShot_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置异步消息通知回调函数
BRAC_API DWORD BRAC_SetNotifyMessageCallBack(BRAC_NotifyMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// 设置视频通话消息通知回调函数
BRAC_API DWORD BRAC_SetVideoCallEventCallBack(BRAC_VideoCallEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);


// 连接服务器
BRAC_API DWORD BRAC_Connect(LPCTSTR lpServerAddr, DWORD dwPort);
// 登录系统
BRAC_API DWORD BRAC_Login(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType);
// 进入房间
BRAC_API DWORD BRAC_EnterRoom(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType);
// 进入房间
BRAC_API DWORD BRAC_EnterRoomEx(LPCTSTR lpRoomName, LPCTSTR lpRoomPass);
// 离开房间
BRAC_API DWORD BRAC_LeaveRoom(DWORD dwRoomid);
// 注销系统
BRAC_API DWORD BRAC_Logout(VOID);

// 释放所有资源
BRAC_API DWORD BRAC_Release(VOID);

// 获取当前房间在线用户列表
BRAC_API DWORD BRAC_GetOnlineUser(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// 查询用户摄像头的状态
BRAC_API DWORD BRAC_GetCameraState(DWORD dwUserid, DWORD& dwState);
// 查询用户发言状态
BRAC_API DWORD BRAC_GetSpeakState(DWORD dwUserid, DWORD& dwState);
// 查询用户级别
BRAC_API DWORD BRAC_GetUserLevel(DWORD dwUserid, DWORD& dwLevel);
// 查询用户名称
BRAC_API DWORD BRAC_GetUserName(DWORD dwUserid, TCHAR* lpUserName, DWORD dwLen);
// 查询房间名称
BRAC_API DWORD BRAC_GetRoomName(DWORD dwRoomId, TCHAR* lpRoomName, DWORD dwLen);
// 显示本地视频画面调节对话框
BRAC_API DWORD BRAC_ShowLVProperty(HWND hParent, LPCTSTR szCaption=NULL, DWORD dwX=0, DWORD dwY=0);

// 查询指定用户相关状态
BRAC_API DWORD BRAC_QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);

// 枚举本地视频采集设备
BRAC_API DWORD BRAC_EnumVideoCapture(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// 选择指定的视频采集设备
BRAC_API DWORD BRAC_SelectVideoCapture(LPCTSTR szCaptureName);
// 获取当前使用的视频采集设备
BRAC_API DWORD BRAC_GetCurVideoCapture(TCHAR* lpDeviceName, DWORD dwLen);
// 枚举本地音频采集设备
BRAC_API DWORD BRAC_EnumAudioCapture(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// 选择指定的音频采集设备
BRAC_API DWORD BRAC_SelectAudioCapture(LPCTSTR szCaptureName);
// 获取当前使用的音频采集设备
BRAC_API DWORD BRAC_GetCurAudioCapture(TCHAR* lpDeviceName, DWORD dwLen);
// 枚举本地音频播放设备
BRAC_API DWORD BRAC_EnumAudioPlayback(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// 选择指定的音频播放设备
BRAC_API DWORD BRAC_SelectAudioPlayback(LPCTSTR szDeviceName);
// 获取当前使用的音频播放设备
BRAC_API DWORD BRAC_GetCurAudioPlayback(TCHAR* lpDeviceName, DWORD dwLen);

// 操作用户视频
BRAC_API DWORD BRAC_UserCameraControl(DWORD dwUserid, BOOL bOpen);
// 操作用户语音
BRAC_API DWORD BRAC_UserSpeakControl(DWORD dwUserid, BOOL bOpen);
// 设置视频显示位置
BRAC_API DWORD BRAC_SetVideoPos(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom);
// 重绘指定用户的视频
BRAC_API DWORD BRAC_RepaintVideo(DWORD dwUserId, HDC hDC);

// 获取指定音频设备的当前音量
BRAC_API DWORD BRAC_AudioGetVolume(BRAC_AudioDevice device, DWORD& dwVolume);
// 设置指定音频设备的音量
BRAC_API DWORD BRAC_AudioSetVolume(BRAC_AudioDevice device, DWORD dwVolume);

// 用户音、视频录制
BRAC_API DWORD BRAC_StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam);
// 对用户的视频进行抓拍（快照）
BRAC_API DWORD BRAC_SnapShot(DWORD dwUserId, DWORD dwFlags, DWORD dwParam);

// 透明通道传送缓冲区
BRAC_API DWORD BRAC_TransBuffer(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
// 透明通道传送缓冲区扩展
BRAC_API DWORD BRAC_TransBufferEx(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// 传送文件
BRAC_API DWORD BRAC_TransFile(DWORD dwUserid, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// 查询传输任务相关信息
BRAC_API DWORD BRAC_QueryTransTaskInfo(DWORD dwUserid, DWORD dwTaskId, int infoname, char FAR* infoval, int infolen);
// 取消传输任务
BRAC_API DWORD BRAC_CancelTransTask(DWORD dwUserid, DWORD dwTaskId);
// 传送文本消息
BRAC_API DWORD BRAC_SendTextMessage(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
// 发送SDK Filter 通信数据
BRAC_API DWORD BRAC_SendSDKFilterData(LPBYTE lpBuf, DWORD dwLen);

// 更改当前的聊天模式
BRAC_API DWORD BRAC_ChangeChatMode(DWORD dwChatMode);
// 获取指定用户当前的聊天模式
BRAC_API DWORD BRAC_GetUserChatMode(DWORD dwUserid, DWORD& dwChatMode);
// 请求与对方私聊，向对方发起私聊请求
BRAC_API DWORD BRAC_PrivateChatRequest(DWORD dwUserid);
// 回复对方的私聊请求
BRAC_API DWORD BRAC_PrivateChatEcho(DWORD dwUserid, DWORD dwRequestid,BOOL bAccept);
// 回复对方的私聊请求（扩展，可以附带出错代码）
BRAC_API DWORD BRAC_PrivateChatEchoEx(DWORD dwUserid, DWORD dwRequestid,DWORD dwErrorCode);
// 退出与某用户的私聊，或者将某用户从自己的私聊列表中清除
BRAC_API DWORD BRAC_PrivateChatExit(DWORD dwUserid);

// SDK内核参数设置
BRAC_API DWORD BRAC_SetSDKOption(int optname, const char FAR* optval, int optlen);
// SDK内核参数状态查询
BRAC_API DWORD BRAC_GetSDKOption(int optname, char FAR* optval, int optlen);

// 组播功能控制
BRAC_API DWORD BRAC_MultiCastControl(LPCTSTR lpMultiCastAddr, DWORD dwPort, LPCTSTR lpNicAddr, DWORD dwTTL, DWORD dwFlags);

// 设置外部输入视频格式
BRAC_API DWORD BRAC_SetInputVideoFormat(BRAC_PixelFormat pixFmt, DWORD dwWidth, DWORD dwHeight, DWORD dwFps, DWORD dwFlags);
// 外部视频数据输入
BRAC_API DWORD BRAC_InputVideoData(LPBYTE lpVideoFrame, DWORD dwSize, DWORD dwTimeStamp);
// 设置外部输入音频格式
BRAC_API DWORD BRAC_SetInputAudioFormat(DWORD dwChannels, DWORD dwSamplesPerSec, DWORD dwBitsPerSample, DWORD dwFlags);
// 外部音频数据输入
BRAC_API DWORD BRAC_InputAudioData(LPBYTE lpSamples, DWORD dwSize, DWORD dwTimeStamp);

// 获取音频播放数据
BRAC_API DWORD BRAC_FetchAudioPlayBuffer(LPBYTE lpSamples, DWORD dwSize, DWORD wParam);

// 远程调试
BRAC_API DWORD BRAC_RemoteDebug(DWORD dwUserId, DWORD dwDebugCode, DWORD dwParam=0, DWORD dwBufLen=0, char* szBuf=NULL);


// 视频呼叫事件控制（请求、回复、挂断等）
BRAC_API DWORD BRAC_VideoCallControl(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags=0, DWORD dwParam=0, LPCTSTR lpUserStr=NULL);

// 获取用户好友ID列表
BRAC_API DWORD BRAC_GetUserFriends(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// 获取好友在线状态
BRAC_API DWORD BRAC_GetFriendStatus(DWORD dwFriendUserId, DWORD& dwStatus);
// 获取用户分组ID列表
BRAC_API DWORD BRAC_GetUserGroups(LPDWORD lpGroupIDArray, DWORD& dwGroupNum);
// 获取分组下面的好友列表
BRAC_API DWORD BRAC_GetGroupFriends(DWORD dwGroupId, LPDWORD lpUserIDArray, DWORD& dwUserNum);
// 获取用户信息
BRAC_API DWORD BRAC_GetUserInfo(DWORD dwUserId, DWORD dwInfoId, TCHAR* lpInfoValue, DWORD dwLen);
// 获取用户分组名称
BRAC_API DWORD BRAC_GetGroupName(DWORD dwGroupId, TCHAR* lpGroupName, DWORD dwLen);
// 用户信息控制
BRAC_API DWORD BRAC_UserInfoControl(DWORD dwUserId, DWORD dwCtrlCode, DWORD wParam=0, DWORD lParam=0, LPCTSTR lpStrValue=NULL);



#endif //BR_ANYCHAT_CORE_SDK_H__INCLUDED_
