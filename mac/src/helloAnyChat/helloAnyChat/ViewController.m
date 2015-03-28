//
//  ViewController.m
//  helloAnyChat
//
//  Created by WangXL on 15/3/24.
//  Copyright (c) 2015年 WangXL. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

@synthesize theRemoteVideo;
@synthesize theLocalVideoSurface;
@synthesize theLocalView;


- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    
    
    [AnyChatPlatform InitSDK:0];
    
    anychat = [[AnyChatPlatform alloc] init];
    anychat.notifyMsgDelegate = self;
    
    [AnyChatPlatform Connect:@"demo.anychat.cn" :8906];
    [AnyChatPlatform Login:@"iMac" :@""];
    [AnyChatPlatform EnterRoom:10 :@""];
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
    if(dwErrorCode == 0)
    {
        [AnyChatPlatform UserSpeakControl:-1 :YES];
        
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];
        [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
        [AnyChatPlatform UserCameraControl:-1 :YES];
    }
    
}

- (void)OnAnyChatOnlineUser:(int)dwUserNum :(int)dwRoomId {
    
    NSMutableArray* onlineusers = [AnyChatPlatform GetOnlineUser];
    for (int i=0; i<[onlineusers count]; i++) {
        int userid = [[onlineusers objectAtIndex:i] intValue];
        [AnyChatPlatform UserSpeakControl:userid :YES];
        [AnyChatPlatform SetVideoPos:userid :self.theRemoteVideo :0 :0 :0 :0];
        [AnyChatPlatform UserCameraControl:userid :YES];
    }
    
}

- (void)OnAnyChatUserEnterRoom:(int)dwUserId {
    
    
}

- (void)OnAnyChatUserLeaveRoom:(int)dwUserId {
 
    
}

- (void)OnAnyChatLinkClose:(int)dwErrorCode {
    
    
}

- (void) OnLocalVideoInit:(id)session
{
    self.theLocalView.wantsLayer =YES;
    self.theLocalView.canDrawConcurrently = YES;
    
    self.theLocalVideoSurface = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.theLocalVideoSurface.frame = self.theLocalView.frame;
    self.theLocalVideoSurface.videoGravity = AVLayerVideoGravityResizeAspectFill;
   [self.theLocalView.layer addSublayer:self.theLocalVideoSurface];
}

- (void) OnLocalVideoRelease:(id)sender
{
    if(self.theLocalVideoSurface)
    {
        self.theLocalVideoSurface = nil;
    }
}






@end
