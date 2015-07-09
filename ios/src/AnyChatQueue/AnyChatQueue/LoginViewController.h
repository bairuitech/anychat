//
//  LoginViewController.h
//  AnyChatQueue
//
//  Created by tim.tan on 15/6/12.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  登录

#import <UIKit/UIKit.h>

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"
#import "AnyChatObjectDefine.h"

@interface LoginViewController : UIViewController
@property (strong, nonatomic) AnyChatPlatform   *anyChat;       //anyChat对象
@property (assign, nonatomic) int remoteUserId;                 //坐席客服id
@property (assign, nonatomic) int customerId;                   //客户id
@end
