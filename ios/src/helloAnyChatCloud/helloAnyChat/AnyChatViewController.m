//
//  AnyChatViewController.m
//  helloAnyChat
//
//  Created by AnyChat on 14-9-12.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "AnyChatViewController.h"
#import "RadioButton.h"
#import "AFNetworking.h"

#define kAnyChatRoomID 1
#define kUserID 1001
#define kSignServerURL @"http://192.168.6.102:8980/"
#define kAnyChatIP @"demo.anychat.cn"
#define kAnyChatPort @"8906"
#define kAnyChatUserName @"AnyChat"
#define kAnyChatGuid @"bb9ca6ec-e611-4208-ab8f-44b5881c41e8"

typedef enum {
    AnyChatVCLoginModeGeneralLogin,
    AnyChatVCLoginModeSignLogin
} AnyChatVCLoginMode;

@interface AnyChatViewController ()
@property (nonatomic, assign) AnyChatVCLoginMode loginMode; // 登录方式
@end

@implementation AnyChatViewController

@synthesize anyChat;
@synthesize videoVC;
@synthesize onLineUserTableView;
@synthesize onlineUserMArray;
@synthesize theOnLineLoginState;
@synthesize theVersion;
@synthesize theStateInfo;
@synthesize theRoomNO;
@synthesize theUserName;
@synthesize theServerIP;
@synthesize theServerPort;
@synthesize theGuid;
@synthesize theLoginBtn;
@synthesize theLoginAlertView;
@synthesize theHideKeyboardBtn;
@synthesize theMyUserID;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        
    }
    return self;
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    [AnyChatPlatform InitSDK:0];
    
    anyChat = [AnyChatPlatform getInstance];
    anyChat.notifyMsgDelegate = self;
    // 设置应用ID
//    [AnyChatPlatform SetSDKOptionString:BRAC_SO_CLOUD_APPGUID :nil];
    
    //创建默认视频参数
    [[SettingVC sharedSettingVC] createObjPlistFileToDocumentsPath];
}


- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUIControls];
}

#pragma mark - Memory Warning Method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return onlineUserMArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *Cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (Cell == nil)
    {
        NSArray *nibs = [[NSBundle mainBundle] loadNibNamed:@"tableVCell" owner:self options:nil];
        Cell = [nibs objectAtIndex:0];
    }
    
    int userID = [[onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    NSString *name = [AnyChatPlatform GetUserName:userID];
    
    UILabel *userIDLabel = (UILabel *)[Cell.contentView viewWithTag:kUserIDValueTag];
    UILabel *nameLabel = (UILabel *)[Cell.contentView viewWithTag:kNameValueTag];
    UIImageView *bgView = (UIImageView *)[Cell viewWithTag:kBackgroundViewTag];
    
    if (theMyUserID == userID)
    {
        nameLabel.text = [name stringByAppendingString:@"(自己)[视频设置]"];
    }
    else
    {
        nameLabel.text = name;
    }
    
    userIDLabel.text = [NSString stringWithFormat:@"%i",userID];
    
    NSString *RandomNo = [[NSString alloc] initWithFormat:@"%i",[self getRandomNumber:1 to:5]];
    bgView.image = [UIImage imageNamed:RandomNo];
    
    Cell.selectionStyle = UITableViewCellSelectionStyleDefault;
    
    return Cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int selectID = [[onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    
    if (selectID != theMyUserID)
    {
        //更新用户自定义视频参数设置
        [[SettingVC sharedSettingVC] updateUserVideoSettings];
        
        videoVC = [VideoViewController new];
        videoVC.iRemoteUserId = selectID;
        [self.navigationController pushViewController:videoVC animated:YES];
    }
    else
    {
        SettingVC *settingVC = [SettingVC new];
        [self.navigationController pushViewController:settingVC animated:YES];
    }
}

//- (CGFloat)tableView:(UITableView *)tabelView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
//	return 81.0f;
//}


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
    onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        theOnLineLoginState = YES;
        theMyUserID = dwUserId;
        [self saveSettings];  //save correct configuration
        theStateInfo.text = [NSString stringWithFormat:@" Login successed. Self UserId: %d", dwUserId];
        [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_logout_01"] forState:UIControlStateNormal];
        
        if([theRoomNO.text length] == 0)
        {
            theRoomNO.text = [NSString stringWithFormat:@"%d",kAnyChatRoomID];
        }
        [AnyChatPlatform EnterRoom:(int)[theRoomNO.text integerValue] :@""];
    }
    else
    {
        theOnLineLoginState = NO;
        theStateInfo.text = [NSString stringWithFormat:@"• Login failed(ErrorCode:%i)",dwErrorCode];
    }
    
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode
{
    if (dwErrorCode != 0) {
        theStateInfo.text = [NSString stringWithFormat:@"• Enter room failed(ErrorCode:%i)",dwErrorCode];
    }
    
    [onLineUserTableView reloadData];
}

// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId
{
    onlineUserMArray = [self getOnlineUserArray];
    [onLineUserTableView reloadData];
}

// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId
{
    onlineUserMArray = [self getOnlineUserArray];
    [onLineUserTableView reloadData];
}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId
{
    if (videoVC.iRemoteUserId == dwUserId )
    {
        [videoVC FinishVideoChat];
        NSString *name = [AnyChatPlatform GetUserName:dwUserId];
        NSString *theLeaveRoomName = [[NSString alloc] initWithFormat:@"\"%@\"已离开房间!",name];
        UIAlertView *leaveRoomAlertView = [[UIAlertView alloc] initWithTitle:theLeaveRoomName
                                                                   message:@"The remote user Leave Room."
                                                                  delegate:self
                                                         cancelButtonTitle:nil
                                                         otherButtonTitles:@"确定",nil];
        [leaveRoomAlertView show];
        videoVC.iRemoteUserId = -1;
    }
    onlineUserMArray = [self getOnlineUserArray];
    [onLineUserTableView reloadData];
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode {
    [videoVC FinishVideoChat];
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    theOnLineLoginState = NO;
    [onlineUserMArray removeAllObjects];
    [onLineUserTableView reloadData];
    
    theStateInfo.text = [NSString stringWithFormat:@"• OnLinkClose(ErrorCode:%i)",dwErrorCode];
    [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_login_01"] forState:UIControlStateNormal];
}


#pragma mark - Get & Save Settings Method
- (void)saveSettings
{   // save settings to file
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

- (NSMutableArray *) getOnlineUserArray
{
    NSMutableArray *onLineUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
    [onLineUserList insertObject:[NSString stringWithFormat:@"%i",self.theMyUserID] atIndex:0];
    return onLineUserList;
}

- (IBAction)hideKeyBoard {
    [theServerIP resignFirstResponder];
    [theServerPort resignFirstResponder];
    [theUserName resignFirstResponder];
    [theRoomNO resignFirstResponder];
    [theGuid resignFirstResponder];
}

- (IBAction)OnLoginBtnClicked:(id)sender
{
    if (theOnLineLoginState == YES)
    {
        [self OnLogout];
    }
    else
    {
        [self OnLogin];
    }
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
    if (self.loginMode == AnyChatVCLoginModeSignLogin) {
        if (theGuid.text.length == 0) {
            MBProgressHUD *mbHUD= [MBProgressHUD showHUDAddedTo:self.view animated:YES];
            mbHUD.labelText = @"应用ID不能为空";
            mbHUD.customView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"error"]];
            mbHUD.mode = MBProgressHUDModeCustomView;
            mbHUD.removeFromSuperViewOnHide = YES;
            [mbHUD hide:YES afterDelay:0.7];
            
            return;
        }
    }
    
    [self showLoadingAnimated];
    
    if (self.loginMode == AnyChatVCLoginModeGeneralLogin && theGuid.text.length != 0) {
        [AnyChatPlatform SetSDKOptionString:BRAC_SO_CLOUD_APPGUID :theGuid.text];
    }
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    [AnyChatPlatform Connect:theServerIP.text : [theServerPort.text intValue]];
    
    if (self.loginMode == AnyChatVCLoginModeSignLogin && theGuid.text.length != 0) {
        [self getSignSuccess:^(id json) {
            if ([[json objectForKey:@"errorcode"] intValue] ==0) {
                int timestamp = [[json objectForKey:@"timestamp"] intValue];
                NSString *signStr = [json objectForKey:@"sigStr"];
                [AnyChatPlatform LoginEx:theUserName.text :kUserID :nil :theGuid.text :timestamp :signStr :nil];
            }else {
                NSLog(@"Json Error,Error Num:%@",[json objectForKey:@"errorcode"]);
            }
        } failure:^(NSError *error) {
            NSLog(@"Request Error:%@",error);
        }];
    }else if(self.loginMode == AnyChatVCLoginModeGeneralLogin){
        
        /*
         * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
         */
        [AnyChatPlatform Login:theUserName.text :nil];
    }
    
    
    [self hideKeyBoard];
}

- (void)getSignSuccess:(void (^)(id))success failure:(void (^)(NSError *))failure{
    
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
    params[@"userid"] = [NSNumber numberWithInt:kUserID];
    params[@"strUserid"] = @"";
    params[@"appid"] = theGuid.text;
    
    [manager POST:kSignServerURL parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        if (success) success(responseObject);
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        if (failure) failure(error);
    }];
    
}

- (void) OnLogout
{
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    theOnLineLoginState = NO;
    [onlineUserMArray removeAllObjects];
    [onLineUserTableView reloadData];
    theStateInfo.text = @"• Logout Server.";
    [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_login_01"] forState:UIControlStateNormal];
}

- (int)getRandomNumber:(int)from to:(int)to
{
    //  +1,result is [from to]; else is [from, to)!!!!!!!
    return (int)(from + (arc4random() % (to - from + 1)));
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

#pragma mark - Animation Method

- (void)showLoadingAnimated
{
    HUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    HUD.labelText = @"helloAnyChat";
    HUD.detailsLabelText = @"Loading...";
}

#pragma mark - UI Controls

- (void)setUIControls
{
    [self.navigationController setNavigationBarHidden:YES];
    
    theRoomNO.text = [NSString stringWithFormat:@"%d",kAnyChatRoomID];
    theRoomNO.keyboardType = UIKeyboardTypePhonePad;
    theUserName.text = kAnyChatUserName;
    theServerIP.text = kAnyChatIP;
    theServerPort.text = kAnyChatPort;
    theGuid.text = kAnyChatGuid;
    
    [theServerIP addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theServerPort addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theUserName addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theRoomNO addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    
    if ([[UIDevice currentDevice].systemVersion floatValue] < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }
    
    [theVersion setText:[AnyChatPlatform GetSDKVersion]];
    [self prefersStatusBarHidden];
    
    UIView *footerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, kSelfView_Width, 70.0f)];
    onLineUserTableView.tableFooterView = footerView;
    
}

-(IBAction)onRadioBtn:(RadioButton*)sender
{
    if ([sender.titleLabel.text isEqualToString:@"签名登录"]) {
        self.loginMode = AnyChatVCLoginModeSignLogin;
    }else {
        self.loginMode = AnyChatVCLoginModeGeneralLogin;
    }
}


@end
