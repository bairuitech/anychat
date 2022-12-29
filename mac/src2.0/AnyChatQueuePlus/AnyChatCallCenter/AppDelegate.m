//
//  AppDelegate.m
//  AnyChatCallCenter
//
//  Created by tim.tan on 15/5/22.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "AppDelegate.h"
#import "MainViewController.h"
@interface AppDelegate ()
@property (weak) IBOutlet NSWindow *window;
@property (strong, nonatomic)MainViewController *mainVC;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    NSProcessInfo *info = [NSProcessInfo processInfo];
    NSLog(@"info:%@",info.operatingSystemVersionString);
    
    MainViewController *mainVC = [[MainViewController alloc] init];
    mainVC.view.frame = ((NSView*)self.window.contentView).bounds;
    self.mainVC = mainVC;
    [self.window.contentView addSubview:self.mainVC.view];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
