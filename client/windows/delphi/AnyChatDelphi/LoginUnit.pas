unit LoginUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs,BRAnyChatCoreSDK,GVErrorCodeDefine,GVMessageDefine,GVSDK,
  StdCtrls, ExtCtrls;

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
    Bevel1: TBevel;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  LoginForm: TLoginForm;

implementation

uses main_Unit;

{$R *.dfm}

procedure TLoginForm.Button1Click(Sender: TObject);
begin
  if  loginForm.Height<=222 then  loginForm.Height:=278 else  loginForm.Height:=222;
end;

procedure TLoginForm.FormCreate(Sender: TObject);
begin
 // LoginUser.Text := 'AnyChat3';

  BRAC_InitSDK(Handle,BRAC_FUNC_VIDEO_AUTODISP);
end;

procedure TLoginForm.Button2Click(Sender: TObject);

begin
 
  LoginForm.Close;
end;

procedure TLoginForm.FormClose(Sender: TObject; var Action: TCloseAction);
VAR RET:INTEGER;

  dwMode:DWORD;
  dwVolume:DWORD;
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



        

   LoginForm.Visible:=FALSE;
   mainform.AppendLogString('正使用帐号 ' + LoginUser.Text+ ' 登录系统');
  LoginForm.Close;
end;

end.
