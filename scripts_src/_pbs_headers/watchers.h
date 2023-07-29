#ifndef WATCHERS_H
#define WATCHERS_H

#include "../sfall/lib.obj.h"

import variable pbs_watcher;

//#define violating_property       (tile_in_tile_rect(20530, 20523, 22930, 23123, dude_tile))  // back room of Doctors' house
#ifdef LVAR_Home_Direction
   #define home_direction           local_var(LVAR_Home_Direction)
   #define save_home_direction      set_local_var(LVAR_Home_Direction, self_cur_rot)
#else
   variable home_direction;
   #define save_home_direction      home_direction := self_cur_rot
#endif
#define caught_sneaking_at          local_var(LVAR_Caught_Sneaking)
#define set_caught_sneaking_at(x)   set_local_var(LVAR_Caught_Sneaking, x)
#define _dude_dist(obj)              (tile_distance_objs(obj, dude_obj))

procedure check_watcher begin
   if (self_obj != pbs_watcher andAlso
      obj_can_hear_and_shoot_obj(self_obj, dude_obj) andAlso
      (pbs_watcher == 0 orElse _dude_dist(self_obj) < _dude_dist(pbs_watcher))
   ) then begin
      pbs_watcher := self_obj;
      ndebug("Watcher changed to: " + obj_name_safe(pbs_watcher));
   end
end

procedure turn_facing_tile(variable tile) begin
   reg_anim_clear(self_obj);
   reg_anim_begin();
   reg_anim_turn_towards(self_obj, tile, -1);
   reg_anim_end();
end

#define turn_facing_direction(dir)     turn_facing_tile(tile_num_in_direction(self_tile, dir, 1))

procedure check_violating_property(variable start_action := 0, variable stop_action := 0) begin
   if (violating_property and self_can_hear_dude) then begin
      if (caught_sneaking_at == 0) then begin
         save_home_direction;
         obj_floater_type(self_obj, g_mstr(random(3925, 3929)), FLOAT_COLOR_BAD);
         set_caught_sneaking_at(game_time);
         ndebug("Caught sneaking!");
         if (start_action) then call start_action;
      end
      else if ((caught_sneaking_at + ONE_GAME_SECOND * 3) < game_time) then begin
         set_local_var(LVAR_Hostile, 2);
         ndebug("Still sneaking, attack!");
      end
      call turn_facing_tile(dude_tile);
   end
   else if (caught_sneaking_at) then begin
      call turn_facing_direction(home_direction);
      set_caught_sneaking_at(0);
      ndebug("Not sneaking anymore, reset.");
      if (stop_action) then call stop_action;
   end
end

#undef _dude_dist

#endif // WATCHERS_H
