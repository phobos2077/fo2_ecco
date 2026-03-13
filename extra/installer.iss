;;;
;;;    
;;;

[Setup]
#define MyAppName "EcCo Gameplay Overhaul for Fallout 2: RPU"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "phobos2077"

#define RPUVersion "2.4"

#define DocsDir "..\docs\"
#define RootDir "..\root\"

;#define WIDTH_ADJUST    200
;#define HEIGHT_ADJUST   200
;#define MyAppURL "http://www.nuclear-city.com/"

AppName={#MyAppName}
AppID=pbs_fallout2_economy_and_combat
AppVerName={#MyAppPublisher} {#MyAppName}
OutputBaseFilename=pbs_fo2rpu_ecco_mod_v1-0-0
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

AppCopyright=Copyright © 2026, (phobos2077)
InfoBeforeFile={#DocsDir}ecco_readme.md
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

en.CMain=EcCo Gameplay Overhaul mod for RP
en.CMeleeRangeHitPenalty=Hit Chance penalty for long guns in melee range
en.CAICalledShots=Improved AI aimed attack selection algorithm
en.CAICalledShotsMore=More frequent aimed attacks
en.CCriticals=Critical hit table improvements
en.CDropWeapon=Weapons drop to the ground sometimes on death & critical hits
en.CAPCost=Action Point related changes
en.CInvenCostPerAction=Every inventory action costs AP, but opening is free
en.CCarryUnspentAP=Carry up to 2 unspent AP to next round
en.CRemoveBonusRoF=Removal of Bonus Rate of Fire perk
en.CReloadCost=Reloading costs 4 AP instead of 2
en.CThrowingMeleeDmg=Apply Melee Damage stat to Throwing weapons
en.CStimpakRadiation=Stimpaks slightly irradiate on use
en.CStimpakSkillScaling=Stimpaks & Healing Powders heal amount scales with First Aid skill
en.CHealingSkillsMod=Healing skills and passive healing overhaul
en.CCarTravelTweaks=Car Travel changes
en.CStealTweaks=Steal changes
en.CDrugNPCTweaks=Skill rolls for drugging NPC's
en.CMonsterParts=New critter body parts and related quests

en.WFalloutNotFound=Fallout not detected in selected directory (fallout2.exe), mod won't work. Install anyway?
en.WRPNotFound=Restoration Project not detected in selected directory! This mod is only compatible with RPU {#RPUVersion}. Are you sure you want to continue?
en.WRPCustomAnimsNotFound=New wakizashi blade and rifle animations not found in selected Restoration Project installation. Certain weapons will be broken. Install anyway?

en.OpenReadme=Open ReadMe
en.OpenDamageCalculator=Open Damage Calculator

; Russian
ru.InstallFull=Полная установка (рекомендуется)
ru.InstallCustom=Выборочная установка
ru.InstallNull=Ничего не выбирать

ru.CMain=EcCo: переработка геймплея для RP
ru.CMeleeRangeHitPenalty=Штраф к шансу попадания для длинноствольного оружия в ближнем бою
ru.CAICalledShots=Улучшенный алгоритм выбора прицельных атак ИИ
ru.CAICalledShotsMore=Более частые прицельные атаки
ru.CCriticals=Улучшения таблицы критических повреждений
ru.CDropWeapon=Падение оружия на землю в бою иногда при смертях и критических попаданиях
ru.CAPCost=Изменения системы Очков Действия
ru.CInvenCostPerAction=Каждое действие в инвентаре стоит ОД, но его открытие - бесплатно
ru.CCarryUnspentAP=Перенос части непотраченных ОД на следующих ход
ru.CRemoveBonusRoF=Удаление перка "Бонус скорострельности"
ru.CReloadCost=Перезарядка стоит 4 ОД вместо 2-х
ru.CThrowingMeleeDmg=Применять урон ближнего боя к метательному оружию
ru.CStimpakRadiation=Стимпаки слегка облучают при применении
ru.CStimpakSkillScaling=Эффективность стимпаков и лечебных порошков зависит от навыка первой помощи
ru.CHealingSkillsMod=Переработка навыков лечения и пассивного лечения
ru.CCarTravelTweaks=Изменения параметров автомобиля
ru.CStealTweaks=Изменения воровства
ru.CDrugNPCTweaks=Бросок на навыки для применения препаратов на НПС
ru.CMonsterParts=Новые части тел существ и связанные с ними квесты

ru.WFalloutNotFound=По указанному пути не найдена установленная игра (fallout2.exe), мод не будет работать! Все равно установить?
ru.WRPNotFound=Restoration Project не обнаружен в указанной папке! Данный мод совместим только с RPU {#RPUVersion}. Все равно продолжить?
ru.WRPCustomAnimsNotFound=В указанной папке с Restoration Project не найдены необходимые моды wakizashi blade animations и new rifle animations. Всё равно установить?

ru.OpenReadme=Открыть Readme
ru.OpenDamageCalculator=Открыть Калькулятор Урона


[Types]
Name: "full"; Description: "{cm:InstallFull}"
Name: "custom"; Description: "{cm:InstallCustom}"; Flags: iscustom
;Name: "null"; Description: "{cm:InstallNull}"

[Components]
Name: "main"; Description: "{cm:CMain}"; Types: full custom; Flags: fixed
Name: "tohit_melee_range"; Description: "{cm:CMeleeRangeHitPenalty}"; Types: full
Name: "ai_called_shots"; Description: "{cm:CAICalledShots}"; Types: full
Name: "ai_called_shots\more"; Description: "{cm:CAICalledShotsMore}"; Types: full
Name: "apcost"; Description: "{cm:CAPCost}"; Types: full
Name: "apcost\carry_unspent_ap"; Description: "{cm:CCarryUnspentAP}"; Types: full
Name: "apcost\inven_cost_per_action"; Description: "{cm:CInvenCostPerAction}"; Types: full
Name: "apcost\reload_cost"; Description: "{cm:CReloadCost}"; Types: full
Name: "apcost\remove_bonus_rof"; Description: "{cm:CRemoveBonusRoF}"; Types: full
Name: "criticals"; Description: "{cm:CCriticals}"; Types: full
Name: "drop_weapons"; Description: "{cm:CDropWeapon}"; Types: full
Name: "throwing_melee_dmg"; Description: "{cm:CThrowingMeleeDmg}"; Types: full
Name: "healing_skills_mod"; Description: "{cm:CHealingSkillsMod}"; Types: full
Name: "stimpak_skill_scaling"; Description: "{cm:CStimpakSkillScaling}"; Types: full
Name: "stimpak_radiation"; Description: "{cm:CStimpakRadiation}"; Types: full
Name: "car_travel_tweaks"; Description: "{cm:CCarTravelTweaks}"; Types: full
Name: "steal_tweaks"; Description: "{cm:CStealTweaks}"; Types: full
Name: "drug_npc_tweaks"; Description: "{cm:CDrugNPCTweaks}"; Types: full
Name: "monster_parts"; Description: "{cm:CMonsterParts}"; Types: full

[InstallDelete]
Type: files; Name: "{app}\data\worldmap.dat"
; cleanup previous EcCo installations:
Type: filesandordirs; Name: "{app}\mods\rpu_y_ecco_pcx.dat"
Type: filesandordirs; Name: "{app}\mods\rpu_y_ecco_patch.dat"
Type: filesandordirs; Name: "{app}\mods\rpu_map_update.dat"
Type: filesandordirs; Name: "{app}\mods\ecco"

[Files]
; 
#define FLAGS "Flags: recursesubdirs createallsubdirs overwritereadonly"
; No need for sfall update for now
; Source: "{#RootDir}ddraw.dll"; DestDir: "{app}\";
Source: "{#RootDir}mods\*"; DestDir: "{app}\mods\"; {#FLAGS}
Source: "{#RootDir}ecco_config\*"; DestDir: "{app}\ecco_config\"; {#FLAGS}
Source: "{#RootDir}sfall\*"; DestDir: "{app}\sfall\"; {#FLAGS}
Source: "{#DocsDir}ecco_readme.md"; DestDir: "{app}\"
Source: "{#DocsDir}ecco_changelog.txt"; DestDir: "{app}\"
;Source: "{#DocsDir}ecco_changelog_ru.txt"; DestDir: "{app}\"


#undef FLAGS

[INI]
; version string
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "VersionString"; String: "FALLOUT II 1.02d  RPU {#RPUVersion} + EcCo v{#MyAppVersion}"; Components: main
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
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer1"; String: "90"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer2"; String: "210"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer3"; String: "330"; Components: main
Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "MovieTimer_artimer4"; String: "450"; Components: main

; Disable wipe_inventory
Filename: "{app}\mods\upu.ini"; Section: "main"; Key: "wipe_inventory"; String: "0"; Components: main

;Filename: "{app}\ddraw.ini"; Section: "Misc"; Key: "CheckWeaponAmmoCost"; String: "1"; Components: combat

Filename: "{app}\ecco_config\combat.ini"; Section: "TOHIT"; Key: "melee_range_mod"; String: "0"; Components: not tohit_melee_range
Filename: "{app}\ecco_config\combat.ini"; Section: "TOHIT"; Key: "melee_range_mod_npc"; String: "0"; Components: not tohit_melee_range
Filename: "{app}\ecco_config\combat.ini"; Section: "AI"; Key: "called_tweaks"; String: "0"; Components: not ai_called_shots
Filename: "{app}\ecco_config\combat.ini"; Section: "AI"; Key: "called_freq_mult"; String: "1.0"; Components: not ai_called_shots\more
Filename: "{app}\ecco_config\combat.ini"; Section: "CRITICALS"; Key: "enable_tweaks"; String: "0"; Components: not criticals
Filename: "{app}\ecco_config\combat.ini"; Section: "CRITICALS"; Key: "drop_flag_fix"; String: "0"; Components: not drop_weapons
Filename: "{app}\ecco_config\combat.ini"; Section: "APCOST"; Key: "carry_unspent_ap"; String: "0"; Components: not apcost\carry_unspent_ap
Filename: "{app}\ecco_config\combat.ini"; Section: "APCOST"; Key: "inventory_cost_per_action"; String: "0"; Components: not apcost\inven_cost_per_action
Filename: "{app}\ecco_config\combat.ini"; Section: "APCOST"; Key: "reload_cost"; String: "-1"; Components: not apcost\reload_cost
Filename: "{app}\ecco_config\combat.ini"; Section: "THROWING"; Key: "apply_melee_dmg_mult"; String: "0"; Components: not throwing_melee_dmg
Filename: "{app}\ecco_config\loot.ini"; Section: "CRITTER_LOOT"; Key: "weapon_drop_chance"; String: "0"; Components: not drop_weapons
Filename: "{app}\ecco_config\loot.ini"; Section: "MONSTER_PARTS"; Key: "enable"; String: "0"; Components: not monster_parts
Filename: "{app}\ecco_config\misc.ini"; Section: "ITEM_TWEAKS"; Key: "stimpak_radiation_disable"; String: "1"; Components: not stimpak_radiation
Filename: "{app}\ecco_config\misc.ini"; Section: "HEALING_DRUGS"; Key: "skill_max"; String: "0"; Components: not stimpak_skill_scaling
Filename: "{app}\ecco_config\misc.ini"; Section: "HEALING_SKILLS"; Key: "skill_use_mod"; String: "0"; Components: not healing_skills_mod
Filename: "{app}\ecco_config\misc.ini"; Section: "HEALING_REST"; Key: "heal_time_rest"; String: "180"; Components: not healing_skills_mod
Filename: "{app}\ecco_config\misc.ini"; Section: "HEALING_REST"; Key: "heal_time_travel"; String: "0"; Components: not healing_skills_mod
Filename: "{app}\ecco_config\misc.ini"; Section: "USEOBJON_SNEAK"; Key: "enable_tweaks"; String: "0"; Components: not drug_npc_tweaks
Filename: "{app}\ecco_config\misc.ini"; Section: "CAR_TRAVEL"; Key: "enable_tweaks"; String: "0"; Components: not car_travel_tweaks
Filename: "{app}\ecco_config\misc.ini"; Section: "STEAL"; Key: "enable_tweaks"; String: "0"; Components: not steal_tweaks

Filename: "{app}\sfall\perks.ini"; Section: "5"; Key: "Level"; String: "15"; Components: not apcost\remove_bonus_rof

                                                                              
[Run]
FileName: "{app}\ecco_readme.md"; Description: "{cm:OpenReadme}"; WorkingDir: "{app}"; Flags: postinstall shellexec
FileName: "http://phobos2077.github.io/fo2_ecco/ttx/damage_calc.html"; Description: "{cm:OpenDamageCalculator}"; Flags: postinstall shellexec unchecked runasoriginaluser
  

; Code for additional effects
#include "installer_code.iss"
