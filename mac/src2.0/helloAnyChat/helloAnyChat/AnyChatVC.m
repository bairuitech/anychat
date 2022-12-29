//
//  AnyChatVC.m
//  HelloAnyChat
//
//  Created by Chen on 15-3-28.
//  Copyright (c) 2015年 AlexChen. All rights reserved.
//

#import "AnyChatVC.h"

@interface AnyChatVC ()

@property (weak) IBOutlet NSTextField *widthText;

@property (weak) IBOutlet NSTextField *heightText;

@end


@implementation AnyChatVC



- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    [AnyChatPlatform InitSDK:0];
    
    anychat = [[AnyChatPlatform alloc] init];
    anychat.notifyMsgDelegate = self;
    anychat.transDataDelegate = self;
    
    [self setUI];
}


#pragma mark - NSTableView delegate & datasource methods


- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    if (tableView == self.onlineUserTableView) {
        return [self.onlineUserMArray count];
    } else if (tableView == self.camTableView) {
        return [self.cameraDeviceArray count];
    }
    return 0;
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    
    NSTableCellView *cellView = [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
    
    if( [tableColumn.identifier isEqualToString:@"userID"] )
    {
        NSString *RandomNo = [[NSString alloc] initWithFormat:@"%i",[self getRandomNumber:1 to:5]];
        cellView.imageView.image = [NSImage imageNamed:RandomNo];
        
        if (row < self.onlineUserMArray.count) {
            
            int userID = [[self.onlineUserMArray objectAtIndex:row] intValue];
            NSString *userName = [AnyChatPlatform GetUserName:userID];
            if (self.pvMyUserID == userID)
            {
                cellView.textField.stringValue = [NSString stringWithFormat:@"%@（自己）",userName];
            }
            else
            {
                cellView.textField.stringValue = [NSString stringWithFormat:@"%@（%d）",userName,userID];
            }
        }
        
        return cellView;
    } else if( [tableColumn.identifier isEqualToString:@"camID"] )
    {
        if (row < self.cameraDeviceArray.count) {
            NSString *deviceName = [self.cameraDeviceArray objectAtIndex:row];
            cellView.textField.stringValue = deviceName;
//            int userID = [[self.onlineUserMArray objectAtIndex:row] intValue];
//            NSString *userName = [AnyChatPlatform GetUserName:userID];
//            if (self.pvMyUserID == userID)
//            {
//                cellView.textField.stringValue = [NSString stringWithFormat:@"%@（自己）",userName];
//            }
//            else
//            {
//                cellView.textField.stringValue = [NSString stringWithFormat:@"%@（%d）",userName,userID];
//            }
        }
    }
    return cellView;
}

- (void)tableViewSelectionDidChange:(NSNotification *)notification
{
    if (notification.object == self.onlineUserTableView) {
        if (self.onlineUserTableView.selectedRow >= 0 && self.onlineUserTableView.selectedRow < self.onlineUserMArray.count) {
            int selectUserID = [[self.onlineUserMArray objectAtIndex:self.onlineUserTableView.selectedRow] intValue];
            self.pvTargerID = selectUserID;
            
            [AnyChatPlatform UserSpeakControl:selectUserID :YES];
            [AnyChatPlatform SetVideoPos:selectUserID :self.remoteVideo :0 :0 :0 :0];
            [AnyChatPlatform UserCameraControl:selectUserID :YES];
        }
    } else if (notification.object == self.camTableView) {
        if (self.camTableView.selectedRow >= 0 && self.camTableView.selectedRow < self.cameraDeviceArray.count) {
            [AnyChatPlatform SelectVideoCapture:[self.cameraDeviceArray objectAtIndex:self.camTableView.selectedRow]];
        }
    
    }
}



#pragma mark - Delegate Method

- (void)OnAnyChatConnect:(BOOL)bSuccess
{
    if (bSuccess)
    {
        [self textViewAddContentStr:@"• Success connected to server" TextView:self.pvTextView];
    }
}

- (void)OnAnyChatLogin:(int)dwUserId :(int)dwErrorCode
{
    self.onlineUserMArray = [NSMutableArray arrayWithCapacity:5];
    
    NSString *appendStr = @"";
    if(dwErrorCode == GV_ERR_SUCCESS)
    {
        self.pvMyUserID = dwUserId;
        appendStr = [NSString stringWithFormat:@" Login successed. Self UserId: %d", dwUserId];
    }
    else
    {
        appendStr = [NSString stringWithFormat:@"• Login failed(ErrorCode:%i)",dwErrorCode];
    }
    
    [self textViewAddContentStr:appendStr TextView:self.pvTextView];
//    BRAC_SetSDKOption(70,4);
//    [AnyChatPlatform SetSDKOptionInt:70 :4];
//    [AnyChatPlatform SetSDKOptionString:BRAC_SO_CORESDK_WRITELOG :[NSString stringWithFormat:@"SetSDKOptionInt 70"]];
    
//    BRAC_UserInfoControl(-1,BRAC_USERINFO_CTRLCODE_DEBUGLOG,2,1,null)
    
    [AnyChatPlatform UserInfoControl:-1 :BRAC_USERINFO_CTRLCODE_DEBUGLOG :2 :1 :@""];
    [AnyChatPlatform EnterRoom:[self.pvRoomNumTextField.stringValue intValue] :@""];
}

- (void)OnAnyChatEnterRoom:(int)dwRoomId :(int)dwErrorCode
{
    if(dwErrorCode == 0)
    {
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
        
        [self mirroredButtonPress:nil];
        
        int iWidth = [self.widthText.stringValue intValue];
        int iHeight = [self.heightText.stringValue intValue];
        if  (iWidth > 0) {
            [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_WIDTHCTRL :iWidth];
        }

        if  (iHeight > 0) {
            [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_HEIGHTCTRL :iHeight];
        }
        // 采用本地视频参数设置，使参数设置生效
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_APPLYPARAM :1];
        
        [AnyChatPlatform UserSpeakControl:-1 :YES];
        
//        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];
//        [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
//        [AnyChatPlatform UserCameraControl:-1 :YES];
        
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :0];
        [AnyChatPlatform SetVideoPos:-1 :self.localImageView :0 :0 :0 :0];
        [AnyChatPlatform UserCameraControl:-1 :YES];
    }
    else
    {
        NSString *appendStr = [NSString stringWithFormat:@"• Enter room failed(ErrorCode:%i)",dwErrorCode];
        [self textViewAddContentStr:appendStr TextView:self.pvTextView];
    }
    
    [self.onlineUserTableView reloadData];
}

- (void)OnAnyChatOnlineUser:(int)dwUserNum :(int)dwRoomId
{
    self.onlineUserMArray = [self getOnlineUserArray];
    [self.onlineUserTableView reloadData];
}

- (void)OnAnyChatUserEnterRoom:(int)dwUserId
{
    self.onlineUserMArray = [self getOnlineUserArray];
    [self.onlineUserTableView reloadData];
}

- (void)OnAnyChatUserLeaveRoom:(int)dwUserId
{
    if (self.pvTargerID == dwUserId)
    {
        [self FinishVideoChat];
        
        NSString *appendStr = [[NSString alloc] initWithFormat:@"\"%d\"已离开房间!",dwUserId];
        [self textViewAddContentStr:appendStr TextView:self.pvTextView];
    }
    
    self.onlineUserMArray = [self getOnlineUserArray];
    [self.onlineUserTableView reloadData];
}

- (void)OnAnyChatLinkClose:(int)dwErrorCode
{
    [self OnLogout];
    NSString *appendStr = [NSString stringWithFormat:@"• OnLinkClose(ErrorCode:%i)",dwErrorCode];
    [self textViewAddContentStr:appendStr TextView:self.pvTextView];
}


#pragma mark - IBAction Method

- (IBAction)OnLoginBtnClicked:(id)sender
{
    [self OnLogin];
}

- (IBAction) OnLogoutBtnClicked:(id)sender
{
    [self OnLogout];
    [self textViewAddContentStr:@"• Logout Server." TextView:self.pvTextView];
}


#pragma mark - Instace Method

-(void)textViewAddContentStr:(NSString *)appendStr TextView:(NSTextView *)sTextView
{
    NSString *newStr = [appendStr stringByAppendingString:@" \n"];
    [[[sTextView textStorage] mutableString] appendString:newStr];
}

- (int)getRandomNumber:(int)from to:(int)to
{
    return (int)(from + (arc4random() % (to - from + 1)));
}

- (NSMutableArray *) getOnlineUserArray
{
    NSMutableArray *onLineUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
//    [onLineUserList insertObject:[NSString stringWithFormat:@"%i",self.pvMyUserID] atIndex:0];
    return onLineUserList;
}

- (void) OnLogin
{
    self.pvTextView.string = @"";
    
    if([self.pvServerIPTextField.stringValue length] == 0)
    {
        self.pvServerIPTextField.stringValue = @"demo.anychat.cn";
    }
    if([self.pvServerPortTextField.stringValue length] == 0)
    {
        self.pvServerPortTextField.stringValue = @"8906";
    }
    if([self.pvUserNameTextField.stringValue length] == 0)
    {
        self.pvUserNameTextField.stringValue = @"AnyChat_iMac";
    }
    if([self.pvRoomNumTextField.stringValue length] == 0)
    {
        self.pvRoomNumTextField.stringValue = @"4";
    }
    
    /*
     * AnyChat可以连接自主部署的服务器、也可以连接AnyChat视频云平台；
     * 连接自主部署服务器的地址为自设的服务器IP地址或域名、端口；
     * 连接AnyChat视频云平台的服务器地址为：cloud.anychat.cn；端口为：8906
     */
    [AnyChatPlatform Connect:self.pvServerIPTextField.stringValue :[self.pvServerPortTextField.stringValue intValue]];
    
    /*
     * AnyChat支持多种用户身份验证方式，包括更安全的签名登录，详情请参考：http://bbs.anychat.cn/forum.php?mod=viewthread&tid=2211&highlight=%C7%A9%C3%FB
     */
    [AnyChatPlatform Login:self.pvUserNameTextField.stringValue :@""];
    
//    [AnyChatPlatform EnterRoom:[self.pvRoomNumTextField.stringValue intValue] :@""];

}

- (void) OnLogout
{
    [self FinishVideoChat];
    [AnyChatPlatform LeaveRoom:-1];
    [AnyChatPlatform Logout];
    
    [self.onlineUserMArray removeAllObjects];
    [self.onlineUserTableView reloadData];

    self.pvServerIPTextField.stringValue = @"";
    self.pvServerPortTextField.stringValue = @"";
    self.pvUserNameTextField.stringValue = @"";
    self.pvRoomNumTextField.stringValue = @"";
    self.pvTextView.string = @"";
    self.remoteVideo.image = [NSImage imageNamed:@"BG_macVideo"];
}

- (void) FinishVideoChat
{
    [AnyChatPlatform UserSpeakControl: -1 : NO];
    [AnyChatPlatform UserCameraControl: -1 : NO];
    
    [AnyChatPlatform UserSpeakControl: self.pvTargerID : NO];
    [AnyChatPlatform UserCameraControl: self.pvTargerID : NO];
    
    self.pvTargerID = -1;
}

- (void)AnyChatNotifyHandler:(NSNotification *)notify
{
    NSDictionary* dict = notify.userInfo;
    [anychat OnRecvAnyChatNotify:dict];
}

- (void) OnLocalVideoInit:(id)session
{
    self.localCaptureLayer = [AVCaptureVideoPreviewLayer layerWithSession: (AVCaptureSession*)session];
    self.localCaptureLayer.frame = CGRectMake(0, 0, 205, 142);
    self.localCaptureLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    [self.localView.layer addSublayer:self.localCaptureLayer];
}

- (void) OnLocalVideoRelease:(id)sender
{
    if(self.localCaptureLayer)
    {
        self.localCaptureLayer = nil;
    }
}

- (void) setUI
{
    self.localView.wantsLayer = YES;
    self.localView.canDrawConcurrently = YES;
    self.localView.layer.contents = (id)[self nsImageToCGImageRef:[NSImage imageNamed:@"BG_macVideo"]];
    
    self.localView.hidden = YES;
    self.localImageView.image = [NSImage imageNamed:@"BG_macVideo"];
}

- (CGImageRef)nsImageToCGImageRef:(NSImage*)image;
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

- (IBAction)videoSettingButtonPress:(id)sender {
    [AnyChatPlatform UserCameraControl:-1 :NO];

    int iWidth = [self.widthText.stringValue intValue];
    int iHeight = [self.heightText.stringValue intValue];
    if  (iWidth > 0) {
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_WIDTHCTRL :iWidth];
    }

    if  (iHeight > 0) {
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_HEIGHTCTRL :iHeight];
    }
    // 采用本地视频参数设置，使参数设置生效
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_APPLYPARAM :1];
    
    [AnyChatPlatform UserSpeakControl:-1 :YES];
    
//        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];
//        [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
//        [AnyChatPlatform UserCameraControl:-1 :YES];
    
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :0];
    [AnyChatPlatform SetVideoPos:-1 :self.localImageView :0 :0 :0 :0];
    [AnyChatPlatform UserCameraControl:-1 :YES];
}

- (void) OnAnyChatTransBufferCallBack:(int) dwUserid : (NSData*) lpBuf
{
    NSString *s_targetUserIDStr = [[NSString alloc] initWithFormat:@"%i",dwUserid];
    NSString *s_targetUserNameStr = [AnyChatPlatform GetUserName:dwUserid];
    
    if (lpBuf != nil)
    {
        NSString *s_contentStr = [[NSString alloc] initWithData:lpBuf encoding:NSUTF8StringEncoding];
 
        NSLog(@"OnAnyChatTransBufferCallBack:%@",s_contentStr);
    }
}

// 透明通道数据扩展回调函数
- (void) OnAnyChatTransBufferExCallBack:(int) dwUserid : (NSData*) lpBuf : (int) wParam : (int) lParam : (int) dwTaskId{
    NSString *s_targetUserIDStr = [[NSString alloc] initWithFormat:@"%i",dwUserid];
    NSString *s_targetUserNameStr = [AnyChatPlatform GetUserName:dwUserid];
    
    if (lpBuf != nil)
    {
        NSString *s_contentStr = [[NSString alloc] initWithData:lpBuf encoding:NSUTF8StringEncoding];
 
        NSLog(@"OnAnyChatTransBufferCallBackEx:%@",s_contentStr);
    }
}

- (void) OnAnyChatTransFileCallBack:(int) dwUserid : (NSString*) lpFileName : (NSString*) lpTempFilePath : (int) dwFileLength : (int) wParam : (int) lParam : (int) dwTaskId
{
    [self textViewAddContentStr:[NSString stringWithFormat:@"receive File userid:%d path:%@",dwUserid,lpTempFilePath] TextView:self.pvTextView];
    
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = @"接收文件提醒";
    alert.informativeText = [NSString stringWithFormat:@"文件保存:%@",lpTempFilePath];
    [alert addButtonWithTitle:@"确定"];
    [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
        if (returnCode == NSAlertFirstButtonReturn){
            
        }
    }];
}
- (void) OnAnyChatSDKFilterDataCallBack:(NSData*) lpBuf
{
    
}
- (IBAction)transFileButtonPress:(id)sender {
    if (self.onlineUserTableView.selectedRow >= 0 && self.onlineUserTableView.selectedRow < self.onlineUserMArray.count) {
        int selectUserID = [[self.onlineUserMArray objectAtIndex:self.onlineUserTableView.selectedRow] intValue];
        self.pvTargerID = selectUserID;
        
        NSOpenPanel *spanel = [NSOpenPanel openPanel];
        NSString *path = @"~/Documents";
        [spanel setDirectory:[path stringByExpandingTildeInPath]];
        [spanel setPrompt:NSLocalizedString(@"Open",nil)];
        //[spanel setRequiredFileType:@"jpeg"];
    //    NSArray * fileTypes = [NSArray arrayWithObjects:@"jpeg", @"jpg", @"png", nil];
        
        NSArray * fileTypes = [NSArray arrayWithObjects:@"ppt",@"pptx",@"xls",@"xlsx",@"doc",@"docx",@"pdf",@"jpg",@"jpeg",@"png",@"bmp",@"txt",@"MP3",@"MP4",@"log", nil];
    //    [spanel setCanChooseDirectories:NO];
    //    [spanel setAllowedFileTypes:fileTypes];
        [spanel setAllowsMultipleSelection:YES];
        int i = [spanel runModalForTypes:fileTypes];
        
        if(i == NSOKButton){
//            [self openFile:[spanel filename]];
            NSArray * select_files = [spanel filenames] ;

            for (int i=0; i<select_files.count; i++)

            {

               NSString *path_all= [select_files objectAtIndex:i];



                NSLog(@"%@",path_all);
                
                if (self.pvTargerID != 0) {
                    
                    [AnyChatPlatform TransFile:self.pvTargerID :path_all :0 :0 :0];
                    
                    [self textViewAddContentStr:[NSString stringWithFormat:@"TransFile userid:%d path:%@",self.pvTargerID,path_all] TextView:self.pvTextView];
                }

            }
   
        }
        
    } else {
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = @"提醒";
        alert.informativeText = [NSString stringWithFormat:@"%@",@"请选择需要发送的用户"];
        [alert addButtonWithTitle:@"确定"];
        [alert beginSheetModalForWindow:[self.view window] completionHandler:^(NSModalResponse returnCode) {
            if (returnCode == NSAlertFirstButtonReturn){
                
            }
        }];
    }
}

-(void)openFile:(NSString*)filePath
{
    if (self.pvTargerID != 0) {
        
        [AnyChatPlatform TransFile:self.pvTargerID :filePath :0 :0 :0];
    }
}

@end

