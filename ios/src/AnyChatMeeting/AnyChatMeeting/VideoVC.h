//
//  VideoVC.h
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2015年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "MZTimerLabel.h"
#import "AnyChatVC.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

#define kVideoWindowNumInt (int)3

@class VideoVC;


typedef void(^passValBlock)(int targerUserID,int imgViewTag,VideoVC *videoVC);
typedef void(^addImgBlock)(int imgViewTag,VideoVC *videoVC);

@interface VideoVC : ACBaseViewController <UIActionSheetDelegate,UIAlertViewDelegate>


@property (nonatomic,copy)passValBlock pvBlock;//有用户加入的回调
@property (nonatomic,copy)addImgBlock aiBlock;


- (void) FinishVideoChat;

@end
