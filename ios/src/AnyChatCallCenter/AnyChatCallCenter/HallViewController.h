//
//  HallViewController.h
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatAppDelegate.h"
#import "VideoViewController.h"
#import "UserEntity.h"
#import "UserInfo.h"
#import "UIView+Toast.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>

@class VideoViewController;

@interface HallViewController : ACBaseViewController<UITableViewDelegate,UITableViewDataSource,UIAlertViewDelegate,AnyChatUserInfoDelegate,AnyChatVideoCallDelegate,AnyChatNotifyMessageDelegate>
{
    AnyChatPlatform *theAnyChat;
}

@end
