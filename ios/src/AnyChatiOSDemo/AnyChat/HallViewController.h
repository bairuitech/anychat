//
//  HallViewController.h
//  AnyChat
//
//  Created by bairuitech on 11-8-8.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface HallViewController : UIViewController {
    
    IBOutlet UILabel*   theSelfUserId;
}

@property (nonatomic, strong) UILabel       *theSelfUserId;


- (void) ShowSelfUserId:(int) userid;

- (IBAction) OnRoom1BtnClicked:(id)sender;

- (IBAction) OnRoom2BtnClicked:(id)sender;

- (IBAction) OnRoom3BtnClicked:(id)sender;

- (IBAction) OnRoom4BtnClicked:(id)sender;


- (IBAction) OnLogoutBtnClicked:(id)sender;


@end
