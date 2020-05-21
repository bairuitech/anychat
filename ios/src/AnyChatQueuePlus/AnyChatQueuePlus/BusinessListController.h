//
//  BusinessListController.h
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  业务列表

#import <UIKit/UIKit.h>

@interface BusinessListController : ACBaseViewController

@property (nonatomic, strong) UITableView *tableView;

@property(nonatomic, strong)NSArray *businessListIdArray;   //队列id数组
@property(nonatomic, assign)int businessHallId;                 //营业厅id
@property(nonatomic, copy)NSString *businessHallName;           //营业厅名字

@end
