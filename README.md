# EcCo Gameplay Overhaul

A mod for Fallout 2 [Restoration Project Updated](https://github.com/BGforgeNet/Fallout2_Restoration_Project).

By phobos2077

---


## Vision

In short, this is a conservative gameplay overhaul.

Design goals:
- make more skills useful, to make non-standard builds more viable (Barter, Throwing, Melee, Repair, etc.)
- add a little more challenge to the combat, barter and other aspects of the game, without any "hardcore"
- make most weapons and other items in the game have a purpose
- keep things configurable and modular, so the players can tweak mod to their liking and mod authors can re-use parts of it in their own creations
- attempt to fix balance issues introduced by RP (more "free" loot, much more EXP, etc.) as well as original game
- stay true to the original game mechanics and design as much as possibly, always try to improve when possible, not reinvent


## Main Highlights

**Combat**:
- rebalanced weapons and adjusted their distribution to make most of them have good use cases
- added a few new guns to "fill" certain voids, like .44 and 14 mm calibers having too short "life"
- automatic weapons further diversified by varying bullet dispersion
- ammo types matter with more to choose from and AP made useful thanks to improved damage formula
- energy weapons made more effective against lesser armors, and laser weapons made more powerful
- melee is more viable mid-game for player as well as NPCs thanks to new more powerful melee weapons, more move points and rebalanced stats
- throwing weapons expanded and made more useful with critical chance bonus for blades, much deadlier grenades and new types to choose from
- improved stats of several critters (like weak types of Deathclaws, large scorpions, etc.)
- new stealth elements: blackjack and sneak attack
- "fair" inventory management in combat - no cost to open, 2 AP per action, 4 AP to reload (mag sizes matter now)

**Economy**:
- prices in stores are affected stronger by Barter skill increases at lower levels and less at higher levels
- selling prices now also depend on Barter skill (instead of always being at 100%)
- some items vary in prices between towns, so you can trade for profit with enough skill
- raise money by selling new types of monster parts or by doing several new quests (see details)
- reduced and made harder to get some overpowered loot in several locations
- ammo, drugs and weapon abundance from fallen foes reduced

**Progression**:
- several small adjustments to quest flow to integrate content from Restoration Project better into the game
- some gangs made tougher (Metzger, Salvatore, Vault 15 raiders)
- redesigned entrances to the Raiders hideout for more challenge and variety
- reduced unbalanced EXP rewards for several quests
- reduced experience when killing the same critter type many times

**Crafting System**:
- craft various items: weapons, ammo, drugs, armor
- available via a new interface button or a via hotkey
- unlock new items by finding crafting teachers across the game

**Traps System**:
- installable traps: "melee" type spike trap, explosive mine and sensor mine
- explosive traps are customized by arming them with any type of explosives or grenades
- become a trapper by luring geckos and rats into your traps using food as bait!

**New Quests**:
- a couple of random-encounter-based "Bounty Hunt" quests
- a couple of fetch quests involving new monster/animal parts

For a detailed description of all features, see [full readme](https://github.com/phobos2077/fo2_ecco/blob/master/docs/ecco_readme.txt).

## COMPATIBILITY

ONLY installable above the Restoration Project Update v27 (with updated maps from Pixote)
Following RP options **_MUST_** be installed:
- New weapon animations (all of them)

Start of a new game is not required, but is **highly** recommended.

[sfall](https://github.com/sfall-team/sfall) **v4.3.9** or higher is required!

## INSTALLATION

1. Install RPU v26 on a clean game installation (installer version is recommended):
- **IMPORTANT**: install Rifle Animations and Wakizashi Animations mods!
https://github.com/BGforgeNet/Fallout2_Restoration_Project/releases/tag/v26

2. Download the archive and extract its contents into the folder where you installed RPU in step 1, overwriting any files.
https://drive.google.com/file/d/1We_IETFZpbLh4ndGvHvMu0qrCtuFCOQH/view?usp=sharing

3. Download the latest ecco_**.zip archive from [releases page](https://github.com/phobos2077/fo2_ecco/releases) and extract the contents into the game folder, overwriting files.

4. Edit ddraw.ini, find keys listed below, uncomment them if they are commented (with a semicolon) and change values as follows:
```
DamageFormula=0

ObjCanHearObjFix=1

DerivedStats=sfall\stats.ini
PerksFile=sfall\perks.ini
BooksFile=sfall\books.ini

MovieTimer_artimer1=120
MovieTimer_artimer2=235
MovieTimer_artimer3=350
MovieTimer_artimer4=470

```

5. Start Fallout 2 and enjoy your game!


If you don't like any changes to mechanics or some other aspects, feel free to read and edit the INI files in the mods/ecco folder.
