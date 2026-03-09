-====================-
-===   EcCo Lite  ===-
-===     v 0.9.9  ===-
-====================-
                  a Fallout 2 mod
						by phobos2077


Based on EcCo: RP, EcCo Lite, as the name suggests, is a cut-down version of the original mod without all the game content changes.
This version of the mod is not tied to Restoration Project or any other Total Conversion and only requires sfall.
Players are encouraged to dive into various ini files (located in `ecco_config` folder) and tinker with them for their own liking, based on the game they're playing.
Although not yet tested, this version *should* work with any Fallout 2 TC, such as EtTu, Resurrection, Nevada, Sonora, etc. with minimal ini tweaks.
Official ini tweak sets for each of those popular mods might come later as I get the chance to test them myself.


Following is the list of optional features included in EcCo Lite.

Important notes:
   - Some of the features from the full mod were disable or toned down by default, but you can enable and tweak them.
   - ALL of these changes are optional and can be disabled or tweaked in the ini files.


> BARTER & ECONOMY:
- Value of items sold to NPC's is affected by skill and generally lower until you get Barter skill high enough.
- Buy/sell ratio differs between item categories. For example, NPC's will offer less for weapons and armor (vs asking price), to balance against the abundance/high price of these loot items.
- Buying prices have a steeper curve to increase the importance of Barter skill (slightly higher on low skill, lower on high skill) - see barter.ini or barter SSL code for detailed formula.


> STEALING:
- Steal rolls calculation changed to make stealing harder but encourage investing into the skill.
- If Steal roll fails but Catch roll also fails - fails steal without getting caught instead of just succeeding, as in vanilla.
- Stealing now correctly uses number of items stolen when calculating difficulty.
- Stealing money and other weightless items now adds to difficulty based on cost.
- [disabled] Town Reputation penalty based on total value of goods being stolen.


> LOOTING:
- [disabled] There is a chance a weapon will get destroyed when critter dies.
- [disabled] Corpses and containers are stripped from some percent of ammo and stimpaks, thus reducing abundance and incentivizing shopping.


> COMBAT:
- A couple of unspent AP points carry over to the next round. This should make low-AG builds more viable and make difference between weapon AP cost less dramatic.
- Opening inventory has no cost, but every action (except reload, see below) requires 2 AP (or 1 with Quick Pockets).
- All two-handed ranged weapons have a hit chance penalty at point-blank range.
- [disabled] Enemy AI will now use aimed shots much more often.
- Critical hits to arms will sometimes make target drop their weapon.
- Bonus Move perk now grants 3 Move Points per level (was 2).
- Most "Melee" NPC's now get Bonus Move perk to close on their gun-wielding foes and make combat more dynamic.


> HEALING:
- New skill healing system replaces the original to make First Aid & Doctor skills useful.
- First Aid Kits & Doctor Bags have limited uses (instead of random 10% removal).
- Much more HP is restored per skill use.
- Critical successes restore even more and crit chance depends heavily on skill level.
- Using kits & bags now has clear benefit: this ignores daily usage limits.
- [disabled] All passive healing was considerably nerfed to motivate more interesting healing options.
- Stimpak/Healing Powder HP gain amount scales with your First Aid skill.


> AMMO:
- A new damage calculation script is included. Almost the same as vanilla, it fixes the issue of ammo types not reducing DT in addition to DR.
- Some dying critters have reduced ammo.


> GUNS:
- Reload now costs 4 AP up from 2. This makes magazine capacity a much bigger factor.
- [disabled] Bursts rebalanced to differ in bullet spread between weapon types. This makes certain guns work in new roles with effective mid-long range bursts.
- In critical bursts, only a portion of bullets will "inherit" the increased damage and penetration of the critical. This should balance against bursts being more "accurate".


> ENERGY WEAPONS:
- Strong single-shot energy weapons now spend more than 1 cell round for each shot.


> THROWING:
- All thrown melee weapons now have a big critical chance and armor penetration boost.
- Melee Damage stat now also applies to thrown weapons, just like it does for Melee.
- Molotov Cocktail now inflicts fire damage and does not knock back targets.


> MELEE & UNARMED:
- Fatal attacks with melee/unarmed will now trigger gory death animations, similar to ranged weapons.
- Thrust attacks now do better against armored enemies, but will cost 1 AP more than swings.
- The cost of unarmed special attacks has been lowered to 4 for punches and 5 for kicks (taken from Weapons Redone mod).
- Increased melee damage bonus for high ST characters


> SOUND EFFECTS:
- Previously unused vanilla weapon sound effect variations are now unlocked.


-=== INSTALLATION (ZIP) ===-
1. Make sure sfall 4.4.9 or higher is installed (https://sourceforge.net/projects/sfall/).
2. Run the game at least once after sfall is installed.
3. Unpack zip contents into the game root folder, overwriting files.
4. Open <game_root>\mods\mods_order.txt and add a new line "ecco_lite" (without quotes)
5. If you want to use EcCo damage formula, open ddraw.ini and find/change the following options in the [Misc] section:

DamageFormula=0


-=== COMPATIBILITY ===-
Inventory Filter (2.0.3+ from github):
- SmartBarter option seems to cause issues with barter, avoid!

FO2Tweaks:
- Don't use with default settings! Some of them has conflicts with EcCo features
- Disable the following (EcCo already includes similar changes):
max_knockback=-1
healing_revision=0
molotov_fire=0
damage_mod=0
ap_rollover=0

