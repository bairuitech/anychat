//
//  QueueViewController.h
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  排队等待

#import <UIKit/UIKit.h>

@interface QueueViewController : ACBaseViewController
@property(nonatomic, assign)int businessId;                             // 队列id
@property (weak, nonatomic) IBOutlet UILabel *queuUserSiteLabel;        // 队列用户位置
@property (weak, nonatomic) IBOutlet UILabel *queueUserCountLabel;      // 队列人数
@property(nonatomic, assign)int isCustomerServiceAutoMode;              //是否开启了自动路由模式

- (void) videoCallRemote:(int)remoteUserId;

- (void)updateLabelBySite:(int)site userCount:(int)userCount;
@end
