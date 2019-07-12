//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import "DetailVC.h"

@interface DetailVC ()

@end

@implementation DetailVC


#pragma mark -
#pragma mark - Life cycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self readDataWithPList];
    self.title = self.theNavTitle;
    self.theDetailSettingTableView.tableFooterView = [UIView new];
    [self.view adaptScreenWidthWithType:AdaptScreenWidthTypeAll exceptViews:nil];
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
#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.theTitlesParamMArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier];
        cell.textLabel.font = [UIFont boldSystemFontOfSize:AdaptW(16)];
        cell.detailTextLabel.font = cell.textLabel.font;
        
    }
    
    cell.textLabel.text = [self.theTitlesParamMArray objectAtIndex:[indexPath row]];
    cell.detailTextLabel.text = [[self.theValuesParamMArray objectAtIndex:[indexPath row]] stringValue];
    
    return cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *selectTitlesStr = [self.theTitlesParamMArray objectAtIndex:[indexPath row]];
    int selectValuesInt = [[self.theValuesParamMArray objectAtIndex:[indexPath row]] intValue];
    NSNumber *selectValuesNum = [NSNumber numberWithInt:selectValuesInt];
    
    if ([self.theNavTitle isEqualToString:@"视频分辨率"])
    {
        [SettingVC sharedSettingVC].theSolutionStr = selectTitlesStr;
        [SettingVC sharedSettingVC].theSolutionNum = selectValuesNum;
    }
    else if([self.theNavTitle isEqualToString:@"视频码率"])
    {
        [SettingVC sharedSettingVC].theBitrateStr = selectTitlesStr;
        [SettingVC sharedSettingVC].theBitrateNum = selectValuesNum;
    }
    else if([self.theNavTitle isEqualToString:@"视频帧率"])
    {
        [SettingVC sharedSettingVC].theFrameRateStr = selectTitlesStr;
        [SettingVC sharedSettingVC].theFrameRateNum = selectValuesNum;
    }
    else if([self.theNavTitle isEqualToString:@"预设参数"])
    {
        [SettingVC sharedSettingVC].thePresetStr = selectTitlesStr;
        [SettingVC sharedSettingVC].thePresetNum = selectValuesNum;
    }
    else if([self.theNavTitle isEqualToString:@"视频质量"])
    {
        [SettingVC sharedSettingVC].theQualityStr = selectTitlesStr;
        [SettingVC sharedSettingVC].theQualityNum = selectValuesNum;
    }
    
    [self.navigationController popViewControllerAnimated:YES];
    
}


#pragma mark -
#pragma mark - Instance Methed

- (NSMutableDictionary *)readPListToMDictionaryWithPListName:(NSString *)thePListName
{
    NSString *thePListPath = [[NSBundle mainBundle] pathForResource:thePListName ofType:@"plist"];
    NSMutableDictionary *theMDict = [NSMutableDictionary alloc];
    if (thePListPath)
    {
        theMDict = [theMDict initWithContentsOfFile:thePListPath];
    }
    else
    {
        theMDict = nil;
        NSLog(@"%@.plist is not in this.",thePListName);
    }
    
    return theMDict;
}

- (void)readDataWithPList
{
    //read Main Setting PList
    self.theMainSettingMDict = [self readPListToMDictionaryWithPListName:@"VideoSettings"];
    
    if ([self.theNavTitle isEqualToString:@"视频分辨率"])
    {
        self.theTitlesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videosolution"
                                            secondMArrayKey:@"Titles"];
        self.theValuesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videosolution"
                                            secondMArrayKey:@"Values"];
    }
    else if ([self.theNavTitle isEqualToString:@"视频码率"])
    {
        self.theTitlesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videobitrate"
                                            secondMArrayKey:@"Titles"];
        self.theValuesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videobitrate"
                                            secondMArrayKey:@"Values"];
    }
    else if ([self.theNavTitle isEqualToString:@"视频帧率"])
    {
        self.theTitlesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videoframerate"
                                            secondMArrayKey:@"Titles"];
        self.theValuesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videoframerate"
                                            secondMArrayKey:@"Values"];
    }
    else if ([self.theNavTitle isEqualToString:@"预设参数"])
    {
        self.theTitlesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videopreset"
                                            secondMArrayKey:@"Titles"];
        self.theValuesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videopreset"
                                            secondMArrayKey:@"Values"];
    }
    else if ([self.theNavTitle isEqualToString:@"视频质量"])
    {
        self.theTitlesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videoquality"
                                            secondMArrayKey:@"Titles"];
        self.theValuesParamMArray = [self getArrayFromMDict:self.theMainSettingMDict
                                              firstMDictKey:@"videoquality"
                                            secondMArrayKey:@"Values"];
    }
}

//Get the Array of the MutableDictionary
- (NSMutableArray *)getArrayFromMDict:(NSMutableDictionary *)mainMDict firstMDictKey:(NSString *)firstKey secondMArrayKey:(NSString *)secondKey
{
    NSMutableDictionary *s_theMDict = [mainMDict objectForKey:firstKey];
    NSMutableArray *s_theMArray = [s_theMDict objectForKey:secondKey];
    
    return s_theMArray;
}


- (void)setType:(NSString *)theTypeName
{
    self.theNavTitle = theTypeName;
}




- (BOOL)shouldAutorotate
{
    return NO;
}


@end
