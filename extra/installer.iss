;;;
;;;    
;;;

[Setup]
#define MyAppName "Fallout 2: EcCo Gameplay Overhaul"
#define MyAppVersion "0.9.6"
#define MyAppPublisher "phobos2077"

#define DocsDir "..\docs\"
#define RootDir "..\root\"

;#define WIDTH_ADJUST    200
;#define HEIGHT_ADJUST   200
;#define MyAppURL "http://www.nuclear-city.com/"

AppName={#MyAppName}
AppID=pbs_fallout2_economy_and_combat
AppVerName={#MyAppPublisher} {#MyAppName}
OutputBaseFilename=pbs_fo2rpu_ecco_mod_v0-9-WIP
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

AppCopyright=Copyright © 2024, (phobos2077)
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
en.InstallFull=Full install (recommended)
en.InstallCustom=Custom install
en.InstallNull=Uncheck all

en.CMain=EcCo Gameplay Overhaul mod
;en.CCombatFreeMove=Bonus move points for high AG characters
en.CCarryUnspentAP=Carry up to 2 unspent AP to next round
en.CRemoveBonusRoF=Removal of Bonus Rate of Fire perk
en.CThrowingMeleeDmg=Apply Melee Damage stat to Throwing weapons
en.CStimpakRadiation=Stimpaks slightly irradiate on use
en.CStimpakSkillScaling=Stimpaks & Healing Powders heal amount scales with First Aid skill
en.CCarTravelTweaks=Car Travel changes (25% slower)
en.CStealTweaks=Steal changes
en.CMonsterParts=New critter body parts and related quests

en.WFalloutNotFound=Fallout not detected in selected directory (fallout2.exe), mod won't work. Install anyway?
en.WRPNotFound=Restoration Project not detected in selected directory! This mod is only compatible with RPU 2.6 or above. Are you sure you want to continue?
en.WRPMapUpdateNotFound=RPU: Maps Updated not detected in selected directory! This mod will not work without that. Are you sure you want to continue?

en.OpenReadme=Open ReadMe
en.OpenDamageCalculator=Open Damage Calculator

; Russian
ru.InstallFull=Полная установка (рекомендуется)
ru.InstallCustom=Выборочная установка
ru.InstallNull=Ничего не выбирать

ru.CMain=EcCo - переработка геймплея
;ru.CCombatFreeMove=Бонусные ОД всем персонажам с высокой Ловкостью
ru.CCarryUnspentAP=Перенос части непотраченных ОД на следующих ход
ru.CRemoveBonusRoF=Удаление перка "Бонус скорострельности"
ru.CThrowingMeleeDmg=Применять урон ближнего боя к метательному оружию
ru.CStimpakRadiation=Стимпаки слегка облучают при применении
ru.CStimpakSkillScaling=Эффективность стимпаков и лечебных порошков зависит от навыка первой помощи
ru.CCarTravelTweaks=Изменения параметров автомобиля (25% медленнее)
ru.CStealTweaks=Изменения воровства
ru.CMonsterParts=Новые части тел существ и связанные с ними квесты

ru.WFalloutNotFound=По указанному пути не найдена установленная игра (fallout2.exe), мод не будет работать! Все равно установить?
ru.WRPNotFound=Restoration Project не обнаружен в указанной папке! Данный мод совместим только с RPU 2.6. Все равно продолжить?
ru.WRPMapUpdateNotFound=RPU: Maps Updated не обнаружен в указанной папке! Данный мод без него работать не будет. Всё равно продолжить?

ru.OpenReadme=Открыть Readme
ru.OpenDamageCalculator=Открыть Калькулятор Урона


[Types]
Name: "full"; Description: "{cm:InstallFull}"
Name: "custom"; Description: "{cm:InstallCustom}"; Flags: iscustom
;Name: "null"; Description: "{cm:InstallNull}"

[Components]
Name: "main"; Description: "{cm:CMain}"; Types: full custom; Flags: fixed
;Name: "option"; Description: "{cm:COptions}"; Types: full
Name: "carry_unspent_ap"; Description: "{cm:CCarryUnspentAP}"; Types: full
Name: "remove_bonus_rof"; Description: "{cm:CRemoveBonusRoF}"; Types: full
Name: "throwing_melee_dmg"; Description: "{cm:CThrowingMeleeDmg}"; Types: full
Name: "stimpak_skill_scaling"; Description: "{cm:CStimpakSkillScaling}"; Types: full
Name: "stimpak_radiation"; Description: "{cm:CStimpakRadiation}"; Types: full
Name: "car_travel_tweaks"; Description: "{cm:CCarTravelTweaks}"; Types: full
Name: "steal_tweaks"; Description: "{cm:CStealTweaks}"; Types: full
Name: "monster_parts"; Description: "{cm:CMonsterParts}"; Types: full

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
;Source: "{#RootDir}ddraw.dll"; DestDir: "{app}\";
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
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "ObjCanSeeObj_ShootThru_Fix"; String: "1"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "DerivedStats"; String: "sfall\stats.ini"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "SkillsFile"; String: "sfall\skills.ini"; Components: main    
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "PerksFile"; String: "sfall\perks.ini"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "BooksFile"; String: "sfall\books.ini"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "DrugsFile"; String: "sfall\drugs.ini"; Components: main
; dreams
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer1"; String: "120"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer2"; String: "235"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer3"; String: "350"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer4"; String: "470"; Components: main

;Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "CheckWeaponAmmoCost"; String: "1"; Components: combat

Filename: "{app}\mods\ecco\combat.ini"; Section: "APCOST"; Key: "carry_unspent_ap"; String: "0"; Components: not carry_unspent_ap
Filename: "{app}\mods\ecco\combat.ini"; Section: "THROWING"; Key: "apply_melee_dmg"; String: "0"; Components: not throwing_melee_dmg
Filename: "{app}\mods\ecco\combat.ini"; Section: "MONSTER_PARTS"; Key: "enable"; String: "0"; Components: not monster_parts
Filename: "{app}\mods\ecco\misc.ini"; Section: "ITEM_TWEAKS"; Key: "stimpak_radiation_disable"; String: "1"; Components: not stimpak_radiation
Filename: "{app}\mods\ecco\misc.ini"; Section: "FIRST_AID"; Key: "ini_healing_skill_max"; String: "0"; Components: not stimpak_skill_scaling
Filename: "{app}\mods\ecco\misc.ini"; Section: "CAR_TRAVEL"; Key: "enable_tweaks"; String: "0"; Components: not car_travel_tweaks
Filename: "{app}\mods\ecco\misc.ini"; Section: "STEAL"; Key: "enable_tweaks"; String: "0"; Components: not steal_tweaks

Filename: "{app}\sfall\perks.ini"; Section: "5"; Key: "Level"; String: "15"; Components: not remove_bonus_rof

                                                                              
[Run]
FileName: "{app}\ecco_readme.txt"; Description: "{cm:OpenReadme}"; WorkingDir: "{app}"; Flags: postinstall shellexec
FileName: "http://phobos2077.github.io/fo2_ecco/ttx/damage_calc.html"; Description: "{cm:OpenDamageCalculator}"; Flags: postinstall shellexec unchecked runasoriginaluser
  

; Code for additional effects
#include "installer_code.iss"
