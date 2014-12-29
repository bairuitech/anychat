//
//  TransFileVC.m
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "TransFileVC.h"

@interface TransFileVC ()

@end

@implementation TransFileVC

@synthesize theTransFileBtnTimes;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.theTransFileBtnTimes = 0;
    }
    return self;
}


#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUI];
    
//    //开启定时器
//    [theNSTimer setFireDate:[NSDate distantPast]];
}

-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
    
    self.theTransFileBtnTimes = 0;
    
    //关闭定时器
    [theNSTimer setFireDate:[NSDate distantFuture]];
    [theNSTimer invalidate];
    theNSTimer = nil;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
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
    [recordLocalVC StartVideoChat:123456];  //DIYServerID
    
    [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:2]
                                          animated:YES];
}

- (IBAction)theTransFileBtn_OnClick;
{
    if (self.theTransFileBtnTimes < 1)
    {
        int targetUserID = 0;
        NSString* photoFilePath = [AnyChatVC sharedAnyChatVC].thePhotoPath;
        NSString* videoFilePath = [AnyChatVC sharedAnyChatVC].theVideoPath;
        
        if (photoFilePath != nil && videoFilePath != nil)
        {
            [self sendFiles:photoFilePath :targetUserID :@"Photo"];
            [self sendFiles:videoFilePath :targetUserID :@"Video"];
            self.theTransFileBtnTimes = 2;
        }
        else
        {
            [[AnyChatVC sharedAnyChatVC] showInfoAlertView:@"上传失败，信息内容完整。"
                                                          :@"Warning"];
        }
    }
    
}

- (void)sendFiles:(NSString *)contentPathStr :(int)targetUserID :(NSString *)fileType
{
    // 传送文本消息
    int taskID = [AnyChatPlatform TransFile:targetUserID :contentPathStr :0 :0 :0];
    if (taskID > 0)
    {
        if ([fileType isEqualToString:@"Photo"])
        {
            [self showTransFileLoadingAnimated:taskID :@"Photo"];
        }
        if ([fileType isEqualToString:@"Video"])
        {
            [self showTransFileLoadingAnimated:taskID :@"Video"];
        }
    }
    else
    {
        [[AnyChatVC sharedAnyChatVC] NetworkAnomaliesAlert];
    }
    
    
    if (m_videoTransStatus)
    {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"上传成功！"
                                                            message:@"Uploading a success."
                                                           delegate:self
                                                  cancelButtonTitle:nil
                                                  otherButtonTitles:@"确定",nil];
        [alertView show];
        
        [theNSTimer invalidate];
        theNSTimer = nil;
    }
}

//Decimal digits
-(NSString *)newFloat:(float)value withNumber:(int)numberOfPlace
{
    NSString *formatStr = @"%0.";
    formatStr = [formatStr stringByAppendingFormat:@"%df", numberOfPlace];
    formatStr = [NSString stringWithFormat:formatStr, value];
//    printf("formatStr %s\n", [formatStr UTF8String]);
    return formatStr;
}

#pragma mark - Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark - TransFile Loading Animation

- (void)showTransFileLoadingAnimated:(int)transFileTaskID :(NSString *)fileType
{
    
    NSMutableDictionary *theMDict = [NSMutableDictionary dictionaryWithCapacity:3];
    [theMDict setValue:[[NSNumber alloc] initWithInt:transFileTaskID] forKey:@"transFileTaskID"];
    [theMDict setValue:fileType forKey:@"fileType"];
 
    //创建定时器
    theNSTimer =  [NSTimer scheduledTimerWithTimeInterval:0.6
                                                   target:self
                                                 selector:@selector(progressLoading:)
                                                 userInfo:theMDict
                                                  repeats:YES];
    
    NSRunLoop *runloop = [NSRunLoop currentRunLoop];
    [runloop addTimer:theNSTimer forMode:NSDefaultRunLoopMode];
//    [theNSTimer fire];
    
//    //开启定时器
//    [theNSTimer setFireDate:[NSDate distantPast]];
    
}

- (void)progressLoading:(NSTimer *)timer
{
    NSString *thefileType = [[timer userInfo] objectForKey:@"fileType"];
    int transFileTaskID = [[[timer userInfo] objectForKey:@"transFileTaskID"] intValue];
 
//    int theTransTaskStatus = 0;
    float theTransFileProgress = 0.0f;
    theTransFileProgress = [AnyChatPlatform QueryTransTaskInfoInt:[AnyChatVC sharedAnyChatVC].theMyUserID
                                                                 :transFileTaskID
                                                                 :BRAC_TRANSTASK_PROGRESS];
    
    int theProgress = [[self newFloat:theTransFileProgress withNumber:0] intValue];
    
    if ([thefileType isEqualToString:@"Photo"])
    {
        //LoadingView
        self.thePhotoProgressView.progress = theProgress;
        NSString *theProgressStr = [[NSString alloc] initWithFormat:@"%i",theProgress];
        self.thePhotoProgressLab.text = [theProgressStr stringByAppendingString:@"%"];
        
        NSLog(@"\n\n %@ 进度 : %i",thefileType,theProgress);
    }
    
    if ([thefileType isEqualToString:@"Video"])
    {
        //LoadingView
        self.theVideoProgressView.progress = theProgress;
        NSString *theProgressStr = [[NSString alloc] initWithFormat:@"%i",theProgress];
        self.theVideoProgressLab.text = [theProgressStr stringByAppendingString:@"%"];
        
        NSLog(@"\n\n %@进度 : %i",thefileType,theProgress);
    }
    
    if (theProgress == 100 )
    {
//        if ([thefileType isEqualToString:@"Photo"])
//        {
//            m_photoTransStatus = YES;
//        }
        
        if ([thefileType isEqualToString:@"Video"])
        {
            m_videoTransStatus = YES;
        }
        
        if (m_videoTransStatus)
        {
            //关闭定时器
//            [theNSTimer setFireDate:[NSDate distantFuture]];
            [theNSTimer invalidate];
            theNSTimer = nil;
            
//            UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"上传成功！"
//                                                                message:@"Uploading a success."
//                                                               delegate:self
//                                                      cancelButtonTitle:nil
//                                                      otherButtonTitles:@"确定",nil];
//            [alertView show];

        }

    }
}


#pragma mark - UI Controls

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)setUI
{
    [self.navigationController setNavigationBarHidden:YES];
    
    if ([[UIDevice currentDevice].systemVersion floatValue] < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }
    
    [self prefersStatusBarHidden];
    
}


@end
