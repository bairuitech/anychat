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
#import "Business.h"
#import "BusinessListController.h"
#import "QueueViewController.h"
#import "VideoViewController.h"
#import "ServerQueueViewController.h"
#import "TextModelTool.h"
#import "TextModel.h"
#import "CustomButton.h"
//#import "SettingVC.h"
//#import "BRFACEX_SettingViewController.h"


#define kAnyChatIP @"demo.anychat.cn"
#define kAnyChatPort @"8906"
#define kAnyChatUserName @"AnyChatQueue"


@interface LoginViewController ()<UITextFieldDelegate,UIPickerViewDelegate,UIPickerViewDataSource,UIActionSheetDelegate, AnyChatNotifyMessageDelegate,AnyChatObjectEventDelegate>


@property (weak, nonatomic) IBOutlet UIButton *clientBtn;
@property (weak, nonatomic) IBOutlet UIButton *agentBtn;
@property (weak, nonatomic) IBOutlet UISwitch *autoRouteSwitch;
@property (weak, nonatomic) IBOutlet UITextField *server;           //服务器地址
@property (weak, nonatomic) IBOutlet UITextField *port;             //端口
@property (weak, nonatomic) IBOutlet UITextField *name;
@property (weak, nonatomic) IBOutlet UITextField *passWord;




@property (weak, nonatomic) IBOutlet UILabel *version;              //底部 SDK版本信息
@property (weak, nonatomic) IBOutlet UILabel *logLab;

@property(nonatomic, strong)NSMutableArray *businessHallDicArr;     //营业厅字典数组
@property(nonatomic, strong)NSArray *businessHallObjArr;            //营业厅模型数组
@property(nonatomic, weak)UIPickerView *pickerView;
@property(nonatomic, assign)int selfUserId;                         //自己的用户id
@property(nonatomic, assign)int waitingBusinessId;                  //队列id


@property (weak, nonatomic) IBOutlet UIView *settingAllView;

@property (weak, nonatomic) UIActionSheet *autoRouteActionSheet;

- (IBAction)loginAction:(UIButton *)sender;
- (IBAction)autoRouteAction:(id)sender;



@end
@implementation LoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setup];
    [self setupNav];
    [self setupAnyChat];
}

- (IBAction)setting:(id)sender {
    
}

- (void)setup {

    NSString *ip = [[NSUserDefaults standardUserDefaults]objectForKey:@"IP"];
    if (!(ip.length>0)) {
        
        ip = kAnyChatIP;
    }
    
    NSString *port = [[NSUserDefaults standardUserDefaults]objectForKey:@"PORT"];
    if (!(port.length>0)) {
        
        port = kAnyChatPort;
    }
    
    self.server.text = ip;
    self.port.text = port;
    self.name.text = kAnyChatUserName;
    
    
    //空白区取消键盘（添加手势响应）
    UITapGestureRecognizer *tapGr = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(viewTapped:)];
    tapGr.cancelsTouchesInView = NO;
    [self.view addGestureRecognizer:tapGr];
    
    // 自定义键盘
    [self customKeybord];
    
    [self selectRole:self.clientBtn];
}
- (void)setupNav {
    //set NavigationBar 背景颜色&title 颜色
    [self.navigationController.navigationBar setBarTintColor:[UIColor colorWithRed:3/255.0 green:139/255.0 blue:227/255.0 alpha:1.0]];
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
    //    self.anyChat.objectDelegate = self;
    
    //设置底部Label文本SDK的版本信息
    self.version.text = [AnyChatPlatform GetSDKVersion];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    self.navigationController.navigationBarHidden = YES;
    [self.navigationController.navigationBar setBackgroundImage:nil forBarMetrics:UIBarMetricsDefault];
    [self.navigationController.navigationBar setShadowImage:nil];
}
- (IBAction)selectRole:(UIButton *)sender {
    
    if (sender == self.clientBtn) {
        
        self.clientBtn.selected = YES;
        self.agentBtn.selected = NO;
        self.settingAllView.hidden = YES;
    }else{
        self.clientBtn.selected = NO;
        self.agentBtn.selected = YES;
        self.settingAllView.hidden = NO;
    }
    
}
- (IBAction)auto:(UISwitch *)sender {
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


// 空白区取消键盘的手势响应
-(void)viewTapped:(UITapGestureRecognizer*)tapGr
{
    [self.view endEditing:YES];
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
    

}

#pragma mark - 点击登录
- (IBAction)loginAction:(UIButton *)sender {
    
    if (self.server.text.length == 0 ) self.server.text = kAnyChatIP;
    if (self.port.text.length == 0 ) self.port.text = kAnyChatPort;
    if (self.name.text.length == 0) self.name.text = kAnyChatUserName;
    
    
    BOOL autoRoute = NO;
    BRAC_QueueRole role = BRAC_QUEUE_OPT_ROLE_CLIENT;
    //设置队列角色
    if (self.clientBtn.selected) {
        
        role = BRAC_QUEUE_OPT_ROLE_CLIENT;
        
    }else if(self.agentBtn.selected && self.autoRouteSwitch.on) {
        role = BRAC_QUEUE_OPT_ROLE_AGENT;
        autoRoute = YES;
        
    }else if(self.agentBtn.selected && !self.autoRouteSwitch.on) {
        role = BRAC_QUEUE_OPT_ROLE_AGENT;
        autoRoute = NO;
        
    }
    
    [AnyChatQueueDataManager getInstance].queueModel = [[AnyChat_QueueModel alloc] initWithRole:role priority:@"10" autoRoute:autoRoute];
    [AnyChatQueueDataManager getInstance].queueModel.delegate = self;
    

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
    [AnyChatPlatform Login:self.name.text :nil];

}

- (BOOL)isAgentRole
{
    return self.agentBtn.selected;
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
        self.selfUserId = dwUserId;

        [[AnyChatQueueDataManager getInstance].queueModel getAreas:dwUserId];
        //
        [[NSUserDefaults standardUserDefaults]setObject:self.server.text forKey:@"IP"];
        [[NSUserDefaults standardUserDefaults]setObject:self.port.text forKey:@"PORT"];

        [[NSUserDefaults standardUserDefaults]synchronize];

    }else {
        [MBProgressHUD hideHUD];
        [MBProgressHUD showError:@"登录失败"];
    }
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode {
    NSLog(@"用户进入房间");
    [MBProgressHUD hideHUD];
    if (dwErrorCode == 0) {
        VideoViewController *videoVC = [[VideoViewController alloc] init];
        if (![self isAgentRole]) {
            videoVC.remoteUserId = [AnyChatQueueDataManager getInstance].remoteUserId;
        }else {
            videoVC.remoteUserId = [AnyChatQueueDataManager getInstance].customerId;
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
    self.selfUserId = -1;
    
    [self.navigationController popToRootViewControllerAnimated:YES];
}

#pragma mark AnyChat_QueueModelDelegate
- (void)onAreasDataFinish:(NSArray *)businessHallDicArr
{
    [MBProgressHUD hideHUD];
    // 跳转到营业厅
    
    //将字典转成模型
    NSMutableArray *arr = [NSMutableArray array];
    for (NSDictionary *dic in businessHallDicArr) {
        
        BusinessHall *bhall = [BusinessHall businessHallWithDic:dic];
        
        [arr addObject:bhall];
    }
    
    BusinessHallViewController *businessHallVC = [[BusinessHallViewController alloc] init];
    businessHallVC.businessHallObjectArr = arr;
    [self.navigationController pushViewController:businessHallVC animated:YES];
}
- (void)onEnterAreaResult:(AnyChatResult *)result data:(NSDictionary *)data
{
    int dwErrorCode = result.errorCode;
    if(dwErrorCode == 0) {
        NSLog(@"进入服务区域成功");
        
        NSMutableArray *businessesObjArr = [NSMutableArray array];
        for (NSDictionary *dic in data[@"queues"]) {
            
            //获取队列名称
            Business *business = [Business businessWithDic:dic];
            [businessesObjArr addObject:business];
        }
        
        
        [MBProgressHUD hideHUD];
        // 界面跳转
        if (![self isAgentRole]) {
            BusinessListController *businessListVC = [[BusinessListController alloc] init];
            
            businessListVC.businesses = businessesObjArr;
            [self.navigationController pushViewController:businessListVC animated:YES];
        }else {
            ServerQueueViewController *serverQVC = [[ServerQueueViewController alloc] init];
            
            serverQVC.businesses = businessesObjArr;
            [self.navigationController pushViewController:serverQVC animated:YES];
        }
        
    }else {
        [MBProgressHUD hideHUD];
        [MBProgressHUD showError:@"进入服务区域失败"];
    }
}
- (void)onEnterQueueResult:(AnyChatResult *)result data:(NSDictionary *)data
{
    int dwErrorCode = result.errorCode;
    if(dwErrorCode == 0) {
        // 进入队列成功
        NSLog(@"用户进入队列成功");
        [MBProgressHUD hideHUD];
        QueueViewController *queueVC = [[QueueViewController alloc] init];
        queueVC.businessId = [data[@"queueId"] intValue];
        self.waitingBusinessId = [data[@"queueId"] intValue];
        [self.navigationController pushViewController:queueVC animated:YES];
    }else {
        [MBProgressHUD hideHUD];
        [MBProgressHUD showError:@"用户进入队列失败"];
    }
    
}
- (void)onProcessChanged:(NSDictionary *)data
{
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
        int queueId = [data[@"queueId"] intValue];
        if ([self.navigationController.viewControllers[3] isKindOfClass:[QueueViewController class]]) {
            if (self.waitingBusinessId == queueId) {
                [self updateQueueUserCountLabel:queueId];
            }
        }
    }
    
    UIViewController *topVC = self.navigationController.topViewController;
    if ([topVC isKindOfClass:[BusinessListController class]] || [topVC isKindOfClass:[ServerQueueViewController class]]) {
        
    }
}

// 更新排队人数Label
- (void)updateQueueUserCountLabel:(int)queueId {
    int navNum = (int)self.navigationController.viewControllers.count;
    if (navNum==4) {
        QueueViewController *queueVC = [self.navigationController.viewControllers objectAtIndex:3];
        int queueUserNum = [[AnyChatQueueDataManager getInstance].queueModel getQueuelengthWithid:[NSString stringWithFormat:@"%d",queueId]];
        queueVC.queueUserCountLabel.text = [NSString stringWithFormat:@"当前排队人数共:%d人",queueUserNum];
        
        int queuUserSite = [[AnyChatQueueDataManager getInstance].queueModel getQueueIndexWithid:[NSString stringWithFormat:@"%d",queueId]] + 1;
        
        //        if (beforeNum < 0) beforeNum = 0;
        queueVC.queuUserSiteLabel.text = [NSString stringWithFormat:@"你现在排在第%d位",queuUserSite];
        
    }
}

#pragma mark - NSNotification Method
//消息观察者方法
- (void)AnyChatNotifyHandler:(NSNotification*)notify
{
    NSDictionary* dict = notify.userInfo;
    [self.anyChat OnRecvAnyChatNotify:dict];
    

}




@end
