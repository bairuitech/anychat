package com.bairuitech.anychat;		// 不能修改包的名称

public class AnyChatServerSDK
{
	public static final int BRAS_MESSAGE_CORESERVERCONN		=	10;	///< 与核心服务器的连接消息，wParam为errorcode
	public static final int BRAS_MESSAGE_RECORDSERVERCONN	=	11;	///< 与录像服务器的连接消息，wParam为errorcode，lParam为recordserverid
	public static final int BRAS_MESSAGE_LOGINSERVERCONN	=	12;	///< 与登录服务器的连接消息，wParam为errorcode，lParam为loginserverid
	public static final int BRAS_MESSAGE_ROOMSERVERCONN		=	13;	///< 与房间服务器的连接消息，wParam为errorcode，lParam为roomserverid
	public static final int BRAS_MESSAGE_MEDIASERVERCONN	=	14;	///< 与流媒体服务器的连接消息，wParam为errorcode，lParam为mediaserverid
	
	// 视频呼叫事件类型定义（API：BRAS_VideoCallControl 传入参数、OnVideoCallEvent回调参数）
	public static final int BRAS_VIDEOCALL_EVENT_REQUEST    =	1;  ///< 呼叫请求
	public static final int BRAS_VIDEOCALL_EVENT_REPLY      =	2;  ///< 呼叫请求回复
	public static final int BRAS_VIDEOCALL_EVENT_START      =	3;  ///< 视频呼叫会话开始事件
	public static final int BRAS_VIDEOCALL_EVENT_FINISH     =	4;  ///< 挂断（结束）呼叫会话
	
	// 用户信息控制类型定义（API：BRAS_UserInfoControl 传入参数、OnUserInfoControl回调参数）
	public static final int BRAS_USERINFO_CTRLCODE_KICKOUT	=	1;	///< 将指定用户从系统中踢掉
	public static final int BRAS_USERINFO_CTRLCODE_SYNCDATA	=	2;	///< 将指定用户的数据同步给客户端
	public static final int BRAS_USERINFO_CTRLCODE_FUNCCTRL =	3;	///< 客户端功能控制，wParam为功能参数组合
	public static final int BRAS_USERINFO_CTRLCODE_ADDGROUP	=	20;	///< 添加用户分组，wParam为分组Id，lpStrValue为分组名称
	public static final int BRAS_USERINFO_CTRLCODE_DELGROUP	=	21;	///< 删除用户分组，wParam为分组Id
	public static final int BRAS_USERINFO_CTRLCODE_ADDFRIEND=	22;	///< 添加用户好友，wParam为好友Id
	public static final int BRAS_USERINFO_CTRLCODE_DELFRIEND=	23;	///< 删除用户好友，wParam为好友Id
	public static final int BRAS_USERINFO_CTRLCODE_SETGROUPRELATION=24;	///< 设置好友与分组的关联关系，wParam为分组Id，lParam为好友Id，表示好友属于某个分组
	
	// 内核参数控制（API：SetSDKOption 传入参数）
	public static final int BRAS_SO_GETTRANSBUFTIMESTAMP	=	1;	///< 获取透明通道时间戳（传入参数为userid）
	public static final int BRAS_SO_RECORD_VIDEOBR			=	2;	///< 录像视频码率设置（参数为：int型，单位：bps）
	public static final int BRAS_SO_RECORD_AUDIOBR			=	3;	///< 录像音频码率设置（参数为：int型，单位：bps）
	public static final int BRAS_SO_RECORD_FILETYPE			=	4;	///< 录制文件类型设置（参数为：int型， 0 MP4[默认], 1 WMV, 2 FLV, 3 MP3）
	public static final int BRAS_SO_RECORD_WIDTH			=	5;	///< 录制视频宽度设置（参数为：int型，如：320）
	public static final int BRAS_SO_RECORD_HEIGHT			=	6;	///< 录制文件高度设置（参数为：int型，如：240）
	public static final int BRAS_SO_RECORD_FILENAMERULE		=	7;	///< 录制文件名命名规则（参数为：int型）
	
	// 初始化标志（API：BRAS_InitSDK 传入参数）
	public static final int BRAS_INITFLAGS_MULTITHREADS		=	1;	///< 多线程模式
	
	// 录像功能标志定义（API：BRAS_StreamRecordCtrl 传入参数）
	public static final int ANYCHAT_RECORD_FLAGS_VIDEO		= 0x00000001;	///< 录制视频
	public static final int ANYCHAT_RECORD_FLAGS_AUDIO		= 0x00000002;	///< 录制音频
	public static final int ANYCHAT_RECORD_FLAGS_SERVER		= 0x00000004;	///< 服务器端录制
	public static final int ANYCHAT_RECORD_FLAGS_MIXAUDIO	= 0x00000010;	///< 录制音频时，将其它人的声音混音后录制
	public static final int ANYCHAT_RECORD_FLAGS_MIXVIDEO	= 0x00000020;	///< 录制视频时，将其它人的视频迭加后录制
	public static final int ANYCHAT_RECORD_FLAGS_ABREAST	= 0x00000100;	///< 录制视频时，将其它人的视频并列录制
	public static final int ANYCHAT_RECORD_FLAGS_STEREO		= 0x00000200;	///< 录制音频时，将其它人的声音混合为立体声后录制
	public static final int ANYCHAT_RECORD_FLAGS_SNAPSHOT	= 0x00000400;	///< 拍照
	public static final int ANYCHAT_RECORD_FLAGS_LOCALCB	= 0x00000800;	///< 触发本地回调
	public static final int ANYCHAT_RECORD_FLAGS_STREAM		= 0x00001000    ///< 对视频流进行录制（效率高，但可能存在视频方向旋转的问题）

	
	
	
	AnyChatServerEvent event;
	
	// 设置事件回调通知接口
	public void SetServerEvent(AnyChatServerEvent e)
	{
		RegisterNotify();
		this.event = e;
	}
	
	// 查询SDK版本信息、编译时间等
	public native String GetSDKVersion();
    
    // 注册消息通知
    public native int RegisterNotify();
    
    // 注册用户身份验证回调类（部署到Web容器中需要调用）
    public native int RegisterVerifyUserClass(AnyChatVerifyUserOutParam ParamObject);
    
    // 初始化SDK
    public native int InitSDK(int flags);
    // 释放资源
    public native int Release();
    
    // 设置SDK定时器回调函数（dwElapse：定时器间隔，单位：ms）
    public native int SetTimerEventCallBack(int elapse);
    
	// 传送文件
	public static native int TransFile(int userid, String filepath, int wparam, int lparam, int flags, AnyChatOutParam outParam);
	// 透明通道传送缓冲区
	public static native int TransBuffer(int userid, byte[] buf, int len);
	// 透明通道传送缓冲区扩展
	public static native int TransBufferEx(int userid, byte[] buf, int len, int wparam, int lparam, int flags, AnyChatOutParam outParam);
	// 发送SDK Filter 通信数据
	public static native int SendSDKFilterData(byte[] buf, int len);
	
	// 向指定用户发送数据
	public static native int SendBufToUser(int userid, byte[] buf, int len);
	// 向指定房间发送数据
	public static native int SendBufToRoom(int roomid, byte[] buf, int len);
	
	// 中心端录像控制
	public static native int StreamRecordCtrl(int dwUserId, int bStartRecord, int dwFlags, int dwParam, int dwRecordServerId);
	// 中心端录像控制（扩展）
	public static native int StreamRecordCtrlEx(int dwUserId, int bStartRecord, int dwFlags, int dwParam, String lpUserStr, int dwRecordServerId);
	// 发送透明通道数据给录像服务器
	public static native int TransBuffer2RecordServer(int dwUserId, byte[] buf, int len, int dwParam, int dwRecordServerId);
	
	// 视频呼叫事件控制（请求、回复、挂断等）
	public static native int VideoCallControl(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, String lpUserStr);
	
	// 设置用户的详细信息
	public static native int SetUserInfo(int dwUserId, int dwInfoId, String lpInfoValue, int dwFlags);
	// 获取用户的详细信息
	public static native String GetUserInfo(int dwUserId, int dwInfoId);
	// 用户信息控制
	public static native int UserInfoControl(int dwUserId, int dwCtrlCode, int wParam, int lParam, String lpStrValue);

	// SDK内核参数设置（整型）
	public static native int SetSDKOptionInt(int optname, int dwValue);
	// SDK内核参数设置（字符串）
	public static native int SetSDKOptionString(int optname, String lpStrValue);

	
	// 服务器应用程序消息回调函数定义
	private void OnAnyChatServerAppMessageExCallBack(int dwNotifyMessage, int wParam, int lParam)
	{
		if(this.event != null)
			this.event.OnAnyChatServerAppMessageExCallBack(dwNotifyMessage, wParam, lParam);
	}
	// SDK定时器回调函数定义
	private void OnAnyChatTimerEventCallBack()
	{
		if(this.event != null)
			this.event.OnAnyChatTimerEventCallBack();
	}
	
	// 用户身份验证回调函数定义
	private int OnAnyChatVerifyUserCallBack(String szUserName, String szPassword, AnyChatVerifyUserOutParam outParam)
	{
		int ret = -1;
		if(this.event != null)
			ret = this.event.OnAnyChatVerifyUserCallBack(szUserName, szPassword, outParam);
		return ret;
	}
	
	// 用户登录成功回调函数定义
	private void OnAnyChatUserLoginActionCallBack(int dwUserId, String szUserName, int dwLevel, String szIpAddr)
	{
		if(this.event != null)
			this.event.OnAnyChatUserLoginActionCallBack(dwUserId, szUserName, dwLevel, szIpAddr);
	}
	// 用户注销回调函数定义
	private void OnAnyChatUserLogoutActionExCallBack(int dwUserId, int dwErrorCode)
	{
		if(this.event != null)
			this.event.OnAnyChatUserLogoutActionExCallBack(dwUserId, dwErrorCode);
	}
	
	// 用户申请进入房间回调函数定义
	private int OnAnyChatPrepareEnterRoomCallBack(int dwUserId, int dwRoomId, String szRoomName, String szPassword)
	{
		int errorcode = -1;
		if(this.event != null)
			errorcode = this.event.OnAnyChatPrepareEnterRoomCallBack(dwUserId, dwRoomId, szRoomName, szPassword);
		return errorcode;
	}
	
	// 用户进入房间回调函数定义
	private void OnAnyChatUserEnterRoomActionCallBack(int dwUserId, int dwRoomId)
	{
		if(this.event != null)
			this.event.OnAnyChatUserEnterRoomActionCallBack(dwUserId, dwRoomId);
	}
	
	// 用户离开房间回调函数定义
	private void OnAnyChatUserLeaveRoomActionCallBack(int dwUserId, int dwRoomId)
	{
		if(this.event != null)
			this.event.OnAnyChatUserLeaveRoomActionCallBack(dwUserId, dwRoomId);
	}
  
    // 文件传输回调函数定义
	private void OnAnyChatTransFileCallBack(int dwUserId, String szFileName, String szTempFilePath, int dwFileLength, int wParam, int lParam, int dwTaskId)
    {
		if(this.event != null)
			this.event.OnAnyChatTransFile(dwUserId, szFileName, szTempFilePath, dwFileLength, wParam, lParam, dwTaskId);
    }
    // 缓冲区回调函数定义
	private void OnAnyChatTransBufferCallBack(int dwUserId, byte[] lpBuf, int dwLen)
    {
		if(this.event != null)
			this.event.OnAnyChatTransBuffer(dwUserId, lpBuf, dwLen);
    }
    // 缓冲区扩展回调函数定义
	private void OnAnyChatTransBufferExCallBack(int dwUserId, byte[] lpBuf, int dwLen, int wParam, int lParam, int dwTaskId)
    {
		if(this.event != null)
			this.event.OnAnyChatTransBufferEx(dwUserId, lpBuf, dwLen, wParam, lParam, dwTaskId);
    }
    // 服务器发送的SDK Filter Data数据回调函数定义
	private void OnAnyChatSDKFilterDataCallBack(int dwUserId, byte[] buf, int len)
    {
		if(this.event != null)
			this.event.OnAnyChatSDKFilterData(dwUserId, buf, len);
    }
	
	// 收到用户文字聊天通信数据回调函数定义
	private void OnAnyChatRecvUserTextMsgCallBack(int dwRoomId, int dwSrcUserId, int dwTarUserId, int bSecret, String szTextMessage, int dwLen)
	{
		if(this.event != null)
			this.event.OnAnyChatRecvUserTextMsgCallBack(dwRoomId, dwSrcUserId, dwTarUserId, bSecret, szTextMessage, dwLen);
	}
	
	// 服务器录像回调函数定义
	private void OnAnyChatServerRecordExCallBack(int dwUserId, String lpFileName, int dwElapse, int dwFlags, int dwParam, String lpUserStr, int dwRecordServerId)
	{
		if(this.event != null)
			this.event.OnAnyChatServerRecordExCallBack(dwUserId, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr, dwRecordServerId);
	}
	
	// 视频通话消息通知回调函数定义
	private int OnAnyChatVideoCallEventCallBack(int dwEventType, int dwSrcUserId, int dwTarUserId, int dwErrorCode, int dwFlags, int dwParam, String lpUserStr)
	{
		if(this.event != null)
			return this.event.OnAnyChatVideoCallEventCallBack(dwEventType, dwSrcUserId, dwTarUserId, dwErrorCode, dwFlags, dwParam, lpUserStr);
		else
			return -1;
	}
	
	// 用户信息控制回调函数定义
	private int OnAnyChatUserInfoCtrlCallBack(int dwSendUserId, int dwUserId, int dwCtrlCode, int wParam, int lParam, String lpStrValue)
	{
		if(this.event != null)
			return this.event.OnAnyChatUserInfoCtrlCallBack(dwSendUserId, dwUserId, dwCtrlCode, wParam, lParam, lpStrValue);
		else
			return -1;
	}
	
    static {
    	System.loadLibrary("anychatserver4java");
    }
    
}


