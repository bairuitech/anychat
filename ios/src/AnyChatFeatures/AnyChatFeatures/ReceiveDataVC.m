//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ReceiveDataVC.h"

@interface ReceiveDataVC ()

@end

@implementation ReceiveDataVC

@synthesize theSendView;
@synthesize theServerView;
@synthesize theRecvView;

@synthesize theSendViewSendLable;
@synthesize theServerViewRecvLable;
@synthesize theRecvViewRecvLable;
@synthesize theRecvViewLossLable;

@synthesize theSendData;
@synthesize theRecvData;
@synthesize theServerGetData;

@synthesize theSendViewIPLable;
@synthesize theRecvViewIPLable;


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
    [self setUI];
    
    //send
    [AnyChatPlatform SetSDKOptionInt:163 :1];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    self.theSendViewIPLable.text = [AnyChatPlatform QueryUserStateString:[AnyChatPlatform GetSDKOptionInt:167] :BRAC_USERSTATE_INTERNETIP];
    self.theRecvViewIPLable.text = [AnyChatPlatform QueryUserStateString:-1 :BRAC_USERSTATE_INTERNETIP];
    
    [self TheTimersActionStart];
}

-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
    
    //close NSTimer
    [theTimers invalidate];
    theTimers=nil;
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - IBAction Method

- (IBAction)LeaveRoomBtn_OnClick
{
    //stop
    [self TheTimersActionStop];

    [AnyChatPlatform LeaveRoom:-1];
    [self.navigationController popViewControllerAnimated:YES];
}


#pragma mark - Instance Method

- (void)TheTimersActionStart
{
    //set
    [AnyChatPlatform SetSDKOptionInt:161 :1000];
    [AnyChatPlatform SetSDKOptionInt:162 :(100)*1000];
    //send
    [AnyChatPlatform SetSDKOptionInt:163 :1];
    
    if(!theTimers)
    {
        theTimers =  [NSTimer scheduledTimerWithTimeInterval:1.0
                                                       target:self
                                                     selector:@selector(ReflashDataDisplay:)
                                                     userInfo:nil
                                                      repeats:YES];
        [theTimers fire];
    }
    
}

- (void)TheTimersActionStop
{
    //stop
    [AnyChatPlatform SetSDKOptionInt:163 :0];
    
    //close NSTimer
    if (theTimers)
    {
//        NSLog(@"调用 theTimers为真！！");
        
        //如果定时器在运行
        if ([theTimers isValid])
        {
//            NSLog(@"单击停止按钮，取消定时器！！");
            
            [theTimers invalidate];
            theTimers = nil;
        }
    }

    
}

- (void)ReflashDataDisplay:(NSTimer *)timer
{
    self.theSendData = [AnyChatPlatform GetSDKOptionInt:166];
    self.theRecvData = [AnyChatPlatform GetSDKOptionInt:164];
    self.theServerGetData = [AnyChatPlatform GetSDKOptionInt:165];
    
    self.theSendViewSendLable.text = [[NSString alloc] initWithFormat:@"%i",self.theSendData];
    self.theRecvViewRecvLable.text = [[NSString alloc] initWithFormat:@"%i",self.theRecvData];
    self.theServerViewRecvLable.text = [[NSString alloc] initWithFormat:@"%i",self.theServerGetData];
    self.theRecvViewLossLable.text = [self DownloadFrameLossRate:self.theSendData :self.theServerGetData :self.theRecvData];
    
}

- (NSString *)DownloadFrameLossRate:(int)send :(int)serverGet :(int)recv
{
    float theLossRate = ((send-recv)/(float)serverGet)*100;
//        NSLog(@"\n\n send :%i \n server:%i \n 上行丢包率： %f \n\n",send,serverGet,theLossRate);
    
    return [[self newFloat:theLossRate withNumber:2] stringByAppendingString:@"%"];
}

//Decimal digits
-(NSString *)newFloat:(float)value withNumber:(int)numberOfPlace
{
    NSString *formatStr = @"%0.";
    formatStr = [formatStr stringByAppendingFormat:@"%df", numberOfPlace];
    formatStr = [NSString stringWithFormat:formatStr, value];
    
    return formatStr;
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}


#pragma mark - UI

- (void)setUI
{
    if ([[UIDevice currentDevice].systemVersion floatValue] < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }
    [self prefersStatusBarHidden];
    
    
    [self setUIwithLayer:self.theSendView.layer:[UIColor colorWithWhite:0.800 alpha:1.000]];
    [self setUIwithLayer:self.theServerView.layer:[UIColor colorWithWhite:0.800 alpha:1.000]];
    [self setUIwithLayer:self.theRecvView.layer:[UIColor colorWithWhite:0.800 alpha:1.000]];
}


- (void)setUIwithLayer:(CALayer *)theLayer :(UIColor *)theBorderColor
{
    //Local View line
    theLayer.borderColor = [theBorderColor CGColor];
    theLayer.borderWidth = 1.0f;
    //Rounded corners
    theLayer.cornerRadius = 3;
    theLayer.masksToBounds = YES;
    theLayer.backgroundColor = [[UIColor clearColor] CGColor];
}

@end
