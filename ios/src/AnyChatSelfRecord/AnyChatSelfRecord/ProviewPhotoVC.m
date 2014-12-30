//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ProviewPhotoVC.h"

@interface ProviewPhotoVC ()

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
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
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
    [self dismissViewControllerAnimated:NO completion:nil];
}

- (void)showSnapShotPhoto:(NSString *)theFilePath transform:(NSString *)transformParam
{
    UIImage *s_Image = [UIImage imageWithContentsOfFile:theFilePath];
    
    UIImageView *theSnapShotImageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 44,kSelfView_Width,kSelfView_Height-44-38)];
    theSnapShotImageView.image = s_Image;
    theSnapShotImageView.contentMode = UIViewContentModeScaleAspectFit;
    
    if ([transformParam isEqualToString:@"Portrait"])
    {
        theSnapShotImageView.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    }
    
    [self.view addSubview:theSnapShotImageView];
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
