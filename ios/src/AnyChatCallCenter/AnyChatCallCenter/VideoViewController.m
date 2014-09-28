//
//  RootViewController.m
//  AnyChatCallCenter
//
//  Created by alex on 14-1-27.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "VideoViewController.h"

@interface VideoViewController ()

@end

@implementation VideoViewController

@synthesize theUIImageView;
@synthesize theUserEntity;
@synthesize iRemoteUserId;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {

    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self StartVideoChat:theUserEntity.theEntityRemoteID];
}


#pragma mark - Action Method

- (void) StartVideoChat:(int) userid
{
    iRemoteUserId = userid;
    
    // open local video
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];
    [AnyChatPlatform UserSpeakControl: -1:YES];
    [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
    [AnyChatPlatform UserCameraControl:-1 : YES];
    
    // request other user video
    [AnyChatPlatform UserSpeakControl: userid:YES];
    [AnyChatPlatform SetVideoPos:userid: self.theUIImageView:0:0:0:0];
    [AnyChatPlatform UserCameraControl:userid : YES];
    
}


- (void) FinishVideoChat
{
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
    
    [AnyChatPlatform UserSpeakControl: self.iRemoteUserId : NO];
    [AnyChatPlatform UserCameraControl: self.iRemoteUserId : NO];
    
    self.iRemoteUserId = -1;
    [AnyChatPlatform LeaveRoom:-1];
    
}


- (IBAction)FinishVideoChat:(id)sender {
    
    HallViewController *hallVC = [[HallViewController alloc] init];
    [hallVC getOnlineUserList:[hallVC getOnlineUserArray]];
    [hallVC refreshTableView];
    
    [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_FINISH :iRemoteUserId :0 :0 :0 :nil];
    
    [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:1]
                                          animated:YES];
}


- (BOOL)prefersStatusBarHidden{
    return YES;
}


#pragma mark - Local Video

- (void) OnLocalVideoInit:(id)session
{
    self.thelocalVideoSurface = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.thelocalVideoSurface.frame = CGRectMake(5, 260, 120, 160);
    self.thelocalVideoSurface.videoGravity = AVLayerVideoGravityResizeAspectFill;
    
    [self.view.layer addSublayer: self.thelocalVideoSurface];
}

- (void) OnLocalVideoRelease:(id)sender
{
    if(self.thelocalVideoSurface)
    {
        self.thelocalVideoSurface = nil;
    }
}


#pragma mark - Memory Warning method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


@end
