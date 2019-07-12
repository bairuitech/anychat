//
//  RecordLocalVC.m
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "RecordLocalVC.h"
#import "ACVideoAlertView.h"

@interface RecordLocalVC ()
{
    NSString            *theLocalRecordMZTimerStatus;
    
    int theLocalRecordFlags;
    int theRecordId;
}

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) UIActionSheet                 *theRecordVideoTypeActSheet;
@property (strong, nonatomic) UIAlertView                   *theVideoBitrateAlertView;

@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;

@property (weak, nonatomic) IBOutlet UIButton               *theLocolFunBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theVideoTimeLab;
@property (weak, nonatomic) IBOutlet UILabel                *theLocalRecordTimeLab;
@property (strong, nonatomic) NSString                      *theCurrentRotation;
@property (strong, nonatomic) MZTimerLabel                  *theVideoMZTimer;
@property (strong, nonatomic) MZTimerLabel                  *theLocalRecordMZTimer;
@property int iRemoteUserId;

@property (weak, nonatomic) IBOutlet UILabel *buttonTipLabel;

@end

@implementation RecordLocalVC



#pragma mark -
#pragma mark - Life cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.iRemoteUserId = [AnyChatVC sharedAnyChatVC].theTargetUserID;
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

-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
    //The Timer Pause
    [self.theVideoMZTimer pause];
    [self.theLocalRecordMZTimer pause];
    theLocalRecordMZTimerStatus = @"pause";
}

- (void)p_configNavItem {
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(switchCameraBtn_OnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [button setImage:[UIImage imageNamed:@"video_switch"] forState:UIControlStateNormal];
    [button sizeToFit];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = rightItem;
    
    UIButton *button1 = [UIButton buttonWithType:UIButtonTypeCustom];
    [button1 addTarget:self action:@selector(theVideoPlayBackBtn_OnClicked) forControlEvents:UIControlEventTouchUpInside];
    [button1 setImage:[UIImage imageNamed:@"record_video_list"] forState:UIControlStateNormal];
    [button1 sizeToFit];
    
    UIBarButtonItem *leftItem = [[UIBarButtonItem alloc] initWithCustomView:button1];
    self.navigationItem.leftBarButtonItem = leftItem;
}

-(BOOL)navBarTranslucent {
    
    return YES;
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
#pragma mark ---- 业务核心代码 -------
#pragma mark - (音视频固定方法) -

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

#pragma mark - UIActionSheet Delegate

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    
    if (actionSheet == self.theRecordVideoTypeActSheet)
    {
        switch (buttonIndex)
        {
            case 0:
            {
                //Self recording
                theRecordId = -1;
                theLocalRecordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_LOCALCB;
                [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                                   : YES
                                                   : theLocalRecordFlags
                                                   : 0
                                                   : @"StarLocolSelfRecord"];
                
                break;
            }
            case 1:
            {
                //Remote recording
                theRecordId = self.iRemoteUserId;
                theLocalRecordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_LOCALCB;
                [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                                   : YES
                                                   : theLocalRecordFlags
                                                   : 0
                                                   : @"StarLocolRemoteRecord"];
                break;
            }
            case 2:
            {
                //Max recording
                theRecordId = self.iRemoteUserId;
                theLocalRecordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_LOCALCB + ANYCHAT_RECORD_FLAGS_MIXAUDIO + ANYCHAT_RECORD_FLAGS_MIXVIDEO + ANYCHAT_RECORD_FLAGS_ABREAST + ANYCHAT_RECORD_FLAGS_STEREO;
                [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                                   : YES
                                                   : theLocalRecordFlags
                                                   : 0
                                                   : @"StarLocolMaxRecord"];
                break;
            }
        }
        
        if (buttonIndex != 3)
        {
            //Show LocalRecord Time
            self.theLocalRecordTimeLab.hidden = NO;
            [self.theLocalRecordMZTimer reset];
            [self.theLocalRecordMZTimer start];
            
            self.theLocolFunBtn.selected = YES;
            self.buttonTipLabel.textColor = [UIColor colorWithRed:255/255.0 green:22/255.0 blue:41/255.0 alpha:1];
        }
    }
}



#pragma mark ---------- ACTION ---------
- (IBAction)theLocolFunBtn_OnClicked:(id)sender
{
    if (self.theLocolFunBtn.selected == NO)
    {
        self.theRecordVideoTypeActSheet = [[UIActionSheet alloc]
                                           initWithTitle:@"请选择录制的类型。"
                                           delegate:self
                                           cancelButtonTitle:nil
                                           destructiveButtonTitle:nil
                                           otherButtonTitles:@"录制自己",@"录制对方",@"合成录制",@"取消", nil];
        
        self.theRecordVideoTypeActSheet.actionSheetStyle = UIActionSheetStyleBlackOpaque;
        [self.theRecordVideoTypeActSheet showInView:self.view];
    }
    else
    {
        //Stop recording local
        [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                           : NO
                                           : theLocalRecordFlags
                                           : 0
                                           : @"StopLocolRecord"];
        //Close LocalRecord Time
        self.theLocalRecordTimeLab.hidden = YES;
        [self.theLocalRecordMZTimer pause];
        self.buttonTipLabel.textColor = [UIColor whiteColor];

        self.theLocolFunBtn.selected = NO;
    }
}

- (IBAction)FinishVideoChatBtnClicked:(id)sender
{
    
    [ACVideoAlertView showAlertViewByTitle:@"是否想要结束当前录像?" clickBlock:^(NSInteger index) {
       
        if(index == 0) {
            
            [self FinishVideoChat];
            [self.navigationController popViewControllerAnimated:YES];
        }
    }];
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
    
    [self btnSelectedOnClicked:sender];
}

- (IBAction)theVideoPlayBackBtn_OnClicked
{

    [self presentShowVC];
}
    
- (IBAction)speakerBtnClicked:(UIButton *)sender {
    sender.selected = !sender.isSelected;
    //开关本地声源
    [AnyChatPlatform UserSpeakControl:-1 :!sender.isSelected];
}
    

- (IBAction)changeContentModeFromImageView
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







- (void)setTheTimer
{
    //The Timer Init
    self.theVideoMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theVideoTimeLab];
    self.theVideoMZTimer.timeFormat = @"HH:mm:ss";
    [_theVideoMZTimer start];
    
    _theLocalRecordMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theLocalRecordTimeLab];
    _theLocalRecordMZTimer.timeFormat = @"HH:mm:ss";
}

- (void)setUI
{
    NSString *targetUserName = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    self.title = [[NSString alloc] initWithFormat:@"与“%@”的会话",targetUserName];
    
    //Local View line
    _theLocalView.layer.borderColor = [[UIColor whiteColor] CGColor];
    _theLocalView.layer.borderWidth = 1.0f;
    //Rounded corners
    _theLocalView.layer.cornerRadius = 4;
    _theLocalView.layer.masksToBounds = YES;
    
    [_theVideoMZTimer start];
    if ([theLocalRecordMZTimerStatus isEqualToString:@"pause"])
    {
        [self.theLocalRecordMZTimer start];
    }
    
    //disable the “idle timer” to avert system sleep.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
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
    self.remoteVideoSurface.layer.transform = kLayer_Z_Axis_3DRotation(0.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(0.0);
    //Scale
    self.remoteVideoSurface.frame = CGRectMake(0, 0, kSelfView_Width, kSelfView_Height);
    self.theLocalView.frame = kLocalVideoPortrait_CGRect;
}

-(void)setFrameOfLandscapeLeft
{
    self.theCurrentRotation =@"LandscapeLeft";
    //Rotate
    self.remoteVideoSurface.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);
    //Scale
    self.remoteVideoSurface.frame = CGRectMake(0, 0, kSelfView_Width, kSelfView_Height);
    self.theLocalView.frame = kLocalVideoLandscape_CGRect;
}

-(void)setFrameOfLandscapeRight
{
    self.theCurrentRotation =@"LandscapeRight";
    //Rotate
    self.remoteVideoSurface.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    //Scale
    self.remoteVideoSurface.frame = CGRectMake(0, 0, kSelfView_Width, kSelfView_Height);
    self.theLocalView.frame = kLocalVideoLandscape_CGRect;
}

@end
