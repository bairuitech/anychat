
//��Ƶ��������������
var code_rate_txt = ["����ģʽ", "40Kbps", "60Kbps", "100Kbps", "150Kbps", "200Kbps", "300Kbps", "400Kbps", "500Kbps", "600Kbps", "800Kbps", "1000Kbps", "1200Kbps", "1500Kbps"]; // ����������
var quality_txt = ["��ͨ��Ƶ����", "�е���Ƶ����", "�Ϻ���Ƶ����"]; // ����������
var resolution_txt = ["176x144", "320x240", "352x288", "640x480", "720x480", "720x576", "800x600", "960x720", "1024x576", "1280x720", "1280x1024", "1920x1080"]; // �ֱ���������
var frame_rate_txt = ["5 FPS", "8 FPS", "12 FPS", "15 FPS", "20 FPS", "25 FPS", "30 FPS"]; // ֡��������
var preinstall_txt = ["1", "2", "3", "4", "5"]; // Ԥ��������
var speakmode_txt = ["����ģʽ(Ĭ��)", "�Ÿ�ģʽ", "����OKģʽ", "��·����ģʽ"]; // ��Ƶģʽ������
var videoshow_clipmode_txt = ["Ĭ��ģʽ", "�ص�ģʽ", "��Сģʽ", "ƽ��ģʽ","��̬ģʽ"]; // ��Ƶ��ʾ�ü�ģʽ������

var bitrate_combo_value = [0, 40000, 60000, 100000, 150000, 200000, 300000, 400000, 500000, 600000, 800000, 1000000, 1200000, 1500000]; // ����ֵ
var quality_combo_value= [2, 3, 4]; // ��������ֵ
var framerate_combo_value= [5, 8, 12, 15 , 20 , 25 , 30 ]; // ֡��ֵ
var videopreset_combo_value= [1, 2, 3, 4, 5]; // Ԥ�����ֵ
var speakmode_combo_value= [0, 1, 2, 3]; // ��Ƶģʽֵ
var videoshow_clipmode_value= [0, 1, 2, 3,4]; // ��Ƶ��ʾ�ü�ģʽֵ

var mVideoWidthValue = 320;
var mVideoHeightValue = 240;
var mBitRateValue = 90000;
var mFrameRateValue = 12;
var mVideoQualityValue = 3;
var mVideoPresetValue = 3;



//���������ֵ
function filltheselect(id, txtArray,valueArray) {
    GetID(id).options.length = 0;
    for (var j = 0; j < txtArray.length; j++) {
        var option = document.createElement("option");
        GetID(id).appendChild(option);
        option.value = valueArray[j];
        option.text = txtArray[j];
    }
}
// ��ʼ���߼����ý������пؼ� ���и�ֵ
function InitAdvanced() {
    filltheselect("code_rate", code_rate_txt,bitrate_combo_value); 			// �������������
    filltheselect("quality", quality_txt,quality_combo_value); 				// �������������
    filltheselect("distinguishability", resolution_txt,resolution_txt); 	// ���ֱ���������
    filltheselect("frame_rate", frame_rate_txt,framerate_combo_value); 		// ���֡��������
    filltheselect("preinstall", preinstall_txt,videopreset_combo_value); 	// ���Ԥ��������
    filltheselect("Speak_Mode", speakmode_txt,speakmode_combo_value); 		// ����ģʽ������
    filltheselect("DeviceType_VideoCapture", BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE), BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE)); 		// ��Ƶ�ɼ��豸������ֵ
    filltheselect("DeviceType_AudioCapture", BRAC_EnumDevices(BRAC_DEVICE_AUDIOCAPTURE),BRAC_EnumDevices(BRAC_DEVICE_AUDIOCAPTURE)); 		// ��Ƶ�ɼ��豸������ֵ
    filltheselect("DeviceType_AudioPlayBack", BRAC_EnumDevices(BRAC_DEVICE_AUDIOPLAYBACK), BRAC_EnumDevices(BRAC_DEVICE_AUDIOPLAYBACK)); 	// ��Ƶ�����豸������ֵ
	filltheselect("videoshow_clipmode", videoshow_clipmode_txt, videoshow_clipmode_value);		// ��Ƶ��ʾ�ü�ģʽ������ֵ
    SetThePos();
    initControlSelected();
}

// ����Ƶ�豸 ��ť����Ч��
function selectSettingMenu(id, dd) {
    // �������в�������
    GetID("Device_Interface").style.display = "none";
    GetID("Video_Parameter_Interface").style.display = "none";
    GetID("Sound_Parameter_Interface").style.display = "none";
    GetID("Other_Parameter_Interface").style.display = "none";
    // ����ĸ���ť  ���³�ʼ��
    var btn = GetID("advanceset_div_Div_Btn").getElementsByTagName("div");
    for (var i = 0; i < btn.length; i++) {
        btn[i].style.backgroundColor = "#9CAAC1"; 		// ���ð�ť��ɫ
        btn[i].setAttribute("clickstate", "false"); 	// ���ð�ť���״̬Ϊδ���
    }
    GetID(dd).setAttribute("clickstate", "true"); 		// ���ñ�����İ�ť״̬Ϊ�����
    GetID(dd).style.backgroundColor = "White"; 			// ���ð�ť����ɫ
    GetID(id).style.display = "block"; 					// ��ʾ��ť��Ӧ�Ĳ�������
}

// �������¼�
function GetTheValue(id) {
    var value = GetID(id).options[GetID(id).selectedIndex].value;
    switch (id) {
        case "DeviceType_VideoCapture": // ��Ƶ�ɼ��豸
            //BRAC_SelectVideoCapture(BRAC_DEVICE_VIDEOCAPTURE, value);
			//alert(value);
			mVideoCaptureDevice = value;
			initControlSelected();
            break;
        case "DeviceType_AudioCapture": // ��Ƶ�ɼ��豸
            BRAC_SelectVideoCapture(BRAC_DEVICE_AUDIOCAPTURE, value);
            break;
        case "DeviceType_AudioPlayBack":// ��Ƶ�����豸
            BRAC_SelectVideoCapture(BRAC_DEVICE_AUDIOPLAYBACK, value);
            break;
        case "quality": 				// ����
			mVideoQualityValue= parseInt(value);
            break;
        case "code_rate": 				// ����
		    mBitRateValue=parseInt(value);
            break;
        case "distinguishability": 		// �ֱ���
            var resolution = value.split('x');
			mVideoWidthValue = parseInt(resolution[0]);
			mVideoHeightValue = parseInt(resolution[1]);
			break;
        case "frame_rate": 				// ֡��
			mFrameRateValue=parseInt(value);
            break;
        case "preinstall": 				// Ԥ��
			mVideoPresetValue=parseInt(value);
            break;
        case "Speak_Mode": 				// ��Ƶ����ģʽ
            BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, parseInt(value));
            break;
		case "videoshow_clipmode":		//��Ƶ��ʾ�ü�ģʽ
			BRAC_SetSDKOption(BRAC_SO_VIDEOSHOW_CLIPMODE, parseInt(value));
			break;
    }
}
//  ��ѡ���¼�
function ChangeTheResult(id) {
    switch (id) {
        case "ServerSetting": // ���������ò�����ť
            var GetAControl = GetID("advanceset_div_Tab").getElementsByTagName("a");
            var SelectTag = GetID("Video_Parameter_Interface").getElementsByTagName("select"); // ȡ�� ��Ƶ�������� ���� ����select��ǩ
            if (GetID("ServerSetting").checked == true) { // ��ǩ����¼�
                for (var i = 0; i < SelectTag.length; i++) { // ѭ����ǩ
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
        case "audio_vadctrl": // �������
            if (GetID(id).checked == true)
				BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL, 1);
            else 
				BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL, 0);
            break;
        case "audio_echoctrl": // ��������
            if (GetID(id).checked == true)
				BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, 1);
            else 
				BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, 0);
            break;
        case "audio_nsctrl": // ��������
            if (GetID(id).checked == true)
			 	BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL, 1);
            else 
				BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL, 0);
            break;
        case "audio_agcctrl": // �Զ�����
            if (GetID(id).checked == true)
				 BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, 1);
            else
				 BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, 0);
            break;
    }
}

// ��ȡ��ǰ����ֵ
function initControlSelected() {
    GetIndex("DeviceType_VideoCapture", BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE),mVideoCaptureDevice,"combobox"); // ��ǰʹ�õ���Ƶ�ɼ���
    GetIndex("DeviceType_AudioCapture", BRAC_EnumDevices(BRAC_DEVICE_AUDIOCAPTURE),BRAC_GetCurrentDevice(BRAC_DEVICE_AUDIOCAPTURE),"combobox"); // ��ǰʹ�õ���Ƶ�ɼ���
	GetIndex("DeviceType_AudioPlayBack", BRAC_EnumDevices(BRAC_DEVICE_AUDIOPLAYBACK),BRAC_GetCurrentDevice(BRAC_DEVICE_AUDIOPLAYBACK),"combobox"); // ��ǰʹ�õ���Ƶ������
	
	var devices = BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE);
	
	for(var i=0;i<BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE).length;i++)
	{
		//alert(mVideoCaptureDevice);
		if(devices[i] == mVideoCaptureDevice)
		{
			GetIndex("code_rate",bitrate_combo_value ,BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOBITRATE),"combobox"); // ��ǰʹ�õ����ʲ���
			GetIndex("distinguishability",resolution_txt, BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOWIDTH) + "x" + 			BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOHEIGHT), "combobox"); // ��ǰʹ�õĵķֱ���
			GetIndex("frame_rate",framerate_combo_value, BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOFPS), "combobox"); // ��ǰʹ�õĵ�֡�ʲ���
			//alert("���ʣ�"+BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOBITRATE)+";�ֱ��ʣ�"+BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOWIDTH)+"*"+BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOHEIGHT)+";֡�ʣ�"+BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOFPS));
			GetID("current_resolution").innerHTML = BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOWIDTH) + "x" + BRAC_GetUserStreamInfoInt(-1,i,BRAC_STREAMINFO_VIDEOHEIGHT) + ")";
		}
	}
	GetIndex("preinstall", videopreset_combo_value,BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_PRESETCTRL), "combobox"); // ��ǰʹ�õ�Ԥ�����
	GetIndex("quality", quality_combo_value,BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_BITRATECTRL),"combobox"); // ��ǰʹ�õ���������
    GetIndex("Speak_Mode",speakmode_combo_value, BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_CAPTUREMODE), "combobox"); // ��ǰʹ�õ���Ƶ����ģʽ
	GetIndex("videoshow_clipmode",videoshow_clipmode_value, BRAC_GetSDKOptionInt(BRAC_SO_VIDEOSHOW_CLIPMODE), "combobox"); // ��ǰʹ�õ���Ƶ��ʾ�ü�ģʽ
	
    GetIndex("audio_vadctrl", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_VADCTRL), "checkbox");// ��ǰʹ�õľ������
    GetIndex("audio_echoctrl", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_ECHOCTRL), "checkbox"); // ��ǰʹ�õĻ�������
    GetIndex("audio_nsctrl", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_NSCTRL), "checkbox"); // ��ǰʹ�õ���������
    GetIndex("audio_agcctrl", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_AGCCTRL), "checkbox"); // ��ǰʹ�õ��Զ�����
    GetIndex("Checkbox_P2P", null,BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_VADCTRL), "checkbox") ;// P2P
    
}


// ���ÿؼ���ʼֵ
function GetIndex(control_id,valueArray,value,type) {
    if (type == "combobox") { // ������
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
    else { // ��ѡ��
        if (value == 1) // 1Ϊ�� 
            GetID(control_id).checked = true;
        else
            GetID(control_id).checked = false;
    }
}

// ���� �߼����ý��� x����
function SetThePos() {
    var TheBodyWidth = document.body.offsetWidth;
    GetID("advanceset_div").style.marginLeft = (TheBodyWidth - 464) / 2 + 87 + "px";
}
// ��ʾ �������  ����
function BtnAdjust() {
    BRAC_ShowLVProperty("");
}
// Ӧ������
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
	
	
	// ���ñ�����Ƶ��������ʣ��������Ϊ0�����ʾʹ����������ģʽ��
	//BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL,mBitRateValue);
	//BRAC_SetUserStreamInfo(-1,);
	// ���ñ�����Ƶ���������
	//BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL,mVideoQualityValue);
	// ���ñ�����Ƶ�ɼ��ֱ���
	//BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_WIDTHCTRL, mVideoWidthValue);
    //BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, mVideoHeightValue);
	// ���ñ�����Ƶ�����֡��
	//BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL,mFrameRateValue);
	// ���ñ�����Ƶ����Ĺؼ�֡���
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_GOPCTRL, mFrameRateValue*4);
	// ������Ƶ����Ԥ�������ֵԽ�󣬱�������Խ�ߣ�ռ��CPU��ԴҲ��Խ�ߣ�
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL,mVideoPresetValue);
	// ����Ƶ������Ч
    BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM, 1);
    setTimeout(initControlSelected, 500);
}