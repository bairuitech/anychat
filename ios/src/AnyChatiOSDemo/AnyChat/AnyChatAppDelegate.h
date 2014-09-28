//
//  AnyChatAppDelegate.h
//  AnyChat
//
//  Created by bairuitech on 11-8-8.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatViewController.h"

#ifdef DEBUG
FILE *fopen$UNIX2003(const char *filename, const char *mode);
size_t fwrite$UNIX2003(const void *ptr, size_t size, size_t nitems, FILE *stream);
#endif

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
