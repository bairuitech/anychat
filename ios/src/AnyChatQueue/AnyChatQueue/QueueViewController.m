//
//  QueueViewController.m
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "QueueViewController.h"
#import "MBProgressHUD+JT.h"
#import "LoginViewController.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface QueueViewController ()<UIAlertViewDelegate,UIActionSheetDelegate,AnyChatVideoCallDelegate>
@property(strong, nonatomic) AnyChatPlatform *anyChat;                  //anyChat对象
@property(weak, nonatomic) LoginViewController *loginVC;
@property(nonatomic, assign)int remoteUserId;                           //客服人员id号
@property(nonatomic, assign)int beforeNum;                              //排在自己前面的人数
@property (weak, nonatomic) IBOutlet UILabel *queueLabel;               //您已经进入xx业务 Label
@property (weak, nonatomic) IBOutlet UILabel *queueWaitingTimeLabel;    //排队等待时间
@property(nonatomic, strong)UIAlertView *requestAlertView;
@property(nonatomic, strong)NSTimer *timer;                             //定时器

- (IBAction)cancelAction:(UIButton *)sender;
@end

@implementation QueueViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.loginVC = [self.navigationController.viewControllers objectAtIndex:0];
    self.anyChat = self.loginVC.anyChat;
    self.anyChat.videoCallDelegate = self;

    self.beforeNum = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_INFO_BEFOREUSERNUM];
    
    self.beforeLabel.text = [NSString stringWithFormat:@"在您前面还有%d人等待",self.beforeNum];
    
    NSString *businessName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_QUEUE :(int)self.businessId :ANYCHAT_OBJECT_INFO_NAME];
    self.title = businessName;
    self.queueLabel.text = [NSString stringWithFormat:@"您已经成功进入%@",businessName];
    
    //排队等待时间
    [self queueWaitingTime];
    
    // 返回按钮
    [self setupBackButton];
    
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:YES];
    [self.timer invalidate];
    self.timer = nil;
}

#pragma mark - AnyChat Call Delegate
- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr{
    self.remoteUserId = dwUserId;
    self.loginVC.remoteUserId = dwUserId;
    switch (dwEventType) {
        
        case BRAC_VIDEOCALL_EVENT_REQUEST://呼叫请求 1
        {
            self.requestAlertView = [[UIAlertView alloc] initWithTitle:@"客服人员请求与您通话" message:nil delegate:self cancelButtonTitle:nil otherButtonTitles:@"确定",@"取消" ,nil];
            self.requestAlertView.delegate = self;
            [self.requestAlertView show];
            
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_REPLY:// 呼叫请求回复 2
        {
            switch (dwErrorCode)
            {
                case GV_ERR_VIDEOCALL_CANCEL: // 源用户主动放弃会话
                {
                    if (self.requestAlertView != nil) [self.requestAlertView dismissWithClickedButtonIndex:self.requestAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"坐席取消会话"];
                    [self.navigationController popViewControllerAnimated:YES];
                    break;
                }
                    
                case GV_ERR_VIDEOCALL_TIMEOUT:// 会话请求超时
                {
                    if (self.requestAlertView != nil) [self.requestAlertView dismissWithClickedButtonIndex:self.requestAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"请求超时"];
                    [self.navigationController popViewControllerAnimated:YES];
                    break;
                }
                    
                case GV_ERR_VIDEOCALL_DISCONNECT:// 网络断线
                {
                    [MBProgressHUD showError:@"网络断线"];
                    
                    break;
                }
                    
            }
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_START://视频呼叫会话开始事件 3
        {
            //进入房间
            [AnyChatPlatform EnterRoom:dwParam :nil];
            break;
        }
        
        case BRAC_VIDEOCALL_EVENT_FINISH://挂断（结束）呼叫会话 4
        {
            // 关闭设备
            [AnyChatPlatform UserSpeakControl: -1 : NO];
            [AnyChatPlatform UserCameraControl: -1 : NO];
            [AnyChatPlatform UserSpeakControl: dwUserId : NO];
            [AnyChatPlatform UserCameraControl: dwUserId : NO];
            // 离开房间
            [AnyChatPlatform LeaveRoom:-1];
            [MBProgressHUD showSuccess:@"视频通话结束"];
            // 跳转
            [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:2] animated:YES];
            
            break;
        }
    }
    
}

#pragma mark - UIAlertViewDelegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) { //同意
        [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :0 :0 :0 :nil];
    }else { //拒绝
        [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :GV_ERR_VIDEOCALL_REJECT :0 :0 :nil];
        [self.navigationController popViewControllerAnimated:YES];
    }
}

#pragma mark - UIActionSheetDelegate
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {
        //退出队列
        [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_CTRL_USERLEAVE :0 :0 :0 :0 :nil];
        [self.navigationController popViewControllerAnimated:YES];
    }
}


#pragma mark - Action
- (void)backAction:(UIControlEvents *)event {
    // 退出队列
    [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_CTRL_USERLEAVE :0 :0 :0 :0 :nil];
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)cancelAction:(UIButton *)sender {
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"您确定退出排队吗？" delegate:self cancelButtonTitle:@"取消" destructiveButtonTitle:@"确定" otherButtonTitles:nil, nil];
    actionSheet.delegate = self;
    [actionSheet showInView:self.view];
}

#pragma mark - Custom Method
// 返回按钮
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

// 排队等待时间
- (void)queueWaitingTime {
    NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(setWaitingTimeLabel) userInfo:nil repeats:YES];
    self.timer = timer;
}

// 设置label计时器
- (void)setWaitingTimeLabel {
    int waitingTime = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_INFO_WAITTIMESECOND];
    NSString *timeLabelText = [self transform:waitingTime];
    self.queueWaitingTimeLabel.text = [NSString stringWithFormat:@"已经等待 %@",timeLabelText];
}

// 时间转换
- (NSString *)transform:(int)second {
    return [NSString stringWithFormat:@"%d时 %d分 %d秒", second/(60*60), (second%(60*60))/60, second%60];
}

#pragma mark - Memory
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
