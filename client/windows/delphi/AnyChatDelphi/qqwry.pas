unit qqwry;

interface

uses Classes,Types,SysUtils,Math,dialogs;

type
  TQQwry = class
  public
    StartIP:DWORD;
    EndIP:DWORD;
    Country:string;
    Local:string;
    CountryFlag:integer; // 标识 Country位置
                          // 0x01,随后3字节为Country偏移,没有Local
                          // 0x02,随后3字节为Country偏移，接着是Local
                          // 其他,Country,Local,Local有类似的压缩。可能多重引用。
    FirstStartIp:DWORD;
    LastStartIp:DWORD;
    EndIpOff:integer;
    fHandle:integer;
    datafile:string;
    //FileLen:integer;
    constructor Create(dbfile:string);virtual;
    destructor Destroy;override;

    function qqwry(dotip:string):integer;

  private
    function IpToInt(ip:string):DWORD;
    function IntToIp(ipint:integer):string;
    function toInt(doint:integer):integer;
    function GetStartIp(RecNo:integer):DWORD;
    function GetEndIp():DWORD;
    function GetStr():string;
    function getFlagStr(offset:integer):string;
    procedure getCountry();
end;

implementation

function Tqqwry.IpToInt(ip:string):DWORD;
var
  str:TStringList;
begin
  str:=TStringList.Create;
  str.CommaText:=stringreplace(ip,'.',' ',[rfReplaceAll]);
  result:=(StrToInt(str.Strings[0]) * 256*256*256)
            + (StrToInt(str.Strings[1])*256*256)
            + (StrToInt(str.Strings[2])*256)
            + StrToInt(str.Strings[3]);
  str.Free;
end;

function Tqqwry.IntToIp(ipint:integer):string;
var
  b1,b2,b3,b4:integer;
begin
    b1:=(ipint and $ff000000)shr 24;
    if (b1<0) then b1:=b1+$100;
    b2:=(ipint and $00ff0000)shr 16;
    if (b2<0) then b2:=b2+$100;
    b3:=(ipint and $0000ff00)shr 8;
    if (b3<0) then b3:=b3+$100;
    b4:= ipint and $000000ff;
    if (b4<0) then b4:=b4+$100;
    result:=inttostr(b1)+'.'+inttostr(b2)+'.'+inttostr(b3)+'.'+inttostr(b4);
end;

constructor TQQwry.Create(dbfile:string);
begin
    StartIP:=0;
    EndIP:=0;
    CountryFlag:=0;
    FirstStartIp:=0;
    LastStartIp:=0;
    EndIpOff:=0;
    datafile:='QQWry.Dat';
    if(dbfile<>'') then
        datafile:=dbfile;
end;

destructor Tqqwry.Destroy;
begin
  if fhandle<>0 then FileClose(fHandle);

end;

function Tqqwry.toInt(doint:integer):integer;
begin
  result:=doint;
  if doint<0 then result:=result+256;
end;

function Tqqwry.GetStartIp(RecNo:integer):DWORD;
var
  offset:dword;
  buf:array[0..7]of char;
begin
    offset := FirstStartIp + RecNo * 7 ;
    fileseek ( fhandle , offset, 0 ) ;
    fileread ( fhandle,buf,7) ;

    EndIpOff := toint(ord(buf[4]))
                + (toint(ord(buf[5]))*256 )
                + (toint(ord(buf[6]))* 256*256);
    StartIP := toint(ord(buf[0]))
                + (toint(ord(buf[1]))*256)
                + (toint(ord(buf[2]))*256*256)
                + (toint(ord(buf[3]))*256*256*256);
    result:=StartIP ;
end;

function tqqwry.GetEndIp():DWORD;
var
  buf:array[0..4]of char;
begin
  FileSeek(fhandle,endipoff,0);
  FileRead( fhandle,buf,5);
  EndIP := toint(ord(buf[0])) + (toint(ord(buf[1]))*256) + (toint(ord(buf[2]))*256*256) + (toint(ord(buf[3]))*256*256*256);
  CountryFlag := ord ( buf[4] ) ;
  result:=EndIP ;
end;

function tqqwry.GetStr():string;
var
  c:integer;
  buf:byte;
begin
  result:='';
  while true do
  begin
    c:=FileRead(fhandle,buf,1);
    if toint(buf)=0 then break;
    result:=result+chr(buf);
  end;
end;

function tqqwry.getFlagStr(offset:integer):string;
var
  flag:integer;
  buf:Byte;
  buffer:array[0..2]of byte;
begin

  while true do
  begin
    FileSeek(fhandle,offset,0);
    FileRead(fhandle,buf,1);
    flag:=toint(buf);
    if((flag=1)or(flag=2))then
    begin
      FileRead(fhandle,buffer,3);
      if flag=2 then
      begin
        CountryFlag := 2 ;
        EndIpOff := offset - 4 ;
      end;
      offset := toint(ord(buffer[0])) + (toint(ord(buffer[1]))*256) + (toint(ord(buffer[2]))* 256*256);
    end else break;
  end;
  if offset<12 then
  begin
    result:='';
    exit;
  end;
  FileSeek(fhandle,offset,0);
  result:=getstr();
end;

procedure tqqwry.getCountry();
begin
  case CountryFlag of
  1..2:begin
            Country := getFlagStr (EndIpOff+4) ;
            if(1 = CountryFlag) then
                Local := ''
            else
                Local := getFlagStr (EndIpOff+8);
       end;
  else
       begin
            Country := getFlagStr (EndIpOff+4) ;

            Local :=   getFlagStr ( fileseek(fhandle,0,1)) ;//fileseek(fhandle,0,1)获得当前文件指针位置
       end;
  end;
end;



function tqqwry.qqwry(dotip:string):integer;
var
  nRet:integer;
  ip:DWORD;
  buf:array[0..7]of char;
  RecintCount,RangB,RangE,RecNo:integer;
begin
  fHandle:=FileOpen(datafile,fmOpenRead);

  if fHandle=0 then
  begin
    showmessage('wrong');
    result:=-1;
    exit;
  end;
  //filelen:=fileseek(fhandle,0,2);
  ip:= IpToInt ( dotip );
  FileSeek(fhandle,0,0);
  fileRead(fhandle,buf,8);
  FirstStartIp := toint(ord(buf[0])) + ((toint(ord(buf[1])))*256) + (toint(ord(buf[2]))*256*256) + (toint(ord(buf[3]))*256*256*256);
  LastStartIp  := toint(ord(buf[4])) + (toint(ord(buf[5]))*256) + (toint(ord(buf[6]))*256*256) + (toint(ord(buf[7]))*256*256*256);

  RecintCount := floor( ( LastStartIp - FirstStartIp ) / 7);

//  showmessage(inttostr(RecintCount)+','+inttostr(LastStartIp));
  if (RecintCount <= 1) then
  begin
        Country := 'FileDataError';
        result:=2 ;
        exit;
  end;
  RangB:= 0;
  RangE:= RecintCount;
  while (RangB < RangE-1) do
  begin
    RecNo:= floor((RangB + RangE) / 2);
    getStartIp(RecNo);
    if ip=StartIp then
    begin
      RangB:=Recno;
      break;
    end;
    if ip>StartIp then
      RangB:=RecNo
    else
      RangE:=RecNo;

  end;//end of while
  getStartIp ( RangB ) ;
  getEndIp ( ) ;
  if((startip<=ip)and(endip>=ip)) then
  begin
    nRet:=0;
    getCountry();
  end else begin
    nRet:=3;
    Country:='未知';
    Local:='';
  end;
  result:=nRet;
end;

end.

