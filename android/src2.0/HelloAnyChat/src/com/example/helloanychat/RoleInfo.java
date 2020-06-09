package com.example.helloanychat;

public class RoleInfo {
	private String mStrName;
	private String mStrUserID;
	private int mRoleIconID;
	private boolean isMySelf;

	public boolean isMySelf() {
		return isMySelf;
	}

	public void setMySelf(boolean mySelf) {
		isMySelf = mySelf;
	}

	public void setName(String strName) {
		mStrName = strName;
	}

	public String getName() {
		return mStrName;
	}

	public void setUserID(String strUserID) {
		mStrUserID = strUserID;
	}

	public String getUserID() {
		return mStrUserID;
	}
	
	public void setRoleIconID(int iconID) {
		mRoleIconID = iconID;
	}

	public int getRoleIconID() {
		return mRoleIconID;
	}
}
