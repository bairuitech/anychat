//
//  AnyChatViewController.m
//  helloAnyChat
//
//  Created by AnyChat on 14-9-12.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "AnyChatViewController.h"

@interface AnyChatViewController ()

@end

@implementation AnyChatViewController

@synthesize onLineUserTableView;
@synthesize onlineUserMArray;
@synthesize anyChat;
@synthesize videoVC;
@synthesize theVersion;
@synthesize theStateInfo;
@synthesize theRoomNO;
@synthesize theUserName;
@synthesize theServerIP;
@synthesize theServerPort;
@synthesize theLoginBtn;
@synthesize onLoginState;
@synthesize theLoginAlertView;
@synthesize theHideKeyboardBtn;




- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    anyChat = [[AnyChatPlatform alloc] init];
    anyChat.notifyMsgDelegate = self;
    
    [AnyChatPlatform InitSDK:0];
    
//    [self createTableView];
    onLoginState = NO;
}


- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    [self setUIControls];
}


#pragma mark - Rotation

- (BOOL)shouldAutorotate {
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
    
    NSInteger userID = [[onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    NSString *name = [AnyChatPlatform GetUserName:userID];
    
    UILabel *userIDLabel = (UILabel *)[Cell.contentView viewWithTag:kUserIDValueTag];
    UILabel *nameLabel = (UILabel *)[Cell.contentView viewWithTag:kNameValueTag];
    UIImageView *bgView = (UIImageView *)[Cell viewWithTag:kBackgroundViewTag];
    
    nameLabel.text = name;
    userIDLabel.text = [NSString stringWithFormat:@"%i",userID];
    
    NSString *RandomNo = [[NSString alloc] initWithFormat:@"%i",[self getRandomNumber:1 to:5]];
    bgView.image = [UIImage imageNamed:RandomNo];
    
    Cell.selectionStyle = UITableViewCellSelectionStyleNone;
    
    return Cell;
}



#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int selectID = [[onlineUserMArray objectAtIndex:[indexPath row]] integerValue];
    
    videoVC = [VideoViewController new];
    videoVC.iRemoteUserId = selectID;
    [self.navigationController pushViewController:videoVC animated:YES];
}

- (CGFloat)tableView:(UITableView *)tabelView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return 70.0f;
}


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
        theStateInfo.text = @"• Successful connection";
    }
    else
    {
        theStateInfo.text = @"• Connection failed";
    }
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode
{
    onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        onLoginState = YES;
        theStateInfo.text = [NSString stringWithFormat:@" Login successful. Self userid:%d", dwUserId];

        [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_logout_01"] forState:UIControlStateNormal];
        
        if([theRoomNO.text length] == 0)
        {
            theRoomNO.text = @"1";
        }
        [AnyChatPlatform EnterRoom:[theRoomNO.text integerValue] :@""];
    }
    else
    {
        onLoginState = NO;
        theStateInfo.text = [NSString stringWithFormat:@"• Login failed(ErrorCode:%i)",dwErrorCode];
    }
    
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode
{
    if (dwErrorCode != 0)
    {
        theStateInfo.text = [NSString stringWithFormat:@"• Enter room failed(ErrorCode:%i)",dwErrorCode];
    }
    else
    {
        [self dimissAlertView:theLoginAlertView];
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
    if (videoVC.iRemoteUserId == -1 ) {
        videoVC.iRemoteUserId = dwUserId;
        [videoVC StartVideoChat:dwUserId];
    }
    onlineUserMArray = [self getOnlineUserArray];
    [onLineUserTableView reloadData];
}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId
{
    if (videoVC.iRemoteUserId == dwUserId ) {
        [videoVC FinishVideoChat];
    }
    onlineUserMArray = [self getOnlineUserArray];
    [onLineUserTableView reloadData];
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode
{
    [videoVC FinishVideoChat];
    [AnyChatPlatform Logout];
    
    videoVC.iRemoteUserId = -1;
    
    theStateInfo.text = [NSString stringWithFormat:@"• AnyChat Link Close(ErrorCode:%i)",dwErrorCode];
}


#pragma mark - Class Method

- (id) GetServerIP
{
    NSString* serverIP;
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    if([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
        NSMutableArray* array = [[NSMutableArray alloc]initWithContentsOfFile:filePath];
        serverIP =  [array objectAtIndex:0];
        
        if([serverIP length] == 0)
            theServerIP.text = @"demo.anychat.cn";
            serverIP = theServerIP.text;
    }
    else
    {
        theServerIP.text = @"demo.anychat.cn";
        serverIP = theServerIP.text;
    }
    return serverIP;
}

- (int) GetServerPort
{
    NSString* serverPort;
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    if([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
        NSMutableArray* array = [[NSMutableArray alloc]initWithContentsOfFile:filePath];
        serverPort = [array objectAtIndex:1];
        
        if([serverPort intValue] == 0 || [serverPort intValue] == 0)
            theServerPort.text = @"8906";
            serverPort = theServerPort.text;
    }
    else
    {
        theServerPort.text = @"8906";
        serverPort = theServerPort.text;
    }
    return [serverPort intValue];
}


#pragma mark - AlertView method

- (void) dimissAlertView:(UIAlertView *)alert
{
    if(alert){
        [alert dismissWithClickedButtonIndex:[alert cancelButtonIndex] animated:YES];
    }
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
    return onLineUserList;
}

- (IBAction)hideKeyBoard
{
    [theServerIP resignFirstResponder];
    [theServerPort resignFirstResponder];
    [theUserName resignFirstResponder];
    [theRoomNO resignFirstResponder];
}

- (IBAction)OnLoginBtnClicked:(id)sender
{
    if (onLoginState == YES)
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
    [self hideKeyBoard];
    
    if (onLoginState == NO)
    {
        theLoginAlertView = [[UIAlertView alloc] initWithTitle:@"Log in, please wait."
                                                       message:@"HelloAnyChat loading..."
                                                      delegate:self
                                             cancelButtonTitle:nil
                                             otherButtonTitles:nil,nil];
        [theLoginAlertView show];
        
        if([theUserName.text length] == 0)
        {
            theUserName.text = @"HelloAnyChat";
        }
        [AnyChatPlatform Connect:[self GetServerIP] : [self GetServerPort]];
        [AnyChatPlatform Login:theUserName.text : @""];
    }
    
}

- (void) OnLogout
{
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    onLoginState = NO;
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

#pragma mark - Memory Warning Method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - Animation Method

- (void) transitionAnimationWithInstance:(id)instanceLayer
{
    CATransition *transition = [CATransition animation];
    transition.delegate = self;
    transition.duration = 0.5;
    transition.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    transition.type = kCATransitionFade;
    
    [instanceLayer addAnimation:transition forKey:@"transitionAnimation"];
}


#pragma mark - UI Controls

- (void)setUIControls
{
    [self.navigationController setNavigationBarHidden:YES];
    
    [theServerIP addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theServerPort addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theUserName addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theRoomNO addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    
    if ([[UIDevice currentDevice].systemVersion floatValue] < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }

    if ([UIScreen mainScreen].bounds.size.height == 480.0f || [UIScreen mainScreen].bounds.size.height == 960.0f)
    {
        onLineUserTableView.frame = CGRectMake(0, 240, 320, 210);
    }
    else if ([UIScreen mainScreen].bounds.size.height == 568.0f || [UIScreen mainScreen].bounds.size.height == 1136.0f)
    {
        onLineUserTableView.frame = CGRectMake(0, 258, 320, 280);
    }
    
    [theVersion setText:[AnyChatPlatform GetSDKVersion]];
    [self prefersStatusBarHidden];
    
}

- (void)saveSettings
{   // save settings to file
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    [[NSArray arrayWithObjects:theUserName.text,theRoomNO.text,theServerIP.text,theServerPort.text, nil] writeToFile:filePath atomically:YES];
}


@end
