//
//  MZTimerLabel.h
//  Version 0.2
//

#import <UIKit/UIKit.h>

typedef enum{
    MZTimerLabelTypeStopWatch,
    MZTimerLabelTypeTimer
}MZTimerLabelType;
 
@class MZTimerLabel;
@protocol MZTimerLabelDelegate <NSObject>
@optional
-(void)timerLabel:(MZTimerLabel*)timerLabel finshedCountDownTimerWithTime:(NSTimeInterval)countTime;
-(void)timerLabel:(MZTimerLabel*)timerlabel countingTo:(NSTimeInterval)time timertype:(MZTimerLabelType)timerType;
@end

@interface MZTimerLabel : UILabel{
    
#if NS_BLOCKS_AVAILABLE
    void (^endedBlock)(NSTimeInterval);
#endif
    
    NSTimeInterval timeUserValue;
    
    NSDate *startCountDate;
    NSDate *pausedTime;
    
    NSDate *date1970;
    NSDate *timeToCountOff;
}

@property (strong) id<MZTimerLabelDelegate> delegate;
@property (nonatomic,strong) NSString *timeFormat;
@property (strong) UILabel *timeLabel;
@property (assign) MZTimerLabelType timerType;
@property (assign,readonly) BOOL counting;
@property (assign) BOOL resetTimerAfterFinish;

-(id)initWithTimerType:(MZTimerLabelType)theType;
-(id)initWithLabel:(UILabel*)theLabel andTimerType:(MZTimerLabelType)theType;
-(id)initWithLabel:(UILabel*)theLabel;

-(void)start;
#if NS_BLOCKS_AVAILABLE
-(void)startWithEndingBlock:(void(^)(NSTimeInterval countTime))end;
#endif
-(void)pause;
-(void)reset;

-(void)setCountDownTime:(NSTimeInterval)time;
-(void)setStopWatchTime:(NSTimeInterval)time;


@end


