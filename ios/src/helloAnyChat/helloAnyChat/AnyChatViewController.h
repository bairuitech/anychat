//
//  AnyChatViewController.h
//  helloAnyChat
//
//  Created by AnyChat on 14-9-12.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "VideoViewController.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@class VideoViewController;

@interface AnyChatViewController : UIViewController<UITableViewDelegate,UITableViewDataSource,UITextFieldDelegate,AnyChatNotifyMessageDelegate>

@property (weak, nonatomic) IBOutlet UITextField            *theUserName;
@property (weak, nonatomic) IBOutlet UITextField            *theRoomNO;
@property (weak, nonatomic) IBOutlet UITextField            *theServerIP;
@property (weak, nonatomic) IBOutlet UITextField            *theServerPort;
@property (weak, nonatomic) IBOutlet UIButton               *theLoginBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theVersion;
@property (weak, nonatomic) IBOutlet UILabel                *theStateInfo;
@property (nonatomic, retain) UITableView                   *onLineUserTableView;
@property (nonatomic, retain) AVCaptureVideoPreviewLayer    *localVideoSurface;
@property (nonatomic, retain) NSMutableArray                *onlineUserMArray;
@property (nonatomic, retain) VideoViewController           *videoVC;
@property (nonatomic, retain) AnyChatPlatform               *anyChat;


- (IBAction)OnLoginBtnClicked:(id)sender;

- (NSMutableArray *) getOnlineUserArray;

- (void) createTableView;

- (id) GetServerIP;

- (int) GetServerPort;

- (void) OnLogout;

@end
