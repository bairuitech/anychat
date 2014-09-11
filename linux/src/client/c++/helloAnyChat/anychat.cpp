#include "anychat.h"
#include <stdlib.h>
#include <stdio.h>

CAnyChat::CAnyChat()
{
    m_dwRemoteUserId = -1;
}

CAnyChat::~CAnyChat()
{

}

//
void CAnyChat::OpenRemoteUserStream(void)
{
    if(m_dwRemoteUserId != (DWORD)-1)      // already opned remote user stream
        return;
    DWORD dwUserNum = 0;
    BRAC_GetOnlineUser(NULL, dwUserNum);
    if(dwUserNum == 0)
        return;
    LPDWORD lpUserList = (LPDWORD)malloc(sizeof(DWORD) * dwUserNum);
    if(!lpUserList)
        return;
    BRAC_GetOnlineUser(lpUserList, dwUserNum);
    for(int i=0; i<(int)dwUserNum; i++)
    {
        m_dwRemoteUserId = lpUserList[i];
        BRAC_UserCameraControl(m_dwRemoteUserId, TRUE);
        BRAC_UserSpeakControl(m_dwRemoteUserId, TRUE);
        break;
    }
}

// 连接服务器消息
void CAnyChat::OnAnyChatConnectMessage(BOOL bSuccess)
{
    fprintf(stdout,"On Connect: bSuccess(%d)\r\n",(int)bSuccess);
}
// 用户登陆消息
void CAnyChat::OnAnyChatLoginMessage(DWORD dwUserId, DWORD dwErrorCode)
{
    fprintf(stdout,"On Login: dwUserId(%d), ErrorCode:%d\r\n",(int)dwUserId,dwErrorCode);
}
// 用户进入房间消息
void CAnyChat::OnAnyChatEnterRoomMessage(DWORD dwRoomId, DWORD dwErrorCode)
{
    fprintf(stdout,"On EnterRoom(dwRoomId=%d, dwErrorCode=%d)\r\n",dwRoomId,dwErrorCode);
    if(dwErrorCode == 0)
    {
        BRAC_UserCameraControl(-1,TRUE);
        BRAC_UserSpeakControl(-1, TRUE);
    }
}
// 房间在线用户消息
void CAnyChat::OnAnyChatOnlineUserMessage(DWORD dwUserNum, DWORD dwRoomId)
{
    fprintf(stdout,"Onlineuser(dwUserNum=%d, dwRoomId=%d)\r\n",dwUserNum,dwRoomId);
    OpenRemoteUserStream();
}
// 用户打开/关闭音频设备设备消息
void CAnyChat::OnAnyChatMicStateChgMessage(DWORD dwUserId, BOOL bOpenMic)
{

}
// 用户进入/退出房间消息
void CAnyChat::OnAnyChatUserAtRoomMessage(DWORD dwUserId, BOOL bEnter)
{
    fprintf(stdout,"On UserAtRoom(dwUserId=%d, bEnter=%d)\r\n",(int)dwUserId,(int)bEnter);

    if(dwUserId == m_dwRemoteUserId && !bEnter)
        m_dwRemoteUserId = -1;
    OpenRemoteUserStream();
}
//网络断开消息
void CAnyChat::OnAnyChatLinkCloseMessage(DWORD dwErrorCode)
{
    fprintf(stdout,"On Link Close(reason=%d)\r\n",dwErrorCode);
    m_dwRemoteUserId = -1;
}

// 用户摄像头状态改变消息
void CAnyChat::OnAnyChatCameraStateChgMessage(DWORD dwUserId, DWORD dwState)
{

}
// 用户聊天模式改变消息
void CAnyChat::OnAnyChatChatModeChgMessage(DWORD dwUserId, BOOL bPublicChat)
{

}
// 用户活动状态发生变化消息
void CAnyChat::OnAnyChatActiveStateChgMessage(DWORD dwUserId, DWORD dwState)
{

}
// P2P连接状态变化消息
void CAnyChat::OnAnyChatP2PConnectStateMessage(DWORD dwUserId, DWORD dwState)
{
    fprintf(stdout,"On P2P Connect State Change(dwUserId=%d, dwState=%d)\r\n",(int)dwUserId,dwState);
}

// 用户私聊请求消息
void CAnyChat::OnAnyChatPrivateRequestMessage(DWORD dwUserId, DWORD dwRequestId)
{

}
// 用户私聊请求回复消息
void CAnyChat::OnAnyChatPrivateEchoMessage(DWORD dwUserId, DWORD dwErrorCode)
{

}
// 用户退出私聊消息
void CAnyChat::OnAnyChatPrivateExitMessage(DWORD dwUserId, DWORD dwErrorCode)
{

}

// SDK警告消息
void CAnyChat::OnAnyChatSDKWarningMessage(DWORD dwErrorCode, DWORD dwReserved)
{

}

// 视频数据回调
void CAnyChat::OnAnyChatVideoDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPBITMAPINFOHEADER lpbmiHeader)
{

}
// 音频数据回调
void CAnyChat::OnAnyChatAudioDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPWAVEFORMATEX lpWaveFormatEx)
{

}
// 发送文字的回调函数
void CAnyChat::OnAnyChatTextMsgCallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen)
{

}
// 透明通道回调函数
void CAnyChat::OnAnyChatTransBufferCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen)
{

}
// 透明通道数据扩展回调函数
void CAnyChat::OnAnyChatTransBufferExCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId)
{

}
// 文件传输回调函数
void CAnyChat::OnAnyChatTransFileCallBack(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId)
{

}
// 音量变化回调函数
void CAnyChat::OnAnyChatVolumeChangeCallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume)
{

}
// SDK Filter 通信数据回调函数
void CAnyChat::OnAnyChatSDKFilterDataCallBack(LPBYTE lpBuf, DWORD dwLen)
{

}
// 录像、快照任务完成回调函数
void CAnyChat::OnAnyChatRecordSnapShotCallBack(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType)
{

}
// 异步消息通知回调函数
void CAnyChat::OnAnyChatNotifyMessageCallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam)
{

}
