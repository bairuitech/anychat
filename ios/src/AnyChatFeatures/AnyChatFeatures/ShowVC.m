//
//  SettingsViewController.m
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ShowVC.h"

@interface ShowVC ()

@end

@implementation ShowVC

@synthesize theShowVCNItem;
@synthesize theVideoRecordTableView;
@synthesize theVideoRecordList;
@synthesize theSelectContentPath;
@synthesize theObjType;


#pragma mark - Life cycle

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.theObjType = [AnyChatVC sharedAnyChatVC].theShowVCType;
    
    if (self.theObjType == -1)
    {
        self.theVideoRecordList = [AnyChatVC sharedAnyChatVC].theVideoRecordSelfMArray;
    }
    else
    {
        self.theVideoRecordList = [AnyChatVC sharedAnyChatVC].theVideoRecordMArray;
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


#pragma mark -
#pragma mark - UITableView Datasource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
//???:删除
//    if (self.theObjType == -1)
//    {
//        self.theVideoRecordList = [AnyChatVC sharedAnyChatVC].theVideoRecordSelfMArray;
//    }
//    else
//    {
//        self.theVideoRecordList = [AnyChatVC sharedAnyChatVC].theVideoRecordMArray;
//    }

    return self.theVideoRecordList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
//???:删除
//    self.theVideoRecordList = [AnyChatVC sharedAnyChatVC].theVideoRecordMArray;
    static NSString *cellIdentifier = @"Cell";
    
    UITableViewCell *s_cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    
    if (s_cell == nil)
    {
       s_cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:cellIdentifier];
    }
    
    s_cell.selectionStyle = UITableViewCellSelectionStyleBlue;
    
    NSDictionary *s_cellDataMDict = [self.theVideoRecordList objectAtIndex:[indexPath row]];
    //Dict info
    NSString *s_targetUserID = [[s_cellDataMDict objectForKey:@"targetUserIDNum"] stringValue];
    NSString *s_useNameStr = [s_cellDataMDict objectForKey:@"useNameStr"];
    NSString *s_productTime = [s_cellDataMDict objectForKey:@"productTimeStr"];
    
    if ([s_useNameStr isEqual:@"合成录制"])
    {
        s_cell.textLabel.text = [[NSString alloc] initWithFormat:@"%@",s_useNameStr];
    }
    else
    {
        s_cell.textLabel.text = [[NSString alloc] initWithFormat:@"%@(%@)",s_useNameStr,s_targetUserID];
    }

    s_cell.detailTextLabel.text = s_productTime;
    
    return s_cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSDictionary *selectCellDataMDict = [self.theVideoRecordList objectAtIndex:[indexPath row]];
    self.theSelectContentPath = [selectCellDataMDict objectForKey:@"contentPathStr"];
    // init
    QLPreviewController *previewController = [[QLPreviewController alloc] init];
    previewController.dataSource = self;
    previewController.delegate = self;
    // start previewing the document at the current section index
    previewController.currentPreviewItemIndex = indexPath.row;
    [self presentViewController:previewController animated:YES completion:nil];
}

#pragma mark - QLPreviewControllerDataSource

- (NSInteger)numberOfPreviewItemsInPreviewController:(QLPreviewController *)previewController
{
    return 1;
}

- (id)previewController:(QLPreviewController *)previewController previewItemAtIndex:(NSInteger)idx
{
    NSURL *fileURL = [NSURL fileURLWithPath:self.theSelectContentPath];
    return fileURL;
}


#pragma mark -
#pragma mark - Instance Method

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction)LeaveBtn_OnClick
{
    [self dismissViewControllerAnimated:YES completion:nil];
}


#pragma mark - UITouch

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self LeaveBtn_OnClick];
}

- (IBAction)clearDatas_OnClick
{
    [self.theVideoRecordList removeAllObjects];
    [self.theVideoRecordTableView reloadData];
}


#pragma mark - UI Controls

- (BOOL)prefersStatusBarHidden
{
    return YES;
}



@end
