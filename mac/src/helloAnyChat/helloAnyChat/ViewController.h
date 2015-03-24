//
//  ViewController.h
//  helloAnyChat
//
//  Created by WangXL on 15/3/24.
//  Copyright (c) 2015年 WangXL. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "../../../sdk/include/AnyChatPlatform.h"
#import "../../../sdk/include/AnyChatDefine.h"
#import "../../../sdk/include/AnyChatErrorCode.h"



@interface ViewController : NSViewController <AnyChatNotifyMessageDelegate> {

    AnyChatPlatform* anychat;

}

- (void)AnyChatNotifyHandler:(NSNotification*)notify;


@end

