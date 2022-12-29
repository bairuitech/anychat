//
//  User.m
//  AnyChatRecord
//
//  Created by tim.tan on 15/6/8.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "User.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>

@implementation User
+ (instancetype)userWithUserId:(NSString *)userId
{
    User *user = [[User alloc] init];
    user.userName = [AnyChatPlatform GetUserName:[userId intValue]];
    user.userId = userId;
    user.userFace = [[NSString alloc] initWithFormat:@"%i",[self getRandomNumber:1 to:5]];
    return user;
}

//获取随机数字
+ (int)getRandomNumber:(int)from to:(int)to {
    return (int)(from + (arc4random() % (to - from + 1)));
}
@end
