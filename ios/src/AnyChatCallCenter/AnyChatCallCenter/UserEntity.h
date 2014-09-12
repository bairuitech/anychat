//
//  UserEntity.h
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UserEntity : NSObject

@property (nonatomic, strong) NSString *theEntityName;
@property (nonatomic, strong) NSString *theEntityPassword;
@property int theEntityID;
@property int theEntityRemoteID;

@end
