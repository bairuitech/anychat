package com.bairuitech.bussinesscenter;

/**
 * 
 * @author liaobin
 * @version 1.0
 * @date 2013-12-30
 *
 */
public class SessionItem  {

	public int sourceUserId;		// 通话发起者userid
	public int targetUserId;		// 通话目标userid
	public int roomId;				// 通话房间Id
	public int sessionStatus;		// 通话状态
	public int sessionType;			// 通话类型
	public SessionItem(int sessionType,int sUserId,int tUserId)
	{
		this.sessionType=sessionType;
		this.sourceUserId=sUserId;
		this.targetUserId=tUserId;
	}
	public int getSourceUserId() {
		return sourceUserId;
	}
	public void setSourceUserId(int sourceUserId) {
		this.sourceUserId = sourceUserId;
	}
	public int getTargetUserId() {
		return targetUserId;
	}
	public void setTargetUserId(int targetUserId) {
		this.targetUserId = targetUserId;
	}
	public int getRoomId() {
		return roomId;
	}
	public void setRoomId(int roomId) {
		this.roomId = roomId;
	}
	public int getSessionStatus() {
		return sessionStatus;
	}
	public void setSessionStatus(int sessionStatus) {
		this.sessionStatus = sessionStatus;
	}
	public int getSessionType() {
		return sessionType;
	}
	public void setSessionType(int sessionType) {
		this.sessionType = sessionType;
	}
	
	/***
	 * 获取通话中另外一方的UserId
	 * @param selfUserId 自己的用户Id
	 * @return 通话中另外一方的UserId
	 */
	public int getPeerUserItem(int selfUserId)
	{
		if(sourceUserId==selfUserId)
		{
			return targetUserId;
		}
		else if(targetUserId==selfUserId)
		{
			return sourceUserId;
		}
		return 0;
		
	}
	

}
