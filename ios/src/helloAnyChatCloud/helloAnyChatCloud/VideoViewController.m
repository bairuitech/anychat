//
//  RootViewController.m
//  AnyChatCallCenter
//
//  Created by alex on 14-1-27.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "VideoViewController.h"

@interface VideoViewController ()


@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (weak, nonatomic) IBOutlet UIButton               *voiceBtn;
@property (weak, nonatomic) IBOutlet UIButton               *cameraBtn;

@end

@implementation VideoViewController

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
   
    self.title = [[NSString alloc] initWithFormat:@"与“%@”的会话",self.remoteUserName];

    [self StartVideoChat:self.iRemoteUserId];
    
    [self p_configNavItem];
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUIControls];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:YES];
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

-(void)navLeftClick {
    
    [self FinishVideoChatBtnClicked:nil];
}
#pragma mark - Memory Warning method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark -
#pragma mark ------ 核心代码 -------


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
    [AnyChatPlatform SetVideoPos:userid: self.remoteVideoSurface:0:0:0:0];
    [AnyChatPlatform UserCameraControl:userid : YES];
    
    self.iRemoteUserId = userid;
    //远程视频显示时随设备的方向改变而旋转（参数为int型， 0表示关闭， 1 开启[默认]，视频旋转时需要参考本地视频设备方向参数）
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION : self.interfaceOrientation];
}

- (void) FinishVideoChat
{
    // 关闭摄像头
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
    
    [AnyChatPlatform UserSpeakControl: self.iRemoteUserId : NO];
    [AnyChatPlatform UserCameraControl: self.iRemoteUserId : NO];
    
    self.iRemoteUserId = -1;
    
    AnyChatViewController *videoVC = [AnyChatViewController new];
    videoVC.onlineUserMArray = [videoVC getOnlineUserArray];
    
    [self.navigationController popViewControllerAnimated:YES];
}

- (void) OnLocalVideoRelease:(id)sender
{
    if(self.localVideoSurface) {
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


#pragma mark - ACTION ------
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

- (IBAction)FinishVideoChatBtnClicked:(id)sender
{
    UIActionSheet *isFinish = [[UIActionSheet alloc]
                               initWithTitle:@"确定结束会话?"
                               delegate:self
                               cancelButtonTitle:nil
                               destructiveButtonTitle:nil
                               otherButtonTitles:@"确定",@"取消", nil];
    isFinish.actionSheetStyle = UIActionSheetStyleBlackOpaque;
    [isFinish showInView:self.view];
}

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





- (IBAction)changeContentModeFromImageView:(id)sender
{
    if (self.remoteVideoSurface.contentMode == UIViewContentModeScaleAspectFit)
    {
        self.remoteVideoSurface.contentMode = UIViewContentModeScaleAspectFill;
    }
    else if (self.remoteVideoSurface.contentMode == UIViewContentModeScaleAspectFill)
    {
        self.remoteVideoSurface.contentMode = UIViewContentModeScaleAspectFit;
    }
}
#pragma mark - UIActionSheet Delegate Method

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0) {
        [self FinishVideoChat];
    }
}


#pragma mark - Orientation Rotation


-(void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    //device orientation
    UIDeviceOrientation devOrientation = [UIDevice currentDevice].orientation;
    
    if (devOrientation == UIDeviceOrientationLandscapeLeft)
    {
        [self setFrameOfLandscapeLeft];
    }
    else if (devOrientation == UIDeviceOrientationLandscapeRight)
    {
        [self setFrameOfLandscapeRight];
    }
    if (devOrientation == UIDeviceOrientationPortrait)
    {
        [self setFrameOfPortrait];
    }
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

#pragma mark - Video Rotation

-(void)setFrameOfPortrait
{
    //Rotate
    self.remoteVideoSurface.layer.transform = kLayer3DRotation_Z_Axis(0.0);
    self.theLocalView.layer.transform = kLayer3DRotation_Z_Axis(0.0);

}

-(void)setFrameOfLandscapeLeft
{
    //Rotate
    self.remoteVideoSurface.layer.transform = kLayer3DRotation_Z_Axis(-90.0);
    self.theLocalView.layer.transform = kLayer3DRotation_Z_Axis(-90.0);

}

-(void)setFrameOfLandscapeRight
{
    //Rotate
    self.remoteVideoSurface.layer.transform = kLayer3DRotation_Z_Axis(90.0);
    self.theLocalView.layer.transform = kLayer3DRotation_Z_Axis(90.0);

}



- (void)setUIControls
{
    
    //Local View line
    self.theLocalView.layer.borderColor = [[UIColor whiteColor] CGColor];
    self.theLocalView.layer.borderWidth = 1.0f;
    //Rounded corners
    self.theLocalView.layer.cornerRadius = 4;
    self.theLocalView.layer.masksToBounds = YES;
    
    //disable the “idle timer” to avert system sleep.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}

- (void)btnSelectedOnClicked:(UIButton*)button
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

@end
