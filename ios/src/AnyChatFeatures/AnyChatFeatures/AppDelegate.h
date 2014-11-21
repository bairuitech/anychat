//
//  AppDelegate.h
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"

@class AnyChatVC;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow                  *window;
@property (strong, nonatomic) UINavigationController    *navController;
@property (strong, nonatomic) AnyChatVC     *anychatVC;

// 获取默认设置
- (void)registerDefaultsFromSettingsBundle;

@end
