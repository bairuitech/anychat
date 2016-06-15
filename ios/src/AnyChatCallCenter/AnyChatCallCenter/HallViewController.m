//
//  HallViewController.m
//  AnyChatCallCenter
//
//  Created by bairuitech on 14-8-14.
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "HallViewController.h"

// Local Settings Parameter Key Define
NSString* const kUseP2P = @"usep2p";
NSString* const kUseServerParam = @"useserverparam";
NSString* const kVideoSolution = @"videosolution";
NSString* const kVideoFrameRate = @"videoframerate";
NSString* const kVideoBitrate = @"videobitrate";
NSString* const kVideoPreset = @"videopreset";
NSString* const kVideoQuality = @"videoquality";

@interface HallViewController ()

@end

@implementation HallViewController

@synthesize theUserNameHall;
@synthesize theUserPasswordHall;
@synthesize theUserEntity;
@synthesize theUInfo;
@synthesize onlineUserTable;
@synthesize onlineUserMArray;
@synthesize theWaitingAlertView;
@synthesize theReplyAlertView;
@synthesize theRejectAlertView;
@synthesize theStateMsg;
@synthesize videoVC;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
    }
    return self;
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    theAnyChat = [AnyChatPlatform getInstance];
    theAnyChat.userInfoDelegate = self;
    theAnyChat.videoCallDelegate = self;
    theAnyChat.notifyMsgDelegate = self;
    
    [self createTableView];
    theUserEntity = [UserEntity new];
}


#pragma mark - Table view data source
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
    
    UserInfo *tempUserInfo = [self.onlineUserMArray objectAtIndex:[indexPath row]];
    
    Cell.textLabel.text = tempUserInfo.theUserInfoName;
	Cell.textLabel.font = [UIFont systemFontOfSize:19];
	Cell.textLabel.numberOfLines = 1;
    
    Cell.detailTextLabel.text = tempUserInfo.theUserInfoID;
	Cell.detailTextLabel.font = [UIFont systemFontOfSize:13];
	Cell.detailTextLabel.numberOfLines = 1;
    
    UIImage *icon = [UIImage imageNamed:tempUserInfo.theUserInfoIcon];
    
    CGSize iconSize = CGSizeMake(45, 45);
    UIGraphicsBeginImageContextWithOptions(iconSize, NO,0.0);
    CGRect imageRect = CGRectMake(0.0, 0.0, iconSize.width, iconSize.height);
    [icon drawInRect:imageRect];
    
    Cell.imageView.image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return Cell;
}


- (CGFloat)tableView:(UITableView *)tabelView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return 54.0f;
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int selectID = [[[self.onlineUserMArray objectAtIndex:[indexPath row]] theUserInfoID] intValue];
    
    [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REQUEST :selectID :0 :0 :0 :nil];
    
    theWaitingAlertView = [[UIAlertView alloc] initWithTitle:@"呼叫等待..." message:@"Call waiting" delegate:self cancelButtonTitle:@"取消" otherButtonTitles:nil, nil];
    [theWaitingAlertView show];
}


#pragma mark - AnyChatCallDelegate

- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr{
    
    theUserEntity.theEntityRemoteID = dwUserId;
    
    switch (dwEventType) {
            
        case BRAC_VIDEOCALL_EVENT_REQUEST:
        {
            [self showReplyAlertView];
            break;
        }
            
            
        case BRAC_VIDEOCALL_EVENT_REPLY:
        {
            switch (dwErrorCode)
            {
                case GV_ERR_VIDEOCALL_CANCEL:
                {
                    [self dimissAlertView:theReplyAlertView];
                    [self showInfoAlertView:@"用户取消会话" :@"CANCEL"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_REJECT:
                {
                    if (theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:theWaitingAlertView];
                    }
                    
                    [self showInfoAlertView:@"用户拒绝会话" :@"REJECT"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_OFFLINE:
                {
                    if (theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"对方不在线" :@"OFFLINE"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_BUSY:
                {
                    if (theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"用户在忙" :@"BUSY"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_TIMEOUT:
                {
                    if (theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"会话请求超时" :@"TIMEOUT"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_DISCONNECT:
                {
                    if (theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"网络断线" :@"DISCONNECT"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_NOTINCALL:
                {
                    if (theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"用户不在呼叫状态" :@"NOTINCALL"];
                    
                    break;
                }
                    
            }
            
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_START:
        {
            if (theWaitingAlertView != nil) {
                [self dimissAlertView:theWaitingAlertView];
            }
            
            [AnyChatPlatform EnterRoom:dwParam :@""];
            
            break;
        }
            
            
        case BRAC_VIDEOCALL_EVENT_FINISH:
        {
            [videoVC FinishVideoChat];
            [AnyChatPlatform LeaveRoom:-1];
            [self showInfoAlertView:@"会话结束!" :@"Finish"];
            
            [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:1]
                                                  animated:YES];
            break;
        }
            
            
    }
    
}


#pragma mark - AlertView Delegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    
    
    if (alertView == theReplyAlertView) {
        
        switch (buttonIndex) {
                
            case 0:
            {
                [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                                 :theUserEntity.theEntityRemoteID
                                                 :GV_ERR_VIDEOCALL_REJECT
                                                 :0
                                                 :0
                                                 :nil];
                break;
            }
                
                
            case 1:
            {
                [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                                 :theUserEntity.theEntityRemoteID
                                                 :0
                                                 :0
                                                 :0
                                                 :nil];
                break;
            }
                
        }
        
    }
    
    
    if (alertView == theWaitingAlertView) {
        
        if (buttonIndex == 0 ) {
            
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                             :theUserEntity.theEntityRemoteID
                                             :GV_ERR_VIDEOCALL_CANCEL
                                             :0
                                             :0
                                             :nil];
            
            [self dimissAlertView:theWaitingAlertView];
            
        }
    }
    
    
}


#pragma mark - AnyChatNotifyMessageDelegate

// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess
{
    
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode
{
    self.onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        [self updateLocalSettings];
        
        UIView *headerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 54.0f)];
        UIView *footerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 54.0f)];
        [self setUserInfoFromHeaderView:headerView :dwUserId];
        onlineUserTable.tableHeaderView = headerView;
        onlineUserTable.tableFooterView = footerView;
    }
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode
{
    
}

// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId
{
    videoVC = [VideoViewController new];
    videoVC.theUserEntity = theUserEntity;
    [self.navigationController pushViewController:videoVC animated:YES];
}

// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId
{
    if (theUserEntity.theEntityRemoteID == dwUserId ) {
        [videoVC StartVideoChat:dwUserId];
    }
}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId
{
    if (theUserEntity.theEntityRemoteID == dwUserId ) {
        [videoVC FinishVideoChat];
    }
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode
{
    [videoVC FinishVideoChat];
    [AnyChatPlatform Logout];
}


#pragma mark - AnyChatUserInfoDelegate


- (void) OnAnyChatUserInfoUpdate:(int) dwUserId : (int) dwType
{
    self.onlineUserMArray = [self getOnlineUserArray];
    [self refreshTableView];
}

- (void) OnAnyChatFriendStatus:(int) dwUserId : (int) dwStatus{
    
    NSString *userID = [[NSString alloc] initWithFormat:@"%i",dwUserId];
    NSString *userName = [AnyChatPlatform GetUserName:dwUserId];
    NSString *offLineTitle = [NSString stringWithFormat:@"%@(%@) Off-line",userName,userID];
    
    if( dwStatus == 0 )
    {
        [self.view makeToast:offLineTitle];
        
        for (int i=0; self.onlineUserMArray.count > i ; i++)
        {
            UserInfo *userInfo = [self.onlineUserMArray objectAtIndex:i];
            
            NSString *theUserInfoID =userInfo.theUserInfoID;
            BOOL isE = [theUserInfoID isEqualToString:userID];
            
            if ( isE == YES ) {
                [self.onlineUserMArray removeObjectAtIndex:i];
            }
        }
    }
    
    [self refreshTableView];
    
}


#pragma mark - AlertView method


- (void) dimissAlertView:(UIAlertView *)alert {
    if(alert){
        [alert dismissWithClickedButtonIndex:[alert cancelButtonIndex] animated:YES];
    }
}


- (void) showReplyAlertView{
    theReplyAlertView = [[UIAlertView alloc] initWithTitle:@"用户请求会话"
                                                   message:@"Video Call"
                                                  delegate:self
                                         cancelButtonTitle:@"拒绝"
                                         otherButtonTitles:@"同意", nil];
    [theReplyAlertView show];
}


- (NSString *)showInfoAlertView:(NSString *)titleCN : (NSString *)titleEN{
    
    theStateMsg = titleEN;
    
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:titleCN
                                                        message:titleEN
                                                       delegate:self
                                              cancelButtonTitle:nil
                                              otherButtonTitles:nil,nil];
    [alertView show];
    
    [self performSelector:@selector(dimissAlertView:) withObject:alertView afterDelay:1.5];
    
    return theStateMsg;
    
}


#pragma mark - Instance Method

- (void)AnyChatNotifyHandler:(NSNotification*)notify
{
    NSDictionary* dict = notify.userInfo;
    [theAnyChat OnRecvAnyChatNotify:dict];
}

- (void)createTableView
{    
    onlineUserTable = [[UITableView alloc] initWithFrame:CGRectMake(0, 46, self.view.frame.size.width, self.view.frame.size.height)];
    
    self.onlineUserTable.delegate = self;
    self.onlineUserTable.dataSource = self;
    
    [self.view addSubview:onlineUserTable];
}

- (void) refreshTableView
{
    [self.onlineUserTable reloadData];
}

- (int)getRandomNumber:(int)from to:(int)to
{
    //  +1,result is [from to]; else is [from, to)!!!!!!!
    return (int)(from + (arc4random() % (to - from + 1)));
}

- (NSMutableArray *) getOnlineUserArray{
    
    NSMutableArray *onLineUserList = [NSMutableArray new];
    NSMutableArray *allUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetUserFriends]];
    
    for (NSString *userID in allUserList) {

        if ([AnyChatPlatform GetFriendStatus:[userID intValue]] == 1) {
            
            theUInfo = [UserInfo new];
            
            theUInfo.theUserInfoName = [AnyChatPlatform GetUserName:[userID intValue]];
            theUInfo.theUserInfoID = [[NSString alloc] initWithFormat:@"%@",userID];
            theUInfo.theUserInfoIcon = [[NSString alloc] initWithFormat:@"%i",[self getRandomNumber:1 to:9]];
            
            if ([onLineUserList containsObject:theUInfo.theUserInfoID] == NO) {
                [onLineUserList addObject:theUInfo];
            }
        }
    }
    
    
    return onLineUserList;
}


- (void) getOnlineUserList:(NSMutableArray *)onlineUList{
    self.onlineUserMArray = onlineUList;
}


- (BOOL)prefersStatusBarHidden{
    return YES;
}


- (IBAction)leaveLoginBtnClicked:(id)sender {
    
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    [self.navigationController popToRootViewControllerAnimated:YES];
}

- (void) setUserInfoFromHeaderView:(UIView *)headerView : (int) dwUserId
{
    UILabel *selfName = [[UILabel alloc] initWithFrame:CGRectMake(75, 8, 200, 25)];
    selfName.text = [AnyChatPlatform GetUserName:dwUserId];
    selfName.font = [UIFont systemFontOfSize:19];
    [headerView addSubview:selfName];
    
    UILabel *selfID = [[UILabel alloc] initWithFrame:CGRectMake(75, 27, 200, 25)];
    selfID.text = [[NSString alloc] initWithFormat:@"%i",dwUserId];
    selfID.font = [UIFont systemFontOfSize:13];
    [headerView addSubview:selfID];
    
    NSString *selfIconStr = [[NSString alloc] initWithFormat:@"%i",[self getRandomNumber:1 to:9]];
    UIImage *selfIconImg = [UIImage imageNamed:selfIconStr];
    UIImageView *selfIconImgV = [[UIImageView alloc] initWithImage:selfIconImg];
    selfIconImgV.frame =CGRectMake(15, 5, 45, 45);
    [headerView addSubview:selfIconImgV];
    
    UIView *lineV = [[UIView alloc] initWithFrame:CGRectMake(75, 53, self.view.frame.size.width - 75, 1.0f)];
    lineV.backgroundColor = [UIColor colorWithRed:220.0/255.0 green:220.0/255.0 blue:223.0/255.0 alpha:1.0];
    [headerView addSubview:lineV];
}


#pragma mark - Video Setting
// 更新本地参数设置
- (void) updateLocalSettings
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults synchronize];
    
    BOOL bUseP2P = [[defaults objectForKey:kUseP2P] boolValue];
    BOOL bUseServerVideoParam = [[defaults objectForKey:kUseServerParam] boolValue];
    int iVideoSolution =    [[defaults objectForKey:kVideoSolution] intValue];
    int iVideoBitrate =     [[defaults objectForKey:kVideoBitrate] intValue];
    int iVideoFrameRate =   [[defaults objectForKey:kVideoFrameRate] intValue];
    int iVideoPreset =      [[defaults objectForKey:kVideoPreset] intValue];
    int iVideoQuality =     [[defaults objectForKey:kVideoQuality] intValue];
    
    // P2P
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_NETWORK_P2PPOLITIC : (bUseP2P ? 1 : 0)];
    
    if(bUseServerVideoParam)
    {
        // 屏蔽本地参数，采用服务器视频参数设置
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_APPLYPARAM :0];
    }
    else
    {
        int iWidth, iHeight;
        switch (iVideoSolution) {
            case 0:     iWidth = 1280;  iHeight = 720;  break;
            case 1:     iWidth = 640;   iHeight = 480;  break;
            case 2:     iWidth = 480;   iHeight = 360;  break;
            case 3:     iWidth = 352;   iHeight = 288;  break;
            case 4:     iWidth = 192;   iHeight = 144;  break;
            default:    iWidth = 352;   iHeight = 288;  break;
        }
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_WIDTHCTRL :iWidth];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_HEIGHTCTRL :iHeight];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_BITRATECTRL :iVideoBitrate];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_FPSCTRL :iVideoFrameRate];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_PRESETCTRL :iVideoPreset];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_QUALITYCTRL :iVideoQuality];
        
        // 采用本地视频参数设置，使参数设置生效
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_APPLYPARAM :1];
    }
    
}


#pragma mark - Memory Warning

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
