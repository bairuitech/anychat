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
#import "VideoViewController.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

#define kNameValueTag               1001
#define kUserIDValueTag             1002
#define kBackgroundViewTag          1003
#define kAnyChatSettingsFileName    @"settings.plist"

@class VideoViewController;

@interface AnyChatViewController : UIViewController<UITableViewDelegate,UITableViewDataSource,UIAlertViewDelegate,UITextFieldDelegate,AnyChatNotifyMessageDelegate>

@property (weak, nonatomic) IBOutlet UITextField            *theUserName;
@property (weak, nonatomic) IBOutlet UITextField            *theRoomNO;
@property (weak, nonatomic) IBOutlet UITextField            *theServerIP;
@property (weak, nonatomic) IBOutlet UITextField            *theServerPort;
@property (weak, nonatomic) IBOutlet UIButton               *theLoginBtn;
@property (weak, nonatomic) IBOutlet UIButton               *theHideKeyboardBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theVersion;
@property (weak, nonatomic) IBOutlet UILabel                *theStateInfo;
@property (retain, nonatomic) IBOutlet UITableView          *onLineUserTableView;
@property (retain, nonatomic) NSMutableArray                *onlineUserMArray;
@property (strong, nonatomic) UIAlertView                   *theLoginAlertView;
@property (retain, nonatomic) VideoViewController           *videoVC;
@property (retain, nonatomic) AnyChatPlatform               *anyChat;
@property BOOL onLoginState;


- (IBAction)hideKeyBoard;

- (IBAction)OnLoginBtnClicked:(id)sender;

- (NSMutableArray *) getOnlineUserArray;

- (id) GetServerIP;

- (int) GetServerPort;

- (void) OnLogout;

@end
