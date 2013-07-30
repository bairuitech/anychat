unit main_Unit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs,BRAnyChatCoreSDK,GVErrorCodeDefine,GVMessageDefine,StdCtrls,GVSDK,
  ComCtrls,MMSystem,StrUtils, ExtCtrls, jpeg, OleCtrls, WMPLib_TLB, Buttons,
  Menus;


const
  WM_CB=WM_USER+500;
  WM_CBVIDEODATA=WM_CB+1;
  WM_VOLCHANGE=WM_CB+2;
  WM_TEXTMSG=WM_CB+3;
 // WM_TransBuffer=WM_CB+4;

type
  PTVideoData=^TVideoData;
  TVideoData=Record
    dwUserid:longint;
    lpBuf:Pointer;
    dwLen:LongWord;
    bmiHeader:PBitmapInfoHeader;//BITMAPINFOHEADER;
  end;

  PTTextMsg=^TTextMsg;
  TTextMsg=Record
    dwFromUserid:longint;
    dwToUserid:longint;
    bSecret:BOOL;
    lpMsgBuf:LPCTSTR;
    dwLen:LongWord;
  end;

  PZoomPos=^TTZoomPos;  //最大化窗口定义
   TTZoomPos=Record
   TOP:longint;
   LEFT:longint;
   Width:longint;
   Heigth  :longint;

   END;

  TUserInfo=class(TObject)
   public
    UserID:longint;
    UserIP:string[30];
    UserCountry:string[100];
    constructor Create(vUserID:dWord;sUserIP:pchar;sUserCountry:pchar);  //vUserID:LongWord

  end;

   TUserInfo_Max6=Record
     sUserName:Array[0..30] of Char;
     fUserSpeakVolume:DOUBLE;
     m_iUserID: longint;
     m_UserRect: TPanel;//TRect;
     m_UserIMAGE: TIMAGE;//TRect;
     m_P2PCONNECT : DWORD;
   end;


  TMainForm = class(TForm)
    OpenAudio: TCheckBox;
    OpenVideo: TCheckBox;
    Panel1: TPanel;
    Button1: TButton;
    Room: TEdit;
    Button2: TButton;
    Button3: TButton;
    m_ctrlInVolume: TTrackBar;
    m_ctrlOutVolume: TTrackBar;
    Label11: TLabel;
    m_lbOnLineUserList: TListBox;
    m_ChatModeCombo: TComboBox;
    m_ctrlEditSendMsg: TMemo;
    m_ctrlEditMessage: TMemo;
    Button4: TButton;
    btPrivaterequest: TButton;
    btPrivateexit: TButton;
    Timer1: TTimer;
    m_ctrlSpeakVolume0: TProgressBar;
    ComboBox1: TComboBox;
    Image_BACK: TImage;
    btSendmessage: TSpeedButton;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    BitBtn1: TBitBtn;
    Image0: TImage;
    ID0: TLabel;
    Panel2: TPanel;
    Image1: TImage;
    ID1: TLabel;
    m_ctrlSpeakVolume1: TProgressBar;
    Panel3: TPanel;
    Image2: TImage;
    ID2: TLabel;
    m_ctrlSpeakVolume2: TProgressBar;
    Panel5: TPanel;
    Image4: TImage;
    ID4: TLabel;
    m_ctrlSpeakVolume4: TProgressBar;
    Panel6: TPanel;
    Image5: TImage;
    ID5: TLabel;
    m_ctrlSpeakVolume5: TProgressBar;
    Panel4: TPanel;
    Image3: TImage;
    ID3: TLabel;
    m_ctrlSpeakVolume3: TProgressBar;
    Panel7: TPanel;
    WindowsMediaPlayer1: TWindowsMediaPlayer;
    imgClose: TImage;
    imgMin: TImage;
    Button5: TButton;
    ROOM_NAME: TLabel;
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure OpenAudioClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Button4Click(Sender: TObject);

     procedure m_ctrlOutVolumeMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure m_ctrlInVolumeMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure btPrivaterequestClick(Sender: TObject);
    procedure btPrivateexitClick(Sender: TObject);
    procedure m_ctrlOutVolumeChange(Sender: TObject);
    procedure m_ctrlInVolumeChange(Sender: TObject);
    procedure m_ctrlEditSendMsgKeyPress(Sender: TObject; var Key: Char);
    procedure Timer1Timer(Sender: TObject);
    procedure Image3DblClick(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure btSendmessageClick(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure SpeedButton2Click(Sender: TObject);
    procedure imgCloseClick(Sender: TObject);
    procedure Image_BACKMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Button5Click(Sender: TObject);
    procedure Panel2DblClick(Sender: TObject);
    procedure m_lbOnLineUserListMouseDown(Sender: TObject;
      Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure N7Click(Sender: TObject);
    procedure N2Click(Sender: TObject);
    procedure N1Click(Sender: TObject);
    procedure OpenVideoClick(Sender: TObject);
  private
    { Private declarations }

     procedure OnGVClientConnect(var msg: TMessage); message WM_GV_CONNECT;  ///< 客户端连接服务器，wParam（BOOL）表示是否连接成功
     procedure OnGVClientLogin(var msg: TMessage); message WM_GV_LOGINSYSTEM; 	///< 客户端登录系统
     procedure OnGVClientEnterRoom(var msg: TMessage);message WM_GV_ENTERROOM;   	///< 客户端进入房间，
    procedure OnGVClientMicStateChange(var msg: TMessage);message WM_GV_MICSTATECHANGE;  ///< 用户的音频设备状态变化消息
    procedure OnGVClientUserAtRoom(var msg: TMessage);message WM_GV_USERATROOM;    ///< 用户进入（离开）房间，
   
    procedure OnGVClientLinkClose(var msg: TMessage);message WM_GV_LINKCLOSE;      	///< 网络连接已关闭，
     procedure OnGVClientOnlineUser(var msg: TMessage);message WM_GV_ONLINEUSER;   	///< 收到当前房间的在线用户信息，
    //
    procedure OnGVClientCameraState(var msg: TMessage);message WM_GV_CAMERASTATE;
     procedure OnGVClientChatModeChange(var msg: TMessage);message WM_GV_CHATMODECHG;
    procedure OnGVClientPrivateChatRequest(var msg: TMessage);message WM_GV_PRIVATEREQUEST;
    procedure OnGVClientPrivateChatEcho(var msg: TMessage);message WM_GV_PRIVATEECHO;
    procedure OnGVClientPrivateChatExit(var msg: TMessage);message WM_GV_PRIVATEEXIT;
    procedure OnGV_ENTERREQUEST(var msg: TMessage);message WM_GV_ENTERREQUEST;    ///用户申请进入或者申请离开的消息

    procedure OnGVClientP2PCONNECTSTATE(var msg: TMessage);message WM_GV_P2PCONNECTSTATE;    ///< 本地用户与其它用户的P2P网络连接状态发生变化，
    procedure OnGVClientACTIVESTATE(var msg: TMessage);message   WM_GV_ACTIVESTATE ;//	     ///< 用户活动状态发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的当前活动状态

    procedure OnSDKWARNING(var msg: TMessage);message WM_GV_SDKWARNING;///< SDK警告信息，

     //回调相关
    procedure OnVideoData_CallBack(var msg:TMessage);message WM_CBVIDEODATA;
    procedure OnVolChange_CallBack(var msg:TMessage);message WM_VOLCHANGE;
    procedure OnTextMsg_CallBack(var msg:TMessage);message WM_TEXTMSG;
   // procedure OnTransBuffer_CallBack(var msg:TMessage);message WM_TransBuffer;

    //声明一自定义事件，拦截“WM_NCHITTEST”消息
    Procedure MoveForm(var M:TWMNCHITTEST);Message WM_NCHITTEST;



  public
    { Public declarations }
    //  UserID:LongWord;
     // constructor Create(vUserID:LongWord);



    procedure AppendLogString(LogStr:String);
    function  OnButtonRefreshcapture():Boolean;

    procedure DrawUserVideo(dwUserid:dWord;lpBuf:Pointer;dwLen:LongWord;bmiHeader:BITMAPINFOHEADER);
    procedure ShowWord(dwFromUserid:dWord;dwToUserid:dWord;bSecret:BOOL;lpMsgBuf:LPCTSTR;dwLen:LongWord);


  end;

var
  MainForm: TMainForm;
  m_iRoomID:longint;
  m_captureFlag:Integer;
  m_iUserID:array[0..6] of longint;
  m_UserRect:array[0..6] of TPanel;//TRect;
   m_UserIMAGE:array[0..6] of TIMAGE;//TRect;
  S_UserNAME:array[0..6] of TLABEL;
  m_P2PCONNECT :array[0..6] of DWORD;

  is_myplay:boolean;
  SpeakVolume:array[0..6] of TProgressBar;
  ZOOM_TOP,ZOOM_LEFT,ZOOM_WIDTH,ZOOM_HEIGHT:INTEGER;
  ON_NETWORKSTATUS_TIME:INTEGER;
  UserInfo_Max6:array[0..6] of TUserInfo_Max6;
  UserZoomPos,MyZoomPos: TTZoomPos;

  POP_UserRect:TPanel;
implementation

uses LoginUnit, movie_form, Movie_UNIT, set_unit,qqwry;

{$R *.dfm}
Procedure TMainForm.MoveForm (var M:TWMNCHITTEST);
begin
  inHerited;                                  //继承，窗体可以继续处理以后的事件
  if (M.Result=HTCLIENT)                    //如果发生在客户区
  and (GetKeyState(vk_CONTROL) < 0)            //检测“Ctrl”键是否按下
then M.Result:=HTCAPTION;                    //更改“.Result”域的值
end;

//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatSDKDemo2Dlg message handlers
(**
*	视频数据回调函数
*)


procedure VideoData_CallBack(dwUserid:DWORD;lpBuf:Pointer;dwLen:DWORD;bmiHeader:BITMAPINFOHEADER;lpUserValue:Pointer);stdcall;
var
  drFrm:TMainForm;
  aTVideoData:TVideoData;
begin
  {$if false}
	CBRAnyChatSDKDemo2Dlg*	pDemoDlg = (CBRAnyChatSDKDemo2Dlg*)lpUserValue;
	if(pDemoDlg)
		pDemoDlg->DrawUserVideo(dwUserid,lpBuf,dwLen,bmiHeader);
  {$ifend}
  //exit;
  aTVideoData.dwUserid:=dwUserid;
  aTVideoData.lpBuf:=lpBuf;
  aTVideoData.dwLen:=dwLen;
  aTVideoData.bmiHeader:=@bmiHeader;
  SendMessage(TMainForm(lpUserValue).Handle,WM_CBVIDEODATA,LongWord(@aTVideoData),0);
  {$if false}
  drFrm:=TForm1(lpUserValue);
  drFrm.DrawUserVideo(dwUserid,lpBuf,dwLen,bmiHeader);
  {$ifend}

end;
//---------------------------------------------------------------------------
procedure TMainForm.OnVideoData_CallBack(var msg:TMessage);
var
  aPTVideoData:PTVideoData;
begin
  aPTVideoData:=PTVideoData(Pointer(msg.WParam));
  try
  begin
    DrawUserVideo(aPTVideoData^.dwUserid,aPTVideoData^.lpBuf,aPTVideoData^.dwLen,aPTVideoData^.bmiHeader^);
  end
  except
    //
  end;
  msg.Result:=1;

end;
//---------------------------------------------------------------------------
(**
*	音频数据回调函数
*)
procedure AudioData_CallBack(dwUserid:DWORD;lpBuf:Pointer;dwLen:DWORD;waveFormatEx:TWAVEFORMATEX;lpUserValue:Pointer);stdcall;
begin
  {$if false}
	CBRAnyChatSDKDemo2Dlg*	pDemoDlg = (CBRAnyChatSDKDemo2Dlg*)lpUserValue;
	if(pDemoDlg)
	{
		// 计算音量
		USHORT* pData = (USHORT*)lpBuf;
		DWORD	datalen = dwLen/2;
		LONGLONG totalvolume = 0;
		for(int i=0; i<(int)datalen; i++)
		{
			totalvolume += *(pData + i);
		}
		DWORD dwCurrentVolume = (DWORD)((totalvolume% (0xFFFF-1))*100)/ (0xFFFF-1);
		TRACE("UserID:%d, Volume:%d\r\n",dwUserid,dwCurrentVolume);

		// do something ...
	}
  {$ifend}
end;
//---------------------------------------------------------------------------
(**
*	音量更改回调函数
*)
procedure VolumeChange_CallBack(device:BRAC_AudioDevice;dwCurrentVolume:DWORD;lpUserValue:Pointer);stdcall;
begin
  {$if false}
	CBRAnyChatSDKDemo2Dlg*	pDemoDlg = (CBRAnyChatSDKDemo2Dlg*)lpUserValue;
	if(pDemoDlg)
	{
		if(device == BRAC_AD_WAVEIN)
			pDemoDlg->OnWaveInVolumeChange(dwCurrentVolume);
		else
			pDemoDlg->OnWaveOutVolumeChange(dwCurrentVolume);
	}
  {$ifend}
  SendMessage(TMainForm(lpUserValue).Handle,WM_VOLCHANGE,LongWord(device),LongWord(dwCurrentVolume));

end;
//---------------------------------------------------------------------------
procedure TMainForm.OnVolChange_CallBack(var msg:TMessage);
begin
  if  (BRAC_AudioDevice(msg.WParam)=BRAC_AD_WAVEIN) then
  begin
      if abs(m_ctrlInVolume.Position-trunc(msg.LParam/5))<4 then exit;
    // m_ctrlInVolume.Position:=integer(trunc(msg.LParam/5));
  end
  else
  begin
    if abs(m_ctrlOutVolume.Position-trunc(msg.LParam/5))<4 then exit;
    //   m_ctrlOutVolume.Position:=integer(trunc(msg.LParam/5));
  end;
   msg.Result:=1;
end;
//---------------------------------------------------------------------------
(**
 *	文字消息回调函数
 *)
procedure TextMessage_CallBack(dwFromUserid:DWORD;dwToUserid:DWORD;bSecret:BOOL;
				lpMsgBuf:LPCTSTR;dwLen:DWORD;lpUserValue:Pointer);stdcall;
var
  aTTextMsg:TTextMsg;
begin
  {$if false}
	CBRAnyChatSDKDemo2Dlg*	pDemoDlg = (CBRAnyChatSDKDemo2Dlg*)lpUserValue;
	if (pDemoDlg)
		pDemoDlg->ShowWord(dwFromUserid,dwToUserid,bSecret,lpMsgBuf,NULL,dwLen);
  {$ifend}
  aTTextMsg.dwFromUserid:=dwFromUserid;
  aTTextMsg.dwToUserid:=dwToUserid;
  aTTextMsg.bSecret:=bSecret;
  aTTextMsg.lpMsgBuf:=lpMsgBuf;
  aTTextMsg.dwLen:=dwLen;
  SendMessage(TMainForm(lpUserValue).Handle,WM_TEXTMSG,LongWord(@aTTextMsg),0);

end;

//---------------------------------------------------------------------------
procedure TMainForm.OnTextMsg_CallBack(var msg:TMessage);
var
  aPTTextMsg:PTTextMsg;
begin
  aPTTextMsg:=PTTextMsg(Pointer(msg.WParam));
  ShowWord(aPTTextMsg^.dwFromUserid,aPTTextMsg^.dwToUserid,aPTTextMsg^.bSecret,aPTTextMsg^.lpMsgBuf,aPTTextMsg^.dwLen);
   msg.Result:=1;
end;

 
//---------------------------------------------------------------------------

(**
 *	透明通道数据回调函数
 *)
procedure  TransBuffer_CallBack(dwUserid:DWORD;lpBuf:PByte;dwLen:DWORD;lpUserValue:Pointer);stdcall;
var
     //bPTTransBuffer:PTTransBuffer;  //透明通道数据定义
     buffer:array of byte;
     url:string;
     i:integer;
begin
  {$if false}
	CBRAnyChatSDKDemo2Dlg*	pDemoDlg = (CBRAnyChatSDKDemo2Dlg*)lpUserValue;
	if (pDemoDlg)
		pDemoDlg->ShowWord(dwUserid,dwUserid,0,NULL,lpBuf,dwLen);
  {$ifend}
     url:='';
     setLength(buffer,dwLen);// copymemory
     copymemory(@(buffer[0]), Pointer(lpBuf) ,dwLen);
     for i:=0 to dwLen-1 do url:=url+char(buffer[i]) ;
   //BRAC_TransBuffer(dwUserid:DWORD;lpBuf:PBYTE;dwLen:DWORD)
   if pos('http://',url)>0 then
   try
        MAINFORM.WindowsMediaPlayer1.controls.stop;
        MAINFORM.WindowsMediaPlayer1.url:=url;
        MAINFORM.WindowsMediaPlayer1.controls.play();
        is_myplay:=FALSE;
         mainform.m_ctrlEditMessage.Lines.Add(inttostr(longint(dwUserid))+'透明通道：：：'+url+'('+inttostr(dwLen)+')');

   except

   end;

    if pos('OpenyourCamera',url)>0 then
   try
         mainform.OpenVideo.Checked:=TRUE;
        BRAC_SetVideoPos(m_iUserID[0],m_UserRect[0].Handle,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].BoundsRect.right,m_UserRect[0].BoundsRect.bottom);
	BRAC_UserCameraControl(m_iUserID[0],TRUE);

   except

   end;
    if pos('CloseyourCamera',url)>0 then
   try
        mainform.OpenVideo.Checked:=FALSE;
        BRAC_SetVideoPos(m_iUserID[0],m_UserRect[0].Handle,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].BoundsRect.right,m_UserRect[0].BoundsRect.bottom);
	BRAC_UserCameraControl(m_iUserID[0],FALSE);

   except

   end;

   if pos('OpenyourAudio',url)>0 then
   try
         mainform.OpenAudio.Checked:=TRUE;
         BRAC_UserSpeakControl(dword(-1), true)

   except

    end;
  if pos('CloseyourAudio',url)>0 then
   try
         mainform.OpenAudio.Checked:=false;
         BRAC_UserSpeakControl(dword(-1), false)

   except

  end;

end;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
(**
*	绘制用户视频
*	数据来源于回调函数
*	@param dwUserid 用户ID号
*	@param lpBuf 视频数据缓冲区
*	@param dwLen 缓冲区大小
*	@param bmiHeader 视频缓冲区的头信息，包含了视频的大小、颜色位数等信息
*)
procedure TMainForm.DrawUserVideo(dwUserid: dWord; lpBuf: Pointer;
  dwLen: LongWord; bmiHeader:BITMAPINFOHEADER);
var
  dwSite:LongInt;
  i:Integer;
  //dispRect:TRect;

  lpbmi:PBitmapInfoHeader;
  ahdc:HDC;
  dcMem:HDC;
  h_Bitmap:HBITMAP;
  holdbm:HBITMAP;
begin
 // exit;
  // 根据用户ID号找到合适的显示区域
	dwSite := -1;
	for i:=0 to 5 do
	begin
		if(dword(m_iUserID[i])= dword(dwUserid) ) then
		begin
			dwSite:= i;
			break;
		end;
	end;
     	if(dwSite = -1) then   	exit;




	//dispRect := m_UserRect[dwSite];
	//构建Bitmap
  GetMem(lpbmi,sizeof(BITMAPINFOHEADER)+dwLen);
	ZeroMemory(lpbmi,sizeof(BITMAPINFOHEADER)+dwLen);
  CopyMemory(lpbmi,
            @bmiHeader,
            sizeof(bmiHeader));
  CopyMemory(Pointer(Integer(lpbmi)+sizeof(BITMAPINFOHEADER)),lpBuf,dwLen);

	ahdc :=GetDC(m_UserRect[dwSite].Handle);
	dcMem :=CreateCompatibleDC(ahdc);
  h_Bitmap := CreateDIBitmap(ahdc,lpbmi^,CBM_INIT,PChar(Integer(lpbmi)+sizeof(BITMAPINFOHEADER)),PBITMAPINFO(lpbmi)^,DIB_RGB_COLORS);

	//绘图
	holdbm := HBITMAP(SelectObject(dcMem,h_Bitmap));
	SetStretchBltMode(ahdc,COLORONCOLOR);
	//StretchBlt(ahdc,dispRect.left,dispRect.top,dispRect.Right-dispRect.Left,dispRect.Bottom-dispRect.Top,dcMem,0,0,bmiHeader.biWidth,bmiHeader.biHeight,SRCCOPY);
  //StretchBlt(ahdc,m_UserRect[dwSite].Left,m_UserRect[dwSite].top,m_UserRect[dwSite].Width,m_UserRect[dwSite].Height,dcMem,0,0,bmiHeader.biWidth,bmiHeader.biHeight,SRCCOPY);
  //StretchBlt(ahdc,0,0,m_UserRect[dwSite].Width,m_UserRect[dwSite].Height,dcMem,0,0,bmiHeader.biWidth,bmiHeader.biHeight,SRCCOPY);
  StretchBlt(ahdc,4,24,m_UserRect[dwSite].Width-8,m_UserRect[dwSite].Height-48,dcMem,0,0,bmiHeader.biWidth,bmiHeader.biHeight,SRCCOPY);

	SelectObject(dcMem,holdbm);
	DeleteObject(dcMem);
	DeleteObject(h_Bitmap);
	DeleteObject(ahdc);
	FreeMem(lpbmi);
	lpbmi :=nil;

end;
//---------------------------------------------------------------------------
procedure TMainForm.ShowWord(dwFromUserid:dWord;dwToUserid:dWord;bSecret:BOOL;lpMsgBuf:LPCTSTR;dwLen:LongWord);
var
  strmsgshow,strmsg,struserid,strtime:String;
  srcusername:array[0..30] of Char;
  tarusername:array[0..30] of Char;
begin
  //
	strtime:=FormatDateTime('(HH:NN:SS)',Now());
	ZeroMemory(@srcusername,sizeof(srcusername));
	BRAC_GetUserName(dwFromUserid,srcusername,sizeof(srcusername));

	if(dwToUserid =dWord(-1)) then
        begin
		struserid:=Format('%s 说: ',[StrPas(srcusername)]);
        end else  begin
		if(longint(dwToUserid) =(m_iUserID[0])) then
                begin
			struserid:=Format('%s 悄悄滴对我 说: ',[StrPas(srcusername)]);
                end else begin
                        ZeroMemory(@tarusername,sizeof(tarusername));
			BRAC_GetUserName(dwToUserid,tarusername,sizeof(tarusername));
			struserid:=Format('%s 对 %s 说: ',[StrPas(srcusername),StrPas(tarusername)]);
		end;
	end;

	if(lpMsgBuf = nil) then
        begin
                strmsg:='';
	end else begin
		strmsg:=Format('%s',[StrPas(lpMsgBuf)]);
        end;

	strmsgshow :=strmsgshow+struserid+strtime    +   strmsg;//+#13#10
	m_ctrlEditMessage.Lines.Add(strmsgshow);


      {  if pos('http://',strmsgshow)>0 then
        begin
             is_myplay:=false;
             WindowsMediaPlayer1.Controls.stop;
             WindowsMediaPlayer1.URL:=StrPas(lpMsgBuf);
             WindowsMediaPlayer1.Controls.play;
        end;  }
end;








procedure TMainForm.FormClose(Sender: TObject; var Action: TCloseAction);
var
  I:integer;
begin

    if m_lbOnLineUserList.Items.Count>0 then
  for i:=m_lbOnLineUserList.Items.Count-1 downto 0 do
  begin
   
   try
         // if  TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID<>integer(-1) then
         m_lbOnLineUserList.Items.Objects[i].Free;
      
   except
       
   end;


  end;
  //  m_lbOnLineUserList.Items.Clear;
   BRAC_LeaveRoom(m_iRoomID); //离开房间
    // AppendLogString('用户从系统注销');
   //   Application.ProcessMessages;
   //Application.ProcessMessages;
 // Application.ProcessMessages;

 
   //   Application.ProcessMessages;
    //  Application.ProcessMessages;
 //  BRAC_Logout();  //退出登录
    
end;

procedure TMainForm.FormCreate(Sender: TObject);
var
  i,VideoQuality:Integer;
  dwMode:DWORD;
  dwVolume:Integer;
  AGC,VAD,NSC,ECH,bAPPLYPARAM:integer;
begin
   is_myplay:=false;
   FOR I:=0 TO 5 DO
   BEGIN
    // UserInfo_Max6[i].m_UserRect:=m_UserRect[i];
    // UserInfo_Max6[i].S_UserNAME:= S_UserNAME[i].;
    // UserInfo_Max6[i].fUserSpeakVolume:=SpeakVolume[i]
    // UserInfo_Max6[i].sUserName:=
   end;
  m_UserRect[0]:= Panel1  ; //TPanel1. 用户县市区
    m_UserRect[1]:= Panel2 ;
     m_UserRect[2]:= Panel3 ;
      m_UserRect[3]:= Panel4 ;
       m_UserRect[4]:= Panel5 ;
        m_UserRect[5]:= Panel6 ;

   S_UserNAME[0]:=ID0;  //创建用户名
    S_UserNAME[1]:=ID1;  //创建用户名
     S_UserNAME[2]:=ID2;  //创建用户名
      S_UserNAME[3]:=ID3;  //创建用户名
       S_UserNAME[4]:=ID4;  //创建用户名
        S_UserNAME[5]:=ID5;  //创建用户名


    m_UserIMAGE[0]:=image0;//TRect;
      m_UserIMAGE[1]:=image1;//TRect;
        m_UserIMAGE[2]:=image2;//TRect;
          m_UserIMAGE[3]:=image3;//TRect;
            m_UserIMAGE[4]:=image4;//TRect;
              m_UserIMAGE[5]:=image5;//TRect;

   SpeakVolume[0]:=m_ctrlSpeakVolume0;  //创建用户音量进度条
   SpeakVolume[1]:=m_ctrlSpeakVolume1;
    SpeakVolume[2]:=m_ctrlSpeakVolume2;
     SpeakVolume[3]:=m_ctrlSpeakVolume3;
      SpeakVolume[4]:=m_ctrlSpeakVolume4;
       SpeakVolume[5]:=m_ctrlSpeakVolume5;
       // SpeakVolume[0]:=ProgressBar0;





        for i:=0 to 5 do
	begin
		m_iUserID[i] :=longint(-1);

                S_UserNAME[i].Caption :='';

	end;
        BRAC_ActiveCallLog(true);//关闭日志输出
        //BRAC_FUNC_VIDEO_CBDATA or BRAC_FUNC_AUDIO_AUTOPLAY or BRAC_FUNC_AUDIO_CBDATA;
      	dwMode :=BRAC_FUNC_VIDEO_AUTODISP or      //通过回调函数处理视频BRAC_FUNC_VIDEO_CBDATA  BRAC_FUNC_VIDEO_AUTODISP
                 BRAC_FUNC_AUDIO_AUTOPLAY or    //SDK自动处理音频数据
                 BRAC_FUNC_CONFIG_LOCALINI or   //< 生成本地配置文件（AnyChatSDK.ini）
                 BRAC_FUNC_AUDIO_VOLUMECALC or   //< 由SDK自动计算语音的音量
                 BRAC_FUNC_FIREWALL_OPEN or      //< 允许SDK操作Windows防火墙，将当前应用程序加入防火墙访问列表（避免Windows提示用户是否阻止当前应用程序）
                 BRAC_FUNC_NET_SUPPORTUPNP ; //;or      //< 允许SDK打开用户网络中的UPNP设备，如果用户的路由器或是防火墙支持UPNP协议，则可提高P2P打洞的成功率
               //  BRAC_SO_AUDIO_AUTOPARAM         //根据音频编码，自动选择参数音频自动蚕食设置

	if(BRAC_InitSDK(mainform.Handle,dwMode) = GV_ERR_SUCCESS) then
	begin
		AppendLogString('初始化成功');
        end else begin
		AppendLogString('初始化失败，可能是因为插件没有注册或缺少相应组件');
         end;

        // AGC:=integer(m_bEnableAGC.Checked);
        // VAD:=integer(m_bEnableVAD.Checked);
       //  NSC:=integer(m_bEnableNS.Checked);
       //  Ech:=integer(m_bEnableEcho.Checked);

      //  BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL,(@AGC),sizeof(integer)); //AGC
      //	BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL,@(VAD),sizeof(integer)); // VAD
      //	BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL,@NSC,sizeof(integer));     // NSC
      //	BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,@Ech,sizeof(integer));   //Ech

         dwVolume:=1; //默认服务器控制P2P
         BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC,@dwVolume,sizeof(dwVolume));

       //可通过BRAC_SetSDKOption接口来设置单声道，或是双声道模式下的音频通信质量，典型设置代码如下：
          dwVolume:=15850;  //单声道模式下，音频编码的质量是：15.85kbps，
         BRAC_SetSDKOption(BRAC_SO_AUDIO_MONOBITRATE,@dwVolume,sizeof(dwVolume));

            dwVolume:=40000;   //双声道模式下，音频的编码质量是：40kbps，
          BRAC_SetSDKOption(BRAC_SO_AUDIO_STEREOBITRATE,@dwVolume,sizeof(dwVolume));



         dwVolume:=60*1000; /////< 本地视频编码码率设置（参数为int型，单位bps，同服务器配置：VideoBitrate）
         BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL,@dwVolume,sizeof(dwVolume));
  

                 dwVolume:=3; /////< 本地视频编码质量因子控制（参数为int型，同服务器配置：VideoQuality）
         BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL,@dwVolume,sizeof(dwVolume));

                 dwVolume:=20; /////< 本地视频编码关键帧间隔控制（参数为int型，同服务器配置：VideoGOPSize）
         BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_GOPCTRL,@dwVolume,sizeof(dwVolume));

                 dwVolume:=8; /////< 本地视频编码帧率控制（参数为int型，同服务器配置：VideoFps）
         BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL,@dwVolume,sizeof(dwVolume));

                 dwVolume:=3; /////< 本地视频编码预设参数控制（参数为int型，1-5）
         BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL,@dwVolume,sizeof(dwVolume));


                  dwVolume:=0;  // ///< 视频显示模式控制（参数为：int型，0 单画面显示，1 视频迭加显示）
          BRAC_SetSDKOption(BRAC_SO_VIDEOSHOW_MODECTRL,@dwVolume,sizeof(dwVolume));


          dwVolume:=1;  // 	///< 视频显示驱动控制（参数为：int型，0 默认驱动， 1 Windows DirectShow，2 Windows GDI，3 SDL）
          BRAC_SetSDKOption(BRAC_SO_VIDEOSHOW_DRIVERCTRL,@dwVolume,sizeof(dwVolume));

                  bAPPLYPARAM:=1;    //立即生效
         BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM,@bAPPLYPARAM,sizeof(integer));





        
        BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_RGB24,VideoData_CallBack,self);  //设置视频回调函数
	BRAC_SetAudioDataCallBack(AudioData_CallBack,self);
	BRAC_SetVolumeChangeCallBack(VolumeChange_CallBack,self);

	BRAC_SetTextMessageCallBack(TextMessage_CallBack,self);
	BRAC_SetTransBufferCallBack(TransBuffer_CallBack,self);
         // 设置异步消息通知回调函数
       // BRAC_SetNotifyMessageCallBack(NotifyMessageCallBack,self);

        dwMode :=50;
        if BRAC_AudioGetVolume(BRAC_AD_WAVEOUT,dwMode)=0 then
	m_ctrlOutVolume.Position:=integer(trunc(dwMode/5));

	dwMode := 50;
       if	BRAC_AudioGetVolume(BRAC_AD_WAVEIN,dwMode)=0 then
	m_ctrlInVolume.Position:=integer(trunc(dwMode/5));


      BRAC_SetVideoPos(dword(-1),m_UserRect[0].Handle,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].BoundsRect.right,m_UserRect[0].BoundsRect.bottom);

end;

procedure TMainForm.OpenAudioClick(Sender: TObject);

begin
   If (OpenAudio.Checked ) Then
       begin

         	AppendLogString('申请发言');
            If  (BRAC_UserSpeakControl(dword(-1), true)<> 0) Then
                 AppendLogString('打开本地音频失败！');
                 //OnButtonRefreshcapture();
                 m_captureFlag := 1;

       end Else begin

         	AppendLogString('停止发言');


              If (BRAC_UserSpeakControl(dword(-1), false) <> 0) Then
                 AppendLogString('关闭本地音频失败！') ;
        	m_captureFlag := 0;
        End;
end;

procedure TMainForm.Button1Click(Sender: TObject);
var dwVolume:dword;
begin

       m_iRoomID:= strtoInt(Room.Text);
       dwVolume:=BRAC_EnterRoom(m_iRoomID, '', 0);
 

end;

procedure TMainForm.Button2Click(Sender: TObject);
var i:integer;
begin
    Timer1.Enabled:=false;
   // Timer1.Interval:=0;
    Application.ProcessMessages;
     Application.ProcessMessages;
  { if  m_lbOnLineUserList.Items.Count>1 then
   for i:=(m_lbOnLineUserList.Items.Count-1) downto 2 do  //
   begin
            try

                 BRAC_UserCameraControl(TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID,longbool(false));
                 BRAC_UserSpeakControl(TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID,longbool(false));

            except

            end;

    end;
    }
    if  BRAC_LeaveRoom(m_iRoomID)=0 then AppendLogString('退出房间');
    //    BRAC_UserCameraControl(dword(-1),false);
   //  BRAC_SetVideoPos(dword(-1),m_UserRect[0].Handle,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].BoundsRect.right,m_UserRect[0].BoundsRect.bottom);
  // Button1.Enabled:=true;
  is_myplay:=false;

   //  Application.ProcessMessages;
   //  Application.ProcessMessages;
   //   Application.ProcessMessages;
  
end;

procedure TMainForm.AppendLogString(LogStr: String);
begin
  m_ctrlEditMessage.Lines.Add(LogStr);
end;


procedure TMainForm.OnGVClientConnect(var msg: TMessage);
var
  bSuccess:Boolean;
begin
  //
  bSuccess :=Boolean(msg.WParam);
      if bSuccess  then
      begin
             AppendLogString('连接服务器成功...') ;
      end else begin
       //连接部分

         if  msg.WParam =  GV_ERR_CONNECT_TIMEOUT	then AppendLogString('//连接服务器超时,连接服务器失败///') else
         if  msg.WParam =  GV_ERR_CONNECT_ABORT		then AppendLogString('//< 与服务器的连接中断///') else
         if  msg.WParam =  GV_ERR_CONNECT_AUTHFAIL	then AppendLogString('//< 未能通过服务器的认证，属于非法连接///') else
         if  msg.WParam =  GV_ERR_CONNECT_DNSERROR	then AppendLogString('//< 域名解析失败  /// ') ;

       end;

  msg.Result:=1;
end;

procedure TMainForm.OnGVClientLogin(var msg: TMessage);
var
  logstr:String;
  dwUserID:longint;//dword
begin
	dwUserID :=longint(msg.WParam);
	if(msg.LParam= 0) then
	begin
                // logstr:=Format('登录服务器成功，自己的用户编号为：%u',[integer(msg.WParam)]);
                 logstr:='登录服务器成功，自己的用户编号为;'+ inttostr(dwUserID);
                 //showmessage(inttostr(dwUserID));
		// 将用户的ID保存在第一个位置，否则在回调函数里面可能找不到绘制的位置
		m_iUserID[0]:=dwUserID;
              // showmessage(inttostr(m_iUserID[0]));
	end  else  begin
		logstr:=Format('登录服务器失败，出错代码为： %u ',[longint(msg.lParam)]);
        end;
	AppendLogString(logstr);
         msg.Result:=1;

end;
//---------------------------------------------------------------------------
procedure TMainForm.OnGVClientEnterRoom(var msg: TMessage);
var
  logstr,RoomName:String;
  roomid:dWord;
  Index:LongWord;
  username:Array[0..30] of char;
  sUserIP:Array[0..30] of char;
  strName:String;
  i:Integer;
begin
          Roomid := longint(msg.wParam);
       
	if(msg.lParam = 0) then
	begin
                Button1.Enabled:=false;
		logstr:=Format('成功进入编号为：%u 的房间',[roomid]);
                MainForm.Caption:=Format('房间编号：%u ',[roomid]);
                 Button2.Enabled:=true;
                 RoomName:='';
                 IF BRAC_GetUserName(Roomid,@RoomName,sizeof(RoomName))=0 THEN

                 BEGIN

                    ROOM_NAME.Caption:=INTTOSTR(Roomid)+RoomName;
                 END;
               
                if m_lbOnLineUserList.Items.Count>0 then
                for i:=m_lbOnLineUserList.Items.Count-1 downto 0 do
                begin
                  try
                        begin
                           TUserInfo(m_lbOnLineUserList.Items.Objects[i]).Free;
                        end;
                   except
        //
                   end;
                end;
                m_lbOnLineUserList.Items.Clear;       ///< 清空用户列表
                m_ChatModeCombo.Items.Clear;         //聊天用户列别同步更新
                m_ChatModeCombo.Items.Add('所有人');
                 m_ChatModeCombo.ItemIndex:=0;
		//index := m_lbOnLineUserList.Items.Add('所有人');
               //m_lbOnLineUserList.Items.Objects[index]:=Pointer(-1);

               //TUserInfo
                 m_lbOnLineUserList.Items.AddObject('所有人',TUserInfo.Create(dword(-1),'',''));  //Create(LongWord(-1))
	         BRAC_GetUserName(m_iUserID[0],username,sizeof(username));
	         strName:=StrPas(username)+'*';	// 在自己的用户名后面加上一个"*"以示区别
                // m_ChatModeCombo.Items.Add(StrPas(username));    自己不对自己说话
               // sUserIP:=;;
                  ZeroMemory(@sUserIP,sizeof(sUserIP));
                 if  BRAC_QueryUserState(m_iUserID[0],BRAC_USERSTATE_INTERNETIP,@sUserIP,sizeof(sUserIP)) = GV_ERR_SUCCESS then
                 begin
                 end;
                 S_UserNAME[0].Caption:=strName+'('+inttostr(longint(m_iUserID[0]))+')';
                 m_lbOnLineUserList.Items.AddObject(strName,TUserInfo.Create(longint(m_iUserID[0]),sUserIP,'')); //LongWord(m_iUserID[0]


                 If (OpenAudio.Checked ) Then
                 begin

                         //根据话筒装套决定是否打开耳麦发言');
                      If  (BRAC_UserSpeakControl(DWORD(-1), true)<> 0) Then  AppendLogString('打开本地音频失败！')
                                                                       else  AppendLogString('麦克开启状态！');

                      m_captureFlag := 1;

                end Else begin


                        AppendLogString('麦克设置为关闭状态');

                        If (BRAC_UserSpeakControl(dword(-1), false) <> 0) Then  AppendLogString('关闭本地音频失败！') ;
                        
                	m_captureFlag := 0;
                 End;
                 // 	OnButtonOpencamera();

                 If (OpenVideo.Checked ) Then   //需要强制打开视频线，反方辩测试
                 begin
                  try
                      AppendLogString(inttostr(m_iUserID[0]));
                      BRAC_SetVideoPos(dword(-1),m_UserRect[0].Handle,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].BoundsRect.right,m_UserRect[0].BoundsRect.bottom);
                        BRAC_UserCameraControl(dword(-1),TRUE);
                  except
                       AppendLogString('打开本地视频失败！')
                  end;

                
               end;
         

                Timer1.Enabled:=true;
	end else begin
                     Button1.Enabled:=true;
                 
                    if msg.lParam = GV_ERR_ROOM_LOCK       then  AppendLogString('房间已被锁住，禁止进入！') else
                    if msg.lParam = GV_ERR_ROOM_PASSERR    then  AppendLogString('房间密码错误，禁止进入') else
                    if msg.lParam = GV_ERR_ROOM_FULLUSER   then  AppendLogString('房间已满员，不能进入') else
                    if msg.lParam = GV_ERR_ROOM_INVALID    then  AppendLogString('房间不存在 ') else
                    if msg.lParam = GV_ERR_ROOM_EXPIRE	    then  AppendLogString('房间服务时间已到期') else
                    if msg.lParam = GV_ERR_ROOM_REJECT	    then  AppendLogString('房主拒绝进入') else
                    if msg.lParam = GV_ERR_ROOM_OWNERBEOUT then  AppendLogString('房主不在，不能进入房间') else
                    if msg.lParam = GV_ERR_ROOM_ENTERFAIL  then  AppendLogString('不能进入房间 ') else
                    if msg.lParam = GV_ERR_ROOM_ALREADIN   then  AppendLogString('已经在房间里面了，');


		logstr:=Format('申请进入房间失败，出错代码为： %u',[msg.lParam]);
         end;
         
       	msg.Result:=1;
end;
procedure TMainForm.OnGVClientMicStateChange(var msg: TMessage);
var
  logStr:String;
  i:integer;
  Userid :longint;
begin
        Userid:=longint(msg.wParam);
	logstr:='编号为：'+inttostr(longint(msg.wParam))+' 的用户 Mic'+IfThen(Boolean(msg.lParam),'获取','释放');
	AppendLogString(logstr);

        for i:=0 to 5 do
        begin
            IF m_iUserID[i]=Userid THEN
            begin
                 SpeakVolume[i].Visible:=Boolean(msg.lParam) ;
                 break;
            end;

        end;
  msg.Result:=1;
end;


///< 用户申请进入房间消息，wParam（INT）表示用户ID号，lParam（BOOL）表示该用户是申请进入（TRUE）房间或离开（FALSE）房间等待队列
procedure TMainForm.OnGV_ENTERREQUEST(var msg: TMessage);
var
  logStr:String;
  i:integer;
  Userid :longint;
begin
       	logstr:='编号为：'+inttostr(longint(msg.wParam))+' 的用户'+IfThen(Boolean(msg.lParam),'申请进入房间','申请退出房间');
     msg.Result:=1;
end;


procedure TMainForm.OnGVClientUserAtRoom(var msg: TMessage);
var
  logstr:String;
  userid:longint;
  bEnter:BOOL;
  username:Array[0..30] of char;
  sUserIP :Array[0..30] of char;
   strName:String;
  index:LongWord;
  i,j:Integer;
  site:Integer;
  aobj:TObject;
  P2P_NETSTATUS:integer;
  URL:ARRAY[1..254] OF BYTE;
begin
	userid :=longint(msg.wParam);
	bEnter :=BOOL(msg.lParam);

       //	logstr:=Format('编号为：%u 的用户 %s 房间',[userid,IfThen(bEnter,'进入','离开')]);
       if bEnter  then   logstr:='编号为：'+inttostr(userid)+' 的用户进入房间'
                  else   logstr:='编号为：'+inttostr(userid)+' 的用户离开房间';
	AppendLogString(logstr);

		ZeroMemory(@username,sizeof(username));
		BRAC_GetUserName(userid,username,sizeof(username));

  if (bEnter) then
  begin

                   m_ChatModeCombo.Items.Add(StrPas(username)); //更新用户聊天列表

		//index := m_lbOnLineUserList.Items.Add(StrPas(username));
		//m_lbOnLineUserList.Items.Objects[index]:=Pointer(userid);
               // sUserIP:=;;
                   // sUserIP:='';  对方IP
                   ZeroMemory(@sUserIP,sizeof(sUserIP));
                    if  BRAC_QueryUserState((userid),BRAC_USERSTATE_INTERNETIP,@sUserIP,sizeof(sUserIP)) = GV_ERR_SUCCESS then
                    BEGIN
                       //SHOWMESSAGE(sUserIP);
                      // strName:=username +' IP:'+  sUserIP;
                    END;

                m_lbOnLineUserList.Items.AddObject(username,TUserInfo.Create(longint(userid),sUserIP,'')); //LongWord(userid)

               
                // 给用户找一个空的位置显示面板（第0号位置留给自己）
               if  m_iUserID[0]<> longint(userid) then
               begin
                     site := -1;
                     for i:=1 to 5 do
                     begin
                          if(m_iUserID[i] = longint(-1)) then
                           begin
	                        site := i;
                                break;
                           end;
                     end;


                    //找到空位置，则登记
                     if(site <> -1) then
                     begin
                                m_iUserID[site]:= userid;
	                 	BRAC_SetVideoPos(userid,m_UserRect[site].Handle,m_UserRect[site].left,m_UserRect[site].top,m_UserRect[site].BoundsRect.right,m_UserRect[site].BoundsRect.bottom);
                                BRAC_UserCameraControl(userid,TRUE);
                                BRAC_UserSpeakControl(userid,TRUE);

                                S_UserNAME[site].Caption:=username+'('+inttostr(longint(m_iUserID[i]))+')';

                                P2P_NETSTATUS:=5;
                                if  BRAC_QueryUserState(m_iUserID[site],BRAC_USERSTATE_P2PCONNECT,@P2P_NETSTATUS,sizeof(Dword)) = GV_ERR_SUCCESS then
                               begin
                                m_P2PCONNECT[i]:= P2P_NETSTATUS;
                               // showmessage('找到网络连接方式'+inttostr(m_P2PCONNECT[i]));
                               end;
                      end;

                 end;

                logstr:=mainform.WindowsMediaPlayer1.URL;
                // SHOWMESSAGE(logstr);
                if  is_myplay AND (length(logstr)>1) then
                BEGIN

                   for i:=1 to length(logstr) do URL[i]:=byte(logstr[i]);
                   BRAC_TransBuffer(longint(userid),@URL[1],Length(logstr));
                  
                END;
  end else  begin
                // showmessage('退出用户：'+inttostr(userid)+'自己是：'+inttostr(m_iUserID[0]));
		if (longint(userid) =(m_iUserID[0])) then
		begin
                        Button1.Enabled:=true;
                        Button2.Enabled:=false;
                      
                      if (m_lbOnLineUserList.Items.Count)>1 then
                      for i:=(m_lbOnLineUserList.Items.Count-1) downto 1 do  //
                      begin
                          try
                            // if  m_lbOnLineUserList.Items.Objects[i]<>nil then
                              m_lbOnLineUserList.Items.Objects[i].Free;
                          //  BRAC_UserCameraControl(TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID,longbool(false));
                           // BRAC_UserSpeakControl(TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID,longbool(false));
                           if  i<=5 then
                           begin


                             S_UserNAME[i].Caption:='';
                             m_UserRect[i].Caption:='';
                            // m_UserRect[i].Repaint;

                            end;

                          except
                              
                          end;

                         
                      end;
                      m_lbOnLineUserList.Items.Clear;
                         Timer1.Enabled:=false;
                      for i:=1 to 5 do   m_iUserID[i] := longint(-1); //清楚用户所占位置

                      for i:=0 to 5 do  S_UserNAME[i].Caption:='';   //清楚用户名


                       m_ChatModeCombo.Items.Clear; //更新用户聊天列表
                       
                        Room_name.Caption:='大厅状态';
                end else  begin
                      //  //清除该用户占用列表位置的信息
                      for i:=m_lbOnLineUserList.Items.Count-1 downto 1 do //0是所有人那个-1是无效的
                      begin
                          try
                                 //
                                 if TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID=longint(userid) then
                                 begin
                                     try
                                        m_lbOnLineUserList.Items.Objects[i].Free;
                                        m_lbOnLineUserList.Items.Delete(i);
                                        m_ChatModeCombo.Items.Delete(i-1);
                                     except
                                         showmessage('清除该用户占用列表位置的信息');
                                     end;

                                    

                                     if i<=5 then
                                     begin
                                         m_iUserID[i] := longint(-1);
                                         S_UserNAME[i].Caption:='';
                                        // m_UserRect[i].Repaint;
                                      end;
                                      break;
                                 end;

                           except

                           end;
                       end;


                       

                        //清除该用户占用显示位置的信息
                         for i:=1 to 5 do
                         begin
                            if(m_iUserID[i]) =longint (userid) then
                            begin
                                  m_iUserID[i] := longint(-1);
                                  S_UserNAME[i].Caption:='';
                                  m_UserRect[i].Refresh;
                                  break;
                            end;
                         end;




                 end;
   end;







  msg.Result:=1;

end;


//---------------------------------------------------------------------------
procedure TMainForm.OnGVClientLinkClose(var msg: TMessage);
var  i:integer;
begin
  AppendLogString('网络连接已关闭（断开），关闭原因代码：'+inttostr( msg.WParam));
   for i:=0 to 5 do
	begin
		m_iUserID[i] :=longint(-1);

                S_UserNAME[i].Caption :='';

	end;

  msg.Result:=1;
end;

//---------------------------------------------------------------------------
procedure TMainForm.OnGVClientOnlineUser(var msg: TMessage);
var
  logstr:String;
  onlinenum:LongWord;
  dwUserNum:DWORD;
  //lpdwUserList:PDWORD;
  lpdwUserList:array of DWORD;
  k,i,j:DWORD;
  username:Array[0..30] of Char;
  index:LongWord;
  userid:longint;
  dwCameraState:DWORD;
  site:LongInt;
  sUserIP: array[0..30] of char;
begin
  //
	onlinenum :=longint(msg.wParam);
	logstr:=Format('在编号为：%u 的房间共有 %u 位在线用户',[longint(msg.lParam),onlinenum]);
	AppendLogString(logstr);
         dwUserNum := 0;
	BRAC_GetOnlineUser(nil,dwUserNum);		///< 首先获取房间内在线人数
	if(dwUserNum=0) then Exit;


	SetLength(lpdwUserList,dwUserNum);
	BRAC_GetOnlineUser(@lpdwUserList[0],dwUserNum);	///< 真正获取在线用户列表

	for k:=0 to dwUserNum-1 do
	begin
                userid := longint(lpdwUserList[k]);
                ZeroMemory(@username,sizeof(username));
		BRAC_GetUserName(lpdwUserList[k],username,sizeof(username));
		//index := m_lbOnLineUserList.Items.Add(StrPas(username));
                //m_lbOnLineUserList.Items.Objects[index]:=Pointer(lpdwUserList[k]);

                 ZeroMemory(@sUserIP,sizeof(sUserIP));
                 if BRAC_QueryUserState(userid,BRAC_USERSTATE_INTERNETIP,@sUserIP,sizeof(sUserIP)) = GV_ERR_SUCCESS then
                  BEGIN
                    // SHOWMESSAGE(USERSTATE_INTERNETIP);
                    // strName:=strName+'  IP:'+sUserIP;
                    AppendLogString(StrPas(sUserIP));
                  END;
                m_lbOnLineUserList.Items.AddObject(StrPas(username),TUserInfo.Create(longint(lpdwUserList[k]),sUserIP,'')); //LongWord(lpdwUserList[k])
                m_ChatModeCombo.Items.Add(StrPas(username)); //更新用户聊天列表
                m_ChatModeCombo.ItemIndex:=0;
	

		// 给用户找一个空的位置显示面板（第0号位置留给自己）
                if k<=5 then
	        begin
                 	site := -1;
	        	for j:=1 to 5 do
	        	begin
		        	if(m_iUserID[j] =longint(-1)) then
		         	begin
			         	site := j;
			        	break;
		        	end;
	         	end;
	        	if(site <> -1) then
	        	begin
		        	//BRAC_SetVideoPos(userid,Handle,m_UserRect[site].left,m_UserRect[site].top,m_UserRect[site].right,m_UserRect[site].bottom);
                                m_iUserID[site] := userid;
                                BRAC_SetVideoPos(userid,m_UserRect[site].Handle,m_UserRect[site].left,m_UserRect[site].top,m_UserRect[site].BoundsRect.right,m_UserRect[site].BoundsRect.bottom);
		         	BRAC_UserCameraControl(userid,TRUE);
		         	BRAC_UserSpeakControl(userid,TRUE);
		        
                                S_UserNAME[site].Caption:=username+'('+inttostr(longint(m_iUserID[site]))+')';

                                case dwCameraState of
                                     0:  m_UserRect[site].Caption:='没有摄像头';
                                     1:  m_UserRect[site].Caption:='摄像头关闭';
                                     2:  m_UserRect[site].Caption:='摄像头已打开';
                                     3:  m_UserRect[site].Caption:='没有摄像头';
                                else ;
                                end;
                                  // m_UserRect[i].Refresh;


                        end
                end;


                BRAC_GetCameraState(userid,dwCameraState);
		logstr:=Format('userid=%u, camerastate=%u',[longint(userid), dwCameraState]);
                 logstr:='userid='+inttostr(longint(userid))+'camerastate='+inttostr(dwCameraState);
		AppendLogString(logstr);



	end;

	SetLength(lpdwUserList,0);

	msg.Result:=1;

end;

   ///< 用户活动状态发生变化，wParam（INT）表示用户ID号，lParam（INT）表示用户的当前活动状态
procedure TMainForm.OnGVClientACTIVESTATE(var msg: TMessage); //

   var
   str:string;
begin
      case (msg.lParam) of
          0: str:='正常';
          1: str:='繁忙';
          2: str:='离开';
          3: str:='未知状态';
          4: str:='未知状态';
          5: str:='未知状态';
       else ;
       end;
       AppendLogString('编号：[' + inttostr(msg.wParam) +  ']的活动状态，当前状态：'+str);

       msg.Result:=1;

end;

///< SDK警告信息，当SDK在运行过程中自检发现异常状态时，将向上层发送该消息，
///wParam（INT）表示警告代码，定义为：GV_ERR_WARNING_XXXX
procedure TMainForm.OnSDKWARNING(var msg: TMessage);///< SDK警告信息，

begin
     // SDK警告
     if msg.wParam =  GV_ERR_WARNING_UDPFAIL         then  AppendLogString('//与服务器的UDP通信异常，流媒体服务将不能正常工作') else
     if msg.wParam =  GV_ERR_WARNING_MISCUTILFAIL    then  AppendLogString('//SDK加载brMiscUtil.dll动态库失败，部分功能将失效') else
     if msg.wParam =  GV_ERR_WARNING_MEDIAUTILFAIL   then  AppendLogString('SDK加载brMediaUtil.dll动态库失败，部分功能将失效');
     msg.Result:=1;
end;
procedure TMainForm.OnGVClientP2PCONNECTSTATE(var msg: TMessage); ///< 本地用户与其它用户的P2P网络连接状态发生变化，
 ///wParam（INT）表示其它用户ID号，lParam（INT）表示本地用户与其它用户的当前P2P网络连接状态
var
   str:string;
   sUserIP:array[0..30] of char;
   i:integer;
   ipq:tqqwry;
begin
      case (msg.lParam) of
          0: str:='服务器中转';
          1: str:='TCP连接';
          2: str:='UDP连接';
          3: str:='TCP_UDP';
          4: str:='未知状态';
          5: str:='未知状态';
       else ;
       end;
       AppendLogString('与编号：[' + inttostr(msg.wParam) +  ']的网络连接状态改变消息，当前状态：'+str);
       for i:=1 to m_lbOnLineUserList.Count-1 do
       begin
           if TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID= msg.wParam then
           begin
                   ZeroMemory(@sUserIP,sizeof(sUserIP));
                   if  BRAC_QueryUserState(msg.wParam,BRAC_USERSTATE_INTERNETIP,@sUserIP,sizeof(sUserIP)) = GV_ERR_SUCCESS then
                    BEGIN

                         TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserIP:=StrPas(sUserIP);
                       //加快速度，此时不可直接查IP  归属地
                       {  try
                            ipq:=tqqwry.Create(ExtractFilePath(Application.ExeName)+'QQWry.Dat');
                            ipq.qqwry(TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserIP);
                            TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserCountry:=ipq.Country+ipq.Local;
                         finally
                            ipq.Free;
                         end;
                        }

                    END;
            

             break;
           end;
       end;
 
       msg.Result:=1;
end;
//---------------------------------------------------------------------------
procedure TMainForm.OnGVClientCameraState(var msg: TMessage);
var
  logstr:String;
  userid:Longint;
  camerastate:Longint;
  i:integer;
begin
	userid :=Longint(msg.wParam);
	camerastate :=Longint(msg.lParam);
	if(m_iUserID[0] = userid) then
	begin
		logstr:='自己（'+inttostr(userid)+'）的摄像头状态改变，当前摄像头状态为：'+
			         Ifthen(camerastate=0,'没有摄像头',Ifthen(camerastate=1,'有摄像头但没有打开','摄像头已打开'));




	end
	else
  begin
		logstr:='编号（'+inttostr(userid)+'）的摄像头状态改变，当前摄像头状态为：'+
			         Ifthen(camerastate=0,'没有摄像头',Ifthen(camerastate=1,'有摄像头但没有打开','摄像头已打开'));
		//  Ifthen(camerastate = 0 ,'没有摄像头',Ifthen(camerastate = 1 ,'有摄像头但没有打开','摄像头已打开'))]);




  end;

	AppendLogString(logstr);

          for i:=0 to 5 do
           if  m_iUserID[i]=userid then
           begin

              case camerastate of
                  0:  m_UserRect[0].Caption:='没有摄像头';
                  1:  m_UserRect[0].Caption:='摄像头关闭';
                  2:  m_UserRect[0].Caption:='摄像头已打开';
                  3:  m_UserRect[0].Caption:='没有摄像头';
                else ;
                end;
                m_UserRect[i].Refresh;
                break;

	   end;


  msg.Result:=1;

end;

//---------------------------------------------------------------------------
function TMainForm.OnButtonRefreshcapture: Boolean;
var
  DeviceName:Array[0..10] of PChar;
  DeviceNum:LongWord;
  i:Integer;
  //
  szVideoDeviceName:Array[0..100] of Char;
  n:Integer;

  szAudioDeviceName:Array[0..100] of Char;
begin
        // 刷新视频采集设备下拉列表


end;

procedure TMainForm.FormShow(Sender: TObject);
begin
  OnButtonRefreshcapture();
end;
//---------------------------------------------------------------------------
procedure TMainForm.OnGVClientChatModeChange(var msg: TMessage);
var
  logstr:String;
  userid,chatmode:longint;
begin
	userid :=longint(msg.wParam);
	chatmode :=dWord(msg.lParam);
	if(m_iUserID[0] = userid) then
	begin
		logstr:='自己（'+ inttostr(userid) + '的聊天模式改变，当前聊天模式为'+IfThen(chatmode = 0,'公聊模式','私聊模式');
    try
    begin
      m_ChatModeCombo.ItemIndex:=chatmode;
    end;
    except
    end;
	end
	else
  begin
		logstr:='编号('+inttostr(userid)+ ')的用户聊天模式改变，当前聊天模式为：'+IfThen(chatmode= 0,'公聊模式','私聊模式');
  end;
	AppendLogString(logstr);


         msg.Result:=1;
end;

//---------------------------------------------------------------------------
//< 用户发起私聊请求，wParam（INT）表示发起者的用户ID号，lParam（INT）表示私聊请求编号，标识该请求
procedure TMainForm.OnGVClientPrivateChatRequest(var msg: TMessage);
var
  logstr:String;
  userid:Longint;
  requestid:Longint;
  bAccept:BOOL;
  notifymsg:String;

begin
	userid :=Longint(msg.wParam);
	requestid :=Longint(msg.lParam);
	bAccept := FALSE;
	notifymsg:='用户（'+inttostr(userid)+'）请求与你私聊，是否同意？';
  if Application.MessageBox(PChar(notifymsg),'私聊请求',MB_YESNO or MB_ICONQUESTION)=IDYES then
  begin
    bAccept :=TRUE;
  	logstr:=Format('同意与编号为：%u 的用户进行私聊',[userid]);
  end
  else
  begin
    bAccept := FALSE;
		logstr:=Format('拒绝与编号为：%u 的用户进行私聊',[userid]);
  end;
	AppendLogString(logstr);
	BRAC_PrivateChatEcho(userid,requestid,bAccept);

         msg.Result:=1;
end;
//---------------------------------------------------------------------------
//< 用户回复私聊请求，wParam（INT）表示回复者的用户ID号，lParam（INT）为出错代码
procedure TMainForm.OnGVClientPrivateChatEcho(var msg: TMessage);
var
  logstr:String;
  userid:Longint;
  errorcode:Longint;
begin
	userid :=Longint(msg.wParam);
	errorcode :=Longint(msg.lParam);
	if(errorcode = GV_ERR_SUCCESS) then
  begin
		logstr:=Format('用户（%u ）同意了私聊请求，进入私聊模式',[userid]);
  end
	else
  begin
       //私聊
         if  msg.lParam =GV_ERR_ROOM_PRINULL	        then 	AppendLogString('401;    ///< 用户已经离开房间 ,私聊请求失败' )else
         if  msg.lParam = GV_ERR_ROOM_REJECTPRI	        then 	AppendLogString('402;	///< 用户拒绝了私聊邀请' )else
         if  msg.lParam = GV_ERR_ROOM_PRIDENY		then 	AppendLogString('403;	///< 不允许与该用户私聊，或是用户禁止私聊  ,私聊请求失败' )else

         if  msg.lParam = GV_ERR_ROOM_PRIREQIDERR	then 	AppendLogString('420;	///< 私聊请求ID号错误，或请求不存在 ,私聊请求失败' )else
         if  msg.lParam = GV_ERR_ROOM_PRIALRCHAT	then 	AppendLogString('421;	///< 已经在私聊列表中 ' )else

         if  msg.lParam = GV_ERR_ROOM_PRITIMEOUT	then 	AppendLogString('431;	///< 私聊请求超时,私聊请求失败' )else
         if  msg.lParam =  GV_ERR_ROOM_PRICHATBUSY	then 	AppendLogString('432;	///< 对方正在私聊中，繁忙状态' )else
         if  msg.lParam = GV_ERR_ROOM_PRIUSERCLOSE	then 	AppendLogString('433;	///< 对方用户关闭私聊,私聊请求失败' )else
         if  msg.lParam = GV_ERR_ROOM_PRISELFCLOSE	then 	AppendLogString('434;	///< 用户自己关闭私聊,私聊请求失败' );



	//	logstr:=Format('用户（%u）拒绝了私聊请求，错误代码为：%d',[userid, errorcode]);
  end;
	AppendLogString(logstr);
       msg.Result:=1;
end;
//---------------------------------------------------------------------------

//< 用户退出私聊，wParam（INT）表示退出者的用户ID号，lParam（INT）为出错代码
procedure TMainForm.OnGVClientPrivateChatExit(var msg: TMessage);
var
  logstr:String;
  userid:Longint;
  errorcode:Longint;
begin
	userid :=Longint(msg.wParam);
	errorcode:=Longint(msg.lParam);
	logstr:=Format('与用户（%u ）的私聊已关闭，错误代码为：%d',[userid, errorcode]);
	AppendLogString(logstr);
      msg.Result:=1;
end;



procedure TMainForm.FormDestroy(Sender: TObject);
begin
 BRAC_Release();
end;

//---------------------------------------------------------------------------
{ TUserInfo }
constructor TUserInfo.Create(vUserID: dWord;sUserIP:pchar;sUserCountry:pchar);
begin
  //
  UserID:=longint(vUserID);
  UserIP:=sUserIP;
  UserCountry:=sUserCountry;

end;

procedure TMainForm.Button4Click(Sender: TObject);

var
     dwVolume:DWORD;
     AGC,VAD,NSC,ECH,MICBOOST,DEINTERLACE:DWORD;
begin
        dwVolume :=50;
      // if	BRAC_AudioGetVolume(BRAC_AD_WAVEOUT,dwVolume)=0 then
	FORM2.m_ctrlOutVolume.Position:=m_ctrlOutVolume.Position;

	dwVolume :=50;
     //  if	BRAC_AudioGetVolume(BRAC_AD_WAVEIN,dwVolume)=0 then
       	FORM2.	m_ctrlInVolume.Position:=m_ctrlInVolume.Position;

       
       // SDK内核参数状态查询
       AGC:=0;
      if BRAC_GetSDKOption(BRAC_SO_AUDIO_AGCCTRL,@AGC,sizeof(AGC))=0 then   FORM2.m_bEnableAGC.Checked:=BOOLEAN(AGC);

       NSC:=0;
      if BRAC_GetSDKOption(BRAC_SO_AUDIO_NSCTRL,@NSC,sizeof(NSC))=0 then   FORM2.m_bEnableNS.Checked:=BOOLEAN(NSC);

       VAD:=0;
      if BRAC_GetSDKOption(BRAC_SO_AUDIO_VADCTRL,@VAD,sizeof(VAD))=0 then   FORM2.m_bEnableVAD.Checked:=BOOLEAN(VAD);

       ECH:=0;
      if BRAC_GetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,@ECH,sizeof(ECH))=0 then   FORM2.m_bEnableECHO.Checked:=BOOLEAN(ECH);

    //   MICBOOST:=0;
    //  if BRAC_GetSDKOption(BRAC_SO_AUDIO_MICBOOST,@MICBOOST,sizeof(MICBOOST))=0 then   FORM2.m_bEnableMICBOOST.Checked:=BOOLEAN(MICBOOST);

    //  DEINTERLACE:=0;
    //  if BRAC_GetSDKOption(BRAC_SO_LOCALVIDEO_DEINTERLACE,@DEINTERLACE,sizeof(DEINTERLACE))=0 then   FORM2.m_bEnableDEINTERLACE.Checked:=BOOLEAN(DEINTERLACE);


       // THEN 	ShowMessage('设置成功，返回'); ;
  // 显示本地视频画面调节对话框
     //	BRAC_ShowLVProperty(Handle,'NGN 本地视频画质调节',0,0);

     form2.ShowModal;
          dwVolume:=FORM2.ComboBox3.ItemIndex;
         BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC,@dwVolume,sizeof(dwVolume));


         dwVolume:=1;
         BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM,@dwVolume,sizeof(dwVolume));

     MAINFORM.ComboBox1.ItemIndex:=form2.ComboBox2.ItemIndex;
     m_ctrlOutVolume.Position:=form2.m_ctrlOutVolume.Position;
     m_ctrlInVolume.Position:= form2.m_ctrlInVolume.Position ;
end;
//---------------------------------------------------------------------------
procedure TMainForm.m_ctrlOutVolumeMouseUp(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
    BRAC_AudioSetVolume(BRAC_AD_WAVEOUT,m_ctrlOutVolume.Position*5);
end;
//---------------------------------------------------------------------------
procedure TMainForm.m_ctrlInVolumeMouseUp(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
   BRAC_AudioSetVolume(BRAC_AD_WAVEIN,m_ctrlInVolume.Position*5);
end;
procedure TMainForm.btPrivaterequestClick(Sender: TObject);
var
  i:Integer;
  usertalkto:longint;
  st:Boolean;
begin
  st:=false;
  for i:=1 to m_lbOnLineUserList.Count-1 do
  begin
    if m_lbOnLineUserList.Selected[i] then
    begin
      usertalkto:=TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID;
      st:=true;
      break;
    end;
  end;

  if not st then
  begin
    ShowMessage('请选择私聊目标用户');
    Exit;
  end;

	if((m_iUserID[0]) = usertalkto) then
	begin
		ShowMessage('请选择私聊目标用户');
    Exit;
	end;
	BRAC_PrivateChatRequest(usertalkto);
end;

procedure TMainForm.btPrivateexitClick(Sender: TObject);
var
  i:Integer;
  usertalkto:longint;
  st:Boolean;
begin
  st:=false;
  for i:=1 to m_lbOnLineUserList.Count-1 do
  begin
    if m_lbOnLineUserList.Selected[i] then
    begin
      usertalkto:=TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID;
      st:=true;
      break;
    end;
  end;

  if not st then
  begin
    ShowMessage('请选择私聊目标用户');
    Exit;
  end;

	if((m_iUserID[0]) = usertalkto) then
	begin
		ShowMessage('请选择私聊目标用户');
    Exit;
	end;

 	BRAC_PrivateChatExit(usertalkto);
  
end;

procedure TMainForm.m_ctrlOutVolumeChange(Sender: TObject);
begin
    // 设置指定音频设备的音量
   BRAC_AudioSetVolume(BRAC_AD_WAVEOUT,DWORD(m_ctrlOutVolume.Position*5));
    // m_ctrlEditMessage.Lines.Add(inttostr(DWORD(m_ctrlOutVolume.Position*5)));
end;

procedure TMainForm.m_ctrlInVolumeChange(Sender: TObject);
begin
     // 设置指定音频设备的音量
    BRAC_AudioSetVolume(BRAC_AD_WAVEIN,DWORD(m_ctrlInVolume.Position*5));
   //  m_ctrlEditMessage.Lines.Add(inttostr(DWORD(m_ctrlInVolume.Position*5)));
end;

procedure TMainForm.m_ctrlEditSendMsgKeyPress(Sender: TObject;
  var Key: Char);
begin
    if key=#13 then MainForm.btSendmessageClick(self);
end;

procedure TMainForm.Timer1Timer(Sender: TObject);
var fSpeakVolume:DOUBLE;
    NETWORKSTATUS,i,P2P_NETSTATUS:dword;
    USERSTATE_INTERNETIP:ARRAY[1..30] OF CHAR  ;
    IP:STRING;
begin
        Timer1.Enabled:=false;
        for i:=0 to 5 do
        begin
                   SpeakVolume[3]:=m_ctrlSpeakVolume3;
                        fSpeakVolume := 0.0;
			if(m_iUserID[i] <> longint(-1))then
                        if (BRAC_QueryUserState(m_iUserID[i],BRAC_USERSTATE_SPEAKVOLUME,@fSpeakVolume,sizeof(DOUBLE)) = GV_ERR_SUCCESS) then
			 begin
                               	SpeakVolume[i].Visible:=(fSpeakVolume>0);
                         	SpeakVolume[i].Position:= trunc(fSpeakVolume)
		         end else begin
				SpeakVolume[i].Position:=0;
                                SpeakVolume[i].Visible:=false;
                         end;
        end;

           ON_NETWORKSTATUS_TIME:=ON_NETWORKSTATUS_TIME+1;
           IF ON_NETWORKSTATUS_TIME>20  THEN
           BEGIN

                ON_NETWORKSTATUS_TIME:=0;   //定时检测网络信号质量

               for i:=0 to 5 do
               begin
                     // m_UserRect[3]:=Panel4;
                   // S_UserNAME[i].Caption:=''
                   // if (m_iUserID[i]<>longint(-1))  then //
                  //  if  BRAC_QueryUserState(m_iUserID[i],BRAC_USERSTATE_INTERNETIP,@USERSTATE_INTERNETIP,sizeof(USERSTATE_INTERNETIP)) = GV_ERR_SUCCESS then
                  //  BEGIN
                      //SHOWMESSAGE(USERSTATE_INTERNETIP);
                    //  S_UserNAME[i].Caption:=USERSTATE_INTERNETIP;
                  //  END;

                       S_UserNAME[i].Caption:='';
                          P2P_NETSTATUS:=5;
                       //	if(m_iUserID[i] <> longint(-1))then
                               if  BRAC_QueryUserState(m_iUserID[i],BRAC_USERSTATE_P2PCONNECT,@P2P_NETSTATUS,sizeof(Dword)) = GV_ERR_SUCCESS then
                               begin
                                m_P2PCONNECT[i]:= P2P_NETSTATUS;
                               // showmessage('找到网络连接方式'+inttostr(m_P2PCONNECT[i]));
                               end;
                  if (m_iUserID[i]<>longint(-1)) AND (i<>0) then //
                  BEGIN
                     case m_P2PCONNECT[i] of
                       0: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'P2P不通';
                       1: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'TCP连接';
                       2: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'UDP连接';
                       3: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'TCP_UDP';

                     else ;
                         S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'未知';
                     end;
                   END ELSE BEGIN
                        S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'';

                   END;
                  // USERSTATE_INTERNETIP:=PCHAR('');

                  NETWORKSTATUS:=5;
                  if m_iUserID[i]<>longint(-1) then
                  if  BRAC_QueryUserState(m_iUserID[i],BRAC_USERSTATE_NETWORKSTATUS,@NETWORKSTATUS,sizeof(Dword)) = GV_ERR_SUCCESS then
                  case NETWORKSTATUS of
                      0: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'：优良';
                      1: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'：较好';
                      2: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'：一般';
                      3: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'：较差';
                      4: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'：很差';
                      5: S_UserNAME[i].Caption:=S_UserNAME[i].Caption+'：断开';
                   end; 

               end;
           //  mainform.ID1.Caption:=inttostr((NETWORKSTATUS));

           END;
       Timer1.Enabled:=true;
end;

procedure TMainForm.Image3DblClick(Sender: TObject);
VAR DW:INTEGER;
begin

      
  if  TImage(Sender).Parent.Align=alclient then
  begin

  end else begin
      UserZoomPos.TOP:= TImage(Sender).Parent.Top;
      UserZoomPos.LEFT:= TImage(Sender).Parent.Left;
      UserZoomPos.WIDTH:= TImage(Sender).Parent.Width;
      UserZoomPos.Heigth:=  TImage(Sender).Parent.Height;
      TImage(Sender).Visible:=FALSE;
      TImage(Sender).Parent.Align:=alclient;
       TImage(Sender).Parent.BringToFront;

      MyZoomPos.TOP:=Panel1.Top;
      MyZoomPos.LEFT:=Panel1.Left;
      MyZoomPos.WIDTH:=Panel1.Width;
      MyZoomPos.Heigth:= Panel1.Height;


      Panel1.Top:=TImage(Sender).Parent.Top+TImage(Sender).Parent.Height-Panel1.Height;
      Panel1.Left:=TImage(Sender).Parent.Width-Panel1.Width;
     // IMAGE0.Visible:=FALSE;
      Panel1.BringToFront;
  end;
end;

procedure TMainForm.ComboBox1Change(Sender: TObject);
 VAR M_AUDIO_CPATUREMODE:INTEGER;
begin
   M_AUDIO_CPATUREMODE:= ComboBox1.ItemIndex;
  BRAC_SetSDKOption(BRAC_SO_AUDIO_CPATUREMODE,(@M_AUDIO_CPATUREMODE),sizeof(M_AUDIO_CPATUREMODE));

   //  MAINFORM.WindowsMediaPlayer1.Visible :=(ComboBox1.ItemIndex=1);

end;

procedure TMainForm.btSendmessageClick(Sender: TObject);
var
  usertalkto:LongInt;
  strGetMessageSend:String;
  chatmode:Integer;
  //
  strmsgshow,strmsg,struserid,strtime:String;
  username:array[0..30] of Char;
begin
  if m_ChatModeCombo.ItemIndex<=0 then   //m_lbOnLineUserList.ItemIndex
  begin
               usertalkto := -1;
  end else  begin
       usertalkto :=TUserInfo(m_lbOnLineUserList.Items.Objects[m_ChatModeCombo.ItemIndex+1]).UserID; //m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex+1)
       if(m_iUserID[0] = usertalkto) then
       begin
         	usertalkto := -1;
       end;
  end;
  //获取发送窗口信息
  strGetMessageSend:=m_ctrlEditSendMsg.Text;
  chatmode := m_ChatModeCombo.ItemIndex;
  BRAC_SendTextMessage(usertalkto,Boolean(chatmode),PChar(strGetMessageSend),Length(strGetMessageSend));
  m_ctrlEditSendMsg.Clear;

  //显示在自己的窗口上
  strtime:=FormatDateTime('(HH:NN:SS)',Now());
  if(usertalkto = -1) then
	begin
		struserid:=Format('我对 %s 说: ',['大家']);
	end  else begin
                ZeroMemory(@username,sizeof(username));
		BRAC_GetUserName(usertalkto,username,sizeof(username));
		struserid:=Format('我悄悄地对 %s 说: ',[StrPas(@username)]);
	end;
  strmsg:=Format('%s',[strGetMessageSend]);
  strmsgshow:=strmsgshow+(struserid+strtime+strmsg); //+#13#10
  m_ctrlEditMessage.Lines.Add(strmsgshow);
  m_ctrlEditSendMsg.Clear;
end;

procedure TMainForm.SpeedButton1Click(Sender: TObject);
var
  usertalkto:LongInt;
  strGetMessageSend:array[1..254] of byte;
  charsum:Integer;
  i:integer;
  URL:String;
  username:array[0..30] of Char;
begin

    form1:=Tform1.Create(self);
    form1.ShowModal;
     form1.Free;

    usertalkto := -1;
    URL:=WindowsMediaPlayer1.URL;
  //获取发送窗口信息
   charsum:= length(URL);
   if charsum<2 then exit;
       is_myplay:=true;
     for i:=1 to charsum do strGetMessageSend[i]:=byte(URL[i]);

    if m_lbOnLineUserList.Items.Count>=2 then
    for i:=m_lbOnLineUserList.Items.Count-1 downto 2 do //0是所有人那个-1是无效的
    begin

        usertalkto :=TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID; //m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex+1)
        BRAC_TransBuffer(usertalkto,@strGetMessageSend[1],charsum);
       // BRAC_SendTextMessage(usertalkto,Boolean(charsum),PChar(strGetMessageSend),Length(strGetMessageSend));

   end;
   
end;

procedure TMainForm.SpeedButton2Click(Sender: TObject);
begin
  // WindowsMediaPlayer1.playState:=1;
 WindowsMediaPlayer1.Controls.stop ;
// WindowsMediaPlayer1.Controls.uiMode::='None'; 播放器界面模式，可为Full, Mini, None, Invisible
//WindowsMediaPlayer1.controls.:=false;
  is_myplay:=false;
end;

procedure TMainForm.imgCloseClick(Sender: TObject);
begin
   MainForm.Close;
end;

procedure TMainForm.Image_BACKMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
Begin
     if ssleft in shift then
      releasecapture;
      perform(WM_SYSCOMMAND,$F012,0);

end;


procedure TMainForm.Button5Click(Sender: TObject);
var
  usertalkto:LongInt;
  strGetMessageSend:array[1..254] of byte;
  charsum:Integer;
  i:integer;

begin


    usertalkto := longint(-1);


  //获取发送窗口信息
   //  setLength(strGetMessageSend,length(m_ctrlEditSendMsg.Text));
  //  copymemory((@strGetMessageSend),pchar(m_ctrlEditSendMsg.Text),length(m_ctrlEditSendMsg.Text));
 // strGetMessageSend:=pchar(m_ctrlEditSendMsg.Text);
    //  //清除该用户占用列表位置的信息
     charsum:= length(m_ctrlEditSendMsg.Text);
      if charsum<1 then exit;

     for i:=1 to charsum do strGetMessageSend[i]:=byte(m_ctrlEditSendMsg.Text[i]);
     if mainform.m_ChatModeCombo.ItemIndex<>0 then
     usertalkto :=TUserInfo(m_lbOnLineUserList.Items.Objects[mainform.m_ChatModeCombo.ItemIndex+1]).UserID;
     BRAC_TransBuffer(usertalkto,@strGetMessageSend[1],charsum);
     
   // if m_lbOnLineUserList.Items.Count>1 then
  //  for i:=m_lbOnLineUserList.Items.Count-1 downto 1 do //0是所有人那个-1是无效的
  //  begin
       // if TUserInfo(m_lbOnLineUserList.Items.Objects[i]).UserID
       // usertalkto :=TUserInfo(m_lbOnLineUserList.Items.Objects[i+1]).UserID; //m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex+1)
        
  // end;

end;

procedure TMainForm.Panel2DblClick(Sender: TObject);
VAR
    i:INTEGER;
begin

  if  TPanel(Sender).Align=alclient then
  begin
      TPanel(Sender).Align:=alNONE;
     
      TPanel(Sender).Top:= UserZoomPos.TOP ;
      TPanel(Sender).Left:= UserZoomPos.LEFT ;
      TPanel(Sender).Width := UserZoomPos.WIDTH;
      TPanel(Sender).Height :=UserZoomPos.Heigth  ;
    //  TPanel(Sender).Visible:=FALSE;
      TPanel(Sender).BringToFront;
      for i:=1 to 5 do
      begin
         if m_UserRect[i]=TPanel(Sender) then
         begin
            // m_UserIMAGE[i]
             m_UserIMAGE[i].Visible:=true;
             break;
         end;
        //  m_UserRect:array[0..6] of TPanel;//TRect;
        // m_UserIMAGE:array[0..6] of TIMAGE;//TRect;
      end;

     Panel1.Top:=  MyZoomPos.TOP;
     Panel1.Left :=MyZoomPos.LEFT;
     Panel1.Width:= MyZoomPos.WIDTH;
     Panel1.Height:=MyZoomPos.Heigth;

     IMAGE0.Visible:=TRUE;;


      Panel1.BringToFront;
  end else begin
  
  end;
end;

procedure TMainForm.m_lbOnLineUserListMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
  var
  i:integer;
  sUserIP :array[0..30] of char;
   ipq:Tqqwry;
begin

     if m_lbOnLineUserList.ItemIndex<1 then
     BEGIN
       m_lbOnLineUserList.ShowHint:=FALSE;;
       EXIT;
     END;
   //  begin
           ZeroMemory(@sUserIP,sizeof(sUserIP)); //查IP
          BRAC_QueryUserState(TUserInfo(m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex]).UserID,BRAC_USERSTATE_INTERNETIP,@sUserIP,sizeof(sUserIP));

          if TUserInfo(m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex]).UserCountry  ='' then
            try
              ipq:=tqqwry.Create(ExtractFilePath(Application.ExeName)+'QQWry.Dat');
              ipq.qqwry(TUserInfo(m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex]).UserIP);
              TUserInfo(m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex]).UserCountry:=ipq.Country+ipq.Local ;
            finally
              ipq.Free;
           end;
            m_lbOnLineUserList.Hint:= TUserInfo(m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex]).UserCountry;


             m_lbOnLineUserList.ShowHint:=true;;

  //  end;


    AppendLogString(TUserInfo(m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex]).UserCountry+'['+TUserInfo(m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex]).UserIP+']');

    if m_lbOnLineUserList.ItemIndex>0 then
    m_lbOnLineUserList.Hint:= TUserInfo(m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex]).UserCountry
                             +'['+TUserInfo(m_lbOnLineUserList.Items.Objects[m_lbOnLineUserList.ItemIndex]).UserIP+']';

end;

procedure TMainForm.N7Click(Sender: TObject);
var
  usertalkto:LongInt;
  strGetMessageSend:array[1..254] of byte;
  charsum:Integer;
  i,j:integer;
  str:string;
begin

     str:='OpenyourCamera';
    usertalkto := longint(-1);
    for i:=0 to 5 do
    begin
       if timage(Sender).Parent=  m_UserRect[i] then
       begin
          usertalkto:= m_iUserID[i];
          if m_iUserID[i]<>longint(-1) then
          begin
                charsum:=length(str);
                for j:=1 to charsum do strGetMessageSend[j]:=byte(str[j]);
               
               BRAC_TransBuffer(usertalkto,@strGetMessageSend[1],charsum);

          end;

          break;
       end;

    end;


end;

procedure TMainForm.N2Click(Sender: TObject);
var
  usertalkto:LongInt;
  i,j:integer;
begin

        showmessage(timage(Sender).Parent.Name);
    usertalkto := longint(-1);
    for i:=0 to 5 do
    begin

       if timage(Sender).Parent=  m_UserRect[i] then
       begin
          usertalkto:= m_iUserID[i];
           showmessage(inttostr(longint(usertalkto)));
          if m_iUserID[i]<>longint(-1) then
          begin
              	BRAC_UserCameraControl(usertalkto,false);

          end;

          break;
       end;

    end;


end;

procedure TMainForm.N1Click(Sender: TObject);
var
  usertalkto:LongInt;
  i,j:integer;
begin


    usertalkto := longint(-1);
    for i:=0 to 5 do
    begin
       if  timage(Sender).Parent=  m_UserRect[i] then
       begin
          usertalkto:= m_iUserID[i];
          if m_iUserID[i]<>longint(-1) then
          begin
              	BRAC_UserCameraControl(usertalkto,true);

          end;

          break;
       end;

    end;


end;

procedure TMainForm.OpenVideoClick(Sender: TObject);
begin
  try
                BRAC_SetVideoPos(dword(-1),m_UserRect[0].Handle,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].BoundsRect.right,m_UserRect[0].BoundsRect.bottom);
               	BRAC_UserCameraControl(dword(-1),OpenVideo.Checked);

           except

           end;
end;

end.


