//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DetailVC.h"
#import "AnyChatViewController.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface SettingVC : ACBaseViewController <UITableViewDelegate,UITableViewDataSource>

//user setting param - Values
@property (strong,nonatomic) NSNumber               *theP2PNum;
@property (strong,nonatomic) NSNumber               *theServerParamNum;
@property (strong,nonatomic) NSNumber               *theSolutionNum;
@property (strong,nonatomic) NSNumber               *theBitrateNum;
@property (strong,nonatomic) NSNumber               *theFrameRateNum;
@property (strong,nonatomic) NSNumber               *thePresetNum;
@property (strong,nonatomic) NSNumber               *theQualityNum;
//user setting param - Titles
@property (strong,nonatomic) NSString               *theSolutionStr;
@property (strong,nonatomic) NSString               *theBitrateStr;
@property (strong,nonatomic) NSString               *theFrameRateStr;
@property (strong,nonatomic) NSString               *thePresetStr;
@property (strong,nonatomic) NSString               *theQualityStr;

@property (strong,nonatomic) NSMutableDictionary    *tempDic;

- (void)createObjPlistFileToDocumentsPath;

- (void)readDataWithPList;

//用户自定义视频参数设置
- (void) updateUserVideoSettings;

kGCD_SINGLETON_FOR_HEADER(SettingVC);

@end

