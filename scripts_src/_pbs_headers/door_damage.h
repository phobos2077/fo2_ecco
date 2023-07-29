#ifndef DOOR_DAMAGE_H
#define DOOR_DAMAGE_H

#include "../sfall/define_extra.h"

import variable pbs_last_hit_roll_result;
import variable pbs_last_burst_size;

/* How much damage the door can withstand */
#ifndef DOOR_HEALTH
   #define DOOR_HEALTH                        (20 + DOOR_STATUS*50)
#endif

#define DOOR_DAMAGE_THRESHOLD                 (5 + DOOR_STATUS*15)

procedure damage_door(variable dmg) begin
   if (DOOR_STATUS != STATE_NON_DESTROY) then begin
      inc_local_var_amt(LVAR_Door_Damage, dmg);
      if (local_var(LVAR_Door_Damage) >= DOOR_HEALTH) then begin // destroy door
          set_local_var(LVAR_Trapped, STATE_INACTIVE);
#ifdef LVAR_Locked
          set_local_var(LVAR_Locked, STATE_INACTIVE);
#endif
          set_obj_visibility(self_obj, 1);
          //destroy_object(self_obj);
      end
   end
end

procedure door_damage_proc begin
   variable trapDamage;
   variable attacker;
   variable weapon;
   variable dmg;
   variable sfx;

   attacker := source_obj;
   weapon := obj_being_used_with;
   if not(is_success(pbs_last_hit_roll_result)) then return;
   dmg := fixed_param;
   if (dmg > 0) then begin  // this only happens when blowing the door with dynamite
      if (attacker == 0 and weapon == 0) then begin
         dmg := get_explosion_damage(PID_DYNAMITE);
      end
   end else begin
      if (attacker) then begin
         if (weapon == 0 or weapon == self_obj) then begin // HTH attack
            dmg := random(1, 2 + get_critter_stat(attacker, STAT_melee_dmg));
         end else begin
            dmg := get_proto_data(obj_pid(weapon), PROTO_WP_DMG_MAX); // max dmg
            if (pbs_last_burst_size > 1) then
               dmg *= pbs_last_burst_size;
            dmg := random(get_proto_data(obj_pid(weapon), PROTO_WP_DMG_MIN), dmg);
         end
      end
   end
   dmg -= DOOR_DAMAGE_THRESHOLD;
   ndebug("Door dmg = "+dmg);
   // display_msg(get_sfall_global_int("HIT/MISS")+"dmg "+dmg+" with "+obj_name(obj_being_used_with)+" by "+obj_name(source_obj)+obj_name(target_obj));
   /*if (DOOR_STATUS == STATE_METAL) then
      sfx := "MXX1";
   else
      sfx := "FXX1";
   play_sfx("WH5"+random(1,2)+sfx);*/
   if (dmg > 0) then begin
      // Trigger trap, if any
      if (local_var(LVAR_Trapped) == STATE_ACTIVE) then begin
         dmg += rpu_Damage_Critter;
      end
      call damage_door(dmg);
      // TODO: new message about door damaged
   end
   else begin
      display_msg(mstr(193)); // not a scratch...
   end
end

#endif
