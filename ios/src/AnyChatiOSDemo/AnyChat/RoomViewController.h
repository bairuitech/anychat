//
//  RoomViewController.h
//  AnyChat
//
//  Created by bairuitech on 13-7-5.
//
//

#import <UIKit/UIKit.h>

@interface RoomViewController : UIViewController<UITableViewDelegate, UITableViewDataSource>{

    IBOutlet UITableView *onlineUserTable;
    NSMutableArray *onlineUserList;
}

@property (nonatomic, strong) IBOutlet UITableView *onlineUserTable;
@property (nonatomic, strong) NSMutableArray *onlineUserList;


-(void) RefreshRoomUserList;

- (IBAction) OnLeaveRoomBtnClicked:(id)sender;

@end

