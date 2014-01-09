package com.bairuitech.bussinesscenter;

public interface VideoCallContrlHandler {

	public void VideoCall_SessionRequest(int dwUserId, int dwFlags, int dwParam, String szUserStr);
	public void VideoCall_SessionReply(int dwUserId, int dwErrorCode,int dwFlags, int dwParam, String szUserStr);
	public void VideoCall_SessionStart(int dwUserId, int dwFlags, int dwParam, String szUserStr);
	public void VideoCall_SessionEnd(int dwUserId, int dwFlags, int dwParam, String szUserStr);

}
