//
//  RootViewController.h
//  AnyChatCallCenter
//
//  Created by alex on 14-1-27.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "AnyChatViewController.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

#define kLocalVideo_Width                   120.0f
#define kLocalVideo_Height                  160.0f
#define kLocalVideoPortrait_CGRect          CGRectMake(200, 320, kLocalVideo_Width, kLocalVideo_Height)
#define kLocalVideoLandscape_CGRect         CGRectMake(320, 200, kLocalVideo_Height, kLocalVideo_Width)

#define kSelfView_Width                     self.view.frame.size.width
#define kSelfView_Height                    self.view.frame.size.height

#define kRadians(degrees)                   M_PI / 180.0 * degrees
#define kLayer3DRotation_Z_Axis(degrees)    CATransform3DMakeRotation(kRadians(degrees), 0.0, 0.0, 1.0)


@interface VideoViewController : UIViewController
{
    AnyChatPlatform *theAnyChat;
}

@property (nonatomic, strong) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (nonatomic, strong) IBOutlet UIImageView          *remoteVideoSurface;
@property (nonatomic, strong) IBOutlet UIView               *theLocalView;
@property int iRemoteUserId;


- (IBAction) FinishVideoChatBtnClicked:(id)sender;

- (IBAction) OnSwitchCameraBtnClicked:(id)sender;

- (void) FinishVideoChat;

- (void) StartVideoChat:(int) userid;

@end
