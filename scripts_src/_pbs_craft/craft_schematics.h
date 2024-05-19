#ifndef PBS_CRAFT_SCHEMATICS_H
#define PBS_CRAFT_SCHEMATICS_H

#include "../sfall/lib.inven.h"

#define item_schematic_sgvar(craftedPid)     sprintf("CRFT%04d", craftedPid)

procedure check_restock_craft_schematic(variable schematicPid, variable craftedItemPid, variable probability := 100) begin
   variable item, isKnown;
   isKnown := (get_sfall_global_int(item_schematic_sgvar(craftedItemPid)) > 0);

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
