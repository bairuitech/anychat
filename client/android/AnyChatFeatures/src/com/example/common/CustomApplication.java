package com.example.common;

import android.app.Application;

public class CustomApplication extends Application{
	private int mUserID;
	private int mCurOpenFuncUIIndex;

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
	
	public void setCurOpenFuncUI(int index)
	{
		mCurOpenFuncUIIndex = index;
	}
	
	public int getCurOpenFuncUI()
	{
		return mCurOpenFuncUIIndex;
	}
}
