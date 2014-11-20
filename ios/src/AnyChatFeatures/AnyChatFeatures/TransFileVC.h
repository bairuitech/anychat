//
//  TransFileVC.h
//  AnyChatFeatures
//
//  Created by alexChen  .
//  Copyright (c) 2014年 GuangZhou BaiRui NetWork Technology Co.,Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AnyChatVC.h"
#import "MBProgressHUD.h"
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"

@interface TransFileVC : UIViewController<MBProgressHUDDelegate,UITableViewDelegate,UITableViewDataSource,NSCoding,UIAlertViewDelegate,UIImagePickerControllerDelegate,UINavigationControllerDelegate,UIActionSheetDelegate>
{
    MBProgressHUD   *HUD;
    UIActionSheet *myActionSheet;
    NSString* theImageFilePath;
}

@property (weak, nonatomic) IBOutlet UILabel            *theFileNameLab;
@property (weak, nonatomic) IBOutlet UIImageView        *theIconImageView;
@property (weak, nonatomic) IBOutlet UINavigationItem   *theTransFileNItem;
@property (weak, nonatomic) IBOutlet UITableView        *theTransFileTableView;
@property (weak, nonatomic) IBOutlet UIToolbar          *theToolbar;
@property (strong, nonatomic) NSMutableArray            *theTableViewDataMArray;
@property (strong, nonatomic) NSMutableDictionary       *theTableViewRowDataMDict;
@property int theTransFileTaskID;


kGCD_SINGLETON_FOR_HEADER(TransFileVC);


- (IBAction)theOpenAlbumBtn_OnClick;

- (IBAction)Leave_Onclick;

- (IBAction)theTransFileBtn_OnClick;

- (IBAction)clearDatas_OnClick;

- (void)TableViewReload;


@end
