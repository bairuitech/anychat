//
//  User.h
//  HelloAnyChatCallCenter
//
//  Created by bairuitech on 15/5/22.
//  Copyright (c) 2015年 bairuitech. All rights reserved.
//  用户模型

#import <Foundation/Foundation.h>

@interface User : NSObject
@property(copy, nonatomic)NSString *userId;     //用户id
@property(copy, nonatomic)NSString *userName;   //用户名
@property(copy, nonatomic)NSString *userFace;   //用户头像

@property(assign, nonatomic) BOOL isCloseCamera;
@property(assign, nonatomic) BOOL isCloseMic;


+ (instancetype)userWithUserId:(NSString *)userId;

@end
