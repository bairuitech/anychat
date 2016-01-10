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

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"
#import "AnyChatObjectDefine.h"

#import "MBProgressHUD+JT.h"

@interface ServerQueueViewController ()<UITableViewDataSource,UITableViewDelegate,AnyChatVideoCallDelegate,UIActionSheetDelegate,UIAlertViewDelegate>
@property(strong, nonatomic) AnyChatPlatform *anyChat;          //anyChat对象
@property(weak, nonatomic) LoginViewController *loginVC;
@property(nonatomic, strong)NSArray *businesses;
@property(nonatomic, assign)int remoteUserId;

- (IBAction)startServerClick:(UIButton *)sender;
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
    self.anyChat = self.loginVC.anyChat;
    self.anyChat.videoCallDelegate = self;
    
    self.navigationItem.title = @"队列列表";
    self.tableView.rowHeight = 50;
    
    // 添加退出按钮
    [self setupBackButton];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    self.navigationController.navigationBarHidden = NO;
}


#pragma mark - AnyChat Call Delegate
- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr{
    
    self.remoteUserId = dwUserId;
    switch (dwEventType) {
            
        case BRAC_VIDEOCALL_EVENT_REPLY:// 呼叫请求回复 2
        {
            switch (dwErrorCode)
            {
                case AC_ERROR_VIDEOCALL_CANCEL: // 源用户主动放弃会话
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_REJECT: // 目标用户拒绝会话
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"顾客拒绝视频通话"];
                    
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_OFFLINE:// 目标用户不在线
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"顾客不在线"];
                    
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_BUSY:// 目标用户忙
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"顾客忙"];
                    
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_TIMEOUT:// 会话请求超时
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"请求超时"];
                    
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_DISCONNECT:// 网络断线
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"网络断线"];
                    
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_NOTINCALL:// 用户不在呼叫状态
                {
                    if (self.waitingAlertView != nil) [self.waitingAlertView dismissWithClickedButtonIndex:self.waitingAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"顾客不在呼叫状态"];
                    
                    break;
                }
                    
            }
            
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
    int queueId = [self.businessListIdArray[indexPath.row] intValue];
    int queuePeopleCount = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :queueId :ANYCHAT_QUEUE_INFO_LENGTH];
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
                                             :AC_ERROR_VIDEOCALL_CANCEL
                                             :0
                                             :0
                                             :nil];
        }
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
    [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT :self.selfUserId :ANYCHAT_AGENT_CTRL_SERVICEREQUEST :0 :0 :0 :0 :nil];

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

@end
