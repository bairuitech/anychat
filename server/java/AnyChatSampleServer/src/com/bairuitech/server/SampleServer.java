package com.bairuitech.server;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.bairuitech.anychat.*;

public class SampleServer implements AnyChatServerEvent{

	public static AnyChatServerSDK anychat;
	public static int iUserIdSeed = 1;
	
	/**
	 * @param args
	 * @throws InterruptedException 
	 * @throws IOException 
	 */
	public static void main(String[] args) throws InterruptedException, IOException {
		anychat = new AnyChatServerSDK();
		anychat.SetServerEvent(new SampleServer());
		anychat.InitSDK(0);
		System.out.print(getCurrentTime() + "Welcome use AnyChat! (" + anychat.GetSDKVersion() + ")\r\n");
		Reader reader = new InputStreamReader(System.in);
		char ch = 0;
		do{
			if(ch != '\r')
				System.out.print(getCurrentTime() + "Business server(Java) still running, press 'q' to exit...\r\n");
			Thread.sleep(100);
		}while((ch=(char)reader.read()) != 'q');
		anychat.Release();
		System.out.print(getCurrentTime() + "Business server(Java) already exited...\r\n");
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
	public void OnAnyChatServerAppMessageCallBack(int dwMsg) {
		if(dwMsg == AnyChatServerSDK.BRAS_SERVERAPPMSG_CONNECTED)
			System.out.print(getCurrentTime() + "Success connected with anychatcoreserver...\r\n");
		else if(dwMsg == AnyChatServerSDK.BRAS_SERVERAPPMSG_DISCONNECT)
			System.out.print(getCurrentTime() + "ERROR: Disconnected from the anychatcoreserver, it may be the anychatcoreserver is closed!\r\n");
		else
			System.out.print(getCurrentTime() + "OnServerAppMessageCallBack: " + dwMsg + "\r\n");
	}
	
	// 用户身份验证，若验证成功，则必须返回0，且分配一个唯一的userid，若验证失败，则返回出错代码，不用分配userid
	@Override
	public int OnAnyChatVerifyUserCallBack(String szUserName, String szPassword, AnyChatVerifyUserOutParam outParam) {
		outParam.SetUserId(iUserIdSeed);		// 若身份验证成功，必须分配一个唯一的userid
		outParam.SetUserLevel(0);
		outParam.SetNickName(szUserName);
		
		System.out.print(getCurrentTime() + "OnVerifyUserCallBack: userid:" + iUserIdSeed + " username: " + szUserName + "\r\n");
		iUserIdSeed += 1;
		return 0;
	}
	
	@Override
	public void OnAnyChatUserLoginActionCallBack(int dwUserId, String szUserName, int dwLevel, String szIpAddr) {
		System.out.print(getCurrentTime() + "OnUserLoginActionCallBack: userid:" + dwUserId + " username: " + szUserName + "\r\n");
		// 演示如何使用TransBufferEx获取taskid
		/*AnyChatTransTaskOutParam outParam = new AnyChatTransTaskOutParam();
		byte[] sendbuf = new byte[100];
		int ret = AnyChatServerSDK.TransBufferEx(dwUserId, sendbuf, sendbuf.length, 0, 0, 0, outParam);
		System.out.print(getCurrentTime() + "TransBufferEx: ret:" + ret + " taskid: " + outParam.GetTaskId() + "\r\n");
		*/
	}
	
	@Override
	public void OnAnyChatUserLogoutActionCallBack(int dwUserId) {
		System.out.print(getCurrentTime() + "OnUserLogoutActionCallBack: userid:" + dwUserId + "\r\n");	
	}

	// 用户准备进入房间验证，如果允许用户进入房间，则必须返回0，则否返回出错代码
	@Override
	public int OnAnyChatPrepareEnterRoomCallBack(int dwUserId, int dwRoomId, String szRoomName, String szPassword) {
		System.out.print(getCurrentTime() + "OnPrepareEnterRoomCallBack: userid:" + dwUserId + " roomid: " + dwRoomId + "\r\n");
		return 0;
	}
	
	@Override
	public void OnAnyChatUserEnterRoomActionCallBack(int dwUserId, int dwRoomId) {
		System.out.print(getCurrentTime() + "OnUserEnterRoomActionCallBack: userid:" + dwUserId + " roomid: " + dwRoomId + "\r\n");
	}

	@Override
	public void OnAnyChatUserLeaveRoomActionCallBack(int dwUserId, int dwRoomId) {
		System.out.print(getCurrentTime() + "OnUserLeaveRoomActionCallBack: userid:" + dwUserId + " roomid: " + dwRoomId + "\r\n");
	}
	
	@Override
	public void OnAnyChatTransFile(int dwUserId, String szFileName, String szTempFilePath, int dwFileLength, int wParam, int lParam, int dwTaskId) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void OnAnyChatTransBuffer(int dwUserId, byte[] lpBuf, int dwLen) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void OnAnyChatTransBufferEx(int dwUserId, byte[] lpBuf, int dwLen, int wParam, int lParam, int dwTaskId) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void OnAnyChatSDKFilterData(int dwUserId, byte[] lpBuf, int dwLen) {
		System.out.print(getCurrentTime() + "OnAnyChatSDKFilterData\r\n");
		
	}

	@Override
	public void OnAnyChatTimerEventCallBack() {
		System.out.print(getCurrentTime() + "OnTimerEventCallBack\r\n");
		
	}

	/**
	 * 文字消息回调，客户端调用文字发送api会触发该回调
	 */
	@Override
	public void OnAnyChatRecvUserTextMsgCallBack(int dwRoomId, int dwSrcUserId, int dwTarUserId, int bSecret, String szTextMessage, int dwLen) {
		System.out.print(getCurrentTime() + "OnAnyChatRecvUserTextMsgCallBack: " + dwSrcUserId + " to " + dwTarUserId + " " + szTextMessage +"\r\n");
		
	}

	/**
	 * 服务器录像回调函数，由中心录像服务器触发
	 * 参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=20&extra=page%3D1
	 */
	@Override
	public void OnAnyChatServerRecordCallBack(int dwUserId, int dwParam, int dwRecordServerId, int dwElapse, String szRecordFileName) {
		// TODO Auto-generated method stub
		String str = "OnAnyChatServerRecordCallBack: dwUserId" + dwUserId + " szRecordFileName:" + szRecordFileName;
		System.out.print(getCurrentTime() + str + "\r\n");
	}

	/**
	 * 视频呼叫事件回调，客户端调用API：BRAC_VideoCallControl会触发该回调
	 */
	@Override
	public int OnAnyChatVideoCallEventCallBack(int dwEventType,
			int dwSrcUserId, int dwTarUserId, int dwErrorCode, int dwFlags,
			int dwParam, String lpUserStr) {
		String str = "OnAnyChatVideoCallEventCallBack: dwEventType:" + dwEventType + " dwSrcUserId:" + dwSrcUserId + 
			" dwTarUserId:" + dwTarUserId + " dwErrorCode:" + dwErrorCode + " dwFlags:" + dwFlags + " dwParam:" + dwParam + " lpUserStr:" + lpUserStr;
		System.out.print(getCurrentTime() + str + "\r\n");
		return 0;
	}


	

	

	

	

}
