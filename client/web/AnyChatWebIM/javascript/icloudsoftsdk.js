// iCloudSoft Business Logic SDK

/********************************************
 *				常量定义部分				*
 *******************************************/
// 文件传输操作类型（API：ICS_FileTransControl 传入参数）
var ICS_FILETRANS_CTRLTYPE_OPENFILE		= 1;		// 打开文件
var ICS_FILETRANS_CTRLTYPE_OPENDIR		= 2;		// 打开文件所在目录

// 文件传输属性查询（API：ICS_FileTransQueryXXXValue 传入参数）
var ICS_FILETRANS_PROPERTY_SRCUSERID	= 1;		// 发送方用户ID
var ICS_FILETRANS_PROPERTY_TARUSERID	= 2;		// 接收方用户ID
var ICS_FILETRANS_PROPERTY_FILESIZE		= 3;		// 文件大小
var ICS_FILETRANS_PROPERTY_FILENAME		= 4;		// 文件名

// 用户对象属性定义
var ICS_USEROBJECT_PROPERTY_NAME		= 1;		// 用户名
var ICS_USEROBJECT_PROPERTY_TYPE		= 2;		// 用户身份
var ICS_USEROBJECT_PROPERTY_IMAGEID		= 3;		// 用户图像ID
var ICS_USEROBJECT_PROPERTY_STATUS		= 4;		// 用户活动状态
var ICS_USEROBJECT_PROPERTY_GROUPID		= 5;		// 用户分组ID

// 分组对象属性定义
var ICS_GROUPOBJECT_PROPERTY_NAME		= 1;		// 用户分组名称

// 会议对象属性定义
var ICS_MEETINGOBJECT_PROPERTY_GUID		= 1;		// 会议GUID
var ICS_MEETINGOBJECT_PROPERTY_NAME		= 2;		// 会议名称
var ICS_MEETINGOBJECT_PROPERTY_THEME	= 3;		// 会议主题
var ICS_MEETINGOBJECT_PROPERTY_PASS		= 4;		// 会议密码
var ICS_MEETINGOBJECT_PROPERTY_STARTTIME =5;		// 会议开始时间
var ICS_MEETINGOBJECT_PROPERTY_TYPE		= 6;		// 会议类型
var ICS_MEETINGOBJECT_PROPERTY_SPKMODE	= 7;		// 会议发言控制模式
var ICS_MEETINGOBJECT_PROPERTY_VIDEOCOUNT=8;		// 会议视频窗口数
var ICS_MEETINGOBJECT_PROPERTY_STATUS	= 9;		// 会议状态
var ICS_MEETINGOBJECT_PROPERTY_OWNER	= 10;		// 会议创建者ID
var ICS_MEETINGOBJECT_PROPERTY_STYLE	= 11;		// 会议界面风格

// 数据类型
var ICS_DATATYPE_ONLINEUSERS 			= 1; 		// 用户信息
var ICS_DATATYPE_MEETINGS				= 2; 		// 会议信息
var ICS_DATATYPE_FRIENDS 				= 3; 		// 好友列表
var ICS_DATATYPE_GROUPS 				= 4; 		// 用户分组
	
var ICS_STATUSTYPE_USERONLINE			= 1;		// 用户在线状态
var ICS_STATUSTYPE_MEETTYPECHG			= 50;		// 会议状态改变
var ICS_STATUSTYPE_MEETDELETE			= 51;		// 会议被删除
var ICS_STATUSTYPE_MEETSPKMODE			= 52;		// 会议发言模式改变
var ICS_STATUSTYPE_MICREFRESH			= 53;		// 会议麦序刷新



// 通信指令返回代码定义
var ICS_RETCODE_SUCCESS					= 0;		// 成功，或是正常状态
var ICS_RETCODE_SESSION_CANCEL			= 100101;	// 源用户主动放弃会话
var ICS_RETCODE_SESSION_OFFLINE			= 100102;	// 目标用户不在线
var	ICS_RETCODE_SESSION_BUSY			= 100103;	// 目标用户忙
var ICS_RETCODE_SESSION_REJECT			= 100104;	// 目标用户拒绝会话
var ICS_RETCODE_SESSION_TIMEOUT			= 100105;	// 会话请求超时
var ICS_RETCODE_FILETRANS_REJECT		= 100201;	// 目标用户拒绝接收文件
var ICS_RETCODE_FILETRANS_CANCEL		= 100202;	// 文件传输被对方取消
var ICS_RETCODE_FILETRANS_REPEAT		= 100203;	// 文件正在传输，不能重复发送
var ICS_RETCODE_FILETRANS_OPENFAIL		= 100204;	// 文件打开失败，可能被占用
var ICS_RETCODE_MEETING_PASSERR			= 100301;	// 会议密码不正确
var ICS_RETCODE_MEETING_NOTINVIT		= 100302;	// 没有被邀请
var ICS_RETCODE_MEETING_LOCKED			= 100303	// 会议处于加锁状态



/********************************************
 *				方法定义部分				*
 *******************************************/
var icloudsoft;									// iCloudSoft插件DMO对象

// 初始化SDK，返回出错代码
function ICS_InitSDK() {
	try {
		icloudsoft = anychat;
		var ANYCHATWEB_SO_ENABLEICSLOGIC = 11001; 
		anychat.SetSDKOptionInt(ANYCHATWEB_SO_ENABLEICSLOGIC, 1);
		// 关联回调事件
		if(window.ActiveXObject) {
			icloudsoft.attachEvent('OnSessionRequest', OnICloudSoftSessionRequest);
			icloudsoft.attachEvent('OnSessionStart', OnICloudSoftSessionStart);
			icloudsoft.attachEvent('OnSessionFinish', OnICloudSoftSessionFinish);
			icloudsoft.attachEvent('OnStatusNotify', OnICloudSoftStatusNotify);
			icloudsoft.attachEvent('OnRecvDataFinish', OnICloudSoftRecvDataFinish);
			icloudsoft.attachEvent('OnRecvObjectData', OnICloudSoftRecvObjectData);
			icloudsoft.attachEvent('OnFileTransRequest', OnICloudSoftFileTransRequest);
			icloudsoft.attachEvent('OnFileTransReply', OnICloudSoftFileTransReply);
			icloudsoft.attachEvent('OnFileTransStart', OnICloudSoftFileTransStart);
			icloudsoft.attachEvent('OnFileTransFinish', OnICloudSoftFileTransFinish);
		} else {
			icloudsoft.OnSessionRequest = OnICloudSoftSessionRequest;
			icloudsoft.OnSessionStart = OnICloudSoftSessionStart;
			icloudsoft.OnSessionFinish = OnICloudSoftSessionFinish;
			icloudsoft.OnStatusNotify = OnICloudSoftStatusNotify;
			icloudsoft.OnRecvDataFinish = OnICloudSoftRecvDataFinish;
			icloudsoft.OnRecvObjectData = OnICloudSoftRecvObjectData;
			icloudsoft.OnFileTransRequest = OnICloudSoftFileTransRequest;
			icloudsoft.OnFileTransReply = OnICloudSoftFileTransReply;
			icloudsoft.OnFileTransStart = OnICloudSoftFileTransStart;
			icloudsoft.OnFileTransFinish = OnICloudSoftFileTransFinish;
		}
		return GV_ERR_SUCCESS;
	}
	catch (e) {
	    return -1;
	}
}

/********************************************
 *				会话操作方法				*
 *******************************************/

// 请求会话
function ICS_SessionRequest(dwUserId, dwParam) {
	return icloudsoft.SessionRequest(dwUserId, dwParam);
}
// 开始会话
function ICS_SessionStart(dwUserId) {
	return icloudsoft.SessionStart(dwUserId);
}
// 结束会话
function ICS_SessionFinish(dwUserId, dwErrorCode) {
	return icloudsoft.SessionFinish(dwUserId, dwErrorCode);
}


/********************************************
 *				对象信息方法				*
 *******************************************/
 
// 获取对象ID列表（返回一个对象ID数组）
function ICS_GetObjectIds(dwObjectType) {
	var idarray = new Array();
	var size = icloudsoft.PrepareFetchObjectIds(dwObjectType);
	for(var i=0; i<size; i++) {
		var objectid = icloudsoft.FetchNextObjectId(dwObjectType);
		idarray[i] = objectid;
	}
	return idarray;
}

// 获取在线用户，返回一个dwUserId的数组
function ICS_GetOnlineUserIds() {
	return ICS_GetObjectIds(ICS_DATATYPE_ONLINEUSERS);
}
// 获取用户分组，返回一个groupid的数组
function ICS_GetGroupIds() {
	return ICS_GetObjectIds(ICS_DATATYPE_GROUPS);
}
// 获取会议列表，返回一个meetingid的数组
function ICS_GetMeetingIds() {
	return ICS_GetObjectIds(ICS_DATATYPE_MEETINGS);
}

// 获取对象整型参数值
function ICS_GetObjectIntValue(dwObjectType, dwObjectId, dwInfoName) {
	return icloudsoft.GetObjectIntValue(dwObjectType, dwObjectId, dwInfoName);
}
// 获取对象字符串参数值
function ICS_GetObjectStringValue(dwObjectType, dwObjectId, dwInfoName) {
	return icloudsoft.GetObjectStringValue(dwObjectType, dwObjectId, dwInfoName);
}


// 获取用户名
function ICS_GetUserName(dwUserId) {
	return ICS_GetObjectStringValue(ICS_DATATYPE_ONLINEUSERS, dwUserId, ICS_USEROBJECT_PROPERTY_NAME);
}
// 获取用户类型
function ICS_GetUserType(dwUserId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_ONLINEUSERS, dwUserId, ICS_USEROBJECT_PROPERTY_TYPE);
}
// 获取用户图像ID
function ICS_GetUserImageId(dwUserId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_ONLINEUSERS, dwUserId, ICS_USEROBJECT_PROPERTY_IMAGEID);
}
// 获取用户在线状态
function ICS_GetUserStatus(dwUserId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_ONLINEUSERS, dwUserId, ICS_USEROBJECT_PROPERTY_STATUS);
}
// 获取用户分组ID
function ICS_GetUserGroupId(dwUserId){
	return ICS_GetObjectIntValue(ICS_DATATYPE_ONLINEUSERS, dwUserId, ICS_USEROBJECT_PROPERTY_GROUPID);
}

// 获取用户分组名
function ICS_GetGroupName(dwGroupId){
	return ICS_GetObjectStringValue(ICS_DATATYPE_GROUPS, dwGroupId, ICS_GROUPOBJECT_PROPERTY_NAME);
}


// 获取会议GUID
function ICS_GetMeetingGuid(dwMeetingId) {
	return ICS_GetObjectStringValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_GUID);
}
// 获取会议名称
function ICS_GetMeetingName(dwMeetingId) {
	return ICS_GetObjectStringValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_NAME);
}
// 获取会议主题
function ICS_GetMeetingTheme(dwMeetingId) {
	return ICS_GetObjectStringValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_THEME);
}
// 获取会议开始时间
function ICS_GetMeetingStartTime(dwMeetingId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_STARTTIME);
}
// 获取会议类型
function ICS_GetMeetingType(dwMeetingId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_TYPE);
}
// 获取会议发言控制模式
function ICS_GetMeetingType(dwMeetingId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_SPKMODE);
}
// 获取会议视频窗口数
function ICS_GetMeetingType(dwMeetingId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_VIDEOCOUNT);
}
// 获取会议状态
function ICS_GetMeetingStatus(dwMeetingId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_STATUS);
}
// 获取会议创建者用户ID
function ICS_GetMeetingOwnerUserId(dwMeetingId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_OWNER);
}
// 获取会议界面风格
function ICS_GetMeetingStyle(dwMeetingId) {
	return ICS_GetObjectIntValue(ICS_DATATYPE_MEETINGS, dwMeetingId, ICS_MEETINGOBJECT_PROPERTY_STYLE);
}


/********************************************
 *				文件传输方法				*
 *******************************************/
 
// 文件传输请求
function ICS_FileTransRequest(dwUserId, szRequestGuid, szFilePathName) {
	return icloudsoft.FileTransRequest(dwUserId, szRequestGuid, szFilePathName);
}
// 文件传输请求回复
function ICS_FileTransReply(szRequestGuid, dwErrorCode) {
	return icloudsoft.FileTransReply(szRequestGuid, dwErrorCode);
}
// 文件传输另存为
function ICS_FileTransSaveAs(szRequestGuid, szSavePath) {
	return icloudsoft.FileTransSaveAs(szRequestGuid, szSavePath);
}
// 文件操作
function ICS_FileTransControl(szRequestGuid, dwCtrlType) {
	return icloudsoft.FileTransControl(szRequestGuid, dwCtrlType);
}
// 查询文件传输整形参数值
function ICS_FileTransQueryIntValue(szRequestGuid, dwInfoName) {
	return icloudsoft.FileTransQueryIntValue(szRequestGuid, dwInfoName);
}
// 查询文件传输字符串参数值
function ICS_FileTransQueryStringValue(szRequestGuid, dwInfoName) {
	return icloudsoft.FileTransQueryStringValue(szRequestGuid, dwInfoName);
}
// 查询文件传输进度（0 ~ 100）
function ICS_FileTransQueryProgress(szRequestGuid) {
	return ICS_FileTransQueryIntValue(szRequestGuid, BRAC_TRANSTASK_PROGRESS);
}
// 查询文件传输码率（bps）
function ICS_FileTransQueryBitrate(szRequestGuid) {
	return ICS_FileTransQueryIntValue(szRequestGuid, BRAC_TRANSTASK_BITRATE);
}
// 打开指定文件
function ICS_FileTransOpenFile(szRequestGuid) {
	return ICS_FileTransControl(szRequestGuid, ICS_FILETRANS_CTRLTYPE_OPENFILE);
}
// 打开文件所在目录
function ICS_FileTransOpenDirectory(szRequestGuid) {
	return ICS_FileTransControl(szRequestGuid, ICS_FILETRANS_CTRLTYPE_OPENDIR);
}
// 查询文件传输任务对应的文件名
function ICS_FileTransGetFileName(szRequestGuid) {
	return ICS_FileTransQueryStringValue(szRequestGuid, ICS_FILETRANS_PROPERTY_FILENAME);
}
// 查询文件传输任务对应的文件大小
function ICS_FileTransGetFileSize(szRequestGuid) {
	return ICS_FileTransQueryIntValue(szRequestGuid, ICS_FILETRANS_PROPERTY_FILESIZE);
}
// 查询文件传输任务发送方用户ID
function ICS_FileTransGetSendUserId(szRequestGuid) {
	return ICS_FileTransQueryIntValue(szRequestGuid, ICS_FILETRANS_PROPERTY_SRCUSERID);
}
// 查询文件传输任务接收方用户ID
function ICS_FileTransGetRecvUserId(szRequestGuid) {
	return ICS_FileTransQueryIntValue(szRequestGuid, ICS_FILETRANS_PROPERTY_TARUSERID);
}




