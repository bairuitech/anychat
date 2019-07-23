//
//  RootViewController.m
//  AnyChatCallCenter
//
//  Created by alex on 14-1-27.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "VideoViewController.h"
#import "ACVideoAlertView.h"

@interface VideoViewController ()



@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) NSMutableArray                *theOnlineUserList;
@property (strong, nonatomic) IBOutlet UIImageView          *theUIImageView;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;


@property (weak, nonatomic) IBOutlet UIButton               *voiceBtn;
@property (weak, nonatomic) IBOutlet UIButton               *cameraBtn;

@property (weak, nonatomic) IBOutlet UILabel                *theVideoTimeLab;
@property (strong, nonatomic) MZTimerLabel                  *theVideoMZTimer;

@property (nonatomic, assign) int                            iRemoteUserId;
@end

@implementation VideoViewController


#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self StartVideoChat:self.theUserEntity.theEntityRemoteID];
    [self setTheTimer];
    [self p_configNavItem];
    self.title = [NSString stringWithFormat:@"与%@的对话", self.theUserEntity.theEntityRemoteName];
    
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];

}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUIControls];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
    //The Timer Pause
    [self.theVideoMZTimer pause];
}

-(void)navLeftClick {
    
    [self FinishVideoChatBtnClicked:nil];
}

-(BOOL)navBarTranslucent {
    
    return YES;
}

- (void)p_configNavItem {
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(OnSwitchCameraBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [button setImage:[UIImage imageNamed:@"video_switch"] forState:UIControlStateNormal];
    [button sizeToFit];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = rightItem;
}

#pragma mark - Action Method

- (void) StartVideoChat:(int) userid
{
    //Get a camera, Must be in the real machine.
    NSMutableArray* cameraDeviceArray = [AnyChatPlatform EnumVideoCapture];
    if (cameraDeviceArray.count > 0)
    {
        if(cameraDeviceArray.count >= 2)
            [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:1]];
        else
            [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:0]];
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
    
    
    [ACVideoAlertView showAlertViewByTitle:@"是否想要结束当前通话？" clickBlock:^(NSInteger index) {
        
        if(index == 0) {
            
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_FINISH :self.iRemoteUserId :0 :0 :0 :nil];
            [self FinishVideoChat];
            [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:1]
                                                  animated:YES];
        }
    }];
}

- (IBAction)OnCloseVoiceBtnClicked:(id)sender
{
    if (self.voiceBtn.selected == NO)
    {
        [AnyChatPlatform UserSpeakControl:-1 :NO];
        self.voiceBtn.selected = YES;
    }
    else
    {
        [AnyChatPlatform UserSpeakControl: -1:YES];
        self.voiceBtn.selected = NO;
    }
}

- (IBAction)OnCloseCameraBtnClicked:(id)sender
{
    if ([AnyChatPlatform GetCameraState:-1] == 1)
    {   //open local Camera
        [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
        [AnyChatPlatform UserCameraControl:-1 : YES];
        self.theLocalView.hidden = NO;
        self.cameraBtn.selected = NO;
    }
    
    if ([AnyChatPlatform GetCameraState:-1] == 2)
    {   //close local Camera
        [AnyChatPlatform UserCameraControl:-1 :NO];
        self.theLocalView.hidden = YES;
        self.cameraBtn.selected = YES;
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

#pragma mark - Local Video

- (void) OnSwitchCameraBtnClicked:(id)sender
{
    static int CurrentCameraDevice = 1;
    NSMutableArray* cameraDeviceArray = [AnyChatPlatform EnumVideoCapture];
    if(cameraDeviceArray.count == 2)
    {
        CurrentCameraDevice = (CurrentCameraDevice+1) % 2;
        [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:CurrentCameraDevice]];
    }
    
    [self btnSelectedOnClicked:sender];
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


- (BOOL)shouldAutorotate {
    return YES;
}
//返回直接支持的方向
- (UIInterfaceOrientationMask)supportedInterfaceOrientations{
    return UIInterfaceOrientationMaskAllButUpsideDown;
}
//返回最优先显示的屏幕方向
- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation {
    return UIInterfaceOrientationPortrait;
}


#pragma mark - UI

- (void)setUIControls
{
//    [self.switchCameraBtn setBackgroundImage:[UIImage imageNamed:@"Icon_camera_w_b"] forState:UIControlStateSelected];
    
    //Local View line
    self.theLocalView.layer.borderColor = [[UIColor whiteColor] CGColor];
    self.theLocalView.layer.borderWidth = 1.0f;
    //Rounded corners
    self.theLocalView.layer.cornerRadius = 4;
    self.theLocalView.layer.masksToBounds = YES;
    
    [self.theVideoMZTimer start];
}

- (void)setTheTimer
{
    //The Timer Init
    self.theVideoMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theVideoTimeLab];
    self.theVideoMZTimer.timeFormat = @"HH:mm:ss";
    [self.theVideoMZTimer start];
}

-(void)dealloc {
    NSLog(@"销毁了");
    [self FinishVideoChat];
}
@end
