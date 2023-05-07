-====================-
-===   EcCo mod   ===-
-=== v0.6.2 BETA  ===-
-====================-
						by phobos2077


In short, this is a conservative gameplay overhaul.

Main goals:
- add more challenge to the combat, barter and other aspects of the game (but without mandatory hardcore)
- fix some stuff of the Restoration Project as well as vanilla game which I feel were broken
- add more variety to the gameplay, mainly to the combat (but in line with original game design, you won't see OP weapons or other unicorns here). 
- keep everything as modular as possible, so the players can configure everything to their liking and modders can re-use parts of this mod in their own


Main Highlights.

Economy Rebalance:
- Barter skill now more useful:
- prices in stores are affected stronger by skill at lower barter levels and less at higher, using arctangent function 
- selling prices are finally increase as Barter skill increase, they also affected by player charisma and merchant skill
- some items are in greater or lower demand in certain towns, you can trade for profit if you skilled enough
- prices are highly customizable via INI
- raise money by selling new types of monster parts or by doing several new quests (see details)
- reduced/made harder to get some critically-overpowered loot in several locations

Combat Rebalance:
- weapons and ammo rebalanced to add realism and more difference between various types of weaponry,
while staying as close as possible to vanilla (the point is not to re-invent weapons, but to improve existing ones)
- amount of ammo in game is reduced
- energy weapons made more effective against lesser armors, and laser weapons made more powerfull
- new melee weapons for Melee skill to be viable in mid-game
- throwing weapons expanded and made much more usefull with skill-based damage bonus for blades, much deadlier grenades and new weapons
- Bozar is now a large caliber sniper rifle (as it should be), firing new rare and expensive .50 rounds
- double-barrel shotguns now have proper duplet mode with new sound and single-shot animation (optional)
- slight ballance changes to armor
- several critters in the game have much better stats now (like weak types of Deathclaws and large scorpions)
- new stealth elements: blackjack and sneak attack

Game Progression changes:
- included gameflow fixes by Lujo: Small changes which should help integrate some of the RP restored content to the original game. A few hooks for some of the content, a new scouting quest in Vault City, and adjustments to the Vault Village quest.
- some gangs made tougher (Metzgers, Salvatores, Vault 15 raiders)
- redesigned entrances to the Raiders hideout for more challange and variety
- reduced unbalanced EXP rewards for several quests
(more to come...)

Crafting System:
- Revamped version of Mr. Fixit mod included (more user friendly)
- existing schematics rebalanced, new added
- several new items to craft: new ammo types, home-made grenade, new drugs, traps
- unlockable crafting groups (explosives, drugs, electronics, etc.), you need to find teacher for each group

Traps System:
- installable traps: "melee" type spike trap, explosive mine and sensor mine
- explosive traps are customized by arming them with any type of explosives or grenades

New Quests:
- a couple of random-encounter-based "Bounty Hunt" quests
- a couple of "Bring X items" quests


Other mods that I used/included:
- sfall 3.5 DLL for Windows XP SP2+ (included)
- Party Orders addon (expanded with "Switch ammo" feature)
- Mr. Fixit (adopted and expanded)
- Haenlomal's Yet Another Ammo Mod damage formula (with sfall)


-=== COMPATIBILITY ===-

ONLY installable above the Killap's Restoration Project 2.3.3
Following RP options MUST be installed:
- Party members change appearence when wearing armor
- New weapon animations (all of them)

Start of a new game is NOT required (but is recommended, as usual...)

-=== INSTALLATION ===-

1) make a backup copy of your entire game installation folder (except master.dat and critter.dat files - those won't be affected)

2) use installer with desired options

3) start Fallout 2 and play

If you won't like the merchant prices or some other aspects, feel free to read and edit the barter.ini and combat.ini as you like.

-=== DETAILS  (WARNING! SPOILERS!!!) ===-

> CRAFTING:
- Mr.Fixit v1.1 was taken and slightly expanded with better hi-res support and some new features
- All crafting rules was rewritten with new "better" balance and variaty, including new game items
- All "schematics" are divided into several categories, you need to find teacher for each category (there is no spoiler here, so try to
find them on your own. I will only say that they all around northern half of the world...)
- Knowing schematics not enough, to start crafting you need tools, skills and components
- Some craftable food
- Crafting menu is accessible by doing description of player or with a hotkey: Ctrl+C.

> TRAPS:
- to use traps you need to craft a Trap Kit first (need explosive schematics for mines and electronics for sensor mine)
- then, put trap in your active hand slot and use it ON your character (or just press Ctrl+1 hotkey) - it will place trap on the ground below (not yet armed)
- use Traps skill on trap to arm it.
- for mines: you can use any explosive from inventory on the floor trap tile; if you just use "Traps" skill on them, the game will first try to arm it with last used explosive type, and then with any explosive found in your inventory.
- you need to pass traps skill check to successfully arm the trap, if you are bad enough, you may end up blowing yourself.
- you can dismantle any trap (both armament and trap kit will return to your inventory) just Using them or using Traps Skill on them.
- number of traps is not limited
- spike traps can be used a couple of times (it loses one "charge" when someone steps on it)
- there are INI-configurable friend-or-foe system (by default dude and party members are ignored by your traps)
- when using spike traps, damage formula is: 7-14 (when traps skill is 0~40), max damage is increased up to 40, by 1 for each 3 skill points (7-40 at 120% skill).
- when using explosives, explosion damage is approximately equal to damage when using those items normally; damage type is also derived from item (EMP for Pulse grenade, Fire for Molotov, etc.)
- sensor mines detect movement on 1 tile radius. If critter passes just near the trap and don't step on it, there is a very small chance trap won't go off.

> PRICES:
- Selling prices are affected by skill. (at lower levels prices may drop as low as 10% from their normal margin). This way, if you wanna get rich by selling weapons, upgrade your Barter or you'll need to sell many times more than before.
- Buying prices use vanilla formula as a base (with all kind of things effecting it, like perks or bad merchant reaction) and multiplies it slightly with arctangent kind of function (example graph in sources folder, for more info study barter.ini)
- Some misc. items prices was adjusted for early game so you can make some money in hardest parts (high prices for gecko pelts and scorpion tails in Klamath, etc.)
- There are several alternative formulas to choose from and many coefficients to tweak (read and modify barter.ini)

> LOOT REDUCTION:
- there is chance a weapon will get destroyed when critter dies (except unique and rare weapons; optional)
- corpses are stripped from some percent of ammo and stimpaks (optional)
- Loot slightly reduced in S.A.D, Hubologist Stash, Toxic Caves 
- EPA: loot rearranged/reduced somewhat; room with most powerful stuff at security level will be harder to get in
- it is harder to steal from Redding doctor now
- slosed rooms in Bishop club are harder to get in

> NEW QUEST CONTENT:
- craft learning (see "crafting" section)
- one of the trappers in Klamath can now teach you gecko skinning (not free)
- kill groups of robbers near Redding
- hunt down several rogues throughout the wastelend, one-by-one (NCR)
- bring a number of hides to Modoc tannery
- bring a number of tentacles to NCR doctor

> AMMO:
- AP and FMJ do less base damage then JHP (unarmored critters), but is very effective against armored targets (thanks to YAAM)
- Penetrating power of AP ammo in ASCENDING order:
10mm AP / .223 FMJ
Small energy cell (energy pistols)
5mm AP / .44 FMJ
7.62x51 / Micro-fusion cell (energy rifles and minigun)
4.7mm caseless
14mm AP : ignores any armor up to Combat Armor
.50 BMG
2mm GAUSS / AP Rocket : make Power Armor user defenceless

- Changed pack size of following ammo types (to balance the total amount of that ammo in game, creating the need of purchase)
[caliber] - [pack size] ([vanilla pack size])
10mm - 20 (24)
12ga - 12 (20)
.44  - 12 (20)
14mm - 12 (20)
5mm  - 40 (50)
7.62 - 20 (20) - unchanged
.45  - 50 (50) - unchanged
.223 - 30 (50)
SEC  - 20 (40)
MFC  - 20 (50)
4.7mm- 40 (50)
2mm  - 10 (20)

- weight and cost was rebalanced as well
- to further reduce "ammo swimming", all dying critters are stripped from some amount of ammo (optional), see MISC section
- ammo now occupies space, so you cannot store unlimited ammo in car trunk (increased trunk capacity by 20% to balance that)
- HE Rocket is extremely powerfull, but AP Rocket penetrates like gauss
- .50 ammo caliber and ammo type added (used only in new Bozar)
- new ammo types: 12ga Slugs, .223AP, 14mm JHP (crafting)


> FIREARMS:
- All shotguns: the max damage is much higher (min dmg is almost the same), wich makes them very deadly against unarmored critters, but cannot penetrate heavy armor and limited in range.
- 2 barrel shotguns have a duplet (burst) firing mode with single shot animation.
- All pistols (including energy pistols): cost 4 AP to shoot (That's what pistols are for in real life - shoot faster), but have smaller firing range and not near as powerfull as rifles.
- Bozar is what it should be - single-shot anti-materiel rifle, uses new .50 BMG ammo (penetrate most armor), need 7 STR and has very high damage. For machinegunning use LSW or M60 instead.
- Sniper Rifle is much more powerful, rechambered "back" to 7.62
- M60 is a true machinegun: more powerful with 100 rounds ammo capacity (like in RL).
- Almost every weapon was subjectively improved (main concerns were: more realism, more interesting balance between weapons, taking new ammo behaviour into account, BUT not going too far from vanilla stats, except those weapons mentioned specifically).


> NEW WEAPONS:
- taser
- 40mm grenade launchers (two types) with two types of grenades
- 9mm SMG in some random encounters


> ENERGY WEAPONS:
- all energy weapons has higher penetration (rifles better than pistols), so now only the best armor can provide strong protection against Laser or Plasma rifles
- Laser weapons are more powerful and armor laser resistance was changed (see below).
- "Real" Turbo Plasma rifle, costs 4 AP for shot (max damage reduced a bit).
- strong single-shot energy weapons now spend more than 1 cell round for each shot


> Some examples of ballance between some weapons of comparable class:
- 10mm Pistol vs 10mm SMG (for single shots): Pistol is faster (4AP) but has reduced range and slightly less damage
- .44 Magnum vs Desert Eagle: first has more power, second is more accurate and long-ranged
- 14mm Pistol does less damage than legendary .223 Pistol, but has more penetration
- Laser pistol and 14mm Pistol are comparable but Laser will better penetrate most armour types except metal armor. 14mm ammo is superb against any armor.
- Assault rifle vs FN FAL: high rate of fire (deadly at close range) vs heavy and piercing 7.62x51 ammo (much more damage than vanilla)
- HK CAWS vs Pancor Jackhammer: first has more range, fires 3-shot burst (like RL); second is low-range, uneconomical due to larger burst, but extremely deadly
- Light Support Weapon (.223) is less deadly than M60 (7.62mm), but has better accuracy


> GRENADES:
- all grenades was made more powerfull:
plasma:  60 - 100
frag:    35 - 60
molotov: 15 - 35
- EMP grenade now can do damage to a man in Power armor (enclave patrols included), due to electro-mechanical nature of this suit
- Home-made grenade can be crafted, it is worse than regular frag, but still powerful


> THROWING:
- Throwing skill now affects damage for all throwing weapons (except grenades), precise formula: 
dmgMax := floor(dmgMax * (1 + skill / 100.0));
So basically, you get 2x maximum damage with 100% skill, 3x damage with 200% and so on. It only affects maximum damage.
- Stats for throwing weapons were improved to make them more useful.
- Throwing Axe - new weapon was added. It's a more powerful replacement for throwing knife for mid-late game combat. Can be bought later in game.
- Molotov Cocktail, while still making visual explosion like frag grenade, now actually inflicts fire damage and does not knockback targets (it's not explosion after all).


> MELEE & UNARMED:
- The cost of the unarmed special attacks has been lowered to 4 for punches and 5 for kicks (taken from Weapons Redone mod).
- Super sledge takes 4,5 AP instead of 3,4 (same as regular sledge; no logical explaination of "faster swing").
- Wakizashi blade is much more powerful.
- new weapons: piston spear and spiked sledge


> ARMOR:
- Armor class was lowered considerably for power armours. AC affects hit chance, the more the AC, the more probable is to miss. It was not looking right when soldiers in big and heavy power armor appeared like they are extremely agile, because power armor is big, it should be easier to hit such target (but actual damage resistance remains the same). 
- Laser resistance changed: leather - zero protection, combat - mediocre, metal - good, power armor & tesla - great protection
- Power Armor user can now take damage from EMP grenades
- all changes to armor affect appropriate critters as well


> CRITTERS:
- some "lesser" critters made tougher: Tough Giant Ant, Large radscorpion, Deathclaws, Mole Rat. (they are rare on early maps and were way too weak)
- new monster parts dropped from critters: Death Claw, Mole Rat Hide, Wanamingo Hand, Mutant Tentacle

> QUESTS and NPCs:
- Lidya in VC rewards 500 for shipment of alcohol (was 300)
- better reward for VC plow quest
- Algernon need rest after work and don't spawn ammo in guns
- Trappers in random encounters now sell pelts through standard barter dialog only, but with high discount
- see Lujo Gameflow fixes mod for more information on additional changes

> MERCHANTS:
- added new items to several shopkeepers
- added some crafting components (mainly junk) to general stores
- Cash tender in Redding now offers cash from 1000 to 7000 depending on player's current level (that should be someone to sell all your stuff to)
- changed some merchants stock to offer some new items and more ammo for purchase

> RANDOM ENCOUNTERS:
- weapon loadouts were adjusted in respect to new weapon balance
- most new weapons are used by people in the wasteland
- throwing weapons will be used against you more often

> MISC:
- some mine traps in the game became more dangerous
- nerfed slot jinxer perk: slots break for month instead of 1 day, high rollers give 2/5 of initial money and there is a luck-based chance to fail. You can still become insanely rich by gambling.
- nerfed gambling dice: you can win maximum about 1000-5000 caps per table, per week (that's still a LOT of money)
- people drop their weapon to the ground in front of them when they die (optional)
- stimpaks radiate upon use (optional)
- drugs cost action points to use, even from inventory (first couple of uses are free though) - optional 
- Bonus Rate of Fire perk was removed (all pistols were completely OP if you take it, especially with the appropriate Trait)
- Hakunin dreams can be delayed, so they happen at more appropriate pace (RP has more content...)  - optional
- added Traps and Barter skill books to the game


-=== FOR MODDERS, TECHNICAL INFO ===-

- mod configs are stored in "barter.ini" and "combat.ini" files
- sfall config files used: Books.ini, Perks.ini
- this mod uses scripts TEST0 (2) for Mr.Fixit and TEST2 (4) for Traps system, no new (regular) scripts are added
- I had to use some normal global variables in range (644-647) for worldmap logic and pipboy quests
- 3 global scripts are running about 5-10 times in second (gl_stlth, gl_traps, gl_fixit)
- several hook script are used, refer to !Sources folder for more info

-=== CHANGELOG ===-

v***
- fixed some installer bugs
- fixed some minor map bug
- restored single-shot mode for M60 to fix firing sound issue
- added a few text corrections from Dravean

v0.6.2:
- moved to latest sfall with new engine features (a lot of refactoring, something might broke)
- improved quality of trap explosion effects and spike trap kill animation
- fixed duplicate trap kill EXP bonuses and kill counter increments
- incendiary projectile weapons now inflict fire damage to secondary targets too
- strong single-shot energy weapons now spend more than 1 cell round for each shot
- slightly lowered armor piercing values for some ammo types
- reverted speed of travel through mountains to vanilla level (was lowered at some point, now I don't think this was a good idea)
- all hotkeys (crafting menu, set trap, party orders) now work without delays (you don't have to press and hold them now)
- you can now close crafting menu with Escape key
- added option to delay Hakunin dreams somewhat
- nerfed double-barrel shotguns: when duplet mode is installed (which is off by default now), vanilla base damage will be used; 
still higher damage when duplet mode is disabled
- added optional AP requirement when using more than 2 drug items from inventory during combat
- added Traps and Barter skill books to the game
- doors to a bunch of loot at Bishop's club are better protected
- removed perk "Bonus rate of fire"
- no more free loot at Dr. Johnson (his stock is hidden just like any other merchant and he keeps an eye on his room)
- implemented robust code that fixes invalid ammo counts and calibers for all map objects (on first map enter)
- expanded melee (throwing, unarmed) combat by adding 4 new mid-game weapons (some craftable, some buyable, some can be found in the world)
- rebalanced some random encounters a bit (mainly to avoid instagib encounters in early game) and fixed several occasions of people unable to use their weapons (due to lack of animation)
- added more powerful shotgun shells to craft
- changed weapon destroy script - it works only for weapons listed in the INI (there were exclusion list before) and weapon destruction is shown in the message log

v0.6.1:
> Bug fixes:
- fixed not beign able to push Vic
- fixed several bugs related to traps
- mole rat hide now drops from Pinky & Brain
- fixed wrong ammo types found in guns and wrong ammo amount in the last pack in stacks (will apply when pickup from container or put weapon in hand)

> Balance
- Salvatore gang members were made tougher
- Increased number of guards in Vault 15
- replaced ALL combat armor in SAD with Metal Mk2 (to fight Salvatores)
- early traps made more appealing: spike traps work in 1 hex radius like sensor traps, skill requirement reduced
- adjusted some crafting schematics
- removed ability to steal full stock from Modoc general store
- added restockable non-stealable money pool to all NR drug dealers
- Eldrige inventory is reduced upon his death (was gamebreaking loot)
- reduced range of all shotguns, restored single mode for Pancor
- reduced laser rifle max damage
- rearranged loot in 2 rooms at EPA security level; only one room is "jammed" now (with better loot)
- added "don't touch that" checks to containers at slaver camp

> New features:
- all geckos and some rats and molerats can now be lured into traps outside of combat using appropriate food
- changed crafting skill requirements: now some schematics will require a sum of two skills instead of two separate skills. This allows for more flexibility in character development.
- ability to craft Super Tool Kit at some point
- changed encounter table for area around Vault Village: now you will encounter Mole rats in accordance to appropriate quest status
- reduced range at which abbey deathclaws start combat (to be able to use traps)
- moved tentacles quest from doctor to Henry next door (more appropriate)
- added trigger to be attacked by bots on S.A.D first floor


v0.6:
> Economy:
- in all barter price calculations, highest Barter skill in party is now used instead of PC skill only (to conform with vanilla)
- price koefficients were tweaked: merchant skill affect prices in similar scale to vanilla game
- one of the trappers in Klamath can now teach you gecko skinning (not free) and leather jacket crafting
- Loot slightly reduced in S.A.D
- Loot slightly reduced in Hubologist Stash
- EPA: added skill-check on two doors leading to locker rooms on security level

> Weapons:
- laser rifle hold frame switched back to "big gun", now super mutants can use it again...
- "LE" BB Gun nerfed a bit.. it's rare but was making many other weapons absolete because of accuracy, 4AP cost and enourmous magazine size
- added 40mm grenade launcher (2 types) with 2 types of grenades
- added 9mm SMG for flavor (and to use 9mm ammo)
- two new craftable ammo types: 14mm JHP and 40mm Incendiary grenade
- rechamber XL70E3 to .223 ammo, now it's a good light alternative to Light Support Weapon; added it to more places in game (still very rare)

> Gameflow:
- integrated Lujo Gameflow Fixes mod (experimental version): http://www.nma-fallout.com/showthread.php?201429-A-rewiev-of-the-RP-game-progression-experience-and-small-tweak-suggestions
- Flick and Tubby in Den are now protected better and their on-death loot is reduced 
- Metzger gang made tougher
- lowered several EXP rewards in NCR-Vault13 area
- redesigned Raiders hideout: secret entrance is more challenging now, while front entrance more straightforward (but still features tough fight)

> Misc:
- included expanded version of Party Orders addon (with Switch Ammo Type feature)
- all modified game scripts were "re-modified" and recompiled against latest RP source files
- craftable food (new teacher in Den)
- crafting menu improvements: changed order of items, more items per page, items split into categories for easier navigation (when there are many available)
- rearranged crafting teachers (3 new teachers added)
- text corrections in changed dialogs for better english
- improved "destroy weapon on death" by excluding rare and unique weapons (they will never be destroyed)
- added more Ropes and Spears to Maida, added free Junk in Den
- added more grenades to NPCs in random encounters
- fixed NPCs not being able to use Throwing Axes and Grenades in several random encounters
- simplified trap assembling: now you need to place them in hands and use them on the chosen one (or press Ctrl+1)


v0.5.2:
- adopted to RP v2.3.3
- added russian translation of mod, readme file and installer
- added new *better* buying price formula (not using vanilla price, but uses all proper variables like perks, discounts, etc.)
- swapped .223 Pistol and Mauser back to vanilla places; to make .223 rare, removed it from NCR shop and all common encounters
- changed some weapon distribution in random encounters according to changed weapon stats, added some grenades and throwing axes
- throwing axe uses knife animation: not much worse than club animation, but allows it to be used by more enemies
- two identical 9mm ammo types now split into "ball" and "Armor piercing"
- fixed Mr.Fixit dialog not producing items when using keyboard shortcut (Ctrl+C)

v0.5.1:
- reduced weight of rope, junk and fish
- "reduce drugs loot" default setting changed to 50%
- Algernon must rest before upgrading next weapon, plus weapon retain the amount of ammo it had before upgrade
- Trappers in random encounters now sell pelts through standard barter dialog only, but with high discount
- for plow quest in VC you get a little more worthy reward
- adjust XP values of some monsters to reflect changes in their stats
- removed Pancor Jackhammer from random encounters and moved M60 around
- made Molerats a little bit tougher
- added new lootable monster body parts: Death Claw, Mole Rat Hide, Wanamingo Hand, Mutant Tentacle.
- added Bounty Hunt quest to Ascorti (Redding)
- added Bounty Hunt quest line to deputy Karl (NCR)
- added Bring Tentacles quest to NCR doctor
- added Bring Molerat Hides quest to Balthas (Modoc)
- experimental feature: stimpaks radiate on use, booze acts as a weak rad-away (optional)

v0.5:
- fixed Mr.Fixit dialog skipping craft items
- fixed getting "trap kill XP" when target not actually killed
- fixed crash when shooting walls
- Taser stats improved
- proper ground image for axe
- added Hercules drug (Carry Weight bonus)
- traps changes:
  - new Proximity mine (junk+battery), 1 tile radius
  - explosions damage calculation changed, critters at 1 tile from explosion will receive the same damage as in epicenter
  - easier arming of "customizable" mines (see TRAPS section)
  - new unique graphics of traps on ground
  - one spike trap can now be used only twice
  - possible stability improvements
- added advanced drugs and leather armor teacher
- craft menu can now be accessed with hotkey: Ctrl+C
- source code file structure refactoring
- micro fusion cell mag size reduced (1 full cell will still charge car with 50% power, so this wasn't affected)
- some "lesser" critters made tougher (Tough Giant Ant, Large radscorpion, Deathclaws)
- added loot reducing in corpses

v0.4.4:
- fixed Smitty dialogue to allow learn crafting after you got a car
- fixed people drop their fist-weapons on death (how would that be possible?)
- fixed "window hang" bug in Poison schematic definition
- new weapon: Taser
- restore Zip Gun in game (craftable)
- party NPC skills used in crafting
- added craftable and installable spike traps (stone plate graphics)
- added configurable friend-or-foe system for traps
- implemented gaining experience points for all trap kills
- slightly reduced 10mm ammo pack size

v0.4.3:
- installable traps
- sneak attack and blackjack
- nerfed slot jinxer perk
- nerfed gambling dice
- adjusted weight and size of some items
- fixed "dancing autofire" death animation occured when using shotgun duplet mode

v0.4.2:
- learn crafting before use
- rebalanced craft rules
- fixed molotov not exploding when miss or hit scenery
- slight changes to barter price calculation (use round() instead of floor() on final prices)
- fix bug in installer causing damaged installation

v0.4.1:
- new items (craftable): 
  - home-made grenade
  - Dragon Skin (fire resistance drug)
  - 12ga slugs
  - .223 AP
- improved Mr. Fixit code to support multiple items in one batch
- added some crafting components to general stores (vanilla items)
- added more town demand item rules
- added weapon drop on death (my own version)

v0.4:
- new barter system
- added some price diversity for some items
- Sniper Rifle rechambered "back" to 7.62
- added some XL70E to stores. Still very rare.
- added sniper rifle and some axes to NCR store
- increased money in some stores

v0.3.1:
- implemented fire damage type for Molotov 
- adjusted grenades damage

v0.3:
- created installer

v0.2.2:
- *slightly* lowered damage and range of most pistols (to balance 5AP->4AP change)
- Bozar AMR now uses Big Guns skill
- M60 now has magazine capacity of 100
- reduced damage for Gauss weapons closely to vanilla state (because even Advanced power armor does not protect against their shots at all)
- reduced rocket launcher damage with explosive rocket to lightly armored targets (was 50% more than vanilla, now only 30%)
- increased DR mod for AP Rocket (to penetrate Adv. power armour)
- reduced 5mm ammo pack size to 40
- increased weight of 7.62mm and .50 ammo packs to roughly meet RL counterparts
- slightly reduced amount of .50 ammo in stores
- minor changes and fixes to some weapon stats

v0.2.1:
- adopted to RP 2.3.2
- fixed some upgraded weapons having different specs from basic ones
- added Mr.Fixit mod (obj_dude script was merged with RP version)

v0.2:
- adopted to RP 2.3
- throwing weapons rebalance, added damage bonus formula
- added Throwing Axe
- added .50 BMG and changed Bozar to use it
- made critters armor changes consistent
- damage changes for Bozar, M60 and LSW
- improved double-barrel shotguns duplet mode with unique sound and proper animations
- copy-pasted hs_calcapcost script from WR 2.2


-=== CREDITS ===-

mod was created by phobos2077 in 2010-2015

additional dialogs, designs, flow fixes: Lujo
russian translators: Pyran, Drobovik, phobos2077, Frederika, PolarTulip

many thanks goes to following people, who made this mod possible:
- Magnus for WR mod that inspired me
- Nirran for the original Barter mod
- Haenlomal for YAAM which gives more weapon balance options
- JimTheDinosaur for trap system inspiration
- Killap for the Restoration Project that gives something new to play in Fallout :)
- Timeslip for sfall with much needed features it gives and Script Editor which is awesome!
- Cubik2k for F2wedit and FO 1/2 Critter proto editor (eased my task VERY MUCH)
- F2se author for this great mod testing tool :)
- pelicano for Party Orders addon
- people at NMA and nuclear-city forums for useful comments
- Black Isle for my personal favorite game of all time! :)


::O
