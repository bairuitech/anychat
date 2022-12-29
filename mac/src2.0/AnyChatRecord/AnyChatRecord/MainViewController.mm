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

#import <AnyChatCoreSDK/AnyChatCoreSDK.h>
#import "User.h"
#import "CmacOSWindowListInfo.h"

#define ANYCHAT_SCREENSOURCE_FLAGS_DISABLECURSOR 0x01        ///< 禁止鼠标光标
#define ANYCHAT_SCREENSOURCE_FLAGS_DISABLEBORDER  0x02        ///< 禁止边框显示
#define ANYCHAT_SCREENSOURCE_FLAGS_DISABLETRACE  0x04        ///< 禁止鼠标追踪
#define ANYCHAT_SCREENSOURCE_FLAGS_NONFULLSCREEN  0x08        ///< 非全屏采集（对窗口画面进行采集分两种：1、共享出去的画面只有窗口大小 2、以整个屏幕的大小共享画面，窗口画面居中，四周留黑）
#define ANYCHAT_SCREENSOURCE_FLAGS_RECT  0x10        ///< 指定采集区域模式（上层传递坐标值）
#define  ANYCHAT_SCREENSOURCE_FLAGS_HOLDWND  0x0100///< 采集指定窗口

#define  BRAC_SO_LOCALVIDEO_SCREENHWND           108 // 屏幕采集窗口句柄

@interface MainViewController ()<AnyChatNotifyMessageDelegate,AnyChatRecordSnapShotDelegate,NSTableViewDelegate, NSTableViewDataSource>
{
    CmacOSWindowListInfo *listInfo;
}
@property(strong, nonatomic)AnyChatPlatform *anychat;
@property(assign, nonatomic)int userId;                                         //用户id
@property(assign, nonatomic)int remoteUserId;                                   //远程对方用户id
@property(strong, nonatomic)NSMutableArray *onlineUserArr;                      //在线用户
@property(strong, nonatomic)AVCaptureVideoPreviewLayer  *localCaptureLayer;

@property(strong, nonatomic)NSMutableArray *windowArr;

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
@property (weak) IBOutlet NSButton *snapButton;

@property (strong) IBOutlet NSTextView *logView;                                //日志输出示图
@property (weak) IBOutlet NSTableView *tableView;                               //用户列表示图

@property (weak) IBOutlet NSTableView *windowTableView;

@property (weak) IBOutlet NSImageView *localVideoView;

@property (weak) IBOutlet NSImageView *remoteVideoView;                         //远程视频窗口示图
@property (weak) IBOutlet NSTextField *recordLabel;                             //录像中标签
@property (weak) IBOutlet NSImageView *localScreenView;

@property(nonatomic, assign)int recordFlags;                                    //录像标记
@property(nonatomic, copy)NSString *recordStr;                                  //录像返回字符串


- (IBAction)loginAction:(NSButton *)sender;                                     //登录事件
- (IBAction)logoutAction:(NSButton *)sender;                                    //注销事件
- (IBAction)startRecordAction:(NSButton *)sender;                               //开始录像
- (IBAction)endRecordAction:(NSButton *)sender;                                 //结束录像
@property (weak) IBOutlet NSTextField *widthTextField;
@property (weak) IBOutlet NSTextField *heightTextField;
@property (weak) IBOutlet NSButton *openRemoteScreenCheckedButton;

@property (weak) IBOutlet NSTextField *filterSoftWareTextField;

@property (weak) IBOutlet NSButton *filterSoftWareCheckedButton;

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
    self.snapButton.enabled = NO;
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
        self.snapButton.enabled = YES;
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
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :0];
        [AnyChatPlatform UserSpeakControl:-1 :YES];
//        [AnyChatPlatform UserCameraControl:-1 :YES];
//        [AnyChatPlatform SetVideoPos:-1 :self.localVideoView :0 :0 :0 :0];
        int streamindex = 0;
        [AnyChatPlatform SetVideoPosEx:-1 :self.localVideoView :0 :0 :0 :0 :streamindex :0];
    
        [AnyChatPlatform UserCameraControlEx:-1 :1 :streamindex :0 :@""];
        
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
            self.snapButton.enabled = NO;
            
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
- (void)OnAnyChatRecordCallBack:(int)dwUserid :(int)dwErrorCode :(NSString *)lpFileName :(int)dwElapse :(int)dwFlags :(int)dwParam :(NSString *)lpUserStr {
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @"录像提醒";
    alert.informativeText = [NSString stringWithFormat:@"视频保存:%@",lpFileName];
    [alert addButtonWithTitle:@"确定"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            
        }
    }];
}
// 录像完成事件
//	

// 拍照完成事件
- (void) OnAnyChatSnapShotCallBack:(int) dwUserid : (int) dwErrorCode : (NSString*) lpFileName : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr
{
    NSLog(@"OnAnyChatSnapShotCallBack");
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @"截图提醒";
    alert.informativeText = [NSString stringWithFormat:@"截图保存:%@",lpFileName];
    [alert addButtonWithTitle:@"确定"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            
        }
    }];
}


#pragma mark - Table Delegate
- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    if (tableView == self.tableView) {
        return [self.onlineUserArr count];
    } else {
        return [self.windowArr count];
    }
    
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    
    NSTableCellView *cellView = [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
    
    if([tableColumn.identifier isEqualToString:@"userID"]) {
        if (tableView == self.tableView) {
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
        } else {
            NSDictionary *dic = self.windowArr[row];
            cellView.textField.stringValue = dic[@"name"];
        }
        return cellView;
    }
    return cellView;
}

- (void)tableViewSelectionDidChange:(NSNotification *)notification
{
    if (notification.object == self.tableView) {

        if (self.tableView.selectedRow >= 0 && self.tableView.selectedRow < self.onlineUserArr.count) {
            self.startdRecordButton.enabled = YES;
            self.snapButton.enabled = YES;
            
            User *user = [self.onlineUserArr objectAtIndex:self.tableView.selectedRow];
            int selectUserID = [user.userId intValue];
            
            self.remoteUserId = selectUserID;
            
            [AnyChatPlatform UserSpeakControl:selectUserID :YES];
            [AnyChatPlatform UserCameraControl:selectUserID :YES];
            [AnyChatPlatform SetVideoPos:selectUserID :self.remoteVideoView :0 :0 :0 :0];
            
            if (self.openRemoteScreenCheckedButton.state == 1) {
                int streamindex = 1;
                [AnyChatPlatform SetVideoPosEx:selectUserID :self.localScreenView :0 :0 :0 :0 :streamindex :0];
                [AnyChatPlatform UserCameraControlEx:selectUserID :1 :streamindex :0 :@""];
            }
        }
    } else if (notification.object == self.windowTableView) {
        if (self.windowTableView.selectedRow >= 0 && self.windowTableView.selectedRow < self.windowArr.count) {
            NSDictionary *dic = self.windowArr[self.windowTableView.selectedRow];
            
            
        }
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
            userId = -1;//self.remoteUserId;
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
    
    if (self.server.stringValue.length == 0) self.server.stringValue = @"mini.anychat.cn";
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
            self.snapButton.enabled = NO;
            
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
- (IBAction)snapButtonPress:(id)sender {
    
    int userId=-1;

    int selectRecordObject = (int)self.recordObject.indexOfSelectedItem;    //录像对象

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
    
    [AnyChatPlatform SnapShot:userId :0 :0];
}
- (IBAction)startShareButtonPress:(id)sender {

    
    //屏幕采集标志
int  dwScreenFlags = ANYCHAT_SCREENSOURCE_FLAGS_DISABLEBORDER;
    
    [self startShare:dwScreenFlags dwWidth:1920 dwHeight:1080];
    
    
}
- (IBAction)endShareButtonPress:(id)sender {
    int streamindex = 1;
    
    [AnyChatPlatform UserCameraControlEx:-1 :NO :streamindex :0 :@"stream SCREEN"];
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_CORESDK_SCREENCAMERACTRL :0];
}
- (IBAction)startRectShare:(id)sender {
    
    //屏幕采集标志
int  dwScreenFlags = ANYCHAT_SCREENSOURCE_FLAGS_RECT;
    
    int width = [self.widthTextField.stringValue intValue];
    int height = [ self.heightTextField.stringValue intValue];
    
    [self startShare:dwScreenFlags dwWidth:width dwHeight:height];
}

- (IBAction)startWindowShare:(id)sender {
    if (self.windowTableView.selectedRow >= 0 && self.windowTableView.selectedRow < self.windowArr.count) {
        NSDictionary *dic = self.windowArr[self.windowTableView.selectedRow];
        
        int  dwScreenFlags = ANYCHAT_SCREENSOURCE_FLAGS_HOLDWND;
        int hwnd = [dic[@"hwnd"] intValue];
        NSLog(@"====hwnd:%d",hwnd);
//        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_SCREENHWND :hwnd];
        [AnyChatPlatform SetSDKOptionString:BRAC_SO_CORESDK_WRITELOG :[NSString stringWithFormat:@"name:%@ hwnd:%@",dic[@"name"],dic[@"hwnd"]]];
            [self startWindowShareInner:dwScreenFlags hwnd:hwnd];

    } else {
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = @"提醒";
        alert.informativeText = [NSString stringWithFormat:@"%@",@"请选择共享窗口"];
        [alert addButtonWithTitle:@"确定"];
        [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
            if (returnCode == NSAlertFirstButtonReturn){
                
            }
        }];
    }
    

}


- (void)startShare:(int)dwScreenFlags dwWidth:(int) dwWidth dwHeight:(int)dwHeight
{
    //开启屏幕共享功能控制
     int OPEN = 1;
//     BRAC_SetSDKOption(BRAC_SO_CORESDK_SCREENCAMERACTRL, OPEN);
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_CORESDK_SCREENCAMERACTRL :OPEN];

     //本地用户ID，-1代表本地用户(自己)
     int mSelfUserId = -1;
     //0号流
     int streamindex = 1;
  ////////////////////////
      //
     //枚举摄像头设备
//     var mDevices = BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE);
     int i = 0;
    int e = 0;//是否设置虚拟摄像头成功
//     for (i in mDevices) {
//
//         var DeviceName = mDevices[i].toString();
//         //不同的机器，摄像头的数量不一样，由于设备名称中包含位置序号信息，不同机器获取的虚拟摄像头设备名称前缀(位置序号信息)不同，但是都包含“Native Screen Camera”。
//         //虚拟摄像头设备名称中包含 Native Screen Camera ，通过匹配子串，找到虚拟摄像头。
//         if (DeviceName.indexOf("Native Screen Camera") != -1) {
//             //指定视频采集设备-虚拟摄像头
//             BRAC_SelectVideoCapture(BRAC_DEVICE_VIDEOCAPTURE, DeviceName);
//             //设置成功
//             e = 1;
//             break;
//         }
//
//     }
    NSMutableArray *videoArr = [AnyChatPlatform EnumVideoCapture];
    for (NSString *captureName in videoArr) {
        if ([captureName containsString:@"Native Screen Camera"]) {
            //指定视频采集设备-虚拟摄像头
//            BRAC_SelectVideoCapture(BRAC_DEVICE_VIDEOCAPTURE, DeviceName);
//            [AnyChatPlatform SelectVideoCapture:captureName];
            [AnyChatPlatform SetUserStreamInfoString:mSelfUserId :streamindex :BRAC_SO_LOCALVIDEO_DEVICENAME :captureName];
            //设置成功
            e = 1;
            break;
        }
    }
    


    int ANYCHAT_SDKCTRL_SCREENCAPPARAM = 72;            ///< 屏幕采集参数设置

  

        //屏幕区域左上角坐标（left，top）
    int dwLeft = 0;
    int dwTop = 0;

//        //屏幕区域
//    int dwWidth = 200;//1920;
//    int dwHeight = 100;//1080;

        //屏幕区域右下角坐标（right,bottom）
    int dwRight = dwLeft + dwWidth;
    int dwBottom = dwTop + dwHeight;

        //录制屏幕json参数
        NSMutableDictionary * screen_json_obj = @{
            @"left": @(dwLeft),
            @"right": @(dwRight),
            @"top": @(dwTop),
            @"bottom": @(dwBottom),
            @"flags": @(dwScreenFlags),
            
        }.mutableCopy;
    
    
    NSString *filterStr = self.filterSoftWareTextField.stringValue;
    if (filterStr.length > 0 && self.filterSoftWareCheckedButton.state == 1) {
        
        NSArray *arr = [filterStr componentsSeparatedByString:@","];
        NSMutableArray *listArr = [NSMutableArray array];
        for (NSString *title in arr) {
            if (title.length > 0) {
                [listArr addObject:@{@"app_name":title}];
            }
        }
        
        if (listArr.count > 0) {
            
            screen_json_obj[@"whitelist"] = @{
                @"whitelite_mode":@(1),
                @"limit_list":listArr
            };
        }
        
    }


        //屏幕采集参数设置
//        BRAC_SDKControl(ANYCHAT_SDKCTRL_SCREENCAPPARAM, JSON.stringify(screen_json_obj));
    NSString *strParam = [self objToJsonString:screen_json_obj];
    [AnyChatPlatform SetSDKOptionString:BRAC_SO_CORESDK_WRITELOG :strParam];
    
    [AnyChatPlatform SDKControl:ANYCHAT_SDKCTRL_SCREENCAPPARAM :strParam];
    
    
//    [AnyChatPlatform SetUserStreamInfoString:myUserId :SCREEN_STREAM_INDEX :BRAC_SO_LOCALVIDEO_DEVICENAME :captureName];
    
    [AnyChatPlatform SetVideoPosEx:mSelfUserId :self.localScreenView :0 :0 :0 :0 :streamindex :0];
    
    [AnyChatPlatform SetUserStreamInfoInt:-1 :streamindex :BRAC_SO_LOCALVIDEO_WIDTHCTRL :1920];
    [AnyChatPlatform SetUserStreamInfoInt:-1 :streamindex :BRAC_SO_LOCALVIDEO_HEIGHTCTRL :1080];
    [AnyChatPlatform SetUserStreamInfoInt:-1 :streamindex :BRAC_SO_LOCALVIDEO_BITRATECTRL :1000*1000];
    // 让视频参数生效
//    BRAC_SetUserStreamInfo(mSelfUserId, streamindex, BRAC_SO_LOCALVIDEO_APPLYPARAM, 1);
    [AnyChatPlatform SetUserStreamInfoInt:mSelfUserId :streamindex :BRAC_SO_LOCALVIDEO_APPLYPARAM :1];
    //打开本地屏幕摄像头(1号流)
//    int TURN_ON = 1;
//    BRAC_UserCameraControlEx(mSelfUserId, TURN_ON, streamindex, 0, "");
    [AnyChatPlatform UserCameraControlEx:mSelfUserId :1 :streamindex :0 :@""];
    
    
}


- (void)startWindowShareInner:(int)dwScreenFlags hwnd:(int)hwnd
{
    //开启屏幕共享功能控制
     int OPEN = 1;
//     BRAC_SetSDKOption(BRAC_SO_CORESDK_SCREENCAMERACTRL, OPEN);
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_CORESDK_SCREENCAMERACTRL :OPEN];

     //本地用户ID，-1代表本地用户(自己)
     int mSelfUserId = -1;
     //0号流
     int streamindex = 1;
  ////////////////////////
      //
     //枚举摄像头设备
//     var mDevices = BRAC_EnumDevices(BRAC_DEVICE_VIDEOCAPTURE);
     int i = 0;
    int e = 0;//是否设置虚拟摄像头成功
//     for (i in mDevices) {
//
//         var DeviceName = mDevices[i].toString();
//         //不同的机器，摄像头的数量不一样，由于设备名称中包含位置序号信息，不同机器获取的虚拟摄像头设备名称前缀(位置序号信息)不同，但是都包含“Native Screen Camera”。
//         //虚拟摄像头设备名称中包含 Native Screen Camera ，通过匹配子串，找到虚拟摄像头。
//         if (DeviceName.indexOf("Native Screen Camera") != -1) {
//             //指定视频采集设备-虚拟摄像头
//             BRAC_SelectVideoCapture(BRAC_DEVICE_VIDEOCAPTURE, DeviceName);
//             //设置成功
//             e = 1;
//             break;
//         }
//
//     }
    NSMutableArray *videoArr = [AnyChatPlatform EnumVideoCapture];
    for (NSString *captureName in videoArr) {
        if ([captureName containsString:@"Native Screen Camera"]) {
            //指定视频采集设备-虚拟摄像头
//            BRAC_SelectVideoCapture(BRAC_DEVICE_VIDEOCAPTURE, DeviceName);
//            [AnyChatPlatform SelectVideoCapture:captureName];
            [AnyChatPlatform SetUserStreamInfoString:mSelfUserId :streamindex :BRAC_SO_LOCALVIDEO_DEVICENAME :captureName];
            //设置成功
            e = 1;
            break;
        }
    }
    


    int ANYCHAT_SDKCTRL_SCREENCAPPARAM = 72;            ///< 屏幕采集参数设置

  

        //屏幕区域左上角坐标（left，top）
    int dwLeft = 0;
    int dwTop = 0;

//        //屏幕区域
//    int dwWidth = 200;//1920;
//    int dwHeight = 100;//1080;

        //屏幕区域右下角坐标（right,bottom）
//    int dwRight = dwLeft + dwWidth;
//    int dwBottom = dwTop + dwHeight;

        //录制屏幕json参数
        NSDictionary * screen_json_obj = @{
//            @"left": @(dwLeft),
//            @"right": @(dwRight),
//            @"top": @(dwTop),
//            @"bottom": @(dwBottom),
            @"flags": @(dwScreenFlags),
        };

        //屏幕采集参数设置
//        BRAC_SDKControl(ANYCHAT_SDKCTRL_SCREENCAPPARAM, JSON.stringify(screen_json_obj));
    NSString *strParam = [self objToJsonString:screen_json_obj];
    [AnyChatPlatform SDKControl:ANYCHAT_SDKCTRL_SCREENCAPPARAM :strParam];
    
    
//    [AnyChatPlatform SetUserStreamInfoString:myUserId :SCREEN_STREAM_INDEX :BRAC_SO_LOCALVIDEO_DEVICENAME :captureName];
    
    [AnyChatPlatform SetVideoPosEx:mSelfUserId :self.localScreenView :0 :0 :0 :0 :streamindex :0];
    
    [AnyChatPlatform SetUserStreamInfoInt:-1 :streamindex :BRAC_SO_LOCALVIDEO_WIDTHCTRL :1920];
    [AnyChatPlatform SetUserStreamInfoInt:-1 :streamindex :BRAC_SO_LOCALVIDEO_HEIGHTCTRL :1080];
    [AnyChatPlatform SetUserStreamInfoInt:-1 :streamindex :BRAC_SO_LOCALVIDEO_BITRATECTRL :1000*1000];

    [AnyChatPlatform SetUserStreamInfoInt:-1 :streamindex :BRAC_SO_LOCALVIDEO_QUALITYCTRL :3];
    // 让视频参数生效
//    BRAC_SetUserStreamInfo(mSelfUserId, streamindex, BRAC_SO_LOCALVIDEO_APPLYPARAM, 1);
    [AnyChatPlatform SetUserStreamInfoInt:mSelfUserId :streamindex :BRAC_SO_LOCALVIDEO_APPLYPARAM :1];
    //打开本地屏幕摄像头(1号流)
//    int TURN_ON = 1;
//    BRAC_UserCameraControlEx(mSelfUserId, TURN_ON, streamindex, 0, "");
    [AnyChatPlatform UserCameraControlEx:mSelfUserId :1 :streamindex :0 :@""];
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_SCREENHWND :hwnd];
    
    
}
- (NSString*)objToJsonString:(id)obj
{
    NSString *jsonString = nil;
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:obj
                                                       options:0 // Pass 0 if you don't care about the readability of the generated string
                                                         error:&error];
    if (!jsonData) {
        NSLog(@"json化失败: %@", error);
    } else {
        jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    return jsonString;
}

- (NSDictionary *)jsonStringToDictionary:(NSString *)jsonStr
{
    if (jsonStr == nil) {
        return nil;
    }
    
    NSData *jsonData = [jsonStr dataUsingEncoding:NSUTF8StringEncoding];
    NSError *error;
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                        options:NSJSONReadingMutableContainers
                                                          error:&error];
    if(error)
    {
        NSLog(@"json解析失败: %@", error);
        return nil;
    }
    return dic;
}

- (IBAction)windowReload:(id)sender {
    
    if (!listInfo) {
        listInfo = new CmacOSWindowListInfo();
    }
    
    std::string screenWindow =  listInfo->getOnScreenWindowInfoList();
    NSString *screenWindowStr= [NSString stringWithCString:screenWindow.c_str() encoding:NSUTF8StringEncoding];
    NSLog(@"====%@",screenWindowStr);
    [AnyChatPlatform SetSDKOptionString:BRAC_SO_CORESDK_WRITELOG :screenWindowStr];
    NSDictionary *dic = [self jsonStringToDictionary:screenWindowStr];
    
    self.windowArr = dic[@"hwndinfo"];
    [self.windowTableView reloadData];
}


@end


