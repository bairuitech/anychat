//
//  FeaturesListVC.m
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "FeaturesListVC.h"

@interface FeaturesListVC ()

@end

@implementation FeaturesListVC

@synthesize theAnyChatVersionLab;
@synthesize videoFUNBtn;
@synthesize textMsgFUNBtn;
@synthesize transBufferFUNBtn;
@synthesize transFileFUNBtn;
@synthesize recordLocalFUNBtn;
@synthesize snapShotFUNBtn;
@synthesize callCenterFUNBtn;
@synthesize theMyUserIDLab;
@synthesize theUDPTraceFUNBtn;


kGCD_SINGLETON_FOR_CLASS(FeaturesListVC);

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}


#pragma mark - Life cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    [self setUI];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - UIActionSheet Delegate Method

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    [self sharedFeaturesInfo:self.theUDPTraceFUNBtn.titleLabel.text FeaturesNO:9];
    [AnyChatPlatform EnterRoom:9 :@""];
    
        //发送方
        if (buttonIndex == 0)
        {
            [self.navigationController pushViewController:[SendDataVC new] animated:NO];
        }
        //接收方
        if (buttonIndex == 1)
        {
            [self.navigationController pushViewController:[ReceiveDataVC new] animated:NO];
        }
    
//    NSLog(@"\n\n  buttonIndex: %i \n\n",(int)buttonIndex);
}


#pragma mark - Action Event Method

- (IBAction)VideoFUNBtnClick:(id)sender
{
    [self sharedFeaturesInfo:self.videoFUNBtn.titleLabel.text FeaturesNO:1];
    [AnyChatPlatform EnterRoom:1 :@""];
    [self.navigationController pushViewController:[UserListVC new] animated:YES];
}

- (IBAction)TextMsgFUNBtnClick:(id)sender
{
    [self sharedFeaturesInfo:self.textMsgFUNBtn.titleLabel.text FeaturesNO:2];
    [AnyChatPlatform EnterRoom:2 :@""];
    [self.navigationController pushViewController:[UserListVC new] animated:YES];
}

- (IBAction)TransBufferFUNBtnClick:(id)sender
{
    [self sharedFeaturesInfo:self.transBufferFUNBtn.titleLabel.text FeaturesNO:3];
    [AnyChatPlatform EnterRoom:3 :@""];
    [self.navigationController pushViewController:[UserListVC new] animated:YES];
}

- (IBAction)TransFileFUNBtnClick:(id)sender
{
    [self sharedFeaturesInfo:self.transFileFUNBtn.titleLabel.text FeaturesNO:4];
    [AnyChatPlatform EnterRoom:4 :@""];
    [self.navigationController pushViewController:[UserListVC new] animated:YES];
}

- (IBAction)RecordLocalFUNBtnClick:(id)sender
{
    [self sharedFeaturesInfo:self.recordLocalFUNBtn.titleLabel.text FeaturesNO:5];
    [AnyChatPlatform EnterRoom:5 :@""];
    [self.navigationController pushViewController:[UserListVC new] animated:YES];
}

- (IBAction)RecordServerFUNBtnClick:(id)sender
{
    [self sharedFeaturesInfo:self.recordServerFUNBtn.titleLabel.text FeaturesNO:6];
    [AnyChatPlatform EnterRoom:6 :@""];
    [self.navigationController pushViewController:[UserListVC new] animated:YES];
}

- (IBAction)SnapShotFUNBtnClick:(id)sender
{
    [self sharedFeaturesInfo:self.snapShotFUNBtn.titleLabel.text FeaturesNO:7];
    [AnyChatPlatform EnterRoom:7 :@""];
    [self.navigationController pushViewController:[UserListVC new] animated:YES];
}

- (IBAction)CallCenterFUNBtnClick:(id)sender
{
    [self sharedFeaturesInfo:self.callCenterFUNBtn.titleLabel.text FeaturesNO:8];
    [AnyChatPlatform EnterRoom:8 :@""];
    [self.navigationController pushViewController:[UserListVC new] animated:YES];
}

- (IBAction)ReturnLoginVCBtnClick:(id)sender
{
    [[AnyChatVC sharedAnyChatVC] OnLogout];
    [self.navigationController popToRootViewControllerAnimated:YES];
}


- (IBAction)videoSettingFUNBtnClick:(id)sender
{
    //    if (k_sysVersion >= 8.0f)
    //    {   //iOS 8.0
    //        NSURL *url = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
    //        if ([[UIApplication sharedApplication] canOpenURL:url]) {
    //            [[UIApplication sharedApplication] openURL:url];
    //        }
    //    }
    
    [self.navigationController pushViewController:[SettingVC sharedSettingVC] animated:YES];
}

- (IBAction)UDPTraceBtnClicked:(id)sender
{
    UIActionSheet *UDPTraceActSheet = [[UIActionSheet alloc]
                               initWithTitle:@"请选择操作角色?"
                               delegate:self
                               cancelButtonTitle:nil
                               destructiveButtonTitle:nil
                               otherButtonTitles:@"发送方",@"接收方", nil];
    UDPTraceActSheet.actionSheetStyle = UIActionSheetStyleBlackOpaque;
    [UDPTraceActSheet showInView:self.view];
}


#pragma mark - Instance Method

- (void)sharedFeaturesInfo:(NSString *)featuresName FeaturesNO:(int)featuresNO
{
    [AnyChatVC sharedAnyChatVC].theFeaturesName = featuresName;
    [AnyChatVC sharedAnyChatVC].theFeaturesNO = featuresNO;
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}


#pragma mark - Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark - UI Controls

- (void)setUI
{
    [self.navigationController setNavigationBarHidden:YES];
    self.theAnyChatVersionLab.text = [AnyChatVC sharedAnyChatVC].theVersionLab.text;
    self.theMyUserIDLab.text = [[NSString alloc] initWithFormat:@"Self userid:%i",[AnyChatVC sharedAnyChatVC].theMyUserID];
    
    if (k_sysVersion < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }
    
    [self prefersStatusBarHidden];
}


@end
