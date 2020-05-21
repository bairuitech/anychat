//
//  BusinessListClientCell.m
//  AnyChatQueue
//
//  Created by bairuitech on 2018/1/25.
//  Copyright © 2018年 tim.tan. All rights reserved.
//

#import "BusinessListClientCell.h"

@implementation BusinessListClientCell
- (IBAction)enterQueue:(id)sender {
    if (self.EnterQueueBlock) {
        self.EnterQueueBlock();
    }
}

- (void)awakeFromNib {
    [super awakeFromNib];
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
