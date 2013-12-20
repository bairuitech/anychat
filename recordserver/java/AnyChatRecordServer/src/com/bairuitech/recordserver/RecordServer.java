package com.bairuitech.recordserver;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.bairuitech.anychat.*;

public class RecordServer implements AnyChatRecordServerEvent{

	public static AnyChatRecordServerSDK anychat;
	
	/**
	 * @param args
	 * @throws InterruptedException 
	 * @throws IOException 
	 */
	public static void main(String[] args) throws InterruptedException, IOException {
		anychat = new AnyChatRecordServerSDK();
		anychat.SetServerEvent(new RecordServer());
		anychat.InitSDK(0);
		anychat.RegisterRecordResultClass(new AnyChatRecordResult());
		System.out.print(getCurrentTime() + "Welcome use AnyChat Record Server! (" + anychat.GetSDKVersion() + ")\r\n");
		Reader reader = new InputStreamReader(System.in);
		char ch = 0;
		do{
			if(ch != '\r')
				System.out.print(getCurrentTime() + "Record server(Java) still running, press 'q' to exit...\r\n");
			Thread.sleep(100);
		}while((ch=(char)reader.read()) != 'q');
		anychat.Release();
		System.out.print(getCurrentTime() + "Record server(Java) already exited...\r\n");
	}

	/**
	 * 获取当前时间
	 */
	public static String getCurrentTime() {
		Date date = new Date(System.currentTimeMillis());
		SimpleDateFormat tm = new SimpleDateFormat("MM-dd HH:mm:ss:SSS");
		String strTime = "";
		try {
			strTime = tm.format(date) + "\t";
		} catch (Exception e) {
			e.printStackTrace();
		}
		return strTime;
	}
	
	@Override
	public void OnAnyChatRecordServerAppMessageCallBack(int dwMsg, int wParam, int lParam) {
		if(dwMsg == AnyChatRecordServerSDK.BRRS_SERVERAPPMSG_CONNECTED)
			System.out.print(getCurrentTime() + "Success connected with anychatcoreserver...\r\n");
		else if(dwMsg == AnyChatRecordServerSDK.BRRS_SERVERAPPMSG_DISCONNECT)
			System.out.print(getCurrentTime() + "ERROR: Disconnected from the anychatcoreserver, errorcode:" + wParam + ")\r\n");
		else
			System.out.print(getCurrentTime() + "OnServerAppMessageCallBack: " + dwMsg + "\r\n");
	}
	// 录像开始事件回调函数
	@Override
	public int OnAnyChatRecordStartCallBack(int dwUserId) {
		String nickname = AnyChatRecordServerSDK.QueryUserStrInfo(dwUserId, AnyChatRecordServerSDK.BRRS_USERINFO_TYPE_NICKNAME);
		System.out.print(getCurrentTime() + "OnAnyChatRecordStartCallBack: " + dwUserId + "(" + nickname + ")\r\n");
		// 判断是否有视频流信息
		int videoCodec = AnyChatRecordServerSDK.QueryUserIntInfo(dwUserId, AnyChatRecordServerSDK.BRRS_USERINFO_TYPE_VCODEC);
		if(videoCodec != 0) {
			// videoCodec=1，H.264编码
			System.out.print(getCurrentTime() + "\tvideo info: codec=" + videoCodec + 
					" width: " + AnyChatRecordServerSDK.QueryUserIntInfo(dwUserId, AnyChatRecordServerSDK.BRRS_USERINFO_TYPE_WIDTH) +
					" height: " + AnyChatRecordServerSDK.QueryUserIntInfo(dwUserId, AnyChatRecordServerSDK.BRRS_USERINFO_TYPE_HEIGHT) +
					" fps: " + AnyChatRecordServerSDK.QueryUserIntInfo(dwUserId, AnyChatRecordServerSDK.BRRS_USERINFO_TYPE_FRAMERATE) + "\r\n");
		}
		// 判断是否有音频流信息
		int audioCodec = AnyChatRecordServerSDK.QueryUserIntInfo(dwUserId, AnyChatRecordServerSDK.BRRS_USERINFO_TYPE_ACODEC);
		if(audioCodec != 0) {
			// audioCodec=11，AMR_WB编码
			System.out.print(getCurrentTime() + "\taudio info: codec=" + audioCodec + 
					" samplerate: " + AnyChatRecordServerSDK.QueryUserIntInfo(dwUserId, AnyChatRecordServerSDK.BRRS_USERINFO_TYPE_SAMPLERATE) +
					" channels: " + AnyChatRecordServerSDK.QueryUserIntInfo(dwUserId, AnyChatRecordServerSDK.BRRS_USERINFO_TYPE_CHANNELS) +
					" samplebits: " + AnyChatRecordServerSDK.QueryUserIntInfo(dwUserId, AnyChatRecordServerSDK.BRRS_USERINFO_TYPE_SAMPLEBITS) + "\r\n");
		}
	
		return 0;
	}
	// 录像数据回调函数
	@Override
	public int OnAnyChatRecordBufferCallBack(int dwUserId, byte[] lpBuf, int dwLen, int timestamp, int flags) {
		if((flags&AnyChatRecordServerSDK.BRRS_RECORD_FLAGS_VIDEO) != 0)
		{
			// 视频流编码数据
			Boolean bKeyFrame = (flags&AnyChatRecordServerSDK.BRRS_RECORD_FLAGS_KEYFRAME) != 0;
			System.out.print(getCurrentTime() + "OnAnyChatRecordBufferCallBack: " + dwUserId + " video, bKeyFrame:" + bKeyFrame + " size:" + dwLen + " timestamp:" + timestamp + "\r\n");
		}
		else if((flags&AnyChatRecordServerSDK.BRRS_RECORD_FLAGS_AUDIO) != 0)
		{
			// 音频流编码数据
			Boolean bSilence = (flags&AnyChatRecordServerSDK.BRRS_RECORD_FLAGS_SILENCE) != 0;
			System.out.print(getCurrentTime() + "OnAnyChatRecordBufferCallBack: " + dwUserId + " audio, bSilence:" + bSilence + " size:" + dwLen + " timestamp:" + timestamp + "\r\n");
		}
		else if((flags&AnyChatRecordServerSDK.BRRS_RECORD_FLAGS_BUFFER) != 0)
		{
			// 数据流数据（业务服务器调用API：TransBuffer2RecordServer发送）
			System.out.print(getCurrentTime() + "OnAnyChatRecordBufferCallBack: " + dwUserId + " buffer, size:" + dwLen + " timestamp:" + timestamp + "\r\n");
		}
		return 0;
	}
	// 录像结束事件回调函数
	@Override
	public int OnAnyChatRecordFinishCallBack(int dwUserId, AnyChatRecordResult result) {
		System.out.print(getCurrentTime() + "OnAnyChatRecordFinishCallBack: " + dwUserId + "\r\n");
		
		// 录像结束后，必须返回录像文件名、录像时长参数，AnyChat内核会通知给业务服务器
		result.SetFileName("temp\\test.mp4");
		result.SetSeconds(10);
		return 0;
	}
	

}
