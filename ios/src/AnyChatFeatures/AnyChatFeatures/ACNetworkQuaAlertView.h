//
//  ACNetworkQuaAlertView.h
//  AnyChatFeatures
//
//  Created by Bairui on 2019/6/14.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "LEOAlertView.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger ,ACNetworkQuaType) {
    
    ACNetworkQuaTypeSend,
    ACNetworkQuaTypeReceive
};

typedef void(^ACNetworkQuaAlertViewCertainBlock)(NSString *roomId);

@interface ACNetworkQuaAlertView : LEOAlertView

@property (nonatomic, readonly) ACNetworkQuaType  quaType;
@property (weak, nonatomic) IBOutlet UITextField *textField;

@property (nonatomic, copy) ACNetworkQuaAlertViewCertainBlock certainClick;
@end

NS_ASSUME_NONNULL_END
