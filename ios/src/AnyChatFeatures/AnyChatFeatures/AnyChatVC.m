//
//  VideoVC.m
//  AnyChatFeatures
//
//  Created by alexChen .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "AnyChatVC.h"

#define kAnyChatUserName @"AnyChat"
#define kUserID 1001

@interface AnyChatVC ()

//@property (strong)NSString *textField0;


@end

@implementation AnyChatVC

@synthesize anyChat;
@synthesize videoVC;
@synthesize theOnLineLoginState;
@synthesize theVersionLab;
@synthesize theStateInfo;
@synthesize theUserName;
@synthesize theServerIP;
@synthesize theServerPort;
@synthesize theLoginBtn;
@synthesize theHideKeyboardBtn;
@synthesize theFeaturesName;
@synthesize theFeaturesNO;
@synthesize theMyUserName;
@synthesize theMyUserID;
@synthesize onlineUserMArray;
@synthesize theTargetUserID;
@synthesize theTargetUserName;
@synthesize theSnapShotAlertView;
@synthesize theVideoRecordAlertView;
@synthesize theVideoRecordMArray;
@synthesize theVideoRecordSelfMArray;
@synthesize theShowVCType;
@synthesize theUDPTraceType;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self)
    {
        
    }
    return self;
}

#pragma mark - Life cycle
- (void)viewDidLoad {
    [super viewDidLoad];

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    [AnyChatPlatform InitSDK:0];
    
    anyChat = [AnyChatPlatform getInstance];
    anyChat.notifyMsgDelegate = self;
    anyChat.textMsgDelegate = self;
    anyChat.transDataDelegate = self;
    anyChat.recordSnapShotDelegate = self;
    anyChat.videoCallDelegate = self;
    
    //视频数据回调设置
//    anyChat.mediaDataDelegate = self;
//    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_VIDEOSHOW_CBPIXFMT :BRAC_PIX_FMT_RGB32];
//    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :0];
    
    self.theVideoRecordMArray = [[NSMutableArray alloc] initWithCapacity:5];
    self.theVideoRecordSelfMArray = [[NSMutableArray alloc] initWithCapacity:5];
    
    //创建默认视频参数
    [[SettingVC sharedSettingVC] createObjPlistFileToDocumentsPath];
    
    //传输文件的开发调试模式
    //[AnyChatPlatform UserInfoControl:-1 :BRAC_USERINFO_CTRLCODE_DEBUGLOG :4 :1 :@""];
    
    //获取APP沙盒路径
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    //设置自定义录像储存路径
    NSString  *myRecordDirectory = [documentsDirectory stringByAppendingPathComponent:@"Record_mp4"];
    [AnyChatPlatform SetSDKOptionString:BRAC_SO_RECORD_TMPDIR :myRecordDirectory];
    //设置自定义抓图储存路径
    NSString  *myPhotoDirectory = [documentsDirectory stringByAppendingPathComponent:@"ShotPhoto_jpg"];
    [AnyChatPlatform SetSDKOptionString:BRAC_SO_SNAPSHOT_TMPDIR :myPhotoDirectory];
    //设置自定义接收文件储存路径
    NSString  *myTransFileDirectory = [documentsDirectory stringByAppendingPathComponent:@"TransFile"];
    [AnyChatPlatform SetSDKOptionString:BRAC_SO_CORESDK_TMPDIR :myTransFileDirectory];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUI];
}

#pragma mark - Memory Warning Method

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - Shared Instance

kGCD_SINGLETON_FOR_CLASS(AnyChatVC);


#pragma mark -
#pragma mark - TextField Delegate

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    return YES;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    return YES;
}


#pragma mark - AnyChatMediaDataDelegate

// 视频数据回调
- (void) OnAnyChatVideoDataExCallBack:(int) dwUserid : (NSData*) lpBuf : (BITMAPINFOHEADER) bmiHeader : (int) dwTimeStamp
{
    
    /* Log var*/
//    NSLog(@"\n\n 视频数据回调 \n  dwUserid:%d  \n  wxh=%d x %d \n  size:%d \n dwTimeStamp:%i \n",dwUserid,bmiHeader.biWidth,bmiHeader.biHeight,(int)sizeof(bmiHeader),dwTimeStamp);
    
    
    // 通过(NSData*) lpBuf 返回的数据 绘制成 图片
    /*Get information about the image*/
    uint8_t *baseAddress = (uint8_t *)[lpBuf bytes];    // (NSData*) lpBuf 参数通过 [NSData bytes] 方法取地址
    size_t bytesPerRow = bmiHeader.biWidth*4;   // RGB32 = pixel size = 4 CVPixelBufferGetBytesPerRow(imageBuffer);
    
    /*Create a CGImageRef from the CVImageBufferRef*/
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef newContext = CGBitmapContextCreate(baseAddress, bmiHeader.biWidth, bmiHeader.biHeight, 8, bytesPerRow, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
    CGImageRef newImage = CGBitmapContextCreateImage(newContext);
    
    /*We release some components*/
    CGContextRelease(newContext);
    CGColorSpaceRelease(colorSpace);
    
    /*We display the result on the image view (We need to change the orientation of the image so that the video is displayed correctly).
     Same thing as for the CALayer we are not in the main thread so ...UIImageOrientationRight */
    UIImageOrientation imageOrientation = UIImageOrientationUp;
    UIImage *image= [UIImage imageWithCGImage:newImage scale:1.0 orientation:imageOrientation];
    
    /*We relase the CGImageRef*/
    CGImageRelease(newImage);

}

// 音频数据回调
- (void) OnAnyChatAudioDataExCallBack:(int) dwUserid : (NSData*) lpBuf : (WAVEFORMATEX) waveFormatEx : (int) dwTimeStamp{
}


#pragma mark - AnyChatNotifyMessageDelegate

// 连接服务器消息
- (void) OnAnyChatConnect:(BOOL) bSuccess
{
    if (bSuccess)
    {
        theStateInfo.text = @"• Success connected to server";
    }else {
        theStateInfo.text = @"• Fail connected to server";
        [HUD hide:YES];
    }
}

// 用户登陆消息
- (void) OnAnyChatLogin:(int) dwUserId : (int) dwErrorCode
{
    self.onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        //更新系统默认视频参数设置
        //[self updateLocalSettings];
        
        theOnLineLoginState = YES;
        self.theMyUserID = dwUserId;
        self.theMyUserName = self.theUserName.text;
        [self saveSettings];  //登陆信息归档
        theStateInfo.text = [NSString stringWithFormat:@" Login successed. Self UserId: %d", dwUserId];
        [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_logout_01"] forState:UIControlStateNormal];
        
        FeaturesListVC *featuresListVC = [[FeaturesListVC alloc] init];
        [self.navigationController pushViewController:featuresListVC animated:YES];
        [HUD hide:YES];
    }
    else
    {
        theOnLineLoginState = NO;
        theStateInfo.text = [NSString stringWithFormat:@"• Login failed(ErrorCode:%i)",dwErrorCode];
    }
    
}

// 用户进入房间消息
- (void) OnAnyChatEnterRoom:(int) dwRoomId : (int) dwErrorCode
{
    //更新用户自定义视频参数设置
    [[SettingVC sharedSettingVC] updateUserVideoSettings];
    
    if (dwErrorCode != 0)
    {
        theStateInfo.text = [NSString stringWithFormat:@"• Enter room failed(ErrorCode:%i)",dwErrorCode];
    }
    
    [[UserListVC sharedUserListVC].onLineUserTableView reloadData];
}

// 房间在线用户消息
- (void) OnAnyChatOnlineUser:(int) dwUserNum : (int) dwRoomId
{
    self.onlineUserMArray = [self getOnlineUserArray];
    [[UserListVC sharedUserListVC].onLineUserTableView reloadData];
}

// 用户进入房间消息
- (void) OnAnyChatUserEnterRoom:(int) dwUserId
{
    self.onlineUserMArray = [self getOnlineUserArray];
    [[UserListVC sharedUserListVC].onLineUserTableView reloadData];
}

// 用户退出房间消息
- (void) OnAnyChatUserLeaveRoom:(int) dwUserId
{
    if (self.theTargetUserID == dwUserId)
    {
        VideoVC *theVideoVC = [[VideoVC alloc] init];
        [theVideoVC FinishVideoChat];
        
        [self.navigationController popViewControllerAnimated:YES];
        
        NSString *theLeaveRoomName = [[NSString alloc] initWithFormat:@"\"%@\"已离开房间!",self.theTargetUserName];
        NSString *theLeaveRoomID = [[NSString alloc] initWithFormat:@"\"%i\"Leave Room!",self.theTargetUserID];
        [self showInfoAlertView:theLeaveRoomName :theLeaveRoomID];
        
        self.theTargetUserID = -1;
    }
    
    self.onlineUserMArray = [self getOnlineUserArray];
    [[UserListVC sharedUserListVC].onLineUserTableView reloadData];
}

// 网络断开消息
- (void) OnAnyChatLinkClose:(int) dwErrorCode
{
    [videoVC FinishVideoChat];
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    [[UserListVC sharedUserListVC].onlineUserMArray removeAllObjects];
    [[UserListVC sharedUserListVC].onLineUserTableView reloadData];
    
    theStateInfo.text = [NSString stringWithFormat:@"• OnLinkClose(ErrorCode:%i)",dwErrorCode];
    theOnLineLoginState = NO;
    [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_login_01"] forState:UIControlStateNormal];
    
    [self.navigationController popToRootViewControllerAnimated:YES];
    UIAlertView *networkAlertView = [[UIAlertView alloc] initWithTitle:@"网络断开,请重新登录."
                                                        message:@"Network disconnection."
                                                       delegate:self
                                              cancelButtonTitle:nil
                                              otherButtonTitles:@"确定",nil];
    [networkAlertView show];
}


#pragma mark - AnyChatTextMsgDelegate
// 发送文字的回调函数
- (void) OnAnyChatTextMsgCallBack:(int) dwFromUserid : (int) dwToUserid : (BOOL) bSecret : (NSString*) lpMsgBuf
{
    NSString *s_targetUserIDStr = [[NSString alloc] initWithFormat:@"%i",dwFromUserid];
    NSString *s_targetUserNameStr = [AnyChatPlatform GetUserName:dwFromUserid];
    
    if (lpMsgBuf != nil)
    {
        [[TextMsg_TransBufferVC sharedTextMsg_TransBufferVC].theMsgMArray
         addObject:[NSDictionary dictionaryWithObjectsAndKeys:
                    s_targetUserIDStr,@"targetUserIDStr",
                    s_targetUserNameStr,@"targetUserNameStr",
                    lpMsgBuf,@"contentStr",
                    @"receive",@"ACTStatus", nil]];
        
        [[TextMsg_TransBufferVC sharedTextMsg_TransBufferVC] TableViewReload];
    }
}


#pragma mark - AnyChatTransDataDelegate
// 透明通道回调函数
- (void) OnAnyChatTransBufferCallBack:(int) dwUserid : (NSData*) lpBuf
{
    NSString *s_targetUserIDStr = [[NSString alloc] initWithFormat:@"%i",dwUserid];
    NSString *s_targetUserNameStr = [AnyChatPlatform GetUserName:dwUserid];
    
    if (lpBuf != nil)
    {
        NSString *s_contentStr = [[NSString alloc] initWithData:lpBuf encoding:NSUTF8StringEncoding];
        [[TextMsg_TransBufferVC sharedTextMsg_TransBufferVC].theMsgMArray
         addObject:[NSDictionary dictionaryWithObjectsAndKeys:
                    s_targetUserIDStr,@"targetUserIDStr",
                    s_targetUserNameStr,@"targetUserNameStr",
                    s_contentStr,@"contentStr",
                    @"receive",@"ACTStatus", nil]];
    
        [[TextMsg_TransBufferVC sharedTextMsg_TransBufferVC] TableViewReload];
    }
}

// 透明通道数据扩展回调函数
- (void) OnAnyChatTransBufferExCallBack:(int) dwUserid : (NSData*) lpBuf : (int) wParam : (int) lParam : (int) dwTaskId{
}

// 文件传输回调函数
- (void) OnAnyChatTransFileCallBack:(int) dwUserid : (NSString*) lpFileName : (NSString*) lpTempFilePath : (int) dwFileLength : (int) wParam : (int) lParam : (int) dwTaskId
{
    NSString *s_targetUserNameStr = [AnyChatPlatform GetUserName:dwUserid];
    NSMutableDictionary *s_theTableViewRowDataMDict = [NSMutableDictionary dictionaryWithCapacity:5];
    [s_theTableViewRowDataMDict setValue:[[NSNumber alloc] initWithInt:dwUserid] forKey:@"targetUserIDNum"];
    [s_theTableViewRowDataMDict setValue:s_targetUserNameStr forKey:@"targetUserNameStr"];

    [s_theTableViewRowDataMDict setValue:@"image" forKey:@"fileTypeStr"];
    [s_theTableViewRowDataMDict setValue:@"receive" forKey:@"ACTStatusStr"];
    [s_theTableViewRowDataMDict setValue:lpTempFilePath forKey:@"contentPathStr"];
    
    [[TransFileVC sharedTransFileVC].theTableViewDataMArray addObject:s_theTableViewRowDataMDict];
    [[TransFileVC sharedTransFileVC] TableViewReload];
    
    UIAlertView *s_filePathAlert = [[UIAlertView alloc] initWithTitle:@"文件保存地址!"
                                                               message:lpFileName
                                                              delegate:nil
                                                     cancelButtonTitle:@"确定"
                                                     otherButtonTitles: nil];
    [s_filePathAlert show];
}

// 通信数据回调函数
- (void) OnAnyChatSDKFilterDataCallBack:(NSData*) lpBuf{
//  SDK Filter
}


#pragma mark - AnyChatRecordSnapShotDelegate
// 录像完成事件
- (void) OnAnyChatRecordCallBack:(int) dwUserid : (int) dwErrorCode : (NSString*) lpFileName : (int) dwElapse : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr
{
    theVideoRecordAlertView = [[UIAlertView alloc] initWithTitle:@"视频保存:"
                                                         message:lpFileName
                                                        delegate:self
                                               cancelButtonTitle:nil
                                               otherButtonTitles:@"预览录制",@"取消",nil];
    [theVideoRecordAlertView show];
    
    NSString *s_useNameStr;

    if ([lpUserStr isEqual: @"StarLocolSelfRecord"])
    {
        s_useNameStr = self.theMyUserName;
    }
    else if ([lpUserStr isEqual: @"StarLocolRemoteRecord"])
    {
        s_useNameStr = self.theTargetUserName;
    }
    else if ([lpUserStr isEqual: @"StarLocolMaxRecord"])
    {
        s_useNameStr = @"合成录制";
    }
    
    NSMutableDictionary *theVideoRecordParamMDict = [NSMutableDictionary dictionaryWithCapacity:5];
    [theVideoRecordParamMDict setValue:s_useNameStr forKey:@"useNameStr"];
    [theVideoRecordParamMDict setValue:[[NSNumber alloc] initWithInt:dwUserid] forKey:@"targetUserIDNum"];
    [theVideoRecordParamMDict setValue:[TransFileVC sharedTransFileVC].getTimeNow forKey:@"productTimeStr"];
    [theVideoRecordParamMDict setValue:@"mp4" forKey:@"fileTypeStr"];
    [theVideoRecordParamMDict setValue:lpFileName forKey:@"contentPathStr"];
    //Save the recordFileUrl
    self.theShowVCType = dwParam;
    if (dwParam == -1)
    {
        [self.theVideoRecordSelfMArray addObject:theVideoRecordParamMDict];
    }
    else
    {
        [self.theVideoRecordMArray addObject:theVideoRecordParamMDict];
    }
}

// 抓拍完成事件
- (void) OnAnyChatSnapShotCallBack:(int) dwUserid : (int) dwErrorCode : (NSString*) lpFileName : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr
{
    theSnapShotAlertView = [[UIAlertView alloc] initWithTitle:@"照片保存:"
                                                      message:lpFileName
                                                     delegate:self
                                            cancelButtonTitle:nil
                                            otherButtonTitles:@"抓拍预览",@"取消",nil];
    [theSnapShotAlertView show];
}


// 视频呼叫回调事件协议
#pragma mark - AnyChatCallDelegate

- (void) OnAnyChatVideoCallEventCallBack:(int) dwEventType : (int) dwUserId : (int) dwErrorCode : (int) dwFlags : (int) dwParam : (NSString*) lpUserStr{
    
    self.theTargetUserID = dwUserId;
    NSString *s_theCallbackUserName = [AnyChatPlatform GetUserName:dwUserId];
    self.theTargetUserName = s_theCallbackUserName;
    
    switch (dwEventType)
    {
        case BRAC_VIDEOCALL_EVENT_REQUEST:
        {
            [[UserListVC sharedUserListVC] showReplyAlertViewWithName:s_theCallbackUserName ID:dwUserId];
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_REPLY:
        {
            switch (dwErrorCode)
            {
                case GV_ERR_VIDEOCALL_CANCEL:
                {
                    [self dimissAlertView:[UserListVC sharedUserListVC].theReplyAlertView];
                    [self showInfoAlertView:@"用户取消会话" :@"CANCEL"];
                    [[UserListVC sharedUserListVC].theAudioPlayer stop];
                    
                    break;
                }
                    
                case GV_ERR_VIDEOCALL_REJECT:
                {
                    if ([UserListVC sharedUserListVC].theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:[UserListVC sharedUserListVC].theWaitingAlertView];
                    }
                    
                    [self showInfoAlertView:@"用户拒绝会话" :@"REJECT"];
                    
                    break;
                }
                    
                case GV_ERR_VIDEOCALL_OFFLINE:
                {
                    if ([UserListVC sharedUserListVC].theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:[UserListVC sharedUserListVC].theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"对方不在线" :@"OFFLINE"];
                    
                    break;
                }
                    
                case GV_ERR_VIDEOCALL_BUSY:
                {
                    if ([UserListVC sharedUserListVC].theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:[UserListVC sharedUserListVC].theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"用户在忙" :@"BUSY"];
                    
                    break;
                }
                    
                case GV_ERR_VIDEOCALL_TIMEOUT:
                {
                    if ([UserListVC sharedUserListVC].theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:[UserListVC sharedUserListVC].theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"会话请求超时" :@"TIMEOUT"];
                    
                    break;
                }
                    
                case GV_ERR_VIDEOCALL_DISCONNECT:
                {
                    if ([UserListVC sharedUserListVC].theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:[UserListVC sharedUserListVC].theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"网络断线" :@"DISCONNECT"];
                    
                    break;
                }
                    
                case GV_ERR_VIDEOCALL_NOTINCALL:
                {
                    if ([UserListVC sharedUserListVC].theWaitingAlertView != nil)
                    {
                        [self dimissAlertView:[UserListVC sharedUserListVC].theWaitingAlertView];
                    }
                    [self showInfoAlertView:@"用户不在呼叫状态" :@"NOTINCALL"];
                    
                    break;
                }
                    
            }
            
            break;
        }

        case BRAC_VIDEOCALL_EVENT_START:
        {
            if ([UserListVC sharedUserListVC].theWaitingAlertView != nil)
            {
                [self dimissAlertView:[UserListVC sharedUserListVC].theWaitingAlertView];
            }
            [[UserListVC sharedUserListVC].theAudioPlayer stop];
            
            //[AnyChatPlatform EnterRoom:dwParam :@""];
            [self.navigationController pushViewController:[[UserListVC sharedUserListVC] pushVC] animated:YES];
            
            break;
        }
            
        case BRAC_VIDEOCALL_EVENT_FINISH:
        {
            VideoVC *s_videoVC = [VideoVC new];
            [s_videoVC FinishVideoChat];
            [self showInfoAlertView:@"会话结束!" :@"Finish"];
            [self.navigationController popToViewController:[self.navigationController.viewControllers objectAtIndex:2]
                                                  animated:YES];
            break;
        }
 
    }
    
}


#pragma mark -
#pragma mark - Get & Save Settings Method
- (void)saveSettings
{
    NSString *documentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *filePath = [documentPath stringByAppendingPathComponent:kAnyChatSettingsFileName];
    [[NSArray arrayWithObjects:theServerIP.text,theServerPort.text,theUserName.text, nil] writeToFile:filePath atomically:YES];
}


#pragma mark - Instance Method

- (void)AnyChatNotifyHandler:(NSNotification*)notify
{
    NSDictionary* dict = notify.userInfo;
    [anyChat OnRecvAnyChatNotify:dict];
}

- (NSMutableArray *) getOnlineUserArray
{
    NSMutableArray *onLineUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
    [onLineUserList insertObject:[NSString stringWithFormat:@"%i",self.theMyUserID] atIndex:0];
    return onLineUserList;
}

- (IBAction)hideKeyBoard
{
    [theServerIP resignFirstResponder];
    [theServerPort resignFirstResponder];
    [theUserName resignFirstResponder];

}

- (IBAction)OnLoginBtnClicked:(id)sender
{
    if (theOnLineLoginState == YES)
    {
        [self OnLogout];
    }
    else
    {
        [self OnLogin];
    }
}

- (void) OnLogin
{
    
    if([theUserName.text length] == 0) {
        theUserName.text = kAnyChatUserName;
    }
    if([theServerIP.text length] == 0) {
        theServerIP.text = kAnyChatIP;
    }
    if([theServerPort.text length] == 0) {
        theServerPort.text = kAnyChatPort;
    }

    [self showLoadingAnimated];
    
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    
    [AnyChatPlatform Connect:theServerIP.text : [theServerPort.text intValue]];
    
    /*
     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
     */
    [AnyChatPlatform Login:theUserName.text :nil];

    
    [self hideKeyBoard];
    
}

- (void) OnLogout
{
    [AnyChatPlatform Logout];
    
    theOnLineLoginState = NO;
    
    theStateInfo.text = @"• Logout Server.";
    [theLoginBtn setBackgroundImage:[UIImage imageNamed:@"btn_login_01"] forState:UIControlStateNormal];
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)showSnapShotPhoto:(NSString *)theFilePath transform:(NSString *)transformParam
{   //Read the photo
    NSString *s_filesName = [theFilePath lastPathComponent];
    UIImage *s_Image = [UIImage imageWithContentsOfFile:theFilePath];

    UIImageView *theSnapShotImageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 44,kSelfView_Width,kSelfView_Height-44)];
    theSnapShotImageView.image = s_Image;
    theSnapShotImageView.contentMode = UIViewContentModeScaleAspectFit;
    
    if ([transformParam isEqualToString:@"Portrait"])
    {
        theSnapShotImageView.layer.transform = kLayer_Z_Axis_3DRotation(90.0);
    }
    
    ShowVC *theShowPhotoVC = [ShowVC new];
    [theShowPhotoVC.view addSubview:theSnapShotImageView];
    theShowPhotoVC.theShowVCNItem.title = s_filesName;
    theShowPhotoVC.theVideoRecordTableView.hidden = YES;
    theShowPhotoVC.theShowVCNItem.hidesBackButton = YES;
    theShowPhotoVC.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
    [self.navigationController presentViewController:theShowPhotoVC animated:YES completion:nil];
}


#pragma mark - AlertView delegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView == theSnapShotAlertView)
    {
        if (buttonIndex == 0)
        {
            [self showSnapShotPhoto:theSnapShotAlertView.message transform:@""];
        }
    }
    if (alertView == theVideoRecordAlertView)
    {
        if (buttonIndex == 0)
        {
            ShowVC *theShowVC = [ShowVC new];
            theShowVC.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
            [self.navigationController presentViewController:theShowVC animated:YES completion:nil];
        }
    }
}


#pragma mark - AlertView method

- (NSString *)showInfoAlertView:(NSString *)Title : (NSString *)subTitle
{
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:Title
                                                        message:subTitle
                                                       delegate:self
                                              cancelButtonTitle:nil
                                              otherButtonTitles:nil,nil];
    [alertView show];
    
    [self performSelector:@selector(dimissAlertView:) withObject:alertView afterDelay:1.5];
    
    return subTitle;
}

- (void) dimissAlertView:(UIAlertView *)alert {
    if(alert){
        [alert dismissWithClickedButtonIndex:[alert cancelButtonIndex] animated:YES];
    }
}


#pragma mark - Loading Animation Method

- (void)showLoadingAnimated
{
    HUD = [[MBProgressHUD alloc] initWithView:self.navigationController.view];
    [self.navigationController.view addSubview:HUD];
    
    HUD.delegate = self;
    HUD.dimBackground = YES;
    HUD.labelText = @"AnyChatFeatures";
    HUD.detailsLabelText = @"Loading...";
    [HUD show:YES];
}

#pragma mark - Rotation
- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark - UI Controls

- (void)setUI
{
    [self.navigationController setNavigationBarHidden:YES];
    
    theUserName.text = kAnyChatUserName;
    theServerIP.text = kAnyChatIP;
    theServerPort.text = kAnyChatPort;
    
    [theServerIP addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theServerPort addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    [theUserName addTarget:self action:@selector(textFieldShouldReturn:) forControlEvents:UIControlEventEditingDidEndOnExit];
    
    if (k_sysVersion < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }

    theVersionLab.text = [AnyChatPlatform GetSDKVersion];
    
    [self prefersStatusBarHidden];
    
}


@end
