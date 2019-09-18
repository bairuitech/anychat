//
//  AnyChatViewController.m
//  HelloAnyChat
//
//  Created by AnyChat on 14-9-12.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "AnyChatViewController.h"
#import "textModel/TextModel.h"
#import "textModel/TextModelTool.h"

#define kAnyChatRoomID 1
#define kUserID 1001
#define kAnyChatIP @"demo.anychat.cn"
#define kAnyChatPort @"8906"
#define kAnyChatUserName @"AnyChat"


@interface AnyChatViewController ()<UIGestureRecognizerDelegate>
{
    MBProgressHUD *HUD;
}

@property (strong, nonatomic) AnyChatPlatform               *anyChat;
@property (strong, nonatomic) VideoViewController           *videoVC;

@property (weak, nonatomic) IBOutlet UITextField            *theUserName;
@property (weak, nonatomic) IBOutlet UITextField            *theRoomNO;
@property (weak, nonatomic) IBOutlet UITextField            *theServerIP;
@property (weak, nonatomic) IBOutlet UITextField            *theServerPort;
@property (weak, nonatomic) IBOutlet UIButton               *theLoginBtn;
@property (weak, nonatomic) IBOutlet UILabel                *theStateInfo;
@property (weak, nonatomic) IBOutlet UILabel                *theVersionLab;

@property (strong, nonatomic) IBOutlet UITableView          *onLineUserTableView;

@property BOOL theOnLineLoginState;
@property int theMyUserID;

@end

@implementation AnyChatViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    [AnyChatPlatform InitSDK:0];
    self.anyChat = [AnyChatPlatform getInstance];
    self.anyChat.notifyMsgDelegate = self;
    //创建默认视频参数
    [[SettingVC sharedSettingVC] createObjPlistFileToDocumentsPath];
    [self readSettings];
    [self p_addTapGes];
    
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    [self setUIControls];
}

#pragma mark - ------ 业务核心代码 -------
- (void)AnyChatNotifyHandler:(NSNotification*)notify {
    NSDictionary* dict = notify.userInfo;
    [self.anyChat OnRecvAnyChatNotify:dict];
}

- (void) OnLogin {
    if([self.theUserName.text length] == 0) {
        self.theUserName.text = kAnyChatUserName;
    }
    if([self.theServerIP.text length] == 0) {
        self.theServerIP.text = kAnyChatIP;
    }
    if([self.theServerPort.text length] == 0) {
        self.theServerPort.text = kAnyChatPort;
    }
    
    [self showLoadingAnimated];
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    
    [AnyChatPlatform Connect:self.theServerIP.text : [self.theServerPort.text intValue]];
    
    /*
     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
     */
    [AnyChatPlatform Login:self.theUserName.text :nil];
    [self hideKeyBoard];
}

- (void) OnLogout {
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    self.theOnLineLoginState = NO;
    [self.onlineUserMArray removeAllObjects];
    [self.onLineUserTableView reloadData];
    self.theStateInfo.text = @"• Logout Server.";
    self.theLoginBtn.selected = NO;
}

#pragma mark - AnyChatNotifyMessageDelegate
// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess {
    if (bSuccess)
    {
        self.theStateInfo.text = @"• Success connected to server";
    }else {
        
        self.theStateInfo.text = @"• Fail connected to server";
        [HUD hide:YES];
    }
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode {
    [MBProgressHUD hideHUDForView:self.view animated:YES];
    self.onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    if(dwErrorCode == GV_ERR_SUCCESS) {
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
    } else {
        self.theOnLineLoginState = NO;
        self.theStateInfo.text = [NSString stringWithFormat:@"• Login failed(ErrorCode:%i)",dwErrorCode];
    }
    
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode {
    if (dwErrorCode != 0) {
        self.theStateInfo.text = [NSString stringWithFormat:@"• Enter room failed(ErrorCode:%i)",dwErrorCode];
    }
    [self.onLineUserTableView reloadData];
}

// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId {
    self.onlineUserMArray = [self getOnlineUserArray];
    [self.onLineUserTableView reloadData];
}

// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId {
    self.onlineUserMArray = [self getOnlineUserArray];
    [self.onLineUserTableView reloadData];
}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId {
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

#pragma mark  - Table view data source
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return self.onlineUserMArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *Cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (Cell == nil) {
        NSArray *nibs = [[NSBundle mainBundle] loadNibNamed:@"tableVCell" owner:self options:nil];
        Cell = [nibs objectAtIndex:0];
        [Cell adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
    }
    
    int userID = [[self.onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    NSString *name = [AnyChatPlatform GetUserName:userID];
    UILabel *userIDLabel = (UILabel *)[Cell.contentView viewWithTag:kUserIDValueTag];
    UILabel *nameLabel = (UILabel *)[Cell.contentView viewWithTag:kNameValueTag];
    UIImageView *bgView = (UIImageView *)[Cell viewWithTag:kBackgroundViewTag];
    
    if (self.theMyUserID == userID) {
        nameLabel.text = [name stringByAppendingString:@"(自己)[视频设置]"];
    } else {
        nameLabel.text = name;
    }
    userIDLabel.text = [NSString stringWithFormat:@"%i",userID];
    NSString *RandomNo = [[NSString alloc] initWithFormat:@"%i",[self getRandomNumber:1 to:5]];
    bgView.image = [UIImage imageNamed:RandomNo];
    Cell.selectionStyle = UITableViewCellSelectionStyleDefault;
    return Cell;
}

#pragma mark - Table view delegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    [self hideKeyBoard];
    int selectID = [[self.onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    
    if (selectID != self.theMyUserID) {
        //更新用户自定义视频参数设置
        [[SettingVC sharedSettingVC] updateUserVideoSettings];
        self.videoVC = [VideoViewController new];
        self.videoVC.iRemoteUserId = selectID;
        self.videoVC.remoteUserName = [AnyChatPlatform GetUserName:selectID];
        [self.navigationController pushViewController:self.videoVC animated:YES];
    } else {
        SettingVC *settingVC = [SettingVC new];
        [settingVC readDataWithPList];
        [self.navigationController pushViewController:settingVC animated:YES];
    }
}

- (CGFloat)tableView:(UITableView *)tabelView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return 81.0f;
}

- (NSMutableArray *) getOnlineUserArray {
    NSMutableArray *onLineUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
    [onLineUserList insertObject:[NSString stringWithFormat:@"%i",self.theMyUserID] atIndex:0];
    return onLineUserList;
}

- (void)hideKeyBoard {
    [self.view endEditing:YES];
}

- (IBAction)OnLoginBtnClicked:(id)sender {
    if (self.theOnLineLoginState == YES) {
        [self OnLogout];
    } else {
        [self OnLogin];
    }
}

#pragma mark - Get & Save Settings Method
- (void)saveSettings {
    // save settings to file
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    [[NSArray arrayWithObjects:self.theServerIP.text,self.theServerPort.text,self.theUserName.text,self.theRoomNO.text, nil] writeToFile:filePath atomically:YES];
}

-(void)readSettings {
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    NSArray* settingArray = [NSArray arrayWithContentsOfFile:filePath];
    
    if (settingArray.count >= 4) {
        self.theServerIP.text = settingArray[0];
        self.theServerPort.text = settingArray[1];
        self.theUserName.text = settingArray[2];
        self.theRoomNO.text = settingArray[3];
    }
    else
    {
        self.theUserName.text = kAnyChatUserName;
        self.theServerIP.text = kAnyChatIP;
        self.theServerPort.text = kAnyChatPort;
        self.theRoomNO.text = [NSString stringWithFormat:@"%d",kAnyChatRoomID];
    }
}

- (int)getRandomNumber:(int)from to:(int)to {
    //  +1,result is [from to]; else is [from, to)!!!!!!!
    return (int)(from + (arc4random() % (to - from + 1)));
}

- (void)p_addTapGes {
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(hideKeyBoard)];
    tap.delegate = self;
    [self.view addGestureRecognizer:tap];
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch {
    if ([NSStringFromClass([touch.view class]) isEqualToString:@"UITableViewCellContentView"]) {
        return NO;
    }
    return  YES;
}

#pragma mark - Animation Method
- (void)showLoadingAnimated {
    HUD = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    HUD.labelText = @"HelloAnyChat";
    HUD.detailsLabelText = @"Loading...";
}

#pragma mark - UI Controls
- (void)setUIControls{
    UIView *footerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, kSelfView_Width, 40.0f)];
    self.onLineUserTableView.tableFooterView = footerView;
    self.theVersionLab.text = [AnyChatPlatform GetSDKVersion];
}

-(BOOL)navBarTranslucent {
    return YES;
}

#pragma mark - Rotation
- (BOOL)shouldAutorotate {
    return YES;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations{
    return UIInterfaceOrientationMaskPortrait;
}

@end
