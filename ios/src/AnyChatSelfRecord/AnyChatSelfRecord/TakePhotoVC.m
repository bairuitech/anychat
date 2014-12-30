//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "TakePhotoVC.h"

@interface TakePhotoVC ()

@end

@implementation TakePhotoVC

@synthesize localVideoSurface;
@synthesize theLocalView;
@synthesize isFinishVideoActSheet;


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
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    if ([AnyChatVC sharedAnyChatVC].theNextVCBool == YES)
    {
        [self nextVC];
        [AnyChatVC sharedAnyChatVC].theNextVCBool = NO;
    }
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
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

- (IBAction)takePhotoBtn_OnClicked:(id)sender
{
    //"0" parameter ： Uploaded to the server
    [AnyChatPlatform SnapShot:-1 :BRAC_RECORD_FLAGS_SNAPSHOT :0];
}

- (void) FinishVideoChat
{
    // close local video
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
    self.localVideoSurface.frame = CGRectMake(0, 0, self.theLocalView.frame.size.width,self.theLocalView.frame.size.height);
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

- (void) nextVC
{
    [self FinishVideoChat];
    
    //录像最佳像素
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_WIDTHCTRL :352];
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_HEIGHTCTRL :288];
    
    RecordLocalVC *recordLocalVC = [RecordLocalVC new];
    [self.navigationController pushViewController:recordLocalVC animated:YES];
}

- (IBAction)returnBtn_OnClick
{
    [self FinishVideoChat];
    [AnyChatPlatform LeaveRoom:-1];
    [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:0]
                                          animated:YES];
}


@end
