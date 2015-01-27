//
//  AnyChatViewController.h
//  helloAnyChat
//
//  Created by AnyChat on 14-9-12.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "AppDelegate.h"
#import "MBProgressHUD.h"
#import "VideoViewController.h"
#import "SettingVC.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"


@class VideoViewController;

@interface AnyChatViewController : UIViewController<UITableViewDelegate,UITableViewDataSource,UIAlertViewDelegate,MBProgressHUDDelegate,UITextFieldDelegate,AnyChatNotifyMessageDelegate>{
    MBProgressHUD *HUD;
}

@property (weak, nonatomic) IBOutlet UITextField            *theUserName;
@property (weak, nonatomic) IBOutlet UITextField            *theRoomNO;
@property (weak, nonatomic) IBOutlet UITextField            *theServerIP;
@property (weak, nonatomic) IBOutlet UITextField            *theServerPort;
@property (weak, nonatomic) IBOutlet UIButton               *theLoginBtn;
@property (weak, nonatomic) IBOutlet UIButton               *theHideKeyboardBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theVersion;
@property (weak, nonatomic) IBOutlet UILabel                *theStateInfo;
@property (strong, nonatomic) IBOutlet UITableView          *onLineUserTableView;
@property (strong, nonatomic) NSMutableArray                *onlineUserMArray;
@property (strong, nonatomic) UIAlertView                   *theLoginAlertView;
@property (strong, nonatomic) VideoViewController           *videoVC;
@property (strong, nonatomic) AnyChatPlatform               *anyChat;
@property BOOL theOnLineLoginState;
@property int theMyUserID;
@property int theTargetUserID;


- (IBAction) hideKeyBoard;

- (IBAction) OnLoginBtnClicked:(id)sender;

- (NSMutableArray *) getOnlineUserArray;

- (id) GetServerIP;

- (id) GetServerPort;

- (id) GetUserName;

- (id) GetRoomNO;

- (void) OnLogout;

- (void) saveSettings;

@end
