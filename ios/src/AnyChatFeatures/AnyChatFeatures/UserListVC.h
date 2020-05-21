//
//  UserListVC.h
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "VideoVC.h"
#import "TransFileVC.h"
#import "TextMsg_TransBufferVC.h"
#import "RecordLocalVC.h"
#import "RecordServerVC.h"
#import "RecordSelfVC.h"
#import "AutodyneVC.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>

@interface UserListVC : ACBaseViewController<UITableViewDelegate,UITableViewDataSource,UIAlertViewDelegate,AVAudioPlayerDelegate>

@property (strong, nonatomic) IBOutlet UITableView          *onLineUserTableView;
@property (strong, nonatomic) NSMutableArray                *onlineUserMArray;
@property (strong, nonatomic) AVAudioPlayer                 *theAudioPlayer;
@property (strong, nonatomic) UIAlertView                   *theReplyAlertView;
@property (strong, nonatomic) UIAlertView                   *theWaitingAlertView;

kGCD_SINGLETON_FOR_HEADER(UserListVC);

- (NSMutableArray *) getOnlineUserArray;

- (UIViewController*)pushVC;


- (void) showReplyAlertViewWithName:(NSString *)callbackUserName ID:(int)callbackUserID;


@end
