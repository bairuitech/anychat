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
#import "MZTimerLabel.h"
#import "AnyChatVC.h"
#import "ShowVC.h"
#import "TransFileVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"


@interface VideoVC : UIViewController <UIActionSheetDelegate>
{
    AnyChatPlatform     *theAnyChat;
    AVAudioPlayer       *theAudioPlayer;
    NSString            *theLocalRecordMZTimerStatus;
    NSString            *theServerRecordMZTimerStatus;
    int theLocalRecordFlags;
    int theServerRecordFlags;
}

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) UIActionSheet                 *isFinishVideoActSheet;
@property (strong, nonatomic) UIImageView                   *theTakePhotoImageView;
@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (weak, nonatomic) IBOutlet UIButton               *theVideoPlayBackBtn;
@property (weak, nonatomic) IBOutlet UINavigationItem       *theVideoNItem;
@property (weak, nonatomic) IBOutlet UIButton               *switchCameraBtn;
@property (weak, nonatomic) IBOutlet UIButton               *endCallBtn;
@property (weak, nonatomic) IBOutlet UIButton               *theLocolFunBtn;
@property (weak, nonatomic) IBOutlet UIButton               *theServerFunBtn;
@property (weak, nonatomic) IBOutlet UIView                 *leftLineView;
@property (weak, nonatomic) IBOutlet UIView                 *rightLineView;
@property (weak, nonatomic) IBOutlet UILabel                *theVideoTimeLab;
@property (weak, nonatomic) IBOutlet UILabel                *theLocalRecordTimeLab;
@property (weak, nonatomic) IBOutlet UILabel                *theServerRecordTimeLab;
@property (strong, nonatomic) NSString                      *theFeaturesName;
@property (strong, nonatomic) NSString                      *theTakePhotoPath;
@property (strong, nonatomic) NSString                      *theCurrentRotation;
@property (strong, nonatomic) MZTimerLabel                  *theVideoMZTimer;
@property (strong, nonatomic) MZTimerLabel                  *theLocalRecordMZTimer;
@property (strong, nonatomic) MZTimerLabel                  *theServerRecordMZTimer;
@property int iRemoteUserId;


- (IBAction) FinishVideoChatBtnClicked:(id)sender;

- (IBAction) switchCameraBtn_OnClicked:(id)sender;

- (IBAction) theLocolFunBtn_OnClicked:(id)sender;

- (IBAction) theServerFunBtn_OnClicked:(id)sender;

- (IBAction) theVideoPlayBackBtn_OnClicked;

- (void) FinishVideoChat;

- (void) StartVideoChat:(int) userid;

- (void) btnSelectedOnClicked:(UIButton*)button;


@end
