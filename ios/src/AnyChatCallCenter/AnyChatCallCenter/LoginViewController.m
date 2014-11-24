//
//  LoginViewController.m
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "LoginViewController.h"

@interface LoginViewController ()

@end

@implementation LoginViewController

@synthesize theUserName;
@synthesize thePassword;
@synthesize theLoginBtn;
@synthesize theSettingsBtn;
@synthesize theVersion;
@synthesize theTitleFony;
@synthesize theHideKeyboardBtn;
@synthesize LoginVC;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    [AnyChatPlatform ActiveCallLog:YES];
    [AnyChatPlatform InitSDK:0];
    [AnyChatPlatform SetSDKOptionInt:134 :1];
}


- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:YES];
    
    [self prefersStatusBarHidden];
    [self.navigationController setNavigationBarHidden:YES];

    float sysVersion = [[UIDevice currentDevice].systemVersion floatValue];
    if (sysVersion <= 7.0) {

        theLoginBtn.titleLabel.font = [UIFont systemFontOfSize:16.0];
        theLoginBtn.titleLabel.textColor = [UIColor grayColor];
        theSettingsBtn.titleLabel.font = [UIFont systemFontOfSize:16.0];
        theSettingsBtn.titleLabel.textColor = [UIColor grayColor];

        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }
    
    [theHideKeyboardBtn setTitle:@"" forState:UIControlStateNormal];
    [theHideKeyboardBtn setTitle:@"" forState:UIControlStateSelected];
    
    [theVersion setText:[AnyChatPlatform GetSDKVersion]];
}


#pragma mark - Action Method


- (IBAction)OnLoginBtnClicked:(id)sender
{
    if([theUserName.text length] == 0)
        theUserName.text=@"iPhone";
    
    HallViewController *hallVC = [[HallViewController alloc] init];
    
    [AnyChatPlatform Connect:[AnyChatAppDelegate GetServerIP] : [AnyChatAppDelegate GetServerPort]];
    [AnyChatPlatform Login:self.theUserName.text : self.thePassword.text];
    
    [self.navigationController pushViewController:hallVC animated:YES];
    
}


- (IBAction)OnNetConfigBtnClicked:(id)sender
{
    SettingsViewController *settingsVC = [SettingsViewController new];
    
    settingsVC.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
    [self presentViewController:settingsVC animated:YES completion:nil];
    
}


- (IBAction) hideKeyBoard:(id)sender
{
    [theUserName resignFirstResponder];
    [thePassword resignFirstResponder];
}


- (BOOL)prefersStatusBarHidden{
    return YES;
}


#pragma mark - Memory Warning

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
