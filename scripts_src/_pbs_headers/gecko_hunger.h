#include "..\_pbs_main\sfall.h"
#include "..\_pbs_main\lib.arrays.h"

procedure getNearestFood(variable maxRadius, variable foodList) begin
   variable items, item, dist, minDist, food;
   items := list_as_array(LIST_GROUNDITEMS);
   minDist := 99999;
   food := 0;
   foreach item in items begin
      if (is_in_array(obj_pid(item), foodList)) then begin
         dist := tile_distance(self_tile, tile_num(item));
         if (dist < maxRadius and dist < minDist) then begin
            minDist := dist;
            food := item;
         end
      end
   end
   return food;
end

procedure getNearestFoodForGecko(variable maxRadius) begin
   variable foodList;
   foodList := temp_list3(PID_MEAT_JERKY,PID_IGUANA_ON_A_STICK,PID_MEAT_ON_A_STICK);
   return getNearestFood(maxRadius, foodList);
end

procedure getNearestFoodForRat(variable maxRadius) begin
   variable foodList;
   foodList := temp_list2(PID_CHEEZY_POOFS, -1);
   return getNearestFood(maxRadius, foodList);
end

procedure anim_go_to(variable food) begin
   reg_anim_clear(self_obj);
   reg_anim_begin();
   reg_anim_obj_move_to_obj(self_obj, food, -1);
   reg_anim_end();
end

procedure anim_go_eat_food(variable food) begin
   reg_anim_clear(self_obj);
   reg_anim_begin();
   reg_anim_obj_move_to_obj(self_obj, food, -1);
   reg_anim_animate(self_obj, ANIM_throw_punch, -1);
   reg_anim_end();
end

#define should_delete_food(food)    (not(anim_busy(self_obj)) and tile_distance_objs(self_obj, food) <= 2)