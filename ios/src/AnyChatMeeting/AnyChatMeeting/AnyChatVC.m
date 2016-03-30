//
//  VideoVC.m
//  AnyChatMeetings
//
//  Created by alexChen .
//  Copyright (c) 2015年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
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
@synthesize videoVC;
@synthesize theOnLineLoginState;
@synthesize theVersionLab;
@synthesize theStateInfo;
@synthesize theUserName;
@synthesize theServerIP;
@synthesize theServerPort;
@synthesize theRoomNO;
@synthesize theLoginBtn;
@synthesize theHideKeyboardBtn;
@synthesize theMyUserName;
@synthesize theMyUserID;
@synthesize onlineUserMArray;
@synthesize theOnChatUserIDStrMArray;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self){
    }
    return self;
}

#pragma mark - Life cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    [AnyChatPlatform InitSDK:0];
    
    anyChat = [[AnyChatPlatform alloc] init];
    anyChat.notifyMsgDelegate = self;
    
    //创建默认视频参数
    [[SettingVC sharedSettingVC] createObjPlistFileToDocumentsPath];
    self.onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    self.theOnChatUserIDStrMArray = [[NSMutableArray alloc] initWithObjects:@"0",@"0",@"0", nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    [self setUI];
}

#pragma mark - Memory Warning Method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
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
    }else {
        theStateInfo.text = @"• Fail connected to server";
        [HUD hide:YES];
    }
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode
{
    [MBProgressHUD hideHUDForView:self.view animated:YES];
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        //更新系统默认视频参数设置
        [[SettingVC sharedSettingVC] updateUserVideoSettings];
        
        theOnLineLoginState = YES;
        self.theMyUserID = dwUserId;
        self.theMyUserName = self.theUserName.text;
        [self saveSettings];  //登陆信息归档
        theStateInfo.text = [NSString stringWithFormat:@" Login successed. Self UserId: %d", dwUserId];
        [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_logout_01"] forState:UIControlStateNormal];

        [AnyChatPlatform EnterRoom:[theRoomNO.text intValue] :@""];
    }
    else
    {
        theOnLineLoginState = NO;
        
        theStateInfo.text = [NSString stringWithFormat:@"• Login failed(ErrorCode:%i)",dwErrorCode];
    }
    
}

// 当前用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode
{
    //更新用户自定义视频参数设置
    [[SettingVC sharedSettingVC] updateUserVideoSettings];
    
    if (dwErrorCode != 0)
    {
        theStateInfo.text = [NSString stringWithFormat:@"• Enter room failed(ErrorCode:%i)",dwErrorCode];
    }

    self.onlineUserMArray = [self getOnlineUserArray];
}

// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId
{
    self.onlineUserMArray = [self getOnlineUserArray];
    
    videoVC = [[VideoVC alloc] init];
    
    [self.navigationController pushViewController:videoVC animated:YES];
}

// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId
{
    NSString *dwUserIdStr = [NSString stringWithFormat:@"%d",dwUserId];
    
    NSInteger isNilArrayOfIndex = [self.theOnChatUserIDStrMArray indexOfObject:@"0"];
    if (isNilArrayOfIndex != NSNotFound)
    {
        [self.theOnChatUserIDStrMArray replaceObjectAtIndex:isNilArrayOfIndex
                                                 withObject:dwUserIdStr];
        
        if (videoVC == nil) {
            videoVC = [[VideoVC alloc] init];
        }
        //进行视频
        videoVC.pvBlock(dwUserId,((int)isNilArrayOfIndex + 1),videoVC);
    }
  
    self.onlineUserMArray = [self getOnlineUserArray];
}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId
{
    if (videoVC == nil)
    {
        videoVC = [[VideoVC alloc] init];
    }

    NSString *dwUserIdStr = [NSString stringWithFormat:@"%d",dwUserId];

    if ([self.theOnChatUserIDStrMArray containsObject:dwUserIdStr])
    {   //find LeaveRoom userID in Array Of Index
        NSInteger userIDIndexOfInt = [self.theOnChatUserIDStrMArray indexOfObject:dwUserIdStr];
        //DEL LeaveRoom userID & set val=“0”
        [self.theOnChatUserIDStrMArray replaceObjectAtIndex:userIDIndexOfInt withObject:@"0"];
        
        //用户离开后，把停止的最后一帧 设置为图片
        videoVC.aiBlock(((int)userIDIndexOfInt+1),videoVC);
    }
    
    NSMutableArray *OnLineWaitingChatUserIDMArray = [self getOnLineWaitingChatUserIDMArray];
    
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode
{
    [videoVC FinishVideoChat];
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    theStateInfo.text = [NSString stringWithFormat:@"• OnLinkClose(ErrorCode:%i)",dwErrorCode];
    theOnLineLoginState = NO;
    [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_login_01"] forState:UIControlStateNormal];
    
    [self.navigationController popToRootViewControllerAnimated:YES];
    UIAlertView *networkAlertView = [[UIAlertView alloc] initWithTitle:@"网络断开,请重新登录."
                                                        message:@"Network disconnection."
                                                       delegate:self
                                              cancelButtonTitle:nil
                                              otherButtonTitles:@"确定",nil];
    [networkAlertView show];
}


#pragma mark -
#pragma mark - Get & Save Settings Method
- (void)saveSettings
{
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    [[NSArray arrayWithObjects:theServerIP.text,theServerPort.text,theUserName.text,theRoomNO.text, nil] writeToFile:filePath atomically:YES];
}


#pragma mark - Instance Method


- (void)AnyChatNotifyHandler:(NSNotification*)notify
{
    NSDictionary* dict = notify.userInfo;
    [anyChat OnRecvAnyChatNotify:dict];
}

//获取等候视频的在线用户
- (NSMutableArray *) getOnLineWaitingChatUserIDMArray
{
    self.onlineUserMArray = [self getOnlineUserArray];
    NSMutableArray *waitingIDStrMArray = [NSMutableArray arrayWithArray:self.onlineUserMArray];
    NSPredicate *thePredicate = [NSPredicate predicateWithFormat:@"NOT (SELF in %@)", self.theOnChatUserIDStrMArray];
    [waitingIDStrMArray filterUsingPredicate:thePredicate];
    
    return waitingIDStrMArray;
}

- (NSMutableArray *) getOnlineUserArray
{
    NSMutableArray *onLineUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
    return onLineUserList;
}

- (IBAction)hideKeyBoard
{
    [self.theServerIP resignFirstResponder];
    [self.theServerPort resignFirstResponder];
    [self.theUserName resignFirstResponder];
    [self.theRoomNO resignFirstResponder];

}

- (IBAction)OnLoginBtnClicked:(id)sender
{
    if (theOnLineLoginState == YES) {
        [self OnLogout];
    }else {
        [self OnLogin];
    }
}

- (void) OnLogin
{
    
    
    if([theServerIP.text length] == 0) {
        theServerIP.text = kAnyChatIP;
    }
    if([theServerPort.text length] == 0) {
        theServerPort.text = kAnyChatPort;
    }
    if([theUserName.text length] == 0) {
        theUserName.text = kAnyChatUserName;
    }
    if([theRoomNO.text length] == 0) {
        theRoomNO.text = [NSString stringWithFormat:@"%d",kAnyChatRoomID];
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
    
    theOnLineLoginState = NO;
    
    theStateInfo.text = @"• Logout Server.";
    [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_login_01"] forState:UIControlStateNormal];
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (IBAction)VideoSetting:(id)sender
{
    [self.navigationController pushViewController:[SettingVC sharedSettingVC] animated:YES];
}


#pragma mark - AlertView delegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
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

#pragma mark - Loading Animation Method

- (void)showLoadingAnimated
{
    HUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    HUD.labelText = @"AnyChatMeetings";
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
    theRoomNO.text = [NSString stringWithFormat:@"%d",kAnyChatRoomID];
 
    [theServerIP addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theServerPort addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theUserName addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theRoomNO addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    
    if (k_sysVersion < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }

    theVersionLab.text = [AnyChatPlatform GetSDKVersion];
    
    [self prefersStatusBarHidden];
    
}

@end
