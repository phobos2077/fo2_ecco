#ifndef PBS_CRAFT_UTILS_H
#define PBS_CRAFT_UTILS_H

#include "../sfall/sfall.h"
#include "../sfall/lib.arrays.h"
//#include "../sfall/lib.strings.h"

#define skill_name(x)                   mstr_skill(100 + x)
#define critter_body_type(crit)        (proto_data(obj_pid(crit), cr_body_type))
#define critter_can_craft(crit)        (critter_body_type(crit) == CR_BODY_BIPED or critter_body_type(crit) == CR_BODY_ROBOTIC)
#define PARTY_DONATE_MAX_DIST          30

pure procedure check_skill_sum(variable crit, variable skills) begin
   variable
      total := 0,
      numSkills := len_array(skills) - 1,
      i;

   for (i := 0; i < numSkills; i++) begin
      total += has_skill(crit, skills[i]);
   end
   return 1 if total >= skills[numSkills] else -total;
end

procedure get_party_member_with_skill(variable skills) begin
   variable ret := 0;
   variable obj;
   //craft_debug("search skill "+debug_array_str(skills)+" at least " + level);
   foreach (obj in party_member_list_critters) begin
      if (obj and critter_can_craft(obj) and check_skill_sum(obj, skills) > 0) then begin
         ret := obj_name(obj);// proto_data(obj_pid, cr_name)
      end
   end
   return ret;
end

pure procedure skill_names(variable skills) begin
   variable
      str := "", numSkills := len_array(skills) - 1,
      i;
   for (i := 0; i < numSkills; i++) begin
      if (i > 0) then str += " + ";
      str += skill_name(skills[i]);
   end
   return str;
end

procedure recipe_max_average_skill(variable recipe) begin
   variable list, skill, skillAvg, numSkills, i,
      maxAvg := 0;
   if (len_array(recipe.skills) > 0) then foreach (list in (recipe.skills)) begin
      numSkills := len_array(list) - 1;
      if (numSkills >= 1) then begin
         skillAvg := list[numSkills] / numSkills;
         if (skillAvg > maxAvg) then
            maxAvg = skillAvg;
      end
   end
   return maxAvg;
end

procedure obj_name_proc(variable obj) begin
   return obj_name(obj) if obj else "(null)";
end

#define ammo_pid_pack_size(pid)                           get_proto_data(pid, PROTO_AM_PACK_SIZE)
#define actual_ammo_count(inven, item, packSize)          (obj_is_carrying_obj(inven, item) - 1) * packSize + get_weapon_ammo_count(item)
#define item_pid_pack_size(pid)                           (ammo_pid_pack_size(pid) if (proto_data(pid, it_type) == item_type_ammo) else 1)

procedure obj_is_carrying_bullets_pid(variable invenObj, variable pid) begin
   variable
      i := 0,
      numBullets := 0,
      packSize := ammo_pid_pack_size(pid),
      item := inven_ptr(invenObj, 0);

   while (item) do begin
      if (obj_pid(item) == pid) then begin
         numBullets += actual_ammo_count(invenObj, item, packSize);
      end
      i += 1;
      item := inven_ptr(invenObj, i);
   end
   return numBullets;
end

procedure remove_bullets_pid(variable invenObj, variable pid, variable quantity) begin
   variable
      toRemove := quantity,
      packSize,
      item := obj_carrying_pid_obj(invenObj, pid),
      i, numPacks, numInTop, numInStack, rmvd, newPacks, newInTop, newInStack;

   if (item == 0) then return 0;

   packSize := ammo_pid_pack_size(pid);
   numPacks := obj_is_carrying_obj(invenObj, item);
   numInTop := get_weapon_ammo_count(item);
   numInStack := (numPacks - 1) * packSize + numInTop;
   craft_debug(string_format("remove_bullets_pid(%s, %s, %d): found %d bullets.", obj_name(invenObj), proto_data(pid, it_name), quantity, numInStack));

   newInStack := numInStack - toRemove;  // numInStack - math_min(toRemove, numInStack);
   if (newInStack < 0) then newInStack := 0;

   newInTop := newInStack % packSize;
   newPacks := newInStack / packSize;
   if (newInTop == 0) then
      newInTop := packSize;
   else
      newPacks += 1;

   if (newPacks < numPacks) then begin
      rmvd := rm_mult_objs_from_inven(invenObj, item, numPacks - newPacks);
      destroy_object(item);
      craft_debug(string_format("remove_bullets_pid: reduced item count: %d - %d = %d", numPacks, rmvd, numPacks - rmvd));
   end
   if (newPacks > 0) then begin
      item := obj_carrying_pid_obj(invenObj, pid);
      set_weapon_ammo_count(item, newInTop);
      craft_debug(string_format("remove_bullets_pid: set top count: %d -> %d", numInTop, newInTop));
   end
   return (numInStack - newInStack);
end

procedure party_member_can_donate_items(variable obj) begin
   return obj == dude_obj
      or (obj
         and obj_is_visible_flag(obj)
         and elevation(obj) == elevation(dude_obj)
         and tile_distance_objs(dude_obj, obj) <= PARTY_DONATE_MAX_DIST);
end

procedure party_is_carrying_obj_pid(variable pid, variable returnAmmoCount := false) begin
   variable
      sum := 0,
      isAmmo := proto_data(pid, it_type) == item_type_ammo,
      obj, num;

   foreach (obj in party_member_list_all) begin
      if (party_member_can_donate_items(obj)) then begin
         num := obj_is_carrying_bullets_pid(obj, pid) if isAmmo else obj_is_carrying_obj_pid(obj, pid);
         if (num > 0) then begin
            craft_debug(string_format("party_is_carrying_obj_pid(%s): %s has %d", proto_data(pid, it_name), obj_name_proc(obj), num));
            sum += num;
         end
      end
   end
   craft_debug(string_format("party_is_carrying_obj_pid(%s): sum = %d", proto_data(pid, it_name), sum));
   // For ammo, we calculate sum in individual bullets but return a number of *full* packs (as if ammo is combined in one inventory)
   if (sum > 0 and isAmmo and (not returnAmmoCount)) then
      sum := sum / ammo_pid_pack_size(pid);
   return sum;
end

// Remove given number of items from party, starting with closest members to the player
procedure party_remove_items_pid(variable pid, variable quantity) begin
   variable
      partyDistMap := temp_array_map,
      isAmmo := proto_data(pid, it_type) == item_type_ammo,
      toRemove := quantity * (ammo_pid_pack_size(pid) if isAmmo else 1),
      obj, d, rmvd;
   
   craft_debug("party_remove_items_pid(" + proto_data(pid, it_name) + ",  " + quantity + ")");
   foreach (obj in party_member_list_all) begin
      if (party_member_can_donate_items(obj)) then begin
         partyDistMap[obj] := tile_distance_objs(dude_obj, obj) + 1; // +1 to avoid 0-unset behavior
      end
   end
   sort_map_value(partyDistMap);
   //craft_debug("sorted party: " + debug_array_str(array_transform(array_keys(partyDistMap), @obj_name_proc)));
   foreach (obj: d in partyDistMap) begin
      rmvd := remove_bullets_pid(obj, pid, toRemove) if isAmmo else remove_items_pid(obj, pid, toRemove);
      if (rmvd > 0) then
         craft_debug(string_format("party_remove_items_pid: removed %d from %s (dist: %d)", rmvd, obj_name_proc(obj), d));
      toRemove -= rmvd;
      if (toRemove <= 0) then break;
   end
   rmvd := quantity - toRemove;
   // For ammo, we removed based on individual bullets, so return a number of full stacks removed
   if (rmvd > 0 and isAmmo) then
      rmvd := rmvd / ammo_pid_pack_size(pid);
   return rmvd;
end

#endif // PBS_CRAFT_UTILS_H
