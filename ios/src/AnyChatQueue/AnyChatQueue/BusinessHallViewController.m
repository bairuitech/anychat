//
//  BusinessHallViewController.m
//  AnyChatQueue
//
//  Created by tim.tan on 15/6/13.
//  Copyright (c) 2015年 tim.tan. All rights reserved.
//

#import "BusinessHallViewController.h"
#import "BusinessHallCell.h"
#import "BusinessListController.h"
#import "BusinessHall.h"
#import "MBProgressHUD+JT.h"
#import <AnyChatCoreSDK/AnyChatCoreSDK.h>
#import "AnyChat_QueueModel.h"

@interface BusinessHallViewController ()<UIActionSheetDelegate>
@end

@implementation BusinessHallViewController

static NSString * const reuseIdentifier = @"BusinessHall";

- (instancetype)init {
    UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
    CGFloat width = [[UIScreen mainScreen] bounds].size.width/2;
    layout.itemSize = CGSizeMake(width-10, 127);   //cell大小
    layout.minimumInteritemSpacing = 1;     //cell水平间距
    layout.minimumLineSpacing = 1;         //cell垂直间距
    layout.sectionInset = UIEdgeInsetsMake(layout.minimumLineSpacing, 0, 0, 0); //section内边距
    
    return [super initWithCollectionViewLayout:layout];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.navigationItem.title = @"营业厅列表";
    [self.navigationController setNavigationBarHidden:NO animated:YES];
    
    // 1.注册一个Collect的cell
    UINib *nib = [UINib nibWithNibName:@"BusinessHallCell" bundle:nil];
    [self.collectionView registerNib:nib forCellWithReuseIdentifier:reuseIdentifier];
    
    // 2.设置collectionView的背景色
    self.collectionView.backgroundColor = [UIColor whiteColor];
    
    // 添加退出按钮
    [self setupBackButton];
}

#pragma mark <UICollectionViewDataSource>
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.businessHallObjectArr.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    // 1.创建cell
    BusinessHallCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:reuseIdentifier forIndexPath:indexPath];
    // 2.传递模型数据
    cell.businessHall = self.businessHallObjectArr[indexPath.item];

    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    
    [MBProgressHUD showMessage:@"正在连接中，请稍等..."];
    
    BusinessHall *bHall = self.businessHallObjectArr[indexPath.item];
    // 进营业厅
    [[AnyChatQueueDataManager getInstance].queueModel enterAreaWithid:[NSString stringWithFormat:@"%d",bHall.hallId]];
    
}

#pragma mark - UIActionSheetDelegate
- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {
        // 注销系统
        [AnyChatPlatform Logout];
        [self.navigationController popToRootViewControllerAnimated:YES];
    }
}

#pragma mark - Custom Method
// 退出按钮
- (void)setupBackButton {
    UIButton *logoutButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 23, 30)];
    [logoutButton setBackgroundImage:[UIImage imageNamed:@"nav_out"] forState:UIControlStateNormal];
    [logoutButton setBackgroundImage:[UIImage imageNamed:@"nav_out_hover"] forState:UIControlStateHighlighted];
    [logoutButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    logoutButton.titleLabel.font = [UIFont systemFontOfSize:13.0f];
    [logoutButton setContentHorizontalAlignment:UIControlContentHorizontalAlignmentLeft];
    [logoutButton setContentVerticalAlignment:UIControlContentVerticalAlignmentBottom];
    [logoutButton addTarget:self action:@selector(backAction:) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:logoutButton];
}

#pragma mark - Action
- (void)backAction:(UIControlEvents *)event {
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"您确定退出排队系统吗？" delegate:self cancelButtonTitle:@"取消" destructiveButtonTitle:@"确定" otherButtonTitles:nil, nil];
    actionSheet.delegate = self;
    [actionSheet showInView:self.view];
}

#pragma mark - Memory
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
