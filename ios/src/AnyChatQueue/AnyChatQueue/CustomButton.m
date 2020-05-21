//
//  customButton.m
//  AnyChatQueue
//
//  Created by lihaitao on 16/11/5.
//  Copyright © 2016年 tim.tan. All rights reserved.
//

#import "CustomButton.h"

@implementation CustomButton


-(void)initTheSubView
{
    self.nameLabel = [[UILabel alloc] init];
    self.checkImageView = [[UIImageView alloc]init];
}

-(void)setCustomUI:(NSString *)text withisChecked: (BOOL)isCheckedEx{
    
    _isChecked=isCheckedEx;
    
    UIImage *image = [UIImage imageNamed:@"已选中按钮"];
    
    self.checkImageView.frame = CGRectMake(0, image.size.height/5, image.size.width/2, image.size.height/2);
    [self addSubview:self.checkImageView];
    
    self.nameLabel.text = text;
    self.nameLabel.font = [UIFont systemFontOfSize:12];
    self.nameLabel.frame = CGRectMake(image.size.width/2+5, 0, self.frame.size.width -image.size.width/2-5, self.frame.size.height);
    [self addSubview:self.nameLabel];
    
    //self.checkImageView.image = [UIImage imageNamed:@"已选中按钮"];
    
    if(_isChecked){
        self.checkImageView.image = [UIImage imageNamed:@"已选中按钮"];
    }else{
        self.checkImageView.image = [UIImage imageNamed:@"未选中按钮"];
    }
}


@end
