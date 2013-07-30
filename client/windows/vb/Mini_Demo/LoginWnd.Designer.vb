<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class LoginWnd
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label
        Me.Label2 = New System.Windows.Forms.Label
        Me.LoginUser = New System.Windows.Forms.TextBox
        Me.Login_Button = New System.Windows.Forms.Button
        Me.Cancel_Button = New System.Windows.Forms.Button
        Me.Room = New System.Windows.Forms.TextBox
        Me.Label3 = New System.Windows.Forms.Label
        Me.Server = New System.Windows.Forms.TextBox
        Me.Label4 = New System.Windows.Forms.Label
        Me.Port = New System.Windows.Forms.TextBox
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(12, 9)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(41, 12)
        Me.Label1.TabIndex = 8
        Me.Label1.Text = "用户名"
        Me.Label1.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(24, 36)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(29, 12)
        Me.Label2.TabIndex = 6
        Me.Label2.Text = "房间"
        Me.Label2.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'LoginUser
        '
        Me.LoginUser.Location = New System.Drawing.Point(59, 6)
        Me.LoginUser.Name = "LoginUser"
        Me.LoginUser.Size = New System.Drawing.Size(102, 21)
        Me.LoginUser.TabIndex = 2
        '
        'Login_Button
        '
        Me.Login_Button.Location = New System.Drawing.Point(14, 137)
        Me.Login_Button.Name = "Login_Button"
        Me.Login_Button.Size = New System.Drawing.Size(59, 24)
        Me.Login_Button.TabIndex = 0
        Me.Login_Button.Text = "登录"
        Me.Login_Button.UseVisualStyleBackColor = True
        '
        'Cancel_Button
        '
        Me.Cancel_Button.DialogResult = System.Windows.Forms.DialogResult.Cancel
        Me.Cancel_Button.Location = New System.Drawing.Point(101, 137)
        Me.Cancel_Button.Name = "Cancel_Button"
        Me.Cancel_Button.Size = New System.Drawing.Size(59, 23)
        Me.Cancel_Button.TabIndex = 1
        Me.Cancel_Button.Text = "取消"
        Me.Cancel_Button.UseVisualStyleBackColor = True
        '
        'Room
        '
        Me.Room.Location = New System.Drawing.Point(59, 33)
        Me.Room.Name = "Room"
        Me.Room.Size = New System.Drawing.Size(102, 21)
        Me.Room.TabIndex = 3
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(12, 77)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(41, 12)
        Me.Label3.TabIndex = 9
        Me.Label3.Text = "服务器"
        Me.Label3.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'Server
        '
        Me.Server.Location = New System.Drawing.Point(59, 74)
        Me.Server.Name = "Server"
        Me.Server.Size = New System.Drawing.Size(101, 21)
        Me.Server.TabIndex = 10
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(24, 104)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(29, 12)
        Me.Label4.TabIndex = 11
        Me.Label4.Text = "端口"
        Me.Label4.TextAlign = System.Drawing.ContentAlignment.TopRight
        '
        'Port
        '
        Me.Port.Location = New System.Drawing.Point(59, 101)
        Me.Port.Name = "Port"
        Me.Port.Size = New System.Drawing.Size(101, 21)
        Me.Port.TabIndex = 12
        '
        'LoginWnd
        '
        Me.AcceptButton = Me.Login_Button
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.CancelButton = Me.Cancel_Button
        Me.ClientSize = New System.Drawing.Size(177, 168)
        Me.Controls.Add(Me.Port)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.Server)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Cancel_Button)
        Me.Controls.Add(Me.Login_Button)
        Me.Controls.Add(Me.Room)
        Me.Controls.Add(Me.LoginUser)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Name = "LoginWnd"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "登录设置"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents LoginUser As System.Windows.Forms.TextBox
    Friend WithEvents Login_Button As System.Windows.Forms.Button
    Friend WithEvents Cancel_Button As System.Windows.Forms.Button
    Friend WithEvents Room As System.Windows.Forms.TextBox
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Server As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Port As System.Windows.Forms.TextBox

End Class
