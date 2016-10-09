//
//  VideoViewController.h
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  视频聊天

#import <UIKit/UIKit.h>

@interface VideoViewController : UIViewController
@property(nonatomic, assign)int remoteUserId;

-(void)openRemoteView;

@end
