//
//  AnyChatViewController.h
//  HelloAnyChat
//
//  Created by AnyChat on 14-9-12.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>
#import "AppDelegate.h"
#import "MBProgressHUD.h"
#import "VideoViewController.h"
#import "SettingVC.h"

@class VideoViewController;

@interface AnyChatViewController : ACBaseViewController <UITableViewDelegate, UITableViewDataSource, UIAlertViewDelegate, UITextFieldDelegate, MBProgressHUDDelegate, AnyChatNotifyMessageDelegate>

@property (strong, nonatomic) NSMutableArray                *onlineUserMArray;

- (NSMutableArray *) getOnlineUserArray;

@end
