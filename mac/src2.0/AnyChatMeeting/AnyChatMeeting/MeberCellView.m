

#import "MeberCellView.h"

@interface MeberCellView ()

@end
@implementation MeberCellView

-(void)awakeFromNib{


}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}

-(void)setUIAction
{
   
//    NSClickGestureRecognizer * clickCamera = [[NSClickGestureRecognizer alloc] initWithTarget:self action:@selector(cameraAction:)];
//    [self.cameraImageView addGestureRecognizer:clickCamera];
//
//    NSClickGestureRecognizer * clickMic = [[NSClickGestureRecognizer alloc] initWithTarget:self action:@selector(micAction:)];
//    [self.micImageView addGestureRecognizer:clickMic];
}

- (IBAction)cameraAction:(id)sender {
    if (self.delegate && [self.delegate respondsToSelector:@selector(tableViewCell:didClickCamera:)]) {
        self.user.isCloseCamera = !self.user.isCloseCamera;
        [self updateUI];
        
        [self.delegate tableViewCell:self didClickCamera:sender];
    }
}

- (IBAction)micAction:(id)sender {
    if (self.delegate && [self.delegate respondsToSelector:@selector(tableViewCell:didClickMic:)]) {
        self.user.isCloseMic = !self.user.isCloseMic;
        [self updateUI];
        
        [self.delegate tableViewCell:self didClickMic:sender];
    }
}

- (IBAction)removeAction:(id)sender {
    if (self.delegate && [self.delegate respondsToSelector:@selector(tableViewCell:didClickRemove:)]) {
        [self.delegate tableViewCell:self didClickRemove:sender];
    }
}

- (IBAction)mainAction:(id)sender {
    if (self.delegate && [self.delegate respondsToSelector:@selector(tableViewCell:didClickRemove:)]) {
        [self.delegate tableViewCell:self didClickMain:sender];
    }
}

//- (void)setMember:(MemberModel *)model{
//    self.userName.stringValue = model.identifier;
//    self.micIcon.hidden = !model.isOpenMic;
//    self.cameraIcon.hidden = !model.isOpenCamera;
//}

- (void)updateUI
{
    if (self.user.isCloseCamera) {
        [self.cameraButton setImage:[NSImage imageNamed:@"camera_false"]];
    } else {
        [self.cameraButton setImage:[NSImage imageNamed:@"camera_true"]];
    }
    
    if (self.user.isCloseMic) {
        [self.micButton setImage:[NSImage imageNamed:@"microphone_false"]];
    } else {
        [self.micButton setImage:[NSImage imageNamed:@"microphone_true"]];
    }
}

@end
