//
//  RecordLocalVC.m
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "RecordLocalVC.h"

@interface RecordLocalVC ()

@end

@implementation RecordLocalVC

@synthesize iRemoteUserId;
@synthesize remoteVideoSurface;
@synthesize localVideoSurface;
@synthesize theLocalView;
@synthesize endCallBtn;
@synthesize switchCameraBtn;
@synthesize theLocolFunBtn;
@synthesize leftLineView;
@synthesize isFinishVideoActSheet;
@synthesize theVideoNItem;
@synthesize theFeaturesName;
@synthesize theTakePhotoPath;
@synthesize theCurrentRotation;
@synthesize theVideoPlayBackBtn;
@synthesize theLocalRecordTimeLab;
@synthesize theVideoTimeLab;
@synthesize theVideoMZTimer;
@synthesize theLocalRecordMZTimer;
@synthesize theRecordVideoTypeActSheet;
@synthesize theVideoBitrateAlertView;


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
    [self.theLocalRecordMZTimer pause];
    theLocalRecordMZTimerStatus = @"pause";
}


#pragma mark - Memory Warning method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark -
#pragma mark - UIActionSheet Delegate

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
            [theLocalRecordMZTimer reset];
            [theLocalRecordMZTimer start];
            
            theLocolFunBtn.selected = YES;
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

- (IBAction)theLocolFunBtn_OnClicked:(id)sender
{
    if (theLocolFunBtn.selected == NO)
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
        [theLocalRecordMZTimer pause];
        
        theLocolFunBtn.selected = NO;
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

- (void)setTheTimer
{
    //The Timer Init
    theVideoMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theVideoTimeLab];
    theVideoMZTimer.timeFormat = @"▷ HH:mm:ss";
    [theVideoMZTimer start];
    
    theLocalRecordMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theLocalRecordTimeLab];
    theLocalRecordMZTimer.timeFormat = @"HH:mm:ss";
}

- (void)setUI
{
    NSString *targetUserName = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    self.theVideoNItem.title = [[NSString alloc] initWithFormat:@"与“%@”视频中",targetUserName];
    
    //Local View line
    theLocalView.layer.borderColor = [[UIColor whiteColor] CGColor];
    theLocalView.layer.borderWidth = 1.0f;
    //Rounded corners
    theLocalView.layer.cornerRadius = 4;
    theLocalView.layer.masksToBounds = YES;
    
    [theVideoMZTimer start];
    if ([theLocalRecordMZTimerStatus isEqualToString:@"pause"])
    {
        [self.theLocalRecordMZTimer start];
    }
}



@end
