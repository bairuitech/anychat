//
//  SettingsViewController.h
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>


@interface ShowVC : ACBaseViewController <UITableViewDelegate,UITableViewDataSource>
@property (strong, nonatomic) IBOutlet UITableView          *theVideoRecordTableView;


@property int   theObjType;


@end
