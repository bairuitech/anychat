//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "SettingVC.h"

@interface SettingVC ()<UIAlertViewDelegate>
{
    BOOL _maybeChange; //是否修改了参数
}

@property (weak, nonatomic) IBOutlet UITableView    *theUserSettingTabelView;
@property (strong,nonatomic) UISwitch               *theP2PSwitch;
@property (strong,nonatomic) UISwitch               *theServerSwitch;
@property (strong,nonatomic) NSMutableDictionary    *theMainUserSettingMDict;
//user setting param - NSMutableDictionary
@property (strong,nonatomic) NSMutableDictionary    *theVideop2pMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoServerParamMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoSolutionMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoBitrateMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoFramerateMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoPresetMDict;
@property (strong,nonatomic) NSMutableDictionary    *theVideoQualityMDict;

@end

@implementation SettingVC

#pragma mark - Life cycle
- (void)viewDidLoad {
    [super viewDidLoad];
    
    _maybeChange = NO;
    self.title = @"视频参数设置";
    [self createObjPlistFileToDocumentsPath]; //创建文件夹
    [self readDataWithPList];//读取plist数据
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:YES];
    [self configParamData];//根据plist数据设置
    [self.theUserSettingTabelView reloadData];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)navLeftClick {
    if(_maybeChange) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"是否保存设置？" message:@"" delegate:self cancelButtonTitle:@"退出" otherButtonTitles:@"保存", nil];
        [alertView show];
    } else {
        [super navLeftClick];
    }
 
}

#pragma mark - AlertViewDelegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if(buttonIndex == 0) {
        _maybeChange = NO;
        [self.navigationController popViewControllerAnimated:YES];
    } else {
        [self saveBtn_OnClick];
    }
}

#pragma mark - Shared Instance
kGCD_SINGLETON_FOR_CLASS(SettingVC);

#pragma mark - Table view data source
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
        cell.textLabel.font = [UIFont systemFontOfSize:AdaptW(16)];
        cell.detailTextLabel.font = [UIFont systemFontOfSize:AdaptW(16)];
        cell.detailTextLabel.textColor = [UIColor colorWithRed:200/255.0 green:200/255.0 blue:200/255.0 alpha:1];
    }
    
    cell.detailTextLabel.text = @"";
    if (indexPath.section == 0) {
        cell.textLabel.text = @"优先P2P";
        cell.accessoryType = UITableViewCellAccessoryNone;
        
        self.theP2PSwitch = [[UISwitch alloc] initWithFrame:CGRectZero];
        [self.theP2PSwitch addTarget:self action:@selector(switchBtnStatus:) forControlEvents:UIControlEventValueChanged];
        self.theP2PSwitch.onTintColor = [UIColor colorWithRed:0 green:139 / 255.0 blue:227 / 255.0 alpha:1];
        self.theP2PSwitch.on = [self.theP2PNum boolValue];
        cell.accessoryView = self.theP2PSwitch;
    } else if(indexPath.section == 1) {
        cell.textLabel.text = @"使用服务器视频参数";
        cell.accessoryType = UITableViewCellAccessoryNone;
        
        self.theServerSwitch = [[UISwitch alloc] initWithFrame:CGRectZero];
        [self.theServerSwitch addTarget:self action:@selector(switchBtnStatus:) forControlEvents:UIControlEventValueChanged];
        self.theServerSwitch.onTintColor = [UIColor colorWithRed:0 green:139 / 255.0 blue:227 / 255.0 alpha:1];
        self.theServerSwitch.on = [self.theServerParamNum boolValue];
        
        cell.accessoryView = self.theServerSwitch;
    } else if(indexPath.section == 2) {
        cell.accessoryView = nil;
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        if (indexPath.row == 0) {
            cell.textLabel.text = @"视频分辨率";
            cell.detailTextLabel.text = self.theSolutionStr;
        } else if(indexPath.row == 1) {
            cell.textLabel.text = @"视频码率";
            cell.detailTextLabel.text = self.theBitrateStr;
        } else if(indexPath.row == 2) {
            cell.textLabel.text = @"视频帧率";
            cell.detailTextLabel.text = self.theFrameRateStr;
        } else if(indexPath.row == 3) {
            cell.textLabel.text = @"预设参数";
            cell.detailTextLabel.text = self.thePresetStr;
        } else if(indexPath.row == 4) {
            cell.textLabel.text = @"视频质量";
            cell.detailTextLabel.text = self.theQualityStr;
        }
    }
    
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {  // Return the number of rows in the section.
    if (section == 2) {
        return 5;
    }
    return 1;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 3;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    if (section == 0) {
        return @"网络参数设置";
    } else if (section == 1) {
        return @"视频参数控制";
    } else if (section == 2) {
        return @"本地视频参数设置";
    }
    return nil;
}

-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 30;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 63;
}

#pragma mark - Table view delegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    DetailVC *detailVC = [[DetailVC alloc] init];
    if (indexPath.section == 2) {
        if (indexPath.row == 0) {
            [detailVC setType:@"视频分辨率"];
        } else if (indexPath.row == 1) {
            [detailVC setType:@"视频码率"];
        } else if (indexPath.row == 2) {
            [detailVC setType:@"视频帧率"];
        } else if (indexPath.row == 3) {
            [detailVC setType:@"预设参数"];
        } else if (indexPath.row == 4) {
            [detailVC setType:@"视频质量"];
        }
        
        [self.navigationController pushViewController:detailVC animated:YES];
        _maybeChange = YES;
    }
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

#pragma mark - Instance Methed
- (NSString *)plistFileAtSandboxPathWithName:(NSString *)thePlistName {
    //Get plist Path
    NSArray *mainPathsArray = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    NSString *documentsPath = [mainPathsArray objectAtIndex:0];
    NSString *plistPath = [documentsPath stringByAppendingPathComponent:thePlistName];

    return plistPath;
}

- (void)createObjPlistFileToDocumentsPath {
    NSString *plistSandboxPath = [self plistFileAtSandboxPathWithName:@"UserVideoSettings.plist"];
    
    //plist isExist
    NSFileManager *theFM = [NSFileManager defaultManager];
    BOOL isExist =[theFM fileExistsAtPath:plistSandboxPath];
    
    NSString *plistObjectPath = [[NSBundle mainBundle] pathForResource:@"UserVideoSettings" ofType:@"plist"];
    if(!(isExist)) {
        BOOL createSuccess = [theFM copyItemAtPath:plistObjectPath toPath:plistSandboxPath error:nil];
        if (!(createSuccess)) {
            NSLog(@"\n create Plist File failed!");
        }
    }
}

- (NSMutableDictionary *)readPListToMDictionaryAtSandboxPList:(NSString *)thePListName {
    NSString *thePListPath = [self plistFileAtSandboxPathWithName:thePListName];
    NSMutableDictionary *theMDict = [NSMutableDictionary alloc];
    if (thePListPath) {
        theMDict = [theMDict initWithContentsOfFile:thePListPath];
    } else {
        theMDict = nil;
        NSLog(@"\n %@ is not in this.",thePListName);
    }
    
    return theMDict;
}

- (void)readDataWithPList {
    //read userData
    self.theMainUserSettingMDict = [self readPListToMDictionaryAtSandboxPList:@"UserVideoSettings.plist"];
    if (self.theMainUserSettingMDict != nil) {
        self.theVideop2pMDict = [self.theMainUserSettingMDict objectForKey:@"usep2p"];
        self.theVideoServerParamMDict = [self.theMainUserSettingMDict objectForKey:@"useserverparam"];
        self.theVideoSolutionMDict = [self.theMainUserSettingMDict objectForKey:@"videosolution"];
        self.theVideoBitrateMDict = [self.theMainUserSettingMDict objectForKey:@"videobitrate"];
        self.theVideoFramerateMDict = [self.theMainUserSettingMDict objectForKey:@"videoframerate"];
        self.theVideoPresetMDict = [self.theMainUserSettingMDict objectForKey:@"videopreset"];
        self.theVideoQualityMDict = [self.theMainUserSettingMDict objectForKey:@"videoquality"];
    }
}

- (void)configParamData {
    if(!_maybeChange) { //数据没变，则读取原数据
        self.theP2PNum = [self.theVideop2pMDict objectForKey:@"Values"];
        self.theServerParamNum = [self.theVideoServerParamMDict objectForKey:@"Values"];
        self.theSolutionStr = [self.theVideoSolutionMDict objectForKey:@"Titles"];
        self.theSolutionNum = [self.theVideoSolutionMDict objectForKey:@"Values"];
        self.theBitrateStr = [self.theVideoBitrateMDict objectForKey:@"Titles"];
        self.theBitrateNum = [self.theVideoBitrateMDict objectForKey:@"Values"];
        self.theFrameRateStr = [self.theVideoFramerateMDict objectForKey:@"Titles"];
        self.theFrameRateNum = [self.theVideoFramerateMDict objectForKey:@"Values"];
        self.thePresetStr = [self.theVideoPresetMDict objectForKey:@"Titles"];
        self.thePresetNum = [self.theVideoPresetMDict objectForKey:@"Values"];
        self.theQualityStr = [self.theVideoQualityMDict objectForKey:@"Titles"];
        self.theQualityNum = [self.theVideoQualityMDict objectForKey:@"Values"];
    } else {
        if (self.theP2PNum == nil) {
            self.theP2PNum = [self.theVideop2pMDict objectForKey:@"Values"];
        }
        
        if (self.theServerParamNum == nil) {
            self.theServerParamNum = [self.theVideoServerParamMDict objectForKey:@"Values"];
        }
        
        if (self.theSolutionNum == nil) {
            self.theSolutionStr = [self.theVideoSolutionMDict objectForKey:@"Titles"];
            self.theSolutionNum = [self.theVideoSolutionMDict objectForKey:@"Values"];
        }
        
        if (self.theBitrateNum == nil) {
            self.theBitrateStr = [self.theVideoBitrateMDict objectForKey:@"Titles"];
            self.theBitrateNum = [self.theVideoBitrateMDict objectForKey:@"Values"];
        }
        
        if (self.theFrameRateNum == nil) {
            self.theFrameRateStr = [self.theVideoFramerateMDict objectForKey:@"Titles"];
            self.theFrameRateNum = [self.theVideoFramerateMDict objectForKey:@"Values"];
        }
        
        if (self.thePresetNum == nil) {
            self.thePresetStr = [self.theVideoPresetMDict objectForKey:@"Titles"];
            self.thePresetNum = [self.theVideoPresetMDict objectForKey:@"Values"];
        }
        
        if (self.theQualityNum == nil) {
            self.theQualityStr = [self.theVideoQualityMDict objectForKey:@"Titles"];
            self.theQualityNum = [self.theVideoQualityMDict objectForKey:@"Values"];
        }
    }
}

- (IBAction)saveBtn_OnClick {
    if (self.theP2PNum && self.theServerParamNum && self.theSolutionNum && self.theBitrateNum && self.theFrameRateNum && self.thePresetNum && self.theQualityNum && self.theSolutionStr && self.theBitrateStr && self.theFrameRateStr && self.thePresetStr && self.theQualityStr) {
        //set Values in Dict
        [self.theVideop2pMDict setValue:self.theP2PNum forKey:@"Values"];
        [self.theVideoServerParamMDict setValue:self.theServerParamNum forKey:@"Values"];
        [self.theVideoSolutionMDict setValue:self.theSolutionNum forKey:@"Values"];
        [self.theVideoBitrateMDict setValue:self.theBitrateNum forKey:@"Values"];
        [self.theVideoFramerateMDict setValue:self.theFrameRateNum forKey:@"Values"];
        [self.theVideoPresetMDict setValue:self.thePresetNum forKey:@"Values"];
        [self.theVideoQualityMDict setValue:self.theQualityNum forKey:@"Values"];
        
        //set Titles in Dict
        [self.theVideoSolutionMDict setValue:self.theSolutionStr forKey:@"Titles"];
        [self.theVideoBitrateMDict setValue:self.theBitrateStr forKey:@"Titles"];
        [self.theVideoFramerateMDict setValue:self.theFrameRateStr forKey:@"Titles"];
        [self.theVideoPresetMDict setValue:self.thePresetStr forKey:@"Titles"];
        [self.theVideoQualityMDict setValue:self.theQualityStr forKey:@"Titles"];
        
        //set Dict in mainDict
        [self.theMainUserSettingMDict setValue:self.theVideop2pMDict forKey:@"usep2p"];
        [self.theMainUserSettingMDict setValue:self.theVideoServerParamMDict forKey:@"useserverparam"];
        [self.theMainUserSettingMDict setValue:self.theVideoSolutionMDict forKey:@"videosolution"];
        [self.theMainUserSettingMDict setValue:self.theVideoBitrateMDict forKey:@"videobitrate"];
        [self.theMainUserSettingMDict setValue:self.theVideoFramerateMDict forKey:@"videoframerate"];
        [self.theMainUserSettingMDict setValue:self.theVideoPresetMDict forKey:@"videopreset"];
        [self.theMainUserSettingMDict setValue:self.theVideoQualityMDict forKey:@"videoquality"];
        
        NSString *saveAtSandboxPath = [self plistFileAtSandboxPathWithName:@"UserVideoSettings.plist"];
        [self.theMainUserSettingMDict writeToFile:saveAtSandboxPath atomically:YES];
        
        [self.navigationController popViewControllerAnimated:YES];
        _maybeChange = NO;
    } else {
        UIAlertView *showInfoAlertView = [[UIAlertView alloc] initWithTitle:@"参数不能为空."
                                                                   message:@"Video Settings cannot be empty."
                                                                  delegate:self
                                                         cancelButtonTitle:nil
                                                         otherButtonTitles:@"确定",nil];
        [showInfoAlertView show];
    }
}

- (void)switchBtnStatus:(UISwitch*)theSwitchBtn {
    BOOL isButtonOn = [theSwitchBtn isOn];
    if (theSwitchBtn == self.theP2PSwitch) {
        if (isButtonOn) {
            BOOL s_isOn = YES;
            self.theP2PNum = [NSNumber numberWithBool:s_isOn];
        }else {
            BOOL s_isOff = NO;
            self.theP2PNum = [NSNumber numberWithBool:s_isOff];
        }
    }
    else if (theSwitchBtn == self.theServerSwitch) {
        if (isButtonOn) {
            BOOL s_isOn = YES;
            self.theServerParamNum = [NSNumber numberWithBool:s_isOn];
        } else {
            BOOL s_isOff = NO;
            self.theServerParamNum = [NSNumber numberWithBool:s_isOff];
        }
    }
    _maybeChange = YES;
}

- (BOOL)shouldAutorotate {
    return NO;
}

//Get the Values of the MutableDictionary
- (id)getValuesFromMDict:(NSMutableDictionary *)mainMDict firstMDictKey:(NSString *)firstKey secondValuesKey:(NSString *)secondKey {
    NSMutableDictionary *theMDict = [mainMDict objectForKey:firstKey];
    NSNumber *theValues = [theMDict objectForKey:secondKey];
    return theValues;
}


#pragma mark - User-defined video parameter Settings
// 更新用户自定义视频参数设置
- (void) updateUserVideoSettings {
    //read user data
    NSMutableDictionary *theMDict = [self readPListToMDictionaryAtSandboxPList:@"UserVideoSettings.plist"];
    
    BOOL bUseP2P = [[self getValuesFromMDict:theMDict
                               firstMDictKey:@"usep2p"
                             secondValuesKey:@"Values"] boolValue];
    BOOL bUseServerVideoParam = [[self getValuesFromMDict:theMDict
                                            firstMDictKey:@"useserverparam"
                                          secondValuesKey:@"Values"] boolValue];
    int iVideoSolution = [[self getValuesFromMDict:theMDict
                                     firstMDictKey:@"videosolution"
                                   secondValuesKey:@"Values"] intValue];
    int iVideoBitrate = [[self getValuesFromMDict:theMDict
                                    firstMDictKey:@"videobitrate"
                                  secondValuesKey:@"Values"] intValue];
    int iVideoFrameRate = [[self getValuesFromMDict:theMDict
                                      firstMDictKey:@"videoframerate"
                                    secondValuesKey:@"Values"] intValue];
    int iVideoPreset = [[self getValuesFromMDict:theMDict
                                   firstMDictKey:@"videopreset"
                                 secondValuesKey:@"Values"] intValue];
    int iVideoQuality = [[self getValuesFromMDict:theMDict
                                    firstMDictKey:@"videoquality"
                                  secondValuesKey:@"Values"] intValue];
    
    // P2P
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_NETWORK_P2PPOLITIC : (bUseP2P ? 1 : 0)];
    
    if(bUseServerVideoParam) {
        // 屏蔽本地参数，采用服务器视频参数设置
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_APPLYPARAM :0];
    } else {
        int iWidth, iHeight;
        switch (iVideoSolution) {
            case 0:     iWidth = 1280;  iHeight = 720;  break;
            case 1:     iWidth = 640;   iHeight = 480;  break;
            case 2:     iWidth = 480;   iHeight = 360;  break;
            case 3:     iWidth = 352;   iHeight = 288;  break;
            case 4:     iWidth = 192;   iHeight = 144;  break;
            default:    iWidth = 352;   iHeight = 288;  break;
        }
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_WIDTHCTRL :iWidth];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_HEIGHTCTRL :iHeight];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_BITRATECTRL :iVideoBitrate];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_FPSCTRL :iVideoFrameRate];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_PRESETCTRL :iVideoPreset];
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_QUALITYCTRL :iVideoQuality];
        
        // 采用本地视频参数设置，使参数设置生效
        [AnyChatPlatform SetSDKOptionInt:BRAC_SO_LOCALVIDEO_APPLYPARAM :1];
    }
}

@end
