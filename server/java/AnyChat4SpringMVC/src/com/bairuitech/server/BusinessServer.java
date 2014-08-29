package com.bairuitech.server;

import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.Vector;

import com.bairuitech.anychat.AnyChatServerEvent;
import com.bairuitech.anychat.AnyChatServerSDK;
import com.bairuitech.anychat.AnyChatVerifyUserOutParam;

/**
 * AnyChat Platform Core SDK ---- Business Server
 */
public class BusinessServer implements AnyChatServerEvent {
	public AnyChatServerSDK anychatserver;
	public StringBuilder message = new StringBuilder();
	public static int iUserIdSeed = 1;

	// 在线用户列表
	public static ArrayList<Integer> onlineusers = new ArrayList<Integer>();
	
	public BusinessServer() {

	}

	/**
	 * 获取当前时间
	 */
	private String getCurrentTime() {
		Date date = new Date(System.currentTimeMillis());
		SimpleDateFormat sdf = new SimpleDateFormat("MM-dd HH:mm:ss:SS");
		String strTime = "";
		try {
			strTime = sdf.format(date);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return strTime;

	}

	/**
	 * 初始化AnyChat Sdk
	 */
	public void initSdk() {
		anychatserver = new AnyChatServerSDK();
		anychatserver.SetServerEvent(this); // 设置回调
		anychatserver.InitSDK(0); // 初始化SDK
		anychatserver.RegisterVerifyUserClass(new AnyChatVerifyUserOutParam());
		String sdkVersion = anychatserver.GetSDKVersion();
		message.append(sdkVersion + "\r\n");
		System.out.println(message);
	}

	private void generateLog(String str) {
		message.append(getCurrentTime() + "  ");
		message.append(str);
		message.append("\n");
		System.out.println(message);
	}

	/**
	 * 连接核心服务器回调消息
	 */
	@Override
	public void OnAnyChatServerAppMessageExCallBack(int dwNotifyMessage, int wParam, int lParam) {
		String str = "";
		if(dwNotifyMessage == AnyChatServerSDK.BRAS_MESSAGE_CORESERVERCONN)
		{
			if(wParam == 0)
				str = "Success connected with anychatcoreserver...";
			else
				str = "ERROR: Disconnected from the anychatcoreserver, errorcode:" + wParam;
			onlineusers.clear();
		}
		else if(dwNotifyMessage == AnyChatServerSDK.BRAS_MESSAGE_RECORDSERVERCONN)
		{
			if(wParam == 0)
				str = "Success connected with anychatrecordserver(id:" + lParam + ") ...";
			else
				str = "ERROR: Disconnected from the anychatrecordserver, errorcode:" + wParam;
		}
		else
			str = "OnServerAppMessageExCallBack, dwNotifyMessage:" + dwNotifyMessage + " wParam:" + wParam + " lParam:" + lParam;
		generateLog(str);
	}

	/**
	 * 用户登录验证函数，可以在此函数中进行验证登录，赋值客户端userid等操作
	 */
	@Override
	public int OnAnyChatVerifyUserCallBack(String szUserName, String szPassword, AnyChatVerifyUserOutParam outParam) {
		outParam.SetUserId(iUserIdSeed);
		outParam.SetUserLevel(0);
		outParam.SetNickName(szUserName);
		iUserIdSeed += 1;
		String str = "OnVerifyUserCallBack: userid:" + iUserIdSeed + " username: " + szUserName;
		generateLog(str);
		return 0;
	}

	/**
	 * 用户登录成功回调
	 */
	@Override
	public void OnAnyChatUserLoginActionCallBack(int dwUserId, String szUserName, int dwLevel, String szIpAddr) {
		System.out.print("OnUserLoginActionCallBack: userid:" + dwUserId + " username: " + szUserName + "\r\n");

		// 将本地用户加入在线用户列表
		onlineusers.add(dwUserId);	
		
		String str = "OnAnyChatUserLoginActionCallBack: userid:" + dwUserId + " username: " + szUserName + " Ip: " + szIpAddr;
		generateLog(str);
	}

	/**
	 * 用户退出登录回调
	 */
	@Override
	public void OnAnyChatUserLogoutActionExCallBack(int dwUserId, int dwErrorCode) {
		String str = "OnUserLogoutActionExCallBack: userid:" + dwUserId + " errorcode:" + dwErrorCode;
		generateLog(str);
		
		// 从在线用户列表中删除
	    Iterator<Integer> it = onlineusers.iterator();
	    while(it.hasNext())
	    {
	        if(it.next() == dwUserId)
	        {
	        	it.remove();
	        	break;
	        }
	    }
	}

	/**
	 * 用户退出登录回调
	 */
	@Override
	public int OnAnyChatPrepareEnterRoomCallBack(int dwUserId, int dwRoomId, String szRoomName, String szPassword) {
		String str = "OnPrepareEnterRoomCallBack: userid:" + dwUserId + " roomid: " + dwRoomId;
		generateLog(str);
		return 0;
	}

	/**
	 * 用户进入房间验证回调，可以在此函数中验证登录房间
	 */
	@Override
	public void OnAnyChatUserEnterRoomActionCallBack(int dwUserId, int dwRoomId) {
		String str = "OnUserEnterRoomActionCallBack: userid:" + dwUserId + " roomid: " + dwRoomId;
		generateLog(str);
	}

	/**
	 * 用户进入房间验证回调，可以在此函数中验证登录房间
	 */
	@Override
	public void OnAnyChatUserLeaveRoomActionCallBack(int dwUserId, int dwRoomId) {
		String str = "OnAnyChatUserLeaveRoomActionCallBack: userid:" + dwUserId	+ " roomid: " + dwRoomId;
		generateLog(str);
	}

	/**
	 * 接收文件回调
	 */

	@Override
	public void OnAnyChatTransFile(int dwUserId, String szFileName, String szTempFilePath, int dwFileLength, int wParam, int lParam, int dwTaskId) {
		// TODO Auto-generated method stub
		String str = "OnAnyChatTransFile->" + "from:" + dwUserId + ";filename:" + szFileName + "path:" + szTempFilePath;
		generateLog(str);
	}

	/**
	 * 接收透明头道数据回调，
	 */
	@Override
	public void OnAnyChatTransBuffer(int dwUserId, byte[] lpBuf, int dwLen) {
		// TODO Auto-generated method stub
		String str = "";
		try {
			str = new String(lpBuf, "GB2312");
			System.out.println(str);
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		generateLog("OnAnyChatTransBuffer:" + " fromUserid:" + dwUserId + str);
	}

	/**
	 * 接收扩展透明头道数据回调，
	 */
	@Override
	public void OnAnyChatTransBufferEx(int dwUserId, byte[] lpBuf, int dwLen, int wParam, int lParam, int dwTaskId) {
		// TODO Auto-generated method stub

		String str = "";
		try {
			str = new String(lpBuf, "GB2312");
			System.out.println(str);
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		message.append("OnAnyChatTransBufferEx:" + " fromUserid:" + dwUserId + str);
		generateLog("OnAnyChatTransBufferEx:" + " fromUserid:" + dwUserId + str);
	}

	/**
	 * 接收SDKfilter数据回调
	 */
	@Override
	public void OnAnyChatSDKFilterData(int dwUserId, byte[] lpBuf, int dwLen) {

		String str = "";
		try {
			str = new String(lpBuf, "GB2312");
			System.out.println(str);
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		message.append("OnAnyChatSDKFilterData:" + " fromUserid:" + dwUserId + str);
		generateLog("OnAnyChatSDKFilterData:" + " fromUserid:" + dwUserId + str);
	}

	@Override
	public void OnAnyChatTimerEventCallBack() {
		System.out.print("OnTimerEventCallBack\r\n");

	}

	/**
	 * 文字消息回调，客户端调用文字发送api会触发该回调
	 */
	@Override
	public void OnAnyChatRecvUserTextMsgCallBack(int dwRoomId, int dwSrcUserId,	int dwTarUserId, int bSecret, String szTextMessage, int dwLen) {
		String str = "OnAnyChatRecvUserTextMsgCallBack: " + dwSrcUserId	+ " to " + dwTarUserId + " " + szTextMessage;
		generateLog(str);
	}

	/**
	 * 服务器录像（扩展）回调函数，由中心录像服务器触发
	 * 参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=20&extra=page%3D1
	 */
	@Override
	public void OnAnyChatServerRecordExCallBack(int dwUserId, String szRecordFileName, int dwElapse, int dwFlags, int dwParam, String lpUserStr, int dwRecordServerId){
		boolean bSnapShotEvent = ((dwFlags & AnyChatServerSDK.ANYCHAT_RECORD_FLAGS_SNAPSHOT) != 0);	// 是否为拍照事件
		String eventStr;
		if(bSnapShotEvent)
			eventStr = " ,SnapShot Event";
		else
			eventStr = " ,Record Event";
		String str = "OnAnyChatServerRecordExCallBack: dwUserId" + dwUserId + eventStr + " ,szRecordFileName:" + szRecordFileName + " lpUserStr:" + lpUserStr;
		generateLog(str);
	}

	/**
	 * 视频呼叫事件回调，客户端调用API：BRAC_VideoCallControl会触发该回调
	 */
	@Override
	public int OnAnyChatVideoCallEventCallBack(int dwEventType,	int dwSrcUserId, int dwTarUserId, int dwErrorCode, int dwFlags, int dwParam, String lpUserStr) {
		String str = "OnAnyChatVideoCallEventCallBack: dwEventType:" + dwEventType + " dwSrcUserId:" + dwSrcUserId + 
			" dwTarUserId:" + dwTarUserId + " dwErrorCode:" + dwErrorCode + " dwFlags:" + dwFlags + " dwParam:" + dwParam + " lpUserStr:" + lpUserStr;
		generateLog(str);
		return 0;
	}

	/**
	 *	用户信息控制回调，客户端调用API：BRAC_UserInfoControl会触发该回调
	 */
	@Override
	public int OnAnyChatUserInfoCtrlCallBack(int dwSendUserId, int dwUserId, int dwCtrlCode, int wParam, int lParam, String lpStrValue) {
		String str = "OnAnyChatUserInfoCtrlCallBack: dwSendUserId:" + dwSendUserId + " dwUserId:" + dwUserId + " dwCtrlCode:" + 
			dwCtrlCode + " wParam:" + wParam + " lParam:" + lParam + " lpStrValue:" + lpStrValue;
		generateLog(str);
		return 0;
	}
	
	
}
