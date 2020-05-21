//
//  VideoChatController.h
//  AnyChat
//
//  Created by bairuitech on 11-11-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#define kLocalVideo_Width                   120.0f
#define kLocalVideo_Height                  160.0f
#define kUI_Spacing                         15.0f
#define kLocalVideoPortrait_CGRect          CGRectMake(15, 305, 120, 160)
#define kLocalVideoLandscape_CGRect         CGRectMake(15, 185, 160, 120)

#define kSelfView_Width                     self.view.frame.size.width
#define kSelfView_Height                    self.view.frame.size.height

#define kRadians(degrees)                   M_PI / 180.0 * degrees
#define kLayer3DRotation_Z_Axis(degrees)    CATransform3DMakeRotation(kRadians(degrees), 0.0, 0.0, 1.0)


#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include <AVFoundation/AVFoundation.h>

@interface VideoChatController : UIViewController {
    
    AVCaptureVideoPreviewLayer *localVideoSurface;
    
    IBOutlet UIImageView *remoteVideoSurface;
    
    int iRemoteUserId;
}

@property (weak, nonatomic) IBOutlet UIView                 *theLocalView;
@property (nonatomic, strong) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (nonatomic, strong) UIImageView                   *remoteVideoSurface;

@property (weak, nonatomic) IBOutlet UINavigationBar        *theNavBar;

- (void) OnLocalVideoInit:(id)session;

- (void) OnLocalVideoRelease:(id)sender;

- (void) StartVideoChat:(int) userid;

- (void) FinishVideoChat;

- (IBAction) OnFinishVideoChatBtnClicked:(id)sender;

- (IBAction) OnSwitchCameraBtnClicked:(id)sender;

@end
