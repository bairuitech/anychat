object Form2: TForm2
  Left = 342
  Top = 129
  BorderStyle = bsSingle
  Caption = #39640#32423#35774#32622
  ClientHeight = 312
  ClientWidth = 548
  Color = clMenuBar
  Ctl3D = False
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 14
  object GroupBox2: TGroupBox
    Left = 280
    Top = 16
    Width = 249
    Height = 113
    Caption = #35270#39057#36136#37327
    TabOrder = 0
    object ComboBox1: TComboBox
      Left = 18
      Top = 28
      Width = 207
      Height = 22
      ItemHeight = 14
      TabOrder = 0
      Text = #26381#21153#22120#37197#32622#36136#37327'('#40664#35748')'
      OnChange = ComboBox1Change
      Items.Strings = (
        #26381#21153#22120#37197#32622#36136#37327'('#40664#35748')'
        #36739#24046#35270#39057#36136#37327
        #19968#33324#35270#39057#36136#37327
        #20013#31561#35270#39057#36136#37327
        #36739#22909#35270#39057#36136#37327
        #26368#22909#35270#39057#36136#37327)
    end
    object BitBtn1: TBitBtn
      Left = 18
      Top = 64
      Width = 75
      Height = 25
      Caption = #30011#38754#35843#33410
      TabOrder = 1
      OnClick = BitBtn1Click
    end
    object m_bEnableDEINTERLACE: TCheckBox
      Left = 160
      Top = 70
      Width = 73
      Height = 17
      Caption = #21453#20132#32455
      TabOrder = 2
    end
  end
  object GroupBox3: TGroupBox
    Left = 280
    Top = 136
    Width = 250
    Height = 121
    Caption = #38899#39057#21442#25968
    TabOrder = 1
    object ComboBox2: TComboBox
      Left = 18
      Top = 28
      Width = 207
      Height = 22
      ItemHeight = 14
      ItemIndex = 0
      TabOrder = 0
      Text = #21457#35328#27169#24335'('#40664#35748')'
      OnChange = ComboBox2Change
      Items.Strings = (
        #21457#35328#27169#24335'('#40664#35748')'
        #25918#27468#27169#24335
        #21345#25289'OK'#27169#24335
        #32447#36335#36755#20837)
    end
    object m_bEnableAGC: TCheckBox
      Left = 128
      Top = 88
      Width = 100
      Height = 17
      Caption = 'AGC'#33258#21160#22686#30410
      TabOrder = 1
    end
    object m_bEnableEcho: TCheckBox
      Left = 128
      Top = 64
      Width = 100
      Height = 17
      Caption = 'ECH'#22238#38899#28040#38500
      TabOrder = 2
    end
    object m_bEnableNS: TCheckBox
      Left = 18
      Top = 88
      Width = 100
      Height = 17
      Caption = 'NSC'#22122#22768#25233#21046
      TabOrder = 3
    end
    object m_bEnableVAD: TCheckBox
      Left = 18
      Top = 64
      Width = 100
      Height = 17
      Caption = 'VAD'#38745#38899#26816#27979
      TabOrder = 4
    end
  end
  object GroupBox4: TGroupBox
    Left = 16
    Top = 136
    Width = 250
    Height = 121
    Caption = #21457#35328#27169#24335
    TabOrder = 2
    object Label1: TLabel
      Left = 18
      Top = 30
      Width = 66
      Height = 13
      AutoSize = False
      Caption = #25918#38899#38899#37327
    end
    object Label2: TLabel
      Left = 18
      Top = 62
      Width = 56
      Height = 14
      Caption = #24405#38899#38899#37327
    end
    object m_bEnableMICBOOST: TCheckBox
      Left = 145
      Top = 84
      Width = 80
      Height = 21
      Caption = 'MIC'#22686#24378
      TabOrder = 0
    end
    object m_ctrlOutVolume: TTrackBar
      Left = 78
      Top = 29
      Width = 147
      Height = 12
      Ctl3D = True
      Max = 20
      Orientation = trHorizontal
      ParentCtl3D = False
      PageSize = 1
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = m_ctrlOutVolumeChange
    end
    object m_ctrlInVolume: TTrackBar
      Left = 78
      Top = 61
      Width = 147
      Height = 12
      Ctl3D = True
      Max = 20
      Orientation = trHorizontal
      ParentCtl3D = False
      PageSize = 1
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 2
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = m_ctrlInVolumeChange
    end
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 250
    Height = 113
    Caption = #35774#22791#36873#25321
    TabOrder = 3
    object Label8: TLabel
      Left = 18
      Top = 36
      Width = 66
      Height = 13
      AutoSize = False
      Caption = #38899#39057#35774#22791
    end
    object Label7: TLabel
      Left = 18
      Top = 68
      Width = 66
      Height = 13
      AutoSize = False
      Caption = #35270#39057#35774#22791
    end
    object m_cbAudioCapture: TComboBox
      Left = 78
      Top = 28
      Width = 155
      Height = 22
      ItemHeight = 14
      TabOrder = 0
      OnChange = m_cbAudioCaptureChange
    end
    object m_cbVideoCapture: TComboBox
      Left = 78
      Top = 60
      Width = 155
      Height = 22
      Style = csDropDownList
      ItemHeight = 14
      TabOrder = 1
      OnChange = m_cbVideoCaptureChange
    end
  end
  object Button1: TButton
    Left = 440
    Top = 272
    Width = 91
    Height = 25
    Caption = #30830#23450
    TabOrder = 4
    OnClick = Button1Click
  end
  object ComboBox3: TComboBox
    Left = 24
    Top = 264
    Width = 145
    Height = 22
    ItemHeight = 14
    TabOrder = 5
    Text = '1-'#26381#21153#22120#25511#21046'P2P'
    Items.Strings = (
      '0-'#31105#27490#26412#22320'P2P'#36830#25509
      '1-'#26381#21153#22120#25511#21046'P2P'
      '2-'#19978#23618#24212#29992#25511#21046'P2P'
      '3-'#25353#38656#24314#31435'P2P'#36830#25509)
  end
end
