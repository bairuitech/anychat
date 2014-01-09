package com.bairuitech.bussinesscenter;

import java.io.Serializable;

import android.util.Log;

public class UserItem implements Serializable,Cloneable{

	private String mStrName;
	private String mStrIp;
	private int mUserId;
	private int mUserIdenty;
	private int mGroupId;
	private static final long serialVersionUID=8502706820090766507L;
	public static final int USERSTATUS_OFFLINE=0;
	public static final int USERSTATUS_ONLINE=1;
	public static final int USERINFO_NAME=1;
	public static final int USERINFO_IP=2;
	public UserItem(int mUserId,String strName,String strIp)
	{
		this.mStrName=strName;
		this.mUserId=mUserId;
		this.mStrIp=strIp;
	}
	public UserItem()
	{
		mStrName="";
	}
	public void setUserId(int pUserid)
	{
		mUserId=pUserid;
	}
	public void setUserIenty(int pIndety)
	{
		mUserIdenty=pIndety;
	}
	public void setUserName(String pUserName)
	{
		mStrName=pUserName;
	}
	public void setIp(String ip)
	{
		mStrIp=ip;
	}
	public String getIp()
	{
		return mStrIp;
	}
	public int getUserId()
	{
		return mUserId;
	}
	public int getUserIdenty()
	{
		return mUserIdenty;
	}
	public String getUserName()
	{
		return mStrName;
	}
	public void setGroupId(int dwGroupId)
	{
		mGroupId=dwGroupId;
	}
	public int getGroupId()
	{
		return mGroupId;
	}
	public UserItem clone()
	{
		UserItem item=null;
		try
		{
			item=(UserItem) super.clone();
		}
		catch(Exception e)
		{
			Log.i("useritem-clone", e.toString());
		}
		return item;
	}
}
