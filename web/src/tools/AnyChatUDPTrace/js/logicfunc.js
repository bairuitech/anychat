// AnyChat for Web SDK
/**
 *@demoVersion 1.0
 *@editor Z.Yanni
 *@timeByFin 2014.12.30
 *@partByEdit 
 */
/*******************************************************************************
 * 业务逻辑控制 *
 ******************************************************************************/
 
var mDefaultServerAddr = "demo.anychat.cn";		// 默认服务器地址
var mDefaultServerPort = 8906;					// 默认服务器端口号
var mSelfUserId = -1; 							// 本地用户ID
var mTargetUserId = -1;							// 目标用户ID（请求了对方的音视频）
var roomID=5;
var mUserName="AnyChat"
var mRefreshPluginTimer = -1;					// 检查插件是否安装完成定时器
var y=0,x=5,t=1,symbol=true,isSend=-1,timeSet,tipAlert=true;//动态控制标识

var o=[">",">",">",">",">",">"];
var o2=["<","<","<","<","<","<"];
var isNeedAppID = false;       					//是否需要AppGuid
var mDefaultAppID = "fbe957d1-c25a-4992-9e75-d993294a5d56";  //默认演示应用AppID

var controller=function(op){
	isSend=op;
	if(isSend){timeSet=setInterval(function() {
	var send=BRAC_GetSDKOptionInt(166),recv=BRAC_GetSDKOptionInt(164),serverGet=BRAC_GetSDKOptionInt(165);
    var per=myRound(((send-recv)/send)*100,2);
    per=((per==false)||(per<0))?"0.00%":per+"%"
    		
    GetID("local_send").innerHTML=send;
    GetID("local_recv").innerHTML=recv;
    GetID("lostPercent").innerHTML=per;
    
    GetID("server_recv").innerHTML=serverGet;
    //GetID("server_send").innerHTML=recv;

    //GetID("remote_server").innerHTML=serverSend;
    GetID("remote_recv").innerHTML=recv;
    GetID("remote_percent").innerHTML=per;
    
   if(y < o.length) {//这里的P++除去后卡死
    	GetID("serverImg").setAttribute("class", "server"+t);
    	t++;
    	if(t==4){t=1}
			o.splice(y,1,"<span>></span>");
			GetID("u1_send").innerHTML=o[0]+o[1]+o[2]+o[3]+o[4]+o[5];
			GetID("server_sendtoU2").innerHTML=o[0]+o[1]+o[2]+o[3]+o[4]+o[5];
			o.splice(y,1,">");
			
			o2.splice(x,1,"<span><</span>");
			GetID("server_sendtoU1").innerHTML=o2[0]+o2[1]+o2[2]+o2[3]+o2[4]+o2[5];
			o2.splice(x,1,"<");
			x--;
			if(x<0){x=5;}
			y++;
			if(y==6){y=0;}
	}
    
}, 1000);}
	else if(isSend!=-1&&isSend==false){
		clearInterval(timeSet);
	}	
};

function LogicInit() {
	 //获取浏览器信息，并匹配Edge浏览器
    var ua = window.navigator.userAgent.toLowerCase();
    var info = {
        edge: /edge/.test(ua)
    };
    if(info.edge) {
       AddEdgePage();
    } else {
	    setTimeout(function () {
			if (navigator.plugins && navigator.plugins.length) {
				window.navigator.plugins.refresh(false);
			}
	        // 检查是否安装了插件
	        var NEED_ANYCHAT_APILEVEL = "0"; 						// 定义业务层需要的AnyChat
																	// API Level
	        var errorcode = BRAC_InitSDK(NEED_ANYCHAT_APILEVEL); 	// 初始化插件
	        if (errorcode == GV_ERR_SUCCESS) {
				
				if(mRefreshPluginTimer != -1)
					clearInterval(mRefreshPluginTimer); 			// 清除插件安装检测定时器
				GetID("prompt_div").style.display = "none"; 		// 隐藏插件安装提示界面
				ShowLoginDiv(true);
				// 初始化界面元素
				InitInterfaceUI();

	        } else { 						// 没有安装插件，或是插件版本太旧，显示插件下载界面
	            GetID("prompt_div").style.display = "block";
	            if (errorcode == GV_ERR_PLUGINNOINSTALL)
	                GetID("prompt_div_line1").innerHTML = "首次进入需要安装插件，请点击下载按钮进行安装！";
	            else if (errorcode == GV_ERR_PLUGINOLDVERSION)
	                GetID("prompt_div_line1").innerHTML = "检测到当前插件的版本过低，请下载安装最新版本！";
					
				if(mRefreshPluginTimer == -1) {
					mRefreshPluginTimer = setInterval(function(){ LogicInit(); }, 1000);
				}
			}
	    }, 500);
    }

}

//加载Edge浏览器下的判断页面样式
function AddEdgePage() {
    var iframeField = document.createElement('iframe');
    iframeField.src = './html/needie.html';
    iframeField.scrolling = "no";
    iframeField.frameborder = "0";
    iframeField.width = "100%";
    iframeField.height = "800px";
    document.body.style.backgroundColor = "#fff";
    document.body.appendChild(iframeField);
}

//设置AnyChat参数，需要在收到登录成功回调之后调用
function ConfigAnyChatParameter(){
	
}

// 初始化界面元素
function InitInterfaceUI() {	
	//是否显示登录页面的应用ID的输入框
	if(!isNeedAppID){
		GetID("AppIDDiv").style.display = "none";
	}else{

	}
	
    // 下载插件按钮鼠标划入划出时间
    GetID("prompt_div_btn_load").onmouseover = function () {
        GetID("prompt_div_btn_load").style.backgroundColor = "#ffc200";
    }
    GetID("prompt_div_btn_load").onmouseout = function () {
        GetID("prompt_div_btn_load").style.backgroundColor = "#ff8100";
    }
    // 下载插件界面关闭按钮
    GetID("prompt_div_headline2").onclick = function () {
        document.URL = location.href;
    }

    
  // 登录AnyChat服务器
    GetID("loginRoom").onclick = function () {
        setLoginInfo();
        if (isNeedAppID){
			if (GetID("AppID") && GetID("AppID").value.length)				// 设置应用ID
	            BRAC_SetSDKOption(BRAC_SO_CLOUD_APPGUID, GetID("AppID").value.toString());        	
        }
    	if(GetID("sendRadio").checked){
    		GetID("server_sendtoU2").style.display="none";
    		GetID("otherUser").style.display="none";
    		GetID("UDP_control").style.display="block";
    		
    		GetID("username").value="发送方";
    		}else if(GetID("reciveRadio").checked){
    		GetID("username").value="接收方";
    		}else if(!GetID("sendRadio").checked&&!GetID("reciveRadio").checked){
    			alert("您需要先选择发送方或者接收方");
    			return
    		}
		
    		if (GetID("username").value != "") {
				DisplayLoadingDiv(true);
				mDefaultServerAddr=GetID("ServerAddr").value;
				mDefaultServerPort=parseInt(GetID("ServerPort").value);
	    		var errorcode = BRAC_Connect(GetID("ServerAddr").value, parseInt(GetID("ServerPort").value)); // 连接服务器
	            errorcode = BRAC_Login(GetID("username").value, "", 0);
	    		
	    	}else{
	    		alert("用户名不能为空！");
	    		GetID("username").focus();
	    	}
    	
    }

    //开始测试按钮
    GetID("uploadKbps").value = "100";
	GetID("uploadStart").onclick = function () {
		if(tipAlert){
		if(symbol){controller(true);}
		symbol=false;
		var iSendBitrate = parseInt(GetID("uploadKbps").value);
		BRAC_SetSDKOption(161, 1000);
		BRAC_SetSDKOption(162, iSendBitrate*1000);
		BRAC_SetSDKOption(163, 1);	
		tipAlert=!tipAlert;
		}else{
			alert("请先停止测试！");
		}
	}
    //停止测试按钮
	GetID("uploadStop").onclick = function () {
		BRAC_SetSDKOption(163, 0);
		controller(false);
		tipAlert=true;
		symbol=true;
//		GetID("local_send").innerHTML="0";
//		GetID("local_recv").innerHTML="0";
//		GetID("lostPercent").innerHTML="0.00%";
//		GetID("server_recv").innerHTML="0";
	}
	GetID("close").onclick = function () {
		BRAC_Logout();
		controller(false);
		tipAlert=true;
		symbol=true;
		GetID("main_box").style.display="none";
				GetID("login_div").style.display="block";
		GetID("local_send").innerHTML="0";
		GetID("local_recv").innerHTML="0";
		GetID("lostPercent").innerHTML="0.00%";
		GetID("server_recv").innerHTML="0";
	}
	
    getLoginInfo();	
}

// 显示等待进度条，提示用户操作正在进行中
function DisplayLoadingDiv(bShow) {
    if (bShow) {
    	displayList("LOADING_GREY_DIV,LOADING_DIV","block");
        var TheWidth = document.body.offsetWidth;
        GetID("LOADING_DIV").style.marginTop = "250px";
        GetID("LOADING_DIV").style.marginLeft = (TheWidth - 130) / 2 + "px";
    }
    else {
    	displayList("LOADING_DIV,LOADING_GREY_DIV","none");
    }
}


// 显示登录界面
function ShowLoginDiv(bShow) {
	if(bShow) {
		GetID("login_div").style.display="block"; 	// 显示登录界面
		GetID("username").focus();
		GetID("ServerAddr").value = mDefaultServerAddr;
		GetID("ServerPort").value = mDefaultServerPort;
		GetID("roomID").value = roomID;
		GetID("username").value= mUserName;
	} else {
		GetID("login_div").style.display="none";	// 隐藏登录界面
	}
}

// 显示UDP界面
function ShowUDPBox(bShow) {
	if(bShow) {
		GetID("main_box").style.display="block";
	}else {
		GetID("main_box").style.display="none";
	}
}

function GetID(id) {
	if (document.getElementById) {
		return document.getElementById(id);
	} else if (window[id]) {
		return window[id];
	}
	return null;
}

function loginBtn(i){
	if(i==0){
		GetID("loginRoom").style.backgroundColor = "#ABCB64";
	}else{
		GetID("loginRoom").style.backgroundColor=  "#7CAF00";
	}
}

function displayList(list,type){
	var list=list.split(",");
	for (var i = 0; i < list.length; i++) {
		GetID(list[i]).style.display=type;
	}
}

function myRound(floatvar, position) {
    var f_x = parseFloat(floatvar);
    if (isNaN(f_x)) {
        return false;
    }
    var f_x = Math.round(floatvar*100)/100;
    var s_x = f_x.toString();
    var pos_decimal = s_x.indexOf('.');
    if (pos_decimal < 0) {
        pos_decimal = s_x.length;
        s_x += '.';
    }
    while (s_x.length <= pos_decimal + position) {
        s_x += '0';
    }
    return s_x;
}

function getIp(ip,id){
	GetID("getIp").innerHTML="";
    var script=document.createElement('script');
    script.setAttribute('type','text/javascript');
    script.setAttribute('src','http://int.dpool.sina.com.cn/iplookup/iplookup.php?format=js&ip='+ip);
    GetID("getIp").appendChild(script);
    
    setTimeout(function() {
    	try{
    		GetID(id).innerHTML=remote_ip_info.country+" "+remote_ip_info.province+" "+remote_ip_info.city+" "+remote_ip_info.isp;
    	}catch(e){
    		console.log("getIp function has exception：" + e);
    		
    	}
		
	}, 1000); 
}

//设置登录信息，包括用户名、服务器IP、服务器端口、应用ID
function setLoginInfo() {
    setCookie('username', GetID("username").value, 30);
    setCookie('ServerAddr', GetID("ServerAddr").value, 30);
    setCookie('ServerPort', GetID("ServerPort").value, 30); 
    setCookie('roomID', GetID("roomID").value, 30); 
    
    if (isNeedAppID){
		setCookie('AppID', GetID("AppID").value, 30);
    }    
}

//获取登录信息
function getLoginInfo() {
    GetID("username").value = getCookie("username");
    var serverIP = getCookie("ServerAddr");
	GetID("ServerAddr").value = (serverIP != "") ? serverIP : mDefaultServerAddr;        
    var serverPort = getCookie("ServerPort");
	GetID("ServerPort").value = (serverPort != "") ? serverPort : mDefaultServerPort;
	var roomID = getCookie("roomID");
	GetID("roomID").value = (roomID != "") ? roomID : 5;
    if (isNeedAppID){
	    var appID = getCookie("AppID");
	    GetID("AppID").value = ((appID != "") ? appID : mDefaultAppID);    	
    }         
}

//获取cookie项的cookie值
function getCookie(c_name) {
    if (document.cookie.length > 0) {
        c_start = document.cookie.indexOf(c_name + "=");
        if (c_start != -1) {
            c_start = c_start + c_name.length + 1;
            c_end = document.cookie.indexOf(";", c_start);
            if (c_end == -1) c_end = document.cookie.length;
            return document.cookie.substring(c_start, c_end);
        }
    }
    return "";
}

//设置cookie
function setCookie(c_name, value, expiredays) {
    var exdate = new Date();
    exdate.setDate(exdate.getDate() + expiredays);
    document.cookie = c_name + "=" + value + ((expiredays == null) ? "" : ";expires=" + exdate.toGMTString());
}

