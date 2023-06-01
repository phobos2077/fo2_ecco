# Skill names for messages
{1}{}{Легкое оружие}
{2}{}{Тяжелое оружие}
{3}{}{Энерго оружие}
{4}{}{Без оружия}
{5}{}{Холод. оружие}
{6}{}{Метание}
{7}{}{Первая помощь}
{8}{}{Доктор}
{9}{}{Скрытность}
{10}{}{Взлом}
{11}{}{Кража}
{12}{}{Ловушки}
{13}{}{Наука}
{14}{}{Ремонт}
{15}{}{Красноречие}
{16}{}{Бартер}
{17}{}{Азартные игры}
{18}{}{Натуралист}
# Skill names for defines
{19}{}{SMALL_GUNS}
{20}{}{BIG_GUNS}
{21}{}{ENERGY_WEAPONS}
{22}{}{UNARMED}
{23}{}{MELEE_WEAPONS}
{24}{}{THROWING}
{25}{}{FIRST_AID}
{26}{}{DOCTOR}
{27}{}{SNEAK}
{28}{}{LOCKPICK}
{29}{}{STEAL}
{30}{}{TRAPS}
{31}{}{SCIENCE}
{32}{}{REPAIR}
{33}{}{SPEECH}
{34}{}{BARTER}
{35}{}{GAMBLING}
{36}{}{OUTDOORSMAN}

# section categories (up to 12 can be defined and used)
{41}{}{Еда}
{42}{}{Первая Помощь}
{43}{}{Препараты}
{44}{}{Взрывчатка}
{45}{}{Боеприпасы}
{46}{}{Ловушки}
{47}{}{Броня}
{48}{}{Электроника}
{49}{}{Ножи}
{50}{}{Оружие}
{51}{}{Разное}

# messages
{81}{}{Вы изучили способ изготовить взрывчатку.}
{82}{}{Вы изучили схемы кожаной брони.}
{83}{}{Вы узнали способы приготовления психотропных зелий первой необходимости.}
{84}{}{Вы узнали рецепты сильнодействующих химических препаратов.}
{85}{}{Вы изучили схемы некоторых электронных устройств.}
{86}{}{Теперь Вы знаете, каким путем создать новый вид боеприпасов.}
{87}{}{Теперь Вы понимаете, как заточить лезвия при помощи кремня.}
{88}{}{Вы получили несколько рецептов еды.}
{89}{}{Возможно, вы можете собрать Рем. Набор самостоятельно.}

{90}{}{Это рабочее место подходит для обработки.}

{100}{}{[ГОТОВО]}
{101}{}{[Выйти]}
{102}{}{[Назад]}
{103}{}{Собрать}
{104}{}{Разобрать}
{105}{}{[Дальше]}
{106}{}{[Назад]}
{107}{}{[Нет схем]}
{108}{}{Собрать все}
{109}{}{Разобрать все}
{110}{}{ (}
{111}{}{ предмет(ы))}
{112}{}{[Категории]}
{120}{}{ГОТОВО}
{121}{}{Fix-Boy недоступен во время боя!}

{150}{}{ или }

{200}{}{Выберите предметы.}
{201}{}{Предмет(ы) собран(ы).}
{202}{}{Предмет(ы) разобран(ы).}
{210}{}{Выберите категорию.}

{300}{}{Инструменты}
{301}{}{Навыки}
{302}{}{Компоненты}
{303}{}{Нет}
{304}{}{Время}
{305}{}{Часов: }
{306}{}{Минут: }

{400}{}{Собрано: }
{401}{}{Разобрано: }
{402}{}{ (}
{403}{}{ предмет(ов)). }
{404}{}{ ч. }
{405}{}{ м. прошло.}

# party members list (those with hands and brains)
{450}{}{16777278}
{451}{}{16777376}
{452}{}{16777377}
{453}{}{16777305}
{454}{}{16777313}
{455}{}{16777323}
{456}{}{16777379}
{457}{}{16777380}
{458}{}{16777295}
{459}{}{16777597}
{460}{}{16777368}
{461}{}{16777718}
{462}{}{16777719}
{463}{}{16777720}

# MOD CONFIGURATION
{491}{}{1}  # allow party members to help with crafting (1 enable, 0 disable)
{492}{}{2}  # split items into categories (0 disable, 1 enable, 2 automatically enable when enough items available)
{493}{}{1}  # use sfall gloval vars to check if item is available
{494}{}{29+33}  # Crafting shortcut: Ctrl+F

# CRAFTING SCHEMATICS:

# FOOD

{1000}{}{[ITEM]}
{1001}{}{627:2}                            # Fish Soup
{1002}{}{pcx/items/stew1.pcx}
{1003}{}{69060}
{1004}{}{CRFT_FOD}                                 # 
{1005}{}{18000}                            # 0 h 30 m
{1006}{}{NO}
{1007}{}{1}                                # food
{1008}{}{[TOOLS]}
{1009}{}{4|236}                            # PID_KNIFE|PID_COMBAT_KNIFE
{1010}{}{[SKILLS]}
{1011}{}{FIRST_AID+OUTDOORSMAN:60}
{1012}{}{[COMPONENTS]}
{1013}{}{535:1|536:1}                      # Fish or Scaly Fish
{1014}{}{71:1}                             # Fruit


{1100}{}{[ITEM]}
{1101}{}{628:2}                            # Meat Stew
{1102}{}{pcx/items/stew2.pcx}
{1103}{}{69060}
{1104}{}{CRFT_FOD}                                 # 
{1105}{}{18000}                            # 0 h 30 m
{1106}{}{NO}
{1107}{}{1}                                # food
{1108}{}{[TOOLS]}
{1109}{}{4|236}                            # PID_KNIFE|PID_COMBAT_KNIFE
{1110}{}{[SKILLS]}
{1111}{}{FIRST_AID+OUTDOORSMAN:60}
{1112}{}{[COMPONENTS]}
{1113}{}{284:2|103:2|81:2}                 # 2x Meat Jerky or 2x Meat-on-a-stick or 2x Iguana-on-a-stick
{1114}{}{71:1}                             # Fruit


# FIRST AID ITEMS

{1200}{}{[ITEM]}
{1201}{}{273}                               # PID_HEALING_POWDER
{1202}{}{pcx/items/healpwdr.pcx}
{1203}{}{47063}
{1204}{}{8}                                 # GVAR_KNOWLEDGE_HEALING_POWDER
{1205}{}{18000}                             # 30 m
{1206}{}{NO}
{1207}{}{3}                                 # Drugs
{1208}{}{[TOOLS]}
{1209}{}{[SKILLS]}
{1210}{}{FIRST_AID+OUTDOORSMAN:50}
{1211}{}{[COMPONENTS]}
{1212}{}{271:1}                             # PID_BROC_FLOWER
{1213}{}{272:1}                             # PID_XANDER_ROOT


{1300}{}{[ITEM]}
{1301}{}{49}                                # PID_ANTIDOTE
{1302}{}{pcx/items/drug_bot.pcx}
{1303}{}{90060}
{1304}{}{CRFT_AID}                          # first aid schematics
{1305}{}{30000}                             # 50 m
{1306}{}{NO}
{1307}{}{3}                                 # Drugs
{1308}{}{[TOOLS]}
{1309}{}{[SKILLS]}
{1310}{}{FIRST_AID+OUTDOORSMAN:70}
{1311}{}{SCIENCE:30}
{1312}{}{[COMPONENTS]}
{1313}{}{92:1|591:2}                        # PID_SCORPION_TAIL or two Small Scorpion Tails
{1314}{}{125:1}                             # PID_BOOZE


{1400}{}{[ITEM]}
{1401}{}{40}                                # PID_STIMPAK
{1402}{}{pcx/items/stimx.pcx}
{1403}{}{89060}
{1404}{}{CRFT_AID}                          # first aid schematics
{1405}{}{51000}                             # 1 h 25 m
{1406}{}{NO}
{1407}{}{3}                                 # Drugs
{1408}{}{[TOOLS]}
{1409}{}{91}                                # PID_DOCTORS_BAG
{1410}{}{[SKILLS]}
{1411}{}{DOCTOR:60}
{1412}{}{SCIENCE:70}
{1413}{}{[COMPONENTS]}
{1414}{}{271:1}                             # PID_BROC_FLOWER
{1415}{}{272:1}                             # PID_XANDER_ROOT
{1416}{}{318:1}                             # PID_HYPODERMIC_NEEDLE


{1500}{}{[ITEM]}
{1501}{}{144}                               # PID_SUPER_STIMPAK
{1502}{}{pcx/items/stimpak.pcx}
{1503}{}{88059}
{1504}{}{CRFT_AID}                          # first aid schematics
{1505}{}{93000}                             # 2 h 35 m
{1506}{}{NO}
{1507}{}{3}                                 # Drugs
{1508}{}{[TOOLS]}
{1509}{}{91}                                # PID_DOCTORS_BAG
{1510}{}{[SKILLS]}
{1511}{}{DOCTOR:80}
{1512}{}{SCIENCE:100}
{1513}{}{[COMPONENTS]}
{1514}{}{71:1}                              # PID_MUTATED_FRUIT
{1515}{}{106:1}                             # PID_NUKA_COLA
{1516}{}{40:2}                              # PID_STIMPAK


# ADVANCED DRUGS

{1600}{}{[ITEM]}
{1601}{}{110}                               # PID_PSYCHO
{1602}{}{pcx/items/lastdrug.pcx}
{1603}{}{77060}
{1604}{}{CRFT_DRG}                          # drugs schematics
{1605}{}{360000}                            # 10 h
{1606}{}{NO}
{1607}{}{3}                                 # adv drug
{1608}{}{[TOOLS]}
{1609}{}{91}                                # PID_DOCTORS_BAG
{1610}{}{[SKILLS]}
{1611}{}{DOCTOR:80}
{1612}{}{SCIENCE:100}
{1613}{}{[COMPONENTS]}
{1614}{}{87:1}                              # PID_BUFFOUT
{1615}{}{71:2}                              # PID_MUTATED_FRUIT
{1616}{}{125:1}                             # PID_BOOZE
{1617}{}{144:1}                             # PID_SUPER_STIMPAK


{1700}{}{[ITEM]}
{1701}{}{334}                               # PID_POISON
{1702}{}{pcx/items/poison.pcx}
{1703}{}{90065}
{1704}{}{CRFT_DRG}                          # drugs schematics
{1705}{}{81000}                             # 2 h 15 m
{1706}{}{NO}
{1707}{}{3}                                 # adv drug
{1708}{}{[TOOLS]}
{1709}{}{91}                                # PID_DOCTORS_BAG
{1710}{}{[SKILLS]}
{1711}{}{DOCTOR:30}
{1712}{}{SCIENCE:50}
{1713}{}{[COMPONENTS]}
{1714}{}{318:1}                             # PID_HYPODERMIC_NEEDLE
{1715}{}{106:1}                             # PID_NUKA_COLA
{1716}{}{92:1|591:1}                        # PID_SCORPION_TAIL or Small Scorpion Tail


{1800}{}{[ITEM]}
{1801}{}{612}                               # new fire resistance grug
{1802}{}{pcx/items/drugskin.pcx}
{1803}{}{90070}
{1804}{}{CRFT_DRG}                          # drugs schematics
{1805}{}{126000}                            # 3 h 30 m
{1806}{}{NO}
{1807}{}{3}                                 # adv drug
{1808}{}{[TOOLS]}
{1809}{}{91}                                # PID_DOCTORS_BAG
{1810}{}{[SKILLS]}
{1811}{}{DOCTOR:70}
{1812}{}{SCIENCE:80}
{1813}{}{[COMPONENTS]}
{1814}{}{144:1}                             # PID_SUPER_STIMPAK
{1815}{}{334:1}                             # PID_POISON


{1900}{}{[ITEM]}                            # 
{1901}{}{620}                               # new carry weight drug
{1902}{}{pcx/items/drugcrry.pcx}
{1903}{}{47074}
{1904}{}{CRFT_DRG}
{1905}{}{30000}                             # 
{1906}{}{NO}
{1907}{}{3}                                 # adv drug
{1908}{}{[TOOLS]}
{1909}{}{91}                                # PID_DOCTORS_BAG
{1910}{}{[SKILLS]}
{1911}{}{DOCTOR:70}
{1912}{}{SCIENCE:60}
{1913}{}{[COMPONENTS]}
{1914}{}{49:1}                              # PID_ANTIDOTE
{1915}{}{71:2}                              # PID_MUTATED_FRUIT
{1916}{}{106:1}                             # PID_NUKA_COLA


# EXPLOSIVES

{2000}{}{[ITEM]}
{2001}{}{159}                               # PID_MOLOTOV_COCKTAIL
{2002}{}{pcx/items/mola.pcx}
{2003}{}{23060}
{2004}{}{CRFT_EXP}                          # explosives schematics
{2005}{}{18000}                             # 0 h 30 m
{2006}{}{NO}
{2007}{}{4}                                 # Explosive
{2008}{}{[TOOLS]}
{2009}{}{75|308}                            # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{2010}{}{[SKILLS]}
{2011}{}{THROWING:40}
{2012}{}{[COMPONENTS]}
{2013}{}{79:1}                              # PID_FLARE
{2014}{}{125:1}                             # PID_BOOZE


{2100}{}{[ITEM]}
{2101}{}{613:4}                             # grenades
{2102}{}{pcx/items/homegren.pcx}
{2103}{}{60050}
{2104}{}{CRFT_EXP}                          # explosives schematics
{2105}{}{108000}                            # 3 h 00 m
{2106}{}{NO}
{2107}{}{4}                                 # Explosive
{2108}{}{[TOOLS]}
{2109}{}{75|308}                            # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{2110}{}{[SKILLS]}
{2111}{}{TRAPS+THROWING:100}
{2112}{}{REPAIR:60}
{2113}{}{[COMPONENTS]}
{2114}{}{98:1}                              # Junk
{2115}{}{51:1|85:1}                         # Dynamite OR Plastic explosive
{2116}{}{95:2}                              # Shotgun shells


{2200}{}{[ITEM]}
{2201}{}{85}                                # PID_PLASTIC_EXPLOSIVES
{2202}{}{pcx/items/plastic.pcx}
{2203}{}{93063}
{2204}{}{CRFT_EXP}                          # explosives schematics
{2205}{}{72000}                             # 2 h 00 m
{2206}{}{NO}
{2207}{}{4}                                 # Explosive
{2208}{}{[TOOLS]}
{2209}{}{75|308}                            # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{2210}{}{[SKILLS]}
{2211}{}{TRAPS+SCIENCE:120}
{2212}{}{REPAIR:60}
{2213}{}{[COMPONENTS]}
{2214}{}{51:1}                              # PID_DYNAMITE
{2215}{}{106:4}                             # PID_NUKA_COLA


# AMMO

{2300}{}{[ITEM]}
{2301}{}{614}                              # new 12ga slug ammo
{2302}{}{pcx/items/ssslugs.pcx}
{2303}{}{74060}
{2304}{}{CRFT_AMM}                         # ammo craft schematics
{2305}{}{54000}                            # 1 h 30 m
{2306}{}{NO}
{2307}{}{5}                                # Ammo
{2308}{}{[TOOLS]}
{2309}{}{75|308}                           # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{2310}{}{[SKILLS]}
{2311}{}{SMALL_GUNS:50}
{2312}{}{REPAIR:40}
{2313}{}{[COMPONENTS]}
{2314}{}{95:1}                             # Shotgun shells
{2315}{}{19:1}                             # PID_ROCK


{2400}{}{[ITEM]}
{2401}{}{641:2}                            # new 12ga incendiary
{2402}{}{pcx/items/ssbcksht.pcx}
{2403}{}{79060}
{2404}{}{CRFT_AMM}                         # ammo craft schematics
{2405}{}{54000}                            # 1 h 30 m
{2406}{}{NO}
{2407}{}{5}                                # Ammo
{2408}{}{[TOOLS]}
{2409}{}{75|308}                           # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{2410}{}{[SKILLS]}
{2411}{}{SMALL_GUNS:50}
{2412}{}{REPAIR:60}
{2413}{}{[COMPONENTS]}
{2414}{}{95:2}                             # Shotgun shells
{2415}{}{32:1|382:1}                       # Flamethrower fuel


{2500}{}{[ITEM]}
{2501}{}{615}                              # new .223 AP
{2502}{}{pcx/items/223ap.pcx}
{2503}{}{81059}
{2504}{}{CRFT_AMM}                         # ammo craft schematics
{2505}{}{162000}                           # 4 h 30 m
{2506}{}{NO}
{2507}{}{5}                                # Ammo
{2508}{}{[TOOLS]}
{2509}{}{308}                              # PID_SUPER_TOOL_KIT
{2510}{}{[SKILLS]}
{2511}{}{SMALL_GUNS:60}
{2512}{}{REPAIR:70}
{2513}{}{[COMPONENTS]}
{2514}{}{34:1}                             # 223 FMJ
{2515}{}{36:1}                             # 5mm AP


{2600}{}{[ITEM]}
{2601}{}{642}                              # 7.62 AP
{2602}{}{pcx/items/223ap.pcx}
{2603}{}{57054}
{2604}{}{CRFT_AMM}                         # ammo craft schematics
{2605}{}{162000}                           # 4 h 30 m
{2606}{}{NO}
{2607}{}{5}                                # Ammo
{2608}{}{[TOOLS]}
{2609}{}{308}                              # PID_SUPER_TOOL_KIT
{2610}{}{[SKILLS]}
{2611}{}{SMALL_GUNS:60}
{2612}{}{REPAIR:80}
{2613}{}{[COMPONENTS]}
{2614}{}{363:1}                            # 7.62 FMJ
{2615}{}{33:1}                             # 14mm AP


{2700}{}{[ITEM]}
{2701}{}{633}                              # 14mm JHP
{2702}{}{pcx/items/14mmJHP.pcx}
{2703}{}{45068}
{2704}{}{CRFT_AMM}                         # Ammo schematics
{2705}{}{72000}                            # 2h
{2706}{}{NO}
{2707}{}{5}                                # Ammo
{2708}{}{[TOOLS]}
{2709}{}{75|308}                           # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{2710}{}{[SKILLS]}
{2711}{}{SMALL_GUNS:60}
{2712}{}{REPAIR:80}
{2713}{}{[COMPONENTS]}
{2714}{}{33:1}                             # 14mm AP


{2800}{}{[ITEM]}
{2801}{}{632}                              # 40mm IC
{2802}{}{pcx/items/40mm_IC.pcx}
{2803}{}{74060}
{2804}{}{CRFT_AMM}                         # Ammo schematics
{2805}{}{36000}                            # 2h
{2806}{}{NO}
{2807}{}{5}                                # Ammo
{2808}{}{[TOOLS]}
{2809}{}{308}                              # Super tool kit
{2810}{}{[SKILLS]}
{2811}{}{BIG_GUNS:60}
{2812}{}{REPAIR:60}
{2813}{}{[COMPONENTS]}
{2814}{}{631:1}                            # 40mm HE grenades
{2815}{}{159:2}                            # Molotov


# TRAPS

{2900}{}{[ITEM]}
{2901}{}{618:4}                            # Trap kit Melee
{2902}{}{pcx/items/spiketrap.pcx}
{2903}{}{85055}
{2904}{}{}                                 # ALWAYS
{2905}{}{108000}                           # 3 h 00 m
{2906}{}{NO}
{2907}{}{6}                                # Traps
{2908}{}{[TOOLS]}
{2909}{}{4|236}                            # PID_KNIFE|PID_COMBAT_KNIFE
{2910}{}{[SKILLS]}
{2911}{}{REPAIR+TRAPS:50}
{2912}{}{[COMPONENTS]}
{2913}{}{127:1}                            # Rope
{2914}{}{7:2|280:2}                        # Spear OR Sharp Spear


{3000}{}{[ITEM]}
{3001}{}{616:4}                            # Trap kit Mine
{3002}{}{pcx/items/trapkit.pcx}
{3003}{}{68061}
{3004}{}{CRFT_EXP}                         # explosive schematics 644
{3005}{}{108000}                           # 3 h 00 m
{3006}{}{NO}
{3007}{}{6}                                # Traps
{3008}{}{[TOOLS]}
{3009}{}{308}                              # PID_SUPER_TOOL_KIT
{3010}{}{[SKILLS]}
{3011}{}{REPAIR+TRAPS:80}
{3012}{}{[COMPONENTS]}
{3013}{}{127:1}                            # Rope
{3014}{}{98:1}                             # Junk


{3100}{}{[ITEM]}
{3101}{}{619:2}                            # Trap kit Proximity
{3102}{}{pcx/items/sensmine.pcx}
{3103}{}{55054}
{3104}{}{CRFT_ELE}                         # Electronics
{3105}{}{108000}                           # 3 h 00 m
{3106}{}{NO}
{3107}{}{6}                                # Traps
{3108}{}{[TOOLS]}
{3109}{}{308}                              # PID_SUPER_TOOL_KIT
{3110}{}{[SKILLS]}
{3111}{}{REPAIR+TRAPS:110}
{3112}{}{SCIENCE:60}
{3113}{}{[COMPONENTS]}
{3114}{}{38:1}                             # SEC
{3115}{}{98:1}                             # Junk


# LEATHER ARMOR

{3200}{}{[ITEM]}
{3201}{}{74}                                # PID_LEATHER_JACKET
{3202}{}{pcx/items/maxinv.pcx}
{3203}{}{62060}
{3204}{}{CRFT_LTJ}                          # Leather Jacket schematics
{3205}{}{180000}                            # 5 h 00 m
{3206}{}{NO}
{3207}{}{7}                                 # Armor
{3208}{}{[TOOLS]}
{3209}{}{4|236}                             # PID_KNIFE|PID_COMBAT_KNIFE
{3210}{}{[SKILLS]}
{3211}{}{REPAIR:35}
{3212}{}{[COMPONENTS]}
{3213}{}{127:1}                             # PID_ROPE
{3214}{}{276:2|623:2}                       # PID_GECKO_PELT or Molerat Hide


{3300}{}{[ITEM]}
{3301}{}{1}                                 # PID_LEATHER_ARMOR
{3302}{}{pcx/items/ltharmor.pcx}
{3303}{}{88055}
{3304}{}{CRFT_LTH}                          # Leather armor schematics
{3305}{}{180000}                            # 5 h 00 m
{3306}{}{NO}
{3307}{}{7}                                 # Armor
{3308}{}{[TOOLS]}
{3309}{}{4|236}                             # PID_KNIFE|PID_COMBAT_KNIFE
{3310}{}{[SKILLS]}
{3311}{}{REPAIR:50}
{3312}{}{[COMPONENTS]}
{3313}{}{127:1}                             # PID_ROPE
{3314}{}{276:4|623:4}                       # PID_GECKO_PELT or Molerat Hide


{3400}{}{[ITEM]}
{3401}{}{379}                               # PID_LEATHER_ARMOR_MK_II
{3402}{}{pcx/items/ltharmr2.pcx}
{3403}{}{88055}
{3404}{}{CRFT_LTH}                          # Leather armor schematics
{3405}{}{180000}                            # 5 h 00 m
{3406}{}{NO}
{3407}{}{7}                                 # Armor
{3408}{}{[TOOLS]}
{3409}{}{4|236}                             # PID_KNIFE|PID_COMBAT_KNIFE
{3410}{}{[SKILLS]}
{3411}{}{REPAIR:75}
{3412}{}{[COMPONENTS]}
{3413}{}{1:1}                               # PID_LEATHER_ARMOR
{3414}{}{277:2}                             # PID_GOLDEN_GECKO_PELT


{3500}{}{[ITEM]}
{3501}{}{2}                                 # PID_METAL_ARMOR
{3502}{}{pcx/items/ltharmor.pcx}
{3503}{}{81065}
{3504}{}{CRFT_LTH}                          # Leather (yeah, I know...)
{3505}{}{180000}                            # 5 h 00 m
{3506}{}{NO}
{3507}{}{7}                                 # Armor
{3508}{}{[TOOLS]}
{3509}{}{75|308}                            # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{3510}{}{[SKILLS]}
{3511}{}{REPAIR:60}
{3512}{}{[COMPONENTS]}
{3513}{}{74:1}                              # PID_LEATHER_JACKET
{3514}{}{98:2|269:1}                        # Junk or Robot Parts


{3600}{}{[ITEM]}
{3601}{}{380}                               # PID_METAL_ARMOR_MK2
{3602}{}{pcx/items/ltharmor.pcx}
{3603}{}{79063}
{3604}{}{CRFT_LTH}                          # Leather (yeah, I know...)
{3605}{}{180000}                            # 5 h 00 m
{3606}{}{NO}
{3607}{}{7}                                 # Armor
{3608}{}{[TOOLS]}
{3609}{}{75|308}                            # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{3610}{}{[SKILLS]}
{3611}{}{REPAIR:90}
{3612}{}{[COMPONENTS]}
{3613}{}{2:1}                               # PID_METAL_ARMOR
{3614}{}{32:2|382:2}                        # Flamethrower fuel


# ELECTRONICS

{3700}{}{[ITEM]}
{3701}{}{77}                                # PID_ELECTRONIC_LOCKPICKS
{3702}{}{pcx/items/elecpic.pcx}
{3703}{}{91060}
{3704}{}{CRFT_EL2}                          # advanced electronics schematic
{3705}{}{288000}                            # 8 h 00 m
{3706}{}{NO}
{3707}{}{8}                                 # Electronics
{3708}{}{[TOOLS]}
{3709}{}{228}                               # PID_TECHNICAL_MANUAL
{3710}{}{75|308}                            # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{3711}{}{[SKILLS]}
{3712}{}{REPAIR+LOCKPICK:100}
{3713}{}{SCIENCE:60}
{3714}{}{[COMPONENTS]}
{3715}{}{59:1}                              # PID_MOTION_SENSOR
{3716}{}{52:1}                              # PID_GEIGER_COUNTER


{3800}{}{[ITEM]}
{3801}{}{411}                               # PID_ELEC_LOCKPICK_MKII
{3802}{}{pcx/items/elockpk2.pcx}
{3803}{}{86056}
{3804}{}{CRFT_EL2}                          # advanced electronics schematic
{3805}{}{216000}                            # 6 h
{3806}{}{NO}
{3807}{}{8}                                 # Electronics
{3808}{}{[TOOLS]}
{3809}{}{228}                               # PID_TECHNICAL_MANUAL
{3810}{}{308}                               # PID_SUPER_TOOL_KIT
{3811}{}{[SKILLS]}
{3812}{}{REPAIR+LOCKPICK:120}
{3813}{}{SCIENCE:80}
{3814}{}{[COMPONENTS]}
{3815}{}{77:1}                              # PID_ELECTRONIC_LOCKPICKS


# SHARPENING

{3900}{}{[ITEM]}
{3901}{}{7}                                 # PID_SPEAR
{3902}{}{pcx/items/spear.pcx}
{3903}{}{159039}
{3904}{}{CRFT_BLD}                          # blades schematics
{3905}{}{27000}                             # 45 m
{3906}{}{NO}
{3907}{}{10}                                # Weapons
{3908}{}{[TOOLS]}
{3909}{}{278}                               # PID_FLINT
{3910}{}{[SKILLS]}
{3911}{}{REPAIR+MELEE_WEAPONS:60}
{3912}{}{[COMPONENTS]}
{3913}{}{4:1}                               # PID_KNIFE
{3914}{}{320:1}                             # PID_SHARPENED_POLE


{4000}{}{[ITEM]}
{4001}{}{280}                               # PID_SHARP_SPEAR
{4002}{}{pcx/items/spear2.pcx}
{4003}{}{159039}
{4004}{}{CRFT_BLD}                          # blades schematics
{4005}{}{27000}                             # 45 m
{4006}{}{NO}
{4007}{}{10}                                # Weapons
{4008}{}{[TOOLS]}
{4009}{}{278}                               # PID_FLINT
{4010}{}{[SKILLS]}
{4011}{}{MELEE_WEAPONS+THROWING:60}
{4012}{}{[COMPONENTS]}
{4013}{}{7:1}                               # PID_SPEAR


# WEAPONS

{4100}{}{[ITEM]}
{4101}{}{300}                              # Zip Gun
{4102}{}{pcx/items/zipgun.pcx}
{4103}{}{90060}
{4104}{}{}                                 # ALWAYS
{4105}{}{108000}                           # 3 h 00 m
{4106}{}{NO}
{4107}{}{10}                               # Weapons
{4108}{}{[TOOLS]}
{4109}{}{4}                                # PID_KNIFE
{4110}{}{[SKILLS]}
{4111}{}{REPAIR+SMALL_GUNS:60}
{4112}{}{[COMPONENTS]}
{4113}{}{7:1|280:1}                        # Spear OR Sharp Spear


{4200}{}{[ITEM]}
{4201}{}{640}                              # Deathclaw Gauntlet
{4202}{}{pcx/items/clawgntl.pcx}
{4203}{}{82053}
{4204}{}{CRFT_GNT}                         # special recipe
{4205}{}{108000}                           # 3 h 00 m
{4206}{}{NO}
{4207}{}{10}                               # Weapons
{4208}{}{[TOOLS]}
{4209}{}{308}                              # PID_SUPER_TOOL_KIT
{4210}{}{[SKILLS]}
{4211}{}{MELEE_WEAPONS:70}
{4212}{}{REPAIR:80}
{4213}{}{[COMPONENTS]}
{4214}{}{622:3}                            # 3 death claws
{4215}{}{235:1}                            # 1 power fist


# MISC

{4300}{}{[ITEM]}
{4301}{}{308}                               # PID_SUPER_TOOL_KIT
{4302}{}{pcx/items/suprtool.pcx}
{4303}{}{57055}
{4304}{}{CRFT_TOL}                          # tool schematics
{4305}{}{72000}                             # 2 h 00 m
{4306}{}{NO}
{4307}{}{11}                                # Misc
{4308}{}{[TOOLS]}
{4309}{}{[SKILLS]}
{4310}{}{REPAIR:70}
{4311}{}{SCIENCE:30}
{4312}{}{[COMPONENTS]}
{4313}{}{75:1}                              # PID_MULTI_TOOL
{4314}{}{384:1}                             # PID_WRENCH
{4315}{}{98:1}                              # Junk

