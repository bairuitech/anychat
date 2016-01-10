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

#import <AVFoundation/AVFoundation.h>

@interface QueueViewController ()<UIAlertViewDelegate,UIActionSheetDelegate,AnyChatVideoCallDelegate,AVAudioPlayerDelegate>
@property(strong, nonatomic) AnyChatPlatform *anyChat;                  //anyChat对象
@property(weak, nonatomic) LoginViewController *loginVC;
@property(nonatomic, assign)int remoteUserId;                           //客服人员id号
@property(nonatomic, assign)int queueUserCount;                         //队列人数
@property(nonatomic, assign)int queueUserSite;                          //队列中用户位置
@property (weak, nonatomic) IBOutlet UILabel *queueWaitingTimeLabel;    //排队等待时间
@property(nonatomic, strong)UIAlertView *requestAlertView;
@property(nonatomic, strong)NSTimer *timer;                             //定时器
@property(nonatomic, strong) AVAudioPlayer *theAudioPlayer;             // 音乐播放器

- (IBAction)cancelAction:(UIButton *)sender;
@end

@implementation QueueViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.loginVC = [self.navigationController.viewControllers objectAtIndex:0];
    self.anyChat = self.loginVC.anyChat;
    self.anyChat.videoCallDelegate = self;

    NSString *businessName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_QUEUE :(int)self.businessId :ANYCHAT_OBJECT_INFO_NAME];
    self.title = [NSString stringWithFormat:@"%@-排队等待中",businessName];
    
    self.queueUserSite = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_INFO_BEFOREUSERNUM] + 1;
    self.queuUserSiteLabel.text = [NSString stringWithFormat:@"你现在排在第%d位",self.queueUserSite];
    
    self.queueUserCount = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_INFO_LENGTH];
    self.queueUserCountLabel.text = [NSString stringWithFormat:@"当前排队人数共:%d人",self.queueUserCount];
    
    // 防止锁屏
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
    // 声音
    [self setVoice];
    
    //排队等待时间
    [self queueWaitingTime];
    
    self.navigationItem.hidesBackButton = YES;
    
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:YES];
    [self.timer invalidate];
    self.timer = nil;
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

#pragma mark - AnyChat Call Delegate
- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr{
    self.remoteUserId = dwUserId;
    self.loginVC.remoteUserId = dwUserId;
    switch (dwEventType) {
        
        case BRAC_VIDEOCALL_EVENT_REQUEST://呼叫请求 1
        {
            NSString *serviceName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_AGENT :dwUserId :ANYCHAT_OBJECT_INFO_NAME];
            self.requestAlertView = [[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"客服 %@请求与您视频通话，是否接受?",serviceName] message:nil delegate:self cancelButtonTitle:nil otherButtonTitles:@"接受",@"拒绝" ,nil];
            self.requestAlertView.delegate = self;
            [self.requestAlertView show];
            
            [self.theAudioPlayer play];
            
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_REPLY:// 呼叫请求回复 2
        {
            switch (dwErrorCode)
            {
                case AC_ERROR_VIDEOCALL_CANCEL: // 源用户主动放弃会话
                {
                    if (self.requestAlertView != nil) [self.requestAlertView dismissWithClickedButtonIndex:self.requestAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"坐席取消会话"];
                    [self.navigationController popViewControllerAnimated:YES];
                    
                    break;
                }
                    
                case AC_ERROR_VIDEOCALL_TIMEOUT:// 会话请求超时
                {
                    if (self.requestAlertView != nil) [self.requestAlertView dismissWithClickedButtonIndex:self.requestAlertView.cancelButtonIndex animated:YES];
                    [MBProgressHUD showError:@"请求超时"];
                    [self.navigationController popViewControllerAnimated:YES];
                    break;
                }
                    
                case AC_ERROR_VIDEOCALL_DISCONNECT:// 网络断线
                {
                    [MBProgressHUD showError:@"网络断线"];
                    break;
                }
                default:
                    break;
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
        [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :AC_ERROR_VIDEOCALL_REJECT :0 :0 :nil];
        [self.navigationController popViewControllerAnimated:YES];
    }
    [self.theAudioPlayer stop];
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

// 排队等待时间
- (void)queueWaitingTime {
    NSTimer *timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(setWaitingTimeLabel) userInfo:nil repeats:YES];
    self.timer = timer;
}

// 设置label计时器
- (void)setWaitingTimeLabel {
    int waitingTime = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_INFO_WAITTIMESECOND];
    NSString *timeLabelText = [self transform:waitingTime];
    self.queueWaitingTimeLabel.text = [NSString stringWithFormat:@"已等待时长 %@",timeLabelText];
}

// 时间转换
- (NSString *)transform:(int)second {
    return [NSString stringWithFormat:@"%d时 %d分 %d秒", second/(60*60), (second%(60*60))/60, second%60];
}

// 声音
- (void)setVoice {
    NSString *musicPath = [[NSBundle mainBundle] pathForResource:@"sound_phoneCall" ofType:@"wav"];
    if (musicPath) {
        NSURL *musicURL = [NSURL fileURLWithPath:musicPath];
        self.theAudioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:musicURL
                                                                     error:nil];
        self.theAudioPlayer.delegate = self;
    }
}

#pragma mark - Memory
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
