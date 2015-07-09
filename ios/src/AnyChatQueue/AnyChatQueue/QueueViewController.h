//
//  QueueViewController.h
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//  排队等待

#import <UIKit/UIKit.h>

@interface QueueViewController : UIViewController
@property(nonatomic, assign)int businessId;     //队列id
@property (weak, nonatomic) IBOutlet UILabel *beforeLabel;
@end
