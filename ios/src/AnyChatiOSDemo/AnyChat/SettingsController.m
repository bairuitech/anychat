//
//  SettingsController.m
//  AnyChat
//
//  Created by bairuitech on 12-4-26.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#import "SettingsController.h"
#import "AnyChatAppDelegate.h"


@implementation SettingsController

@synthesize theServerIP;
@synthesize theServerPort;

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
    
    theServerIP.text = [AnyChatAppDelegate GetServerIP];
    theServerPort.text = [NSString stringWithFormat:@"%d", [AnyChatAppDelegate GetServerPort]];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


//- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
//{
//    // Return YES for supported orientations
//    return (interfaceOrientation == UIInterfaceOrientationPortrait);
//}


-(IBAction)OnSaveSettingsBtnClick:(id)sender
{
    // save settings to file
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    [[NSArray arrayWithObjects:theServerIP.text,theServerPort.text, nil] writeToFile:filePath atomically:YES];
    
    [[AnyChatAppDelegate GetApp].viewController showLoginView];
}


@end
