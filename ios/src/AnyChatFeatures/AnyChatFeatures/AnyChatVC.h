//
//  VideoVC.h
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "MBProgressHUD.h"
#import "VideoVC.h"
#import "UserListVC.h"
#import "FeaturesListVC.h"
#import "TextMsg_TransBufferVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"


@class VideoVC;

@interface AnyChatVC : UIViewController<NSCoding,UITextFieldDelegate,MBProgressHUDDelegate,AnyChatNotifyMessageDelegate,AnyChatTextMsgDelegate,AnyChatTransDataDelegate,AnyChatRecordSnapShotDelegate,AnyChatVideoCallDelegate>
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
@property (strong, nonatomic) VideoVC                       *videoVC;
@property (strong, nonatomic) AnyChatPlatform               *anyChat;
@property (strong, nonatomic) NSMutableArray                *onlineUserMArray;
@property (strong, nonatomic) NSString                      *theFeaturesName;
@property (strong, nonatomic) NSString                      *theMyUserName;
@property (strong, nonatomic) NSString                      *theTargetUserName;
@property int   theFeaturesNO;
@property int   theMyUserID;
@property int   theTargetUserID;
@property BOOL  theOnLineLoginState;


kGCD_SINGLETON_FOR_HEADER(AnyChatVC);

- (IBAction) hideKeyBoard;

- (IBAction) OnLoginBtnClicked:(id)sender;

- (id) GetServerIP;

- (id) GetServerPort;

- (id) GetUserName;

- (void) OnLogout;

- (void) saveSettings;

- (void) dimissAlertView:(UIAlertView *)alert;

- (NSString *)showInfoAlertView:(NSString *)Title : (NSString *)subTitle;

- (NSMutableArray *) getOnlineUserArray;

@end
