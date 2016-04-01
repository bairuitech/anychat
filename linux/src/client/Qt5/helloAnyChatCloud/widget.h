#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QImage>
#include <QDebug>
#include <QString>
#include <QCloseEvent>
#include <windows.h>
#include <stdio.h>
#include <atltypes.h>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "BRAnyChatCoreSDK.h"

namespace Ui {
class Widget;
}

#define MAX_USER_NUM 10
#define MAX_VIDEOFRAME_NUM 2

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

	CRect m_UserRect[2];
    
    QString m_strLogInfo;           //显示sys消息
    QTimer *m_pTimer;               //定时器

    char*   m_lpLocalVideoFrame;    //本地视频缓冲
    int     m_iLocalVideoSize;      //本地视频缓冲大小

    char*   m_lpRemoteVideoFrame;   //远程视频缓冲
    int     m_iRemoteVideoSize;     //远程视频缓冲大小

    int     m_iUserID[MAX_USER_NUM];//其他用户ID号
    int     m_SelfId;               //自己的ID

    bool    m_isLogin;              // login server

    QNetworkAccessManager* m_http_manager;
    char m_sign_data[256];
    int  m_sign_ts;
    int  m_sign_err;
    QString m_qsign_data;

    void HelloChatInit();      //初始化
    void HelloChatLogin();     //登陆服务器
    void HelloChatRefreshUserList();//刷新列表,最后一个参数用于设置添加（0）或者删除(-1）用户

    void AppendLogString(QString logstr);
    void DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader,Widget *pWidget);
    //以下为异步消息回调，初始化的时候设置
    long OnGVClientConnect(WPARAM wParam, LPARAM lParam);
    long OnGVClientLogin(WPARAM wParam, LPARAM lParam);
    long OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam);
    long OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam);
    long OnGVClientMicStateChange(WPARAM wParam, LPARAM lParam);
    long OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam);
    long OnGVClientLinkClose(WPARAM wParam, LPARAM lParam);

    virtual void OnAnyChatCameraStateChgMessage(DWORD dwUserId, DWORD dwState) {}    // 用户摄像头状态改变消息
    virtual void OnAnyChatActiveStateChgMessage(DWORD dwUserId, DWORD dwState) {}    // 用户活动状态发生变化消息
    virtual void OnAnyChatP2PConnectStateMessage(DWORD dwUserId, DWORD dwState){}    // P2P连接状态变化消息
    virtual void OnAnyChatPrivateRequestMessage(DWORD dwUserId, DWORD dwRequestId) {}// 用户私聊请求消息
    virtual void OnAnyChatPrivateEchoMessage(DWORD dwUserId, DWORD dwErrorCode) {}   // 用户私聊请求回复消息
    virtual void OnAnyChatPrivateExitMessage(DWORD dwUserId, DWORD dwErrorCode) {}   // 用户退出私聊消息
    virtual void OnAnyChatSDKWarningMessage(DWORD dwErrorCode, DWORD dwReserved) {}  // SDK警告消息
    virtual void OnAnyChatNotifyMessageCallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam) {}// 异步消息通知回调函数

    void static CALLBACK VideoData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue);
    void static CALLBACK AudioData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue);
    void static CALLBACK NotifyMessage_CallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam, LPVOID lpUserValue);
    void static CALLBACK TextMessage_CallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue);
	void static CALLBACK TimerProc_CallBack(HWND hwnd, UINT uMsg, UINT nIDEvent, DWORD dwTime); //定时器回调函数

    void request_sign(QString server_url,
                      QString appid,
                      QString userid);

signals:
    void changeSysLogs(QString str); //回调返回信息

public slots:
    void setSysLogs(QString str);    //显示回调返回信息

private slots:
    void TimerProc();
    void response_callback(QNetworkReply* http_reply);

    virtual void closeEvent(QCloseEvent *event);//关闭窗口事件

    void on_UserlistWidget_doubleClicked(const QModelIndex &index);//双击用户列表事件<选择用户并请求视频>

    void on_SendMsg_Btn_clicked();

    void on_Appid_checkBox_clicked();

    void on_Login_btn_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
