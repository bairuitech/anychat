//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ShowVC.h"

@interface ShowVC ()
@property (weak, nonatomic) IBOutlet UIButton *nextButton;
@property (weak, nonatomic) IBOutlet UIImageView *imageView;

@end

@implementation ShowVC

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
    self.title = @"录像回放";
    self.imageView.image = [UIImage imageWithContentsOfFile:[AnyChatVC sharedAnyChatVC].videoCoverImagePath];
    self.imageView.contentMode = UIViewContentModeScaleAspectFill;
    self.imageView.layer.masksToBounds = YES;
    self.nextButton.layer.borderWidth = 1;
    self.nextButton.layer.borderColor = [UIColor colorWithRed:0 green:139/255.0 blue:227/255.0 alpha:1].CGColor;
    self.nextButton.layer.masksToBounds = YES;
    [self p_configItem];
    
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
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

- (void)p_configItem {
    
    UIButton *btn= [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setTitle:@"重录" forState:UIControlStateNormal];
    [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    btn.titleLabel.font = [UIFont systemFontOfSize:15];
    [btn addTarget:self action:@selector(LeaveBtn_OnClick) forControlEvents:UIControlEventTouchUpInside];
    [btn sizeToFit];
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:btn];
    self.navigationItem.rightBarButtonItem = rightItem;
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

- (void)LeaveBtn_OnClick
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)returnBtn_OnClick
{
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

//#pragma mark - UITouch
//
//- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
//{
//    [self LeaveBtn_OnClick];
//}


-(BOOL)needLeftBackNavItem {
    
    return NO;
}

@end
