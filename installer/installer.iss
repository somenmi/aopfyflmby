[Setup]
AppName=aopfyflmby
AppVersion=1.0
AppPublisher=Yalkee (somenmi)
AppPublisherURL=https://github.com/somenmi/aopfyflmby
DefaultDirName={pf}\aopfyflmby
DefaultGroupName=aopfyflmby
UninstallDisplayIcon={app}\logo.ico
Compression=lzma2
SolidCompression=yes
OutputDir=.
OutputBaseFilename=aopfyflmby_setup
SetupIconFile=logo.ico
WizardImageFile=setup.bmp
WizardSmallImageFile=setup.bmp
SetupLogging=yes
DisableStartupPrompt=no
PrivilegesRequired=admin
ShowLanguageDialog=yes
UsePreviousLanguage=no
DisableWelcomePage=no

VersionInfoCompany=Yalkee
VersionInfoDescription=♫
VersionInfoCopyright=© 2029 Yalkee
VersionInfoProductName=aopfyflmby
VersionInfoProductVersion=1.0

[Languages]
Name: "Russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "English"; MessagesFile: "compiler:Default.isl"
Name: "Chinese"; MessagesFile: "compiler:Languages\Chinese.isl"

[Files]
; Все три версии программы
Source: "aopfyflmby_RUS.exe"; DestDir: "{app}"; DestName: "aopfyflmby.exe"; Flags: ignoreversion; Check: IsRussianSelected
Source: "aopfyflmby_ENG.exe"; DestDir: "{app}"; DestName: "aopfyflmby.exe"; Flags: ignoreversion; Check: IsEnglishSelected
Source: "aopfyflmby_CHN.exe"; DestDir: "{app}"; DestName: "aopfyflmby.exe"; Flags: ignoreversion; Check: IsChineseSelected

; Общие файлы
Source: "bass.dll"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{commondesktop}\aopfyflmby"; Filename: "{app}\aopfyflmby.exe"; IconFilename: "{app}\aopfyflmby.exe"
Name: "{group}\aopfyflmby"; Filename: "{app}\aopfyflmby.exe"; IconFilename: "{app}\aopfyflmby.exe"
Name: "{group}\Удалить aopfyflmby"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\aopfyflmby.exe"; Description: "{cm:LaunchProgram,aopfyflmby}"; Flags: postinstall nowait skipifsilent

[Registry]
Root: HKCU; Subkey: "Software\Microsoft\Windows\CurrentVersion\Run"; ValueType: string; ValueName: "aopfyflmby"; ValueData: "{app}\aopfyflmby.exe"; Flags: uninsdeletevalue; Check: ShouldAddToAutoRun

[Code]
var
  AutoRunPage: TInputOptionWizardPage;
  VersionPage: TInputOptionWizardPage;
  SelectedVersion: Integer; // 0 = Русский, 1 = English, 2 = 中文

procedure InitializeWizard;
begin
  { Создаем страницу с автозапуском (два пункта: добавить и не добавлять) }
  AutoRunPage := CreateInputOptionPage(wpSelectTasks,
    ExpandConstant('{cm:AutoRunTitle}'),
    ExpandConstant('{cm:AutoRunDescription}'),
    ExpandConstant('{cm:AutoRunCaption}'),
    True, False);
  AutoRunPage.Add(ExpandConstant('{cm:AutoRunOptionAdd}'));
  AutoRunPage.Add(ExpandConstant('{cm:AutoRunOptionSkip}'));
  AutoRunPage.Values[1] := True;  { По умолчанию выбран пункт "Не добавлять" }
  
  { Создаем страницу выбора языка программы }
  VersionPage := CreateInputOptionPage(wpSelectProgramGroup,
    ExpandConstant('{cm:VersionTitle}'),
    ExpandConstant('{cm:VersionDescription}'),
    ExpandConstant('{cm:VersionCaption}'),
    True, False);
  VersionPage.Add(ExpandConstant('{cm:VersionRussian}'));
  VersionPage.Add(ExpandConstant('{cm:VersionEnglish}'));
  VersionPage.Add(ExpandConstant('{cm:VersionChinese}'));
  
  { По умолчанию выбираем язык, соответствующий языку интерфейса установщика }
  if ActiveLanguage = 'ru' then
    VersionPage.Values[0] := True
  else if ActiveLanguage = 'en' then
    VersionPage.Values[1] := True
  else if ActiveLanguage = 'zh' then
    VersionPage.Values[2] := True
  else
    VersionPage.Values[0] := True;
end;

function ShouldAddToAutoRun: Boolean;
begin
  { Возвращаем True, если выбран первый пункт (добавить в автозагрузку) }
  Result := AutoRunPage.Values[0];
end;

function IsRussianSelected: Boolean;
begin
  Result := VersionPage.Values[0];
  if Result then SelectedVersion := 0;
end;

function IsEnglishSelected: Boolean;
begin
  Result := VersionPage.Values[1];
  if Result then SelectedVersion := 1;
end;

function IsChineseSelected: Boolean;
begin
  Result := VersionPage.Values[2];
  if Result then SelectedVersion := 2;
end;

function GetExeName(Param: String): String;
begin
  if SelectedVersion = 0 then
    Result := 'aopfyflmby_RUS.exe'
  else if SelectedVersion = 1 then
    Result := 'aopfyflmby_ENG.exe'
  else
    Result := 'aopfyflmby_CHN.exe';
end;

[CustomMessages]
; Русский
Russian.AutoRunTitle=Автозапуск
Russian.AutoRunDescription=Запускать при старте Windows
Russian.AutoRunCaption=Выберите опцию автозапуска:
Russian.AutoRunOptionAdd=Добавить aopfyflmby в автозагрузку
Russian.AutoRunOptionSkip=Не добавлять в автозагрузку

Russian.VersionTitle=Выбор языка программы
Russian.VersionDescription=Какой язык будет установлен по умолчанию (в настройках, будет возможность изменить на любой)
Russian.VersionCaption=Выберите версию программы:
Russian.VersionRussian=Русский
Russian.VersionEnglish=English (Английский)
Russian.VersionChinese=中文 (Китайский)

Russian.WelcomeText=Добро пожаловать в aopfyflmby!%n%nЭтот установщик поможет вам установить музыкальный плеер на ваш компьютер.

; English
English.AutoRunTitle=AutoRun
English.AutoRunDescription=Launch at Windows startup
English.AutoRunCaption=Select auto-run option:
English.AutoRunOptionAdd=Add aopfyflmby to startup
English.AutoRunOptionSkip=Do not add to startup

English.VersionTitle=Program Language Selection
English.VersionDescription=Which language will be set by default (in the settings, you will be able to change it to any)
English.VersionCaption=Select program version:
English.VersionRussian=Russian
English.VersionEnglish=English
English.VersionChinese=Chinese

English.WelcomeText=Welcome to aopfyflmby!%n%nThis installer will help you install the music player on your computer.

; Chinese
Chinese.AutoRunTitle=自动启动
Chinese.AutoRunDescription=Windows启动时运行
Chinese.AutoRunCaption=选择自动启动选项：
Chinese.AutoRunOptionAdd=添加 aopfyflmby 到自动启动
Chinese.AutoRunOptionSkip=不添加到自动启动

Chinese.VersionTitle=程序语言选择
Chinese.VersionDescription=默认设置哪种语言 (在设置中，您可以随时更改为任何语言)
Chinese.VersionCaption=选择程序版本：
Chinese.VersionRussian=俄语 (RU)
Chinese.VersionEnglish=英语 (EN)
Chinese.VersionChinese=中文 (CH)

Chinese.WelcomeText=欢迎使用 aopfyflmby！%n%n此安装程序将帮助您在计算机上安装音乐播放器。