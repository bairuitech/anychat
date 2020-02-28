//
//  ACBaseViewController.h
//  AnyChatFeatures
//
//  Created by Bairui on 2019/6/10.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface ACBaseViewController : UIViewController

//导航栏左键返回  重写可自定义返回逻辑
- (void)navLeftClick;

//导航栏是否透明  默认NO
- (BOOL)navBarTranslucent;


- (UIColor *)navBarColor;

- (BOOL)needLeftBackNavItem;

- (void )showAutoDismissAlertView:(NSString *)Title : (NSString *)subTitle;
@end

NS_ASSUME_NONNULL_END
