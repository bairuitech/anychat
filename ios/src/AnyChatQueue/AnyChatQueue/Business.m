//
//  Business.m
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "Business.h"

@implementation Business

- (instancetype)initWithDic:(NSDictionary *)dic {
    
    self = [super init];
    if (self) {
        self.title = [dic objectForKey:@"name"];
        self.businessId = [[dic objectForKey:@"id"] intValue];
    }
    return self;
}

+ (instancetype)businessWithDic:(NSDictionary *)dic {
    return [[self alloc] initWithDic:dic];
}

@end
