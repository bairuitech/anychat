//
//  BRAC_Result.h
//  AnyChatInterviewIphone
//
//  Created by bairuitech on 2017/7/8.
//  Copyright © 2017年 anychat. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AnyChatResult : NSObject

/**
 错误码
 */
@property (nonatomic, assign) int errorCode;

/**
 错误描述
 */
@property (nonatomic, copy) NSString *errorMsg;

- (instancetype)initWithErr:(int)code msg:(NSString *)msg;
- (instancetype)initWithErr:(int)code;

- (NSDictionary *)toDictionary;
@end
