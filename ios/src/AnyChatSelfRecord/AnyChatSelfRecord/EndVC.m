//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "EndVC.h"

@interface EndVC ()

@property (weak, nonatomic) IBOutlet UIButton *nextButton;
@end

@implementation EndVC

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}


#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.nextButton.layer.borderWidth = 1;
    self.nextButton.layer.borderColor = [UIColor colorWithRed:0 green:139/255.0 blue:227/255.0 alpha:1].CGColor;
    self.nextButton.layer.masksToBounds = YES;
    
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - Instance Method

- (IBAction)returnBtn_OnClick
{
    RecordLocalVC *recordVC = [RecordLocalVC new];
    [recordVC FinishVideoChat];
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    [AnyChatVC sharedAnyChatVC].theStateInfo.text = [NSString stringWithFormat:@"• Logout."];
    [AnyChatVC sharedAnyChatVC].theLoginState = NO;
    [AnyChatVC sharedAnyChatVC].theLoginBtn.selected = NO;
    
    [self.navigationController popToRootViewControllerAnimated:YES];
    
    
}

-(BOOL)needLeftBackNavItem {
    
    return NO;
}

-(BOOL)navBarTranslucent {
    
    return YES;
}
@end
