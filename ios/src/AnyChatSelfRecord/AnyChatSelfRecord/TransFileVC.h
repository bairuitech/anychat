//
//  TransFileVC.h
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"
#import "EndVC.h"
#import "RecordLocalVC.h"
#import "ProviewPhotoVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface TransFileVC : UIViewController <UIAlertViewDelegate>
{
    BOOL m_photoTransStatus;
    BOOL m_videoTransStatus;
    NSTimer *theNSTimer;
}


@property (weak, nonatomic) IBOutlet UILabel                *thePhotoProgressLab;
@property (weak, nonatomic) IBOutlet UILabel                *theVideoProgressLab;

@property int theTransFileBtnTimes;

- (IBAction)theTransFileBtn_OnClick;

@end
