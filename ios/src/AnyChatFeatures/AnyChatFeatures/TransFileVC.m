//
//  TransFileVC.m
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "TransFileVC.h"

@interface TransFileVC ()

@end

@implementation TransFileVC

@synthesize theTransFileNItem;
@synthesize theTransFileTableView;
@synthesize theTableViewDataMArray;
@synthesize theToolbar;
@synthesize theTableViewRowDataMDict;
@synthesize theFileNameLab;
@synthesize theIconImageView;
@synthesize theTransFileTaskID;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}


#pragma mark - Life Cycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.theTableViewDataMArray = [[NSMutableArray alloc] initWithCapacity:5];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUIControls];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark - Shared Instance

kGCD_SINGLETON_FOR_CLASS(TransFileVC);


#pragma mark - TableView DataSource

-(NSInteger) numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

-(NSInteger) tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.theTableViewDataMArray.count;
}

-(UITableViewCell *) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *Cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (Cell == nil)
    {
        NSArray *nibs = [[NSBundle mainBundle] loadNibNamed:@"theTransFileCell" owner:self options:nil];
        Cell = [nibs objectAtIndex:0];
    }
    
    UILabel *s_titleLab = (UILabel *)[Cell viewWithTag:kTheTransFileCell_titleLabTag];
    UILabel *s_statusLab = (UILabel *)[Cell viewWithTag:kTheTransFileCell_statusLabTag];
    UIImageView *s_imageView = (UIImageView *)[Cell viewWithTag:kTheTransFileCell_imageViewTag];
    
    NSString *s_Content = @"";
    
    NSDictionary *s_tableViewRowDataMDict = [self.theTableViewDataMArray objectAtIndex:[indexPath row]];
    //Dict info
    NSString *s_targetUserName = [s_tableViewRowDataMDict objectForKey:@"targetUserNameStr"];
    NSString *s_fileType = [s_tableViewRowDataMDict objectForKey:@"fileTypeStr"];
    NSString *s_contentPath = [s_tableViewRowDataMDict objectForKey:@"contentPathStr"];
    
    //actionStatus
    NSString *actionStatus = [s_tableViewRowDataMDict objectForKey:@"ACTStatusStr"];
    if ([actionStatus isEqualToString:@"send"])
    {
        s_titleLab.textColor = [UIColor redColor];
        s_Content = [[NSString alloc] initWithFormat:@"发送“%@”文件到“%@”",s_fileType,s_targetUserName];
    }
    else if ([actionStatus isEqualToString:@"receive"])
    {
        s_titleLab.textColor = [UIColor blueColor];
        s_Content = [[NSString alloc] initWithFormat:@"接收“%@”的“%@”文件",s_targetUserName,s_fileType];
    }
    
    //Cell config
    s_titleLab.text = s_Content;
    s_statusLab.text = s_contentPath;
    if ([s_fileType isEqualToString:@"image"])
    {
        s_imageView.image = [UIImage imageWithContentsOfFile:s_contentPath];
    }
    
    return Cell;
}


#pragma mark - TableView Delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (CGFloat)tableView:(UITableView *)tabelView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 50.0f;
}


#pragma mark - Instance Method

- (void)sendFiles:(NSString *)contentPathStr
{
    int s_targetUserIDInt = [AnyChatVC sharedAnyChatVC].theTargetUserID;
    NSNumber *s_targetUserIDNum = [[NSNumber alloc] initWithInt:s_targetUserIDInt];
    NSString *s_targetUserNameStr = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    NSString *s_fileTypeStr = @"image";

    // 传送文本消息
    self.theTransFileTaskID = [AnyChatPlatform TransFile:s_targetUserIDInt :contentPathStr :0 :0 :0];
    if (self.theTransFileTaskID > 0)
    {
        self.theTableViewRowDataMDict = [NSMutableDictionary dictionaryWithCapacity:3];
        [self.theTableViewRowDataMDict setValue:s_targetUserIDNum forKey:@"targetUserIDNum"];
        [self.theTableViewRowDataMDict setValue:s_targetUserNameStr forKey:@"targetUserNameStr"];
        [self.theTableViewRowDataMDict setValue:s_fileTypeStr forKey:@"fileTypeStr"];
        [self.theTableViewRowDataMDict setValue:@"send" forKey:@"ACTStatusStr"];
        [self.theTableViewRowDataMDict setValue:contentPathStr forKey:@"contentPathStr"];
        
        [self showTransFileLoadingAnimated];
    }
    else
    {
        [[TextMsg_TransBufferVC sharedTextMsg_TransBufferVC] NetworkAnomaliesAlert];
    }
}

- (void)TableViewReload
{
    [self.theTransFileTableView reloadData];
    [self.theTransFileTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:[self.theTableViewDataMArray count]-1 inSection:0]
                                    atScrollPosition: UITableViewScrollPositionBottom
                                            animated:YES];
}

- (IBAction)Leave_Onclick
{
    [self clearDatas_OnClick];
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)clearDatas_OnClick
{
    [self.theTableViewDataMArray removeAllObjects];
    [self.theTransFileTableView reloadData];
}

- (NSString *)getTimeNow
{
    NSString* timeNow;
    
    NSDateFormatter * formatter = [[NSDateFormatter alloc ] init];

    [formatter setDateFormat:@"MMdd_hhmmss"];
    timeNow = [formatter stringFromDate:[NSDate date]];
    
    return timeNow;
}


#pragma mark - Access photo album

- (IBAction)theTransFileBtn_OnClick;
{
    int theTargetUserID = [AnyChatVC sharedAnyChatVC].theTargetUserID;
    if (theTargetUserID != 0 && theTargetUserID != -1 && theImageFilePath != nil)
    {
        [self sendFiles:theImageFilePath];
    }
    else if(theTargetUserID == -1 || theTargetUserID == 0)
    {
        [[AnyChatVC sharedAnyChatVC] showInfoAlertView:@"请选择您要发送的用户。"
                                                      :@"Warning"];
    }
    else if(theImageFilePath == nil)
    {
        [[AnyChatVC sharedAnyChatVC] showInfoAlertView:@"请再重新选择图片。"
                                                      :@"Warning"];
    }
}

- (IBAction)theOpenAlbumBtn_OnClick
{    //open photo album
    myActionSheet = [[UIActionSheet alloc]
                     initWithTitle:nil
                     delegate:self
                     cancelButtonTitle:@"取消"
                     destructiveButtonTitle:nil
                     otherButtonTitles:@"打开手机相册",nil];
    
    [myActionSheet showInView:self.view];
}

-(void)LocalPhoto
{
    UIImagePickerController *picker = [[UIImagePickerController alloc] init];
    
    picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    picker.delegate = self;
    picker.allowsEditing = YES;
    [self.navigationController presentViewController:picker animated:YES completion:nil];
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    switch (buttonIndex)
    {
        case 0:
            [self LocalPhoto];
            break;
    }
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    //Cancel Picker
    [picker dismissViewControllerAnimated:YES completion:nil];
}

-(void)imagePickerController:(UIImagePickerController*)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSString *s_type = [info objectForKey:UIImagePickerControllerMediaType];
    NSString *s_ImageName = [[NSString alloc] initWithFormat:@"%@.png",[self getTimeNow]];
    NSString *s_Path_ImageName = [[NSString alloc] initWithFormat:@"/%@",s_ImageName];
    
    //photo type
    if ([s_type isEqualToString:@"public.image"])
    {
        //photo to NSData
        UIImage* imageOfSetected = [info objectForKey:@"UIImagePickerControllerOriginalImage"];
        NSData *dataOfSetectedPhoto;
        if (UIImagePNGRepresentation(imageOfSetected) == nil)
        {
            dataOfSetectedPhoto = UIImageJPEGRepresentation(imageOfSetected, 1.0);
        }
        else
        {
            dataOfSetectedPhoto = UIImagePNGRepresentation(imageOfSetected);
        }
        
        //get documents path
        NSString * DocumentsPath = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
        NSFileManager *fileManager = [NSFileManager defaultManager];
        //dataOfPhoto copy to documents and save to image.png
        [fileManager createDirectoryAtPath:DocumentsPath withIntermediateDirectories:YES attributes:nil error:nil];
        [fileManager createFileAtPath:[DocumentsPath stringByAppendingString:s_Path_ImageName] contents:dataOfSetectedPhoto attributes:nil];
        //get photo path
        theImageFilePath = [[NSString alloc]initWithFormat:@"%@%@",DocumentsPath,s_Path_ImageName];
        
        [picker dismissViewControllerAnimated:YES completion:nil];
        
        //From the selected photos to create ICONS in the UI
        self.theIconImageView.image = imageOfSetected;
        self.theFileNameLab.text = s_ImageName;
    }
}


#pragma mark - Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark - TransFile Loading Animation

- (void)showTransFileLoadingAnimated
{
    HUD = [[MBProgressHUD alloc] initWithView:self.navigationController.view];
    [self.navigationController.view addSubview:HUD];
    
    HUD.mode = MBProgressHUDModeDeterminate;
    
    HUD.delegate = self;
    HUD.dimBackground = YES;
    HUD.labelText = @"Loading";
    
    [HUD showWhileExecuting:@selector(myProgressTask) onTarget:self withObject:nil animated:YES];
}

- (void)myProgressTask
{
    float theTransFileProgress = 0.0f;
    int theTransTaskStatus = 0;

    while (theTransFileProgress <= 100.0f && theTransTaskStatus != kTransStatus_Success)
    {
        theTransFileProgress = [AnyChatPlatform QueryTransTaskInfoInt:[AnyChatVC sharedAnyChatVC].theMyUserID
                                                                          :self.theTransFileTaskID
                                                                          :BRAC_TRANSTASK_PROGRESS];
        if (theTransFileProgress > 98.0f )
        {
            theTransTaskStatus = [AnyChatPlatform QueryTransTaskInfoInt:[AnyChatVC sharedAnyChatVC].theMyUserID
                                                                    :self.theTransFileTaskID
                                                                    :BRAC_TRANSTASK_STATUS];
        }

        HUD.progress = kTransFileProgress(theTransFileProgress);
        usleep(50000);
    }
    
    if (theTransTaskStatus == kTransStatus_Success)
    {
        [self.theTableViewDataMArray addObject:self.theTableViewRowDataMDict];
        [self TableViewReload];

        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"成功发送！"
                                                            message:@"Send a success."
                                                           delegate:self
                                                  cancelButtonTitle:nil
                                                  otherButtonTitles:@"确定",nil];
        [alertView show];
    }
}


#pragma mark - UI Controls

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)setUIControls
{
    //Title
    NSString *targetUserName = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    self.theTransFileNItem.title = [[NSString alloc] initWithFormat:@"与“%@”传输文件中",targetUserName];
    [self.theTransFileTableView reloadData];
    
    [self.navigationController setNavigationBarHidden:YES];
    
    if ([[UIDevice currentDevice].systemVersion floatValue] < 7.0)
    {
        [[UIApplication sharedApplication] setStatusBarHidden:YES];
    }
    
    [self prefersStatusBarHidden];
    
    UIView *headerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, kSelfView_Width, 70.0f)];
    UIView *footerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, kSelfView_Width, 70.0f)];
    self.theTransFileTableView.tableFooterView = headerView;
    self.theTransFileTableView.tableHeaderView = footerView;
}


@end
