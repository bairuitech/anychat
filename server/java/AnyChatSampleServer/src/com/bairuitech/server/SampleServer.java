package com.bairuitech.server;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.ArrayList;
import java.util.Iterator;

import com.bairuitech.anychat.*;

public class SampleServer implements AnyChatServerEvent{

	public static AnyChatServerSDK anychat;
	public static int iUserIdSeed = 1;
	public static boolean bShowActionLog = true;			// 是否显示用户活动日志信息
	
	// 队列业务类型
	public static final int QUEUE_ABILITY_TYPE_PERSONAL		=	1;		///< 个人业务
	public static final int QUEUE_ABILITY_TYPE_COMPANY		=	2;		///< 对公业务
	
	/**
	 * @param args
	 * @throws InterruptedException 
	 * @throws IOException 
	 */
	public static void main(String[] args) throws InterruptedException, IOException {
		anychat = new AnyChatServerSDK();
		anychat.SetServerEvent(new SampleServer());
		anychat.InitSDK(0);
		anychat.RegisterVerifyUserClass(new AnyChatVerifyUserOutParam());
		
		// 初始化业务队列
		InitBusinessQueue();
				
		System.out.print(getCurrentTime() + "Welcome use AnyChat! (" + anychat.GetSDKVersion() + ")\r\n");
		Reader reader = new InputStreamReader(System.in);
		char ch = 0;
		do{
			if(ch == 'd')
				bShowActionLog = !bShowActionLog;
			else if(ch != '\r') {
				int[] onlineusers = AnyChatServerSDK.GetOnlineUsers(-1);		// 获取系统所有在线用户列表
				System.out.print(getCurrentTime() + "Business server(Java) still running, press 'q' to exit...(Online users: " + onlineusers.length + ")\r\n");
			}
			Thread.sleep(100);
		}while((ch=(char)reader.read()) != 'q');
		anychat.Release();
		System.out.print(getCurrentTime() + "Business server(Java) already exited...\r\n");
	}

	/**
	 * 初始化业务队列
	 */
	private static void InitBusinessQueue() {
		// 服务器端创建一个营业厅对象，并设置属性
		int dwAreaId = 10001;
		AnyChatServerSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, dwAreaId, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_CREATE, 0, 0, 0, 0, "");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, dwAreaId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME, "科韵路营业厅");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, dwAreaId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_DESCRIPTION, "位于广州市科韵路，服务超级棒！");
		
		// 创建队列对象
		int dwQueueId = 101;
		AnyChatServerSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_CREATE, dwAreaId, 0, 0, 0, "");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME, "个人业务队列");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_DESCRIPTION, "开户、挂失、转帐");
		// 设置队列优先级
		int dwPriority = 0;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_PRIORITY, dwPriority);
		// 设置队列业务类型
		int dwQueueAbility = QUEUE_ABILITY_TYPE_PERSONAL;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_ATTRIBUTE, dwQueueAbility);
		// 设置队列整型标签值（上层业务自定义用途）
		int dwQueueIntTag = 2;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_INTTAG, dwQueueIntTag);

		dwQueueId = 102;
		AnyChatServerSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_CREATE, dwAreaId, 0, 0, 0, "");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME, "个人业务队列(VIP)");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_DESCRIPTION, "开户、挂失、转帐");
		// 设置队列优先级
		dwPriority = 10;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_PRIORITY, dwPriority);
		// 设置队列业务类型
		dwQueueAbility = QUEUE_ABILITY_TYPE_PERSONAL;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_ATTRIBUTE, dwQueueAbility);
		// 设置队列整型标签值（上层业务自定义用途）
		dwQueueIntTag = 2;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_INTTAG, dwQueueIntTag);
		
		dwQueueId = 103;
		AnyChatServerSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_CREATE, dwAreaId, 0, 0, 0, "");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME, "对公业务队列");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_DESCRIPTION, "支票、回单、基本户");
		// 设置队列优先级
		dwPriority = 0;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_PRIORITY, dwPriority);
		// 设置队列业务类型
		dwQueueAbility = QUEUE_ABILITY_TYPE_COMPANY;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_ATTRIBUTE, dwQueueAbility);
		// 设置队列整型标签值（上层业务自定义用途）
		dwQueueIntTag = 3;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_INTTAG, dwQueueIntTag);

		
		// 服务器端创建另一个营业厅对象，并设置属性（dwAreaId编号变化）
		dwAreaId = 10002;
		AnyChatServerSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, dwAreaId, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_CREATE, 0, 0, 0, 0, "");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, dwAreaId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME, "天河路营业厅");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_AREA, dwAreaId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_DESCRIPTION, "七星级旗舰店，高端客户首选！");
		
		// 创建队列对象
		dwQueueId = 201;
		AnyChatServerSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_CREATE, dwAreaId, 0, 0, 0, "");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME, "投资理财业务队列");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_DESCRIPTION, "基金、理财产品、贵金属");
		// 设置队列优先级
		dwPriority = 0;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_PRIORITY, dwPriority);
		// 设置队列业务类型
		dwQueueAbility = QUEUE_ABILITY_TYPE_PERSONAL;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_ATTRIBUTE, dwQueueAbility);
		// 设置队列整型标签值（上层业务自定义用途）
		dwQueueIntTag = 2;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_INTTAG, dwQueueIntTag);

		
		dwQueueId = 202;
		AnyChatServerSDK.ObjectControl(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_CTRL_CREATE, dwAreaId, 0, 0, 0, "");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_NAME, "商业贷款业务队列");
		AnyChatServerSDK.ObjectSetStringValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_DESCRIPTION, "房贷、车贷、公积金");
		// 设置队列优先级
		dwPriority = 10;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_PRIORITY, dwPriority);
		// 设置队列业务类型
		dwQueueAbility = QUEUE_ABILITY_TYPE_COMPANY;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_ATTRIBUTE, dwQueueAbility);
		// 设置队列整型标签值（上层业务自定义用途）
		dwQueueIntTag = 3;
		AnyChatServerSDK.ObjectSetIntValue(AnyChatObjectDefine.ANYCHAT_OBJECT_TYPE_QUEUE, dwQueueId, AnyChatObjectDefine.ANYCHAT_OBJECT_INFO_INTTAG, dwQueueIntTag);
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
		if(bShowActionLog)
			System.out.print(getCurrentTime() + "OnVerifyUserCallBack: userid:" + iUserIdSeed + " username: " + szUserName + "\r\n");
		iUserIdSeed += 1;
		return 0;
	}
	
	@Override
	public void OnAnyChatUserLoginActionCallBack(int dwUserId, String szUserName, int dwLevel, String szIpAddr) {
		if(bShowActionLog)
			System.out.print(getCurrentTime() + "OnUserLoginActionCallBack: userid:" + dwUserId + " username: " + szUserName + " ip: " + szIpAddr + "\r\n");
	}
	
	@Override
	public void OnAnyChatUserLogoutActionExCallBack(int dwUserId, int dwErrorCode) {
	    if(bShowActionLog)
			System.out.print(getCurrentTime() + "OnUserLogoutActionExCallBack: userid:" + dwUserId + " errorcode:" + dwErrorCode + "\r\n");
	}

	// 用户准备进入房间验证，如果允许用户进入房间，则必须返回0，则否返回出错代码
	@Override
	public int OnAnyChatPrepareEnterRoomCallBack(int dwUserId, int dwRoomId, String szRoomName, String szPassword) {
		if(bShowActionLog)
			System.out.print(getCurrentTime() + "OnPrepareEnterRoomCallBack: userid:" + dwUserId + " roomid: " + dwRoomId + "\r\n");
		return 0;
	}
	
	@Override
	public void OnAnyChatUserEnterRoomActionCallBack(int dwUserId, int dwRoomId) {
		if(bShowActionLog)
			System.out.print(getCurrentTime() + "OnUserEnterRoomActionCallBack: userid:" + dwUserId + " roomid: " + dwRoomId + "\r\n");
	}

	@Override
	public void OnAnyChatUserLeaveRoomActionCallBack(int dwUserId, int dwRoomId) {
		if(bShowActionLog)
			System.out.print(getCurrentTime() + "OnUserLeaveRoomActionCallBack: userid:" + dwUserId + " roomid: " + dwRoomId + "\r\n");
	}
	
	@Override
	public void OnAnyChatTransFile(int dwUserId, String szFileName, String szTempFilePath, int dwFileLength, int wParam, int lParam, int dwTaskId) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void OnAnyChatTransBuffer(int dwUserId, byte[] lpBuf, int dwLen) {
		// TODO Auto-generated method stub
		if(bShowActionLog)
			System.out.print(getCurrentTime() + "OnAnyChatTransBuffer: userid:" + dwUserId + "len: " + dwLen + " timestamp: " + 
					AnyChatServerSDK.SetSDKOptionInt(AnyChatServerSDK.BRAS_SO_GETTRANSBUFTIMESTAMP, dwUserId) + "\r\n");
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
		if(bShowActionLog)
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
		if(bShowActionLog)
			System.out.print(getCurrentTime() + str + "\r\n");
	}

	/**
	 * 视频呼叫事件回调，客户端调用API：BRAC_VideoCallControl会触发该回调
	 */
	@Override
	public int OnAnyChatVideoCallEventCallBack(int dwEventType, int dwSrcUserId, int dwTarUserId, int dwErrorCode, int dwFlags, int dwParam, String lpUserStr) {
		String str = "OnAnyChatVideoCallEventCallBack: dwEventType:" + dwEventType + " dwSrcUserId:" + dwSrcUserId + 
			" dwTarUserId:" + dwTarUserId + " dwErrorCode:" + dwErrorCode + " dwFlags:" + dwFlags + " dwParam:" + dwParam + " lpUserStr:" + lpUserStr;
		if(bShowActionLog)
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
		if(bShowActionLog)
			System.out.print(getCurrentTime() + str + "\r\n");
		return 0;
	}

	@Override
	public int OnAnyChatObjectEventCallBack(int dwObjectType, int dwObjectId,
			int dwEventType, int dwParam1, int dwParam2, int dwParam3, int dwParam4, String lpStrParam) {

		return 0;
	}

}
