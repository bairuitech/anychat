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

@property (nonatomic, strong) IBOutlet UITextField   *theIP;
@property (nonatomic, strong) IBOutlet UITextField   *thePort;
@property (nonatomic, strong) IBOutlet UITextField   *theUserName;
@property (nonatomic, strong) IBOutlet UIButton      *theLoginBtn;
@property (nonatomic, strong) IBOutlet UILabel       *theVersion;
@end

@implementation LoginViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [AnyChatPlatform InitSDK:0];
    [AnyChatPlatform SetSDKOptionInt:134 :1];
    
    self.theUserName.text = kAnyChatUserName;
    self.theIP.text = kAnyChatIP;
    self.thePort.text = kAnyChatPort;
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
}


- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:YES];
    
    [self.theVersion setText:[AnyChatPlatform GetSDKVersion]];
}

#pragma mark - Action Method


- (IBAction)OnLoginBtnClicked:(id)sender
{
    
    
    if([self.theUserName.text length] == 0) {
        self.theUserName.text = kAnyChatUserName;
    }
    if([self.theIP.text length] == 0) {
        self.theIP.text = kAnyChatIP;
    }
    if([self.thePort.text length] == 0) {
        self.thePort.text = kAnyChatPort;
    }
    
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    [AnyChatPlatform Connect:self.theIP.text : [self.thePort.text intValue]];
    
    
    /*
     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
     */
    [AnyChatPlatform Login:self.theUserName.text :nil];
    
    
    HallViewController *hallVC = [[HallViewController alloc] init];
    [self.navigationController pushViewController:hallVC animated:YES];
    
}

- (IBAction) hideKeyBoard:(id)sender
{
    [self.view endEditing:YES];
}

-(BOOL)navBarTranslucent {
    
    return YES;
}
@end
