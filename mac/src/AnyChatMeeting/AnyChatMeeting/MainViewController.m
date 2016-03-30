//
//  MainViewController.m
//  AnyChatMeeting
//
//  Created by bairuitech on 15/6/1.
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

#define imageViewOriginX 265
#define imageViewOriginY 371
#define imageViewWidth 210
#define imageViewHeight 136
#define imageViewPadding 10

@interface MainViewController ()<AnyChatNotifyMessageDelegate, NSTableViewDelegate, NSTableViewDataSource>

@property(strong, nonatomic)AnyChatPlatform *anychat;
@property(assign, nonatomic)int userId;                                         //用户id
@property(strong, nonatomic)NSMutableArray *roomUserModelArr;                   //房间用户模型数组
@property(assign, nonatomic)int newUserId;                                      //新用户id
@property(strong, nonatomic)AVCaptureVideoPreviewLayer  *localCaptureLayer;

@property (weak) IBOutlet NSTextField *server;                                  //服务器地址
@property (weak) IBOutlet NSTextField *port;                                    //端口
@property (weak) IBOutlet NSTextField *username;                                //用户名
@property (weak) IBOutlet NSTextField *roomId;                                  //房间号
@property (weak) IBOutlet NSButton *loginButton;                                //登录按钮
@property (weak) IBOutlet NSButton *logoutButton;                               //注销按钮
@property (strong) IBOutlet NSTextView *logView;                                //日志输出
@property (weak) IBOutlet NSTableView *tableView;                               //用户列表
@property (weak) IBOutlet NSView *localVideoView;                               //本地视频窗口

@property(strong, nonatomic)NSMutableArray *videoChatUserArr;                   //视频通话中用户

- (IBAction)loginAction:(NSButton *)sender;                                     //登录事件
- (IBAction)logoutAction:(NSButton *)sender;                                    //注销事件

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
    self.anychat = anychat;
    
    //设置本地视频窗口
    self.localVideoView.wantsLayer = YES;
    self.localVideoView.layer.contents = (id)[self convertUIImageToCGImageRef:[NSImage imageNamed:@"BG_macVideo"]];
 
    //注册通知中心
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    self.videoChatUserArr = [NSMutableArray arrayWithCapacity:4];
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
        self.userId = dwUserId;
        //进入房间
        [AnyChatPlatform EnterRoom:[self.roomId intValue] :@""];
        appendMessage = [NSString stringWithFormat:@"• Login successed. Self UserId: %d", dwUserId];
    }else {
        appendMessage = [NSString stringWithFormat:@"Login failed(ErrorCode:%i)",dwErrorCode];
    }
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
    
    [self setOnlineUserIsSetVideo:YES];
    if(self.roomUserModelArr.count <= 4){
        [self setAllVideoChatView];
        // 刷新用户列表
        [self.tableView reloadData];
        appendMessage = [NSString stringWithFormat:@"• OnlineUserCount:%ld", self.roomUserModelArr.count];
    }else {
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = @"信息提醒";
        alert.informativeText = @"多人视频人数过多，请稍后再试";
        [alert addButtonWithTitle:@"确定"];
        [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
            [AnyChatPlatform LeaveRoom:-1];
            [AnyChatPlatform Logout];
            self.loginButton.enabled = YES;
            self.logoutButton.enabled = NO;
        }];
        appendMessage = [NSString stringWithFormat:@"• Too Many People Online,Please Try Again Later..."];
    }
    
    [self appendLogMessage:appendMessage];
}

// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId {
    NSString *appendMessage;
    User *newUser = [User userWithUserId:[NSString stringWithFormat:@"%d",dwUserId]];
    
    
    // 1.多人视频人数还没满，请求在线视频
    if ([self getVideoChatOnlineUserNum] <4) {
        
        int tag = [self getVideoTag];

        [self setupVideoChatViewTag:tag-1 user:newUser flag:YES];

        //视频数组中把标记位替换/直接追加
        if (tag>[self getVideoChatOnlineUserNum]) {
            [self.videoChatUserArr addObject:[NSString stringWithFormat:@"%d",dwUserId]];
        }else {
            [self.videoChatUserArr replaceObjectAtIndex:tag-1 withObject:[NSString stringWithFormat:@"%d",dwUserId]];
        }
        appendMessage = [NSString stringWithFormat:@"• New Online Video User:%d",dwUserId];
    } else {
        appendMessage = [NSString stringWithFormat:@"• New Online User:%d",dwUserId];
    }
    
    // 2.刷新用户列表
    [self setOnlineUserIsSetVideo:NO];
    [self.tableView reloadData];
    
    [self appendLogMessage:appendMessage];

}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId {
    NSString *appendMessage;
    // 1.在视频聊天中
    NSUInteger index = [self.videoChatUserArr indexOfObject:[NSString stringWithFormat:@"%d",dwUserId]];
    if (index != NSNotFound) { //在视频数组中
        
        int videoNum = (int)self.videoChatUserArr.count-1;
        if (index == videoNum) { //视频队列中最后一位，直接删除数据
            
            [self.videoChatUserArr removeLastObject];
            
            int num= [self getVideoChatOnlineUserNum];
            if (num == 0) [self.videoChatUserArr removeAllObjects];
            
            //删除最后数据后，末尾是标记位，则一直删除(从末尾反方向开始删除)
            int c=(int)self.videoChatUserArr.count-1;
            for (int i=c; i>=0; i--) {
                NSString *uid = self.videoChatUserArr[i];
                if ([uid isEqualToString:@"flag"]){
                    [self.videoChatUserArr removeLastObject];
                }else {
                    break;
                }
            }
            
            

            
            
        }else { //视频队列中中间的某位，做上标记空位
            [self.videoChatUserArr replaceObjectAtIndex:index withObject:@"flag"];
        }
        
        [self setupVideoChatViewTag:(int)index user:[User userWithUserId:[NSString stringWithFormat:@"%d",dwUserId]] flag:NO];
        
        
        appendMessage = [NSString stringWithFormat:@"• Online Video User Leave:%d",dwUserId];
    } else {
        appendMessage = [NSString stringWithFormat:@"• Online User Leave:%d",dwUserId];
    }
    
    // 2.刷新用户列表
    [self setOnlineUserIsSetVideo:NO];
    [self.tableView reloadData];
    [self appendLogMessage:appendMessage];
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode {
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @"信息提醒";
    alert.informativeText = @"网络状态不稳定，已断开连接，请重新登录";
    [alert addButtonWithTitle:@"确定"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            
            for (int i=0; i<self.videoChatUserArr.count; i++) {
                NSString *uid = self.videoChatUserArr[i];
                if (![uid isEqualToString:@"flag"]) {
                    [self setupVideoChatViewTag:i user:[User userWithUserId:uid] flag:NO];
                }
            }
            
            self.loginButton.enabled = YES;
            self.logoutButton.enabled = NO;
            
            [AnyChatPlatform UserSpeakControl: -1 : NO];
            [AnyChatPlatform UserCameraControl: -1 : NO];
            
            [AnyChatPlatform LeaveRoom:-1];
            [AnyChatPlatform Logout];
            
            [self.roomUserModelArr removeAllObjects];
            [self.tableView reloadData];
            
            self.server.stringValue = @"";
            self.port.stringValue = @"";
            self.username.stringValue = @"";
            [self appendLogMessage:[NSString stringWithFormat:@"• LinkClose(ErrorCode:%i)",dwErrorCode]];
        }
    }];
    
}

#pragma mark - NSTableView delegate & datasource methods


- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return self.roomUserModelArr.count;
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    
    NSTableCellView *cellView = [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
    
    if([tableColumn.identifier isEqualToString:@"userID"]) {
        User *user = self.roomUserModelArr[row];
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

/**
 *  设置房间用户模型
 *
 */
- (void) setOnlineUserIsSetVideo:(BOOL)isSet
{
    
    NSMutableArray *onlineUserArr = [NSMutableArray new];
    NSMutableArray *roomUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
    for (int i=0; i<roomUserList.count; i++) {
        NSString *userId = roomUserList[i];
        if ([AnyChatPlatform GetFriendStatus:[userId intValue]] == 1) {
            [onlineUserArr addObject:[User userWithUserId:userId]];
            //把用户添加到视频聊天数组中
            if (isSet) [self.videoChatUserArr addObject:[NSString stringWithFormat:@"%@",userId]];
            
        }
    }
    
    self.roomUserModelArr = onlineUserArr;

}



/**
 *  设置多个视频聊天的窗口
 *
 */
- (void)setAllVideoChatView {
    
    if (self.roomUserModelArr.count>0) {
        for (int i=0; i<self.roomUserModelArr.count; i++) {
            [self setupVideoChatViewTag:i user:self.roomUserModelArr[i] flag:YES];
        }
    }
}

/**
 *  设置单个视频聊天的窗口
 *  
 *  tag:  标题窗口位置
 *  user: 远程视频聊天的用户数据模型
 *  flag: YES:开启对方音视频请求   NO:关闭对方音视频
 */
- (void)setupVideoChatViewTag:(int)tag user:(User *)user flag:(BOOL)flag{
    
    if (tag>4) return;
    
    NSTextField *titleLabel = [self.view viewWithTag:100+tag];
    NSImageView *imageView = [self.view viewWithTag:1000+tag];
    
    // 视频请求
    [AnyChatPlatform UserSpeakControl:[user.userId intValue] :flag];
    [AnyChatPlatform UserCameraControl:[user.userId intValue] :flag];
    
    if (flag == YES) {
        // 设置窗口标题
        [titleLabel setStringValue:user.userName];
        // 设置视频窗口
        [AnyChatPlatform SetVideoPos:[user.userId intValue] :imageView :0 :0 :0 :0];
    }else {
        [titleLabel setStringValue:@""];
        imageView.image = [NSImage imageNamed:@"BG_remote"];
    }
    
}




/**
 *  去除占位符后在线视频的人数
 */
- (int)getVideoChatOnlineUserNum {
    
    int num = (int)self.videoChatUserArr.count;
    for (NSString *str in self.videoChatUserArr) {
        if ([str isEqualToString:@"flag"]) num--;
    }
    return num;
}

/**
 *  获取视频插入位置
 */
- (int)getVideoTag {
    //默认位置在最后
    int tag=(int)self.videoChatUserArr.count+1;
    //有占位符
    for (int i=0; i<self.videoChatUserArr.count; i++) {
        NSString *userId = self.videoChatUserArr[i];
        if ([userId isEqualToString:@"flag"]){
            return tag = i+1;
        }
    }
    return tag;
}

//创建和初始化 AVCaptureVideoPreviewLayer 对象,实现本地视频的显示
- (void) OnLocalVideoInit:(id)session {
    self.localCaptureLayer = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.localCaptureLayer.frame = CGRectMake(0, 0, 212, 141);
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



#pragma mark - Action
//登录
- (IBAction)loginAction:(NSButton *)sender {
    
    if (self.server.stringValue.length == 0) self.server.stringValue = @"demo.anychat.cn";
    if (self.port.stringValue.length == 0)  self.port.stringValue = @"8906";
    if (self.username.stringValue.length == 0) self.username.stringValue = @"Jack";
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
    alert.informativeText = @"你确定要注销AnyChat视频聊天吗";
    [alert addButtonWithTitle:@"确定"];
    [alert addButtonWithTitle:@"取消"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            
            for (int i=0; i<self.videoChatUserArr.count; i++) {
                NSString *uid = self.videoChatUserArr[i];
                if (![uid isEqualToString:@"flag"]) {
                    [self setupVideoChatViewTag:i user:[User userWithUserId:uid] flag:NO];
                }
            }
            
            [AnyChatPlatform UserSpeakControl: -1 : NO];
            [AnyChatPlatform UserCameraControl: -1 : NO];
            
            [AnyChatPlatform LeaveRoom:-1];
            [AnyChatPlatform Logout];
            
            self.loginButton.enabled = YES;
            self.logoutButton.enabled = NO;
            
            [self.roomUserModelArr removeAllObjects];
            [self.videoChatUserArr removeAllObjects];
            
            [self.tableView reloadData];

            self.server.stringValue = @"";
            self.port.stringValue = @"";
            self.username.stringValue = @"";
            self.roomId.stringValue = @"";
            self.logView.string = @"";
            
        }
    }];
    
}


@end
