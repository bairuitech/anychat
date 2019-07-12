//
//  RecordLocalVC.m
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "RecordSelfVC.h"

@interface RecordSelfVC ()
{
    NSString            *theLocalRecordMZTimerStatus;
}
@property (strong, nonatomic) UIActionSheet                 *isFinishVideoActSheet;

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (weak, nonatomic) IBOutlet UIButton               *theLocolFunBtn;

@property (weak, nonatomic) IBOutlet UILabel                *theLocalRecordTimeLab;
@property (strong, nonatomic) MZTimerLabel                  *theLocalRecordMZTimer;

@property (weak, nonatomic) IBOutlet UILabel *buttonTipLabel;

@end

@implementation RecordSelfVC


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

    [self StartVideoChat:0];
    [self setTheTimer];
    [self p_configNavItem];
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
    [self.theLocalRecordMZTimer pause];
    theLocalRecordMZTimerStatus = @"pause";
}

-(BOOL)navBarTranslucent {
    
    return YES;
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
}


#pragma mark - Orientation Rotation

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark -
#pragma mark ----------- 业务员核心代码 ----------

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
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION : self.interfaceOrientation];
}

- (void) FinishVideoChat
{
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
}


- (void) OnLocalVideoInit:(id)session
{
    self.localVideoSurface = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.localVideoSurface.frame = CGRectMake(0, 0, self.theLocalView.frame.size.width,self.theLocalView.frame.size.height);
    self.localVideoSurface.videoGravity = AVLayerVideoGravityResizeAspectFill;
    
    [self.theLocalView.layer addSublayer:self.localVideoSurface];
}

- (void) OnLocalVideoRelease:(id)sender
{
    if(self.localVideoSurface)
    {
        self.localVideoSurface = nil;
    }
}



//开启和停止录像
- (IBAction)theLocolFunBtn_OnClicked:(id)sender
{

    int theRecordId = -1;
    int theLocalRecordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_LOCALCB;
    
    if (self.theLocolFunBtn.selected == NO)
    {
        //Self recording
        [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                           : YES
                                           : theLocalRecordFlags
                                           : -1
                                           : @"StarLocolSelfRecord"];
        
        //Show LocalRecord Time
        self.theLocalRecordTimeLab.hidden = NO;
        [self.theLocalRecordMZTimer reset];
        [self.theLocalRecordMZTimer start];
        
        self.theLocolFunBtn.selected = YES;
        self.buttonTipLabel.textColor = [UIColor colorWithRed:255/255.0 green:22/255.0 blue:41/255.0 alpha:1];
    }
    else
    {
        //Stop recording local
        [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                           : NO
                                           : theLocalRecordFlags
                                           : -1
                                           : @"StopLocolSelfRecord"];
        //Close LocalRecord Time
        self.theLocalRecordTimeLab.hidden = YES;
        [self.theLocalRecordMZTimer pause];
        
        self.theLocolFunBtn.selected = NO;
        self.buttonTipLabel.textColor = [UIColor whiteColor];
    }
}


- (IBAction)FinishVideoChatBtnClicked:(id)sender
{
    self.isFinishVideoActSheet = [[UIActionSheet alloc]
                                  initWithTitle:@"确定结束?"
                                  delegate:self
                                  cancelButtonTitle:nil
                                  destructiveButtonTitle:nil
                                  otherButtonTitles:@"确定",@"取消", nil];
    
    self.isFinishVideoActSheet.actionSheetStyle = UIActionSheetStyleBlackOpaque;
    [self.isFinishVideoActSheet showInView:self.view];
}


#pragma mark ----  ACTION ----
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
    self.theLocalRecordMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theLocalRecordTimeLab];
    self.theLocalRecordMZTimer.timeFormat = @"HH:mm:ss";
}

- (void)setUI
{
    self.title = @"录制自己";
    
    if ([theLocalRecordMZTimerStatus isEqualToString:@"pause"])
    {
        [self.theLocalRecordMZTimer start];
    }
    
    //disable the “idle timer” to avert system sleep.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}


@end
