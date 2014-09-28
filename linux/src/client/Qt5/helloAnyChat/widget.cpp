#include "widget.h"
#include "ui_widget.h"
#include <QThread>

#define REFRESH_TRANSTASK_STATUS_TIMER 	1	//刷新传输任务状态定时器
#define REFRESH_SPEAKVOLUME_TIMER	    2   //更新用户说话音量定时器
#define REFRESH_RECORDSTATE_TIMER	    3   //更新录像状态定时器

Widget* pthis;

static int g_sOpenedCamUserId=0;            //已经请求视频的用户id

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    int width = this->geometry().width();
    int height = this->geometry().height();
    this->setFixedSize(width,height); //设置窗体固定大小

    pthis=this;

    m_pTimer =new QTimer;
    m_strLogInfo="";

    m_lpLocalVideoFrame = NULL;
    m_iLocalVideoSize = 0;

    m_lpRemoteVideoFrame = NULL;
    m_iRemoteVideoSize = 0;

    ui->RemoteUserlabel->setStyleSheet("background-color:black");//设置默认显示背景
    ui->LocalUserlabel->setStyleSheet ("background-color:black");
    ui->RoomId_lineEdit->setText("1");
    ui->ServerIP_lineEdit->setText("demo.anychat.cn");
    ui->ServerPort_lineEdit->setText("8906");
    ui->UserName_lineEdit->setText("QtDemo");
    connect(this,SIGNAL(changeSysLogs(QString)),this,SLOT(setSysLogs(QString)));

    memset(m_iUserID,-1,sizeof(m_iUserID));

    HelloChatInit(); //初始化
}

Widget::~Widget()
{
    if(m_lpLocalVideoFrame)
    {
        free(m_lpLocalVideoFrame);
        m_lpLocalVideoFrame = NULL;
    }

    if(m_lpRemoteVideoFrame)
    {
        free(m_lpRemoteVideoFrame);
        m_lpRemoteVideoFrame = NULL;
    }

    delete m_pTimer;
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    BRAC_Logout();
    BRAC_Release();
    event->accept();
}

void Widget::HelloChatRefreshUserList()
{
    //先清空列表
    ui->UserlistWidget->clear();
    memset(m_iUserID,-1,sizeof(MAX_USER_NUM));

    //获取在线用户人数
    DWORD dwUserNum = 0;
    BRAC_GetOnlineUser(NULL, dwUserNum);
    if(!dwUserNum)
        return ;

    //获取在线用户ID列表
    LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD) *dwUserNum);
    BRAC_GetOnlineUser(lpdwUserList, dwUserNum);//获取在线用户id

    //重新入列
    for(int i = 0; i < (int)dwUserNum; i++) //刷新用户列表
    {
        DWORD dwUserID = lpdwUserList[i];

        if(dwUserID != -1)
        {
            char cUserName[30];
            BRAC_GetUserName(dwUserID,cUserName,sizeof(cUserName));//获取用户名

            m_iUserID[i] = dwUserID;
            ui->UserlistWidget->insertItem(i,cUserName);//对应的用户名添加到列表中,从0开始
        }
        else
            break;
    }
    free(lpdwUserList);
}

//消息打印，槽函数
void Widget::setSysLogs(QString str)
{
    m_strLogInfo += (str + "\r\n");
    ui->SysMsgTextEdit->setText(m_strLogInfo);
    ui->SysMsgTextEdit->moveCursor(QTextCursor::End);
}

void Widget::HelloChatInit()
{
    //获取SDK的版本信息
    DWORD dwMainVer,dwSubVer;
    char szCompileTime[100] = {0};
    BRAC_GetSDKVersion(dwMainVer,dwSubVer,szCompileTime,sizeof(szCompileTime));

    QString logstr;
    logstr.sprintf("#INFO# AnyChat Core SDK Version:%d.%d(%s)",dwMainVer,dwSubVer,szCompileTime);
    AppendLogString(logstr);   //调用AppendLogString函数在消息框中显示当前SDK的版本信息

    //打开（关闭）SDK的日志记录功能
    BRAC_ActiveCallLog(true);

    //设置SDK核心组件所在目录（注：demo程序只是设置为当前目录，项目中需要设置为实际路径）
    QString szCoreSDKPath;
    szCoreSDKPath = QCoreApplication::applicationDirPath();   //获取当前应用程序路径
    (strrchr((char*)szCoreSDKPath.toStdString().c_str(),'/'))[1] = 0;
    BRAC_SetSDKOption(BRAC_SO_CORESDK_PATH,(char*)szCoreSDKPath.toStdString().c_str(),strlen((char*)szCoreSDKPath.toStdString().c_str()));

    // 根据BRAC_InitSDK的第二个参数：dwFuncMode，来告诉SDK该如何处理相关的任务（详情请参考开发文档）
    DWORD dwFuncMode = BRAC_FUNC_VIDEO_CBDATA/*BRAC_FUNC_VIDEO_AUTODISP*/ | BRAC_FUNC_AUDIO_AUTOPLAY | BRAC_FUNC_CHKDEPENDMODULE |
                       BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
                       BRAC_FUNC_AUDIO_AUTOVOLUME | BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_CONFIG_LOCALINI;

    BRAC_InitSDK((HWND*)this->winId(), dwFuncMode);
    BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_RGB32,VideoData_CallBack, this);//设置视频数据回调
    BRAC_SetAudioDataCallBack(AudioData_CallBack, this);                   //设置声音数据回调
    BRAC_SetNotifyMessageCallBack(NotifyMessage_CallBack,this);            //设置异步消息回调
    BRAC_SetTextMessageCallBack(TextMessage_CallBack,this);                //设置消息发送回调

    // 设置服务器认证密码
    QString pwd = "BaiRuiTech";
    BRAC_SetServerAuthPass((LPCTSTR)pwd.toStdString().c_str());
    // 设置定时器并打开
    m_pTimer->setInterval(100);
    m_pTimer->start();
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(TimerProc()));
}

void Widget::HelloChatLogin()
{
   QString UserName   = ui->UserName_lineEdit->text();
   QString ServerIP   = ui->ServerIP_lineEdit->text();
   QString ServerPort = ui->ServerPort_lineEdit->text();
   int port = ServerPort.toInt();

   BRAC_Connect(ServerIP.toStdString().c_str(),port);  //连接服务器 :connect to server
   BRAC_Login(UserName.toStdString().c_str(), "", 0);  //登陆服务器 :loging to server
}

void Widget::AppendLogString(QString logstr)
{
    m_strLogInfo += (logstr + "\r\n");
    ui->SysMsgTextEdit->setText(m_strLogInfo);
    ui->SysMsgTextEdit->moveCursor(QTextCursor::End);  //自动滚动
}

// 收到消息：客户端连接服务器 wParam（BOOL）表示是否连接成功
long Widget::OnGVClientConnect(WPARAM wParam, LPARAM lParam)
{
    bool bSuccess = (bool)wParam;
    QString str(bSuccess ? "#INFO# Connect to server OK" : "#INFO# Connect to Server error");
    emit changeSysLogs(str);

    return 0;
}

// 收到消息：客户端登录系统 wParam （INT）表示自己的用户ID号, lParam （INT）表示登录结果：0 成功，否则为出错代码，参考出错代码定义
long Widget::OnGVClientLogin(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
    DWORD dwUserID = wParam;
    if(lParam == 0)
    {
        CHAR username[30];
        BRAC_GetUserName(dwUserID,username,sizeof(username));
        logstr.sprintf("#INFO# Login Server OK UserId：%d(%s)",dwUserID,username);

        //将自己的ID保存
        m_SelfId= dwUserID;
    }
    else
        logstr.sprintf("#INFO# Login  Server Error： %d ",lParam);

    emit changeSysLogs(logstr);

    return 0;
}

// 收到消息：客户端进入房间  wParam （INT）表示所进入房间的ID号,
//                       lParam （INT）表示是否进入房间：0成功进入，否则为出错代码
long Widget::OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam)
{
        QString logstr;
        int roomid = (int)wParam;

        if(lParam == 0) //自己成功进入房间，然后打开视频和音频
        {
                logstr.sprintf("#INFO# success enter room：%d,user ",roomid);
                //Open Local Camera
                BRAC_UserCameraControl(-1,TRUE);
                BRAC_UserSpeakControl(-1,TRUE);
        }
        else
        {
                logstr.sprintf("#INFO# can not enter room，error code： %d ",lParam);
        }

        emit changeSysLogs(logstr);
        return 0;
}

// 收到当前房间的在线用户信息 wParam （INT）表示在线用户数（不包含自己）,
//                       lParam  （INT）表示房间ID
long Widget::OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam)
 {
     QString logstr;
     int onlinenum = (int)wParam;
     logstr.sprintf("#INFO# the room id：%d\n#INFO# total %d user online",lParam, onlinenum);
     emit changeSysLogs(logstr);

     //刷新列表
     HelloChatRefreshUserList();

     return 0;
 }

// 收到消息：用户的音频设备状态变化消息  wParam （INT）表示用户ID号 lParam （BOOL）表示该用户是否已打开音频采集设备
long Widget::OnGVClientMicStateChange(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
    logstr.sprintf("#INFO# user id：%d ", wParam);
    logstr.append( lParam ? "open":"close");
    logstr.append(" Local Mic Device");

    emit changeSysLogs(logstr);
    return 0;
}

// 收到消息：用户进入（离开）房间 wParam （INT）表示用户ID号,
//                           lParam （BOOL）表示该用户是进入（TRUE）或离开（FALSE）房间
long Widget::OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
     int userid = (int)wParam;
     bool bEnter = (bool)lParam;

     char username[30]={0};
     BRAC_GetUserName(userid,username,sizeof(username));
     logstr.sprintf("#INFO# User id：%d ,User name(%s) ",userid,username);
     logstr.append(bEnter ? "Enter" : "Leave");
     logstr.append("Room");
     emit changeSysLogs(logstr);

     if(bEnter)                            //有用户进入
     {

           HelloChatRefreshUserList();     //刷新列表
     }
     else                                  //有用户离开
     {
         HelloChatRefreshUserList();

         if(g_sOpenedCamUserId == userid)  //如果视频当中离开 则关闭
         {
             BRAC_UserCameraControl(g_sOpenedCamUserId,FALSE);
             BRAC_UserSpeakControl (g_sOpenedCamUserId,FALSE);
             g_sOpenedCamUserId = 0;

             ui->RemoteUserlabel->clear();
             ui->RemoteUserlabel->setText("RemoteUser");
         }
      }
      return 0;
}

//收到消息：网络连接已关闭    (该消息只有在客户端连接服务器成功之后，网络异常中断之时触发)
long Widget::OnGVClientLinkClose(WPARAM wParam, LPARAM lParam)
{
    emit changeSysLogs("network disconnect");
    for(INT i=0; i<MAX_USER_NUM; i++)
    {
            m_iUserID[i] = -1;
            ui->UserlistWidget->takeItem(i);
    }
    return 0;
}

//这里调用本地定时器触发去执行刷新
void Widget::TimerProc()
{
    TimerProc_CallBack(NULL,0,REFRESH_SPEAKVOLUME_TIMER,0);
}

//定时器回调函数
void CALLBACK Widget::TimerProc_CallBack(HWND hwnd, UINT uMsg, UINT nIDEvent, DWORD dwTime)
{
    Widget* pwidget =(Widget*)hwnd;
    switch(nIDEvent)
    {
    case  REFRESH_SPEAKVOLUME_TIMER:		// 刷新用户说话音量
        {
             //本地用户音频实时刷新
            double fSpeakVolume = 0.0;
            if( pthis->m_SelfId != -1 && BRAC_QueryUserState(pthis->m_SelfId,
                                                  BRAC_USERSTATE_SPEAKVOLUME,
                                                  (PCHAR)&fSpeakVolume,
                                                  sizeof(DOUBLE)) == GV_ERR_SUCCESS)
            {
                pthis->ui->LocalUserProgressBar->setValue((INT)fSpeakVolume);
            }
            else
            {
                    pthis->ui->LocalUserProgressBar->setValue(0);
            }

            //远程用户音频实时刷新
            fSpeakVolume = 0.0;
            if(g_sOpenedCamUserId != 0 && BRAC_QueryUserState(g_sOpenedCamUserId,
                                                        BRAC_USERSTATE_SPEAKVOLUME,
                                                        (PCHAR)&fSpeakVolume,
                                                        sizeof(DOUBLE)) == GV_ERR_SUCCESS)
            {
                    pthis->ui->RemoteUserprogressBar->setValue((INT)fSpeakVolume);
            }
            else
            {
                    pthis->ui->RemoteUserprogressBar->setValue(0);
            }

        }
        break;
    case REFRESH_RECORDSTATE_TIMER:		// 刷新录像状态
        {
            //Doing......
        }
        break;
    default:
        break;
    }

}

// video data callback
void CALLBACK Widget::VideoData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue)
{
    Widget *pDemoDlg = (Widget*)lpUserValue;
    if(pDemoDlg)
    {
          pDemoDlg->DrawUserVideo(dwUserid,lpBuf,dwLen,bmiHeader,pDemoDlg);
    }
}

// audio data callback
void CALLBACK Widget::AudioData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue)
{
    Widget *pDemoDlg = (Widget*)lpUserValue;
    if(pDemoDlg)
    {
        // 因为我初始化SDK的时候使用了自动播放声音功能，所以回调这里不做任何事情
        // 使用者如果需要获取音频并处理，可以在初始化SDK设置为回调获取方式即可
    }
}

// 文字消息回调函数定义
void CALLBACK Widget::TextMessage_CallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue)
{
        Widget*	pDemoDlg = (Widget*)lpUserValue;
        QString message;
        if(pDemoDlg)
        {
            QDateTime time    = QDateTime::currentDateTime();    //获取系统当前时间
            QString   strTime = time.toString("yyyy-MM-dd hh:mm:ss ");
            CHAR      username[30];

            BRAC_GetUserName(dwFromUserid,username,sizeof(username));//获取用户名
            pDemoDlg->AppendLogString(username + strTime);
            message.sprintf("%s", lpMsgBuf);
            pDemoDlg->AppendLogString(message);
        }
}

// 异步消息通知回调函数定义
void CALLBACK Widget::NotifyMessage_CallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue)
{
        Widget*	pAnyChatSDKProc = (Widget*)lpUserValue;
        if(!pAnyChatSDKProc)
                return;

        switch(dwNotifyMsg)
        {
        case WM_GV_CONNECT:		    pAnyChatSDKProc->OnGVClientConnect(wParam,NULL);		        break;
        case WM_GV_LOGINSYSTEM:		pAnyChatSDKProc->OnGVClientLogin(wParam,lParam);                break;
        case WM_GV_ENTERROOM:       pAnyChatSDKProc->OnGVClientEnterRoom(wParam,lParam);            break;
        case WM_GV_MICSTATECHANGE:	pAnyChatSDKProc->OnGVClientMicStateChange(wParam,lParam);       break;
        case WM_GV_USERATROOM:		pAnyChatSDKProc->OnGVClientUserAtRoom(wParam,lParam);           break;
        case WM_GV_LINKCLOSE:       pAnyChatSDKProc->OnGVClientLinkClose(wParam, lParam);           break;
        case WM_GV_ONLINEUSER:		pAnyChatSDKProc->OnGVClientOnlineUser(wParam,lParam);           break;

        case WM_GV_CAMERASTATE:		pAnyChatSDKProc->OnAnyChatCameraStateChgMessage(wParam,lParam);	break;
        case WM_GV_ACTIVESTATE:		pAnyChatSDKProc->OnAnyChatActiveStateChgMessage(wParam,lParam);	break;
        case WM_GV_P2PCONNECTSTATE:	pAnyChatSDKProc->OnAnyChatP2PConnectStateMessage(wParam,lParam);break;
        case WM_GV_SDKWARNING:		pAnyChatSDKProc->OnAnyChatSDKWarningMessage(wParam,lParam);     break;

        default:
                break;
        }
        pAnyChatSDKProc->OnAnyChatNotifyMessageCallBack(dwNotifyMsg,wParam,lParam);
};

//视频数据显示
void Widget::DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader,Widget *pWidget)
{
    if(dwLen <= 0 || lpBuf == NULL)
        return;

    int width  = bmiHeader.biWidth;
    int height = bmiHeader.biHeight;

    //判断用户id选择不同的显示区域
    if(m_SelfId == dwUserid) //本地用户视频
    {
        char* p = m_lpLocalVideoFrame;
        if(  !p ||m_iLocalVideoSize < dwLen)
        {
            p = (char*)realloc(p, dwLen);
            if(!p)
                return;
            m_iLocalVideoSize = dwLen;
        }
        memcpy(p, lpBuf, dwLen);
        QImage img = QImage((uchar *)p,width,height,QImage::Format_RGB32);// can load the image
#ifdef  WIN32
        QImage img2 = img.mirrored();
        pWidget->ui->RemoteUserlabel->setPixmap(QPixmap::fromImage(img2));
#else
        pWidget->ui->RemoteUserlabel->setPixmap(QPixmap::fromImage(img));
#endif
    }
    else  //远程用户视频
    {
        char* p = m_lpRemoteVideoFrame;
        if(  !p ||m_iRemoteVideoSize < dwLen)
        {
            p = (char*)realloc(p, dwLen);
            if(!p)
                return;
            m_iRemoteVideoSize = dwLen;
        }
        memcpy(p, lpBuf, dwLen);
        QImage img = QImage((uchar *)p,width,height,QImage::Format_RGB32);// can load the image
#ifdef  WIN32
        QImage img2 = img.mirrored();
        pWidget->ui->RemoteUserlabel->setPixmap(QPixmap::fromImage(img2));
#else
        pWidget->ui->RemoteUserlabel->setPixmap(QPixmap::fromImage(img));
#endif
    }
}

//单击进入房间事件
void Widget::on_EnterRoom_Btn_clicked()
{
    HelloChatLogin();//登陆
    QString roomId = ui->RoomId_lineEdit->text();                           //房间号
    QString pwd = "";                                                       //密码
    BRAC_EnterRoom(roomId.toInt(), (LPCTSTR)pwd.toStdString().c_str() , 0); //进入房间
}

//单击离开房间事件
void Widget::on_LeaveRoom_Btn_clicked()
{
    //先关闭远程用户视频
    BRAC_UserCameraControl(g_sOpenedCamUserId,0);
    BRAC_UserSpeakControl(g_sOpenedCamUserId,0);
    ui->RemoteUserlabel->clear();
    ui->RemoteUserlabel->setText("RemoteUser");
    //关闭本地用户视频
    BRAC_UserCameraControl(m_SelfId,0);
    BRAC_UserSpeakControl(m_SelfId,0);
    ui->LocalUserlabel->clear();
    ui->LocalUserlabel->setText("LocalUser");
    //离开当前房间
    BRAC_LeaveRoom(1);
    //然后清空用户列表
    HelloChatRefreshUserList(); //清空用户列表
    AppendLogString("#INFO# User Leave Room");
    g_sOpenedCamUserId = 0;
    BRAC_Logout();
}

//双击列表事件，双击后请求远程用户视频
void Widget::on_UserlistWidget_doubleClicked(const QModelIndex &index)
{
    int row = ui->UserlistWidget->currentRow();      //获取所在当前列表行号
    if(g_sOpenedCamUserId!=0)                        //先关闭正在视频
    {
        BRAC_UserCameraControl(g_sOpenedCamUserId,0);
        BRAC_UserSpeakControl(g_sOpenedCamUserId,0);

        g_sOpenedCamUserId = 0;
        ui->RemoteUserlabel->clear();
    }

    BRAC_UserCameraControl(m_iUserID[row],1);      //打开新请求用户视频
    BRAC_UserSpeakControl (m_iUserID[row],1);

    g_sOpenedCamUserId = m_iUserID[row];
}


void Widget::on_SendMsg_Btn_clicked()
{
    QString message = ui->SendMsglineEdit->text();
    if(g_sOpenedCamUserId==0)
    {
        AppendLogString("#ERROR#no user chat with you");
        AppendLogString("#ERROR#please Request Chat first");
        ui->SendMsglineEdit->setText("");
        return ;
    }

    if((BRAC_SendTextMessage(g_sOpenedCamUserId, NULL, (LPCTSTR)message.toStdString().c_str(), message.toStdString().length()))== 0)  //发送成功
    {
        QDateTime time = QDateTime::currentDateTime();    //获取系统当前时间
        QString strTime = time.toString("  yyyy-MM-dd hh:mm:ss ");
        QString info ="#INFO#";
        CHAR username[30];
        BRAC_GetUserName(g_sOpenedCamUserId,username,sizeof(username));
        AppendLogString(info+username + strTime);
        AppendLogString(message);
    }

    ui->SendMsglineEdit->setText("");
}
