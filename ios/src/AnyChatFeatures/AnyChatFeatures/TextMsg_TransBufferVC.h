//
//  TextMsgVC.h
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>

@interface TextMsg_TransBufferVC : ACBaseViewController<NSCoding,UITextFieldDelegate,UITableViewDelegate,UITableViewDataSource>


@property (strong, nonatomic) NSMutableArray            *theMsgMArray;


kGCD_SINGLETON_FOR_HEADER(TextMsg_TransBufferVC);




- (void)TableViewReload;

- (void)NetworkAnomaliesAlert;

@end
