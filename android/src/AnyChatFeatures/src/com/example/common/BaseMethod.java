package com.example.common;

import java.io.File;

import com.example.anychatfeatures.R;

import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.media.SoundPool;
import android.net.Uri;

public class BaseMethod{
	public static final int CALLSOUNDID = 1;
	public static final int PHOTOSSOUNDID = 2;
	public static SoundPool mPhotoSoundPool = null;
	
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
	
	// 播放拍照的声音
	public static void playSound( Context context, int soundIndxe) {		
		if (mPhotoSoundPool == null){
			mPhotoSoundPool = new SoundPool(10, AudioManager.STREAM_MUSIC, 5);
		}
		
		if (soundIndxe == PHOTOSSOUNDID){
			mPhotoSoundPool.load(context, R.raw.photossound, 1);
			mPhotoSoundPool.play(1, 1, 1, 0, 0, 1);
		}
	}
}
