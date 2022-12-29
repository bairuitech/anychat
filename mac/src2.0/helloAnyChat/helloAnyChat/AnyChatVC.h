//
//  AnyChatVC.h
//  HelloAnyChat
//
//  Created by Chen on 15-3-28.
//  Copyright (c) 2015年 AlexChen. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>
#import <QuartzCore/CIFilter.h>
#import <AVFoundation/AVFoundation.h>

#import <AnyChatCoreSDK/AnyChatCoreSDK.h>

@interface AnyChatVC : NSViewController<AnyChatNotifyMessageDelegate, NSTableViewDelegate, NSTableViewDataSource>
{
    AnyChatPlatform *anychat;
}


@property (nonatomic, strong) IBOutlet NSImageView          *remoteVideo;
@property (nonatomic, strong) AVCaptureVideoPreviewLayer    *localCaptureLayer;
@property (nonatomic, strong) IBOutlet NSView               *localView;
@property (weak) IBOutlet NSImageView *localImageView;

@property (weak, nonatomic) IBOutlet NSButton               *loginBtn;

@property (weak) IBOutlet NSTextField                       *pvServerIPTextField;
@property (weak) IBOutlet NSTextField                       *pvServerPortTextField;
@property (weak) IBOutlet NSTextField                       *pvUserNameTextField;
@property (weak) IBOutlet NSTextField                       *pvRoomNumTextField;
@property (strong) IBOutlet NSTextView                      *pvTextView;

@property (strong, nonatomic) NSMutableArray                *onlineUserMArray;
@property (weak) IBOutlet NSTableView                       *onlineUserTableView;

@property (strong, nonatomic) NSMutableArray                *cameraDeviceArray;
@property (weak) IBOutlet NSTableView *camTableView;


@property int pvMyUserID;
@property int pvTargerID;


- (IBAction) OnLoginBtnClicked:(id)sender;

- (IBAction) OnLogoutBtnClicked:(id)sender;

- (void)AnyChatNotifyHandler:(NSNotification *)notify;

- (void) OnLocalVideoInit:(id)session;

- (void) OnLocalVideoRelease:(id)sender;



@end

