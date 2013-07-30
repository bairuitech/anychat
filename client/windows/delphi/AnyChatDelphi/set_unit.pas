unit set_unit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, StdCtrls, Buttons, ExtCtrls,
  BRAnyChatCoreSDK,GVErrorCodeDefine,GVMessageDefine,GVSDK;

type
  TForm2 = class(TForm)
    GroupBox2: TGroupBox;
    GroupBox3: TGroupBox;
    GroupBox4: TGroupBox;
    GroupBox1: TGroupBox;
    Label8: TLabel;
    Label7: TLabel;
    m_cbAudioCapture: TComboBox;
    m_cbVideoCapture: TComboBox;
    ComboBox1: TComboBox;
    BitBtn1: TBitBtn;
    m_bEnableDEINTERLACE: TCheckBox;
    ComboBox2: TComboBox;
    m_bEnableAGC: TCheckBox;
    m_bEnableEcho: TCheckBox;
    m_bEnableNS: TCheckBox;
    m_bEnableVAD: TCheckBox;
    m_bEnableMICBOOST: TCheckBox;
    m_ctrlOutVolume: TTrackBar;
    m_ctrlInVolume: TTrackBar;
    Label1: TLabel;
    Label2: TLabel;
    Button1: TButton;
    ComboBox3: TComboBox;
    procedure FormCreate(Sender: TObject);
    procedure ComboBox2Change(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure m_ctrlOutVolumeChange(Sender: TObject);
    procedure m_ctrlInVolumeChange(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure m_cbAudioCaptureChange(Sender: TObject);
    procedure m_cbVideoCaptureChange(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation

{$R *.dfm}

procedure TForm2.FormCreate(Sender: TObject);
var
  DeviceName:Array[0..10] of PChar;
  DeviceNum:LongWord;
  i:Integer;
  //
  szVideoDeviceName:Array[0..100] of Char;
  n:Integer;
  M_AUDIO_CPATUREMODE:INTEGER;
  szAudioDeviceName:Array[0..100] of Char;
begin
  // 刷新视频采集设备下拉列表
  ZeroMemory(@DeviceName,sizeof(DeviceName));
  DeviceNum:=10;
  BRAC_EnumVideoCapture(@DeviceName,DeviceNum);
  m_cbVideoCapture.Items.Clear;
  for i:=0 to DeviceNum-1 do
  begin
    if Assigned(DeviceName[i]) then
		begin
			m_cbVideoCapture.Items.Add(StrPas(DeviceName[i]));
                        GlobalFree(HGLOBAL(DeviceName[i]));
			DeviceName[i] := nil;
		end;
  end;

  // 选择当前打开的视频采集设备
  ZeroMemory(@szVideoDeviceName,sizeof(szVideoDeviceName));
  BRAC_GetCurVideoCapture(szVideoDeviceName,sizeof(szVideoDeviceName));
  n:=m_cbVideoCapture.Items.IndexOf(StrPas(@szVideoDeviceName));
  m_cbVideoCapture.ItemIndex:=n;

  // 刷新音频采集设备下拉列表
	DeviceNum := 10;
	BRAC_EnumAudioCapture(@DeviceName,DeviceNum);
  m_cbAudioCapture.Items.Clear;
  for i:=0 to DeviceNum-1 do
  begin
    if Assigned(DeviceName[i]) then
    begin
      m_cbAudioCapture.Items.Add(StrPas(DeviceName[i]));
      GlobalFree(HGLOBAL(DeviceName[i]));
			DeviceName[i] := nil;
    end;
  end;
	// 选择当前打开的音频采集设备
  ZeroMemory(@szAudioDeviceName,sizeof(szAudioDeviceName));
  BRAC_GetCurAudioCapture(szAudioDeviceName,sizeof(szAudioDeviceName));
  n:=m_cbAudioCapture.Items.IndexOf(StrPas(@szAudioDeviceName));
  m_cbAudioCapture.ItemIndex:=n;

  //  M_AUDIO_CPATUREMODE:=0;// ComboBox1.ItemIndex;  //默认发言模式
   // BRAC_SetSDKOption(BRAC_SO_AUDIO_CPATUREMODE,(@M_AUDIO_CPATUREMODE),sizeof(M_AUDIO_CPATUREMODE));

end;


procedure TForm2.ComboBox2Change(Sender: TObject);
VAR M_AUDIO_CPATUREMODE:INTEGER;
   AGC,VAD,NSC,ECH,MICBOOST:DWORD;
begin
   // M_AUDIO_CPATUREMODE:= ComboBox2.ItemIndex;
   // BRAC_SetSDKOption(BRAC_SO_AUDIO_CPATUREMODE,(@M_AUDIO_CPATUREMODE),sizeof(M_AUDIO_CPATUREMODE));
    
   //  MAINFORM.WindowsMediaPlayer1.Visible :=(ComboBox1.ItemIndex=1);
       // SDK内核参数状态查询
       AGC:=0;
      if BRAC_GetSDKOption(BRAC_SO_AUDIO_AGCCTRL,@AGC,sizeof(AGC))=0 then  m_bEnableAGC.Checked:=BOOLEAN(AGC);

       NSC:=0;
      if BRAC_GetSDKOption(BRAC_SO_AUDIO_NSCTRL,@NSC,sizeof(NSC))=0 then   m_bEnableNS.Checked:=BOOLEAN(NSC);

       VAD:=0;
      if BRAC_GetSDKOption(BRAC_SO_AUDIO_VADCTRL,@VAD,sizeof(VAD))=0 then   m_bEnableVAD.Checked:=BOOLEAN(VAD);

       ECH:=0;
      if BRAC_GetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,@ECH,sizeof(ECH))=0 then   m_bEnableECHO.Checked:=BOOLEAN(ECH);

    //   MICBOOST:=0;
    //  if BRAC_GetSDKOption(BRAC_SO_AUDIO_MICBOOST,@MICBOOST,sizeof(MICBOOST))=0 then   m_bEnableMICBOOST.Checked:=BOOLEAN(MICBOOST);



end;

procedure TForm2.BitBtn1Click(Sender: TObject);
begin
   // 显示本地视频画面调节对话框
	BRAC_ShowLVProperty(Handle,'NGN 本地视频画质调节',0,0);
end;

procedure TForm2.m_ctrlOutVolumeChange(Sender: TObject);
begin
    // 设置指定音频设备的音量
   BRAC_AudioSetVolume(BRAC_AD_WAVEOUT,DWORD(m_ctrlOutVolume.Position*5));
    // m_ctrlEditMessage.Lines.Add(inttostr(DWORD(m_ctrlOutVolume.Position*5)));
end;

procedure TForm2.m_ctrlInVolumeChange(Sender: TObject);
begin
       // 设置指定音频设备的音量
    BRAC_AudioSetVolume(BRAC_AD_WAVEIN,DWORD(m_ctrlInVolume.Position*5));
   //  m_ctrlEditMessage.Lines.Add(inttostr(DWORD(m_ctrlInVolume.Position*5)));
end;

procedure TForm2.Button1Click(Sender: TObject);
var

  AGC,VAD,NSC,ECH,MICBOOST,DEINTERLACE,AUTOPARAM:INTEGER;
begin
        AGC:=integer(m_bEnableAGC.Checked);
        VAD:=integer(m_bEnableVAD.Checked);
        NSC:=integer(m_bEnableNS.Checked);
        Ech:=integer(m_bEnableEcho.Checked);
        MICBOOST:=integer(m_bEnableMICBOOST.Checked);

       //  AUTOPARAM:=0;

        BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL,(@AGC),sizeof(AGC));
	BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL,@(VAD),sizeof(VAD));
	BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL,@NSC,sizeof(NSC));
	BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,@Ech,sizeof(Ech));
     ///   BRAC_SetSDKOption(BRAC_SO_AUDIO_MICBOOST,@MICBOOST,sizeof(MICBOOST));
      //  BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_DEINTERLACE,@DEINTERLACE,sizeof(DEINTERLACE));

       // BRAC_SetSDKOption(BRAC_SO_AUDIO_AUTOPARAM,@AUTOPARAM,sizeof(AUTOPARAM));
       // THEN 	ShowMessage('设置成功，返回'); ;
   close;
end;

procedure TForm2.ComboBox1Change(Sender: TObject);
var
   VideoQuality:integer;
begin
        if  ComboBox1.ItemIndex=0 then VideoQuality:=2 else
        VideoQuality:=ComboBox1.ItemIndex;
        if  BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL,@VideoQuality,sizeof(integer))<>0 then
       	showmessage('视频质量银子设置失败');
end;

procedure TForm2.m_cbAudioCaptureChange(Sender: TObject);
begin
    BRAC_SelectaudioCapture(pchar(form2.m_cbaudioCapture.text));//m_cbVideoCapture.text
end;

procedure TForm2.m_cbVideoCaptureChange(Sender: TObject);
begin
    BRAC_SelectVideoCapture(pchar(m_cbVideoCapture.text));//
end;

end.
