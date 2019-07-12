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
