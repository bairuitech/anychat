package com.bairuitech.demo;

import java.io.UnsupportedEncodingException;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JLabel;

import com.bairuitech.anychat.AnyChatBaseEvent;
import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import com.bairuitech.anychat.AnyChatTextMsgEvent;
import com.bairuitech.anychat.AnyChatTransDataEvent;

public class AnyChatDemo implements AnyChatBaseEvent, AnyChatTextMsgEvent,
		AnyChatTransDataEvent {

	private static LoginJFrame mLoginJframe;
	private static RoomListJFrame mRoomJframe;
	private static VideoJFrame mVideoJframe;
	private static AnyChatCoreSDK anychat;
	private static AnyChatDemo mInstance;
	private static boolean bRealse = false;
	private int dwSelfUserid;


	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("java.library.path is " + System.getProperty("java.library.path"));
		// TODO Auto-generated method stub
		mInstance = new AnyChatDemo();
		initSdk();
		anychat.InitSDK(0, 0);
		bRealse = true;
//		anychat.SetSDKOptionString(AnyChatDefine.BRAC_SO_CORESDK_TMPDIR, "d:\\");
		initView();
	}

	static void initView() {
		mLoginJframe = new LoginJFrame(anychat);
	}
	static void initSdk()
	{
		if(anychat==null)
			anychat = AnyChatCoreSDK.getInstance();
		// 如果BRAnyChatCore.dll及其它库不在当前路径下，则需要设置相关库的路径，实现应用程序与AnyChat库的解耦
		int ret = anychat.SetSDKOptionString(AnyChatDefine.BRAC_SO_CORESDK_PATH, "C:\\Program Files (x86)\\BaiRuiTech\\AnyChatWeb");
		if(ret != 0)
			ret = anychat.SetSDKOptionString(AnyChatDefine.BRAC_SO_CORESDK_PATH, "C:\\Program Files\\BaiRuiTech\\AnyChatWeb");
		if(ret != 0)
			ret = anychat.SetSDKOptionString(AnyChatDefine.BRAC_SO_CORESDK_PATH, "D:\\Program Files (x86)\\BaiRuiTech\\AnyChatWeb");
		if(ret != 0)
			ret = anychat.SetSDKOptionString(AnyChatDefine.BRAC_SO_CORESDK_PATH, "D:\\Program Files\\BaiRuiTech\\AnyChatWeb");
		anychat.SetBaseEvent(mInstance);
	}
	
	@Override
	public void OnAnyChatTextMessage(int dwFromUserid, int dwToUserid,
			boolean bSecret, String message) {
		// TODO Auto-generated method stub
		System.out.println(message);
	}

	@Override
	public void OnAnyChatConnectMessage(boolean bSuccess) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatLoginMessage(int dwUserId, int dwErrorCode) {
		// TODO Auto-generated method stub
		if (dwErrorCode == 0) {
			mLoginJframe.hideLogin();
			mRoomJframe = new RoomListJFrame(anychat, dwUserId);
			dwSelfUserid = dwUserId;
		}
	}

	@Override
	public void OnAnyChatEnterRoomMessage(int dwRoomId, int dwErrorCode) {
		// TODO Auto-generated method stub
		if (dwErrorCode == 0) {

			mRoomJframe.setVisible(false);
			mVideoJframe = new VideoJFrame(anychat, dwSelfUserid,mRoomJframe);
			anychat.UserCameraControl(-1, 1);
			anychat.UserSpeakControl(-1, 1);
			anychat.SetVideoPos(-1, mVideoJframe, 10, 440, 260, 640);

		}
		System.out.println(dwErrorCode + "");
	}

	@Override
	public void OnAnyChatOnlineUserMessage(int dwUserNum, int dwRoomId) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatUserAtRoomMessage(int dwUserId, boolean bEnter) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatLinkCloseMessage(int dwErrorCode) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatTransFile(int dwUserid, String FileName,
			String TempFilePath, int dwFileLength, int wParam, int lParam,
			int dwTaskId) {
		// TODO Auto-generated method stub
		System.out.println(FileName);
	}

	@Override
	public void OnAnyChatTransBuffer(int dwUserid, byte[] lpBuf, int dwLen) {
		// TODO Auto-generated method stub
		String strContent = "";
		try {
			strContent = new String(lpBuf, "GB2312");
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(strContent);
	}

	@Override
	public void OnAnyChatTransBufferEx(int dwUserid, byte[] lpBuf, int dwLen,
			int wparam, int lparam, int taskid) {
		// TODO Auto-generated method stub

	}

	@Override
	public void OnAnyChatSDKFilterData(byte[] lpBuf, int dwLen) {
		// TODO Auto-generated method stub

	}

}
