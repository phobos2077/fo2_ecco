#ifndef ENGINE_FUNCTIONS_H
#define ENGINE_FUNCTIONS_H

/*
   Copies or partial copies of some engine functions in SSL.
*/

#include "../sfall/define_lite.h"
#include "../sfall/define_extra.h"

#define DAM_CRIP                 (DAM_CRIP_ARM_LEFT bwor DAM_CRIP_ARM_RIGHT bwor DAM_CRIP_LEG_LEFT bwor DAM_CRIP_LEG_RIGHT bwor DAM_BLIND)
#define critter_cur_hp(cr)       get_critter_stat(cr, STAT_current_hp)
#define critter_has_dmg_flag(cr, flag)        ((get_object_data(cr, OBJ_DATA_DAMAGE_FLAGS) bwand flag) != 0)

/**
 * Exactly like FO2 roll_check functions, but without returning "how_much" and disabling criticals in the first day.
 * @arg {int} rollMod
 * @arg {int} critChance
 */
procedure roll_check(variable rollMod, variable critChance) begin
   variable
      delta := rollMod - random(1, 100),
      roll;

   if (delta < 0) then begin
      return ROLL_CRITICAL_FAILURE if (random(1, 100) <= -delta / 10) else ROLL_FAILURE;
   end
   return ROLL_CRITICAL_SUCCESS if (random(1, 100) <= delta / 10 + critChance) else ROLL_SUCCESS;
end

// This data is in the struct in the engine, written as switch for simplicity.
procedure get_skill_xp(variable skill) begin
   switch (skill) begin
      case SKILL_FIRST_AID: return 25;
      case SKILL_REPAIR: return 25; // vanilla is 0
      case SKILL_DOCTOR: return 50;
      // TODO: other skills
      default: return 0;
   end
end

procedure show_skill_use_messages(variable skill, variable successCount := 1) begin
   variable baseExp, xpToAdd, before, after;
   if (successCount <= 0) then return;

   baseExp = get_skill_xp(skill);
   if (baseExp == 0) then return;

   xpToAdd = successCount * baseExp;

   before = get_pc_stat(PCSTAT_experience);

   give_exp_points(xpToAdd);

   after = get_pc_stat(PCSTAT_experience);
   display_msg(sprintf(mstr_skill(505), after - before));
end

procedure critter_is_dead(variable critter) begin
   if (not critter) then
      return false;

   if (obj_type(critter) != OBJ_TYPE_CRITTER) then
      return false;

   if (critter_cur_hp(critter) <= 0) then
      return true;

   if (is_critter_dead(critter) != 0) then
      return true;

   return false;
end

procedure critter_is_crippled(variable critter) begin
   if (not critter) then
      return false;

   if (obj_type(critter) != OBJ_TYPE_CRITTER) then
      return false;

   return critter_has_dmg_flag(critter, DAM_CRIP);
end

#endif
