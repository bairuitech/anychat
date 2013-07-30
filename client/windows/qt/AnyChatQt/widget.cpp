#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QTextCursor>
#include <QMessageBox>
#include "BRAnyChatCoreSDK.h"
#include <QTextCodec>
#include <QLibrary>
#include <QFileDialog>
#include <QTimer>
#include <QDateTime>


#define REFRESH_TRANSTASK_STATUS_TIMER 	1	//< 刷新传输任务状态定时器
#define REFRESH_SPEAKVOLUME_TIMER	2       //< 更新用户说话音量定时器
#define REFRESH_RECORDSTATE_TIMER	3       //< 更新录像状态定时器

#ifdef __AFX_H__
        #define	BR_AFX_MANAGE_STATE	AFX_MANAGE_STATE(AfxGetStaticModuleState())
#else
        #define	BR_AFX_MANAGE_STATE
#endif //__AFX_H__


typedef int(*pcom_open)(int,int,int);   //定义函数指针
#pragma comment(lib,"BRAnyChatCore.lib")


Widget*  pthis;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    pthis = this;

    //ui->IplineEdit->setInputMask("000.000.000.000");        //设置IP地址的输入格式
    ui->IplineEdit->setText("demo.anychat.cn");               //设置IP地址
    ui->PortLineEdit->setText("8906");                      //设置端口号
    ui->UserLineEdit->setText("AnyChatQt");                 //设置用户名
    ui->RoomIDlineEdit->setText("1");                       //设置房间号
    ui->Speak0ProgressBar->setValue(0);                     //进程条初始值设为0
    ui->Speak1ProgressBar->setValue(0);
    ui->Speak2ProgressBar->setValue(0);
    ui->Speak3ProgressBar->setValue(0);

    m_dwTransTaskId = -1;

    for(int i=0; i <DEMO_SHOW_USER_NUM; i++)
    {
             m_iUserID[i] = -1;
    }

     ui->VideocomboBox->insertItem(1,"this is a test");
     ui->VideocomboBox->insertItem(2,"Video Play");

     ui->RecordState0->hide();
     ui->RecordState1->hide();
     ui->RecordState2->hide();
     ui->RecordState3->hide();


    QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));    //设置能够中文输出
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));
}

Widget::~Widget()
{
    m_AnyChatSDK.Release();       //释放资源
    delete ui;
}

void Widget::AppendLogString(QString logstr)
{
    m_strLogInfo += (logstr + "\r\n");
    ui->m_ctrlEditLog->setText(m_strLogInfo);
    ui->m_ctrlEditLog->moveCursor(QTextCursor::End);  //自动滚动

}

 //初始化
void Widget::on_initBtn_clicked()
{
    m_AnyChatSDK.LoadFilterDll(L"BRAnyChatCore.dll");  //利用对象加载动态库

    //获取SDK的版本信息
    DWORD dwMainVer,dwSubVer;
    char szCompileTime[100] = {0};
    m_AnyChatSDK.GetSDKVersion(dwMainVer,dwSubVer,szCompileTime,sizeof(szCompileTime));

    QString logstr;
    logstr.sprintf("AnyChat Core SDK Version:%d.%d(%s)",dwMainVer,dwSubVer,szCompileTime);
    AppendLogString(logstr);   //调用AppendLogString函数在textEdit中显示当前SDK的版本信息

    //打开（关闭）SDK的日志记录功能
    m_AnyChatSDK.ActiveCallLog(true);

    //设置SDK核心组件所在目录（注：demo程序只是设置为当前目录，项目中需要设置为实际路径）
    QString szCoreSDKPath;
    szCoreSDKPath = QCoreApplication::applicationDirPath();   //获取当前应用程序路径
    (strrchr((char*)szCoreSDKPath.toStdString().c_str(),'/'))[1] = 0;
    m_AnyChatSDK.SetSDKOption(BRAC_SO_CORESDK_PATH,(char*)szCoreSDKPath.toStdString().c_str(),strlen((char*)szCoreSDKPath.toStdString().c_str()));

    // 根据BRAC_InitSDK的第二个参数：dwFuncMode，来告诉SDK该如何处理相关的任务（详情请参考开发文档）
    DWORD dwFuncMode = BRAC_FUNC_VIDEO_AUTODISP | BRAC_FUNC_AUDIO_AUTOPLAY | BRAC_FUNC_CHKDEPENDMODULE |
                       BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
                       BRAC_FUNC_AUDIO_AUTOVOLUME | BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_CONFIG_LOCALINI;

    m_AnyChatSDK.InitSDK(this->winId(), dwFuncMode);
    m_AnyChatSDK.SetVideoDataCallBack(BRAC_PIX_FMT_RGB24,VideoData_CallBack, this);
    m_AnyChatSDK.SetAudioDataCallBack(AudioData_CallBack, this);
    m_AnyChatSDK.SetVolumeChangeCallBack(VolumeChange_CallBack, this);
    m_AnyChatSDK.SetTextMessageCallBack(TextMessage_CallBack,this);
    m_AnyChatSDK.SetTransBufferExCallBack(TransBufferEx_CallBack, this);
    m_AnyChatSDK.SetTransBufferCallBack(TransBuffer_CallBack, this);
    m_AnyChatSDK.SetTransFileCallBack(TransFile_CallBack, this);
    m_AnyChatSDK.SetRecordSnapShotCallBack(RecordSnapShot_CallBack, this);
    m_AnyChatSDK.SetSDKFilterDataCallBack(SDKFilterData_CallBack, this);
    m_AnyChatSDK.SetNotifyMessageCallBack(NotifyMessage_CallBack,this);
   // m_AnyChatSDK.SetTimerProcCallBack(TimerProc_CallBack, this);


    m_bEnableVAD = ui->VADcheckBox->checkState();   //获得四个复选框的值
    m_bEnableAGC = ui->AGCcheckBox->checkState();
    m_bEnableEcho = ui->AECcheckBox->checkState();
    m_bEnableNS = ui->NScheckBox->checkState();

    m_AnyChatSDK.SetSDKOption(BRAC_SO_AUDIO_AGCCTRL,(PCHAR)&m_bEnableAGC,sizeof(m_bEnableAGC));
    m_AnyChatSDK.SetSDKOption(BRAC_SO_AUDIO_VADCTRL,(PCHAR)&m_bEnableVAD,sizeof(m_bEnableVAD));
    m_AnyChatSDK.SetSDKOption(BRAC_SO_AUDIO_NSCTRL,(PCHAR)&m_bEnableNS,sizeof(m_bEnableNS));
    m_AnyChatSDK.SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,(PCHAR)&m_bEnableEcho,sizeof(m_bEnableEcho));

    // 设置录像临时文件保存路径
    QString szRecordDirectory;
    szRecordDirectory = QCoreApplication::applicationDirPath();   //获取当前就用程序路径
    (strrchr((char*)szRecordDirectory.toStdString().c_str(),'/'))[1] = 0;
    szRecordDirectory.append("/Record");
    m_AnyChatSDK.SetSDKOption(BRAC_SO_RECORD_TMPDIR, (char*)szRecordDirectory.toStdString().c_str(), strlen((char*)szRecordDirectory.toStdString().c_str()));

     // 设置录像文件质量参数
     DWORD dwVideoBitrate = 200 * 1000;	// 200kbps
     m_AnyChatSDK.SetSDKOption(BRAC_SO_RECORD_VIDEOBR,(PCHAR)&dwVideoBitrate,sizeof(DWORD));
     DWORD dwAudioBitrate = 96 * 1000;	// 96kbps
     m_AnyChatSDK.SetSDKOption(BRAC_SO_RECORD_AUDIOBR,(PCHAR)&dwAudioBitrate,sizeof(DWORD));

     // 设置快照临时文件保存路径
     QString szSnapShotDirectory;
     szSnapShotDirectory = QCoreApplication::applicationDirPath();   //获取当前应用程序路径
     (strrchr((char*)szSnapShotDirectory.toStdString().c_str(),'/'))[1] = 0;
     szSnapShotDirectory.append("/SnapShot");
     m_AnyChatSDK.SetSDKOption(BRAC_SO_SNAPSHOT_TMPDIR, (char*)szSnapShotDirectory.toStdString().c_str(), strlen((char*)szSnapShotDirectory.toStdString().c_str()));

     // 设置SDK临时文件路径
     QString szTempPath;
     szTempPath = QCoreApplication::applicationDirPath();   //获取当前就用程序路径
     (strrchr((char*)szTempPath.toStdString().c_str(),'/'))[1] = 0;
     szTempPath.append("/SnapShot");
     m_AnyChatSDK.SetSDKOption(BRAC_SO_CORESDK_TMPDIR, (char*)szTempPath.toStdString().c_str(), strlen((char*)szTempPath.toStdString().c_str()));

    // 设置服务器认证密码
    QString pwd = "BaiRuiTech";
    m_AnyChatSDK.SetServerAuthPass((LPCTSTR)pwd.toStdString().c_str());

    DWORD dwVolume = 0;
    m_AnyChatSDK.AudioGetVolume(BRAC_AD_WAVEOUT, dwVolume);
    ui->OutVolumeChangeSlider->setSliderPosition(dwVolume);//滑条的位置的设置

    dwVolume = 0;
    m_AnyChatSDK.AudioGetVolume(BRAC_AD_WAVEIN, dwVolume);
    ui->InVolumeChangeSlider->setSliderPosition(dwVolume);//滑条的位置的设置

//    SetTimer(this->winId(), REFRESH_SPEAKVOLUME_TIMER,100,(TIMERPROC)TimerProc_CallBack);  //参数为：窗口句柄，定时器，时间间隔，回调函数
//    SetTimer(this->winId(), REFRESH_RECORDSTATE_TIMER,1000,(TIMERPROC)TimerProc_CallBack);


    m_UserRect[0].setRect(9, 380, 170, 140);
    m_UserRect[1].setRect(190, 380, 170, 140);
    m_UserRect[2].setRect(370, 380, 170, 140);
    m_UserRect[3].setRect(550, 380, 170, 140);
}

//用户登录
void Widget::on_loginBtn_clicked()
{
    bool ok;
    QString strServerIp = ui->IplineEdit->text();           //IP地址
    QString strUserName = ui->UserLineEdit->text();         //用户名
    QString strPassword = ui->PwdLineEdit->text();          //密码
    int intPort = ui->PortLineEdit->text().toInt(&ok);      //端口号由字符串格式转换为整型格式

    if(strServerIp == "..." || intPort <= 0)    //如果服务器地址为空或端口号小于0的话
    {
        QMessageBox::warning(this,tr("warning"),tr("Invalid server IP address or port!"));
        return;
    }
    if(strUserName.isEmpty())                       //用户名为空
    {
         QMessageBox::warning(this,tr("warning"),tr("Must input username for login system!"));
    }

    m_AnyChatSDK.Connect((LPCTSTR)strServerIp.toStdString().c_str(), intPort);   //？用GetBuffer
    m_AnyChatSDK.Login((LPCTSTR)strUserName.toStdString().c_str(), (LPCTSTR)strPassword.toStdString().c_str(), 0);
}

//进入房间
void Widget::on_enterRoomBtn_clicked()
{
    QString roomId = ui->RoomIDlineEdit->text();
    QString pwd = "";
    m_AnyChatSDK.EnterRoom(roomId.toInt(), (LPCTSTR)pwd.toStdString().c_str() , 0);
}

//离开房间
void Widget::on_leaveRoomBtn_clicked()
{
    m_AnyChatSDK.LeaveRoom(1);
    //保留自己的userid, 因为这儿只是leaveroom, 并非logout
    for(int i = 1; i < DEMO_SHOW_USER_NUM; i ++)
    {
        m_iUserID[i] = -1;
    }
}

//用户注销
void Widget::on_logoutBtn_clicked()
{
    m_AnyChatSDK.Logout();
    for(int i = 0; i < DEMO_SHOW_USER_NUM; i++)
    {
        m_iUserID[i] = -1;
    }
}

//释放资源
void Widget::on_releaseBtn_clicked()
{
    m_AnyChatSDK.Release();
    for(int i = 0; i < DEMO_SHOW_USER_NUM; i++)
    {
        m_iUserID[i] = -1;
    }
    m_dwTransTaskId = -1;
}

//传输文件
void Widget::on_sendFileBtn_clicked()
{
    if(m_dwTransTaskId != -1)
        return;

    QString path = QFileDialog::getOpenFileName(this);  //NULL, tr("打开"), "/", tr("Any files(*)")
    if(! path.isEmpty())
    {
        DWORD dwTaskId = 0 ;
        DWORD wParam = 1 ;
        DWORD lParam = 2;
        DWORD dwFlags = 0;
        AppendLogString(path);
        DWORD ret = m_AnyChatSDK.TransFile(m_iUserID[1], (LPCTSTR)path.toStdString().c_str(), wParam, lParam, dwFlags, dwTaskId);
        if(ret == GV_ERR_SUCCESS)      //0表示任务建立成功
        {
            m_dwTransTaskId = dwTaskId;
            QString str;
            str.sprintf("%d", m_dwTransTaskId);
            AppendLogString(str);
            SetTimer(this->winId(), REFRESH_TRANSTASK_STATUS_TIMER,100,(TIMERPROC)TimerProc_CallBack);
        }
        else
        {
            QString strError;
            strError.sprintf("创建文件传输任务失败，出错代码：%d", ret);
            AppendLogString(strError);
            ui->fileStatuslabel->setText("文件传输失败！");
        }
    }
}

//传输缓冲区
void Widget::on_TransbufBtn_clicked()
{
    if(m_dwTransTaskId != -1)	// 演示程序为了简洁，同时只允许传一个任务，实际上SDK是可以多任务并发的
        return;

    PCHAR lpBuf = (PCHAR)malloc(10*1024);		// 为了演示，创建一个10KByte大小的缓冲区
    if(!lpBuf)
        return;
    DWORD dwLen = 10*1024;
    lpBuf[1000] = 'Y';			// 演示的需要，为了验证收到的数据是否正确，在缓冲区中间某个位置设置一个标志，对方接收后，可判断该标志是否为设定值

    DWORD dwTaskId = 0;
    DWORD wParam = 3;			// 上层应用程序可自定义wParam、lParam的值，这两个参数的值将被回调给对方
    DWORD lParam = 4;
    DWORD dwFlags = 0;			// 该标志设置为0，则SDK将自动根据网络状态选择合适的传输途径（TCP、UDP or P2P）
    DWORD ret = m_AnyChatSDK.TransBufferEx(m_iUserID[1],(PBYTE)lpBuf,dwLen,wParam,lParam,dwFlags,dwTaskId);
    if(ret == GV_ERR_SUCCESS)
    {
            m_dwTransTaskId = dwTaskId;
            SetTimer(this->winId(), REFRESH_TRANSTASK_STATUS_TIMER,100,(TIMERPROC)TimerProc_CallBack);

    }
    else
    {
            QString strError;
            strError.sprintf("创建缓冲区传输任务失败，出错代码:%d",ret);
            AppendLogString(strError);
            ui->fileStatuslabel->setText("");
    }
    // 缓冲区调用完成后， 可以立即释放掉
    free(lpBuf);
}

//发送信息
void Widget::on_sendMessageBtn_clicked()
{
    QString message = ui->messagelineEdit->text();
    if((m_AnyChatSDK.SendTextMessage(-1, NULL, (LPCTSTR)message.toStdString().c_str(), message.toStdString().length()))== 0)  //发送成功
    {
        QDateTime time = QDateTime::currentDateTime();    //获取系统当前时间
        QString strTime = time.toString("  yyyy-MM-dd hh:mm:ss ");
        CHAR username[30];
        m_AnyChatSDK.GetUserName(m_iUserID[0],username,sizeof(username));
        AppendLogString(username + strTime);
        AppendLogString(message);
    }
}

//画质调试
void Widget::on_VideopropertyBtn_clicked()
{
    QString str = "AnyChat 本地视频画质调节";
    m_AnyChatSDK.ShowLVProperty(this->winId(), (LPCTSTR)str.toStdString().c_str(), 0, 0);
}

//静音检测
void Widget::on_VADcheckBox_clicked()
{
    m_bEnableVAD = ui->VADcheckBox->checkState();
    m_AnyChatSDK.SetSDKOption(BRAC_SO_AUDIO_VADCTRL, (PCHAR)&m_bEnableVAD, sizeof(m_bEnableVAD));
}

//回音消除
void Widget::on_AECcheckBox_clicked()
{
    m_bEnableEcho = ui->AECcheckBox->checkState();
    m_AnyChatSDK.SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, (PCHAR)&m_bEnableEcho, sizeof(m_bEnableEcho));
}

//自动增益
void Widget::on_AGCcheckBox_clicked()
{
    m_bEnableAGC = ui->AGCcheckBox->checkState();
    m_AnyChatSDK.SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, (PCHAR)&m_bEnableAGC, sizeof(m_bEnableAGC));
}

//噪声控制
void Widget::on_NScheckBox_clicked()
{
    m_bEnableNS = ui->NScheckBox->checkState();
    m_AnyChatSDK.SetSDKOption(BRAC_SO_AUDIO_NSCTRL, (PCHAR)&m_bEnableNS, sizeof(m_bEnableNS));
}

//选择视频设备
void Widget::on_VideocomboBox_activated(QString logstr )    //logstr是将选中的字符串
{
    m_AnyChatSDK.SelectVideoCapture((LPCTSTR)logstr.toStdString().c_str());
}

//选择音频设备
void Widget::on_AudiocomboBox_activated(QString logstr)
{
    m_AnyChatSDK.SelectAudioCapture((LPCTSTR)logstr.toStdString().c_str());
}

//刷新设备列表
void Widget::on_RefreshBtn_clicked()
{
    // 刷新视频采集设备下拉列表
    PCHAR DeviceName[10] = {0};
    DWORD DeviceNum = 10;
    m_AnyChatSDK.EnumVideoCapture(DeviceName, DeviceNum);

    ui->VideocomboBox->clear();
    int i = 0;
    for(i = 0; i < (int)DeviceNum; i ++)
    {
        if(DeviceName[i])
        {
            ui->VideocomboBox->insertItem(i+1, DeviceName[i]);
            ::GlobalFree((HGLOBAL) DeviceName[i]);
            DeviceName[i] = NULL;
        }
    }

    // 选择当前打开的视频采集设备
    CHAR szVideoDeviceName[100] = {0};
    m_AnyChatSDK.GetCurVideoCapture(szVideoDeviceName, sizeof(szVideoDeviceName));

    //刷新音频采集设备下拉列表
    DeviceNum = 10;
    m_AnyChatSDK.EnumAudioCapture(DeviceName, DeviceNum);

    ui->AudiocomboBox->clear();
    for(i = 0; i < (int)DeviceNum; i++)
    {
        if(DeviceName[i])
        {
            ui->AudiocomboBox->insertItem(i+1, DeviceName[i]);
            ::GlobalFree((HGLOBAL)DeviceName[i]);
            DeviceName[i] = NULL;
        }
    }

    //选择当前打开的音频采集设备
    CHAR szAudioDeviceName[100] = {0};
    m_AnyChatSDK.GetCurAudioCapture(szAudioDeviceName, sizeof(szAudioDeviceName));
}

//控制输出声音的变化
void Widget::on_OutVolumeChangeSlider_valueChanged(int value)
{
     m_AnyChatSDK.AudioSetVolume(BRAC_AD_WAVEOUT, value);
}

//控制输入声音的变化
void Widget::on_InVolumeChangeSlider_valueChanged(int value)
{
    m_AnyChatSDK.AudioSetVolume(BRAC_AD_WAVEIN, value);
}

//视频控制0
void Widget::on_Videoctrl0Btn_clicked()
{
    // 为了演示程序简单，这儿采用静态变量保存上一次的状态，可能不准确，因为可能在别的地方有打开，或是关闭的操作，下同
    // 特别是当前用户离开房间，别的用户再进来时，初始状态将不准确
    static BOOL bLastState = TRUE;
    if(m_iUserID[0] != -1)
    {
        m_AnyChatSDK.UserCameraControl(m_iUserID[0], !bLastState);
        bLastState = !bLastState;
    }
}

//视频控制1
void Widget::on_Videoctrl1Btn_clicked()
{
    static BOOL bLastState = TRUE;
    if(m_iUserID[1] != -1)     //等于-1，表示对本地进行控制，不等于的话，向对方发出一个视频请求
    {
        m_AnyChatSDK.UserCameraControl(m_iUserID[1], !bLastState);
        bLastState = !bLastState;
    }
}

//视频控制2
void Widget::on_Videoctrl2Btn_clicked()
{
    static BOOL bLastState = TRUE;
    if(m_iUserID[2] != -1)     //等于-1，表示对本地进行控制，不等于的话，向对方发出一个视频请求
    {
        m_AnyChatSDK.UserCameraControl(m_iUserID[2], !bLastState);
        bLastState = !bLastState;
    }
}

//视频控制3
void Widget::on_Videoctrl3Btn_clicked()
{
    static BOOL bLastState = TRUE;
    if(m_iUserID[3] != -1)     //等于-1，表示对本地进行控制，不等于的话，向对方发出一个视频请求
    {
        m_AnyChatSDK.UserCameraControl(m_iUserID[3], !bLastState);
        bLastState = !bLastState;
    }
}

//音频控制0
void Widget::on_Audioctrl0Btn_clicked()
{
    static BOOL bLastState = TRUE;
    if(m_iUserID[0] != -1)    //同样为-1的话，就是对本地用户发言进行控制，不为-1的话，向对方提出一个音频请求
    {
            m_AnyChatSDK.UserSpeakControl(m_iUserID[0],!bLastState);  //bLastState为true,表示请求发言，为false，表示停止发言
            bLastState = !bLastState;
    }
}

//音频控制1
void Widget::on_Audioctrl1Btn_clicked()
{
    static BOOL bLastState = TRUE;
    if(m_iUserID[1] != -1)    //同样为-1的话，就是对本地用户发言进行控制，不为-1的话，向对方提出一个音频请求
    {
            m_AnyChatSDK.UserSpeakControl(m_iUserID[1],!bLastState);  //bLastState为true,表示请求发言，为false，表示停止发言
            bLastState = !bLastState;
    }
}

//音频控制2
void Widget::on_Audioctrl2Btn_clicked()
{
    static BOOL bLastState = TRUE;
    if(m_iUserID[2] != -1)    //同样为-1的话，就是对本地用户发言进行控制，不为-1的话，向对方提出一个音频请求
    {
            m_AnyChatSDK.UserSpeakControl(m_iUserID[2],!bLastState);  //bLastState为true,表示请求发言，为false，表示停止发言
            bLastState = !bLastState;
    }
}

//音频控制3
void Widget::on_Audioctrl3Btn_clicked()
{
    static BOOL bLastState = TRUE;
    if(m_iUserID[3] != -1)    //同样为-1的话，就是对本地用户发言进行控制，不为-1的话，向对方提出一个音频请求
    {
            m_AnyChatSDK.UserSpeakControl(m_iUserID[3],!bLastState);  //bLastState为true,表示请求发言，为false，表示停止发言
            bLastState = !bLastState;
    }
}

//录像控制0
void Widget::on_Recordctrl0Btn_clicked()
{
    static BOOL bLastState = FALSE;
    if(m_iUserID[0] != -1)
    {
            m_AnyChatSDK.StreamRecordCtrl(m_iUserID[0],!bLastState,0,0);
            bLastState = !bLastState;
    }
}

//录像控制1
void Widget::on_Recordctrl1Btn_clicked()
{
    static BOOL bLastState = FALSE;
    if(m_iUserID[1] != -1)
    {
            m_AnyChatSDK.StreamRecordCtrl(m_iUserID[1],!bLastState,0,0);
            bLastState = !bLastState;
    }
}

//录像控制2
void Widget::on_Recordctrl2Btn_clicked()
{
    static BOOL bLastState = FALSE;
    if(m_iUserID[2] != -1)
    {
            m_AnyChatSDK.StreamRecordCtrl(m_iUserID[2],!bLastState,0,0);
            bLastState = !bLastState;
    }
}

//录像控制3
void Widget::on_Recordctrl3Btn_clicked()
{
    static BOOL bLastState = FALSE;
    if(m_iUserID[3] != -1)
    {
            m_AnyChatSDK.StreamRecordCtrl(m_iUserID[3],!bLastState,0,0);
            bLastState = !bLastState;
    }
}

//快照0
void Widget::on_Snapshotctrl0Btn_clicked()     //快照，相当于在视频当中拍下一张照片
{
    if(m_iUserID[0] != -1)
        m_AnyChatSDK.SnapShot(m_iUserID[0], 0, 0);
}

//快照1
void Widget::on_Snapshotctrl1Btn_clicked()
{
    if(m_iUserID[1] != -1)
        m_AnyChatSDK.SnapShot(m_iUserID[1], 0, 0);
}

//快照2
void Widget::on_Snapshotctrl2Btn_clicked()
{
    if(m_iUserID[2] != -1)
        m_AnyChatSDK.SnapShot(m_iUserID[2], 0, 0);
}

//快照3
void Widget::on_Snapshotctrl3Btn_clicked()
{
    if(m_iUserID[3] != -1)
        m_AnyChatSDK.SnapShot(m_iUserID[3], 0, 0);
}


// 绘制用户视频
void Widget::DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader)
{
    //
}


// 录音的音量发生改变
void Widget::OnWaveInVolumeChange(DWORD dwVolume)
{
    ui->InVolumeChangeSlider->setValue(dwVolume);
}

// 放音的音量发生改变
void Widget::OnWaveOutVolumeChange(DWORD dwVolume)
{
    ui->OutVolumeChangeSlider->setValue(dwVolume);
}


// 收到消息：客户端连接服务器 wParam（BOOL）表示是否连接成功
LRESULT Widget::OnGVClientConnect(WPARAM wParam, LPARAM lParam)
{
    bool bSuccess = (bool)wParam;
    AppendLogString(bSuccess ? "连接服务器成功......" : "连接服务器失败......");
    return 0;
}

// 收到消息：客户端登录系统 wParam （INT）表示自己的用户ID号, lParam （INT）表示登录结果：0 成功，否则为出错代码，参考出错代码定义
LRESULT Widget::OnGVClientLogin(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
    DWORD dwUserID = wParam;
    if(lParam == 0)
    {
            CHAR username[30];
            m_AnyChatSDK.GetUserName(dwUserID,username,sizeof(username));
            logstr.sprintf("登录服务器成功，自己的用户编号为：%d(%s)",wParam,username);

            // 将用户的ID保存在第一个位置，否则在回调函数里面可能找不到绘制的位置
            //m_iUserID[0] = dwUserID;
    }
    else
            logstr.sprintf("登录服务器失败，出错代码为： %d ",lParam);

    AppendLogString(logstr);
    return 0;
}

// 收到消息：客户端进入房间  wParam （INT）表示所进入房间的ID号,lParam （INT）表示是否进入房间：0成功进入，否则为出错代码
LRESULT Widget::OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam)
{
        QString logstr;
        INT roomid = (INT)wParam;
        if(lParam == 0)
        {
                logstr.sprintf("成功进入编号为：%d 的房间",roomid);

                m_AnyChatSDK.SetVideoPos(-1, this->winId(), m_UserRect[0].left(), m_UserRect[0].top(), m_UserRect[0].right(), m_UserRect[0].bottom());
                m_AnyChatSDK.UserCameraControl(-1,TRUE);
                m_AnyChatSDK.UserSpeakControl(-1,TRUE);
        }
        else
                logstr.sprintf("申请进入房间失败，出错代码为： %d ",lParam);

        AppendLogString(logstr);
        return 0;
}

// 收到当前房间的在线用户信息 wParam （INT）表示在线用户数（不包含自己）,lParam （INT）表示房间ID
LRESULT Widget::OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam)
 {
     QString logstr;
     int onlinenum = (int)wParam;
     logstr.sprintf("在编号为：%d的房间共有%d位在线用户",lParam, onlinenum);
     AppendLogString(logstr);

     DWORD dwUserNum = 0;
     m_AnyChatSDK.GetOnlineUser(NULL, dwUserNum);      //首先获取房间内在线人数
     if(!dwUserNum)
         return 0;

     LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD) *dwUserNum);
     m_AnyChatSDK.GetOnlineUser(lpdwUserList, dwUserNum);

     for(int i = 0; i < (int)dwUserNum; i++)
     {
         DWORD userid = lpdwUserList[i];
         // 给用户找一个空的位置显示面板（第0号位置留给自己）
         INT site = -1;
         for(INT i=1; i<DEMO_SHOW_USER_NUM; i++)
        {
            if(m_iUserID[i] == -1)
            {
                site = i;
                break;
             }
         }
         if(site != -1)
         {
             m_AnyChatSDK.SetVideoPos(userid, this->winId(), m_UserRect[site].left(), m_UserRect[site].top(), m_UserRect[site].right(), m_UserRect[site].bottom());
             m_AnyChatSDK.UserCameraControl(userid, true);
             m_AnyChatSDK.UserSpeakControl(userid, true);

             DWORD dwState = 0;
             m_AnyChatSDK.GetCameraState(userid, dwState);
             logstr.sprintf("用户%d的视频状态是：%d", userid, dwState);
             AppendLogString(logstr);

             m_iUserID[site] = userid;
         }
         else
             break;
     }
     free(lpdwUserList);
     return 0;
 }

// 收到消息：用户的音频设备状态变化消息  wParam （INT）表示用户ID号 lParam （BOOL）表示该用户是否已打开音频采集设备
LRESULT Widget::OnGVClientMicStateChange(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
    logstr.sprintf("编号为：%d 的用户 ", wParam);
    logstr.append( lParam ? "打开":"关闭");
    logstr.append(" 本地Mic设备");
    AppendLogString(logstr);
    return 0;
}

// 收到消息：用户进入（离开）房间 wParam （INT）表示用户ID号,lParam （BOOL）表示该用户是进入（TRUE）或离开（FALSE）房间
LRESULT Widget::OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
     int userid = (int)wParam;
     bool bEnter = (bool)lParam;

     char username[30]={0};
     m_AnyChatSDK.GetUserNameW(userid,username,sizeof(username));
     logstr.sprintf("编号为：%d 的用户(%s) ",userid,username);
     logstr.append(bEnter ? "进入" : "离开");
     logstr.append("房间");
     AppendLogString(logstr);

     if(bEnter)
     {
            // 给用户找一个空的位置显示面板（第0号位置留给自己）
            int site = -1;
            for(INT i=1; i<DEMO_SHOW_USER_NUM; i++)
            {
                if(m_iUserID[i] == -1)
                {
                        site = i;
                        break;
                 }
             }
            if(site != -1)
            {
                m_AnyChatSDK.SetVideoPos(userid,this->winId(),m_UserRect[site].left(),m_UserRect[site].top(),m_UserRect[site].right(),m_UserRect[site].bottom());
                m_AnyChatSDK.UserCameraControl(userid,TRUE);
                m_AnyChatSDK.UserSpeakControl(userid,TRUE);
                m_iUserID[site] = userid;
            }
        }
        else
        {
            //清除该用户占用位置的信息
            for(INT i=1; i<DEMO_SHOW_USER_NUM; i++)
            {
                 if(m_iUserID[i] == userid)
                 {
                        m_iUserID[i] = -1;
                        break;
                  }
            }
      }
      return 0;
}

//收到消息：网络连接已关闭    (该消息只有在客户端连接服务器成功之后，网络异常中断之时触发)
LRESULT Widget::OnGVClientLinkClose(WPARAM wParam, LPARAM lParam)
{
    AppendLogString("网络连接已关闭（断开）");

    for(INT i=0; i<DEMO_SHOW_USER_NUM; i++)
    {
            m_iUserID[i] = -1;
    }
    return 0;
}

//用户聊天模式发生变化  wParam （INT）表示用户ID号,lParam （INT）表示用户的当前聊天模式
LRESULT Widget::OnGVClientChatModeChange(WPARAM wParam, LPARAM lParam)
{
    QString logstr;
    int userid = (int)wParam;
    int chatmode = (int)lParam;

    if(m_iUserID[0] == userid)   //聊天模式为0，表示公聊。为1，表示私聊
    {
            logstr.sprintf("自己（%d ）的聊天模式改变，当前聊天模式为：",userid);
            logstr.append( chatmode == 0 ? "公聊模式" : "私聊模式");
    }
    else
    {
            logstr.sprintf("编号为：%d 的用户聊天模式改变，当前聊天模式为：",userid);
            logstr.append(chatmode == 0 ? "公聊模式" : "私聊模式");
    }
    AppendLogString(logstr);
    return 0;
}

//定时器回调函数
void CALLBACK Widget::TimerProc_CallBack(HWND hwnd, UINT uMsg, UINT nIDEvent, DWORD dwTime)
{
    switch(nIDEvent)
    {
    case REFRESH_TRANSTASK_STATUS_TIMER:     // 刷新缓冲区传输任务状态
        {
            if(pthis->m_dwTransTaskId == -1)
            {
                KillTimer(pthis->winId(), REFRESH_TRANSTASK_STATUS_TIMER);
                break;
            }
            DWORD ret;
            DWORD dwStatus = 0;
            ret = pthis->m_AnyChatSDK.QueryTransTaskInfo(-1, pthis->m_dwTransTaskId,BRAC_TRANSTASK_STATUS,(PCHAR)&dwStatus,sizeof(DWORD));
            if(ret != GV_ERR_SUCCESS)
            {
                KillTimer(pthis->winId(), REFRESH_TRANSTASK_STATUS_TIMER);
                pthis->m_dwTransTaskId = -1;
                pthis->ui->fileStatuslabel->setText("");
                if(ret == GV_ERR_TRANSBUF_NOTASK)
                    pthis->AppendLogString("传输任务不在在，可能对方已离开房间！");
                else
                   pthis-> AppendLogString("查询任务信息失败！");
                break;
            }
            double dbProgress = 0.0;
            pthis->m_AnyChatSDK.QueryTransTaskInfo(-1,pthis->m_dwTransTaskId,BRAC_TRANSTASK_PROGRESS,(PCHAR)&dbProgress,sizeof(DOUBLE));
            DWORD dwBitrate  = 0;
            pthis->m_AnyChatSDK.QueryTransTaskInfo(-1,pthis->m_dwTransTaskId,BRAC_TRANSTASK_BITRATE,(PCHAR)&dwBitrate,sizeof(DWORD));

            QString strStatus;
            switch(dwStatus)
            {
            case 1:		strStatus = "Ready";        break;
            case 2:		strStatus = "Process";      break;
            case 3:		strStatus = "Finish";       break;
            case 4:		strStatus = "Cancel";       break;
            case 5:		strStatus = "Reject";       break;
            default:            strStatus = "Unkonw";       break;
            }
            if(dwStatus == 3)           //finish
            {
                KillTimer(pthis->winId(), REFRESH_TRANSTASK_STATUS_TIMER);
                pthis->m_dwTransTaskId = -1;
                pthis->AppendLogString("传输任务已完成！");
            }
           QString strBitrate;
            if(dwBitrate >= 1000 * 1000)
                    strBitrate.sprintf("%.2f Mbps",(float)dwBitrate/1000/1000);
            else if(dwBitrate >= 1000)
                    strBitrate.sprintf("%.2f Kbps",(float)dwBitrate/1000);
            else
                    strBitrate.sprintf("%.2f bps",(float)dwBitrate);

           QString strNotify;
           strNotify.sprintf("-%.2f%-", dbProgress);
           pthis->ui->fileStatuslabel->setText(strStatus + strNotify + strBitrate);   //QString类型的能相加表示合并
      }
    case  REFRESH_SPEAKVOLUME_TIMER:		// 刷新用户说话音量
        {
            double fSpeakVolume = 0.0;
            if(pthis->m_iUserID[0] != -1 && pthis->m_AnyChatSDK.QueryUserState(pthis->m_iUserID[0],BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume,sizeof(DOUBLE)) == GV_ERR_SUCCESS)
                    pthis->ui->Speak0ProgressBar->setValue((INT)fSpeakVolume);
            else
                    pthis->ui->Speak0ProgressBar->setValue(0);

            fSpeakVolume = 0.0;
            if(pthis->m_iUserID[1] != -1 && pthis->m_AnyChatSDK.QueryUserState(pthis->m_iUserID[1],BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume,sizeof(DOUBLE)) == GV_ERR_SUCCESS)
                    pthis->ui->Speak1ProgressBar->setValue((INT)fSpeakVolume);
            else
                   pthis->ui->Speak1ProgressBar->setValue(0);

            fSpeakVolume = 0.0;
            if(pthis->m_iUserID[2] != -1 && pthis->m_AnyChatSDK.QueryUserState(pthis->m_iUserID[2],BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume,sizeof(DOUBLE)) == GV_ERR_SUCCESS)
                    pthis->ui->Speak2ProgressBar->setValue((INT)fSpeakVolume);
            else
                    pthis->ui->Speak2ProgressBar->setValue(0);

            fSpeakVolume = 0.0;
            if(pthis->m_iUserID[3] != -1 && pthis->m_AnyChatSDK.QueryUserState(pthis->m_iUserID[3],BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume,sizeof(DOUBLE)) == GV_ERR_SUCCESS)
                    pthis->ui->Speak3ProgressBar->setValue((INT)fSpeakVolume);
            else
                    pthis->ui->Speak3ProgressBar->setValue(0);
        }
        break;
    case REFRESH_RECORDSTATE_TIMER:		// 刷新录像状态
        {
                DWORD dwRecordState = 0;
                if(pthis->m_iUserID[0] != -1 && pthis->m_AnyChatSDK.QueryUserState(pthis->m_iUserID[0],BRAC_USERSTATE_RECORDING,(PCHAR)&dwRecordState,sizeof(DWORD)) == GV_ERR_SUCCESS)
                {
                        static BOOL bShow = FALSE;
                        bShow = dwRecordState ? !bShow : FALSE;
                        if(bShow)
                        {
                            pthis->ui->RecordState0->show();
                        }
                        else
                            pthis->ui->RecordState0->hide();
                }

                dwRecordState = 0;
                if(pthis->m_iUserID[1] != -1 && pthis->m_AnyChatSDK.QueryUserState(pthis->m_iUserID[1],BRAC_USERSTATE_RECORDING,(PCHAR)&dwRecordState,sizeof(DWORD)) == GV_ERR_SUCCESS)
                {
                        static BOOL bShow = FALSE;
                        bShow = dwRecordState ? !bShow : FALSE;
                        if(bShow)
                        {
                            pthis->ui->RecordState1->show();
                        }
                        else
                            pthis->ui->RecordState1->hide();
                }

                dwRecordState = 0;
                if(pthis->m_iUserID[2] != -1 && pthis->m_AnyChatSDK.QueryUserState(pthis->m_iUserID[2],BRAC_USERSTATE_RECORDING,(PCHAR)&dwRecordState,sizeof(DWORD)) == GV_ERR_SUCCESS)
                {
                        static BOOL bShow = FALSE;
                        bShow = dwRecordState ? !bShow : FALSE;
                        if(bShow)
                        {
                            pthis->ui->RecordState2->show();
                        }
                        else
                            pthis->ui->RecordState2->hide();
                }
                dwRecordState = 0;
                if(pthis->m_iUserID[3] != -1 && pthis->m_AnyChatSDK.QueryUserState(pthis->m_iUserID[3],BRAC_USERSTATE_RECORDING,(PCHAR)&dwRecordState,sizeof(DWORD)) == GV_ERR_SUCCESS)
                {
                        static BOOL bShow = FALSE;
                        bShow = dwRecordState ? !bShow : FALSE;
                        if(bShow)
                        {
                            pthis->ui->RecordState3->show();
                        }
                        else
                            pthis->ui->RecordState3->hide();
                }
        }
        break;
        default:
        break;
    }

}

// 视频数据回调函数
void CALLBACK Widget::VideoData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue)
{
    Widget *pDemoDlg = (Widget*)lpUserValue;
    if(pDemoDlg)
    {
          pDemoDlg->DrawUserVideo(dwUserid,lpBuf,dwLen,bmiHeader);
    }
}

// 音频数据回调函数
void CALLBACK Widget::AudioData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue)
{
    Widget *pDemoDlg = (Widget*)lpUserValue;
    if(pDemoDlg)
    {
        // do something ...
    }
}

// 音量更改回调函数
void CALLBACK Widget::VolumeChange_CallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue)
{
    Widget *pDemoDlg = (Widget*)lpUserValue;
    if(pDemoDlg)
    {
        if(device == BRAC_AD_WAVEIN)
                pDemoDlg->OnWaveInVolumeChange(dwCurrentVolume);
        else
                pDemoDlg->OnWaveOutVolumeChange(dwCurrentVolume);
    }
}

// 透明通道数据扩展回调函数定义
void CALLBACK Widget::TransBufferEx_CallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
        Widget *pDemoDlg = (Widget*)lpUserValue;
        if(pDemoDlg)
        {
                BOOL bSuccess = FALSE;
                if(dwLen > 1000)
                {
                        bSuccess = lpBuf[1000] == 'Y' ? TRUE : FALSE;
                }
                QString strNotify;
                strNotify.sprintf("TransBuffer_CallBack:dwUserid-%d, bufSize-%d",dwUserid,dwLen,bSuccess ? "Success" : "Fail");
                pDemoDlg->AppendLogString(strNotify);
        }
}

// 透明通道数据回调函数定义
void CALLBACK Widget::TransBuffer_CallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
        Widget *pDemoDlg = (Widget*)lpUserValue;
        if(pDemoDlg)
        {
                QString strNotify;
                strNotify.sprintf("TransBuffer_CallBack:dwUserid-%d, bufSize-%d",dwUserid,dwLen);
                pDemoDlg->AppendLogString(strNotify);
        }
}

// 文件传输回调函数定义
void CALLBACK Widget::TransFile_CallBack(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
        Widget *pDemoDlg = (Widget*)lpUserValue;
        if(pDemoDlg)
        {
                QString strNotify;
                strNotify.sprintf("TransFile_CallBack:dwUserid-%d, lpFileName-%s, lpTempFilePath-%s",dwUserid,lpFileName,lpTempFilePath);
                pDemoDlg->AppendLogString(strNotify);
        }
}

// 录像、快照任务完成回调函数定义
void CALLBACK Widget::RecordSnapShot_CallBack(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType, LPVOID lpUserValue)
{
        Widget *pDemoDlg = (Widget*)lpUserValue;
        if(pDemoDlg)
        {
                QString strNotify;
                strNotify.sprintf("%s CallBack:dwUserid-%d, FilePathName-%s",bRecordType?"Record":"SnapShot",(int)dwUserid,lpFileName);
                pDemoDlg->AppendLogString(strNotify);
        }
}

// SDK Filter 通信数据回调函数定义
void CALLBACK Widget::SDKFilterData_CallBack(LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
        Widget *pDemoDlg = (Widget*)lpUserValue;
        if(pDemoDlg)
        {
                QString strNotify;
                strNotify.sprintf("SDK Filter CallBack:%s",lpBuf);
                pDemoDlg->AppendLogString(strNotify);
        }
}

// 文字消息回调函数定义
void CALLBACK Widget::TextMessage_CallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue)
{
        BR_AFX_MANAGE_STATE;
        Widget*	pDemoDlg = (Widget*)lpUserValue;
        QString message;
        if(pDemoDlg)
        {
            QDateTime time = QDateTime::currentDateTime();    //获取系统当前时间
            QString strTime = time.toString("  yyyy-MM-dd hh:mm:ss ");
            CHAR username[30];
            pDemoDlg->m_AnyChatSDK.GetUserName(dwFromUserid,username,sizeof(username));
            pDemoDlg->AppendLogString(username + strTime);
            message.sprintf("%s", lpMsgBuf);
            pDemoDlg->AppendLogString(message);
        }
}

// 异步消息通知回调函数定义
void CALLBACK Widget::NotifyMessage_CallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue)
{
        BR_AFX_MANAGE_STATE;
        Widget*	pAnyChatSDKProc = (Widget*)lpUserValue;
        if(!pAnyChatSDKProc)
                return;
        switch(dwNotifyMsg)
        {
        case WM_GV_CONNECT:		pAnyChatSDKProc->OnGVClientConnect(wParam,NULL);		break;
        case WM_GV_LOGINSYSTEM:		pAnyChatSDKProc->OnGVClientLogin(wParam,lParam);                break;
        case WM_GV_ENTERROOM:           pAnyChatSDKProc->OnGVClientEnterRoom(wParam,lParam);            break;
        case WM_GV_MICSTATECHANGE:	pAnyChatSDKProc->OnGVClientMicStateChange(wParam,lParam);       break;
        case WM_GV_USERATROOM:		pAnyChatSDKProc->OnGVClientUserAtRoom(wParam,lParam);           break;
        case WM_GV_LINKCLOSE:           pAnyChatSDKProc->OnGVClientLinkClose(wParam, lParam);           break;
        case WM_GV_ONLINEUSER:		pAnyChatSDKProc->OnGVClientOnlineUser(wParam,lParam);           break;

        case WM_GV_CAMERASTATE:		pAnyChatSDKProc->OnAnyChatCameraStateChgMessage(wParam,lParam);	break;
        case WM_GV_CHATMODECHG:		pAnyChatSDKProc->OnGVClientChatModeChange(wParam,lParam);       break;
        case WM_GV_ACTIVESTATE:		pAnyChatSDKProc->OnAnyChatActiveStateChgMessage(wParam,lParam);	break;
        case WM_GV_P2PCONNECTSTATE:	pAnyChatSDKProc->OnAnyChatP2PConnectStateMessage(wParam,lParam);break;

        case WM_GV_PRIVATEREQUEST:	pAnyChatSDKProc->OnAnyChatPrivateRequestMessage(wParam,lParam);	break;
        case WM_GV_PRIVATEECHO:		pAnyChatSDKProc->OnAnyChatPrivateEchoMessage(wParam,lParam);	break;
        case WM_GV_PRIVATEEXIT:		pAnyChatSDKProc->OnAnyChatPrivateExitMessage(wParam,lParam);	break;

        case WM_GV_SDKWARNING:		pAnyChatSDKProc->OnAnyChatSDKWarningMessage(wParam,lParam);     break;

        default:
                break;
        }
        pAnyChatSDKProc->OnAnyChatNotifyMessageCallBack(dwNotifyMsg,wParam,lParam);
};








