//
//  LoginViewController.h
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatAppDelegate.h"
#import "SettingsViewController.h"
#import "HallViewController.h"

@class AnyChatPlatform;

@interface LoginViewController : UIViewController

@property (nonatomic, strong) IBOutlet UITextField   *theUserName;
@property (nonatomic, strong) IBOutlet UITextField   *thePassword;
@property (nonatomic, strong) IBOutlet UIButton      *theLoginBtn;
@property (nonatomic, strong) IBOutlet UIButton      *theSettingsBtn;
@property (nonatomic, strong) IBOutlet UILabel       *theVersion;
@property (nonatomic, strong) IBOutlet UILabel       *theTitleFony;
@property (nonatomic, strong) IBOutlet UIButton      *theHideKeyboardBtn;
@property (nonatomic, strong) LoginViewController    *LoginVC;


- (IBAction) OnNetConfigBtnClicked:(id)sender;

- (IBAction) OnLoginBtnClicked:(id)sender;

- (IBAction) hideKeyBoard:(id)sender;


@end
