#ifndef PBS_INVEN_UTILS_H
#define PBS_INVEN_UTILS_H


#include "../sfall/lib.arrays.h"
#include "../sfall/lib.inven.h"

#include "../_pbs_headers/ecco_define.h"
#include "../_pbs_headers/math_ext.h"
#include "../_pbs_headers/ecco_log.h"


procedure reduce_item_count(variable invenObj, variable item, variable newCount) begin
   variable count := obj_is_carrying_obj(invenObj, item);
   if (newCount >= count) then return;

   count := rm_mult_objs_from_inven(invenObj, item, count - newCount);
   destroy_object(item);
end

#define inven_ammo_qty_formula(invenQty, packSize, ammoCount)          ((invenQty - 1) * packSize + ammoCount)
#define inven_ammo_qty_obj_w_pack_size(invenObj, ammoObj, packSize)    inven_ammo_qty_formula(obj_is_carrying_obj(invenObj, ammoObj), packSize, get_weapon_ammo_count(ammoObj))
#define inven_ammo_qty_obj(invenObj, ammoObj)                          inven_ammo_qty_obj_w_pack_size(invenObj, ammoObj, proto_ammo_pack_size(obj_pid(ammoObj)))

procedure inven_ammo_qty_pid(variable invenObj, variable pid) begin
   variable
      i := 0,
      numBullets := 0,
      packSize := proto_ammo_pack_size(pid),
      item := inven_ptr(invenObj, 0);

   while (item) do begin
      if (obj_pid(item) == pid) then begin
         numBullets += inven_ammo_qty_obj_w_pack_size(invenObj, item, packSize);
      end
      i += 1;
      item := inven_ptr(invenObj, i);
   end
   return numBullets;
end

procedure inven_set_ammo_qty_pid(variable invenObj, variable pid, variable qty) begin
   variable
      packSize := proto_ammo_pack_size(pid),
      packsNeeded := ceil(1.0 * qty / packSize),
      ammoObj;

   call set_items_qty_pid(invenObj, pid, packsNeeded);
   if (qty > 0) then begin
      ammoObj := obj_carrying_pid_obj(invenObj, pid);
      set_weapon_ammo_count(ammoObj, qty - (packsNeeded - 1) * packSize);
   end
end

procedure inven_set_ammo_qty_obj(variable invenObj, variable ammoObj, variable qty) begin
   variable
      pid := obj_pid(ammoObj),
      packSize := proto_ammo_pack_size(pid),
      packsNeeded := ceil(1.0 * qty / packSize),
      packsActual := obj_is_carrying_obj(invenObj, ammoObj);

   if (packsNeeded > packsActual) then begin
      ammoObj := add_items_pid(invenObj, pid, packsNeeded - packsActual);
   end
   if (qty > 0) then begin
      set_weapon_ammo_count(ammoObj, qty - (packsNeeded - 1) * packSize);
   end
   if (packsNeeded < packsActual) then begin
      ammoObj := rm_mult_objs_from_inven(invenObj, ammoObj, packsActual - packsNeeded);
      destroy_object(ammoObj);
   end
end


#endif
