//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface ReceiveDataVC : UIViewController
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

@property   int   theSendData;
@property   int   theRecvData;
@property   int   theServerGetData;

@end
