program anyshatroom;

uses
  Forms,
  main_Unit in 'main_Unit.pas' {MainForm},
  Movie_UNIT in 'Movie_UNIT.pas' {Form1},
  LoginUnit in 'LoginUnit.pas' {LoginForm},
  set_unit in 'set_unit.pas' {Form2},
  qqwry in 'qqwry.pas',
  Unit3 in 'Unit3.pas' {Form3};

{$R *.res}

begin
  Application.Initialize;
 

  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TForm2, Form2);
  Application.CreateForm(TForm3, Form3);
  LoginForm:=tLoginForm.Create(application);
  LoginForm.ShowModal;
  LoginForm.Free;
  MainForm.Visible:=true;
 // Application.CreateForm(TForm1, Form1);
  //Application.CreateForm(TLoginForm, LoginForm);
  Application.Run;
end.
