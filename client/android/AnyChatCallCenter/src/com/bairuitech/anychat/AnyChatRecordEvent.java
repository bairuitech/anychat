package com.bairuitech.anychat;

// AnyChat视频录制事件通知接口
public interface AnyChatRecordEvent {
    // 视频录制完成事件
	public void OnAnyChatRecordEvent(int dwUserId, String filename, int dwParam);
	// 拍照完成事件
	public void OnAnyChatSnapShotEvent(int dwUserId, String filename, int dwParam);
}