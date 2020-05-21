//
//  LoginViewController.h
//  队列界面
//
//  Created by j-bairui on 2016/11/5.
//  Copyright © 2016年 anychat. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>

@interface LoginViewController : ACBaseViewController

@property (strong, nonatomic) AnyChatPlatform   *anyChat;       //anyChat对象
@property (assign, nonatomic) int remoteUserId;                 //坐席客服id
@property (assign, nonatomic) int customerId;                   //客户id


@end
