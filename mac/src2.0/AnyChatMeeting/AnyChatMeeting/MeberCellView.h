

#import <Cocoa/Cocoa.h>
#import "User.h"
@class MeberCellView;
@protocol MeberCellViewDelegate<NSObject>
- (void)tableViewCell:(MeberCellView *)cell didClickCamera:(NSButton *)button;
- (void)tableViewCell:(MeberCellView *)cell didClickMic:(NSButton *)button;
- (void)tableViewCell:(MeberCellView *)cell didClickRemove:(NSButton *)button;
- (void)tableViewCell:(MeberCellView *)cell didClickMain:(NSButton *)button;
@end

@interface MeberCellView : NSTableCellView

@property (weak, nonatomic) id<MeberCellViewDelegate> delegate;

@property (weak) IBOutlet NSTextField *userNameTextField;

@property (weak) IBOutlet NSButton *cameraButton;
@property (weak) IBOutlet NSButton *micButton;
@property (weak) IBOutlet NSButton *removeButton;
@property (weak) IBOutlet NSButton *mainButton;

@property (strong, nonatomic) User *user;

- (void)updateUI;

@end
