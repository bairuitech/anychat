object LoginForm: TLoginForm
  Left = 662
  Top = 202
  AutoScroll = False
  Caption = 'LoginForm'
  ClientHeight = 180
  ClientWidth = 349
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 40
    Top = 40
    Width = 38
    Height = 13
    Caption = #29992#25143'ID:'
  end
  object Label2: TLabel
    Left = 40
    Top = 80
    Width = 36
    Height = 13
    Caption = #23494#30721#65306
  end
  object Label3: TLabel
    Left = 32
    Top = 200
    Width = 36
    Height = 13
    Caption = #26381#21153#22120
  end
  object Label4: TLabel
    Left = 216
    Top = 200
    Width = 24
    Height = 13
    Caption = #31471#21475
  end
  object LoginUser: TEdit
    Left = 88
    Top = 32
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'LoginUser'
  end
  object Edit2: TEdit
    Left = 88
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'Edit2'
  end
  object Button1: TButton
    Left = 40
    Top = 128
    Width = 65
    Height = 25
    Caption = #35774#32622
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 232
    Top = 128
    Width = 75
    Height = 25
    Caption = #30331#38470
    TabOrder = 3
    OnClick = Button2Click
  end
  object Server: TEdit
    Left = 80
    Top = 192
    Width = 121
    Height = 21
    TabOrder = 4
    Text = '211.155.25.90'
  end
  object Port: TEdit
    Left = 264
    Top = 192
    Width = 57
    Height = 21
    TabOrder = 5
    Text = '8906'
  end
end
