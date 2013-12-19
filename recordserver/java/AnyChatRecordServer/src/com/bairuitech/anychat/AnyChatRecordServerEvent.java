package com.bairuitech.anychat;

import com.bairuitech.anychat.AnyChatRecordResult;

// 数据传输通知接口
public interface AnyChatRecordServerEvent {
	
	// 服务器应用程序消息回调函数定义
	public void OnAnyChatRecordServerAppMessageCallBack(int dwMsg, int wParam, int lParam);
	
	// 录像开始事件回调函数定义
	public int OnAnyChatRecordStartCallBack(int dwUserId);
	// 录像数据回调函数定义
	public int OnAnyChatRecordBufferCallBack(int dwUserId, byte[] lpBuf, int dwLen, int timestamp, int flags);
	// 录像结束事件回调函数定义
	public int OnAnyChatRecordFinishCallBack(int dwUserId, AnyChatRecordResult result);

}
