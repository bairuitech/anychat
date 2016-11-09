//
//  LoginViewController.m
//  AnyChatQueue
//
//  Created by tim.tan on 15/6/12.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//
#import "LoginViewController.h"
#import "BusinessHallViewController.h"
#import "MBProgressHUD+JT.h"
#import "BusinessHall.h"
#import "BusinessListController.h"
#import "QueueViewController.h"
#import "VideoViewController.h"
#import "ServerQueueViewController.h"
#import "TextModelTool.h"
#import "TextModel.h"
#import "CustomButton.h"

#define kUserID 1001
#define kAnyChatIP @"demo.anychat.cn"
#define kAnyChatPort @"8906"
#define kAnyChatUserName @"AnyChatQueue"


@interface LoginViewController ()<UITextFieldDelegate,AnyChatNotifyMessageDelegate,AnyChatObjectEventDelegate,UIPickerViewDelegate,UIPickerViewDataSource,UIActionSheetDelegate>
@property (weak, nonatomic) IBOutlet UITextField *role;             //角色
@property (weak, nonatomic) IBOutlet UITextField *server;           //服务器地址
@property (weak, nonatomic) IBOutlet UITextField *port;             //端口
@property (weak, nonatomic) IBOutlet UITextField *username;         //用户名
@property (weak, nonatomic) IBOutlet UILabel *version;              //底部 SDK版本信息

@property(nonatomic, strong)NSMutableArray *businessHallDicArr;     //营业厅字典数组
@property(nonatomic, strong)NSArray *businessHallObjArr;            //营业厅模型数组
@property(nonatomic, weak)UIPickerView *pickerView;
@property(nonatomic, assign)int selfUserId;                         //自己的用户id
@property(nonatomic, assign)int waitingBusinessId;                  //队列id
@property (weak, nonatomic) IBOutlet UIButton *autoRoute;
@property (weak, nonatomic) IBOutlet CustomButton *cash;
@property (weak, nonatomic) IBOutlet CustomButton *manage;
@property (weak, nonatomic) IBOutlet CustomButton *loan;
@property (weak, nonatomic) IBOutlet UIView *settingAllView;

@property (weak, nonatomic) UIActionSheet *autoRouteActionSheet;

- (IBAction)loginAction:(UIButton *)sender;
- (IBAction)autoRouteAction:(id)sender;
- (IBAction)cashAction:(id)sender;
- (IBAction)manageAction:(id)sender;
- (IBAction)loanAction:(id)sender;


@end

@implementation LoginViewController

- (NSMutableArray *)businessHallDicArr {
    
    if (_businessHallDicArr == nil) {
        NSMutableArray *businessHallDicArray = [NSMutableArray array];
        _businessHallDicArr = businessHallDicArray;
    }
    return _businessHallDicArr;
}

- (NSArray *)businessHallObjArr {
    if (_businessHallObjArr == nil) {
        _businessHallObjArr = [NSMutableArray array];
    }
    //将字典转成模型
    NSMutableArray *arr = [NSMutableArray array];
    for (NSDictionary *dic in self.businessHallDicArr) {
        
        BusinessHall *bhall = [BusinessHall businessHallWithDic:dic];

        [arr addObject:bhall];
    }
    _businessHallObjArr = arr;
    return _businessHallObjArr;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setup];
    [self setupNav];
    [self setupAnyChat];
    
    
    TextModel *textModel = [TextModelTool textModel];
    if (textModel.chatIp) {
        self.role.text = textModel.roomId;
        self.username.text = textModel.userName;
        self.server.text = textModel.chatIp;
        self.port.text = textModel.chatPort;
    }else{
        textModel.roomId = self.role.text;
        textModel.userName = self.username.text;
        textModel.chatIp = self.server.text;
        textModel.chatPort = self.port.text;
    }
    
    
    [TextModelTool saveText:textModel];
    
    [self initAddSubViewWithQueues];
    
    [self setupSkills];
    
    if([self.role.text isEqualToString:@"普通用户"]){
        
        self.settingAllView.hidden = YES;
    }
    
}

-(void)initAddSubViewWithQueues{
    
    [self.cash initTheSubView];
    [self.manage initTheSubView];
    [self.loan initTheSubView];
}

-(void)setupSkills{
    
    [self.cash setCustomUI:@"现金" withisChecked:YES];
    [self.manage setCustomUI:@"理财" withisChecked:YES];
    [self.loan setCustomUI:@"贷款" withisChecked:YES];
}

- (void)setup {
    self.server.delegate = self;
    self.port.delegate = self;
    self.username.delegate = self;
    
    self.server.text = kAnyChatIP;
    self.port.text = kAnyChatPort;
    self.username.text = kAnyChatUserName;
    
    //设置底部Label文本SDK的版本信息
    self.version.text = [AnyChatPlatform GetSDKVersion];
    
    //空白区取消键盘（添加手势响应）
    UITapGestureRecognizer *tapGr = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(viewTapped:)];
    tapGr.cancelsTouchesInView = NO;
    [self.view addGestureRecognizer:tapGr];
    
    // 自定义键盘
    [self customKeybord];
}
- (void)setupNav {
    //set NavigationBar 背景颜色&title 颜色
    [self.navigationController.navigationBar setBarTintColor:[UIColor colorWithRed:16/255.0 green:45/255.0 blue:59/255.0 alpha:1.0]];
    [self.navigationController.navigationBar setTitleTextAttributes:@{NSForegroundColorAttributeName:[UIColor whiteColor]}];
}
- (void)setupAnyChat {
    // 1.初始化系统 功能：加载资源,应用程序中只需要执行一次,其他的功能接口都必须在初始化之 后才能正常使用
    [AnyChatPlatform InitSDK:0];
    
    // 2.设置AnyChat的通知监听
    // 功能:运用通知中心机制,实现监听“连接服务器、用户登录、进入房间、与服务器网络连接”等事件
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    //3.初始化sdk的核心类对象 AnyChatPlatform
    self.anyChat = [AnyChatPlatform getInstance];
    
    //4.设置通知代理
    self.anyChat.notifyMsgDelegate = self;
    self.anyChat.objectDelegate = self;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    self.navigationController.navigationBarHidden = YES;
}

#pragma mark - AnyChat Delegate
// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess {
    if (bSuccess) {
        
    }else {
        [MBProgressHUD hideHUD];
        [MBProgressHUD showError:@"连接服务器失败"];
    }
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode {
    if (dwErrorCode == 0) {
        self.businessHallDicArr = nil;
        self.selfUserId = dwUserId;
        // 初始化本地对象信息
        if ([self.role.text isEqualToString:@"普通用户"]) {
            [self InitClientObjectInfo:dwUserId :0];
        }else if([self.role.text isEqualToString:@"坐席"] && [self.autoRoute.titleLabel.text isEqualToString:@"开启"]) {
            [self InitClientObjectInfo:dwUserId :ANYCHAT_OBJECT_FLAGS_AGENT+ANYCHAT_OBJECT_FLAGS_AUTOMODE];
        }else if([self.role.text isEqualToString:@"坐席"] && [self.autoRoute.titleLabel.text isEqualToString:@"关闭"]) {
            [self InitClientObjectInfo:dwUserId :ANYCHAT_OBJECT_FLAGS_AGENT];
        }
    }else {
        [MBProgressHUD hideHUD];
        [MBProgressHUD showError:@"登录失败"];
    }
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode {
    NSLog(@"用户进入房间");
    if (dwErrorCode == 0) {
        VideoViewController *videoVC = [[VideoViewController alloc] init];
        if ([self.role.text isEqualToString:@"普通用户"]) {
            videoVC.remoteUserId = self.remoteUserId;
        }else if([self.role.text isEqualToString:@"坐席"]) {
            videoVC.remoteUserId = self.customerId;
        }
        [self.navigationController pushViewController:videoVC animated:YES];
        _videoViewController=videoVC;
    }
}

// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId {
    [self.videoViewController openRemoteView];
}
// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId {
    if (dwUserId == self.videoViewController.remoteUserId) {
        [self.videoViewController openRemoteView];
    }
}
// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId {}
// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode {
    NSLog(@"网络断开");
    // 注销系统
    [AnyChatPlatform Logout];
    [MBProgressHUD hideHUD];
    [MBProgressHUD showError:@"网络断线，请稍后再试"];
    self.businessHallDicArr = nil;
    self.selfUserId = -1;
    self.customerId = 0;
    self.remoteUserId = 0;
    [self.navigationController popToRootViewControllerAnimated:YES];
}

#pragma mark - AnyChatObjectEventDelegate
- (void) OnAnyChatObjectEventCallBack: (int) dwObjectType : (int) dwObjectId : (int) dwEventType : (int) dwParam1 : (int) dwParam2 : (int) dwParam3 : (int) dwParam4 : (NSString*) lpStrParam {
    switch (dwEventType) {
        case ANYCHAT_OBJECT_EVENT_UPDATE:// 1.对象数据更新
            [self AnyChatObjectUpdate:dwObjectType :dwObjectId];
            break;
        case ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH:// 2.对象数据同步结束
            [self AnyChatObjectSynDataFinish:dwObjectType];
            break;
            
        case ANYCHAT_AREA_EVENT_USERENTER:// 3.用户进入服务区域
            [self AnyChatUserEnterArea:dwObjectType :dwObjectId :dwParam1 :dwParam2 :dwParam3 :dwParam4];
            break;
        case ANYCHAT_AREA_EVENT_ENTERRESULT:// 4.进入服务区域结果
            [self AnyChatEnterAreaResult:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_AREA_EVENT_USERLEAVE:// 5.用户离开服务区域
            [self AnyChatUserLeaveArea:dwObjectType :dwObjectId :dwParam1 :dwParam2];
            break;
        case ANYCHAT_AREA_EVENT_LEAVERESULT:// 6.离开服务区域结果
            [self AnyChatLeaveAreaResult:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_AREA_EVENT_STATUSCHANGE:// 7.服务区域状态变化
            [self AnyChatAreaStatusChanged:dwObjectType :dwObjectId];
            break;
            
        case ANYCHAT_QUEUE_EVENT_USERENTER:// 8.进入队列
            [self AnyChatUserEnterQueue:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_QUEUE_EVENT_ENTERRESULT:// 9.用户进入队列结果
            [self AnyChatEnterQueueResult:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_QUEUE_EVENT_USERLEAVE:// 10.用户离开队列
            [self AnyChatUserLeaveQueue:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_QUEUE_EVENT_LEAVERESULT:// 11.用户离开队列结果
            [self AnyChatLeaveQueueResult:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_QUEUE_EVENT_STATUSCHANGE:// 12.队列状态变化
            [self AnyChatQueueStatusChanged:dwObjectType :dwObjectId];
            break;
            
        case ANYCHAT_AGENT_EVENT_STATUSCHANGE:// 13.坐席状态变化
            [self AnyChatAgentStatusChanged:dwObjectType :dwObjectId];
            break;
        case ANYCHAT_AGENT_EVENT_SERVICENOTIFY:// 14.坐席服务通知（哪个用户到哪个客服办理业务）
            [self AnyChatAgentServiceNotify:dwParam1 :dwParam2];
            break;
        case ANYCHAT_AGENT_EVENT_WAITINGUSER:// 15.暂时没有客户，请等待
            [self AnyChatAgentWaitingUser:dwObjectType];
            break;
        
        default:
            break;
    }
}

// 1.对象数据更新(进和出都会触发)
-(void) AnyChatObjectUpdate:(int)dwObjectType :(int)dwObjectId {
    NSLog(@"对象数据更新事件");
    if(dwObjectType == ANYCHAT_OBJECT_TYPE_AREA) {
        // 获取营业厅名称
        NSString *areaName = [AnyChatPlatform ObjectGetStringValue:dwObjectType :dwObjectId :ANYCHAT_OBJECT_INFO_NAME];

        NSDictionary *dic = [[NSDictionary alloc] initWithObjectsAndKeys:areaName,@"areaName",[NSString stringWithFormat:@"%d",dwObjectId],@"areaId", nil];
        
        [self.businessHallDicArr addObject:dic];

        NSLog(@"服务区域");
    }else if(dwObjectType == ANYCHAT_OBJECT_TYPE_QUEUE) {
        NSLog(@"队列");
    }
    
}

// 2.对象数据同步结束
-(void)AnyChatObjectSynDataFinish:(int)dwObjectType {
    NSLog(@"对象数据同步结束");
    if(dwObjectType == ANYCHAT_OBJECT_TYPE_AREA) { //营业厅
        [MBProgressHUD hideHUD];
        // 跳转到营业厅
        BusinessHallViewController *businessHallVC = [[BusinessHallViewController alloc] init];
        businessHallVC.businessHallObjectArr = self.businessHallObjArr;
        self.businessHallDicArr = nil;
        [self.navigationController pushViewController:businessHallVC animated:YES];
        
        NSLog(@"服务区域");
    }
}

// 3.用户进入服务区域
-(void) AnyChatUserEnterArea:(int)dwObjectType :(int)dwObjectId :(int)dwUserId :(int)dwFlags :(int)dwAttribute :(int)dwPriority {
    NSLog(@"用户进入服务区域");
}

// 4.进入服务区域结果
-(void) AnyChatEnterAreaResult:(int)dwObjectType :(int)dwObjectId :(int)dwErrorCode {
    if(dwErrorCode == 0) {
        NSLog(@"进入服务区域成功");
        [MBProgressHUD hideHUD];
        
        NSMutableArray *queuesArray= [AnyChatPlatform ObjectGetIdList:ANYCHAT_OBJECT_TYPE_QUEUE];

        // 界面跳转
        if ([self.role.text isEqualToString:@"普通用户"]) {
            BusinessListController *businessListVC = [[BusinessListController alloc] init];
            businessListVC.businessListIdArray = queuesArray;
            businessListVC.businessHallId = dwObjectId;
            [self.navigationController pushViewController:businessListVC animated:YES];
        }else if([self.role.text isEqualToString:@"坐席"]) {
            ServerQueueViewController *serverQVC = [[ServerQueueViewController alloc] init];
            serverQVC.businessListIdArray = queuesArray;
            serverQVC.businessHallId = dwObjectId;
            serverQVC.selfUserId = self.selfUserId;
            [self.navigationController pushViewController:serverQVC animated:YES];
        }
        
    }else {
        [MBProgressHUD hideHUD];
        [MBProgressHUD showError:@"进入服务区域失败"];
    }
}

// 5.用户离开服务区域
-(void) AnyChatUserLeaveArea:(int)dwObjectType :(int)dwObjectId :(int)dwUserId :(int)dwErrorCode {
    NSLog(@"用户离开服务区域");
}

// 6.离开服务区域结果
-(void) AnyChatLeaveAreaResult:(int)dwObjectType :(int)dwObjectId :(int)dwErrorCode {
    
    //移除营业厅中的字典
    if (dwErrorCode == 0) {
        NSLog(@"离开服务区域成功");
        for (NSDictionary *dic in self.businessHallDicArr) {
            NSString *areaId = [dic objectForKey:@"areaId"];
            if ([areaId intValue] == dwObjectId) {
                [self.businessHallDicArr removeObject:dic];
            }
        }
    }
}

// 7.服务区域状态变化
- (void) AnyChatAreaStatusChanged:(int)dwObjectType :(int)dwObjectId {
    NSLog(@"服务区域状态变化");
}

// 8.用户进入队列
-(void) AnyChatUserEnterQueue:(int)dwObjectType :(int)dwObjectId :(int)dwUserId {
    NSLog(@"用户进入队列");
    int controllersCount = (int)self.navigationController.viewControllers.count;
    if(controllersCount == 4){
        [self updateQueueUserCountLabel:dwObjectId];
    }
}

// 9.用户进入队列结果
-(void) AnyChatEnterQueueResult:(int)dwObjectType :(int)dwObjectId :(int)dwErrorCode {
    if(dwErrorCode == 0) {
        // 进入队列成功
        NSLog(@"用户进入队列成功");
        [MBProgressHUD hideHUD];
        QueueViewController *queueVC = [[QueueViewController alloc] init];
        queueVC.businessId = dwObjectId;
        self.waitingBusinessId = dwObjectId;
        [self.navigationController pushViewController:queueVC animated:YES];
    }else {
        [MBProgressHUD hideHUD];
        [MBProgressHUD showError:@"用户进入队列失败"];
    }
}

// 10.用户离开队列
-(void) AnyChatUserLeaveQueue:(int)dwObjectType :(int)dwObjectId :(int)dwUserId {
    NSLog(@"用户离开队列");
    int controllersCount = (int)self.navigationController.viewControllers.count;
    if(controllersCount == 4){
        [self updateQueueUserCountLabel:dwObjectId];
    }
}

// 11.用户离开队列结果
-(void) AnyChatLeaveQueueResult :(int)dwObjectType :(int)dwObjectId :(int)dwErrorCode {
    if (dwErrorCode == 0) {
        NSLog(@"用户离开队列成功");
    }
}

// 12.队列状态变化
-(void) AnyChatQueueStatusChanged:(int)dwObjectType :(int)dwObjectId {
    NSLog(@"队列状态变化");
    
    int controllersCount = (int)self.navigationController.viewControllers.count;
    if(controllersCount == 3 || controllersCount == 4){
        if ([self.navigationController.viewControllers[2] isKindOfClass:[BusinessListController class]]) {
            BusinessListController *businessListVC = self.navigationController.viewControllers[2];
            [businessListVC.tableView reloadData];
        }
        if ([self.navigationController.viewControllers[2] isKindOfClass:[ServerQueueViewController class]]) {
            ServerQueueViewController *serverQVC = self.navigationController.viewControllers[2];
            [serverQVC.tableView reloadData];
        }
        
    }
    if (controllersCount == 4) {
        if ([self.navigationController.viewControllers[3] isKindOfClass:[QueueViewController class]]) {
            if (self.waitingBusinessId == dwObjectId) {
                [self updateQueueUserCountLabel:dwObjectId];
            }
        }
    }
}

// 13.坐席状态变化
-(void) AnyChatAgentStatusChanged:(int)dwObjectType :(int)dwObjectId {
    NSLog(@"坐席状态变化");
}

// 14.坐席服务通知(有人排队)
-(void) AnyChatAgentServiceNotify:(int)dwAgentId :(int)clientId {
    NSLog(@"坐席服务通知");
    if ([self.role.text isEqualToString:@"坐席"] && self.selfUserId == dwAgentId) {
        self.customerId = clientId;
        // 呼叫用户
        [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REQUEST :clientId :0 :0 :0 :nil];
        ServerQueueViewController *serverQVC = [self.navigationController.viewControllers lastObject];
        serverQVC.waitingAlertView = [[UIAlertView alloc] initWithTitle:@"呼叫请求中，等待客户响应..." message:nil delegate:serverQVC cancelButtonTitle:@"取消" otherButtonTitles:nil, nil];
        [serverQVC.waitingAlertView show];
    }
}

// 15.坐席等待用户(没人排队)
-(void) AnyChatAgentWaitingUser:(int)dwObjectType {
    NSLog(@"坐席等待用户");
    if([self.autoRoute.titleLabel.text isEqualToString:@"开启"]){
        
        [MBProgressHUD showSuccess:@"正在服务"];
        
    }
    else if([self.autoRoute.titleLabel.text isEqualToString:@"关闭"]){
        
        [MBProgressHUD showError:@"暂时还没有顾客排队，请稍后再试"];
    }
    
}

#pragma mark - UITextFieldDelegate
//当用户按下return键或者按回车键，keyboard消失
- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

//开始编辑输入框的时候，软键盘出现，执行此事件
-(void)textFieldDidBeginEditing:(UITextField *)textField
{

    CGRect frame = textField.frame;
    NSLog(@"==%@",NSStringFromCGRect(frame));
    int offset = frame.origin.y + 32 - (self.view.frame.size.height - 216.0);//键盘高度216
    NSTimeInterval animationDuration = 0.30f;
    [UIView beginAnimations:@"ResizeForKeyBoard" context:nil];
    [UIView setAnimationDuration:animationDuration];
    float width = self.view.frame.size.width;
    float height = self.view.frame.size.height;
    if(offset > 0)
    {
        CGRect rect = CGRectMake(0.0f, -offset,width,height);
        self.view.frame = rect;
    }
    [UIView commitAnimations];
}


//输入框编辑完成以后，将视图恢复到原始状态
-(void)textFieldDidEndEditing:(UITextField *)textField
{
    self.view.frame =CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);
}

#pragma mark - UIPickerView Delegate
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView {
    return 1;
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component {
    return 2;
}

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component {
    if (component ==0) {
        if (row ==0) {
            
            self.settingAllView.hidden = YES;
            
            return @"普通用户";
        }else if (row == 1) {
            
            self.settingAllView.hidden = NO;
            
            return @"坐席";
        }
    }
    return 0;
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
    if (component ==0) {
        if (row ==0) {
            self.role.text = @"普通用户";
        }else if (row == 1) {
            self.role.text = @"坐席";
        }
    }
}

#pragma mark - NSNotification Method
//消息观察者方法
- (void)AnyChatNotifyHandler:(NSNotification*)notify
{
    NSDictionary* dict = notify.userInfo;
    [self.anyChat OnRecvAnyChatNotify:dict];
}


#pragma mark - Custom Method
// 初始化本地对象信息
- (void)InitClientObjectInfo:(int)mSelfUserId :(int)dwAgentFlags {
    // 业务对象身份初始化
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_OBJECT_INITFLAGS : dwAgentFlags]; // 0 普通用户 2 坐席
    // 客户端用户对象优先级
    [AnyChatPlatform ObjectSetIntValue:ANYCHAT_OBJECT_TYPE_CLIENTUSER :mSelfUserId :ANYCHAT_OBJECT_INFO_PRIORITY :10];
    
    //坐席  开启自动路由
    if(dwAgentFlags == ANYCHAT_OBJECT_FLAGS_AGENT+ANYCHAT_OBJECT_FLAGS_AUTOMODE){
    
        int attribute = 0;
        if(self.cash.isChecked){
        
            attribute = attribute + 1;
        }
        if(self.manage.isChecked){
            
            attribute = attribute + 2;
        }
        if(self.loan.isChecked){
        
            attribute = attribute + 4;
        }
        
        [AnyChatPlatform ObjectSetIntValue:ANYCHAT_OBJECT_TYPE_CLIENTUSER :mSelfUserId :ANYCHAT_OBJECT_INFO_ATTRIBUTE :attribute];
    }
    else{
    
        [AnyChatPlatform ObjectSetIntValue:ANYCHAT_OBJECT_TYPE_CLIENTUSER :mSelfUserId :ANYCHAT_OBJECT_INFO_ATTRIBUTE :-1];
    }
    
    // 向服务器发送数据同步请求指令
    [AnyChatPlatform ObjectControl: ANYCHAT_OBJECT_TYPE_AREA :ANYCHAT_INVALID_OBJECT_ID :ANYCHAT_OBJECT_CTRL_SYNCDATA :mSelfUserId :0 :0 :0 :nil];
}

// 空白区取消键盘的手势响应
-(void)viewTapped:(UITapGestureRecognizer*)tapGr
{
    [self.view endEditing:YES];
}

// 更新排队人数Label
- (void)updateQueueUserCountLabel:(int)queueId {
    int navNum = (int)self.navigationController.viewControllers.count;
    if (navNum==4) {
        QueueViewController *queueVC = [self.navigationController.viewControllers objectAtIndex:3];
        int queueUserNum = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :queueId :ANYCHAT_QUEUE_INFO_LENGTH];
        queueVC.queueUserCountLabel.text = [NSString stringWithFormat:@"当前排队人数共:%d人",queueUserNum];
        
        int queuUserSite = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :queueId :ANYCHAT_QUEUE_INFO_BEFOREUSERNUM] + 1;
        //        if (beforeNum < 0) beforeNum = 0;
        queueVC.queuUserSiteLabel.text = [NSString stringWithFormat:@"你现在排在第%d位",queuUserSite];
        
    }
}

// 自定义键盘
- (void)customKeybord {
    
    // 工具条
    UIToolbar *toolBar = [[UIToolbar alloc] initWithFrame:CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, 44)];
    toolBar.barTintColor = [UIColor colorWithRed:86/255.0 green:115/255.0 blue:146/255.0 alpha:1.0];
    UIBarButtonItem *item1 = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
    UIBarButtonItem *item2 = [[UIBarButtonItem alloc] initWithTitle:@"完成" style:UIBarButtonItemStylePlain target:self action:@selector(viewTapped:)];
    [item2 setTintColor:[UIColor whiteColor]];
    toolBar.items = @[item1,item2];
    
    // pickView
    UIPickerView *pickerView = [[UIPickerView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
    pickerView.delegate = self;
    pickerView.dataSource = self;
    self.role.inputView = pickerView;
    self.role.inputAccessoryView = toolBar;
}

#pragma mark - Action
- (IBAction)loginAction:(UIButton *)sender {
    
    if (self.server.text.length == 0 ) self.server.text = kAnyChatIP;
    if (self.port.text.length == 0 ) self.port.text = kAnyChatPort;
    if (self.username.text.length == 0) self.username.text = kAnyChatUserName;

    //连接服务器，准备回调连接服务器方法 OnAnyChatConnect
    [MBProgressHUD showMessage:@"正在连接中，请稍等..."];
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    
    [AnyChatPlatform Connect:self.server.text : [self.port.text intValue]];
    
    /*
     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
     */
    [AnyChatPlatform Login:self.username.text :nil];

}

- (IBAction)autoRouteAction:(id)sender {
    
    UIActionSheet *actionSheet = [[UIActionSheet alloc]initWithTitle:nil delegate:self cancelButtonTitle:nil destructiveButtonTitle:nil otherButtonTitles:@"开启",@"关闭", nil];
    
    [actionSheet showInView:self.view];
    self.autoRouteActionSheet = actionSheet;
}

- (IBAction)cashAction:(id)sender {
    
    CustomButton *btn = (CustomButton *)sender;

    [btn setCustomUI:@"现金" withisChecked:!btn.isChecked];

}

- (IBAction)manageAction:(id)sender {
    
    CustomButton *btn = (CustomButton *)sender;
    
    [btn setCustomUI:@"理财" withisChecked:!btn.isChecked];
}

- (IBAction)loanAction:(id)sender {
    
    CustomButton *btn = (CustomButton *)sender;
    
    [btn setCustomUI:@"贷款" withisChecked:!btn.isChecked];
}

#pragma mark -UIActionSheetDelegate
-(void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex{

    if(actionSheet == self.autoRouteActionSheet){
    
        if(buttonIndex == 0){
            
            [self.autoRoute setTitle:@"开启" forState:UIControlStateNormal];
            
        }else if (buttonIndex == 1){
            
            [self.autoRoute setTitle:@"关闭" forState:UIControlStateNormal];
        }
    }
}


@end
