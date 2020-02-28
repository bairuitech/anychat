package com.bairuitech.anychat;		// 不能修改包的名称

import java.awt.Component;


public class AnyChatCoreSDK
{
	AnyChatBaseEvent		baseEvent;
	AnyChatStateChgEvent	stateChgEvent;
	AnyChatPrivateChatEvent	privateChatEvent;
	AnyChatTextMsgEvent		textMsgEvent;
	AnyChatTransDataEvent	transDataEvent;
	AnyChatVideoCallEvent	videoCallEvent;
	AnyChatUserInfoEvent	userInfoEvent;
	AnyChatDataEncDecEvent	encdecEvent;
	AnyChatRecordEvent		recordEvent;
	AnyChatObjectEvent		objectEvent;
	AnyChatCoreSDKEvent		coresdkEvent;
	AnyChatStreamCallBack	streamcbEvent;
	
	private static AnyChatCoreSDK mAnyChat = null;		// 单例模式对象
	
	// 获取单例模式对象
	public synchronized static AnyChatCoreSDK getInstance()
	{
		if(mAnyChat==null)
			mAnyChat = new AnyChatCoreSDK();
		return mAnyChat;
	}
	
	private AnyChatCoreSDK() {
		
	}
	
	// 设置AnyChat基本事件通知接口
	public void SetBaseEvent(AnyChatBaseEvent e)
	{
		RegisterNotify();
		this.baseEvent = e;
	}
	// 设置AnyChat状态变化事件通知接口
	public void SetStateChgEvent(AnyChatStateChgEvent e)
	{
		RegisterNotify();
		this.stateChgEvent = e;
	}
	// 设置AnyChat私聊消息通知接口
	public void SetPrivateChatEvent(AnyChatPrivateChatEvent e)
	{
		RegisterNotify();
		this.privateChatEvent = e;
	}
	// 设置文字聊天消息通知接口
	public void SetTextMessageEvent(AnyChatTextMsgEvent e)
	{
		RegisterNotify();
		this.textMsgEvent = e;
	}
	// 设置数据传输消息通知接口
	public void SetTransDataEvent(AnyChatTransDataEvent e)
	{
		RegisterNotify();
		this.transDataEvent = e;
	}
	// 设置视频呼叫事件通知接口
	public void SetVideoCallEvent(AnyChatVideoCallEvent e)
	{
		RegisterNotify();
		this.videoCallEvent = e;
	}
	// 设置用户信息（好友）事件通知接口
	public void SetUserInfoEvent(AnyChatUserInfoEvent e)
	{
		RegisterNotify();
		this.userInfoEvent = e;
	}
	// 设置数据加密、解密回调事件接口
	public void SetDataEncDecEvent(AnyChatDataEncDecEvent e)
	{
		RegisterNotify();
		this.encdecEvent = e;
	}
	// 设置视频录制、拍照事件通知接口
	public void SetRecordSnapShotEvent(AnyChatRecordEvent e)
	{
		RegisterNotify();
		this.recordEvent = e;
	}
	// 设置业务对象事件通知接口
	public void SetObjectEvent(AnyChatObjectEvent e)
	{
		RegisterNotify();
		this.objectEvent = e;
	}
	// 设置Core SDK事件通知接口
	public void SetCoreSDKEvent(AnyChatCoreSDKEvent e)
	{
		RegisterNotify();
		this.coresdkEvent = e;
	}
	// 设置媒体数据回调事件接口
	public void SetMediaCallBackEvent(AnyChatStreamCallBack e)
	{
		RegisterNotify();
		this.streamcbEvent = e;
	}
	// 移除所有事件
	public void removeEvent(Object e) 
	{
		if (this.baseEvent == e) 
			this.baseEvent = null;
		if (this.stateChgEvent == e) 
			this.stateChgEvent = null;
		if (this.privateChatEvent == e)
			this.privateChatEvent = null;
		if (this.textMsgEvent == e) 
			this.textMsgEvent = null;
		if (this.transDataEvent == e)
			this.transDataEvent = null;
		if (this.videoCallEvent == e)
			this.videoCallEvent = null;
		if (this.userInfoEvent == e)
			this.userInfoEvent = null;
		if (this.encdecEvent == e)
			this.encdecEvent = null;
		if (this.recordEvent == e)
			this.recordEvent = null;
		if (this.objectEvent == e)
			this.objectEvent = null;
		if (this.coresdkEvent == e)
			this.coresdkEvent = null;
		if (this.streamcbEvent == e)
			this.streamcbEvent = null;
	}
	
	// 查询SDK主版本号
	public int GetSDKMainVersion()
	{
		return GetSDKOptionInt(AnyChatDefine.BRAC_SO_CORESDK_MAINVERSION);
	}
	// 查询SDK从版本号
	public int GetSDKSubVersion()
	{
		return GetSDKOptionInt(AnyChatDefine.BRAC_SO_CORESDK_SUBVERSION);
	}
	// 查询SDK编译时间
	public String GetSDKBuildTime()
	{
		return GetSDKOptionString(AnyChatDefine.BRAC_SO_CORESDK_BUILDTIME);
	}
    
    // 注册消息通知
    public native int RegisterNotify();
    
    // 初始化SDK
    public native int InitSDK(int osver, int flags);
    // 连接服务器
    public native int Connect(String serverip, int port);
    // 登录系统
    public native int Login(String username, String password);
	// 登录系统（扩展）
    public native int LoginEx(String nickname, int userid, String struserid, String appid, int timestamp, String sigstr, String strparam);
    // 进入房间（房间ID）
    public native int EnterRoom(int roomid, String password);
    // 进入房间（房间名称）
    public native int EnterRoomEx(String roomname, String password);
    
    // 退出房间
    public native int LeaveRoom(int roomid);
    // 注销登录
    public native int Logout();
    // 释放资源
    public native int Release();
    
    // 获取在线用户列表（推荐使用GetRoomOnlineUsers）
    public native int[] GetOnlineUser();
    // 获取指定房间在线用户列表
    public native int[] GetRoomOnlineUsers(int roomid);
    // 设置视频显示位置
    public native int SetVideoPos(int userid, Component s, int lef, int top, int right, int bottom);
    // 设置视频显示位置（扩展）
    public native int SetVideoPosEx(int userid, Component s, int lef, int top, int right, int bottom, int streamindex, int flags);
    // 用户摄像头控制
    public native int UserCameraControl(int userid, int bopen);
    // 用户摄像头控制（扩展）
    public native int UserCameraControlEx(int userid, int bopen, int streamindex, int flags, String strparam);
    // 用户音频控制
    public native int UserSpeakControl(int userid, int bopen);
    // 用户音频控制（扩展）
    public native int UserSpeakControlEx(int userid, int bopen, int streamindex, int flags, String strparam);
    
    // 设置指定用户音视频流相关参数（整型值）
 	public native int SetUserStreamInfoInt(int userid, int streamindex, int infoname, int infovalue);
 	// 设置指定用户音视频流相关参数（字符串值）
 	public native int SetUserStreamInfoString(int userid, int streamindex, int infoname, String infovalue);
 	// 查询指定用户音视频流相关参数（整型值）
 	public native int GetUserStreamInfoInt(int userid, int streamindex, int infoname);
 	// 查询指定用户音视频流相关参数（字符串值）
 	public native String GetUserStreamInfoString(int userid, int streamindex, int infoname);
    
    // 用户音、视频录制
	public native int StreamRecordCtrl(int userid, int bstartrecord, int flags, int param);
	// 用户音、视频录制（扩展）
	public native int StreamRecordCtrlEx(int userid, int bstartrecord, int flags, int param, String szUserStr);
	// 用户图像抓拍
	public native int SnapShot(int userid, int flags, int param);
	
	// 获取指定音频设备的当前音量
	public native int AudioGetVolume(int device);
	// 设置指定音频设备的音量
	public native int AudioSetVolume(int device, int volume);
    
    // 获取指定用户的字符串类型状态
    public native String QueryUserStateString(int userid, int infoname);
	// 获取指定用户的整型状态
    public native int QueryUserStateInt(int userid, int infoname);
    // 获取指定用户的说话音量(0 ~ 100)
    public native int GetUserSpeakVolume(int userid);
    // 获取指定用户的摄像头状态
    public native int GetCameraState(int userid);
    // 获取指定用户的音频设备状态
	public native int GetSpeakState(int userid);
	// 获取指定用户的视频分辨率宽度
	public native int GetUserVideoWidth(int userid);
	// 获取指定用户的视频分辨率高度
	public native int GetUserVideoHeight(int userid);
	
	// 获取指定房间的字符串类型状态
    public native String QueryRoomStateString(int roomid, int infoname);
	// 获取指定房间的整型状态
    public native int QueryRoomStateInt(int roomid, int infoname);

	// 设置服务器认证密码
	public native int SetServerAuthPass(String Password);
	// 设置SDK参数（整型值）
	public native int SetSDKOptionInt(int optname, int optvalue);
	// 设置SDK参数（字符串值）
	public native int SetSDKOptionString(int optname, String optvalue);
	// 查询SDK参数（整型值）
	public native int GetSDKOptionInt(int optname);
	// 查询SDK参数（字符串值）
	public native String GetSDKOptionString(int optname);
	
	// 发送文字消息
	public native int SendTextMessage(int userid, int secret, String message);
	// 传送文件
	public native int TransFile(int userid, String filepath, int wparam, int lparam, int flags, AnyChatOutParam outParam);
	// 传送文件（扩展）
	public native int TransFileEx(String taskguid, int userid, String filepath, int flags, String userstr);
	// 透明通道传送缓冲区
	public native int TransBuffer(int userid, byte[] buf, int len);
	// 透明通道传送缓冲区扩展
	public native int TransBufferEx(int userid, byte[] buf, int len, int wparam, int lparam, int flags, AnyChatOutParam outParam);
	// 终止传输任务
	public native int CancelTransTask(int userid, int taskid);
	// 取消传输任务（扩展）
	public native int CancelTransTaskEx(String taskguid, int flags, int errorcode);
	// 查询传输任务状态
	public native int QueryTransTaskInfo(int userid, int taskid, int infoname, AnyChatOutParam outParam);
	// 查询传输任务相关信息（扩展）
	public native int QueryTransTaskInfoEx(String taskguid, int infoname, AnyChatOutParam outParam);
	// 发送SDK Filter 通信数据
	public native int SendSDKFilterData(byte[] buf, int len);
	
	// 获取音频播放数据
	public static native byte[] FetchAudioPlayBuffer(int size);
	
	// 本地视频自动对焦
	public void CameraAutoFocus()
	{
		SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_FOCUSCTRL, 1);
	}
	// 查询指定用户名称
	public String GetUserName(int userid)
	{
		return QueryUserStateString(userid, AnyChatDefine.BRAC_USERSTATE_NICKNAME);
	}
	// 查询指定用户互联网IP地址
	public String GetUserIPAddr(int userid)
	{
		return QueryUserStateString(userid, AnyChatDefine.BRAC_USERSTATE_INTERNETIP);
	}
	
	// 枚举本地视频采集设备
	public native String[] EnumVideoCapture();
	// 选择指定的视频采集设备
	public native int SelectVideoCapture(String devicename);
	// 获取当前使用的视频采集设备
	public native String GetCurVideoCapture();
	// 枚举本地音频采集设备
	public native String[] EnumAudioCapture();
	// 选择指定的音频采集设备
	public native int SelectAudioCapture(String devicename);
	// 获取当前使用的音频采集设备
	public native String GetCurAudioCapture();
	// 枚举本地音频播放设备
	public native String[] EnumAudioPlayback();
	// 选择指定的音频播放设备
	public native int SelectAudioPlayback(String devicename);
	// 获取当前使用的音频播放设备
	public native String GetCurAudioPlayback();	
	
	// 更改当前的聊天模式
	public native int ChangeChatMode(int chatmode);
	// 获取指定用户当前的聊天模式（返回值为dwChatMode）
	public native int GetUserChatMode(int userid);
	// 请求与对方私聊，向对方发起私聊请求
	public native int PrivateChatRequest(int userid);
	// 回复对方的私聊请求
	public native int PrivateChatEcho(int userid, int requestid, int baccept);
	// 回复对方的私聊请求（扩展，可以附带出错代码）
	public native int PrivateChatEchoEx(int userid, int requestid, int errorcode);
	// 退出与某用户的私聊，或者将某用户从自己的私聊列表中清除
	public native int PrivateChatExit(int userid);
	
	// 设置外部输入视频格式
	public static native int SetInputVideoFormat(int pixFmt, int dwWidth, int dwHeight, int dwFps, int dwFlags);
	// 设置外部输入视频格式（扩展）
	public static native int SetInputVideoFormatEx(int dwStreamIndex, int dwCodecId, int pixFmt, int dwWidth, int dwHeight, int dwFps, int dwFlags);
	// 外部视频数据输入
	public static native int InputVideoData(byte[] lpVideoFrame, int dwSize, int dwTimeStamp);
	// 外部视频数据输入（扩展）
	public static native int InputVideoDataEx(int dwStreamIndex, byte[] lpVideoFrame, int dwSize, int dwTimeStamp, int dwFlags);
	// 设置外部输入音频格式
	public static native int SetInputAudioFormat(int dwChannels, int dwSamplesPerSec, int dwBitsPerSample, int dwFlags);
	// 设置外部输入音频格式（扩展）
	public static native int SetInputAudioFormatEx(int dwStreamIndex, int dwCodecId, int dwChannels, int dwSamplesPerSec, int dwBitsPerSample, int dwFlags);
	// 外部音频数据输入
	public static native int InputAudioData(byte[] lpSamples, int dwSize, int dwTimeStamp);
	// 外部音频数据输入（扩展）
	public static native int InputAudioDataEx(int dwStreamIndex, byte[] lpSamples, int dwSize, int dwTimeStamp, int dwFlags);
	
	// 视频呼叫事件控制（请求、回复、挂断等）
	public native int VideoCallControl(int dwEventType, int dwUserId, int dwErrorCode, int dwFlags, int dwParam, String szUserStr);
	
	// 获取用户好友ID列表
	public native int[] GetUserFriends();
	// 获取好友在线状态
	public native int GetFriendStatus(int dwFriendUserId);
	// 获取用户分组ID列表
	public native int[] GetUserGroups();
	// 获取分组下面的好友列表
	public native int[] GetGroupFriends(int dwGroupId);
	// 获取用户信息
	public native String GetUserInfo(int dwUserId, int dwInfoId);
	// 获取用户分组名称
	public native String GetGroupName(int dwGroupId);
	// 用户信息控制
	public native int UserInfoControl(int dwUserId, int dwCtrlCode, int wParam, int lParam, String szStrValue);
	
	// IP组播功能控制
	public native int MultiCastControl(String lpMultiCastAddr, int dwPort, String lpNicAddr, int dwTTL, int dwFlags);
	// 向服务器动态查询相关信息
	public native String QueryInfoFromServer(int dwInfoName, String strInParam, int dwFlags);
	// SDK控制
	public native String SDKControl(int dwCtrlCode, String strInParam);
	
	// 获取业务对象列表
	public static native int[] ObjectGetIdList(int dwObjectType);
	// 获取业务对象参数值（整型）
	public static native int ObjectGetIntValue(int dwObjectType, int dwObjectId, int dwInfoName);
	// 获取业务对象参数值（字符串）
	public static native String ObjectGetStringValue(int dwObjectType, int dwObjectId, int dwInfoName);
	// 业务对象参数设置（整形）
	public static native int ObjectSetIntValue(int dwObjectType, int dwObjectId, int dwInfoName, int dwValue);
	// 业务对象参数设置（字符串）
	public static native int ObjectSetStringValue(int dwObjectType, int dwObjectId, int dwInfoName, String lpStrValue);
	// 业务对象参数控制
	public static native int ObjectControl(int dwObjectType, int dwObjectId, int dwCtrlCode, int dwParam1, int dwParam2, int dwParam3, int dwParam4, String lpStrValue);

	// 流媒体播放初始化
	public native int StreamPlayInit(String lpTaskGuid, String lpStreamPath, int dwFlags, String lpStrParam);
	// 流媒体播放控制
	public native int StreamPlayControl(String lpTaskGuid, int dwCtrlCode, int dwParam, int dwFlags, String lpStrParam);
	// 流媒体播放设置视频显示位置
	public native int StreamPlaySetVideoPos(String lpTaskGuid, Component s, int dwLeft, int dwTop, int dwRight, int dwBottom);
	// 流媒体播放获取参数信息
	public native String StreamPlayGetInfo(String lpTaskGuid, int dwInfoName);
	// 流媒体播放释放资源
	public native int StreamPlayDestroy(String lpTaskGuid, int dwFlags);
	
    // 异步消息通知
    public void OnNotifyMsg(int dwNotifyMsg, int wParam, int lParam)
    {
    	switch(dwNotifyMsg)
    	{
		case AnyChatDefine.WM_GV_CONNECT:			
			if(baseEvent != null)
				baseEvent.OnAnyChatConnectMessage(wParam>=1?true:false);
			break;
		case AnyChatDefine.WM_GV_LOGINSYSTEM:
			if(baseEvent != null)
				baseEvent.OnAnyChatLoginMessage(wParam,lParam);
			break;
		case AnyChatDefine.WM_GV_ENTERROOM:
			if(baseEvent != null)
				baseEvent.OnAnyChatEnterRoomMessage(wParam, lParam);
			break;
		case AnyChatDefine.WM_GV_USERATROOM:
			if(baseEvent != null)
				baseEvent.OnAnyChatUserAtRoomMessage(wParam,lParam>=1?true:false);
			break;
		case AnyChatDefine.WM_GV_LINKCLOSE:
			if(baseEvent != null)
				baseEvent.OnAnyChatLinkCloseMessage(lParam);
			break;
		case AnyChatDefine.WM_GV_ONLINEUSER:
			if(baseEvent != null)
				baseEvent.OnAnyChatOnlineUserMessage(wParam,lParam);
			break;
		case AnyChatDefine.WM_GV_MICSTATECHANGE:
			if(stateChgEvent != null)
				stateChgEvent.OnAnyChatMicStateChgMessage(wParam,lParam==0?false:true);
			break;			
		case AnyChatDefine.WM_GV_CAMERASTATE:
			if(stateChgEvent != null)
				stateChgEvent.OnAnyChatCameraStateChgMessage(wParam,lParam);
			break;
		case AnyChatDefine.WM_GV_CHATMODECHG:
			if(stateChgEvent != null)
				stateChgEvent.OnAnyChatChatModeChgMessage(wParam,lParam==0?true:false);
			break;
		case AnyChatDefine.WM_GV_ACTIVESTATE:
			if(stateChgEvent != null)
				stateChgEvent.OnAnyChatActiveStateChgMessage(wParam,lParam);
			break;
		case AnyChatDefine.WM_GV_P2PCONNECTSTATE:
			if(stateChgEvent != null)
				stateChgEvent.OnAnyChatP2PConnectStateMessage(wParam,lParam);
			break;
		case AnyChatDefine.WM_GV_VIDEOSIZECHG:
//			OnAnyChatVideoSizeChgMessage(wParam, LOWORD(lParam), HIWORD(lParam));
			break;
		case AnyChatDefine.WM_GV_PRIVATEREQUEST:
			if(privateChatEvent != null)
				privateChatEvent.OnAnyChatPrivateRequestMessage(wParam,lParam);
			break;
		case AnyChatDefine.WM_GV_PRIVATEECHO:
			if(privateChatEvent != null)
				privateChatEvent.OnAnyChatPrivateEchoMessage(wParam,lParam);
			break;
		case AnyChatDefine.WM_GV_PRIVATEEXIT:
			if(privateChatEvent != null)
				privateChatEvent.OnAnyChatPrivateExitMessage(wParam,lParam);
			break;
		default:
			break;
		}
    }
   
    // 异步消息通知（AnyChat底层其它线程回调上来，需要通过Msg传递到主线程）
	private void OnAnyChatNotifyMsg(int dwNotifyMsg, int wParam, int lParam)
    {
		AnyChatCoreSDK.this.OnNotifyMsg(dwNotifyMsg,wParam,lParam);
    }
    // 文字消息通知（AnyChat底层其它线程回调上来，需要通过Msg传递到主线程）
	private void OnTextMessageCallBack(int dwFromUserid, int dwToUserid, int bSecret, String message)
    {
		if(AnyChatCoreSDK.this.textMsgEvent != null)
			AnyChatCoreSDK.this.textMsgEvent.OnAnyChatTextMessage(dwFromUserid, dwToUserid, bSecret!=0?true:false, message);
    }
    // 文件传输回调函数定义
	private void OnTransFileCallBack(int userid, String filename, String tempfilepath, int filelength, int wparam, int lparam, int taskid)
    {
		if(AnyChatCoreSDK.this.transDataEvent != null)
		AnyChatCoreSDK.this.transDataEvent.OnAnyChatTransFile(userid, filename, tempfilepath, filelength, wparam, lparam, taskid);
    }
    // 缓冲区回调函数定义
	private void OnTransBufferCallBack(int userid, byte[] buf, int len)
    {
		if (AnyChatCoreSDK.this.transDataEvent != null)
			AnyChatCoreSDK.this.transDataEvent.OnAnyChatTransBuffer(userid, buf, len);
    }
    // 缓冲区扩展回调函数定义
	private void OnTransBufferExCallBack(int userid, byte[] buf, int len, int wparam, int lparam, int taskid)
    {
		if (AnyChatCoreSDK.this.transDataEvent != null)
			AnyChatCoreSDK.this.transDataEvent.OnAnyChatTransBufferEx(userid, buf, len, wparam, lparam, taskid);
    }
    // 服务器发送的SDK Filter Data数据回调函数定义
	private void OnSDKFilterDataCallBack(byte[] buf, int len)
    {
		if(AnyChatCoreSDK.this.transDataEvent != null)
			AnyChatCoreSDK.this.transDataEvent.OnAnyChatSDKFilterData(buf, len);
    }
	
	// 视频数据回调函数
	private void OnVideoDataCallBack(int userid, byte[] buf, int len, int width, int height)
	{
		if(AnyChatCoreSDK.this.streamcbEvent != null)
			AnyChatCoreSDK.this.streamcbEvent.OnAnyChatVideoDataCallBack(userid, 0, buf, len, width, height);
	}
	
	// 视频数据回调函数（扩展）
	private void OnVideoDataCallBackEx(int userid, int streamindex, byte[] buf, int len, int width, int height)
	{
		if(AnyChatCoreSDK.this.streamcbEvent != null)
			AnyChatCoreSDK.this.streamcbEvent.OnAnyChatVideoDataCallBack(userid, streamindex, buf, len, width, height);
	}
	
	// 音频数据回调函数（扩展）
	private void OnAudioDataCallBack(int userid, int streamindex, byte[] buf, int len, int timestamp, int channels, int samplespersecond, int bitspersample)
	{
		if(AnyChatCoreSDK.this.streamcbEvent != null)
			AnyChatCoreSDK.this.streamcbEvent.OnAnyChatAudioDataCallBack(userid, streamindex, buf, len, timestamp, channels, samplespersecond, bitspersample);
	}
	
	// 视频呼叫事件回调函数
	private void OnVideoCallEventCallBack(int eventtype, int userid, int errorcode, int flags, int param, String userStr)
	{
		if(AnyChatCoreSDK.this.videoCallEvent != null)
			AnyChatCoreSDK.this.videoCallEvent.OnAnyChatVideoCallEvent(eventtype, userid, errorcode, flags, param, userStr);
	}
	
	// 录像、快照任务完成回调函数
	private void OnRecordSnapShotExCallBack(int dwUserId, int dwErrorCode, String lpFileName, int dwElapse, int dwFlags, int dwParam, String lpUserStr)
	{
		if(AnyChatCoreSDK.this.recordEvent != null) {
        	 if((dwFlags & AnyChatDefine.ANYCHAT_RECORD_FLAGS_SNAPSHOT) == 0)
        		 AnyChatCoreSDK.this.recordEvent.OnAnyChatRecordEvent(dwUserId, dwErrorCode, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr);
        	 else
        		 AnyChatCoreSDK.this.recordEvent.OnAnyChatSnapShotEvent(dwUserId, dwErrorCode, lpFileName, dwFlags, dwParam, lpUserStr);
   	 	}
	}
	
	// 数据加密、解密回调函数
	private int OnDataEncDecCallBack(int userid, int flags, byte[] buf, int len, AnyChatOutParam outParam)
	{
		if(AnyChatCoreSDK.this.encdecEvent != null)
			return AnyChatCoreSDK.this.encdecEvent.OnAnyChatDataEncDec(userid, flags, buf, len, outParam);
		else
			return -1;
	}
	
	// 业务对象事件回调函数定义
	private void OnObjectEventNotifyCallBack(int dwObjectType, int dwObjectId, int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, String lpStrParam)
	{
		 if(AnyChatCoreSDK.this.objectEvent != null)
			 AnyChatCoreSDK.this.objectEvent.OnAnyChatObjectEvent(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, lpStrParam);
	}
	
	// Core SDK事件回调函数
	private void OnAnyChatCoreSDKEventCallBack(int dwEventType, String lpJsonStr)
	{
		if(AnyChatCoreSDK.this.coresdkEvent != null)
			AnyChatCoreSDK.this.coresdkEvent.OnAnyChatCoreSDKEvent(dwEventType, lpJsonStr);
	}
    
    static {
    	System.loadLibrary("anychatcore4java");
    }
    
}

