//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "AnyChatVC.h"

#define kAnyChatRoomID 1
#define kUserID 1001
#define kAnyChatIP @"demo.anychat.cn"
#define kAnyChatPort @"8906"
#define kAnyChatUserName @"AnyChat"

@interface AnyChatVC ()

@end

@implementation AnyChatVC

@synthesize anyChat;
@synthesize theLoginState;
@synthesize theVersionLab;
@synthesize theStateInfo;
@synthesize theUserName;
@synthesize theServerIP;
@synthesize theServerPort;
@synthesize theLoginBtn;
@synthesize theHideKeyboardBtn;
@synthesize theFeaturesNO;
@synthesize theMyUserName;
@synthesize theMyUserID;
@synthesize onlineUserMArray;
@synthesize theTargetUserID;
@synthesize theTargetUserName;
@synthesize theVideoRecordMArray;
@synthesize thePhotoPath;
@synthesize theVideoPath;
@synthesize theNextVCBool;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {

    }
    return self;
}

#pragma mark - Life cycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    [AnyChatPlatform InitSDK:0];
    
    anyChat = [AnyChatPlatform getInstance];
    anyChat.notifyMsgDelegate = self;
    anyChat.transDataDelegate = self;
    anyChat.recordSnapShotDelegate = self;
    
    self.theVideoRecordMArray = [[NSMutableArray alloc] initWithCapacity:5];
    
    //创建默认视频参数
    [[SettingVC sharedSettingVC] createObjPlistFileToDocumentsPath];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUI];
}


#pragma mark - Shared Instance

kGCD_SINGLETON_FOR_CLASS(AnyChatVC);


#pragma mark -
#pragma mark - TextField Delegate

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    return YES;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    return YES;
}


#pragma mark - AnyChatNotifyMessageDelegate

// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess
{
    if (bSuccess)
    {
        theStateInfo.text = @"• Success connected to server";
    }
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode
{
    [MBProgressHUD hideHUDForView:self.view animated:YES];
    self.onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        //用户自定义视频参数设置
        [[SettingVC sharedSettingVC] updateUserVideoSettings];
        
        theLoginState = YES;
        self.theMyUserID = dwUserId;
        self.theMyUserName = self.theUserName.text;
        [self saveSettings];  //登陆信息归档
        theStateInfo.text = [NSString stringWithFormat:@" Login successed. Self UserId: %d", dwUserId];
        [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_logout_01"] forState:UIControlStateNormal];
        [AnyChatPlatform EnterRoom:1 :@""];
    }
    else
    {
        theLoginState = NO;
        theStateInfo.text = [NSString stringWithFormat:@"• Login failed(ErrorCode:%i)",dwErrorCode];
    }
    
}

// 进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode
{
    //拍照最佳像素
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_WIDTHCTRL :1280];
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_HEIGHTCTRL :720];
    
    TakePhotoVC *takePhotoVC = [[TakePhotoVC alloc] init];
    [self.navigationController pushViewController:takePhotoVC animated:YES];
}

- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId{
// 房间在线用户消息
}

- (void) OnAnyChatUserEnterRoom:(int) dwUserId{
// 用户进入房间消息
}

- (void) OnAnyChatUserLeaveRoom:(int) dwUserId{
// 用户退出房间消息
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode
{
    RecordLocalVC *recordVC = [RecordLocalVC new];
    [recordVC FinishVideoChat];
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    theStateInfo.text = [NSString stringWithFormat:@"• OnLinkClose(ErrorCode:%i)",dwErrorCode];
    theLoginState = NO;
    [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_login_01"] forState:UIControlStateNormal];
    
    [self.navigationController popToRootViewControllerAnimated:YES];
    UIAlertView *networkAlertView = [[UIAlertView alloc] initWithTitle:@"网络断开,请重新登录."
                                                        message:@"Network disconnection."
                                                       delegate:self
                                              cancelButtonTitle:nil
                                              otherButtonTitles:@"确定",nil];
    [networkAlertView show];
}


#pragma mark - AnyChatTransDataDelegate

- (void) OnAnyChatTransBufferCallBack:(int) dwUserid : (NSData*) lpBuf{
// 透明通道回调函数
}

- (void) OnAnyChatTransBufferExCallBack:(int) dwUserid : (NSData*) lpBuf : (int) wParam : (int) lParam : (int) dwTaskId{
// 透明通道数据扩展回调函数
}

- (void) OnAnyChatTransFileCallBack:(int) dwUserid : (NSString*) lpFileName : (NSString*) lpTempFilePath : (int) dwFileLength : (int) wParam : (int) lParam : (int) dwTaskId{
// 文件传输回调函数
}

// 通信数据回调函数
- (void) OnAnyChatSDKFilterDataCallBack:(NSData*) lpBuf{
//  SDK Filter
}


#pragma mark - AnyChatRecordSnapShotDelegate
// 录像完成事件
- (void) OnAnyChatRecordCallBack:(int) dwUserid : (int) dwErrorCode : (NSString*) lpFileName : (int) dwElapse : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr
{
    self.theVideoPath = lpFileName;
    
    ShowVC *showVC = [ShowVC new];
    [self.navigationController pushViewController:showVC animated:YES];
}

// 抓拍完成事件
- (void) OnAnyChatSnapShotCallBack:(int) dwUserid : (int) dwErrorCode : (NSString*) lpFileName : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr
{
    ProviewPhotoVC *proviewPhotoVC = [ProviewPhotoVC new];
    [proviewPhotoVC showSnapShotPhoto:lpFileName transform:@""];
    proviewPhotoVC.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
    [self.navigationController presentViewController:proviewPhotoVC animated:YES completion:nil];
    
    if (lpFileName)
    {
        self.thePhotoPath = lpFileName;
    }
    
}


#pragma mark -
#pragma mark - Get & Save Settings Method
- (void)saveSettings
{
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    [[NSArray arrayWithObjects:theServerIP.text,theServerPort.text,theUserName.text, nil] writeToFile:filePath atomically:YES];
}


#pragma mark - Instance Method

- (void)AnyChatNotifyHandler:(NSNotification*)notify
{
    NSDictionary* dict = notify.userInfo;
    [anyChat OnRecvAnyChatNotify:dict];
}

- (IBAction)hideKeyBoard
{
    [theServerIP resignFirstResponder];
    [theServerPort resignFirstResponder];
    [theUserName resignFirstResponder];

}

- (IBAction)OnLoginBtnClicked:(id)sender
{
    if (theLoginState == YES)
    {
        [self OnLogout];
    }
    else
    {
        [self OnLogin];
    }
}

- (IBAction)VideoSetting:(id)sender
{
    [self.navigationController pushViewController:[SettingVC sharedSettingVC] animated:YES];
}

- (void) OnLogin
{
    if([theUserName.text length] == 0) {
        theUserName.text = kAnyChatUserName;
    }
    if([theServerIP.text length] == 0) {
        theServerIP.text = kAnyChatIP;
    }
    if([theServerPort.text length] == 0) {
        theServerPort.text = kAnyChatPort;
    }
    
    [self showLoadingAnimated];
    
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */

    [AnyChatPlatform Connect:theServerIP.text : [theServerPort.text intValue]];
   
    /*
     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
     */
    [AnyChatPlatform Login:theUserName.text :nil];
    
    [self hideKeyBoard];
}

- (void) OnLogout
{
    [AnyChatPlatform Logout];
    
    theLoginState = NO;
    
    theStateInfo.text = @"• Logout Server.";
    [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_login_01"] forState:UIControlStateNormal];
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}


#pragma mark - AlertView method

- (NSString *)showInfoAlertView:(NSString *)Title : (NSString *)subTitle
{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:Title
                                                        message:subTitle
                                                       delegate:self
                                              cancelButtonTitle:nil
                                              otherButtonTitles:nil,nil];
    [alertView show];
    
    [self performSelector:@selector(dimissAlertView:) withObject:alertView afterDelay:1.5];
    
    return subTitle;
}

- (void) dimissAlertView:(UIAlertView *)alert {
    if(alert){
        [alert dismissWithClickedButtonIndex:[alert cancelButtonIndex] animated:YES];
    }
}

- (void)NetworkAnomaliesAlert
{
    UIAlertView *failuresMsgAlert = [[UIAlertView alloc] initWithTitle:@"发送失败！"
                                                               message:@"网络出现异常,请重新登录再试!"
                                                              delegate:nil
                                                     cancelButtonTitle:@"确定"
                                                     otherButtonTitles: nil];
    [failuresMsgAlert show];
}

#pragma mark - Loading Animation Method

- (void)showLoadingAnimated
{
    HUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    HUD.labelText = @"AnyChatSingleVideo";
    HUD.detailsLabelText = @"Loading...";
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
    
    theUserName.text = kAnyChatUserName;
    theServerIP.text = kAnyChatIP;
    theServerPort.text = kAnyChatPort;

    [theServerIP addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theServerPort addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theUserName addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    
    if (k_sysVersion < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }

    theVersionLab.text = [AnyChatPlatform GetSDKVersion];
    
    [self prefersStatusBarHidden];
    
}

@end
