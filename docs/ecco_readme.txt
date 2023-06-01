-====================-
-===   EcCo mod   ===-
-=== v0.9.0 BETA  ===-
-====================-
						by phobos2077


In short, this is a conservative gameplay overhaul.

Main goals:
- add more challenge to the combat, barter and other aspects of the game (but without mandatory hardcore)
- fix some stuff of the Restoration Project as well as vanilla game which I feel were broken
- add more variety to the gameplay, mainly to the combat (but in line with original game design, you won't see OP weapons or other unicorns here). 
- keep things configurable and modular, so the players can tweak mod to their liking and modders can re-use parts of it in their own creations


Main Highlights.

Economy Rebalance:
- Barter skill now more useful:
- prices in stores are affected stronger by skill at lower barter levels and less at higher, using arctangent function 
- selling prices now depend on Barter skill, as well as player charisma merchant skill
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
- Bozar is now a large caliber sniper rifle (per its picture and description), firing new rare and expensive .50 rounds
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
- become a trapper by luring geckos and rats into your traps using food as bait!

New Quests:
- a couple of random-encounter-based "Bounty Hunt" quests
- a couple of "Bring X items" quests


Other mods that I used/included:
- Mr. Fixit (adopted and expanded)
- Haenlomal's Yet Another Ammo Mod damage formula (with sfall)


-=== COMPATIBILITY ===-

ONLY installable above the Restoration Project Update v27 (with updated maps from Pixote)
Following RP options MUST be installed:
- New weapon animations (all of them)

Start of a new game is NOT required (but is recommended, as usual...)

-=== INSTALLATION ===-

1) install RPU v26 on a clean game installation (installer version is recommended):
- IMPORTANT: install Rifle Animations and Wakizashi Animations mods!
https://github.com/BGforgeNet/Fallout2_Restoration_Project/releases/tag/v26

2) download the archive and extract it's contents into the folder where you installed RPU in step 1 (should overwrite rpu.dat file)
https://drive.google.com/file/d/1CgCZjDh0H_zgLk0nQs9qLlUeaZ-zJPjK/view?usp=share_link

3) extract the contents of the archive into the game folder, overwriting files

4) edit ddraw.ini and change the following:
  a) Find DamageFormula and set it to 5 (to use YAAM)
DamageFormula=5

  b) Find and uncomment the following lines:
PerksFile=sfall\perks.ini
BooksFile=sfall\books.ini

5) start Fallout 2 and play

If you won't like the merchant prices or some other aspects, feel free to read and edit the barter.ini and combat.ini in mods folder as you like.


-=== DETAILS  (WARNING! SPOILERS!!!) ===-

> CRAFTING:
- New crafting system based on Mr.Fixit by Team-X and Fix-Boy by Lexx
- Custom crafting schematics designed to serve game's balance and add variaty, including new game items
- All "schematics" are divided into several categories, you need to find teacher for each category (there is no spoiler here, so try to
find them on your own. I will only say that most are found around northern half of the world...)
- Knowing schematics not enough: to start crafting you may also need skills, components and tools
- Some craftable food
- Crafting menu is accessible by clicking a new button on main panel or with a hotkey: Ctrl+F.

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
- parameters of all ammo types were carefully edited to fix vanilla issues and add choices
- AP/FMJ generally do less damage then JHP against unarmored, but is effective against armored targets (thanks to new damage script)
- Changed pack size of ammo to balance the total amount of that ammo in game, creating the need of purchase:
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
- new "calibers" and ammo types: .50 BMG (for AMR) and 40mm Grenade
- new ammo types for existing calibers: 12ga Slugs, 12ga Buckshot, .223AP, 14mm JHP (some craftable)


> FIREARMS:
- Shotgun Shells: much more deadly against unarmored critters, but cannot penetrate heavy armor and limited in range (but Slugs can!).
- Sawed off shotgun have a duplet (burst) firing mode with single shot animation.
- All "small" pistols cost 4 AP to shoot.
- Bozar changed to be a single-shot anti-materiel rifle, uses new .50 BMG ammo, need 7 STR and has very high damage. For machinegunning use LSW or M60 instead.
- Sniper Rifle is much more powerful, rechambered "back" to 7.62.
- M60 is a true machinegun: more powerful with 100 rounds ammo capacity.
- Bursts rebalanced to differ in bullet spread between weapon types (thanks to sfall). This makes certain guns work in new roles with effective mid-long range bursts. Expect guns that should have small recoil to do better at long-range bursts.
- Burst sizes were reduced across the board and rebalanced. This should make bursts viable with the added ammo scarcity.
- Almost every weapon was subjectively improved (main concerns were: more interesting balance between weapons, taking new ammo behaviour into account, BUT not going too far from vanilla stats, except those weapons mentioned specifically).


> NEW WEAPONS:
- Taser (stuns enemies from a short distance)
- 40mm grenade launchers (two types) with two types of grenades
- Late-game non-firearm weapons: one "unarmed", a sprear weapon, a sledge weapon, two throwing weapons
- A new craftable grenade


> ENERGY WEAPONS:
- Laser weapons are now very effective against everything below Combat/Metal Armor.
- "Real" Turbo Plasma rifle, costs 4 AP for shot (max damage reduced a bit).
- Strong single-shot energy weapons now spend more than 1 cell round for each shot.


> Some examples of ballance between some weapons of comparable class:
- 10mm Pistol vs 10mm SMG (for single shots): Pistol is faster (4AP) but has reduced range and slightly less damage
- .44 Magnum vs Desert Eagle: first has more power, second is more accurate and long-ranged
- 14mm Pistol does less damage than legendary .223 Pistol, but has more penetration
- Laser pistol and 14mm Pistol are comparable but Laser will better penetrate most armour types except metal armor. 14mm ammo is superb against any armor.
- Assault rifle vs FN FAL: high rate of fire (deadly at close and medium range) vs powerful 7.62x51 ammo (poor burst accuracy at long range, but better single shoot)
- HK CAWS vs Pancor Jackhammer: first has more range, fires 3-shot burst; second is low-range, uneconomical due to larger burst, but extremely deadly
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


-=== CREDITS ===-

mod was developed by phobos2077 between 2010 and 2023 (with years-long gaps)

additional dialogs, designs, flow fixes: Lujo
russian translators: Pyran, Drobovik, phobos2077, Frederika, PolarTulip

many thanks goes to following people, who made this mod possible:
- Magnus for WR mod that inspired me
- Nirran for the original Barter mod
- JimTheDinosaur for trap system inspiration
- Lexx for his Fix-Boy art and code
- Killap and RP team for the Restoration Project that gives something new to play in Fallout :)
- BGForgeNet team for carrying the torch of FO2 modding
- Timeslip for sfall and Script Editor, without which this mod wouldn't be possible
- NovaRain for his dedication to sfall and helping me get back on track
- Mr.Stalin for contributions to sfall and Proto Manager
- Cubik2k for F2wedit and FO 1/2 Critter proto editor
- vad for F12se - an invaluable mod testing/debugging tool
- PercivalCrump for another save editor with unique features
- Ziro for solid balance advice
- pelicano for his Party Orders addon
- Haenlomal for YAAM which was the basis for my balancing efforts
- people at NMA and Nuclear-City forums for useful comments
- Black Isle Studios for my favorite game of all time!


External art credits:
- Skipperino (DownloadFree3D.com, Low Poly Lever Action Rifle)
- "Grenade launcher - Milkor MGL" (https://skfb.ly/oESu8) by Valo is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).
- "MP9" (https://skfb.ly/ovNCI) by FranciscoRodriguez is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).
- Obsidian Entertainment
- Bethesda Game Studios


::O
