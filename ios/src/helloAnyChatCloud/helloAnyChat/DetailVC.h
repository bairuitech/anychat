//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SettingVC.h"

@interface DetailVC : UIViewController

@property (weak, nonatomic) IBOutlet UINavigationItem       *theDetailNItem;
@property (strong, nonatomic) IBOutlet UITableView          *theDetailSettingTableView;
@property (strong, nonatomic) NSMutableDictionary           *theMainSettingMDict;
@property (strong, nonatomic) NSMutableArray                *theTitlesParamMArray;
@property (strong, nonatomic) NSMutableArray                *theValuesParamMArray;
@property (strong, nonatomic) NSString                      *theNavTitle;
@property (strong, nonatomic) NSString                      *theTitlesParamStr;
@property (strong, nonatomic) NSString                      *theValuesParamStr;


- (void)setType:(NSString *)theTypeName;

- (NSMutableArray *)getArrayFromMDict:(NSMutableDictionary *)mainMDict firstMDictKey:(NSString *)firstKey secondMArrayKey:(NSString *)secondKey;

- (NSMutableDictionary *)readPListToMDictionaryWithPListName:(NSString *)thePListName;

- (IBAction)LeaveBtn_OnClick;

@end
