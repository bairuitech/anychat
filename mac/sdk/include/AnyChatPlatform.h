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
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#   import <UIKit/UIKitDefines.h>
#   import <UIKit/UIView.h>
#else
#   import <AppKit/AppKitDefines.h>
#   import <AppKit/NSView.h>
#endif

#include "AnyChatDefine.h"
#include "AnyChatErrorCode.h"
#include "AnyChatObjectDefine.h"

#if !defined(BITMAPINFOHEADER_DEFINE)
#define BITMAPINFOHEADER_DEFINE
typedef struct tagBITMAPINFOHEADER {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
}__attribute__((packed)) BITMAPINFOHEADER;
#endif

#if !defined(WAVEFORMATEX_DEFINE)
#define WAVEFORMATEX_DEFINE
typedef struct tagWAVEFORMATEX{
    uint16_t  wFormatTag;
    uint16_t  nChannels;
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t  nBlockAlign;
    uint16_t  wBitsPerSample;
    uint16_t  cbSize;
}__attribute__((packed)) WAVEFORMATEX,*LPWAVEFORMATEX;
#endif


/**
 *	AnyChat 异步消息事件协议
 */
@protocol AnyChatNotifyMessageDelegate <NSObject>
@optional
/**
 *  连接服务器消息
 *
 *  @param bSuccess 是否连接成功
 */
- (void)OnAnyChatConnect:(BOOL) bSuccess;
/**
 *  用户登陆消息
 *
 *  @param dwUserId    用户的ID
 *  @param dwErrorCode 错误码
 */
- (void) OnAnyChatLogin:(int) dwUserId :(int) dwErrorCode;

/**
 *  用户进入房间消息
 *
 *  @param dwRoomId    房间号
 *  @param dwErrorCode 错误码
 */
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode;
/**
 *  房间在线用户消息
 *
 *  @param dwUserNum 房间用户的人数
 *  @param dwRoomId  房间号
 */
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId;
/**
 *  用户进入房间消息
 *
 *  @param dwUserId 用户的ID
 */
- (void) OnAnyChatUserEnterRoom:(int) dwUserId;
/**
 *  用户离开房间消息
 *
 *  @param dwUserId 用户的ID
 */

- (void) OnAnyChatUserLeaveRoom:(int) dwUserId;

/**
 *  网络断开的消息
 *
 *  @param dwErrorCode 错误码
 */
- (void) OnAnyChatLinkClose:(int) dwErrorCode;

@end

/**
 *	AnyChat 用户好友事件协议
 */
@protocol AnyChatUserInfoDelegate <NSObject>
/**
 *  用户信息更新通知
 *
 *  @param dwUserId (INT）用户ID号
 *  @param dwType   (INT)更新类别
 */
- (void) OnAnyChatUserInfoUpdate:(int) dwUserId : (int) dwType;

/**
 *  好友在线状态变化
 *
 *  @param dwUserId  (INT）好友用户ID号
 *  @param dwStatus （INT）用户的当前活动状态：0 离线， 1 上线
 */
- (void)OnAnyChatFriendStatus:(int) dwUserId : (int) dwStatus;
@end


/**
 *	AnyChat 状态改变事件协议
 */
@protocol AnyChatStateChangeDelegate <NSObject>

/**
 *  用户得到/释放mic消息
 *
 *  @param dwUserId  状态变化的用户 ID
 *  @param bGetMic   该用户是否已打开音频采集设备
 */
- (void) OnAnyChatMicStateChg:(int) dwUserId : (BOOL) bGetMic;

/**
 *  视频设备状态改变事件
 *
 *  @param dwUserId  状态变化的用户 ID
 *  @param dwState   该用户当前的视频设备状态:0  没有摄像头设备
 1  有摄像头设备,但没有打开
 2  已打开摄像头设备
 */
- (void) OnAnyChatCameraStateChg:(int) dwUserId : (int) dwState;
/**
 *  用户活动状态发生变化消息
 *
 *  @param dwUserId  状态变化的用户 ID
 *  @param dwState   表示该用户当前的活动状态:
 */
- (void) OnAnyChatActiveStateChg:(int) dwUserId : (int) dwState;
/**
 *  用户P2P连接改变事件 : 当进入房间成功之后,与其它用户建立 P2P 连接,或是 P2P 连接被断开 时触发该接口
 *
 *  @param dwUserId  其它用户 ID 号
 *  @param dwState   本地用户与其它用户的当前 P2P 网络连接状态:
 0:没有任何连接
 1:P2P 连接成功,TCP 连接
 2:P2P 连接成功,UDP 连接
 3:P2P 连接成功,TCP 与 UDP 连接
 */
- (void) OnAnyChatP2PConnectState:(int) dwUserId : (int) dwState;
/**
 *  用户视频大小改变事件 : 当进入房间成功之后,成功打开本地视频设备,或是修改视频设备采集分 辨率之后将触发该接口
 *
 *  @param dwUserId  状态变化的用户 ID
 *  @param dwWidth  该用户当前的视频宽度
 *  @param dwHeight 表示该用户当前的视频高度
 */
- (void) OnAnyChatVideoSizeChg:(int) dwUserId : (int) dwWidth : (int) dwHeight;
@end

/**
 *	AnyChat 私聊事件协议
 */
@protocol AnyChatPrivateChatDelegate <NSObject>
/**
 *  用户聊天模式改变消息
 *
 *  @param dwUserId    聊天模式变化的用户 ID
 *  @param bPublicChat 是否是公共聊天
 */
- (void) OnAnyChatChatModeChg:(int) dwUserId : (BOOL) bPublicChat;

/**
 *  用户私聊请求消息
 *
 *  @param dwUserId    私聊请求的用户ID
 *  @param dwRequestId
 */
- (void) OnAnyChatPrivateRequest:(int) dwUserId : (int) dwRequestId;

/**
 *  用户私聊请求回复消息
 *
 *  @param dwUserId     私聊请求的用户ID
 *  @param dwErrorCode
 */
- (void) OnAnyChatPrivateEcho:(int) dwUserId : (int) dwErrorCode;

/**
 *  用户退出私聊消息
 *
 *  @param dwUserId    私聊请求的用户ID
 *  @param dwErrorCode <#dwErrorCode description#>
 */
- (void) OnAnyChatPrivateExit:(int) dwUserId : (int) dwErrorCode;
@end

/**
 *	AnyChat 数据传输事件协议
 */
@protocol AnyChatTransDataDelegate <NSObject>
@optional
/**
 *  收到透明通道数据事件 : 当收到其它用户使用“TransBuffer”方法发送的缓冲区数据时,将会触发该
 接口,等同于回调函数:BRAC_TransBuffer_CallBack。 由于该函数传递的数据是一个与本 SDK 无关的缓冲区(由上层应用自己填
 充内容),相对于本 SDK 来说是透明的,故称为透明通道,利用该通道,可以向 当前房间内的任何用户传输上层应用自定义的数据。
 *
 *  @param dwUserid 用户 ID,指示发送用户
 *  @param lpBuf    缓冲区地址
 */
- (void) OnAnyChatTransBufferCallBack:(int) dwUserid : (NSData*) lpBuf;
/**
 *  收到扩展透明通道数据事件 ： 当收到其它用户使用“TransBufferEx”方法发送的缓冲区数据时,将会触发该接口,等同于回调函数:BRAC_TransBufferEx_CallBack
 *
 *  @param dwUserid 用户 ID,指示发送用户
 *  @param lpBuf    缓冲区地址
 *  @param wParam   缓冲区附带参数(有发送者设置，上层应用可自定义用途)
 *  @param lParam   缓冲区附带参数2
 *  @param dwTaskId 该缓冲区所对应的传输任务编号
 */
- (void) OnAnyChatTransBufferExCallBack:(int) dwUserid : (NSData*) lpBuf : (int) wParam : (int) lParam : (int) dwTaskId;
// 文件传输回调函数
/**
 *  收到文件传输数据事件 : 当收到其它用户使用“TransFile”方法发送的文件时,将会触发该接口,等同于回调函数:BRAC_TransFile_CallBack。
 特别提示:本 SDK 不会删除“lpTempFilePath”所指示的临时文件,上层应用在处理完毕后,需要主动删除该临时文件。
 *
 *  @param dwUserid       用户 ID,指示发送用户
 *  @param lpFileName     文件名(含扩展名,不含路径)
 *  @param lpTempFilePath 接收完成后,SDK 保存在本地的临时文件(包含完整路 径)
 *  @param dwFileLength   文件总长度
 *  @param wParam         附带参数 1
 *  @param lParam         附带参数 2
 *  @param dwTaskId       该文件所对应的任务编号
 */
- (void) OnAnyChatTransFileCallBack:(int) dwUserid : (NSString*) lpFileName : (NSString*) lpTempFilePath : (int) dwFileLength : (int) wParam : (int) lParam : (int) dwTaskId;
// SDK Filter 通信数据回调函数
/**
 *  收到SDK Filter数据事件
 *
 *  @param lpBuf 缓冲区地址
 */
- (void) OnAnyChatSDKFilterDataCallBack:(NSData*) lpBuf;
@end

/**
 *	AnyChat 文字消息事件协议
 */
@protocol AnyChatTextMsgDelegate <NSObject>
// 发送文字的回调函数
/**
 *   收到文字聊天消息事件 : 当进入房间成功之后,收到其他用户发送的文字聊天信息时将触发该接口, 等同于 WIN32 平台的回调函数:BRAC_TextMessage_CallBack。本地用户向其 它用户发送文字消息时,将不会触发该接口。
 *
 *  @param dwFromUserid 消息发送者用户 ID
 *  @param dwToUserid   目标用户,-1 表示发送给大家,即房间所有人
 *  @param bSecret      是否为悄悄话,当目标用户不为-1 时有效
 *  @param lpMsgBuf     消息字符串
 */
- (void) OnAnyChatTextMsgCallBack:(int) dwFromUserid : (int) dwToUserid : (BOOL) bSecret : (NSString*) lpMsgBuf;
@end

/**
 *	AnyChat 录像、拍照事件协议
 */
@protocol AnyChatRecordSnapShotDelegate <NSObject>

/**
 *  视频录制完成事件
 *
 *  @param dwUserid    被录制用户 ID
 *  @param dwErrorCode <#dwErrorCode description#>
 *  @param lpFileName  文件保存路径
 *  @param dwElapse    录像时长,单位:秒
 *  @param dwFlags     录像标志
 *  @param dwParam     用户自定义参数,整型
 *  @param lpUserStr   用户自定义参数,字符串类型
 */
- (void) OnAnyChatRecordCallBack:(int) dwUserid : (int) dwErrorCode : (NSString*) lpFileName : (int) dwElapse : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr;

/**
 *  拍照完成事件
 *
 *  @param dwUserid    被拍照用户 ID
 *  @param dwErrorCode <#dwErrorCode description#>
 *  @param lpFileName  文件保存路径
 *  @param dwFlags     拍照标志
 *  @param dwParam     用户自定义参数,整型
 *  @param lpUserStr   用户自定义参数,字符串类型
 */
- (void) OnAnyChatSnapShotCallBack:(int) dwUserid : (int) dwErrorCode : (NSString*) lpFileName : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr;
@end


/**
 *  AnyChat 音频、视频数据回调事件协议
 */
@protocol AnyChatMediaDataDelegate <NSObject>

/**
 *  视频数据回调
 *
 *  @param dwUserid    用户ID
 *  @param lpBuf       缓冲区地址
 *  @param bmiHeader   <#bmiHeader description#>
 *  @param dwTimeStamp 整形值,签名的时间戳,由签名工具返回
 */
- (void) OnAnyChatVideoDataExCallBack:(int) dwUserid : (NSData*) lpBuf : (BITMAPINFOHEADER) bmiHeader : (int) dwTimeStamp;

/**
 *  音频数据回调
 *
 *  @param dwUserid     用户ID
 *  @param lpBuf        缓冲区地址
 *  @param waveFormatEx <#waveFormatEx description#>
 *  @param dwTimeStamp  整形值,签名的时间戳,由签名工具返回
 */
- (void) OnAnyChatAudioDataExCallBack:(int) dwUserid : (NSData*) lpBuf : (WAVEFORMATEX) waveFormatEx : (int) dwTimeStamp;
@end

/**
 *	视频呼叫回调事件协议
 */
@protocol AnyChatVideoCallDelegate <NSObject>
/**
 *  视频呼叫事件
 *
 *  @param dwEventType 呼叫事件类型,详见函数 BRAC_VideoCallControl 中的定义
 *  @param dwUserId    视频呼叫事件发起方用户 ID
 *  @param dwErrorCode 错误代码,当事件类型为“Reply”和“Finish”时有效
 *  @param dwFlags     视频呼叫标志
 *  @param dwParam     事件附带参数(整型)
 *  @param lpUserStr   事件附带参数(字符串)
 */
- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr;
@end
@protocol AnyChatDataEncDecDelegate <NSObject>
/**
 *  数据加密、解密回调事件协议
 *
 *  @param dwUserId 加密的数据的用户ID
 *  @param dwFlags  加密标志
 *  @param lpInBuf  输入缓冲区地址
 *  @param lpOutBuf 输出缓冲区地址
 */
- (void) OnAnyChatDataEncDecCallBack:(int) dwUserId : (int) dwFlags : (NSData*) lpInBuf : (NSData*) lpOutBuf;
@end

/**
 *  业务对象事件协议
 */
@protocol AnyChatObjectEventDelegate <NSObject>
/**
 *  业务对象完成事件
 *
 *  @param dwObjectType 业务对象类型,见3.6.1.1章节描述内容;
 *  @param dwObjectId   业务对象 ID
 *  @param dwEventType  业务对象回调事件类型,见3.6.4 章节描述内容;
 *  @param dwParam1     整型参数值一(需要和业务事件类型参数值匹配)
 *  @param dwParam2     整型参数值二(需要和业务事件类型参数值匹配)
 *  @param dwParam3     整型参数值三(需要和业务事件类型参数值匹配)
 *  @param dwParam4     整型参数值四(需要和业务事件类型参数值匹配)
 *  @param lpStrParam   字符串参数值(需要和业务事件类型参数值匹配)
 */
- (void) OnAnyChatObjectEventCallBack: (int) dwObjectType : (int) dwObjectId : (int) dwEventType : (int) dwParam1 : (int) dwParam2 : (int) dwParam3 : (int) dwParam4 : (NSString*) lpStrParam;
@end


/**
 *	AnyChat for iOS API方法定义
 */
@interface AnyChatPlatform : NSObject {

}

@property (nonatomic, weak) id<AnyChatNotifyMessageDelegate>  	notifyMsgDelegate;
@property (nonatomic, weak) id<AnyChatStateChangeDelegate>		stateChangeDelegate;
@property (nonatomic, weak) id<AnyChatPrivateChatDelegate>		priateChatDelegate;
@property (nonatomic, weak) id<AnyChatTransDataDelegate>		transDataDelegate;
@property (nonatomic, weak) id<AnyChatTextMsgDelegate>			textMsgDelegate;
@property (nonatomic, weak) id<AnyChatRecordSnapShotDelegate>	recordSnapShotDelegate;
@property (nonatomic, weak) id<AnyChatMediaDataDelegate>        mediaDataDelegate;
@property (nonatomic, weak) id<AnyChatVideoCallDelegate>        videoCallDelegate;
@property (nonatomic, weak) id<AnyChatUserInfoDelegate>         userInfoDelegate;
@property (nonatomic, weak) id<AnyChatDataEncDecDelegate>       dataEncDecDelegate;
@property (nonatomic, weak) id<AnyChatObjectEventDelegate>      objectDelegate;

- (void) OnRecvAnyChatNotify:(NSDictionary*) dict;

// 获取单例对象
+ (AnyChatPlatform *) getInstance;

// 获取SDK版本信息
+ (NSString*) GetSDKVersion;

/**
 *  激活(关闭)SDK调用日志 : 打开,或是关闭 SDK 调用期间所产生的日志
 *
 *  @param bActive 是否打开日志功能
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) ActiveCallLog: (BOOL) bActive;

// 设置服务器验证密码（可用于阻止非法用户用SDK连接服务器，合法用户可正常连接）
+ (int) SetServerAuthPass: (NSString*) lpPassword;
// 初始化系统
+ (int) InitSDK: (int) dwFuncMode;


// 连接服务器
// 第一个参数为你需要连接的 AnyChat 核心服务器地址,如果您部署 AnyChat 核心服务器 的地址为 192.168.1.8,则传入这个地址;第二个参数为端口号
/**
 *  连接服务器 : 用于与服务器建立连接。
 *
 *  @param lpServerAddr 服务器 IP 地址,或是网站域名(URL)地址
 *  @param dwPort       服务端口号(默认为 8906)
 *
 *  返回值为 0 并不表示连接服务器成功,仅表示 SDK 已成功收到连接服务器的 指令,如果连接成功,或是失败,都将会通过相应的接口通知上层应用,这里是 一个异步的过程。
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) Connect: (NSString*) lpServerAddr : (int) dwPort;
/**
 *   登录系统
 *
 *  @param lpUserName 注册用户名;
 *  @param lpPassword 登录密码(为空表示游客);
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) Login: (NSString*) lpUserName : (NSString*) lpPassword;
/**
 *  登录扩展接口,支持用户身份验证签名后进行登录。
 *
 *  @param lpNickName  字符串值,用户显示名称
 *  @param dwUserId    整形值,用户 Id 值,如果应用没有此参数,则传入-1
 *  @param lpStrUserId 字符串值,用户编号,如果 dwUserId 参数有值,则此参 数值可为传空字符串;如果 dwUserId 为-1,则需要传此 参数值
 *  @param lpAppId     字符串值，在集群版本、视频云平台申请的应用ID
 *  @param dwTimeStamp 整形值,签名的时间戳,由签名工具返回
 *  @param lpSigStr    字符串值,使用应用的公钥和私钥进行签名后生成的签名字符串
 *  @param lpStrParam  字符串值,预留参数,传空字符串
 *
 *  @return 0 表示成功,否则为出错代码;
 *
 * 说明：此接口用于用户在自有的或第三方的身份验证系统验证后,根据获取的应用 公钥和设置的私钥数据,再调用 AnyChat 提供的或自己编写的身份签名工具对用 户进行身份签名。签名后再调用此接口进行登录;通过该接口后则不需要再由 AnyChat 业务服务器进行身份验证了。
 如果在系统或应用中设置了允许用户以游客的身份进行登录,则该接口也可 以不用验证用户身份签名,允许用户登录系统
 */
+ (int) LoginEx: (NSString*) lpNickName : (int) dwUserId : (NSString*) lpStrUserId : (NSString*) lpAppId : (int) dwTimeStamp : (NSString*) lpSigStr : (NSString*) lpStrParam;
/**
 *  进入房间(根据房间编号)
 *
 *  @param dwRoomid   房间编号,系统唯一;
 *  @param lpRoomPass 房间密码(当房间需要密码时有效,如果没有可为空);
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) EnterRoom: (int) dwRoomid : (NSString*) lpRoomPass;
/**
 *  根据房间名称进入房间
 *
 *  @param lpRoomName 房间名称
 *  @param lpRoomPass 房间密码(当房间需要密码时有效,如果没有可为空);
 *
 *  @return 0 表示成功,否则为出错代码
 *
 *  该方法与“EnterRoom”功能相同,区别在于房间的标识不同,其中 “EnterRoom”是用房间 ID 进入房间,而该方法是用房间名称进入房间,如果 房间不存在,而且系统配置为自动创建房间时,将会由系统分配一个唯一的房间 编号,通过异步消息事件接口(AnyChatNotifyMessageDelegate)返回给上层应用, 上层应用可以通过方法“GetRoomName”来获取房间名称。
 */
+ (int) EnterRoomEx: (NSString*) lpRoomName : (NSString*) lpRoomPass;
/**
 *  离开房间 : 在用户变换房间之前,需要调用该方法离开房间,然后才能进入新的房间。
 *
 *  @param dwRoomid 房间编号,为-1 表示退出当前房间
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) LeaveRoom: (int) dwRoomid;
/**
 *  注销系统
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) Logout;
/**
 *  释放 SDK 占用的所有资源
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) Release;
/**
 *  在线用户 ID 数组
 *
 *  @return 在线用户 ID 数组
 *
 *  获取在线用户列表,并不包 当前用户自己的 ID,自己的 ID 在登录事件 (AnyChatNotifyMessageDelegate)中已通知给上层应用。
 */
+ (NSMutableArray*) GetOnlineUser;
/**
 *  获取指定房间在线用户列表
 *
 *  @param dwRoomId 整形值,房间编号;
 *
 *  @return 返回房间在线用户 ID 数组
 *
 *  获取指定房间在线用户列表,接口调用后会返回在线用户 ID 数组。
 */
+ (NSMutableArray*) GetRoomOnlineUsers: (int) dwRoomId;
/**
 *  查询用户摄像头的状态
 *
 *  @param dwUserid 用户编号,为-1 时表示获取自己的摄像头状态;
 *
 *  @return 返回指定用户的摄像头状态,定义为:
 0 没有摄像头
 1 有摄像头但没有打开
 2 摄像头已打开
 *
 *备注:该方法必须在登录系统之后调用方有效，根据返回参数的不同，可以判断用户当前摄像头的状态,以及判断用户是否有摄像头。
 */
+ (int) GetCameraState: (int) dwUserid;
/**
 *  查询用户音频设备采集状态
 *
 *  @param dwUserid 用户编号,为-1 时表示获取自己的音频设备状态;
 *
 *  @return 返回指定用户的音频设备状态,定义为:
 0 音频采集关闭
 1 音频采集开启
 *
 *  这里所说的“音频设备采集状态”是指在 SDK 内部是否已开始音频采集, 当返回值为 1 时,表示 SDK 已经开始采集,当有其它用户请求时,才对外传输。
 关于实际应用中的“公麦”、“麦序”等属于业务逻辑范畴,具体的实现方式 可参考《AnyChat Server SDK 开发指南》中“常用业务处理逻辑”的章节。
 
 */
+ (int) GetSpeakState: (int) dwUserid;
/**
 *  查询用户级别
 *
 *  @param dwUserid  用户编号,为-1 时表示获取自己的用户级别
 *
 *  @return 用户级别
 */
+ (int) GetUserLevel: (int) dwUserid;
/**
 *  查询用户用户昵称
 *
 *  @param dwUserid 用户编号,为-1 时表示获取自己的 昵称;
 *
 *  @return 用户昵称 字符串
 *
 *  这里所查询到的用户昵称，是用户在身份验证时，服务器端调用SDK Filter的“BRGS_VerifyUser”方法时，由SDK Filter返回给服务器的lpNickName参数值，如果lpNickName为空，则默认采用登录用户名替代用户昵称。
 */
+ (NSString*) GetUserName: (int) dwUserid;
/**
 *  查询用户互联网 IP 地址
 *
 *  @param dwUserid 用户编号,为-1 时表示获取自己的 IP 地址;
 *
 *  @return 用户 IP 字符串
 *
 *  这里所查询到的用户 IP 为互联网 IP 地址,可能是用户本机的真实 IP,也可 能是用户接入互联网的网关 IP 地址。
 */
+ (NSString*) GetUserIPAddr: (int) dwUserid;
/**
 *  查询用户视频分辨率的宽度值
 *
 *  @param dwUserid 用户编号,为-1 时表示获取自己的视频宽度;
 *
 *  @return 返回指定用户的视频宽度,如果用户视频没有打开,或是打开视频设备 失败,则获取的值为 0
 *
 *  如查询本地的视频宽度值,则必须在打开本地视频设备成功之后方能查询成 功;如查询其它用户的视频宽度值,则必须在对方打开视频设备成功,且状态同 步到本地后,才能查询成功,故上层应用可用一个定时器间隔查询。
 */
+ (int) GetUserVideoWidth: (int) dwUserid;
/**
 *  查询用户视频分辨率的高度值
 *
 *  @param dwUserid 用户编号,为-1 时表示获取自己的视频高度;
 *
 *  @return 返回指定用户的视频高度,如果用户视频没有打开,或是打开视频设备 失败,则获取的值为 0
 *
 *  如查询本地的视频高度值,则必须在打开本地视频设备成功之后方能查询成 功;如查询其它用户的视频高度值,则必须在对方打开视频设备成功,且状态同 步到本地后,才能查询成功,故上层应用可用一个定时器间隔查询。
 */
+ (int) GetUserVideoHeight: (int) dwUserid;
/**
 *  查询根据房间 ID 获取房间名称 : 目前只能查询当前所在房间的房间名称,当用户离开房间后,查询将会失败。
 *
 *  @param dwRoomId 房间编号;
 *
 *  @return 返回房间名称,如查询失败,则返回空字符串
 */
+ (NSString*) GetRoomName: (int) dwRoomId;
/**
 *  查询指定用户状态(字符串类型) : 通过调用该方法,可以查询指定用户的相关状态值。
 *
 *  @param dwUserId 用户编号,可用-1 代表本地用户(自己)
 *  @param infoname 需要查询的信息代码(见 WIN32 平台 SDK 相关定义)
 *
 *  @return 相关状态的字符串
 */
+ (NSString*) QueryUserStateString: (int) dwUserId : (int) infoname;
/**
 *  查询指定用户状态(字符串类型) : 通过调用该方法,可以查询指定用户的相关状态值
 *
 *  @param dwUserId 用户编号,可用-1 代表本地用户(自己);
 *  @param infoname 需要查询的信息代码(见 WIN32 平台 SDK 相关定义)
 *
 *  @return 相关状态值
 */
+ (int) QueryUserStateInt: (int) dwUserId : (int) infoname;
#pragma mark - 系统设置
/**
 *  :枚举本地视频采集设备
 *
 *  @return 返回设备列表
 */
+ (NSMutableArray*) EnumVideoCapture;
/**
 *  选择指定的视频采集设备 ： 当用户有多个视频采集设备时,可以通过该方法选用指定的视频采集设备。 采集设备名称必须是调用“EnumVideoCapture”方法枚举得到。
 *
 *  @param szCaptureName 所获取设备的名称;
 *
 *  @return 0 表示成功,否则为出错代码
 *
 *  当设备没有打开时,返回空值。
 */
+ (int) SelectVideoCapture: (NSString*) szCaptureName;

/**
 *  获取当前使用的视频采集设备名称
 *
 *  @return 当前已打开的视频采集设备名称
 */
+ (NSString*) GetCurVideoCapture;

/**
 *  枚举本地音频采集设备
 *
 *  @return 返回设备列表
 */
+ (NSMutableArray*) EnumAudioCapture;

/**
 *  选择指定的音频采集设备 ： 当用户有多个音频采集设备时,可以通过该方法选用指定的音频采集设备。 采集设备名称必须是调用“EnumAudioCapture”方法枚举得到。
 *
 *  @param szCaptureName 0 表示成功,否则为出错代码
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) SelectAudioCapture: (NSString*) szCaptureName;

/**
 *  获取当前使用的音频采集设备 ： 获取当前使用的音频采集设备
 *
 *  @return 当前已打开的音频采集设备名称
 */
+ (NSString*) GetCurAudioCapture;

/**
 *  枚举本地音频采集设备 ： iPhone 设备有两个播放设备:Receiver( 筒)、Speaker(喇叭)。AnyChat
 默认使用 Speaker 播放声音,如需转到 Receiver 则需要进行选择
 *
 *  @return 返回设备列表
 */
+ (NSMutableArray*) EnumAudioPlayback;

/**
 *  选择指定的音频播放设备 ： 可以通过该方法选用指定的音频播放设备,在 Receiver 和 Speaker 之间切换。 播放设备名称必须是调用“EnumAudioPlayback”方法枚举得到。
 *
 *  @param szDeviceName 播放设备名称;
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) SelectAudioPlayback: (NSString*) szDeviceName;

/**
 *  获取当前使用的音频播放设备
 *
 *  @return 当前已打开的音频播放设备名称 ： 当设备没有打开时,返回空值
 */
+ (NSString*) GetCurAudioPlayback;

/**
 *  用户视频控制,打开或关闭本地摄像头,或请求对方的视频 ： 用户视频控制,打开或关闭本地摄像头,或请求对方的视频
 *
 *  @param dwUserid 用户编号,为-1 表示对本地视频进行控制
 *  @param bOpen    是否打开视频
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) UserCameraControl: (int) dwUserid : (BOOL) bOpen;

/**
 *  用户音频控制 ： 对于本地用户,该方法是直接操作用户的 Mic,而对于其它用户,该方法只 是向对方发送一个请求(取消)音频流的申请,并不会直接操作对方的 Mic。
 *
 *  @param dwUserid 用户编号,为-1 表示对本地发言进行控制
 *  @param bOpen    是否允许用户发言,当 dwUserid=-1 时,1 表示请求发言(拿 Mic),0 表示停止发言(放 Mic)
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) UserSpeakControl: (int) dwUserid : (BOOL) bOpen;

/**
 *  设置视频显示位置,或是刷新视频显示
 *
 *  @param dwUserid 用户编号,为-1 表示操作自己的视频显示位置
 *  @param surface  视频显示对象
 *  @param left     位置信息,默认为 0
 *  @param top      位置信息,默认为 0
 *  @param width    位置信息,默认为 0
 *  @param height   位置信息,默认为 0
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) SetVideoPos: (int) dwUserid : (NSObject*) surface : (int) left : (int) top : (int) width : (int) height;


/**
 *  获取指定音频设备的当前音量 ： 根据设备类型(device)参数的不同,可以获取放音设备(WaveOut)和录音
 设备(WaveIn)的当前音量大小。
 *
 *  @param device 设备类型,定义为:
 AD_WAVEIN  = 0,    ///< 输入设备:Mic
 AD_WAVEOUT = 1,    ///< 输出设备:Wave
 dwVolume 保存该设备的当前音量,取值范围:0~100;
 *
 *  @return 当前音量大小
 */
+ (int) AudioGetVolume:(int) device;

/**
 *   获取指定音频设备的当前音量 ： 根据设备类型(device)参数的不同,可以获取放音设备(WaveOut)和录音
 设备(WaveIn)的当前音量大小。
 *
 *  @param device 设备类型,定义为:
 AD_WAVEIN  = 0,    ///< 输入设备:Mic
 AD_WAVEOUT = 1,    ///< 输出设备:Wave
 *  @param dwVolume dwVolume 需要设置的音量,取值范围:0~100,值越大,音量越大;
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) AudioSetVolume:(int) device : (int) dwVolume;

/**
 *  对指定用户的音视频流进行录制。
 *
 *  @param dwUserId     需要录制视频的用户编号,可用-1 表示本地用户(自己);
 *  @param bStartRecord 指示当前指令是启动录像,或是停止录像;
 *  @param dwFlags      录制功能标志,参考备注;
 *  @param dwParam      录制指令附带参数,录像任务结束时,该参数将通过回调函 数返回给上层应用。
 *
 *  @return 0 表示录制指令被 SDK 成功接收,否则为出错代码
 */
+ (int) StreamRecordCtrl: (int) dwUserId : (BOOL) bStartRecord : (int) dwFlags : (int) dwParam;

/**
 *  对指定用户的音视频流进行录制(扩展)
 *
 *  @param dwUserId     需要录制视频的用户编号,可用-1 表示本地用户(自己);
 *  @param bStartRecord 指示当前指令是启动录像,或是停止录像;
 *  @param dwFlags      录制功能标志,参考备注;
 *  @param dwParam      录制指令附带参数,录像任务结束时,该参数将通过回调函 数返回给上层应用。
 *  @param lpUserStr    录制指令附带参数(字符串类型),录像任务结束时,该参 数将通过回调函数返回给上层应用。
 *
 *  @return 0 表示录制指令被 SDK 成功接收,否则为出错代码
 */
+ (int) StreamRecordCtrlEx: (int) dwUserId : (BOOL) bStartRecord : (int) dwFlags : (int) dwParam : (NSString*)lpUserStr;

/**
 *  对指定用户的视频进行抓拍 : 该方法只是向 SDK 下达图像抓拍任务,视频抓拍完成之后, 将触发回调事
 件:OnAnyChatSnapShotCallBack。
 
 *
 *  @param dwUserId 需要抓拍视频的用户编号,可用-1 表示本地用户(自己);
 *  @param dwFlags  功能标志;
 *  @param dwParam  抓拍指令附带参数(整形),抓拍图像成功之后,该参数将通过回调函数返回给上层应用;
 *
 *  @return 0 表示抓拍指令被 SDK 成功接收,否则为出错代码
 */
+ (int) SnapShot: (int) dwUserId : (int) dwFlags : (int) dwParam;

/**
 *   获取音频播放数据
 *
 *  @param dwSize <#dwSize description#>
 *
 *  @return 音频播放数据
 */
+ (NSData*) FetchAudioPlayBuffer: (int)dwSize;

/**
 *  透明通道传送缓冲区
 *
 *  @param dwUserid 用户 ID,指示发送用户
 *  @param lpBuf    缓冲区地址
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) TransBuffer: (int) dwUserid : (NSData*) lpBuf;

/**
 *  透明通道传送缓冲区（扩展方法）
 *
 *  @param dwUserid 目标用户编号,只针对某一个用户,不能为-1(所有人)
 *  @param lpBuf    缓冲区,≤1024KB(1MB),内部会自动分包处理
 *  @param wParam   附带参数,由上层应用自定义
 *  @param lParam   附带参数 2,由上层应用自定义
 *  @param dwFlags  特殊功能标志,当对该缓冲区有特殊要求时,可通过使用相关的功能标志,通知 SDK 进行特殊的处理,默认为 0,SDK 将自动根据网络状态选择合适的传输途径(TCP、UDP or P2P)
 *
 *  @return >0 表示任务 ID 号(可利用该 ID 查询该任务的传输进度),否则表示出 错。
 *
 * 该方法与“TransBuffer”功能相同,都是传输上层应用自定义(透明通道) 数据,区别在于该方法通过设置相应的功能标识,如可选择采用 UDP 通道传输, 但是只针对指定的用户传输,而“TransBuffer”方法则固定采用 TCP 通道传输,
 且缓冲区大小不能超过 1024 个字节,但可以针对所有用户传输。 从应用来看:
 (1)、TransBuffer 适合数据量小、要求实时传输的缓冲区传递,如控制指令 等;
 (2)、TransBufferEx 适合数据量大、对实时性要求不高的需求;
 */
+ (int) TransBufferEx: (int) dwUserid : (NSData*) lpBuf : (int) wParam : (int) lParam : (int) dwFlags;

/**
 *  传送文件给指定用户
 *
 *  @param dwUserid        目标用户编号,只针对某一个用户,不能为-1(所有人)
 *  @param lpLocalPathName 本地文件名, 路径
 *  @param wParam          附带参数 1,便于上层应用扩展
 *  @param lParam          附带参数 2
 *  @param dwFlags         特殊功能标志,当对该缓冲区有特殊要求时,可通过使用相关的功能标志,通知 SDK 进行特殊的处理,默认为 0,SDK 将自动根据网络状态选择合适的传输途径(TCP、UDP or P2P)
 *
 *  @return >0 表示任务 ID 号(可利用该 ID 查询该任务的传输进度),否则表示出 错。
 */
+ (int) TransFile: (int) dwUserid : (NSString*) lpLocalPathName : (int) wParam : (int) lParam : (int) dwFlags;

/**
 *  查询传输任务相关信息
 *
 *  @param dwUserid 任务发起者用户编号(并非传输目标用户编号)
 *  @param dwTaskId 任务发起者用户编号
 *  @param infoname 需要查询的信息代码(见5.5.7备注附表)
 *
 *  @return 状态值
 */
+ (int) QueryTransTaskInfoInt: (int) dwUserid : (int) dwTaskId : (int) infoname;
/**
 *  取消传输任务
 *
 *  @param dwUserid 任务发起者用户编号
 *  @param dwTaskId 任务发起者用户编号
 *
 *  @return <#return value description#>
 */

+ (int) CancelTransTask: (int) dwUserid : (int) dwTaskId;
// 传送文本消息
/**
 *  向指定的用户传送文本消息
 *
 *  @param dwUserid 目标用户编号,-1 表示大家(所有人)
 *  @param bSecret  是否为密语,只在 dwUserid 不为-1 时有效,选择密语时,其它用户看不到发送的消息
 *  @param lpMsgBuf 消息字符串
 *
 *  @return 0 表示成功,否则为出错代码
 *
 *  可以利用该消息实现文字交流的功能,发送消息的对象可以是大家,也可以是指定的对象,如果是对指定的对象发送文字消息,可以选择密语。
 对方收到该消息后,会触发 AnyChatTextMsgDelegate 接口的接口函数的调用。
 */
+ (int) SendTextMessage: (int) dwUserid : (BOOL) bSecret : (NSString*) lpMsgBuf;

/**
 *  向服务器发送 SDK Filter 通信数据 : 服务器收到数据后,会将该缓冲区数据全部提交给 SDK Filter,由 SDK Filter 来解析,该缓冲区的内容对于本 SDK 和服务器来说,都是透明的。
 *
 *  @param lpBuf 缓冲区
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) SendSDKFilterData: (NSData*) lpBuf;

/**
 *  更改当前的聊天模式
 *
 *  @param dwChatMode <#dwChatMode description#>
 *
 *  @return <#return value description#>
 */
+ (int) ChangeChatMode: (int) dwChatMode;

/**
 *  获取指定用户当前的聊天模式
 *
 *  @param dwUserid 用户的ID
 *
 *  @return <#return value description#>
 */
+ (int) GetUserChatMode: (int) dwUserid;
// 请求与对方私聊，向对方发起私聊请求
/**
 *  <#Description#>
 *
 *  @param dwUserid <#dwUserid description#>
 *
 *  @return <#return value description#>
 */
+ (int) PrivateChatRequest: (int) dwUserid;

/**
 *  回复对方的私聊请求
 *
 *  @param dwUserid    <#dwUserid description#>
 *  @param dwRequestid <#dwRequestid description#>
 *  @param bAccept     <#bAccept description#>
 *
 *  @return <#return value description#>
 */
+ (int) PrivateChatEcho: (int) dwUserid : (int) dwRequestid : (BOOL) bAccept;
// 回复对方的私聊请求（扩展，可以附带出错代码）
/**
 *  <#Description#>
 *
 *  @param dwUserid    <#dwUserid description#>
 *  @param dwRequestid <#dwRequestid description#>
 *  @param dwErrorCode <#dwErrorCode description#>
 *
 *  @return <#return value description#>
 */
+ (int) PrivateChatEchoEx: (int) dwUserid : (int) dwRequestid : (int) dwErrorCode;

/**
 *  退出与某用户的私聊，或者将某用户从自己的私聊列表中清除
 *
 *  @param dwUserid 用户ID
 *
 *  @return <#return value description#>
 */
+ (int) PrivateChatExit: (int) dwUserid;

/**
 *  SDK 内核参数设置(整形值参数) ： 可以通过该方法对AnyChat Core SDK内部的参数进行设置,实现特殊的功
 能要求。
 *
 *  @param optname 内核参数名称;
 *  @param value   设置的参数值
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) SetSDKOptionInt:(int) optname : (int) value;

/**
 *  SDK 内核参数设置(字符串值参数) ： 可以通过该方法对AnyChat Core SDK内部的参数进行设置,实现特殊的功 能要求。
 *
 *  @param optname 内核参数名称;
 *  @param value   设置的参数值
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) SetSDKOptionString:(int) optname : (NSString*) value;

/**
 *  SDK 内核参数状态查询(整形值) ： 可以通过该方法对AnyChat Core SDK内部的参数进行状态查询,获取当前的设置。
 *
 *  @param optname 内核参数名称;
 *
 *  @return 返回查询结果
 */
+ (int) GetSDKOptionInt:(int) optname;

/**
 *  SDK 内核参数状态查询(字符串) ： 可以通过该方法对AnyChat Core SDK内部的参数进行状态查询,获取当前的设置。
 *
 *  @param optname 内核参数名称;
 *
 *  @return 返回查询结果
 */
+ (NSString*) GetSDKOptionString:(int) optname;

// 组播功能控制
/**
 *  <#Description#>
 *
 *  @param lpMultiCastAddr <#lpMultiCastAddr description#>
 *  @param dwPort          <#dwPort description#>
 *  @param lpNicAddr       <#lpNicAddr description#>
 *  @param dwTTL           <#dwTTL description#>
 *  @param dwFlags         <#dwFlags description#>
 *
 *  @return <#return value description#>
 */
+ (int) MultiCastControl: (NSString*) lpMultiCastAddr : (int) dwPort : (NSString*) lpNicAddr : (int) dwTTL : (int) dwFlags;

// 设置外部输入视频格式
/**
 *  <#Description#>
 *
 *  @param pixFmt   <#pixFmt description#>
 *  @param dwWidth  <#dwWidth description#>
 *  @param dwHeight <#dwHeight description#>
 *  @param dwFps    <#dwFps description#>
 *  @param dwFlags  <#dwFlags description#>
 *
 *  @return <#return value description#>
 */
+ (int) SetInputVideoFormat: (int) pixFmt : (int) dwWidth : (int) dwHeight : (int) dwFps : (int) dwFlags;
// 外部视频数据输入
/**
 *  <#Description#>
 *
 *  @param lpVideoFrame <#lpVideoFrame description#>
 *  @param dwTimeStamp  <#dwTimeStamp description#>
 *
 *  @return <#return value description#>
 */
+ (int) InputVideoData: (NSData*) lpVideoFrame : (int) dwTimeStamp;
// 设置外部输入音频格式
/**
 *  <#Description#>
 *
 *  @param dwChannels      <#dwChannels description#>
 *  @param dwSamplesPerSec <#dwSamplesPerSec description#>
 *  @param dwBitsPerSample <#dwBitsPerSample description#>
 *  @param dwFlags         <#dwFlags description#>
 *
 *  @return <#return value description#>
 */
+ (int) SetInputAudioFormat: (int) dwChannels : (int) dwSamplesPerSec : (int) dwBitsPerSample : (int) dwFlags;
// 外部音频数据输入
/**
 *  <#Description#>
 *
 *  @param lpSamples   <#lpSamples description#>
 *  @param dwTimeStamp <#dwTimeStamp description#>
 *
 *  @return <#return value description#>
 */
+ (int) InputAudioData: (NSData*) lpSamples : (int) dwTimeStamp;

/**
 *  对视频呼叫业务流程进行控制,发起视频呼叫,或是结束视频通话等。
 *
 *  @param dwEventType 事件类型,定义为:
 #define BRAC_VIDEOCALL_EVENT_REQUEST  1    ///< 呼叫请求
 #define BRAC_VIDEOCALL_EVENT_REPLY    2    ///< 呼叫请求回复
 #define BRAC_VIDEOCALL_EVENT_START    3    ///< 视频呼叫会话开始事件
 #define BRAC_VIDEOCALL_EVENT_FINISH   4    ///< 挂断(结束)呼叫会话
 *  @param dwUserId    目标用户 ID
 *  @param dwErrorCode 出错代码,与事件类型相关,默认为 0
 *  @param dwFlags     视频呼叫标志,默认为 0
 *  @param dwParam     用户自定义参数(整型),默认为 0
 *  @param lpUserStr   用户自定义参数(字符串),默认为空
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) VideoCallControl: (int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr;
// 向服务器动态查询相关信息
/**
 *  <#Description#>
 *
 *  @param dwInfoName <#dwInfoName description#>
 *  @param lpInParam  <#lpInParam description#>
 *  @param dwFlags    <#dwFlags description#>
 *
 *  @return return value description
 */
+ (NSString*) QueryInfoFromServer: (int) dwInfoName : (NSString*) lpInParam : (int) dwFlags;

/**
 *  获取本地用户的好友列表;
 *
 *  @return 返回好友用户 ID 列表数组;
 *
 *  当客户端登录系统成功之后,会触发异步消息:WM_GV_LOGINSYSTEM,同时 服务器会向客户端发送用户好友信息,当客户端接收完成之后会触发客户端的 异步消息:WM_GV_USERINFOUPDATE,且该消息的 lParam 为 0,表示好友列表有 更新。所以该 API 通常在接收到WM_GV_USERINFOUPDATE 异步消息之后调用。
 */
+ (NSMutableArray*) GetUserFriends;

/**
 *  获取本地用户的好友在线状态,根据状态可以知道好友是否在线。
 *
 *  @param dwFriendUserId 好友的用户 ID;
 *
 *  @return 返回该好友的在线状态:0 离线, 1 在线
 */
+ (int) GetFriendStatus: (int) dwFriendUserId;

/**
 *  获取本地用户的好友分组列表,返回好友分组 ID 列表数组 : 登录成功之后调用有效。好友分组是指将好友归纳到某一个组别下,如“家 人”、“大学同学”以及“老师”等。每一个分组对应一个分组 ID,通过分组 ID 可以获取分组的名称。
 *
 *  @return 用户 ID 数组
 */
+ (NSMutableArray*) GetUserGroups;

/**
 *  获取分组所对应的用户列表,即该分组下有多少用户 : 登录成功之后调用有效。通过该 API 接口,可以获得每一个分组下面的用户 列表,进而可以获得该分组下每一个用户的详细信息。
 
 *
 *  @param dwGroupId 分组 ID;
 *
 *  @return 用户 ID 数组
 */
+ (NSMutableArray*) GetGroupFriends: (int) dwGroupId;

/**
 *  获取好友用户的详细信息。
 *
 *  @param dwUserId 好友用户 ID;
 *  @param dwInfoId 用户信息类型 ID,业务层可自定义;
 *
 *  @return 用户信息字符串
 *
 *  登录成功之后调用有效。当业务服务器调用 API:BRAS_SetUserInfo 设置了 用户的信息之后,客户端便可以通过该 API 获取业务服务器所设置的信息,其中 dInfoId 由业务层(上层应用)自己定义。
 关于好友用户信息这一部分,对于 AnyChat 来说是透明的,业务服务器设置 了什么样的信息,客户端便可以获取到什么样的信息,AnyChat 只是提供了一个 信息传输的中间通道,业务层可以自由扩展。
 */
+ (NSString*) GetUserInfo: (int) dwUserId : (int) dwInfoId;

/**
 *  根据分组 ID 获取分组名称 :  登录成功之后调用有效。分组名称由业务服务器设置。
 *
 *  @param dwGroupId 分组 ID;
 *
 *  @return 分组名称字符串
 */
+ (NSString*) GetGroupName: (int) dwGroupId;

/**
 *  对用户信息进行控制 : 登录成功之后调用有效。该 API 调用之后,会向业务服务器发送信息控制指 令,将会触发业务服务器对应的回调函数。
 *
 *  @param dwUserId   用户 ID;
 *  @param dwCtrlCode 控制代码,业务层自定义,其中<100 的值为系统保留,业务层使用时,其值必须>100
 *  @param wParam     附带参数,业务层自定义;
 *  @param lParam     附带参数,业务层自定义;
 *  @param lpStrValue 附带参数(字符串类型),业务层自定义,可为空;
 *
 *  @return 0 表示成功,否则为出错代码
 */
+ (int) UserInfoControl: (int) dwUserId : (int) dwCtrlCode : (int) wParam : (int) lParam : (NSString*) lpStrValue;



#pragma mark-  业务排队

/**
 *  获取业务对象的 Id 数组 : 可以通过该方法查询业务对象的整形 id 数组,如服务区域的业务队列的 id 数组。
 *
 *  @param dwObjectType 业务对象类型,见3.6.1.1章节描述内容;
 *
 *  @return id 数组
 */
+ (NSMutableArray*) ObjectGetIdList: (int) dwObjectType;

/**
 *  获取对象属性值(整型) : 可以通过该方法查询业务对象的整形属性值,如队列人数,排队时间等。
 *
 *  @param dwObjectType 业务对象类型,见3.6.1.1章节描述内容;
 *  @param dwObjectId   业务对象的 Id
 *  @param dwInfoName   要查询的业务对象的属性名,各类业务对象的属性定义见3.6.2 章节描述内容;
 *
 *  @return 业务对象属性值
 */
+ (int) ObjectGetIntValue: (int) dwObjectType : (int) dwObjectId : (int) dwInfoName;

/**
 *  获取对象属性值(字符串) : 以通过该方法查询业务对象的字符串属性,如服务区域名称,队列名称等。
 *
 *  @param dwObjectType 业务对象类型,见3.6.1.1章节描述内容;
 *  @param dwObjectId   业务对象的 Id
 *  @param dwInfoName   要查询的业务对象的属性名,各类业务对象的属性定义见3.6.2 章节描述内容;
 *
 *  @return 业务对象属性值
 */
+ (NSString*) ObjectGetStringValue: (int) dwObjectType : (int) dwObjectId : (int) dwInfoName;

/**
 *  设置对象属性值(整形)
 *
 *  @param dwObjectType 业务对象类型,见3.6.1.1章节描述内容;
 *  @param dwObjectId   业务对象的 Id
 *  @param dwInfoName   要设置的业务对象的属性名,各类业务对象的属性定义见3.6.2 章节描述内容;
 *  @param dwValue      要设置的业务对象的属性值
 *
 *  @return 0 表示成功,否则为错误代码
 */
+ (int) ObjectSetIntValue: (int) dwObjectType : (int) dwObjectId : (int) dwInfoName : (int) dwValue;

/**
 *  设置对象属性值(字符串)
 *
 *  @param dwObjectType 业务对象类型,见3.6.1.1章节描述内容
 *  @param dwObjectId   业务对象的 Id
 *  @param dwInfoName   要设置的业务对象的属性名,各类业务对象的属性定义见3.6.2 章节描述内容;
 *  @param lpStrValue   要设置的业务对象的属性值
 *
 *  @return 0 表示成功,否则为错误代码
 */
+ (int) ObjectSetStringValue: (int) dwObjectType : (int) dwObjectId : (int) dwInfoName : (NSString*) lpStrValue;

/**
 *  对业务对象进行参数控制 : 可以通过该方法对业务对象进行参数控制,如进/出服务区域,进/出队列, 开始/结束服务等。
 *
 *  @param dwObjectType 业务对象类型,见3.6.1.1章节描述内容;
 *  @param dwObjectId   业务对象的 Id
 *  @param dwCtrlCode   对象公共参数定义,见3.6.3 章节描述内容;
 *  @param dwParam1     默认为 0
 *  @param dwParam2     默认为 0
 *  @param dwParam3     默认为 0
 *  @param dwParam4     默认为 0
 *  @param lpStrValue   默认为空
 *
 *  @return 0 表示成功,否则表示错误代码
 */
+ (int) ObjectControl: (int) dwObjectType : (int) dwObjectId : (int) dwCtrlCode : (int) dwParam1 : (int) dwParam2 : (int) dwParam3 : (int) dwParam4 : (NSString*) lpStrValue;




@end







#endif //_ANYCHAT_PLATFORM_H_INCLUDEDED_
