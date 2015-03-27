//
//  ViewController.h
//  helloAnyChat
//
//  Created by WangXL on 15/3/24.
//  Copyright (c) 2015年 WangXL. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <AVFoundation/AVFoundation.h>
#import "../../../sdk/include/AnyChatPlatform.h"
#import "../../../sdk/include/AnyChatDefine.h"
#import "../../../sdk/include/AnyChatErrorCode.h"



@interface ViewController : NSViewController <AnyChatNotifyMessageDelegate> {

    AnyChatPlatform* anychat;

    IBOutlet NSImageView* theRemoteVideo;
    IBOutlet NSImageView* theLocalView;
    
    AVCaptureVideoPreviewLayer* theLocalVideoSurface;
}

@property (nonatomic, strong) NSImageView* theRemoteVideo;
@property (nonatomic, strong) AVCaptureVideoPreviewLayer* theLocalVideoSurface;
@property (nonatomic, strong) IBOutlet NSView* theLocalView;




- (void)AnyChatNotifyHandler:(NSNotification*)notify;

- (void) OnLocalVideoInit:(id)session;

- (void) OnLocalVideoRelease:(id)sender;


@end

