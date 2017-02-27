//
//  MZTimerLabel.m
//  Version 0.2
//

#import "MZTimerLabel.h"

#define kDefaultTimeFormat  @"HH:mm:ss"
#define kDefaultFireIntervalNormal  0.1
#define kDefaultFireIntervalHighUse  0.02

@interface MZTimerLabel()

    @property (strong) NSTimer *timer;
    -(void)setup;
    -(void)updateLabel:(NSTimer*)timer;

@end

#pragma mark - Initialize method

@implementation MZTimerLabel

-(id)init{
    self = [super init];
    if (self) {
        _timeLabel = self;
        _timerType = MZTimerLabelTypeStopWatch;
    }
    return self;
}

-(id)initWithTimerType:(MZTimerLabelType)theType{
    return [self initWithLabel:nil andTimerType:theType];
}

-(id)initWithLabel:(UILabel *)theLabel andTimerType:(MZTimerLabelType)theType
{
    self = [super init];
    
    if(self){
        _timeLabel = theLabel;
        _timerType = theType;
        [self setup];
    }
    return self;
}

-(id)initWithLabel:(UILabel*)theLabel{
    
    self = [super init];
    
    if(self){
        _timeLabel = theLabel;
        _timerType = MZTimerLabelTypeStopWatch;
        [self setup];
    }
    return self;
}

#pragma mark - Getter and Setter Method

-(void)setStopWatchTime:(NSTimeInterval)time{
    
    timeUserValue = (time < 0) ? 0 : time;
    if(timeUserValue > 0){
        startCountDate = [[NSDate date] dateByAddingTimeInterval:(timeUserValue<0)?0:-timeUserValue];
        [self start];
        [self updateLabel:nil];
        [self pause];
    }
}

-(void)setCountDownTime:(NSTimeInterval)time{
    
    timeUserValue = time;
    timeToCountOff = [date1970 dateByAddingTimeInterval:time];
    [self updateLabel:nil];
}

-(void)setTimeFormat:(NSString *)timeFormat{
    
    _timeFormat = timeFormat;
    if ([_timeFormat length] != 0) {
        _timeFormat = timeFormat;
    }
    [self updateLabel:nil];
}

#pragma mark - Timer Control Method


-(void)start{
    
    [self setup];
    if(_timer == nil){
        
        if ([_timeFormat rangeOfString:@"SS"].location != NSNotFound) {
            _timer = [NSTimer scheduledTimerWithTimeInterval:kDefaultFireIntervalHighUse target:self selector:@selector(updateLabel:) userInfo:nil repeats:YES];
        }else{
            _timer = [NSTimer scheduledTimerWithTimeInterval:kDefaultFireIntervalNormal target:self selector:@selector(updateLabel:) userInfo:nil repeats:YES];
        }
        [[NSRunLoop currentRunLoop] addTimer:_timer forMode:NSRunLoopCommonModes];
        
        if(startCountDate == nil){
            startCountDate = [NSDate date];
            
            if (_timerType == MZTimerLabelTypeStopWatch && timeUserValue > 0) {
                startCountDate = [startCountDate dateByAddingTimeInterval:(timeUserValue<0)?0:-timeUserValue];
            }
        }
        if(pausedTime != nil){
            NSTimeInterval countedTime = [pausedTime timeIntervalSinceDate:startCountDate];
            startCountDate = [[NSDate date] dateByAddingTimeInterval:-countedTime];
            pausedTime = nil;
        }
        
        _counting = YES;
        [_timer fire];
        
    }
}

#if NS_BLOCKS_AVAILABLE
-(void)startWithEndingBlock:(void(^)(NSTimeInterval))end{
    [self start];
    endedBlock = end;
}
#endif
    
-(void)pause{
    [_timer invalidate];
    _timer = nil;
    _counting = NO;
    pausedTime = [NSDate date];
}

-(void)reset{
    
    pausedTime = nil;
    if(_timerType == MZTimerLabelTypeStopWatch) timeUserValue = 0;
    
    if(_counting){
        startCountDate = [NSDate date];
    }else{
        startCountDate = nil;
    }

    [self updateLabel:nil];
}


#pragma mark - Private method

-(void)setup{
    
    if ([_timeFormat length] == 0) {
        _timeFormat = kDefaultTimeFormat;
    }
    
    if(_timeLabel == nil){
        _timeLabel = self;
    }
    
    date1970 = [NSDate dateWithTimeIntervalSince1970:0];
    _timeLabel.adjustsFontSizeToFitWidth = YES;
    
    [self updateLabel:nil];
}


-(void)updateLabel:(NSTimer*)timer{
    
    NSTimeInterval timeDiff = [[[NSDate alloc] init] timeIntervalSinceDate:startCountDate];
//    NSDate *timeToShow = [NSDate date];
    NSDate *timeToShow;
    
    if(_timerType == MZTimerLabelTypeStopWatch){
        
        if (_counting) {
            timeToShow = [date1970 dateByAddingTimeInterval:timeDiff];
        }else{
            timeToShow = [date1970 dateByAddingTimeInterval:(!startCountDate)?0:timeDiff];
        }
        
        if([_delegate respondsToSelector:@selector(timerLabel:countingTo:timertype:)]){
            [_delegate timerLabel:self countingTo:timeDiff timertype:_timerType];
        }
    
    }else{
        
        //timer now
        
        if (_counting) {
            
            if([_delegate respondsToSelector:@selector(timerLabel:countingTo:timertype:)]){
                NSTimeInterval timeLeft = timeUserValue - timeDiff;
                [_delegate timerLabel:self countingTo:timeLeft timertype:_timerType];
            }
                        
            if(abs(timeDiff) >= timeUserValue){
                [self pause];
                timeToShow = [date1970 dateByAddingTimeInterval:0];
                pausedTime = nil;
                startCountDate = nil;
                
                if([_delegate respondsToSelector:@selector(timerLabel:finshedCountDownTimerWithTime:)]){
                    [_delegate timerLabel:self finshedCountDownTimerWithTime:timeUserValue];
                }
                
#if NS_BLOCKS_AVAILABLE
                if(endedBlock != nil){
                    endedBlock(timeUserValue);
                }
#endif
                if(_resetTimerAfterFinish){
                    [self reset];
                    return;
                }
                
            }else{
                timeToShow = [timeToCountOff dateByAddingTimeInterval:(timeDiff*-1)];
            }
            
        }else{
            timeToShow = timeToCountOff;
        }
    }
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:_timeFormat];
    [dateFormatter setTimeZone:[NSTimeZone timeZoneWithName:@"GMT"]];
    NSString *strDate = [dateFormatter stringFromDate:timeToShow];
    _timeLabel.text = strDate;
    
}

@end
