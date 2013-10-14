var mSelfUserName = ""; //账号
var mSelfPassWord = ""; //密码
var mTargetUserId = "";//视频会话 对方ID
var mSelfUserId; //获得自己的ID
var mRefreshVolumeTimer; // 实时音量大小定时器
var mCurrentGroupNum = 0; //获得当前选中的用户分组ID
var mGroupList = new Array(); //分组信息列表
var mTransTimer; // 定时器
var mMissionQuantity;  // 文件传输任务数量
var mFlickerNews; // 新信息闪烁提示
var mWhetherMainForm = false;

function Getdmo(element) {
    if (document.getElementById) {
        return document.getElementById(element);
    } else if (window[element]) {
        return window[element];
    }
    return null;
}
$(document).ready(function () {
    $(document).keydown(function (event) {//按下Tab键  不做任何动作
        if (event.keyCode == 9) return false;
    });
    $("#mDefaultServerAddr").attr("value", mDefaultServerAddr);
    $("#mDefaultServerPort").attr("value", mDefaultServerPort);
    // 搜索栏按钮事件
    $("#mSearchTarget").keyup(function (event) {
        Getdmo("UserListContent").innerHTML = "";
        var lower = $(this).val();
        BtnSearch(lower.toLocaleLowerCase());
    });
});
//禁用Textarea回车键换行功能   使用发送信息快捷键时才不会自动换行
function NewLine(event) {
    event = event || window.event;
    if (event.keyCode == 13) {
        event.returnValue = false; return false;
    }
}
// 页面加载完成执行函数
function LogicInit() {
    setTimeout(function () {
        //检查是否安装了插件	
        var NEED_ANYCHAT_APILEVEL = "8"; 					// 定义业务层需要的AnyChat API Level
        var errorcode = BRAC_InitSDK(NEED_ANYCHAT_APILEVEL); 	//初始化插件
        if (errorcode == GV_ERR_SUCCESS)
			$("#BodyDIV").show();
        else
			$("#prompt_div").show(); // 没有安装插件，或是插件版本太旧，显示插件下载界面
    }, 500);
    var VHeight = document.body.offsetHeight; //  (包括边线的宽)
    var VWidth = document.body.offsetWidth; //  (包括边线的宽)
    var Cookies = document.cookie;
    var GetInfos = Cookies.split("Getdmo");
    if (GetInfos.length > 3) { // 获得上次登录信息
        $("#txtUserName").attr("value", GetInfos[0]); // 用户
        $("#txtPassWord").attr("value", GetInfos[1]); // 密码
        mDefaultServerAddr = GetInfos[2]; // 地址
    }
    document.body.style.backgroundColor = "#FFFFFF";
}
//初始化所有界面位置 和 下拉框的值
function initialize() {
    var mBrowserWidth = document.body.offsetWidth; // 网页可见区域宽
    var mBrowserHeight = document.documentElement.clientHeight; //  网页可见区域高
    CenterPosition(mBrowserWidth, mBrowserHeight, "Initiative_Call_Div", 300, 170); //主动呼叫层垂直水平居中
    CenterPosition(mBrowserWidth, mBrowserHeight, "BeCalls_Div", 300, 170); //被呼叫层垂直水平居中
    CenterPosition(mBrowserWidth, mBrowserHeight, "InquityEnd", 300, 170); //结束会话询问层垂直水平居中
    CenterPosition(mBrowserWidth, mBrowserHeight, "HallDiv", 770, 650); //结束会话询问层垂直水平居中
    if (mBrowserHeight < 650) $("#HallDiv").css("top", "0px");
    Getdmo("fontfamily").options.length = 0; // 填充字体下拉框
    for (var i = 0; i < mFontsArray.length; i++) {
        var option = document.createElement("option");
        Getdmo("fontfamily").appendChild(option);
        option.value = i;
        option.text = mFontsArray[i];
    }
    Getdmo("fontsize").options.length = 0; // 填充字体大小下拉框
    for (var sizes = 8; sizes < 23; sizes++) {
        var option = document.createElement("option");
        Getdmo("fontsize").appendChild(option);
        option.value = sizes - 8;
        option.text = sizes;
    }
}
//登录按钮
function LoginToHall() {
    var the_date = new Date("December 31, 2020");
    var expiresDate = the_date.toGMTString(); //转换成 GMT 格式。
    mSelfUserName = Getdmo('txtUserName').value;
    mSelfPassWord = Getdmo('txtPassWord').value;
    if (mSelfUserName != "" && mSelfPassWord != "") {
        prompt("正在连接...<br /><img src='./images/Others/LoadImg.gif' style='width:145px;height:30px' />");
        BRAC_Connect(Getdmo('mDefaultServerAddr').value, parseInt(Getdmo('mDefaultServerPort').value));
        BRAC_Login(mSelfUserName, mSelfPassWord, 0);
        document.cookie = mSelfUserName + "Getdmo" + mSelfPassWord + "Getdmo" + mDefaultServerAddr + "Getdmo; expires=" + expiresDate; //写入Cookie 设置过期时间
    }
    else prompt("<div style='color:red;'>账号密码不能为空.</div>");
}
// 登录提示信息
function prompt(message) {
    Getdmo("prompt_box_div").innerHTML = message;
    Getdmo("prompt_box_div").style.display = "block";
}
//设置服务器IP
function DisplaySettingDiv() {
    $("#mUser_Info_Div").hide();
    $("#mServer_Info_Div").show();
}
//保存设置 按钮
function SaveServerInfo() {
    mDefaultServerAddr = $("#mDefaultServerAddr").val();
    mDefaultServerPort = $("#mDefaultServerPort").val();
    $("#mServer_Info_Div").hide();
    $("#mUser_Info_Div").show();
}
//呼叫用户双击
function ImgDBclick(ID) {
    if (mSelfUserId == ID) ForSession("不能呼叫自己...");
    else {
        mTargetUserId = ID;
		BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REQUEST,mTargetUserId,0,0,0,"");  // 向指定的用户发送会话邀请
		var GetUserName = BRAC_GetUserName(mTargetUserId);
        GetUserName = GetUserName.fontcolor("Red");
        Getdmo("Initiative_Call_Div_Content").innerHTML = "向用户" + GetUserName + "发起邀请<br /><img src='./images/Others/LoadImg.gif' style='width: 145px;height:30px;' />";
        Getdmo("Shade_Div").style.display = "block";
        Getdmo("Initiative_Call_Div").style.display = "block";
    }
}
//取消主动呼叫
function CancelCall() {
    $("#Shade_Div").hide();
    $("#Initiative_Call_Div").hide();
	BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REPLY,mTargetUserId,ICS_RETCODE_SESSION_CANCEL,0,0,"");  
    ForSession("取消呼叫...");
}
//同意会话
function OnAcceptRequestBtnClick() {
	BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REPLY,mTargetUserId,0,0,0,"");  
    $("#BeCalls_Div").hide();
}
//拒绝会话
function OnRejectRequestBtnClick() {
	BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REPLY,mTargetUserId,ICS_RETCODE_SESSION_REJECT,0,0,"");  
    $("#Shade_Div").hide();
    $("#BeCalls_Div").hide();
    ForSession("拒绝对方请求...");
}
//好友搜索按钮
function BtnSearch(Values){
    var re = /^[1-9]+[0-9]*]*$/;   //判断是否纯数字
    var UserList = BRAC_GetUserFriends(); // 获取所有在线用户
	var SearchResult = false;
	if (!re.test(Values)) {//不是纯数字  则根据用户名
	    for (var i = 0; i < UserList.length; i++) {
	        var UserName = BRAC_GetUserName(UserList[i]);
	        UserName = UserName.toLocaleLowerCase();
	        if (UserName.indexOf(Values) > -1) {
	            DisplayResult(i);
	            SearchResult = true;
	        }
	    }
	}
	else {//根据ID
	    for (var i = 0; i < UserList.length; i++) {
	        if (UserList[i] == (Values)) {
	            DisplayResult(i);
	            SearchResult = true;
	            //break;
	        }
	    }
	}
	if (!SearchResult) {//查找不到
	    DisplayResult("NotFound");
	}
}
//显示搜索结果
function DisplayResult(No) {
    Getdmo("Group0").style.background = "url(./images/hall/05.png)"; // 所有用户组不被选中
    Getdmo("Group0").style.width = "127px"; // 所有用户组宽度
    for (var j = 0; j < mGroupList.length; j++) { // 其他所有组不被选中 
        Getdmo("Group" + mGroupList[j]).style.background = "url(./images/hall/05.png)";
        Getdmo("Group" + mGroupList[j]).style.width = "127px";
    }
    if (No != "NotFound") { // 有相符结果
        var UserList = BRAC_GetUserFriends(); // 获取所有在线用户
        DisplayOnLineUser(UserList[No]); // 显示符合条件的在线用户
    }
}
// DIV层垂直居中和水平居中  浏览器可视区域宽度  浏览器可视区域高度  DIV层ID DIV层的高度 DIV层的宽度
function CenterPosition(VWidth, VHeight, DivID, DivWidth, DivHeight) {
    $("#" + DivID).css("left", (VWidth - DivWidth) / 2 + "px"); // 设置X坐标
    $("#" + DivID).css("top", (VHeight - DivHeight) / 2 + "px"); // 设置Y坐标
}
// 开始视频会话第一界面 宽屏视频
function CreateWideScreen() {
    //网页可见区域宽：
    var VWidth = document.body.offsetWidth; // (包括边线的宽) 
    //网页可见区域高：
    var VHeight = document.body.offsetHeight; //  (包括边线的高)
    CenterPosition(VWidth, 730, "VideoShowDiv", 1020, 450);
    VideoContainer(); // 动态生成宽屏视频容器
    ChangeVideoShow("videoshow2", "videoshow1", "Video_Show_MySelf", "Video_Show_Target");
}
//分组栏和好友栏滚动条
function StartScroll(BackGround, Scroll, Content, Line) {
    var scrollheight = document.getElementById(Content).scrollHeight; // 列表实际高度
    var offsetheight = document.getElementById(Content).offsetHeight; // 列表可见高度
    var back = document.getElementById(BackGround); // 滚动条背景层
    var line = document.getElementById(Line);
    var ScrollSlid = document.getElementById(Scroll); // 滑块层
    var backgroundheight = back.offsetHeight; // 滚动条背景层高度
    if (scrollheight > offsetheight) { // 判断是否需要显示滚动条
        ScrollSlid.style.display = "block";
        line.style.display = "block";
        ScrollSlid.onmousedown = function () {
            ScrollSlid.onmousemove = function () {
                ScrollSlid.setCapture();
                if (event.clientY - 150 < backgroundheight && event.clientY > 170) {
                    ScrollSlid.style.marginTop = event.clientY - 170 + "px";
                    document.getElementById(Content).scrollTop = (event.clientY - 170) * ((scrollheight - offsetheight) / 460);
                }
            }
        }
        ScrollSlid.onmouseup = function () {
            ScrollSlid.onmousemove = "";
            ScrollSlid.releaseCapture();
        }
    }
    else {
        ScrollSlid.style.display = "none";
        line.style.display = "none";
    }
}

// 显示大厅
function GoToHall() {
    $("#BodyDIV").hide(); // 隐藏登录界面
    $("#HallDiv").show(); // 显示大厅界面
    $("#LoginHead").hide(); // 隐藏顶部背景层
}

// 返回登录界面
function GoToLogin() {
	ForSession("网络连接已断开..."); // 提示层
	// 隐藏所有界面
	$("HallDiv").hide(); // 隐藏大厅
    $("DialogueDiv").hide(); // 隐藏会话层
    $("Shade_Div").hide(); // 隐藏遮罩层
    $("DivColor").hide(); // 隐藏颜色层
    $("GetExpression").hide(); // 隐藏表情层
    $("advanceset_div").hide(); // 隐藏高级设置层
	
	Getdmo("GroupContent").innerHTML = "";
	Getdmo("mSelfInfo").innerHTML = "";
	Getdmo("UserListContent").innerHTML = "";
	
	// 显示登录界面
	$("BodyDIV").show();
	$("#LoginHead").show();
	LogicInit();
}

// 结束会话返回大厅
function BackToHall() {
	BRAC_LeaveRoom(-1);
    Getdmo("HallDiv").style.display = "block"; // 显示大厅
    Getdmo("DialogueDiv").style.display = "none"; // 隐藏会话层
    Getdmo("Shade_Div").style.display = "none"; // 隐藏遮罩层
    Getdmo("DivColor").style.display = "none"; // 隐藏颜色层
    Getdmo("GetExpression").style.display = "none"; // 隐藏表情层
    Getdmo("advanceset_div").style.display = "none"; // 隐藏高级设置层
    $("#SendMsg").html(""); // 清空发送信息框内容
    $("#Enquire_Div").hide(); // 隐藏结束会话询问框
    $("#VideoShowDiv").hide(); // 隐藏宽频层
    ForSession("会话结束..."); // 提示层
    clearInterval(mRefreshVolumeTimer); // 关闭语音音量显示
}
//闪烁提示
function MessageFlicker() {
    var GetImg = true; // 图片显示
    if (!mWhetherMainForm) { // 显示界面为宽频层
        mFlickerNews = setInterval(function () {
            if (GetImg) {
                $("#SwappingDiv").css("background-image", "url('./images/dialog/flicker.png')");
                GetImg = false;
            }
            else {
                $("#SwappingDiv").css("background-image", "url('./images/dialog/btntrue_move.png')");
                GetImg = true;
            }
        }, 500);
    }
}
// 文件传输信息回复显示
function ReplyMsgStyle(id, Msg, type) {
    Getdmo(id).innerHTML = Msg;
    if (type) // 单行信息的高度
        $("#" + id).css({ "color": "#999999", "height": "35px", "font-size": "12px" });
    else // 多行信息时的高度
        $("#" + id).css({ "color": "#999999", "height": "65px", "font-size": "12px" });
}