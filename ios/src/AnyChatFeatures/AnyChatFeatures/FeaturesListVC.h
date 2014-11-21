//
//  FeaturesListVC.h
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UserListVC.h"
#import "AnyChatVC.h"

@interface FeaturesListVC : UIViewController<UIAlertViewDelegate>

@property (weak, nonatomic) IBOutlet UIButton *theReturnBtn;
@property (weak, nonatomic) IBOutlet UIButton *videoFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *textMsgFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *transBufferFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *transFileFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *recordFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *snapShotFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *callCenterFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *videoSettingFUNBtn;
@property (weak, nonatomic) IBOutlet UILabel  *theAnyChatVersionLab;
@property (weak, nonatomic) IBOutlet UILabel  *theMyUserIDLab;

kGCD_SINGLETON_FOR_HEADER(FeaturesListVC);

- (IBAction)VideoFUNBtnClick:(id)sender;

- (IBAction)TextMsgFUNBtnClick:(id)sender;

- (IBAction)TransBufferFUNBtnClick:(id)sender;

- (IBAction)TransFileFUNBtnClick:(id)sender;

- (IBAction)RecordFUNBtnClick:(id)sender;

- (IBAction)SnapShotFUNBtnClick:(id)sender;

- (IBAction)CallCenterFUNBtnClick:(id)sender;

- (IBAction)ReturnLoginVCBtnClick:(id)sender;

- (IBAction)videoSettingFUNBtnClick:(id)sender;

@end