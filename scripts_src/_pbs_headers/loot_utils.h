#ifndef PBS_LOOT_UTILS_H
#define PBS_LOOT_UTILS_H


#include "../sfall/lib.arrays.h"
#include "../sfall/lib.inven.h"
#include "../sfall/lib.math.h"

#include "math_ext.h"
#include "ecco_define.h"
#include "ecco_log.h"

#include "inven_utils.h"


procedure calc_reduced_ammo_range(variable count, variable percentRange, variable emptyChance := 0) begin
   if (emptyChance > 0 and random(0, 99) < emptyChance) then
      return 0;

   /* variable
      rnd := random(percentRange[0], percentRange[1]),
      clamped := math_max(100 - rnd, 0),
      multed := count * clamped / 100.0,
      rounded := math_round_chance(multed),
      allInOne :=   */

   //debug_log_fmt("calc range from %d: rnd = %d, clamped = %d, multed = %.2f, rounded = %d, allInOne = %d", count, rnd, clamped, multed, rounded, allInOne);
   return math_round_chance(count * math_max(100 - random(percentRange[0], percentRange[1]), 0) / 100.0);
end

/**
 * Reduces number of individual bullets in an ammo stack by a percentage range.
 * @arg {ObjectPtr} invenObj - Container or critter
 * @arg {ObjectPtr} item - item stack object
 * @arg {list} percentRange - [min, max] range of % to remove
 * @arg {int} emptyChance - probabiltiy to remove all ammo
 * @ret {string}
 */
procedure reduce_ammo_in_stack(variable invenObj, variable item, variable percentRange, variable emptyChance := 0) begin
   if (percentRange[1] <= 0) then return "";

   variable
      pid := obj_pid(item),
      packSize := get_proto_data(pid, PROTO_AM_PACK_SIZE),
      count := (obj_is_carrying_obj(invenObj, item) - 1) * packSize + get_weapon_ammo_count(item),
      newCount := calc_reduced_ammo_range(count, percentRange, emptyChance),
      itemName := obj_name(item);

   //display_msg("count: "+count+", pack: "+packSize+", new: "+newCount+" ("+ceil(1.0*newCount / packSize)+")");
   call reduce_item_count(invenObj, item, ceil(1.0 * newCount / packSize));
   // if number of items reduced, object reference will be different
   item := obj_carrying_pid_obj(invenObj, pid);
   if (item and newCount % packSize > 0) then
      set_weapon_ammo_count(item, newCount % packSize);

   return itemName+" ("+count+" -> "+newCount+"), ";
end


/**
 * Reduces number of individual bullets in an ammo stack by a percentage range.
 * @arg {ObjectPtr} item - Weapon item
 * @arg {list} percentRange - [min, max] range of % to remove
 * @arg {int} emptyChance - probabiltiy to remove all ammo
 * @ret {string}
 */
procedure reduce_ammo_in_weapon(variable item, variable percentRange, variable emptyChance := 0) begin
   if (percentRange[1] <= 0) then return "";

   variable
      count := get_weapon_ammo_count(item),
      newCount;

   if (count <= 0) then return "";

   newCount := calc_reduced_ammo_range(count, percentRange, emptyChance);
   set_weapon_ammo_count(item, newCount);
   return string_format("%s mag ammo (%d -> %d), ", obj_name(item), count, newCount);
end

/**
 * Reduces number of individual bullets in an ammo obj on the ground.
 * @arg {ObjectPtr} item - item stack object
 * @arg {list} percentRange - [min, max] range of % to remove
 */
procedure reduce_ammo_on_ground(variable item, variable percentRange) begin
   if (percentRange[1] <= 0) then return "";

   variable
      count := get_weapon_ammo_count(item),
      newCount := calc_reduced_ammo_range(count, percentRange);

   if (newCount > 0) then
      set_weapon_ammo_count(item, newCount);
   else
      destroy_object(item);

   return string_format("%s (%d -> %d), ", obj_name(item), count, newCount);
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
      or (pidList andAlso not is_in_array(obj_pid(item), pidList))) then
      return "";

   // reduce with probability formula
   variable
      count := obj_is_carrying_obj(invenObj, item),
      newCount := count * (100 - percent) / 100.0;

   //debug_log_fmt("reducing %s: %d -> %04f", obj_name(item), count, newCount);
   newCount := floor(newCount) + (random(0, 99) < (newCount - floor(newCount))*100);
   if (newCount >= count) then return "";

   call reduce_item_count(invenObj, item, newCount);
   return obj_name(item)+" ("+count+" -> "+newCount+"), ";
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

procedure unload_weapon(variable item) begin
   variable count := get_weapon_ammo_count(item);
   if (count <= 0) then return "";

   set_weapon_ammo_count(item, 0);
   return string_format("%s mag ammo (%d -> 0)", obj_name(item), count);
end


procedure loot_trim_inventory(variable invenObj, variable pidToQty) begin
   variable item, pid, list, n, qtyMax, qtyActual, rmvd, removeStats;
   removeStats := "";

   list := inven_as_array(invenObj);
   foreach item in list begin
      pid := obj_pid(item);
      qtyActual := obj_is_carrying_obj(invenObj, item);
      qtyMax := pidToQty[pid];
      if (qtyActual > qtyMax) then begin
         call inven_unwield_item(invenObj, item);
         if (qtyMax > 0 and obj_item_subtype(item) == item_type_weapon) then
            call unload_weapon(item);
         removeStats += string_format("%s (%d -> %d); ", obj_name(item), qtyActual, qtyMax);
         n := rm_mult_objs_from_inven(invenObj, item, qtyActual - qtyMax);
         if (n != qtyActual - qtyMax) then
            debug_err_fmt("Expected to remove %d of %s, but actually removed: %d", qtyActual - qtyMax, obj_name(item), n);
         destroy_object(item);
      end
   end
   if (removeStats != "") then
      debug_log_fmt("Removed merchant loot in %s: %s", obj_name(invenObj), removeStats);
end

/*
procedure merchant_stock_cleanup(variable invenObj, variable percentMoney, variable percentAmmo, variable pidsToKeep) begin
   variable item, pid, list, n, prob, qtyMax, qtyActual, packSize, removeStats;
   removeStats := "";
   item_caps_adjust(invenObj, -(item_caps_total(invenObj) * percentMoney / 100));

   list := inven_as_array(invenObj);
   foreach item in list begin
      pid := obj_pid(item);
      if (proto_item_is_hidden(pid) or pid == PID_BOTTLE_CAPS) then continue;

      qtyMax := pidsToKeep[pid];
      if (qtyMax == 0) then begin
         removeStats += string_format("%s -> 0", obj_name(item));
         call remove_item_obj(invenObj, item);
      end else if (obj_item_subtype(item) == item_type_ammo) then begin
         packSize := proto_ammo_pack_size(pid);
         qtyMax := qtyMax * packSize * percentAmmo / 100;
         qtyActual := inven_ammo_qty_obj_w_pack_size(invenObj, item, packSize);
         if (qtyActual > qtyMax) then begin
            removeStats += string_format("%s (%d -> %d)", obj_name(item), qtyActual, qtyMax);
            call inven_set_ammo_qty_obj(invenObj, item, qtyAmmo * percentAmmo / 100);
         end
      end else begin
         qtyActual := obj_is_carrying_obj(invenObj, item);
         if (qtyActual > qtyMax) then begin
            removeStats += string_format("%s (%d -> %d)", obj_name(item), qtyActual, qtyMax);
            n := rm_mult_objs_from_inven(invenObj, item, qtyActual - qtyMax);
            destroy_object(item);
         end
      end
   end
   if (removeStats != "") then
      debug_log_fmt("Removed merchant loot in %s: %s", obj_name(invenObj), removeStats);
end
*/


#endif
