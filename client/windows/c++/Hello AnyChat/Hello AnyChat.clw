; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CHelloAnyChatDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Hello AnyChat.h"

ClassCount=3
Class1=CHelloAnyChatApp
Class2=CHelloAnyChatDlg

ResourceCount=3
Resource2=IDD_HELLOANYCHAT_DIALOG
Resource1=IDR_MAINFRAME
Class3=VideoSetDlg
Resource3=IDD_DIALOG_VIDEOSET

[CLS:CHelloAnyChatApp]
Type=0
HeaderFile=Hello AnyChat.h
ImplementationFile=Hello AnyChat.cpp
Filter=N
LastObject=CHelloAnyChatApp

[CLS:CHelloAnyChatDlg]
Type=0
HeaderFile=Hello AnyChatDlg.h
ImplementationFile=Hello AnyChatDlg.cpp
Filter=D
LastObject=IDC_BUTTON_SETTING
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_HELLOANYCHAT_DIALOG]
Type=1
Class=CHelloAnyChatDlg
ControlCount=19
Control1=IDLOGOUT,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_IP,edit,1350631552
Control5=IDC_EDIT_NAME,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_PORT,edit,1350639744
Control9=IDC_EDIT_ROOM,edit,1350639744
Control10=IDC_STATIC_USERLISTTITLE,static,1342308865
Control11=IDLOGIN,button,1342242817
Control12=IDC_LIST_USERMSG,SysListView32,1350631424
Control13=IDC_STATIC_SELFVIEW,button,1342177287
Control14=IDC_STATIC_REMOTEVIEW,button,1342177287
Control15=IDC_STATIC_SDKVER,static,1342308352
Control16=IDC_STATIC_LINKMSG,static,1342308352
Control17=IDC_BUTTON_SETTING,button,1342242816
Control18=IDC_BUTTON_AUDIOCTRL,button,1342242816
Control19=IDC_BUTTON_VIDEOCTRL,button,1342242816

[DLG:IDD_DIALOG_VIDEOSET]
Type=1
Class=VideoSetDlg
ControlCount=22
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO_VIDEODEVICE,combobox,1344339970
Control3=IDC_COMBO_AUDIODEVICE,combobox,1344339970
Control4=IDC_CHK_SERVERPRIORITY,button,1342242819
Control5=IDC_COMBO_BITRATE,combobox,1344339970
Control6=IDC_COMBO_FRAMERATE,combobox,1344339970
Control7=IDC_COMBO_QUALITY,combobox,1344339970
Control8=IDC_COMBO_RESOLUTION,combobox,1344339970
Control9=IDC_COMBO_PREPARAM,combobox,1344339970
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_COMBO_AUDIOMODE,combobox,1344339970
Control16=IDC_CHECK_ENABLEVAD,button,1342242819
Control17=IDC_CHECK_ENABLEECHO,button,1342242819
Control18=IDC_CHECK_ENABLENS,button,1342242819
Control19=IDC_CHECK_ENABLEAGC,button,1342242819
Control20=IDC_STATIC,static,1342308352
Control21=IDC_COMBO_PLAYDEVICE,combobox,1344340226
Control22=IDC_STATIC,static,1342308352

[CLS:VideoSetDlg]
Type=0
HeaderFile=VideoSetDlg.h
ImplementationFile=VideoSetDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO_PLAYDEVICE
VirtualFilter=dWC

