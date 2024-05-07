#ifndef PBS_CRAFT_UTILS_H
#define PBS_CRAFT_UTILS_H

#include "../sfall/sfall.h"
#include "../sfall/lib.arrays.h"
//#include "../sfall/lib.strings.h"

#define skill_name(x)                   mstr_skill(100 + x)
#define critter_body_type(crit)        (proto_data(obj_pid(crit), cr_body_type))
#define critter_can_craft(crit)        (critter_body_type(crit) == CR_BODY_BIPED or critter_body_type(crit) == CR_BODY_ROBOTIC)

pure procedure check_skill_sum(variable crit, variable skills) begin
   variable
      total := 0,
      numSkills := len_array(skills) - 1,
      i;

   for (i := 0; i < numSkills; i++) begin
      total += has_skill(crit, skills[i]);
   end
   return total >= skills[numSkills];
end

procedure get_party_member_with_skill(variable skills) begin
   variable ret := 0;
   variable obj;
   //craft_debug("search skill "+debug_array_str(skills)+" at least " + level);
   foreach (obj in party_member_list_critters) begin
      if (obj and critter_can_craft(obj) and check_skill_sum(obj, skills)) then begin
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

procedure obj_name_proc(variable obj) begin
   return obj_name(obj) if obj else "(null)";
end

procedure party_is_carrying_obj_pid(variable pid) begin
   variable sum := 0;
   variable obj, num;
   foreach (obj in party_member_list_all) begin
      if (obj and obj_is_visible_flag(obj)) then begin
         num := obj_is_carrying_obj_pid(obj, pid);
         if (num > 0) then
            craft_debug(string_format("party_is_carrying_obj_pid(%s): %s has %d", proto_data(pid, it_name), obj_name_proc(obj), num));
         sum += num;
      end
   end
   craft_debug(string_format("party_is_carrying_obj_pid(%s): sum = %d", proto_data(pid, it_name), sum));
   return sum;
end

// Remove given number of items from party, starting with closest members to the player
procedure party_remove_items_pid(variable pid, variable quantity) begin
   variable
      toRemove := quantity,
      partyDistMap := temp_array_map,
      obj, d, rmvd;
   
   craft_debug("party_remove_items_pid(" + proto_data(pid, it_name) + ",  " + quantity + ")");
   foreach (obj in party_member_list_all) begin
      if (obj and obj_is_visible_flag(obj)) then begin
         partyDistMap[obj] := tile_distance_objs(dude_obj, obj) + 1; // +1 to avoid 0-unset behavior
      end
   end
   sort_map_value(partyDistMap);
   //craft_debug("sorted party: " + debug_array_str(array_transform(array_keys(partyDistMap), @obj_name_proc)));
   foreach (obj: d in partyDistMap) begin
      rmvd := remove_items_pid(obj, pid, toRemove);
      if (rmvd > 0) then
         craft_debug(string_format("party_remove_items_pid: removed %d from %s (dist: %d)", rmvd, obj_name_proc(obj), d));
      toRemove -= rmvd;
      if (toRemove <= 0) then break;
   end
   return quantity - toRemove;
end

#endif // PBS_CRAFT_UTILS_H
