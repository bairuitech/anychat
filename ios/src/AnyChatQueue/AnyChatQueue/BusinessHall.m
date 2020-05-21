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
        self.hallId = [[dic objectForKey:@"areaId"] intValue];
        self.title = [dic objectForKey:@"areaName"];
        self.icon = [NSString stringWithFormat:@"营业厅%i",(arc4random()%2)+1];
    }
    return self;
}

+ (instancetype)businessHallWithDic:(NSDictionary *)dic {
    return [[self alloc] initWithDic:dic];
}

@end
