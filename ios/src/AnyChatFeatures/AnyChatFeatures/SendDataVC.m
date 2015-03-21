//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "SendDataVC.h"

@interface SendDataVC ()

@end

@implementation SendDataVC


@synthesize theSendView;
@synthesize theServerView;
@synthesize theControlView;

@synthesize theSendViewSendLable;
@synthesize theSendViewRecvLable;
@synthesize theSendViewLossLable;
@synthesize theServerViewRecvLable;
@synthesize theSendViewIPLable;

@synthesize theSendBitLable;

@synthesize theStartBtn;
@synthesize theEndBtn;

@synthesize theSendData;
@synthesize theRecvData;
@synthesize theServerGetData;


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
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    onClickTimes = 0;
    self.theSendViewIPLable.text = [AnyChatPlatform QueryUserStateString:-1 :BRAC_USERSTATE_INTERNETIP];
}

-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:YES];
    
    //stop
    [AnyChatPlatform SetSDKOptionInt:163 :0];
    
    //close NSTimer
    [theNSTimer invalidate];
    theNSTimer = nil;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - IBAction Method

- (IBAction)LeaveRoomBtn_OnClick
{
    [AnyChatPlatform LeaveRoom:-1];
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)theStartBtn_Click:(id)sender
{
    if (onClickTimes < 1)
    {
        onClickTimes = 2;
    }
    else
    {
        [self TheTimersActionStop];
        onClickTimes = 0;
    }
    
    [self TheTimersActionStart];
}

- (IBAction)theEndBtn_Click:(id)sender
{
    [self TheTimersActionStop];
}


#pragma mark - Instance Method

- (void)TheTimersActionStart
{
    //set
    [AnyChatPlatform SetSDKOptionInt:161 :1000];
    [AnyChatPlatform SetSDKOptionInt:162 :([self.theSendBitLable.text intValue])*1000];
    //send
    [AnyChatPlatform SetSDKOptionInt:163 :1];
    
    if(!theNSTimer)
    {
        theNSTimer =  [NSTimer scheduledTimerWithTimeInterval:1.0
                                                      target:self
                                                    selector:@selector(ReflashDataDisplay:)
                                                    userInfo:nil
                                                     repeats:YES];
        [theNSTimer fire];
//        NSLog(@"\n\n 开始theTimers:%@ \n\n",theNSTimer);
    }
    
}

- (void)TheTimersActionStop
{
    //stop
    [AnyChatPlatform SetSDKOptionInt:163 :0];
    
    //close NSTimer
    if (theNSTimer)
    {
        //如果定时器在运行
        if ([theNSTimer isValid])
        {
//            NSLog(@"\n\n 取消定时器theTimers:%@ \n\n",theNSTimer);

            [theNSTimer invalidate];
            theNSTimer = nil;
        }
    }
    
    self.theSendViewSendLable.text = @"0";
    self.theSendViewRecvLable.text = @"0";
    self.theSendViewLossLable.text = @"0.00%";
    self.theServerViewRecvLable.text = @"0";
    
}

- (void)ReflashDataDisplay:(NSTimer *)timer
{
    self.theSendData = [AnyChatPlatform GetSDKOptionInt:166];
    self.theRecvData = [AnyChatPlatform GetSDKOptionInt:164];
    self.theServerGetData = [AnyChatPlatform GetSDKOptionInt:165];
    
    self.theSendViewSendLable.text = [[NSString alloc] initWithFormat:@"%i",self.theSendData];
    self.theSendViewRecvLable.text = [[NSString alloc] initWithFormat:@"%i",self.theRecvData];
    self.theServerViewRecvLable.text = [[NSString alloc] initWithFormat:@"%i",self.theServerGetData];
    self.theSendViewLossLable.text = [self UploadFrameLossRate:self.theSendData :self.theServerGetData];

}

- (NSString *)UploadFrameLossRate:(int)send :(int)serverGet
{
    float theLossRate = ((send-serverGet)/(float)send)*100;
//    NSLog(@"\n\n send :%i \n server:%i \n 上行丢包率： %f \n\n",send,serverGet,theLossRate);
    
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
    [self setUIwithLayer:self.theControlView.layer:[UIColor colorWithWhite:0.800 alpha:1.000]];
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
