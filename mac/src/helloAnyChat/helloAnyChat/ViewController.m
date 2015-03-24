//
//  ViewController.m
//  helloAnyChat
//
//  Created by WangXL on 15/3/24.
//  Copyright (c) 2015年 WangXL. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    [AnyChatPlatform InitSDK:0];
    
    anychat = [[AnyChatPlatform alloc] init];
    anychat.notifyMsgDelegate = self;
    
    [AnyChatPlatform Connect:@"demo.anychat.cn" :8906];
    [AnyChatPlatform Login:@"iMac" :@""];
    [AnyChatPlatform EnterRoom:1 :@""];
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (void)AnyChatNotifyHandler:(NSNotification*)notify
{
    NSDictionary* dict = notify.userInfo;
    [anychat OnRecvAnyChatNotify:dict];
}

- (void)OnAnyChatConnect:(BOOL)bSuccess {
    
    
}

- (void)OnAnyChatLogin:(int)dwUserId :(int)dwErrorCode {
    
    
}

- (void)OnAnyChatEnterRoom:(int)dwRoomId :(int)dwErrorCode {
    
    
}

- (void)OnAnyChatOnlineUser:(int)dwUserNum :(int)dwRoomId {
    
    
}

- (void)OnAnyChatUserEnterRoom:(int)dwUserId {
    
    
}

- (void)OnAnyChatUserLeaveRoom:(int)dwUserId {
 
    
}

- (void)OnAnyChatLinkClose:(int)dwErrorCode {
    
    
}

@end
