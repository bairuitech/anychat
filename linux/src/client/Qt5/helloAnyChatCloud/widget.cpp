#include "widget.h"
#include "ui_widget.h"
#include <QThread>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrl>
#include <QString>

#define REFRESH_TRANSTASK_STATUS_TIMER 	1	
#define REFRESH_SPEAKVOLUME_TIMER	    2
#define REFRESH_AUDIOBITRATE_TIMER		3
#define REFRESH_VIDEOBITRATE_TIMER		4
#define REFRESH_RECORDSTATE_TIMER	    5   

#define MAX_SIGN_LEN 100
Widget* pthis;

typedef struct login_info_struct
{
    char sign[MAX_SIGN_LEN];
    int  ts;
    int  err;
}LOGIN_INFO,*LPLOGIN_INFO;

static int g_sOpenedCamUserId=0;
LOGIN_INFO *g_login_info;

//http request
void Widget::request_sign(QString server_url,
                  QString appid,
                  QString userid)
{
    QNetworkRequest http_request;
    http_request.setUrl(QUrl(server_url));
    QString head_appid("appid=");
    QString head_userid("userid=");
    QString head_strUserid("strUserid=");
    QString str_userid_value("");
    QString head_add("&");

    QString content_data=head_appid + appid + head_add + head_userid + userid + head_add + head_strUserid + str_userid_value;
    QByteArray content_string = content_data.toUtf8();

    printf("json >> %s\n",content_data.toStdString().c_str());
    qDebug()<<"http<post>:"<< content_data.toStdString().c_str();

    http_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QByteArray post_data_sz = QByteArray::number(content_string.size());
    http_request.setRawHeader("Content-Length",post_data_sz);

    QObject:connect(m_http_manager,SIGNAL(finished(QNetworkReply*)),  //关联信号和槽
                this,SLOT(response_callback(QNetworkReply*)));

    m_http_manager->post(http_request, content_string);
}

//http response
void Widget::response_callback(QNetworkReply* http_reply)
{
    if(http_reply->error() != QNetworkReply::NoError)
    {
        AppendLogString("http conect error");
        qDebug() << "Error:" << http_reply->errorString();
        printf("post error\n");
        qDebug()<<"post error";
        return;
    }

    QByteArray recv_data = http_reply->readAll();

    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(recv_data, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            if(obj.contains("errorcode"))
            {
                QJsonValue error_value = obj.take("errorcode");
                if(error_value.isDouble())
                {
                    pthis->m_sign_err = error_value.toInt();
                    qDebug()<<"#debug# error:"<<pthis->m_sign_err;
                }
            }
            if(obj.contains("timestamp"))
            {
                QJsonValue timestamp_value = obj.take("timestamp");
                if(timestamp_value.isDouble())
                {
                    pthis->m_sign_ts = timestamp_value.toVariant().toInt();
                    qDebug()<<"#debug# timestamp:"<<pthis->m_sign_ts;
                }
            }
            if(obj.contains("sigStr"))
            {
                QJsonValue sigStr_value = obj.take("sigStr");
                if(sigStr_value.isString())
                {
                    QString sigStr = sigStr_value.toString();
                    m_qsign_data = sigStr_value.toString();

                    memset(pthis->m_sign_data,'\0',256);
                    memcpy(pthis->m_sign_data, sigStr.toStdString().c_str(),sigStr.toStdString().size());

                    //login to server
                    if(pthis->m_sign_err == 0)
                    {
						QString serveraddr = ui->ServerAddrlineEdit->text();
						QString serverport = ui->ServerPortlineEdit->text();
						QString username = ui->UserNamelineEdit->text();
						BRAC_Connect(LPCTSTR(serveraddr.toStdString().c_str()), serverport.toInt());
                        QString str_appid = ui->Appid_lineEdit->text();
                        QByteArray ba = m_qsign_data.toLatin1();
                        char *pSign = ba.data();

						BRAC_LoginEx(LPCTSTR(username.toStdString().c_str()), 33, LPCTSTR(0), LPCTSTR(str_appid.toStdString().c_str()), pthis->m_sign_ts, LPCTSTR(pSign));
						QString roomId = ui->RoomId_lineEdit->text();
						QString pwd = "";
						BRAC_EnterRoom(roomId.toInt(), (LPCTSTR)pwd.toStdString().c_str(), 0);
					}
                }
            }
        }
    }

    http_reply->deleteLater();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_http_manager = new QNetworkAccessManager(this);
    int width = this->geometry().width();
    int height = this->geometry().height();
    this->setFixedSize(width,height); 

    pthis = this;

	//pthis->setWindowIcon(QIcon("AnyChatVideoMixer.ico"));

    m_pTimer = new QTimer;
    m_strLogInfo = "";
    m_lpLocalVideoFrame = NULL;
    m_iLocalVideoSize = 0;
    m_lpRemoteVideoFrame = NULL;
    m_iRemoteVideoSize = 0;

    ui->RemoteUserlabel->setStyleSheet("background-color:black");
    ui->LocalUserlabel->setStyleSheet ("background-color:black");
    ui->RoomId_lineEdit->setText("1");
    ui->Appid_lineEdit->setText("fbe957d1-c25a-4992-9e75-d993294a5d56");
	ui->ServerAddrlineEdit->setText("demo.anychat.cn");
	ui->ServerPortlineEdit->setText("8906");

    connect(this,SIGNAL(changeSysLogs(QString)),this,SLOT(setSysLogs(QString)));

    memset(m_iUserID,-1,sizeof(m_iUserID));

    m_isLogin     = false;

    HelloChatInit();
}

Widget::~Widget()
{
    if(m_http_manager)
        delete m_http_manager;

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
    //BRAC_Logout();
    BRAC_Release();
    event->accept();
}

void Widget::HelloChatRefreshUserList()
{
    ui->UserlistWidget->clear();
    memset(m_iUserID,-1,sizeof(MAX_USER_NUM));

    DWORD dwUserNum = 0;
    BRAC_GetOnlineUser(NULL, dwUserNum);
    if(!dwUserNum)
        return ;
	if (dwUserNum > MAX_USER_NUM)
		return;

    LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD) * dwUserNum);
	if (NULL == lpdwUserList)
		return;
    BRAC_GetOnlineUser(lpdwUserList, dwUserNum);

    for(int i = 0; i < (INT)dwUserNum; i++) 
    {
        DWORD dwUserID = lpdwUserList[i];

        if(dwUserID != -1)
        {
            char cUserName[120];
            BRAC_GetUserName(dwUserID,(TCHAR*)cUserName,sizeof(cUserName));

            m_iUserID[i] = dwUserID;
            ui->UserlistWidget->insertItem(i,cUserName);
        }
        else
            break;
    }
    free(lpdwUserList);
	/*************/
	lpdwUserList = NULL;
}

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
	TCHAR szCompileTime[100] = {0};
	BRAC_GetSDKVersion(dwMainVer, dwSubVer, (TCHAR*)szCompileTime, sizeof(szCompileTime));

    QString logstr;
    logstr.sprintf("#INFO# AnyChat Core SDK Version:%d.%d(%s)",dwMainVer,dwSubVer,szCompileTime);
    AppendLogString(logstr);  //调用AppendLogString函数在textEdit中显示当前SDK的版本信息

    //打开（关闭）SDK的日志记录功能
    BRAC_ActiveCallLog(true);

    //设置SDK核心组件所在目录（注：demo程序只是设置为当前目录，项目中需要设置为实际路径）
    QString szCoreSDKPath;
    szCoreSDKPath = QCoreApplication::applicationDirPath();   
    (strrchr((char*)szCoreSDKPath.toStdString().c_str(),'/'))[1] = 0;
    BRAC_SetSDKOption(BRAC_SO_CORESDK_PATH,(char*)szCoreSDKPath.toStdString().c_str(),strlen((char*)szCoreSDKPath.toStdString().c_str()));

    // 根据BRAC_InitSDK的第二个参数：dwFuncMode，来告诉SDK该如何处理相关的任务（详情请参考开发文档）
    DWORD dwFuncMode = /*BRAC_FUNC_VIDEO_CBDATA*/ BRAC_FUNC_VIDEO_AUTODISP | BRAC_FUNC_AUDIO_AUTOPLAY | BRAC_FUNC_CHKDEPENDMODULE |
                       BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
                       BRAC_FUNC_AUDIO_AUTOVOLUME | BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_CONFIG_LOCALINI;

    BRAC_InitSDK((HWND)this->winId(), dwFuncMode);
    BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_RGB32, VideoData_CallBack, this);
    BRAC_SetAudioDataCallBack(AudioData_CallBack, this);
    BRAC_SetNotifyMessageCallBack(NotifyMessage_CallBack,this);
    BRAC_SetTextMessageCallBack(TextMessage_CallBack,this);

    // 设置服务器认证密码
    QString pwd = "BaiRuiTech";
    BRAC_SetServerAuthPass((LPCTSTR)pwd.toStdString().c_str());
    m_pTimer->setInterval(100);
    m_pTimer->start();
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(TimerProc()));

    m_UserRect[0].SetRect(30, 420, 231, 600);
    m_UserRect[1].SetRect(280, 30, 791, 390);
}

void Widget::HelloChatLogin()
{
    //appid登录方式
    if(ui->Appid_checkBox->isChecked() && !ui->Appid_lineEdit->text().isEmpty())
    {
         QString server_url = "http://demo.anychat.cn:8930";	///< 签名服务器地址
         QString appid_content = ui->Appid_lineEdit->text();	///< 应用ID
         QString userid = "33";									///< 用户编码
         request_sign(server_url, appid_content, userid);
    }
    else   //普通登录方式
    {
		QString serveraddr = ui->ServerAddrlineEdit->text();
		QString serverport = ui->ServerPortlineEdit->text();
		QString username = ui->UserNamelineEdit->text();
		BRAC_Connect(LPCTSTR(serveraddr.toStdString().c_str()), (DWORD)serverport.toInt());
		BRAC_Login(LPCTSTR(username.toStdString().c_str()), LPCTSTR(""), 0);
		QString roomId = ui->RoomId_lineEdit->text();
		QString pwd = "";
		BRAC_EnterRoom(roomId.toInt(), (LPCTSTR)pwd.toStdString().c_str(), 0);
    }
}

void Widget::AppendLogString(QString logstr)
{
    m_strLogInfo += (logstr + "\r\n");
    ui->SysMsgTextEdit->setText(m_strLogInfo);
    ui->SysMsgTextEdit->moveCursor(QTextCursor::End);  
}

long Widget::OnGVClientConnect(WPARAM wParam, LPARAM lParam)
{
    bool bSuccess = (bool)wParam;
    QString str(bSuccess ? "#INFO# Connect to server OK" : "#INFO# Connect to Server error");
    emit changeSysLogs(str);

    return 0;
}

long Widget::OnGVClientLogin(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
    DWORD dwUserID = wParam;
    if(lParam == 0)
    {
        CHAR username[120];
        BRAC_GetUserName(dwUserID,(TCHAR*)username,sizeof(username));
        logstr.sprintf("#INFO# Login Server OK UserId %d(%s)", dwUserID, username);

        m_SelfId= dwUserID;

        m_isLogin = true;
        ui->Login_btn->setText("Logout");
    }
    else
        logstr.sprintf("#INFO# Login  Server Error  %d ", lParam);

    emit changeSysLogs(logstr);

    return 0;
}

long Widget::OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
    int roomid = (int)wParam;

    if(lParam == 0) 
    {
        logstr.sprintf("#INFO# Success enter room %d,user %d",roomid, m_SelfId);
		BRAC_SetVideoPos(-1, (HWND)this->winId(), m_UserRect[0].left, m_UserRect[0].top, m_UserRect[0].right, m_UserRect[0].bottom);
		
        //Open Local Camera
        BRAC_UserCameraControl(-1, TRUE);
        BRAC_UserSpeakControl(-1, TRUE);

    }
    else
    {
        logstr.sprintf("#INFO# Can not enter room Error code  %d ",lParam);
    }

    emit changeSysLogs(logstr);
    return 0;
}

long Widget::OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam)
 {
     QString logstr;
     int onlinenum = (int)wParam;
     logstr.sprintf("#INFO# The room id %d",lParam);
     emit changeSysLogs(logstr);

    
     HelloChatRefreshUserList();

     return 0;
 }

long Widget::OnGVClientMicStateChange(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
    logstr.sprintf("#INFO# User id %d ", wParam);
    logstr.append( lParam ? "open":"close");
    logstr.append(" Local Mic Device");

    emit changeSysLogs(logstr);
    return 0;
}

long Widget::OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
    int userid = (int)wParam;
    bool bEnter = (bool)lParam;
    
    char username[120] = {0};
	BRAC_GetUserName(userid, (TCHAR*)username, sizeof(username));
    logstr.sprintf("#INFO# User id %d ,User name(%s) ", userid, username);
    logstr.append(bEnter ? "Enter" : "Leave");
    logstr.append("Room");
    emit changeSysLogs(logstr);

    if(bEnter)                            
    {
        HelloChatRefreshUserList();     
    }
    else                                  
    {
        HelloChatRefreshUserList();

        if(g_sOpenedCamUserId == userid)
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

long Widget::OnGVClientLinkClose(WPARAM wParam, LPARAM lParam)
{
    emit changeSysLogs("Network disconnect");
    for(INT i = 0; i < MAX_USER_NUM; i++)
    {
        m_iUserID[i] = -1;
        ui->UserlistWidget->takeItem(i);
    }
    return 0;
}

void Widget::TimerProc()
{
    TimerProc_CallBack(NULL, 0, REFRESH_SPEAKVOLUME_TIMER, 0);
	TimerProc_CallBack(NULL, 0, REFRESH_AUDIOBITRATE_TIMER, 0);
	TimerProc_CallBack(NULL, 0, REFRESH_VIDEOBITRATE_TIMER, 0);

}

// 定时器回调函数
void CALLBACK Widget::TimerProc_CallBack(HWND hwnd, UINT uMsg, UINT nIDEvent, DWORD dwTime)
{
    Widget* pwidget =(Widget*)hwnd;
    switch(nIDEvent)
    {
		case  REFRESH_SPEAKVOLUME_TIMER:		
			{
				double fSpeakVolume = 0.0;
				if( pthis->m_SelfId != -1 && BRAC_QueryUserState(pthis->m_SelfId, BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume, sizeof(DOUBLE)) == GV_ERR_SUCCESS)
				{
                    pthis->ui->LocalUserProgressBar->setValue((INT)fSpeakVolume);
				}
				else
				{
                    pthis->ui->LocalUserProgressBar->setValue(0);
				}

				fSpeakVolume = 0.0;
				if(g_sOpenedCamUserId != 0 && BRAC_QueryUserState(g_sOpenedCamUserId, BRAC_USERSTATE_SPEAKVOLUME, (PCHAR)&fSpeakVolume, sizeof(DOUBLE)) == GV_ERR_SUCCESS)
				{
					pthis->ui->RemoteUserprogressBar->setValue((INT)fSpeakVolume);
				}
				else
				{
					pthis->ui->RemoteUserprogressBar->setValue(0);
				}
			}
		case REFRESH_AUDIOBITRATE_TIMER:
			{
				int dwAudioBps = 0;
				if (pthis->m_SelfId != -1 && BRAC_QueryUserState(pthis->m_SelfId, BRAC_USERSTATE_AUDIOBITRATE, (PCHAR)&dwAudioBps, sizeof(int)) == GV_ERR_SUCCESS)
				{
					dwAudioBps /= 1000;
					pthis->ui->localAudioBpslabel->setNum(dwAudioBps);
				}
				else
				{
					pthis->ui->localAudioBpslabel->setNum(0);
				}

				if (g_sOpenedCamUserId != -1 && BRAC_QueryUserState(g_sOpenedCamUserId, BRAC_USERSTATE_AUDIOBITRATE, (PCHAR)&dwAudioBps, sizeof(int)) == GV_ERR_SUCCESS)
				{
					dwAudioBps /= 1000;
					pthis->ui->RemoteAudioBpslabel->setNum(dwAudioBps);
				}
				else
				{
					pthis->ui->RemoteAudioBpslabel->setNum(0);
				}
			}
		case REFRESH_VIDEOBITRATE_TIMER:
			{
				int dwVideoBps = 0;
				if (pthis->m_SelfId != -1 && BRAC_QueryUserState(pthis->m_SelfId, BRAC_USERSTATE_VIDEOBITRATE, (PCHAR)&dwVideoBps, sizeof(int)) == GV_ERR_SUCCESS)
				{
					dwVideoBps /= 1000;
					pthis->ui->localVideoBpslabel->setNum(dwVideoBps);
				}
				else
				{
					pthis->ui->localVideoBpslabel->setNum(0);
				}

				if (g_sOpenedCamUserId != -1 && BRAC_QueryUserState(g_sOpenedCamUserId, BRAC_USERSTATE_VIDEOBITRATE, (PCHAR)&dwVideoBps, sizeof(int)) == GV_ERR_SUCCESS)
				{
					dwVideoBps /= 1000;
					pthis->ui->RemoteVideoBpslabel->setNum(dwVideoBps);
				}
				else
				{
					pthis->ui->RemoteVideoBpslabel->setNum(0);
				}
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
	return;
}

// audio data callback
void CALLBACK Widget::AudioData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue)
{
    Widget *pDemoDlg = (Widget*)lpUserValue;
    if(pDemoDlg)
    {
		/////////////
    }
}


void CALLBACK Widget::TextMessage_CallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue)
{
    Widget*	pDemoDlg = (Widget*)lpUserValue;
    QString message;
    if(pDemoDlg)
    {
        QDateTime time    = QDateTime::currentDateTime();   
        QString   strTime = time.toString("yyyy-MM-dd hh:mm:ss ");
        CHAR      username[120];

	    BRAC_GetUserName(dwFromUserid, (TCHAR*)username, sizeof(username));
        pDemoDlg->AppendLogString(username + strTime);
        message.sprintf("%s", lpMsgBuf);
        pDemoDlg->AppendLogString(message);
    }
}

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

void Widget::DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader,Widget *pWidget)
{
    if(dwLen <= 0 || lpBuf == NULL)
        return;

    int width  = bmiHeader.biWidth;
    int height = bmiHeader.biHeight;

	if (pWidget == NULL)
		return;
    
    if(m_SelfId == dwUserid)
    {
        char* p = m_lpLocalVideoFrame;
        if(  !p ||m_iLocalVideoSize < (int)dwLen)
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
        pWidget->ui->LocalUserlabel->setPixmap(QPixmap::fromImage(img2));
#else
        pWidget->ui->LocalUserlabel->setPixmap(QPixmap::fromImage(img));
#endif
		free(p);
		p = NULL;
    }
    else
    {
        char* p = m_lpRemoteVideoFrame;
        if(  !p ||m_iRemoteVideoSize < (int)dwLen)
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
		free(p);
		p = NULL;
    }
}

void Widget::on_UserlistWidget_doubleClicked(const QModelIndex &index)
{
    int row = ui->UserlistWidget->currentRow();      
    if(g_sOpenedCamUserId != 0)                        
    {
        BRAC_UserCameraControl(g_sOpenedCamUserId,0);
        BRAC_UserSpeakControl(g_sOpenedCamUserId,0);

        g_sOpenedCamUserId = 0;
        ui->RemoteUserlabel->clear();
    }

	BRAC_SetVideoPos(m_iUserID[row], (HWND)this->winId(), m_UserRect[1].left, m_UserRect[1].top, m_UserRect[1].right, m_UserRect[1].bottom);
    
	BRAC_UserCameraControl(m_iUserID[row],1);      
    BRAC_UserSpeakControl (m_iUserID[row],1);

    g_sOpenedCamUserId = m_iUserID[row];
}


void Widget::on_SendMsg_Btn_clicked()
{
    QString message = ui->SendMsglineEdit->text();
    if(g_sOpenedCamUserId==0)
    {
        AppendLogString("#ERROR# No user chat with you");
        AppendLogString("#ERROR# Please request chat first");
        ui->SendMsglineEdit->setText("");
        return ;
    }

    if((BRAC_SendTextMessage(g_sOpenedCamUserId, NULL, (LPCTSTR)message.toStdString().c_str(), message.toStdString().length()))== 0)  
    {
        QDateTime time = QDateTime::currentDateTime();    
        QString strTime = time.toString("  yyyy-MM-dd hh:mm:ss ");
        QString info ="#INFO#";
        CHAR username[120];
		BRAC_GetUserName(g_sOpenedCamUserId, (TCHAR*)username, sizeof(username));
        AppendLogString(info + username + strTime);
        AppendLogString(message);
    }

    ui->SendMsglineEdit->setText("");
}

void Widget::on_Appid_checkBox_clicked()
{
    if(ui->Appid_checkBox->isChecked())
        ui->Appid_lineEdit->setEnabled(true);
    else
        ui->Appid_lineEdit->setEnabled(false);
}

void Widget::on_Login_btn_clicked()
{
    if(!m_isLogin)
    {
         HelloChatLogin();
    }
    else
    {
        m_isLogin = false;
        ui->Login_btn->setText("Login");

		BRAC_UserCameraControl(g_sOpenedCamUserId, 0);
		BRAC_UserSpeakControl(g_sOpenedCamUserId, 0);
		ui->RemoteUserlabel->clear();
		ui->RemoteUserlabel->setText("RemoteUser");

		BRAC_UserCameraControl(m_SelfId, 0);
		BRAC_UserSpeakControl(m_SelfId, 0);
		ui->LocalUserlabel->clear();
		ui->LocalUserlabel->setText("LocalUser");

		BRAC_LeaveRoom(1);

		HelloChatRefreshUserList();
		AppendLogString("#INFO# User Leave Room");
		g_sOpenedCamUserId = 0;

        BRAC_Logout();
    }
}
