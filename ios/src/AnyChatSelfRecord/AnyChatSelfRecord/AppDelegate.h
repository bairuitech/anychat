//
//  AppDelegate.h
//  AnyChatSelfRecord
//
//  Created by alexChen on 14-12-19.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"

@class AnyChatVC;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow                  *window;
@property (strong, nonatomic) UINavigationController    *navController;
@property (strong, nonatomic) AnyChatVC     *anychatVC;

@end
