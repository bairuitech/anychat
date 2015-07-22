package com.bairuitech.common;

import android.app.Application;

public class CustomApplication extends Application{
	private int mUserID;
	private int userType;
	private int CurrentAreaId;
	private int CurrentQueueId;
	private String selfUserName;
	private int RoomId;
	private  int TargetUserId;
	@Override
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
}
