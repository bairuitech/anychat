//
//  ACVideoAlertView.m
//  AnyChatFeatures
//
//  Created by Bairui on 2019/6/14.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ACVideoAlertView.h"

@interface ACVideoAlertView()
@property (weak, nonatomic) IBOutlet UILabel *titleLabel;

@end

@implementation ACVideoAlertView
- (IBAction)buttonAction:(UIButton *)sender {

    NSInteger index = sender.tag - 1000;
    [self dismiss];
    if(self.clickBlock)
        self.clickBlock(index);
}

-(void)show {
    
    UIView *view = [[NSBundle mainBundle] loadNibNamed:@"ACVideoAlertView" owner:self options:nil][0];
    [view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
    view.bounds = CGRectMake(0, 0, AdaptW(282), AdaptW(124));
    self.contentView = view;
    self.type = LEOAlertViewTypeNormal;
    self.clickBgHidden = NO;
    [super show];
}

- (void)changeTitle:(NSString *)title {
    
    self.titleLabel.text = title;
}


+ (ACVideoAlertView *)showAlertViewByTitle:(NSString *)title
                                clickBlock:(ACVideoAlertViewClick) clickBlock {
    
    ACVideoAlertView *alertView = [[ACVideoAlertView alloc] init];
    alertView.clickBlock = clickBlock;
    alertView.clickBgHidden = NO;
    [alertView show];
    [alertView changeTitle:title];
    return alertView;
}

@end
