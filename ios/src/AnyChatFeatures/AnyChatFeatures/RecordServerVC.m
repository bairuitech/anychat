//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "RecordServerVC.h"
#import "ACVideoAlertView.h"
@interface RecordServerVC ()
{
    NSString            *theServerRecordMZTimerStatus;
    
    int theServerRecordFlags;
    int theRecordId;
}

@property (strong, nonatomic) UIActionSheet                 *theRecordVideoTypeActSheet;

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (weak, nonatomic) IBOutlet UIButton               *theServerFunBtn;
@property (weak, nonatomic) IBOutlet UILabel                *buttonTipLabel;


@property (weak, nonatomic) IBOutlet UILabel                *theVideoTimeLab;
@property (weak, nonatomic) IBOutlet UILabel                *theServerRecordTimeLab;
@property (strong, nonatomic) MZTimerLabel                  *theVideoMZTimer;
@property (strong, nonatomic) MZTimerLabel                  *theServerRecordMZTimer;

@property (strong, nonatomic) NSString                      *theCurrentRotation;
@property int iRemoteUserId;

@end

@implementation RecordServerVC


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
    [self.theServerRecordMZTimer pause];
    theServerRecordMZTimerStatus = @"pause";
}

- (void)p_configNavItem {
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(switchCameraBtn_OnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [button setImage:[UIImage imageNamed:@"video_switch"] forState:UIControlStateNormal];
    [button sizeToFit];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = rightItem;
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
#pragma mark ------ 业务核心代码 ------

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
//#warning todo  记得改回来
    [AnyChatPlatform SetVideoPos:userid: self.remoteVideoSurface:0:0:0:0];
//    [AnyChatPlatform SetVideoPos:userid: self:0:0:0:0];
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

#pragma mark -  Record Video Method

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
                theServerRecordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_LOCALCB + ANYCHAT_RECORD_FLAGS_SERVER;
                [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                                   : YES
                                                   : theServerRecordFlags
                                                   : 0
                                                   : @"StarServerSelfRecord"];
                break;
            }
            case 1:
            {
                //Remote recording
                theRecordId = self.iRemoteUserId;
                theServerRecordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_LOCALCB + ANYCHAT_RECORD_FLAGS_SERVER;
                [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                                   : YES
                                                   : theServerRecordFlags
                                                   : 0
                                                   : @"StarServerRemoteRecord"];
                break;
            }
            case 2:
            {
                //Max recording
                theRecordId = self.iRemoteUserId;
                theServerRecordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_MIXAUDIO + ANYCHAT_RECORD_FLAGS_MIXVIDEO + ANYCHAT_RECORD_FLAGS_ABREAST + ANYCHAT_RECORD_FLAGS_STEREO + ANYCHAT_RECORD_FLAGS_LOCALCB + ANYCHAT_RECORD_FLAGS_SERVER + ANYCHAT_RECORD_FLAGS_STREAM;
                [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                                   : YES
                                                   : theServerRecordFlags
                                                   : 0
                                                   : @"StarServerMaxRecord"];
                break;
            }
        }
        
        if (buttonIndex != 3)
        {
            //Show ServerRecord Time
            self.theServerRecordTimeLab.hidden = NO;
            [self.theServerRecordMZTimer reset];
            [self.theServerRecordMZTimer start];
            
            self.theServerFunBtn.selected = YES;
            self.buttonTipLabel.textColor = [UIColor colorWithRed:255/255.0 green:22/255.0 blue:41/255.0 alpha:1];
            
        }
    }
    
}


#pragma mark === ACTION ====
- (IBAction)theServerFunBtn_OnClicked:(id)sender
{
    if (self.theServerFunBtn.selected == NO)
    {
        //Server to record
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
        //Stop the server record
        [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                           : NO
                                           : theServerRecordFlags
                                           : 0
                                           : @"StopServerRecord"];
        //Close ServerRecord Time
        self.theServerRecordTimeLab.hidden = YES;
        [self.theServerRecordMZTimer pause];
        
        self.theServerFunBtn.selected = NO;
        self.buttonTipLabel.textColor = [UIColor whiteColor];

    }
}

- (IBAction)FinishVideoChatBtnClicked:(id)sender
{
    [ACVideoAlertView showAlertViewByTitle:@"是否想要结束当前通话？" clickBlock:^(NSInteger index) {
    
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

- (IBAction)speakerBtnClicked:(UIButton *)sender {
    sender.selected = !sender.isSelected;
    //开关本地声源
    [AnyChatPlatform UserSpeakControl:-1 :!sender.isSelected];
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



- (void)setTheTimer
{
    //The Timer Init
    self.theVideoMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theVideoTimeLab];
    self.theVideoMZTimer.timeFormat = @"HH:mm:ss";
    [self.theVideoMZTimer start];
    
    self.theServerRecordMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theServerRecordTimeLab];
    self.theServerRecordMZTimer.timeFormat = @"HH:mm:ss";
}

- (void)setUI
{
    NSString *targetUserName = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    self.title = [[NSString alloc] initWithFormat:@"与“%@”的对话",targetUserName];
    
    //Local View line
    self.theLocalView.layer.borderColor = [[UIColor redColor] CGColor];
    self.theLocalView.layer.borderWidth = 1.0f;
    //Rounded corners
    self.theLocalView.layer.cornerRadius = 4;
    self.theLocalView.layer.masksToBounds = YES;
    
    [self.theVideoMZTimer start];
    if ([theServerRecordMZTimerStatus isEqualToString:@"pause"])
    {
        [self.theServerRecordMZTimer start];
    }
    
    //disable the “idle timer” to avert system sleep.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}






#pragma mark -------------- ROTATION ------------
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

@end
