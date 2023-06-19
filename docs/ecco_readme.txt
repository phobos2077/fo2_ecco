-====================-
-===   EcCo mod   ===-
-=== v0.9.1 BETA  ===-
-====================-
						by phobos2077


> CRAFTING:
- New crafting system based on Mr.Fixit by Team-X and Fix-Boy by Lexx.
- Custom crafting schematics designed to serve game's balance and add variety, including new game items.
- All "schematics" are divided into several categories, you need to find teacher for each category.
- Knowing schematics is not enough: to start crafting you may also need skills, components and tools.
- Some craftable food.
- Crafting menu is accessible by clicking a new button on main panel or with a hotkey: Ctrl+F.


> TRAPS:
- To use traps you need to craft a Trap Kit first (need explosive schematics for mines and electronics for sensor mine).
- To place the trap on the ground, put it in your active hand slot and use it ON your character (or just press Ctrl+1 hotkey).
- To actually arm the trap, use Traps skill on it.
- For mines: you can use any explosive from inventory on the floor trap tile; if you just use "Traps" skill on them, the game will first try to arm it with last used explosive type, and then with any explosive found in your inventory.
- You need to pass traps skill check to successfully arm the trap, if you are bad enough, you may end up blowing yourself.
- You can dismantle any trap (both armament and trap kit will return to your inventory) just Using them or using Traps Skill on them.
- Spike traps can be used a couple of times (it loses one "charge" when someone steps on it).
- Player and party members can't be hurt by your traps.
- When using spike traps, damage formula is: 7-14 (when traps skill is 0~40), max damage is increased up to 40, by 1 for each 3 skill points (7-40 at 120% skill).
- When using explosives, explosion damage is approximately equal to damage when using those items normally; damage type is also derived from item (EMP for Pulse grenade, Fire for Molotov, etc.).
- Sensor mines detect movement on 1 tile radius. If critter passes just near the trap and don't step on it, there is a very small chance trap won't go off.
- New book for Traps skill added.


> BARTER:
- Selling prices are affected by skill. (at lower levels prices may drop as low as 25% from their normal margin). This way, if you want to get rich by selling weapons, upgrade your Barter, or you'll need to sell many times more than before.
- Buying prices are comparable to base game, but have a steeper curve (slightly higher on low skill, lower on high skill) - see barter.ini or barter SSL code for detailed formula.
- Some misc items prices were adjusted, so you can still make profit selling them, especially in early game (gecko pelts and scorpion tails in Klamath, etc.).
- New book for Barter skill added.


> LOOT REDUCTION:
- There is a chance a weapon will get destroyed when critter dies (except unique and rare weapons).
- Corpses are stripped from some percent of ammo and stimpaks, thus reducing abundance and incentivizing shopping.
- Loot slightly reduced in S.A.D, Hubologist Stash, Toxic Caves.
- EPA: loot rearranged/reduced somewhat; room with most powerful stuff at security level will be harder to get in.
- It is harder to steal from Redding doctor now.
- Closed rooms in Bishop club are harder to get in.


> NEW QUEST CONTENT:
- Craft learning (see "crafting" section).
- One of the trappers in Klamath can now teach you gecko skinning (not free).
- Kill groups of robbers near Redding.
- Hunt down several rogues throughout the wastelend, one-by-one (NCR).
- Bring a number of hides to Modoc tannery.
- Bring a number of tentacles to NCR doctor.


> COMBAT:
- A couple of unspent AP points carry over to the next round.
- Opening inventory has no cost, but every action requires 2 AP (except reload, see below).
- All characters now get a bonus move points (not AP!) for every AG point above 5. Double for NPCs. This should allow melee characters to close on their gun-wielding foes and make combat more dynamic.


> AMMO:
- Parameters of all ammo types were carefully edited to fix vanilla issues and add choices.
- AP/FMJ generally do less damage then JHP against unarmored, but is effective against armored targets (thanks to new damage script).
- Reduced pack sizes of certain ammo calibers to further balance the total amount of that ammo in game.
- Weight and cost was rebalanced as well.
- To further reduce "ammo swimming", all dying critters are stripped from some amount of ammo (optional), see MISC section.
- Ammo now occupies space, so you cannot store unlimited ammo in car trunk (increased trunk capacity by 20% to balance that).
- New "calibers" and ammo types: .50 BMG (for AMR) and 40mm Grenade.
- New ammo types for existing calibers: 12ga Slugs, "special" 12ga ammo, .223AP, 7.62mm AP, 14mm JHP.


> NEW WEAPONS:
- Taser (stuns enemies from a short distance)
- one .44 Magnum weapon
- one 14mm automatic weapon
- 40mm grenade launchers (two types) with two types of grenades
- Late-game non-firearm weapons: one "unarmed", a spear weapon, a sledge weapon, two throwing weapons
- A new craftable grenade


> GUNS:
- New gun for .44 Magnum and 14mm calibers to add variety and make these calibers feel "complete".
- Reload now costs 4 AP up from 2. This makes magazine capacity a much bigger factor.
- Shotgun Shells: much more deadly against unarmored critters, but cannot penetrate heavy armor and limited in range (but Slugs can!).
- Sawed off shotgun have a duplet (burst) firing mode with single shot animation and correct death animations.
- Some smaller pistols cost 4 AP to shoot to make them viable compared to "long" guns.
- Sniper Rifle is much more powerful, rechambered to 7.62.
- .223 Pistol is now unique, can only be found in one place.
- Bursts rebalanced to differ in bullet spread between weapon types (thanks to sfall). This makes certain guns work in new roles with effective mid-long range bursts. Expect guns that should have small recoil to do better at long-range bursts.
- Burst sizes were reduced across the board and rebalanced. This should make bursts viable with the added ammo scarcity.
- In critical bursts, only half of bullets will "inherit" the increased damage and penetration of the critical. This should balance against bursts being more "accurate".
- Almost every weapon was subjectively improved (main concerns were: more interesting balance between weapons, taking new ammo behavior into account, BUT not going too far from vanilla stats, except those weapons mentioned specifically).


> BIG GUNS:
- Two new 40mm Grenade weapons added to make Big Guns skill more useful in early-to-mid game.
- Bozar changed to be a single-shot anti-materiel rifle, uses new .50 BMG ammo, need 7 STR and has very high damage. For machinegunning use LSW or M60 instead.
- M60 is a true machine gun: more powerful with 100 rounds ammo capacity.
- ST now adds to base skill


> ENERGY WEAPONS:
- Taser to stun enemies.
- Laser weapons are now very effective against everything below Combat/Metal Armor.
- "Real" Turbo Plasma rifle, costs 4 AP for shot (max damage reduced a bit).
- Strong single-shot energy weapons now spend more than 1 cell round for each shot.


> THROWING:
- All throwing non-explosive weapons now have a big critical chance boost.
- Stats for throwing weapons were improved to make them more useful.
- New, more powerful, non-explosive throwing weapons for mid-game.
- Molotov Cocktail now inflicts fire damage and does not knock back targets.
- Increased damage by all grenades.
- EMP grenades now can temporarily disrupt power armors, forcing target to lose turn (also their radius was increased).


> MELEE & UNARMED:
- Thrust attacks now do better against armored enemies, but will cost 1 AP more than swings.
- The cost of unarmed special attacks has been lowered to 4 for punches and 5 for kicks (taken from Weapons Redone mod).
- Increased melee damage bonus for high ST characters
- Super sledge takes 4,5 AP instead of 3,4 (same as regular sledge).
- Wakizashi blade is much more powerful.
- New weapons: one spear and one sledge type.
- Some melee oriented NPCs made more dangerous.


> ARMOR:
- Base AC is now = AG * 1.5 (was AG * 1, applies to all critters)
- Armor Class lowered for heavy armor (metal and power). AC only affects hit chance, so it makes sense bigger/bulkier target is easier to hit.
- Laser resistance changed: leather - zero protection, combat - mediocre, metal - good, power armor & tesla - great protection.
- Explosion and Fire resistance slightly lowered for some armor.
- All changes to armor are applied to all critters wielding that armor.


> CRITTERS:
- Some "lesser" critters made tougher: Tough Giant Ant, Large radscorpion, Deathclaws, Mole Rat. (they are rare on early maps and were way too weak).
- New monster parts can be harvested from critters for profit: Deathclaws, Mole Rats, Wanamingos, mutants.


> QUESTS and NPCs:
- Lidya in VC rewards 500 for shipment of alcohol (was 300).
- Better reward for VC plow quest.
- Algernon need rest after work.
- Trappers in random encounters now sell pelts through standard barter dialog only, but with high discount.
- Small changes which better integrate some content restored by RP. A few hooks for some content, a new scouting quest in Vault City, and adjustments to the Vault Village quest. (by Lujo)


> MERCHANTS:
- More crafting components (mainly junk) sold at general stores.
- Cash tender in Redding now offers cash from 1000 to 7000 depending on player's current level.
- Changed some merchants stock to offer some new items and more ammo for purchase.


> RANDOM ENCOUNTERS:
- Weapon loadouts were adjusted in respect to new weapon balance.
- Most new weapons are used by people in the wasteland.
- Throwing weapons will be used against you more often.


> MISC:
- Small adjustments to base value formulas of some skills for better balance
- Some mine traps in the game became more dangerous.
- Nerfed slot jinxer perk: slots break for month instead of 1 day, high rollers give 2/5 of initial money and there is a luck-based chance to fail. You can still become insanely rich by gambling.
- Nerfed gambling dice: you can win maximum about 1000-5000 caps per table, per week (that's still a LOT of money).
- People drop their weapon to the ground in front of them when they die.
- Bonus Rate of Fire perk was removed (all pistols were completely OP if you take it, especially with the appropriate Trait).
- Hakunin dreams delayed, so they happen at more appropriate pace (RP has more content...).



-=== COMPATIBILITY ===-
Talking Heads Addon & Talking Heads Actually Talk (THAT):
- Full built-in support, no patches needed (if you previously used compatibility patches, DELETE them)

Inventory Filter (2.0.2 from github):
- SmartBarter option seems to cause issues with barter, avoid!

FO2Tweaks:
- Don't use with default settings! Some of them has conflicts with EcCo features
- Disable the following (EcCo already includes similar changes):
molotov_fire=0
damage_mod=0



-=== CREDITS ===-

Mod was developed by phobos2077 between 2010 and 2023 (with years-long gaps).

Additional dialogs, designs, flow fixes: Lujo.
Russian translators: Pyran, Drobovik, phobos2077, Frederika, PolarTulip.

Many thanks to following people, who made this mod possible:
- Magnus for Weapons Redone mod that inspired me
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
- Haenlomal, Glovz and Burn for their damage formulas that inspired me to make my own
- people at NMA and Nuclear-City forums for useful comments
- Black Isle Studios (R.I.P.) for my favorite game of all time!


External art credits:
- Skipperino (DownloadFree3D.com, Low Poly Lever Action Rifle)
- "Grenade launcher - Milkor MGL" (https://skfb.ly/oESu8) by Valo is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).
- "MP9" (https://skfb.ly/ovNCI) by FranciscoRodriguez is licensed under Creative Commons Attribution (http://creativecommons.org/licenses/by/4.0/).
- Obsidian Entertainment
- Bethesda Game Studios


::O
