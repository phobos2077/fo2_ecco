;;;
;;;    
;;;

[Setup]
#define MyAppName "Fallout 2: EcCo Gameplay Overhaul"
#define MyAppVersion "0.9.2"
#define MyAppPublisher "phobos2077"

#define DocsDir "..\docs\"
#define RootDir "..\root\"

;#define WIDTH_ADJUST    200
;#define HEIGHT_ADJUST   200
;#define MyAppURL "http://www.nuclear-city.com/"

AppName={#MyAppName}
AppID=pbs_fallout2_economy_and_combat
AppVerName={#MyAppPublisher} {#MyAppName}
OutputBaseFilename=pbs_fo2rpu_ecco_mod_v0-9-2
DefaultDirName={sd}\Games\Fallout2\
AppendDefaultDirName=no
;UsePreviousAppDir=no
DirExistsWarning=no
UninstallFilesDir={app}
Uninstallable = no
CreateUninstallRegKey=no
AlwaysShowComponentsList=yes
;DisableDirPage=no
DisableProgramGroupPage=yes
DisableStartupPrompt=yes
DisableReadyPage=no
DisableWelcomePage=no
VersionInfoCompany={#MyAppPublisher}
VersionInfoDescription=
VersionInfoVersion={#MyAppVersion}
;SolidCompression=yes
;Compression=lzma
OutputDir=.

AppCopyright=Copyright © 2023, (phobos2077)
InfoBeforeFile={#DocsDir}ecco_readme.txt
SetupIconFile=fallout.ico
WizardSmallImageFile=phobos.bmp
WizardImageFile=wizard.bmp
WizardImageStretch=no
WizardStyle=modern
BackColor=clBlack
BackColor2=clRed

;ExtraDiskSpaceRequired=20971520
;PrivilegesRequired=admin
SetupLogging=yes

[Languages]
Name: "en"; MessagesFile: "compiler:default.isl"
Name: "ru"; MessagesFile: "compiler:Languages\Russian.isl"
; InfoBeforeFile: "{#DocsDir}ecco_readme_ru.txt"

[CustomMessages]
; English
en.InstallFull=Full install
en.InstallCustom=Custom install
en.InstallNull=Uncheck all

en.CMain=EcCo mod
en.CEconomy=Economy Rebalance
en.CCombat=Combat Rebalance: weapons, ammo and items

en.WFalloutNotFound=Fallout not detected in selected directory (fallout2.exe), mod won't work. Install anyway?
en.WRPNotFound=Restoration Project not detected in selected directory! This mod is only compatible with RPU 2.6 or above. Are you sure you want to continue?
en.WRPMapUpdateNotFound=RPU: Maps Updated not detected in selected directory! This mod will not work without that. Are you sure you want to continue?

; Russian
ru.InstallFull=Полная установка
ru.InstallCustom=Выборочная установка
ru.InstallNull=Ничего не выбирать

ru.CEconomy=Экономический ребаланс
ru.CCombat=Боевой Ребаланс: Оружие, боеприпасы и предметы

ru.WFalloutNotFound=По указанному пути не найдена установленная игра (fallout2.exe), мод не будет работать! Все равно установить?
ru.WRPNotFound=Restoration Project не обнаружен в указанной папке! Данный мод совместим только с RPU 2.6. Все равно продолжить?
ru.WRPMapUpdateNotFound=RPU: Maps Updated не обнаружен в указанной папке! Данный мод без него работать не будет. Всё равно продолжить?


[Types]
Name: "full"; Description: "{cm:InstallFull}"
;Name: "custom"; Description: "{cm:InstallCustom}"; Flags: iscustom
;Name: "null"; Description: "{cm:InstallNull}"

[Components]
Name: "main"; Description: "EcCo mod"; Types: full; Flags: fixed

[InstallDelete]
Type: files; Name: "{app}\data\worldmap.dat"
; cleanup previous EcCo installations:
Type: filesandordirs; Name: "{app}\mods\rpu_y_ecco_pcx.dat"
Type: filesandordirs; Name: "{app}\mods\rpu_y_ecco_patch.dat"
Type: filesandordirs; Name: "{app}\mods\ecco"

[Files]
; 
#define FLAGS "Flags: recursesubdirs createallsubdirs overwritereadonly"
; 
Source: "{#RootDir}ddraw.dll"; DestDir: "{app}\";
Source: "{#RootDir}mods\*"; DestDir: "{app}\mods\"; {#FLAGS}
Source: "{#RootDir}sfall\*"; DestDir: "{app}\sfall\"; {#FLAGS}
Source: "{#DocsDir}ecco_readme.txt"; DestDir: "{app}\"
Source: "{#DocsDir}ecco_changelog.txt"; DestDir: "{app}\"
Source: "{#DocsDir}ecco_changelog_ru.txt"; DestDir: "{app}\"

;Source: "__batch\@pbs_rebalance_finalize.cmd"; DestDir: "{app}\"

#undef FLAGS

[INI]
; requirement
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "DamageFormula"; String: "0"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "ObjCanHearObjFix"; String: "1"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "DerivedStats"; String: "sfall\stats.ini"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "SkillsFile"; String: "sfall\skills.ini"; Components: main    
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "PerksFile"; String: "sfall\perks.ini"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "BooksFile"; String: "sfall\books.ini"; Components: main
; dreams
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer1"; String: "120"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer2"; String: "235"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer3"; String: "350"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer4"; String: "470"; Components: main

;Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "CheckWeaponAmmoCost"; String: "1"; Components: combat

;Filename: "{app}\combat.ini"; Section: "APCOST"; Key: "drugs_free_uses"; String: "2"; Components: combat\inven_ap_drugs

                                                                              
;[Run]
;FileName: "{app}\@pbs_rebalance_finalize.cmd"; WorkingDir: "{app}"; Flags: shellexec waituntilterminated

; Optional:
;FileName: "{app}\weapon_chart.xls"; Description: "Открыть таблицу характеристик оружия"; WorkingDir: "{app}"; Flags: postinstall shellexec unchecked
;FileName: "{app}\@pbs_rebalance_readme.rtf"; Description: "Открыть ReadMe"; WorkingDir: "{app}"; Flags: postinstall shellexec
  

; Code for additional effects
#include "installer_code.iss"


