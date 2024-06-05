#ifndef PBS_LOOT_UTILS_H
#define PBS_LOOT_UTILS_H


#include "../sfall/lib.arrays.h"
#include "../sfall/lib.inven.h"

#include "../_pbs_headers/math_ext.h"
#include "../_pbs_headers/ecco_log.h"


procedure reduce_item_count(variable invenObj, variable item, variable newCount) begin
   variable count := obj_is_carrying_obj(invenObj, item);
   if (newCount >= count) then return;

   count := rm_mult_objs_from_inven(invenObj, item, count - newCount);
   destroy_object(item);
end

#define calc_reduced_ammo_range(count, percentRange)        math_round_chance(count * (100 - random(percentRange[0], percentRange[1])) / 100.0)

/**
 * Reduces number of individual bullets in an ammo stack by a percentage range.
 * @arg {ObjectPtr} invenObj - Container or critter
 * @arg {ObjectPtr} item - item stack object
 * @arg {list} percentRange - [min, max] range of % to remove
 * @ret {string}
 */
procedure reduce_ammo_in_stack(variable invenObj, variable item, variable percentRange) begin
   if (percentRange[1] <= 0) then return "";

   variable
      pid := obj_pid(item),
      packSize := get_proto_data(pid, PROTO_AM_PACK_SIZE),
      count := (obj_is_carrying_obj(invenObj, item) - 1) * packSize + get_weapon_ammo_count(item),
      newCount := calc_reduced_ammo_range(count, percentRange);

   //display_msg("count: "+count+", pack: "+packSize+", new: "+newCount+" ("+ceil(1.0*newCount / packSize)+")");
   call reduce_item_count(invenObj, item, ceil(1.0 * newCount / packSize));
   // if number of items reduced, object reference will be different
   item := obj_carrying_pid_obj(invenObj, pid);
   if (item and newCount % packSize > 0) then
      set_weapon_ammo_count(item, newCount % packSize);

   return obj_name(item)+" ("+count+" -> "+newCount+")";
end


/**
 * Reduces number of individual bullets in an ammo stack by a percentage range.
 * @arg {ObjectPtr} item - Weapon item
 * @arg {list} percentRange - [min, max] range of % to remove
 * @ret {string}
 */
procedure reduce_ammo_in_weapon(variable item, variable percentRange) begin
   if (percentRange[1] <= 0) then return "";

   variable
      pid := obj_pid(item),
      count := get_weapon_ammo_count(item),
      newCount;

   if (count <= 0) then return "";

   newCount := calc_reduced_ammo_range(count, percentRange);
   set_weapon_ammo_count(item, newCount);
   return string_format("%s mag ammo (%d -> %d)", obj_name(item), count, newCount);
end

/**
 * Reduces number of individual bullets in an ammo obj on the ground.
 * @arg {ObjectPtr} item - item stack object
 * @arg {list} percentRange - [min, max] range of % to remove
 */
procedure reduce_ammo_on_ground(variable item, variable percentRange) begin
   if (percentRange[1] <= 0) then return "";

   variable
      pid := obj_pid(item),
      count := get_weapon_ammo_count(item),
      newCount := calc_reduced_ammo_range(count, percentRange);

   if (newCount > 0) then
      set_weapon_ammo_count(item, newCount);
   else
      destroy_object(item);

   return string_format("%s (%d -> %d)", obj_name(item), count, newCount);
end


/**
 * Reduces number of drug/misc items in stack by a percentage.
 * @arg {ObjectPtr} invenObj - Container or critter
 * @arg {ObjectPtr} item - item stack object
 * @arg {list} pidList - list of pids allowed to be removed (0 to remove regardless of PID)
 * @arg {int} percent - % to remove
 * @ret {string}
 */
procedure reduce_item_in_stack(variable invenObj, variable item, variable pidList, variable percent) begin
   if (percent <= 0
      or (pidList and not is_in_array(obj_pid(item), pidList))) then
      return "";

   // reduce with probability formula
   variable
      count := obj_is_carrying_obj(invenObj, item),
      newCount := count * (100 - percent) / 100.0;

   //debug_log_fmt("reducing %d -> %04f", count, newCount);
   newCount := floor(newCount) + (random(0, 99) < (newCount - floor(newCount))*100);
   if (newCount == count) then return "";

   call reduce_item_count(invenObj, item, newCount);
   return obj_name(item)+" ("+count+" -> "+newCount+")";
end

/**
 * Removes item on the ground with a given percentage chance.
 * @arg {ObjectPtr} item - item stack object
 * @arg {list} pidList - list of pids allowed to be removed (0 to remove regardless of PID)
 * @arg {int} percent - % chance to remove
 */
procedure reduce_item_on_ground(variable item, variable pidList, variable percent) begin
   if (percent <= 0
      or (pidList and not is_in_array(obj_pid(item), pidList))
      or random(0, 99) >= percent) then
      return "";

   destroy_object(item);
   return obj_name(item) + " (removed)";
end

#endif
