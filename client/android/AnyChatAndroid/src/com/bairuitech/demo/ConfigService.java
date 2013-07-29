package com.bairuitech.demo;

import com.bairuitech.anychat.AnyChatDefine;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class ConfigService {

	public static ConfigEntity LoadConfig(Context context)
	{
		ConfigEntity configEntity = new ConfigEntity();
    	SharedPreferences  share = context.getSharedPreferences("perference", Context.MODE_WORLD_WRITEABLE);  

        configEntity.name = share.getString("name", "");
        configEntity.password = share.getString("password", "");
        configEntity.IsSaveNameAndPw = share.getString("IsSaveNameAndPw", "").equals("1") ? true : false;
      
        configEntity.ip = share.getString("ip", "demo.anychat.cn");
        configEntity.port = share.getInt("port", 8906);
        
        configEntity.configMode = share.getInt("configMode", ConfigEntity.VIDEO_MODE_CUSTOMCONFIG);
        configEntity.resolution_width = share.getInt("resolution_width", 320);
        configEntity.resolution_height = share.getInt("resolution_height", 240);
        configEntity.videoBitrate = share.getInt("videoBitrate", 0);
        configEntity.videoFps = share.getInt("videoFps", 10);
        configEntity.videoQuality = share.getInt("videoQuality", ConfigEntity.VIDEO_QUALITY_GOOD);
        configEntity.videoPreset = share.getInt("videoPreset", 3);
        configEntity.videoOverlay = share.getInt("videoOverlay", 1);
        configEntity.videorotatemode = share.getInt("VideoRotateMode", 0);
        configEntity.videoCapDriver = share.getInt("VideoCapDriver", AnyChatDefine.VIDEOCAP_DRIVER_JAVA);
        configEntity.fixcolordeviation = share.getInt("FixColorDeviation", 0);
        configEntity.videoShowGPURender = share.getInt("videoShowGPURender", 0);

        configEntity.enableP2P = share.getInt("enableP2P", 1);
        configEntity.useARMv6Lib = share.getInt("useARMv6Lib", 0);
        configEntity.enableAEC = share.getInt("enableAEC", 1);
        configEntity.useHWCodec = share.getInt("useHWCodec", 0);
        configEntity.smoothPlayMode = share.getInt("smoothPlayMode", 0);
        configEntity.videoShowDriver = share.getInt("videoShowDriver", AnyChatDefine.VIDEOSHOW_DRIVER_JAVA);
        configEntity.audioPlayDriver = share.getInt("audioPlayDriver", AnyChatDefine.AUDIOPLAY_DRIVER_JAVA);   
        configEntity.audioRecordDriver = share.getInt("audioRecordDriver", AnyChatDefine.AUDIOREC_DRIVER_JAVA);
		return configEntity;
	}
	
	public static void SaveConfig(Context context,ConfigEntity configEntity)
	{
    	SharedPreferences  share = context.getSharedPreferences("perference",  Context.MODE_WORLD_WRITEABLE);  
        Editor editor = share.edit();//È¡µÃ±à¼­Æ÷
        
        editor.putString("name", configEntity.name);
        editor.putString("password", configEntity.password);
        editor.putString("IsSaveNameAndPw", configEntity.IsSaveNameAndPw ? "1" : "0");
        
        editor.putString("ip", configEntity.ip);
        editor.putInt("port", configEntity.port);
        
        editor.putInt("configMode", configEntity.configMode);
        editor.putInt("resolution_width", configEntity.resolution_width);
        editor.putInt("resolution_height", configEntity.resolution_height);

        editor.putInt("videoBitrate", configEntity.videoBitrate);
        editor.putInt("videoFps", configEntity.videoFps);
        editor.putInt("videoQuality", configEntity.videoQuality);
        editor.putInt("videoPreset", configEntity.videoPreset);
        editor.putInt("videoOverlay", configEntity.videoOverlay);
        editor.putInt("VideoRotateMode", configEntity.videorotatemode);
        editor.putInt("VideoCapDriver", configEntity.videoCapDriver);
        editor.putInt("FixColorDeviation", configEntity.fixcolordeviation);
        editor.putInt("videoShowGPURender", configEntity.videoShowGPURender);
        
        editor.putInt("enableP2P", configEntity.enableP2P);
        editor.putInt("useARMv6Lib", configEntity.useARMv6Lib);
        editor.putInt("enableAEC", configEntity.enableAEC);
        editor.putInt("useHWCodec", configEntity.useHWCodec);
        editor.putInt("smoothPlayMode", configEntity.smoothPlayMode);
        editor.putInt("videoShowDriver", configEntity.videoShowDriver);
        editor.putInt("audioPlayDriver", configEntity.audioPlayDriver); 
        editor.putInt("audioRecordDriver", configEntity.audioRecordDriver);         
    	editor.commit();
		
	}
	
}
