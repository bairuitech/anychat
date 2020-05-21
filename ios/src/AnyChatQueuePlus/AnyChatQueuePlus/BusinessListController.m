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
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>
#import "BusinessListClientCell.h"

@interface BusinessListController ()<UITableViewDataSource, UITableViewDelegate>
@property(nonatomic, strong)NSArray *businesses;
@end

@implementation BusinessListController

// 懒加载
- (NSArray *)businesses {
    if (_businesses == nil) {
        NSMutableArray *businessesObjArr = [NSMutableArray array];
        for (NSString *businessId in self.businessListIdArray) {
            //获取队列名称
            NSString *businessName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_QUEUE :[businessId intValue] :ANYCHAT_OBJECT_INFO_NAME];
            NSDictionary *dic = [[NSDictionary alloc] initWithObjectsAndKeys:businessName,@"title", businessId,@"id",nil];
            Business *business = [Business businessWithDic:dic];
            [businessesObjArr addObject:business];
        }
        _businesses = businessesObjArr;
    }
    
    return _businesses;
}

-(UITableView *)tableView {
    
    if(!_tableView) {
        
        UITableView *tableView = [[UITableView alloc] initWithFrame:self.view.bounds];
        tableView.dataSource = self;
        tableView.delegate = self;
        [tableView registerNib:[UINib nibWithNibName:@"BusinessListClientCell" bundle:nil] forCellReuseIdentifier:@"client"];
        tableView.tableFooterView = [UIView new];
        _tableView = tableView;
    }
    
    return _tableView;
}

- (void)viewDidLoad {
    [super viewDidLoad];

//    self.title = self.businessHallName;
    NSString *areaName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_AREA :(int)self.businessHallId :ANYCHAT_OBJECT_INFO_NAME];

    self.title = areaName;
    
    [self.view addSubview:self.tableView];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    
    [BusinessListController interfaceOrientation:UIInterfaceOrientationPortrait];
}

#pragma mark - Action
- (void)navLeftClick {
    // 退出营业厅
    [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AREA :self.businessHallId :ANYCHAT_AREA_CTRL_USERLEAVE :0 :0 :0 :0 :nil];
    [self.navigationController popViewControllerAnimated:YES];
}

#pragma mark - Table view data source
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.businesses.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 82;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    
    BusinessListClientCell *cell = [tableView dequeueReusableCellWithIdentifier:@"client"];
    Business *business = self.businesses[indexPath.row];
    //设置排队人数
    cell.queueNameLab.text =  business.title;
    int queueId = [self.businessListIdArray[indexPath.row] intValue];
    int queuePeopleCount = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :queueId :ANYCHAT_QUEUE_INFO_QUEUELENGTH];
    cell.countLab.text = [NSString stringWithFormat:@"当前队列有%d人在等待",queuePeopleCount];
    [cell setEnterQueueBlock:^{

        [MBProgressHUD showMessage:@"正在连接中，请稍等..."];
        [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_QUEUE :queueId :ANYCHAT_QUEUE_CTRL_USERENTER :0 :0 :0 :0 :nil];
    }];

    return cell;
    
}

#pragma mark - Memory
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

+ (void)interfaceOrientation:(UIInterfaceOrientation)orientation
{
    
    if ([[UIDevice currentDevice] respondsToSelector:@selector(setOrientation:)]) {
        SEL selector  = NSSelectorFromString(@"setOrientation:");
        NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:[UIDevice instanceMethodSignatureForSelector:selector]];
        [invocation setSelector:selector];
        [invocation setTarget:[UIDevice currentDevice]];
        int val = orientation;
        // 从2开始是因为0 1 两个参数已经被selector和target占用
        [invocation setArgument:&val atIndex:2];
        [invocation invoke];
    }
}
@end
