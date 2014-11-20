//
//  TextMsgVC.h
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface TextMsg_TransBufferVC : UIViewController<NSCoding,UITextFieldDelegate,UITableViewDelegate,UITableViewDataSource>

@property (weak, nonatomic) IBOutlet UINavigationItem   *theTextMsgNItem;
@property (weak, nonatomic) IBOutlet UITextField        *theTextMsgTextField;
@property (weak, nonatomic) IBOutlet UITableView        *theTextMsgTableView;
@property (weak, nonatomic) IBOutlet UIToolbar          *theToolbar;
@property (strong, nonatomic) NSMutableArray            *theMsgMArray;


kGCD_SINGLETON_FOR_HEADER(TextMsg_TransBufferVC);

- (IBAction)theSendMsg_OnClick:(id)sender;

- (IBAction)LeaveBtn_Onclick;

- (IBAction)clearDatas_OnClick;

- (void)TableViewReload;

- (void)NetworkAnomaliesAlert;

@end
