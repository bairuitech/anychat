//
//  AnyChatAppDelegate.h
//  AnyChatCallCenter
//
//  Created by AnyChat on 14-9-4.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LoginViewController.h"
#import "AnyChatNavigationController.h"

@interface AnyChatAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

+ (AnyChatAppDelegate*) GetApp;

// 获取默认设置
- (void)registerDefaultsFromSettingsBundle;

@end
