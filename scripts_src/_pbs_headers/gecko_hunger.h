#ifndef GECKO_HUNGER_H
#define GECKO_HUNGER_H

#include "../sfall/sfall.h"
#include "../sfall/lib.arrays.h"

#include "../sfall/command_lite.h"
#include "../headers/itempid.h"
#include "../headers/animcomd.h"

#ifndef FOOD_DETECT_RADIUS
   #define FOOD_DETECT_RADIUS (20)
#endif

#ifndef FOOD_SEEK_IMPROBABILITY
   #define FOOD_SEEK_IMPROBABILITY (50)
#endif

#define FOOD_PREFERENCE_GECKO (0)
#define FOOD_PREFERENCE_RAT (1)

variable food;



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

procedure getFoodPidList(variable preference) begin
   switch (preference) begin
      case FOOD_PREFERENCE_GECKO:
         return [PID_MEAT_JERKY, PID_IGUANA_ON_A_STICK, PID_MEAT_ON_A_STICK];
      case FOOD_PREFERENCE_RAT:
         return [PID_CHEEZY_POOFS, PID_MUTATED_FRUIT];
   end
end

procedure seekAndEatFood(variable improbability, variable radius, variable foodPreference) begin
   if (random(0, improbability) == 0 and not(food)) then begin
      food := getNearestFood(radius, getFoodPidList(foodPreference));
      if (food) then begin
         call anim_go_to(food);
      end
   end else if (food) then if (should_delete_food(food)) then begin
      use_obj(food);
      destroy_object(food);
      food := 0;
   end
end

procedure forgetFood begin
   food := 0; // forget about food in combat
end

#define SEEK_AND_EAT_FOOD_GECKO  call seekAndEatFood(15, FOOD_DETECT_RADIUS, FOOD_PREFERENCE_GECKO);
#define SEEK_AND_EAT_FOOD_RAT  call seekAndEatFood(15, FOOD_DETECT_RADIUS, FOOD_PREFERENCE_RAT);

#endif
