//
//  AnyChatVC.m
//  HelloAnyChat
//
//  Created by Chen on 15-3-28.
//  Copyright (c) 2015年 AlexChen. All rights reserved.
//

#import "AnyChatVC.h"

@interface AnyChatVC ()

@end


@implementation AnyChatVC



- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(AnyChatNotifyHandler:) name:@"ANYCHATNOTIFY" object:nil];
    
    [AnyChatPlatform InitSDK:0];
    
    anychat = [[AnyChatPlatform alloc] init];
    anychat.notifyMsgDelegate = self;
    
    [self setUI];
}


#pragma mark - NSTableView delegate & datasource methods


- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return [self.onlineUserMArray count];
}

- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    
    NSTableCellView *cellView = [tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
    
    if( [tableColumn.identifier isEqualToString:@"userID"] )
    {
        NSString *RandomNo = [[NSString alloc] initWithFormat:@"%i",[self getRandomNumber:1 to:5]];
        cellView.imageView.image = [NSImage imageNamed:RandomNo];
        
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
        
        return cellView;
    }
    return cellView;
}

- (void)tableViewSelectionDidChange:(NSNotification *)notification
{
    int selectUserID = [[self.onlineUserMArray objectAtIndex:self.onlineUserTableView.selectedRow] intValue];
    self.pvTargerID = selectUserID;

    [AnyChatPlatform UserSpeakControl:selectUserID :YES];
    [AnyChatPlatform SetVideoPos:selectUserID :self.remoteVideo :0 :0 :0 :0];
    [AnyChatPlatform UserCameraControl:selectUserID :YES];
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
}

- (void)OnAnyChatEnterRoom:(int)dwRoomId :(int)dwErrorCode
{
    if(dwErrorCode == 0)
    {
        [AnyChatPlatform UserSpeakControl:-1 :YES];
        
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_OVERLAY :1];
        [AnyChatPlatform SetVideoPos:-1 :self :0 :0 :0 :0];
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
    [onLineUserList insertObject:[NSString stringWithFormat:@"%i",self.pvMyUserID] atIndex:0];
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
        self.pvUserNameTextField.stringValue = @"mAnyChat";
    }
    if([self.pvRoomNumTextField.stringValue length] == 0)
    {
        self.pvRoomNumTextField.stringValue = @"10";
    }
    
    [AnyChatPlatform Connect:self.pvServerIPTextField.stringValue :[self.pvServerPortTextField.stringValue intValue]];
    [AnyChatPlatform Login:self.pvUserNameTextField.stringValue :@""];
    [AnyChatPlatform EnterRoom:[self.pvRoomNumTextField.stringValue intValue] :@""];

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



@end
