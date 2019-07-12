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
//#define kUserID 1001

#define kAnyChatIP @"demo.anychat.cn" //普通登录服务器IP
#define kAnyChatPort @"8906"
#define kAnyChatUserName @"AnyChat"

#define kAnyChatSignServerURL @"http://demo.anychat.cn:8930/" //签名服务器
#define kAnyChatSignIP @"cloud.anychat.cn" //签名登录服务器IP
#define kAnyChatSignGuid @"fbe957d1-c25a-4992-9e75-d993294a5d56" //签名登录应用ID


typedef enum {
    AnyChatVCLoginModeGeneralLogin,
    AnyChatVCLoginModeSignLogin
} AnyChatVCLoginMode;

@interface AnyChatViewController () {
    BOOL _connectSuccess;
    MBProgressHUD *HUD;

}
@property (nonatomic, assign) AnyChatVCLoginMode loginMode; // 登录方式

@property (weak, nonatomic) IBOutlet UITextField            *theUserName;
@property (weak, nonatomic) IBOutlet UITextField            *theRoomNO;
@property (weak, nonatomic) IBOutlet UITextField            *theServerIP;
@property (weak, nonatomic) IBOutlet UITextField            *theServerPort;
@property (weak, nonatomic) IBOutlet UITextField            *theGuid;
@property (weak, nonatomic) IBOutlet UITextField            *theSignServer;
@property (weak, nonatomic) IBOutlet UIButton               *theLoginBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theVersion;
@property (weak, nonatomic) IBOutlet UILabel                *theStateInfo;
@property (strong, nonatomic) IBOutlet UITableView          *onLineUserTableView;


@property (strong, nonatomic) VideoViewController           *videoVC;
@property (strong, nonatomic) AnyChatPlatform               *anyChat;
@property BOOL theOnLineLoginState;
@property int theMyUserID;

@end

@implementation AnyChatViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self setUIControls];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    [AnyChatPlatform InitSDK:0];
    self.anyChat = [AnyChatPlatform getInstance];
    self.anyChat.notifyMsgDelegate = self;
    // 设置应用ID
//    [AnyChatPlatform SetSDKOptionString:BRAC_SO_CLOUD_APPGUID :nil];
    
    //创建默认视频参数
    [[SettingVC sharedSettingVC] createObjPlistFileToDocumentsPath];
    self.onLineUserTableView.dataSource = self;
    self.onLineUserTableView.delegate = self;
   
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll
                            exceptViews:nil];
}


- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
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
    return self.onlineUserMArray.count;
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
    
    int userID = [[self.onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    NSString *name = [AnyChatPlatform GetUserName:userID];
    
    UILabel *userIDLabel = (UILabel *)[Cell.contentView viewWithTag:kUserIDValueTag];
    UILabel *nameLabel = (UILabel *)[Cell.contentView viewWithTag:kNameValueTag];
    UIImageView *bgView = (UIImageView *)[Cell viewWithTag:kBackgroundViewTag];
    
    if (self.theMyUserID == userID)
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
    int selectID = [[self.onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    
    if (selectID != self.theMyUserID)
    {
        //更新用户自定义视频参数设置
        [[SettingVC sharedSettingVC] updateUserVideoSettings];
        
        self.videoVC = [VideoViewController new];
        self.videoVC.iRemoteUserId = selectID;
        NSString *name = [AnyChatPlatform GetUserName:selectID];
        self.videoVC.remoteUserName = name;
        [self.navigationController pushViewController:self.videoVC animated:YES];
    }
    else
    {
        SettingVC *settingVC = [SettingVC new];
        [settingVC readDataWithPList];
        [self.navigationController pushViewController:settingVC animated:YES];
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (CGFloat)tableView:(UITableView *)tabelView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 81.0f;
}

#pragma mark - AnyChatNotifyMessageDelegate

// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess
{
    _connectSuccess = bSuccess;
    if (bSuccess)
    {
        self.theStateInfo.text = @"• Success connected to server";
    }else {
        
        self.theStateInfo.text = @"• Fail connected to server";
        [HUD hide:YES];
    }
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode
{
    [MBProgressHUD hideHUDForView:self.view animated:YES];
    self.onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        self.theOnLineLoginState = YES;
        self.theMyUserID = dwUserId;
        [self saveSettings];  //save correct configuration
        self.theStateInfo.text = [NSString stringWithFormat:@" Login successed. Self UserId: %d", dwUserId];
        self.theLoginBtn.selected = YES;
        
        if([self.theRoomNO.text length] == 0)
        {
            self.theRoomNO.text = [NSString stringWithFormat:@"%d",kAnyChatRoomID];
        }
        [AnyChatPlatform EnterRoom:(int)[self.theRoomNO.text integerValue] :@""];
    }
    else
    {
        self.theOnLineLoginState = NO;
        self.theStateInfo.text = [NSString stringWithFormat:@"• Login failed(ErrorCode:%i)",dwErrorCode];
    }
    
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode
{
    if (dwErrorCode != 0) {
        self.theStateInfo.text = [NSString stringWithFormat:@"• Enter room failed(ErrorCode:%i)",dwErrorCode];
    }
    
    [self.onLineUserTableView reloadData];
}

// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId
{
    self.onlineUserMArray = [self getOnlineUserArray];
    [self.onLineUserTableView reloadData];
}

// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId
{
    self.onlineUserMArray = [self getOnlineUserArray];
    [self.onLineUserTableView reloadData];
}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId
{
    if (self.videoVC.iRemoteUserId == dwUserId )
    {
        [self.videoVC FinishVideoChat];
        NSString *name = [AnyChatPlatform GetUserName:dwUserId];
        NSString *theLeaveRoomName = [[NSString alloc] initWithFormat:@"\"%@\"已离开房间!",name];
        UIAlertView *leaveRoomAlertView = [[UIAlertView alloc] initWithTitle:theLeaveRoomName
                                                                   message:@"The remote user Leave Room."
                                                                  delegate:self
                                                         cancelButtonTitle:nil
                                                         otherButtonTitles:@"确定",nil];
        [leaveRoomAlertView show];
        self.videoVC.iRemoteUserId = -1;
    }
    self.onlineUserMArray = [self getOnlineUserArray];
    [self.onLineUserTableView reloadData];
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode {
    [self.videoVC FinishVideoChat];
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    self.theOnLineLoginState = NO;
    [self.onlineUserMArray removeAllObjects];
    [self.onLineUserTableView reloadData];
    
    self.theStateInfo.text = [NSString stringWithFormat:@"• OnLinkClose(ErrorCode:%i)",dwErrorCode];
    self.theLoginBtn.selected = NO;
}


#pragma mark - Get & Save Settings Method
- (void)saveSettings
{   // save settings to file
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    [[NSArray arrayWithObjects:self.theServerIP.text,self.theServerPort.text,self.theUserName.text,self.theRoomNO.text, nil] writeToFile:filePath atomically:YES];
}


#pragma mark - Instance Method

- (void)AnyChatNotifyHandler:(NSNotification*)notify
{
    NSDictionary* dict = notify.userInfo;
    [self.anyChat OnRecvAnyChatNotify:dict];
}

- (NSMutableArray *) getOnlineUserArray
{
    NSMutableArray *onLineUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
    [onLineUserList insertObject:[NSString stringWithFormat:@"%i",self.theMyUserID] atIndex:0];
    return onLineUserList;
}

- (void)hideKeyBoard {

    [self.view endEditing:YES];
}

- (IBAction)OnLoginBtnClicked:(id)sender
{
    if (self.theOnLineLoginState == YES)
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
    
    if([self.theUserName.text length] == 0) {
        self.theUserName.text = kAnyChatUserName;
    }
    if([self.theServerIP.text length] == 0) {
        self.theServerIP.text = kAnyChatIP;
    }
    if([self.theServerPort.text length] == 0) {
        self.theServerPort.text = kAnyChatPort;
    }

    if (self.loginMode == AnyChatVCLoginModeSignLogin) {
        
        if (self.theGuid.text.length == 0) {
            MBProgressHUD *mbHUD= [MBProgressHUD showHUDAddedTo:self.view animated:YES];
            mbHUD.labelText = @"应用ID不能为空";
            mbHUD.customView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"error"]];
            mbHUD.mode = MBProgressHUDModeCustomView;
            mbHUD.removeFromSuperViewOnHide = YES;
            [mbHUD hide:YES afterDelay:0.7];
            
            return;
        } else if (self.theSignServer.text.length == 0) {
            
            MBProgressHUD *mbHUD= [MBProgressHUD showHUDAddedTo:self.view animated:YES];
            mbHUD.labelText = @"签名服务器不能为空";
            mbHUD.customView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"error"]];
            mbHUD.mode = MBProgressHUDModeCustomView;
            mbHUD.removeFromSuperViewOnHide = YES;
            [mbHUD hide:YES afterDelay:0.7];
            
            return;
        }
    }
    
    [self showLoadingAnimated];
    
    if (self.loginMode == AnyChatVCLoginModeGeneralLogin && self.theGuid.text.length != 0) {
        [AnyChatPlatform SetSDKOptionString:BRAC_SO_CLOUD_APPGUID :self.theGuid.text];
    }
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    
    if (self.loginMode == AnyChatVCLoginModeSignLogin && self.theGuid.text.length != 0 && self.theSignServer.text.length != 0) {
        
        
        [self getSignSuccess:^(id json) {
            NSLog(@"sign json:%@",json);

            if ([[json objectForKey:@"errorcode"] intValue] ==0) {
                
                int timestamp = [[json objectForKey:@"timestamp"] intValue];
                NSString *signStr = [json objectForKey:@"sigStr"];
                // dwUserId 如果应用没有此参数，则传入-1(请参考iOS开发手册)
                NSLog(@"===username:%@,guid:%@,timestamp:%d,signStr:%@",self.theUserName.text,self.theGuid.text,timestamp,signStr);
                
                [AnyChatPlatform Connect:self.theServerIP.text : [self.theServerPort.text intValue]];

                [AnyChatPlatform LoginEx:self.theUserName.text :-1 :self.theUserName.text :self.theGuid.text :timestamp :signStr :nil];
                
            }else {
                NSLog(@"Json Error,Error Num:%@",[json objectForKey:@"errorcode"]);
                [self showSignError];
            }
        } failure:^(NSError *error) {
            NSLog(@"Request Error:%@",error);
            [self showSignError];
        }];
    }else if(self.loginMode == AnyChatVCLoginModeGeneralLogin){
        
        [AnyChatPlatform Connect:self.theServerIP.text : [self.theServerPort.text intValue]];

        /*
         * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
         */
        [AnyChatPlatform Login:self.theUserName.text :nil];
    }
    
    
    [self hideKeyBoard];
}

- (void)showSignError
{
    [HUD hide:YES];
    MBProgressHUD *mbHUD= [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    mbHUD.labelText = @"获取签名失败";
    mbHUD.customView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"error"]];
    mbHUD.mode = MBProgressHUDModeCustomView;
    mbHUD.removeFromSuperViewOnHide = YES;
    [mbHUD hide:YES afterDelay:0.7];
}

- (void)getSignSuccess:(void (^)(id))success failure:(void (^)(NSError *))failure{
    
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    //参数请参考签名服务器文档
    // dwUserId 如果应用没有此参数，则传入-1(请参考iOS开发手册)
    NSMutableDictionary *params = [NSMutableDictionary dictionary];
//    params[@"userid"] = [NSNumber numberWithInt:kUserID];
//    params[@"strUserid"] = @"";
    params[@"userid"] = [NSNumber numberWithInt:-1];
    params[@"struserid"] = self.theUserName.text;
    params[@"appid"] = self.theGuid.text;
    
    [manager POST:self.theSignServer.text parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        if (success) success(responseObject);
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        if (failure) failure(error);
    }];
    
}

- (void) OnLogout
{
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    self.theOnLineLoginState = NO;
    [self.onlineUserMArray removeAllObjects];
    [self.onLineUserTableView reloadData];
    self.theStateInfo.text = @"• Logout Server.";
    self.theLoginBtn.selected = NO;
}

- (int)getRandomNumber:(int)from to:(int)to
{
    //  +1,result is [from to]; else is [from, to)!!!!!!!
    return (int)(from + (arc4random() % (to - from + 1)));
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
    self.theRoomNO.text = [NSString stringWithFormat:@"%d",kAnyChatRoomID];
    self.theRoomNO.keyboardType = UIKeyboardTypePhonePad;
    self.theUserName.text = kAnyChatUserName;
    self.theServerIP.text = kAnyChatIP;
    self.theServerPort.text = kAnyChatPort;

    [self.theVersion setText:[AnyChatPlatform GetSDKVersion]];
    [self updateSignUI];

//    UIView *footerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, kSelfView_Width, 70.0f)];
//    onLineUserTableView.tableFooterView = footerView;
    
}

-(IBAction)onRadioBtn:(RadioButton*)sender
{
    if ([sender.titleLabel.text containsString:@"签名登录"]) {
        self.loginMode = AnyChatVCLoginModeSignLogin;
    }else {
        self.loginMode = AnyChatVCLoginModeGeneralLogin;
    }
    [self updateSignUI];
}

- (void)updateSignUI
{
    if(self.loginMode == AnyChatVCLoginModeSignLogin) {
        self.theServerIP.text = kAnyChatSignIP;
        self.theGuid.text = kAnyChatSignGuid;
        self.theSignServer.text = kAnyChatSignServerURL;
    } else {
        self.theServerIP.text = kAnyChatIP;
        self.theGuid.text = @"";
        self.theSignServer.text = @"";
    }
}


-(BOOL)navBarTranslucent {
    
    return YES;
}
@end
