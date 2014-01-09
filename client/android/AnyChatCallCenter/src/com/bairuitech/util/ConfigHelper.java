package com.bairuitech.util;

import com.bairuitech.anychat.AnyChatCoreSDK;
import com.bairuitech.anychat.AnyChatDefine;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class ConfigHelper {
	private static ConfigHelper configHelper = new ConfigHelper();

	private ConfigHelper() {

	}

	public ConfigEntity LoadConfig(Context context) {
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
        configEntity.videoBitrate = share.getInt("videoBitrate", 150*1000);
        configEntity.videoFps = share.getInt("videoFps", 10);
        configEntity.videoQuality = share.getInt("videoQuality", ConfigEntity.VIDEO_QUALITY_GOOD);
        configEntity.videoPreset = share.getInt("videoPreset", 3);
        configEntity.videoOverlay = share.getInt("videoOverlay", 1);
        configEntity.videorotatemode = share.getInt("VideoRotateMode", 0);
        configEntity.videoCapDriver = share.getInt("VideoCapDriver", AnyChatDefine.VIDEOCAP_DRIVER_JAVA);
        configEntity.fixcolordeviation = share.getInt("FixColorDeviation", 0);
        configEntity.videoShowGPURender = share.getInt("videoShowGPURender", 0);
        configEntity.videoAutoRotation = share.getInt("videoAutoRotation", 1);

        configEntity.enableP2P = share.getInt("enableP2P", 1);
        configEntity.useARMv6Lib = share.getInt("useARMv6Lib", 0);
        configEntity.enableAEC = share.getInt("enableAEC", 1);
        configEntity.useHWCodec = share.getInt("useHWCodec", 0);
        configEntity.videoShowDriver = share.getInt("videoShowDriver", AnyChatDefine.VIDEOSHOW_DRIVER_JAVA);
        configEntity.audioPlayDriver = share.getInt("audioPlayDriver", AnyChatDefine.AUDIOPLAY_DRIVER_JAVA);   
        configEntity.audioRecordDriver = share.getInt("audioRecordDriver", AnyChatDefine.AUDIOREC_DRIVER_JAVA);
		return configEntity;
	}

	public void SaveConfig(Context context, ConfigEntity configEntity) {
		SharedPreferences  share = context.getSharedPreferences("perference",  Context.MODE_WORLD_WRITEABLE);  
        Editor editor = share.edit();//取得编辑器
        
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
        editor.putInt("videoAutoRotation", configEntity.videoAutoRotation);
        
        editor.putInt("enableP2P", configEntity.enableP2P);
        editor.putInt("useARMv6Lib", configEntity.useARMv6Lib);
        editor.putInt("enableAEC", configEntity.enableAEC);
        editor.putInt("useHWCodec", configEntity.useHWCodec);
        editor.putInt("videoShowDriver", configEntity.videoShowDriver);
        editor.putInt("audioPlayDriver", configEntity.audioPlayDriver); 
        editor.putInt("audioRecordDriver", configEntity.audioRecordDriver);         
    	editor.commit();

	}

	public static ConfigHelper getConfigHelper() {
		return configHelper;
	}


	// 根据配置文件设置视频参数
	public void ApplyVideoConfig(Context context)
	{
		ConfigEntity configEntity = ConfigHelper.getConfigHelper().LoadConfig(context);
		if(configEntity.configMode == 1)		// 自定义视频参数配置
		{
			// 设置本地视频编码的码率（如果码率为0，则表示使用质量优先模式）
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_BITRATECTRL, configEntity.videoBitrate);
			if(configEntity.videoBitrate==0)
			{
				// 设置本地视频编码的质量
				AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_QUALITYCTRL, configEntity.videoQuality);
			}
			// 设置本地视频编码的帧率
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_FPSCTRL, configEntity.videoFps);
			// 设置本地视频编码的关键帧间隔
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_GOPCTRL, configEntity.videoFps*4);
			// 设置本地视频采集分辨率
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_WIDTHCTRL, configEntity.resolution_width);
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_HEIGHTCTRL, configEntity.resolution_height);
			// 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
			AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_PRESETCTRL, configEntity.videoPreset);
		}
		// 让视频参数生效
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_APPLYPARAM, configEntity.configMode);
		// P2P设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_NETWORK_P2PPOLITIC, configEntity.enableP2P);
		// 本地视频Overlay模式设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_OVERLAY, configEntity.videoOverlay);
		// 回音消除设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_ECHOCTRL, configEntity.enableAEC);
		// 平台硬件编码设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_CORESDK_USEHWCODEC, configEntity.useHWCodec);
		// 视频旋转模式设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_ROTATECTRL, configEntity.videorotatemode);
		// 视频采集驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_CAPDRIVER, configEntity.videoCapDriver);
		// 本地视频采集偏色修正设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_FIXCOLORDEVIA, configEntity.fixcolordeviation);
		// 视频显示驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_DRIVERCTRL, configEntity.videoShowDriver);
		// 音频播放驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_PLAYDRVCTRL, configEntity.audioPlayDriver);
		// 音频采集驱动设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_AUDIO_RECORDDRVCTRL, configEntity.audioRecordDriver);
		// 视频GPU渲染设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_VIDEOSHOW_GPUDIRECTRENDER, configEntity.videoShowGPURender);
		// 本地视频自动旋转设置
		AnyChatCoreSDK.SetSDKOptionInt(AnyChatDefine.BRAC_SO_LOCALVIDEO_AUTOROTATION, configEntity.videoAutoRotation);


}
}
