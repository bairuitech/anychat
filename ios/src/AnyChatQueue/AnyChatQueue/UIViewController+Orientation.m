//
//  UIViewController+Orientation.m
//  AnyChatQueue
//
//  Created by bairui on 2019/7/22.
//  Copyright © 2019 tim.tan. All rights reserved.
//

#import "UIViewController+Orientation.h"

@implementation UIViewController (Orientation)

- (BOOL)shouldAutorotate {
    return YES;
}
//返回直接支持的方向
- (UIInterfaceOrientationMask)supportedInterfaceOrientations{
    return UIInterfaceOrientationMaskPortrait;
}
//返回最优先显示的屏幕方向
- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation {
    return UIInterfaceOrientationPortrait;
}
@end
