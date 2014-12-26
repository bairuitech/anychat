//
//  SettingsViewController.m
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ShowVC.h"

@interface ShowVC ()

@end

@implementation ShowVC

@synthesize theShowVCNItem;
@synthesize theVideoFilePath;

#pragma mark - Life cycle

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        self.theVideoFilePath = [AnyChatVC sharedAnyChatVC].theVideoPath;
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    if ([AnyChatVC sharedAnyChatVC].theNextVCBool == YES)
    {
        [self nextVC];
        [AnyChatVC sharedAnyChatVC].theNextVCBool = NO;
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - QLPreviewControllerDataSource

- (NSInteger)numberOfPreviewItemsInPreviewController:(QLPreviewController *)previewController
{
    return 1;
}

- (id)previewController:(QLPreviewController *)previewController previewItemAtIndex:(NSInteger)idx
{
    NSURL *fileURL = [NSURL fileURLWithPath:self.theVideoFilePath];
    return fileURL;
}


#pragma mark -
#pragma mark - Instance Method

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction)LeaveBtn_OnClick
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)returnBtn_OnClick
{
    RecordLocalVC *recordLocalVC = [RecordLocalVC new];
    [recordLocalVC StartVideoChat:123456];  //DIYServerID
    
    [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:2]
                                          animated:YES];
}

- (IBAction)playBackVideo
{
    //QLPreviewController init
    QLPreviewController *previewController = [[QLPreviewController alloc] init];
    previewController.dataSource = self;
    previewController.delegate = self;
    // start previewing the document at the current section index
    previewController.currentPreviewItemIndex = 0;
    [self presentViewController:previewController animated:NO completion:nil];
}

- (IBAction)nextVC
{
    RecordLocalVC *recordLocalVC = [RecordLocalVC new];
    [recordLocalVC FinishVideoChat];
    
    TransFileVC *transFileVC = [TransFileVC new];
    [self.navigationController pushViewController:transFileVC animated:YES];
}

#pragma mark - UITouch

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self LeaveBtn_OnClick];
}


#pragma mark - UI Controls

- (BOOL)prefersStatusBarHidden
{
    return YES;
}



@end
