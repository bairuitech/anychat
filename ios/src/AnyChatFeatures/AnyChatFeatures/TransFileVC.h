//
//  TransFileVC.h
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"
#import "ShowVC.h"
#import "MBProgressHUD.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface TransFileVC : ACBaseViewController <MBProgressHUDDelegate,UITableViewDelegate,UITableViewDataSource,NSCoding,UIAlertViewDelegate,UIImagePickerControllerDelegate,UINavigationControllerDelegate,UIActionSheetDelegate>


@property (strong, nonatomic) NSMutableArray            *theTableViewDataMArray;



kGCD_SINGLETON_FOR_HEADER(TransFileVC);

- (void)TableViewReload;

- (NSString *)getTimeNow;

@end
