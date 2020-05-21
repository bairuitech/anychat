//
//  TextModel.h
//  helloAnyChat
//
//  Created by Mac on 16/5/19.
//  Copyright © 2016年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TextModel : NSObject

//#define kAnyChatRoomID 1
//#define kUserID 1001
//#define kAnyChatIP @"demo.anychat.cn"
//#define kAnyChatPort @"8906"
//#define kAnyChatUserName @"AnyChat"

@property (nonatomic, strong) NSString *roomId;

@property (nonatomic, strong) NSString *userId;

@property (nonatomic, strong) NSString *chatIp;

@property (nonatomic, strong) NSString *chatPort;

@property (nonatomic, strong) NSString *userName;



@end
