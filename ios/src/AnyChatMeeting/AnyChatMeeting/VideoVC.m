//
//  VideoVC.m
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2015年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "VideoVC.h"

@interface VideoVC ()


@property (strong, nonatomic) IBOutlet UIImageView          *iRemoteVideoView1;
@property (strong, nonatomic) IBOutlet UIImageView          *iRemoteVideoView2;
@property (strong, nonatomic) IBOutlet UIImageView          *iRemoteVideoView3;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;

@property (strong, nonatomic) UIActionSheet                 *isFinishVideoActSheet;

@property (weak, nonatomic) IBOutlet UILabel                *theLabel3001;
@property (weak, nonatomic) IBOutlet UILabel                *theLabel3002;
@property (weak, nonatomic) IBOutlet UILabel                *theLabel3003;
@property (weak, nonatomic) IBOutlet UILabel                *theSelfIDLabel;

@property (strong, nonatomic) NSString                      *theCurrentRotation;

@end

@implementation VideoVC


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
    //  local Video
    [self StartLocalVideoChat];
    //  iRemote Video
    [self myEnterRoomChat];
    
    [self p_configNavItem];
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
    self.title = @"多方视频会议";
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
//                videoVC.iRemoteVideoView1.contentMode = UIViewContentModeScaleAspectFill;
                break;
            }
                
            case 2 :
            {
                videoVC.theLabel3002.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
                [AnyChatPlatform SetVideoPos:targerUserID: videoVC.iRemoteVideoView2:0:0:0:0];
//                videoVC.iRemoteVideoView2.contentMode = UIViewContentModeScaleAspectFill;
                break;
            }
                
            case 3 :
            {
                videoVC.theLabel3003.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
                [AnyChatPlatform SetVideoPos:targerUserID: videoVC.iRemoteVideoView3:0:0:0:0];
//                videoVC.iRemoteVideoView3.contentMode = UIViewContentModeScaleAspectFill;
                break;
            }
            default:
                break;
                
        }
        [AnyChatPlatform UserCameraControl:targerUserID : YES];
    };
    
    //add image Block
    self.aiBlock = ^(int imgViewTag,VideoVC *videoVC)
    {
        UIImage *bgImg = [UIImage imageNamed:@"video_item_bg"];
        
        switch (imgViewTag)
        {
            case 1 :
            {
                videoVC.theLabel3001.text = @"远程视频";
                videoVC.iRemoteVideoView1.image = bgImg;
                break;
            }
                
            case 2 :
            {
                videoVC.theLabel3002.text = @"远程视频";
                videoVC.iRemoteVideoView2.image = bgImg;
                break;
            }
                
            case 3 :
            {
                videoVC.theLabel3003.text = @"远程视频";
                videoVC.iRemoteVideoView3.image = bgImg;
                break;
            }
            default:
                break;
        }

    };

}


-(UIColor *)navBarColor {
    
    return [UIColor colorWithRed:41/255.0 green:41/255.0 blue:41/255.0 alpha:1];
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


#pragma mark -
#pragma mark - UIActionSheet Delegate & Record Video Method

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (actionSheet == self.isFinishVideoActSheet)
    {
        if (buttonIndex == 0)
        {
            [self FinishVideoChat];
            [[AnyChatVC sharedAnyChatVC] OnLoginBtnClicked:nil];
            
            [self.navigationController popViewControllerAnimated:YES];
        }
    }
}


- (void)navLeftClick
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
    
    [self btnSelectedOnClicked:sender];
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
    self.iRemoteVideoView1.layer.transform = kLayer_Z_Axis_3DRotation(0.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(0.0);

}

-(void)setFrameOfLandscapeLeft
{
    self.theCurrentRotation =@"LandscapeLeft";
    //Rotate
    self.iRemoteVideoView1.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(-90.0);

}

-(void)setFrameOfLandscapeRight
{
    self.theCurrentRotation =@"LandscapeRight";
    //Rotate
    self.iRemoteVideoView1.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    self.theLocalView.layer.transform = kLayer_Z_Axis_3DRotation(90.0);

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
//            self.iRemoteVideoView1.contentMode = UIViewContentModeScaleAspectFit;
            break;
        }
            
        case 2 :
        {
            self.theLabel3002.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
            [AnyChatPlatform SetVideoPos:targerUserID: self.iRemoteVideoView2:0:0:0:0];
//            self.iRemoteVideoView2.contentMode = UIViewContentModeScaleAspectFit;
            break;
        }
            
        case 3 :
        {
            self.theLabel3003.text = [NSString stringWithFormat:@"%@(%d)",userName,targerUserID];
            [AnyChatPlatform SetVideoPos:targerUserID: self.iRemoteVideoView3:0:0:0:0];
//            self.iRemoteVideoView3.contentMode = UIViewContentModeScaleAspectFit;
            break;
        }
            
    }
    [AnyChatPlatform UserCameraControl:targerUserID : YES];
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION :(int)[UIApplication sharedApplication].statusBarOrientation];
}

- (void) StartLocalVideoChat
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
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_ORIENTATION :(int)[UIApplication sharedApplication].statusBarOrientation];
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
    
    CGFloat width = AdaptW(kLocalVideo_Width);
    CGFloat height = AdaptW(kLocalVideo_Height);
    self.localVideoSurface.frame = CGRectMake(0, 0, width, height);
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


- (void)setUI
{
    self.title = @"多方视频会议";
    self.theSelfIDLabel.text = [NSString stringWithFormat:@"%@(%d)",[AnyChatVC sharedAnyChatVC].theMyUserName,[AnyChatVC sharedAnyChatVC].theMyUserID];
    
    UIColor *bgColor = [[UIColor blackColor] colorWithAlphaComponent:0.4];
    self.theSelfIDLabel.backgroundColor = bgColor;
    self.theLabel3001.backgroundColor = bgColor;
    self.theLabel3002.backgroundColor = bgColor;
    self.theLabel3003.backgroundColor = bgColor;
    
//    //Local View line
//    theLocalView.layer.borderColor = [[UIColor redColor] CGColor];
//    theLocalView.layer.borderWidth = 1.0f;
    
    //disable the “idle timer” to avert system sleep.
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
}

@end
