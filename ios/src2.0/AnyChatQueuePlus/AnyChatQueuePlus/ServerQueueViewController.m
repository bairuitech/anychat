//
//  ServerQueueViewController.m
//  AnyChatQueue
//
//  Created by tim.tan on 15/6/25.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "ServerQueueViewController.h"
#import "Business.h"
#import "LoginViewController.h"
#import "BusinessListAgentCell.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>
#import "MBProgressHUD+JT.h"
#import <AVFoundation/AVFoundation.h>

@interface ServerQueueViewController ()<UITableViewDataSource,UITableViewDelegate,AnyChatVideoCallDelegate,UIActionSheetDelegate,UIAlertViewDelegate>
@property(strong, nonatomic) AnyChatPlatform *anyChat;          //anyChat对象
@property(weak, nonatomic) LoginViewController *loginVC;
@property(nonatomic, strong)NSArray *businesses;
@property(nonatomic, assign)int remoteUserId;

@property(nonatomic, strong)UIAlertView *requestAlertView;
@property(nonatomic, strong) AVAudioPlayer *theAudioPlayer;             // 音乐播放器

- (IBAction)startServerClick:(UIButton *)sender;
@property (weak, nonatomic) IBOutlet UIButton *StartServerBtn;

@end

@implementation ServerQueueViewController
// 懒加载
- (NSArray *)businesses {
    if (_businesses == nil) {
        NSMutableArray *businessesObjArr = [NSMutableArray array];
        for (NSString *businessId in self.businessListIdArray) {
            //获取队列名称
            NSString *businessName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_QUEUE :[businessId intValue] :ANYCHAT_OBJECT_INFO_NAME];
            NSDictionary *dic = [[NSDictionary alloc] initWithObjectsAndKeys:businessName,@"title", businessId,@"id",nil];
            Business *business = [Business businessWithDic:dic];
            [businessesObjArr addObject:business];
        }
        _businesses = businessesObjArr;
    }
    return _businesses;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.loginVC = [self.navigationController.viewControllers objectAtIndex:0];
    self.anyChat = [AnyChatPlatform getInstance];//self.loginVC.anyChat;
    self.anyChat.videoCallDelegate = self;
    
    self.navigationItem.title = @"队列列表";
    self.tableView.rowHeight = 70;
    [self.tableView registerNib:[UINib nibWithNibName:@"BusinessListAgentCell" bundle:nil] forCellReuseIdentifier:@"agent"];

    self.StartServerBtn.layer.masksToBounds = YES;
    self.StartServerBtn.layer.cornerRadius = 15;
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    self.navigationController.navigationBarHidden = NO;
}

-(void)viewDidDisappear:(BOOL)animated {
    
    [super viewDidDisappear:animated];
    [self.theAudioPlayer stop];
    [self.requestAlertView dismissWithClickedButtonIndex:[self.requestAlertView cancelButtonIndex] animated:YES];
}
#pragma mark - AnyChat Call Delegate
- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr{
    
    self.remoteUserId = dwUserId;
    switch (dwEventType) {
            
        case BRAC_VIDEOCALL_EVENT_REQUEST://呼叫请求 1
        {
            NSLog(@"BRAC_VIDEOCALL_EVENT_REQUEST");
            self.remoteUserId = dwUserId;
            self.loginVC.customerId = dwUserId;
            
            NSString *serviceName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_CLIENTUSER :dwUserId :ANYCHAT_OBJECT_INFO_NAME];
            self.requestAlertView = [[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"用户 %@请求与您视频通话，是否接受?",serviceName] message:nil delegate:self cancelButtonTitle:nil otherButtonTitles:@"接受",@"拒绝" ,nil];
            self.requestAlertView.delegate = self;
            [self.requestAlertView show];
            
            if(!self.theAudioPlayer) {

                [self setVoice];
            }
            [self.theAudioPlayer play];
            
            break;
            
        }
            
        case BRAC_VIDEOCALL_EVENT_REPLY:// 呼叫请求回复 2
        {
            switch (dwErrorCode)
            {
                case GV_ERR_VIDEOCALL_CANCEL: // 源用户主动放弃会话
                {
                    if (self.waitingAlertView != nil)
                        [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    
                    if(self.requestAlertView!=nil)
                        [self.requestAlertView dismissWithClickedButtonIndex:self.requestAlertView.cancelButtonIndex animated:YES];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_REJECT: // 目标用户拒绝会话
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"顾客拒绝视频通话"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_OFFLINE:// 目标用户不在线
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"顾客不在线"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_BUSY:// 目标用户忙
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"顾客忙"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_TIMEOUT:// 会话请求超时
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"请求超时"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_DISCONNECT:// 网络断线
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"网络断线"];
                    
                    break;
                }
                    
                    
                case GV_ERR_VIDEOCALL_NOTINCALL:// 用户不在呼叫状态
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"顾客不在呼叫状态"];
                    
                    break;
                }
                    
            }
            
            //结束服务
            [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT :self.selfUserId :ANYCHAT_AGENT_CTRL_FINISHSERVICE :0 :0 :0 :0 :nil];
            
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_START://用户同意，视频开始 3
        {
            if (self.waitingAlertView != nil) {
                [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
            }
            //进入房间
            [AnyChatPlatform EnterRoom:dwParam :nil];
            
            break;
        }
            
            
        case BRAC_VIDEOCALL_EVENT_FINISH://视频结束 4
        {
            // 结束服务
            [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT :self.selfUserId :ANYCHAT_AGENT_CTRL_FINISHSERVICE :0 :0 :0 :0 :nil];
            // 关闭设备
            [AnyChatPlatform UserSpeakControl: -1 : NO];
            [AnyChatPlatform UserCameraControl: -1 : NO];
            [AnyChatPlatform UserSpeakControl: dwUserId : NO];
            [AnyChatPlatform UserCameraControl: dwUserId : NO];
            // 离开房间
            [AnyChatPlatform LeaveRoom:-1];
            [MBProgressHUD showSuccess:@"视频通话结束"];
            [self.navigationController popViewControllerAnimated:YES];
            break;
        }
            
            
    }
    
}

- (void)onAgentStatusChanged:(NSDictionary *)data {
    NSLog(@"坐席状态发生改变");
    NSString *status = data[@"status"];
    if ([status isEqualToString:@"0"]) {
        
        [self.StartServerBtn setTitle:@"已关闭" forState:UIControlStateNormal];
        
    }else if ([status isEqualToString:@"1"]) {
        
        [self.StartServerBtn setTitle:@"等待服务中" forState:UIControlStateNormal];
        
    }else if ([status isEqualToString:@"2"]) {
        
        [self.StartServerBtn setTitle:@"忙碌中" forState:UIControlStateNormal];
        
    }else if ([status isEqualToString:@"3"]) {
        
        [self.StartServerBtn setTitle:@"暂停服务" forState:UIControlStateNormal];
        
    }else if ([status isEqualToString:@"10"]) {
        
        [self.StartServerBtn setTitle:@"离线" forState:UIControlStateNormal];
    }
}



#pragma mark - TableView Delegate
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.businesses.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    
    BusinessListAgentCell *cell = [tableView dequeueReusableCellWithIdentifier:@"agent"];
    Business *business = self.businesses[indexPath.row];
    cell.queueNameLab.text =  business.title;
    int queueId = [self.businessListIdArray[indexPath.row] intValue];
    int queuePeopleCount = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :queueId :ANYCHAT_QUEUE_INFO_QUEUELENGTH];
    cell.queueCountLab.text = [NSString stringWithFormat:@"%d 人",queuePeopleCount];
    return cell;
//    static NSString *cellID = @"cell";
//    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellID];
//    if (cell == nil) {
//        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:cellID];
//    }
//    Business *business = self.businesses[indexPath.row];
//    cell.textLabel.text =  business.title;
//    int queueId = [self.businessListIdArray[indexPath.row] intValue];
//    int queuePeopleCount = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :queueId :ANYCHAT_QUEUE_INFO_QUEUELENGTH];
//    cell.detailTextLabel.text = [NSString stringWithFormat:@"有%d人在排队",queuePeopleCount];
//    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];// 取消选中这行
}

#pragma mark - UIActionSheetDelegate
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {
        // 退出营业厅
        [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AREA :self.businessHallId :ANYCHAT_AREA_CTRL_USERLEAVE :0 :0 :0 :0 :nil];
        [self.navigationController popViewControllerAnimated:YES];
    }
}

#pragma mark - UIAlertViewDelegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (alertView == self.waitingAlertView) {
        if (buttonIndex == 0 ) {// 自己主动取消呼叫
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                             :self.remoteUserId
                                             :GV_ERR_VIDEOCALL_CANCEL
                                             :0
                                             :0
                                             :nil];
        }
    }
    else if(alertView == self.requestAlertView)
    {
        if (buttonIndex == 0) { //同意
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :0 :0 :0 :nil];
        }else { //拒绝
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :GV_ERR_VIDEOCALL_REJECT :0 :0 :nil];
            //然后结束本次服务
            [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT :self.selfUserId :ANYCHAT_AGENT_CTRL_FINISHSERVICE :0 :0 :0 :0 :nil];
            
        }
        [self.theAudioPlayer stop];
        
    }
}
#pragma mark - Action
- (IBAction)startServerClick:(UIButton *)sender {
    // 开始服务
    [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT :self.selfUserId :ANYCHAT_AGENT_CTRL_SERVICEREQUEST :0 :0 :0 :0 :nil];
}
- (void)navLeftClick {
    
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"您确定退出坐席服务区吗？" delegate:self cancelButtonTitle:@"取消" destructiveButtonTitle:@"确定" otherButtonTitles:nil, nil];
    actionSheet.delegate = self;
    [actionSheet showInView:self.view];
}


- (void)setVoice {
    NSString *musicPath = [[NSBundle mainBundle] pathForResource:@"sound_phoneCall" ofType:@"wav"];
    if (musicPath) {
        NSURL *musicURL = [NSURL fileURLWithPath:musicPath];
        self.theAudioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:musicURL
                                                                     error:nil];
    }
}

#pragma mark - Memory
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
