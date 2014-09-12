//
//  VideoChatController.h
//  AnyChat
//
//  Created by bairuitech on 11-11-22.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <AVFoundation/AVFoundation.h>

@interface VideoChatController : UIViewController {
    
    AVCaptureVideoPreviewLayer *localVideoSurface;
    
    IBOutlet UIImageView *remoteVideoSurface;
    
    int iRemoteUserId;
}

@property (nonatomic, strong) AVCaptureVideoPreviewLayer *localVideoSurface;
@property (nonatomic, strong) UIImageView *remoteVideoSurface;


- (void) OnLocalVideoInit:(id)session;

- (void) OnLocalVideoRelease:(id)sender;

- (void) StartVideoChat:(int) userid;

- (void) FinishVideoChat;

- (IBAction) OnFinishVideoChatBtnClicked:(id)sender;

- (IBAction) OnSwitchCameraBtnClicked:(id)sender;

@end
