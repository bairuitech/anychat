//
//  RootViewController.h
//  AnyChatCallCenter
//
//  Created by alex on 14-1-27.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatAppDelegate.h"
#import <AVFoundation/AVFoundation.h>
#import "HallViewController.h"
#import "UserEntity.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"
#import "MZTimerLabel.h"
@interface VideoViewController : ACBaseViewController<UIActionSheetDelegate>

@property (strong, nonatomic) UserEntity                    *theUserEntity;


- (void) StartVideoChat:(int) userid;


@end
