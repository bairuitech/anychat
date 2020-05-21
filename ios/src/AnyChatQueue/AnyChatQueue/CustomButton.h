//
//  customButton.h
//  AnyChatQueue
//
//  Created by lihaitao on 16/11/5.
//  Copyright © 2016年 tim.tan. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CustomButton : UIButton

@property (nonatomic, strong) UIImageView *checkImageView;

@property (nonatomic, strong) UILabel *nameLabel;

@property (nonatomic, assign) BOOL isChecked;

-(void)initTheSubView;

-(void)setCustomUI:(NSString *)text withisChecked: (BOOL)isCheckedEx;


@end
