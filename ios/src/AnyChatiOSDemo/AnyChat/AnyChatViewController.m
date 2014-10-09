//
//  AnyChatViewController.m
//  AnyChat
//
//  Created by bairuitech on 11-8-8.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "AnyChatViewController.h"
#import "LoginViewController.h"
#import "HallViewController.h"
#import "VideoChatController.h"
#import "SettingsController.h"
#import "RoomViewController.h"

// Local Settings Parameter Key Define
NSString* const kUseP2P = @"usep2p";
NSString* const kUseServerParam = @"useserverparam";
NSString* const kVideoSolution = @"videosolution";
NSString* const kVideoFrameRate = @"videoframerate";
NSString* const kVideoBitrate = @"videobitrate";
NSString* const kVideoPreset = @"videopreset";
NSString* const kVideoQuality = @"videoquality";



@implementation AnyChatViewController
{
    BOOL isSupporteAutorotate;
}

@synthesize loginViewController;
@synthesize hallViewController;
@synthesize videoChatController;
@synthesize settingsController;
@synthesize roomViewController;


- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];

    iCurrentChatUserId = -1;
    
    // register our handler
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    anychat = [[AnyChatPlatform alloc] init];
    anychat.notifyMsgDelegate = self;
    
    [AnyChatPlatform InitSDK:0];
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskAllButUpsideDown;
}

-(BOOL)shouldAutorotate
{
    return isSupporteAutorotate;
}


- (void) hideAllView
{
    for(NSInteger i=0;i<[self.view.subviews count];i++){  
        [[self.view.subviews objectAtIndex:i] removeFromSuperview];  
    }
}

- (void) showNetConfigView
{
    [self hideAllView];
    [self.view insertSubview:settingsController.view atIndex:0];
    isSupporteAutorotate = NO;
}

- (void) showLoginView
{
    [self hideAllView];
    [self.view insertSubview:loginViewController.view atIndex:0];
    isSupporteAutorotate = NO;
}

- (void) showHallView
{
    [self hideAllView];
    [self.view insertSubview:hallViewController.view atIndex:0];
    isSupporteAutorotate = NO;
}

- (void) showRoomView
{
    [self hideAllView];
    [self.view insertSubview:roomViewController.view atIndex:0];
    isSupporteAutorotate = NO;
}

- (void) showVideoChatView:(int) userid
{
    iCurrentChatUserId = userid;
    [self hideAllView];
    [self.view insertSubview:videoChatController.view atIndex:0];
    [self.videoChatController StartVideoChat:userid];
    isSupporteAutorotate = YES;
}

- (void)AnyChatNotifyHandler:(NSNotification*)notify
{
    NSDictionary* dict = notify.userInfo;
    [anychat OnRecvAnyChatNotify:dict];
}

// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess
{

}
// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode
{
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        [self updateLocalSettings];
        
        [self showHallView];
        [hallViewController ShowSelfUserId:dwUserId];
    }
    else
    {
        
    }
}
// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode
{
    [self showRoomView];
    [roomViewController RefreshRoomUserList];
}

// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId
{
    [roomViewController RefreshRoomUserList];
}

// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId
{
    [roomViewController RefreshRoomUserList];
}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId
{
    if(iCurrentChatUserId == dwUserId) {
        [videoChatController FinishVideoChat];
        [self showRoomView];
    }
    [roomViewController RefreshRoomUserList];
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode
{
    [videoChatController FinishVideoChat];
    [AnyChatPlatform Logout];
    [self showLoginView];
    iCurrentChatUserId = -1;
}

// 更新本地参数设置
- (void) updateLocalSettings
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults synchronize];
    
    BOOL bUseP2P = [[defaults objectForKey:kUseP2P] boolValue];
    BOOL bUseServerVideoParam = [[defaults objectForKey:kUseServerParam] boolValue];
    int iVideoSolution =    [[defaults objectForKey:kVideoSolution] intValue];
    int iVideoBitrate =     [[defaults objectForKey:kVideoBitrate] intValue];
    int iVideoFrameRate =   [[defaults objectForKey:kVideoFrameRate] intValue];
    int iVideoPreset =      [[defaults objectForKey:kVideoPreset] intValue];
    int iVideoQuality =     [[defaults objectForKey:kVideoQuality] intValue];
    
    // P2P
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_NETWORK_P2PPOLITIC : (bUseP2P ? 1 : 0)];
    
    if(bUseServerVideoParam)
    {
        // 屏蔽本地参数，采用服务器视频参数设置
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_APPLYPARAM :0];
    }
    else
    {
        int iWidth, iHeight;
        switch (iVideoSolution) {
            case 0:     iWidth = 1280;  iHeight = 720;  break;
            case 1:     iWidth = 640;   iHeight = 480;  break;
            case 2:     iWidth = 480;   iHeight = 360;  break;
            case 3:     iWidth = 352;   iHeight = 288;  break;
            case 4:     iWidth = 192;   iHeight = 144;  break;
            default:    iWidth = 352;   iHeight = 288;  break;
        }
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_WIDTHCTRL :iWidth];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_HEIGHTCTRL :iHeight];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_BITRATECTRL :iVideoBitrate];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_FPSCTRL :iVideoFrameRate];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_PRESETCTRL :iVideoPreset];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_QUALITYCTRL :iVideoQuality];
        
        // 采用本地视频参数设置，使参数设置生效
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_APPLYPARAM :1];
    }
    
}


@end
