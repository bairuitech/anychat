
//视频参数界面下拉框
var code_rate_txt = ["质量模式", "40Kbps", "60Kbps", "100Kbps", "150Kbps", "200Kbps", "300Kbps", "400Kbps", "500Kbps", "600Kbps", "800Kbps", "1000Kbps", "1200Kbps", "1500Kbps"]; // 码率下拉框
var quality_txt = ["普通视频质量", "中等视频质量", "较好视频质量"]; // 质量下拉框
var resolution_txt = ["176x144", "320x240", "352x288", "640x480", "720x480", "720x576", "800x600", "960x720", "1024x576", "1280x720", "1280x1024", "1920x1080"]; // 分辨率下拉框
var frame_rate_txt = ["5 FPS", "8 FPS", "12 FPS", "15 FPS", "20 FPS", "25 FPS", "30 FPS"]; // 帧率下拉框
var preinstall_txt = ["1", "2", "3", "4", "5"]; // 预设下拉框
var speakmode_txt = ["发言模式(默认)", "放歌模式", "卡拉OK模式", "线路输入模式"]; // 音频模式下拉框
var videoshow_clipmode_txt = ["默认模式", "重叠模式", "缩小模式", "平铺模式","动态模式"]; // 视频显示裁剪模式下拉框

var bitrate_combo_value = [0, 40000, 60000, 100000, 150000, 200000, 300000, 400000, 500000, 600000, 800000, 1000000, 1200000, 1500000]; // 码率值
var quality_combo_value= [2, 3, 4]; // 质量因子值
var framerate_combo_value= [5, 8, 12, 15 , 20 , 25 , 30 ]; // 帧率值
var videopreset_combo_value= [1, 2, 3, 4, 5]; // 预设参数值
var speakmode_combo_value= [0, 1, 2, 3]; // 音频模式值
var videoshow_clipmode_value= [0, 1, 2, 3,4]; // 视频显示裁剪模式值

var mVideoWidthValue = 320;
var mVideoHeightValue = 240;
var mBitRateValue = 90000;
var mFrameRateValue = 12;
var mVideoQualityValue = 3;
var mVideoPresetValue = 3;



//填充下拉框值
function filltheselect(id, txtArray,valueArray) {
    GetID(id).options.length = 0;
    for (var j = 0; j < txtArray.length; j++) {
        var option = document.createElement("option");
        GetID(id).appendChild(option);
        option.value = valueArray[j];
        option.text = txtArray[j];
    }
}
// 初始化高级设置界面所有控件 进行赋值
function InitAdvanced() {
    filltheselect("code_rate", code_rate_txt,bitrate_combo_value); 			// 填充码率下拉框
    filltheselect("quality", quality_txt,quality_combo_value); 				// 填充质量下拉框
    filltheselect("distinguishability", resolution_txt,resolution_txt); 	// 填充分辨率下拉框
    filltheselect("frame_rate", frame_rate_txt,framerate_combo_value); 		// 填充帧率下拉框
    filltheselect("preinstall", preinstall_txt,videopreset_combo_value); 	// 填充预设下拉框
    filltheselect("Speak_Mode", speakmode_txt,speakmode_combo_value); 		// 发言模式下拉框
    filltheselect("DeviceType_VideoCapture", BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE), BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE)); 		// 视频采集设备下拉框值
    filltheselect("DeviceType_AudioCapture", BRAC_EnumDevices(BRAC_DEVICE_AUDIOCAPTURE),BRAC_EnumDevices(BRAC_DEVICE_AUDIOCAPTURE)); 		// 音频采集设备下拉框值
    filltheselect("DeviceType_AudioPlayBack", BRAC_EnumDevices(BRAC_DEVICE_AUDIOPLAYBACK), BRAC_EnumDevices(BRAC_DEVICE_AUDIOPLAYBACK)); 	// 音频播放设备下拉框值
	filltheselect("videoshow_clipmode", videoshow_clipmode_txt, videoshow_clipmode_value);		// 视频显示裁剪模式下拉框值
    SetThePos();
    initControlSelected();
}

// 音视频设备 按钮划入效果
function selectSettingMenu(id, dd) {
    // 隐藏所有参数界面
    GetID("Device_Interface").style.display = "none";
    GetID("Video_Parameter_Interface").style.display = "none";
    GetID("Sound_Parameter_Interface").style.display = "none";
    GetID("Other_Parameter_Interface").style.display = "none";
    // 获得四个按钮  重新初始化
    var btn = GetID("advanceset_div_Div_Btn").getElementsByTagName("div");
    for (var i = 0; i < btn.length; i++) {
        btn[i].style.backgroundColor = "#9CAAC1"; 		// 设置按钮颜色
        btn[i].setAttribute("clickstate", "false"); 	// 设置按钮点击状态为未点击
    }
    GetID(dd).setAttribute("clickstate", "true"); 		// 设置被点击的按钮状态为被点击
    GetID(dd).style.backgroundColor = "White"; 			// 设置按钮背景色
    GetID(id).style.display = "block"; 					// 显示按钮对应的参数界面
}

// 下拉框事件
function GetTheValue(id) {
    var value = GetID(id).options[GetID(id).selectedIndex].value;
    switch (id) {
        case "DeviceType_VideoCapture": // 视频采集设备
            //BRAC_SelectVideoCapture(BRAC_DEVICE_VIDEOCAPTURE, value);
			//alert(value);
			mVideoCaptureDevice = value;
			initControlSelected();
            break;
        case "DeviceType_AudioCapture": // 音频采集设备
            BRAC_SelectVideoCapture(BRAC_DEVICE_AUDIOCAPTURE, value);
            break;
        case "DeviceType_AudioPlayBack":// 音频播放设备
            BRAC_SelectVideoCapture(BRAC_DEVICE_AUDIOPLAYBACK, value);
            break;
        case "quality": 				// 质量
			mVideoQualityValue= parseInt(value);
            break;
        case "code_rate": 				// 码率
		    mBitRateValue=parseInt(value);
            break;
        case "distinguishability": 		// 分辨率
            var resolution = value.split('x');
			mVideoWidthValue = parseInt(resolution[0]);
			mVideoHeightValue = parseInt(resolution[1]);
			break;
        case "frame_rate": 				// 帧率
			mFrameRateValue=parseInt(value);
            break;
        case "preinstall": 				// 预设
			mVideoPresetValue=parseInt(value);
            break;
        case "Speak_Mode": 				// 音频播放模式
            BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, parseInt(value));
            break;
		case "videoshow_clipmode":		//视频显示裁剪模式
			BRAC_SetSDKOption(BRAC_SO_VIDEOSHOW_CLIPMODE, parseInt(value));
			break;
    }
}
//  复选框事件
function ChangeTheResult(id) {
    switch (id) {
        case "ServerSetting": // 服务器配置参数按钮
            var GetAControl = GetID("advanceset_div_Tab").getElementsByTagName("a");
            var SelectTag = GetID("Video_Parameter_Interface").getElementsByTagName("select"); // 取得 音频参数设置 界面 所有select标签
            if (GetID("ServerSetting").checked == true) { // 标签点击事件
                for (var i = 0; i < SelectTag.length; i++) { // 循环标签
                    SelectTag[i].disabled = "disabled";
                }
                for (var j = 0; j < GetAControl.length; j++)
                    GetAControl[j].style.color = "#999999";
            }
            else {
                for (var i = 0; i < SelectTag.length; i++) 
                        SelectTag[i].disabled = "";
                for (var j = 0; j < GetAControl.length; j++)
                        GetAControl[j].style.color = "Black";
            }
            break;
			
			
			
		case "ScreenCtrl":
			if (GetID(id).checked == true)
				BRAC_SetSDKOption(BRAC_SO_CORESDK_SCREENCAMERACTRL, 1);
			else 
				BRAC_SetSDKOption(BRAC_SO_CORESDK_SCREENCAMERACTRL, 0);
			break;
			
        case "Checkbox_P2P":
            if (GetID(id).checked == true)
				BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC, 1);
            else 
				BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC, 0);
            break;
        case "audio_vadctrl": // 静音检测
            if (GetID(id).checked == true)
				BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL, 1);
            else 
				BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL, 0);
            break;
        case "audio_echoctrl": // 回音消除
            if (GetID(id).checked == true)
				BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, 1);
            else 
				BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, 0);
            break;
        case "audio_nsctrl": // 噪音抑制
            if (GetID(id).checked == true)
			 	BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL, 1);
            else 
				BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL, 0);
            break;
        case "audio_agcctrl": // 自动增益
            if (GetID(id).checked == true)
				 BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, 1);
            else
				 BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, 0);
            break;
    }
}

// 获取当前参数值
function initControlSelected() {
    GetIndex("DeviceType_VideoCapture", BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE),mVideoCaptureDevice,"combobox"); // 当前使用的视频采集器
    GetIndex("DeviceType_AudioCapture", BRAC_EnumDevices(BRAC_DEVICE_AUDIOCAPTURE),BRAC_GetCurrentDevice(BRAC_DEVICE_AUDIOCAPTURE),"combobox"); // 当前使用的音频采集器
	GetIndex("DeviceType_AudioPlayBack", BRAC_EnumDevices(BRAC_DEVICE_AUDIOPLAYBACK),BRAC_GetCurrentDevice(BRAC_DEVICE_AUDIOPLAYBACK),"combobox"); // 当前使用的音频播放器
	
	var devices = BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE);
	
	for(var i=0;i<BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE).length;i++)
	{
		//alert(mVideoCaptureDevice);
		if(devices[i] == mVideoCaptureDevice)
		{
			GetIndex("code_rate",bitrate_combo_value ,BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOBITRATE),"combobox"); // 当前使用的码率参数
			GetIndex("distinguishability",resolution_txt, BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOWIDTH) + "x" + 			BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOHEIGHT), "combobox"); // 当前使用的的分辨率
			GetIndex("frame_rate",framerate_combo_value, BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOFPS), "combobox"); // 当前使用的的帧率参数
			//alert("码率："+BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOBITRATE)+";分辨率："+BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOWIDTH)+"*"+BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOHEIGHT)+";帧率："+BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOFPS));
			GetID("current_resolution").innerHTML = BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOWIDTH) + "x" + BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOHEIGHT) + ")";
		}
	}
	GetIndex("preinstall", videopreset_combo_value,BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_PRESETCTRL), "combobox"); // 当前使用的预设参数
	GetIndex("quality", quality_combo_value,BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_BITRATECTRL),"combobox"); // 当前使用的质量参数
    GetIndex("Speak_Mode",speakmode_combo_value, BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_CAPTUREMODE), "combobox"); // 当前使用的音频播放模式
	GetIndex("videoshow_clipmode",videoshow_clipmode_value, BRAC_GetSDKOptionInt(BRAC_SO_VIDEOSHOW_CLIPMODE), "combobox"); // 当前使用的视频显示裁剪模式
	
    GetIndex("audio_vadctrl", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_VADCTRL), "checkbox");// 当前使用的静音检测
    GetIndex("audio_echoctrl", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_ECHOCTRL), "checkbox"); // 当前使用的回音消除
    GetIndex("audio_nsctrl", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_NSCTRL), "checkbox"); // 当前使用的噪音抑制
    GetIndex("audio_agcctrl", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_AGCCTRL), "checkbox"); // 当前使用的自动增益
    GetIndex("Checkbox_P2P", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_VADCTRL), "checkbox") ;// P2P
    
}


// 设置控件初始值
function GetIndex(control_id,valueArray,value,type) {
    if (type == "combobox") { // 下拉框
		var valueIndex=0;
		for(var i=0;i<valueArray.length;i++)
		{
			if(value==valueArray[i])
			{
				valueIndex=i;
				break;
			}
		}
		GetID(control_id).selectedIndex=valueIndex;
    }
    else { // 复选框
        if (value == 1) // 1为打开 
            GetID(control_id).checked = true;
        else
            GetID(control_id).checked = false;
    }
}

// 设置 高级设置界面 x坐标
function SetThePos() {
    var TheBodyWidth = document.body.offsetWidth;
    GetID("advanceset_div").style.marginLeft = (TheBodyWidth - 464) / 2 + 87 + "px";
}
// 显示 画面调节  界面
function BtnAdjust() {
    BRAC_ShowLVProperty("");
}
// 应用设置
function BtnApply() {
	
	var devices = BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE);
	//alert(mVideoCaptureDevice);
	for(var i=0;i<BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE).length;i++)
	{
		//alert(BRAC_GetCurrentDevice(BRAC_DEVICE_VIDEOCAPTURE)+"   device  "+ );
		if(devices[i] == mVideoCaptureDevice)
		{
			
			//alert(i);
			BRAC_SetUserStreamInfo(-1,i,BRAC_SO_LOCALVIDEO_BITRATECTRL,mBitRateValue);
			BRAC_SetUserStreamInfo(-1,i,BRAC_SO_LOCALVIDEO_WIDTHCTRL,mVideoWidthValue);
			BRAC_SetUserStreamInfo(-1,i,BRAC_SO_LOCALVIDEO_HEIGHTCTRL,mVideoHeightValue);
			BRAC_SetUserStreamInfo(-1,i,BRAC_SO_LOCALVIDEO_FPSCTRL,mFrameRateValue);
			BRAC_SetUserStreamInfo(-1,i,BRAC_SO_LOCALVIDEO_APPLYPARAM,1);
		}
	}
	
	
	// 设置本地视频编码的码率（如果码率为0，则表示使用质量优先模式）
	//BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL,mBitRateValue);
	//BRAC_SetUserStreamInfo(-1,);
	// 设置本地视频编码的质量
	//BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL,mVideoQualityValue);
	// 设置本地视频采集分辨率
	//BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_WIDTHCTRL, mVideoWidthValue);
    //BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, mVideoHeightValue);
	// 设置本地视频编码的帧率
	//BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL,mFrameRateValue);
	// 设置本地视频编码的关键帧间隔
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_GOPCTRL, mFrameRateValue*4);
	// 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL,mVideoPresetValue);
	// 让视频参数生效
    BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM, 1);
    setTimeout(initControlSelected, 500);
}