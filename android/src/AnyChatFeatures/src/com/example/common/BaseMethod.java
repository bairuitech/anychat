package com.example.common;

import java.io.File;

import com.example.anychatfeatures.R;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.AudioManager;
import android.media.SoundPool;
import android.media.ThumbnailUtils;
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
	
	public static Bitmap getImageThumbnail(String imagePath, int width, int height) {  
        Bitmap bitmap = null;  
        BitmapFactory.Options options = new BitmapFactory.Options();  
        options.inJustDecodeBounds = true;  
        // 获取这个图片的宽和高，注意此处的bitmap为null  
        bitmap = BitmapFactory.decodeFile(imagePath, options);  
        options.inJustDecodeBounds = false; // 设为 false  
        // 计算缩放比  
        int h = options.outHeight;  
        int w = options.outWidth;  
        int beWidth = w / width;  
        int beHeight = h / height;  
        int be = 1;  
        if (beWidth < beHeight) {  
            be = beWidth;  
        } else {  
            be = beHeight;  
        }  
        if (be <= 0) {  
            be = 1;  
        }  
        options.inSampleSize = be;  
        // 重新读入图片，读取缩放后的bitmap，注意这次要把options.inJustDecodeBounds 设为 false  
        bitmap = BitmapFactory.decodeFile(imagePath, options);  
        // 利用ThumbnailUtils来创建缩略图，这里要指定要缩放哪个Bitmap对象  
        bitmap = ThumbnailUtils.extractThumbnail(bitmap, width, height,  
                ThumbnailUtils.OPTIONS_RECYCLE_INPUT);  
        return bitmap;  
    }  
	
	public static Bitmap getVideoThumbnail(String videoPath, int width, int height,  
	            int kind) {  
	        Bitmap bitmap = null;  
	        // 获取视频的缩略图  
	        bitmap = ThumbnailUtils.createVideoThumbnail(videoPath, kind);  
	        System.out.println("w"+bitmap.getWidth());  
	        System.out.println("h"+bitmap.getHeight());  
	        bitmap = ThumbnailUtils.extractThumbnail(bitmap, width, height,  
	                ThumbnailUtils.OPTIONS_RECYCLE_INPUT);  
	        return bitmap;  
	}  
}
