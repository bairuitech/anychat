//
//  VideoViewController.m
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "VideoViewController.h"
#import "BusinessListController.h"
#import <AVFoundation/AVFoundation.h>
#import "MZTimerLabel.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface VideoViewController ()<UIActionSheetDelegate>
@property(strong, nonatomic)AVCaptureVideoPreviewLayer  *localCaptureLayer;
@property (weak, nonatomic) IBOutlet UIView *localVideoView;
@property (weak, nonatomic) IBOutlet UIImageView *remoteVideoView;
@property (weak, nonatomic) IBOutlet UILabel *timerLabel;
- (IBAction)EndCallAction:(UIButton *)sender;

@end

@implementation VideoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // 设置本地视频窗口的layer属性
    [self setLocalViewLayerStyle];
    // 开始视频通话
    [self StartVideoChat];
    // 切换imageView的contentMode
    [self.remoteVideoView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(changeContentModeFromImageView)]];
    self.view.backgroundColor = [UIColor blackColor];
    
    // 防止锁屏
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
    // 设置label计时器
    [self setTheTimerLabel];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    self.navigationController.navigationBarHidden = YES;
}

- (void)orientationChanged:(NSNotification *)note  {
    UIDeviceOrientation o = [[UIDevice currentDevice] orientation];
    switch (o) {
        case UIDeviceOrientationPortrait:            // Device oriented vertically, home button on the bottom
            [AnyChatPlatform UserInfoControl:self.remoteUserId :BRAC_USERINFO_CTRLCODE_ROTATION :0 :0 :nil];
            self.localVideoView.transform = CGAffineTransformIdentity;
            break;
        case UIDeviceOrientationPortraitUpsideDown:  // Device oriented vertically, home button on the top
            break;
        case UIDeviceOrientationLandscapeLeft:      // Device oriented horizontally, home button on the right
            [AnyChatPlatform UserInfoControl:self.remoteUserId :BRAC_USERINFO_CTRLCODE_ROTATION :BRAC_ROTATION_FLAGS_ROTATION270 :0 :nil];
            self.localVideoView.transform = CGAffineTransformMakeRotation((270.0f * M_PI) / 180.0f);
            break;
        case UIDeviceOrientationLandscapeRight:      // Device oriented horizontally, home button on the left
            [AnyChatPlatform UserInfoControl:self.remoteUserId :BRAC_USERINFO_CTRLCODE_ROTATION :BRAC_ROTATION_FLAGS_ROTATION90 :0 :nil];
            self.localVideoView.transform = CGAffineTransformMakeRotation((90.0f * M_PI) / 180.0f);
            
            break;
        default:
            break;
    }
}


-(void)viewWillDisappear:(BOOL)animated {
    
    NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
    UIDevice *device = [UIDevice currentDevice]; //Get the device object
    [nc removeObserver:self name:UIDeviceOrientationDidChangeNotification object:device];
}

- (void)viewDidAppear:(BOOL)animated {
    // Do any additional setup after loading the view from its nib.
    //----- SETUP DEVICE ORIENTATION CHANGE NOTIFICATION -----
    UIDevice *device = [UIDevice currentDevice]; //Get the device object
    [device beginGeneratingDeviceOrientationNotifications]; //Tell it to start monitoring the accelerometer for orientation
    NSNotificationCenter *nc = [NSNotificationCenter defaultCenter]; //Get the notification centre for the app
    [nc addObserver:self selector:@selector(orientationChanged:) name:UIDeviceOrientationDidChangeNotification  object:device];
}

#pragma mark - UIActionSheetDelegate
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {
        // 结束呼叫通话
        [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_FINISH :self.remoteUserId :0 :0 :0 :nil];
    }
}

#pragma mark - Custom Method
// 设置本地视频窗口的layer属性
- (void)setLocalViewLayerStyle {
    self.localVideoView.layer.borderColor = [[UIColor whiteColor] CGColor];
    self.localVideoView.layer.borderWidth = 1.0f;
    self.localVideoView.layer.cornerRadius = 4;
    self.localVideoView.layer.masksToBounds = YES;
}

//打开对方的视频
-(void)openRemoteView
{
    [AnyChatPlatform UserSpeakControl:self.remoteUserId :YES];
    [AnyChatPlatform UserCameraControl:self.remoteUserId : YES];
    [AnyChatPlatform SetVideoPos:self.remoteUserId :self.remoteVideoView :0:0:0:0];
}


// 开始视频通话
- (void)StartVideoChat
{
    // 枚举本地视频采集设备
    NSMutableArray* videoDeviceArray = [AnyChatPlatform EnumVideoCapture];
    // 选择指定的视频采集设备
    if (videoDeviceArray.count > 0) [AnyChatPlatform SelectVideoCapture:[videoDeviceArray objectAtIndex:1]];
    
    //设置本地视频采用 Overlay 模式
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];
    [AnyChatPlatform UserSpeakControl: -1:YES];
    [AnyChatPlatform UserCameraControl:-1 : YES];
    [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
    
//    [AnyChatPlatform UserSpeakControl:self.remoteUserId :YES];
//    [AnyChatPlatform UserCameraControl:self.remoteUserId : YES];
//    [AnyChatPlatform SetVideoPos:self.remoteUserId :self.remoteVideoView :0:0:0:0];
    
}

//创建和初始化 AVCaptureVideoPreviewLayer 对象,实现本地视频的显示
- (void) OnLocalVideoInit:(id)session {
    self.localCaptureLayer = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.localCaptureLayer.frame = CGRectMake(0, 0, 100, 130);
    self.localCaptureLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    [self.localVideoView.layer addSublayer:self.localCaptureLayer];
}

- (void) OnLocalVideoRelease:(id)sender {
    if(self.localCaptureLayer) self.localCaptureLayer = nil;
}

//手势双击 切换ImageView的contentMode模式
- (void)changeContentModeFromImageView
{
    if (self.remoteVideoView.contentMode == UIViewContentModeScaleAspectFit) {
        //等比例放大，截图（全屏效果）
        self.remoteVideoView.contentMode = UIViewContentModeScaleAspectFill;
    }
    else if (self.remoteVideoView.contentMode == UIViewContentModeScaleAspectFill) {
        //等比例缩小，显示完整图片，窗口左右留白
        self.remoteVideoView.contentMode = UIViewContentModeScaleAspectFit;
    }
}

// 设置label计时器
- (void)setTheTimerLabel
{
    //The Timer Init
    MZTimerLabel *theVideoMZTimer = [[MZTimerLabel alloc]initWithLabel:self.timerLabel];
    theVideoMZTimer.timeFormat = @"▷ HH:mm:ss";
    [theVideoMZTimer start];
}

#pragma mark - Action
- (IBAction)EndCallAction:(UIButton *)sender {
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"您确定是否结束当前的视频服务吗？" delegate:self cancelButtonTitle:@"取消" destructiveButtonTitle:@"确定" otherButtonTitles:nil, nil];
    actionSheet.delegate = self;
    [actionSheet showInView:self.view];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
