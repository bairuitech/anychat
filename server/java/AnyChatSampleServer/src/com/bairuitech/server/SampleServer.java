package com.bairuitech.server;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;

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
		System.out.print("Welcome use AnyChat! (" + anychat.GetSDKVersion() + ")\r\n");
		Reader reader = new InputStreamReader(System.in);
		do{
			System.out.print("Business server(Java) still running, press 'q' to exit...\r\n\r\n");
			Thread.sleep(100);
		}while((char)reader.read() != 'q');
		System.out.print("Business server(Java) already exited...\r\n");
	}

	@Override
	public void OnAnyChatServerAppMessageCallBack(int dwMsg) {
		if(dwMsg == AnyChatServerSDK.BRAS_SERVERAPPMSG_CONNECTED)
			System.out.print("Success connected with anychatcoreserver...\r\n");
		else if(dwMsg == AnyChatServerSDK.BRAS_SERVERAPPMSG_DISCONNECT)
			System.out.print("ERROR: Disconnected from the anychatcoreserver, it may be the anychatcoreserver is closed!\r\n");
		else
			System.out.print("OnServerAppMessageCallBack: " + dwMsg + "\r\n");
	}
	
	@Override
	public int OnAnyChatVerifyUserCallBack(String szUserName, String szPassword, VerifyUserOutParam outParam) {
		outParam.SetUserId(iUserIdSeed);
		outParam.SetUserLevel(0);
		outParam.SetNickName(szUserName);
		
		System.out.print("OnVerifyUserCallBack: userid:" + iUserIdSeed + " username: " + szUserName + "\r\n");
		iUserIdSeed += 1;
		return 0;
	}
	
	@Override
	public void OnAnyChatUserLoginActionCallBack(int dwUserId, String szUserName, int dwLevel, String szIpAddr) {
		System.out.print("OnUserLoginActionCallBack: userid:" + dwUserId + " username: " + szUserName + "\r\n");
		// ��ʾTransBufferEx����
		/*TransTaskOutParam outParam = new TransTaskOutParam();
		byte[] sendbuf = new byte[100];
		int ret = AnyChatServerSDK.TransBufferEx(dwUserId, sendbuf, sendbuf.length, 0, 0, 0, outParam);
		System.out.print("TransBufferEx: ret:" + ret + " taskid: " + outParam.GetTaskId() + "\r\n");
		*/
	}
	
	@Override
	public void OnAnyChatUserLogoutActionCallBack(int dwUserId) {
		System.out.print("OnUserLogoutActionCallBack: userid:" + dwUserId + "\r\n");	
	}

	// �û�������뷿��ص������������û����뷿�䣬�򷵻�0�����򷵻س������
	@Override
	public int OnAnyChatPrepareEnterRoomCallBack(int dwUserId, int dwRoomId, String szRoomName, String szPassword) {
		System.out.print("OnPrepareEnterRoomCallBack: userid:" + dwUserId + " roomid: " + dwRoomId + "\r\n");
		return 0;
	}
	
	@Override
	public void OnAnyChatUserEnterRoomActionCallBack(int dwUserId, int dwRoomId) {
		System.out.print("OnUserEnterRoomActionCallBack: userid:" + dwUserId + " roomid: " + dwRoomId + "\r\n");
	}

	@Override
	public void OnAnyChatUserLeaveRoomActionCallBack(int dwUserId, int dwRoomId) {
		System.out.print("OnUserLeaveRoomActionCallBack: userid:" + dwUserId + " roomid: " + dwRoomId + "\r\n");
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
		System.out.print("OnAnyChatSDKFilterData\r\n");
		
	}

	@Override
	public void OnAnyChatTimerEventCallBack() {
		System.out.print("OnTimerEventCallBack\r\n");
		
	}

	@Override
	public void OnAnyChatRecvUserTextMsgCallBack(int dwRoomId, int dwSrcUserId, int dwTarUserId, int bSecret, String szTextMessage, int dwLen) {
		System.out.print("OnAnyChatRecvUserTextMsgCallBack: " + dwSrcUserId + " to " + dwTarUserId + " " + szTextMessage +"\r\n");
		
	}

	@Override
	public void OnAnyChatServerRecordCallBack(int dwUserId, int dwParam, int dwRecordServerId, int dwElapse, String szRecordFileName) {
		// TODO Auto-generated method stub
		
	}


	

	

	

	

}
