//
//  UINavigationController+DeviceOrientataion.m
//  HelloAnyChat
//
//  Created by bairui on 2019/7/18.
//  Copyright © 2019 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "UINavigationController+DeviceOrientataion.h"

@implementation UINavigationController (DeviceOrientataion)

-(UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return self.topViewController.supportedInterfaceOrientations;
}

-(BOOL)shouldAutorotate {
    return [self.topViewController shouldAutorotate];
}

- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation {
    return [self.topViewController preferredInterfaceOrientationForPresentation];
}

@end
