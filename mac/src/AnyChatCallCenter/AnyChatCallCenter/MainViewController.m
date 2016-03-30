//
//  MainViewController.m
//  HelloAnyChatCallCenter
//
//  Created by bairuitech on 15/5/21.
//  Copyright (c) 2015年 bairuitech. All rights reserved.
//

#import <Quartz/Quartz.h>
#import <QuartzCore/CIFilter.h>
#import <AVFoundation/AVFoundation.h>

#import "MainViewController.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"
#import "User.h"

@interface MainViewController ()<AnyChatNotifyMessageDelegate, AnyChatVideoCallDelegate, AnyChatUserInfoDelegate, NSTableViewDelegate, NSTableViewDataSource>
@property(strong, nonatomic)AnyChatPlatform *anychat;
@property(assign, nonatomic)int userId;                                         //用户id
@property(assign, nonatomic)int remoteUserId;                                   //远程对方用户id
@property(strong, nonatomic)NSMutableArray *onlineUserArr;                      //在线用户
@property(strong, nonatomic)AVCaptureVideoPreviewLayer  *localCaptureLayer;
@property(strong, nonatomic)NSWindow *requestWindow;                            //呼叫等待请求窗口

@property (weak) IBOutlet NSTextField *server;                                  //服务器地址
@property (weak) IBOutlet NSTextField *port;                                    //端口
@property (weak) IBOutlet NSTextField *username;                                //用户名
@property (weak) IBOutlet NSButton *loginButton;                                //登录按钮
@property (weak) IBOutlet NSButton *logoutButton;                               //注销按钮
@property (weak) IBOutlet NSButton *endCallButton;                              //结束通话按钮
@property (strong) IBOutlet NSTextView *logView;                                //日志输出示图
@property (weak) IBOutlet NSTableView *tableView;                               //用户列表示图
@property (weak) IBOutlet NSView *localVideoView;                               //本地视频窗口示图
@property (weak) IBOutlet NSImageView *remoteVideoView;                         //远程视频窗口示图
- (IBAction)loginAction:(NSButton *)sender;                                     //登录事件
- (IBAction)logoutAction:(NSButton *)sender;                                    //注销事件
- (IBAction)endCallAction:(NSButton *)sender;




@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    //初始化系统
    [AnyChatPlatform InitSDK:0];
    //初始化SDK
    AnyChatPlatform *anychat = [[AnyChatPlatform alloc] init];
    //设置代理
    anychat.notifyMsgDelegate = self;
    anychat.userInfoDelegate = self;
    anychat.videoCallDelegate = self;
    self.anychat = anychat;
    
    self.endCallButton.enabled = NO;
    self.logoutButton.enabled = NO;
    
    //设置本地视频窗口
    self.localVideoView.wantsLayer = YES;
//    self.localVideoView.canDrawConcurrently = YES;
    self.localVideoView.layer.contents = (id)[self convertUIImageToCGImageRef:[NSImage imageNamed:@"BG_macVideo"]];
    
    
    //注册通知中心
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    

}


#pragma mark - AnyChat Notify Delegate
// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess {
    NSString *appendMessage;
    if (bSuccess) { //连接成功
        appendMessage = @"• Success connected to server";
    }else {
        appendMessage = @" Failed connected to server. ";
    }
    [self appendLogMessage:appendMessage];
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode {
    NSString *appendMessage;
    if(dwErrorCode == GV_ERR_SUCCESS) { //登录成功
        self.loginButton.enabled = NO;
        self.logoutButton.enabled = YES;
        appendMessage = [NSString stringWithFormat:@"• Login successed. Self UserId: %d", dwUserId];
    }else {
        appendMessage = [NSString stringWithFormat:@"Login failed(ErrorCode:%i)",dwErrorCode];
    }
    [self.tableView reloadData];
    [self appendLogMessage:appendMessage];
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode {
    if(dwErrorCode == 0) {
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];//Overlay 模式
        [AnyChatPlatform UserSpeakControl:-1 :YES];
        [AnyChatPlatform UserCameraControl:-1 :YES];
        [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
        sleep(1);
        //设置远程视频
        [AnyChatPlatform UserSpeakControl:self.remoteUserId :YES];
        [AnyChatPlatform UserCameraControl:self.remoteUserId :YES];
        [AnyChatPlatform SetVideoPos:self.remoteUserId :self.remoteVideoView :0 :0 :0 :0];
    }
    //设置本地视频
    
    
}
// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId {
    
}
// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId {
}
// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId {
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode {
    
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @"信息提醒";
    alert.informativeText = @"网络状态不稳定，已断开连接，请重新登录";
    [alert addButtonWithTitle:@"确定"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            
            self.loginButton.enabled = YES;
            self.logoutButton.enabled = NO;
            
            [self closeDevice];
            [AnyChatPlatform LeaveRoom:-1];
            // 注销系统
            [AnyChatPlatform Logout];
            
            [self.onlineUserArr removeAllObjects];
            [self.tableView reloadData];
            
            self.server.stringValue = @"";
            self.port.stringValue = @"";
            self.username.stringValue = @"";
            self.remoteVideoView.image = [NSImage imageNamed:@"BG_macVideo"];
            [self appendLogMessage:[NSString stringWithFormat:@"• LinkClose(ErrorCode:%i)",dwErrorCode]];
        }
    }];
    

}


#pragma mark - AnyChat UserInfo Delegate
// 用户信息更新通知，wParam（INT）表示用户ID号，lParam（INT）表示更新类别
- (void) OnAnyChatUserInfoUpdate:(int) dwUserId : (int) dwType {
    self.onlineUserArr = [self getOnlineUserArray];
    [self.tableView reloadData];
}

// 好友在线状态变化，wParam（INT）表示好友用户ID号，lParam（INT）表示用户的当前活动状态：0 离线， 1 上线
- (void) OnAnyChatFriendStatus:(int) dwUserId : (int) dwStatus {
    self.onlineUserArr = [self getOnlineUserArray];
    [self.tableView reloadData];
}

#pragma mark - AnyChat Call Delegate

- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr{
    
    self.remoteUserId = dwUserId;
    
    switch (dwEventType) {
            
        case BRAC_VIDEOCALL_EVENT_REQUEST:// 呼叫请求
        {
            NSAlert *alert = [[NSAlert alloc] init];
            alert.messageText = @"信息提醒";
            alert.informativeText = @"用户请求会话";
            [alert addButtonWithTitle:@"同意"];
            [alert addButtonWithTitle:@"拒绝"];
            [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
                if (returnCode == NSAlertFirstButtonReturn){
                    // 呼叫中心-同意呼叫
                    [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                                     :dwUserId
                                                     :0
                                                     :0
                                                     :0
                                                     :nil];
                    [self appendLogMessage:[NSString stringWithFormat:@"• Agree Call With %d",dwUserId]];
                } else if (returnCode == NSAlertSecondButtonReturn){
                    // 呼叫中心-拒绝呼叫
                    [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                                     :dwUserId
                                                     :AC_ERROR_VIDEOCALL_REJECT
                                                     :0
                                                     :0
                                                     :nil];
                    [self appendLogMessage:[NSString stringWithFormat:@"• Reject Call With %d",dwUserId]];
                }
            }];
            break;
        }
            
            
        case BRAC_VIDEOCALL_EVENT_REPLY:// 呼叫请求回复
        {
            switch (dwErrorCode)
            {
                case AC_ERROR_VIDEOCALL_CANCEL://源用户主动放弃会话
                {

                    
                    [self appendLogMessage:[NSString stringWithFormat:@"• User Cancel The Session %d",dwUserId]];
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_REJECT://用户拒绝会话
                {
                    
                    self.requestWindow.isVisible = NO;  //隐藏呼叫请求窗口
                    self.requestWindow = nil;
                    NSAlert *alert = [[NSAlert alloc] init];
                    alert.messageText = @"信息提醒";
                    alert.informativeText = @"用户拒绝了会话";
                    [alert addButtonWithTitle:@"确定"];
                    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
                        if (returnCode == NSAlertFirstButtonReturn){
                            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY
                                                             :dwUserId
                                                             :0
                                                             :0
                                                             :0
                                                             :nil];
                            [self appendLogMessage:[NSString stringWithFormat:@"• User Session Reject %d",dwUserId]];
                        }
                    }];
                    
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_OFFLINE://对方不在线
                {

                    [self appendLogMessage:[NSString stringWithFormat:@"• User Don't Online %d",dwUserId]];
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_BUSY://用户在忙
                {
                    NSAlert *alert = [[NSAlert alloc] init];
                    alert.messageText = @"信息提醒";
                    alert.informativeText = @"用户在忙，请稍后再试";
                    [alert addButtonWithTitle:@"确定"];
                    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
                        if (returnCode == NSAlertFirstButtonReturn){
                            [self appendLogMessage:[NSString stringWithFormat:@"• User Busy %d",dwUserId]];
                        }
                    }];

                    
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_TIMEOUT://会话请求超时
                {
                    self.requestWindow.isVisible = NO;  //隐藏呼叫请求窗口
                    self.requestWindow = nil;
                    NSAlert *alert = [[NSAlert alloc] init];
                    alert.messageText = @"信息提醒";
                    alert.informativeText = @"会话请求超时，请稍后再试";
                    [alert addButtonWithTitle:@"确定"];
                    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
                        if (returnCode == NSAlertFirstButtonReturn){
                            [self appendLogMessage:[NSString stringWithFormat:@"• Session Request Timeout %d",dwUserId]];
                        }
                    }];
                    
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_DISCONNECT://网络断线
                {

                    //
                    [self appendLogMessage:[NSString stringWithFormat:@"• Disconnect With %d",dwUserId]];
                    break;
                }
                    
                    
                case AC_ERROR_VIDEOCALL_NOTINCALL://用户不在呼叫状态
                {

                    [self appendLogMessage:[NSString stringWithFormat:@"• User Not In A Call State %d",dwUserId]];
                    break;
                }
                    
            }
            
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_START://用户同意，视频开始
        {
        
            self.requestWindow.isVisible = NO;  //隐藏呼叫请求窗口
            self.requestWindow = nil;
            self.endCallButton.enabled = YES;
            [AnyChatPlatform EnterRoom:dwParam :@""];
            [self appendLogMessage:[NSString stringWithFormat:@"• Enter Room %d",dwParam]];
//            sleep(1);



            [self appendLogMessage:[NSString stringWithFormat:@"• START Call With %d",dwUserId]];
            break;
        }
            
            
        case BRAC_VIDEOCALL_EVENT_FINISH://视频结束
        {
            [AnyChatPlatform LeaveRoom:-1];
            NSAlert *alert = [[NSAlert alloc] init];
            alert.messageText = @"信息提醒";
            alert.informativeText = @"通话结束";
            [alert addButtonWithTitle:@"确定"];
            [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
                if (returnCode == NSAlertFirstButtonReturn){
                    [AnyChatPlatform UserSpeakControl: self.remoteUserId : NO];         // 关闭对方语音
                    [AnyChatPlatform UserCameraControl: self.remoteUserId : NO];        // 关闭对方摄像头
                    self.remoteUserId = 0;
                    self.endCallButton.enabled = NO;
                    self.remoteVideoView.image = [NSImage imageNamed:@"BG_macVideo"];
                    [self appendLogMessage:@"• End Call"];
                }
            }];
            
            
            
            break;
        }
            
            
    }
    
}

#pragma mark - Table Delegate
- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return [self.onlineUserArr count];
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    
    NSTableCellView *cellView = [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
    
    if([tableColumn.identifier isEqualToString:@"userID"]) {
        User *user = self.onlineUserArr[row];
        //设置头像
        cellView.imageView.image = [NSImage imageNamed:user.userFace];
        //设置用户名
        int userID = [user.userId intValue];
        NSString *userName = user.userName;
        if (self.userId == userID) {
            cellView.textField.stringValue = [NSString stringWithFormat:@"%@（自己）",userName];
        }else {
            cellView.textField.stringValue = [NSString stringWithFormat:@"%@（%d）",userName,userID];
        }
        return cellView;
    }
    return cellView;
}

- (void)tableViewSelectionDidChange:(NSNotification *)notification
{
    User *user = [self.onlineUserArr objectAtIndex:self.tableView.selectedRow];
    int selectUserID = [user.userId intValue];
    if(selectUserID != self.userId) {
        
        // 呼叫中心-呼叫请求
        [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REQUEST :selectUserID :0 :0 :0 :nil];
        [self appendLogMessage:[NSString stringWithFormat:@"• Request Call With %d",selectUserID]];
        
        //==============================子窗口 start===========================================================
        NSWindow *requestWindow = [[NSWindow alloc] initWithContentRect:NSMakeRect(500, 500, 300, 120) styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO];
        NSTextField *field = [[NSTextField alloc] initWithFrame: NSMakeRect(90, 60, 150, 30)];
        field.bordered = NO;
        field.backgroundColor = [NSColor controlColor];
        [field setEditable:NO];
        field.stringValue = @"请求通话中，请等待...";
        [[requestWindow contentView] addSubview:field];
        
        NSButton *button = [[NSButton alloc] initWithFrame:NSMakeRect(120, 20, 70, 30)];
        button.title = @"取消";
        [button setBezelStyle:NSRoundedBezelStyle];
//        [button setAction:@selector(requestCancel)];
        [[requestWindow contentView] addSubview:button];
        
        self.requestWindow = requestWindow;
        
        [button setAction:@selector(cancelRequest:)];
        
        [self.view.window addChildWindow:requestWindow ordered:NSWindowAbove];
        
        [self.requestWindow becomeKeyWindow];
        
    }
    
}

#pragma mark - Custom Method

//消息观察者方法
- (void)AnyChatNotifyHandler:(NSNotification *)notify
{
    NSDictionary* dict = notify.userInfo;
    [self.anychat OnRecvAnyChatNotify:dict];
}

//追加显示日志信息
-(void)appendLogMessage:(NSString *)message
{
    [[[self.logView textStorage] mutableString] appendString:[message stringByAppendingString:@" \n"]];
}

//获取在线用户
- (NSMutableArray *) getOnlineUserArray
{
    NSMutableArray *onlineUserArr = [NSMutableArray new];
    NSMutableArray *allUserListArr = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetUserFriends]];
    
    for (NSString *userID in allUserListArr) {
        
        if ([AnyChatPlatform GetFriendStatus:[userID intValue]] == 1) {
            [onlineUserArr addObject:[User userWithUserId:userID]];
        }
    }
    return onlineUserArr;
    
}

//创建和初始化 AVCaptureVideoPreviewLayer 对象,实现本地视频的显示
- (void) OnLocalVideoInit:(id)session {
    self.localCaptureLayer = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.localCaptureLayer.frame = CGRectMake(0, 0, 215, 140);
    self.localCaptureLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    [self.localVideoView.layer addSublayer:self.localCaptureLayer];
}

- (void) OnLocalVideoRelease:(id)sender {
    if(self.localCaptureLayer) self.localCaptureLayer = nil;
}

//NSImage转CGImageRef
- (CGImageRef)convertUIImageToCGImageRef:(NSImage*)image;
{
    NSData * imageData = [image TIFFRepresentation];
    CGImageRef imageRef;
    if(imageData)
    {
        CGImageSourceRef imageSource =
        CGImageSourceCreateWithData(
                                    (CFDataRef)imageData,  NULL);
        
        imageRef = CGImageSourceCreateImageAtIndex(
                                                   imageSource, 0, NULL);
    }
    return imageRef;
}

//关闭设备
- (void) closeDevice {
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
    [AnyChatPlatform UserSpeakControl: self.remoteUserId : NO];
    [AnyChatPlatform UserCameraControl: self.remoteUserId : NO];
}


#pragma mark - Action
//登录
- (IBAction)loginAction:(NSButton *)sender {
    
    if (self.server.stringValue.length == 0) self.server.stringValue = @"demo.anychat.cn";
    if (self.port.stringValue.length == 0)  self.port.stringValue = @"8906";
    if (self.username.stringValue.length == 0) self.username.stringValue = @"AnyChat007";
    //连接服务器
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    [AnyChatPlatform Connect:self.server.stringValue :[self.port.stringValue intValue]];
    
    
    //登录
    /*
     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
     */
    [AnyChatPlatform Login:self.username.stringValue :@""];
}

//注销
- (IBAction)logoutAction:(NSButton *)sender {
    
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @"注销提醒";
    alert.informativeText = @"你确定要注销AnyChat视频聊天吗";
    [alert addButtonWithTitle:@"确定"];
    [alert addButtonWithTitle:@"取消"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            [self closeDevice];
            
            [AnyChatPlatform LeaveRoom:-1];
            [AnyChatPlatform Logout];
            
            self.loginButton.enabled = YES;
            self.logoutButton.enabled = NO;
            
            [self.onlineUserArr removeAllObjects];
            [self.tableView reloadData];
            
            self.endCallButton.enabled = NO;
            self.server.stringValue = @"";
            self.port.stringValue = @"";
            self.username.stringValue = @"";
            self.logView.string = @"";
            self.remoteVideoView.image = [NSImage imageNamed:@"BG_macVideo"];
        }
    }];

}

//结束通话
- (IBAction)endCallAction:(NSButton *)sender {
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @"信息提醒";
    alert.informativeText = @"确定要结束视频通话吗？";
    [alert addButtonWithTitle:@"确定"];
    [alert addButtonWithTitle:@"取消"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            self.endCallButton.enabled = NO;
            [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_FINISH :self.remoteUserId :0 :0 :0 :nil];
        }
    }];
    
}

//请求呼叫后，取消按钮事件
- (void)cancelRequest:(NSButton *)button {
    // 主动取消呼叫
    [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REPLY :self.remoteUserId :AC_ERROR_VIDEOCALL_CANCEL :0 :0 :nil];
    self.requestWindow.isVisible = NO;
    self.requestWindow = nil;
    [self.view.window becomeKeyWindow];
}

@end
