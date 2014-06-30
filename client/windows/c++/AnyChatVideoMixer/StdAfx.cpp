// stdafx.cpp : source file that includes just the standard includes
//	AnyChatVideoMixer.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"



LOCAL_SETTINGS	g_localSettings = {0};


// 刷新本地配置信息
void RefreshLocalSettings(void)
{
	TCHAR szConfigFile[MAX_PATH] = {0};
	GetModuleFileName(NULL,szConfigFile,MAX_PATH);
	(_tcsrchr(szConfigFile,'.'))[1] = 0;
	_tcscat(szConfigFile,"ini");


	GetPrivateProfileString("Base Settings", "SERVER", "demo.anychat.cn", g_localSettings.szServer, sizeof(g_localSettings.szServer), szConfigFile);
	GetPrivateProfileString("Base Settings", "USERNAME", "VideoMixer", g_localSettings.szUserName, sizeof(g_localSettings.szUserName), szConfigFile);
	GetPrivateProfileString("Base Settings", "PASSWORD", "", g_localSettings.szPassWord, sizeof(g_localSettings.szPassWord), szConfigFile);

	g_localSettings.dwPort = GetPrivateProfileInt("Base Settings", "PORT", 8906, szConfigFile);
	g_localSettings.dwRoomId = GetPrivateProfileInt("Base Settings", "ROOMID", 1, szConfigFile);

	g_localSettings.dwWidth = GetPrivateProfileInt("Advance Settings", "WIDTH", 640, szConfigFile);
	g_localSettings.dwHeight = GetPrivateProfileInt("Advance Settings", "HEIGHT", 480, szConfigFile);
	g_localSettings.dwBitrate= GetPrivateProfileInt("Advance Settings", "BITRATE", 0, szConfigFile);
	g_localSettings.dwFrameRate = GetPrivateProfileInt("Advance Settings", "FRAMERATE", 15, szConfigFile);

	g_localSettings.dwAudioMix = GetPrivateProfileInt("Advance Settings", "AUDIOMIX", 1, szConfigFile);

}

// 更新本地配置参数到配置文件中
void UpdateLocalSettings2IniFile(void)
{
	TCHAR szConfigFile[MAX_PATH] = {0};
	GetModuleFileName(NULL,szConfigFile,MAX_PATH);
	(_tcsrchr(szConfigFile,'.'))[1] = 0;
	_tcscat(szConfigFile,"ini");

	WritePrivateProfileString("Base Settings", "SERVER", g_localSettings.szServer, szConfigFile);
	WritePrivateProfileString("Base Settings", "USERNAME", g_localSettings.szUserName, szConfigFile);
	WritePrivateProfileString("Base Settings", "PASSWORD", g_localSettings.szPassWord, szConfigFile);

	CHAR s[10]={0};
	_itoa(g_localSettings.dwPort, s, sizeof(s));
	WritePrivateProfileString("Base Settings", "PORT", s, szConfigFile);
	_itoa(g_localSettings.dwRoomId, s, sizeof(s));
	WritePrivateProfileString("Base Settings", "ROOMID", s, szConfigFile);

	_itoa(g_localSettings.dwWidth, s, sizeof(s));
	WritePrivateProfileString("Advance Settings", "WIDTH", s, szConfigFile);
	_itoa(g_localSettings.dwHeight, s, sizeof(s));
	WritePrivateProfileString("Advance Settings", "HEIGHT", s, szConfigFile);
	_itoa(g_localSettings.dwBitrate, s, sizeof(s));
	WritePrivateProfileString("Advance Settings", "BITRATE", s, szConfigFile);
	_itoa(g_localSettings.dwFrameRate, s, sizeof(s));
	WritePrivateProfileString("Advance Settings", "FRAMERATE", s, szConfigFile);

	_itoa(g_localSettings.dwAudioMix, s, sizeof(s));
	WritePrivateProfileString("Advance Settings", "AUDIOMIX", s, szConfigFile);
}