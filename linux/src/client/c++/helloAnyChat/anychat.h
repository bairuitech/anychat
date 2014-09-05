#ifndef ANYCHAT_H
#define ANYCHAT_H

#include "BRAnyChatSDKProc.h"


class CAnyChat : public CBRAnyChatSDKProc
{
    public:
        CAnyChat();
        virtual ~CAnyChat();

    protected:
        DWORD   m_dwRemoteUserId;

    private:
    //
    void OpenRemoteUserStream(void);

	// 连接服务器消息
	virtual void OnAnyChatConnectMessage(BOOL bSuccess);
	// 用户登陆消息
	virtual void OnAnyChatLoginMessage(DWORD dwUserId, DWORD dwErrorCode);
	// 用户进入房间消息
	virtual void OnAnyChatEnterRoomMessage(DWORD dwRoomId, DWORD dwErrorCode);
	// 房间在线用户消息
	virtual void OnAnyChatOnlineUserMessage(DWORD dwUserNum, DWORD dwRoomId);
	// 用户打开/关闭音频设备设备消息
	virtual void OnAnyChatMicStateChgMessage(DWORD dwUserId, BOOL bOpenMic);
	// 用户进入/退出房间消息
	virtual void OnAnyChatUserAtRoomMessage(DWORD dwUserId, BOOL bEnter);
	//网络断开消息
	virtual void OnAnyChatLinkCloseMessage(DWORD dwErrorCode);

	// 用户摄像头状态改变消息
	virtual void OnAnyChatCameraStateChgMessage(DWORD dwUserId, DWORD dwState);
	// 用户聊天模式改变消息
	virtual void OnAnyChatChatModeChgMessage(DWORD dwUserId, BOOL bPublicChat);
	// 用户活动状态发生变化消息
	virtual void OnAnyChatActiveStateChgMessage(DWORD dwUserId, DWORD dwState);
	// P2P连接状态变化消息
	virtual void OnAnyChatP2PConnectStateMessage(DWORD dwUserId, DWORD dwState);

	// 用户私聊请求消息
	virtual void OnAnyChatPrivateRequestMessage(DWORD dwUserId, DWORD dwRequestId);
	// 用户私聊请求回复消息
	virtual void OnAnyChatPrivateEchoMessage(DWORD dwUserId, DWORD dwErrorCode);
	// 用户退出私聊消息
	virtual void OnAnyChatPrivateExitMessage(DWORD dwUserId, DWORD dwErrorCode);

	// SDK警告消息
	virtual void OnAnyChatSDKWarningMessage(DWORD dwErrorCode, DWORD dwReserved);

	// 视频数据回调
	virtual void OnAnyChatVideoDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPBITMAPINFOHEADER lpbmiHeader);
	// 音频数据回调
	virtual void OnAnyChatAudioDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPWAVEFORMATEX lpWaveFormatEx);
	// 发送文字的回调函数
	virtual void OnAnyChatTextMsgCallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
	// 透明通道回调函数
	virtual void OnAnyChatTransBufferCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
	// 透明通道数据扩展回调函数
	virtual void OnAnyChatTransBufferExCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId);
	// 文件传输回调函数
	virtual void OnAnyChatTransFileCallBack(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId);
	// 音量变化回调函数
	virtual void OnAnyChatVolumeChangeCallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume);
	// SDK Filter 通信数据回调函数
	virtual void OnAnyChatSDKFilterDataCallBack(LPBYTE lpBuf, DWORD dwLen);
	// 录像、快照任务完成回调函数
	virtual void OnAnyChatRecordSnapShotCallBack(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType);
	// 异步消息通知回调函数
	virtual void OnAnyChatNotifyMessageCallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam);
};

#endif // ANYCHAT_H
