//
//  LEOAlertView.m
//  LEOAlertView
//
//  Created by LeoWang on 2019/6/13.
//  Copyright © 2019年 LeoWang. All rights reserved.
//

#import "LEOAlertView.h"

@interface LEOAlertView ()
@property (nonatomic, strong) UIView *bgView;


@end

@implementation LEOAlertView


- (instancetype)init
{
    if (self = [super init]) {
        
        self.frame = CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, [UIScreen mainScreen].bounds.size.height);
        self.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:0.2];
        self.alpha = 0;
    }
    
    return self;
}

#pragma mark - Public method -
- (void)show
{
    
    [self showInView:[UIApplication sharedApplication].keyWindow];
}



- (void)showInView:(UIView *)view {

    [view addSubview:self];
    switch (self.type) {
        case LEOAlertViewTypeNormal:
            self.showAnimation = [self p_defaultAlertShowAnimation];
            break;
        case LEOAlertViewTypeActionSheet:
            self.showAnimation = [self p_defaultActionSheetShowAnimation];
            break;
        default:
            self.showAnimation = [self p_defaultAlertShowAnimation];
            break;
    }
    
    [_contentView.layer addAnimation:self.showAnimation forKey:@"show"];
    [UIView animateWithDuration:0.25 animations:^{
        
        self.alpha = 1;
    }];
}



- (void)dismiss {

    [self.contentView.layer removeAnimationForKey:@"show"];
    
    switch (self.type) {
        case LEOAlertViewTypeNormal:
            self.dismissAnimation = [self p_defalutAlertDismissAnimation];
            break;
        case LEOAlertViewTypeActionSheet:
            self.dismissAnimation = [self p_defaultActionSheetDismissAnimation];
            break;
        default:
            self.dismissAnimation = [self p_defalutAlertDismissAnimation];
            break;
    }

    
    [_contentView.layer addAnimation:self.dismissAnimation forKey:@"dismiss"];
    [UIView animateWithDuration:0.3 animations:^{

        self.alpha = 0;
    } completion:^(BOOL finished) {

        [self removeFromSuperview];
    }];
}








#pragma mark - default animations -

- (CAAnimation *)p_defaultAlertShowAnimation {
    
    CAKeyframeAnimation *animation = [CAKeyframeAnimation animationWithKeyPath:@"transform"];
    animation.duration = 0.25;
    animation.removedOnCompletion = NO;
    animation.fillMode = kCAFillModeForwards;
    NSMutableArray *values = [NSMutableArray array];
    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(0.9, 0.9, 1.0)]];
    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(1.1, 1.1, 1.0)]];
    [values addObject:[NSValue valueWithCATransform3D:CATransform3DMakeScale(1.0, 1.0, 1.0)]];
    animation.values = values;
    
    return animation;
}
-(CAAnimation *)p_defalutAlertDismissAnimation {
    
    CABasicAnimation *opacityAnimation = [CABasicAnimation animationWithKeyPath:@"opacity"];
    opacityAnimation.fromValue = [NSNumber numberWithFloat:1.0];
    opacityAnimation.toValue = [NSNumber numberWithFloat:0.0];
    opacityAnimation.duration = 0.30;
    opacityAnimation.removedOnCompletion = NO;
    opacityAnimation.fillMode = kCAFillModeForwards;
    return opacityAnimation;
}



- (CAAnimation *)p_defaultActionSheetShowAnimation {
    
    CALayer *layer = self.contentView.layer;
    CGPoint toPoint = layer.position;
    toPoint.y -= CGRectGetHeight(self.contentView.bounds);
    
    CABasicAnimation *animation  = [CABasicAnimation animationWithKeyPath:@"position"];
    animation.fromValue =  [NSValue valueWithCGPoint: layer.position];
    animation.toValue = [NSValue valueWithCGPoint:toPoint];
    animation.duration = 0.20;
    animation.fillMode = kCAFillModeForwards;
    animation.removedOnCompletion = NO;
    return animation;
}



- (CAAnimation *)p_defaultActionSheetDismissAnimation {
    
    CALayer *layer = self.contentView.layer;
    CGPoint fromPoint = layer.position;
    fromPoint.y -= CGRectGetHeight(self.contentView.bounds);
    
    CABasicAnimation *animation  = [CABasicAnimation animationWithKeyPath:@"position"];
    animation.fromValue =  [NSValue valueWithCGPoint: fromPoint];
    animation.toValue = [NSValue valueWithCGPoint:layer.position];
    animation.duration = 0.25;
    animation.fillMode = kCAFillModeForwards;
    animation.removedOnCompletion = NO;
    return animation;
}

#pragma mark - overwrite -

- (UIView *)bgView
{
    if (_bgView == nil) {
        
        _bgView = [[UIView alloc] initWithFrame:self.bounds];
        if (self.contentView) {
            
            [self insertSubview:_bgView belowSubview:self.contentView];
        }else{
            
            [self addSubview:_bgView];
        }
    }
    return _bgView;
}

- (void)setType:(LEOAlertViewType)type
{
    _type = type;
    if (self.contentView && _type == LEOAlertViewTypeActionSheet) {
        
        _contentView.frame = CGRectMake((CGRectGetMaxX(self.frame) - CGRectGetWidth(_contentView.frame)) * 0.5, CGRectGetMaxY(self.frame), CGRectGetWidth(_contentView.frame), CGRectGetHeight(_contentView.frame));
        [self p_addRoundingCorners];
    } else if(self.contentView && _type == LEOAlertViewTypeNormal) {
        
        _contentView.center = self.center;
    }
}

- (void)setContentView:(UIView *)contentView
{
    _contentView = contentView;
    if (self.type == LEOAlertViewTypeActionSheet) {
        
        _contentView.frame = CGRectMake((CGRectGetMaxX(self.frame) - CGRectGetWidth(_contentView.frame)) * 0.5, CGRectGetMaxY(self.frame), CGRectGetWidth(_contentView.frame), CGRectGetHeight(_contentView.frame));
    
        [self p_addRoundingCorners];
    } else{
        
        _contentView.center = self.center;
    }
    [self addSubview:_contentView];
}




-(void)setClickBgHidden:(BOOL)clickBgHidden {
    
    _clickBgHidden = clickBgHidden;
    if(_clickBgHidden) {
        
        [self.bgView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(dismiss)]];
    }
}


- (void)p_addRoundingCorners {
    
    UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:_contentView.bounds byRoundingCorners:UIRectCornerTopLeft | UIRectCornerTopRight cornerRadii:CGSizeMake(5, 5)];
    CAShapeLayer *shapeLayer = [CAShapeLayer layer];
    shapeLayer.frame = _contentView.bounds;
    shapeLayer.path = path.CGPath;
    _contentView.layer.mask = shapeLayer;
}
@end
