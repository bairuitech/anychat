//
//  RootViewController.h
//  AnyChatCallCenter
//
//  Created by alex on 14-1-27.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "AnyChatViewController.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>

@interface VideoViewController : ACBaseViewController<UIActionSheetDelegate,UIGestureRecognizerDelegate>

@property (nonatomic, assign) int iRemoteUserId;
@property (nonatomic, copy) NSString *remoteUserName;
- (void) FinishVideoChat;
@end
