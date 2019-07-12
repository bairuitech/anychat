//
//  LEOAlertView.h
//  LEOAlertView
//
//  Created by LeoWang on 2019/6/13.
//  Copyright © 2019年 LeoWang. All rights reserved.
//

#import <UIKit/UIKit.h>


typedef NS_ENUM(NSInteger, LEOAlertViewType) {
    LEOAlertViewTypeNormal,         //普通alert
    LEOAlertViewTypeActionSheet,    //普通actionSheet
    LEOAlertViewTypeCustom,         //自定义

};

NS_ASSUME_NONNULL_BEGIN

@interface LEOAlertView : UIView


@property (nonatomic, assign) LEOAlertViewType  type;

/*
 * contentView为自定义弹窗的容器，请优先指定contentView
 */
@property (nonatomic, strong) UIView *contentView;

/*
 * type为 normal或actionSheet 则默认动画；如果要自定义动画，请先设置type=custom
 * 默认为alert动画
 */
@property (nonatomic, strong) CAAnimation *showAnimation;
@property (nonatomic, strong) CAAnimation *dismissAnimation;

/*
 * 点击背景是否自动隐藏，默认为YES
 */
@property (nonatomic, assign) BOOL clickBgHidden;



//默认show在keywindow中
- (void)show;

//在指定的view上显示
- (void)showInView:(UIView *)view;

- (void)dismiss;

@end

NS_ASSUME_NONNULL_END
