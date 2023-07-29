#ifndef DOORS_EXT_H
#define DOORS_EXT_H

/**
 * Extended door logic for EcCo. Intended to be used as a wrapper for doors.h.
 * - Adds watcher logic, similar to zilockr script
 * - Replaces explosion attempts with door HP, allowing to destroy doors with more than explosives
 */

#define custom_use_p_proc
#define custom_use_obj_on_p_proc
#define custom_use_skill_on_p_proc
#define custom_damage_p_proc
#define custom_Damage_Critter
#include "../headers/doors.h"

#include "../sfall/lib.obj.h"

// Track total damage to door instead of number of explosions
#define LVAR_Door_Damage                      LVAR_Explosion_Attempts

procedure rpu_Damage_Critter;

#include "door_damage.h"

// override default crowbar bonus, to make it harder
#ifndef Crowbar_Bonus
   #if DOOR_STATUS == STATE_METAL
      #define Crowbar_Bonus                   (-5)
   #else
      #define Crowbar_Bonus                   (-2)
   #endif
#endif

// override default trap damage (2x higher)
#ifndef MIN_DAMAGE
   #define MIN_DAMAGE                      (20)
#endif
#ifndef MAX_DAMAGE
   #define MAX_DAMAGE                      (40)
#endif

#ifdef WATCHER_OBJ
   import variable WATCHER_OBJ;
   #ifndef WATCH_ATTACK_PROBABILITY
      #define WATCH_ATTACK_PROBABILITY       (50)
   #endif
#endif
#ifndef DO_CHECK_TAMPER_CONDITION
   #define DO_CHECK_TAMPER_CONDITION         (true)            // setting this to true will always check no matter what
#endif

// TODO: door scripts have no LVAR_Flags! no place for additional flag >:(
/*
#define gave_warning_bit                     bit_11
#define gave_warning                         ((lvar_bit(LVAR_Flags, gave_warning_bit)) or (SKIP_WARNING))
*/
#ifndef do_warning_action
   #define do_warning_action                 float_msg(WATCHER_OBJ, g_mstr(5400), FLOAT_COLOR_NORMAL);
#endif
#ifndef do_attack_action
   #define do_attack_action                  attack_setup(WATCHER_OBJ, user_obj);
#endif
/*#define set_gave_warning                     if (gave_warning) then begin        \
                                                do_attack_action                 \
                                             end else begin                      \
                                                do_warning_action                \
                                             end                                 \
                                             set_lvar_bit_on(LVAR_Flags, gave_warning_bit)
*/
#define attack_or_warn                       if (random(1, 100) < WATCH_ATTACK_PROBABILITY) then begin  \
                                                do_attack_action                 \
                                             end else begin                      \
                                                do_warning_action                \
                                             end

#ifndef watch_box_conditions
   #define watch_box_conditions              obj_can_hear_and_shoot_obj(WATCHER_OBJ, user_obj)
#endif

procedure rpu_use_p_proc begin
   /* Trap_Roll is a global variable to this script, defined at the beginning
      of the script. */
   
   Traps_Roll:=roll_vs_skill(source_obj,SKILL_TRAPS,Trap_Bonus);
   if (local_var(LVAR_Trapped) == STATE_ACTIVE) then begin
      if (is_success(Traps_Roll)) then begin
         script_overrides;
         set_local_var(LVAR_Found_Trap,1);
         reg_anim_clear(source_obj);
         
         if (source_obj == dude_obj) then begin
            display_msg(my_mstr(204));
         end
         else begin
            display_msg(my_mstr(205));
         end
      end
      
      else begin
         if (obj_is_locked(self_obj)) then begin
            script_overrides;
            display_msg(my_mstr(203));
            call Damage_Critter;
         end
         else begin
            call Damage_Critter;
         end
      end
   end
   else if (obj_is_locked(self_obj)) then begin
      script_overrides;
      display_msg(my_mstr(203));
   end
   if (CLOSE_STATUS == STATE_DOOR_CLOSE) then begin
      last_source_obj := source_obj;
      add_timer_event(self_obj, 10, TIMER_CLOSE);
   end
end

procedure rpu_use_skill_on_p_proc begin
   variable Skill_Used;
   Skill_Used:=action_being_used;
   if (Skill_Used == SKILL_LOCKPICK) then begin
     script_overrides; //added by killap
     if (local_var(LVAR_Locked) == STATE_ACTIVE) then begin
       call Unlock_Lock;
     end
     else begin
       call Set_Lock;
     end
   end                                                          // End of Skill_Lockpick
   else if (Skill_Used == SKILL_TRAPS) then begin
     script_overrides; //added by killap
     if (local_var(LVAR_Trapped) == STATE_ACTIVE) then begin
       call Skill_Disarm_Traps;
     end
     else begin
       if (source_obj == dude_obj) then begin
         display_msg(my_mstr(195));
       end
       
       else begin
         display_msg(obj_name(source_obj)+my_mstr(200));
       end
     end
   end                                                          // End of Skill_Traps
end

/*
procedure rpu_damage_p_proc begin
   variable trapDamage;
   if (weapon_dmg_type(target_obj) == DMG_explosion) then begin
      if (DOOR_STATUS == STATE_WOOD) then begin
         if (local_var(LVAR_Trapped) == STATE_ACTIVE) then begin
            set_local_var(LVAR_Trapped, STATE_INACTIVE);
            set_local_var(LVAR_Locked, STATE_INACTIVE);
            trapDamage:=random(MIN_DAMAGE,MAX_DAMAGE);
            explosion(self_tile, self_elevation, trapDamage);
            destroy_object(self_obj);
         end
         else begin
            set_local_var(LVAR_Trapped, STATE_INACTIVE);
            set_local_var(LVAR_Locked, STATE_INACTIVE);
            destroy_object(self_obj);
         end
      end
      else if (DOOR_STATUS == STATE_METAL) then begin
         set_local_var(LVAR_Explosion_Attempts,local_var(LVAR_Explosion_Attempts)+1);
         if (local_var(LVAR_Trapped) == STATE_ACTIVE) then begin
            set_local_var(LVAR_Locked, STATE_INACTIVE);
            trapDamage:=random(MIN_DAMAGE,MAX_DAMAGE);
            explosion(self_tile, self_elevation, trapDamage);
         end
         else if (local_var(LVAR_Explosion_Attempts) > DOOR_STRENGTH) then begin
            set_local_var(LVAR_Trapped, STATE_INACTIVE);
            set_local_var(LVAR_Locked,STATE_INACTIVE);
            destroy_object(self_obj);
         end
      end
   end
   else begin
      display_msg(my_mstr(193));
   end
end
*/

procedure rpu_Damage_Critter begin
   variable Trap_Damage;
   Trap_Damage:=random(MIN_DAMAGE,MAX_DAMAGE);
   reg_anim_clear(source_obj); // prevent "you were hit for no damage" from the next line when running through a closed door
   explosion(self_tile, self_elevation, 0); // just the animation
   pcnpc_display_str(source_obj, my_mstr(166)+Trap_Damage+my_mstr(167), my_mstr(168)+Trap_Damage+my_mstr(169))
   critter_heal(source_obj, -Trap_Damage);
   set_local_var(LVAR_Trapped, STATE_INACTIVE);
   return Trap_Damage;
end

procedure Damage_Critter begin
   variable trapDmg := rpu_Damage_Critter;
   call damage_door(trapDmg); // damage door itself
end

procedure check_tamper(variable isLoud := false) begin
#ifdef WATCHER_OBJ
   variable user_obj := source_obj;
   if (DO_CHECK_TAMPER_CONDITION and WATCHER_OBJ) then begin
      ndebug("Checking tamper vs " + obj_name(WATCHER_OBJ));
      if (is_visible(WATCHER_OBJ) and is_critter_dead(WATCHER_OBJ) == false and (isLoud or watch_box_conditions)) then begin
         ndebug("Tampered! triggering watcher");
         script_overrides;
         attack_or_warn
         return true;
      end
   end
#endif
   return false;
end

procedure use_p_proc begin
   if (check_tamper) then return;
   call rpu_use_p_proc;
end

procedure use_obj_on_p_proc begin
   variable Tool;
   if (check_tamper) then return;

   Tool:=obj_pid(obj_being_used_with);
   pry_trap_block
   full_lockpick_block
end

procedure use_skill_on_p_proc begin
   if (check_tamper) then return;
   call rpu_use_skill_on_p_proc;
end

procedure damage_p_proc begin
   call door_damage_proc;
   call check_tamper(true);
end

#endif
