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
@synthesize theLogoutBtn;
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
    self.onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    videoVC = [VideoViewController new];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    
    [theVersion setText:[AnyChatPlatform GetSDKVersion]];
    
    [self prefersStatusBarHidden];
    [self.navigationController setNavigationBarHidden:YES];
    
    float sysVersion = [[UIDevice currentDevice].systemVersion floatValue];
    if (sysVersion < 7.0) {
        
        theLoginBtn.titleLabel.font = [UIFont systemFontOfSize:16.0];
        theLoginBtn.titleLabel.textColor = [UIColor grayColor];
        theLogoutBtn.titleLabel.font = [UIFont systemFontOfSize:16.0];
        theLogoutBtn.titleLabel.textColor = [UIColor grayColor];
        
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }
    
    [theVersion setText:[AnyChatPlatform GetSDKVersion]];
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
    
    if(Cell == nil) {
        Cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
    }
    
    NSInteger userID = [[self.onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    NSString *name = [AnyChatPlatform GetUserName:userID];
    
    Cell.textLabel.text = name;
    Cell.detailTextLabel.text = [NSString stringWithFormat:@"%i",userID];
    
    return Cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int selectID = [[self.onlineUserMArray objectAtIndex:[indexPath row]] integerValue];
    videoVC.iRemoteUserId = selectID;
    [self.navigationController pushViewController:videoVC animated:YES];
}


#pragma mark - AnyChatNotifyMessageDelegate

// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess
{
    if (bSuccess == YES) {
        theStateInfo.text = @"• Connection to server successfully!";
    }
    else
    {
        theStateInfo.text = @"• Connection failed, please try again.";
    }
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode
{
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        if([theRoomNO.text length] == 0)
        {
            theRoomNO.text = @"1";
        }
        [AnyChatPlatform EnterRoom:[theRoomNO.text integerValue] :@""];
    }
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode
{
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
    if (videoVC.iRemoteUserId == dwUserId ) {
        [videoVC StartVideoChat:dwUserId];
    }
    [self.onLineUserTableView reloadData];
}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId
{
    if (videoVC.iRemoteUserId == dwUserId ) {
        [videoVC FinishVideoChat];
    }
    [self.onLineUserTableView reloadData];
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode
{
    [videoVC FinishVideoChat];
    [AnyChatPlatform Logout];
    
    videoVC.iRemoteUserId = -1;
}


#pragma mark - Class method

- (id) GetServerIP
{
    if([theServerIP.text length] == 0)
    {
        theServerIP.text = @"demo.anychat.cn";
    }
    
    return theServerIP.text;
}

- (int) GetServerPort
{
    if([theServerPort.text intValue] == 0 || [theServerPort.text intValue] == 0)
    {
        theServerPort.text = @"8906";
    }
    
    return [theServerPort.text intValue];
}


#pragma mark - Instance method

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

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

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (IBAction) hideKeyBoard:(id)sender
{
    [theUserName resignFirstResponder];
    [theRoomNO resignFirstResponder];
    [theServerIP resignFirstResponder];
    [theServerPort resignFirstResponder];
}

- (IBAction)OnLoginBtnClicked:(id)sender
{
    [AnyChatPlatform Logout];
    
    if([theUserName.text length] == 0)
    {
        theUserName.text = @"HelloAnyChat";
    }
    [AnyChatPlatform Connect:[self GetServerIP] : [self GetServerPort]];
    [AnyChatPlatform Login:theUserName.text : @""];
}

- (IBAction)OnLogoutBtnClicked:(id)sender
{
    [AnyChatPlatform Logout];
    theStateInfo.text = @"• Logout Server.";
    [onlineUserMArray removeAllObjects];
    [self.onLineUserTableView reloadData];
}



#pragma mark - Memory Warning method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

@end
