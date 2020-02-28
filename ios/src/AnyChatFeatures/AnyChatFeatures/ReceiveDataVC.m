//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ReceiveDataVC.h"
#import "AnyChatVC.h"

@interface ReceiveDataVC ()

{
    NSTimer *theTimers;
}

@property (strong, nonatomic) IBOutlet UIView               *theSendView;
@property (strong, nonatomic) IBOutlet UIView               *theServerView;
@property (strong, nonatomic) IBOutlet UIView               *theRecvView;

@property (strong, nonatomic) IBOutlet UILabel          *theSendViewSendLable;
@property (strong, nonatomic) IBOutlet UILabel          *theServerViewRecvLable;
@property (strong, nonatomic) IBOutlet UILabel          *theRecvViewRecvLable;
@property (strong, nonatomic) IBOutlet UILabel          *theRecvViewLossLable;

@property (strong, nonatomic) IBOutlet UILabel          *theSendViewIPLable;
@property (strong, nonatomic) IBOutlet UILabel          *theRecvViewIPLable;
@property (strong, nonatomic) IBOutlet UILabel          *theServerViewIPLable;

@property   int   theSendData;
@property   int   theRecvData;
@property   int   theServerGetData;
@end

@implementation ReceiveDataVC

#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setUI];
    
    //send ///< UDP数据包跟踪控制（参数为int型，1 启动， 0 停止）
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_UDPTRACE_START :1];
    self.title = @"网络质量评估";
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self TheTimersActionStart];
    
    //IP
    self.theSendViewIPLable.text = [AnyChatPlatform QueryUserStateString:[AnyChatPlatform GetSDKOptionInt:BRAC_SO_UDPTRACE_SENDUSERID] :BRAC_USERSTATE_INTERNETIP];
    self.theRecvViewIPLable.text = [AnyChatPlatform QueryUserStateString:-1 :BRAC_USERSTATE_INTERNETIP];
    
    self.theServerViewIPLable.text = [AnyChatVC sharedAnyChatVC].theMyServerAddr;

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


- (void)navLeftClick
{
    //stop
    [self TheTimersActionStop];

    [AnyChatPlatform LeaveRoom:-1];
    [self.navigationController popViewControllerAnimated:NO];
}


#pragma mark ----- 业务核心代码 ----

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
        if ([theTimers isValid]) //NSTimer is runing
        {
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

    if ([self.theSendViewIPLable.text isEqualToString:@""])
    {
        self.theSendViewIPLable.text = [AnyChatPlatform QueryUserStateString:[AnyChatPlatform GetSDKOptionInt:167] :BRAC_USERSTATE_INTERNETIP];
    }
    
}

- (NSString *)DownloadFrameLossRate:(int)send :(int)serverGet :(int)recv
{
    
    float theLossRate = 0.0f;
    if (serverGet > 0) {
        theLossRate = ((send-recv)/(float)serverGet)*100;
    }
    if (theLossRate<0.0f)
    {
        theLossRate = 0.00;
    }
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


#pragma mark - Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark - UI

- (void)setUI
{

    
    
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
