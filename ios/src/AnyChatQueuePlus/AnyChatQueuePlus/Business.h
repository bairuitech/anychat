//
//  Business.h
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  业务模型数据

#import <Foundation/Foundation.h>

@interface Business : NSObject

@property(nonatomic, assign)long long businessId;
@property(nonatomic, copy)NSString *title;


- (instancetype)initWithDic:(NSDictionary *)dic;
+ (instancetype)businessWithDic:(NSDictionary *)dic;
@end
