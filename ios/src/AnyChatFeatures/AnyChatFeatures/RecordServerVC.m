//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "RecordServerVC.h"

@interface RecordServerVC ()

@end

@implementation RecordServerVC

@synthesize iRemoteUserId;
@synthesize remoteVideoSurface;
@synthesize localVideoSurface;
@synthesize theLocalView;
@synthesize endCallBtn;
@synthesize switchCameraBtn;
@synthesize leftLineView;
@synthesize isFinishVideoActSheet;
@synthesize theVideoNItem;
@synthesize theServerFunBtn;
@synthesize theFeaturesName;
@synthesize theTakePhotoPath;
@synthesize theCurrentRotation;
@synthesize theServerRecordTimeLab;
@synthesize theVideoTimeLab;
@synthesize theVideoMZTimer;
@synthesize theServerRecordMZTimer;
@synthesize theRecordVideoTypeActSheet;


#pragma mark -
#pragma mark - Life cycle

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

-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
    //The Timer Pause
    [self.theVideoMZTimer pause];
    [self.theServerRecordMZTimer pause];
    theServerRecordMZTimerStatus = @"pause";
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
                [self FinishVideoChat];
                [self.navigationController popViewControllerAnimated:YES];
        }
    }
    
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
                theServerRecordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_MIXAUDIO + ANYCHAT_RECORD_FLAGS_MIXVIDEO + ANYCHAT_RECORD_FLAGS_ABREAST + ANYCHAT_RECORD_FLAGS_STEREO + ANYCHAT_RECORD_FLAGS_LOCALCB + ANYCHAT_RECORD_FLAGS_SERVER;
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
            [theServerRecordMZTimer reset];
            [theServerRecordMZTimer start];
            
            theServerFunBtn.selected = YES;
        }
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

- (IBAction)theServerFunBtn_OnClicked:(id)sender
{
    if (theServerFunBtn.selected == NO)
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
        [theServerRecordMZTimer pause];
        
        theServerFunBtn.selected = NO;
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
    theVideoMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theVideoTimeLab];
    theVideoMZTimer.timeFormat = @"▷ HH:mm:ss";
    [theVideoMZTimer start];
    
    theServerRecordMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theServerRecordTimeLab];
    theServerRecordMZTimer.timeFormat = @"HH:mm:ss";
}

- (void)setUI
{
    NSString *targetUserName = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    self.theVideoNItem.title = [[NSString alloc] initWithFormat:@"与“%@”视频中",targetUserName];
    
    [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_offRecordVideo_Server"] forState:UIControlStateNormal];
    [self.theServerFunBtn setBackgroundImage:[UIImage imageNamed:@"Icon_onRecordVideo_Server"] forState:UIControlStateSelected];
    
    //Local View line
    theLocalView.layer.borderColor = [[UIColor whiteColor] CGColor];
    theLocalView.layer.borderWidth = 1.0f;
    //Rounded corners
    theLocalView.layer.cornerRadius = 4;
    theLocalView.layer.masksToBounds = YES;
    
    [theVideoMZTimer start];
    if ([theServerRecordMZTimerStatus isEqualToString:@"pause"])
    {
        [self.theServerRecordMZTimer start];
    }
    
    //disable the “idle timer” to avert system sleep.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}



@end
