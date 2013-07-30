unit mainUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs,BRAnyChatCoreSDK,GVErrorCodeDefine,GVMessageDefine,GVSDK,
  StdCtrls;

type
  TLoginForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    LoginUser: TEdit;
    Edit2: TEdit;
    Button1: TButton;
    Button2: TButton;
    Label3: TLabel;
    Server: TEdit;
    Label4: TLabel;
    Port: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  LoginForm: TLoginForm;

implementation

{$R *.dfm}

procedure TLoginForm.Button1Click(Sender: TObject);
begin
  if  Form1.Height=222 then  Form1.Height:=260 else  Form1.Height:=222;
end;

procedure TLoginForm.FormCreate(Sender: TObject);
begin
  LoginUser.Text := 'AnyChat3';
  BRAC_InitSDK(FORM1.Handle,BRAnyChatCoreSDK.BRAC_FUNC_VIDEO_AUTODISP);
end;

procedure TLoginForm.Button2Click(Sender: TObject);
VAR RET:INTEGER;
begin
  ret := -1;
  ret := BRAC_SetServerAuthPass('BaiRuiTech');
  If (ret <> 0) Then
  BEGIN
      SHOWMESSAGE('设置服务器验证密码失败！');
       EXIT;
  END;

  ret := -1 ;
  ret := BRAC_Connect(PCHAR(Server.Text), STRTOINT(Port.Text));
        If ret <> 0 Then
        BEGIN
            SHOWMESSAGE('请求连接服务器失败！') ;
            Exit;
        End;

  ret := -1;
        ret := BRAC_Login(PCHAR(LoginUser.Text), '', 0);
        If (ret <> 0) Then
        BEGIN
            SHOWMESSAGE('请求登录系统失败！');
            Exit;
        End;

        ret := -1;
        ret := BRAC_EnterRoom(112, '', 0); //CInt(Room.Text)
        If (ret <> 0) Then
        BEGIN
            SHOWMESSAGE('进入房间失败！');
            Exit;
        End;

   Form1.Height:=260;
end;

end.
