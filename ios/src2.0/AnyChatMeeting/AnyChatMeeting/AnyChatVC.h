//
//  VideoVC.h
//  AnyChatMeetings
//
//  Created by alexChen .
//  Copyright (c) 2015年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "MBProgressHUD.h"
#import "VideoVC.h"
#import "SettingVC.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>


@class VideoVC;


@interface AnyChatVC : ACBaseViewController <NSCoding,UITextFieldDelegate,UIAlertViewDelegate,MBProgressHUDDelegate,AnyChatNotifyMessageDelegate>

@property (strong, nonatomic) NSMutableArray                *onlineUserMArray;
@property (strong, nonatomic) NSMutableArray                *theOnChatUserIDStrMArray;

@property (strong, nonatomic) NSString                      *theMyUserName;
@property (assign, nonatomic) int                            theMyUserID;

kGCD_SINGLETON_FOR_HEADER(AnyChatVC);


- (IBAction)OnLoginBtnClicked:(id)sender;
- (NSMutableArray *) getOnlineUserArray;

@end
