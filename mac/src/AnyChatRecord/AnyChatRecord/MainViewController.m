//
//  MainViewController.m
//  AnyChatRecord
//
//  Created by tim.tan on 15/6/8.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//
#import <Quartz/Quartz.h>
#import <QuartzCore/CIFilter.h>
#import <AVFoundation/AVFoundation.h>

#import "MainViewController.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"
#import "User.h"

@interface MainViewController ()<AnyChatNotifyMessageDelegate,AnyChatRecordSnapShotDelegate,NSTableViewDelegate, NSTableViewDataSource>
@property(strong, nonatomic)AnyChatPlatform *anychat;
@property(assign, nonatomic)int userId;                                         //用户id
@property(assign, nonatomic)int remoteUserId;                                   //远程对方用户id
@property(strong, nonatomic)NSMutableArray *onlineUserArr;                      //在线用户
@property(strong, nonatomic)AVCaptureVideoPreviewLayer  *localCaptureLayer;

@property (weak) IBOutlet NSTextField *server;                                  //服务器地址
@property (weak) IBOutlet NSTextField *port;                                    //端口
@property (weak) IBOutlet NSTextField *username;                                //用户名
@property (weak) IBOutlet NSTextField *roomId;                                  //房间号
@property (weak) IBOutlet NSButton *loginButton;                                //登录按钮
@property (weak) IBOutlet NSButton *logoutButton;                               //注销按钮
@property (weak) IBOutlet NSComboBox *recodeMode;                               //录像方法
@property (weak) IBOutlet NSComboBox *recordObject;                             //录像对象
@property (weak) IBOutlet NSButton *startdRecordButton;                         //开始录像按钮
@property (weak) IBOutlet NSButton *endRecordButton;                            //结束录像按钮
@property (strong) IBOutlet NSTextView *logView;                                //日志输出示图
@property (weak) IBOutlet NSTableView *tableView;                               //用户列表示图
@property (weak) IBOutlet NSView *localVideoView;                               //本地视频窗口示图
@property (weak) IBOutlet NSImageView *remoteVideoView;                         //远程视频窗口示图
@property (weak) IBOutlet NSTextField *recordLabel;                             //录像中标签

@property(nonatomic, assign)int recordFlags;                                    //录像标记
@property(nonatomic, copy)NSString *recordStr;                                  //录像返回字符串


- (IBAction)loginAction:(NSButton *)sender;                                     //登录事件
- (IBAction)logoutAction:(NSButton *)sender;                                    //注销事件
- (IBAction)startRecordAction:(NSButton *)sender;                               //开始录像
- (IBAction)endRecordAction:(NSButton *)sender;                                 //结束录像

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
    anychat.recordSnapShotDelegate = self;
    
    self.anychat = anychat;
    
    self.startdRecordButton.enabled = NO;
    self.endRecordButton.enabled = NO;
    self.logoutButton.enabled = NO;
    
    //设置本地视频窗口
    self.localVideoView.wantsLayer = YES;
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
        self.startdRecordButton.enabled = YES;
        self.loginButton.enabled = NO;
        self.logoutButton.enabled = YES;
        self.userId = dwUserId;
        //进入房间
        [AnyChatPlatform EnterRoom:[self.roomId intValue] :@""];
        appendMessage = [NSString stringWithFormat:@"• Login successed. Self UserId: %d", dwUserId];
    }else {
        appendMessage = [NSString stringWithFormat:@"Login failed(ErrorCode:%i)",dwErrorCode];
    }
    [self.tableView reloadData];
    [self appendLogMessage:appendMessage];
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode {
    
    NSString *appendMessage;
    if(dwErrorCode == 0) {
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];
        [AnyChatPlatform UserSpeakControl:-1 :YES];
        [AnyChatPlatform UserCameraControl:-1 :YES];
        [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
        appendMessage = [NSString stringWithFormat:@"• Enter Room successed. Room Id: %d", dwRoomId];
    }else {
        appendMessage = [NSString stringWithFormat:@"• Enter room failed(ErrorCode:%i)", dwRoomId];
    }
    [self appendLogMessage:appendMessage];
    
}
// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId {
    NSString *appendMessage;
    
    [self setOnlineUserArray];
    // 刷新用户列表
    [self.tableView reloadData];
    appendMessage = [NSString stringWithFormat:@"• OnlineUserCount:%ld", self.onlineUserArr.count];
    
    [self appendLogMessage:appendMessage];
}
// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId {
    [self setOnlineUserArray];
    // 刷新用户列表
    [self.tableView reloadData];
    
    [self appendLogMessage:[NSString stringWithFormat:@"• New User Enter Room UserId:%d", dwUserId]];
    
}
// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId {
    [self setOnlineUserArray];
    // 刷新用户列表
    [self.tableView reloadData];
    
    if (self.remoteUserId == dwUserId) {
        [AnyChatPlatform UserSpeakControl:dwUserId :NO];
        [AnyChatPlatform UserCameraControl:dwUserId :NO];
        self.remoteVideoView.image = [NSImage imageNamed:@"BG_macVideo"];
    }
    
    [self appendLogMessage:[NSString stringWithFormat:@"• User Leave Room UserId:%d", dwUserId]];
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
            self.startdRecordButton.enabled = NO;
            
            [AnyChatPlatform UserSpeakControl: -1 : NO];
            [AnyChatPlatform UserCameraControl: -1 : NO];
            [AnyChatPlatform UserSpeakControl: self.remoteUserId : NO];
            [AnyChatPlatform UserCameraControl: self.remoteUserId : NO];
            
            [AnyChatPlatform LeaveRoom:-1];
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

#pragma mark - Record Delegate
// 录像完成事件
- (void) OnAnyChatRecordCallBack:(int) dwUserid : (NSString*) lpFileName : (int) dwElapse : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr {
    
    
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @"录像提醒";
    alert.informativeText = [NSString stringWithFormat:@"视频保存:%@",lpFileName];
    [alert addButtonWithTitle:@"确定"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            
        }
    }];

}

// 拍照完成事件
- (void) OnAnyChatSnapShotCallBack:(int) dwUserid : (NSString*) lpFileName : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr {

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
    
    self.startdRecordButton.enabled = YES;
    
    User *user = [self.onlineUserArr objectAtIndex:self.tableView.selectedRow];
    int selectUserID = [user.userId intValue];
    
    self.remoteUserId = selectUserID;
    
    [AnyChatPlatform UserSpeakControl:selectUserID :YES];
    [AnyChatPlatform UserCameraControl:selectUserID :YES];
    [AnyChatPlatform SetVideoPos:selectUserID :self.remoteVideoView :0 :0 :0 :0];
    
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
- (void) setOnlineUserArray
{
    NSMutableArray *onlineUserArr = [NSMutableArray new];
    NSMutableArray *allUserListArr = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
    for (NSString *userID in allUserListArr) {
        [onlineUserArr addObject:[User userWithUserId:userID]];
    }
    self.onlineUserArr = onlineUserArr;
    
}


//创建和初始化 AVCaptureVideoPreviewLayer 对象,实现本地视频的显示
- (void) OnLocalVideoInit:(id)session {
    self.localCaptureLayer = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.localCaptureLayer.frame = CGRectMake(0, 0, 110, 127);
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

// 开始录像
- (void)startRecordWithRecordMode:(int)selectMode recordObject:(int)selectObject {
    int userId;         // 用户id
    
    self.recordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_LOCALCB;
    
    switch (selectMode) {
        case 0://本地录像
            self.recordStr = @"StartLocal";
            break;
        case 1://服务器录像
            self.recordStr = @"StartServer";
            self.recordFlags += ANYCHAT_RECORD_FLAGS_SERVER;
            break;
        default:
            break;
    }
    
    
    switch (selectObject) {
        case 0://录自己
            userId = -1;
            self.recordStr = [self.recordStr stringByAppendingString:@"SelfRecord"];
            break;
        case 1://录对方
            userId = self.remoteUserId;
            self.recordStr = [self.recordStr stringByAppendingString:@"RemoteRecord"];
            break;
        case 2://合成
            userId = self.remoteUserId;
            self.recordStr = [self.recordStr stringByAppendingString:@"ComposeRecord"];
            self.recordFlags += ANYCHAT_RECORD_FLAGS_MIXAUDIO + ANYCHAT_RECORD_FLAGS_MIXVIDEO + ANYCHAT_RECORD_FLAGS_ABREAST + ANYCHAT_RECORD_FLAGS_STEREO;
            break;
        default:
            break;
    }
    
    [AnyChatPlatform StreamRecordCtrlEx: userId
                                       : YES
                                       : self.recordFlags
                                       : 0
                                       : self.recordStr];
}

#pragma mark - Action
//登录
- (IBAction)loginAction:(NSButton *)sender {
    
    if (self.server.stringValue.length == 0) self.server.stringValue = @"demo.anychat.cn";
    if (self.port.stringValue.length == 0)  self.port.stringValue = @"8906";
    if (self.username.stringValue.length == 0) self.username.stringValue = @"AnyChatRecord007";
    if (self.roomId.stringValue.length == 0) self.roomId.stringValue = @"23";
    
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
    alert.informativeText = @"你确定要注销AnyChat视频录像聊天吗";
    [alert addButtonWithTitle:@"确定"];
    [alert addButtonWithTitle:@"取消"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            [AnyChatPlatform UserSpeakControl: -1 : NO];
            [AnyChatPlatform UserCameraControl: -1 : NO];
            
            [AnyChatPlatform UserSpeakControl: self.remoteUserId : NO];
            [AnyChatPlatform UserCameraControl: self.remoteUserId : NO];
            
            [AnyChatPlatform LeaveRoom:-1];
            [AnyChatPlatform Logout];
            
            self.loginButton.enabled = YES;
            self.logoutButton.enabled = NO;
            self.startdRecordButton.enabled = NO;
            
            [self.onlineUserArr removeAllObjects];
            [self.tableView reloadData];
            
            self.server.stringValue = @"";
            self.port.stringValue = @"";
            self.username.stringValue = @"";
            self.roomId.stringValue = @"";
            self.logView.string = @"";
            
            self.remoteVideoView.image = [NSImage imageNamed:@"BG_macVideo"];
        }
    }];
    
}

//开始录像
- (IBAction)startRecordAction:(NSButton *)sender {

    int selectRecordMode = (int)self.recodeMode.indexOfSelectedItem;        //录像方式
    int selectRecordObject = (int)self.recordObject.indexOfSelectedItem;    //录像对象
    if (selectRecordMode == -1 || selectRecordObject == -1) {
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = @"录像提醒";
        alert.informativeText = @"请选择录像方式和录像对象";
        [alert addButtonWithTitle:@"确定"];
        [alert beginSheetModalForWindow:[self.view window] completionHandler:nil];
    }else {
        
        if (self.remoteUserId == 0 && selectRecordObject != 0) {
            NSAlert *alert = [[NSAlert alloc] init];
            alert.messageText = @"录像提醒";
            alert.informativeText = @"视频聊天还没开始，暂时只能录制自己";
            [alert addButtonWithTitle:@"确定"];
            [alert beginSheetModalForWindow:[self.view window] completionHandler:nil];
        }else {
            //开始录像
            [self startRecordWithRecordMode:selectRecordMode recordObject:selectRecordObject];
            self.startdRecordButton.enabled = NO;
            self.endRecordButton.enabled = YES;
            
            self.recordLabel.hidden = NO;
            
        }
        
        
    }
    
}

//结束录像
- (IBAction)endRecordAction:(NSButton *)sender {
    int userId;
    NSString *param;
    int selectRecordMode = (int)self.recodeMode.indexOfSelectedItem;        //录像方式
    int selectRecordObject = (int)self.recordObject.indexOfSelectedItem;    //录像对象
    switch (selectRecordMode) {
        case 0://本地录像
            param = @"StopLocalRecord";
            break;
        case 1://服务器录像
            param = @"StopServerRecord";
            break;
        default:
            break;
    }
    switch (selectRecordObject) {
        case 0://录自己
            userId = -1;
            break;
        case 1://录对方
            userId = self.remoteUserId;
            break;
        case 2://合成
            userId = -1;
            break;
        default:
            break;
    }
    
    [AnyChatPlatform StreamRecordCtrlEx: userId
                                       : NO
                                       : self.recordFlags
                                       : 0
                                       : param];
    
    self.startdRecordButton.enabled = YES;
    self.endRecordButton.enabled = NO;
    self.recordLabel.hidden = YES;
}

@end
