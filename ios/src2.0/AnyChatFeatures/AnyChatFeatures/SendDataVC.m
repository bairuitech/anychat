//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "SendDataVC.h"
#import "AnyChatVC.h"

@interface SendDataVC ()
{
    NSTimer *theNSTimer;
}

@property (strong, nonatomic) IBOutlet UIView           *theSendView;
@property (strong, nonatomic) IBOutlet UIView           *theServerView;
@property (strong, nonatomic) IBOutlet UIView           *theControlView;

@property (strong, nonatomic) IBOutlet UILabel          *theSendViewSendLable;
@property (strong, nonatomic) IBOutlet UILabel          *theSendViewRecvLable;
@property (strong, nonatomic) IBOutlet UILabel          *theSendViewLossLable;
@property (strong, nonatomic) IBOutlet UILabel          *theServerViewRecvLable;

@property (strong, nonatomic) IBOutlet UILabel          *theSendViewIPLable;
@property (strong, nonatomic) IBOutlet UILabel          *theServerViewIPLable;

@property (strong, nonatomic) IBOutlet UITextField      *theSendBitLable;

@property (strong, nonatomic) IBOutlet UIButton         *theStartBtn;

@property   BOOL  theStartBtnOnClickState;

@property   int   theSendData;
@property   int   theRecvData;
@property   int   theServerGetData;


@end

@implementation SendDataVC



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
    self.title = @"网络质量评估";
    self.theStartBtn.backgroundColor = [UIColor colorWithRed:0.800 green:0.941 blue:0.600 alpha:1.000];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    self.theStartBtnOnClickState = NO;
    //查询自己互联网ip
    self.theSendViewIPLable.text = [AnyChatPlatform QueryUserStateString:-1 :BRAC_USERSTATE_INTERNETIP];
    
    self.theServerViewIPLable.text = [AnyChatVC sharedAnyChatVC].theMyServerAddr;
    
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
    if (self.theStartBtnOnClickState == NO)
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


#pragma mark ------ 业务核心代码 ------

- (void)TheTimersActionStart
{
    self.theStartBtnOnClickState = YES;
    //set
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_UDPTRACE_PACKSIZE :1000];
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_UDPTRACE_BITRATE :([self.theSendBitLable.text intValue])*1000];
    //send
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_UDPTRACE_START :1];
    
    if(!theNSTimer)
    {
        theNSTimer =  [NSTimer scheduledTimerWithTimeInterval:1.0
                                                      target:self
                                                    selector:@selector(ReflashDataDisplay:)
                                                    userInfo:nil
                                                     repeats:YES];
        [theNSTimer fire];
    }
    self.theSendViewSendLable.text = @"0";
    self.theSendViewRecvLable.text = @"0";
    self.theSendViewLossLable.text = @"0.00%";
    self.theServerViewRecvLable.text = @"0";

}

- (void)TheTimersActionStop
{
    self.theStartBtnOnClickState = NO;
    //stop
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_UDPTRACE_START :0];
    
    //close NSTimer
    if (theNSTimer)
    {
        if ([theNSTimer isValid])
        {
            [theNSTimer invalidate];
            theNSTimer = nil;
        }
    }
    

}

- (void)ReflashDataDisplay:(NSTimer *)timer
{
    self.theSendData = [AnyChatPlatform GetSDKOptionInt:BRAC_SO_UDPTRACE_SOURCESENDNUM];
    self.theRecvData = [AnyChatPlatform GetSDKOptionInt:BRAC_SO_UDPTRACE_LOCALRECVNUM];
    self.theServerGetData = [AnyChatPlatform GetSDKOptionInt:BRAC_SO_UDPTRACE_SERVERRECVNUM];
    
    self.theSendViewSendLable.text = [[NSString alloc] initWithFormat:@"%i",self.theSendData];
    self.theSendViewRecvLable.text = [[NSString alloc] initWithFormat:@"%i",self.theRecvData];
    self.theServerViewRecvLable.text = [[NSString alloc] initWithFormat:@"%i",self.theServerGetData];
    self.theSendViewLossLable.text = [self UploadFrameLossRate:self.theSendData :self.theServerGetData];

}

- (NSString *)UploadFrameLossRate:(int)send :(int)serverGet
{
    float theLossRate = 0.0f;
    if (send > 0) {
        theLossRate = ((send-serverGet)/(float)send)*100;
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

- (IBAction)hideKeyBoard
{
    [self.theSendBitLable resignFirstResponder];
}


#pragma mark - UI

- (void)setUI
{

    
    [self setUIwithLayer:self.theSendView.layer:[UIColor colorWithWhite:0.800 alpha:1.000]];
    [self setUIwithLayer:self.theServerView.layer:[UIColor colorWithWhite:0.700 alpha:1.000]];
    [self setUIwithLayer:self.theControlView.layer:[UIColor colorWithWhite:0.600 alpha:1.000]];
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
