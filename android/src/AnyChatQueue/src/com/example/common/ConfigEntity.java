package com.example.common;

public class ConfigEntity {
	public static final int VIDEO_MODE_SERVERCONFIG = 0;	// 鏈嶅姟鍣ㄨ棰戝弬鏁伴厤缃�
	public static final int VIDEO_MODE_CUSTOMCONFIG = 1;	// 鑷畾涔夎棰戝弬鏁伴厤缃�
	
	public static final int VIDEO_QUALITY_NORMAL = 2;		// 鏅�氳棰戣川閲�
	public static final int VIDEO_QUALITY_GOOD = 3;			// 涓瓑瑙嗛璐ㄩ�?
	public static final int VIDEO_QUALITY_BEST = 4;			// 杈冨ソ瑙嗛璐ㄩ�?
	
	public boolean IsSaveNameAndPw;
	public String name = "yuanyukun";
	public String password = "";

	public String ip = "demo.anychat.cn";
	public int port = 8906;
	
	//排队对象Id保存；
	public int CurrentObjectId = 0;
	public int CurrentQueueId = 0;
	
	public int configMode = VIDEO_MODE_SERVERCONFIG;
	public int resolution_width = 0;
	public int resolution_height = 0;
	
	public int videoBitrate = 150*1000;						// 鏈湴瑙嗛鐮佺�?
	public int videoFps = 10;								// 鏈湴瑙嗛甯х巼
	public int videoQuality = VIDEO_QUALITY_GOOD;
	public int videoPreset = 1;
	public int videoOverlay = 1;							// 鏈湴瑙嗛鏄惁閲囩敤Overlay妯�?�紡
	public int videorotatemode = 0;							// 鏈湴瑙嗛鏃嬭浆妯″紡
	public int fixcolordeviation = 0;						// 淇鏈�?湴瑙嗛閲囬泦鍋忚壊锛�0 鍏抽�?(榛樿锛夛紝 1 寮�鍚�
	public int videoShowGPURender = 0;						// 瑙嗛鏁版嵁閫氳繃GPU鐩存帴娓叉煋锛�0  鍏抽�?(榛樿�?)锛� 1 寮�鍚�
	public int videoAutoRotation = 1;						// 鏈湴瑙嗛鑷姩鏃嬭浆鎺у埗锛堝弬鏁颁负int鍨嬶�? 0琛ㄧず鍏抽棴锛� 1 寮�鍚痆榛樿]锛岃棰戞棆杞椂闇�瑕佸弬鑰冩湰鍦拌棰戣澶囨柟鍚戝弬鏁帮級
	
	public int enableP2P = 1;
	public int useARMv6Lib = 0;								// 鏄惁寮哄埗浣跨敤ARMv6鎸囦护闆嗭紝榛樿鏄唴鏍歌嚜鍔ㄥ垽鏂�
	public int enableAEC = 1;								// 鏄惁浣跨敤鍥為煶娑堥櫎鍔熻�?
	public int useHWCodec = 0;								// 鏄惁浣跨敤骞冲彴鍐呯疆纭欢缂栬В鐮佸櫒
}
