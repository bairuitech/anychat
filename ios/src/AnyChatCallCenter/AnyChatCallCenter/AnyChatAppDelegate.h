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

#ifdef DEBUG
FILE *fopen$UNIX2003(const char *filename, const char *mode);
size_t fwrite$UNIX2003(const void *ptr, size_t size, size_t nitems, FILE *stream);
#endif

@interface AnyChatAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

+ (AnyChatAppDelegate*) GetApp;

+ (id) GetServerIP;

+ (int) GetServerPort;

@end
