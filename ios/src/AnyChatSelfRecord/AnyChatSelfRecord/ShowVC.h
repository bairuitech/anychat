//
//  SettingsViewController.h
//  AnyChatCallCenter
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


@interface ShowVC : UIViewController <QLPreviewControllerDataSource,QLPreviewControllerDelegate>

@property (weak, nonatomic) IBOutlet UINavigationItem       *theShowVCNItem;
@property (strong, nonatomic) NSString                      *theVideoFilePath;

- (IBAction)LeaveBtn_OnClick;

- (IBAction)playBackVideo;

@end
