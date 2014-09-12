//
//  AnyChatAppDelegate.h
//  AnyChat
//
//  Created by bairuitech on 11-8-8.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatViewController.h"

@class AnyChatViewController;

@interface AnyChatAppDelegate : NSObject <UIApplicationDelegate> {


}

@property (nonatomic, strong) IBOutlet UIWindow *window;


@property (nonatomic, strong) IBOutlet AnyChatViewController *viewController;

+ (AnyChatAppDelegate*) GetApp;

+ (id) GetServerIP;

+ (int) GetServerPort;

// 获取默认设置
- (void)registerDefaultsFromSettingsBundle;

@end
