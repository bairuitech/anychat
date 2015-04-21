//
//  VideoVC.m
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2015年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "VideoVC.h"

@interface VideoVC ()

@end

@implementation VideoVC


@synthesize localVideoSurface;
@synthesize theLocalView;
@synthesize switchCameraBtn;
@synthesize isFinishVideoActSheet;
@synthesize theVideoBitrateAlertView;
@synthesize theVideoNItem;
@synthesize theCurrentRotation;
@synthesize onRoomUserMArray;
@synthesize theSelfIDLabel;

@synthesize iRemoteVideoView1;
@synthesize iRemoteVideoView2;
@synthesize iRemoteVideoView3;
@synthesize theLabel3001;
@synthesize theLabel3002;
@synthesize theLabel3003;


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
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUI];
    
    
    //Video Chat Block
    self.pvBlock =  ^(int targerUserID,int imgViewTag,VideoVC *videoVC)
    {
        NSString *userName = [AnyChatPlatform GetUserName:targerUserID];
        
        // request other user video
        [AnyChatPlatform UserSpeakControl: targerUserID:YES];
        switch (imgViewTag)
        {
            case 1 :
            {
                videoVC.theLabel3001.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
                [AnyChatPlatform SetVideoPos:targerUserID: videoVC.iRemoteVideoView1:0:0:0:0];
                videoVC.iRemoteVideoView1.contentMode = UIViewContentModeScaleAspectFit;
                break;
            }
                
            case 2 :
            {
                videoVC.theLabel3002.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
                [AnyChatPlatform SetVideoPos:targerUserID: videoVC.iRemoteVideoView2:0:0:0:0];
                videoVC.iRemoteVideoView2.contentMode = UIViewContentModeScaleAspectFit;
                break;
            }
                
            case 3 :
            {
                videoVC.theLabel3003.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
                [AnyChatPlatform SetVideoPos:targerUserID: videoVC.iRemoteVideoView3:0:0:0:0];
                videoVC.iRemoteVideoView3.contentMode = UIViewContentModeScaleAspectFit;
                break;
            }
                
        }
        [AnyChatPlatform UserCameraControl:targerUserID : YES];
    };
    
    //add image Block
    self.aiBlock = ^(int imgViewTag,VideoVC *videoVC)
    {
        UIImage *bgImg = [UIImage imageNamed:@"Default"];
        
        switch (imgViewTag)
        {
            case 1 :
            {
                videoVC.iRemoteVideoView1.image = bgImg;
                break;
            }
                
            case 2 :
            {
                videoVC.iRemoteVideoView2.image = bgImg;
                break;
            }
                
            case 3 :
            {
                videoVC.iRemoteVideoView3.image = bgImg;
                break;
            }
        }

    };

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


#pragma mark - IBAction Method

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


#pragma mark -
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
    iRemoteVideoView1.layer.transform = kLayer_Z_Axis_3DRotation(0.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(0.0);
    //Scale
    self.iRemoteVideoView1.frame = CGRectMake(0, 0, kSelfView_Width, kSelfView_Height);
    self.theLocalView.frame = kLocalVideoPortrait_CGRect;
}

-(void)setFrameOfLandscapeLeft
{
    self.theCurrentRotation =@"LandscapeLeft";
    //Rotate
    iRemoteVideoView1.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);
    //Scale
    self.iRemoteVideoView1.frame = CGRectMake(0, 0, kSelfView_Width, kSelfView_Height);
    self.theLocalView.frame = kLocalVideoLandscape_CGRect;
}

-(void)setFrameOfLandscapeRight
{
    self.theCurrentRotation =@"LandscapeRight";
    //Rotate
    iRemoteVideoView1.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    //Scale
    self.iRemoteVideoView1.frame = CGRectMake(0, 0, kSelfView_Width, kSelfView_Height);
    self.theLocalView.frame = kLocalVideoLandscape_CGRect;
}


#pragma mark - Instance Method


- (void) myEnterRoomChat
{
    NSMutableArray *onlineUserMArray = [[AnyChatVC sharedAnyChatVC] getOnlineUserArray];
    
    
    //获取循环的最大次数
    int forCount = 0;
    int uArrayCount = (int)onlineUserMArray.count;
    uArrayCount > kVideoWindowNumInt ? (forCount = kVideoWindowNumInt) : (forCount = uArrayCount);
    
    if (uArrayCount > 0)
    {
        for (int i = 0; i < forCount; i++)
        {
            int iRemoteUserID = [[onlineUserMArray objectAtIndex:i] intValue];

            [self StartTargerVideoChatWithID:iRemoteUserID Tag:(i+1)];

            //记录已经视频的userID到theTargetUserIDStrMArray
            [[AnyChatVC sharedAnyChatVC].theOnChatUserIDStrMArray replaceObjectAtIndex:i
                                                                            withObject:[[NSString alloc] initWithFormat:@"%d",iRemoteUserID]];
        }
    }

}

- (void) StartTargerVideoChatWithID:(int)targerUserID Tag:(int)tag
{
    
    NSString *userName = [AnyChatPlatform GetUserName:targerUserID];
    
    // request other user video
    [AnyChatPlatform UserSpeakControl: targerUserID:YES];
    switch (tag)
    {
        case 1 :
        {
            self.theLabel3001.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
            [AnyChatPlatform SetVideoPos:targerUserID: self.iRemoteVideoView1:0:0:0:0];
            self.iRemoteVideoView1.contentMode = UIViewContentModeScaleAspectFit;
            break;
        }
            
        case 2 :
        {
            self.theLabel3002.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
            [AnyChatPlatform SetVideoPos:targerUserID: self.iRemoteVideoView2:0:0:0:0];
            self.iRemoteVideoView2.contentMode = UIViewContentModeScaleAspectFit;
            break;
        }
            
        case 3 :
        {
            self.theLabel3003.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
            [AnyChatPlatform SetVideoPos:targerUserID: self.iRemoteVideoView3:0:0:0:0];
            self.iRemoteVideoView3.contentMode = UIViewContentModeScaleAspectFit;
            break;
        }
            
    }
    [AnyChatPlatform UserCameraControl:targerUserID : YES];
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION : self.interfaceOrientation];
}

- (void) StartLocalVideoChat
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

- (void) FinishVideoChat
{
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
    
   //???:添加释放 imgview FUN
    for (NSString *uID in [AnyChatVC sharedAnyChatVC].theOnChatUserIDStrMArray )
    {
        int userId = [uID intValue];
        if (userId != 0 )
        {
            [AnyChatPlatform UserSpeakControl: userId : NO];
            [AnyChatPlatform UserCameraControl: userId : NO];
        }
    }
    
    [AnyChatPlatform LeaveRoom:-1];
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

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)setUI
{
    self.theVideoNItem.title = [[NSString alloc] initWithFormat:@"多方视频会议"];
    self.theSelfIDLabel.text = [NSString stringWithFormat:@"%@(%d)",[AnyChatVC sharedAnyChatVC].theMyUserName,[AnyChatVC sharedAnyChatVC].theMyUserID];
    
    //Local View line
    theLocalView.layer.borderColor = [[UIColor redColor] CGColor];
    theLocalView.layer.borderWidth = 1.0f;
    
    //disable the “idle timer” to avert system sleep.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}

@end
