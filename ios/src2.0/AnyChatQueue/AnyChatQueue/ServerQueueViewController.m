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
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>
#import "MBProgressHUD+JT.h"
#import "AnyChat_QueueModel.h"
#import <AVFoundation/AVFoundation.h>

@interface ServerQueueViewController ()<UITableViewDataSource, UITableViewDelegate, AnyChatVideoCallDelegate, UIActionSheetDelegate, UIAlertViewDelegate, AVAudioPlayerDelegate>

@property(strong, nonatomic) AnyChatPlatform *anyChat;//anyChat对象
@property(weak, nonatomic) LoginViewController *loginVC;
@property(nonatomic, strong) AVAudioPlayer *theAudioPlayer;// 音乐播放器
@property(nonatomic, assign)int remoteUserId;

- (IBAction)startServerClick:(UIButton *)sender;
@property (weak, nonatomic) IBOutlet UIButton *StartServerBtn;

@end

@implementation ServerQueueViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.loginVC = [self.navigationController.viewControllers objectAtIndex:0];
    self.anyChat = [AnyChatPlatform getInstance];//self.loginVC.anyChat;
    self.anyChat.videoCallDelegate = self;
    
    self.navigationItem.title = @"队列列表";
    self.tableView.rowHeight = 50;
    self.tableView.tableFooterView = [UIView new];
    
    // 添加退出按钮
    [self setupBackButton];
    [self setVoice];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    self.navigationController.navigationBarHidden = NO;
    [self.navigationController.navigationBar setBackgroundImage:nil forBarMetrics:UIBarMetricsDefault];
    [self.navigationController.navigationBar setShadowImage:nil];

}


#pragma mark - AnyChat Call Delegate
- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr{
    
    self.remoteUserId = dwUserId;
    [AnyChatQueueDataManager getInstance].customerId = dwUserId;
    
    switch (dwEventType) {
        case BRAC_VIDEOCALL_EVENT_REQUEST://呼叫请求 1
        {
            NSString *userName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_CLIENTUSER :dwUserId :ANYCHAT_OBJECT_INFO_NAME];
            NSString *message = [NSString stringWithFormat:@"客户%@请求与您视频通话，是否接受？", userName];
            self.waitingAlertView = [[UIAlertView alloc] initWithTitle:@"来电中..." message:message delegate:self cancelButtonTitle:nil otherButtonTitles:@"接受",@"拒绝" ,nil];
            self.waitingAlertView.delegate = self;
            [self.waitingAlertView show];
            [self.theAudioPlayer play];
            
            break;
        }
        case BRAC_VIDEOCALL_EVENT_REPLY:// 呼叫请求回复 2
        {
            if (dwErrorCode) {
                [self hideWaitingAlertView];
            }
            switch (dwErrorCode)
            {
                case GV_ERR_VIDEOCALL_CANCEL: // 源用户主动放弃会话
                {
                    [MBProgressHUD showError:@"顾客取消会话"];
                    break;
                }
                case GV_ERR_VIDEOCALL_REJECT: // 目标用户拒绝会话
                {
                    [MBProgressHUD showError:@"顾客拒绝视频通话"];
                    break;
                }
                case GV_ERR_VIDEOCALL_OFFLINE:// 目标用户不在线
                {
                    [MBProgressHUD showError:@"顾客不在线"];
                    break;
                }
                case GV_ERR_VIDEOCALL_BUSY:// 目标用户忙
                {
                    [MBProgressHUD showError:@"顾客忙"];
                    break;
                }
                case GV_ERR_VIDEOCALL_TIMEOUT:// 会话请求超时
                {
                    [MBProgressHUD showError:@"请求超时"];
                    break;
                }
                case GV_ERR_VIDEOCALL_DISCONNECT:// 网络断线
                {
                    [MBProgressHUD showError:@"网络断线"];
                    break;
                }
                case GV_ERR_VIDEOCALL_NOTINCALL:// 用户不在呼叫状态
                {
                    [MBProgressHUD showError:@"顾客不在呼叫状态"];
                    break;
                }
            }
            [[AnyChatQueueDataManager getInstance].queueModel agentServiceCtrlWithCtrlCode:BRAC_AGENT_SERVICE_FINISHSERVICE];
            [[AnyChatQueueDataManager getInstance].queueModel agentServiceCtrlWithCtrlCode:BRAC_AGENT_SERVICE_WAITTING];
            break;
        }
        case BRAC_VIDEOCALL_EVENT_START://用户同意，视频开始 3
        {
            [self hideWaitingAlertView];
            [MBProgressHUD showMessage:@"正在进入房间，请稍等..."];
            //进入房间
            [AnyChatPlatform EnterRoom:dwParam :nil];
            [self.theAudioPlayer stop];
            break;
        }
        case BRAC_VIDEOCALL_EVENT_FINISH://视频结束 4
        {
            // 结束服务
            [[AnyChatQueueDataManager getInstance].queueModel agentServiceCtrlWithCtrlCode:BRAC_AGENT_SERVICE_FINISHSERVICE];
            [[AnyChatQueueDataManager getInstance].queueModel agentServiceCtrlWithCtrlCode:BRAC_AGENT_SERVICE_WAITTING];
            
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

#pragma mark - TableView Delegate
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.businesses.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellID = @"cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellID];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:cellID];
    }
    Business *business = self.businesses[indexPath.row];
    cell.textLabel.text =  business.title;
    int queuePeopleCount = [[AnyChatQueueDataManager getInstance].queueModel getQueuelengthWithid:[NSString stringWithFormat:@"%d",business.businessId]];
    cell.detailTextLabel.text = [NSString stringWithFormat:@"有%d人在排队",queuePeopleCount];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];// 取消选中这行
}

#pragma mark - UIActionSheetDelegate
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {
        // 退出营业厅
        [[AnyChatQueueDataManager getInstance].queueModel setAgentObserver:nil];
        [[AnyChatQueueDataManager getInstance].queueModel leaveArea];
        [self.navigationController popViewControllerAnimated:YES];
    }
}

#pragma mark - UIAlertViewDelegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (alertView == self.waitingAlertView) {
        if (buttonIndex == 0) { //同意
            NSString *btnTitle = [alertView buttonTitleAtIndex:buttonIndex];
            if ([btnTitle isEqualToString:@"取消"]) {// 自己主动取消呼叫
                [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                                 :self.remoteUserId
                                                 :GV_ERR_VIDEOCALL_CANCEL
                                                 :0
                                                 :0
                                                 :nil];
                [[AnyChatQueueDataManager getInstance].queueModel agentServiceCtrlWithCtrlCode:BRAC_AGENT_SERVICE_FINISHSERVICE];
                [[AnyChatQueueDataManager getInstance].queueModel agentServiceCtrlWithCtrlCode:BRAC_AGENT_SERVICE_WAITTING];
            } else if ([btnTitle isEqualToString:@"接受"]) {
                [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :0 :0 :0 :nil];
            }
        } else { //拒绝
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :GV_ERR_VIDEOCALL_REJECT :0 :0 :nil];
            [[AnyChatQueueDataManager getInstance].queueModel agentServiceCtrlWithCtrlCode:BRAC_AGENT_SERVICE_FINISHSERVICE];
            [[AnyChatQueueDataManager getInstance].queueModel agentServiceCtrlWithCtrlCode:BRAC_AGENT_SERVICE_WAITTING];
        }
        [self.theAudioPlayer stop];
    }
}

- (void)hideWaitingAlertView {
    if (self.waitingAlertView) {
        [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
    }
    [self.theAudioPlayer stop];
}

#pragma mark - Audio Delegate
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    [self.theAudioPlayer play];
}

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player {
    [self.theAudioPlayer play];
}

- (void)setVoice {
    NSString *musicPath = [[NSBundle mainBundle] pathForResource:@"sound_phoneCall" ofType:@"wav"];
    if (musicPath) {
        NSURL *musicURL = [NSURL fileURLWithPath:musicPath];
        self.theAudioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:musicURL error:nil];
        self.theAudioPlayer.delegate = self;
    }
}

#pragma mark - Custom Method
// 退出按钮
- (void)setupBackButton {
    UIButton *backButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 17, 30)];
    [backButton setBackgroundImage:[UIImage imageNamed:@"nav_back"] forState:UIControlStateNormal];
    [backButton setBackgroundImage:[UIImage imageNamed:@"nav_back_hover"] forState:UIControlStateHighlighted];
    [backButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    backButton.titleLabel.font = [UIFont systemFontOfSize:13.0f];
    [backButton setContentHorizontalAlignment:UIControlContentHorizontalAlignmentLeft];
    [backButton setContentVerticalAlignment:UIControlContentVerticalAlignmentBottom];
    [backButton addTarget:self action:@selector(backAction:) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:backButton];
}

#pragma mark - Action
- (IBAction)startServerClick:(UIButton *)sender {
    // 开始服务
    AnyChat_AgentObserver *observer = [[AnyChat_AgentObserver alloc] init];
    __weak typeof(self) weakSelf = self;
    observer.agentStatusChangedBlock = ^(NSDictionary * _Nonnull data) {
        [weakSelf onAgentStatusChanged:data];
    };
    observer.serviceNotifyBlock = ^(NSDictionary * _Nonnull data) {
        [weakSelf onServiceNotify:data];
    };
    [[AnyChatQueueDataManager getInstance].queueModel setAgentObserver:observer];
    [[AnyChatQueueDataManager getInstance].queueModel agentServiceCtrlWithCtrlCode:BRAC_AGENT_SERVICE_WAITTING];
}

- (void)backAction:(UIControlEvents *)event {
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"您确定退出坐席服务区吗？" delegate:self cancelButtonTitle:@"取消" destructiveButtonTitle:@"确定" otherButtonTitles:nil, nil];
    actionSheet.delegate = self;
    [actionSheet showInView:self.view];
}

#pragma mark - Memory
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)onAgentStatusChanged:(NSDictionary *)data {
    NSString *status = data[@"status"];
    NSString *title = nil;
    if ([status isEqualToString:@"0"]) {
        title = @"已关闭";
        [self.StartServerBtn setTitle:title forState:UIControlStateNormal];
    }else if ([status isEqualToString:@"1"]) {
        if ([AnyChatQueueDataManager getInstance].queueModel.autoRoute) {
            title = @"等待服务中";
            [self.StartServerBtn setTitle:title forState:UIControlStateNormal];
        } else {
            title = @"开始呼叫客户";
            [self.StartServerBtn setTitle:title forState:UIControlStateNormal];
        }
    }else if ([status isEqualToString:@"2"]) {
        title = @"忙碌中";
        [self.StartServerBtn setTitle:title forState:UIControlStateNormal];
    }else if ([status isEqualToString:@"3"]) {
        title = @"暂停服务";
        [self.StartServerBtn setTitle:title forState:UIControlStateNormal];
    }else if ([status isEqualToString:@"10"]) {
        title = @"离线";
        [self.StartServerBtn setTitle:title forState:UIControlStateNormal];
    }
    NSLog(@"坐席状态发生改变:%@%@", status,title);
}

- (void)onServiceNotify:(NSDictionary *)data
{
    int clientId = [data[@"customerId"] intValue];
    [AnyChatQueueDataManager getInstance].customerId = clientId;
    [AnyChatQueueDataManager getInstance].remoteUserId = self.remoteUserId;
    // 呼叫用户
    [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REQUEST :clientId :0 :0 :0 :nil];
    NSString *userName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_CLIENTUSER :clientId :ANYCHAT_OBJECT_INFO_NAME];
    NSString *message = [NSString stringWithFormat:@"等待客户%@响应，请稍后...", userName];
    self.waitingAlertView = [[UIAlertView alloc] initWithTitle:@"呼叫中..." message:message delegate:self cancelButtonTitle:@"取消" otherButtonTitles:nil ,nil];
    [self.waitingAlertView show];
    [self.theAudioPlayer play];
}

@end
