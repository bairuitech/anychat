//
//  ServerQueueViewController.h
//  AnyChatQueue
//
//  Created by tim.tan on 15/6/25.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  坐席（客服）----- 坐席服务控制器(含业务队列列表)

#import <UIKit/UIKit.h>

@interface ServerQueueViewController : UIViewController
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property(nonatomic, strong)UIAlertView *waitingAlertView;
//@property(nonatomic, strong)NSArray *businessListIdArray;   //队列id数组
//@property(nonatomic, assign)int businessHallId;             //营业厅id
//@property(nonatomic, assign)int selfUserId;                 //用户id
@property(nonatomic, strong)NSArray *businesses;

@end
