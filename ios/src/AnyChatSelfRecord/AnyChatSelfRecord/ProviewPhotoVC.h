//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"
#import "RecordLocalVC.h"


@interface ProviewPhotoVC : UIViewController

- (IBAction)returnBtn_OnClick;

- (IBAction)nextBtn_OnClick;

- (void)showSnapShotPhoto:(NSString *)theFilePath transform:(NSString *)transformParam;

@end
