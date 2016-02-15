$(document).ready(function () {
    // 检测发送框输入信息高度是否需要显示滚动条
    $("#SendMsg").keyup(function (event) {
        var ImportText = Getdmo("SendMsg");
        var VisiblHeight = ImportText.offsetHeight; // 发送框可见高度
        var ActualHeight = ImportText.scrollHeight; // 发送框滚动条高度
        if (ActualHeight > VisiblHeight) { // 滚动条高度高于可见高度
            Getdmo("SendMsg").style.overflowY = "scroll"; // 显示滚动条
            Getdmo("SendMsg").scrollTop = Getdmo("SendMsg").scrollHeight; // 滚动条自动到底
        }
        else Getdmo("SendMsg").style.overflowY = "hidden"; // 可见高度小于滚动条高度 滚动条隐藏
        var message = $("#SendMsg").html();
        Expression(message, 0); // 检查发送框是否有表情  有就显示表情图片
    });
    // 回车键发送消息
    $("#SendMsg").keypress(function (event) {
        if (event.keyCode == 13) {
            if ($("#SendMsg").html() == "") return false; // 发送内容为空  不作任何动作
            SendMessage(); // 发送信息
            $("#SendMsg").html(""); // 清空发送框
        }
    });
    // 显示高级设置界面
    $("#AdvanceBtn").click(function () {
        $("#advanceset_div").toggle(); // 高级设置界面显隐
    });
    // 本地视频 远程视频 切换
    $("#RightSide_MiddleButton img:last").click(function () {
        if ($("#RightSide_MiddleButton a").attr("longrange") == "true") { // 大视频框为远程视频
            ChangeVideoShow("Video_Show_Target", "Video_Show_MySelf", "Video_Show_Target", "Video_Show_MySelf"); // 大视频框设置为本地视频
            $("#DialogueDiv_RightSide a:first").html("本地视频"); // 对应文字提示
            $("#DialogueDiv_RightSide a:last").html("远程视频"); // 对应文字提示
            $("#RightSide_MiddleButton a").attr("longrange", "false"); // 标识大视频框为本地视频
        }
        else {
            ChangeVideoShow("Video_Show_MySelf", "Video_Show_Target", "Video_Show_Target", "Video_Show_MySelf"); // 大视频框设置为远程视频
            $("#DialogueDiv_RightSide a:first").html("远程视频"); // 对应文字提示
            $("#DialogueDiv_RightSide a:last").html("本地视频"); // 对应文字提示
            $("#RightSide_MiddleButton a").attr("longrange", "true"); // 标识大视频框为远程视频
        }
    });
    // 大视频框 开关按钮
    $("#RightSide_MiddleButton img:first").click(function () {
        if ($("#RightSide_MiddleButton a:first").attr("longrange") == "true") // 大视频框为远程视频
            OperateVideo("#RightSide_MiddleButton img:first", mTargetUserId); // 大按钮操作目标ID视频
        else // 大视频框为本地视频
            OperateVideo("#RightSide_MiddleButton img:first", mSelfUserId); // 大按钮操作本地ID视频
    });
    // 小视频框 开关按钮
    $("#DialogueDiv_RightSide img:last").click(function () {
        if ($("#RightSide_MiddleButton a:first").attr("longrange") == "true") // 大视频框为远程视频
            OperateVideo("#DialogueDiv_RightSide img:last", mSelfUserId); // 小按钮操作本地ID视频
        else // 大视频框为远程视频
            OperateVideo("#DialogueDiv_RightSide img:last", mTargetUserId); // 小按钮操作目标ID视频
    });
    // 开关操作
    function OperateVideo(element, target_id) {
        if ($(element).attr("videostate") == "true") { // 该视频框为开启状态
            BRAC_UserCameraControl(target_id, 0); // 关闭视频
            $(element).attr("videostate", "false"); // 设置状态属性为关闭
        }
        else { // 该视频框为关闭状态
            BRAC_UserCameraControl(target_id, 1); // 开启视频
            $(element).attr("videostate", "true"); // 设置状态属性为开启
        }
    }
});
//发送文字信息
function SendMessage() {
    $(".Phiz").each(function () { $(this).replaceWith("[" + $(this).attr("alt") + "]"); }); // 将表情显示在发送框中
    var txt = $("#SendMsg").html();
    var len = txt.length;
    if (len > 0) { // 判断发送信息是否为空
        MessageFormat();
        var mFontFamily = Getdmo("SendMsg").style.fontFamily;
        var mFontColor = Getdmo("SendMsg").style.color;
        var mFontSize = Getdmo("SendMsg").style.fontSize;
        txt = "<div style=' color:" + mFontColor + "; font-size:" + mFontSize + "; font-family:" + mFontFamily + ";'>" + txt + "</div>";
        if (compute(txt) < 1000) { // 判断信息长度是否太长
            var msg_div = document.createElement("div");
            msg_div.style.width = "360px";
            msg_div.style.textAlign = "left";
            msg_div.style.color = mFontColor;
            msg_div.style.fontSize = mFontSize;
            msg_div.style.fontFamily = mFontFamily;
            msg_div.style.margin = "0px 0px 0px 10px";
            msg_div.innerHTML = Expression(txt, 1);
            Getdmo("ReceiveMsg").appendChild(msg_div); // 接收信息框显示己方发送信息内容
            BRAC_SendTextMessage(mTargetUserId, 1, txt); // 发送信息
            $("#SendMsg").html(""); // 清空发送框
            ReceiveMsgBoxScroll(); // 判断接收框是否需要显示滚动条
            $("#SendMsg").focus(); // 发送框获得焦点
            $("#SendMsg").css("overflowY", "hidden"); // 发送框滚动条隐藏
        }
        else $("#ReceiveMsg").append("<div class='StandardSize' style='color:#999999'>发送失败,文字信息过长...</div>");
    }
    else Getdmo("SendMsg").focus();
}
//计算信息长度
function compute(str) {
    var i = 0;
    for (var j = 0; j < str.length; j++) {
        if (str.charCodeAt(j) < 0 || str.charCodeAt(j) > 255) i += 2;
        else i++;
    }
    return i;
}
// 结束会话询问
function FinishDialogue() {
    Getdmo("Enquire_Div").innerHTML = ""; // 清空结束会话框 重新生成
    var ask_div = document.createElement("div");
    ask_div.className = "AskInfo";
    ask_div.innerHTML = "是否结束本次会话";
    Getdmo("Enquire_Div").appendChild(ask_div);
    var finish_btn = document.createElement("div"); // 结束会话按钮
    finish_btn.className = "AskButtonImg";
    finish_btn.style.margin = "10px 10px 0px 20px";
    finish_btn.innerHTML = "结束";
    finish_btn.onclick = function () {
        mWhetherMainForm = false;  // 设置会话框状态属性为false
        BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_FINISH,mTargetUserId,0,0,0,""); 
        BackToHall(); // 退回大厅
    }
    Getdmo("Enquire_Div").appendChild(finish_btn);
    var cancel_btn = document.createElement("div");
    cancel_btn.className = "AskButtonImg";
    cancel_btn.innerHTML = "取消"; // 取消结束会话按钮
    cancel_btn.style.margin = "10px 10px 0px 0px";
    cancel_btn.onclick = function () {
        $("#Enquire_Div").hide(); // 隐藏询问框
    }
    Getdmo("Enquire_Div").appendChild(cancel_btn);
    $("#Enquire_Div").show(); // 显示询问框
}
//文本对话框字体设置
function SetFontFamily() {
    var SelectFamily = Getdmo("fontfamily");
    var FontStyle = SelectFamily.options[SelectFamily.selectedIndex].text;
    $("#SendMsg").css("font-family", FontStyle);
}
//文本对话框字体大小设置
function SetFontSize() {
    var SelectSize = Getdmo("fontsize");
    var FontSize = SelectSize.options[SelectSize.selectedIndex].text + "px";
    $("#SendMsg").css("fontSize", FontSize);
}
// 颜色面板和表情面板点击事件
function CorrespondingDiv(ShowID, HideID) {
    $("#" + HideID).hide();
    $("#" + ShowID).toggle();
}
//打开文件传送界面
function GetFilePath() {
    var guid = GUID();
    var GetTheResult = ICS_FileTransRequest(mTargetUserId, guid, "");
    if (GetTheResult == 0) { //发送传输请求
        MessageFormat();
        var main_div = document.createElement("div");
        main_div.id = "SendFileMsg" + guid;
        main_div.className = "SendFileMsg";
        main_div.style.height = "54px";
        Getdmo("ReceiveMsg").appendChild(main_div);

        var prompt_div = document.createElement("div");
        prompt_div.style.fontSize = "12px";
        prompt_div.innerHTML = "&nbsp&nbsp发送文件: " + ViewFileDetail(guid) + " <br />&nbsp&nbsp等待对方接收......";
        main_div.appendChild(prompt_div);

        var cancel_div = document.createElement("div");
        cancel_div.id = "Discontinue" + guid;
        cancel_div.className = "CancelTransmit";
        cancel_div.setAttribute("Belong", guid);

        var cancel_btn = document.createElement("div");
        cancel_btn.style.fontSize = "12px";
        cancel_btn.style.color = "blue";
        cancel_btn.style.cursor = "pointer";
        cancel_btn.style.marginLeft = "10px";
        cancel_btn.innerHTML = "取消";
        cancel_btn.style.height = "20px";
        cancel_btn.onclick = function () {
            ICS_FileTransReply(guid, ICS_RETCODE_FILETRANS_CANCEL);
            ReplyMsgStyle("SendFileMsg" + guid, "&nbsp&nbsp您取消了文件: " + ViewFileDetail(guid) + "的发送<br />&nbsp&nbsp文件传输失败...", true);
            ReceiveMsgBoxScroll();
        }
        cancel_div.appendChild(cancel_btn);
        main_div.appendChild(cancel_div);
    }
    ReceiveMsgBoxScroll();
} 
//在光标处插入表情
function InsertExpression(html) {
    var sel, range;
    document.getElementById("SendMsg").focus();
    if (window.getSelection) {
        sel = window.getSelection();
        if (sel.getRangeAt && sel.rangeCount) {
            range = sel.getRangeAt(0);
            range.deleteContents();
            var el = document.createElement("div");
            el.innerHTML = html;
            var frag = document.createDocumentFragment(), node, lastNode;
            while ((node = el.firstChild)) {
                lastNode = frag.appendChild(node);
            }
            range.insertNode(frag);
            if (lastNode) {
                range = range.cloneRange();
                range.setStartAfter(lastNode);
                range.collapse(true);
                sel.removeAllRanges();
                sel.addRange(range);
            }
        }
    } else if (document.selection && document.selection.type != "Control") {
        document.selection.createRange().pasteHTML(html);
    }
}
//判断信息接收框是否需要显示滚动条
function ReceiveMsgBoxScroll() {
    var ReceiveMsg = Getdmo("ReceiveMsg");
    var VisiblHeight = ReceiveMsg.offsetHeight;
    var ActualHeight = ReceiveMsg.scrollHeight;
    if (ActualHeight > VisiblHeight) {
        Getdmo("ReceiveMsg").style.overflowY = "scroll";
        Getdmo("ReceiveMsg").scrollTop = Getdmo("ReceiveMsg").scrollHeight;
    }
    else
        Getdmo("ReceiveMsg").style.overflowY = "hidden";
}
//设置己放信息显示格式
function MessageFormat() {
    var TimeFormat = new Date();
    var ShowTime = TimeFormat.toLocaleTimeString();
    var txt_div = document.createElement("div");
    txt_div.id = "SendMsgStyle";
    txt_div.innerHTML = mSelfUserName + "  " + ShowTime;
    Getdmo("ReceiveMsg").appendChild(txt_div);
}
// 产生一个GUID
function G() {
    return (((1 + Math.random()) * 0x10000) | 0).toString(16).substring(1)
}
function GUID() {
    var guid = (G() + G() + "-" + G() + "-" + G() + "-" + G() + "-" + G() + G() + G()).toUpperCase();
    return guid;
}
//格式: XXX.txt(122MB)
function ViewFileDetail(Guid) {
    return ICS_FileTransGetFileName(Guid) + "(" + UnitConversion(ICS_FileTransGetFileSize(Guid), "MB", "KB", "B", 1) + ")";
}
//单位转换
function UnitConversion(Values, M, KB, B, Type) {
    var unit;
    if (Type == 0)
        Values = Values / 8;
    if (Values > 1024) {
        Values = (Values / 1024);
        if (Values > 1024) {
            Values = (Values / 1024);
            unit = M;
        }
        else {
            Values = Values;
            unit = KB;
        }
    }
    else {
        Values = Values;
        unit = B;
    }
    return Math.floor(Values * 100) / 100 + unit;
}
////音量 麦声量
//var mCoordinateX;
//function OnLoad(GetSlider) {
//    var slider = document.getElementById(GetSlider);
//    slider.onmousedown = function () {
//        slider.onmousemove = function () {
//            slider.setCapture();
//            if (event.clientX > mCoordinateX && event.clientX < mCoordinateX + 140) {
//                slider.style.marginLeft = event.clientX - mCoordinateX + "px";
//            }
//        }
//    }
//    slider.onmouseup = function () {
//        slider.onmousemove = "";
//        slider.releaseCapture();
//    }
//}
function ClickEvent(Div_ID) {
    var element = Getdmo(Div_ID);
    var CoordinateX = event.clientX;
    var CoordinateY = event.clientY;
    var MinelementX = element.offsetLeft;
    var MinelementY = element.offsetTop;
    var MaxelementX = element.offsetLeft + element.offsetWidth;
    var MaxelementY = element.offsetTop + element.offsetHeight;
    $(document).click(function () {
        if (CoordinateX < MinelementX && CoordinateX > MaxelementX && MinelementY < MinelementY && MinelementY > MaxelementY)
            Div_ID.hide();
    });
}
//动态生成宽屏视频容器
function VideoContainer() {
    Getdmo("VideoShowDiv").innerHTML = "";
    // 左边视频框
    var upper_video1 = document.createElement("div");
    upper_video1.id = "videoshow1";
    upper_video1.className = "videoshow";
    Getdmo("VideoShowDiv").appendChild(upper_video1);
    // 右边视频框
    var upper_video2 = document.createElement("div");
    upper_video2.id = "videoshow2";
    upper_video2.className = "videoshow";
    upper_video2.style.marginLeft = "6px";
    Getdmo("VideoShowDiv").appendChild(upper_video2);
    // 显示己方名字
    var upper_othername = document.createElement("div");
    upper_othername.className = "ShowName";
    upper_othername.innerHTML = BRAC_GetUserName(mTargetUserId);
    Getdmo("VideoShowDiv").appendChild(upper_othername);
    // 显示对方名字
    var upper_myname = document.createElement("div");
    upper_myname.className = "ShowName";
    upper_myname.innerHTML = BRAC_GetUserName(mSelfUserId);
    Getdmo("VideoShowDiv").appendChild(upper_myname);
    // 挂断 按钮
    var under_finish = document.createElement("div");
    under_finish.id = "finishprivate";
    under_finish.onmouseout = function () {
        $("#finishprivate").css("background", "url('./images/dialog/btnfalse_move.png')");
    }
    under_finish.onmouseover = function () {
        $("#finishprivate").css("background", "url('./images/dialog/btnfalse_over.png')");
    }
    under_finish.onclick = function () {
		BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_FINISH,mTargetUserId,0,0,0,""); 	// 挂断
    }
    Getdmo("VideoShowDiv").appendChild(under_finish);
    // 切换界面 按钮
    var under_change = document.createElement("div");
    under_change.id = "SwappingDiv";
    under_change.className = "Buttons";
    under_change.onmouseout = function () {
        $("#SwappingDiv").css("background", "url('./images/dialog/btntrue_move.png')");
    }
    under_change.onmouseover = function () {
        $("#SwappingDiv").css("background", "url('./images/dialog/btntrue_over.png')");
    }
    under_change.onclick = function () {
        SwappingVideo(true);
    }
    under_change.innerHTML = "文字模式";
    Getdmo("VideoShowDiv").appendChild(under_change);
}
// 视频会话模式切换
function SwappingVideo(type) {
    mWhetherMainForm = type; // 哪一个界面被显示
    if (type) { // 切换到文字模式
        clearInterval(mFlickerNews);  // 取消新信息闪烁提示
        $("#VideoShowDiv").hide(); //隐藏语音视频层
        $("#DialogueDiv").show();
        Getdmo("SendMsg").focus(); //发送框获取焦点
        ChangeVideoShow("Video_Show_MySelf", "Video_Show_Target", "videoshow2", "videoshow1");
        mRefreshVolumeTimer = setInterval(CurrentVolume, 200); // 获取显示语音音量
    }
    else { // 切换到宽频模式
        $("#VideoShowDiv").show(); //显示语音视频层
        $("#DialogueDiv").hide();
        ChangeVideoShow("videoshow2", "videoshow1", "Video_Show_MySelf", "Video_Show_Target");
        clearInterval(mRefreshVolumeTimer); // 关闭语音音量显示
    }
}
// 双方音量条
function CurrentVolume() {
    Getdmo("Mine_Volume").style.width = Getdmo("Video_Show_MySelf").offsetWidth / 100 * BRAC_QueryUserStateInt(mSelfUserId, BRAC_USERSTATE_SPEAKVOLUME) + "px";
    Getdmo("Target_Volume").style.width = Getdmo("Video_Show_Target").offsetWidth / 100 * BRAC_QueryUserStateInt(mTargetUserId, BRAC_USERSTATE_SPEAKVOLUME) + "px";
}
// 设置显示视频位置
function ChangeVideoShow(firVideo, secVideo, ClearfirVideo, ClearsecVideo) {
    Getdmo(ClearfirVideo).innerHTML = "";
    Getdmo(ClearsecVideo).innerHTML = "";
    BRAC_SetVideoPos(mSelfUserId, Getdmo(firVideo), "ANYCHAT_VIDEO_LOCAL");
    BRAC_SetVideoPos(mTargetUserId, Getdmo(secVideo), "ANYCHAT_VIDEO_REMOTE");
}
// 切换到宽屏模式
function ToWideScreen() {
    SwappingVideo(false);
}