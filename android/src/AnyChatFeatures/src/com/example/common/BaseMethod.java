package com.example.common;

import java.io.File;

import android.content.Intent;
import android.net.Uri;

public class BaseMethod{
	public static String getTimeShowStr(int seconds){
		String strShow=new String();
		int hour = seconds / (60*60);
		int min = (seconds/60) % 60;
		int s = seconds % 60;
		String hourStr = (hour >= 10) ? "" + hour : "0" + hour;
		String minStr = (min >= 10) ? "" + min : "0" + min;
		String seondStr = (s >= 10) ? "" + s : "0" + s;
		strShow = hourStr + ":" + minStr + ":" + seondStr;
		return strShow;		
	}
	
	public static Intent getIntent(String filePath, String fileType){
		 Intent intent = new Intent("android.intent.action.VIEW");
	     intent.addCategory("android.intent.category.DEFAULT");
	     intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
	     Uri uri = Uri.fromFile(new File(filePath ));
	     intent.setDataAndType(uri, fileType);
	     return intent;
	}
}
