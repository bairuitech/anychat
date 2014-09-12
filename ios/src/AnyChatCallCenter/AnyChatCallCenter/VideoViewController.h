//
//  RootViewController.h
//  AnyChatCallCenter
//
//  Created by alex on 14-1-27.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatAppDelegate.h"
#import <AVFoundation/AVFoundation.h>
#import "HallViewController.h"
#import "UserEntity.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"


@interface VideoViewController : UIViewController
{
    AnyChatPlatform *theAnyChat;
}

@property (nonatomic, strong) AVCaptureVideoPreviewLayer    *thelocalVideoSurface;
@property (nonatomic, strong) NSMutableArray                *theOnlineUserList;
@property (nonatomic, strong) IBOutlet UIImageView          *theUIImageView;
@property (nonatomic, strong) UserEntity                    *theUserEntity;
@property int iRemoteUserId;


- (IBAction) FinishVideoChat:(id)sender;

- (void) FinishVideoChat;

- (void) StartVideoChat:(int) userid;

- (void) OnLocalVideoInit:(id)session;

- (void) OnLocalVideoRelease:(id)sender;

@end
