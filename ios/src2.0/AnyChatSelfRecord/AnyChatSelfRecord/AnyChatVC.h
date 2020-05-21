//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "MBProgressHUD.h"
#import "SettingVC.h"
#import "TakePhotoVC.h"
#import "ProviewPhotoVC.h"
#import "RecordLocalVC.h"
#import "ShowVC.h"
#import "TransFileVC.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>


@interface AnyChatVC : ACBaseViewController <NSCoding,UITextFieldDelegate,MBProgressHUDDelegate,AnyChatNotifyMessageDelegate,AnyChatTransDataDelegate,AnyChatRecordSnapShotDelegate>


@property (weak, nonatomic) IBOutlet UILabel                *theStateInfo;
@property (weak, nonatomic) IBOutlet UIButton               *theLoginBtn;

@property (nonatomic, assign) BOOL                          theNextVCBool;//判断是否到下一步
@property (nonatomic, copy) NSString                        *videoCoverImagePath;//截取视频中的一帧
@property (strong, nonatomic) NSString                      *thePhotoPath;
@property (strong, nonatomic) NSString                      *theVideoPath;

@property (nonatomic, assign) int                           theMyUserID;
@property (nonatomic, assign) BOOL                          theLoginState;

kGCD_SINGLETON_FOR_HEADER(AnyChatVC);


@end
