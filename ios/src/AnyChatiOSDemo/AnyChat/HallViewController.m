//
//  HallViewController.m
//  AnyChat
//
//  Created by bairuitech on 11-8-8.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "HallViewController.h"
#import "AnyChatAppDelegate.h"
#import "../../sdk/include/AnyChatPlatform.h"
#import "../../sdk/include/AnyChatDefine.h"

@implementation HallViewController
@synthesize theSelfUserId;


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

- (void) ShowSelfUserId:(int) userid
{
    theSelfUserId.text = [NSString stringWithFormat:@"Self userid:%d", userid];
}

- (IBAction) OnRoom1BtnClicked:(id)sender;
{
    [AnyChatPlatform EnterRoom:1 :@""];
}

- (IBAction) OnRoom2BtnClicked:(id)sender;
{
    [AnyChatPlatform EnterRoom:2 :@""];
}

- (IBAction) OnRoom3BtnClicked:(id)sender;
{
    [AnyChatPlatform EnterRoom:3 :@""];
}

- (IBAction) OnRoom4BtnClicked:(id)sender;
{
    [AnyChatPlatform EnterRoom:4 :@""];
}


- (IBAction) OnLogoutBtnClicked:(id)sender
{
    [AnyChatPlatform Logout];
    [[AnyChatAppDelegate GetApp].viewController showLoginView];
}

@end
