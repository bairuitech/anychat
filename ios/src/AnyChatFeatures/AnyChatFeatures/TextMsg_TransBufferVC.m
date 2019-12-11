//
//  TextMsgVC.m
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "TextMsg_TransBufferVC.h"

@interface TextMsg_TransBufferVC ()
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *toolBarBottomConstr;

@property (weak, nonatomic) IBOutlet UITextField        *theTextMsgTextField;
@property (weak, nonatomic) IBOutlet UITableView        *theTextMsgTableView;
@property (weak, nonatomic) IBOutlet UIToolbar          *theToolbar;
@end

@implementation TextMsg_TransBufferVC




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
    
    
    self.theMsgMArray = [[NSMutableArray alloc] initWithCapacity:5];
    [self p_configNavItem];
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeConstraint exceptViews:nil];
    
   
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:YES];
    [self setUI];
    
    IQKeyboardManager *keyboardManager =  [IQKeyboardManager sharedManager];
    keyboardManager.enable = NO;
    [self theNotificationCenter];

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(void)viewDidDisappear:(BOOL)animated {
    
    [super viewDidDisappear:animated];
    
    IQKeyboardManager *keyboardManager =  [IQKeyboardManager sharedManager];
    keyboardManager.enable = YES;
    [self removeNotification];
}

- (void)p_configNavItem {
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(clearDatas_OnClick) forControlEvents:UIControlEventTouchUpInside];
    [button setImage:[UIImage imageNamed:@"icon_remove"] forState:UIControlStateNormal];
    [button sizeToFit];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithCustomView:button];
    self.navigationItem.rightBarButtonItem = rightItem;
}
#pragma mark - Shared Instance

kGCD_SINGLETON_FOR_CLASS(TextMsg_TransBufferVC);

#pragma mark ---- Instance Method （业务核心代码） -------

- (IBAction)theSendMsg_OnClick:(id)sender
{   //The string filter
    NSString *contentStr = [self.theTextMsgTextField.text stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    
    if ([contentStr isEqual: @""] || contentStr == nil)
    {
        UIAlertView *errorMsgAlert = [[UIAlertView alloc] initWithTitle:@"发送失败！"
                                                        message:@"发送的内容不能为空！"
                                                       delegate:nil
                                              cancelButtonTitle:@"确定"
                                              otherButtonTitles: nil];
        [errorMsgAlert show];
    }else
    {
        [self sendMassage:contentStr];
    }
    
    self.theTextMsgTextField.text = @"";
}

- (void)sendMassage:(NSString *)contentStr
{
    NSString *s_targetUserIDStr = [[NSString alloc] initWithFormat:@"%i",[AnyChatVC sharedAnyChatVC].theTargetUserID];
    NSString *s_targetUserNameStr = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    
    NSData* contentData = [contentStr dataUsingEncoding:NSUTF8StringEncoding];
    
    int isSuccess = 0;
    if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"文字聊天"])
    {   // 传送文本消息
        isSuccess = [AnyChatPlatform SendTextMessage:[s_targetUserIDStr intValue] :NO :contentStr];
        if (isSuccess == 0)
        {
            [self.theMsgMArray addObject:[NSDictionary dictionaryWithObjectsAndKeys:
                                          s_targetUserIDStr,@"targetUserIDStr",
                                          s_targetUserNameStr,@"targetUserNameStr",
                                          contentStr,@"contentStr",
                                          @"send",@"ACTStatus", nil]];
            [self TableViewReload];
        }
        else
        {
            [self NetworkAnomaliesAlert];
        }
    }
    else if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"透明通道"])
    {   // 透明通道传送缓冲区
        isSuccess = [AnyChatPlatform TransBuffer:[s_targetUserIDStr intValue] :contentData];
        if (isSuccess == 0)
        {
            [self.theMsgMArray addObject:[NSDictionary dictionaryWithObjectsAndKeys:
                                          s_targetUserIDStr,@"targetUserIDStr",
                                          s_targetUserNameStr,@"targetUserNameStr",
                                          contentStr,@"contentStr",
                                          @"send",@"ACTStatus", nil]];
            [self TableViewReload];
        }
        else
        {
            [self NetworkAnomaliesAlert];
        }
    }
}

- (void)NetworkAnomaliesAlert
{
    UIAlertView *failuresMsgAlert = [[UIAlertView alloc] initWithTitle:@"发送失败！"
                                                               message:@"网络出现异常,请重新登录再试!"
                                                              delegate:nil
                                                     cancelButtonTitle:@"确定"
                                                     otherButtonTitles: nil];
    [failuresMsgAlert show];
}

- (void)TableViewReload
{
    [self.theTextMsgTableView reloadData];
    [self.theTextMsgTableView scrollToRowAtIndexPath:[NSIndexPath indexPathForRow:[self.theMsgMArray count]-1 inSection:0]
                                    atScrollPosition: UITableViewScrollPositionBottom
                                            animated:YES];
}

- (void)navLeftClick
{
    [self clearDatas_OnClick];
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)clearDatas_OnClick
{
    [self.theMsgMArray removeAllObjects];
    [self.theTextMsgTableView reloadData];
}




#pragma mark - TableView DataSource

-(NSInteger) numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

-(NSInteger) tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.theMsgMArray.count;
}

-(UITableViewCell *) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *Cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (Cell == nil)
    {
        NSArray *nibs = [[NSBundle mainBundle] loadNibNamed:@"theMsgCell" owner:self options:nil];
        Cell = [nibs objectAtIndex:0];
        Cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    
    // Config
    UILabel *theTitleLabel = (UILabel *)[Cell.contentView viewWithTag:kTitleCell_LableTag];
    UILabel *theContentLabel = (UILabel *)[Cell.contentView viewWithTag:kContentCell_LableTag];
    theContentLabel.numberOfLines = 0;
    NSDictionary *textMsgDict = [self.theMsgMArray objectAtIndex:[indexPath row]];
    NSString *actionStatus = [textMsgDict objectForKey:@"ACTStatus"];
    
    // actionStatus
    if ([actionStatus isEqualToString:@"send"])
    {
        theTitleLabel.textColor = [UIColor blackColor];
        theContentLabel.textColor = [UIColor blackColor];
        
        // Send Content
        if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"文字聊天"])
        {
            theTitleLabel.text = [[NSString alloc] initWithFormat:@"我说："];
            theContentLabel.text = [textMsgDict objectForKey:@"contentStr"];
        }
        else if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"透明通道"])
        {
            theTitleLabel.text = [[NSString alloc] initWithFormat:@"我发送指令："];
            theContentLabel.text = [textMsgDict objectForKey:@"contentStr"];
        }
    }
    else if ([actionStatus isEqualToString:@"receive"])
    {
        theTitleLabel.textColor = [UIColor blueColor];
        theContentLabel.textColor = [UIColor blueColor];
        
        // Receive Content
        if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"文字聊天"])
        {
            theTitleLabel.text = [[NSString alloc] initWithFormat:@"“%@”说：",[textMsgDict objectForKey:@"targetUserNameStr"]];
            theContentLabel.text = [textMsgDict objectForKey:@"contentStr"];
        }
        else if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"透明通道"])
        {
            theTitleLabel.text = [[NSString alloc] initWithFormat:@"“%@”发送指令：",[textMsgDict objectForKey:@"targetUserNameStr"]];
            theContentLabel.text = [textMsgDict objectForKey:@"contentStr"];
        }
    }
    
    return Cell;
}


#pragma mark - TableView Delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    [self.theTextMsgTextField resignFirstResponder];
}

- (CGFloat)tableView:(UITableView *)tabelView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
        if (indexPath.row < self.theMsgMArray.count) {
            NSDictionary *textMsgDict = [self.theMsgMArray objectAtIndex:[indexPath row]];
    
            NSString *str =  [textMsgDict objectForKey:@"contentStr"];
    
            CGFloat width = SCREEN_WIDTH - 3;
    
            CGSize size =  [str boundingRectWithSize:CGSizeMake(width, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingUsesFontLeading  attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:18]} context:nil].size;
            return size.height + 24+10;// after createTextContainer, have value
    
    
        }
    return 60;
}


#pragma mark - TextField Delegate Methods

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    return YES;
}





#pragma mark - NSNotification Center

- (void)theNotificationCenter
{
    //Listening to the keyboard height transformation
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
}


- (void)removeNotification {
    
    [[NSNotificationCenter defaultCenter]removeObserver:self name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillHideNotification object:nil];
}


#pragma mark - Keyboard Responding events

- (void)keyboardWillShow:(NSNotification *)notification
{
    NSDictionary *userInfo = [notification userInfo];

    NSValue* aValue = [userInfo objectForKey:UIKeyboardFrameEndUserInfoKey];
    CGRect keyboardRect = [aValue CGRectValue];
    NSTimeInterval t = [userInfo[UIKeyboardAnimationDurationUserInfoKey] floatValue];


    [self autoMovekeyBoard:keyboardRect.size.height duration:t];
}


- (void)keyboardWillHide:(NSNotification *)notification
{
    NSDictionary* userInfo = [notification userInfo];
    NSTimeInterval t = [userInfo[UIKeyboardAnimationDurationUserInfoKey] floatValue];
    [self autoMovekeyBoard:0 duration:t];
}

-(void) autoMovekeyBoard: (float) high duration:(NSTimeInterval)duration
{
    
    self.toolBarBottomConstr.constant = -high;
    
    [UIView animateWithDuration:duration animations:^{
        [self.theToolbar layoutIfNeeded];
    }];
}


#pragma mark - Rotation

- (BOOL)shouldAutorotate
{
    return NO;
}


#pragma mark - UI Controls

- (void)setUI
{
    //Title
    NSString *targetUserName = [AnyChatVC sharedAnyChatVC].theTargetUserName;
    if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"文字聊天"])
    {
        self.title = [[NSString alloc] initWithFormat:@"与“%@”聊天中",targetUserName];
    }
    else if ([[AnyChatVC sharedAnyChatVC].theFeaturesName isEqualToString:@"透明通道"])
    {
        self.title = [[NSString alloc] initWithFormat:@"与“%@”发送指令中",targetUserName];
    }
    
    self.theTextMsgTextField.text = @"";
    [self.theTextMsgTableView reloadData];
    
    
    UIView *headerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, kSelfView_Width, 10.0f)];
    self.theTextMsgTableView.tableHeaderView = headerView;
}


@end
