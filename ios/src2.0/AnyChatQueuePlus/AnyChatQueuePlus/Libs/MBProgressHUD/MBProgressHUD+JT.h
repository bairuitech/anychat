//
//  MBProgressHUD+JT.h
//
//  Created by tim.tan on 15/5/16.
//  Copyright (c) 2015年 bairuitech. All rights reserved.
//

#import "MBProgressHUD.h"

@interface MBProgressHUD (JT)

#pragma mark 显示一些信息
+ (MBProgressHUD *)showMessage:(NSString *)message;
+ (MBProgressHUD *)showMessage:(NSString *)message toView:(UIView *)view;

#pragma mark 显示正确信息
+ (void)showSuccess:(NSString *)success;
+ (void)showSuccess:(NSString *)success toView:(UIView *)view;

#pragma mark 显示错误信息
+ (void)showError:(NSString *)error;
+ (void)showError:(NSString *)error toView:(UIView *)view;

#pragma mark 隐藏信息
+ (void)hideHUD;
+ (void)hideHUDForView:(UIView *)view;

@end
