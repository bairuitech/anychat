//
//  BusinessHall.h
//  AnyChatQueue
//
//  Created by tim.tan on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  营业厅模型数据

#import <Foundation/Foundation.h>

@interface BusinessHall : NSObject

@property(nonatomic, assign)long long hallId;       //营业厅id号
@property(nonatomic, copy)NSString *title;          //标题
@property(nonatomic, copy)NSString *icon;           //图标

- (instancetype)initWithDic:(NSDictionary *)dic;

+ (instancetype)businessHallWithDic:(NSDictionary *)dic;
@end
