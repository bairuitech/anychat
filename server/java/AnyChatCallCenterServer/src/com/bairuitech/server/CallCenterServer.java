package com.bairuitech.server;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.ArrayList;
import java.util.Iterator;

import com.bairuitech.anychat.*;

public class CallCenterServer implements AnyChatServerEvent{

	public static AnyChatServerSDK anychat;
	public static int iUserIdSeed = 1;
	
	// 在线用户列表
	public static ArrayList<Integer> onlineusers = new ArrayList<Integer>();
	
	/**
	 * @param args
	 * @throws InterruptedException 
	 * @throws IOException 
	 */
	public static void main(String[] args) throws InterruptedException, IOException {
		anychat = new AnyChatServerSDK();
		anychat.SetServerEvent(new CallCenterServer());
		anychat.InitSDK(0);
		anychat.RegisterVerifyUserClass(new AnyChatVerifyUserOutParam());
		System.out.print(getCurrentTime() + "Welcome use AnyChat! (" + anychat.GetSDKVersion() + ")\r\n");
		Reader reader = new InputStreamReader(System.in);
		char ch = 0;
		do{
			if(ch != '\r')
				System.out.print(getCurrentTime() + "AnyChatCallCenter server(Java) still running, press 'q' to exit...\r\n");
			Thread.sleep(100);
		}while((ch=(char)reader.read()) != 'q');
		anychat.Release();
		System.out.print(getCurrentTime() + "AnyChatCallCenter server(Java) already exited...\r\n");
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
	public void OnAnyChatServerAppMessageExCallBack(int dwNotifyMessage, int wParam, int lParam) {
		if(dwNotifyMessage == AnyChatServerSDK.BRAS_MESSAGE_CORESERVERCONN)
		{
			if(wParam == 0)
				System.out.print(getCurrentTime() + "Success connected with anychatcoreserver...\r\n");
			else
				System.out.print(getCurrentTime() + "ERROR: Disconnected from the anychatcoreserver, errorcode:" + wParam + "\r\n");
			onlineusers.clear();
		}
		else if(dwNotifyMessage == AnyChatServerSDK.BRAS_MESSAGE_RECORDSERVERCONN)
		{
			if(wParam == 0)
				System.out.print(getCurrentTime() + "Success connected with anychatrecordserver(id:" + lParam + ") ...\r\n");
			else
				System.out.print(getCurrentTime() + "ERROR: Disconnected from the anychatrecordserver, errorcode:" + wParam + "\r\n");
		}
		else
			System.out.print(getCurrentTime() + "OnServerAppMessageExCallBack, dwNotifyMessage:" + dwNotifyMessage + " wParam:" + wParam + " lParam:" + lParam + "\r\n");
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
		/*AnyChatOutParam outParam = new AnyChatOutParam();
		byte[] sendbuf = new byte[100];
		int ret = AnyChatServerSDK.TransBufferEx(dwUserId, sendbuf, sendbuf.length, 0, 0, 0, outParam);
		System.out.print(getCurrentTime() + "TransBufferEx: ret:" + ret + " taskid: " + outParam.GetIntValue() + "\r\n");
		*/
		
		// 添加用户分组
		int iGroupId = 1;
		AnyChatServerSDK.UserInfoControl(dwUserId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_ADDGROUP, iGroupId, 0, "我的好友");	// 用户名+密码方式登录的用户
		iGroupId = 2;
		AnyChatServerSDK.UserInfoControl(dwUserId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_ADDGROUP, iGroupId, 0, "在线游客");	// 密码为空的用户
		
		// 将当前所有在线用户添加为自己的好友
		for(Integer otheruserid : onlineusers)
			AnyChatServerSDK.UserInfoControl(dwUserId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_ADDFRIEND, otheruserid, 0, "");
		
		// 设置好友与分组的关系（即好友属于哪一个分组）
		iGroupId = 1;
		for(Integer otheruserid : onlineusers)
		{
			iGroupId = (otheruserid > 0) ? 1 : 2;		// 游客密码为空，userid由核心服务器分配，为负数
			AnyChatServerSDK.UserInfoControl(dwUserId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_SETGROUPRELATION, iGroupId, otheruserid, "");
		}
		
		// 设置当前用户信息（用户资料，客户端可以通过API：BRAC_GetUserInfo来获取这些信息）
		int iInfoId = 1;	// InfoId由业务层自己定义
		AnyChatServerSDK.SetUserInfo(dwUserId, iInfoId, szUserName, 0);
		iInfoId = 2;
		AnyChatServerSDK.SetUserInfo(dwUserId, iInfoId, szIpAddr, 0);
		iInfoId = 3;
		AnyChatServerSDK.SetUserInfo(dwUserId, iInfoId, "我的签名", 0);
		iInfoId = 4;
		AnyChatServerSDK.SetUserInfo(dwUserId, iInfoId, String.valueOf(dwUserId%10 + 1), 0);		// 随机分配一个图像ID
		
		// 将本地用户添加为其它用户的好友列表中
		for(Integer otheruserid : onlineusers)
		{
			// 添加好友
			AnyChatServerSDK.UserInfoControl(otheruserid, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_ADDFRIEND, dwUserId, 0, "");
			// 关联好友分组
			iGroupId = (dwUserId > 0) ? 1 : 2;
			AnyChatServerSDK.UserInfoControl(otheruserid, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_SETGROUPRELATION, iGroupId, dwUserId, "");
			// 下发同步指令，将新设置的好友同步给客户端
			AnyChatServerSDK.UserInfoControl(otheruserid, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_SYNCDATA,  0, 0, "");
		}
		
		// 下发同步指令，将前面设置的资料同步给当前客户端
		AnyChatServerSDK.UserInfoControl(dwUserId, AnyChatServerSDK.BRAS_USERINFO_CTRLCODE_SYNCDATA,  0, 0, "");
		
		// 将本地用户加入在线用户列表
		onlineusers.add(dwUserId);
	}
	
	@Override
	public void OnAnyChatUserLogoutActionExCallBack(int dwUserId, int dwErrorCode) {
		System.out.print(getCurrentTime() + "OnUserLogoutActionExCallBack: userid:" + dwUserId + " errorcode:" + dwErrorCode + "\r\n");	
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
	    // 核心服务器会通知其它用户（如果是好友），提示好友下线，不需要业务服务器干预
	    
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
		System.out.print(getCurrentTime() + str + "\r\n");
	}

	/**
	 * 视频呼叫事件回调，客户端调用API：BRAC_VideoCallControl会触发该回调
	 */
	@Override
	public int OnAnyChatVideoCallEventCallBack(int dwEventType, int dwSrcUserId, int dwTarUserId, int dwErrorCode, int dwFlags, int dwParam, String lpUserStr) {
		String str = "OnAnyChatVideoCallEventCallBack: dwEventType:" + dwEventType + " dwSrcUserId:" + dwSrcUserId + 
			" dwTarUserId:" + dwTarUserId + " dwErrorCode:" + dwErrorCode + " dwFlags:" + dwFlags + " dwParam:" + dwParam + " lpUserStr:" + lpUserStr;
		System.out.print(getCurrentTime() + str + "\r\n");
		return 0;
	}

	/**
	 *	用户信息控制回调，客户端调用API：BRAC_UserInfoControl会触发该回调
	 */
	@Override
	public int OnAnyChatUserInfoCtrlCallBack(int dwSendUserId, int dwUserId, int dwCtrlCode, int wParam, int lParam, String lpStrValue) {
		String str = "OnAnyChatUserInfoCtrlCallBack: dwSendUserId:" + dwSendUserId + " dwUserId:" + dwUserId + " dwCtrlCode:" + 
			dwCtrlCode + " wParam:" + wParam + " lParam:" + lParam + " lpStrValue:" + lpStrValue;
		System.out.print(getCurrentTime() + str + "\r\n");
		return 0;
	}

	@Override
	public int OnAnyChatObjectEventCallBack(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, String lpStrParam) {

		
		return 0;
	}

}
