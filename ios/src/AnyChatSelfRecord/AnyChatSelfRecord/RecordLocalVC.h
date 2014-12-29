//
//  RecordLocalVC.h
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "MZTimerLabel.h"
#import "AnyChatVC.h"
#import "ProviewPhotoVC.h"
#import "TakePhotoVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface RecordLocalVC : UIViewController <UIActionSheetDelegate,UIAlertViewDelegate>
{
    AnyChatPlatform     *theAnyChat;
    AVAudioPlayer       *theAudioPlayer;
    NSString            *theLocalRecordMZTimerStatus;
    NSString            *theServerRecordMZTimerStatus;
    
    BOOL    theRecordStatusIsEnd;
    int     theLocalRecordFlags;
    int     theRecordId;
}

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) UIActionSheet                 *theRecordVideoTypeActSheet;
@property (strong, nonatomic) UIAlertView                   *theVideoBitrateAlertView;
@property (strong, nonatomic) IBOutlet UIImageView          *remoteVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (weak, nonatomic) IBOutlet UIButton               *theLocolFunBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theLocalRecordTimeLab;
@property (strong, nonatomic) NSString                      *theTakePhotoPath;
@property (strong, nonatomic) NSString                      *theCurrentRotation;
@property (strong, nonatomic) MZTimerLabel                  *theLocalRecordMZTimer;
@property int iRemoteUserId;
@property int theTimes;


- (IBAction) recordLocolBtn_OnClicked:(id)sender;

- (IBAction) videoPlayBackBtn_OnClicked;

- (void) FinishVideoChat;

- (void) StartVideoChat:(int) userid;

- (void) btnSelectedOnClicked:(UIButton*)button;

@end
