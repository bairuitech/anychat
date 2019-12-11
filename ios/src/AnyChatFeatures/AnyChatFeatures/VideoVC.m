//
//  VideoVC.m
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "VideoVC.h"
#import "ACVideoAlertView.h"
@interface VideoVC ()
{
    
    AVAudioPlayer       *theAudioPlayer;
}



@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (weak, nonatomic) IBOutlet UIButton               *theLocolFunBtn;
@property (weak, nonatomic) IBOutlet UIButton               *theServerFunBtn;

@property (weak, nonatomic) IBOutlet UILabel                *theVideoTimeLab;
@property (strong, nonatomic) MZTimerLabel                  *theVideoMZTimer;

@property (strong, nonatomic) NSString                      *theFeaturesName;
@property (strong, nonatomic) NSString                      *theCurrentRotation;

@property (assign, nonatomic) int iRemoteUserId;
@property (weak, nonatomic) IBOutlet UILabel *leftButtonTipLabel;
@property (weak, nonatomic) IBOutlet UILabel *rightButtonTipLabel;

@end

@implementation VideoVC


#pragma mark -
#pragma mark - Life cycle

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self){
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.view.layer.masksToBounds = YES;
    self.iRemoteUserId = [AnyChatVC sharedAnyChatVC].theTargetUserID;
    self.theFeaturesName = [AnyChatVC sharedAnyChatVC].theFeaturesName;
    [self StartVideoChat:self.iRemoteUserId];
    [self setTheTimer];
    [self p_configNavItem];
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];

}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUI];
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
    //The Timer Pause
    [self.theVideoMZTimer pause];
}

- (void)p_configNavItem {
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(switchCameraBtn_OnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [button setImage:[UIImage imageNamed:@"video_switch"] forState:UIControlStateNormal];
    [button sizeToFit];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = rightItem;
}

-(void)navLeftClick {
    
    [self FinishVideoChatBtnClicked:nil];
}

-(BOOL)navBarTranslucent {
    
    return YES;
}
#pragma mark - Memory Warning method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark -
#pragma mark ----- 业务核心代码 -----

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
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION : self.interfaceOrientation];
}

- (void) FinishVideoChat
{
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
    
    [AnyChatPlatform UserSpeakControl: self.iRemoteUserId : NO];
    [AnyChatPlatform UserCameraControl: self.iRemoteUserId : NO];
    
    self.iRemoteUserId = -1;
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


- (IBAction)theLocolFunBtn_OnClicked:(id)sender
{


    self.theLocolFunBtn.selected = !self.theLocolFunBtn.selected;
    //当前 selected = YES, 则关闭声音；否则，打开声音
    if([self.theFeaturesName isEqualToString:@"音视频交互"] || [self.theFeaturesName isEqualToString:@"呼叫中心"]) {
        
        [AnyChatPlatform UserSpeakControl:-1 :!self.theLocolFunBtn.selected];
    } else if ([self.theFeaturesName isEqualToString:@"视频抓拍"])
    {   // Local video SnapShot
        [theAudioPlayer play];
        [AnyChatPlatform SnapShot:-1 :BRAC_RECORD_FLAGS_SNAPSHOT :0];
    }
}

//[AnyChatPlatform GetCameraState:-1]  0 没有摄像头  1 有摄像头但没有打开 2 摄像头已打开
- (IBAction)theServerFunBtn_OnClicked:(id)sender
{

    if([self.theFeaturesName isEqualToString:@"音视频交互"] || [self.theFeaturesName isEqualToString:@"呼叫中心"]) {
        
        if (self.theServerFunBtn.selected == NO)  {
            
            if ([AnyChatPlatform GetCameraState:-1] == 2)//摄像头已打开
            {
                //close local Camera 关闭本地摄像头
                [AnyChatPlatform UserCameraControl:-1 :NO];
            }
            self.theLocalView.hidden = YES;
            self.theServerFunBtn.selected = YES;

        } else  {
            
            if ([AnyChatPlatform GetCameraState:-1] == 1)//有摄像头但没有打开
            {
                //open local Camera 打开本地摄像头
                [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
                [AnyChatPlatform UserCameraControl:-1 : YES];
            }
            self.theLocalView.hidden = NO;
            self.theServerFunBtn.selected = NO;
        }
        

    } else if ([self.theFeaturesName isEqualToString:@"视频抓拍"]) {
       
        // RemoteUser video SnapShot
        [theAudioPlayer play];
        [AnyChatPlatform SnapShot:self.iRemoteUserId :BRAC_RECORD_FLAGS_SNAPSHOT :0];
    }

}

- (IBAction)FinishVideoChatBtnClicked:(id)sender
{

    
    [ACVideoAlertView showAlertViewByTitle:@"是否想要结束当前通话？" clickBlock:^(NSInteger index) {
       
        if(index == 0) {
            
            if ([self.theFeaturesName isEqualToString:@"呼叫中心"])
            {
                [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_FINISH :self.iRemoteUserId :0 :0 :0 :nil];
            }
            [self FinishVideoChat];
            [self.navigationController popViewControllerAnimated:YES];
        }
    }];
}



#pragma mark action
- (void) switchCameraBtn_OnClicked:(UIButton *)button
{
    static int CurrentCameraDevice = 1;
    NSMutableArray* cameraDeviceArray = [AnyChatPlatform EnumVideoCapture];
    if(cameraDeviceArray.count == 2)
    {
        CurrentCameraDevice = (CurrentCameraDevice+1) % 2;
        [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:CurrentCameraDevice]];
    }
    
    [self btnSelectedOnClicked:button];
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


#pragma mark - others -
//iRemote user video loading status
-(BOOL)remoteVideoDidLoadStatus
{
    BOOL isDidLoad = NO;
    int videoHeight = 0;
    int theTimes = 0;
    
    while (isDidLoad == NO && theTimes < 5000)
    {
        videoHeight = [AnyChatPlatform GetUserVideoHeight:self.iRemoteUserId];
        
        if (videoHeight > 0) {
            isDidLoad = YES;
        }
        else
        {
            isDidLoad = NO;
            theTimes++;
        }
    }
    
    return isDidLoad;
}

- (void)initWithTakePhotoSound
{
    NSString *musicPath = [[NSBundle mainBundle] pathForResource:@"sound_takePhoto"
                                                          ofType:@"wav"];
    if (musicPath)
    {
        NSURL *musicURL = [NSURL fileURLWithPath:musicPath];
        theAudioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:musicURL
                                                                error:nil];
    }
}

- (void)setTheTimer
{
    //The Timer Init
    self.theVideoMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theVideoTimeLab];
    self.theVideoMZTimer.timeFormat = @"HH:mm:ss";
    [self.theVideoMZTimer start];
}

- (void)setUI
{
    NSString *targetUserName = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    self.title = [[NSString alloc] initWithFormat:@"与“%@”的对话",targetUserName];
    
    if ([self.theFeaturesName isEqualToString:@"音视频交互"] || [self.theFeaturesName isEqualToString:@"呼叫中心"])// 开关音频  开关视频
    {
        [self.theLocolFunBtn setBackgroundImage:[UIImage imageNamed:@"video_audio_on"] forState:UIControlStateNormal];
        [self.theLocolFunBtn setBackgroundImage:[UIImage imageNamed:@"video_audio_off"] forState:UIControlStateSelected];
        [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"video_video_on"] forState:UIControlStateNormal];
        [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"video_video_off"] forState:UIControlStateSelected];
        self.leftButtonTipLabel.text = @"语音";
        self.rightButtonTipLabel.text = @"视频";
    }
    else if ([self.theFeaturesName isEqualToString:@"视频抓拍"])//自拍 拍照
    {
        [self initWithTakePhotoSound];
        
        [self.theLocolFunBtn setBackgroundImage:[UIImage imageNamed:@"snap_local"] forState:UIControlStateNormal];
        [self.theLocolFunBtn setBackgroundImage:nil forState:UIControlStateSelected];
        [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"snap_server"] forState:UIControlStateNormal];
        [self.theServerFunBtn setBackgroundImage:nil forState:UIControlStateSelected];
        self.leftButtonTipLabel.text = @"自拍";
        self.rightButtonTipLabel.text = @"拍照";
    }
    
    //Local View line
    self.theLocalView.layer.borderColor = [[UIColor whiteColor] CGColor];
    self.theLocalView.layer.borderWidth = 1.0f;
    //Rounded corners
    self.theLocalView.layer.cornerRadius = 4;
    self.theLocalView.layer.masksToBounds = YES;
    
    [self.theVideoMZTimer start];
    
    //disable the “idle timer” to avert system sleep.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
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
    self.theCurrentRotation =@"Portrait";
    //Rotate
    self.remoteVideoSurface.layer.transform = kLayer_Z_Axis_3DRotation(0.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(0.0);

}

-(void)setFrameOfLandscapeLeft
{
    self.theCurrentRotation =@"LandscapeLeft";
    //Rotate
    self.remoteVideoSurface.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);

}

-(void)setFrameOfLandscapeRight
{
    self.theCurrentRotation =@"LandscapeRight";
    //Rotate
    self.remoteVideoSurface.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
}

@end
