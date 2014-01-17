// JavaScript Document
var mSelfUserId = -1; 							// 本地用户ID
var mTargetUserId = 0;							// 目标用户ID（请求了对方的音视频）

var USER_ONLINE_STATUS=1;//用户上线
var USER_OFFLINE_STATUS=0;//用户下线

var USERINFO_NAME=1;//用户昵称讯息
var USERINFO_IP=2;//用户IP地址讯息
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
    var UserName = BRAC_GetUserInfo(userid,USERINFO_NAME); // 用户姓名
	var UserIp=BRAC_GetUserInfo(userid,USERINFO_IP); // 用户IP地址;
    var main_div = document.createElement("div");
    main_div.id = "UserID_" + userid;
    main_div.className = "OnLineUser_Div";

    var left_div = document.createElement("div");
    left_div.className = "UserImg_Holder";
    main_div.appendChild(left_div);

    var left_img = document.createElement("img");
    left_img.id = userid;
	var img_value=Math.abs(userid)%10;
    left_img.src = "./images/head/"+img_value+".gif";
    left_img.className = "UserImg";
    left_div.appendChild(left_img);

    var right_div = document.createElement("div");
    right_div.className = "UserInfo_Holder";
    main_div.appendChild(right_div);

    var right_name= document.createElement("div");
    right_name.className = "UserInfo";
    right_name.innerHTML = UserName;
    right_div.appendChild(right_name);
	
	var right_ip = document.createElement("div");
    right_ip.className = "UserInfo";
    right_ip.innerHTML = UserIp;
    right_div.appendChild(right_ip);
	
	var right_userId= document.createElement("div");
    right_userId.className = "UserInfo";
    right_userId.innerHTML = userid;
    right_div.appendChild(right_userId);
    
	   //下载插件按钮鼠标划入划出时间
    main_div.onmouseover = function () {
       main_div.style.backgroundColor = "#8FBC8B";
    }
    main_div.onmouseout = function () {
       main_div.style.backgroundColor = "#FAFADD";
    }
	main_div.onclick=function () { VideoCallRequest(userid); }
    Getdmo("UserListContent").appendChild(main_div);
}

//清楚离线用户
function removeOfflineUser(dwUserId)
{
	Getdmo("UserListContent").removeChild(Getdmo("UserID_" + dwUserId));
}