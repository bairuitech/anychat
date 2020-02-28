package com.bairuitech.common;

public class ConfigEntity {
	public static final int VIDEO_MODE_SERVERCONFIG = 0;	// 服务器视频参数配置
	public static final int VIDEO_MODE_CUSTOMCONFIG = 1;	// 自定义视频参数配置
	
	public static final int VIDEO_QUALITY_NORMAL = 2;		// 普通视频质量
	public static final int VIDEO_QUALITY_GOOD = 3;			// 中等视频质量
	public static final int VIDEO_QUALITY_BEST = 4;			// 较好视频质量
	
	public boolean IsSaveNameAndPw;							//是否保存用户名和密码
	public String name = "Tom";							//登陆用户名，默认为name
	public String password = "";

	public String ip = "demo.anychat.cn";					//登陆服务器地址，默认佰锐公司服务器地址
	public int port = 8906;									//端口默认8906
	
	
	public int configMode = VIDEO_MODE_SERVERCONFIG;		
	public int resolution_width = 0;
	public int resolution_height = 0;
	
	public int videoBitrate = 150*1000;						// 本地视频码率
	public int videoFps = 10;								// 本地视频帧率
	public int videoQuality = VIDEO_QUALITY_GOOD;			//视频质量
	public int videoPreset = 1;
	public int videoOverlay = 1;							// 本地视频是否采用Overlay模式
	public int videorotatemode = 0;							// 本地视频旋转模式
	public int fixcolordeviation = 0;						// 修正本地视频采集偏色：0 关闭(默认）， 1 开启
	public int videoShowGPURender = 0;						// 视频数据通过GPU直接渲染：0  关闭(默认)， 1 开启
	public int videoAutoRotation = 1;						// 本地视频自动旋转控制（参数为int型， 0表示关闭， 1 开启[默认]，视频旋转时需要参考本地视频设备方向参数）
	
	public int enableP2P = 1;
	public int useARMv6Lib = 0;								// 是否强制使用ARMv6指令集，默认是内核自动判断
	public int enableAEC = 1;								// 是否使用回音消除功能
	public int useHWCodec = 0;								// 是否使用平台内置硬件编解码器
}
