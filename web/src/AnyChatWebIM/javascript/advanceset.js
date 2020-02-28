
//��Ƶ��������������
var mDefaultCodeRate = ["����ģʽ", "40", "60", "100", "150", "200", "300", "400", "500", "600", "800", "1000", "1200", "1500"]; // ����������
var mDefaultQuality = ["�ϲ�����", "һ������", "�е�����", "�Ϻ�����", "�������"]; // ����������
var mDefaultResolution = ["176x144", "320x240", "352x288", "640x480", "720x480", "720x576", "800x600", "960x720", "1024x576", "1280x720", "1280x1024", "1920x1080"]; // �ֱ���������
var mDefaultFrame_rate = ["5 FPS", "8 FPS", "12 FPS", "15 FPS", "20 FPS", "25 FPS", "30 FPS"]; // ֡��������
var mDefaultPreinstall = ["1", "2", "3", "4", "5"]; // Ԥ��������
var mDefaultSpeakmode = ["����ģʽ(Ĭ��)", "�Ÿ�ģʽ", "����OKģʽ", "��·����ģʽ"]; // ��Ƶģʽ������

//���������ֵ
function filltheselect(id, theArray) {
    Getdmo(id).options.length = 0;
    for (var j = 0; j < theArray.length; j++) {
        var option = document.createElement("option");
        Getdmo(id).appendChild(option);
        option.value = j;
        option.text = theArray[j];
    }
}
// ��ʼ���߼����ý������пؼ� ���и�ֵ
function InitAdvanced() {
    filltheselect("code_rate", mDefaultCodeRate); // �������������
    filltheselect("quality", mDefaultQuality); // �������������
    filltheselect("distinguishability", mDefaultResolution); // ���ֱ���������
    filltheselect("frame_rate", mDefaultFrame_rate); // ���֡��������
    filltheselect("preinstall", mDefaultPreinstall); // ���Ԥ��������
    filltheselect("Speak_Mode", mDefaultSpeakmode); // ����ģʽ������
    filltheselect("DeviceType_VideoCapture", BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE)); // ��Ƶ�ɼ��豸������ֵ
    filltheselect("DeviceType_AudioCapture", BRAC_EnumDevices(BRAC_DEVICE_AUDIOCAPTURE)); // ��Ƶ�ɼ��豸������ֵ
    filltheselect("DeviceType_AudioPlayBack", BRAC_EnumDevices(BRAC_DEVICE_AUDIOPLAYBACK)); // ��Ƶ�����豸������ֵ
    GetCurrentDevice();
}
// ����Ƶ�豸 ��ť����Ч��
function SettingBtnMouseout(id) {
    if (Getdmo(id).getAttribute("clickstate") == "false") // û�б�����İ�ť�ı䱳��ɫ
        Getdmo(id).style.backgroundColor = "#9CAAC1";
}
// ����Ƶ�豸 ��ť����Ч��
function SettingBtnClick(id, dd) {
    // �������в�������
    Getdmo("Device_Interface").style.display = "none";
    Getdmo("Video_Parameter_Interface").style.display = "none";
    Getdmo("Sound_Parameter_Interface").style.display = "none";
    Getdmo("Other_Parameter_Interface").style.display = "none";
    // ����ĸ���ť  ���³�ʼ��
    var btn = Getdmo("advanceset_div_Div_Btn").getElementsByTagName("div");
    for (var i = 0; i < btn.length; i++) {
        btn[i].style.backgroundColor = "#9CAAC1"; // ���ð�ť��ɫ
        btn[i].setAttribute("clickstate", "false"); // ���ð�ť���״̬Ϊδ���
    }
    Getdmo(dd).setAttribute("clickstate", "true"); // ���ñ�����İ�ť״̬Ϊ�����
    Getdmo(dd).style.backgroundColor = "White"; // ���ð�ť����ɫ
    Getdmo(id).style.display = "block"; // ��ʾ��ť��Ӧ�Ĳ�������
}

// �������¼�
function GetTheValue(id) {
    var value = Getdmo(id).options[Getdmo(id).selectedIndex].text;
    switch (id) {
        case "DeviceType_VideoCapture": // ��Ƶ�ɼ��豸
            BRAC_SelectVideoCapture(BRAC_DEVICE_VIDEOCAPTURE, value);
            break;
        case "DeviceType_AudioCapture": // ��Ƶ�ɼ��豸
            BRAC_SelectVideoCapture(BRAC_DEVICE_AUDIOCAPTURE, value);
            break;
        case "DeviceType_AudioPlayBack": // ��Ƶ�����豸
            BRAC_SelectVideoCapture(BRAC_DEVICE_AUDIOPLAYBACK, value);
            break;
        case "quality": // ����
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL, value);
            break;
        case "code_rate": // ����
            if (value == "����ģʽ")
                Getdmo("quality").disabled = "";
            else {
                BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL, parseInt(value));
                Getdmo("quality").disabled = "disabled";
            }
            break;
        case "distinguishability": // �ֱ���
            var resolution = value.split('x');
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_WIDTHCTRL, parseInt(resolution[0]));
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, parseInt(resolution[1]));
            //Getdmo("current_resolution").innerHTML = BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL) + "x" + BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL) + ")";
            break;
        case "frame_rate": // ֡��
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL, parseInt(value));
            break;
        case "preinstall": // Ԥ��
            BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL, parseInt(value));
            break;
        case "Speak_Mode": // ��Ƶ����ģʽ
            if (value == "����ģʽ(Ĭ��)")
                BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, 0);
            if (value == "�Ÿ�ģʽ")
                BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, 1);
            if (value == "����OKģʽ")
                BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, 2);
            if (value == "��·����ģʽ")
                BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, 3);
            break;
    }
}
//  ��ѡ���¼�
function ChangeTheResult(id) {
    switch (id) {
        case "ServerSetting": // ���������ò�����ť
            var GetAControl = Getdmo("advanceset_div_Tab").getElementsByTagName("a");
            var SelectTag = Getdmo("Video_Parameter_Interface").getElementsByTagName("select"); // ȡ�� ��Ƶ�������� ���� ����select��ǩ
            if (Getdmo("ServerSetting").checked == true) { // ��ǩ����¼�
                for (var i = 0; i < SelectTag.length; i++) { // ѭ����ǩ
                    SelectTag[i].disabled = "disabled";
                }
                for (var j = 0; j < GetAControl.length; j++)
                    GetAControl[j].style.color = "#999999";
            }
            else {
                for (var i = 0; i < SelectTag.length; i++) { // ѭ����ǩ
                    if (SelectTag[i].id != "quality") { //���� �������渴ѡ��ѡ�ж�����
                        SelectTag[i].disabled = "";
                        if (Getdmo("code_rate").options[Getdmo("code_rate").selectedIndex].text == "����ģʽ")
                            Getdmo("quality").disabled = "";
                    }
                    for (var j = 0; j < GetAControl.length; j++)
                        GetAControl[j].style.color = "Black";
                }
            }
            break;
        case "Checkbox_P2P":
            if (Getdmo(id).checked == true) BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC, 1);
            else BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC, 0);
            break;
        case "audio_vadctrl": // �������
            if (Getdmo(id).checked == true) BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL, 1);
            else BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL, 0);
            break;
        case "audio_echoctrl": // ��������
            if (Getdmo(id).checked == true) BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, 1);
            else BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, 0);
            break;
        case "audio_nsctrl": // ��������
            if (Getdmo(id).checked == true) BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL, 1);
            else BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL, 0);
            break;
        case "audio_agcctrl": // �Զ�����
            if (Getdmo(id).checked == true) BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, 1);
            else BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, 0);
            break;
    }
}

// ��ȡ��ǰ����ֵ
function GetCurrentDevice() {
    GetIndex("DeviceType_VideoCapture", BRAC_GetCurrentDevice(1), "combobox"); // ��ǰʹ�õ���Ƶ�ɼ���
    GetIndex("DeviceType_AudioCapture", BRAC_GetCurrentDevice(2), "combobox"); // ��ǰʹ�õ���Ƶ�ɼ���
    GetIndex("DeviceType_AudioPlayBack", BRAC_GetCurrentDevice(3), "combobox"); // ��ǰʹ�õ���Ƶ������
    GetIndex("quality", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_QUALITYCTRL), "combobox"); // ��ǰʹ�õ���������
    GetIndex("code_rate", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_BITRATECTRL), "combobox"); // ��ǰʹ�õ����ʲ���
    GetIndex("distinguishability", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL) + "x" + BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL), "combobox"); // ��ǰʹ�õĵķֱ���
    GetIndex("frame_rate", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_FPSCTRL), "combobox"); // ��ǰʹ�õĵ�֡�ʲ���
    GetIndex("preinstall", BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_PRESETCTRL), "combobox"); // ��ǰʹ�õ�Ԥ�����

    GetIndex("Speak_Mode", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_CAPTUREMODE), "combobox"); // ��ǰʹ�õ���Ƶ����ģʽ

    GetIndex("audio_vadctrl", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_VADCTRL), "checkbox") // ��ǰʹ�õľ������
    GetIndex("audio_echoctrl", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_ECHOCTRL), "checkbox") // ��ǰʹ�õĻ�������
    GetIndex("audio_nsctrl", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_NSCTRL), "checkbox") // ��ǰʹ�õ���������
    GetIndex("audio_agcctrl", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_AGCCTRL), "checkbox") // ��ǰʹ�õ��Զ�����

    GetIndex("Checkbox_P2P", BRAC_GetSDKOptionInt(BRAC_SO_AUDIO_VADCTRL), "checkbox") // P2P

    Getdmo("current_resolution").innerHTML = BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_WIDTHCTRL) + "x" + BRAC_GetSDKOptionInt(BRAC_SO_LOCALVIDEO_HEIGHTCTRL) + ")";
}

// ���ÿؼ���ʼֵ
function GetIndex(control_id, value, type) {
    if (type == "combobox") { // ������
        var slt = Getdmo(control_id);
        for (var i = 0; i < slt.length; i++) {
            if (slt[i].text == value) {
                Getdmo(control_id).selectedIndex = i;
                break;
            }
        }
    }
    else { // ��ѡ��
        if (value == 1) // 1Ϊ�� 
            Getdmo(control_id).checked = true;
        else
            Getdmo(control_id).checked = false;
    }
}
// ��ʾ �������  ����
function BtnAdjust() {
    BRAC_ShowLVProperty("");
}
// Ӧ������
function BtnApply() {
    BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM, 1);
    setTimeout(GetCurrentDevice, 500);
}
//div��ť��껮�뻮��Ч��
function Mouseover(id) {
    Getdmo(id).style.backgroundColor = "#FFFFCC";
}
//div��ť��껮�뻮��Ч��
function Mouseout(id) {
    Getdmo(id).style.backgroundColor = "#E6E6E6";
}