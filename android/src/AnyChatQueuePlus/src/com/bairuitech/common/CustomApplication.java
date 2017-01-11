package com.bairuitech.common;

import android.app.Application;

public class CustomApplication extends Application{
	private int mUserID;				//本地用户Id
	private int userType;				//用户类型：普通客户、座席两种
	private int CurrentAreaId;			//当前营业厅的Id
	private int CurrentQueueId;			//当前队列Id
	private String selfUserName;		//本地用户名字
	private String targetUserName;		//对方用户名字
	private int RoomId;					//进入房间号
	private  int TargetUserId;			//对方用户Id
    private String ReceivedTips;		//呼叫请求提示

	public void onCreate() {
		super.onCreate();
	}
	
	public void setUserID(int sUserID)
	{
		mUserID = sUserID;
	}
	
	public int getUserID()
	{
		return mUserID;
	}
	

	public int getUserType() {
		return userType;
	}

	public void setUserType(int userType) {
		this.userType = userType;
	}

	public int getCurrentAreaId() {
		return CurrentAreaId;
	}

	public void setCurrentAreaId(int currentAreaId) {
		CurrentAreaId = currentAreaId;
	}

	public int getCurrentQueueId() {
		return CurrentQueueId;
	}

	public void setCurrentQueueId(int currentQueueId) {
		CurrentQueueId = currentQueueId;
	}

	public String getSelfUserName() {
		return selfUserName;
	}

	public void setSelfUserName(String selfUserName) {
		this.selfUserName = selfUserName;
	}

	public int getRoomId() {
		return RoomId;
	}

	public void setRoomId(int roomId) {
		RoomId = roomId;
	}

	public int getTargetUserId() {
		return TargetUserId;
	}

	public void setTargetUserId(int targetUserId) {
		TargetUserId = targetUserId;
	}

	public String getTargetUserName() {
		return targetUserName;
	}

	public void setTargetUserName(String targetUserName) {
		this.targetUserName = targetUserName;
	}

    public String getReceivedTips() {
        return ReceivedTips;
    }

    public void setReceivedTips(String receivedTips) {
        this.ReceivedTips = receivedTips;
    }

}
