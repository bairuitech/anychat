//
//  BusinessListController.m
//  AnyChatQueue
//
//  Created by bairuitech on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "BusinessListController.h"
#import "Business.h"
#import "QueueViewController.h"
#import "MBProgressHUD+JT.h"

#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"
#import "AnyChatObjectDefine.h"
#import "AnyChat_QueueModel.h"

@interface BusinessListController ()

@end

@implementation BusinessListController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.navigationItem.title = @"队列列表";
    
    // 添加退出按钮
    [self setupBackButton];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    self.navigationController.navigationBarHidden = NO;
    [self.navigationController.navigationBar setBackgroundImage:nil forBarMetrics:UIBarMetricsDefault];
    [self.navigationController.navigationBar setShadowImage:nil];

}

#pragma mark - Action
- (void)backAction:(UIControlEvents *)event {
    // 退出营业厅
    [[AnyChatQueueDataManager getInstance].queueModel leaveArea];
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - Table view data source
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.businesses.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 60;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *identifier = @"business";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:identifier];
    }
    Business *business = self.businesses[indexPath.row];
    cell.textLabel.text =  business.title;
    int queuePeopleCount = [[AnyChatQueueDataManager getInstance].queueModel getQueuelengthWithid:[NSString stringWithFormat:@"%d",business.businessId]];
    cell.detailTextLabel.text = [NSString stringWithFormat:@"有%d人在排队",queuePeopleCount];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [MBProgressHUD showMessage:@"正在连接中，请稍等..."];
    // 进队列
    Business *business = self.businesses[indexPath.row];
    
    [[AnyChatQueueDataManager getInstance].queueModel enterQueueWithid:[NSString stringWithFormat:@"%d",business.businessId]];
}

#pragma mark - Custom Method
// 退出按钮
- (void)setupBackButton {
    UIButton *backButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 17, 30)];
    [backButton setBackgroundImage:[UIImage imageNamed:@"nav_back"] forState:UIControlStateNormal];
    [backButton setBackgroundImage:[UIImage imageNamed:@"nav_back_hover"] forState:UIControlStateHighlighted];
    [backButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    backButton.titleLabel.font = [UIFont systemFontOfSize:13.0f];
    [backButton setContentHorizontalAlignment:UIControlContentHorizontalAlignmentLeft];
    [backButton setContentVerticalAlignment:UIControlContentVerticalAlignmentBottom];
    [backButton addTarget:self action:@selector(backAction:) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:backButton];
}

#pragma mark - Memory
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
