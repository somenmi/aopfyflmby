; *** Inno Setup version 6.5.0+ Chinese Simplified messages ***
;
; Translation by somenmi

[LangOptions]
LanguageName=中文
LanguageID=$0804
LanguageCodePage=936

[Messages]

; *** Application titles
SetupAppTitle=安装
SetupWindowTitle=安装 — %1
UninstallAppTitle=卸载
UninstallAppFullTitle=卸载 — %1

; *** Misc. common
InformationTitle=信息
ConfirmTitle=确认
ErrorTitle=错误

; *** SetupLdr messages
SetupLdrStartupMessage=此程序将在您的计算机上安装 %1，是否继续？
LdrCannotCreateTemp=无法创建临时文件。安装已中止
LdrCannotExecTemp=无法在临时目录中执行文件。安装已中止
HelpTextNote=

; *** Startup error messages
LastErrorMessage=%1。%n%n错误 %2: %3
SetupFileMissing=安装文件夹中缺少文件 %1。请纠正问题或获取程序的新副本。
SetupFileCorrupt=安装文件已损坏。请获取程序的新副本。
SetupFileCorruptOrWrongVer=这些安装文件已损坏或与此版本的安装程序不兼容。请纠正问题或获取程序的新副本。
InvalidParameter=命令行包含无效参数：%n%n%1
SetupAlreadyRunning=安装程序已在运行。
WindowsVersionNotSupported=此程序不支持您计算机上安装的 Windows 版本。
WindowsServicePackRequired=此程序需要 %1 Service Pack %2 或更高版本。
NotOnThisPlatform=此程序不能在 %1 上运行。
OnlyOnThisPlatform=此程序只能在 %1 上运行。
OnlyOnTheseArchitectures=此程序只能安装在以下处理器架构的 Windows 版本上：%n%n%1
WinVersionTooLowError=此程序需要 %1 版本 %2 或更高版本。
WinVersionTooHighError=此程序无法安装在 %1 版本 %2 或更高版本上。
AdminPrivilegesRequired=要安装此程序，您必须以管理员身份登录。
PowerUserPrivilegesRequired=要安装此程序，您必须以管理员或高级用户组成员的身份登录。
SetupAppRunningError=检测到 %1 正在运行。%n%n请关闭所有应用程序实例，然后按“确定”继续，或按“取消”退出。
UninstallAppRunningError=卸载程序检测到 %1 正在运行。%n%n请关闭所有应用程序实例，然后按“确定”继续，或按“取消”退出。

; *** Startup questions
PrivilegesRequiredOverrideTitle=选择安装模式
PrivilegesRequiredOverrideInstruction=选择安装模式
PrivilegesRequiredOverrideText1=%1 可以安装为所有用户（需要管理员权限）或仅为您自己安装。
PrivilegesRequiredOverrideText2=%1 可以仅为您自己安装，或安装为所有用户（需要管理员权限）。
PrivilegesRequiredOverrideAllUsers=安装为所有用户(&A)
PrivilegesRequiredOverrideAllUsersRecommended=安装为所有用户(&A)（推荐）
PrivilegesRequiredOverrideCurrentUser=仅为我安装(&M)
PrivilegesRequiredOverrideCurrentUserRecommended=仅为我安装(&M)（推荐）

; *** Misc. errors
ErrorCreatingDir=无法创建文件夹 "%1"
ErrorTooManyFilesInDir=无法在目录 "%1" 中创建文件，因为该目录中的文件过多

; *** Setup common messages
ExitSetupTitle=退出安装程序
ExitSetupMessage=安装尚未完成。如果退出，程序将不会被安装。%n%n您可以稍后再次运行安装程序来完成安装。%n%n是否退出安装程序？
AboutSetupMenuItem=关于(&A)...
AboutSetupTitle=关于
AboutSetupMessage=%1，版本 %2%n%3%n%n%1 网站：%n%4
AboutSetupNote=
TranslatorNote=中文翻译

; *** Buttons
ButtonBack=上一步(&B)
ButtonNext=下一步(&N)
ButtonInstall=安装(&I)
ButtonOK=确定
ButtonCancel=取消
ButtonYes=是(&Y)
ButtonYesToAll=全部是(&A)
ButtonNo=否(&N)
ButtonNoToAll=全部否(&O)
ButtonFinish=完成(&F)
ButtonBrowse=浏览(&B)...
ButtonWizardBrowse=浏览(&B)...
ButtonNewFolder=新建文件夹(&N)

; *** "Select Language" dialog messages
SelectLanguageTitle=选择安装语言
SelectLanguageLabel=选择安装过程中要使用的语言。

; *** Common wizard text
ClickNext=单击“下一步”继续，或单击“取消”退出安装程序。
BeveledLabel=
BrowseDialogTitle=浏览文件夹
BrowseDialogLabel=从列表中选择一个文件夹，然后单击“确定”。
NewFolderName=新建文件夹

; *** "Welcome" wizard page
WelcomeLabel1=欢迎使用 [name] 安装向导
WelcomeLabel2=此程序将在您的计算机上安装 [name/ver]。%n%n建议您在继续之前关闭所有其他应用程序。

; *** "Password" wizard page
WizardPassword=密码
PasswordLabel1=此程序受密码保护。
PasswordLabel3=请输入密码，然后单击“下一步”。密码区分大小写。
PasswordEditLabel=密码(&P):
IncorrectPassword=您输入的密码不正确。请重试。

; *** "License Agreement" wizard page
WizardLicense=许可协议
LicenseLabel=请在继续之前阅读以下重要信息。
LicenseLabel3=请阅读以下许可协议。您必须接受此协议的条款才能继续。
LicenseAccepted=我接受协议(&A)
LicenseNotAccepted=我不接受协议(&N)

; *** "Information" wizard pages
WizardInfoBefore=信息
InfoBeforeLabel=请在继续之前阅读以下重要信息。
InfoBeforeClickLabel=准备继续安装时，单击“下一步”。
WizardInfoAfter=信息
InfoAfterLabel=请在继续之前阅读以下重要信息。
InfoAfterClickLabel=准备继续安装时，单击“下一步”。

; *** "User Information" wizard page
WizardUserInfo=用户信息
UserInfoDesc=请输入您的信息。
UserInfoName=用户名(&N):
UserInfoOrg=组织(&O):
UserInfoSerial=序列号(&S):
UserInfoNameRequired=您必须输入用户名。

; *** "Select Destination Location" wizard page
WizardSelectDir=选择目标位置
SelectDirDesc=您想将 [name] 安装在哪里？
SelectDirLabel3=安装程序将把 [name] 安装到以下文件夹。
SelectDirBrowseLabel=单击“下一步”继续。如果您想选择其他文件夹，请单击“浏览”。
DiskSpaceGBLabel=至少需要 [gb] GB 的可用磁盘空间。
DiskSpaceMBLabel=至少需要 [mb] MB 的可用磁盘空间。
CannotInstallToNetworkDrive=无法安装到网络驱动器。
CannotInstallToUNCPath=无法安装到 UNC 路径。
InvalidPath=您必须指定一个包含驱动器的完整路径；例如：%n%nC:\APP%n%n或 UNC 路径：%n%n\\服务器名\共享名
InvalidDrive=您选择的驱动器或网络路径不存在或不可访问。请选择其他位置。
DiskSpaceWarningTitle=磁盘空间不足
DiskSpaceWarning=安装需要至少 %1 KB 的可用空间，但所选驱动器上只有 %2 KB 可用。%n%n是否仍要继续安装？
DirNameTooLong=文件夹名称或路径过长。
InvalidDirName=指定的文件夹名称无效。
BadDirName32=文件夹名称不能包含以下字符：%n%n%1
DirExistsTitle=文件夹已存在
DirExists=文件夹%n%n%1%n%n已存在。是否仍要安装到此文件夹？
DirDoesntExistTitle=文件夹不存在
DirDoesntExist=文件夹%n%n%1%n%n不存在。是否要创建该文件夹？

; *** "Select Components" wizard page
WizardSelectComponents=选择组件
SelectComponentsDesc=要安装哪些组件？
SelectComponentsLabel2=选择要安装的组件，清除不想安装的组件的复选框。准备继续时单击“下一步”。
FullInstallation=完整安装
CompactInstallation=紧凑安装
CustomInstallation=自定义安装
NoUninstallWarningTitle=已安装的组件
NoUninstallWarning=安装程序检测到以下组件已安装在您的计算机上：%n%n%1%n%n取消选择这些组件不会将其删除。%n%n是否继续？
ComponentSize1=%1 KB
ComponentSize2=%1 MB
ComponentsDiskSpaceGBLabel=当前选择至少需要 [gb] GB 磁盘空间。
ComponentsDiskSpaceMBLabel=当前选择至少需要 [mb] MB 磁盘空间。

; *** "Select Additional Tasks" wizard page
WizardSelectTasks=选择附加任务
SelectTasksDesc=要执行哪些附加任务？
SelectTasksLabel2=选择安装 [name] 时要执行的附加任务，然后单击“下一步”：

; *** "Select Start Menu Folder" wizard page
WizardSelectProgramGroup=选择开始菜单文件夹
SelectStartMenuFolderDesc=安装程序应在哪里创建快捷方式？
SelectStartMenuFolderLabel3=安装程序将在以下开始菜单文件夹中创建快捷方式。
SelectStartMenuFolderBrowseLabel=单击“下一步”继续。如果您想选择其他文件夹，请单击“浏览”。
MustEnterGroupName=您必须输入文件夹名称。
GroupNameTooLong=组文件夹名称或路径过长。
InvalidGroupName=指定的组文件夹名称无效。
BadGroupName=组文件夹名称不能包含以下字符：%n%n%1
NoProgramGroupCheck2=不创建开始菜单文件夹(&D)

; *** "Ready to Install" wizard page
WizardReady=准备安装
ReadyLabel1=安装程序已准备好开始在您的计算机上安装 [name]。
ReadyLabel2a=单击“安装”继续，或单击“上一步”查看或更改安装设置。
ReadyLabel2b=单击“安装”继续。
ReadyMemoUserInfo=用户信息：
ReadyMemoDir=目标位置：
ReadyMemoType=安装类型：
ReadyMemoComponents=所选组件：
ReadyMemoGroup=开始菜单文件夹：
ReadyMemoTasks=附加任务：

; *** TDownloadWizardPage wizard page and DownloadTemporaryFile
DownloadingLabel2=正在下载文件...
ButtonStopDownload=停止下载(&S)
StopDownload=您确定要停止下载吗？
ErrorDownloadAborted=下载已中止
ErrorDownloadFailed=下载失败：%1 %2
ErrorDownloadSizeFailed=获取大小失败：%1 %2
ErrorProgress=执行错误：%1 / %2
ErrorFileSize=文件大小不正确：预期 %1，实际 %2

; *** TExtractionWizardPage wizard page and Extract7ZipArchive
ExtractingLabel=正在解压文件...
ButtonStopExtraction=停止解压(&S)
StopExtraction=您确定要停止解压吗？
ErrorExtractionAborted=解压已中止
ErrorExtractionFailed=解压失败：%1

; *** Archive extraction failure details
ArchiveIncorrectPassword=密码不正确
ArchiveIsCorrupted=压缩包已损坏
ArchiveUnsupportedFormat=不支持的压缩包格式

; *** "Preparing to Install" wizard page
WizardPreparing=准备安装
PreparingDesc=安装程序正在准备将 [name] 安装到您的计算机。
PreviousInstallNotCompleted=之前程序的安装或卸载未完成。您需要重新启动计算机以完成该安装。%n%n重新启动后，请再次运行安装程序以完成 [name] 的安装。
CannotContinue=无法继续安装。单击“取消”退出安装程序。
ApplicationsFound=以下应用程序正在使用安装程序需要更新的文件。建议让安装程序自动关闭这些应用程序。
ApplicationsFound2=以下应用程序正在使用安装程序需要更新的文件。建议让安装程序自动关闭这些应用程序。安装完成后，安装程序将尝试重新启动它们。
CloseApplications=自动关闭这些应用程序(&A)
DontCloseApplications=不关闭这些应用程序(&D)
ErrorCloseApplications=安装程序无法自动关闭所有应用程序。建议您在继续安装之前关闭所有使用需要更新的文件的应用程序。
PrepareToInstallNeedsRestart=安装程序需要重新启动您的计算机。重新启动完成后，请再次运行安装程序以完成 [name] 的安装。%n%n是否立即重新启动？

; *** "Installing" wizard page
WizardInstalling=正在安装
InstallingLabel=请等待，直到 [name] 安装到您的计算机。

; *** "Setup Completed" wizard page
FinishedHeadingLabel=完成 [name] 安装向导
FinishedLabelNoIcons=[name] 已安装在您的计算机上。
FinishedLabel=[name] 已安装在您的计算机上。可以使用相应图标启动应用程序。
ClickFinish=单击“完成”退出安装程序。
FinishedRestartLabel=要完成 [name] 的安装，需要重新启动您的计算机。是否立即重新启动？
FinishedRestartMessage=要完成 [name] 的安装，需要重新启动您的计算机。%n%n是否立即重新启动？
ShowReadmeCheck=查看 README 文件
YesRadio=是，立即重新启动(&Y)
NoRadio=否，稍后重新启动(&N)
RunEntryExec=运行 %1
RunEntryShellExec=查看 %1

; *** "Setup Needs the Next Disk" stuff
ChangeDiskTitle=需要下一张磁盘
SelectDiskLabel2=请插入磁盘 %1 并单击“确定”。%n%n如果该磁盘上的文件可以在以下位置以外的其他位置找到，请输入正确的路径或单击“浏览”。
PathLabel=路径(&P):
FileNotInDir2=在 "%2" 中未找到文件 "%1"。请插入正确的磁盘或选择其他文件夹。
SelectDirectoryLabel=请指定下一张磁盘的路径。

; *** Installation phase messages
SetupAborted=安装未完成。%n%n请纠正问题并再次运行安装程序。
AbortRetryIgnoreSelectAction=选择操作
AbortRetryIgnoreRetry=重试(&R)
AbortRetryIgnoreIgnore=忽略并继续(&I)
AbortRetryIgnoreCancel=取消安装
RetryCancelSelectAction=选择操作
RetryCancelRetry=重试(&R)
RetryCancelCancel=取消

; *** Installation status messages
StatusClosingApplications=正在关闭应用程序...
StatusCreateDirs=正在创建文件夹...
StatusExtractFiles=正在解压文件...
StatusDownloadFiles=正在下载文件...
StatusCreateIcons=正在创建快捷方式...
StatusCreateIniEntries=正在创建 INI 条目...
StatusCreateRegistryEntries=正在创建注册表条目...
StatusRegisterFiles=正在注册文件...
StatusSavingUninstall=正在保存卸载信息...
StatusRunProgram=正在完成安装...
StatusRestartingApplications=正在重新启动应用程序...
StatusRollback=正在回滚更改...

; *** Misc. errors
ErrorInternal2=内部错误: %1
ErrorFunctionFailedNoCode=%1: 失败
ErrorFunctionFailed=%1: 失败; 错误代码 %2
ErrorFunctionFailedWithMessage=%1: 失败; 错误代码 %2。%n%3
ErrorExecutingProgram=无法执行文件：%n%1

; *** Registry errors
ErrorRegOpenKey=打开注册表项时出错：%n%1\%2
ErrorRegCreateKey=创建注册表项时出错：%n%1\%2
ErrorRegWriteKey=写入注册表项时出错：%n%1\%2

; *** INI errors
ErrorIniEntry=在 INI 文件 "%1" 中创建条目时出错。

; *** File copying errors
FileAbortRetryIgnoreSkipNotRecommended=跳过此文件(&S)（不推荐）
FileAbortRetryIgnoreIgnoreNotRecommended=忽略并继续(&I)（不推荐）
SourceIsCorrupted=源文件已损坏
SourceDoesntExist=源文件 "%1" 不存在
SourceVerificationFailed=源文件验证失败: %1
VerificationSignatureDoesntExist=签名文件 "%1" 不存在
VerificationSignatureInvalid=签名文件 "%1" 无效
VerificationKeyNotFound=签名文件 "%1" 使用未知密钥
VerificationFileNameIncorrect=文件名不正确
VerificationFileTagIncorrect=文件标签不正确
VerificationFileSizeIncorrect=文件大小不正确
VerificationFileHashIncorrect=文件哈希值不正确
ExistingFileReadOnly2=无法替换现有文件，因为它被标记为只读。
ExistingFileReadOnlyRetry=删除只读属性并重试(&R)
ExistingFileReadOnlyKeepExisting=保留现有文件(&K)
ErrorReadingExistingDest=尝试读取现有文件时出错：
FileExistsSelectAction=选择操作
FileExists2=文件已存在。
FileExistsOverwriteExisting=覆盖现有文件(&O)
FileExistsKeepExisting=保留现有文件(&K)
FileExistsOverwriteOrKeepAll=对所有后续冲突应用此操作(&A)
ExistingFileNewerSelectAction=选择操作
ExistingFileNewer2=现有文件比正在安装的文件更新。
ExistingFileNewerOverwriteExisting=覆盖现有文件(&O)
ExistingFileNewerKeepExisting=保留现有文件(&K)（推荐）
ExistingFileNewerOverwriteOrKeepAll=对所有后续冲突应用此操作(&A)
ErrorChangingAttr=尝试更改现有文件的属性时出错：
ErrorCreatingTemp=尝试在目标文件夹中创建文件时出错：
ErrorReadingSource=尝试读取源文件时出错：
ErrorCopying=尝试复制文件时出错：
ErrorDownloading=尝试下载文件时出错：
ErrorExtracting=尝试从压缩包提取文件时出错：
ErrorReplacingExistingFile=尝试替换现有文件时出错：
ErrorRestartReplace=RestartReplace 错误：
ErrorRenamingTemp=尝试重命名目标文件夹中的文件时出错：
ErrorRegisterServer=无法注册 DLL/OCX: %1
ErrorRegSvr32Failed=执行 RegSvr32 时出错，返回代码 %1
ErrorRegisterTypeLib=无法注册类型库: %1

; *** Uninstall display name markings
UninstallDisplayNameMark=%1 (%2)
UninstallDisplayNameMarks=%1 (%2, %3)
UninstallDisplayNameMark32Bit=32位
UninstallDisplayNameMark64Bit=64位
UninstallDisplayNameMarkAllUsers=所有用户
UninstallDisplayNameMarkCurrentUser=当前用户

; *** Post-installation errors
ErrorOpeningReadme=尝试打开 README 文件时出错。
ErrorRestartingComputer=安装程序无法重新启动计算机。请手动重新启动。

; *** Uninstaller messages
UninstallNotFound=文件 "%1" 不存在，无法卸载。
UninstallOpenError=无法打开文件 "%1"。无法卸载
UninstallUnsupportedVer=卸载日志文件 "%1" 不被此版本的卸载程序识别。无法卸载
UninstallUnknownEntry=在卸载日志文件中遇到未知条目 (%1)
ConfirmUninstall=您确定要删除 %1 及其所有组件吗？
UninstallOnlyOnWin64=此程序只能在 64 位 Windows 上卸载。
OnlyAdminCanUninstall=此程序只能由具有管理员权限的用户卸载。
UninstallStatusLabel=请等待，直到从您的计算机中删除 %1。
UninstalledAll=%1 已从您的计算机中完全删除。
UninstalledMost=%1 卸载完成。%n%n某些项目无法删除。您可以手动删除它们。
UninstalledAndNeedsRestart=要完成 %1 的卸载，需要重新启动您的计算机。%n%n是否立即重新启动？
UninstallDataCorrupted=文件 "%1" 已损坏。无法卸载

; *** Uninstallation phase messages
ConfirmDeleteSharedFileTitle=删除共享文件？
ConfirmDeleteSharedFile2=系统指示以下共享文件不再被任何其他应用程序使用。确认删除该文件？%n%n如果有任何程序仍在使用此文件并且被删除，它们将无法正常工作。如果您不确定，请选择“否”。保留该文件不会损害您的系统。
SharedFileNameLabel=文件名：
SharedFileLocationLabel=位置：
WizardUninstalling=正在卸载
StatusUninstalling=正在卸载 %1...

; *** Shutdown block reasons
ShutdownBlockReasonInstallingApp=正在安装 %1。
ShutdownBlockReasonUninstallingApp=正在卸载 %1。

[CustomMessages]

NameAndVersion=%1, 版本 %2
AdditionalIcons=附加图标：
CreateDesktopIcon=创建桌面快捷方式(&D)
CreateQuickLaunchIcon=创建快速启动栏快捷方式(&Q)
ProgramOnTheWeb=%1 网站
UninstallProgram=卸载 %1
LaunchProgram=启动 %1
AssocFileExtension=将 %1 与 %2 文件关联(&A)
AssocingFileExtension=正在将 %1 与 %2 文件关联...
AutoStartProgramGroupDescription=自动启动：
AutoStartProgram=自动启动 %1
AddonHostProgramNotFound=在您指定的文件夹中未找到 %1。%n%n是否仍要继续？