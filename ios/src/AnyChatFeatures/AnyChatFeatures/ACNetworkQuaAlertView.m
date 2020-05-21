//
//  ACNetworkQuaAlertView.m
//  AnyChatFeatures
//
//  Created by Bairui on 2019/6/14.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ACNetworkQuaAlertView.h"

@interface ACNetworkQuaAlertView ()

@property (nonatomic, assign) ACNetworkQuaType  quaType;

@property (weak, nonatomic) IBOutlet UIButton *sendButton;
@property (weak, nonatomic) IBOutlet UIButton *reciveButton;

@end

@implementation ACNetworkQuaAlertView



-(void)show {

    UIView *view = [[NSBundle mainBundle] loadNibNamed:@"ACNetworkQuaAlertView" owner:self options:nil][0];
    [view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
    view.bounds = CGRectMake(0, 0, AdaptW(328), AdaptW(248));
    self.contentView = view;
    self.type = LEOAlertViewTypeNormal;
    self.clickBgHidden = NO;
    self.quaType = ACNetworkQuaTypeSend;
    [super show];
}



- (IBAction)selectBtnClick:(UIButton *)sender {
    
    if(sender.selected == YES)//已选择 不可重复点击
        return;
    
    if(sender == self.sendButton) {
        
        self.quaType = ACNetworkQuaTypeSend;
    } else {
        
        self.quaType = ACNetworkQuaTypeReceive;
    }
}

- (IBAction)cancelClick:(id)sender {
    
    [self dismiss];
}
- (IBAction)certainClick:(id)sender {
    
    [self dismiss];    
    if(self.certainClick) {
        
        self.certainClick(self.textField.text);
    }
}


-(void)setQuaType:(ACNetworkQuaType)quaType {
    
    _quaType = quaType;
    if(quaType == ACNetworkQuaTypeSend) {
        
        self.sendButton.selected = YES;
        self.reciveButton.selected = NO;
    } else {
        
        self.sendButton.selected = NO;
        self.reciveButton.selected = YES;
    }
}

@end
