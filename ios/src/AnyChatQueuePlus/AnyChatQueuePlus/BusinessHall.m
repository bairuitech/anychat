//
//  BusinessHall.m
//  AnyChatQueue
//
//  Created by tim.tan on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "BusinessHall.h"

@implementation BusinessHall

- (instancetype)initWithDic:(NSDictionary *)dic {
    self = [super init];
    if (self != nil) {
        self.hallId = [[dic objectForKey:@"areaId"] longLongValue];
        self.title = [dic objectForKey:@"areaName"];
        self.icon = [NSString stringWithFormat:@"stronghold_0%i",(arc4random()%4)+1];
    }
    return self;
}

+ (instancetype)businessHallWithDic:(NSDictionary *)dic {
    return [[self alloc] initWithDic:dic];
}

@end
