//
//  BRFACEX_SettingViewController.m
//  AnyChatInterviewIphone
//
//  Created by bairuitech on 2017/4/19.
//  Copyright © 2017年 anychat. All rights reserved.
//

#import "BRFACEX_SettingViewController.h"
#import "SettingCell.h"
#import "MBProgressHUD+JT.h"
#define SCREEN_WIDTH ([[UIScreen mainScreen] bounds].size.width)
#define SCREEN_HEIGHT ([[UIScreen mainScreen] bounds].size.height)
#define LineColor [UIColor colorWithRed:240.0/255.0 green:240.0/255.0 blue:240.0/255.0 alpha:1]

@interface BRFACEX_SettingViewController ()<UITableViewDelegate,UITableViewDataSource,UITextFieldDelegate>
@property (nonatomic, strong) UITableView *tableview;
@property (copy, nonatomic) NSString *anyChatIP;
@property (copy, nonatomic) NSString *anyChatPort;

@property (copy, nonatomic) NSString *appid;
@end

@implementation BRFACEX_SettingViewController
{
  
    NSMutableArray *list;
    NSArray *texts;

}
- (void)viewWillAppear:(BOOL)animated{
    
    [super viewWillAppear:animated];
}

- (void)viewDidDisappear:(BOOL)animated{
    
    [super viewDidDisappear:animated];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupUI];
    [self loadUrls];
}

- (void)setupUI {

    
    self.tableview = [UITableView new];
    self.tableview.frame = self.view.bounds;
    [self.view addSubview:self.tableview];
    self.tableview.showsVerticalScrollIndicator = NO;
    self.tableview.delegate = self;
    self.tableview.backgroundColor = LineColor;
    self.tableview.dataSource = self;
    self.tableview.clipsToBounds = NO;
    UINib *nib = [UINib nibWithNibName:@"SettingCell" bundle:nil];
    [self.tableview registerNib:nib forCellReuseIdentifier:@"tf"];
    UIView *footView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, SCREEN_WIDTH, 120)];
    [self.tableview setTableFooterView:footView];
    
    
    UIButton *clearButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [footView addSubview:clearButton];
    clearButton.backgroundColor = [UIColor colorWithRed:3/255.0 green:139/255.0 blue:227/255.0 alpha:1];
    [clearButton setTitle:@"清空" forState:UIControlStateNormal];
    [clearButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    clearButton.titleLabel.font = [UIFont systemFontOfSize:13];
//    [clearButton cornerRadius:3];
    clearButton.layer.masksToBounds = YES;
    clearButton.layer.cornerRadius = 5;
    clearButton.frame = CGRectMake(50, 20, 110, 40);
    [clearButton addTarget:self action:@selector(clear) forControlEvents:UIControlEventTouchUpInside];
    
    
    UIButton *doneButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [footView addSubview:doneButton];
    doneButton.backgroundColor = [UIColor colorWithRed:3/255.0 green:139/255.0 blue:227/255.0 alpha:1];;
    [doneButton setTitle:@"完成" forState:UIControlStateNormal];
    [doneButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    doneButton.titleLabel.font = [UIFont systemFontOfSize:13];
    doneButton.frame = CGRectMake(180, 20, 110, 40);
    doneButton.layer.masksToBounds = YES;
    doneButton.layer.cornerRadius = 5;
    [doneButton addTarget:self action:@selector(done) forControlEvents:UIControlEventTouchUpInside];
    
    
    
    texts = @[@"请输入IP地址",@"请输入端口号"];
    
    
    self.title  = @"设置";
}

#pragma mark action
- (void)loadUrls{
    
   
    self.anyChatIP = [[NSUserDefaults standardUserDefaults]objectForKey:@"AnyChatSerVer"];
    if (self.anyChatIP.length == 0) {
        
        self.anyChatIP = kAnyChatIP;
    }
    
    self.anyChatPort = [[NSUserDefaults standardUserDefaults]objectForKey:@"AnyChatPort"];
    if (self.anyChatPort.length == 0) {
        
        self.anyChatPort = kAnyChatPort;
    }
    
    self.appid = [[NSUserDefaults standardUserDefaults]objectForKey:@"AnyChatAppId"];
    if (self.appid.length == 0 && [self.anyChatIP isEqualToString:kAnyChatIP]) {
        self.appid = kAnyChatAppId;
    }
    [self.tableview reloadData];

    
}
#pragma mark - UITextField代理

- (void)textFieldDidEndEditing:(UITextField *)textField {
    if (textField.tag == 0) {
        //anychatIP
        self.anyChatIP = textField.text;
    } else if (textField.tag == 1) {
        //anychatPort
        self.anyChatPort = textField.text;
    }else if (textField.tag == 4) {
        //appID
        self.appid = textField.text;
    }
}
- (void)clear{
    
    
    self.anyChatIP = nil;
    self.anyChatPort = nil;
    self.appid = nil;
    [self.tableview reloadData];
}


- (void)done{
   
    [self.view endEditing:YES];
   
    if (self.anyChatIP.length < 1) {

        [MBProgressHUD showError:@"请输入anychat IP地址" toView:self.view];
        return;
    }
    if (self.anyChatPort.length < 1) {
        
        [MBProgressHUD showError:@"请输入anychat 端口地址" toView:self.view];
        return;
    }

    [MBProgressHUD showMessage:@""];
    [[NSUserDefaults standardUserDefaults]setObject:self.anyChatIP forKey:@"AnyChatSerVer"];
    [[NSUserDefaults standardUserDefaults]setObject:self.anyChatPort forKey:@"AnyChatPort"];
    [[NSUserDefaults standardUserDefaults]setObject:self.appid forKey:@"AnyChatAppId"];
    [[NSUserDefaults standardUserDefaults]synchronize];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [MBProgressHUD hideHUD];
        [MBProgressHUD showSuccess:@"设置成功"];
        [self.navigationController popViewControllerAnimated:YES];
    });
    
}


#pragma mark UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
 
    return 2;
}
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    
    if (section ==1) {
        
        return 1;
    }
    return 2;
}
- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section{
    
    UILabel *lab = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, SCREEN_WIDTH, 50)];
    lab.backgroundColor = LineColor;
    lab.font = [UIFont systemFontOfSize:15];
    if (section ==0) {
        
        lab.text = [NSString stringWithFormat:@" %@AnyChat服务器",@""];
    }
    else{
        
        lab.text = [NSString stringWithFormat:@" %@应用ID",@""];
    }
    return lab;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section{
    
    return 50;
}
#pragma mark - UISCrollView代理
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    [self.view endEditing:YES];
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    
    SettingCell *cell = [tableView dequeueReusableCellWithIdentifier:@"tf"];
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.textf.delegate = self;
    if (indexPath.section == 0) {
        if (indexPath.row == 0) {
            cell.textf.tag = 0;
            cell.textf.text = self.anyChatIP;
        }else if (indexPath.row == 1) {
            cell.textf.tag = 1;
        cell.textf.text = self.anyChatPort;
        }
    }else if (indexPath.section == 1) {
        if (indexPath.row == 0) {
            cell.textf.tag = 4;
            cell.textf.text = self.appid;
        }
    }
    
    if (indexPath.section == 1) {
        
        cell.textf.placeholder = @"请输入应用ID";
    }else{
        
        cell.textf.placeholder = texts[indexPath.row];
    }
    return cell;
}


#pragma mark UITableViewDelegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 50;
}

@end
