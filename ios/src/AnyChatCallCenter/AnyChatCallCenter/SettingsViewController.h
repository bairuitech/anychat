//
//  SettingsViewController.h
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatAppDelegate.h"
#import "LoginViewController.h"

#ifndef kAnyChatSettingsFileName
#define kAnyChatSettingsFileName           @"settings.plist"
#define kAnyChatDefaultServerIP            @"demo.anychat.cn"
#define kAnyChatDefaultServerPort          @"8906"
#endif //kAnyChatSettingsFileName


@interface SettingsViewController : UIViewController

@property (nonatomic, strong) IBOutlet UITextField   *theServerIP;
@property (nonatomic, strong) IBOutlet UITextField   *theServerPort;

- (IBAction)OnSaveSettingsBtnClick:(id)sender;

@end
