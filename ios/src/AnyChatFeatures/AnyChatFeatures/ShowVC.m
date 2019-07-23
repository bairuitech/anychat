//
//  SettingsViewController.m
//  AnyChatCallCenter
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ShowVC.h"
#import <MediaPlayer/MediaPlayer.h>
@interface ShowVC ()
@property (strong, nonatomic) MPMoviePlayerViewController *moviePlayerVC;

@property (strong, nonatomic) NSMutableArray                *theVideoRecordList;
@property (strong, nonatomic) NSString                      *theSelectContentPath;
@end

@implementation ShowVC


#pragma mark - Life cycle


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
    [self p_configNavItem];
    self.theVideoRecordTableView.tableFooterView = [UIView new];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)p_configNavItem {
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(clearDatas_OnClick) forControlEvents:UIControlEventTouchUpInside];
    [button setImage:[UIImage imageNamed:@"icon_remove"] forState:UIControlStateNormal];
    [button sizeToFit];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = rightItem;
}
#pragma mark -
#pragma mark - UITableView Datasource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{

    return self.theVideoRecordList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{

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

    s_cell.detailTextLabel.text = [NSString stringWithFormat:@"录制时间：%@",s_productTime];
    
    return s_cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSDictionary *selectCellDataMDict = [self.theVideoRecordList objectAtIndex:[indexPath row]];
    self.theSelectContentPath = [selectCellDataMDict objectForKey:@"contentPathStr"];
    // init
    if (self.theSelectContentPath) {
        
        NSURL *url =  [NSURL fileURLWithPath:self.theSelectContentPath];
        
        // 实例化
        _moviePlayerVC = [[MPMoviePlayerViewController alloc] initWithContentURL:url];
        
        // 弹出控制器
        [self.navigationController presentViewController:_moviePlayerVC animated:YES completion:nil];
        
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];

}

#pragma mark - Instance Method

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - UITouch

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction)clearDatas_OnClick
{
    [self.theVideoRecordList removeAllObjects];
    [self.theVideoRecordTableView reloadData];
}

@end
