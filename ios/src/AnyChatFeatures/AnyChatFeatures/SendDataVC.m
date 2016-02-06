//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "SendDataVC.h"
#import "AnyChatVC.h"

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
@synthesize theServerViewIPLable;

@synthesize theSendBitLable;

@synthesize theStartBtn;

@synthesize theSendData;
@synthesize theRecvData;
@synthesize theServerGetData;

@synthesize theStartBtnOnClickState;


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
    
    theStartBtnOnClickState = NO;
    
    self.theSendViewIPLable.text = [AnyChatPlatform QueryUserStateString:-1 :BRAC_USERSTATE_INTERNETIP];
    
    self.theServerViewIPLable.text = kAnyChatIP;
    
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
    [self.navigationController popViewControllerAnimated:NO];
}

- (IBAction)theStartBtn_Click:(id)sender
{
    if (theStartBtnOnClickState == NO)
    {
        [self.theStartBtn setTitle:@"停止测试" forState:UIControlStateNormal];
        self.theStartBtn.backgroundColor = [UIColor colorWithWhite:0.902 alpha:1.000];
        [self TheTimersActionStart];
    }
    else
    {
        [self.theStartBtn setTitle:@"开始测试" forState:UIControlStateNormal];
        self.theStartBtn.backgroundColor = [UIColor colorWithRed:0.800 green:0.941 blue:0.600 alpha:1.000];
        [self TheTimersActionStop];
    }
}


#pragma mark - Instance Method

- (void)TheTimersActionStart
{
    theStartBtnOnClickState = YES;
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
    }

}

- (void)TheTimersActionStop
{
    theStartBtnOnClickState = NO;
    //stop
    [AnyChatPlatform SetSDKOptionInt:163 :0];
    
    //close NSTimer
    if (theNSTimer)
    {
        if ([theNSTimer isValid])
        {
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
    if (theLossRate<0.0f)
    {
        theLossRate = 0.00;
    }
//    NSLog(@"\n\n send :%i \n server:%i \n UploadFrameLossRate： %f \n\n",send,serverGet,theLossRate);
    
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


#pragma mark - Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}

- (IBAction)hideKeyBoard
{
    [self.theSendBitLable resignFirstResponder];
}


#pragma mark - UI

- (void)setUI
{
    if ([[UIDevice currentDevice].systemVersion floatValue] < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }
    else
    {
        self.theStartBtn.backgroundColor = [UIColor colorWithRed:0.567 green:0.918 blue:0.535 alpha:1.000]
        ;
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
