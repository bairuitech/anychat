//
//  VideoChatController.m
//  AnyChat
//
//  Created by bairuitech on 11-11-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "VideoChatController.h"
#import "AnyChatAppDelegate.h"
#import "../../sdk/include/AnyChatPlatform.h"
#import "../../sdk/include/AnyChatDefine.h"

@implementation VideoChatController

@synthesize localVideoSurface;
@synthesize remoteVideoSurface;
@synthesize theLocalView;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}


- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    UIDevice *device = [UIDevice currentDevice];
    [device beginGeneratingDeviceOrientationNotifications];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(deviceOrientation:) name:UIDeviceOrientationDidChangeNotification object:device];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    self.theLocalView = nil;
}

- (void) OnLocalVideoInit:(id)session
{
    self.localVideoSurface = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.localVideoSurface.frame = CGRectMake(0, 0, 120, 160);
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

- (void) StartVideoChat:(int) userid
{
    // open local video
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];
    [AnyChatPlatform UserSpeakControl: -1:YES];
    [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
    [AnyChatPlatform UserCameraControl:-1 : YES];
    
    // request other user video
    [AnyChatPlatform UserSpeakControl: userid:YES];
    [AnyChatPlatform SetVideoPos:userid: self.remoteVideoSurface:0:0:0:0];
    [AnyChatPlatform UserCameraControl:userid : YES];
    
    self->iRemoteUserId = userid;
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION : self.interfaceOrientation];
}

- (void) FinishVideoChat
{
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
    
    [AnyChatPlatform UserSpeakControl: self->iRemoteUserId : NO];
    [AnyChatPlatform UserCameraControl: self->iRemoteUserId : NO];
    
    self->iRemoteUserId = -1;
}

- (IBAction) OnSwitchCameraBtnClicked:(id)sender
{
    static int CurrentCameraDevice = 0;
    NSMutableArray* cameraDeviceArray = [AnyChatPlatform EnumVideoCapture];
    if(cameraDeviceArray.count == 2)
    {
        CurrentCameraDevice = (++CurrentCameraDevice) % 2;
        [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:CurrentCameraDevice]];
    }
}

- (IBAction) OnFinishVideoChatBtnClicked:(id)sender
{
    [self FinishVideoChat];
    [[AnyChatAppDelegate GetApp].viewController showRoomView];
}

#pragma mark - Orientation Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - Video Rotation

- (void)deviceOrientation:(NSNotification *)notification
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


-(void)setFrameOfPortrait
{
    //Rotate
    remoteVideoSurface.layer.transform = kLayer3DRotation_Z_Axis(0.0);
    self.theLocalView.layer.transform = kLayer3DRotation_Z_Axis(0.0);
    //Scale
    self.remoteVideoSurface.frame = CGRectMake(0, 0, kScreen_Width, kScreen_Height);
    self.theLocalView.frame = kLocalVideoPortrait_CGRect;
}

-(void)setFrameOfLandscapeLeft
{
    //Rotate
    remoteVideoSurface.layer.transform = kLayer3DRotation_Z_Axis(90.0);
    self.theLocalView.layer.transform = kLayer3DRotation_Z_Axis(-90.0);
    //Scale
    self.remoteVideoSurface.frame = CGRectMake(0, 0, kScreen_Height, kScreen_Width);
    self.theLocalView.frame = kLocalVideoLandscape_CGRect;
}

-(void)setFrameOfLandscapeRight
{
    //Rotate
    remoteVideoSurface.layer.transform = kLayer3DRotation_Z_Axis(-90.0);;
    self.theLocalView.layer.transform = kLayer3DRotation_Z_Axis(90.0);
    //Scale
    self.remoteVideoSurface.frame = CGRectMake(0, 0, kScreen_Height, kScreen_Width);
    self.theLocalView.frame = kLocalVideoLandscape_CGRect;
}

@end
