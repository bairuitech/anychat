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
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>
#import <AVFoundation/AVFoundation.h>

@interface QueueViewController ()<UIAlertViewDelegate,UIActionSheetDelegate,AnyChatVideoCallDelegate,AVAudioPlayerDelegate, AnyChatTransDataDelegate>
@property(strong, nonatomic) AnyChatPlatform *anyChat;                  //anyChat对象
@property(weak, nonatomic) LoginViewController *loginVC;
@property(nonatomic, assign)int remoteUserId;                           //客服人员id号
@property (weak, nonatomic) IBOutlet UILabel *queueWaitingTimeLabel;    //排队等待时间
@property(nonatomic, strong)UIAlertView *requestAlertView;
@property(nonatomic, strong)NSTimer *timer;                             //定时器
@property(nonatomic, strong) AVAudioPlayer *theAudioPlayer;             // 音乐播放器
@property (strong, nonatomic) UIAlertView  *theWaitingAlertView;

- (IBAction)cancelAction:(UIButton *)sender;
@end

@implementation QueueViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.loginVC = [self.navigationController.viewControllers objectAtIndex:0];
    self.anyChat = [AnyChatPlatform getInstance];
    self.anyChat.videoCallDelegate = self;
    self.anyChat.transDataDelegate = self;//暂时舍弃
    
    self.title = @"排队中";
    
    int site = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_INFO_BEFOREUSERNUM] + 1;
    int userCount = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_INFO_QUEUELENGTH];
    NSString *businessName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_QUEUE :(int)self.businessId :ANYCHAT_OBJECT_INFO_NAME];

    self.queuUserSiteLabel.text = [NSString stringWithFormat:@"当前队列：%@",businessName];
    [self updateLabelBySite:site userCount:userCount];
    // 防止锁屏
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
    // 声音
    [self setVoice];
    
    //排队等待时间
    [self queueWaitingTime];
    
    self.isCustomerServiceAutoMode = NO;
    
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:YES];
    [self.timer invalidate];
    self.timer = nil;
    [self dimissAlertView:self.theWaitingAlertView];
}

- (void)updateLabelBySite:(int)site userCount:(int)userCount {
    
    NSString *text = [NSString stringWithFormat:@"当前排队人数：%d 人 您排在第 %d 位", userCount, site + 1 > userCount ? userCount : site + 1];
    self.queueUserCountLabel.text = text;
}

- (void) videoCallRemote:(int)remoteUserId
{
    [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REQUEST :remoteUserId:0 :0 :0 :nil];
    self.remoteUserId = remoteUserId;
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


- (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString
{
    if (jsonString == nil) {
        return nil;
    }
    
    NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *err;
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                        options:NSJSONReadingMutableContainers
                                                          error:&err];
    if(err)
    {
        NSLog(@"json解析失败：%@",err);
        return nil;
    }
    return dic;
}

#pragma mark - AnyChatTransDataDelegate -
- (void) OnAnyChatTransBufferCallBack:(int) dwUserid : (NSData*) lpBuf{
    //如果透明通道收到数据则进行解析
    if(lpBuf){
        NSString *result = [[NSString alloc] initWithData:lpBuf encoding:NSUTF8StringEncoding];
        NSDictionary* jsonObj = [self dictionaryWithJsonString:result];
        if ([jsonObj[@"commandType"] isEqualToString: @"videoCall"] && [jsonObj[@"isAutoMode"] intValue] == 1){
            
            self.isCustomerServiceAutoMode = YES;
            [self videoCallRemote:[jsonObj[@"targetUserId"] intValue]];
        }
    }
}



#pragma mark - AnyChat Call Delegate
- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr{
    self.remoteUserId = dwUserId;
//    self.loginVC.remoteUserId = dwUserId;
    switch (dwEventType) {
            
        case BRAC_VIDEOCALL_EVENT_REQUEST://呼叫请求 1
        {
            

            NSLog(@"BRAC_VIDEOCALL_EVENT_REQUEST");
            NSString *serviceName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_AGENT :dwUserId :ANYCHAT_OBJECT_INFO_NAME];
            self.requestAlertView = [[UIAlertView alloc] initWithTitle:[NSString stringWithFormat:@"客服 %@请求与您视频通话，是否接受?",serviceName] message:nil delegate:self cancelButtonTitle:nil otherButtonTitles:@"接受",@"拒绝" ,nil];
            self.requestAlertView.delegate = self;
            [self.requestAlertView show];

            [self.theAudioPlayer play];
            
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_REPLY:// 呼叫请求回复 2
        {
            NSLog(@"BRAC_VIDEOCALL_EVENT_REPLY---:%d",dwParam);
            if (self.isCustomerServiceAutoMode == NO) {
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
            } else {
                switch (dwErrorCode)
                {
                    case GV_ERR_SUCCESS: // 呼叫成功等待对方反应
                    {
                        NSString *message = @"正在等待客服回应，请稍候...";
                        self.theWaitingAlertView = [[UIAlertView alloc] initWithTitle:@"呼叫中..."
                                                                              message:message
                                                                             delegate:self
                                                                    cancelButtonTitle:@"取消"
                                                                    otherButtonTitles:nil, nil];
                        [self.theWaitingAlertView show];
                        
                        break;
                    }
                    case GV_ERR_VIDEOCALL_CANCEL: // 源用户主动放弃会话
                    {
                        
                        [self dimissAlertView:self.theWaitingAlertView];
                        [MBProgressHUD showError:@"坐席取消会话"];
                        [self.navigationController popViewControllerAnimated:YES];
                        
                        break;
                    }
                        
                    case GV_ERR_VIDEOCALL_TIMEOUT:// 会话请求超时
                    {
                        
                        [self dimissAlertView:self.theWaitingAlertView];
                        [MBProgressHUD showError:@"请求超时"];
                        [self.navigationController popViewControllerAnimated:YES];
                        break;
                    }
                        
                    case GV_ERR_VIDEOCALL_DISCONNECT:// 网络断线
                    {
                        [self dimissAlertView:self.theWaitingAlertView];
                        [MBProgressHUD showError:@"网络断线"];
                        break;
                    }
                        
                    case GV_ERR_VIDEOCALL_REJECT: // 目标用户拒绝会话
                    {
                        [self dimissAlertView:self.theWaitingAlertView];
                        // 退出队列
                        [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_CTRL_USERLEAVE :0 :0 :0 :0 :nil];
                        [self.navigationController popViewControllerAnimated:YES];
                        [MBProgressHUD showError:@"客服拒绝视频通话"];
                        break;
                    }
                        
                        
                }
            }
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_START://视频呼叫会话开始事件 3
        {
            if (self.theWaitingAlertView ) {
                [self dimissAlertView:self.theWaitingAlertView];
            }
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
    if (alertView == self.theWaitingAlertView) {
        
        if (buttonIndex == 0 )
        {
            //源用户自己点击取消
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :GV_ERR_VIDEOCALL_CANCEL :0 :0 :nil];
            
            [self dimissAlertView:self.theWaitingAlertView];
            [self.theAudioPlayer stop];
            [self.navigationController popViewControllerAnimated:YES];
        }
    } else if (alertView == self.requestAlertView) {
        if (buttonIndex == 0) { //同意
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :0 :0 :0 :nil];
        }else { //拒绝
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :GV_ERR_VIDEOCALL_REJECT :0 :0 :nil];
//            [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_CTRL_USERLEAVE :0 :0 :0 :0 :nil];
            [self.navigationController popViewControllerAnimated:YES];
        }
        [self.theAudioPlayer stop];
    }
    
}

//关闭alertView
- (void) dimissAlertView:(UIAlertView *)alert {
    if(alert){
        [alert dismissWithClickedButtonIndex:[alert cancelButtonIndex] animated:YES];
    }
}

#pragma mark - UIActionSheetDelegate
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {
        
        if (self.isCustomerServiceAutoMode==YES) {
            //用户主动取消对话
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                             :self.remoteUserId
                                             :GV_ERR_VIDEOCALL_CANCEL
                                             :0
                                             :0
                                             :nil];
            //退出队列
            [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_CTRL_USERLEAVE :0 :0 :0 :0 :nil];
            [self.navigationController popViewControllerAnimated:YES];
        }
        else
        {
            //退出队列
            [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_QUEUE :self.businessId :ANYCHAT_QUEUE_CTRL_USERLEAVE :0 :0 :0 :0 :nil];
            [self.navigationController popViewControllerAnimated:YES];
        }
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
    self.queueWaitingTimeLabel.text = timeLabelText;
}

// 时间转换
- (NSString *)transform:(int)second {
    return [NSString stringWithFormat:@"%02d:%02d", (second%(60*60))/60, second%60];
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


-(BOOL)needLeftBackItem {
    
    return NO;
}

@end
