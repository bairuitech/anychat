//
//  FeaturesListVC.h
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UserListVC.h"
#import "SendDataVC.h"
#import "ReceiveDataVC.h"
#import "AnyChatVC.h"
#import "SettingVC.h"

@interface FeaturesListVC : UIViewController<UIAlertViewDelegate,UIActionSheetDelegate>

@property (weak, nonatomic) IBOutlet UIButton *theReturnBtn;
@property (weak, nonatomic) IBOutlet UIButton *videoFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *textMsgFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *transBufferFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *transFileFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *recordLocalFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *recordServerFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *snapShotFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *callCenterFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *videoSettingFUNBtn;
@property (weak, nonatomic) IBOutlet UIButton *theUDPTraceFUNBtn;
@property (weak, nonatomic) IBOutlet UILabel  *theAnyChatVersionLab;
@property (weak, nonatomic) IBOutlet UILabel  *theMyUserIDLab;
@property (strong, nonatomic) UIAlertView     *theUDPTraceAlertView;
@property (strong, nonatomic) UITextField     *theUDPTraceTextField;

kGCD_SINGLETON_FOR_HEADER(FeaturesListVC);

- (IBAction)VideoFUNBtnClick:(id)sender;

- (IBAction)TextMsgFUNBtnClick:(id)sender;

- (IBAction)TransBufferFUNBtnClick:(id)sender;

- (IBAction)TransFileFUNBtnClick:(id)sender;

- (IBAction)RecordLocalFUNBtnClick:(id)sender;

- (IBAction)RecordServerFUNBtnClick:(id)sender;

- (IBAction)SnapShotFUNBtnClick:(id)sender;

- (IBAction)CallCenterFUNBtnClick:(id)sender;

- (IBAction)ReturnLoginVCBtnClick:(id)sender;

- (IBAction)videoSettingFUNBtnClick:(id)sender;

- (IBAction)UDPTraceBtnClicked:(id)sender;

@end