//
//  LoginViewController.m
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "LoginViewController.h"
#import "MBProgressHUD+JT.h"
#import "RadioButton.h"
#import "AFNetworking.h"

#define kUserID 1001
#define kSignServerURL @"http://192.168.1.7:8980/"
#define kAnyChatIP @"cluster.anychat.cn"
#define kAnyChatPort @"8102"
#define kAnyChatUserName @"AnyChat"
#define kAnyChatGuid @"bb9ca6ec-e611-4208-ab8f-44b5881c41e8"

typedef enum {
    AnyChatVCLoginModeGeneralLogin,
    AnyChatVCLoginModeSignLogin
} AnyChatVCLoginMode;

@interface LoginViewController ()
@property (nonatomic, assign) AnyChatVCLoginMode loginMode; // 登录方式
@end

@implementation LoginViewController

@synthesize theIP;
@synthesize thePort;
@synthesize theGuid;
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
    theGuid.text = kAnyChatGuid;
    
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
    if (self.loginMode == AnyChatVCLoginModeSignLogin) {
        if (theGuid.text.length == 0) {
            [MBProgressHUD showError:@"应用ID不能为空"];
            return;
        }
    }
    
    if (self.loginMode == AnyChatVCLoginModeGeneralLogin && theGuid.text.length != 0) {
        [AnyChatPlatform SetSDKOptionString:BRAC_SO_CLOUD_APPGUID :theGuid.text];
    }
    
    [AnyChatPlatform Connect:theIP.text : [thePort.text intValue]];
    
    if (self.loginMode == AnyChatVCLoginModeSignLogin && theGuid.text.length != 0) {
        [self getSignSuccess:^(id json) {
            if ([[json objectForKey:@"errorcode"] intValue] ==0) {
                int timestamp = [[json objectForKey:@"timestamp"] intValue];
                NSString *signStr = [json objectForKey:@"sigStr"];
                [AnyChatPlatform LoginEx:theUserName.text :kUserID :nil :theGuid.text :timestamp :signStr :nil];
            }else {
                NSLog(@"Json Error,Error Num:%@",[json objectForKey:@"errorcode"]);
            }
        } failure:^(NSError *error) {
            NSLog(@"Request Error:%@",error);
        }];
    }else if(self.loginMode == AnyChatVCLoginModeGeneralLogin){
        [AnyChatPlatform Login:theUserName.text :nil];
    }
    
    
    [self.navigationController pushViewController:hallVC animated:YES];
    
}

- (void)getSignSuccess:(void (^)(id))success failure:(void (^)(NSError *))failure{
    
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    params[@"userid"] = [NSNumber numberWithInt:kUserID];
    params[@"strUserid"] = @"";
    params[@"appid"] = theGuid.text;
    
    [manager POST:kSignServerURL parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        if (success) success(responseObject);
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        if (failure) failure(error);
    }];
    
}

- (IBAction) hideKeyBoard:(id)sender
{
    [theIP resignFirstResponder];
    [thePort resignFirstResponder];
    [theGuid resignFirstResponder];
    [theUserName resignFirstResponder];
}


- (BOOL)prefersStatusBarHidden{
    return YES;
}

-(IBAction)onRadioBtn:(RadioButton*)sender
{
    if ([sender.titleLabel.text isEqualToString:@"签名登录"]) {
        self.loginMode = AnyChatVCLoginModeSignLogin;
    }else {
        self.loginMode = AnyChatVCLoginModeGeneralLogin;
    }
}


@end
