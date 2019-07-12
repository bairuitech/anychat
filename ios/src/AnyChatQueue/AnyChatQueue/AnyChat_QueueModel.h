//
//  AnyChat_QueueModel.h
//  AnyChatQueue
//
//  Created by Mac on 2019/6/19.
//  Copyright © 2019 tim.tan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AnyChatPlatform.h"
#import "AnyChatDefine.h"
#import "AnyChatErrorCode.h"
#import "AnyChatObjectDefine.h"
#import "AnyChatResult.h"

NS_ASSUME_NONNULL_BEGIN

/**
 角色
 */
typedef NS_ENUM(NSInteger, BRAC_QueueRole){
    /**
     *  客户
     */
    BRAC_QUEUE_OPT_ROLE_CLIENT  = 1,
    
    /**
     *  坐席
     */
    BRAC_QUEUE_OPT_ROLE_AGENT   = 2,
    
};

typedef NS_ENUM(NSInteger, BRAC_AgentServiceCtrlCode){
    /**
     *  示闲
     */
    BRAC_AGENT_SERVICE_WAITTING        = 0,
    /**
     *  结束服务
     */
    BRAC_AGENT_SERVICE_FINISHSERVICE   = 1,
    /**
     *  示忙
     */
    BRAC_AGENT_SERVICE_PAUSED          = 2,
    /**
     * 转移下一个坐席服务
     */
    BRAC_AGENT_SERVICE_FINISHSERVICE_TIMEOUT = 3,
    
};



/**
 坐席状态变化回调
 
 @param data  status 坐席状态  (0 关闭，不对外提供服务,  1 等待中，可随时接受用户服务,  2 工作中，正在为用户服务,   3 暂停服务,  10 离线)
 */
typedef void (^AgentStatusChangedCallback)(NSDictionary *data);

/**
 坐席服务通知(有人排队)
 
 @param data agentId 坐席ID
 customerId 客户ID
 queueId 队列ID
 */
typedef void (^ServiceNotifyCallback)(NSDictionary *data);

@interface AnyChat_AgentObserver : NSObject

@property (nonatomic, copy) AgentStatusChangedCallback agentStatusChangedBlock;

@property (nonatomic, copy) ServiceNotifyCallback serviceNotifyBlock;

@end

@protocol AnyChat_QueueModelDelegate <NSObject>
@optional
- (void)onAreasDataFinish:(NSArray *)businessHallDicArr;
- (void)onEnterAreaResult:(AnyChatResult *)result data:(NSDictionary *)data;
- (void)onEnterQueueResult:(AnyChatResult *)result data:(NSDictionary *)data;

/**
 队列变化回调
 
 @param data data userNumInQueue 当前队列总人数
 currentPos 当前排队位置
 waitingTime 排队时长
 */
- (void)onProcessChanged:(NSDictionary *)data;

/**
 坐席已经准备好，由客户端发起呼叫
 
 @param data agentId 坐席ID
 customerId 客户ID
 queueId 队列ID
 */
- (void)onServiceNotify:(NSDictionary *)data;

@end

@interface AnyChat_QueueModel : NSObject<AnyChatObjectEventDelegate>

@property (nonatomic, weak) id<AnyChat_QueueModelDelegate> delegate;
@property (nonatomic, assign, readonly) int selfUserId;

- (instancetype)initWithRole:(BRAC_QueueRole)role priority:(NSString *)priority autoRoute:(BOOL)autoRoute;

- (void)getAreas:(int)selfUserId;

- (void)enterAreaWithid:(NSString *)areaId;

- (void)enterQueueWithid:(NSString *)queueId;

- (void)cancelQueuing;

- (void)leaveArea;


- (int)getQueuelengthWithid:(NSString *)queueId;
- (int)getQueueIndexWithid:(NSString *)queueId;
- (int)getQueueTimeWithid:(NSString *)queueId;


//坐席
@property (nonatomic, strong) AnyChat_AgentObserver *agentObserver;
- (void)agentServiceCtrlWithCtrlCode:(BRAC_AgentServiceCtrlCode)code;


@end

@interface AnyChatQueueDataManager : NSObject

/**
 *  单例方法
 *
 *  @return 实例对象
 */
+ (AnyChatQueueDataManager*)getInstance;

@property (nonatomic, strong) AnyChat_QueueModel *queueModel;

@property (assign, nonatomic) int remoteUserId;                 //坐席客服id
@property (assign, nonatomic) int customerId;                   //客户id

@end

NS_ASSUME_NONNULL_END
