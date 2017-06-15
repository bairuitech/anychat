#if !defined(BR_ANYCHAT_CORE_SDK_H__INCLUDED_)
#define BR_ANYCHAT_CORE_SDK_H__INCLUDED_

#include <mmsystem.h>
#include <wingdi.h>
#include "AnyChatDefine.h"
#include "AnyChatObjectDefine.h"
#include "GVErrorCodeDefine.h"
#include "GVMessageDefine.h"


/**
 *	AnyChat Core SDK Include File
 */



#define BRAC_API extern "C" __declspec(dllexport)


// ��Ƶ���ݻص���������
typedef void (CALLBACK * BRAC_VideoData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue);
// ��Ƶ������չ�ص��������壨����ʱ�����
typedef void (CALLBACK * BRAC_VideoDataEx_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, DWORD dwTimeStamp, LPVOID lpUserValue);
// ��Ƶ������չ�ص��������壨����ʱ�����֧�ֶ�·����
typedef void (CALLBACK * BRAC_VideoDataEx2_CallBack)(DWORD dwUserid, DWORD dwStreamIndex, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, DWORD dwTimeStamp, LPVOID lpUserValue);
// ��Ƶ���ݻص���������
typedef void (CALLBACK * BRAC_AudioData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue);
// ��Ƶ������չ�ص��������壨����ʱ�����
typedef void (CALLBACK * BRAC_AudioDataEx_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, DWORD dwTimeStamp, LPVOID lpUserValue);
// ��Ƶ������չ�ص��������壨����ʱ�����֧�ֶ�·����
typedef void (CALLBACK * BRAC_AudioDataEx2_CallBack)(DWORD dwUserid, DWORD dwStreamIndex, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, DWORD dwTimeStamp, LPVOID lpUserValue);
// ������Ϣ�ص���������
typedef void (CALLBACK * BRAC_TextMessage_CallBack)(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue);
// ͸��ͨ�����ݻص���������
typedef void (CALLBACK * BRAC_TransBuffer_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// ͸��ͨ��������չ�ص���������
typedef void (CALLBACK * BRAC_TransBufferEx_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// �ļ�����ص���������
typedef void (CALLBACK * BRAC_TransFile_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue);
// �ļ�����ص��������壨��չ��
typedef void (CALLBACK * BRAC_TransFileEx_CallBack)(DWORD dwUserid, DWORD dwErrorCode, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD dwFlags, CHAR* lpTaskGuid, LPCTSTR lpUserStr, LPVOID lpUserValue);
// �����仯�ص���������
typedef void (CALLBACK * BRAC_VolumeChange_CallBack)(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue);
// SDK Filter ͨ�����ݻص���������
typedef void (CALLBACK * BRAC_SDKFilterData_CallBack)(LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// ¼�񡢿���������ɻص���������
typedef void (CALLBACK * BRAC_RecordSnapShot_CallBack)(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType, LPVOID lpUserValue);
// ¼�񡢿������������չ�ص���������
typedef void (CALLBACK * BRAC_RecordSnapShotEx_CallBack)(DWORD dwUserId, LPCTSTR lpFileName, DWORD dwElapse, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);
// ¼�񡢿������������չ�ص���������
typedef void (CALLBACK * BRAC_RecordSnapShotEx2_CallBack)(DWORD dwUserId, DWORD dwErrorCode, LPCTSTR lpFileName, DWORD dwElapse, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);
// �첽��Ϣ֪ͨ�ص���������
typedef void (CALLBACK* BRAC_NotifyMessage_CallBack)(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
// ��Ƶ��Ļ�¼��ص���������
typedef void (CALLBACK * BRAC_VideoScreenEvent_CallBack)(DWORD dwUserid, DWORD type, DWORD key, DWORD dwFlags, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
// ��Ƶͨ����Ϣ֪ͨ�ص���������
typedef void (CALLBACK * BRAC_VideoCallEvent_CallBack)(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue);
// ���ݼ��ܡ����ܻص���������
typedef DWORD (CALLBACK * BRAC_DataEncDec_CallBack)(DWORD dwUserId, DWORD dwFlags, LPBYTE lpInBuf, DWORD dwInSize, LPBYTE lpOutBuf, LPDWORD lpOutSize, LPVOID lpUserValue);
// �������ݷ��ͻص���������
typedef DWORD (CALLBACK * BRAC_NetworkDataSend_CallBack)(DWORD hSocket, DWORD dwFlags, CHAR* lpBuf, DWORD dwSize, DWORD dwTargetAddr, DWORD dwTargetPort, LPVOID lpUserValue);
// ҵ������¼�֪ͨ�ص���������
typedef void (CALLBACK * BRAC_ObjectEventNotify_CallBack)(DWORD dwObjectType, DWORD dwObjectId, DWORD dwEventType, DWORD dwParam1, DWORD dwParam2, DWORD dwParam3, DWORD dwParam4, LPCTSTR lpStrParam, LPVOID lpUserValue);
// Core SDK�¼�֪ͨ��Json��ʽ��
typedef void (CALLBACK * BRAC_CoreSDKEvent_CallBack)(DWORD dwEventType, LPCTSTR lpEventJsonStr, LPVOID lpUserValue);
// Core SDK�������ص�
typedef void (CALLBACK * BRAC_CoreSDKData_CallBack)(DWORD dwDataType, LPVOID lpBuf, DWORD dwLen, LPCTSTR lpJsonStr, LPVOID lpUserValue);

/**
 *	API��������
 */

// ��ȡSDK�汾��Ϣ
BRAC_API DWORD BRAC_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, TCHAR* lpCompileTime, DWORD dwBufLen);
// ����رգ�SDK������־
BRAC_API DWORD BRAC_ActiveCallLog(BOOL bActive);

// ���÷�������֤���루��������ֹ�Ƿ��û���SDK���ӷ��������Ϸ��û����������ӣ�
BRAC_API DWORD BRAC_SetServerAuthPass(LPCTSTR lpPassword);
// ��ʼ��ϵͳ
BRAC_API DWORD BRAC_InitSDK(HWND hWnd, DWORD dwFuncMode);

// ������Ƶ���ݻص�����
BRAC_API DWORD BRAC_SetVideoDataCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ������չ�ص�����������ʱ�����
BRAC_API DWORD BRAC_SetVideoDataExCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoDataEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ���ݻص�����
BRAC_API DWORD BRAC_SetAudioDataCallBack(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ���ݻص���չ����������ʱ�����
BRAC_API DWORD BRAC_SetAudioDataExCallBack(BRAC_AudioDataEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����������Ϣ�ص�����
BRAC_API DWORD BRAC_SetTextMessageCallBack(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����͸��ͨ�����ݻص�����
BRAC_API DWORD BRAC_SetTransBufferCallBack(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����͸��ͨ��������չ�ص�����
BRAC_API DWORD BRAC_SetTransBufferExCallBack(BRAC_TransBufferEx_CallBack lpFunction, LPVOID lpUserValue=NULL);
// �����ļ�����ص�����
BRAC_API DWORD BRAC_SetTransFileCallBack(BRAC_TransFile_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ���������仯�ص�����
BRAC_API DWORD BRAC_SetVolumeChangeCallBack(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����SDK Filterͨ�����ݻص���������
BRAC_API DWORD BRAC_SetSDKFilterDataCallBack(BRAC_SDKFilterData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����¼������������֪ͨ�ص�����
BRAC_API DWORD BRAC_SetRecordSnapShotCallBack(BRAC_RecordSnapShot_CallBack lpFunction, LPVOID lpUserValue=NULL);
// �����첽��Ϣ֪ͨ�ص�����
BRAC_API DWORD BRAC_SetNotifyMessageCallBack(BRAC_NotifyMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ��Ļ�¼��ص�����
BRAC_API DWORD BRAC_SetScreenEventCallBack(BRAC_VideoScreenEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶͨ����Ϣ֪ͨ�ص�����
BRAC_API DWORD BRAC_SetVideoCallEventCallBack(BRAC_VideoCallEvent_CallBack lpFunction, LPVOID lpUserValue=NULL);
// �������ݼ��ܡ����ܻص�����
BRAC_API DWORD BRAC_SetDataEncDecCallBack(BRAC_DataEncDec_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ���ûص��������
BRAC_API DWORD BRAC_SetCallBack(DWORD dwCBType, LPVOID lpFunction, LPVOID lpUserValue=NULL);

// ���ӷ�����
BRAC_API DWORD BRAC_Connect(LPCTSTR lpServerAddr, DWORD dwPort);
// ��¼ϵͳ
BRAC_API DWORD BRAC_Login(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType);
// ��¼ϵͳ����չ��
BRAC_API DWORD BRAC_LoginEx(LPCTSTR lpNickName, DWORD dwUserId, LPCTSTR lpStrUserId=NULL, LPCTSTR lpAppId=NULL, DWORD dwTimeStamp=0, LPCTSTR lpSigStr=NULL, LPCTSTR lpStrParam=NULL);
// ���뷿��
BRAC_API DWORD BRAC_EnterRoom(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType);
// ���뷿��
BRAC_API DWORD BRAC_EnterRoomEx(LPCTSTR lpRoomName, LPCTSTR lpRoomPass);
// �뿪����
BRAC_API DWORD BRAC_LeaveRoom(DWORD dwRoomid);
// ע��ϵͳ
BRAC_API DWORD BRAC_Logout(VOID);

// �ͷ�������Դ
BRAC_API DWORD BRAC_Release(VOID);

// ��ȡ��ǰ���������û��б��Ƽ�ʹ�ã�BRAC_GetRoomOnlineUsers��
BRAC_API DWORD BRAC_GetOnlineUser(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// ��ȡָ�����������û��б�
BRAC_API DWORD BRAC_GetRoomOnlineUsers(DWORD dwRoomId, LPDWORD lpUserIDArray, DWORD& dwUserNum);
// ��ѯ�û�����ͷ��״̬
BRAC_API DWORD BRAC_GetCameraState(DWORD dwUserid, DWORD& dwState);
// ��ѯ�û�����״̬
BRAC_API DWORD BRAC_GetSpeakState(DWORD dwUserid, DWORD& dwState);
// ��ѯ�û�����
BRAC_API DWORD BRAC_GetUserLevel(DWORD dwUserid, DWORD& dwLevel);
// ��ѯ�û�����
BRAC_API DWORD BRAC_GetUserName(DWORD dwUserid, TCHAR* lpUserName, DWORD dwLen);
// ��ѯ��������
BRAC_API DWORD BRAC_GetRoomName(DWORD dwRoomId, TCHAR* lpRoomName, DWORD dwLen);
// ��ʾ������Ƶ������ڶԻ���
BRAC_API DWORD BRAC_ShowLVProperty(HWND hParent, LPCTSTR szCaption=NULL, DWORD dwX=0, DWORD dwY=0);

// ��ѯָ���û����״̬
BRAC_API DWORD BRAC_QueryUserState(DWORD dwUserId, int infoname, char FAR* infoval, int infolen);
// ��ѯָ���������״̬
BRAC_API DWORD BRAC_QueryRoomState(DWORD dwRoomId, int infoname, char FAR* infoval, int infolen);

// ö�ٱ�����Ƶ�ɼ��豸
BRAC_API DWORD BRAC_EnumVideoCapture(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�ɼ��豸
BRAC_API DWORD BRAC_SelectVideoCapture(LPCTSTR szCaptureName);
// ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
BRAC_API DWORD BRAC_GetCurVideoCapture(TCHAR* lpDeviceName, DWORD dwLen);
// ö�ٱ�����Ƶ�ɼ��豸
BRAC_API DWORD BRAC_EnumAudioCapture(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�ɼ��豸
BRAC_API DWORD BRAC_SelectAudioCapture(LPCTSTR szCaptureName);
// ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
BRAC_API DWORD BRAC_GetCurAudioCapture(TCHAR* lpDeviceName, DWORD dwLen);
// ö�ٱ�����Ƶ�����豸
BRAC_API DWORD BRAC_EnumAudioPlayback(TCHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�����豸
BRAC_API DWORD BRAC_SelectAudioPlayback(LPCTSTR szDeviceName);
// ��ȡ��ǰʹ�õ���Ƶ�����豸
BRAC_API DWORD BRAC_GetCurAudioPlayback(TCHAR* lpDeviceName, DWORD dwLen);

// �����û���Ƶ
BRAC_API DWORD BRAC_UserCameraControl(DWORD dwUserid, BOOL bOpen);
// �����û���Ƶ����չ��
BRAC_API DWORD BRAC_UserCameraControlEx(DWORD dwUserid, BOOL bOpen, DWORD dwStreamIndex=0, DWORD dwFlags=0, LPCTSTR lpStrParam=NULL);
// �����û�����
BRAC_API DWORD BRAC_UserSpeakControl(DWORD dwUserid, BOOL bOpen);
// �����û���������չ��
BRAC_API DWORD BRAC_UserSpeakControlEx(DWORD dwUserid, BOOL bOpen, DWORD dwStreamIndex=0, DWORD dwFlags=0, LPCTSTR lpStrParam=NULL);
// ������Ƶ��ʾλ��
BRAC_API DWORD BRAC_SetVideoPos(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom);
// ������Ƶ��ʾλ�ã���չ��
BRAC_API DWORD BRAC_SetVideoPosEx(DWORD dwUserid, HWND hWnd, DWORD dwLeft=0, DWORD dwTop=0, DWORD dwRight=0, DWORD dwBottom=0, DWORD dwStreamIndex=0, DWORD dwFlags=0);
// �ػ�ָ���û�����Ƶ
BRAC_API DWORD BRAC_RepaintVideo(DWORD dwUserId, HDC hDC);
// ����ָ���û�����Ƶ����ز�������Ҫ��Ա����û���
BRAC_API DWORD BRAC_SetUserStreamInfo(DWORD dwUserId, DWORD dwStreamIndex, int infoname, char FAR* infoval, int infolen);
// ��ȡָ���û�����Ƶ����ز���
BRAC_API DWORD BRAC_GetUserStreamInfo(DWORD dwUserId, DWORD dwStreamIndex, int infoname, char FAR* infoval, int infolen);


// ��ȡָ����Ƶ�豸�ĵ�ǰ����
BRAC_API DWORD BRAC_AudioGetVolume(BRAC_AudioDevice device, DWORD& dwVolume);
// ����ָ����Ƶ�豸������
BRAC_API DWORD BRAC_AudioSetVolume(BRAC_AudioDevice device, DWORD dwVolume);

// �û�������Ƶ¼�ƣ��Ƽ�ʹ��API��BRAC_StreamRecordCtrlEx��
BRAC_API DWORD BRAC_StreamRecordCtrl(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam);
// �û�������Ƶ¼�ƣ���չ��
BRAC_API DWORD BRAC_StreamRecordCtrlEx(DWORD dwUserId, BOOL bStartRecord, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr);
// ���û�����Ƶ����ץ�ģ����գ�
BRAC_API DWORD BRAC_SnapShot(DWORD dwUserId, DWORD dwFlags, DWORD dwParam);

// ͸��ͨ�����ͻ�����
BRAC_API DWORD BRAC_TransBuffer(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
// ͸��ͨ�����ͻ�������չ
BRAC_API DWORD BRAC_TransBufferEx(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// �����ļ�
BRAC_API DWORD BRAC_TransFile(DWORD dwUserid, LPCTSTR lpLocalPathName, DWORD wParam, DWORD lParam, DWORD dwFlags, DWORD& dwTaskId);
// ��ѯ�������������Ϣ
BRAC_API DWORD BRAC_QueryTransTaskInfo(DWORD dwUserid, DWORD dwTaskId, int infoname, char FAR* infoval, int infolen);
// ȡ����������
BRAC_API DWORD BRAC_CancelTransTask(DWORD dwUserid, DWORD dwTaskId);

// �����ļ�����չ��
BRAC_API DWORD BRAC_TransFileEx(CHAR* lpTaskGuid, DWORD dwUserId, LPCTSTR lpLocalPathName, DWORD dwFlags, CHAR* lpUserString);
// ��ѯ�������������Ϣ����չ��
BRAC_API DWORD BRAC_QueryTransTaskInfoEx(CHAR* lpTaskGuid, int infoname, char FAR* infoval, int infolen);
// ȡ������������չ��
BRAC_API DWORD BRAC_CancelTransTaskEx(CHAR* lpTaskGuid, DWORD dwFlags, DWORD dwErrorCode);

// �����ı���Ϣ
BRAC_API DWORD BRAC_SendTextMessage(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);
// ����SDK Filter ͨ������
BRAC_API DWORD BRAC_SendSDKFilterData(LPBYTE lpBuf, DWORD dwLen);

// ���ĵ�ǰ������ģʽ
BRAC_API DWORD BRAC_ChangeChatMode(DWORD dwChatMode);
// ��ȡָ���û���ǰ������ģʽ
BRAC_API DWORD BRAC_GetUserChatMode(DWORD dwUserid, DWORD& dwChatMode);
// ������Է�˽�ģ���Է�����˽������
BRAC_API DWORD BRAC_PrivateChatRequest(DWORD dwUserid);
// �ظ��Է���˽������
BRAC_API DWORD BRAC_PrivateChatEcho(DWORD dwUserid, DWORD dwRequestid,BOOL bAccept);
// �ظ��Է���˽��������չ�����Ը���������룩
BRAC_API DWORD BRAC_PrivateChatEchoEx(DWORD dwUserid, DWORD dwRequestid,DWORD dwErrorCode);
// �˳���ĳ�û���˽�ģ����߽�ĳ�û����Լ���˽���б������
BRAC_API DWORD BRAC_PrivateChatExit(DWORD dwUserid);

// SDK�ں˲�������
BRAC_API DWORD BRAC_SetSDKOption(int optname, const char FAR* optval, int optlen);
// SDK�ں˲���״̬��ѯ
BRAC_API DWORD BRAC_GetSDKOption(int optname, char FAR* optval, int optlen);

// �鲥���ܿ���
BRAC_API DWORD BRAC_MultiCastControl(LPCTSTR lpMultiCastAddr, DWORD dwPort, LPCTSTR lpNicAddr, DWORD dwTTL, DWORD dwFlags);

// �����ⲿ������Ƶ��ʽ
BRAC_API DWORD BRAC_SetInputVideoFormat(BRAC_PixelFormat pixFmt, DWORD dwWidth, DWORD dwHeight, DWORD dwFps, DWORD dwFlags);
// �����ⲿ������Ƶ��ʽ����չ��
BRAC_API DWORD BRAC_SetInputVideoFormatEx(DWORD dwStreamIndex, DWORD dwCodecId, DWORD pixFmt, DWORD dwWidth, DWORD dwHeight, DWORD dwFps, DWORD dwFlags);
// �ⲿ��Ƶ��������
BRAC_API DWORD BRAC_InputVideoData(LPBYTE lpVideoFrame, DWORD dwSize, DWORD dwTimeStamp);
// �ⲿ��Ƶ�������루��չ��
BRAC_API DWORD BRAC_InputVideoDataEx(DWORD dwStreamIndex, LPBYTE lpVideoFrame, DWORD dwSize, DWORD dwTimeStamp, DWORD dwFlags);
// �����ⲿ������Ƶ��ʽ
BRAC_API DWORD BRAC_SetInputAudioFormat(DWORD dwChannels, DWORD dwSamplesPerSec, DWORD dwBitsPerSample, DWORD dwFlags);
// �����ⲿ������Ƶ��ʽ����չ��
BRAC_API DWORD BRAC_SetInputAudioFormatEx(DWORD dwStreamIndex, DWORD dwCodecId, DWORD dwChannels, DWORD dwSamplesPerSec, DWORD dwBitsPerSample, DWORD dwFlags);
// �ⲿ��Ƶ��������
BRAC_API DWORD BRAC_InputAudioData(LPBYTE lpSamples, DWORD dwSize, DWORD dwTimeStamp);
// �ⲿ��Ƶ�������루��չ��
BRAC_API DWORD BRAC_InputAudioDataEx(DWORD dwStreamIndex, LPBYTE lpSamples, DWORD dwSize, DWORD dwTimeStamp, DWORD dwFlags);

// ��ȡ��Ƶ��������
BRAC_API DWORD BRAC_FetchAudioPlayBuffer(LPBYTE lpSamples, DWORD dwSize, DWORD wParam);

// ���������̬��ѯ�����Ϣ
BRAC_API DWORD BRAC_QueryInfoFromServer(DWORD dwInfoName, TCHAR* lpInParam, DWORD dwInSize, TCHAR* lpResult, DWORD& dwOutSize, DWORD dwFlags=0);
// SDK����
BRAC_API DWORD BRAC_SDKControl(DWORD dwCtrlCode, CHAR* lpInParam, CHAR* lpResult, DWORD dwBufSize);

// ��Ƶ�����¼����ƣ����󡢻ظ����Ҷϵȣ�
BRAC_API DWORD BRAC_VideoCallControl(DWORD dwEventType, DWORD dwUserId, DWORD dwErrorCode, DWORD dwFlags=0, DWORD dwParam=0, LPCTSTR lpUserStr=NULL);

// ��ȡ�û�����ID�б�
BRAC_API DWORD BRAC_GetUserFriends(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// ��ȡ��������״̬
BRAC_API DWORD BRAC_GetFriendStatus(DWORD dwFriendUserId, DWORD& dwStatus);
// ��ȡ�û�����ID�б�
BRAC_API DWORD BRAC_GetUserGroups(LPDWORD lpGroupIDArray, DWORD& dwGroupNum);
// ��ȡ��������ĺ����б�
BRAC_API DWORD BRAC_GetGroupFriends(DWORD dwGroupId, LPDWORD lpUserIDArray, DWORD& dwUserNum);
// ��ȡ�û���Ϣ
BRAC_API DWORD BRAC_GetUserInfo(DWORD dwUserId, DWORD dwInfoId, TCHAR* lpInfoValue, DWORD dwLen);
// ��ȡ�û���������
BRAC_API DWORD BRAC_GetGroupName(DWORD dwGroupId, TCHAR* lpGroupName, DWORD dwLen);
// �û���Ϣ����
BRAC_API DWORD BRAC_UserInfoControl(DWORD dwUserId, DWORD dwCtrlCode, DWORD wParam=0, DWORD lParam=0, LPCTSTR lpStrValue=NULL);

// ��ȡ����ID�б�
BRAC_API DWORD BRAC_ObjectGetIdList(DWORD dwObjectType, LPDWORD lpIdArray, DWORD& dwIdNum);
// ��ȡ��������ֵ
BRAC_API DWORD BRAC_ObjectGetValue(DWORD dwObjectType, DWORD dwObjectId, DWORD dwInfoName, TCHAR* lpInfoValue, DWORD dwLen);
// ���ö�������ֵ
BRAC_API DWORD BRAC_ObjectSetValue(DWORD dwObjectType, DWORD dwObjectId, DWORD dwInfoName, TCHAR* lpInfoValue, DWORD dwLen);
// �����������
BRAC_API DWORD BRAC_ObjectControl(DWORD dwObjectType, DWORD dwObjectId, DWORD dwCtrlCode, DWORD dwParam1=0, DWORD dwParam2=0, DWORD dwParam3=0, DWORD dwParam4=0, LPCTSTR lpStrValue=NULL);

// ��ý�岥�ų�ʼ��
BRAC_API DWORD BRAC_StreamPlayInit(CHAR* lpTaskGuid, CHAR* lpStreamPath, DWORD dwFlags=0, CHAR* lpStrParam=NULL);
// ��ý�岥�ſ���
BRAC_API DWORD BRAC_StreamPlayControl(CHAR* lpTaskGuid, DWORD dwCtrlCode, DWORD dwParam=0, DWORD dwFlags=0, CHAR* lpStrParam=NULL);
// ��ý�岥��������Ƶ��ʾλ��
BRAC_API DWORD BRAC_StreamPlaySetVideoPos(CHAR* lpTaskGuid, HWND hWnd, DWORD dwLeft=0, DWORD dwTop=0, DWORD dwRight=0, DWORD dwBottom=0);
// ��ý�岥�Ż�ȡ������Ϣ
BRAC_API DWORD BRAC_StreamPlayGetInfo(CHAR* lpTaskGuid, DWORD dwInfoName, CHAR* infoValue, DWORD dwSize);
// ��ý�岥���ͷ���Դ
BRAC_API DWORD BRAC_StreamPlayDestroy(CHAR* lpTaskGuid, DWORD dwFlags=0);


#endif //BR_ANYCHAT_CORE_SDK_H__INCLUDED_
