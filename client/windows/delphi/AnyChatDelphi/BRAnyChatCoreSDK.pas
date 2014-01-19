unit BRAnyChatCoreSDK;
(****************************************************************************
     BRAnyChatCoreSDK.h
****************************************************************************)

interface
uses
  Windows,MMSystem,SysUtils,Messages,Classes,Types,Graphics,
  GVMessageDefine,GVErrorCodeDefine,GVSDK;

const
  C_BRAnyChatCoreLibName = 'BRAnyChatCore.dll';

  // 视频图像格式定义
type BRAC_PixelFormat=(
	          BRAC_PIX_FMT_RGB24 = 0,			///< Packed RGB 8:8:8, 24bpp, RGBRGB...（MEDIASUBTYPE_RGB24）
	          BRAC_PIX_FMT_RGB32,				///< 对应于：MEDIASUBTYPE_RGB32，Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
	          BRAC_PIX_FMT_YV12,				///< 对应于：MEDIASUBTYPE_YV12，Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	          BRAC_PIX_FMT_YUY2					///< 对应于：MEDIASUBTYPE_YUY2，Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
     );

  // 音频设备定义
type BRAC_AudioDevice=(
	        BRAC_AD_WAVEIN = 0,					///< 输入设备：Mic
          	BRAC_AD_WAVEOUT			     		///< 输出设备：Wave
     );


  // 功能模式定义
const
  BRAC_FUNC_VIDEO_CBDATA		=$00000001;		///< 通过回调函数输出视频数据
  BRAC_FUNC_VIDEO_AUTODISP		=$00000002;		///< 由SDK包处理视频，将视频显示在指定的窗口上
  BRAC_FUNC_AUDIO_CBDATA		=$00000004;		///< 通过顺调函数输出音频数据
  BRAC_FUNC_AUDIO_AUTOPLAY		=$00000008;		///< 由SDK包处理音频，直接播放
  BRAC_FUNC_CONFIG_LOCALINI 	=$00000010;		///< 生成本地配置文件（AnyChatSDK.ini）
  BRAC_FUNC_FIREWALL_OPEN   	=$00000020;		///< 允许SDK操作Windows防火墙，将当前应用程序加入防火墙访问列表（避免Windows提示用户是否阻止当前应用程序）
  BRAC_FUNC_CHKDEPENDMODULE   	=$00000040;		///< 自动检查SDK所依赖的组件，并自动注册
  BRAC_FUNC_AUDIO_VOLUMECALC  	=$00000080;		///< 由SDK自动计算语音的音量
  BRAC_FUNC_AUDIO_AUTOVOLUME  	=$00000100;		///< 允许SDK自动控制Mic录音音量
  BRAC_FUNC_NET_SUPPORTUPNP   	=$00000200;		///< 允许SDK打开用户网络中的UPNP设备，如果用户的路由器或是防火墙支持UPNP协议，则可提高P2P打洞的成功率
  BRAC_FUNC_DISABLEDECODE		=$00000400;		///< 禁止对收到的数据进行解码和播放，为了提高代理客户端的数据转发性能，可设置该标志，否则不能设置该标志

  //内核参数定义
  BRAC_SO_AUDIO_VADCTRL			=1;	  		    ///< 音频静音检测控制（参数为：int型：1打开，0关闭）
  BRAC_SO_AUDIO_NSCTRL			=2;	    		///< 音频噪音抑制控制（参数为：int型：1打开，0关闭）
  BRAC_SO_AUDIO_ECHOCTRL		=3;	   		    ///< 音频回音消除控制（参数为：int型：1打开，0关闭）
  BRAC_SO_AUDIO_AGCCTRL			=4;	  			///< 音频自动增益控制（参数为：int型：1打开，0关闭）
  BRAC_SO_AUDIO_CPATUREMODE		=5;				///< 音频采集模式设置（参数为：int型：0 发言模式，1 放歌模式，2 卡拉OK模式，3 线路输入模式）
  BRAC_SO_AUDIO_MICBOOST		=6;				///< 音频采集Mic增强控制（参数为：int型：0 取消，1 选中，2 设备不存在[查询时返回值]）
  BRAC_SO_AUDIO_AUTOPARAM		=7;				///< 根据音频采集模式，自动选择合适的相关参数，包括编码器、采样参数、码率参数等（参数为int型：1 启用，0 关闭[默认]）
  BRAC_SO_AUDIO_MONOBITRATE		=8;				///< 设置单声道模式下音频编码目标码率（参数为：int型，单位：bps）
  BRAC_SO_AUDIO_STEREOBITRATE	=9;				///< 设置双声道模式下音频编码目标码率（参数为：int型，单位：bps）
  BRAC_SO_AUDIO_PLAYDRVCTRL		=70;			///< 音频播放驱动选择（参数为：int型，0默认驱动， 1 DSound驱动， 2 WaveOut驱动）
  BRAC_SO_AUDIO_CNGCTRL			=71;			///< 舒适噪音生成控制（参数为：int型：1打开，0关闭）
  BRAC_SO_AUDIO_SOFTVOLMODE		=73;			///< 设置软件音量模式控制（参数为int型，1打开，0关闭[默认]），使用软件音量模式，将不会改变系统的音量设置
  BRAC_SO_AUDIO_RECORDDRVCTRL	=74;			///< 音频采集驱动控制（参数为int型，0默认驱动， 1 DSound驱动， 2 WaveIn驱动， 3 Java采集[Android平台使用]）

  BRAC_SO_RECORD_VIDEOBR		=10;	 		///< 录像视频码率设置（参数为：int型，单位：bps）
  BRAC_SO_RECORD_AUDIOBR		=11;	  		///< 录像音频码率设置（参数为：int型，单位：bps）
  BRAC_SO_RECORD_TMPDIR			=12;	 		///< 录像文件临时目录设置（参数为字符串PCHAR类型）
  BRAC_SO_SNAPSHOT_TMPDIR		=13;	 		///< 快照文件临时目录设置（参数为字符串PCHAR类型）
  BRAC_SO_CORESDK_TMPDIR		=14;	  		///< 设置AnyChat Core SDK临时目录（参数为字符串PCHAR类型）
  BRAC_SO_CORESDK_PATH			=20;	  		///< 设置AnyChat Core SDK相关组件路径（参数为字符串PCHAR类型）
  BRAC_SO_CORESDK_DUMPCOREINFO	=21;			///< 输出内核信息到日志文件中，便于分析故障原因（参数为：int型：1 输出）
  BRAC_SO_CORESDK_EXTVIDEOINPUT	=26;			///< 外部扩展视频输入控制（参数为int型， 0 关闭外部视频输入[默认]， 1 启用外部视频输入）
  BRAC_SO_CORESDK_EXTAUDIOINPUT	=27;			///< 外部扩展音频输入控制（参数为int型， 0 关闭外部音频输入[默认]， 1 启用外部音频输入）

  BRAC_SO_LOCALVIDEO_BITRATECTRL	=30;		///< 本地视频编码码率设置（参数为int型，单位bps，同服务器配置：VideoBitrate）
  BRAC_SO_LOCALVIDEO_QUALITYCTRL	=31;		///< 本地视频编码质量因子控制（参数为int型，同服务器配置：VideoQuality）
  BRAC_SO_LOCALVIDEO_GOPCTRL		=32;		///< 本地视频编码关键帧间隔控制（参数为int型，同服务器配置：VideoGOPSize）
  BRAC_SO_LOCALVIDEO_FPSCTRL		=33;		///< 本地视频编码帧率控制（参数为int型，同服务器配置：VideoFps）
  BRAC_SO_LOCALVIDEO_PRESETCTRL		=34;		///< 本地视频编码预设参数控制（参数为int型，1-5）
  BRAC_SO_LOCALVIDEO_APPLYPARAM		=35;		///< 应用本地视频编码参数，使得前述修改即时生效（参数为int型：1 使用新参数，0 使用默认参数）
  BRAC_SO_LOCALVIDEO_VIDEOSIZEPOLITIC=36;		///< 本地视频采集分辩率控制策略（参数为int型，0 自动向下逐级匹配[默认]；1 使用采集设备默认分辩率），当配置的分辩率不被采集设备支持时有效
  BRAC_SO_LOCALVIDEO_DEINTERLACE	=37;		///< 本地视频反交织参数控制（参数为int型： 0 不进行反交织处理[默认]；1 反交织处理），当输入视频源是隔行扫描源（如电视信号）时通过反交织处理可以提高画面质量
  BRAC_SO_LOCALVIDEO_WIDTHCTRL		=38;		///< 本地视频采集分辨率宽度控制（参数为int型，同服务器配置：VideoWidth）
  BRAC_SO_LOCALVIDEO_HEIGHTCTRL		=39;		///< 本地视频采集分辨率高度控制（参数为int型，同服务器配置：VideoHeight）
  BRAC_SO_LOCALVIDEO_TVFORMAT		=104;		///< 视频采集制式设置（参数为：int型，定义为DirectShow::strmif.h::AnalogVideoStandard，默认为：AnalogVideo_PAL_B）

  BRAC_SO_NETWORK_P2PPOLITIC		=40;		///< 本地网络P2P策略控制（参数为：int型：0 禁止本地P2P，1 服务器控制P2P[默认]，2 上层应用控制P2P连接，3 按需建立P2P连接）
  BRAC_SO_NETWORK_P2PCONNECT		=41;		///< 尝试与指定用户建立P2P连接（参数为int型，表示目标用户ID），连接建立成功后，会通过消息反馈给上层应用，P2P控制策略=2时有效
  BRAC_SO_NETWORK_P2PBREAK			=42;		///< 断开与指定用户的P2P连接（参数为int型，表示目标用户ID）[暂不支持，保留]
  BRAC_SO_NETWORK_TCPSERVICEPORT	=43;		///< 设置本地TCP服务端口（参数为int型），连接服务器之前设置有效
  BRAC_SO_NETWORK_UDPSERVICEPORT	=44;		///< 设置本地UDP服务端口（参数为int型），连接服务器之前设置有效
  BRAC_SO_NETWORK_MULTICASTPOLITIC	=45;		///< 组播策略控制（参数为int型：0 执行服务器路由策略，禁止组播发送[默认]， 1 忽略服务器路由策略，只向组播组广播媒体流， 2 执行服务器路由策略，同时组播）
  BRAC_SO_NETWORK_TRANSBUFMAXBITRATE=46;		///< 传输缓冲区、文件最大码率控制（参数为int型，0 不限制，以最快速率传输[默认]， 否则表示限制码率，单位为：bps）

  BRAC_SO_PROXY_FUNCTIONCTRL	=50;			///< 本地用户代理功能控制，（参数为：int型，1启动代理，0关闭代理[默认]）
  BRAC_SO_PROXY_VIDEOCTRL		=51;			///< 本地用户代理视频控制，将本地视频变为指定用户的视频对外发布（参数为int型，表示其它用户的userid）
  BRAC_SO_PROXY_AUDIOCTRL		=52;			///< 本地用户代理音频控制，将本地音频变为指定用户的音频对外发布（参数同BRAC_SO_PROXY_VIDEOCTRL） 
  
  BRAC_SO_STREAM_MAXBUFFERTIME	=60;			///< 最大流缓冲时间（参数为int型，单位：毫秒，取值范围：500 ~ 5000，默认：800），发言模式设置值，歌曲模式会自动增加一倍
  BRAC_SO_STREAM_SMOOTHPLAYMODE =61;			///< 平滑播放模式（参数为int型，0 关闭[默认], 1 打开），打开状态下遇到视频丢帧时会继续播放（可能出现马赛克），不会卡住
  
  // 传输任务信息参数定义
  BRAC_TRANSTASK_PROGRESS		=1;	   			///< 传输任务进度查询（参数为：DOUBLE型（0.0 ~ 100.0））
  BRAC_TRANSTASK_BITRATE		=2;				///< 传输任务当前传输码率（参数为：int型，单位：bps）
  BRAC_TRANSTASK_STATUS			=3;				///< 传输任务当前状态（参数为：int型）
  BRAC_TRANSTASK_SAVEASPATH		=4;				///< 文件传输任务另存为路径设置（参数为字符串TCHAR类型）

  // 录像功能标志定义
  BRAC_RECORD_FLAGS_VIDEO		=$00000001;		///< 录制视频
  BRAC_RECORD_FLAGS_AUDIO		=$00000002;		///< 录制音频
  BRAC_RECORD_FLAGS_SERVER		=$00000004;		///< 服务器端录制
  BRAC_RECORD_FLAGS_MIXAUDIO	=$00000010;		///< 录制音频时，将其它人的声音混音后录制
  BRAC_RECORD_FLAGS_MIXVIDEO	=$00000020;		///< 录制视频时，将其它人的视频迭加后录制

  // 用户状态标志定义
  BRAC_USERSTATE_CAMERA			=1;				///< 用户摄像头状态（参数为DWORD型）
  BRAC_USERSTATE_HOLDMIC		=2;				///< 用户音频设备状态（参数为DWORD型，返回值：0 音频采集关闭， 1 音频采集开启）
  BRAC_USERSTATE_SPEAKVOLUME	=3;				///< 用户当前说话音量（参数为DOUBLE类型（0.0 ~ 100.0））
  BRAC_USERSTATE_RECORDING		=4;				///< 用户录像（音）状态（参数为DWORD型）
  BRAC_USERSTATE_LEVEL			=5;				///< 用户级别（参数为DWORD型）
  BRAC_USERSTATE_NICKNAME		=6;				///< 用户昵称（参数为字符串PCHAR类型）
  BRAC_USERSTATE_LOCALIP		=7;				///< 用户本地IP地址（内网，参数为字符串PCHAR类型）
  BRAC_USERSTATE_INTERNETIP		=8;				///< 用户互联网IP地址（参数为字符串PCHAR类型）
  BRAC_USERSTATE_VIDEOBITRATE	=9;				///< 用户当前的视频码率（参数为DWORD类型，Bps）
  BRAC_USERSTATE_AUDIOBITRATE	=10;			///< 用户当前的音频码率（参数为DWORD类型，Bps）
  BRAC_USERSTATE_P2PCONNECT		=11;			///< 查询本地用户与指定用户的当前P2P连接状态（参数为DWORD类型，返回值：0 P2P不通， 1 P2P连接成功[TCP]，2 P2P连接成功[UDP]，3 P2P连接成功[TCP、UDP]）
  BRAC_USERSTATE_PACKLOSSRATE	=14;			///< 查询指定用户的网络流媒体数据丢包率（参数为DWORD类型，返回值：0 - 100，如：返回值为5，表示丢包率为5%）
  BRAC_USERSTATE_DEVICETYPE		=15;			///< 查询指定用户的终端类型（参数为DWORD类型，返回值：0 Unknow， 1 Windows，2 Android，3 iOS，4 Web，5 Linux，6 Mac，7 Win Phone，8 WinCE）
  BRAC_USERSTATE_SELFUSERSTATUS	=16;			///< 查询本地用户的当前状态（参数为DWORD类型，返回值：0 Unknow，1 Connected，2 Logined，3 In Room，4 Logouted，5 Link Closed）
  BRAC_USERSTATE_SELFUSERID		=17;			///< 查询本地用户的ID（参数为DWORD类型，若用户登录成功，返回用户实际的userid，否则返回-1）

  // 视频呼叫事件类型定义（API：BRAC_VideoCallControl 传入参数、VideoCallEvent回调参数）
  BRAC_VIDEOCALL_EVENT_REQUEST	=1;				///< 呼叫请求
  BRAC_VIDEOCALL_EVENT_REPLY	=2;				///< 呼叫请求回复
  BRAC_VIDEOCALL_EVENT_START	=3;				///< 视频呼叫会话开始事件
  BRAC_VIDEOCALL_EVENT_FINISH	=4;				///< 挂断（结束）呼叫会话

  // 视频呼叫标志定义（API：BRAC_VideoCallControl 传入参数）
  BRAC_VIDEOCALL_FLAGS_AUDIO		=	$01;	///< 语音通话
  BRAC_VIDEOCALL_FLAGS_VIDEO		=	$02;	///< 视频通话
  BRAC_VIDEOCALL_FLAGS_FBSRCAUDIO	=	$10;	///< 禁止源（呼叫端）音频
  BRAC_VIDEOCALL_FLAGS_FBSRCVIDEO	=	$20;	///< 禁止源（呼叫端）视频
  BRAC_VIDEOCALL_FLAGS_FBTARAUDIO	=	$40;	///< 禁止目标（被呼叫端）音频
  BRAC_VIDEOCALL_FLAGS_FBTARVIDEO	=	$80;	///< 禁止目标（被呼叫端）视频


type
  // 视频数据回调函数定义
  BRAC_VideoData_CallBack=procedure(dwUserid:DWORD;lpBuf:Pointer;dwLen:DWORD; bmiHeader:BITMAPINFOHEADER;lpUserValue:Pointer);stdcall;
    
  // 音频数据回调函数定义
  BRAC_AudioData_CallBack=procedure(dwUserid:DWORD;lpBuf:Pointer;dwLen:DWORD; waveFormatEx:TWaveFormatEx;lpUserValue:Pointer);stdcall;
    
  // 文字消息回调函数定义
  BRAC_TextMessage_CallBack=procedure(dwFromUserid:DWORD;dwToUserid:DWORD; bSecret:BOOL;lpMsgBuf:LPCTSTR;dwLen:DWORD;lpUserValue:Pointer);stdcall;
    
  // 透明通道数据回调函数定义
  BRAC_TransBuffer_CallBack=procedure(dwUserid:DWORD;lpBuf:PByte;dwLen:DWORD; lpUserValue:Pointer);stdcall;

// 透明通道数据扩展回调函数定义
  BRAC_TransBufferEx_CallBack=procedure(dwUserid:DWORD;lpBuf:PByte;dwLen:DWORD;wParam:DWORD;lParam:DWORD; dwTaskId:DWORD;lpUserValue:Pointer);stdcall;
    
  // 音量变化回调函数定义
  BRAC_VolumeChange_CallBack=procedure(device:BRAC_AudioDevice;dwCurrentVolume:DWORD; lpUserValue:Pointer);stdcall;

  // 文件传输回调函数定义
  BRAC_TransFile_CallBack=procedure(dwUserid:DWORD;lpFileName:LPCTSTR;lpTempFilePath:LPCTSTR; dwFileLength:DWORD;wParam:DWORD;lParam:DWORD;dwTaskId:DWORD;lpUserValue:Pointer);stdcall;

  // SDK Filter 通信数据回调函数定义
  BRAC_SDKFilterData_CallBack=procedure(lpBuf:PByte;dwLen:DWORD;lpUserValue:Pointer);stdcall;
  
  // 录像、快照任务完成回调函数定义
  BRAC_RecordSnapShot_CallBack=procedure(dwUserid:DWORD;lpFileName:LPCTSTR; dwParam:DWORD;bRecordType:BOOL;lpUserValue:Pointer);stdcall;
    
  // 异步消息通知回调函数定义
  BRAC_NotifyMessage_CallBack=procedure(dwNotifyMsg:DWORD;wParam:DWORD;lParam:DWORD; lpUserValue:Pointer);stdcall;
	
  // 视频通话消息通知回调函数定义
  BRAC_VideoCallEvent_CallBack=procedure(dwEventType:DWORD; dwUserId:DWORD; dwErrorCode:DWORD; dwFlags:DWORD; dwParam:DWORD; lpUserStr:LPCTSTR; lpUserValue:Pointer);stdcall;

(**
 *	API方法定义
 *)

  // 获取SDK版本信息
  function BRAC_GetSDKVersion(var dwMainVer:DWORD;var dwSubVer:DWORD;lpCompileTime:LPSTR;dwBufLen:DWORD):DWORD;cdecl;

  // 激活（关闭）SDK调用日志
  function BRAC_ActiveCallLog(bActive:BOOL):DWORD;cdecl;
  
  // 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
  function BRAC_SetServerAuthPass(lpPassword:LPCTSTR):DWORD;cdecl;

  // 初始化系统
  function BRAC_InitSDK(hWnd:HWND;dwFuncMode:DWORD):DWORD;cdecl;
  

  // 设置视频数据回调函数
  function BRAC_SetVideoDataCallBack(pixFmt:BRAC_PixelFormat;lpFunction:BRAC_VideoData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置音频数据回调函数
  function BRAC_SetAudioDataCallBack(lpFunction:BRAC_AudioData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置文字消息回调函数
  function BRAC_SetTextMessageCallBack(lpFunction:BRAC_TextMessage_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置透明通道数据回调函数
  function BRAC_SetTransBufferCallBack(lpFunction:BRAC_TransBuffer_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置透明通道数据扩展回调函数
  function BRAC_SetTransBufferExCallBack(lpFunction:BRAC_TransBufferEx_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置文件传输回调函数
  function BRAC_SetTransFileCallBack(lpFunction:BRAC_TransFile_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置音量变化回调函数
  function BRAC_SetVolumeChangeCallBack(lpFunction:BRAC_VolumeChange_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置SDK Filter通信数据回调函数定义
  function BRAC_SetSDKFilterDataCallBack(lpFunction:BRAC_SDKFilterData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置录像快照任务完成通知回调函数
  function BRAC_SetRecordSnapShotCallBack(lpFunction:BRAC_RecordSnapShot_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置异步消息通知回调函数
  function BRAC_SetNotifyMessageCallBack(lpFunction:BRAC_NotifyMessage_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
  // 设置视频通话消息通知回调函数
  function BRAC_SetVideoCallEventCallBack(lpFunction:BRAC_VideoCallEvent_CallBack; lpUserValue:Pointer=nil):DWORD;cdecl;


  // 连接服务器
  function BRAC_Connect(lpServerAddr:LPCTSTR;dwPort:DWORD):DWORD;cdecl;
  // 登录系统
  function BRAC_Login(lpUserName:LPCTSTR;lpPassword:LPCTSTR;dwPassEncType:DWORD):DWORD;cdecl;
  // 进入房间
  function BRAC_EnterRoom(dwRoomid:DWORD;lpRoomPass:LPCTSTR;dwPassEncType:DWORD):DWORD;cdecl;
  // 进入房间
  function BRAC_EnterRoomEx(lpRoomName:LPCTSTR;lpRoomPass:LPCTSTR):DWORD;cdecl;
  // 离开房间
  function BRAC_LeaveRoom(dwRoomid:DWORD):DWORD;cdecl;
  // 注销系统
  function BRAC_Logout():DWORD;cdecl;
  // 释放所有资源
  function BRAC_Release():DWORD;cdecl;

  // 获取当前房间在线用户列表
  function BRAC_GetOnlineUser(lpUserIDArray:LPDWORD;var dwUserNum:DWORD):DWORD;cdecl;
  // 查询用户摄像头的状态
  function BRAC_GetCameraState(dwUserid:DWORD;var dwState:DWORD):DWORD;cdecl;
  // 查询用户发言状态
  function BRAC_GetSpeakState(dwUserid:DWORD;var dwState:DWORD):DWORD;cdecl;
  // 查询用户级别
  function BRAC_GetUserLevel(dwUserid:DWORD;var dwLevel:DWORD):DWORD;cdecl;
  // 查询用户名称
  function BRAC_GetUserName(dwUserid:DWORD;lpUserName:PChar;dwLen:DWORD):DWORD;cdecl;
  // 查询房间名称
  function BRAC_GetRoomName(dwRoomId:DWORD;lpRoomName:PChar;dwLen:DWORD):DWORD;cdecl;  
  // 显示本地视频画面调节对话框
  function BRAC_ShowLVProperty(hParent:THandle;szCaption:LPCTSTR=nil;dwX:DWORD=0;dwY:DWORD=0):DWORD;cdecl;
  // 查询指定用户相关状态
  function BRAC_QueryUserState(dwUserId:DWORD;infoname:Integer;infoval:Pointer;infolen:Integer):DWORD;cdecl;


  // 枚举本地视频采集设备
  function BRAC_EnumVideoCapture(lpDeviceName:PPChar;var dwDeviceNum:DWORD):DWORD;cdecl;
  // 选择指定的视频采集设备
  function BRAC_SelectVideoCapture(szCaptureName:LPCTSTR):DWORD;cdecl;
  // 获取当前使用的视频采集设备
  function BRAC_GetCurVideoCapture(lpDeviceName:PChar;dwLen:DWORD):DWORD;cdecl;
  // 枚举本地音频采集设备
  function BRAC_EnumAudioCapture(lpDeviceName:PPChar;var dwDeviceNum:DWORD):DWORD;cdecl;
  // 选择指定的音频采集设备
  function BRAC_SelectAudioCapture(szCaptureName:LPCTSTR):DWORD;cdecl;
  // 获取当前使用的音频采集设备
  function BRAC_GetCurAudioCapture(lpDeviceName:PChar;dwLen:DWORD):DWORD;cdecl;


  // 操作用户视频
  function BRAC_UserCameraControl(dwUserid:DWORD;bOpen:BOOL):DWORD;cdecl;
  // 操作用户语音
  function BRAC_UserSpeakControl(dwUserid:DWORD;bOpen:BOOL):DWORD;cdecl;
  // 设置视频显示位置
  function BRAC_SetVideoPos(dwUserid:DWORD;hWnd:THandle;dwLeft:DWORD;dwTop:DWORD;dwRight:DWORD;dwBottom:DWORD):DWORD;cdecl;

  // 获取指定音频设备的当前音量
  function BRAC_AudioGetVolume(device:BRAC_AudioDevice;var dwVolume:DWORD):DWORD;cdecl;
  // 设置指定音频设备的音量
  function BRAC_AudioSetVolume(device:BRAC_AudioDevice;dwVolume:DWORD):DWORD;cdecl;

  // 用户音、视频录制
  function BRAC_StreamRecordCtrl(dwUserId:DWORD;bStartRecord:BOOL;dwFlags:DWORD;dwParam:DWORD):DWORD;cdecl;
  // 对用户的视频进行抓拍（快照）
  function BRAC_SnapShot(dwUserId:DWORD;dwFlags:DWORD;dwParam:DWORD):DWORD;cdecl;
  

  // 透明通道传送缓冲区
  function BRAC_TransBuffer(dwUserid:DWORD;lpBuf:PBYTE;dwLen:DWORD):DWORD;cdecl;
  // 透明通道传送缓冲区扩展
  function BRAC_TransBufferEx(dwUserid:DWORD;lpBuf:PByte;dwLen:DWORD;wParam:DWORD;
    lParam:DWORD;dwFlags:DWORD;dwTaskId:PDWORD):DWORD;cdecl;
  // 传送文件
  function BRAC_TransFile(dwUserid:DWORD;lpLocalPathName:LPCTSTR;wParam:DWORD;
    lParam:DWORD;dwFlags:DWORD;dwTaskId:PDWORD):DWORD;cdecl;
  // 查询传输任务相关信息
  function BRAC_QueryTransTaskInfo(dwUserid:DWORD;dwTaskId:DWORD;infoname:Integer;
    infoval:Pointer;infolen:Integer):DWORD;cdecl;
  // 取消传输任务
  function BRAC_CancelTransTask(dwUserid:DWORD;dwTaskId:DWORD):DWORD;cdecl;
  // 传送文本消息
  function BRAC_SendTextMessage(dwUserid:DWORD;bSecret:BOOL;lpMsgBuf:LPCTSTR;
    dwLen:DWORD):DWORD;cdecl;
  // 发送SDK Filter 通信数据
  function BRAC_SendSDKFilterData(lpBuf:PByte;dwLen:DWORD):DWORD;cdecl;

  // 更改当前的聊天模式
  function BRAC_ChangeChatMode(dwChatMode:DWORD):DWORD;cdecl;
  // 获取指定用户当前的聊天模式
  function BRAC_GetUserChatMode(dwUserid:DWORD;var dwChatMode:DWORD):DWORD;cdecl;
  // 请求与对方私聊，向对方发起私聊请求
  function BRAC_PrivateChatRequest(dwUserid:DWORD):DWORD;cdecl;
  // 回复对方的私聊请求
  function BRAC_PrivateChatEcho(dwUserid:DWORD;dwRequestid:DWORD;bAccept:BOOL):DWORD;cdecl;
  // 回复对方的私聊请求（扩展，可以附带出错代码）
  function BRAC_PrivateChatEchoEx(dwUserid:DWORD;dwRequestid:DWORD;dwErrorCode:DWORD):DWORD;cdecl;
  // 退出与某用户的私聊，或者将某用户从自己的私聊列表中清除
  function BRAC_PrivateChatExit(dwUserid:DWORD):DWORD;cdecl;
  // SDK内核参数设置
  function  BRAC_SetSDKOption(optname:Integer;optval:Pointer;optlen:Integer):DWORD;cdecl;
  // SDK内核参数状态查询
  function BRAC_GetSDKOption(optname:Integer;optval:Pointer;optlen:Integer):DWORD;cdecl;  
  
  // 视频呼叫事件控制（请求、回复、挂断等）
  function BRAC_VideoCallControl(dwEventType:DWORD; dwUserId:DWORD; dwErrorCode:DWORD; dwFlags:DWORD; dwParam:DWORD; lpUserStr:LPCTSTR):DWORD;cdecl;

implementation

  // 获取SDK版本信息
  function BRAC_GetSDKVersion(var dwMainVer:DWORD;var dwSubVer:DWORD;lpCompileTime:LPSTR;dwBufLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetSDKVersion';

  // 激活（关闭）SDK调用日志
  function BRAC_ActiveCallLog(bActive:BOOL):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_ActiveCallLog';

  // 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
  function BRAC_SetServerAuthPass(lpPassword:LPCTSTR):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetServerAuthPass';

  // 初始化系统
  function BRAC_InitSDK(hWnd:HWND;dwFuncMode:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_InitSDK';
  // 设置视频数据回调函数
  function BRAC_SetVideoDataCallBack(pixFmt:BRAC_PixelFormat;lpFunction:BRAC_VideoData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetVideoDataCallBack';
  // 设置音频数据回调函数
  function BRAC_SetAudioDataCallBack(lpFunction:BRAC_AudioData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetAudioDataCallBack';
  // 设置文字消息回调函数
  function BRAC_SetTextMessageCallBack(lpFunction:BRAC_TextMessage_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetTextMessageCallBack';
  // 设置透明通道数据回调函数
  function BRAC_SetTransBufferCallBack(lpFunction:BRAC_TransBuffer_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetTransBufferCallBack';

  // 设置透明通道数据扩展回调函数
  function BRAC_SetTransBufferExCallBack(lpFunction:BRAC_TransBufferEx_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetTransBufferExCallBack';

  // 设置文件传输回调函数
  function BRAC_SetTransFileCallBack(lpFunction:BRAC_TransFile_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetTransFileCallBack';

  // 设置音量变化回调函数
  function BRAC_SetVolumeChangeCallBack(lpFunction:BRAC_VolumeChange_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetVolumeChangeCallBack';

  // 设置SDK Filter通信数据回调函数定义
  function BRAC_SetSDKFilterDataCallBack(lpFunction:BRAC_SDKFilterData_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetSDKFilterDataCallBack';

  // 设置录像快照任务完成通知回调函数
  function BRAC_SetRecordSnapShotCallBack(lpFunction:BRAC_RecordSnapShot_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetRecordSnapShotCallBack';

  // 设置异步消息通知回调函数
  function BRAC_SetNotifyMessageCallBack(lpFunction:BRAC_NotifyMessage_CallBack;lpUserValue:Pointer=nil):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetNotifyMessageCallBack';

  // 设置视频通话消息通知回调函数
  function BRAC_SetVideoCallEventCallBack(lpFunction:BRAC_VideoCallEvent_CallBack; lpUserValue:Pointer=nil):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_SetVideoCallEventCallBack';


  // 连接服务器
  function BRAC_Connect(lpServerAddr:LPCTSTR;dwPort:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_Connect';
  // 登录系统
  function BRAC_Login(lpUserName:LPCTSTR;lpPassword:LPCTSTR;dwPassEncType:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_Login';
  // 进入房间
  function BRAC_EnterRoom(dwRoomid:DWORD;lpRoomPass:LPCTSTR;dwPassEncType:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_EnterRoom';
  // 进入房间
  function BRAC_EnterRoomEx(lpRoomName:LPCTSTR;lpRoomPass:LPCTSTR):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_EnterRoomEx';  
  // 离开房间
  function BRAC_LeaveRoom(dwRoomid:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_LeaveRoom';
  // 注销系统
  function BRAC_Logout():DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_Logout';
  // 释放所有资源
  function BRAC_Release():DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_Release';  

  // 获取当前房间在线用户列表
  function BRAC_GetOnlineUser(lpUserIDArray:LPDWORD;var dwUserNum:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetOnlineUser';
  // 查询用户摄像头的状态
  function BRAC_GetCameraState(dwUserid:DWORD;var dwState:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetCameraState'; 
  // 查询用户发言状态
  function BRAC_GetSpeakState(dwUserid:DWORD;var dwState:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetSpeakState';
  // 查询用户级别
  function BRAC_GetUserLevel(dwUserid:DWORD;var dwLevel:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetUserLevel';
  // 查询用户名称
  function BRAC_GetUserName(dwUserid:DWORD;lpUserName:PChar;dwLen:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetUserName';
  // 查询房间名称
  function BRAC_GetRoomName(dwRoomId:DWORD;lpRoomName:PChar;dwLen:DWORD):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_GetRoomName';  

  // 显示本地视频画面调节对话框
  function BRAC_ShowLVProperty(hParent:THandle;szCaption:LPCTSTR;dwX:DWORD;dwY:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_ShowLVProperty';

  // 查询指定用户相关状态
  function BRAC_QueryUserState(dwUserId:DWORD;infoname:Integer;infoval:Pointer;infolen:Integer):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_QueryUserState';             

  // 枚举本地视频采集设备
  function BRAC_EnumVideoCapture(lpDeviceName:PPChar;var dwDeviceNum:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_EnumVideoCapture';
  // 选择指定的视频采集设备
  function BRAC_SelectVideoCapture(szCaptureName:LPCTSTR):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SelectVideoCapture';
  // 获取当前使用的视频采集设备
  function BRAC_GetCurVideoCapture(lpDeviceName:PChar;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetCurVideoCapture';
  // 枚举本地音频采集设备
  function BRAC_EnumAudioCapture(lpDeviceName:PPChar;var dwDeviceNum:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_EnumAudioCapture'; 
  // 选择指定的音频采集设备
  function BRAC_SelectAudioCapture(szCaptureName:LPCTSTR):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SelectAudioCapture'; 
  // 获取当前使用的音频采集设备
  function BRAC_GetCurAudioCapture(lpDeviceName:PChar;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetCurAudioCapture';


  // 操作用户视频
  function BRAC_UserCameraControl(dwUserid:DWORD;bOpen:BOOL):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_UserCameraControl';
  // 操作用户语音
  function BRAC_UserSpeakControl(dwUserid:DWORD;bOpen:BOOL):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_UserSpeakControl';
  // 设置视频显示位置
  function BRAC_SetVideoPos(dwUserid:DWORD;hWnd:THandle;dwLeft:DWORD;dwTop:DWORD;dwRight:DWORD;dwBottom:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetVideoPos'; 

  // 获取指定音频设备的当前音量
  function BRAC_AudioGetVolume(device:BRAC_AudioDevice;var dwVolume:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_AudioGetVolume';
  // 设置指定音频设备的音量
  function BRAC_AudioSetVolume(device:BRAC_AudioDevice;dwVolume:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_AudioSetVolume';

  // 用户音、视频录制
  function BRAC_StreamRecordCtrl(dwUserId:DWORD;bStartRecord:BOOL;dwFlags:DWORD;dwParam:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_StreamRecordCtrl';

  // 对用户的视频进行抓拍（快照）
  function BRAC_SnapShot(dwUserId:DWORD;dwFlags:DWORD;dwParam:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SnapShot';                          

  // 透明通道传送缓冲区
  function BRAC_TransBuffer(dwUserid:DWORD;lpBuf:PBYTE;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_TransBuffer';

  // 透明通道传送缓冲区扩展
  function BRAC_TransBufferEx(dwUserid:DWORD;lpBuf:PByte;dwLen:DWORD;wParam:DWORD;
    lParam:DWORD;dwFlags:DWORD;dwTaskId:PDWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_TransBufferEx';

  // 传送文件           
  function BRAC_TransFile(dwUserid:DWORD;lpLocalPathName:LPCTSTR;wParam:DWORD;
    lParam:DWORD;dwFlags:DWORD;dwTaskId:PDWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_TransFile';

  // 查询传输任务相关信息
  function BRAC_QueryTransTaskInfo(dwUserid:DWORD;dwTaskId:DWORD;infoname:Integer;
    infoval:Pointer;infolen:Integer):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_QueryTransTaskInfo';

  // 取消传输任务
  function BRAC_CancelTransTask(dwUserid:DWORD;dwTaskId:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_CancelTransTask';                                           

  // 传送文本消息
  function BRAC_SendTextMessage(dwUserid:DWORD;bSecret:BOOL;lpMsgBuf:LPCTSTR;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SendTextMessage';

  // 发送SDK Filter 通信数据
  function BRAC_SendSDKFilterData(lpBuf:PByte;dwLen:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SendSDKFilterData';

  // 更改当前的聊天模式
  function BRAC_ChangeChatMode(dwChatMode:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_ChangeChatMode';
  // 获取指定用户当前的聊天模式
  function BRAC_GetUserChatMode(dwUserid:DWORD;var dwChatMode:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetUserChatMode';
  // 请求与对方私聊，向对方发起私聊请求
  function BRAC_PrivateChatRequest(dwUserid:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_PrivateChatRequest';
  // 回复对方的私聊请求
  function BRAC_PrivateChatEcho(dwUserid:DWORD;dwRequestid:DWORD;bAccept:BOOL):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_PrivateChatEcho';
  // 回复对方的私聊请求（扩展，可以附带出错代码）
  function BRAC_PrivateChatEchoEx(dwUserid:DWORD;dwRequestid:DWORD;dwErrorCode:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_PrivateChatEchoEx';
  // 退出与某用户的私聊，或者将某用户从自己的私聊列表中清除
  function BRAC_PrivateChatExit(dwUserid:DWORD):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_PrivateChatExit';

  // SDK内核参数设置
  function  BRAC_SetSDKOption(optname:Integer;optval:Pointer;optlen:Integer):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_SetSDKOption';

  // SDK内核参数状态查询
  function BRAC_GetSDKOption(optname:Integer;optval:Pointer;optlen:Integer):DWORD;cdecl;
           external C_BRAnyChatCoreLibName name 'BRAC_GetSDKOption';                          
            
  // 视频呼叫事件控制（请求、回复、挂断等）
  function BRAC_VideoCallControl(dwEventType:DWORD; dwUserId:DWORD; dwErrorCode:DWORD; dwFlags:DWORD; dwParam:DWORD; lpUserStr:LPCTSTR):DWORD;cdecl;
			external C_BRAnyChatCoreLibName name 'BRAC_VideoCallControl';     


end.
