//
//  AnyChatPlatform.h
//  AnyChat Platform Core SDK for iOS
//
//  Created by bairuitech on 11-8-2.
//  Copyright 2011 BaiRuiTech. All rights reserved.
//

#if !defined(_ANYCHAT_PLATFORM_H_INCLUDEDED_)
#define _ANYCHAT_PLATFORM_H_INCLUDEDED_

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>

#if !defined(BITMAPINFOHEADER_DEFINE)
#define BITMAPINFOHEADER_DEFINE
typedef struct tagBITMAPINFOHEADER {
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
}BITMAPINFOHEADER;
#endif

#if !defined(WAVEFORMATEX_DEFINE)
#define WAVEFORMATEX_DEFINE
typedef struct tagWAVEFORMATEX{
    short  wFormatTag;
    short  nChannels;
    int nSamplesPerSec;
    int nAvgBytesPerSec;
    short  nBlockAlign;
    short  wBitsPerSample;
    short  cbSize;
}WAVEFORMATEX,*LPWAVEFORMATEX;
#endif

/**
 *	AnyChat 异步消息事件协议
 */
@protocol AnyChatNotifyMessageDelegate <NSObject>
// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess;
// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode;
// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode;
// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId;
// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId;
// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId;
// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode;

@end

/**
 *	AnyChat 用户好友事件协议
 */
@protocol AnyChatUserInfoDelegate <NSObject>
// 用户信息更新通知，wParam（INT）表示用户ID号，lParam（INT）表示更新类别
- (void) OnAnyChatUserInfoUpdate:(int) dwUserId : (int) dwType;
// 好友在线状态变化，wParam（INT）表示好友用户ID号，lParam（INT）表示用户的当前活动状态：0 离线， 1 上线
- (void) OnAnyChatFriendStatus:(int) dwUserId : (int) dwStatus;
@end


/**
 *	AnyChat 状态改变事件协议
 */
@protocol AnyChatStateChangeDelegate <NSObject>
// 用户得到/释放mic消息
- (void) OnAnyChatMicStateChg:(int) dwUserId : (BOOL) bGetMic;
// 用户摄像头状态改变消息
- (void) OnAnyChatCameraStateChg:(int) dwUserId : (int) dwState;
// 用户活动状态发生变化消息
- (void) OnAnyChatActiveStateChg:(int) dwUserId : (int) dwState;
// P2P连接状态变化消息
- (void) OnAnyChatP2PConnectState:(int) dwUserId : (int) dwState;
// 用户视频分辨率改变消息
- (void) OnAnyChatVideoSizeChg:(int) dwUserId : (int) dwWidth : (int) dwHeight;
@end

/**
 *	AnyChat 私聊事件协议
 */
@protocol AnyChatPrivateChatDelegate <NSObject>
// 用户聊天模式改变消息
- (void) OnAnyChatChatModeChg:(int) dwUserId : (BOOL) bPublicChat;
// 用户私聊请求消息
- (void) OnAnyChatPrivateRequest:(int) dwUserId : (int) dwRequestId;
// 用户私聊请求回复消息
- (void) OnAnyChatPrivateEcho:(int) dwUserId : (int) dwErrorCode;
// 用户退出私聊消息
- (void) OnAnyChatPrivateExit:(int) dwUserId : (int) dwErrorCode;
@end

/**
 *	AnyChat 数据传输事件协议
 */
@protocol AnyChatTransDataDelegate <NSObject>
// 透明通道回调函数
- (void) OnAnyChatTransBufferCallBack:(int) dwUserid : (NSData*) lpBuf;
// 透明通道数据扩展回调函数
- (void) OnAnyChatTransBufferExCallBack:(int) dwUserid : (NSData*) lpBuf : (int) wParam : (int) lParam : (int) dwTaskId;
// 文件传输回调函数
- (void) OnAnyChatTransFileCallBack:(int) dwUserid : (NSString*) lpFileName : (NSString*) lpTempFilePath : (int) dwFileLength : (int) wParam : (int) lParam : (int) dwTaskId;
// SDK Filter 通信数据回调函数
- (void) OnAnyChatSDKFilterDataCallBack:(NSData*) lpBuf;
@end

/**
 *	AnyChat 文字消息事件协议
 */
@protocol AnyChatTextMsgDelegate <NSObject>
// 发送文字的回调函数
- (void) OnAnyChatTextMsgCallBack:(int) dwFromUserid : (int) dwToUserid : (BOOL) bSecret : (NSString*) lpMsgBuf;
@end

/**
 *	AnyChat 录像、拍照事件协议
 */
@protocol AnyChatRecordSnapShotDelegate <NSObject>
// 录像完成事件
- (void) OnAnyChatRecordCallBack:(int) dwUserid : (NSString*) lpFileName : (int) dwElapse : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr;
// 拍照完成事件
- (void) OnAnyChatSnapShotCallBack:(int) dwUserid : (NSString*) lpFileName : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr;
@end


/**
 *  AnyChat 音频、视频数据回调事件协议
 */
@protocol AnyChatMediaDataDelegate <NSObject>
// 视频数据回调
- (void) OnAnyChatVideoDataExCallBack:(int) dwUserid : (NSData*) lpBuf : (BITMAPINFOHEADER) bmiHeader : (int) dwTimeStamp;
// 音频数据回调
- (void) OnAnyChatAudioDataExCallBack:(int) dwUserid : (NSData*) lpBuf : (WAVEFORMATEX) waveFormatEx : (int) dwTimeStamp;
@end

/**
 *	视频呼叫回调事件协议
 */
@protocol AnyChatVideoCallDelegate <NSObject>
- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr;
@end

/**
 *	数据加密、解密回调事件协议
 */
 @protocol AnyChatDataEncDecDelegate <NSObject>
 - (void) OnAnyChatDataEncDecCallBack:(int) dwUserId : (int) dwFlags : (NSData*) lpInBuf : (NSData*) lpOutBuf;
@end


/**
 *	AnyChat for iOS API方法定义
 */
@interface AnyChatPlatform : NSObject {
    
    id<AnyChatNotifyMessageDelegate>    notifyMsgDelegate;
	id<AnyChatStateChangeDelegate>		stateChangeDelegate;
	id<AnyChatPrivateChatDelegate>		priateChatDelegate;
	id<AnyChatTransDataDelegate>		transDataDelegate;
	id<AnyChatTextMsgDelegate>			textMsgDelegate;
	id<AnyChatRecordSnapShotDelegate>	recordSnapShotDelegate;
    id<AnyChatMediaDataDelegate>        mediaDataDelegate;
	id<AnyChatVideoCallDelegate>		videoCallDelegate;
    id<AnyChatUserInfoDelegate>         userInfoDelegate;
	id<AnyChatDataEncDecDelegate>		dataEncDecDelegate;
}

@property (nonatomic, assign) id<AnyChatNotifyMessageDelegate>  	notifyMsgDelegate;
@property (nonatomic, assign) id<AnyChatStateChangeDelegate>		stateChangeDelegate;
@property (nonatomic, assign) id<AnyChatPrivateChatDelegate>		priateChatDelegate;
@property (nonatomic, assign) id<AnyChatTransDataDelegate>			transDataDelegate;
@property (nonatomic, assign) id<AnyChatTextMsgDelegate>			textMsgDelegate;
@property (nonatomic, assign) id<AnyChatRecordSnapShotDelegate>		recordSnapShotDelegate;
@property (nonatomic, assign) id<AnyChatMediaDataDelegate>          mediaDataDelegate;
@property (nonatomic, assign) id<AnyChatVideoCallDelegate>          videoCallDelegate;
@property (nonatomic, assign) id<AnyChatUserInfoDelegate>           userInfoDelegate;
@property (nonatomic, assign) id<AnyChatDataEncDecDelegate>			dataEncDecDelegate;

- (void) OnRecvAnyChatNotify:(NSDictionary*) dict;

// 获取SDK版本信息
+ (NSString*) GetSDKVersion;

// 激活（关闭）SDK调用日志
+ (int) ActiveCallLog: (BOOL) bActive;

// 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
+ (int) SetServerAuthPass: (NSString*) lpPassword;
// 初始化系统
+ (int) InitSDK: (int) dwFuncMode;


// 连接服务器
+ (int) Connect: (NSString*) lpServerAddr : (int) dwPort;
// 登录系统
+ (int) Login: (NSString*) lpUserName : (NSString*) lpPassword;
// 进入房间
+ (int) EnterRoom: (int) dwRoomid : (NSString*) lpRoomPass;
// 进入房间
+ (int) EnterRoomEx: (NSString*) lpRoomName : (NSString*) lpRoomPass;
// 离开房间
+ (int) LeaveRoom: (int) dwRoomid;
// 注销系统
+ (int) Logout;

// 释放所有资源
+ (int) Release;

// 获取当前房间在线用户列表
+ (NSMutableArray*) GetOnlineUser;
// 查询用户摄像头的状态
+ (int) GetCameraState: (int) dwUserid;
// 查询用户发言状态
+ (int) GetSpeakState: (int) dwUserid;
// 查询用户级别
+ (int) GetUserLevel: (int) dwUserid;
// 查询用户名称
+ (NSString*) GetUserName: (int) dwUserid;
// 查询用户IP
+ (NSString*) GetUserIPAddr: (int) dwUserid;
// 查询用户 Video Width
+ (int) GetUserVideoWidth: (int) dwUserid;
// 查询用户 Video Height
+ (int) GetUserVideoHeight: (int) dwUserid;
// 查询房间名称
+ (NSString*) GetRoomName: (int) dwRoomId;

// 查询指定用户相关状态
+ (NSString*) QueryUserStateString: (int) dwUserId : (int) infoname;
// 查询指定用户相关状态
+ (int) QueryUserStateInt: (int) dwUserId : (int) infoname;

// 枚举本地视频采集设备
+ (NSMutableArray*) EnumVideoCapture;
// 选择指定的视频采集设备
+ (int) SelectVideoCapture: (NSString*) szCaptureName;
// 获取当前使用的视频采集设备
+ (NSString*) GetCurVideoCapture;
// 枚举本地音频采集设备
+ (NSMutableArray*) EnumAudioCapture;
// 选择指定的音频采集设备
+ (int) SelectAudioCapture: (NSString*) szCaptureName;
// 获取当前使用的音频采集设备
+ (NSString*) GetCurAudioCapture;
// 枚举本地音频播放设备
+ (NSMutableArray*) EnumAudioPlayback;
// 选择指定的音频播放设备
+ (int) SelectAudioPlayback: (NSString*) szDeviceName;
// 获取当前使用的音频播放设备
+ (NSString*) GetCurAudioPlayback;

// 操作用户视频
+ (int) UserCameraControl: (int) dwUserid : (BOOL) bOpen;
// 操作用户语音
+ (int) UserSpeakControl: (int) dwUserid : (BOOL) bOpen;
// 设置视频显示位置
+ (int) SetVideoPos: (int) dwUserid : (NSObject*) surface : (int) left : (int) top : (int) width : (int) height;


// 获取指定音频设备的当前音量
+ (int) AudioGetVolume:(int) device;
// 设置指定音频设备的音量
+ (int) AudioSetVolume:(int) device : (int) dwVolume;

// 用户音、视频录制
+ (int) StreamRecordCtrl: (int) dwUserId : (BOOL) bStartRecord : (int) dwFlags : (int) dwParam;
// 用户音、视频录制(扩展)
+ (int) StreamRecordCtrlEx: (int) dwUserId : (BOOL) bStartRecord : (int) dwFlags : (int) dwParam : (NSString*)lpUserStr;
// 对用户的视频进行抓拍（快照）
+ (int) SnapShot: (int) dwUserId : (int) dwFlags : (int) dwParam;

// 透明通道传送缓冲区
+ (int) TransBuffer: (int) dwUserid : (NSData*) lpBuf;
// 透明通道传送缓冲区扩展
+ (int) TransBufferEx: (int) dwUserid : (NSData*) lpBuf : (int) wParam : (int) lParam : (int) dwFlags;
// 传送文件
+ (int) TransFile: (int) dwUserid : (NSString*) lpLocalPathName : (int) wParam : (int) lParam : (int) dwFlags;
// 查询传输任务相关信息
+ (int) QueryTransTaskInfoInt: (int) dwUserid : (int) dwTaskId : (int) infoname;
// 取消传输任务
+ (int) CancelTransTask: (int) dwUserid : (int) dwTaskId;
// 传送文本消息
+ (int) SendTextMessage: (int) dwUserid : (BOOL) bSecret : (NSString*) lpMsgBuf;
// 发送SDK Filter 通信数据
+ (int) SendSDKFilterData: (NSData*) lpBuf;

// 更改当前的聊天模式
+ (int) ChangeChatMode: (int) dwChatMode;
// 获取指定用户当前的聊天模式
+ (int) GetUserChatMode: (int) dwUserid;
// 请求与对方私聊，向对方发起私聊请求
+ (int) PrivateChatRequest: (int) dwUserid;
// 回复对方的私聊请求
+ (int) PrivateChatEcho: (int) dwUserid : (int) dwRequestid : (BOOL) bAccept;
// 回复对方的私聊请求（扩展，可以附带出错代码）
+ (int) PrivateChatEchoEx: (int) dwUserid : (int) dwRequestid : (int) dwErrorCode;
// 退出与某用户的私聊，或者将某用户从自己的私聊列表中清除
+ (int) PrivateChatExit: (int) dwUserid;

// SDK内核参数设置
+ (int) SetSDKOptionInt:(int) optname : (int) value;
// SDK内核参数设置
+ (int) SetSDKOptionString:(int) optname : (NSString*) value;
// SDK内核参数状态查询
+ (int) GetSDKOptionInt:(int) optname;
// SDK内核参数状态查询
+ (NSString*) GetSDKOptionString:(int) optname;

// 组播功能控制
+ (int) MultiCastControl: (NSString*) lpMultiCastAddr : (int) dwPort : (NSString*) lpNicAddr : (int) dwTTL : (int) dwFlags;

// 设置外部输入视频格式
+ (int) SetInputVideoFormat: (int) pixFmt : (int) dwWidth : (int) dwHeight : (int) dwFps : (int) dwFlags;
// 外部视频数据输入
+ (int) InputVideoData: (NSData*) lpVideoFrame : (int) dwTimeStamp;
// 设置外部输入音频格式
+ (int) SetInputAudioFormat: (int) dwChannels : (int) dwSamplesPerSec : (int) dwBitsPerSample : (int) dwFlags;
// 外部音频数据输入
+ (int) InputAudioData: (NSData*) lpSamples : (int) dwTimeStamp;

// 视频呼叫事件控制（请求、回复、挂断等）
+ (int) VideoCallControl: (int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr;


// 获取用户好友ID列表
+ (NSMutableArray*) GetUserFriends;
// 获取好友在线状态
+ (int) GetFriendStatus: (int) dwFriendUserId;
// 获取用户分组ID列表
+ (NSMutableArray*) GetUserGroups;
// 获取分组下面的好友列表
+ (NSMutableArray*) GetGroupFriends: (int) dwGroupId;
// 获取用户信息
+ (NSString*) GetUserInfo: (int) dwUserId : (int) dwInfoId;
// 获取用户分组名称
+ (NSString*) GetGroupName: (int) dwGroupId;
// 用户信息控制
+ (int) UserInfoControl: (int) dwUserId : (int) dwCtrlCode : (int) wParam : (int) lParam : (NSString*) lpStrValue;



@end







#endif //_ANYCHAT_PLATFORM_H_INCLUDEDED_
