//
//  ACFeaturesListVC.m
//  AnyChatFeatures
//
//  Created by Bairui on 2019/6/10.
//  Copyright © 2019年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "ACFeaturesListVC.h"
#import "ACFeatureCollectionCell.h"
#import "ACNetworkQuaAlertView.h"
#import "SendDataVC.h"
#import "ReceiveDataVC.h"

@interface ACFeaturesListVC ()<UICollectionViewDelegate, UICollectionViewDataSource>
@property (weak, nonatomic) IBOutlet UICollectionView *collectionView;

@property (nonatomic, strong) NSMutableArray *imageArray;
@property (nonatomic, strong) NSArray *nameArray;
@end

@implementation ACFeaturesListVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    [self p_configDataSource];
    [self p_configCollectionView];
    [self p_configRightItem];
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
    self.title = @"功能列表";
}

-(void)viewWillAppear:(BOOL)animated {
    
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:NO];

}

#pragma mark - UICollectionViewDelegate and Datasource -
-(NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    
    return 9;
}

-(UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    ACFeatureCollectionCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"ACFeatureCollectionCell" forIndexPath:indexPath];
    
    [cell configCellByImage:[UIImage imageNamed:self.imageArray[indexPath.row]]
                       name:self.nameArray[indexPath.row]];
    
    return cell;
}


-(void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    
    
    if(indexPath.row == 8) {//网络状态
        
        [self p_showNetworkQuaAlertView];
    } else  {
        
        [self p_selectFeature:indexPath.row + 1 name:self.nameArray[indexPath.row]];
    }
    [collectionView deselectItemAtIndexPath:indexPath animated:YES];
}



#pragma mark - UI -

- (void)p_configCollectionView {
    
    CGFloat cellWid = 85;
    NSInteger count = 3;
    CGFloat collectionWid = [UIScreen mainScreen].bounds.size.width - AdaptW(30 * 2);
    CGFloat spacing = (collectionWid - count * cellWid) / (count - 1);
    
    UICollectionViewFlowLayout * layout = [[UICollectionViewFlowLayout alloc]init];
    layout.scrollDirection = UICollectionViewScrollDirectionVertical;
    layout.itemSize = CGSizeMake(cellWid, 90);
    layout.minimumLineSpacing = 40;
    layout.minimumInteritemSpacing = spacing;
    
    
    self.collectionView.collectionViewLayout = layout;
    self.collectionView.delegate = self;
    self.collectionView.dataSource = self;
    [self.collectionView registerNib:[UINib nibWithNibName:@"ACFeatureCollectionCell" bundle:nil] forCellWithReuseIdentifier:@"ACFeatureCollectionCell"];
}


- (void)p_configDataSource {
    
    self.nameArray = @[@"音视频交互",@"文字聊天",@"透明通道", @"文件传输",@"本地录像",@"服务器录像", @"视频抓拍", @"呼叫中心", @"网络质量评估",];
    
    self.imageArray = [NSMutableArray arrayWithCapacity:9];
    for (int index = 0; index < 9; index ++) {
        
        NSString *name = [NSString stringWithFormat:@"list_%d", index];
        [self.imageArray addObject:name];
    }
}

- (void)p_configRightItem {
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(navRightClick) forControlEvents:UIControlEventTouchUpInside];
    [button setImage:[UIImage imageNamed:@"icon_setting"] forState:UIControlStateNormal];
    [button sizeToFit];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = rightItem;
}

#pragma mark ----- 业务核心代码 ------

- (void)p_sharedFeaturesInfo:(NSString *)featuresName FeaturesNO:(int)featuresNO
{
    [AnyChatVC sharedAnyChatVC].theFeaturesName = featuresName;
    [AnyChatVC sharedAnyChatVC].theFeaturesNO = featuresNO;
}


-(void)p_selectFeature:(NSInteger)featureNo name:(NSString *)featureName {
    
    [self p_sharedFeaturesInfo:featureName FeaturesNO:(int)featureNo];
    [AnyChatPlatform EnterRoom:(int)featureNo : featureName];
    [self.navigationController pushViewController:[UserListVC new] animated:YES];
}




#pragma mark - AlertView method

//网络状态。
- (void)p_showNetworkQuaAlertView
{
    
    ACNetworkQuaAlertView  *alertView = [[ACNetworkQuaAlertView alloc] init];
    alertView.certainClick = ^(NSString * roomId){
        
        [self.view endEditing:YES];
        int roomNo = [roomId intValue];
        [self p_sharedFeaturesInfo:@"网络质量评估" FeaturesNO:roomNo];
        [AnyChatPlatform EnterRoom:roomNo :@""];
        
        if (alertView.quaType == ACNetworkQuaTypeSend)//发送方
        {
            [self.navigationController pushViewController:[SendDataVC new] animated:NO];
        } else //接收方
        {
            [self.navigationController pushViewController:[ReceiveDataVC new] animated:NO];
        }
    };
    [alertView show];
    alertView.textField.text = @"9";
}


#pragma mark - NavItemClick & Overwrite -

-(void)navLeftClick {
    
    [[AnyChatVC sharedAnyChatVC] OnLogout];
    [self.navigationController popToRootViewControllerAnimated:YES];
}


-(void)navRightClick {
    
    SettingVC *setVC = [SettingVC new];
    [setVC readDataWithPList];
    [self.navigationController pushViewController:setVC animated:YES];
}

-(BOOL)navBarTranslucent {
    
    return YES;
}

@end
