#ifndef CONTAINERS_EXT_H
#define CONTAINERS_EXT_H

/**
 * Extended door logic for EcCo. Intended to be used as a wrapper for containers.h.
 * - Adds watcher logic, similar to zilockr script
 */

#ifndef WATCHER_OBJ
   #define WATCHER_OBJ                       pbs_watcher     // pbs: universal watcher (see gl_pbs_watcher)
#endif

#define custom_use_p_proc
#define custom_use_obj_on_p_proc
#define custom_use_skill_on_p_proc
#include "../headers/containers.h"

#include "check_tamper.h"

// override default crowbar bonus, to make it harder
#ifndef Crowbar_Bonus
   #if DOOR_STATUS == STATE_METAL
      #define Crowbar_Bonus                   (-5)
   #else
      #define Crowbar_Bonus                   (-3)
   #endif
#endif

// override default trap damage (2x higher)
#ifndef MIN_DAMAGE
   #define MIN_DAMAGE                      (20)
#endif
#ifndef MAX_DAMAGE
   #define MAX_DAMAGE                      (40)
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

#endif
