package com.example.helloanychat;

public class ConfigEntity {
	public static final int showLoginFlag = 1;  //显示的按钮是登陆状态的标识
	public static final int showWaitingFlag =2; //显示的按钮是等待状态的标识
	public static final int showLogoutFlag = 3; //显示的按钮是登出状态的标识
	
	
	public int videoCapDriver = 3;	 	// 本地视频采集驱动（0 默认， 1 Linux驱动，3 Java驱动
	public int videoShowDriver = 5;	 	// 视频显示驱动（0 默认， 4 Android 2.x兼容模式，5 Java驱动）
	public int audioPlayDriver = 3;	 	// 音频播放驱动（0 默认，3 Java驱动）
	public int audioRecordDriver = 3;	// 音频采集驱动（0默认，3 Java驱动）
	
}
