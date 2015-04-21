//
//  VideoVC.h
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2015年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "MZTimerLabel.h"
#import "AnyChatVC.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

#define kVideoWindowNumInt (int)3

@class VideoVC;


typedef void(^passValBlock)(int targerUserID,int imgViewTag,VideoVC *videoVC);
typedef void(^addImgBlock)(int imgViewTag,VideoVC *videoVC);

@interface VideoVC : UIViewController <UIActionSheetDelegate,UIAlertViewDelegate>
{
    AnyChatPlatform     *theAnyChat;
}

@property (strong, nonatomic) IBOutlet UIImageView          *iRemoteVideoView1;
@property (strong, nonatomic) IBOutlet UIImageView          *iRemoteVideoView2;
@property (strong, nonatomic) IBOutlet UIImageView          *iRemoteVideoView3;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) NSString                      *theCurrentRotation;
@property (strong, nonatomic) NSMutableArray                *onRoomUserMArray;
@property (strong, nonatomic) UIActionSheet                 *isFinishVideoActSheet;
@property (strong, nonatomic) UIAlertView                   *theVideoBitrateAlertView;

@property (weak, nonatomic) IBOutlet UINavigationItem       *theVideoNItem;
@property (weak, nonatomic) IBOutlet UIButton               *switchCameraBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theLabel3001;
@property (weak, nonatomic) IBOutlet UILabel                *theLabel3002;
@property (weak, nonatomic) IBOutlet UILabel                *theLabel3003;
@property (weak, nonatomic) IBOutlet UILabel                *theSelfIDLabel;

@property (nonatomic,copy)passValBlock pvBlock;
@property (nonatomic,copy)addImgBlock aiBlock;


- (IBAction) FinishVideoChatBtnClicked:(id)sender;
- (IBAction) switchCameraBtn_OnClicked:(id)sender;
- (void) FinishVideoChat;
- (void) StartLocalVideoChat;
- (void) myEnterRoomChat;

@end
