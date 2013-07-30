Imports System.Windows.Forms.ListView

Public Class MainWnd

    Private Sub MainWnd_FormClosed(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        GCHandle2.Free()
        GCHandle1.Free()

        Dim ret As Integer
        ret = -1
        ret = BRAC_LeaveRoom(-1)
        If (ret <> 0) Then
            MsgBox("离开房间失败！")
        End If

        ret = -1
        ret = BRAC_Logout()
        If (ret <> 0) Then
            MsgBox("退出登录失败！")
        End If

        ret = -1
        ret = BRAC_Release()
        If (ret <> 0) Then
            MsgBox("释放SDK资源失败！")
        End If

        LoginWnd.Close()
    End Sub

    Private Sub MainWnd_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        LoginState.Text = "您尚未登录！"

        OpenAudio.Checked = True

        MyInfo.UserID = -1
        MyInfo.NickName = ""
        MyInfo.Level = ""
        MyInfo.AudioState = -1
        MyInfo.VideoState = -1

        LastOperation = 0

        Dim ret As Integer

        WaveInVolume.Value = 5
        ret = -1
        ret = BRAC_AudioSetVolume(BRAC_AudioDevice.BRAC_AD_WAVEOUT, 50)
        If (ret <> 0) Then
            PrintInfo("设置输出设备音量失败！")
        End If

        WaveOutVolume.Value = 3
        ret = -1
        ret = BRAC_AudioSetVolume(BRAC_AudioDevice.BRAC_AD_WAVEIN, 30)
        If (ret <> 0) Then
            PrintInfo("设置输入设备音量失败！")
        End If
    End Sub

    Private Sub OpenAudio_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenAudio.CheckedChanged
        Dim ret As Integer
        If (OpenAudio.Checked = True) Then
            ret = -1
            ret = BRAC_UserSpeakControl(-1, 1)
            If (ret <> 0) Then
                PrintInfo("打开本地音频失败！")
            End If
        Else
            ret = -1
            ret = BRAC_UserSpeakControl(-1, 0)
            If (ret <> 0) Then
                PrintInfo("关闭本地音频失败！")
            End If
        End If
    End Sub

    Private Sub OnlineUser_DoubleClick(ByVal sender As Object, ByVal e As System.EventArgs) Handles OnlineUser.DoubleClick
        Dim ret As Integer

        Dim AudioState As Integer
        Dim VideoState As Integer

        Dim Items As SelectedListViewItemCollection
        Items = OnlineUser.SelectedItems()
        If (Items.Count <> 1) Then
            Exit Sub
        End If

        Dim userid As Integer
        userid = Items.Item(0).Tag

        If (userid = MyInfo.UserID) Then
            Exit Sub
        End If

        If (LastOperation <> 0) Then
            ret = -1
            ret = BRAC_UserSpeakControl(LastOperation, 0)
            If (ret <> 0) Then
                PrintInfo("关闭上个操作用户音频失败！")
            End If

            ret = -1
            ret = BRAC_UserCameraControl(LastOperation, 0)
            If (ret <> 0) Then
                PrintInfo("关闭上个操作用户视频失败！")
            End If
        End If

        Dim ChatMode As Integer
        ret = -1
        ret = BRAC_GetUserChatMode(userid, ChatMode)
        If (ret <> 0) Then
            PrintInfo("获取远程用户聊天状态失败！")
        Else
            If (ChatMode = GV_CHATMODE_PRIVATE) Then
                PrintInfo("远程用户处于私聊状态，您暂时无法接收到远程用户的音视频数据！")
            End If
        End If

        ret = -1
        ret = BRAC_QueryUserStateEx(userid, BRAC_USERSTATE_HOLDMIC, AudioState, Len(AudioState))
        If (ret <> 0) Then
            PrintInfo("获取远程用户音频状态失败！")
        Else
            If (AudioState = 0) Then
                PrintInfo("远程用户尚未持有MIC，您暂时无法接收到远程用户的音频数据")
            End If
        End If
        ret = BRAC_UserSpeakControl(userid, 1)

        ret = -1
        ret = BRAC_QueryUserStateEx(userid, BRAC_USERSTATE_CAMERA, VideoState, Len(VideoState))
        If (ret <> 0) Then
            PrintInfo("获取远程用户视频状态失败！")
        Else
            If (VideoState = 0) Then
                PrintInfo("远程用户尚未安装视频，您暂时无法接收到远程用户的视频数据")
            ElseIf (VideoState = 1) Then
                PrintInfo("远程用户尚未打开视频，您暂时无法接收到远程用户的视频数据")
            End If
        End If
        ret = BRAC_SetVideoPos(userid, RemoteVideo.Handle, 0, 0, RemoteVideo.Width, RemoteVideo.Height)
        ret = BRAC_UserCameraControl(userid, 1)

        LastOperation = userid
        'Dim OperationSuccess As Boolean
        'OperationSuccess = False

        'ret = -1
        'ret = BRAC_QueryUserStateEx(userid, BRAC_USERSTATE_HOLDMIC, AudioState, Len(AudioState))
        'If (ret <> 0) Then
        'PrintInfo("获取远程用户音频状态失败！")
        'Else
        'If (AudioState = 1) Then
        'ret = -1
        'ret = BRAC_UserSpeakControl(userid, 1)
        'If (ret <> 0) Then
        'PrintInfo("请求远程音频失败！")
        'Else
        'OperationSuccess = True
        'End If
        'ElseIf (AudioState = 0) Then
        'PrintInfo("远程用户尚未持有MIC！")
        'End If
        'End If


        'ret = -1
        'ret = BRAC_QueryUserStateEx(userid, BRAC_USERSTATE_CAMERA, VideoState, Len(VideoState))
        'If (ret <> 0) Then
        'PrintInfo("获取远程用户视频状态失败！")
        'Else
        'If (VideoState = 2) Then
        'ret = -1
        'ret = BRAC_SetVideoPos(userid, RemoteVideo.Handle, 0, 0, RemoteVideo.Width, RemoteVideo.Height)
        'If (ret <> 0) Then
        'PrintInfo("设置远程视频位置失败！")
        'Else
        'ret = -1
        'ret = BRAC_UserCameraControl(userid, 1)
        'If (ret <> 0) Then
        'PrintInfo("请求远程视频失败！")
        'Else
        'OperationSuccess = True
        'End If
        'End If
        'ElseIf (VideoState = 1) Then
        'PrintInfo("远程用户尚未打开摄像头！")
        'ElseIf (VideoState = 0) Then
        'PrintInfo("远程用户没有摄像头！")
        'End If
        'End If

        'If (OperationSuccess) Then
        'LastOperation = userid
        'End If
    End Sub

    Private Sub SendTextMessage_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SendTextMessage.Click
        If (MessageToSend.Text = "") Then
            MsgBox("您不能发送空消息！")
            Exit Sub
        End If

        Dim Content As String

        Dim ret As Integer
        ret = -1
        ret = BRAC_SendTextMessage(-1, 0, MessageToSend.Text, (Len(MessageToSend.Text) + 1) * 2)
        If (ret <> 0) Then
            PrintInfo("发送文字消息失败！")
            Exit Sub
        End If

        Content = MyInfo.NickName & "说：" & vbCrLf
        Content = Content & MessageToSend.Text & vbCrLf

        PrintInfo(Content)
        MessageToSend.Text = ""
    End Sub

    Private Sub WaveOutVolume_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles WaveOutVolume.Scroll
        Dim ret As Integer
        ret = -1
        ret = BRAC_AudioSetVolume(BRAC_AudioDevice.BRAC_AD_WAVEOUT, WaveOutVolume.Value * 10)
        If (ret <> 0) Then
            PrintInfo("设置输出设备音量失败！")
        End If
    End Sub

    Private Sub WaveInVolume_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles WaveInVolume.Scroll
        Dim ret As Integer
        ret = -1
        ret = BRAC_AudioSetVolume(BRAC_AudioDevice.BRAC_AD_WAVEIN, WaveOutVolume.Value * 10)
        If (ret <> 0) Then
            PrintInfo("设置输入设备音量失败！")
        End If
    End Sub

    Private Sub OnlineUser_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OnlineUser.SelectedIndexChanged

    End Sub
End Class