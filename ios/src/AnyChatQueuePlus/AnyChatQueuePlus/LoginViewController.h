//
//  LoginViewController.h
//  队列界面
//
//  Created by j-bairui on 2016/11/5.
//  Copyright © 2016年 anychat. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"
#import "AnyChatObjectDefine.h"
@class VideoViewController;

@interface LoginViewController : UIViewController

@property (strong, nonatomic) AnyChatPlatform   *anyChat;       //anyChat对象
@property (assign, nonatomic) int remoteUserId;                 //坐席客服id
@property (assign, nonatomic) int customerId;                   //客户id

@property(nonatomic,weak) VideoViewController* videoViewController; //视频通话控制器

@end
