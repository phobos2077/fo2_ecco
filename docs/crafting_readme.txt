Crafting system in EcCo is made completely independent from the rest of the mod. 
It is fully configurable and only requires a fairly recent version of sfall.

All recipes and general settings are configured in data/config/pbs_craft.ini (description for every setting and recipe examples included).
All custom art is in data/pcx folder. You can change it however you need as long as you don't change image sizes.

You can choose to use recipe categories, if you have many recipes.
You can use sfall global vars to unlock certain recipes (they will only show if given gvar value is non 0).
If gvar value is a number - it will be automatically treated as a regular Fallout global var.

You can use schematics system to easily add new unlockable recipes to the game:
- Set schema=1 for a recipe.
- Designate a certain set of items as a "schematics" and list them in [Main].schematic_pids
- Open a script that will spawn a schematic item (such as shop stock box) and include "craft_schematics.h".
- Call check_restock_craft_schematic to spawn a schematic item, see comment for details.
