//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "TransFileVC.h"
#import "MBProgressHUD.h"
@interface TransFileVC ()
@property (weak, nonatomic) IBOutlet UIButton *uploadButton;

@end

@implementation TransFileVC

@synthesize theTransFileBtnTimes;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
    }
    return self;
}


#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.theTransFileBtnTimes = 0;
    
    self.uploadButton.layer.borderWidth = 1;
    self.uploadButton.layer.borderColor = [UIColor colorWithRed:0 green:139/255.0 blue:227/255.0 alpha:1].CGColor;
    self.uploadButton.layer.masksToBounds = YES;
    
    self.thePhotoProgressView.layer.cornerRadius = 5;
    self.thePhotoProgressView.layer.masksToBounds = YES;
    
    self.theVideoProgressView.layer.cornerRadius = 5;
    self.theVideoProgressView.layer.masksToBounds = YES;
    
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
}

-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
    
    self.theTransFileBtnTimes = 0;
    
    //close NSTimer
    [theNSTimer invalidate];
    theNSTimer = nil;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(BOOL)navBarTranslucent {
    
    return YES;
}

-(BOOL)needLeftBackNavItem {
    
    return NO;
}

#pragma mark - AlertView delegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 0)
    {
        EndVC *endVC = [EndVC new];
        [self.navigationController pushViewController:endVC animated:YES];
    }
}


#pragma mark - Instance Method

- (IBAction)returnBtn_OnClick
{
    RecordLocalVC *recordLocalVC = [RecordLocalVC new];
    [recordLocalVC FinishVideoChat];
    
    [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:2]
                                          animated:YES];
}

- (IBAction)theTransFileBtn_OnClick;
{
    if (self.theTransFileBtnTimes < 1)
    {
        
        NSString* photoFilePath = [AnyChatVC sharedAnyChatVC].thePhotoPath;
        NSString* videoFilePath = [AnyChatVC sharedAnyChatVC].theVideoPath;
        
        if (photoFilePath != nil && videoFilePath != nil)
        {
            // 传送文本消息
            int photoTaskID = [AnyChatPlatform TransFile:0 :photoFilePath :0 :0 :0];
            int videoTaskID = [AnyChatPlatform TransFile:0 :videoFilePath :0 :0 :0];
            
            NSMutableDictionary *theMDict = [NSMutableDictionary dictionaryWithCapacity:3];
            [theMDict setValue:[[NSNumber alloc] initWithInt:photoTaskID] forKey:@"photoTaskID"];
            [theMDict setValue:[[NSNumber alloc] initWithInt:videoTaskID] forKey:@"videoTaskID"];
            
            theNSTimer =  [NSTimer scheduledTimerWithTimeInterval:0.5
                                                           target:self
                                                         selector:@selector(progressLoading:)
                                                         userInfo:theMDict
                                                          repeats:YES];
            
            self.theTransFileBtnTimes = 2;
        }
        else
        {

            [self showAutoDismissAlertView:@"上传失败，信息内容完整。" :@"Warning"];
            self.theTransFileBtnTimes = 0;
        }
    }
    
}

//Decimal digits
-(NSString *)newFloat:(float)value withNumber:(int)numberOfPlace
{
    NSString *formatStr = @"%0.";
    formatStr = [formatStr stringByAppendingFormat:@"%df", numberOfPlace];
    formatStr = [NSString stringWithFormat:formatStr, value];
    
    return formatStr;
}


#pragma mark - Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark - TransFile Loading Animation

- (void)progressLoading:(NSTimer *)timer
{
    int photoTaskID = [[[timer userInfo] objectForKey:@"photoTaskID"] intValue];
    int videoTaskID = [[[timer userInfo] objectForKey:@"videoTaskID"] intValue];
    
    float photoTaskIDProgress = 0.0f;
    float videoTaskIDProgress = 0.0f;
    
    photoTaskIDProgress = [AnyChatPlatform QueryTransTaskInfoInt:[AnyChatVC sharedAnyChatVC].theMyUserID
                                                                :photoTaskID
                                                                :BRAC_TRANSTASK_PROGRESS];
    
    videoTaskIDProgress = [AnyChatPlatform QueryTransTaskInfoInt:[AnyChatVC sharedAnyChatVC].theMyUserID
                                                                :videoTaskID
                                                                :BRAC_TRANSTASK_PROGRESS];
    
    
    int thephotoProgress = [[self newFloat:photoTaskIDProgress withNumber:0] intValue];
    int thevideoProgress = [[self newFloat:videoTaskIDProgress withNumber:0] intValue];

    
    //Photo Progress
    self.thePhotoProgressView.progress = thephotoProgress / 100.0;
    NSString *thephotoProgressStr = [[NSString alloc] initWithFormat:@"%i",thephotoProgress];
    self.thePhotoProgressLab.text = [thephotoProgressStr stringByAppendingString:@"%"];
    
    //Video Progress
    self.theVideoProgressView.progress = thevideoProgress / 100.0;
    NSString *thevideoProgressStr = [[NSString alloc] initWithFormat:@"%i",thevideoProgress];
    self.theVideoProgressLab.text = [thevideoProgressStr stringByAppendingString:@"%"];
    
    if (thevideoProgress == 100 && thephotoProgress == 100)
    {
        //close NSTimer
        [theNSTimer invalidate];
        theNSTimer = nil;
        EndVC *endVC = [EndVC new];
        [self.navigationController pushViewController:endVC animated:YES];
        
    }
}


@end
