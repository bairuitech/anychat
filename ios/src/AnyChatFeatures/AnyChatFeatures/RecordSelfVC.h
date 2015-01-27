//
//  RecordLocalVC.h
//  AnyChatFeatures
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
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface RecordSelfVC : UIViewController <UIActionSheetDelegate,UIAlertViewDelegate>
{
    AnyChatPlatform     *theAnyChat;
    AVAudioPlayer       *theAudioPlayer;
    NSString            *theLocalRecordMZTimerStatus;
    NSString            *theServerRecordMZTimerStatus;
    
    BOOL theFirstGetVideoBitrate;
    BOOL theFirstGetAudioBitrate;
    int theLocalRecordFlags;
    int theRecordId;
}

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) UIActionSheet                 *isFinishVideoActSheet;
@property (strong, nonatomic) UIActionSheet                 *theRecordVideoTypeActSheet;
@property (strong, nonatomic) UIAlertView                   *theVideoBitrateAlertView;
@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (weak, nonatomic) IBOutlet UIButton               *theVideoPlayBackBtn;
@property (weak, nonatomic) IBOutlet UINavigationItem       *theVideoNItem;
@property (weak, nonatomic) IBOutlet UIButton               *switchCameraBtn;
@property (weak, nonatomic) IBOutlet UIButton               *theLocolFunBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theVideoTimeLab;
@property (weak, nonatomic) IBOutlet UILabel                *theLocalRecordTimeLab;
@property (strong, nonatomic) NSString                      *theTakePhotoPath;
@property (strong, nonatomic) NSString                      *theCurrentRotation;
@property (strong, nonatomic) MZTimerLabel                  *theVideoMZTimer;
@property (strong, nonatomic) MZTimerLabel                  *theLocalRecordMZTimer;


- (IBAction) FinishVideoChatBtnClicked:(id)sender;

- (IBAction) switchCameraBtn_OnClicked:(id)sender;

- (IBAction) theLocolFunBtn_OnClicked:(id)sender;

- (IBAction) theVideoPlayBackBtn_OnClicked;

- (void) FinishVideoChat;

- (void) StartVideoChat:(int) userid;

- (void) btnSelectedOnClicked:(UIButton*)button;

@end
