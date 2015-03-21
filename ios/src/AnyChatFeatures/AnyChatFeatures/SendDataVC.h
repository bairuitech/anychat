//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface SendDataVC : UIViewController
{
    NSTimer *theNSTimer;
    int onClickTimes;
}

@property (strong, nonatomic) IBOutlet UIView           *theSendView;
@property (strong, nonatomic) IBOutlet UIView           *theServerView;
@property (strong, nonatomic) IBOutlet UIView           *theControlView;

@property (strong, nonatomic) IBOutlet UILabel          *theSendViewSendLable;
@property (strong, nonatomic) IBOutlet UILabel          *theSendViewRecvLable;
@property (strong, nonatomic) IBOutlet UILabel          *theSendViewLossLable;
@property (strong, nonatomic) IBOutlet UILabel          *theServerViewRecvLable;
@property (strong, nonatomic) IBOutlet UILabel          *theSendViewIPLable;

@property (strong, nonatomic) IBOutlet UITextField      *theSendBitLable;

@property (strong, nonatomic) IBOutlet UIButton         *theStartBtn;
@property (strong, nonatomic) IBOutlet UIButton         *theEndBtn;

@property   int   theSendData;
@property   int   theRecvData;
@property   int   theServerGetData;


- (IBAction)theStartBtn_Click:(id)sender;
- (IBAction)theEndBtn_Click:(id)sender;


@end
