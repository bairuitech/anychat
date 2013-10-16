// iCloudSoft Business Logic  SDK

/********************************************
 *				事件回调部分				*
 *******************************************/

 // 根据用户ID获取其分组序号
 function GetUserGroupIdByUserId(userid) {
	var groupid = 0;
	var grouplist = BRAC_GetUserGroups();
	for(var i=0; i<grouplist.length; i++) {
		var friendlist = BRAC_GetGroupFriends(grouplist[i]);
		for(var j=0; j<friendlist.length; j++) {
			if(friendlist[j] == userid) {
				return grouplist[i];
			}
		}
	}
	return 0;
 }
 
 
// 用户会话请求
function OnICloudSoftSessionRequest(dwSrcUserId, dwTargetUserId, wParam) {
    $("#Shade_Div").show();
    $("#BeCalls_Div").show();
    $("#BeCalls_Div_Content").html("收到用户  " + BRAC_GetUserName(dwSrcUserId) + "  会话邀请<br />      是否同意?");
    mTargetUserId = dwSrcUserId;
}
// 用户会话开始
function OnICloudSoftSessionStart(dwSrcUserId, dwTargetUserId, dwRoomId) {
    mMissionQuantity = 0;
    Getdmo("ReceiveMsg").innerHTML = "";
    Getdmo("Initiative_Call_Div").style.display = "none";
    Getdmo("HallDiv").style.display = "none";
    chatuserid = dwSrcUserId;
    $("#VideoShowDiv").show();
    $("#mTargetPhoto").html("<img src='" + GetUserImageAddrById(mTargetUserId, 50) + "' alt='用户头像' style='height:65px;width:65px;' />");
    $("#mTargetInfo").html("目标的ID：" + mTargetUserId + "<br />目标名称：" + BRAC_GetUserName(mTargetUserId) + "<br />所属分组：" + BRAC_GetGroupName(GetUserGroupIdByUserId(mTargetUserId)) + "<br />");
    //    ComboboxInint();
    InitAdvanced();
    ReceiveMsgBoxScroll();
}
// 用户会话结束
function OnICloudSoftSessionFinish(dwSrcUserId, dwTargetUserId, dwErrorCode) {
    if (dwErrorCode == ICS_RETCODE_SESSION_REJECT) {
        ForSession("对方拒绝会话邀请...");
    }
    else if (dwErrorCode == ICS_RETCODE_SESSION_BUSY) {
        ForSession("用户正在会话中...");
    }
    else if (dwErrorCode == ICS_RETCODE_SESSION_CANCEL) {
        ForSession("用户取消会话邀请...");
        Getdmo("BeCalls_Div").style.display = "none";
    }
    else
        BackToHall();
}
// 状态通知
function OnICloudSoftStatusNotify(dwDataType, dwObjectId, dwStatus, wParam, lParam, sParam) {

}
// 接收数据完成
function OnICloudSoftRecvDataFinish(dwDataType, dwParam) {

}
// 收到数据
function OnICloudSoftRecvObjectData(dwDataType, dwObjectId) {
    
}
// 文件传输请求
function OnICloudSoftFileTransRequest(dwSrcUserId, szRequestGuid, dwFileSize, szFileName) {
    MessageFormat();
    MessageFlicker();
    var main_div = document.createElement("div");
    main_div.id = "Receive" + szRequestGuid;
    main_div.className = "ReceiveInform";
    main_div.setAttribute("Receiving", "false");
    main_div.setAttribute("Belong", szRequestGuid);
    main_div.innerHTML = "&nbsp&nbsp文件名:" + szFileName +
                          "<br />&nbsp&nbsp文件大小: " + UnitConversion(dwFileSize, "MB", "KB", "B", 1) + "<br />";
    Getdmo("ReceiveMsg").appendChild(main_div);

    var under_receive = document.createElement("a");
    under_receive.id = "Receive" + szRequestGuid;
    under_receive.style.marginLeft = "10px";
    under_receive.innerHTML = "接收";
    under_receive.onclick = function () {
        ICS_FileTransReply(szRequestGuid, 0) //接收回复
    }
    main_div.appendChild(under_receive);

    var under_saveAs = document.createElement("a");
    under_saveAs.id = "SaveAs" + szRequestGuid;
    under_saveAs.setAttribute("Belong", dwSrcUserId);
    under_saveAs.style.marginLeft = "5px";
    under_saveAs.innerHTML = "另存为";
    under_saveAs.onclick = function () {
        if (ICS_FileTransSaveAs(szRequestGuid, "") == 0)
            ICS_FileTransReply(szRequestGuid, 0);
    }
    main_div.appendChild(under_saveAs);

    var under_refuse = document.createElement("a");
    under_refuse.id = "Refuse" + dwSrcUserId;
    under_refuse.setAttribute("Belong", dwSrcUserId);
    under_refuse.style.marginLeft = "5px";
    under_refuse.innerHTML = "拒绝";
    under_refuse.onclick = function () {
        ICS_FileTransReply(szRequestGuid, ICS_RETCODE_FILETRANS_REJECT); //拒绝回复
        $("#Receive" + szRequestGuid).html("&nbsp&nbsp您拒绝了对方文件: " + ViewFileDetail(szRequestGuid) + " 的发送请求...");
        $("#Receive" + szRequestGuid).css("color", "#999999");
    }
    main_div.appendChild(under_refuse);
    ReceiveMsgBoxScroll();
}
// 开始传输 显示进度条层
function DisplayProgress(guid, id) {
    // 生成进度条层
    // 进度条外框
    var upper_div = document.createElement("div");
    upper_div.className = "ProgressBorder";
    Getdmo(id).appendChild(upper_div);
    // 进度颜色条
    var img = document.createElement("img");
    img.id = "TheProgress" + guid;
    img.src = "./images/dialog/Progress.png";
    img.style.width = "0px";
    img.style.marginTop = "4px";
    upper_div.appendChild(img);

    var under_div = document.createElement("div");
    under_div.style.width = "100%";
    Getdmo(id).appendChild(under_div);

    var under_div_space = document.createElement("div");
    under_div_space.className = "Bitrate" + guid;
    under_div_space.style.styleFloat = "left";
    under_div_space.style.width = "45%";
    under_div.appendChild(under_div_space);

    var under_div_cancel = document.createElement("div");
    under_div_cancel.id = "Discontinue" + guid;
    under_div_cancel.className = "CancelTransmit";
    under_div_cancel.innerHTML = "取消";
    under_div_cancel.onclick = function () {
        ICS_FileTransReply(guid, ICS_RETCODE_FILETRANS_CANCEL);
        ReplyMsgStyle(id, "您中止了文件: " + ViewFileDetail(guid) + "的发送...", true);
        ReceiveMsgBoxScroll();
    }
    under_div.appendChild(under_div_cancel);
}
// 文件传输回复
function OnICloudSoftFileTransReply(szRequestGuid, dwErrorCode) {
    if (dwErrorCode == ICS_RETCODE_FILETRANS_REJECT) { // 对方拒绝接收
        ReplyMsgStyle("SendFileMsg" + szRequestGuid, "&nbsp&nbsp对方拒绝接收文件 " + ViewFileDetail(szRequestGuid) + "...<br />&nbsp&nbsp传输失败", true);
    }
    else if (dwErrorCode == ICS_RETCODE_FILETRANS_CANCEL) { // 文件传输被取消
        if (ICS_FileTransGetSendUserId(szRequestGuid) == mTargetUserId)//判断是哪一方取消传输
            ReplyMsgStyle("Receive" + szRequestGuid, "&nbsp&nbsp对方取消了文件 " + ViewFileDetail(szRequestGuid) + " 的传输...<br />&nbsp&nbsp传输失败", true);
        else
            ReplyMsgStyle("SendFileMsg" + szRequestGuid, "&nbsp&nbsp对方中断了 " + ViewFileDetail(szRequestGuid) + " 的接收...<br />&nbsp&nbsp传输失败", true);
    }
}
// 开始文件传输
function OnICloudSoftFileTransStart(szRequestGuid) {
    mMissionQuantity++;
    if (mMissionQuantity == 1) mTransTimer = setInterval(ProgressBar, 300);
    var receiver_id = ICS_FileTransGetRecvUserId(szRequestGuid); // 发送方ID
    var sender_id = ICS_FileTransGetSendUserId(szRequestGuid); // 接收方ID
    if (sender_id == mSelfUserId) {
        ReplyMsgStyle("SendFileMsg" + szRequestGuid, "开始发送文件 " + ViewFileDetail(szRequestGuid) + "...", false);
        DisplayProgress(szRequestGuid, "SendFileMsg" + szRequestGuid);
    }
    else {
        ReplyMsgStyle("Receive" + szRequestGuid, "开始接收文件 " + ViewFileDetail(szRequestGuid) + "...", false);
        $("#Receive" + szRequestGuid).attr("Receiving", "true"); //设置所在层为正在接收状态
        DisplayProgress(szRequestGuid, "Receive" + szRequestGuid);
    }
}
// 动态改变进度条
function ProgressBar() {
    $(".Receive").each(function () {
        if ($(this).attr("Receiving") == "true") {
            $("#TheProgress" + $(this).attr("Belong")).css("width", ICS_FileTransQueryProgress($(this).attr("Belong")) * 2 + "px");
        }
    });
}
// 文件传输结束
function OnICloudSoftFileTransFinish(szRequestGuid) {
    var receiver_id = ICS_FileTransGetRecvUserId(szRequestGuid); // 发送方ID
    var sender_id = ICS_FileTransGetSendUserId(szRequestGuid); // 接收方ID
    if (sender_id == mSelfUserId) // 发送方
        OperationFile(szRequestGuid, "SendFileMsg");
    else  // 接收方
        OperationFile(szRequestGuid, "Receive");
}
// 传输完成 显示 打开文件  打开目录 按钮
function OperationFile(szRequestGuid, id) {
    Getdmo(id + szRequestGuid).innerHTML = "";
    var Result;
    if (id == "SendFileMsg") Result = ") 发送完成.<br />";
    else Result = ") 接收完成.<br />";
    var left_div = document.createElement("div");
    left_div.style.styleFloat = "left";
    left_div.style.cssFloat = "left";
    Getdmo(id + szRequestGuid).appendChild(left_div);
    var left_img = document.createElement("img");
    left_img.src = "./images/dialog/OpenFolder.png";
    left_img.style.width = "50px";
    left_img.style.height = "50px";
    left_div.appendChild(left_img);

    var right_div = document.createElement("div");
    right_div.style.fontSize = "12px";
    right_div.innerHTML = "&nbsp&nbsp文件 " + ICS_FileTransGetFileName(szRequestGuid) + "<br />&nbsp&nbsp大小 (" +
                          UnitConversion(ICS_FileTransGetFileSize(szRequestGuid), "MB", "KB", "B", 1) + Result;
    Getdmo(id + szRequestGuid).appendChild(right_div);

    var open_file = document.createElement("a");
    open_file.className = "OperateFile";
    open_file.style.marginLeft = "10px";
    open_file.innerHTML = "打开文件";
    open_file.onclick = function () {
        ICS_FileTransOpenFile(szRequestGuid);
    }
    Getdmo(id + szRequestGuid).appendChild(open_file);

    var open_path = document.createElement("a");
    open_path.className = "OperateFile";
    open_path.innerHTML = "打开目录";
    open_path.onclick = function () {
        ICS_FileTransOpenDirectory(szRequestGuid);
    }
    Getdmo(id + szRequestGuid).appendChild(open_path);
    Getdmo(id + szRequestGuid).style.height = "55px";
}

// 获取用户图像
function GetUserImageAddrById(userid, type) {
    var imageid = parseInt(BRAC_GetUserInfo(userid, 4));
    if (type == 20)
        return "./images/avatar/20/" + imageid + ".gif";
    else if (type == 30)
        return "./images/avatar/30/" + imageid + ".gif";
    else
        return "./images/avatar/50/" + imageid + ".gif";
}

//判断收到字符串中是否含有[]  获得表情
function Expression(message, type) {
    var reg = /\[(.*?)\]/gi; //判断字符[]的正则法则
    var tmp = message.match(reg); //检查收到信息中是否存在[]
    if (tmp) {//存在[]
        for (var i = 0; i < tmp.length; i++) {//循环取得每个[]
            var GetAttr = tmp[i].replace(reg, "$1"); //获取[]中的内容
            for (var j = 0; j < mExpressionArray.length; j++) {//检查[]内容是否在数组中有对应字符
                if (mExpressionArray[j].split(":")[0] == GetAttr) {//有对应字符
                    message = message.replace(tmp[i], "<img src='./images/emotion/" + mExpressionArray[j].split(":")[1] + ".gif' />"); //将符合要求的字符转换为图片进行显示
                    if (type == 0)
                        $("#SendMsg").html(message);
                    break;
                }
            }
        }
    }
    return message;
}

//会话提示信息
function ForSession(message) {
    var VHeight = document.body.clientHeight; //  (包括边线的高)
    $("#SessionPrompt_Div").css("top", "255px"); //设置提示层垂直位置
    Getdmo("Shade_Div").style.display = "none";
    Getdmo("Initiative_Call_Div").style.display = "none";
    Getdmo("SessionPrompt_Div").style.color = "White";
    Getdmo("SessionPrompt_Div").innerHTML = message;
    $("#SessionPrompt_Div").fadeTo("slow", 1);
        setTimeout("$('#SessionPrompt_Div').fadeTo('slow', 0 , BusyDivOut)", 2000);
    $("#SessionPrompt_Div").css("left", (document.body.offsetWidth - 600) / 2 + "px");
}
function BusyDivOut() {
    $("#SessionPrompt_Div").css("top", "500%");
}

// 生成分组列表界面
function UserGroupDiv(group_id, content) {
    var main_div = document.createElement("div"); // 里表中添加一个新层
    main_div.style.width = "290px";
    main_div.style.height = "35px";
    main_div.style.overflow = "hidden";
    Getdmo("GroupContent").appendChild(main_div);

    var group_div_left = document.createElement("div"); // 新层中添加左浮动框 放置用户组图标
    group_div_left.style.textAlign = "center";
    group_div_left.style.width = "85px";
    group_div_left.style.height = "27px";
    group_div_left.style.styleFloat = "left"; // IE
    group_div_left.style.cssFloat = "left"; // firefox
    main_div.appendChild(group_div_left);

    var left_image = document.createElement("img"); // 左边 用户组图标
    left_image.className = "GroupImg";
    if (group_id == 0) left_image.src = "./images/Hall/1.png";
    else left_image.src = "./images/Hall/2.png";
    group_div_left.appendChild(left_image);

    var group_div_right = document.createElement("div"); // 新层中添加右浮动框 放置用户组名称
    if (group_id == 0) group_div_right.id = "Group0";
    else group_div_right.id = "Group" + group_id;
    group_div_right.className = "OnLineUserRow";
    group_div_right.onclick = function () {
        OpenGroup(group_id);
    }
    group_div_right.style.width = "127px";
    group_div_right.style.height = "27px";
    group_div_right.style.styleFloat = "left"; // IE
    group_div_right.style.cssFloat = "left"; // firefox
    group_div_right.innerHTML = content;
    main_div.appendChild(group_div_right);
}


//创建在线好友图标
function CreateUserImage(type) {
    Getdmo("UserListContent").innerHTML = "";
    var OnLineUserList = BRAC_GetUserFriends(); // 获取所有好友
    if (type == "whole") { // 所有在线用户
        DisplayOnLineUser(mSelfUserId); // 在第一个位置创建自己的图标
        for (var i = 0; i < OnLineUserList.length; i++) {
            if (OnLineUserList[i] != mSelfUserId && BRAC_GetFriendStatus(OnLineUserList[i]) != 0)	// 只显示在线用户
                DisplayOnLineUser(OnLineUserList[i]);
        }
    }
    else { // 指定用户组在线用户
        for (var i = 0; i < OnLineUserList.length; i++) {
            var UserGroupID = GetUserGroupIdByUserId(OnLineUserList[i]);
            if (UserGroupID == mCurrentGroupNum && BRAC_GetFriendStatus(OnLineUserList[i]) != 0)	// 只显示在线用户
                DisplayOnLineUser(OnLineUserList[i]);
        }
    }
    StartScroll("UserListScroll", "UserListSlider", "UserListContent", "UserListBaseLine");
}
//显示上线用户
function DisplayOnLineUser(userid) {
    var UserName = BRAC_GetUserName(userid); // 用户姓名
    var main_div = document.createElement("div");
    main_div.id = "UserID_" + userid;
    main_div.className = "OnLineUser_Div";

    var left_div = document.createElement("div");
    left_div.className = "UserImg";
    main_div.appendChild(left_div);

    var left_img = document.createElement("img");
    left_img.id = userid;
    left_img.src = GetUserImageAddrById(userid, 30);
    left_img.onclick = function () { ImgDBclick(userid); }
    left_img.className = "User";
    left_div.appendChild(left_img);

    var right_div = document.createElement("div");
    right_div.className = "UserMsg";
    main_div.appendChild(right_div);

    var right_a = document.createElement("a");
    right_a.className = "UserNameMsg";
    right_a.innerHTML = UserName;
    right_div.appendChild(right_a);

    Getdmo("UserListContent").appendChild(main_div);
}
//用户分组栏
function OpenGroup(GroupID) {
    for (var j = 0; j < mGroupList.length; j++) {//设置所有组按钮为未选中状态
        Getdmo("Group" + mGroupList[j]).style.background = "url(./images/Hall/05.png)"; //添加背景图片
        Getdmo("Group" + mGroupList[j]).style.width = "127px";
    }
    Getdmo("Group0").style.background = "url(./images/Hall/05.png)"; //添加背景图片
    Getdmo("Group0").style.width = "127px";
    if (GroupID == 0) {//根据传过来的GroupID设置该组为选中状态
        Getdmo("Group0").style.background = "url(./images/Hall/03.png)";
        Getdmo("Group0").style.width = "165px";
    }
    else {
        Getdmo("Group" + GroupID).style.background = "url(./images/Hall/03.png)";  //根据传过来的GroupID设置该组为选中状态
        Getdmo("Group" + GroupID).style.width = "165px";
    }
    mCurrentGroupNum = GroupID; //设置当前选中组为全局变量  后边需要用到当前选中组ID
    if (GroupID == 0) {//在线用户  全部人
        CreateUserImage("whole");
    }
    else {
        CreateUserImage("appoint");
    }
}