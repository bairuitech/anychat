//
//  SettingsViewController.h
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"
#import <QuickLook/QLPreviewController.h>
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"


@interface ShowVC : UIViewController <UITableViewDelegate,UITableViewDataSource,QLPreviewControllerDataSource,QLPreviewControllerDelegate>

@property (weak, nonatomic) IBOutlet UINavigationItem       *theShowVCNItem;
@property (strong, nonatomic) IBOutlet UITableView          *theVideoRecordTableView;
@property (strong, nonatomic) NSMutableArray                *theVideoRecordList;
@property (strong, nonatomic) NSString                      *theSelectContentPath;

- (IBAction)LeaveBtn_OnClick;

@end
