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

#import <AnyChatCoreSDK/AnyChatCoreSDK.h>
#import "User.h"
#import "MeberCellView.h"

#define imageViewOriginX 265
#define imageViewOriginY 371
#define imageViewWidth 210
#define imageViewHeight 136
#define imageViewPadding 10

#define kSendAllCode @"sendAll"
#define kSendOneCode @"sendOne"
#define kCommandCode @"command"

#define kCMD_Meeting_Exit @"CMD_Meeting_Exit"
#define kCMD_Meeting_Allow @"CMD_Meeting_Allow"
#define kCMD_Meeting_Forbid @"CMD_Meeting_Forbid"
#define kCMD_Meeting_DeviceState @"CMD_Meeting_DeviceState"
#define kCMD_Meeting_mainView @"CMD_Meeting_mainView"

#define kTypeAudio @"Audio"
#define kTypeVideo @"Video"


#define kAdminUserName @"admin"
#define kAdminUserId 1000000

@interface MainViewController ()<AnyChatNotifyMessageDelegate, NSTableViewDelegate, NSTableViewDataSource>

@property(strong, nonatomic)AnyChatPlatform *anychat;
@property(assign, nonatomic)int userId;                                         //用户id
@property(strong, nonatomic)NSMutableArray *roomUserModelArr;                   //房间用户模型数组
@property(assign, nonatomic)int newUserId;                                      //新用户id
@property(strong, nonatomic)AVCaptureVideoPreviewLayer  *localCaptureLayer;

@property (weak) IBOutlet NSTextField *server;                                  //服务器地址
@property (weak) IBOutlet NSTextField *port;                                    //端口
@property (weak) IBOutlet NSTextField *appIdTextField;

@property (weak) IBOutlet NSTextField *username;                                //用户名
@property (weak) IBOutlet NSTextField *roomId;                                  //房间号
@property (weak) IBOutlet NSButton *loginButton;                                //登录按钮
@property (weak) IBOutlet NSButton *logoutButton;                               //注销按钮
@property (strong) IBOutlet NSTextView *logView;                                //日志输出
@property (weak) IBOutlet NSTableView *tableView;                               //用户列表
@property (weak) IBOutlet NSImageView *localVideoView;                               //本地视频窗口

@property(strong, nonatomic)NSMutableArray *videoChatUserArr;                   //视频通话中用户

- (IBAction)loginAction:(NSButton *)sender;                                     //登录事件
- (IBAction)logoutAction:(NSButton *)sender;                                    //注销事件
@property (weak) IBOutlet NSTextField *sendTextField;

@property(assign, nonatomic)int sendTextUserId;
@property (weak) IBOutlet NSButton *cameraButton;
@property (weak) IBOutlet NSButton *micButton;

@property (weak) IBOutlet NSTextField *sendTextTip;

@property(assign, nonatomic) BOOL isCloseCamera;
@property(assign, nonatomic) BOOL isCloseMic;

@property (strong, nonatomic) NSMutableArray                *cameraDeviceArray;
@property (weak) IBOutlet NSTableView *camTableView;

@property (weak) IBOutlet NSTextField *imagexTextField;
@property (weak) IBOutlet NSTextField *imageyTextField;
@property (weak) IBOutlet NSButton *waterImageButton;

@property (weak) IBOutlet NSTextField *textxTextField;
@property (weak) IBOutlet NSTextField *textyTextField;
@property (weak) IBOutlet NSButton *waterTextButton;

@property(assign, nonatomic)int isShowWaterText;
@property(assign, nonatomic)int isShowWaterImage;

@property (weak) IBOutlet NSComboBox *recodeMode;
@property (weak) IBOutlet NSButton *startdRecordButton;
@property (weak) IBOutlet NSButton *endRecordButton;
@property (weak) IBOutlet NSButton *snapButton;

@property(nonatomic, assign)int recordFlags;                                    //录像标记
@property(nonatomic, copy)NSString *recordStr;                                  //录像返回字符串
@property (weak) IBOutlet NSButton *onlyAudioButton;


@property(assign, nonatomic) int mainUserId;

@property (weak) IBOutlet NSButton *selfMainButton;

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
    anychat.textMsgDelegate = self;
    anychat.recordSnapShotDelegate = self;
    
    self.anychat = anychat;
    
    //设置本地视频窗口
    self.localVideoView.wantsLayer = YES;
    self.localVideoView.layer.contents = (id)[self convertUIImageToCGImageRef:[NSImage imageNamed:@"BG_macVideo"]];
 
    //注册通知中心
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    self.videoChatUserArr = [NSMutableArray arrayWithCapacity:4];
    self.selfMainButton.hidden = YES;

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
        NSMutableArray* cameraDeviceArray = [AnyChatPlatform EnumVideoCapture];
        self.cameraDeviceArray = cameraDeviceArray;
        NSLog(@"===cameraDevice count:%d",(int)self.cameraDeviceArray.count);
        [self.camTableView reloadData];
        
        if (cameraDeviceArray.count > 0) {
//            if(cameraDeviceArray.count >= 2)
//                [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:1]];
//            else
                [AnyChatPlatform SelectVideoCapture:[cameraDeviceArray objectAtIndex:0]];
        }
        
        [self openOrCloseLocalVideo:YES];
        [self openOrCloseLocalAudio:YES];
        
        [self showWarterMark];
        appendMessage = [NSString stringWithFormat:@"• Enter Room successed. Room Id: %d", dwRoomId];
    }else {
        appendMessage = [NSString stringWithFormat:@"• Enter room failed(ErrorCode:%i)", dwRoomId];
    }
    [self appendLogMessage:appendMessage];
    
    
    
}

- (void)openOrCloseLocalVideo:(BOOL)open
{
    self.isCloseCamera = !open;
    if (open) {
        
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :0];
        [AnyChatPlatform UserCameraControl:-1 :YES];
        [AnyChatPlatform SetVideoPos:-1 :self.localVideoView :0 :0 :0 :0];
    } else {
        [AnyChatPlatform UserCameraControl:-1 :NO];
    }
    
    [self updateCameraMicUI];
    
    [self CMD_Meeting_DeviceState:open type:kTypeVideo];
}

- (void)openOrCloseLocalAudio:(BOOL)open
{
    self.isCloseMic = !open;
    
    if (open) {
        [AnyChatPlatform UserSpeakControl:-1 :YES];
    } else {
        [AnyChatPlatform UserSpeakControl:-1 :NO];
    }
    
    [self updateCameraMicUI];
    
    [self CMD_Meeting_DeviceState:open type:kTypeAudio];
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
            self.userId = 0;
            self.sendTextField.stringValue = @"";
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
    if (self.userId == kAdminUserId) {
        [self CMD_Meeting_mainView:self.mainUserId];
    }
    
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
//    return self.roomUserModelArr.count;
    if (tableView == self.tableView) {
        return [self.roomUserModelArr count];
    } else if (tableView == self.camTableView) {
        return [self.cameraDeviceArray count];
    }
    return 0;
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    
    NSTableCellView *aCellView = [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
//    MeberCellView *cellView = [tableView makeViewWithIdentifier:@"MemberCellViewID" owner:self];
    
    if([tableColumn.identifier isEqualToString:@"MemberCellViewID"]) {
        MeberCellView *cellView = (MeberCellView *)aCellView;
        User *user = self.roomUserModelArr[row];
        
        cellView.user = user;
        cellView.delegate = self;
        
        //设置头像
        cellView.imageView.image = [NSImage imageNamed:user.userFace];
        //设置用户名
        int userID = [user.userId intValue];
        NSString *userName = user.userName;
        if (self.userId == userID) {
            cellView.userNameTextField.stringValue = [NSString stringWithFormat:@"%@（自己）",userName];
        }else {
            cellView.userNameTextField.stringValue = [NSString stringWithFormat:@"%@（%d）",userName,userID];
        }
        [cellView updateUI];
        if (self.userId == kAdminUserId) {
            cellView.mainButton.hidden = NO;
        } else {
            cellView.mainButton.hidden = YES;
        }
        
        return cellView;
    }else if( [tableColumn.identifier isEqualToString:@"camID"] )
    {
        NSTableCellView *cellView = aCellView;
        if (row < self.cameraDeviceArray.count) {
            NSString *deviceName = [self.cameraDeviceArray objectAtIndex:row];
            cellView.textField.stringValue = deviceName;
        }
    }
    return aCellView;
    
}

- (void)tableViewSelectionDidChange:(NSNotification *)notification
{
    if (notification.object == self.tableView) {

        if (self.tableView.selectedRow >= 0 && self.tableView.selectedRow < self.roomUserModelArr.count) {
            
            User *user = self.roomUserModelArr[self.tableView.selectedRow];
            self.sendTextUserId = [user.userId intValue];
            
            self.sendTextTip.stringValue = [NSString stringWithFormat:@"发送给 %@:",user.userName];
        } else {
            self.sendTextUserId = 0;
            [self.tableView deselectRow:self.tableView.selectedRow];
            
            self.sendTextTip.stringValue = [NSString stringWithFormat:@"发送给 %@:",@"所有人"];
        }
        

    }else if (notification.object == self.camTableView) {
        if (self.camTableView.selectedRow >= 0 && self.camTableView.selectedRow < self.cameraDeviceArray.count) {
            [AnyChatPlatform SelectVideoCapture:[self.cameraDeviceArray objectAtIndex:self.camTableView.selectedRow]];
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
    [self.logView scrollRangeToVisible:NSMakeRange(self.logView.string.length, 0)];
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
        //if ([AnyChatPlatform GetFriendStatus:[userId intValue]] == 1)
        {
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
    NSTextField *mainLabel = [self.view viewWithTag:10000+tag];
    
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
        mainLabel.hidden = YES;
    }
    
}


/// @param userId 用户id
- (void)setMainVideoChatViewWithuserId:(int)userId {
    self.mainUserId = userId;
    // 自己的主视图标志
    NSTextField *mainViewLabel = [self.view viewWithTag:9999];
    mainViewLabel.hidden = self.userId != userId;
    
    // 远程的主视图标志
    for (int i=0; i<self.videoChatUserArr.count; i++) {
        int userID = [[self.videoChatUserArr objectAtIndex:i] intValue];
        NSTextField *mainViewLabel = [self.view viewWithTag:10000+i];
        mainViewLabel.hidden = userId != userID;
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


#pragma mark - Action
//登录
- (IBAction)loginAction:(NSButton *)sender {
    
    if (self.server.stringValue.length == 0) self.server.stringValue = @"mini.anychat.cn";
    if (self.port.stringValue.length == 0)  self.port.stringValue = @"8906";
    if (self.username.stringValue.length == 0) self.username.stringValue = @"Jack";
    if (self.roomId.stringValue.length == 0) self.roomId.stringValue = @"2";
    
    self.isShowWaterText = 1;
    self.isShowWaterImage = 1;
    
    NSString *appID = self.appIdTextField.stringValue;
    if (appID.length>0) {
        
        [AnyChatPlatform SetSDKOptionString:BRAC_SO_CLOUD_APPGUID :appID];
    }
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
//    [AnyChatPlatform Login:self.username.stringValue :@""];
    if ([self.username.stringValue isEqualToString:kAdminUserName]) {
        [AnyChatPlatform LoginEx:kAdminUserName :kAdminUserId :@"" :appID :0 :@"" :@""];
        self.selfMainButton.hidden = NO;
    } else {
        [AnyChatPlatform Login:self.username.stringValue :@""];
        self.selfMainButton.hidden = YES;
    }
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
            
            [self anychatLogout];
            
        }
    }];
    
}

-(void)anychatLogout
{
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
    
    self.isCloseMic = NO;
    self.isCloseCamera = NO;
    [self updateCameraMicUI];
    
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
    
    [self.cameraDeviceArray removeAllObjects];
    [self.camTableView reloadData];
    [self setMainVideoChatViewWithuserId:-999999999];
}

- (IBAction)sendAction:(NSButton *)sender {
    NSString *sendText = self.sendTextField.stringValue;
    if (sendText.length > 0) {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        
        dict[@"data"] = @{
                @"msg":sendText
            };
        
        
        if (self.sendTextUserId == 0) {
            //群发
            dict[@"code"] = kSendAllCode;
            [self sendCodeTextAll:dict];
        } else {
            //私聊
            
            dict[@"code"] = kSendOneCode;
            [self sendCodeTextOne:dict userId:self.sendTextUserId];
        }
        
        
        {
            NSString *timeStr = [self getTimeStr];
            
            NSString *showMsg = @"";
            NSString *code = dict[@"code"];
            NSString *msg = sendText;
            if ([code isEqualToString:kSendAllCode]) {
                showMsg = [NSString stringWithFormat:@"[发送群聊消息]%@",msg];
            } else if ([code isEqualToString:kSendOneCode]) {
                NSString *username = [AnyChatPlatform GetUserName:self.sendTextUserId];
                showMsg = [NSString stringWithFormat:@"[发给%@的私聊消息]%@",username,msg];
            }
            
            
            NSString *appendMessage = [NSString stringWithFormat:@"%@ %@",timeStr,showMsg];
            
            [self appendLogMessage:appendMessage];
        }

    }
    self.sendTextField.stringValue = @"";
}

- (void)sendCodeTextAll:(NSDictionary *)dict
{
    NSString *codeText =  [self objToJsonString:dict];
    NSLog(@"====codeTextAll:%@",codeText);
    [AnyChatPlatform SendTextMessage:0 :NO :codeText];
}

- (void)sendCodeTextOne:(NSDictionary *)dict userId:(int)userId
{
    NSString *codeText =  [self objToJsonString:dict];
    NSLog(@"====codeTextOne userId:%d :%@",userId, codeText);
    [AnyChatPlatform SendTextMessage:userId :YES :codeText];
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

- (void) OnAnyChatTextMsgCallBack:(int) dwFromUserid : (int) dwToUserid : (BOOL) bSecret : (NSString*) lpMsgBuf
{
    NSDictionary *dict = [self jsonStringToDictionary:lpMsgBuf];
    if (dict) {

        NSString *timeStr = [self getTimeStr];
        
        NSString *username = [AnyChatPlatform GetUserName:dwFromUserid];
        
        NSString *code = dict[@"code"];
        if (![code isKindOfClass:[NSString class]]) return;
        if ([code isEqualToString:kSendAllCode] || [code isEqualToString:kSendOneCode] ) {
            NSString *msg = dict[@"data"][@"msg"];
            NSString *showMsg = @"";
            if ([code isEqualToString:kSendAllCode]) {
                showMsg = [NSString stringWithFormat:@"[收到%@的群聊消息]%@",username,msg];
            } else if ([code isEqualToString:kSendOneCode]) {
                showMsg = [NSString stringWithFormat:@"[收到%@的私聊消息]%@",username,msg];
            }
            
            
            NSString *appendMessage = [NSString stringWithFormat:@"%@ %@",timeStr,showMsg];
            
            [self appendLogMessage:appendMessage];
        } else if ([code isEqualToString:kCommandCode]  ){
            [self onCommandCallBack:dwFromUserid :dwToUserid :bSecret :lpMsgBuf];
        }
        
    }
    
}

- (void) onCommandCallBack:(int) dwFromUserid : (int) dwToUserid : (BOOL) bSecret : (NSString*) lpMsgBuf
{
    NSLog(@"====onCommandCallBack:%@",lpMsgBuf);
    NSDictionary *dict = [self jsonStringToDictionary:lpMsgBuf];
    if (dict) {
        NSDictionary *dataDict = dict[@"data"];
        NSString *cmd = dataDict[@"cmd"];
        NSDictionary *cmdDict = dataDict[@"data"];
        
        if ([cmd isEqualToString:kCMD_Meeting_Exit]) {
            [self anychatLogout];
        } else if ([cmd isEqualToString:kCMD_Meeting_Allow]) {
            NSString *type = cmdDict[@"type"];
            if ([type isEqualToString:kTypeAudio]) {
                [self openOrCloseLocalAudio:YES];
            } else if ([type isEqualToString:kTypeVideo]) {
                [self openOrCloseLocalVideo:YES];
            }
        } else if ([cmd isEqualToString:kCMD_Meeting_Forbid]) {
            NSString *type = cmdDict[@"type"];
            if ([type isEqualToString:kTypeAudio]) {
                [self openOrCloseLocalAudio:NO];
            } else if ([type isEqualToString:kTypeVideo]) {
                [self openOrCloseLocalVideo:NO];
            }
        } else if ([cmd isEqualToString:kCMD_Meeting_DeviceState]) {
            NSString *type = cmdDict[@"type"];
            int state = [cmdDict[@"state"] intValue];
            
            [self updateRemoteUI:dwFromUserid type:type state:state];

        }else if ([cmd isEqualToString:kCMD_Meeting_mainView]) {
            
            int userId = [cmdDict[@"userid"] intValue];
            [self setMainVideoChatViewWithuserId:userId];
        }
        
    }
}

- (void)updateRemoteUI:(int)dwUserId type:(NSString *)type state:(int)state
{
    // 1.在视频聊天中
    NSUInteger index = [self.videoChatUserArr indexOfObject:[NSString stringWithFormat:@"%d",dwUserId]];
    if (index != NSNotFound) { //在视频数组中
        
//        int videoNum = (int)self.videoChatUserArr.count-1;
//        if (index == videoNum) { //视频队列中最后一位，直接删除数据
//
//            [self.videoChatUserArr removeLastObject];
//
//            int num= [self getVideoChatOnlineUserNum];
//            if (num == 0) [self.videoChatUserArr removeAllObjects];
//
//            //删除最后数据后，末尾是标记位，则一直删除(从末尾反方向开始删除)
//            int c=(int)self.videoChatUserArr.count-1;
//            for (int i=c; i>=0; i--) {
//                NSString *uid = self.videoChatUserArr[i];
//                if ([uid isEqualToString:@"flag"]){
//                    [self.videoChatUserArr removeLastObject];
//                }else {
//                    break;
//                }
//            }
//
//
//
//
//
//        }else { //视频队列中中间的某位，做上标记空位
//            [self.videoChatUserArr replaceObjectAtIndex:index withObject:@"flag"];
//        }
//
//        [self setupVideoChatViewTag:(int)index user:[User userWithUserId:[NSString stringWithFormat:@"%d",dwUserId]] flag:NO];
        
        User *targetUser;
        for (int i=0; i<self.roomUserModelArr.count; i++) {
            User *user = [self.roomUserModelArr objectAtIndex:i];
            int userID = [user.userId intValue];
            
            if (userID == dwUserId) {
                targetUser = user;
                break;
            }
        }
        
        
        int tag = (int)index;
        if (tag>4) return;
        
//        NSTextField *titleLabel = [self.view viewWithTag:100+tag];
//        NSImageView *imageView = [self.view viewWithTag:1000+tag];
        
        if (targetUser) {
            if ([type isEqualToString:kTypeVideo]) {
                targetUser.isCloseCamera = !state;
                
                [self setupVideoChatViewTag:(int)index user:targetUser flag:state];
                
            } if ([type isEqualToString:kTypeAudio]) {
                targetUser.isCloseMic = !state;
            }
        }
        [self.tableView reloadData];

    }
    
    
}


- (NSString *)getTimeStr
{
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"HH:mm:ss"];
    NSString *timeStr = [dateFormatter stringFromDate:[NSDate date]];
    return timeStr;
}

- (IBAction)cameraAction:(NSButton *)sender {
    if (self.userId == 0) return;
    
    self.isCloseCamera = !self.isCloseCamera;

    if (self.isCloseCamera) {
        [self openOrCloseLocalVideo:NO];
    } else {
        [self openOrCloseLocalVideo:YES];
    }
    
}

- (IBAction)microphoneAction:(NSButton *)sender {
    if (self.userId == 0) return;
    
    self.isCloseMic = !self.isCloseMic;
    
    if (self.isCloseMic) {
        [self openOrCloseLocalAudio:NO];
    } else {
        [self openOrCloseLocalAudio:YES];
    }

}

- (void)updateCameraMicUI
{
    if (self.isCloseCamera) {
        [self.cameraButton setImage:[NSImage imageNamed:@"camera_false"]];
    } else {
        [self.cameraButton setImage:[NSImage imageNamed:@"camera_true"]];
    }
    
    if (self.isCloseMic) {
        [self.micButton setImage:[NSImage imageNamed:@"microphone_false"]];
    } else {
        [self.micButton setImage:[NSImage imageNamed:@"microphone_true"]];
    }
}

- (void)tableViewCell:(MeberCellView *)cell didClickCamera:(NSButton *)button
{
    if (cell.user) {
        NSLog(@"cell user:%@",cell.user.userId);
        
        NSString *type=kTypeVideo;
        if (cell.user.isCloseCamera) {
            [self CMD_Meeting_Forbid:[cell.user.userId intValue] type:type];
            
            {
//                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//
//                });
            }
        } else {
            [self CMD_Meeting_Allow:[cell.user.userId intValue] type:type];
        }
        
        NSUInteger index = [self.videoChatUserArr indexOfObject:cell.user.userId];
        if (index != NSNotFound) { //在视频数组中
            int state = !cell.user.isCloseCamera;
            
//            [self setupVideoChatViewTag:(int)index user:cell.user flag:state];
        }
        

        
    }
}

- (void)tableViewCell:(MeberCellView *)cell didClickMic:(NSButton *)button
{
    if (cell.user) {
        NSLog(@"cell user:%@",cell.user.userId);
        
        NSString *type=kTypeAudio;
        if (cell.user.isCloseMic) {
            [self CMD_Meeting_Forbid:[cell.user.userId intValue] type:type];
        } else {
            [self CMD_Meeting_Allow:[cell.user.userId intValue] type:type];
        }
    }
    
}
- (void)tableViewCell:(MeberCellView *)cell didClickRemove:(NSButton *)button
{
    if (cell.user) {
        NSLog(@"cell user:%@",cell.user.userId);
        
        [self CMD_Meeting_Exit:[cell.user.userId intValue]];
    }
}

- (void)tableViewCell:(MeberCellView *)cell didClickMain:(NSButton *)button
{
    if (cell.user) {
        NSLog(@"cell user:%@",cell.user.userId);
        int userId = [cell.user.userId intValue];
        [self CMD_Meeting_mainView:userId];
        self.mainUserId = userId;
        [self setMainVideoChatViewWithuserId:userId];
    }
}

- (void)CMD_Meeting_mainView:(int)userId
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    
    dict[@"data"] = @{
            @"cmd":kCMD_Meeting_mainView,
            @"data":@{
                @"userid":@(userId)
            }
        };
    // 设置主屏幕
    dict[@"code"] = kCommandCode;
    [self sendCodeTextAll:dict];
}


- (void)CMD_Meeting_Exit:(int)userId
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    
    dict[@"data"] = @{
            @"cmd":kCMD_Meeting_Exit
        };
    

    //私聊
    
    dict[@"code"] = kCommandCode;
    [self sendCodeTextOne:dict userId:userId];
    
}

- (void)CMD_Meeting_Allow:(int)userId type:(NSString *)type
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    
    dict[@"data"] = @{
            @"cmd":kCMD_Meeting_Allow,
            @"data":@{
                @"type":type
            }
        };
    

    //私聊
    
    dict[@"code"] = kCommandCode;
    [self sendCodeTextOne:dict userId:userId];
    
}

- (void)CMD_Meeting_Forbid:(int)userId type:(NSString *)type
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    
    dict[@"data"] = @{
            @"cmd":kCMD_Meeting_Forbid,
            @"data":@{
                @"type":type
            }
        };
    

    //私聊
    
    dict[@"code"] = kCommandCode;
    [self sendCodeTextOne:dict userId:userId];
    
}


- (void)CMD_Meeting_DeviceState:(int)state type:(NSString *)type
{
    NSMutableDictionary *dict = [NSMutableDictionary dictionary];
    
    dict[@"data"] = @{
            @"cmd":kCMD_Meeting_DeviceState,
            @"data":@{
                @"type":type,
                @"state":@(state)
            }
        };
    

    //私聊
    
    dict[@"code"] = kCommandCode;
    [self sendCodeTextAll:dict];
    
}

- (IBAction)mirroredButtonPress:(id)sender {
    
    
    //    // 本地视频采集方向修正，wParam为方向参数，lParam为修正角度
    //    #define BRAC_USERINFO_CTRLCODE_LVORIENTFIX    10
    //
        // 视频方向修正标志定义
        // 图像需要镜像翻转
        #define BRAC_ROTATION_FLAGS_MIRRORED        0x1000
        // 顺时针旋转90度
        #define BRAC_ROTATION_FLAGS_ROTATION90        0x2000
        // 顺时针旋转180度
        #define BRAC_ROTATION_FLAGS_ROTATION180    0x4000
        // 顺时针旋转270度
        #define BRAC_ROTATION_FLAGS_ROTATION270    0x8000
    //
    //
    //
    //    //BRAC_UserInfoControl(-1, BRAC_USERINFO_CTRLCODE_LVORIENTFIX, BRAC_ROTATION_FLAGS_MIRRORED, 0, "");
    //    [AnyChatPlatform UserInfoControl:-1 :BRAC_USERINFO_CTRLCODE_LVORIENTFIX :BRAC_ROTATION_FLAGS_MIRRORED :0 :@""];
        
    #define BRAC_SO_LOCALVIDEO_CAMERAROTATION        101        ///< 本地摄像头旋转角度

    //DWORD dwFlags = STREAM_FLAGS_MIRRORED;
    //SetSDKOption(BRAC_SO_LOCALVIDEO_CAMERAROTATION, dwFlags);
        static int flag = 0;
        flag = !flag;
        int dwFlags = BRAC_ROTATION_FLAGS_MIRRORED;
        if (flag == 0) {
            dwFlags = 0;
        }
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_CAMERAROTATION :dwFlags];
        
        // 采用本地视频参数设置，使参数设置生效
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_APPLYPARAM :1];



}

- (void)showWarterMark
{
    int x = [self.imagexTextField.stringValue intValue];
    int y = [self.imageyTextField.stringValue intValue];
    int textx = [self.textxTextField.stringValue intValue];
    int texty = [self.textyTextField.stringValue intValue];

    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
    
    NSString *fontPath = [NSString stringWithFormat:@"%@/%@",documentPath,@"timestamp.ttf"];
    NSString *imagePath = [NSString stringWithFormat:@"%@/%@",documentPath,@"image.jpg"];
    
    NSLog(@"%@",fontPath);
    NSLog(@"%@",imagePath);
    int BRAC_SO_LOCALVIDEO_WATERMARK = 113;   ///< 视频迭加水印控制（图片、文字）
    NSMutableDictionary* strdic = @{}.mutableCopy;
    if (self.isShowWaterText) {
        strdic[@"textoverlay"] =@{
            @"alpha": @(50),
            @"fontcolor": @"0xffffff",
//                @"fontfile": @"/Users/temp/Downloads/AnyChatCoreSDK_Mac_r6709-my/src/AnyChatMeeting/AnyChatMeeting/DroidSansFallback.ttf",
            @"fontfile":fontPath,
            @"fontsize": @(60),
            @"posx": @(textx),
            @"posy": @(texty),
            @"text": @"[timestamp]实时水印",
            @"useservertime": @(1)
        };
    }
    if (self.isShowWaterImage) {
        strdic[@"watermark"] = @{
            @"alpha": @(50),
            @"imagepath": imagePath,
            @"overlayimgheight": @(140),
            @"overlayimgwidth": @(250),
            @"posx": @(x),
            @"posy": @(y)
        };
    }
    
//        @"textoverlay": ,
//        @"watermark":

    
    NSString *str = [self objToJsonString:strdic];
    NSLog(@"BRAC_SO_LOCALVIDEO_WATERMARK %@",str);
    [AnyChatPlatform SetUserStreamInfoString:-1 :0 :BRAC_SO_LOCALVIDEO_WATERMARK :str];
}

- (IBAction)waterImageButtonPress:(id)sender {
    self.isShowWaterImage = 1;
    
    [self showWarterMark];
}

- (IBAction)waterTextButtonPress:(id)sender {
    self.isShowWaterText = 1;
    
    [self showWarterMark];
}

- (IBAction)waterImageCloseButtonPress:(id)sender {
    self.isShowWaterImage = 0;
    
    [self showWarterMark];
}

- (IBAction)waterTextCloseButtonPress:(id)sender {
    self.isShowWaterText = 0;
    
    [self showWarterMark];
}

- (IBAction)startRecordAction:(id)sender {
    
    int selectRecordMode = (int)self.recodeMode.indexOfSelectedItem;        //录像方式
//    int selectRecordObject = (int)self.recordObject.indexOfSelectedItem;    //录像对象
    if (selectRecordMode == -1 ) {
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = @"录像提醒";
        alert.informativeText = @"请选择录像方式";
        [alert addButtonWithTitle:@"确定"];
        [alert beginSheetModalForWindow:[self.view window] completionHandler:nil];
    }else {
        
//        if (self.remoteUserId == 0 && selectRecordObject != 0) {
//            NSAlert *alert = [[NSAlert alloc] init];
//            alert.messageText = @"录像提醒";
//            alert.informativeText = @"视频聊天还没开始，暂时只能录制自己";
//            [alert addButtonWithTitle:@"确定"];
//            [alert beginSheetModalForWindow:[self.view window] completionHandler:nil];
//        }else {
            //开始录像
            [self startRecordWithRecordMode:selectRecordMode recordObject:0];
            self.startdRecordButton.enabled = NO;
            self.endRecordButton.enabled = YES;
            
//            self.recordLabel.hidden = NO;
            
//        }
        
        
    }
    
}

- (IBAction)endRecordAction:(id)sender {
    int userId;
    NSString *param;
    int selectRecordMode = (int)self.recodeMode.indexOfSelectedItem;        //录像方式
//    int selectRecordObject = (int)self.recordObject.indexOfSelectedItem;    //录像对象
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
//    switch (selectRecordObject) {
//        case 0://录自己
//            userId = -1;
//            break;
//        case 1://录对方
//            userId = self.remoteUserId;
//            break;
//        case 2://合成
//            userId = -1;
//            break;
//        default:
//            break;
//    }
    userId = -1;
    
    [AnyChatPlatform StreamRecordCtrlEx: userId
                                       : NO
                                       : self.recordFlags
                                       : 0
                                       : param];
    
    self.startdRecordButton.enabled = YES;
    self.endRecordButton.enabled = NO;
//    self.recordLabel.hidden = YES;
}
- (IBAction)snapButtonPress:(id)sender {
    
    int userId=-1;

//    int selectRecordObject = (int)self.recordObject.indexOfSelectedItem;    //录像对象
//
//    switch (selectRecordObject) {
//        case 0://录自己
//            userId = -1;
//            break;
//        case 1://录对方
//            userId = self.remoteUserId;
//            break;
//        case 2://合成
//            userId = -1;
//            break;
//        default:
//            break;
//    }
    if (self.tableView.selectedRow >= 0 && self.tableView.selectedRow < self.roomUserModelArr.count) {
        
        User *user = self.roomUserModelArr[self.tableView.selectedRow];
        userId = [user.userId intValue];
        

    }
    
    [AnyChatPlatform SnapShot:userId :0 :0];
}

// 开始录像
- (void)startRecordWithRecordMode:(int)selectMode recordObject:(int)selectObject {
    int userId;         // 用户id
    
    self.recordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_VIDEO + ANYCHAT_RECORD_FLAGS_LOCALCB;
    if (self.onlyAudioButton.state == 1) {
        self.recordFlags = ANYCHAT_RECORD_FLAGS_AUDIO + ANYCHAT_RECORD_FLAGS_LOCALCB;
    }
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
    
    
//    switch (selectObject) {
//        case 0://录自己
//            userId = -1;
//            self.recordStr = [self.recordStr stringByAppendingString:@"SelfRecord"];
//            break;
//        case 1://录对方
//            userId = self.remoteUserId;
//            self.recordStr = [self.recordStr stringByAppendingString:@"RemoteRecord"];
//            break;
//        case 2://合成
//            userId = -1;//self.remoteUserId;
//            self.recordStr = [self.recordStr stringByAppendingString:@"ComposeRecord"];
//            self.recordFlags += ANYCHAT_RECORD_FLAGS_MIXAUDIO + ANYCHAT_RECORD_FLAGS_MIXVIDEO + ANYCHAT_RECORD_FLAGS_ABREAST + ANYCHAT_RECORD_FLAGS_STEREO;
//            break;
//        default:
//            break;
//    }
    userId = -1;//self.remoteUserId;
    self.recordStr = [self.recordStr stringByAppendingString:@"ComposeRecord"];
    
    if (self.onlyAudioButton.state == 1) {
        self.recordFlags += ANYCHAT_RECORD_FLAGS_MIXAUDIO  + ANYCHAT_RECORD_FLAGS_STEREO;
    } else {
        self.recordFlags += ANYCHAT_RECORD_FLAGS_MIXAUDIO + ANYCHAT_RECORD_FLAGS_MIXVIDEO + ANYCHAT_RECORD_FLAGS_ABREAST + ANYCHAT_RECORD_FLAGS_STEREO;
    }
    
    [AnyChatPlatform StreamRecordCtrlEx: userId
                                       : YES
                                       : self.recordFlags
                                       : 0
                                       : self.recordStr];
}

- (IBAction)selfMainButtonPress:(id)sender {
    int userId = self.userId;
    [self CMD_Meeting_mainView:userId];
    self.mainUserId = userId;
    [self setMainVideoChatViewWithuserId:userId];
}

@end
