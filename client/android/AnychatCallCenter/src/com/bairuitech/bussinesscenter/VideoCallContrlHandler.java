package com.bairuitech.bussinesscenter;

public interface VideoCallContrlHandler {
    public static final int ERRORCODE_SUCCESS=0;
    public static final int ERRORCODE_SESSION_QUIT = 100101;// 源用户主动放弃会话
    public static final int ERRORCODE_SESSION_OFFLINE = 100102;// 目标用户不在线
    public static final int ERRORCODE_SESSION_BUSY = 100103;// 目标用户忙
    public static final int ERRORCODE_SESSION_REFUSE = 100104;// 目标用户拒绝会话
    public static final int ERRORCODE_SESSION_TIMEOUT = 100105;//会话请求超时
    public static final int ERRORCODE_SESSION_DISCONNECT= 100106;// 网络断线
	public void VideoCall_SessionRequest(int dwUserId, int dwFlags, int dwParam, String szUserStr);
	public void VideoCall_SessionReply(int dwUserId, int dwErrorCode,int dwFlags, int dwParam, String szUserStr);
	public void VideoCall_SessionStart(int dwUserId, int dwFlags, int dwParam, String szUserStr);
	public void VideoCall_SessionEnd(int dwUserId, int dwFlags, int dwParam, String szUserStr);

}
