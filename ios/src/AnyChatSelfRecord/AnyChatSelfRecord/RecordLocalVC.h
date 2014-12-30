//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "MZTimerLabel.h"
#import "AnyChatVC.h"
#import "ShowVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface RecordLocalVC : UIViewController <UIActionSheetDelegate,UIAlertViewDelegate>
{
    AnyChatPlatform     *theAnyChat;
    AVAudioPlayer       *theAudioPlayer;
    NSString            *theLocalRecordMZTimerStatus;
    
    int     theLocalRecordFlags;
}

@property (strong, nonatomic) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (strong, nonatomic) IBOutlet UIView               *theLocalView;
@property (weak, nonatomic) IBOutlet UIButton               *theLocolFunBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theLocalRecordTimeLab;
@property (strong, nonatomic) MZTimerLabel                  *theLocalRecordMZTimer;


- (IBAction) recordLocolBtn_OnClicked:(id)sender;

- (void) FinishVideoChat;

- (void) StartVideoChat:(int) userid;

- (void) btnSelectedOnClicked:(UIButton*)button;

@end
