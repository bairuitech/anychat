Imports System.Text
Imports System.Runtime.InteropServices
Module MainFunc
    Structure UserInfo
        Dim UserID As Integer
        Dim NickName As String
        Dim Level As String
        Dim AudioState As String
        Dim VideoState As String
    End Structure

    Public MyInfo As UserInfo

    Public LastOperation As Integer

    Public GCHandle1 As GCHandle
    Public GCHandle2 As GCHandle

    Public Const EM_GETLINECOUNT As Integer = &HBA
    Public Const EM_LINESCROLL As Integer = &HB6

    Public Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Integer, ByVal wMsg As Integer, ByVal wParam As Integer, ByVal lParam As Integer) As Integer

    Function InitSDK() As Boolean

        InitSDK = True

        Dim ret As Integer

        'Dim dwMainVer As Integer
        'Dim dwSubVer As Integer

        'dwMainVer = 0
        'dwSubVer = 0

        'Dim szCompileTime As String
        'szCompileTime = Space(128)

        'Dim ptr As IntPtr = Marshal.StringToHGlobalAnsi(szCompileTime)

        'ret = BRAC_GetSDKVersion(dwMainVer, dwSubVer, ptr, Len(szCompileTime))

        'If (ret <> 0) Then
        'MsgBox("获取SDK版本信息失败！")
        'End If
        'szCompileTime = Marshal.PtrToStringAnsi(ptr)
        'Marshal.FreeHGlobal(ptr)

        'szCompileTime = "SDK Compile Time：" & szCompileTime & vbCrLf

        'MsgBox("szCompileTime")
        '''''''''''''''如果要打印SDK版本，请取消上面的代码的注释''''''''''''''''


        ret = BRAC_ActiveCallLog(1)
        If (ret <> 0) Then
            MsgBox("打开SDK日志记录功能失败！")
        End If

        ret = BRAC_InitSDK(MainWnd.Handle.ToInt32, BRAC_FUNC_VIDEO_AUTODISP Or BRAC_FUNC_AUDIO_AUTOPLAY Or BRAC_FUNC_CONFIG_LOCALINI Or BRAC_FUNC_FIREWALL_OPEN Or BRAC_FUNC_CHKDEPENDMODULE Or BRAC_FUNC_AUDIO_VOLUMECALC Or BRAC_FUNC_AUDIO_AUTOVOLUME Or BRAC_FUNC_NET_SUPPORTUPNP)
        If (ret <> 0) Then
            MsgBox("初始化系统失败！")
            InitSDK = False
            Exit Function
        End If


        Dim mysub As New BRAC_TextMessage_CallBack(AddressOf TextMessage_CallBack)
        '这里注意下垃圾回收()

        GCHandle1 = GCHandle.Alloc(mysub)

        ret = BRAC_SetTextMessageCallBack(mysub, MainWnd.Handle)
        If (ret <> 0) Then
            MsgBox("设置文字消息回调函数失败！")
            InitSDK = False
            Exit Function
        End If

        Dim mysub1 As New BRAC_NotifyMessage_CallBack(AddressOf NotifyMessage_CallBack)

        GCHandle2 = GCHandle.Alloc(mysub1)

        ret = BRAC_SetNotifyMessageCallBack(mysub1, MainWnd.Handle)
        If (ret <> 0) Then
            MsgBox("设置异步消息通知回调函数失败！")
            InitSDK = False
            Exit Function
        End If

        'Dim mysub2 As New DelegateAudioDataCallBackProc(AddressOf AudioData_CallBack)
        'GCHandle.Alloc(mysub2)

        'ret = BRAC_SetAudioDataCallBack(mysub2, MainWnd.Handle.ToInt32)
    End Function

    Sub NotifyMessage_CallBack(ByVal dwNotifyMsg As Integer, ByVal wParam As Integer, ByVal lParam As Integer, ByVal lpUserValue As IntPtr)
        Dim ret As Integer
        Select Case dwNotifyMsg
            Case WM_GV_CONNECT
                If (wParam = 0) Then
                    MsgBox("连接服务器失败！")
                    MainWnd.Hide()
                    LoginWnd.Show()
                Else
                    PrintInfo("连接服务器成功")
                End If
            Case WM_GV_LOGINSYSTEM
                If (lParam = 0) Then
                    PrintInfo("登录系统成功")

                    MyInfo.UserID = wParam

                    ret = -1
                    Dim NickName As String
                    NickName = Space(128)
                    Dim ptr As IntPtr
                    ptr = Marshal.StringToHGlobalAnsi(NickName)
                    ret = BRAC_QueryUserState(wParam, BRAC_USERSTATE_NICKNAME, ptr, Len(NickName))
                    If (ret <> 0) Then
                        MsgBox("获取登录昵称失败！")
                    End If
                    NickName = Marshal.PtrToStringAnsi(ptr)
                    MyInfo.NickName = NickName
                    Marshal.FreeHGlobal(ptr)

                    MainWnd.LoginState.Text = "欢迎您 ID " & CStr(wParam) & " " & NickName
                Else
                    MsgBox("登录服务器失败！")
                    MainWnd.Hide()
                    LoginWnd.Show()
                End If
            Case WM_GV_ENTERROOM
                If (lParam = 0) Then
                    PrintInfo("进入房间成功")
                    ret = -1
                    ret = BRAC_SetVideoPos(-1, MainWnd.LocalVideo.Handle, 0, 0, MainWnd.LocalVideo.Width, MainWnd.LocalVideo.Height)
                    If (ret <> 0) Then
                        PrintInfo("设置本地视频位置失败！")
                    End If

                    ret = -1
                    ret = BRAC_UserCameraControl(-1, 1)
                    If (ret <> 0) Then
                        PrintInfo("打开本地摄像头失败！")
                    End If

                    ret = -1
                    ret = BRAC_UserSpeakControl(-1, 1)
                    If (ret <> 0) Then
                        PrintInfo("打开本地音频失败！ ")
                    End If

                    ShowOnlineUser()
                Else
                    MsgBox("进入房间失败！")
                    MainWnd.Hide()
                    LoginWnd.Show()
                End If
            Case WM_GV_ONLINEUSER
                ShowOnlineUser()
            Case WM_GV_USERATROOM
                ShowOnlineUser()
            Case WM_GV_MICSTATECHANGE
                PrintInfo("用户 ID" & wParam & " 的音频状态变化为： " & lParam)
        End Select
    End Sub

    Sub ShowOnlineUser()
        Dim ret As Integer
        Dim dwUserNum As Integer

        Dim Item As ListViewItem

        MainWnd.OnlineUser.Items.Clear()

        Item = MainWnd.OnlineUser.Items.Add(MyInfo.NickName)
        Item.Tag = MyInfo.UserID

        ret = -1
        ret = BRAC_GetOnlineUser(vbNullString, dwUserNum)
        If (ret <> 0) Then
            MsgBox("获取房间在线用户人数失败！")
        End If

		if (dwUserNum > 0) Then
			Dim lpUserIDArray() As Integer
			ReDim lpUserIDArray(dwUserNum - 1)

			ret = -1
			ret = BRAC_GetOnlineUser(lpUserIDArray(0), dwUserNum)
			If (ret <> 0) Then
				MsgBox("获取房间在线用户ID列表失败！")
			End If

			Dim i As Integer
			i = 0

			Dim Buffer As String

			Do While (i < dwUserNum)
				Buffer = Space(128)

				Dim ptr As IntPtr
				ptr = Marshal.StringToHGlobalAnsi(Buffer)

				ret = -1
				ret = BRAC_QueryUserState(lpUserIDArray(i), BRAC_USERSTATE_NICKNAME, ptr, Len(Buffer))
				If (ret <> 0) Then
					MsgBox("获取用户 ID" & lpUserIDArray(i) & " 的昵称失败！ ")
				End If

				Buffer = Marshal.PtrToStringAnsi(ptr)
				Marshal.FreeHGlobal(ptr)


				Item = MainWnd.OnlineUser.Items.Add(Buffer)
				Item.Tag = lpUserIDArray(i)

				i = i + 1
			Loop
		End If
    End Sub

    Sub TextMessage_CallBack(ByVal dwFromUserid As Integer, ByVal dwTouserid As Integer, ByVal bSecret As Integer, ByVal lpMsgbuf As IntPtr, ByVal dwLen As Integer, ByVal lpUserValue As IntPtr)
        Dim hwnd As IntPtr
        hwnd = MainWnd.InfomationCtrl.Handle

        Dim NickName As String
        NickName = Space(128)
        Dim ptr As IntPtr
        ptr = Marshal.StringToHGlobalAnsi(NickName)

        Dim ret As Integer

        ret = BRAC_QueryUserState(dwFromUserid, BRAC_USERSTATE_NICKNAME, ptr, Len(NickName))
        If (ret <> 0) Then
            PrintInfo("获取文字消息发送用户昵称失败！")
            NickName = "未知用户"
        End If

        NickName = Marshal.PtrToStringAnsi(ptr)
        Marshal.FreeHGlobal(ptr)

        Dim Content As String
        Content = NickName & "说：" & vbCrLf
        Content = Content & Marshal.PtrToStringAnsi(lpMsgbuf) & vbCrLf

        PrintInfo(Content)
    End Sub

    Public Sub ScrollTextBox(ByRef CTextBox As System.Windows.Forms.TextBox)
        Dim LineCount As Integer

        LineCount = SendMessage(CTextBox.Handle.ToInt32, EM_GETLINECOUNT, 0, 0)
        SendMessage(CTextBox.Handle.ToInt32, EM_LINESCROLL, 0, LineCount)
    End Sub

    Sub PrintInfo(ByRef InfoString As String)
        MainWnd.InfomationCtrl.Text = MainWnd.InfomationCtrl.Text & InfoString & vbCrLf
        ScrollTextBox(MainWnd.InfomationCtrl)
    End Sub
End Module
