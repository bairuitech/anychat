//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DetailVC.h"
#import "AnyChatVC.h"

@interface SettingVC : UIViewController <UITableViewDelegate,UITableViewDataSource>

@property (weak, nonatomic) IBOutlet UITableView    *theUserSettingTabelView;
@property (strong,nonatomic) UISwitch               *theP2PSwitch;
@property (strong,nonatomic) UISwitch               *theServerSwitch;
@property (strong,nonatomic) NSMutableDictionary    *theMainUserSettingMDict;
//user setting param - NSMutableDictionary
@property (strong,nonatomic) NSMutableDictionary    *theVideop2pMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoServerParamMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoSolutionMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoBitrateMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoFramerateMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoPresetMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoQualityMDict;
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


kGCD_SINGLETON_FOR_HEADER(SettingVC);

- (IBAction)saveBtn_OnClick;

- (NSMutableDictionary *)readPListToMDictionaryAtSandboxPList:(NSString *)thePListName;

- (id)getValuesFromMDict:(NSMutableDictionary *)mainMDict firstMDictKey:(NSString *)firstKey secondValuesKey:(NSString *)secondKey;

- (void)createObjPlistFileToDocumentsPath;

//用户自定义视频参数设置
- (void) updateUserVideoSettings;

@end

