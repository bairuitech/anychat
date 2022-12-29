//
//  AppDelegate.m
//  HelloAnyChat
//
//  Created by Chen on 15-3-28.
//  Copyright (c) 2015年 AlexChen. All rights reserved.
//

#import "AppDelegate.h"
#import "AnyChatVC.h"


@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@property (nonatomic,strong) IBOutlet AnyChatVC *pvAnyChatVC;


@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    self.pvAnyChatVC = [[AnyChatVC alloc] initWithNibName:@"AnyChatVC" bundle:nil];
    
    [self.window.contentView addSubview:self.pvAnyChatVC.view];
    self.pvAnyChatVC.view.frame = ((NSView*)self.window.contentView).bounds;
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
