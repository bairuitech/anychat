//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuickLook/QLPreviewController.h>
#import "AnyChatVC.h"
#import "RecordLocalVC.h"
#import "TransFileVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"


@interface ShowVC : ACBaseViewController <QLPreviewControllerDataSource,QLPreviewControllerDelegate>

@property (strong, nonatomic) NSString                      *theVideoFilePath;


- (IBAction)playBackVideo;

@end
