//
//  LoginViewController.m
//  AnyChatiPhone
//
//  Created by bairuitech on 11-8-5.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "LoginViewController.h"
#import "AnyChatPlatform.h"
#import "AnyChatAppDelegate.h"

@implementation LoginViewController

@synthesize theUserName;
@synthesize thePassword;
@synthesize theLoginBtn;
@synthesize theSettingsBtn;
@synthesize theVersion;

@synthesize theHideKeyboardBtn;



- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}


- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [theHideKeyboardBtn setTitle:@"" forState:UIControlStateNormal];
    [theHideKeyboardBtn setTitle:@"" forState:UIControlStateSelected];
    
    // get anychat version string
    [theVersion setText:[AnyChatPlatform GetSDKVersion]];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


-(IBAction)OnLoginBtnClicked:(id)sender
{
    if([theUserName.text length] == 0)
        theUserName.text=@"iPhone";
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    [AnyChatPlatform Connect:[AnyChatAppDelegate GetServerIP] : [AnyChatAppDelegate GetServerPort]];
    
    /*
     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
     */
    [AnyChatPlatform Login:theUserName.text : thePassword.text];
}

-(IBAction)OnNetConfigBtnClicked:(id)sender
{
    [[AnyChatAppDelegate GetApp].viewController showNetConfigView];
}

- (IBAction) hideKeyBoard:(id)sender
{
    [theUserName resignFirstResponder];
    [thePassword resignFirstResponder];
}

@end
