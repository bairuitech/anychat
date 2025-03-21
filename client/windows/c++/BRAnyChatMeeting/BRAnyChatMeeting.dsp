# Microsoft Developer Studio Project File - Name="BRAnyChatMeeting" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BRAnyChatMeeting - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BRAnyChatMeeting.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BRAnyChatMeeting.mak" CFG="BRAnyChatMeeting - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BRAnyChatMeeting - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BRAnyChatMeeting - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BRAnyChatMeeting - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../AnyChatSDK/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../bin/Release/BRAnyChatMeeting.exe" /libpath:"../AnyChatSDK/lib"

!ELSEIF  "$(CFG)" == "BRAnyChatMeeting - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../AnyChatSDK/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../bin/Debug/BRAnyChatMeeting.exe" /pdbtype:sept /libpath:"../AnyChatSDK/lib"

!ENDIF 

# Begin Target

# Name "BRAnyChatMeeting - Win32 Release"
# Name "BRAnyChatMeeting - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Ctrls\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BRAnyChatMeeting.cpp
# End Source File
# Begin Source File

SOURCE=.\BRAnyChatMeeting.rc
# End Source File
# Begin Source File

SOURCE=.\BRAnyChatMeetingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Ctrls\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\FullScreenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Ctrls\GradientProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\HallDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Ctrls\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Ctrls\SlideBar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\VideoPanelDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BRAnyChatMeeting.h
# End Source File
# Begin Source File

SOURCE=.\BRAnyChatMeetingDlg.h
# End Source File
# Begin Source File

SOURCE=.\FullScreenDlg.h
# End Source File
# Begin Source File

SOURCE=.\HallDlg.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\VideoPanelDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BRAnyChatMeeting.ico
# End Source File
# Begin Source File

SOURCE=.\res\BRAnyChatMeeting.rc2
# End Source File
# Begin Source File

SOURCE=.\res\camera_close.ico
# End Source File
# Begin Source File

SOURCE=.\res\camera_open.ico
# End Source File
# Begin Source File

SOURCE=.\res\chatlogo.jpg
# End Source File
# Begin Source File

SOURCE=.\res\CloseAudio.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CloseVideo.bmp
# End Source File
# Begin Source File

SOURCE=".\res\login-top.jpg"
# End Source File
# Begin Source File

SOURCE=.\res\mic.ico
# End Source File
# Begin Source File

SOURCE=.\res\netstatus\netstatus_bad.jpg
# End Source File
# Begin Source File

SOURCE=.\res\netstatus\netstatus_good.jpg
# End Source File
# Begin Source File

SOURCE=.\res\netstatus\netstatus_normal.jpg
# End Source File
# Begin Source File

SOURCE=.\res\netstatus\netstatus_verybad.jpg
# End Source File
# Begin Source File

SOURCE=.\res\netstatus\netstatus_verygood.jpg
# End Source File
# Begin Source File

SOURCE=.\res\OpenAudio.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OpenVideo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\snapshot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\videopanel\vfBottomLeft.jpg
# End Source File
# Begin Source File

SOURCE=.\res\videopanel\vfBottomMiddle.jpg
# End Source File
# Begin Source File

SOURCE=.\res\videopanel\vfBottomRight.jpg
# End Source File
# Begin Source File

SOURCE=.\res\videopanel\vfLeft.jpg
# End Source File
# Begin Source File

SOURCE=.\res\videopanel\vfRight.jpg
# End Source File
# Begin Source File

SOURCE=.\res\videopanel\vfTopLeft.jpg
# End Source File
# Begin Source File

SOURCE=.\res\videopanel\vfTopMiddle.jpg
# End Source File
# Begin Source File

SOURCE=.\res\videopanel\vfTopRight.jpg
# End Source File
# Begin Source File

SOURCE=.\res\videobk.jpg
# End Source File
# End Group
# End Target
# End Project
