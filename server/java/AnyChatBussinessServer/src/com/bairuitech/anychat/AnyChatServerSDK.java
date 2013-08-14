package com.bairuitech.anychat;		// 不能修改包的名称

import com.bairuitech.anychat.AnyChatTransTaskOutParam;

public class AnyChatServerSDK
{
	public static final int BRAS_SERVERAPPMSG_CONNECTED		= 	1;	///< 与AnyChat核心服务器连接成功
	public static final int BRAS_SERVERAPPMSG_DISCONNECT	=	2;	///< 与AnyChat核心服务器断开连接

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
    
    // 初始化SDK
    public native int InitSDK(int flags);
    // 释放资源
    public native int Release();
    
    // 设置SDK定时器回调函数（dwElapse：定时器间隔，单位：ms）
    public native int SetTimerEventCallBack(int elapse);
    
	// 传送文件
	public static native int TransFile(int userid, String filepath, int wparam, int lparam, int flags, AnyChatTransTaskOutParam outParam);
	// 透明通道传送缓冲区
	public static native int TransBuffer(int userid, byte[] buf, int len);
	// 透明通道传送缓冲区扩展
	public static native int TransBufferEx(int userid, byte[] buf, int len, int wparam, int lparam, int flags, AnyChatTransTaskOutParam outParam);
	// 发送SDK Filter 通信数据
	public static native int SendSDKFilterData(byte[] buf, int len);
	
	// 向指定用户发送数据
	public static native int SendBufToUser(int userid, byte[] buf, int len);
	// 向指定房间发送数据
	public static native int SendBufToRoom(int roomid, byte[] buf, int len);
	
	// 中心端录像控制
	public static native int StreamRecordCtrl(int dwUserId, int bStartRecord, int dwFlags, int dwParam, int dwRecordServerId);
	
	
	// 服务器应用程序消息回调函数定义
	private void OnAnyChatServerAppMessageCallBack(int dwMsg)
	{
		if(this.event != null)
			this.event.OnAnyChatServerAppMessageCallBack(dwMsg);
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
	private void OnAnyChatUserLogoutActionCallBack(int dwUserId)
	{
		if(this.event != null)
			this.event.OnAnyChatUserLogoutActionCallBack(dwUserId);
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
	private void OnAnyChatServerRecordCallBack(int dwUserId, int dwParam, int dwRecordServerId, int dwElapse, String szRecordFileName)
	{
		if(this.event != null)
			this.event.OnAnyChatServerRecordCallBack(dwUserId, dwParam, dwRecordServerId, dwElapse, szRecordFileName);
	}
	
    static {
    	System.loadLibrary("anychatserver4java");
    }
    
}


