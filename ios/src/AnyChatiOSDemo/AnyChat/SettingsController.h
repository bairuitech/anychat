//
//  SettingsController.h
//  AnyChat
//
//  Created by bairuitech on 12-4-26.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#ifndef kAnyChatSettingsFileName
#define kAnyChatSettingsFileName           @"settings.plist"
#define kAnyChatDefaultServerIP            @"demo.anychat.cn"
#define kAnyChatDefaultServerPort          @"8906"
#endif //kAnyChatSettingsFileName

@interface SettingsController : UIViewController {
    
    IBOutlet UITextField    *theServerIP;
    IBOutlet UITextField    *theServerPort;
}

@property (nonatomic, strong) UITextField   *theServerIP;
@property (nonatomic, strong) UITextField   *theServerPort;

-(IBAction)OnSaveSettingsBtnClick:(id)sender;


@end
