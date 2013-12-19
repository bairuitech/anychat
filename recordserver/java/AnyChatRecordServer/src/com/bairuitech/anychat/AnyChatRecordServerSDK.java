package com.bairuitech.anychat;		// 不能修改包的名称

import com.bairuitech.anychat.AnyChatRecordResult;;

public class AnyChatRecordServerSDK
{
	public static final int BRRS_SERVERAPPMSG_CONNECTED		= 	1;	///< 与AnyChat核心服务器连接成功
	public static final int BRRS_SERVERAPPMSG_DISCONNECT	=	2;	///< 与AnyChat核心服务器断开连接
	
	// 查询信息类型定义（API：BRRS_QueryUserInfo 传入参数）
	public static final int BRRS_USERINFO_TYPE_NICKNAME		=	1;	///< 用户名
	public static final int BRRS_USERINFO_TYPE_VCODEC		=	10;	///< 视频编码器
	public static final int BRRS_USERINFO_TYPE_WIDTH		=	11;	///< 视频宽度
	public static final int BRRS_USERINFO_TYPE_HEIGHT		=	12;	///< 视频高度
	public static final int BRRS_USERINFO_TYPE_FRAMERATE	=	13;	///< 视频帧率
	public static final int BRRS_USERINFO_TYPE_ACODEC		=	20;	///< 音频编码器
	public static final int BRRS_USERINFO_TYPE_SAMPLERATE	=	21;	///< 音频采样率
	public static final int BRRS_USERINFO_TYPE_CHANNELS		=	22;	///< 音频采样通道数
	public static final int BRRS_USERINFO_TYPE_SAMPLEBITS	=	23;	///< 音频采样位数
	
	// 数据类型标志（回调函数：OnAnyChatRecordBufferCallBack 参数）
	public static final int BRRS_RECORD_FLAGS_AUDIO			=	1;	///< 音频数据
	public static final int BRRS_RECORD_FLAGS_VIDEO			=	2;	///< 音频数据
	public static final int BRRS_RECORD_FLAGS_BUFFER		=	4;	///< 缓冲区数据
	public static final int BRRS_RECORD_FLAGS_KEYFRAME		=	16;	///< 视频关键帧
	public static final int BRRS_RECORD_FLAGS_SILENCE		=	32;	///< 音频静音帧

	AnyChatRecordServerEvent event;
	
	// 设置事件回调通知接口
	public void SetServerEvent(AnyChatRecordServerEvent e)
	{
		RegisterNotify();
		this.event = e;
	}
	
	// 查询SDK版本信息、编译时间等
	public native String GetSDKVersion();
    // 注册消息通知
    public native int RegisterNotify();
    // 注册用户身份验证回调类（部署到Web容器中需要调用）
    public native int RegisterRecordResultClass(AnyChatRecordResult resultObject);
    
    // 初始化SDK
    public native int InitSDK(int flags);
    // 释放资源
    public native int Release();
    
	// 查询指定用户的信息（整型）
	public static native int QueryUserIntInfo(int dwUserId, int dwInfoId);
	// 查询指定用户的信息（字符串类型）
	public static native String QueryUserStrInfo(int dwUserId, int dwInfoId);

	// SDK内核参数设置（整型）
	public static native int SetSDKOptionInt(int optname, int dwValue);
	// SDK内核参数设置（字符串）
	public static native int SetSDKOptionString(int optname, String lpStrValue);

	
	// 服务器应用程序消息回调函数定义
	private void OnAnyChatRecordServerAppMessageCallBack(int dwMsg, int wParam, int lParam)
	{
		if(this.event != null)
			this.event.OnAnyChatRecordServerAppMessageCallBack(dwMsg, wParam, lParam);
	}
	
	// 录像开始事件回调函数定义
	private int OnAnyChatRecordStartCallBack(int dwUserId)
	{
		if(this.event != null)
			return this.event.OnAnyChatRecordStartCallBack(dwUserId);
		else
			return -1;
	}
	// 录像数据回调函数定义
	private int OnAnyChatRecordBufferCallBack(int dwUserId, byte[] lpBuf, int dwLen, int timestamp, int flags)
	{
		if(this.event != null)
			return this.event.OnAnyChatRecordBufferCallBack(dwUserId, lpBuf, dwLen, timestamp, flags);
		else
			return -1;
	}
	// 录像结束事件回调函数定义
	private int OnAnyChatRecordFinishCallBack(int dwUserId, AnyChatRecordResult result)
	{
		if(this.event != null)
			return this.event.OnAnyChatRecordFinishCallBack(dwUserId, result);
		else
			return -1;
	}
	
    static {
    	System.loadLibrary("anychatrecordserversdk");
    }
    
}


