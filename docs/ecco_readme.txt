-====================-
-===   EcCo mod   ===-
-=== v0.9.6 BETA  ===-
-====================-
						by phobos2077


> CRAFTING:
- New crafting system based on Mr.Fixit by Team-X and Fix-Boy by Lexx with many improvements.
- Custom crafting schematics designed to serve game's balance and add variety, including new item types.
- Unlock crafting schematics by finding teachers, buying blueprints from traders, and other means.
- Knowing schematics is not enough: to start crafting you may also need skills, components and tools.
- Gain a little EXP for crafting a new item for the first time.
- Craftable food that heals a little, reduces negative effects and increases some stats.
- Crafting menu is accessible by clicking a new button on main panel or with a hotkey: Ctrl+C.
- New book for Doctor skill (required to craft drugs).


> TRAPS:
- To use traps you need to craft a Trap Kit first (need explosive schematics for mines and electronics for sensor mine).
- To place the trap on the ground, Use it from the inventory screen or from your active hand slot. You can also use hotkey Ctrl+4 if you have a trap kit in active hand.
- To actually arm the trap, use Traps skill on it.
- For mines: you can use any explosive from inventory on the floor trap tile; if you just use "Traps" skill on them, the game will first try to arm it with last used explosive type, and then with any explosive found in your inventory.
- You need to pass traps skill check to successfully arm the trap, if you are bad enough, you may end up blowing yourself. But if you're good, you'll have a chance of critical hit with your trap.
- You can dismantle any trap (both armament and trap kit will return to your inventory) just Using them or using Traps Skill on them.
- Some traps can be used several times (see number of remaining uses in trap description).
- Player and party members can't be hurt by your traps.
- Bear Trap can immobilize the enemy for several turns. He can still shoot you though!
- When using explosives, explosion damage is approximately equal to damage when using those items normally; damage type is also derived from item (EMP for Pulse grenade, Fire for Molotov, etc.).
- Some traps require the enemy to step on the exact tile of the trap, while others can trigger in a small radius.
- New book for Traps skill added.


> BARTER:
- Selling prices are affected by skill. (at lower levels prices may drop as low as 25% from their normal margin). This way, if you want to get rich by selling weapons, invest into Barter, or you'll need to sell many times more than before.
- Buying prices are comparable to base game, but have a steeper curve (slightly higher on low skill, lower on high skill) - see barter.ini or barter SSL code for detailed formula.
- Some misc items prices were adjusted, so you can still make profit selling them, especially in early game (gecko pelts and scorpion tails in Klamath, etc.).
- Some items have their prices differ between towns to simulate supply/demand differences.
- New book for Barter skill added.


> STEALING:
- Steal rolls calculation changed to make stealing harder but encourage investing into the skill.
- If Steal roll fails but Catch roll also fails - fails steal without getting caught instead of just succeeding, as in vanilla.
- Stealing now correctly uses number of items stolen when calculating difficulty.
- Stealing money and other weightless items now adds to difficulty based on cost.
- Karma penalty based on total value of goods being stolen.


> LOOTING:
- There is a chance a weapon will get destroyed when critter dies (except unique and rare weapons).
- Corpses are stripped from some percent of ammo and stimpaks, thus reducing abundance and incentivizing shopping.
- Loot slightly reduced/rearranged in various containers across the game, especially in certain underground facilities.
- NPCs will be more likely to detect if you're stealing from their property.
- EPA: room with most powerful stuff at security level will be harder to get in.
- Measures introduced to prevent trivial stealing from some places in Redding, New Reno and NCR.


> NEW QUEST CONTENT:
- Learning crafting recipes (see "crafting" section).
- One of the trappers in Klamath can now teach you gecko skinning (not free).
- Kill groups of robbers near Redding.
- Hunt down several rogues throughout the wastelend, one-by-one (NCR).
- Bring a number of hides to Modoc tannery.
- Bring a number of tentacles to NCR doctor.


> COMBAT:
- A couple of unspent AP points carry over to the next round. This should make low-AG builds more viable and make difference between weapon AP cost less dramatic.
- Opening inventory has no cost, but every action (except reload, see below) requires 2 AP (or 1 with Quick Pockets).
- Bonus Move perk is now available at level 3 (was 6) and grants 3 Move Points per level (was 2).
- Most "Melee" NPC's now get Bonus Move perk to close on their gun-wielding foes and make combat more dynamic.
- Enemy AI will now use aimed shots much more often.
- Critical hits to arms will sometimes make target drop their weapon.


> Healing:
- New healing system replaces the original to make First Aid & Doctor skills useful.
- First Aid Kits & Doctor Bags have limited uses (instead of random 10% removal).
- Much more HP is restored per skill use.
- Critical successes restore even more and crit chance depends heavily on skill level.
- Using kits & bags now has clear benefit: this ignores daily usage limits.
- To have more reason for using these skills, all passive healing was considerably nerfed (now it matches in-game Healing Rate description from vanilla).


> AMMO:
- Parameters of all ammo types were carefully edited to fix vanilla issues and add choices.
- AP/FMJ generally do less damage then JHP against unarmored, but is effective against armored targets (thanks to new damage script).
- Reduced pack sizes of certain ammo calibers to further balance the total amount of that ammo in game.
- Weight and cost was rebalanced as well.
- To further reduce "ammo swimming", all dying critters are stripped from some amount of ammo.
- Ammo now occupies space, so you cannot store unlimited ammo in car trunk (increased trunk capacity by 20% to balance that).
- New "calibers" and ammo types: .50 BMG (for AMR) and 40mm Grenade.
- New ammo types for existing calibers: 12ga Slugs, "special" 12ga ammo, .223AP, 7.62mm AP, 14mm JHP.


> GUNS:
- New guns for .44 Magnum and 14mm calibers to add variety and make these calibers feel "complete".
- Reload now costs 4 AP up from 2. This makes magazine capacity a much bigger factor.
- Shotgun Shells: much more deadly against unarmored critters, but cannot penetrate heavy armor and limited in range (but Slugs can!).
- Sawed off shotgun have a duplet (burst) firing mode with single shot animation and correct death animations.
- Some smaller pistols cost 4 AP to shoot to make them viable compared to "long" guns.
- Sniper Rifle is much more powerful, rechambered to 7.62.
- .223 Pistol is now unique, can only be found in one place.
- Bursts rebalanced to differ in bullet spread between weapon types (thanks to sfall). This makes certain guns work in new roles with effective mid-long range bursts. Expect guns that should have small recoil to do better at long-range bursts.
- Burst sizes were reduced across the board and rebalanced. This should make bursts viable with the added ammo scarcity.
- In critical bursts, only half of bullets will "inherit" the increased damage and penetration of the critical. This should balance against bursts being more "accurate".
- Better Scoped weapon aiming: penalty distance reduced (8 -> 6), perception mult increased (2.5x -> 3x)
- Almost every weapon was subjectively improved (main concerns were: more interesting balance between weapons, taking new ammo behavior into account, BUT not going too far from vanilla stats, except those weapons mentioned specifically).


> BIG GUNS:
- Two new 40mm Grenade weapons and a new flamethrower added to make Big Guns skill more useful in early-to-mid game.
- Bozar changed to be a single-shot anti-materiel rifle, uses new .50 BMG ammo, need 7 STR and has very high damage. For machinegunning use LSW or M60 instead.
- M60 is a true machine gun: more powerful with 100 rounds ammo capacity.
- ST now adds to base skill.


> ENERGY WEAPONS:
- New Taser Pistol to stun enemies and a new laser weapon for early/mid game will make this skill useful earlier.
- Laser weapons are now very effective against everything below Combat/Metal Armor.
- "Real" Turbo Plasma rifle, costs 4 AP for shot (max damage reduced a bit).
- Strong single-shot energy weapons now spend more than 1 cell round for each shot.


> THROWING:
- New grenade type that you can craft yourself, as well as recipe for Molotov will ensure weapon availability early.
- New, more powerful, melee thrown weapons for mid-game, including some that return to you after throw on successful skill roll.
- All thrown melee weapons now have a big critical chance and armor penetration boost.
- Melee Damage stat now also applies to thrown weapons, just like it does for Melee.
- Stats for thrown weapons were improved to make them more useful.
- Molotov Cocktail now inflicts fire damage and does not knock back targets.
- Increased damage by all grenades.
- EMP grenades now can temporarily disrupt power armors, forcing target to lose turn (also their radius was increased).


> MELEE & UNARMED:
- New weapons added (two "spear" type, one "knife", one "sledge") to fill the gaps in weapon progression for most weapon animation types.
- Thrust attacks now do better against armored enemies, but will cost 1 AP more than swings.
- The cost of unarmed special attacks has been lowered to 4 for punches and 5 for kicks (taken from Weapons Redone mod).
- Increased melee damage bonus for high ST characters
- Super sledge takes 4,5 AP instead of 3,4 (same as regular sledge).
- Wakizashi blade is much more powerful.
- Some melee oriented NPCs made more dangerous.


> ARMOR:
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
- Small changes which better integrate some content restored by RP. A few hooks for some content, a new scouting quest in Vault City, and adjustments to the Vault Village quest. (by Lujo)


> MERCHANTS:
- More crafting components sold at general stores.
- Cash tender in Redding now offers cash from 1000 to 7000 depending on player's current level.
- Changed some merchants stock to offer some new items and more ammo for purchase.


> RANDOM ENCOUNTERS:
- Weapon loadouts were adjusted in respect to new weapon balance.
- Most new weapons are used by people in the wasteland.
- Throwing weapons will be used against you more often.
- Ranged enemies will sure to have some spare ammo.


> MISC:
- Slightly nerfed car travel speed and fuel consumption upgrades to buff Outdoorsman skill and increase money sink.
- Small adjustments to base value formulas of some skills for better balance.
- Buffed some underused perks: Demolition Expert, Pyromaniac, Survivalist, MrFixit, Medic, Ghost, Ranger, Harmless, Salesman.
- Some mine traps in the game became more dangerous.
- Nerfed slot jinxer perk: slots break for month instead of 1 day, high rollers give 2/5 of initial money and there is a luck-based chance to fail. You can still become insanely rich by gambling.
- Nerfed gambling dice: you can win maximum about 1000-5000 caps per table, per week (that's still a LOT of money).
- Bonus Rate of Fire perk was removed (all pistols were completely OP if you take it, especially with the appropriate Trait).
- Hakunin dreams delayed, so they happen at more appropriate pace (RP has more content...).



-=== COMPATIBILITY ===-
Talking Heads Addon & Talking Heads Actually Talk (THAT):
- Full built-in support, no patches needed (if you previously used compatibility patches, DELETE them)

Inventory Filter (2.0.3+ from github):
- SmartBarter option seems to cause issues with barter, avoid!

FO2Tweaks:
- Don't use with default settings! Some of them has conflicts with EcCo features
- Disable the following (EcCo already includes similar changes):
molotov_fire=0
damage_mod=0

Companion Expansion:
- Has conflicts, mainly with the RPU/maps update that EcCo requires, needs a patch!



-=== CREDITS ===-

Mod was developed by phobos2077 between 2010 and 2024 (with years-long gaps).

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
