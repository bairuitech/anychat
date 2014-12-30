//
//  VideoVC.m
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "VideoVC.h"

@interface VideoVC ()

@end

@implementation VideoVC

@synthesize iRemoteUserId;
@synthesize remoteVideoSurface;
@synthesize localVideoSurface;
@synthesize theLocalView;
@synthesize endCallBtn;
@synthesize switchCameraBtn;
@synthesize theLocolFunBtn;
@synthesize leftLineView;
@synthesize rightLineView;
@synthesize isFinishVideoActSheet;
@synthesize theVideoBitrateAlertView;
@synthesize theVideoNItem;
@synthesize theServerFunBtn;
@synthesize theFeaturesName;
@synthesize theTakePhotoPath;
@synthesize theCurrentRotation;
@synthesize theVideoPlayBackBtn;
@synthesize theVideoTimeLab;
@synthesize theVideoMZTimer;


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
    
    self.iRemoteUserId = [AnyChatVC sharedAnyChatVC].theTargetUserID;
    self.theFeaturesName = [AnyChatVC sharedAnyChatVC].theFeaturesName;
    [self StartVideoChat:self.iRemoteUserId];
    [self setTheTimer];

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


#pragma mark - Memory Warning method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark -
#pragma mark - UIActionSheet Delegate & Record Video Method

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (actionSheet == self.isFinishVideoActSheet)
    {
        if (buttonIndex == 0)
        {
            if ([self.theFeaturesName isEqualToString:@"呼叫中心"])
            {
                [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_FINISH :iRemoteUserId :0 :0 :0 :nil];
            }
            else
            {
                [self FinishVideoChat];
                [self.navigationController popViewControllerAnimated:YES];
            }
        }
    }
}

#pragma mark - AlertView delegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView == self.theVideoBitrateAlertView)
    {
        if (buttonIndex == 0)
        {
            [self FinishVideoChat];
            [self.navigationController popViewControllerAnimated:YES];
        }
    }
    
    self.theVideoBitrateAlertView = nil;
}


#pragma mark - Orientation Rotation

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (BOOL)shouldAutorotate
{
    return YES;
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
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


#pragma mark - Video Rotation

-(void)setFrameOfPortrait
{
    self.theCurrentRotation =@"Portrait";
    //Rotate
    remoteVideoSurface.layer.transform = kLayer_Z_Axis_3DRotation(0.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(0.0);
    //Scale
    self.remoteVideoSurface.frame = CGRectMake(0, 0, kSelfView_Width, kSelfView_Height);
    self.theLocalView.frame = kLocalVideoPortrait_CGRect;
}

-(void)setFrameOfLandscapeLeft
{
    self.theCurrentRotation =@"LandscapeLeft";
    //Rotate
    remoteVideoSurface.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);
    //Scale
    self.remoteVideoSurface.frame = CGRectMake(0, 0, kSelfView_Width, kSelfView_Height);
    self.theLocalView.frame = kLocalVideoLandscape_CGRect;
}

-(void)setFrameOfLandscapeRight
{
    self.theCurrentRotation =@"LandscapeRight";
    //Rotate
    remoteVideoSurface.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    //Scale
    self.remoteVideoSurface.frame = CGRectMake(0, 0, kSelfView_Width, kSelfView_Height);
    self.theLocalView.frame = kLocalVideoLandscape_CGRect;
}


#pragma mark -
#pragma mark - Instance Method

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
    [AnyChatPlatform SetVideoPos:userid: self.remoteVideoSurface:0:0:0:0];
    [AnyChatPlatform UserCameraControl:userid : YES];
    
    self.iRemoteUserId = userid;
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION : self.interfaceOrientation];
}

- (IBAction)theLocolFunBtn_OnClicked:(id)sender
{
    if (theLocolFunBtn.selected == NO)
    {
        if([self.theFeaturesName isEqualToString:@"音视频交互"] || [self.theFeaturesName isEqualToString:@"呼叫中心"])
        {   //本地声源.关
            [AnyChatPlatform UserSpeakControl:-1 :NO];
        }

        theLocolFunBtn.selected = YES;
    }
    else
    {
        if([self.theFeaturesName isEqualToString:@"音视频交互"] || [self.theFeaturesName isEqualToString:@"呼叫中心"])
        {   //本地声源.开
            [AnyChatPlatform UserSpeakControl: -1:YES];
        }

        theLocolFunBtn.selected = NO;
    }
    
    if ([self.theFeaturesName isEqualToString:@"视频抓拍"])
    {   // Local video SnapShot
        [theAudioPlayer play];
        [AnyChatPlatform SnapShot:-1 :BRAC_RECORD_FLAGS_SNAPSHOT :0];
    }
}

- (IBAction)theServerFunBtn_OnClicked:(id)sender
{
    if (theServerFunBtn.selected == NO)
    {

        if([self.theFeaturesName isEqualToString:@"音视频交互"] || [self.theFeaturesName isEqualToString:@"呼叫中心"])
        {
            if ([AnyChatPlatform GetCameraState:-1] == 2)
            {   //close local Camera
                [AnyChatPlatform UserCameraControl:-1 :NO];
                self.theLocalView.hidden = YES;
            }
        }
        
        theServerFunBtn.selected = YES;
    }
    else
    {
        if([self.theFeaturesName isEqualToString:@"音视频交互"] || [self.theFeaturesName isEqualToString:@"呼叫中心"])
        {
            if ([AnyChatPlatform GetCameraState:-1] == 1)
            {   //open local Camera
                [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
                [AnyChatPlatform UserCameraControl:-1 : YES];
                self.theLocalView.hidden = NO;
            }
        }
        
        theServerFunBtn.selected = NO;
    }
    
    if ([self.theFeaturesName isEqualToString:@"视频抓拍"])
    {   // RemoteUser video SnapShot
        [theAudioPlayer play];
        [AnyChatPlatform SnapShot:self.iRemoteUserId :BRAC_RECORD_FLAGS_SNAPSHOT :0];
    }
}

- (IBAction)FinishVideoChatBtnClicked:(id)sender
{
        self.isFinishVideoActSheet = [[UIActionSheet alloc]
                                      initWithTitle:@"确定结束会话?"
                                      delegate:self
                                      cancelButtonTitle:nil
                                      destructiveButtonTitle:nil
                                      otherButtonTitles:@"确定",@"取消", nil];
    
        self.isFinishVideoActSheet.actionSheetStyle = UIActionSheetStyleBlackOpaque;
        [self.isFinishVideoActSheet showInView:self.view];
}

- (void) FinishVideoChat
{
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
    
    [AnyChatPlatform UserSpeakControl: self.iRemoteUserId : NO];
    [AnyChatPlatform UserCameraControl: self.iRemoteUserId : NO];
    
    self.iRemoteUserId = -1;
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (IBAction) switchCameraBtn_OnClicked:(id)sender
{
    static int CurrentCameraDevice = 1;
    NSMutableArray* cameraDeviceArray = [AnyChatPlatform EnumVideoCapture];
    if(cameraDeviceArray.count == 2)
    {
        CurrentCameraDevice = (CurrentCameraDevice+1) % 2;
        [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:CurrentCameraDevice]];
    }
    
    [self btnSelectedOnClicked:switchCameraBtn];
}

- (IBAction)theVideoPlayBackBtn_OnClicked
{
    ShowVC *theShowVC = [ShowVC new];
    theShowVC.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
    [self.navigationController presentViewController:theShowVC animated:YES completion:nil];
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
    theVideoMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theVideoTimeLab];
    theVideoMZTimer.timeFormat = @"▷ HH:mm:ss";
    [theVideoMZTimer start];
}

- (void)setUI
{
    NSString *targetUserName = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    self.theVideoNItem.title = [[NSString alloc] initWithFormat:@"与“%@”视频中",targetUserName];
    
    if ([self.theFeaturesName isEqualToString:@"视频录像"])
    {
        [self.theLocolFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_offRecordVideo_Local"] forState:UIControlStateNormal];
        [self.theLocolFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_onRecordVideo_Local"] forState:UIControlStateSelected];
        [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_offRecordVideo_Server"] forState:UIControlStateNormal];
        [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_onRecordVideo_Server"] forState:UIControlStateSelected];

        self.theVideoPlayBackBtn.hidden = NO;
    }
    else if ([self.theFeaturesName isEqualToString:@"音视频交互"] || [self.theFeaturesName isEqualToString:@"呼叫中心"])
    {
        [self.theLocolFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_speak_on"] forState:UIControlStateNormal];
        [self.theLocolFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_speak_off"] forState:UIControlStateSelected];
        [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_camera_on"] forState:UIControlStateNormal];
        [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_camera_off"] forState:UIControlStateSelected];
    }
    else if ([self.theFeaturesName isEqualToString:@"视频抓拍"])
    {
        [self initWithTakePhotoSound];
        
        [self.theLocolFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_takePhoto_Local"] forState:UIControlStateNormal];
        [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_takePhoto_Server"] forState:UIControlStateNormal];
    }
    
    //Local View line
    theLocalView.layer.borderColor = [[UIColor whiteColor] CGColor];
    theLocalView.layer.borderWidth = 1.0f;
    //Rounded corners
    theLocalView.layer.cornerRadius = 4;
    theLocalView.layer.masksToBounds = YES;
    
    [theVideoMZTimer start];
}


@end
