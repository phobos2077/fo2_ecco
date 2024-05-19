#ifndef PBS_CRAFT_SCHEMATICS_H
#define PBS_CRAFT_SCHEMATICS_H

#include "../sfall/lib.arrays.h"
#include "../sfall/lib.inven.h"

#define ARR_SCHEMAS             "pbs_craft_schemas"

variable
   craft_schemas_map;

procedure get_craft_schemas begin
   if (not craft_schemas_map) then
      craft_schemas_map := load_create_array_map(ARR_SCHEMAS);
   return craft_schemas_map;
end

#define schema_is_known(id)        get_array(get_craft_schemas, id)
#define schema_set_as_known(id)    set_array(get_craft_schemas, id, 1)

/**
 * Adds one recipe item for a given crafted item, if it doesn't exist. If recipe is known, deletes the item.
 */
procedure check_restock_craft_schematic(variable schematicPid, variable craftedItemPid, variable probability := 100) begin
   variable item, isKnown;
   isKnown := schema_is_known(craftedItemPid);

   foreach (item in (inven_as_array(self_obj))) begin
      if (obj_pid(item) == schematicPid andAlso get_weapon_ammo_count(item) == craftedItemPid) then begin // already in stock
         if (isKnown) then begin // if known - remove from stock
            rm_obj_from_inven(self_obj, item);
            destroy_object(item);
         end else
            return;
      end
   end

   if (isKnown or random(1, 100) > probability) then return;

   display_msg("spawning " + schematicPid);
   item := create_object(schematicPid, 0, 0);
   set_weapon_ammo_count(item, craftedItemPid); // set count before adding to prevent stacking
   add_obj_to_inven(self_obj, item);
end

#endif
