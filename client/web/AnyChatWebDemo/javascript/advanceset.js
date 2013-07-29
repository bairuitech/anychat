
//视频参数界面下拉框
var code_rate = ["质量模式", "40", "60", "100", "150", "200", "300", "400", "500", "600", "800", "1000", "1200", "1500"]; // 码率下拉框
var quality = ["较差质量", "一般质量", "中等质量", "较好质量", "最好质量"]; // 质量下拉框
var distinguishability = ["176x144", "320x240", "352x288", "640x480", "720x480", "720x576", "800x600", "960x720", "1024x576", "1280x720", "1280x1024", "1920x1080"]; // 分辨率下拉框
var frame_rate = ["5 FPS", "8 FPS", "12 FPS", "15 FPS", "20 FPS", "25 FPS", "30 FPS"]; // 帧率下拉框
var preinstall = ["1", "2", "3", "4", "5"]; // 预设下拉框
var speakmode = ["发言模式(默认)", "放歌模式", "卡拉OK模式", "线路输入模式"]; // 音频模式下拉框

//填充下拉框值
function filltheselect(id, theArray) {
    GetID(id).options.length = 0;
    for (var j = 0; j < theArray.length; j++) {
        var option = document.createElement("option");
        GetID(id).appendChild(option);
        option.value = j;
        option.text = theArray[j];
    }
}
// 初始化高级设置界面所有控件 进行赋值
function InitAdvanced() {
    filltheselect("code_rate", code_rate); // 填充码率下拉框
    filltheselect("quality", quality); // 填充质量下拉框
    filltheselect("distinguishability", distinguishability); // 填充分辨率下拉框
    filltheselect("frame_rate", frame_rate); // 填充帧率下拉框
    filltheselect("preinstall", preinstall); // 填充预设下拉框
    filltheselect("Speak_Mode", speakmode); // 发言模式下拉框
    filltheselect("DeviceType_VideoCapture", BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE)); // 视频采集设备下拉框值
    filltheselect("DeviceType_AudioCapture", BRAC_EnumDevices(BRAC_DEVICE_AUDIOCAPTURE)); // 音频采集设备下拉框值
    filltheselect("DeviceType_AudioPlayBack", BRAC_EnumDevices(BRAC_DEVICE_AUDIOPLAYBACK)); // 音频播放设备下拉框值
    SetThePos();
    GetCurrentDevice();
}
// 音视频设备 按钮划出效果
function SettingBtnMouseout(id) {
    if (GetID(id).getAttribute("clickstate") == "false") // 没有被点击的按钮改变背景色
        GetID(id).style.backgroundColor = "#9CAAC1";
}
// 音视频设备 按钮划入效果
function SettingBtnMouseover(id, dd) {
    // 隐藏所有参数界面
    GetID("Device_Interface").style.display = "none";
    GetID("Video_Parameter_Interface").style.display = "none";
    GetID("Sound_Parameter_Interface").style.display = "none";
    GetID("Other_Parameter_Interface").style.display = "none";
    // 获得四个按钮  重新初始化
    var btn = GetID("advanceset_div_Div_Btn").getElementsByTagName("div");
    for (var i = 0; i < btn.length; i++) {
        btn[i].style.backgroundColor = "#9CAAC1"; // 设置按钮颜色
        btn[i].setAttribute("clickstate", "false"); // 设置按钮点击状态为未点击
    }
    GetID(dd).setAttribute("clickstate", "true"); // 设置被点击的按钮状态为被点击
    GetID(dd).style.backgroundColor = "White"; // 设置按钮背景色
    GetID(id).style.display = "block"; // 显示按钮对应的参数界面
}

// 下拉框事件
function GetTheValue(id) {
    var value = GetID(id).options[GetID(id).selectedIndex].text;
    switch (id) {
        case "DeviceType_VideoCapture": // 视频采集设备
            BRAC_SelectVideoCapture(BRAC_DEVICE_VIDEOCAPTURE, value);
            break;
        case "DeviceType_AudioCapture": // 音频采集设备
            BRAC_SelectVideoCapture(BRAC_DEVICE_AUDIOCAPTURE, value);
            break;
        case "DeviceType_AudioPlayBack": // 音频播放设备
            BRAC_SelectVideoCapture(BRAC_DEVICE_AUDIOPLAYBACK, value);
            break;
        case "quality": // 质量
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL, value);
            break;
        case "code_rate": // 码率
            if (value == "质量模式")
                GetID("quality").disabled = "";
            else {
                BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL, parseInt(value));
                GetID("quality").disabled = "disabled";
            }
            break;
        case "distinguishability": // 分辨率
            var resolution = value.split('x');
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_WIDTHCTRL, parseInt(resolution[0]));
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, parseInt(resolution[1]));
            //GetID("current_resolution").innerHTML = BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL) + "x" + BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL) + ")";
            break;
        case "frame_rate": // 帧率
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL, parseInt(value));
            break;
        case "preinstall": // 预设
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL, parseInt(value));
            break;
        case "Speak_Mode": // 音频播放模式
            if (value == "发言模式(默认)")
                BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, 0);
            if (value == "放歌模式")
                BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, 1);
            if (value == "卡拉OK模式")
                BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, 2);
            if (value == "线路输入模式")
                BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, 3);
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
                for (var i = 0; i < SelectTag.length; i++) { // 循环标签
                    if (SelectTag[i].id != "quality") { //质量 下拉框不随复选框选中而启用
                        SelectTag[i].disabled = "";
                        if (GetID("code_rate").options[GetID("code_rate").selectedIndex].text == "质量模式")
                            GetID("quality").disabled = "";
                    }
                    for (var j = 0; j < GetAControl.length; j++)
                        GetAControl[j].style.color = "Black";
                }
            }
            break;
        case "Checkbox_P2P":
            if (GetID(id).checked == true) BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC, 1);
            else BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC, 0);
            break;
        case "audio_vadctrl": // 静音检测
            if (GetID(id).checked == true) BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC, 1);
            else BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC, 0);
            break;
        case "audio_echoctrl": // 回音消除
            if (GetID(id).checked == true) BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, 1);
            else BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, 0);
            break;
        case "audio_nsctrl": // 噪音抑制
            if (GetID(id).checked == true) BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL, 1);
            else BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL, 0);
            break;
        case "audio_agcctrl": // 自动增益
            if (GetID(id).checked == true) BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, 1);
            else BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, 0);
            break;
    }
}

// 获取当前参数值
function GetCurrentDevice() {
    GetIndex("DeviceType_VideoCapture", BRAC_GetCurrentDevice(1), "combobox"); // 当前使用的视频采集器
    GetIndex("DeviceType_AudioCapture", BRAC_GetCurrentDevice(2), "combobox"); // 当前使用的音频采集器
    GetIndex("DeviceType_AudioPlayBack", BRAC_GetCurrentDevice(3), "combobox"); // 当前使用的音频播放器
    GetIndex("quality", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_QUALITYCTRL), "combobox"); // 当前使用的质量参数
    GetIndex("code_rate", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_BITRATECTRL), "combobox"); // 当前使用的码率参数
    GetIndex("distinguishability", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL) + "x" + BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL), "combobox"); // 当前使用的的分辨率
    GetIndex("frame_rate", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_FPSCTRL), "combobox"); // 当前使用的的帧率参数
    GetIndex("preinstall", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_PRESETCTRL), "combobox"); // 当前使用的预设参数

    GetIndex("Speak_Mode", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_CAPTUREMODE), "combobox"); // 当前使用的音频播放模式

    GetIndex("audio_vadctrl", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_VADCTRL), "checkbox") // 当前使用的静音检测
    GetIndex("audio_echoctrl", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_ECHOCTRL), "checkbox") // 当前使用的回音消除
    GetIndex("audio_nsctrl", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_NSCTRL), "checkbox") // 当前使用的噪音抑制
    GetIndex("audio_agcctrl", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_AGCCTRL), "checkbox") // 当前使用的自动增益

    GetIndex("Checkbox_P2P", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_VADCTRL), "checkbox") // P2P

    GetID("current_resolution").innerHTML = BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL) + "x" + BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL) + ")";
}

// 设置控件初始值
function GetIndex(control_id, value, type) {
    if (type == "combobox") { // 下拉框
        var slt = GetID(control_id);
        for (var i = 0; i < slt.length; i++) {
            if (slt[i].text == value) {
                GetID(control_id).selectedIndex = i;
                break;
            }
        }
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
    BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM, 1);
    setTimeout(GetCurrentDevice, 500);
}