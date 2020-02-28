//
//  UserListVC.m
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "UserListVC.h"

@interface UserListVC ()

@property int myUserID;

@end

@implementation UserListVC



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
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUI];
}

-(void)viewDidDisappear:(BOOL)animated {
    
    [super viewDidDisappear:animated];
    [self.theAudioPlayer pause];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - shared Instance

kGCD_SINGLETON_FOR_CLASS(UserListVC);



#pragma mark --- Table view Delegate (业务核心代码) ----

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
   
    int selectID = [[self.onlineUserMArray objectAtIndex:[indexPath row]] intValue];
    if (selectID != self.myUserID)//非本人
    {
        NSString *selectUserName = [AnyChatPlatform GetUserName:selectID];
        [AnyChatVC sharedAnyChatVC].theTargetUserID = selectID;
        [AnyChatVC sharedAnyChatVC].theTargetUserName = selectUserName;

        if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"呼叫中心"])
        {
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REQUEST :selectID :0 :0 :0 :nil];
            
            self.theWaitingAlertView = [[UIAlertView alloc] initWithTitle:@"呼叫中..."
                                                             message:[[NSString alloc] initWithFormat:@"等待 %@ 回应...",selectUserName]
                                                            delegate:self
                                                   cancelButtonTitle:@"挂断"
                                                   otherButtonTitles:nil, nil];
            [self.theWaitingAlertView show];
            
        } else{
            
            [self.navigationController pushViewController:[self pushVC] animated:YES];
        }
        
    } else{
        
        if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"本地录像"])
        {
            RecordSelfVC *theRecordSelfVC = [RecordSelfVC new];
            [self.navigationController pushViewController:theRecordSelfVC animated:YES];
        }
        else if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"视频抓拍"])
        {
            //拍照最佳像素
            [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_WIDTHCTRL :1280];
            [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_HEIGHTCTRL :720];
            
            AutodyneVC *theAutodyneVC = [AutodyneVC new];
            [self.navigationController pushViewController:theAutodyneVC animated:YES];
        }
    }
}





#pragma mark --- AlertView Delegate (业务：呼叫中心 -->核心代码)---

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
            
            [self.theWaitingAlertView dismissWithClickedButtonIndex:[self.theWaitingAlertView cancelButtonIndex] animated:YES];
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


#pragma mark --- AlertView method ---

- (void) showReplyAlertViewWithName:(NSString *)callbackUserName ID:(int)callbackUserID
{
    self.theReplyAlertView = [[UIAlertView alloc] initWithTitle:@"通话请求"
                                                        message:[[NSString alloc] initWithFormat:@" %@ 请求与你通话",callbackUserName]
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
    self.title = @"在线用户";
    
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

#pragma mark - Table view datasource -

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
        if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"本地录像"])
        {
            nameLabel.text = [name stringByAppendingString:@"[录制自己]"];
        }
        else if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"视频抓拍"])
        {
            nameLabel.text = [name stringByAppendingString:@"[自拍]"];
        }
        else
        {
            nameLabel.text = [name stringByAppendingString:@"(自己)"];
        }
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

- (CGFloat)tableView:(UITableView *)tabelView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
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


- (int)getRandomNumber:(int)from to:(int)to
{
    return (int)(from + (arc4random() % (to - from + 1)));
}

- (void)navLeftClick
{
    [AnyChatPlatform LeaveRoom:-1];
    [[UserListVC sharedUserListVC].onlineUserMArray removeAllObjects];
    [[UserListVC sharedUserListVC].onLineUserTableView reloadData];
    
    [self.navigationController popViewControllerAnimated:YES];
}
@end
