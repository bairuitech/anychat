//
//  LoginViewController.h
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatAppDelegate.h"
#import "HallViewController.h"

@class AnyChatPlatform;

@interface LoginViewController : UIViewController

@property (nonatomic, strong) IBOutlet UITextField   *theIP;
@property (nonatomic, strong) IBOutlet UITextField   *thePort;
@property (nonatomic, strong) IBOutlet UITextField   *theGuid;
@property (nonatomic, strong) IBOutlet UITextField   *theUserName;
@property (nonatomic, strong) IBOutlet UIButton      *theLoginBtn;
@property (nonatomic, strong) IBOutlet UILabel       *theVersion;
@property (nonatomic, strong) IBOutlet UIButton      *theHideKeyboardBtn;
@property (nonatomic, strong) LoginViewController    *LoginVC;

- (IBAction) OnLoginBtnClicked:(id)sender;

- (IBAction) hideKeyBoard:(id)sender;


@end
