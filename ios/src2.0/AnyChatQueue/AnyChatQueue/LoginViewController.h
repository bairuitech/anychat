//
//  LoginViewController.h
//  AnyChatQueue
//
//  Created by tim.tan on 15/6/12.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  登录

#import <UIKit/UIKit.h>
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>
#import "AnyChat_QueueModel.h"

@class VideoViewController;

@interface LoginViewController : UIViewController
@property (strong, nonatomic) AnyChatPlatform   *anyChat;       //anyChat对象
@property(nonatomic,weak) VideoViewController* videoViewController; //视频通话控制器
@end
