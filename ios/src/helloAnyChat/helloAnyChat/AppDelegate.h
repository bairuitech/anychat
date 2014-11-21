//
//  AppDelegate.h
//  helloAnyChat
//
//  Created by AnyChat on 14-9-12.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatViewController.h"

@class AnyChatViewController;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow                  *window;
@property (strong, nonatomic) UINavigationController    *navController;
@property (strong, nonatomic) AnyChatViewController     *anychatVC;

// 获取默认设置
- (void)registerDefaultsFromSettingsBundle;

@end
