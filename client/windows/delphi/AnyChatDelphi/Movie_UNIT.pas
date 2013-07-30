unit Movie_UNIT;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, jpeg, ExtCtrls;

type
  TForm1 = class(TForm)
    Image1: TImage;
    Button1: TButton;
    Button2: TButton;
    Edit1: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses main_Unit;

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
  if (EDIT1.Text<>'') THEN
  BEGIN
     try
      // MAINFORM.WindowsMediaPlayer1.Visible:=true;
      MAINFORM.WindowsMediaPlayer1.url:=PCHAR(EDIT1.Text);
      MAINFORM.WindowsMediaPlayer1.controls.play();
      Form1.Close;
     except

     end;

     
  END ELSE BEGIN
       MAINFORM.WindowsMediaPlayer1.Visible:=false;;
      SHOWMESSAGE('«Î ‰»Î“Ù¿÷µÿ÷∑');

  END;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
    Form1.Close;
end;

end.
