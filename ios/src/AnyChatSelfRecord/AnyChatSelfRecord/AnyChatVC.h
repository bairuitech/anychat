//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "MBProgressHUD.h"
#import "SettingVC.h"
#import "TakePhotoVC.h"
#import "ProviewPhotoVC.h"
#import "RecordLocalVC.h"
#import "ShowVC.h"
#import "TransFileVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"


@interface AnyChatVC : UIViewController <NSCoding,UITextFieldDelegate,MBProgressHUDDelegate,AnyChatNotifyMessageDelegate,AnyChatTransDataDelegate,AnyChatRecordSnapShotDelegate>
{
    MBProgressHUD   *HUD;
}

@property (weak, nonatomic) IBOutlet UITextField            *theUserName;
@property (weak, nonatomic) IBOutlet UITextField            *theServerIP;
@property (weak, nonatomic) IBOutlet UITextField            *theServerPort;
@property (weak, nonatomic) IBOutlet UIButton               *theLoginBtn;
@property (weak, nonatomic) IBOutlet UIButton               *theHideKeyboardBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theVersionLab;
@property (weak, nonatomic) IBOutlet UILabel                *theStateInfo;
@property (strong, nonatomic) NSMutableArray                *onlineUserMArray;
@property (strong, nonatomic) NSMutableArray                *theVideoRecordMArray;
@property (strong, nonatomic) NSString                      *theMyUserName;
@property (strong, nonatomic) NSString                      *theTargetUserName;
@property (strong, nonatomic) NSString                      *thePhotoPath;
@property (strong, nonatomic) NSString                      *theVideoPath;
@property (strong, nonatomic) AnyChatPlatform               *anyChat;
@property int   theFeaturesNO;
@property int   theMyUserID;
@property int   theTargetUserID;
@property BOOL  theLoginState;
@property BOOL  theNextVCBool;


kGCD_SINGLETON_FOR_HEADER(AnyChatVC);

- (IBAction)hideKeyBoard;

- (IBAction)OnLoginBtnClicked:(id)sender;

- (id)GetServerIP;

- (id)GetServerPort;

- (id)GetUserName;

- (void)OnLogout;

- (void)saveSettings;

- (void)dimissAlertView:(UIAlertView *)alert;

- (void)NetworkAnomaliesAlert;

- (NSString *)showInfoAlertView:(NSString *)Title : (NSString *)subTitle;

- (IBAction)VideoSetting:(id)sender;


@end
