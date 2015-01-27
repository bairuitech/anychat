//
//  VideoVC.h
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "AnyChatVC.h"
#import "ShowVC.h"
#import "TransFileVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"


@interface AutodyneVC : UIViewController <UIActionSheetDelegate>
{
    AnyChatPlatform     *theAnyChat;
    AVAudioPlayer       *theAudioPlayer;
    int theLocalRecordFlags;
    int theServerRecordFlags;
}

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (weak, nonatomic) IBOutlet UINavigationItem       *theVideoNItem;
@property (weak, nonatomic) IBOutlet UIButton               *switchCameraBtn;
@property (strong, nonatomic) NSString                      *theFeaturesName;
@property (strong, nonatomic) NSString                      *theTakePhotoPath;
@property (strong, nonatomic) NSString                      *theCurrentRotation;


- (IBAction) FinishVideoChatBtnClicked:(id)sender;

- (IBAction) switchCameraBtn_OnClicked:(id)sender;

- (IBAction) theLocolFunBtn_OnClicked:(id)sender;

- (void) FinishVideoChat;

- (void) StartVideoChat:(int) userid;

- (void) btnSelectedOnClicked:(UIButton*)button;

@end
