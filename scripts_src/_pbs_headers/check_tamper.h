#ifndef ECCO_CHECK_TAMPER_H
#define ECCO_CHECK_TAMPER_H

#include "../sfall/lib.obj.h"

#ifdef WATCHER_OBJ
   import variable WATCHER_OBJ;
#endif

#ifndef DO_CHECK_TAMPER_CONDITION
   #define DO_CHECK_TAMPER_CONDITION         (true)            // setting this to true will always check no matter what
#endif

#ifndef watch_box_conditions
   #define watch_box_conditions              obj_can_hear_obj(WATCHER_OBJ, user_obj)
#endif

#ifndef do_warning_action
   #define do_warning_action                 float_msg(WATCHER_OBJ, g_mstr(5400), FLOAT_COLOR_NORMAL);
#endif
#ifndef do_attack_action
   #define do_attack_action                  attack_setup(WATCHER_OBJ, user_obj);
#endif 

#ifdef gave_warning_bit
   #define gave_warning                      (lvar_bit(LVAR_Flags, gave_warning_bit))
   #define attack_or_warn  \
      if (gave_warning) then begin        \
         do_attack_action                 \
      end else begin                      \
         do_warning_action                \
      end                                 \
      set_lvar_bit_on(LVAR_Flags, gave_warning_bit);
#else
   #ifndef WATCH_ATTACK_PROBABILITY
      #define WATCH_ATTACK_PROBABILITY       (50)
   #endif
   #define attack_or_warn  \
      if (random(1, 100) < WATCH_ATTACK_PROBABILITY) then begin  \
         do_attack_action                 \
      end else begin                      \
         do_warning_action                \
      end
#endif

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

#endif // ECCO_CHECK_TAMPER_H
