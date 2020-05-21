//
//  VideoVC.h
//  AnyChatFeatures
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "MBProgressHUD.h"
#import "VideoVC.h"
#import "SettingVC.h"
#import "UserListVC.h"
#import "TextMsg_TransBufferVC.h"

#import "RecordLocalVC.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

#define kAnyChatIP @"demo.anychat.cn"
#define kAnyChatPort @"8906"

typedef enum {
    AnyChatVCLoginModeGeneralLogin,
    AnyChatVCLoginModeSignLogin
} AnyChatVCLoginMode;

@class VideoVC;

@interface AnyChatVC : ACBaseViewController <NSCoding,UITextFieldDelegate,UIAlertViewDelegate,MBProgressHUDDelegate,AnyChatNotifyMessageDelegate,AnyChatTextMsgDelegate,AnyChatTransDataDelegate,AnyChatRecordSnapShotDelegate,AnyChatVideoCallDelegate,AnyChatMediaDataDelegate>


@property (readonly, nonatomic) NSMutableArray                *onlineUserMArray;
@property (readonly, nonatomic) NSMutableArray                *theVideoRecordMArray;
@property (readonly, nonatomic) NSMutableArray                *theVideoRecordSelfMArray;

@property (readonly, nonatomic) int   theShowVCType;

@property (assign, nonatomic) int  theFeaturesNO;
@property (strong, nonatomic) NSString *theFeaturesName;

@property (readonly, nonatomic) int   theMyUserID;
@property (readonly, nonatomic) NSString   *theMyUserName;
@property (strong, nonatomic) NSString* theMyServerAddr;

@property (assign, nonatomic) int   theTargetUserID;
@property (strong, nonatomic) NSString  *theTargetUserName;


kGCD_SINGLETON_FOR_HEADER(AnyChatVC);


- (void) OnLogout;


- (NSMutableArray *) getOnlineUserArray;

@end
