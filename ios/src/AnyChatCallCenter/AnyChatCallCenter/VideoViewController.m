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
@synthesize localVideoSurface;
@synthesize theLocalView;
@synthesize endCallBtn;
@synthesize switchCameraBtn;
@synthesize voiceBtn;
@synthesize cameraBtn;


#pragma mark - Life Cycle

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

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUIControls];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - UIActionSheet Delegate Method

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0)
    {
       [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_FINISH :iRemoteUserId :0 :0 :0 :nil];
        
        [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:1]
                                              animated:YES];
    }
}


#pragma mark - Action Method

- (void) StartVideoChat:(int) userid
{
    //Get a camera, Must be in the real machine.
    NSMutableArray* cameraDeviceArray = [AnyChatPlatform EnumVideoCapture];
    if (cameraDeviceArray.count > 0)
    {
        [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:1]];
    }
    
    // open local video
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];
    [AnyChatPlatform UserSpeakControl: -1:YES];
    [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
    [AnyChatPlatform UserCameraControl:-1 : YES];
    
    // request other user video
    [AnyChatPlatform UserSpeakControl: userid:YES];
    [AnyChatPlatform SetVideoPos:userid: self.theUIImageView:0:0:0:0];
    [AnyChatPlatform UserCameraControl:userid : YES];
    
    self.iRemoteUserId = userid;
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION : self.interfaceOrientation];
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


- (IBAction)FinishVideoChatBtnClicked:(id)sender {
    
    HallViewController *hallVC = [[HallViewController alloc] init];
    [hallVC getOnlineUserList:[hallVC getOnlineUserArray]];
    [hallVC refreshTableView];
    
    UIActionSheet *isFinish = [[UIActionSheet alloc]
                               initWithTitle:@"确定结束会话?"
                               delegate:self
                               cancelButtonTitle:nil
                               destructiveButtonTitle:nil
                               otherButtonTitles:@"确定",@"取消", nil];
    isFinish.actionSheetStyle = UIActionSheetStyleBlackOpaque;
    [isFinish showInView:self.view];
}

- (IBAction)OnCloseVoiceBtnClicked:(id)sender
{
    if (voiceBtn.selected == NO)
    {
        [AnyChatPlatform UserSpeakControl:-1 :NO];
        voiceBtn.selected = YES;
    }
    else
    {
        [AnyChatPlatform UserSpeakControl: -1:YES];
        voiceBtn.selected = NO;
    }
}

- (IBAction)OnCloseCameraBtnClicked:(id)sender
{
    if ([AnyChatPlatform GetCameraState:-1] == 1)
    {   //open local Camera
        [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
        [AnyChatPlatform UserCameraControl:-1 : YES];
        self.theLocalView.hidden = NO;
        cameraBtn.selected = NO;
    }
    
    if ([AnyChatPlatform GetCameraState:-1] == 2)
    {   //close local Camera
        [AnyChatPlatform UserCameraControl:-1 :NO];
        self.theLocalView.hidden = YES;
        cameraBtn.selected = YES;
    }
}

- (void) btnSelectedOnClicked:(UIButton*)button
{
    if (button.selected)
    {
        button.selected = NO;
    }
    else
    {
        button.selected = YES;
    }
}

- (BOOL)prefersStatusBarHidden{
    return YES;
}

#pragma mark - Local Video

- (IBAction) OnSwitchCameraBtnClicked:(id)sender
{
    static int CurrentCameraDevice = 1;
    NSMutableArray* cameraDeviceArray = [AnyChatPlatform EnumVideoCapture];
    if(cameraDeviceArray.count == 2)
    {
        CurrentCameraDevice = (++CurrentCameraDevice) % 2;
        [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:CurrentCameraDevice]];
    }
    
    [self btnSelectedOnClicked:switchCameraBtn];
}

- (void) OnLocalVideoRelease:(id)sender
{
    if(self.localVideoSurface)
    {
        self.localVideoSurface = nil;
    }
}

- (void) OnLocalVideoInit:(id)session
{
    self.localVideoSurface = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.localVideoSurface.frame = CGRectMake(0, 0, kLocalVideo_Width, kLocalVideo_Height);
    self.localVideoSurface.videoGravity = AVLayerVideoGravityResizeAspectFill;
    
    [self.theLocalView.layer addSublayer:self.localVideoSurface];
}


#pragma mark - UI

- (void)setUIControls
{
    [switchCameraBtn setBackgroundImage:[UIImage imageNamed:@"Icon_camera_w_b"] forState:UIControlStateSelected];
    
    //Local View line
    theLocalView.layer.borderColor = [[UIColor whiteColor] CGColor];
    theLocalView.layer.borderWidth = 1.0f;
    //Rounded corners
    theLocalView.layer.cornerRadius = 4;
    theLocalView.layer.masksToBounds = YES;
}


@end
