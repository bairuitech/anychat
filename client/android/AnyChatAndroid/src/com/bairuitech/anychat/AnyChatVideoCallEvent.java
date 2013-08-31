package com.bairuitech.anychat;

// AnyChat视频呼叫事件通知接口
public interface AnyChatVideoCallEvent {
	// 用户私聊请求消息，dwUserId表示发起者的用户ID号，dwRequestId表示私聊请求编号，标识该请求
    public void OnAnyChatVideoCallEvent(int dwEventType, int dwUserId, int dwErrorCode, int wParam, int lParam, String userStr);
}