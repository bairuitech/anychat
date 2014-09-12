//
//  HallViewController.h
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatAppDelegate.h"
#import "VideoViewController.h"
#import "UserEntity.h"
#import "UserInfo.h"
#import "Toast+UIView.h"
#import "AnyChatPlatform.h"

@class VideoViewController;

@interface HallViewController : UIViewController<UITableViewDelegate,UITableViewDataSource,UIAlertViewDelegate,AnyChatUserInfoDelegate,AnyChatVideoCallDelegate,AnyChatNotifyMessageDelegate>
{
    AnyChatPlatform *theAnyChat;
}

@property (nonatomic, strong) NSString              *theUserNameHall;
@property (nonatomic, strong) NSString              *theUserPasswordHall;
@property (nonatomic, strong) NSString              *theStateMsg;

@property (nonatomic, strong) NSMutableArray        *onlineUserMArray;
@property (nonatomic, strong) UITableView           *onlineUserTable;
@property (nonatomic, strong) UIAlertView           *theReplyAlertView;
@property (nonatomic, strong) UIAlertView           *theRejectAlertView;
@property (nonatomic, strong) UIAlertView           *theWaitingAlertView;

@property (nonatomic, strong) UserEntity            *theUserEntity;
@property (nonatomic, strong) UserInfo              *theUInfo;
@property (nonatomic, strong) VideoViewController   *videoVC;


- (IBAction) leaveLoginBtnClicked:(id)sender;

- (void) AnyChatNotifyHandler:(NSNotification*)notify;

- (void) createTableView;

- (void) refreshTableView;

- (void) showReplyAlertView;

- (void) dimissAlertView:(UIAlertView *)alert;

- (void) getOnlineUserList:(NSMutableArray *)onlineUList;

- (NSMutableArray *) getOnlineUserArray;

- (NSString *) showInfoAlertView:(NSString *)titleCN : (NSString *)titleEN;




@end
