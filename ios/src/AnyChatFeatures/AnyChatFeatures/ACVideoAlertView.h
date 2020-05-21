//
//  ACVideoAlertView.h
//  AnyChatFeatures
//
//  Created by Bairui on 2019/6/14.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "LEOAlertView.h"

NS_ASSUME_NONNULL_BEGIN

typedef void(^ACVideoAlertViewClick)(NSInteger index);


@interface ACVideoAlertView : LEOAlertView


@property (nonatomic, copy) ACVideoAlertViewClick clickBlock;
- (void)changeTitle:(NSString *)title;


+ (ACVideoAlertView *)showAlertViewByTitle:(NSString *)title
                                clickBlock:(ACVideoAlertViewClick) clickBlock;
@end

NS_ASSUME_NONNULL_END
