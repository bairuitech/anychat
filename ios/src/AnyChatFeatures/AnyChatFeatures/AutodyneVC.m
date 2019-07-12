//
//  VideoVC.m
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "AutodyneVC.h"

@interface AutodyneVC ()
{
    AVAudioPlayer       *theAudioPlayer;
}

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;



@end

@implementation AutodyneVC



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
    [self StartVideoChat:0];
    [self p_configNavItem];
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUI];
}

- (void)p_configNavItem {
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(switchCameraBtn_OnClicked:) forControlEvents:UIControlEventTouchUpInside];
    [button setImage:[UIImage imageNamed:@"video_switch"] forState:UIControlStateNormal];
    [button sizeToFit];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = rightItem;
}
#pragma mark - Memory Warning method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(BOOL)navBarTranslucent {
    
    return YES;
}

-(void)navLeftClick {
    
    [self FinishVideoChat];
    [super navLeftClick];
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
    self.localVideoSurface.frame = CGRectMake(0, 0, self.theLocalView.frame.size.width,self.theLocalView.frame.size.height);
    self.localVideoSurface.videoGravity = AVLayerVideoGravityResizeAspectFill;
    
    [self.theLocalView.layer addSublayer:self.localVideoSurface];
}



- (IBAction)theLocolFunBtn_OnClicked:(id)sender
{
    // Local video SnapShot
    [theAudioPlayer play];
    [AnyChatPlatform SnapShot:-1 :BRAC_RECORD_FLAGS_SNAPSHOT :0];
}





- (void) switchCameraBtn_OnClicked:(id)sender
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



#pragma mark - UI & others -
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

- (void)setUI
{
    self.title = @"自拍";
    
    [self initWithTakePhotoSound];
    //disable the “idle timer” to avert system sleep.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}

@end
