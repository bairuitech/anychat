//
//  BusinessListClientCell.h
//  AnyChatQueue
//
//  Created by bairuitech on 2018/1/25.
//  Copyright © 2018年 tim.tan. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BusinessListClientCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *queueNameLab;
@property (weak, nonatomic) IBOutlet UILabel *countLab;
@property (copy, nonatomic) void (^EnterQueueBlock)();
@end
