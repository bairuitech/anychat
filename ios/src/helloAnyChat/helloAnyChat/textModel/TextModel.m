//
//  TextModel.m
//  HelloAnyChat
//
//  Created by Mac on 16/5/19.
//  Copyright © 2016年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "TextModel.h"

@interface TextModel()<NSCoding>

@end

@implementation TextModel

/**
 *  从文件中解析对象的时候调用
 *
 */
- (id)initWithCoder:(NSCoder *)decode {
    if (self = [super init]) {
        self.roomId = [decode decodeObjectForKey:@"roomId "];
        self.userName = [decode decodeObjectForKey:@"userName"];
        self.chatIp = [decode decodeObjectForKey:@"chatIp"];
        self.chatPort = [decode decodeObjectForKey:@"chatPort"];
        
    }
    return self;
}

/**
 *  将对象写入到文件的时候调用
 *
 */
- (void)encodeWithCoder:(NSCoder *)encode {
    [encode encodeObject:self.roomId forKey:@"roomId"];
    [encode encodeObject:self.userName forKey:@"userName"];
    [encode encodeObject:self.chatIp forKey:@"chatIp"];
    [encode encodeObject:self.chatPort forKey:@"chatPort"];
}

@end
