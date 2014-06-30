; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAnyChatVideoMixerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AnyChatVideoMixer.h"

ClassCount=3
Class1=CAnyChatVideoMixerApp
Class2=CAnyChatVideoMixerDlg

ResourceCount=3
Resource2=IDD_ANYCHATVIDEOMIXER_DIALOG
Resource1=IDR_MAINFRAME
Class3=CConfigDlg
Resource3=IDD_DIALOG_CONFIG

[CLS:CAnyChatVideoMixerApp]
Type=0
HeaderFile=AnyChatVideoMixer.h
ImplementationFile=AnyChatVideoMixer.cpp
Filter=N

[CLS:CAnyChatVideoMixerDlg]
Type=0
HeaderFile=AnyChatVideoMixerDlg.h
ImplementationFile=AnyChatVideoMixerDlg.cpp
Filter=D
LastObject=IDC_EDIT6
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_ANYCHATVIDEOMIXER_DIALOG]
Type=1
Class=CAnyChatVideoMixerDlg
ControlCount=3
Control1=IDC_BUTTON_START,button,1342242816
Control2=IDC_EDIT_LOG,edit,1350637764
Control3=IDC_BUTTON_CONFIG,button,1342242816

[DLG:IDD_DIALOG_CONFIG]
Type=1
Class=CConfigDlg
ControlCount=21
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_SERVER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_PORT,edit,1350639744
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_USERNAME,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_PASSWORD,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_ROOMID,edit,1350631552
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_COMBO_RESOLUTION,combobox,1344340226
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_VIDEO_FPS,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT_BITRATE,edit,1350631552
Control21=IDC_STATIC,static,1342308352

[CLS:CConfigDlg]
Type=0
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

