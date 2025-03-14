//
//  AnyChat_QueueModel.m
//  AnyChatQueue
//
//  Created by Mac on 2019/6/19.
//  Copyright © 2019 tim.tan. All rights reserved.
//

#import "AnyChat_QueueModel.h"
#import "MBProgressHUD+JT.h"

@implementation AnyChat_AgentObserver

@end

@interface AnyChat_QueueModel()
@property(nonatomic, strong)NSMutableArray *businessHallDicArr;     //营业厅字典数组

@property (nonatomic, assign) int queueId;
@property (nonatomic, assign) int areaId;
@property (nonatomic, assign) int agenId;

@property (nonatomic, assign) int selfUserId;                         //自己的用户id
/**
 角色
 */
@property (nonatomic, assign) BRAC_QueueRole role;
/**
 优先级
 */
@property (nonatomic, copy) NSString *priority;


/**
 业务属性，可以根据业务需求传入JSON对象
 */
@property (nonatomic, copy) NSString *attribute;

/**
 主动路由
 */
@property (nonatomic, assign) BOOL autoRoute;



@end

@implementation AnyChat_QueueModel

- (instancetype)initWithRole:(BRAC_QueueRole)role priority:(NSString *)priority autoRoute:(BOOL)autoRoute
{
    if (self = [super init]) {
        self.role = role;
        self.priority = priority;
        self.autoRoute = autoRoute;
        
        [self commonInit];
    }
    return self;
}

- (void)commonInit {
    if (self.role != BRAC_QUEUE_OPT_ROLE_AGENT) {
        self.role = BRAC_QUEUE_OPT_ROLE_CLIENT;
    }
    if (!self.priority || [self.priority intValue] == 0) {
        self.priority = @"10";
    }
    
    [AnyChatPlatform getInstance].objectDelegate = self;
    [AnyChatPlatform getInstance].transDataDelegate = self;
    
}

- (NSMutableArray *)businessHallDicArr {
    
    if (_businessHallDicArr == nil) {
        NSMutableArray *businessHallDicArray = [NSMutableArray array];
        _businessHallDicArr = businessHallDicArray;
    }
    return _businessHallDicArr;
}

- (void)getAreas:(int)selfUserId
{
    self.selfUserId = selfUserId;
    
    int agentFlag = 0;
    if (self.role ==BRAC_QUEUE_OPT_ROLE_AGENT) {
        
//        agentFlag = ANYCHAT_OBJECT_FLAGS_AGENT + 0x0200;
        agentFlag = ANYCHAT_OBJECT_FLAGS_AGENT;
        self.agenId = selfUserId;
    }
    if (self.autoRoute) agentFlag += ANYCHAT_OBJECT_FLAGS_AUTOMODE;
    
    [self InitClientObjectInfo:selfUserId :agentFlag priority:self.priority attribute:self.attribute];
}

- (void)enterAreaWithid:(NSString *)areaId
{
    // 进营业厅
    [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AREA :[areaId intValue] :ANYCHAT_AREA_CTRL_USERENTER :0 :0 :0 :0 :nil];
    
}

- (void)enterQueueWithid:(NSString *)queueId
{
    // 进队列
    [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_QUEUE :[queueId intValue] :ANYCHAT_QUEUE_CTRL_USERENTER :0 :0 :0 :0 :nil];
    
}

- (void)cancelQueuing
{
    
    // 退出队列
    [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_QUEUE :self.queueId :ANYCHAT_QUEUE_CTRL_USERLEAVE :0 :0 :0 :0 :nil];

}

- (void)leaveArea
{
    // 退出营业厅
    [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AREA :self.areaId :ANYCHAT_AREA_CTRL_USERLEAVE :0 :0 :0 :0 :nil];
}



// 初始化本地对象信息
- (void)InitClientObjectInfo:(int)mSelfUserId :(int)dwAgentFlags priority:(NSString *)priority attribute:(NSString *)attribute {
    // 业务对象身份初始化
    [AnyChatPlatform SetSDKOptionInt:BRAC_SO_OBJECT_INITFLAGS : dwAgentFlags]; // 0 普通用户 2 坐席
    // 客户端用户对象优先级
    [AnyChatPlatform ObjectSetIntValue:ANYCHAT_OBJECT_TYPE_CLIENTUSER :mSelfUserId :ANYCHAT_OBJECT_INFO_PRIORITY :[self.priority intValue]];
    
    //坐席  开启自动路由
    if(dwAgentFlags == ANYCHAT_OBJECT_FLAGS_AGENT+ANYCHAT_OBJECT_FLAGS_AUTOMODE && [attribute intValue] > 0){
        
        [AnyChatPlatform ObjectSetIntValue:ANYCHAT_OBJECT_TYPE_CLIENTUSER :mSelfUserId :ANYCHAT_OBJECT_INFO_ATTRIBUTE :[self.attribute intValue]];
    }
    else{
        
        [AnyChatPlatform ObjectSetIntValue:ANYCHAT_OBJECT_TYPE_CLIENTUSER :mSelfUserId :ANYCHAT_OBJECT_INFO_ATTRIBUTE :-1];
    }
    
    // 向服务器发送数据同步请求指令
    [AnyChatPlatform ObjectControl: ANYCHAT_OBJECT_TYPE_AREA :ANYCHAT_INVALID_OBJECT_ID :ANYCHAT_OBJECT_CTRL_SYNCDATA :mSelfUserId :0 :0 :0 :nil];
}

#pragma mark - AnyChatTransDataDelegate
// 透明通道回调函数
- (void) OnAnyChatTransBufferCallBack:(int) dwUserid : (NSData*) lpBuf {
    //如果透明通道收到数据则进行解析
    if(lpBuf){
        NSString *result = [[NSString alloc] initWithData:lpBuf encoding:NSUTF8StringEncoding];
        NSDictionary* jsonObj = [self dictionaryWithJsonString:result];
        NSLog(@"*****************%@", jsonObj);
        if ([jsonObj[@"commandType"] isEqualToString: @"videoCall"] ){
            //self.autoRoute = YES;
            [self videoCallRemote:[jsonObj[@"targetUserId"] intValue]];
        }
    }
}

// 透明通道数据扩展回调函数
- (void) OnAnyChatTransBufferExCallBack:(int) dwUserid : (NSData*) lpBuf : (int) wParam : (int) lParam : (int) dwTaskId {
    
}

// 文件传输回调函数
- (void) OnAnyChatTransFileCallBack:(int) dwUserid : (NSString*) lpFileName : (NSString*) lpTempFilePath : (int) dwFileLength : (int) wParam : (int) lParam : (int) dwTaskId {
    
}

// SDK Filter 通信数据回调函数
- (void) OnAnyChatSDKFilterDataCallBack:(NSData*) lpBuf {
    
}

- (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString {
    if (jsonString == nil) {
        return nil;
    }
    
    NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *err;
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                        options:NSJSONReadingMutableContainers
                                                          error:&err];
    if(err) {
        NSLog(@"json解析失败：%@",err);
        return nil;
    }
    return dic;
}

-(NSString*)DataTOjsonString:(id)object {
    NSString *jsonString = nil;
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:object
                                                       options:NSJSONWritingPrettyPrinted // Pass 0 if you don't care about the readability of the generated string
                                                         error:&error];
    if (! jsonData) {
        NSLog(@"Got an error: %@", error);
    } else {
        jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    }
    return jsonString;
}

- (void) videoCallRemote:(int)remoteUserId {
    [AnyChatPlatform VideoCallControl:BRAC_VIDEOCALL_EVENT_REQUEST :remoteUserId:0 :0 :0 :nil];
    [AnyChatQueueDataManager getInstance].customerId = self.selfUserId;
    [AnyChatQueueDataManager getInstance].remoteUserId = self.agenId;
}

#pragma mark - AnyChatObjectEventDelegate
- (void) OnAnyChatObjectEventCallBack: (int) dwObjectType : (int) dwObjectId : (int) dwEventType : (int) dwParam1 : (int) dwParam2 : (int) dwParam3 : (int) dwParam4 : (NSString*) lpStrParam {
    //增加排队日志
    switch (dwEventType) {
        case ANYCHAT_QUEUE_EVENT_USERENTER:
        case ANYCHAT_QUEUE_EVENT_ENTERRESULT:
        case ANYCHAT_QUEUE_EVENT_USERLEAVE:
        case ANYCHAT_QUEUE_EVENT_LEAVERESULT:
            
        case ANYCHAT_AGENT_EVENT_SERVICENOTIFY:
        case ANYCHAT_AGENT_EVENT_ISREADY:
        {
            NSString *typeStr = @"";
            if (dwEventType == ANYCHAT_QUEUE_EVENT_USERENTER) {
                typeStr = @"ANYCHAT_QUEUE_EVENT_USERENTER";
            } else if (dwEventType == ANYCHAT_QUEUE_EVENT_ENTERRESULT) {
                typeStr = @"ANYCHAT_QUEUE_EVENT_ENTERRESULT";
            } else if (dwEventType == ANYCHAT_QUEUE_EVENT_USERLEAVE) {
                typeStr = @"ANYCHAT_QUEUE_EVENT_USERLEAVE";
            } else if (dwEventType == ANYCHAT_QUEUE_EVENT_LEAVERESULT) {
                typeStr = @"ANYCHAT_QUEUE_EVENT_LEAVERESULT";
            } else if (dwEventType == ANYCHAT_AGENT_EVENT_SERVICENOTIFY) {
                typeStr = @"ANYCHAT_AGENT_EVENT_SERVICENOTIFY";
            } else if (dwEventType == ANYCHAT_AGENT_EVENT_ISREADY) {
                typeStr = @"ANYCHAT_AGENT_EVENT_ISREADY";
            }
            
            NSString *str = [NSString stringWithFormat:@">>>>>>>OnAnyChatObjectEventCallBack(%@) dwEventType:%d,dwObjectType:%d,dwObjectId:%d,dwParam1:%d",typeStr,dwEventType,dwObjectType,dwObjectId,dwParam1];
            NSLog(@"%@",str);
            
        }
            
            break;
            
        default:
            break;
    }
    switch (dwEventType) {
        case ANYCHAT_OBJECT_EVENT_UPDATE:// 1.对象数据更新
            [self AnyChatObjectUpdate:dwObjectType :dwObjectId];
            break;
        case ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH:// 2.对象数据同步结束
            [self AnyChatObjectSynDataFinish:dwObjectType];
            break;
            
        case ANYCHAT_AREA_EVENT_USERENTER:// 3.用户进入营业厅
            [self AnyChatUserEnterArea:dwObjectType :dwObjectId :dwParam1 :dwParam2 :dwParam3 :dwParam4];
            break;
        case ANYCHAT_AREA_EVENT_ENTERRESULT:// 4.进入营业厅结果
            [self AnyChatEnterAreaResult:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_AREA_EVENT_USERLEAVE:// 5.用户离开营业厅
            [self AnyChatUserLeaveArea:dwObjectType :dwObjectId :dwParam1 :dwParam2];
            break;
        case ANYCHAT_AREA_EVENT_LEAVERESULT:// 6.离开营业厅结果
            [self AnyChatLeaveAreaResult:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_AREA_EVENT_STATUSCHANGE:// 7.营业厅状态变化
            [self AnyChatAreaStatusChanged:dwObjectType :dwObjectId];
            break;
            
        case ANYCHAT_QUEUE_EVENT_USERENTER:// 8.进入队列
            [self AnyChatUserEnterQueue:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_QUEUE_EVENT_ENTERRESULT:// 9.用户进入队列结果
            [self AnyChatEnterQueueResult:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_QUEUE_EVENT_USERLEAVE:// 10.用户离开队列
            [self AnyChatUserLeaveQueue:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_QUEUE_EVENT_LEAVERESULT:// 11.用户离开队列结果
            [self AnyChatLeaveQueueResult:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_QUEUE_EVENT_STATUSCHANGE:// 12.队列状态变化
            [self AnyChatQueueStatusChanged:dwObjectType :dwObjectId];
            break;
            
        case ANYCHAT_AGENT_EVENT_STATUSCHANGE:// 13.坐席状态变化
            [self AnyChatAgentStatusChanged:dwObjectType :dwObjectId :dwParam1];
            break;
        case ANYCHAT_AGENT_EVENT_SERVICENOTIFY:// 14.坐席服务通知（哪个用户到哪个客服办理业务）
            [self AnyChatAgentServiceNotify:dwParam1 :dwParam2 :dwParam3];
            break;
        case ANYCHAT_AGENT_EVENT_WAITINGUSER:// 15.暂时没有客户，请等待
            [self AnyChatAgentWaitingUser:dwObjectType];
            break;
        case ANYCHAT_AGENT_EVENT_ISREADY:// 坐席准备好，可以发起呼叫
            [self AnyChatReadyServiceNotify:dwParam1 :dwParam2 :dwParam3];
            break;

        default:
            break;
    }
}

// 1.对象数据更新(进和出都会触发)
-(void) AnyChatObjectUpdate:(int)dwObjectType :(int)dwObjectId {
    if(dwObjectType == ANYCHAT_OBJECT_TYPE_AREA) {
        // 获取营业厅名称
        NSString *areaName = [AnyChatPlatform ObjectGetStringValue:dwObjectType :dwObjectId :ANYCHAT_OBJECT_INFO_NAME];
        
        NSDictionary *dic = [[NSDictionary alloc] initWithObjectsAndKeys:areaName,@"areaName",[NSString stringWithFormat:@"%d",dwObjectId],@"areaId", nil];
        
        [self.businessHallDicArr addObject:dic];
        
        NSLog(@"营业厅对象数据更新事件:%@,%d", areaName, dwObjectId);
    }else if(dwObjectType == ANYCHAT_OBJECT_TYPE_QUEUE) {
        // 获取队列名称
        NSString *queueName = [AnyChatPlatform ObjectGetStringValue:dwObjectType :dwObjectId :ANYCHAT_OBJECT_INFO_NAME];
        NSLog(@"队列对象数据更新事件:%@,%d", queueName, dwObjectId);
    }
    
}

// 2.对象数据同步结束
-(void)AnyChatObjectSynDataFinish:(int)dwObjectType {
    if(dwObjectType == ANYCHAT_OBJECT_TYPE_AREA) { //营业厅
        if (self.delegate && [self.delegate respondsToSelector:@selector(onAreasDataFinish:)]) {
            [self.delegate onAreasDataFinish:self.businessHallDicArr];
        }
        self.businessHallDicArr = nil;
        NSLog(@"营业厅对象数据同步结束");
    } else if (dwObjectType == ANYCHAT_OBJECT_TYPE_QUEUE) {
        NSLog(@"队列对象数据同步结束");
    }
}

// 3.用户进入营业厅
-(void) AnyChatUserEnterArea:(int)dwObjectType :(int)dwObjectId :(int)dwUserId :(int)dwFlags :(int)dwAttribute :(int)dwPriority {
    NSString *areaName = [AnyChatPlatform ObjectGetStringValue:dwObjectType :dwObjectId :ANYCHAT_OBJECT_INFO_NAME];
    NSLog(@"用户进入营业厅:%@,%d", areaName, dwObjectId);
}

// 4.进入营业厅结果
-(void) AnyChatEnterAreaResult:(int)dwObjectType :(int)dwObjectId :(int)dwErrorCode {
    
    AnyChatResult *result =[[AnyChatResult alloc]initWithErr:dwErrorCode];
    NSMutableArray *queuesArray = [NSMutableArray array];
    NSDictionary *areaInfo = [self getAreaInfoWithId:dwObjectId];
    NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithDictionary:areaInfo];
    if(dwErrorCode == 0) {
        self.areaId = dwObjectId;
        NSMutableArray *queueIds = [[AnyChatPlatform ObjectGetIdList:ANYCHAT_OBJECT_TYPE_QUEUE] mutableCopy];
        [dic setObject:@(queueIds.count) forKey:@"queueCount"];
        for (int a =0; a<queueIds.count; a++) {
            int queueId = [[NSString stringWithFormat:@"%@",queueIds[a]] intValue];
            NSString *name = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_QUEUE :queueId :ANYCHAT_OBJECT_INFO_NAME];
            NSString *queueIdstr = [NSString stringWithFormat:@"%d",queueId];
            [queuesArray addObject:@{@"id":queueIdstr,@"name":name,@"desc":@""}];
        }
        [dic setObject:queuesArray forKey:@"queues"];
        NSLog(@"用户进入营业厅成功:%@", dic);
    } else {
        NSLog(@"用户进入营业厅失败:(error:%d)", dwErrorCode);
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(onEnterAreaResult:data:)]) {
        [self.delegate onEnterAreaResult:result data:dic];
    }
}

// 5.用户离开营业厅
-(void) AnyChatUserLeaveArea:(int)dwObjectType :(int)dwObjectId :(int)dwUserId :(int)dwErrorCode {
    NSLog(@"用户离开营业厅:%d", dwObjectId);
}

// 6.离开营业厅结果
-(void) AnyChatLeaveAreaResult:(int)dwObjectType :(int)dwObjectId :(int)dwErrorCode {
    
    //移除营业厅中的字典
    if (dwErrorCode == 0) {
        NSLog(@"离开营业厅成功:%d", dwObjectId);
    } else {
        NSLog(@"离开营业厅失败:(error:%d)", dwErrorCode);
    }
}

// 7.营业厅状态变化
- (void) AnyChatAreaStatusChanged:(int)dwObjectType :(int)dwObjectId {
    NSLog(@"营业厅状态变化:%d", dwObjectId);
}

// 8.用户进入队列
-(void) AnyChatUserEnterQueue:(int)dwObjectType :(int)dwObjectId :(int)dwUserId {
    NSLog(@"用户进入队列:%d", dwObjectId);
}

// 9.用户进入队列结果
-(void) AnyChatEnterQueueResult:(int)dwObjectType :(int)dwObjectId :(int)dwErrorCode {
    AnyChatResult *result =[[AnyChatResult alloc]initWithErr:dwErrorCode];
    NSDictionary *dic;
    if(dwErrorCode == 0) {
        dic = [self getQueueInfoWihtId:[NSString stringWithFormat:@"%d",dwObjectId]];
        self.queueId = dwObjectId;
        NSLog(@"用户进入队列成功:%@", dic);
    } else {
        NSLog(@"用户进入队列失败:(error:%d)", dwErrorCode);
    }
    if (self.delegate && [self.delegate respondsToSelector:@selector(onEnterQueueResult:data:)]) {
        [self.delegate onEnterQueueResult:result data:dic];
    }
    
}

// 10.用户离开队列
-(void) AnyChatUserLeaveQueue:(int)dwObjectType :(int)dwObjectId :(int)dwUserId {
    NSLog(@"用户离开队列:%d", dwObjectId);
}

// 11.用户离开队列结果
-(void) AnyChatLeaveQueueResult :(int)dwObjectType :(int)dwObjectId :(int)dwErrorCode {
    if (dwErrorCode == 0) {
        NSLog(@"用户离开队列成功:%d", dwObjectId);
        self.queueId = 0;
    } else {
        NSLog(@"用户离开队列失败:(error:%d)", dwErrorCode);
    }
}

// 12.队列状态变化
-(void) AnyChatQueueStatusChanged:(int)dwObjectType :(int)dwObjectId {
    NSLog(@"队列状态变化:%d", dwObjectId);
    NSString *queueId = [NSString stringWithFormat:@"%d",dwObjectId];
    NSDictionary *dic = [self getQueueInfoWihtId:queueId];
    if (self.delegate && [self.delegate respondsToSelector:@selector(onProcessChanged:)]) {
        [self.delegate onProcessChanged:dic];
    }
}

// 13.坐席状态变化
-(void) AnyChatAgentStatusChanged:(int)dwObjectType :(int)dwObjectId :(int)dwParam1{
    NSLog(@"坐席状态变化:%d", dwParam1);
    //0--关闭，不对外提供服务,
    //1--等待中，可随时接受用户服务,
    //2--工作中，正在为用户服务
    //3--暂停服务,
    //10--离线
    if (dwObjectId == self.agenId) {
        if (self.agentObserver && self.agentObserver.agentStatusChangedBlock) {
            NSString *status = [NSString stringWithFormat:@"%d",dwParam1];
            self.agentObserver.agentStatusChangedBlock(@{@"status":status});
        }
        return;
    }
}

// 14.坐席服务通知(有人排队)
-(void) AnyChatAgentServiceNotify:(int)dwAgentId :(int)clientId :(int)queueId {
    NSLog(@"坐席服务通知(有人排队):agent:%d,client:%d,queue:%d", dwAgentId, clientId, queueId);
    if (self.role == BRAC_QUEUE_OPT_ROLE_AGENT  && dwAgentId == self.agenId) {
        NSNumber *agentId = [NSNumber numberWithInt:dwAgentId];
        NSNumber *customerId = [NSNumber numberWithInt:clientId];
        NSString *queue = [NSString stringWithFormat:@"%d",queueId];
        
        NSString *ip = [[NSUserDefaults standardUserDefaults] objectForKey:@"AnyChatSerVer"];
        if ([ip isEqualToString:kAnyChatCloudIP]) {
            // 连接云平台cloud.anychat.cn时为客户呼叫坐席
            NSDictionary *dict = @{@"commandType":@"videoCall",@"targetUserId":agentId,@"isAutoMode":@(self.autoRoute)};
            NSLog(@"transBuffer:%@", dict);
            NSString* string =  [self DataTOjsonString:dict];
            [AnyChatPlatform TransBuffer:clientId :[string dataUsingEncoding:NSUTF8StringEncoding]];
        } else {
            // 连接非云平台demo.anychat.cn时为坐席呼叫客户
            if (self.agentObserver && self.agentObserver.serviceNotifyBlock) {
               NSDictionary *data = @{@"agentId":agentId,@"customerId":customerId,@"queueId":queue};
                self.agentObserver.serviceNotifyBlock(data);
            }
        }
    }
}

// 15.坐席等待用户(没人排队)
-(void) AnyChatAgentWaitingUser:(int)dwObjectType {
    NSLog(@"坐席等待用户(没人排队)");
    //[MBProgressHUD showError:@"无人排队，稍后再试"];
}

// 14.坐席已经准备好，由客户端发起呼叫
-(void) AnyChatReadyServiceNotify:(int)dwAgentId :(int)clientId  :(int)queueId{
    NSLog(@"坐席已经准备好，由客户端发起呼叫通知");
    if (self.role == BRAC_QUEUE_OPT_ROLE_CLIENT) {
        self.agenId = dwAgentId;
        NSNumber *agentId = [NSNumber numberWithInt:dwAgentId];
        NSNumber *customerId = [NSNumber numberWithInt:clientId];
        NSString *queue = [NSString stringWithFormat:@"%d",queueId];
        if (self.delegate && [self.delegate respondsToSelector:@selector(onServiceNotify:)]) {
            [self.delegate onServiceNotify:@{@"agentId":agentId,@"customerId":customerId,@"queueId":queue}];
        }
    }
}

- (NSDictionary *)getAreaInfoWithId:(int)areaId{
    
    // 获取营业厅名称
    NSString *areaName = [AnyChatPlatform ObjectGetStringValue:ANYCHAT_OBJECT_TYPE_AREA :areaId :ANYCHAT_OBJECT_INFO_NAME];
    // 营业厅内访客的用户数（没有排入队列的用户）；
    int guestCount = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_AREA :areaId :ANYCHAT_AREA_INFO_GUESTCOUNT];
    
    // 营业厅内访客的用户数；
    int queningUserCount = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_AREA :areaId :ANYCHAT_AREA_INFO_QUEUEUSERCOUNT];
    NSString *areaIdstr = [NSString stringWithFormat:@"%d",areaId];
    return @{@"areaId":areaIdstr,@"areaName":areaName,@"areaDesc":@"",@"guestCount":@(guestCount),@"queningUserCount":@(queningUserCount)};
}

- (NSDictionary *)getQueueInfoWihtId:(NSString *)queueId{
    
    int queuePeopleCount = [self getQueuelengthWithid:queueId];
    int myIndex = [self getQueueIndexWithid:queueId];
    int time = [self getQueueTimeWithid:queueId];
    NSDictionary *dic = @{@"queueId":queueId,
                          @"userNumInQueue":@(queuePeopleCount),
                          @"currentPos":@(myIndex),
                          @"waitingTime":@(time)};
    return dic;
}

- (int)getQueuelengthWithid:(NSString *)queueId{
    
    int queuePeopleCount = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :[queueId intValue] :ANYCHAT_QUEUE_INFO_QUEUELENGTH];
    return queuePeopleCount;
}

- (int)getQueueTimeWithid:(NSString *)queueId{
    
    int time = [AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :[queueId intValue] :ANYCHAT_QUEUE_INFO_WAITTIMESECOND];
    return time;
}

- (int)getQueueIndexWithid:(NSString *)queueId{
    
    int queueIndex =[AnyChatPlatform ObjectGetIntValue:ANYCHAT_OBJECT_TYPE_QUEUE :[queueId intValue] :ANYCHAT_QUEUE_INFO_MYSEQUENCENO];
    if (queueIndex <= 0) {
        queueIndex =0;
    }
    return  queueIndex;
}

- (void)agentServiceCtrlWithCtrlCode:(BRAC_AgentServiceCtrlCode)code
{
    int anyChatId = self.selfUserId;
    if (code == BRAC_AGENT_SERVICE_WAITTING) {
        
        [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT :anyChatId :ANYCHAT_AGENT_CTRL_SERVICEREQUEST :0 :0 :0 :0 :nil];
        
        
        //[AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT
        //                              :anyChatId
        //                              :ANYCHAT_AGENT_CTRL_SERVICESTATUS
        //                              :ANYCHAT_AGENT_STATUS_WAITTING :0 :0 :0 :nil];
        
        
    }else if (code == BRAC_AGENT_SERVICE_PAUSED) {
        
        //
        [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT
                                      :anyChatId
                                      :ANYCHAT_AGENT_CTRL_SERVICESTATUS
                                      :ANYCHAT_AGENT_STATUS_PAUSED :0 :0 :0 :nil];
    }else if (code == BRAC_AGENT_SERVICE_FINISHSERVICE){
        
        // 结束服务
        [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT :anyChatId :ANYCHAT_AGENT_CTRL_FINISHSERVICE :0 :0 :0 :0 :nil];
    }
    else{
        
        // 超时结束服务
        [AnyChatPlatform ObjectControl:ANYCHAT_OBJECT_TYPE_AGENT :anyChatId :ANYCHAT_AGENT_CTRL_FINISHSERVICE :GV_ERR_VIDEOCALL_TIMEOUT :0 :0 :0 :nil];
    }
}

@end

@implementation AnyChatQueueDataManager

static AnyChatQueueDataManager *_instance;

+ (instancetype)allocWithZone:(struct _NSZone *)zone
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _instance = [super allocWithZone:zone];
    });
    return _instance;
}

+ (instancetype)getInstance
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _instance = [[self alloc] init];
    });
    return _instance;
}

- (id)copyWithZone:(NSZone *)zone
{
    return _instance;
}

@end
