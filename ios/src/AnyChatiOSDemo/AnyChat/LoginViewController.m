//
//  LoginViewController.m
//  AnyChatiPhone
//
//  Created by bairuitech on 11-8-5.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "LoginViewController.h"
#import "../../sdk/include/AnyChatPlatform.h"
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
//    self.view.backgroundColor = [[UIColor alloc] initWithPatternImage:[UIImage imageNamed:@"login_bk.jpg"]];
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
    
    [AnyChatPlatform Connect:[AnyChatAppDelegate GetServerIP] : [AnyChatAppDelegate GetServerPort]];
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
