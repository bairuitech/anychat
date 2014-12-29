//
//  RoomViewController.m
//  AnyChat
//
//  Created by bairuitech on 13-7-5.
//
//

#import "RoomViewController.h"
#import "AnyChatAppDelegate.h"
#import "../../sdk/include/AnyChatPlatform.h"


@interface RoomViewController ()

@end

@implementation RoomViewController

@synthesize onlineUserTable;
@synthesize onlineUserList;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    NSMutableArray *userlist = [AnyChatPlatform GetOnlineUser];
    return userlist.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if(cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    
    onlineUserList = [[NSMutableArray alloc] initWithArray:[AnyChatPlatform GetOnlineUser]];
    
    NSUInteger row = [indexPath row];
    
    NSString* username = [AnyChatPlatform GetUserName:[[onlineUserList objectAtIndex:row] intValue]];
    cell.textLabel.text = [NSString stringWithFormat:@"%@(%i)", username, [[onlineUserList objectAtIndex:row] intValue]];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int userid = [[self.onlineUserList objectAtIndex:[indexPath row]] intValue];
    
    [[AnyChatAppDelegate GetApp].viewController showVideoChatView:userid];
}

-(void) RefreshRoomUserList
{
    [self.onlineUserTable reloadData];
}

- (IBAction) OnLeaveRoomBtnClicked:(id)sender
{
    [AnyChatPlatform LeaveRoom:-1];
    [[AnyChatAppDelegate GetApp].viewController showHallView];
}

@end
