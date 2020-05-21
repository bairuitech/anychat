//
//  BusinessHallCell.m
//  AnyChatQueue
//
//  Created by tim.tan on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "BusinessHallCell.h"
#import "BusinessHall.h"

@interface BusinessHallCell()
@property (weak, nonatomic) IBOutlet UIImageView *iconView;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;

@end

@implementation BusinessHallCell

- (void)awakeFromNib {
    [super awakeFromNib];
    self.iconView.layer.cornerRadius = 7;
    self.iconView.clipsToBounds = YES;
}

- (void)setBusinessHall:(BusinessHall *)businessHall {

    _businessHall = businessHall;
    
    // 1.设置头像
    self.iconView.image = [UIImage imageNamed:businessHall.icon];
    
    // 2.设置标题
    self.nameLabel.text = businessHall.title;
}

@end
