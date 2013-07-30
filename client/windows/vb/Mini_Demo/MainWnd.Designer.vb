<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class MainWnd
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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(MainWnd))
        Me.InfomationCtrl = New System.Windows.Forms.TextBox
        Me.MessageToSend = New System.Windows.Forms.TextBox
        Me.RemoteVideo = New System.Windows.Forms.PictureBox
        Me.LocalVideo = New System.Windows.Forms.PictureBox
        Me.WaveOutVolume = New System.Windows.Forms.TrackBar
        Me.WaveInVolume = New System.Windows.Forms.TrackBar
        Me.OpenAudio = New System.Windows.Forms.CheckBox
        Me.SendTextMessage = New System.Windows.Forms.Button
        Me.PictureBox3 = New System.Windows.Forms.PictureBox
        Me.PictureBox4 = New System.Windows.Forms.PictureBox
        Me.LoginState = New System.Windows.Forms.Label
        Me.OnlineUser = New System.Windows.Forms.ListView
        CType(Me.RemoteVideo, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.LocalVideo, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.WaveOutVolume, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.WaveInVolume, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.PictureBox3, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.PictureBox4, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'InfomationCtrl
        '
        Me.InfomationCtrl.Location = New System.Drawing.Point(124, 37)
        Me.InfomationCtrl.Multiline = True
        Me.InfomationCtrl.Name = "InfomationCtrl"
        Me.InfomationCtrl.ReadOnly = True
        Me.InfomationCtrl.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.InfomationCtrl.Size = New System.Drawing.Size(339, 240)
        Me.InfomationCtrl.TabIndex = 8
        '
        'MessageToSend
        '
        Me.MessageToSend.Location = New System.Drawing.Point(123, 283)
        Me.MessageToSend.Multiline = True
        Me.MessageToSend.Name = "MessageToSend"
        Me.MessageToSend.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.MessageToSend.Size = New System.Drawing.Size(340, 140)
        Me.MessageToSend.TabIndex = 2
        '
        'RemoteVideo
        '
        Me.RemoteVideo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.RemoteVideo.Location = New System.Drawing.Point(469, 37)
        Me.RemoteVideo.Name = "RemoteVideo"
        Me.RemoteVideo.Size = New System.Drawing.Size(320, 240)
        Me.RemoteVideo.TabIndex = 3
        Me.RemoteVideo.TabStop = False
        '
        'LocalVideo
        '
        Me.LocalVideo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.LocalVideo.Location = New System.Drawing.Point(629, 283)
        Me.LocalVideo.Name = "LocalVideo"
        Me.LocalVideo.Size = New System.Drawing.Size(160, 120)
        Me.LocalVideo.TabIndex = 4
        Me.LocalVideo.TabStop = False
        '
        'WaveOutVolume
        '
        Me.WaveOutVolume.Location = New System.Drawing.Point(505, 321)
        Me.WaveOutVolume.Name = "WaveOutVolume"
        Me.WaveOutVolume.Size = New System.Drawing.Size(118, 45)
        Me.WaveOutVolume.TabIndex = 5
        '
        'WaveInVolume
        '
        Me.WaveInVolume.Location = New System.Drawing.Point(505, 358)
        Me.WaveInVolume.Name = "WaveInVolume"
        Me.WaveInVolume.Size = New System.Drawing.Size(118, 45)
        Me.WaveInVolume.TabIndex = 6
        '
        'OpenAudio
        '
        Me.OpenAudio.BackgroundImage = CType(resources.GetObject("OpenAudio.BackgroundImage"), System.Drawing.Image)
        Me.OpenAudio.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch
        Me.OpenAudio.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft
        Me.OpenAudio.Location = New System.Drawing.Point(469, 283)
        Me.OpenAudio.Name = "OpenAudio"
        Me.OpenAudio.Size = New System.Drawing.Size(71, 32)
        Me.OpenAudio.TabIndex = 7
        Me.OpenAudio.UseVisualStyleBackColor = True
        '
        'SendTextMessage
        '
        Me.SendTextMessage.Location = New System.Drawing.Point(394, 429)
        Me.SendTextMessage.Name = "SendTextMessage"
        Me.SendTextMessage.Size = New System.Drawing.Size(69, 28)
        Me.SendTextMessage.TabIndex = 1
        Me.SendTextMessage.Text = "发送"
        Me.SendTextMessage.UseVisualStyleBackColor = True
        '
        'PictureBox3
        '
        Me.PictureBox3.Image = CType(resources.GetObject("PictureBox3.Image"), System.Drawing.Image)
        Me.PictureBox3.Location = New System.Drawing.Point(469, 321)
        Me.PictureBox3.Name = "PictureBox3"
        Me.PictureBox3.Size = New System.Drawing.Size(38, 37)
        Me.PictureBox3.TabIndex = 9
        Me.PictureBox3.TabStop = False
        '
        'PictureBox4
        '
        Me.PictureBox4.Image = CType(resources.GetObject("PictureBox4.Image"), System.Drawing.Image)
        Me.PictureBox4.Location = New System.Drawing.Point(469, 358)
        Me.PictureBox4.Name = "PictureBox4"
        Me.PictureBox4.Size = New System.Drawing.Size(38, 37)
        Me.PictureBox4.TabIndex = 10
        Me.PictureBox4.TabStop = False
        '
        'LoginState
        '
        Me.LoginState.AutoSize = True
        Me.LoginState.Location = New System.Drawing.Point(12, 9)
        Me.LoginState.Name = "LoginState"
        Me.LoginState.Size = New System.Drawing.Size(41, 12)
        Me.LoginState.TabIndex = 11
        Me.LoginState.Text = "Label1"
        '
        'OnlineUser
        '
        Me.OnlineUser.Location = New System.Drawing.Point(12, 37)
        Me.OnlineUser.MultiSelect = False
        Me.OnlineUser.Name = "OnlineUser"
        Me.OnlineUser.Size = New System.Drawing.Size(106, 386)
        Me.OnlineUser.TabIndex = 12
        Me.OnlineUser.UseCompatibleStateImageBehavior = False
        Me.OnlineUser.View = System.Windows.Forms.View.List
        '
        'MainWnd
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.AutoSize = True
        Me.ClientSize = New System.Drawing.Size(804, 468)
        Me.Controls.Add(Me.LocalVideo)
        Me.Controls.Add(Me.WaveInVolume)
        Me.Controls.Add(Me.PictureBox4)
        Me.Controls.Add(Me.OnlineUser)
        Me.Controls.Add(Me.LoginState)
        Me.Controls.Add(Me.WaveOutVolume)
        Me.Controls.Add(Me.PictureBox3)
        Me.Controls.Add(Me.SendTextMessage)
        Me.Controls.Add(Me.OpenAudio)
        Me.Controls.Add(Me.RemoteVideo)
        Me.Controls.Add(Me.MessageToSend)
        Me.Controls.Add(Me.InfomationCtrl)
        Me.Name = "MainWnd"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "AnyChat"
        CType(Me.RemoteVideo, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.LocalVideo, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.WaveOutVolume, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.WaveInVolume, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.PictureBox3, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.PictureBox4, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents InfomationCtrl As System.Windows.Forms.TextBox
    Friend WithEvents MessageToSend As System.Windows.Forms.TextBox
    Friend WithEvents RemoteVideo As System.Windows.Forms.PictureBox
    Friend WithEvents LocalVideo As System.Windows.Forms.PictureBox
    Friend WithEvents WaveOutVolume As System.Windows.Forms.TrackBar
    Friend WithEvents WaveInVolume As System.Windows.Forms.TrackBar
    Friend WithEvents OpenAudio As System.Windows.Forms.CheckBox
    Friend WithEvents SendTextMessage As System.Windows.Forms.Button
    Friend WithEvents PictureBox3 As System.Windows.Forms.PictureBox
    Friend WithEvents PictureBox4 As System.Windows.Forms.PictureBox
    Friend WithEvents LoginState As System.Windows.Forms.Label
    Friend WithEvents OnlineUser As System.Windows.Forms.ListView
End Class
