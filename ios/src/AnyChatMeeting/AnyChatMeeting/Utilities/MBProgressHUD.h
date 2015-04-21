//
//  MBProgressHUD.h
//  Version 0.4
//

#import <UIKit/UIKit.h>

@protocol MBProgressHUDDelegate;

typedef enum {
    /** Progress is shown using an UIActivityIndicatorView. This is the default. */
    MBProgressHUDModeIndeterminate,
    /** Progress is shown using a MBRoundProgressView. */
	MBProgressHUDModeDeterminate,
	/** Shows a custom view */
	MBProgressHUDModeCustomView
} MBProgressHUDMode;

typedef enum {
    /** Opacity animation */
    MBProgressHUDAnimationFade,
    /** Opacity + scale animation */
    MBProgressHUDAnimationZoom
} MBProgressHUDAnimation;


@interface MBProgressHUD : UIView {
	
	MBProgressHUDMode mode;
    MBProgressHUDAnimation animationType;
	
	SEL methodForExecution;
	id targetForExecution;
	id objectForExecution;
	BOOL useAnimation;
	
    float yOffset;
    float xOffset;
	
	float width;
	float height;
	
	CGSize minSize;
	BOOL square;
	
	float margin;
	
	BOOL dimBackground;
	
	BOOL taskInProgress;
	float graceTime;
	float minShowTime;
	NSTimer *graceTimer;
	NSTimer *minShowTimer;
	NSDate *showStarted;
	
	UIView *indicator;
	UILabel *label;
	UILabel *detailsLabel;
	
	float progress;
	
#if __has_feature(objc_arc_weak)
	id<MBProgressHUDDelegate> __weak delegate;
#elif __has_feature(objc_arc)
	id<MBProgressHUDDelegate> __unsafe_unretained delegate;
#else
	id<MBProgressHUDDelegate> delegate;
#endif
    NSString *labelText;
	NSString *detailsLabelText;
	float opacity;
	UIFont *labelFont;
	UIFont *detailsLabelFont;
	
    BOOL isFinished;
	BOOL removeFromSuperViewOnHide;
	
	UIView *customView;
	
	CGAffineTransform rotationTransform;
}

+ (MBProgressHUD *)showHUDAddedTo:(UIView *)view animated:(BOOL)animated;

+ (BOOL)hideHUDForView:(UIView *)view animated:(BOOL)animated;

- (id)initWithWindow:(UIWindow *)window;

- (id)initWithView:(UIView *)view;

#if __has_feature(objc_arc)
@property (strong) UIView *customView;
#else
@property (retain) UIView *customView;
#endif

@property (assign) MBProgressHUDMode mode;

@property (assign) MBProgressHUDAnimation animationType;

#if __has_feature(objc_arc_weak)
@property (weak) id<MBProgressHUDDelegate> delegate;
#elif __has_feature(objc_arc)
@property (unsafe_unretained) id<MBProgressHUDDelegate> delegate;
#else
@property (assign) id<MBProgressHUDDelegate> delegate;
#endif

@property (copy) NSString *labelText;
@property (copy) NSString *detailsLabelText;
@property (assign) float opacity;
@property (assign) float xOffset;
@property (assign) float yOffset;
@property (assign) float margin;
@property (assign) BOOL dimBackground;
@property (assign) float graceTime;
@property (assign) float minShowTime;
@property (assign) BOOL taskInProgress;
@property (assign) BOOL removeFromSuperViewOnHide;

#if __has_feature(objc_arc)
@property (strong) UIFont* labelFont;
#else
@property (retain) UIFont* labelFont;
#endif

#if __has_feature(objc_arc)
@property (strong) UIFont* detailsLabelFont;
#else
@property (retain) UIFont* detailsLabelFont;
#endif

@property (assign) float progress;
@property (assign) CGSize minSize;
@property (assign, getter = isSquare) BOOL square;

- (void)show:(BOOL)animated;

- (void)hide:(BOOL)animated;

- (void)hide:(BOOL)animated afterDelay:(NSTimeInterval)delay;

- (void)showWhileExecuting:(SEL)method onTarget:(id)target withObject:(id)object animated:(BOOL)animated;

@end

@protocol MBProgressHUDDelegate <NSObject>

@optional

- (void)hudWasHidden:(MBProgressHUD *)hud;

- (void)hudWasHidden __attribute__ ((deprecated)); 

@end

@interface MBRoundProgressView : UIView {
@private
    float _progress;
}


@property (nonatomic, assign) float progress;

@end


