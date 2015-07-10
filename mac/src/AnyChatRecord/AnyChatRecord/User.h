//
//  User.h
//  AnyChatRecord
//
//  Created by tim.tan on 15/6/8.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  用户数据模型

#import <Foundation/Foundation.h>

@interface User : NSObject
@property(copy, nonatomic)NSString *userId;     //用户id
@property(copy, nonatomic)NSString *userName;   //用户名
@property(copy, nonatomic)NSString *userFace;   //用户头像

+ (instancetype)userWithUserId:(NSString *)userId;

@end
