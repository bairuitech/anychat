//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"
#import "RecordLocalVC.h"

@protocol ProviewPhotoVCDelegate <NSObject>
@optional
-(void)dismissVC;

@end


@interface ProviewPhotoVC : ACBaseViewController
@property (nonatomic, weak) id<ProviewPhotoVCDelegate> delegate;
@property (nonatomic, copy) NSString *filePath;

- (IBAction)nextBtn_OnClick;


@end
