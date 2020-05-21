//
//  VideoViewController.h
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  视频聊天

#import <UIKit/UIKit.h>

@interface VideoViewController : ACBaseViewController
@property(nonatomic, assign)int remoteUserId;

//打开对方的视频
-(void)openRemoteView;

@end
