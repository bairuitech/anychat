//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "AnyChatVC.h"
#import "ProviewPhotoVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"


@interface TakePhotoVC : UIViewController
{
    AnyChatPlatform     *theAnyChat;
}

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) UIActionSheet                 *isFinishVideoActSheet;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;

- (IBAction) takePhotoBtn_OnClicked:(id)sender;

- (void) FinishVideoChat;

- (void) StartVideoChat:(int) userid;

- (void) btnSelectedOnClicked:(UIButton*)button;

- (void) nextVC;

@end
