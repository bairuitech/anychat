//
//  UserListVC.h
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "FeaturesListVC.h"
#import "VideoVC.h"
#import "TransFileVC.h"
#import "TextMsg_TransBufferVC.h"
#import "RecordLocalVC.h"
#import "RecordServerVC.h"
#import "RecordSelfVC.h"
#import "AutodyneVC.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface UserListVC : UIViewController<UITableViewDelegate,UITableViewDataSource,UIAlertViewDelegate,AVAudioPlayerDelegate>
{
    UITableView         *onLineUserTableView;
    NSMutableArray      *onlineUserMArray;
}

@property (weak, nonatomic) IBOutlet UINavigationItem       *onlineUserNItem;
@property (strong, nonatomic) IBOutlet UITableView          *onLineUserTableView;
@property (strong, nonatomic) AVAudioPlayer                 *theAudioPlayer;
@property (strong, nonatomic) UIAlertView                   *theReplyAlertView;
@property (strong, nonatomic) UIAlertView                   *theRejectAlertView;
@property (strong, nonatomic) UIAlertView                   *theWaitingAlertView;
@property (strong, nonatomic) NSMutableArray                *onlineUserMArray;
@property int myUserID;


kGCD_SINGLETON_FOR_HEADER(UserListVC);

- (NSMutableArray *) getOnlineUserArray;

- (UIViewController*)pushVC;

- (IBAction)LeaveRoomBtn_OnClick;

- (void) showReplyAlertViewWithName:(NSString *)callbackUserName ID:(int)callbackUserID;


@end
