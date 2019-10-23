//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ProviewPhotoVC.h"

@interface ProviewPhotoVC ()
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (weak, nonatomic) IBOutlet UIButton *nextButton;

@end

@implementation ProviewPhotoVC

#pragma mark - Life cycle

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
    [self p_configItem];
    self.title = @"照片预览";
    
    self.nextButton.layer.borderWidth = 1;
    self.nextButton.layer.borderColor = [UIColor colorWithRed:0 green:139/255.0 blue:227/255.0 alpha:1].CGColor;
    self.nextButton.layer.masksToBounds = YES;
    
    self.imageView.image = [UIImage imageWithContentsOfFile:self.filePath];

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

-(BOOL)needLeftBackNavItem{
    
    return NO;
}

- (void)p_configItem {
    
    UIButton *btn= [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setTitle:@"重拍" forState:UIControlStateNormal];
    [btn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    btn.titleLabel.font = [UIFont systemFontOfSize:15];
    [btn addTarget:self action:@selector(returnBtn_OnClick) forControlEvents:UIControlEventTouchUpInside];
    [btn sizeToFit];
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:btn];
    self.navigationItem.rightBarButtonItem = rightItem;
}

#pragma mark -
#pragma mark - Instance Method

- (IBAction)returnBtn_OnClick
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)nextBtn_OnClick
{
    [AnyChatVC sharedAnyChatVC].theNextVCBool = YES;
//    [self dismissViewControllerAnimated:NO completion:nil];
    
    [self dismissViewControllerAnimated:NO completion:^{
        if ([self.delegate respondsToSelector:@selector(dismissVC)]) {
            [self.delegate dismissVC];
        }
    }];
}



#pragma mark - Orientation Rotation

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark - UI Controls

- (BOOL)prefersStatusBarHidden
{
    return YES;
}



@end
