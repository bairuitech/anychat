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

@interface VideoViewController ()<UIActionSheetDelegate,UIGestureRecognizerDelegate>
@property(strong, nonatomic)AVCaptureVideoPreviewLayer  *localCaptureLayer;
@property (weak, nonatomic) IBOutlet UIView *localVideoView;
@property (weak, nonatomic) IBOutlet UIImageView *remoteVideoView;
@property (weak, nonatomic) IBOutlet UILabel *timerLabel;
- (IBAction)EndCallAction:(UIButton *)sender;

@end

@implementation VideoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self p_configNavItem];
    // 设置本地视频窗口的layer属性
    [self setLocalViewLayerStyle];
    // 开始视频通话
    [self StartVideoChat];
    // 切换imageView的contentMode
    [self.remoteVideoView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(changeContentModeFromImageView)]];
    self.view.backgroundColor = [UIColor blackColor];
    
    UIPanGestureRecognizer *pan = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePan:)];
    pan.delegate = self;
    [self.localVideoView addGestureRecognizer:pan];
    
    // 防止锁屏
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
    // 设置label计时器
    [self setTheTimerLabel];
    
}

- (void)p_configNavItem {
    {
        UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
        [button addTarget:self action:@selector(navLeftClick) forControlEvents:UIControlEventTouchUpInside];
        [button setImage:[UIImage imageNamed:@"icon_back"] forState:UIControlStateNormal];
        [button sizeToFit];
        
        UIBarButtonItem *leftItem = [[UIBarButtonItem alloc] initWithCustomView:button];
        self.navigationItem.leftBarButtonItem = leftItem;
    }
    {
        UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
        [button addTarget:self action:@selector(OnSwitchCameraBtnClicked:) forControlEvents:UIControlEventTouchUpInside];
        [button setImage:[UIImage imageNamed:@"video_switch"] forState:UIControlStateNormal];
        [button sizeToFit];
        
        UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:button];
        self.navigationItem.rightBarButtonItem = rightItem;
    }
}

- (void)navLeftClick {
    
    [self EndCallAction:nil];
    
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
    
//    [self btnSelectedOnClicked:sender];
}



- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    [self.navigationController.navigationBar setBackgroundImage:[UIImage new] forBarMetrics:UIBarMetricsDefault];
    [self.navigationController.navigationBar setShadowImage:[UIImage new]];

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
    
    //打开对方的视频
    [AnyChatPlatform UserSpeakControl:self.remoteUserId :YES];
    [AnyChatPlatform UserCameraControl:self.remoteUserId : YES];
    [AnyChatPlatform SetVideoPos:self.remoteUserId :self.remoteVideoView :0:0:0:0];
    
}

//创建和初始化 AVCaptureVideoPreviewLayer 对象,实现本地视频的显示
- (void) OnLocalVideoInit:(id)session {
    self.localCaptureLayer = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.localCaptureLayer.frame = CGRectMake(0, 0, 121, 162);
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
    theVideoMZTimer.timeFormat = @"HH:mm:ss";
    [theVideoMZTimer start];
}

#pragma mark - Action
- (IBAction)EndCallAction:(UIButton *)sender {
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"您确定是否结束当前的视频服务吗？" delegate:self cancelButtonTitle:@"取消" destructiveButtonTitle:@"确定" otherButtonTitles:nil, nil];
    actionSheet.delegate = self;
    [actionSheet showInView:self.view];
}

#pragma mark - action
- (void)handlePan:(UIPanGestureRecognizer*)recognizer {
    
    CGPoint translation = [recognizer translationInView:self.remoteVideoView];
    recognizer.view.center = CGPointMake(recognizer.view.center.x + translation.x,
                                         recognizer.view.center.y + translation.y);
    
//    NSLog(@"-------center x:%.2f y:%.2f",recognizer.view.center.x,recognizer.view.center.y);
    
    if (recognizer.view.frame.origin.x<2) {
        CGRect rect = recognizer.view.frame;
        rect.origin.x = 2;
        recognizer.view.frame = rect;
    }
    
    CGFloat rightX = self.view.frame.size.width -2 - recognizer.view.frame.size.width;
    if (recognizer.view.frame.origin.x > rightX) {
        NSLog(@"recognizer.view.x = %f",recognizer.view.frame.origin.x);
        CGRect rect = recognizer.view.frame;
        rect.origin.x =  rightX;
        recognizer.view.frame = rect;
        
    }
    
    if (recognizer.view.frame.origin.y<2) {
        CGRect rect = recognizer.view.frame;
        rect.origin.y = 2;
        recognizer.view.frame = rect;
    }
    
    CGFloat righty = self.view.frame.size.height -2 - recognizer.view.frame.size.height;
    if (recognizer.view.frame.origin.y > righty) {
        CGRect rect = recognizer.view.frame;
        rect.origin.y = righty;
        recognizer.view.frame = rect;
    }
    
    [recognizer setTranslation:CGPointZero inView:self.remoteVideoView];
}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
