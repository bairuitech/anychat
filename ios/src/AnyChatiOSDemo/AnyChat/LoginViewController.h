//
//  LoginViewController.h
//  AnyChatiPhone
//
//  Created by bairuitech on 11-8-5.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>



@interface LoginViewController : UIViewController {
    
    IBOutlet UITextField    *theUserName;
    IBOutlet UITextField    *thePassword;
    IBOutlet UIButton       *theLoginBtn;
    IBOutlet UIButton       *theSettingsBtn;
    IBOutlet UILabel        *theVersion;
    
    IBOutlet UIButton       *theHideKeyboardBtn;
    
    
}

@property (nonatomic, strong) UITextField   *theUserName;
@property (nonatomic, strong) UITextField   *thePassword;
@property (nonatomic, strong) UIButton      *theLoginBtn;
@property (nonatomic, strong) UIButton      *theSettingsBtn;
@property (nonatomic, strong) UILabel       *theVersion;

@property (nonatomic, strong) UIButton      *theHideKeyboardBtn;


-(IBAction)OnNetConfigBtnClicked:(id)sender;

-(IBAction)OnLoginBtnClicked:(id)sender;

- (IBAction) hideKeyBoard:(id)sender;

@end
