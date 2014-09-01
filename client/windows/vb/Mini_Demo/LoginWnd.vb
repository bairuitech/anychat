Public Class LoginWnd



    Private Sub LoginWnd_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        InitSDK()
        LoginUser.Text = "AnyChat5"
        Room.Text = "1"

        Server.Text = "demo.anychat.cn"
        Port.Text = "8906"
    End Sub

    Private Sub Login_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Login_Button.Click
        Dim ret As Integer
        ret = -1
        ret = BRAC_SetServerAuthPass("BaiRuiTech")
        If (ret <> 0) Then
            MsgBox("设置服务器验证密码失败！")
            Exit Sub
        End If

        '此功能暂未实现
        'Dim VersionOK

        BRAC_Connect(Server.Text, CInt(Port.Text))
        
        ret = -1
        ret = BRAC_Login(LoginUser.Text, "", 0)
        If (ret <> 0) Then
            MsgBox("请求登录系统失败！")
            Exit Sub
        End If

        ret = -1
        ret = BRAC_EnterRoom(CInt(Room.Text), "", 0)

        Me.Hide()
        MainWnd.Show()
    End Sub

    Private Sub Cancel_Button_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Cancel_Button.Click
        Me.Close()
    End Sub
End Class
