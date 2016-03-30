//
//  LoginViewController.m
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "LoginViewController.h"

#define kUserID 1001
#define kAnyChatIP @"demo.anychat.cn"
#define kAnyChatPort @"8906"
#define kAnyChatUserName @"AnyChat"

@interface LoginViewController ()

@end

@implementation LoginViewController

@synthesize theIP;
@synthesize thePort;
@synthesize theUserName;
@synthesize theLoginBtn;
@synthesize theVersion;
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
    
    [AnyChatPlatform InitSDK:0];
    [AnyChatPlatform SetSDKOptionInt:134 :1];
}


- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:YES];
    
    [self prefersStatusBarHidden];
    [self.navigationController setNavigationBarHidden:YES];
  
    theUserName.text = kAnyChatUserName;
    theIP.text = kAnyChatIP;
    thePort.text = kAnyChatPort;
    
    float sysVersion = [[UIDevice currentDevice].systemVersion floatValue];
    if (sysVersion <= 7.0) {

        theLoginBtn.titleLabel.font = [UIFont systemFontOfSize:16.0];
        theLoginBtn.titleLabel.textColor = [UIColor grayColor];

        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }
    
    [theHideKeyboardBtn setTitle:@"" forState:UIControlStateNormal];
    [theHideKeyboardBtn setTitle:@"" forState:UIControlStateSelected];
    
    [theVersion setText:[AnyChatPlatform GetSDKVersion]];
}

#pragma mark - Action Method


- (IBAction)OnLoginBtnClicked:(id)sender
{
    
    HallViewController *hallVC = [[HallViewController alloc] init];
    
    if([theUserName.text length] == 0) {
        theUserName.text = kAnyChatUserName;
    }
    if([theIP.text length] == 0) {
        theIP.text = kAnyChatIP;
    }
    if([thePort.text length] == 0) {
        thePort.text = kAnyChatPort;
    }

    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    [AnyChatPlatform Connect:theIP.text : [thePort.text intValue]];
    
    
    /*
     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
     */
    [AnyChatPlatform Login:theUserName.text :nil];
    
    
    
    [self.navigationController pushViewController:hallVC animated:YES];
    
}

- (IBAction) hideKeyBoard:(id)sender
{
    [theIP resignFirstResponder];
    [thePort resignFirstResponder];
    [theUserName resignFirstResponder];
}


- (BOOL)prefersStatusBarHidden{
    return YES;
}

@end
