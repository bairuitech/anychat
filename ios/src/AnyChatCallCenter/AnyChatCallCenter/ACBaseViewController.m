//
//  ACBaseViewController.m
//  AnyChatFeatures
//
//  Created by Bairui on 2019/6/10.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ACBaseViewController.h"

@interface ACBaseViewController ()

@end

@implementation ACBaseViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self p_configLeftItem];
    
}

-(void)viewWillAppear:(BOOL)animated {
    
    [super viewWillAppear:animated];
    
    self.navigationController.navigationBarHidden = NO;
   
    UIColor *color = [UIColor colorWithRed:0 green:139 / 255.0 blue:227 / 255.0 alpha:1];
    CGFloat alpha = [self navBarTranslucent] ? 0 : 1;
    UIImage *image = [ACBaseViewController createImageWithColor:[color colorWithAlphaComponent:alpha]];
    [self.navigationController.navigationBar setBackgroundImage:image forBarMetrics:UIBarMetricsDefault];
    self.navigationController.navigationBar.shadowImage = image;
    
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;

}



-(BOOL)navBarTranslucent {
    
    return NO;
}

- (void)p_configLeftItem {
    
    if(![self needLeftItem])
        return;
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(navLeftClick) forControlEvents:UIControlEventTouchUpInside];
    [button setImage:[UIImage imageNamed:@"icon_back"] forState:UIControlStateNormal];
    [button sizeToFit];
    
    UIBarButtonItem *leftItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.leftBarButtonItem = leftItem;
}

- (BOOL)needLeftItem {
    
    if(self.presentingViewController) {
        
        return YES;
    } else if(self.navigationController.viewControllers > 0 && self.navigationController.viewControllers[0] != self) {
        
        return YES;
    }
    
    return NO;
}


- (void)navLeftClick {
    
    if(self.presentingViewController) {
        
        [self dismissViewControllerAnimated:YES completion:nil];
    } else {
        
        [self.navigationController popViewControllerAnimated:YES];
    }
    
}

-(BOOL)prefersStatusBarHidden {
    
    return NO;
}

-(UIStatusBarStyle)preferredStatusBarStyle {
    
    return UIStatusBarStyleLightContent;
}



- (BOOL)shouldAutorotate {
    return NO;
}
//返回直接支持的方向
- (UIInterfaceOrientationMask)supportedInterfaceOrientations{
    return UIInterfaceOrientationMaskPortrait;
}
//返回最优先显示的屏幕方向
- (UIInterfaceOrientation)preferredInterfaceOrientationForPresentation {
    return UIInterfaceOrientationPortrait;
}



- (void )showAutoDismissAlertView:(NSString *)Title : (NSString *)subTitle {

    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:Title
                                                        message:subTitle
                                                       delegate:self
                                              cancelButtonTitle:nil
                                              otherButtonTitles:nil,nil];
    [alertView show];
    
    [self performSelector:@selector(p_dimissAlertView:) withObject:alertView afterDelay:1.5];
}

- (void)p_dimissAlertView:(UIAlertView *)alert {
    
    if(alert){
        [alert dismissWithClickedButtonIndex:[alert cancelButtonIndex] animated:YES];
    }
}


+(UIImage*) createImageWithColor:(UIColor*) color
{
    CGRect rect=CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return theImage;
}

@end
