//
//  RootViewController.h
//  AnyChatCallCenter
//
//  Created by alex on 14-1-27.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "AnyChatViewController.h"

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
@property int iRemoteUserId;


- (IBAction) FinishVideoChatBtnClicked:(id)sender;

- (IBAction) OnSwitchCameraBtnClicked:(id)sender;

- (void) FinishVideoChat;

- (void) StartVideoChat:(int) userid;

@end
