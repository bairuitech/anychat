//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "RecordLocalVC.h"

@interface RecordLocalVC ()

@end

@implementation RecordLocalVC

@synthesize localVideoSurface;
@synthesize theLocalView;
@synthesize theLocolFunBtn;
@synthesize theLocalRecordTimeLab;
@synthesize theLocalRecordMZTimer;


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


#pragma mark - Memory Warning method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
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
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION : self.interfaceOrientation];
}

- (IBAction)recordLocolBtn_OnClicked:(id)sender
{
    int theRecordId = -1;
    theLocalRecordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_LOCALCB;
    
    if (theLocolFunBtn.selected == NO)
    {
        //Self recording
        [AnyChatPlatform StreamRecordCtrlEx: theRecordId
                                           : YES
                                           : theLocalRecordFlags
                                           : 0
                                           : @"StarLocolSelfRecord"];
        
        //Show LocalRecord Time
        self.theLocalRecordTimeLab.hidden = NO;
        [theLocalRecordMZTimer reset];
        [theLocalRecordMZTimer start];
        
        theLocolFunBtn.selected = YES;
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

- (void) FinishVideoChat
{
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
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
    self.localVideoSurface.frame = CGRectMake(0, 0, self.theLocalView.frame.size.width, self.theLocalView.frame.size.height);
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
    theLocalRecordMZTimer = [[MZTimerLabel alloc]initWithLabel:self.theLocalRecordTimeLab];
    theLocalRecordMZTimer.timeFormat = @"HH:mm:ss";
}

- (void)setUI
{
    if ([theLocalRecordMZTimerStatus isEqualToString:@"pause"])
    {
        [self.theLocalRecordMZTimer start];
    }
}

- (IBAction)returnBtn_OnClick
{
    [self FinishVideoChat];
    [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:1]
                                          animated:YES];
}

@end
