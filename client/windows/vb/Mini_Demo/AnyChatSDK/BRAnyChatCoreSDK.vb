Option Strict On
Option Explicit On
Imports System.Runtime.InteropServices

Module BRAnyChatCoreSDK
	Public Const AnyChatSDKDLL As String = "BRAnyChatCore.dll"
	
	'// 功能模式定义
	Public Const BRAC_FUNC_VIDEO_CBDATA 	As Integer = &H1
	'#define BRAC_FUNC_VIDEO_CBDATA      0x00000001L ///< 通过回调函数输出视频数据
	Public Const BRAC_FUNC_VIDEO_AUTODISP 	As Integer = &H2
	'#define BRAC_FUNC_VIDEO_AUTODISP    0x00000002L ///< 由SDK包处理视频，将视频显示在指定的窗口上
	Public Const BRAC_FUNC_AUDIO_CBDATA 	As Integer = &H4
	'#define BRAC_FUNC_AUDIO_CBDATA      0x00000004L ///< 通过回调函数输出音频数据
	Public Const BRAC_FUNC_AUDIO_AUTOPLAY 	As Integer = &H8
	'#define BRAC_FUNC_AUDIO_AUTOPLAY    0x00000008L ///< 由SDK包处理音频，直接播放
	Public Const BRAC_FUNC_CONFIG_LOCALINI 	As Integer = &H10
	'#define BRAC_FUNC_CONFIG_LOCALINI   0x00000010L ///< 生成本地配置文件（AnyChatSDK.ini）
	Public Const BRAC_FUNC_FIREWALL_OPEN 	As Integer = &H20
	'#define BRAC_FUNC_FIREWALL_OPEN     0x00000020L ///< 允许SDK操作Windows防火墙，将当前应用程序加入防火墙访问列表（避免Windows提示用户是否阻止当前应用程序）
	Public Const BRAC_FUNC_CHKDEPENDMODULE 	As Integer = &H40
	'#define BRAC_FUNC_CHKDEPENDMODULE   0x00000040L ///< 自动检查SDK所依赖的组件，并自动注册
	Public Const BRAC_FUNC_AUDIO_VOLUMECALC As Integer = &H80
	'#define BRAC_FUNC_AUDIO_VOLUMECALC  0x00000080L ///< 由SDK自动计算语音的音量
	Public Const BRAC_FUNC_AUDIO_AUTOVOLUME As Integer = &H100
	'#define BRAC_FUNC_AUDIO_AUTOVOLUME  0x00000100L ///< 允许SDK自动控制Mic录音音量
	Public Const BRAC_FUNC_NET_SUPPORTUPNP 	As Integer = &H200
	'#define BRAC_FUNC_NET_SUPPORTUPNP   0x00000200L ///< 允许SDK打开用户网络中的UPNP设备，如果用户的路由器或是防火墙支持UPNP协议，则可提高P2P打洞的成功率
	
	
	'// 内核参数定义
	Public Const BRAC_SO_AUDIO_VADCTRL 		As Integer = 1
	'#define BRAC_SO_AUDIO_VADCTRL               1   ///< 音频静音检测控制（参数为：int型：1打开，0关闭）
	Public Const BRAC_SO_AUDIO_NSCTRL 		As Integer = 2
	'#define BRAC_SO_AUDIO_NSCTRL                2   ///< 音频噪音抑制控制（参数为：int型：1打开，0关闭）
	Public Const BRAC_SO_AUDIO_ECHOCTRL 	As Integer = 3
	'#define BRAC_SO_AUDIO_ECHOCTRL              3   ///< 音频回音消除控制（参数为：int型：1打开，0关闭）
	Public Const BRAC_SO_AUDIO_AGCCTRL 		As Integer = 4
	'#define BRAC_SO_AUDIO_AGCCTRL               4   ///< 音频自动增益控制（参数为：int型：1打开，0关闭）
	Public Const BRAC_SO_AUDIO_SOFTVOLMODE	As Integer = 73
	'#define BRAC_SO_AUDIO_SOFTVOLMODE			73	///< 设置软件音量模式控制（参数为int型，1打开，0关闭[默认]），使用软件音量模式，将不会改变系统
	Public Const BRAC_SO_AUDIO_RECORDDRVCTRL As Integer= 74
	'#define BRAC_SO_AUDIO_RECORDDRVCTRL			74	///< 音频采集驱动控制（参数为int型，0默认驱动， 1 DSound驱动， 2 WaveIn驱动， 3 Java采集[Android平台使用]）
	
	Public Const BRAC_SO_RECORD_VIDEOBR 	As Integer = 10
	'#define BRAC_SO_RECORD_VIDEOBR              10  ///< 录像视频码率设置（参数为：int型，单位：bps）
	Public Const BRAC_SO_RECORD_AUDIOBR 	As Integer = 11
	'#define BRAC_SO_RECORD_AUDIOBR              11  ///< 录像音频码率设置（参数为：int型，单位：bps）
	Public Const BRAC_SO_RECORD_TMPDIR 		As Integer = 12
	'#define BRAC_SO_RECORD_TMPDIR               12  ///< 录像文件临时目录设置（参数为字符串PCHAR类型）
	Public Const BRAC_SO_SNAPSHOT_TMPDIR 	As Integer = 13
	'#define BRAC_SO_SNAPSHOT_TMPDIR             13  ///< 快照文件临时目录设置（参数为字符串PCHAR类型）
	Public Const BRAC_SO_CORESDK_TMPDIR 	As Integer = 14
	'#define BRAC_SO_CORESDK_TMPDIR              14  ///< 设置AnyChat Core SDK临时目录（参数为字符串PCHAR类型）
	
	Public Const BRAC_SO_CORESDK_PATH 		As Integer = 20
    '#define BRAC_SO_CORESDK_PATH                20  ///< 设置AnyChat Core SDK相关组件路径（参数为字符串PCHAR类型）

    Public Const BRAC_SO_NETWORK_P2PPOLITIC As Integer = 40
	'#define BRAC_SO_NETWORK_P2PPOLITIC			40	///< 本地网络P2P策略控制（参数为：int型：0 禁止本地P2P，1 服务器控制P2P[默认]，2 上层应用控制P2P连接，3 按需建立P2P连接）
	Public Const BRAC_SO_NETWORK_P2PCONNECT As Integer = 41
	'#define BRAC_SO_NETWORK_P2PCONNECT			41	///< 尝试与指定用户建立P2P连接（参数为int型，表示目标用户ID），连接建立成功后，会通过消息反馈给上层应用，P2P控制策略=2时有效
	Public Const BRAC_SO_NETWORK_P2PBREAK 	As Integer = 42
	'#define BRAC_SO_NETWORK_P2PBREAK			42	///< 断开与指定用户的P2P连接（参数为int型，表示目标用户ID）[暂不支持，保留]

    Public Const BRAC_SOPROXY_FUNCTIONCTRL 	As Integer = 50
    '#define BRAC_SO_PROXY_FUNCTIONCTRL			50	///< 本地用户代理功能控制，（参数为：int型，1启动代理，0关闭代理[默认]）

    Public Const BRAC_SO_PROXY_VIDEOCTRL 	As Integer = 51
    '#define BRAC_SO_PROXY_VIDEOCTRL				51	///< 本地用户代理视频控制，将本地视频变为指定用户的视频对外发布（参数为int型，表示其它用户的userid）

    Public Const BRAC_SO_PROXY_AUDIOCTRL 	As Integer = 52
    '#define BRAC_SO_PROXY_AUDIOCTRL				52	///< 本地用户代理音频控制，将本地音频变为指定用户的音频对外发布（参数同BRAC_SO_PROXY_VIDEOCTRL）

    Public Const BRAC_SO_STREAM_BUFFERTIME 	As Integer = 60
    '#define BRAC_SO_STREAM_BUFFERTIME			60	///< 流缓冲时间（参数为int型，单位：毫秒，取值范围：500 ~ 5000，默认：800）
	Public Const BRAC_SO_STREAM_SMOOTHPLAYMODE As Integer = 61
	'#define BRAC_SO_STREAM_SMOOTHPLAYMODE		61	///< 平滑播放模式（参数为int型，0 关闭[默认], 1 打开），打开状态下遇到视频丢帧时会继续播放（可能出现马赛克），不会卡住

	'// 传输任务信息参数定义
	Public Const BRAC_TRANSTASK_PROGRESS 	As Short = 1
	'#define BRAC_TRANSTASK_PROGRESS             1   ///< 传输任务进度查询（参数为：DOUBLE型（0.0 ~ 100.0））
	Public Const BRAC_TRANSTASK_BITRATE 	As Short = 2
	'#define BRAC_TRANSTASK_BITRATE              2   ///< 传输任务当前传输码率（参数为：int型，单位：bps）
	Public Const BRAC_TRANSTASK_STATUS 		As Short = 3
	'#define BRAC_TRANSTASK_STATUS               3   ///< 传输任务当前状态（参数为：int型）
	
	
	'// 录像功能标志定义
	Public Const BRAC_RECORD_FLAGS_VIDEO 	As Integer = &H1
	'#define BRAC_RECORD_FLAGS_VIDEO     0x00000001L ///< 录制视频
	Public Const BRAC_RECORD_FLAGS_AUDIO 	As Integer = &H2
	'#define BRAC_RECORD_FLAGS_AUDIO     0x00000002L ///< 录制音频
	Public Const BRAC_RECORD_FLAGS_SERVER 	As Integer = &H4
	'#define BRAC_RECORD_FLAGS_SERVER	0x00000004L	///< 服务器端录制
	Public Const BRAC_RECORD_FLAGS_MIXAUDIO As Integer = &H10
	'#define BRAC_RECORD_FLAGS_MIXAUDIO	0x00000010L	///< 录制音频时，将其它人的声音混音后录制
	Public Const BRAC_RECORD_FLAGS_MIXVIDEO As Integer = &H20
	'#define BRAC_RECORD_FLAGS_MIXVIDEO	0x00000020L	///< 录制视频时，将其它人的视频迭加后录制
	
	
	'// 用户状态标志定义
	Public Const BRAC_USERSTATE_CAMERA 		As Integer = 1
	'#define BRAC_USERSTATE_CAMERA          1   ///< 用户摄像头状态（参数为int型）
	Public Const BRAC_USERSTATE_HOLDMIC 	As Integer = 2
	'#define BRAC_USERSTATE_HOLDMIC         2   ///< 用户音频设备状态（参数为DWORD型，返回值：0 音频采集关闭， 1 音频采集开启）
	Public Const BRAC_USERSTATE_SPEAKVOLUME As Integer = 3
	'#define BRAC_USERSTATE_SPEAKVOLUME		3   ///< 用户当前说话音量（参数为DOUBLE类型（0.0 ~ 100.0））
	Public Const BRAC_USERSTATE_RECORDING 	As Integer = 4
	'#define BRAC_USERSTATE_RECORDING 		4   ///< 用户录像（音）状态（参数为int型）
	Public Const BRAC_USERSTATE_LEVEL 		As Integer = 5
	'#define BRAC_USERSTATE_LEVEL			5   ///< 用户级别（参数为int型）
	Public Const BRAC_USERSTATE_NICKNAME 	As Integer = 6
	'#define BRAC_USERSTATE_NICKNAME		6   ///< 用户昵称（参数为字符串PCHAR类型）
	Public Const BRAC_USERSTATE_LOCALIP 	As Integer = 7
	'#define BRAC_USERSTATE_LOCALIP			7   ///< 用户本地IP地址（内网，参数为字符串PCHAR类型）
	Public Const BRAC_USERSTATE_INTERNETIP 	As Integer = 8
	'#define BRAC_USERSTATE_INTERNETIP		8   ///< 用户互联网IP地址（参数为字符串PCHAR类型）
	Public Const BRAC_USERSTATE_VIDEOBITRATE As Integer = 9
	'#define BRAC_USERSTATE_VIDEOBITRATE	9	///< 用户当前的视频码率（参数为DWORD类型，Bps）
	Public Const BRAC_USERSTATE_AUDIOBITRATE As Integer = 10
	'#define BRAC_USERSTATE_AUDIOBITRATE	10	///< 用户当前的音频码率（参数为DWORD类型，Bps）
	Public Const BRAC_USERSTATE_P2PCONNECT As Integer = 11
	'#define BRAC_USERSTATE_P2PCONNECT		11	///< 查询本地用户与指定用户的当前P2P连接状态（参数为DWORD类型，返回值：0 P2P不通， 1 P2P连接成功[TCP]，2 P2P连接成功[UDP]，3 P2P连接成功[TCP、UDP]）
	Public Const BRAC_USERSTATE_NETWORKSTATUS As Integer = 12
	'#define BRAC_USERSTATE_NETWORKSTATUS	12	///< 查询指定用户的网络状态（参数为DWORD类型，返回值：0 优良，1 较好，2 一般，3 较差，4 非常差），注：查询间隔需要>1s
	Public Const BRAC_USERSTATE_VIDEOSIZE As Integer = 13
	'#define BRAC_USERSTATE_VIDEOSIZE		13	///< 查询指定用户的视频分辨率（参数为DWORD类型，返回值：低16位表示宽度，高16位表示高度）
	Public Const BRAC_USERSTATE_PACKLOSSRATE As Integer = 14
	'#define BRAC_USERSTATE_PACKLOSSRATE	14	///< 查询指定用户的网络流媒体数据丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）
	Public Const BRAC_USERSTATE_DEVICETYPE As Integer = 15
	'#define BRAC_USERSTATE_DEVICETYPE		15	///< 查询指定用户的终端类型（参数为DWORD类型，返回值：0 Unknow， 1 Windows，2 Android，3 iOS，4 Web，5 Linux，6 Mac，7 Win Phone，8 WinCE）	
	Public Const BRAC_USERSTATE_SELFUSERSTATUS As Integer =	16
	'#define BRAC_USERSTATE_SELFUSERSTATUS		16	///< 查询本地用户的当前状态（参数为DWORD类型，返回值：0 Unknow，1 Connected，2 Logined，3 In Room，4 Logouted，5 Link Closed）
	Public Const BRAC_USERSTATE_SELFUSERID As Integer =	17
	'#define BRAC_USERSTATE_SELFUSERID			17	///< 查询本地用户的ID（参数为DWORD类型，若用户登录成功，返回用户实际的userid，否则返回-1）
	
	'// 视频呼叫事件类型定义（API：BRAC_VideoCallControl 传入参数、VideoCallEvent回调参数）
	'#define BRAC_VIDEOCALL_EVENT_REQUEST		1	///< 呼叫请求
	Public Const BRAC_VIDEOCALL_EVENT_REQUEST As Integer = 1
	'#define BRAC_VIDEOCALL_EVENT_REPLY			2	///< 呼叫请求回复
	Public Const BRAC_VIDEOCALL_EVENT_REPLY As Integer = 2
	'#define BRAC_VIDEOCALL_EVENT_START			3	///< 视频呼叫会话开始事件
	Public Const BRAC_VIDEOCALL_EVENT_START As Integer = 3
	'#define BRAC_VIDEOCALL_EVENT_FINISH			4	///< 挂断（结束）呼叫会话
	Public Const BRAC_VIDEOCALL_EVENT_FINISH As Integer = 4

	'// 视频呼叫标志定义（API：BRAC_VideoCallControl 传入参数）
	'#define BRAC_VIDEOCALL_FLAGS_AUDIO		0x01	///< 语音通话
	Public Const BRAC_VIDEOCALL_FLAGS_AUDIO As Integer = &H1
	'#define BRAC_VIDEOCALL_FLAGS_VIDEO		0x02	///< 视频通话
	Public Const BRAC_VIDEOCALL_FLAGS_VIDEO As Integer = &H2
	'#define BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO	0x10	///< 禁止源（呼叫端）音频
	Public Const BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO As Integer = &H10
	'#define BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO	0x20	///< 禁止源（呼叫端）视频
	Public Const BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO As Integer = &H20
	'#define BRAC_VIDEOCALL_FLAGS_FBTARAUDIO	0x40	///< 禁止目标（被呼叫端）音频
	Public Const BRAC_VIDEOCALL_FLAGS_FBTARAUDIO As Integer = &H40
	'#define BRAC_VIDEOCALL_FLAGS_FBTARVIDEO	0x80	///< 禁止目标（被呼叫端）视频
	Public Const BRAC_VIDEOCALL_FLAGS_FBTARVIDEO As Integer = &H80

    '注意：所有的BOOL类型都声明为integer类型

	Public Structure BITMAPINFOHEADER
        Public biSize As Integer
        Public biWidth As Integer
        Public biHeight As Integer
        Public biPlanes As Short
        Public biBitCount As Short
        Public biCompression As Integer
        Public biSizeImage As Integer
        Public biXPelsPerMeter As Integer
        Public biyPelsPerMeter As Integer
        Public biClrUsed As Integer
        Public biClrImportant As Integer
    End Structure
    '// 视频数据回调函数定义
    'typedef void (CALLBACK * BRAC_VideoData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue);
    Public Delegate Sub BRAC_VideoData_CallBack(ByVal dwUserid As Integer, ByVal lpBuf As IntPtr, ByVal dwLen As Integer, ByVal bmiHeader As BITMAPINFOHEADER, ByVal lpUserValue As IntPtr)

    Public Structure WAVEFORMATEX
        Public wFormatTag As Short
        Public nChannels As Short
        Public nSamplesPesSec As Integer
        Public nAvgBytesPerSec As Integer
        Public nBlockAlign As Short
        Public wBitsPerSample As Short
        Public cbSize As Short
    End Structure
    '// 音频数据回调函数定义
    'typedef void (CALLBACK * BRAC_AudioData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue);
    Public Delegate Sub BRAC_AudioData_CallBack(ByVal dwUserid As Integer, ByVal lpBuf As IntPtr, ByVal dwLen As Integer, ByVal waveFormatEx As WAVEFORMATEX, ByVal lpUserValue As IntPtr)

    '// 文字消息回调函数定义
    'typedef void (CALLBACK * BRAC_TextMessage_CallBack)(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue);
    Public Delegate Sub BRAC_TextMessage_CallBack(ByVal dwFromUserid As Integer, ByVal dwTouserid As Integer, ByVal bSecret As Integer, ByVal lpMsgbuf As IntPtr, ByVal dwLen As Integer, ByVal lpUserValue As IntPtr)

    '// 透明通道数据回调函数定义
    'typedef void (CALLBACK * BRAC_TransBuffer_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
    Public Delegate Sub BRAC_TransBuffer_CallBack(ByVal dwUserid As Integer, ByVal lpBuf As Byte(), ByVal dwLen As Integer, ByVal lpUserValue As IntPtr)

    '// 透明通道数据扩展回调函数定义
    'typedef void (CALLBACK * BRAC_TransBufferEx_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
    Public Delegate Sub BRAC_TransBufferEx_CallBack(ByVal dwUserid As Integer, ByVal lpBuf As Byte(), ByVal dwLen As Integer, ByVal wParam As Integer, ByVal lParam As Integer, ByVal dwTaskId As Integer, ByVal lpUserValue As IntPtr)

    '// 文件传输回调函数定义
    'typedef void (CALLBACK * BRAC_TransFile_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
    Public Delegate Sub BRAC_TransFile_CallBack(ByVal dwUserid As Integer, ByVal lpFileName As String, ByVal lpTempFilePath As String, ByVal dwFileLength As Integer, ByVal wParam As Integer, ByVal lParam As Integer, ByVal dwTaskId As Integer, ByVal lpUserValue As IntPtr)

    'enum BRAC_AudioDevice{
    'BRAC_AD_WAVEIN = 0,							///< 输入设备：Mic
    'BRAC_AD_WAVEOUT,							///< 输出设备：Wave
    '};
    Public Enum BRAC_AudioDevice
        BRAC_AD_WAVEIN = 0
        BRAC_AD_WAVEOUT
    End Enum
    '// 音量变化回调函数定义
    'typedef void (CALLBACK * BRAC_VolumeChange_CallBack)(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue);
    Public Delegate Sub BRAC_VolumeChange_CallBack(ByVal device As BRAC_AudioDevice, ByVal dwCurrentVolume As Integer, ByVal lpUserValue As IntPtr)

    '// SDK Filter 通信数据回调函数定义
    'typedef void (CALLBACK * BRAC_SDKFilterData_CallBack)(LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
    Public Delegate Sub BRAC_SDKFilterData_CallBack(ByVal lpBuf As Byte(), ByVal dwLen As Integer, ByVal lpUserValue As IntPtr)

    '// 录像、快照任务完成回调函数定义
    'typedef void (CALLBACK * BRAC_RecordSnapShot_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType, LPVOID lpUserValue);
    Public Delegate Sub BRAC_RecordSnapShot_CallBack(ByVal dwUserid As Integer, ByVal lpFileName As String, ByVal dwParam As Integer, ByVal bRecordType As Integer, ByVal lpUserValue As IntPtr)

    '// 异步消息通知回调函数定义
    'typedef void (CALLBACK* BRAC_NotifyMessage_CallBack)(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
    Public Delegate Sub BRAC_NotifyMessage_CallBack(ByVal dwNotifyMsg As Integer, ByVal wParam As Integer, ByVal lParam As Integer, ByVal lpUserValue As IntPtr)
	
	'// 视频通话消息通知回调函数定义
	'typedef void (CALLBACK * BRAC_VideoCallEvent_CallBack)(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);
    Public Delegate Sub BRAC_VideoCallEvent_CallBack(ByVal dwEventType As Integer, ByVal dwUserId As Integer, ByVal dwErrorCode As Integer, ByVal dwFlags As Integer, ByVal dwParam As Integer, ByVal lpUserStr As String, ByVal lpUserValue As IntPtr)

    '/**
    ' *  API方法定义
    ' */
    '注意：这里将LPSTR类型的参数lpCompileTime声明为类型IntPtr，请使用Marshal.StringToHGlobalAnsi函数将一个托管的String字符串复制并返回一个非托管的缓冲区指针。注意，请记得使用Marshal.FreeHGlobal释放该指针。
    '// 获取SDK版本信息
    'BRAC_API DWORD BRAC_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, LPSTR lpCompileTime, DWORD dwBufLen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetSDKVersion", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetSDKVersion(ByRef dwMainVer As Integer, ByRef dwSubVer As Integer, ByVal lpCompileTime As IntPtr, ByVal dwBufLen As Integer) As Integer
    End Function

    '// 激活（关闭）SDK调用日志
    'BRAC_API DWORD BRAC_ActiveCallLog(BOOL bActive);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_ActiveCallLog", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_ActiveCallLog(ByVal bActive As Integer) As Integer
    End Function

    '// 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
    'BRAC_API DWORD BRAC_SetServerAuthPass(LPCTSTR lpPassword);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetServerAuthPass", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetServerAuthPass(ByVal lpPassword As String) As Integer
    End Function

    '// 初始化系统
    'BRAC_API DWORD BRAC_InitSDK(HWND hWnd, DWORD dwFuncMode);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_InitSDK", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_InitSDK(ByVal hwnd As IntPtr, ByVal dwFuncMode As Integer) As Integer
    End Function

    '// 视频图像格式定义
    'enum BRAC_PixelFormat{
    'BRAC_PIX_FMT_RGB24 = 0,						///< Packed RGB 8:8:8, 24bpp, RGBRGB...（MEDIASUBTYPE_RGB24）
    'BRAC_PIX_FMT_RGB32,							///< 对应于：MEDIASUBTYPE_RGB32，Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
    'BRAC_PIX_FMT_YV12,							///< 对应于：MEDIASUBTYPE_YV12，Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
    'BRAC_PIX_FMT_YUY2,							///< 对应于：MEDIASUBTYPE_YUY2，Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
    '};
    Public Enum BRAC_PixelFormat
        BRAC_PIX_FMT_RGB24 = 0
        BRAC_PIX_FMT_RGB32
        BRAC_PIX_FMT_YV12
        BRAC_PIX_FMT_YUY2
    End Enum
    '// 设置视频数据回调函数
    'BRAC_API DWORD BRAC_SetVideoDataCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetVideoDataCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetVideoDataCallBack(ByVal pixFmt As BRAC_PixelFormat, ByVal lpFunction As BRAC_VideoData_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function

    '// 设置音频数据回调函数
    'BRAC_API DWORD BRAC_SetAudioDataCallBack(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetAudioDataCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetAudioDataCallBack(ByVal lpFunction As BRAC_AudioData_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function
    

    '// 设置文字消息回调函数
    'BRAC_API DWORD BRAC_SetTextMessageCallBack(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetTextMessageCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetTextMessageCallBack(ByVal lpFunction As BRAC_TextMessage_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function

    '// 设置透明通道数据回调函数
    'BRAC_API DWORD BRAC_SetTransBufferCallBack(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetTransBufferCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetTransBufferCallBack(ByVal lpFunction As BRAC_TransBuffer_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function

    '// 设置透明通道数据扩展回调函数
    'BRAC_API DWORD BRAC_SetTransBufferExCallBack(BRAC_TransBufferEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetTransBufferExCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetTransBufferExCallBack(ByVal lpFunction As BRAC_TransBufferEx_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function

    '// 设置文件传输回调函数
    'BRAC_API DWORD BRAC_SetTransFileCallBack(BRAC_TransFile_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetTransFileCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetTransFileCallBack(ByVal lpFunction As BRAC_TransFile_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function

    '// 设置音量变化回调函数
    'BRAC_API DWORD BRAC_SetVolumeChangeCallBack(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetVolumeChangeCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetVolumeChangeCallBack(ByVal lpFunction As BRAC_VolumeChange_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function

    '// 设置SDK Filter通信数据回调函数定义
    'BRAC_API DWORD BRAC_SetSDKFilterDataCallBack(BRAC_SDKFilterData_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetSDKFilterDataCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetSDKFilterDataCallBack(ByVal lpFunction As BRAC_SDKFilterData_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function

    '// 设置录像快照任务完成通知回调函数
    'BRAC_API DWORD BRAC_SetRecordSnapShotCallBack(BRAC_RecordSnapShot_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetRecordSnapShotCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetRecordSnapShotCallBack(ByVal lpFunction As BRAC_RecordSnapShot_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function

    '// 设置异步消息通知回调函数
    'BRAC_API DWORD BRAC_SetNotifyMessageCallBack(BRAC_NotifyMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetNotifyMessageCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetNotifyMessageCallBack(ByVal lpFunction As BRAC_NotifyMessage_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function

	'// 设置视频通话消息通知回调函数
	'BRAC_API DWORD BRAC_SetVideoCallEventCallBack(BRAC_VideoCallEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);
	<DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetVideoCallEventCallBack", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetVideoCallEventCallBack(ByVal lpFunction As BRAC_VideoCallEvent_CallBack, ByVal lpUserValue As IntPtr) As Integer
    End Function


    '// 连接服务器
    'BRAC_API DWORD BRAC_Connect(LPCTSTR lpServerAddr, DWORD dwPort);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_Connect", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_Connect(ByVal lpServerAddr As String, ByVal dwPort As Integer) As Integer
    End Function

    '// 登录系统
    'BRAC_API DWORD BRAC_Login(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_Login", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_Login(ByVal lpUserName As String, ByVal lpPassword As String, ByVal dwPassEntype As Integer) As Integer
    End Function

    '// 进入房间
    'BRAC_API DWORD BRAC_EnterRoom(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_EnterRoom", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_EnterRoom(ByVal dwRoomId As Integer, ByVal lpRoomPass As String, ByVal dwPassEncType As Integer) As Integer
    End Function

    '// 进入房间
    'BRAC_API DWORD BRAC_EnterRoomEx(LPCTSTR lpRoomName, LPCTSTR lpRoomPass);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_EnterRoomEx", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_EnterRoomEx(ByVal lpRoomName As String, ByVal lpRoomPass As String) As Integer
    End Function

    '// 离开房间
    'BRAC_API DWORD BRAC_LeaveRoom(DWORD dwRoomid);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_LeaveRoom", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_LeaveRoom(ByVal dwRoomId As Integer) As Integer
    End Function

    '// 注销系统
    'BRAC_API DWORD BRAC_Logout(VOID);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_Logout", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_Logout() As Integer
    End Function

    '// 释放所有资源
    'BRAC_API DWORD BRAC_Release(VOID);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_Release", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_Release() As Integer
    End Function

    '// 获取当前房间在线用户列表
    'BRAC_API DWORD BRAC_GetOnlineUser(LPDWORD lpUserIDArray, DWORD& dwUserNum);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetOnlineUser", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetOnlineUser(ByRef lpUserIDArray As Integer, ByRef dwUserNum As Integer) As Integer
    End Function

    '// 查询用户摄像头的状态
    'BRAC_API DWORD BRAC_GetCameraState(DWORD dwUserid, DWORD& dwState);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetCameraState", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetCameraState(ByVal dwUserid As Integer, ByRef dwState As Integer) As Integer
    End Function

    '// 查询用户发言状态
    'BRAC_API DWORD BRAC_GetSpeakState(DWORD dwUserid, DWORD& dwState);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetSpeakState", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetSpeakState(ByVal dwUserid As Integer, ByRef dwState As Integer) As Integer
    End Function

    '// 查询用户级别
    'BRAC_API DWORD BRAC_GetUserLevel(DWORD dwUserid, DWORD& dwLevel);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetUserLevel", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetUserLevel(ByVal dwUserid As Integer, ByRef dwLevel As Integer) As Integer
    End Function

    '注意：这里将CHAR*类型的参数lpUserName声明为类型IntPtr，请使用Marshal.StringToHGlobalAnsi函数将一个托管的String字符串复制并返回一个非托管的缓冲区指针。注意，请记得使用Marshal.FreeHGlobal释放该指针。
    '// 查询用户名称
    'BRAC_API DWORD BRAC_GetUserName(DWORD dwUserid, CHAR* lpUserName, DWORD dwLen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetUserName", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetUserName(ByVal dwUserid As Integer, ByVal lpUserName As IntPtr, ByVal dwLen As Integer) As Integer
    End Function

    '// 查询房间名称
    'BRAC_API DWORD BRAC_GetRoomName(DWORD dwRoomId, CHAR* lpRoomName, DWORD dwLen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetRoomName", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetRoomName(ByVal dwRoomId As Integer, ByVal lpRoomName As String, ByVal dwLen As Integer) As Integer
    End Function

    '// 显示本地视频画面调节对话框
    'BRAC_API DWORD BRAC_ShowLVProperty(HWND hParent, LPCTSTR szCaption=NULL, DWORD dwX=0, DWORD dwY=0);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_ShowLVProperty", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_ShowLVProperty(ByVal hParent As IntPtr, ByVal szCaption As String, ByVal dwX As Integer, ByVal dwY As Integer) As Integer
    End Function

    '注意：这里将char FAR*类型的参数infoval声明为类型IntPtr，请使用Marshal.StringToHGlobalAnsi函数将一个托管的String字符串复制并返回一个非托管的缓冲区指针。注意，请记得使用Marshal.FreeHGlobal释放该指针。
    '// 查询指定用户相关状态
    'BRAC_API DWORD BRAC_QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_QueryUserState", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_QueryUserState(ByVal dwUserid As Integer, ByVal infoname As Integer, ByVal infoval As IntPtr, ByVal infolen As Integer) As Integer
    End Function

    '注意：SDK里并没有BRAC_QueryuserStateEx这个函数，这里只是为了方便对DWORD类型的infoval参数的BRAC_QueryUserState函数的调用所定义的该函数的另一个签名
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_QueryUserState", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_QueryUserStateEx(ByVal dwUserid As Integer, ByVal infoname As Integer, ByRef infoval As Integer, ByVal infolen As Integer) As Integer
    End Function

    '注意：这里将CHAR**类型的参数lpDeviceName定义为引用传递的IntPtr类型,请注意这里传递回来的CHAR*指针所指缓冲区为函数在内部所分配，应注意手工释放该缓冲区，具体请参见相应SDK文档
    '// 枚举本地视频采集设备
    'BRAC_API DWORD BRAC_EnumVideoCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_EnumVideoCapture", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_EnumVideoCapture(ByRef lpDeviceName As IntPtr, ByRef dwDeviceNum As Integer) As Integer
    End Function

    '// 选择指定的视频采集设备
    'BRAC_API DWORD BRAC_SelectVideoCapture(LPCTSTR szCaptureName);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SelectVideoCapture", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SelectVideoCapture(ByVal szCaptureName As Integer) As Integer
    End Function


    '注意：这里将CHAR*类型的参数lpDeviceName声明为IntPtr类型，请使用Marshal.StringToHGlobalAnsi函数讲一个托管的String字符串复制并返回一个非托管的缓冲区指针。注意，请记得使用Marshal.FreeHGlobal释放该指针。
    '// 获取当前使用的视频采集设备
    'BRAC_API DWORD BRAC_GetCurVideoCapture(CHAR* lpDeviceName, DWORD dwLen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetCurVideoCapture", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetCurVideoCapture(ByVal lpDeviceName As IntPtr, ByVal dwLen As Integer) As Integer
    End Function

    '注意：这里将CHAR**类型的参数lpDeviceName定义为引用传递的IntPtr类型,请注意这里传递回来的CHAR*指针所指缓冲区为函数在内部所分配，应注意手工释放该缓冲区，具体请参见相应SDK文档
    '// 枚举本地音频采集设备
    'BRAC_API DWORD BRAC_EnumAudioCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_EnumAudioCapture", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_EnumAudioCapture(ByRef lpDeviceName As IntPtr, ByRef dwDeviceNum As Integer) As Integer
    End Function

    '// 选择指定的音频采集设备
    'BRAC_API DWORD BRAC_SelectAudioCapture(LPCTSTR szCaptureName);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SelectAudioCapture", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SelectAudioCapture(ByVal szCaptureName As String) As Integer
    End Function

    '注意：这里将CHAR*类型的参数lpDeviceName声明为IntPtr类型，请使用Marshal.StringToHGlobalAnsi函数讲一个托管的String字符串复制并返回一个非托管的缓冲区指针。注意，请记得使用Marshal.FreeHGlobal释放该指针。
    '// 获取当前使用的音频采集设备
    'BRAC_API DWORD BRAC_GetCurAudioCapture(CHAR* lpDeviceName, DWORD dwLen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetCurAudioCapture", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetCurAudioCapture(ByVal lpDeviceName As IntPtr, ByVal dwLen As Integer) As Integer
    End Function

    '// 操作用户视频
    'BRAC_API DWORD BRAC_UserCameraControl(DWORD dwUserid, BOOL bOpen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_UserCameraControl", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_UserCameraControl(ByVal dwUserid As Integer, ByVal bOpen As Integer) As Integer
    End Function

    '// 操作用户语音
    'BRAC_API DWORD BRAC_UserSpeakControl(DWORD dwUserid, BOOL bOpen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_UserSpeakControl", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_UserSpeakControl(ByVal dwUserid As Integer, ByVal bOpen As Integer) As Integer
    End Function

    '// 设置视频显示位置
    'BRAC_API DWORD BRAC_SetVideoPos(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetVideoPos", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetVideoPos(ByVal dwUserid As Integer, ByVal hwnd As IntPtr, ByVal dwLeft As Integer, ByVal dwTop As Integer, ByVal dwRight As Integer, ByVal dwBottom As Integer) As Integer
    End Function

    '// 获取指定音频设备的当前音量
    'BRAC_API DWORD BRAC_AudioGetVolume(BRAC_AudioDevice device, DWORD& dwVolume);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_AudioGetVolume", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_AudioGetVolume(ByVal device As Integer, ByRef dwVolume As Integer) As Integer
    End Function

    '// 设置指定音频设备的音量
    'BRAC_API DWORD BRAC_AudioSetVolume(BRAC_AudioDevice device, DWORD dwVolume);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_AudioSetVolume", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_AudioSetVolume(ByVal device As BRAC_AudioDevice, ByVal dwVolume As Integer) As Integer
    End Function


    '// 用户音、视频录制
    'BRAC_API DWORD BRAC_StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_StreamRecordCtrl", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_StreamRecordCtrl(ByVal dwuserId As Integer, ByVal bStartRecord As Integer, ByVal dwFlags As Integer, ByVal dwParam As Integer) As Integer
    End Function


    '// 对用户的视频进行抓拍（快照）
    'BRAC_API DWORD BRAC_SnapShot(DWORD dwUserId, DWORD dwFlags, DWORD dwParam);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SnapShot", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SnapShot(ByVal dwuserId As Integer, ByVal dwFlags As Integer, ByVal dwParam As Integer) As Integer
    End Function

    '// 透明通道传送缓冲区
    'BRAC_API DWORD BRAC_TransBuffer(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_TransBuffer", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_TransBuffer(ByVal dwUserid As Integer, ByVal lpBuf As Byte(), ByVal dwLen As Integer) As Integer
    End Function

    '// 透明通道传送缓冲区扩展
    'BRAC_API DWORD BRAC_TransBufferEx(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_TransBufferEx", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_TransBufferEx(ByVal dwUserid As Integer, ByVal lpBuf As Byte(), ByVal dwLen As Integer, ByVal wParam As Integer, ByVal lParam As Integer, ByVal dwFlags As Integer, ByRef dwTaskId As Integer) As Integer
    End Function

    '// 传送文件
    'BRAC_API DWORD BRAC_TransFile(DWORD dwUserid, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_TransFile", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_TransFile(ByVal dwUserid As Integer, ByVal lpLocalPathName As String, ByVal wParam As Integer, ByVal lParam As Integer, ByVal dwFlags As Integer, ByRef dwTaskId As Integer) As Integer
    End Function

    '注意：这个函数的声明需要验证
    '// 查询传输任务相关信息
    'BRAC_API DWORD BRAC_QueryTransTaskInfo(DWORD dwUserid, DWORD dwTaskId, int infoname, char FAR* infoval, int infolen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_QueryTransTaskInfo", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_QueryTransTaskInfo(ByVal dwUserid As Integer, ByVal dwTaskId As Integer, ByVal infoname As Integer, ByVal infoval As Byte(), ByVal infolen As Integer) As Integer
    End Function

    '// 取消传输任务
    'BRAC_API DWORD BRAC_CancelTransTask(DWORD dwUserid, DWORD dwTaskId);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_CancelTransTask", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_CancelTransTask(ByVal dwUserid As Integer, ByVal dwTaskId As Integer) As Integer
    End Function

    '// 传送文本消息
    'BRAC_API DWORD BRAC_SendTextMessage(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SendTextMessage", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SendTextMessage(ByVal dwUserid As Integer, ByVal bSecret As Integer, ByVal lpMsgBuf As String, ByVal dwLen As Integer) As Integer
    End Function

    '// 发送SDK Filter 通信数据
    'BRAC_API DWORD BRAC_SendSDKFilterData(LPBYTE lpBuf, DWORD dwLen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SendSDKFilterData", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SendSDKFilterData(ByVal lpbuf As Byte(), ByVal dwLen As Integer) As Integer
    End Function

    '// 更改当前的聊天模式
    'BRAC_API DWORD BRAC_ChangeChatMode(DWORD dwChatMode);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_ChangeChatMode", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_ChangeChatMode(ByVal dwChatMode As Integer) As Integer
    End Function

    '// 获取指定用户当前的聊天模式
    'BRAC_API DWORD BRAC_GetUserChatMode(DWORD dwUserid, DWORD& dwChatMode);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetUserChatMode", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetUserChatMode(ByVal dwUserid As Integer, ByRef dwChatMode As Integer) As Integer
    End Function

    '// 请求与对方私聊，向对方发起私聊请求
    'BRAC_API DWORD BRAC_PrivateChatRequest(DWORD dwUserid);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_PrivateChatRequest", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_PrivateChatRequest(ByVal dwUserid As Integer) As Integer
    End Function

    '// 回复对方的私聊请求
    'BRAC_API DWORD BRAC_PrivateChatEcho(DWORD dwUserid, DWORD dwRequestid,BOOL bAccept);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_PrivateChatEcho", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_PrivateChatEcho(ByVal dwUserid As Integer, ByVal dwRequestid As Integer, ByVal bAccept As Integer) As Integer
    End Function

    '// 回复对方的私聊请求（扩展，可以附带出错代码）
    'BRAC_API DWORD BRAC_PrivateChatEchoEx(DWORD dwUserid, DWORD dwRequestid,DWORD dwErrorCode);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_PrivateChatEchoEx", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_PrivateChatEchoEx(ByVal dwUserid As Integer, ByVal dwRequestid As Integer, ByVal dwErrorCode As Integer) As Integer
    End Function

    '// 退出与某用户的私聊，或者将某用户从自己的私聊列表中清除
    'BRAC_API DWORD BRAC_PrivateChatExit(DWORD dwUserid);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_PrivateChatExit", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_PrivateChatExit(ByVal dwUserid As Integer) As Integer
    End Function

    '// SDK内核参数设置
    'BRAC_API DWORD BRAC_SetSDKOption(int optname, const char FAR* optval, int optlen);
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetSDKOption", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetSDKOption(ByVal optname As Integer, ByVal optval As String, ByVal optlen As Integer) As Integer
    End Function

    '注意：SDK里并没有BRAC_SetSDKOptionsEx这个函数，这里只是为了方便调用类型为DWORD的参数optval的函数BRAC_SetSDKOption函数而定义的一个签名
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_SetSDKOption", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_SetSDKOptionEx(ByVal optname As Integer, ByRef optval As Integer, ByVal optlen As Integer) As Integer
    End Function

    '注意：这里将类型为char FAR*的参数optval声明为类型IntPrt,请使用Marshal.StringToHGlobalAnsi函数将一个托管的String字符串复制并返回一个非托管的缓冲区
    '// SDK内核参数状态查询
    'BRAC_API DWORD BRAC_GetSDKOption(int optname, char FAR* optval, int optlen);
    <DllImport(AnyChatSDKDLL, entryPoint:="BRAC_GetSDKOption", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetSDKOption(ByVal optname As Integer, ByVal optval As IntPtr, ByVal optlen As Integer) As Integer
    End Function

    '注意：SDK里并没有BRAC_GetSDKOptionsEx这个函数，这里只是为了方便调用类型为DWORD的参数optval的函数BRAC_GetSDKOption函数而定义的一个签名
    <DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_GetSDKOption", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_GetSDKOptionEx(ByVal optname As Integer, ByRef optval As Integer, ByVal optlen As Integer) As Integer
    End Function
	
	'// 视频呼叫事件控制（请求、回复、挂断等）
	'BRAC_API DWORD BRAC_VideoCallControl(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags=0, DWORD dwParam=0, LPCTSTR lpUserStr=NULL);
	<DllImport(AnyChatSDKDLL, EntryPoint:="BRAC_VideoCallControl", CallingConvention:=CallingConvention.Cdecl)> _
    Function BRAC_VideoCallControl(ByVal dwEventType As Integer, ByVal dwUserId As Integer, ByVal dwErrorCode As Integer, ByVal dwFlags As Integer, ByVal dwParam As Integer, ByVal lpUserStr As String) As Integer
    End Function
	
End Module