//
//  BusinessListController.h
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  客户 ----- 业务队列列表

#import <UIKit/UIKit.h>

@interface BusinessListController : UIViewController
//@property(nonatomic, strong)NSArray *businessListIdArray;   //队列id数组
//@property(nonatomic, assign)int businessHallId;                 //营业厅id
@property(nonatomic, strong)NSArray *businesses;

@property (nonatomic, strong)IBOutlet  UITableView *tableView;

@end
