# Skill names for messages
{1}{}{������ ������}
{2}{}{������� ������}
{3}{}{������ ������}
{4}{}{��� ������}
{5}{}{�����. ������}
{6}{}{�������}
{7}{}{������ ������}
{8}{}{������}
{9}{}{����������}
{10}{}{�����}
{11}{}{�����}
{12}{}{�������}
{13}{}{�����}
{14}{}{������}
{15}{}{�����������}
{16}{}{������}
{17}{}{�������� ����}
{18}{}{����������}
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
{41}{}{���}
{42}{}{������ ������}
{43}{}{���������}
{44}{}{����������}
{45}{}{����������}
{46}{}{�������}
{47}{}{�����}
{48}{}{�����������}
{49}{}{����}
{50}{}{������}
{51}{}{������}

# messages
{81}{}{�� ������� ������ ���������� ����������.}
{82}{}{�� ������� ����� ������� �����.}
{83}{}{�� ������ ������� ������������� ������������ ����� ������ �������������.}
{84}{}{�� ������ ������� ����������������� ���������� ����������.}
{85}{}{�� ������� ����� ��������� ����������� ���������.}
{86}{}{������ �� ������, ����� ����� ������� ����� ��� �����������.}
{87}{}{������ �� ���������, ��� �������� ������ ��� ������ ������.}
{88}{}{�� �������� ��������� �������� ���.}
{89}{}{��������, �� ������ ������� ���. ����� ��������������.}

{90}{}{��� ������� ����� �������� ��� ���������.}

{100}{}{[������]}
{101}{}{[�����]}
{102}{}{[�����]}
{103}{}{�������}
{104}{}{���������}
{105}{}{[������]}
{106}{}{[�����]}
{107}{}{[��� ����]}
{108}{}{������� ���}
{109}{}{��������� ���}
{110}{}{ (}
{111}{}{ �������(�))}
{112}{}{[���������]}
{120}{}{������}
{121}{}{Fix-Boy ���������� �� ����� ���!}

{150}{}{ ��� }

{200}{}{�������� ��������.}
{201}{}{�������(�) ������(�).}
{202}{}{�������(�) ��������(�).}
{210}{}{�������� ���������.}

{300}{}{�����������}
{301}{}{������}
{302}{}{����������}
{303}{}{���}
{304}{}{�����}
{305}{}{�����: }
{306}{}{�����: }

{400}{}{�������: }
{401}{}{���������: }
{402}{}{ (}
{403}{}{ �������(��)). }
{404}{}{ �. }
{405}{}{ �. ������.}

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
{494}{}{29+46}  # Crafting shortcut: Ctrl+C

# CRAFTING SCHEMATICS:

# FOOD

{1000}{}{[ITEM]}
{1001}{}{627}                              # Fish Soup
{1002}{}{pcx/items/stew1.pcx}
{1003}{}{69060}
{1004}{}{CRFT_FOD}                                 # 
{1005}{}{18000}                            # 0 h 30 m
{1006}{}{NO}
{1007}{}{1}                                # food
{1008}{}{[TOOLS]}
{1009}{}{4|236}                            # PID_KNIFE|PID_COMBAT_KNIFE
{1010}{}{[SKILLS]}
{1011}{}{FIRST_AID+OUTDOORSMAN:90}
{1012}{}{[COMPONENTS]}
{1013}{}{535:1|536:1}                      # Fish or Scaly Fish
{1014}{}{106:1}                            # PID_NUKA_COLA
{1015}{}{71:1}                             # Fruit


{1100}{}{[ITEM]}
{1101}{}{628}                              # Meat Stew
{1102}{}{pcx/items/stew2.pcx}
{1103}{}{69060}
{1104}{}{CRFT_FOD}                                 # 
{1105}{}{18000}                            # 0 h 30 m
{1106}{}{NO}
{1107}{}{1}                                # food
{1108}{}{[TOOLS]}
{1109}{}{4|236}                            # PID_KNIFE|PID_COMBAT_KNIFE
{1110}{}{[SKILLS]}
{1111}{}{FIRST_AID+OUTDOORSMAN:80}
{1112}{}{[COMPONENTS]}
{1113}{}{284:2|103:2|81:2}                 # 2x Meat Jerky or 2x Meat-on-a-stick or 2x Iguana-on-a-stick
{1114}{}{124:1|310:1}                      # PID_BEER or PID_GAMMA_GULP_BEER
{1115}{}{71:1}                             # Fruit


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
{1210}{}{DOCTOR+OUTDOORSMAN:60}
{1211}{}{[COMPONENTS]}
{1212}{}{271:1}                             # PID_BROC_FLOWER
{1213}{}{272:1}                             # PID_XANDER_ROOT


{1300}{}{[ITEM]}
{1301}{}{49}                                # PID_ANTIDOTE
{1302}{}{pcx/items/drug_bot.pcx}
{1303}{}{90060}
{1304}{}{}                                  # ALWAYS
{1305}{}{30000}                             # 50 m
{1306}{}{NO}
{1307}{}{3}                                 # Drugs
{1308}{}{[TOOLS]}
{1309}{}{[SKILLS]}
{1310}{}{DOCTOR+OUTDOORSMAN:50}
{1311}{}{SCIENCE:25}
{1312}{}{[COMPONENTS]}
{1313}{}{92:1|591:2}                        # PID_SCORPION_TAIL or two Small Scorpion Tails
{1314}{}{125:1|469:1}                       # PID_BOOZE or PID_ROT_GUT


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
{1605}{}{144000}                            # 4 h
{1606}{}{NO}
{1607}{}{3}                                 # adv drug
{1608}{}{[TOOLS]}
{1609}{}{91}                                # PID_DOCTORS_BAG
{1610}{}{[SKILLS]}
{1611}{}{DOCTOR:80}
{1612}{}{SCIENCE:90}
{1613}{}{[COMPONENTS]}
{1614}{}{87:1}                              # PID_BUFFOUT
{1615}{}{71:3}                              # PID_MUTATED_FRUIT
{1616}{}{311:1}                             # PID_ROENTGEN_RUM
{1617}{}{40:1}                              # PID_STIMPAK


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
{1805}{}{108000}                            # 3 h
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


{1900}{}{[ITEM]}
{1901}{}{620}                               # new carry weight drug
{1902}{}{pcx/items/drugcrry.pcx}
{1903}{}{47074}
{1904}{}{CRFT_DRG}                          # drugs schematics
{1905}{}{108000}                            # 3 h
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
{1916}{}{124:2|310:2}                       # PID_BEER or PID_GAMMA_GULP_BEER


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
{2012}{}{REPAIR:30}
{2013}{}{[COMPONENTS]}
{2014}{}{79:1}                              # PID_FLARE
{2015}{}{125:1|469:1}                       # PID_BOOZE or PID_ROT_GUT


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
{2305}{}{36000}                            # 1 h
{2306}{}{NO}
{2307}{}{5}                                # Ammo
{2308}{}{[TOOLS]}
{2309}{}{75|308}                           # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{2310}{}{[SKILLS]}
{2311}{}{SMALL_GUNS:60}
{2312}{}{REPAIR:50}
{2313}{}{[COMPONENTS]}
{2314}{}{95:1}                             # Shotgun shells
{2315}{}{19:1}                             # PID_ROCK


{2400}{}{[ITEM]}
{2401}{}{641:2}                            # new 12ga incendiary
{2402}{}{pcx/items/ssbcksht.pcx}
{2403}{}{79060}
{2404}{}{CRFT_AMM}                         # ammo craft schematics
{2405}{}{72000}                            # 2 h
{2406}{}{NO}
{2407}{}{5}                                # Ammo
{2408}{}{[TOOLS]}
{2409}{}{75|308}                           # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{2410}{}{[SKILLS]}
{2411}{}{SMALL_GUNS:100}
{2412}{}{REPAIR:80}
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
{2511}{}{SMALL_GUNS:80}
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
{2611}{}{SMALL_GUNS:100}
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
{2711}{}{SMALL_GUNS:80}
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
{2811}{}{BIG_GUNS:70}
{2812}{}{REPAIR:60}
{2813}{}{[COMPONENTS]}
{2814}{}{631:1}                            # 40mm HE grenades
{2815}{}{159:2}                            # Molotov


# TRAPS

{2900}{}{[ITEM]}
{2901}{}{618:4}                            # Trap kit Spike
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
{2914}{}{365:8|583:8|320:4|7:2|280:2}      # Plant Spikes OR Sharp Poles OR Spears OR Sharp Spears


{3000}{}{[ITEM]}
{3001}{}{645}                              # Bear Trap
{3002}{}{pcx/items/spiketrap.pcx}
{3003}{}{69055}
{3004}{}{CRFT_BLD}                         # blades schematics
{3005}{}{108000}                           # 3 h 00 m
{3006}{}{NO}
{3007}{}{6}                                # Traps
{3008}{}{[TOOLS]}
{3009}{}{308}                              # PID_SUPER_TOOL_KIT
{3010}{}{[SKILLS]}
{3011}{}{REPAIR+TRAPS:140}
{3012}{}{[COMPONENTS]}
{3013}{}{98:1}                             # Junk
{3014}{}{4:3|45:3|7:2|280:2}               # Knives OR throwing knives OR Spears OR Sharp Spears


{3100}{}{[ITEM]}
{3101}{}{616:4}                            # Trap kit Mine
{3102}{}{pcx/items/trapkit.pcx}
{3103}{}{68061}
{3104}{}{CRFT_EXP}                         # explosive schematics 644
{3105}{}{108000}                           # 3 h 00 m
{3106}{}{YES}
{3107}{}{6}                                # Traps
{3108}{}{[TOOLS]}
{3109}{}{75|308}                           # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{3110}{}{[SKILLS]}
{3111}{}{REPAIR+TRAPS:80}
{3112}{}{[COMPONENTS]}
{3113}{}{127:1}                            # Rope
{3114}{}{98:1}                             # Junk


{3200}{}{[ITEM]}
{3201}{}{619:3}                            # Trap kit Proximity
{3202}{}{pcx/items/sensmine.pcx}
{3203}{}{55054}
{3204}{}{CRFT_ELE}                         # Electronics
{3205}{}{108000}                           # 3 h 00 m
{3206}{}{NO}
{3207}{}{6}                                # Traps
{3208}{}{[TOOLS]}
{3209}{}{308}                              # PID_SUPER_TOOL_KIT
{3210}{}{[SKILLS]}
{3211}{}{REPAIR+TRAPS:120}
{3212}{}{SCIENCE:60}
{3213}{}{[COMPONENTS]}
{3214}{}{38:1}                             # SEC
{3215}{}{98:1}                             # Junk


# LEATHER ARMOR

{3300}{}{[ITEM]}
{3301}{}{74}                                # PID_LEATHER_JACKET
{3302}{}{pcx/items/maxinv.pcx}
{3303}{}{62060}
{3304}{}{CRFT_LTJ}                          # Leather Jacket schematics
{3305}{}{180000}                            # 5 h 00 m
{3306}{}{NO}
{3307}{}{7}                                 # Armor
{3308}{}{[TOOLS]}
{3309}{}{4|236}                             # PID_KNIFE|PID_COMBAT_KNIFE
{3310}{}{[SKILLS]}
{3311}{}{REPAIR:35}
{3312}{}{[COMPONENTS]}
{3313}{}{127:1}                             # PID_ROPE
{3314}{}{276:2|623:2}                       # PID_GECKO_PELT or Molerat Hide


{3400}{}{[ITEM]}
{3401}{}{1}                                 # PID_LEATHER_ARMOR
{3402}{}{pcx/items/ltharmor.pcx}
{3403}{}{88055}
{3404}{}{CRFT_LTH}                          # Leather armor schematics
{3405}{}{180000}                            # 5 h 00 m
{3406}{}{NO}
{3407}{}{7}                                 # Armor
{3408}{}{[TOOLS]}
{3409}{}{4|236}                             # PID_KNIFE|PID_COMBAT_KNIFE
{3410}{}{[SKILLS]}
{3411}{}{REPAIR:50}
{3412}{}{[COMPONENTS]}
{3413}{}{127:1}                             # PID_ROPE
{3414}{}{276:6|623:4}                       # PID_GECKO_PELT or Molerat Hide


{3500}{}{[ITEM]}
{3501}{}{379}                               # PID_LEATHER_ARMOR_MK_II
{3502}{}{pcx/items/ltharmr2.pcx}
{3503}{}{88055}
{3504}{}{CRFT_LTH}                          # Leather armor schematics
{3505}{}{180000}                            # 5 h 00 m
{3506}{}{NO}
{3507}{}{7}                                 # Armor
{3508}{}{[TOOLS]}
{3509}{}{4|236}                             # PID_KNIFE|PID_COMBAT_KNIFE
{3510}{}{[SKILLS]}
{3511}{}{REPAIR:75}
{3512}{}{[COMPONENTS]}
{3513}{}{1:1}                               # PID_LEATHER_ARMOR
{3514}{}{277:2}                             # PID_GOLDEN_GECKO_PELT


{3600}{}{[ITEM]}
{3601}{}{2}                                 # PID_METAL_ARMOR
{3602}{}{pcx/items/ltharmor.pcx}
{3603}{}{81065}
{3604}{}{CRFT_LTH}                          # Leather (yeah, I know...)
{3605}{}{180000}                            # 5 h 00 m
{3606}{}{NO}
{3607}{}{7}                                 # Armor
{3608}{}{[TOOLS]}
{3609}{}{308}                               # PID_SUPER_TOOL_KIT
{3610}{}{[SKILLS]}
{3611}{}{REPAIR:75}
{3612}{}{[COMPONENTS]}
{3613}{}{74:1}                              # PID_LEATHER_JACKET
{3614}{}{98:3|269:1}                        # Junk or Robot Parts


{3700}{}{[ITEM]}
{3701}{}{380}                               # PID_METAL_ARMOR_MK2
{3702}{}{pcx/items/ltharmor.pcx}
{3703}{}{79063}
{3704}{}{CRFT_LTH}                          # Leather (yeah, I know...)
{3705}{}{180000}                            # 5 h 00 m
{3706}{}{NO}
{3707}{}{7}                                 # Armor
{3708}{}{[TOOLS]}
{3709}{}{308}                               # PID_SUPER_TOOL_KIT
{3710}{}{[SKILLS]}
{3711}{}{REPAIR:100}
{3712}{}{[COMPONENTS]}
{3713}{}{2:1}                               # PID_METAL_ARMOR
{3714}{}{32:2|382:2}                        # Flamethrower fuel


# ELECTRONICS

{3800}{}{[ITEM]}
{3801}{}{77}                                # PID_ELECTRONIC_LOCKPICKS
{3802}{}{pcx/items/elecpic.pcx}
{3803}{}{91060}
{3804}{}{CRFT_EL2}                          # advanced electronics schematic
{3805}{}{288000}                            # 8 h 00 m
{3806}{}{NO}
{3807}{}{8}                                 # Electronics
{3808}{}{[TOOLS]}
{3809}{}{228}                               # PID_TECHNICAL_MANUAL
{3810}{}{75|308}                            # PID_MULTI_TOOL | PID_SUPER_TOOL_KIT
{3811}{}{[SKILLS]}
{3812}{}{REPAIR+LOCKPICK:100}
{3813}{}{SCIENCE:60}
{3814}{}{[COMPONENTS]}
{3815}{}{59:1}                              # PID_MOTION_SENSOR
{3816}{}{52:1}                              # PID_GEIGER_COUNTER


{3900}{}{[ITEM]}
{3901}{}{411}                               # PID_ELEC_LOCKPICK_MKII
{3902}{}{pcx/items/elockpk2.pcx}
{3903}{}{86056}
{3904}{}{CRFT_EL2}                          # advanced electronics schematic
{3905}{}{216000}                            # 6 h
{3906}{}{NO}
{3907}{}{8}                                 # Electronics
{3908}{}{[TOOLS]}
{3909}{}{228}                               # PID_TECHNICAL_MANUAL
{3910}{}{308}                               # PID_SUPER_TOOL_KIT
{3911}{}{[SKILLS]}
{3912}{}{REPAIR+LOCKPICK:120}
{3913}{}{SCIENCE:80}
{3914}{}{[COMPONENTS]}
{3915}{}{77:1}                              # PID_ELECTRONIC_LOCKPICKS


# SHARPENING

{4000}{}{[ITEM]}
{4001}{}{7}                                 # PID_SPEAR
{4002}{}{pcx/items/spear.pcx}
{4003}{}{159039}
{4004}{}{CRFT_BLD}                          # blades schematics
{4005}{}{27000}                             # 45 m
{4006}{}{NO}
{4007}{}{10}                                # Weapons
{4008}{}{[TOOLS]}
{4009}{}{278}                               # PID_FLINT
{4010}{}{[SKILLS]}
{4011}{}{REPAIR+MELEE_WEAPONS:60}
{4012}{}{[COMPONENTS]}
{4013}{}{4:1}                               # PID_KNIFE
{4014}{}{320:1}                             # PID_SHARPENED_POLE


{4100}{}{[ITEM]}
{4101}{}{280}                               # PID_SHARP_SPEAR
{4102}{}{pcx/items/spear2.pcx}
{4103}{}{159039}
{4104}{}{CRFT_BLD}                          # blades schematics
{4105}{}{27000}                             # 45 m
{4106}{}{NO}
{4107}{}{10}                                # Weapons
{4108}{}{[TOOLS]}
{4109}{}{278}                               # PID_FLINT
{4110}{}{[SKILLS]}
{4111}{}{MELEE_WEAPONS+THROWING:60}
{4112}{}{[COMPONENTS]}
{4113}{}{7:1}                               # PID_SPEAR


# WEAPONS

{4200}{}{[ITEM]}
{4201}{}{300}                              # Zip Gun
{4202}{}{pcx/items/zipgun.pcx}
{4203}{}{90060}
{4204}{}{}                                 # ALWAYS
{4205}{}{108000}                           # 3 h 00 m
{4206}{}{NO}
{4207}{}{10}                               # Weapons
{4208}{}{[TOOLS]}
{4209}{}{4}                                # PID_KNIFE
{4210}{}{[SKILLS]}
{4211}{}{REPAIR+SMALL_GUNS:60}
{4212}{}{[COMPONENTS]}
{4213}{}{7:1|280:1}                        # Spear OR Sharp Spear


{4300}{}{[ITEM]}
{4301}{}{640}                              # Deathclaw Gauntlet
{4302}{}{pcx/items/clawgntl.pcx}
{4303}{}{82053}
{4304}{}{CRFT_GNT}                         # special recipe
{4305}{}{108000}                           # 3 h 00 m
{4306}{}{NO}
{4307}{}{10}                               # Weapons
{4308}{}{[TOOLS]}
{4309}{}{308}                              # PID_SUPER_TOOL_KIT
{4310}{}{[SKILLS]}
{4311}{}{MELEE_WEAPONS:70}
{4312}{}{REPAIR:80}
{4313}{}{[COMPONENTS]}
{4314}{}{622:3}                            # 3 death claws
{4315}{}{235:1}                            # 1 power fist


# MISC

{4400}{}{[ITEM]}
{4401}{}{308}                               # PID_SUPER_TOOL_KIT
{4402}{}{pcx/items/suprtool.pcx}
{4403}{}{57055}
{4404}{}{CRFT_TOL}                          # tool schematics
{4405}{}{72000}                             # 2 h 00 m
{4406}{}{YES}
{4407}{}{11}                                # Misc
{4408}{}{[TOOLS]}
{4409}{}{[SKILLS]}
{4410}{}{REPAIR:70}
{4411}{}{SCIENCE:30}
{4412}{}{[COMPONENTS]}
{4413}{}{75:1}                              # PID_MULTI_TOOL
{4414}{}{384:1}                             # PID_WRENCH
{4415}{}{98:1}                              # Junk

