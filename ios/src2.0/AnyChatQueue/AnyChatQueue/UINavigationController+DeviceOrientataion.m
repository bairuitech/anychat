//
//  UINavigationController+DeviceOrientataion.m
//  AnyChatCallCenter
//
//  Created by bairui on 2019/7/18.
//  Copyright © 2019 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "UINavigationController+DeviceOrientataion.h"

@implementation UINavigationController (DeviceOrientataion)


-(UIInterfaceOrientationMask)supportedInterfaceOrientations
{
    return self.viewControllers.lastObject.supportedInterfaceOrientations;
}
-(BOOL)shouldAutorotate
{
    return [self.viewControllers.lastObject shouldAutorotate];
}

- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation
{
    return [self.viewControllers.lastObject preferredInterfaceOrientationForPresentation];
}


-(BOOL)prefersStatusBarHidden {
    
    return NO;
}

-(UIStatusBarStyle)preferredStatusBarStyle {
    
    return UIStatusBarStyleLightContent;
}

@end
