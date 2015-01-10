//
//  UserListVC.m
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "UserListVC.h"

@interface UserListVC ()

@end

@implementation UserListVC

@synthesize myUserID;
@synthesize onLineUserTableView;
@synthesize onlineUserMArray;
@synthesize theReplyAlertView;
@synthesize theRejectAlertView;
@synthesize theWaitingAlertView;
@synthesize theAudioPlayer;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        
    }
    return self;
}


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUI];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - shared Instance

kGCD_SINGLETON_FOR_CLASS(UserListVC);


#pragma mark - Table view datasource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    self.onlineUserMArray = [AnyChatVC sharedAnyChatVC].onlineUserMArray;
    return self.onlineUserMArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    self.onlineUserMArray = [AnyChatVC sharedAnyChatVC].onlineUserMArray;
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *Cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (Cell == nil)
    {
        NSArray *nibs = [[NSBundle mainBundle] loadNibNamed:@"tableVCell" owner:self options:nil];
        Cell = [nibs objectAtIndex:0];
    }
    
    int userID = [[self.onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    NSString *name = [AnyChatPlatform GetUserName:userID];
    
    UILabel *userIDLabel = (UILabel *)[Cell.contentView viewWithTag:kTableVCell_UserIDLabTag];
    UILabel *nameLabel = (UILabel *)[Cell.contentView viewWithTag:kTableVCell_NameLabTag];
    UIImageView *bgView = (UIImageView *)[Cell viewWithTag:kTableVCell_BGViewTag];
    
    if (self.myUserID == userID)
    {
        nameLabel.text = [name stringByAppendingString:@"(自己)"];
    }
    else
    {
        nameLabel.text = name;
    }
    
    userIDLabel.text = [NSString stringWithFormat:@"%i",userID];
    
    NSString *RandomNo = [[NSString alloc] initWithFormat:@"%i",[self getRandomNumber:1 to:5]];
    bgView.image = [UIImage imageNamed:RandomNo];
    
    Cell.selectionStyle = UITableViewCellSelectionStyleBlue;
    
    return Cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int selectID = [[self.onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    
    if (selectID != self.myUserID)
    {
        NSString *selectUserName = [AnyChatPlatform GetUserName:selectID];
        [AnyChatVC sharedAnyChatVC].theTargetUserID = selectID;
        [AnyChatVC sharedAnyChatVC].theTargetUserName = selectUserName;

        if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"呼叫中心"])
        {
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REQUEST :selectID :0 :0 :0 :nil];
            
            theWaitingAlertView = [[UIAlertView alloc] initWithTitle:@"呼叫等待..."
                                                             message:[[NSString alloc] initWithFormat:@"Waiting for %@(%i) response",selectUserName,selectID]
                                                            delegate:self
                                                   cancelButtonTitle:@"取消"
                                                   otherButtonTitles:nil, nil];
            [theWaitingAlertView show];
        }
        else
        {
            [self.navigationController pushViewController:[self pushVC] animated:YES];
        }
    }
}

- (CGFloat)tableView:(UITableView *)tabelView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return 70.0f;
}


#pragma mark - Audio Delegate

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
    [self.theAudioPlayer play];
}

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player
{
    [self.theAudioPlayer play];
}


#pragma mark - AlertView Delegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView == self.theReplyAlertView)
    {
        switch (buttonIndex)
        {
            case 0:
            {
                [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                                 :[AnyChatVC sharedAnyChatVC].theTargetUserID
                                                 :GV_ERR_VIDEOCALL_REJECT
                                                 :0
                                                 :0
                                                 :nil];
                [self.theAudioPlayer stop];
                break;
            }
              
            case 1:
            {
                [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                                 :[AnyChatVC sharedAnyChatVC].theTargetUserID
                                                 :0
                                                 :0
                                                 :0
                                                 :nil];
                break;
            }
        }
        
    }
    
    
    if (alertView == self.theWaitingAlertView) {
        
        if (buttonIndex == 0 )
        {
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                             :[AnyChatVC sharedAnyChatVC].theTargetUserID
                                             :GV_ERR_VIDEOCALL_CANCEL
                                             :0
                                             :0
                                             :nil];
            
            [[AnyChatVC sharedAnyChatVC] dimissAlertView:self.theWaitingAlertView];
            [[UserListVC sharedUserListVC].theAudioPlayer stop];
        }
    }
    
}


#pragma mark -
#pragma mark - Instance Method

- (NSMutableArray *) getOnlineUserArray
{
    NSMutableArray *onLineUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
    [onLineUserList insertObject:[NSString stringWithFormat:@"%i",self.myUserID] atIndex:0];
    return onLineUserList;
}

- (int)getRandomNumber:(int)from to:(int)to
{
    return (int)(from + (arc4random() % (to - from + 1)));
}

- (IBAction)LeaveRoomBtn_OnClick
{
    [AnyChatPlatform LeaveRoom:-1];
    [[UserListVC sharedUserListVC].onlineUserMArray removeAllObjects];
    [[UserListVC sharedUserListVC].onLineUserTableView reloadData];
    
    [self.navigationController popViewControllerAnimated:YES];
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (UIViewController*)pushVC
{
    int featuresNO;
    UIViewController *thePushVC = [UIViewController new];
    featuresNO = [AnyChatVC sharedAnyChatVC].theFeaturesNO;
    
    switch (featuresNO)
    {
        case 1:
        {
            VideoVC *videoVC = [VideoVC new];
            thePushVC = videoVC;
            break;
        }
            
        case 2:
        {
            TextMsg_TransBufferVC *textMsgVC = [TextMsg_TransBufferVC new];
            thePushVC = textMsgVC;
            break;
        }

        case 3:
        {
            TextMsg_TransBufferVC *textMsgVC = [TextMsg_TransBufferVC new];
            thePushVC = textMsgVC;
            break;
        }

        case 4:
        {
            TransFileVC *transFileVC = [TransFileVC new];
            thePushVC = transFileVC;
            break;
        }
            
        case 5:
        {
            RecordLocalVC *recordLocalVC = [RecordLocalVC new];
            thePushVC = recordLocalVC;
            break;
        }
            
        case 6:
        {
            RecordServerVC *recordServerVC = [RecordServerVC new];
            thePushVC = recordServerVC;
            break;
        }
            
        case 7:
        {
            VideoVC *videoVC = [VideoVC new];
            thePushVC = videoVC;
            break;
        }
            
        case 8:
        {
            VideoVC *videoVC = [VideoVC new];
            thePushVC = videoVC;
            break;
        }

    }

    return thePushVC;
}


#pragma mark - AlertView method

- (void) showReplyAlertViewWithName:(NSString *)callbackUserName ID:(int)callbackUserID
{
    self.theReplyAlertView = [[UIAlertView alloc] initWithTitle:@"用户请求会话"
                                                        message:[[NSString alloc] initWithFormat:@"%@(%i) Request to video",callbackUserName,callbackUserID]
                                                       delegate:self
                                              cancelButtonTitle:@"拒绝"
                                              otherButtonTitles:@"同意", nil];
    [self.theReplyAlertView show];
    [self.theAudioPlayer play];
}


#pragma mark - Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark - UI Controls

- (void)setUI
{
    self.myUserID = [AnyChatVC sharedAnyChatVC].theMyUserID;
    self.onlineUserNItem.title = @"在线用户";
    [self prefersStatusBarHidden];
    
    UIView *footerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, kSelfView_Width, 70.0f)];
    self.onLineUserTableView.tableFooterView = footerView;
    
    if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"呼叫中心"])
    {
        [self initWithCallSound];
    }
}

- (void)initWithCallSound
{
    NSString *musicPath = [[NSBundle mainBundle] pathForResource:@"sound_phoneCall"
                                                          ofType:@"wav"];
    if (musicPath)
    {
        NSURL *musicURL = [NSURL fileURLWithPath:musicPath];
        self.theAudioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:musicURL
                                                             error:nil];
        self.theAudioPlayer.delegate = self;
    }
}


@end
