//
//  BRAC_Result.m
//  AnyChatInterviewIphone
//
//  Created by bairuitech on 2017/7/8.
//  Copyright © 2017年 anychat. All rights reserved.
//

#import "AnyChatResult.h"

@implementation AnyChatResult

- (instancetype)initWithErr:(int)code msg:(NSString *)msg{
    
    self = [super init];
    self.errorCode = code;
    self.errorMsg = msg;
    return self;
}

- (NSString *)description{
    
    return [NSString stringWithFormat:@"errorCode = %d,errorMsg = %@",self.errorCode,self.errorMsg];
    
}

- (NSDictionary *)toDictionary{
    
    NSString *code = [NSString stringWithFormat:@"%d",self.errorCode];
    return @{@"errorCode":code,@"errorMsg":self.errorMsg};
}
    
- (instancetype)initWithErr:(int)code{
    
    self = [super init];
    self.errorCode = code;
    self.errorMsg = [self msgByCode:code];
    return self;
}
    
- (NSString *)msgByCode:(int)code{
    
    NSString *errorMsg = @"";
    switch (code) {
        case 0:
        errorMsg = @"success";
        break;
        /******************* system error code define *********************/
        case 1:
        errorMsg = @"数据库错误";
        break;
        case 2:
        errorMsg = @"系统没有初始化";
        break;
        case 3:
        errorMsg = @"还未进入房间";
        break;
        case 4:
        errorMsg = @"not enough memory";
        break;
        case 5:
        errorMsg = @"出现异常";
        break;
        case 6:
        errorMsg = @"操作被取消";
        break;
        case 7:
        errorMsg = @"通信协议出错";
        break;
        case 8:
        errorMsg = @"会话不存在";
        break;
        case 9:
        errorMsg = @"数据不存在";
        break;
        case 10:
        errorMsg = @"数据已经存在";
        break;
        case 11:
        errorMsg = @"无效GUID";
        break;
        case 12:
        errorMsg = @"资源被回收";
        break;
        case 13:
        errorMsg = @"资源被占用";
        break;
        case 14:
        errorMsg = @"Json解析出错";
        break;
        case 15:
        errorMsg = @"对象被删除";
        break;
        case 16:
        errorMsg = @"会话已存在";
        break;
        case 17:
        errorMsg = @"会话没有初始化";
        break;
        case 18:
        errorMsg = @"数据没有准备好";
        break;
        case 19:
        errorMsg = @"收到SIGTERM信号(kill指令)";
        break;
        case 20:
        errorMsg = @"函数功能不允许";
        break;
        case 21:
        errorMsg = @"function parameters error";
        break;
        case 22:
        errorMsg = @"device open failed or device no install";
        break;
        case 23:
        errorMsg = @"没有足够的资源";
        break;
        case 24:
        errorMsg = @"指定的格式不能被显示设备所支持";
        break;
        case 25:
        errorMsg = @"指定的IP地址不是有效的组播地址";
        break;
        case 26:
        errorMsg = @"不支持多实例运行";
        break;
        case 27:
        errorMsg = @"文件签名验证失败";
        break;
        case 28:
        errorMsg = @"授权验证失败";
        break;
        case 29:
        errorMsg = @"授权证书用户数验证失败";
        break;
        case 30:
        errorMsg = @"所指定的主服务器是热备服务器，不支持再次热备";
        break;
        case 31:
        errorMsg = @"主服务器没有经过授权认证，不支持热备";
        break;
        case 32:
        errorMsg = @"版本不匹配";
        break;
        case 33:
        errorMsg = @"第二次授权验证失败";
        break;
        case 34:
        errorMsg = @"服务器安全验证失败";
        break;
        case 35:
        errorMsg = @"客户端授权验证失败";
        break;
        case 36:
        errorMsg = @"授权功能校验失败";
        break;
        case 37:
        errorMsg = @"远程控制";
        break;
        case 38:
        errorMsg = @"ServiceGuid重复";
        break;
        case 39:
        errorMsg = @"目录错误";
        break;
        case 40:
        errorMsg = @"解压文件失败";
        break;
        case 41:
        errorMsg = @"启动进程失败";
        break;
        case 42:
        errorMsg = @"服务已启动";
        break;
        case 43:
        errorMsg = @"磁盘空间不足";
        break;
        case 44:
        errorMsg = @"业务服务发送请求失败";
        break;
        case 45:
        errorMsg = @"无效的物理机对象";
        break;
        case 46:
        errorMsg = @"获取授权信息失败";
        break;
        case 47:
        errorMsg = @"集群属性不匹配";
        break;
        case 48:
        errorMsg = @"集群ID为空";
        break;
        case 49:
        errorMsg = @"同台物理机创建多个相同服务，一类服务暂时不允许创建多个";
        break;
        case 50:
        errorMsg = @"拷贝文件失败";
        break;
        case 51:
        errorMsg = @"云平台内部数据库出错";
        break;
        case 52:
        errorMsg = @"云平台OSS文件上传失败";
        break;
        case 53:
        errorMsg = @"服务绑定关系变化";
        break;
        case 54:
        errorMsg = @"服务没有被绑定";
        break;
        case 55:
        errorMsg = @"服务绑定失败";
        break;
        case 56:
        errorMsg = @"PipeLine通信用户ID出错";
        break;
        case 57:
        errorMsg = @"PipeLine通信会话出错";
        break;
        case 58:
        errorMsg = @"服务被关闭";
        break;
        case 59:
        errorMsg = @"文件已被加密过";
        break;
        case 60:
        errorMsg = @"解密无效（文件校验不通过）";
        break;
        case 61:
        errorMsg = @"解密失败，可能密码错误";
        break;
        case 62:
        errorMsg = @"缓冲区太长";
        break;
        case 63:
        errorMsg = @"服务器版本太旧";
        break;
        case 64:
        errorMsg = @"不支持的文件类型";
        break;
        case 65:
        errorMsg = @"文件内容出错";
        break;
        case 66:
        errorMsg = @"密钥校验失败";
        break;
        case 67:
        errorMsg = @"缺少证书链";
        break;
        case 68:
        errorMsg = @"证书校验失败";
        break;
        case 69:
        errorMsg = @"证书日期校验失败";
        break;
        case 70:
        errorMsg = @"证书日期校验失败";
        break;
        case 71:
        errorMsg = @"缺少公钥";
        break;
        case 72:
        errorMsg = @"服务器没有配置SSL证书所对应的私钥";
        break;
        case 73:
        errorMsg = @"服务器没有配置SSL证书";
        break;
        case 74:
        errorMsg = @"安全级别限制，不允许连接";
        break;
        case 75:
        errorMsg = @"安全协商失败";
        break;
        case 76:
        errorMsg = @"算法协商失败";
        break;
        case 77:
        errorMsg = @"缺少CertHelper库文件";
        break;
        /******************* 连接部分 *********************/
        case 100:
        errorMsg = @"连接服务器超时";
        break;
        case 101:
        errorMsg = @"与服务器的连接中断";
        break;
        case 102:
        errorMsg = @"连接服务器认证失败（服务器设置了认证密码）";
        break;
        case 103:
        errorMsg = @"域名解析失败";
        break;
        case 104:
        errorMsg = @"超过授权用户数";
        break;
        case 105:
        errorMsg = @"服务器功能受限制（演示模式）";
        break;
        case 106:
        errorMsg = @"只能在内网使用";
        break;
        case 107:
        errorMsg = @"版本太旧，不允许连接";
        break;
        case 108:
        errorMsg = @"Socket出错";
        break;
        case 109:
        errorMsg = @"设备连接限制（没有授权）";
        break;
        case 110:
        errorMsg = @"服务已被暂停";
        break;
        case 111:
        errorMsg = @"热备服务器不支持连接（主服务在启动状态）";
        break;
        case 112:
        errorMsg = @"授权用户数校验出错，可能内存被修改";
        break;
        case 113:
        errorMsg = @"IP被禁止连接";
        break;
        case 114:
        errorMsg = @"连接类型错误，服务器不支持当前类型的连接";
        break;
        case 115:
        errorMsg = @"服务器IP地址不正确";
        break;
        case 116:
        errorMsg = @"连接被主动关闭";
        break;
        case 117:
        errorMsg = @"没有获取到服务器列表";
        break;
        case 118:
        errorMsg = @"连接负载均衡服务器超时";
        break;
        case 119:
        errorMsg = @"服务器不在工作状态";
        break;
        case 120:
        errorMsg = @"服务器不在线";
        break;
        case 121:
        errorMsg = @"网络带宽受限";
        break;
        case 122:
        errorMsg = @"网络流量不足";
        break;
        case 123:
        errorMsg = @"不支持IPv6 Only网络";
        break;
        case 124:
        errorMsg = @"没有Master服务器在线";
        break;
        case 125:
        errorMsg = @"没有上报工作状态";
        break;
        /******************* 登录部分  *********************/
        case 200:
        errorMsg = @"认证失败，用户名或密码有误";
        break;
        case 201:
        errorMsg = @"该用户已登录";
        break;
        case 202:
        errorMsg = @"帐户已被暂时锁定";
        break;
        case 203:
        errorMsg = @"IP地址已被暂时锁定";
        break;
        case 204:
        errorMsg = @"游客登录被禁止（登录时没有输入密码）";
        break;
        case 205:
        errorMsg = @"无效的用户ID（用户不存在）";
        break;
        case 206:
        errorMsg = @"与业务服务器连接失败，认证功能失效";
        break;
        case 207:
        errorMsg = @"业务服务器执行任务超时";
        break;
        case 208:
        errorMsg = @"没有登录";
        break;
        case 209:
        errorMsg = @"该用户在其它计算机上登录";
        break;
        case 210:
        errorMsg = @"用户名为空";
        break;
        case 211:
        errorMsg = @"被服务器踢掉";
        break;
        case 212:
        errorMsg = @"业务服务器重启";
        break;
        case 213:
        errorMsg = @"操作被禁止，没有权限";
        break;
        case 214:
        errorMsg = @"签名信息为空，禁止登录";
        break;
        case 215:
        errorMsg = @"签名验证失败";
        break;
        case 216:
        errorMsg = @"签名验证公钥为空";
        break;
        case 217:
        errorMsg = @"签名私钥为空";
        break;
        case 218:
        errorMsg = @"签名参数为空";
        break;
        case 219:
        errorMsg = @"签名参数出错";
        break;
        case 220:
        errorMsg = @"签名时间失效";
        break;
        case 221:
        errorMsg = @"应用没有被激活";
        break;
        case 222:
        errorMsg = @"应用被用户暂停";
        break;
        case 223:
        errorMsg = @"应用被用户锁定";
        break;
        case 224:
        errorMsg = @"应用已过期";
        break;
        case 225:
        errorMsg = @"应用未知状态";
        break;
        case 226:
        errorMsg = @"签名已经被使用";
        break;
        case 227:
        errorMsg = @"获取用户角色失败";
        break;
        case 228:
        errorMsg = @"坐席无效(不存在)";
        break;
        case 229:
        errorMsg = @"客户端校验服务器签名失败";
        break;
        /******************* 进入房间  *********************/
        case 300:
        errorMsg = @"房间已被锁住，禁止进入";
        break;
        case 301:
        errorMsg = @"房间密码错误，禁止进入";
        break;
        case 302:
        errorMsg = @"房间已满员，不能进入";
        break;
        case 303:
        errorMsg = @"房间不存在";
        break;
        case 304:
        errorMsg = @"房间服务时间已到期";
        break;
        case 305:
        errorMsg = @"房主拒绝进入";
        break;
        case 306:
        errorMsg = @"房主不在，不能进入房间";
        break;
        case 307:
        errorMsg = @"不能进入房间";
        break;
        case 308:
        errorMsg = @"已经在房间里面了，本次进入房间请求忽略";
        break;
        case 309:
        errorMsg = @"不在房间中，对房间相关的API操作失败";
        break;
        /******************* 数据流  *********************/
        case 350:
        errorMsg = @"过期数据包";
        break;
        case 351:
        errorMsg = @"相同的数据包";
        break;
        case 352:
        errorMsg = @"数据包丢失";
        break;
        case 353:
        errorMsg = @"数据包出错，帧序号存在误差";
        break;
        case 354:
        errorMsg = @"媒体流缓冲时间不足";
        break;
        /******************* 私聊  *********************/
        case 401:
        errorMsg = @"用户已经离开房间";
        break;
        case 402:
        errorMsg = @"用户拒绝了私聊邀请";
        break;
        case 403:
        errorMsg = @"不允许与该用户私聊，或是用户禁止私聊";
        break;
        case 420:
        errorMsg = @"私聊请求ID号错误，或请求不存在";
        break;
        case 421:
        errorMsg = @"已经在私聊列表中";
        break;
        case 431:
        errorMsg = @"私聊请求超时";
        break;
        case 432:
        errorMsg = @"对方正在私聊中，繁忙状态";
        break;
        case 433:
        errorMsg = @"对方用户关闭私聊";
        break;
        case 434:
        errorMsg = @"用户自己关闭私聊";
        break;
        case 435:
        errorMsg = @"私聊请求被取消";
        break;
        /******************* 视频呼叫  *********************/
        case 440:
        errorMsg = @"正在通话中";
        break;
        /******************* Mic控制权  *********************/
        case 500:
        errorMsg = @"说话时间太长，请休息一下";
        break;
        case 501:
        errorMsg = @"有高级别用户需要发言，请休息一下";
        break;
        /******************* 集群总线  *********************/
        case 610:
        errorMsg = @"本地总线为Master状态";
        break;
        case 611:
        errorMsg = @"有其它总线存在";
        break;
        case 612:
        errorMsg = @"优先级不够";
        break;
        /******************* 传输部分  *********************/
        case 700:
        errorMsg = @"创建任务失败";
        break;
        case 701:
        errorMsg = @"没有该任务，或是任务已完成";
        break;
        case 702:
        errorMsg = @"上传失败";
        break;
        case 710:
        errorMsg = @"打开文件出错";
        break;
        case 711:
        errorMsg = @"文件长度为0";
        break;
        case 712:
        errorMsg = @"文件长度太大";
        break;
        case 713:
        errorMsg = @"读文件出错";
        break;
        case 714:
        errorMsg = @"文件正在下载中";
        break;
        case 715:
        errorMsg = @"文件下载失败";
        break;
        case 716:
        errorMsg = @"没有该任务，或是任务已完成";
        break;
        /******************* 录像部分  *********************/
        case 720:
        errorMsg = @"没有录像任务";
        break;
        case 721:
        errorMsg = @"创建录像任务失败";
        break;
        case 722:
        errorMsg = @"等待用户相关信息，暂时不能录像";
        break;
        /******************* 队列部分  *********************/
        case 750:
        errorMsg = @"无效的队列ID";
        break;
        case 751:
        errorMsg = @"准备接受服务，离开队列";
        break;
        /******************* SDK警告  *********************/
        case 780:
        errorMsg = @"与服务器的UDP通信异常，流媒体服务将不能正常工作";
        break;
        case 781:
        errorMsg = @"SDK加载brMiscUtil.dll动态库失败，部分功能将失效";
        break;
        case 782:
        errorMsg = @"SDK加载brMediaUtil.dll动态库失败，部分功能将失效";
        break;
        case 783:
        errorMsg = @"SDK加载brMediaCore.dll动态库失败，部分功能将失效";
        break;
        case 784:
        errorMsg = @"SDK加载brMediaShow.dll动态库失败，部分功能将失效";
        break;
        /******************* 授权证书  *********************/
        case 800:
        errorMsg = @"获取授权信息失败";
        break;
        case 801:
        errorMsg = @"授权已过期";
        break;
        case 802:
        errorMsg = @"证书解码失败";
        break;
        case 810:
        errorMsg = @"解析硬件特征码失败（可能是证书存在问题）";
        break;
        case 811:
        errorMsg = @"CPU特征码不匹配（CPU数量）";
        break;
        case 812:
        errorMsg = @"CPU特征码不匹配（CPU主频）";
        break;
        case 813:
        errorMsg = @"内存特征码不匹配（内存容量）";
        break;
        case 814:
        errorMsg = @"网卡特征码不匹配（MAC地址）";
        break;
        case 815:
        errorMsg = @"CPU特征码不匹配（CPU型号）";
        break;
        case 816:
        errorMsg = @"硬盘特征码不匹配（磁盘ID）";
        break;
        case 830:
        errorMsg = @"UKey信息不正常";
        break;
        case 831:
        errorMsg = @"没有查询到UKey设备";
        break;
        case 832:
        errorMsg = @"获取UKey信息特征码失败";
        break;
        case 833:
        errorMsg = @"绑定的UKey和当前插入的UKey不匹配";
        break;
        case 834:
        errorMsg = @"加载UKey动态库失败";
        break;
        case 840:
        errorMsg = @"域名解析验证失败";
        break;
        case 842:
        errorMsg = @"域名解析失败";
        break;
        case 850:
        errorMsg = @"绑定的IP地址和服务器本地IP地址不匹配";
        break;
        case 860:
        errorMsg = @"域名信息错误";
        break;
        case 861:
        errorMsg = @"UKey信息错误";
        break;
        case 862:
        errorMsg = @"IP地址错误";
        break;
        /******************* video device error code define *********************/
        case 10001:
        errorMsg = @"Open video device fail";
        break;
        case 10002:
        errorMsg = @"Unknow output video pix format";
        break;
        case 10003:
        errorMsg = @"Driver Not supported VIDIOC_G_FMT";
        break;
        case 10004:
        errorMsg = @"Driver Not supported VIDIOC_S_FMT";
        break;
        case 10005:
        errorMsg = @"Driver Not supported VIDIOC_G_PARM";
        break;
        case 10006:
        errorMsg = @"Driver Not supported VIDIOC_S_PARM";
        break;
        case 10007:
        errorMsg = @"Driver Not supported VIDIOC_QUERYCAP";
        break;
        case 10008:
        errorMsg = @"This is not a capture video device";
        break;
        case 10009:
        errorMsg = @"For acquisition error";
        break;
        case 10010:
        errorMsg = @"Device Not supported for mmap and usermap mode";
        break;
        case 10011:
        errorMsg = @"get physaddr to block fail";
        break;
        case 10012:
        errorMsg = @"physaddr map to viraddr fail";
        break;
        case 10013:
        errorMsg = @"video prepbuff fail";
        break;
        case 10014:
        errorMsg = @"get video fail";
        break;
        case 10015:
        errorMsg = @"QBUF fail";
        break;
        case 10016:
        errorMsg = @"VIDIOC_STREAMON fail";
        break;
        case 10017:
        errorMsg = @"VIDIOC_STREAMOFF fail";
        break;
        case 10018:
        errorMsg = @"May be camera is used by other progress now";
        break;
        case 10019:
        errorMsg = @"unsupport video capture mode";
        break;
        case 10020:
        errorMsg = @"the requested buffer type not supported, or VIDIOC_TRY_FMT was called and is not supported with this buffer type.";
        break;
        /******************* Audio device error code define *********************/
        case 10500:
        errorMsg = @"Open Audio device fail";
        break;
        case 10501:
        errorMsg = @"alloc hwparams fail";
        break;
        case 10502:
        errorMsg = @"set interleaved mode fail";
        break;
        case 10503:
        errorMsg = @"set wBitsPerSample fail";
        break;
        case 10504:
        errorMsg = @"set SamplesPerSec fail";
        break;
        case 10505:
        errorMsg = @"set channels fail";
        break;
        case 10506:
        errorMsg = @"set periods  fail";
        break;
        case 10507:
        errorMsg = @"set buffer size fail";
        break;
        case 10508:
        errorMsg = @"function :snd_pcm_hw_params fail";
        break;
        case 10509:
        errorMsg = @"set rebuffer time fail";
        break;
        case 10510:
        errorMsg = @"get rebuffer frames fail";
        break;
        case 10511:
        errorMsg = @"get period time fail";
        break;
        case 10512:
        errorMsg = @"get period time fail";
        break;
        case 10513:
        errorMsg = @"alloc swparams fail";
        break;
        case 10514:
        errorMsg = @"set start threshoid fail";
        break;
        case 10515:
        errorMsg = @"set start avail min fail";
        break;
        case 10516:
        errorMsg = @"function snd_pcm_prepare fail";
        break;
        case 10517:
        errorMsg = @"function read fail";
        break;
        case 30000:
        errorMsg = @"创建会话失败";
        break;
        /******************* 视频呼叫 *********************/
        case 100101:
        errorMsg = @"源用户主动放弃会话";
        break;
        case 100102:
        errorMsg = @"目标用户不在线";
        break;
        case 100103:
        errorMsg = @"目标用户忙";
        break;
        case 100104:
        errorMsg = @"目标用户拒绝会话";
        break;
        case 100105:
        errorMsg = @"会话请求超时";
        break;
        case 100106:
        errorMsg = @"网络断线";
        break;
        case 100107:
        errorMsg = @"用户不在呼叫状态";
        break;
        /******************* 业务对象 *********************/
        case 100201:
        errorMsg = @"已经进入一个服务区域";
        break;
        case 100202:
        errorMsg = @"已经进入一个服务队列";
        break;
        /******************* 应用ID *********************/
        case 100300:
        errorMsg = @"默认的应用ID（空）不被支持";
        break;
        case 100301:
        errorMsg = @"应用登录需要签名";
        break;
        case 100302:
        errorMsg = @"应用签名校验失败";
        break;
        case 100303:
        errorMsg = @"应用ID不存在";
        break;
        case 100304:
        errorMsg = @"应用ID被系统锁定";
        break;
        case 100305:
        errorMsg = @"应用ID与当前服务不匹配";
        break;
        case 100306:
        errorMsg = @"连接的服务器不是云平台地址";
        break;
        case 100307:
        errorMsg = @"应用所对应的计费服务器不足";
        break;
        case 100308:
        errorMsg = @"应用计费模式改变";
        break;
        /******************* 创建用户 *********************/
        case 100400:
        errorMsg = @"用户密码长度过短";
        break;
        case 100401:
        errorMsg = @"用户名重名";
        break;
        case 100402:
        errorMsg = @"权限受限";
        break;
        case 100403:
        errorMsg = @"不允许创建该用户名";
        break;
        /******************* 升级服务过程 *********************/
        case 100500:
        errorMsg = @"升级服务开始";
        break;
        case 100501:
        errorMsg = @"升级服务，正在停止当前服务...";
        break;
        case 100502:
        errorMsg = @"升级服务，正在备份当前服务...";
        break;
        case 100503:
        errorMsg = @"升级服务，正在删除当前服务...";
        break;
        case 100504:
        errorMsg = @"升级服务，正在拷贝新服务...";
        break;
        case 100505:
        errorMsg = @"升级服务，正在启动新服务...";
        break;
        case 100506:
        errorMsg = @"升级服务，正在恢复老版本...";
        break;
        case 100507:
        errorMsg = @"升级服务，已经是目标版本";
        break;
        case 100508:
        errorMsg = @"升级服务，当前服务需要停止，才能执行升级操作";
        break;
        case 100509:
        errorMsg = @"升级服务，备份失败";
        break;
        case 100510:
        errorMsg = @"升级服务，删除失败";
        break;
        case 100511:
        errorMsg = @"升级服务，拷贝失败";
        break;
        case 100512:
        errorMsg = @"升级服务，恢复老版本失败";
        break;
        case 100513:
        errorMsg = @"升级服务，通讯桥未注册";
        break;
        case 100514:
        errorMsg = @"升级服务，写入配置文件失败";
        break;
        case 100515:
        errorMsg = @"升级服务，获取备份文件夹失败";
        break;
        case 100516:
        errorMsg = @"升级服务结束";
        break;
        case 100517:
        errorMsg = @"无法获取维护信息";
        break;
        case 100518:
        errorMsg = @"不能重命名文件夹";
        break;
        /******************* 停止进程过程 *********************/
        case 100600:
        errorMsg = @"停止进程，超时";
        break;
        case 100601:
        errorMsg = @"停止进程，失败(被回复失败)";
        break;
        case 100602:
        errorMsg = @"停止进程，强行杀死失败";
        break;
        /******************* 启动进程 *********************/
        case 100603:
        errorMsg = @"启动进程,规定时间内没有收到通讯桥通知";
        break;
        case 100604:
        errorMsg = @"service 正在被控制中(e.g 正在执行升级任务的时候，还收到了其他控制命令)";
        break;
        case 100605:
        errorMsg = @"在启动或解压之前，发现除目标之外还存在其他版本";
        break;
        case 100606:
        errorMsg = @"不支持此操作（e.g 对PMServer下达挂起命令等 ）";
        break;
        case 100607:
        errorMsg = @"不存在该版本的升级包";
        break;
        case 100608:
        errorMsg = @"升级包中不存在该服务";
        break;
        case 100609:
        errorMsg = @"扩展的配置参数非法（e.g LUServer 的 serviceBaseInfo 的扩展参数解析错误） ";
        break;
        case 100610:
        errorMsg = @"移动临时文件到升级目录时失败";
        break;
        case 100611:
        errorMsg = @"不兼容当前OS平台";
        break;
        case 100612:
        errorMsg = @"获取 rootserverconnect 失败";
        break;
        /******************* 业务服务器错误代码 *********************/
        case 100701:
        errorMsg = @"无效参数";
        break;
        case 100702:
        errorMsg = @"应用ID不存在";
        break;
        case 100703:
        errorMsg = @"Body无效";
        break;
        case 100704:
        errorMsg = @"签名验证失败";
        break;
        case 100705:
        errorMsg = @"签名时间戳无效";
        break;
        case 100706:
        errorMsg = @"not enough memory";
        break;
        case 100707:
        errorMsg = @"出现异常";
        break;
        case 100708:
        errorMsg = @"通信协议出错";
        break;
        case 100709:
        errorMsg = @"业务服务器执行任务超时";
        break;
        case 100710:
        errorMsg = @"文件不存在";
        break;
        /******************* 数据库服务器错误代码 *********************/
        case 100801:
        errorMsg = @"数据库执行错误";
        break;
        case 100802:
        errorMsg = @"数据库查询不到数据";
        break;
        case 100803:
        errorMsg = @"数据库读取行数据错误";
        break;
        case 100804:
        errorMsg = @"出现异常";
        break;
        case 100805:
        errorMsg = @"连接异常";
        break;
        
        case 100806:
        errorMsg = @"发送信息超时";
        break;
            
        case 100900:
            errorMsg = @"业务请求超时";
            break;
        case 100901:
            errorMsg = @"业务请求参数错误";
            break;
        /******************* 机器人错误代码 *********************/
        case 200000:
        {
            errorMsg = @"目标用户不存在";
        }
            break;
        case 200001:
        {
            errorMsg = @"目标用户已开启该功能";
        }
            break;
        case 200002:
        {
            errorMsg = @"AI对象不存在";
        }
            break;
        case 200003:
        {
            errorMsg = @"AI参数错误";
        }
            break;
        case 200004:
        {
            errorMsg = @"AI能力不支持";
        }
            break;
        case 200005:
        {
            errorMsg = @"未知AI能力";
        }
            break;
        case 200006:
        {
            errorMsg = @"http请求失败";
        }
            break;
        case 200007:
        {
            errorMsg = @"AI请求初始化失败";
        }
            break;
        case 200008:
        {
            errorMsg = @"AI请求失败";
        }
            break;
        case 200009:
        {
            errorMsg = @"AI请求超时";
        }
            break;
        case 200010:
        {
            errorMsg = @"内部数据无效";
        }
            break;
        case 200011:
        {
            errorMsg = @"内部数据不存在";
        }
            break;
        case 200012:
        {
            errorMsg = @"内部对象无效";
        }
            break;
        case 200013:
        {
            errorMsg = @"AI心跳超时";
        }
            break;
        case 200014:
        {
            errorMsg = @"AI离线";
        }
            break;
        case 200015:
        {
            errorMsg = @"AI请求内容超长";
        }
            break;
        case 200016:
        {
            errorMsg = @"anychat指令超长";
        }
            break;
        case 200017:
        {
            errorMsg = @"AI请求超过并发数";
        }
            break;
        default:
        errorMsg = @"未定义错误信息，请反馈给我们。";
        break;
    }
    return errorMsg;
}
@end
