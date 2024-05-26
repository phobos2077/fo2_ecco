#ifndef ENGINE_FUNCTIONS_H
#define ENGINE_FUNCTIONS_H

/*
   Copies or partial copies of some engine functions in SSL.
*/

#include "../sfall/define_lite.h"
#include "../sfall/define_extra.h"
#include "ecco_ini.h"

#define DAM_CRIP                 (DAM_CRIP_ARM_LEFT bwor DAM_CRIP_ARM_RIGHT bwor DAM_CRIP_LEG_LEFT bwor DAM_CRIP_LEG_RIGHT bwor DAM_BLIND)
#define critter_cur_hp(cr)       get_critter_stat(cr, STAT_current_hp)
#define critter_has_dmg_flag(cr, flag)        ((get_object_data(cr, OBJ_DATA_DAMAGE_FLAGS) bwand flag) != 0)

variable sfall_ini_RemoveCriticalTimelimits := -2;

/**
 * Exactly like FO2 roll_check function, but without returning "how_much".
 * @arg {int} rollMod
 * @arg {int} critSuccessMod
 */
procedure roll_check(variable rollMod, variable critSuccessMod) begin
   variable
      delta := rollMod - random(1, 100),
      roll, criticalsAllowed;

   if (sfall_ini_RemoveCriticalTimelimits == -2) then
      sfall_ini_RemoveCriticalTimelimits := get_int_from_ini(INI_SFALL, "Misc", "RemoveCriticalTimelimits");

   criticalsAllowed := (sfall_ini_RemoveCriticalTimelimits > 0) or (game_time >= ONE_GAME_DAY);

   if (delta < 0) then begin
      return ROLL_CRITICAL_FAILURE
         if (criticalsAllowed and random(1, 100) <= -delta / 10)
         else ROLL_FAILURE;
   end
   return ROLL_CRITICAL_SUCCESS
      if (criticalsAllowed and random(1, 100) <= delta / 10 + critSuccessMod)
      else ROLL_SUCCESS;
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

procedure critter_body_type(variable critter) begin
   if (not critter) then begin
      debug_msg("\nError: critter_body_type: pobj was NULL!");
      return CR_BODY_BIPED;
   end

   if (obj_type(critter) != OBJ_TYPE_CRITTER) then
      return CR_BODY_BIPED;

   return proto_data(obj_pid(critter), cr_body_type);
end

procedure critter_is_crippled(variable critter) begin
   if (not critter) then
      return false;

   if (obj_type(critter) != OBJ_TYPE_CRITTER) then
      return false;

   return critter_has_dmg_flag(critter, DAM_CRIP);
end

procedure item_hit_with(variable critter, variable attackType) begin
   if (attackType == ATKTYPE_LWEP1 or attackType == ATKTYPE_LWEP2 or attackType == ATKTYPE_LWEP_RELOAD) then
      return critter_inven_obj2(critter, INVEN_TYPE_LEFT_HAND);
   if (attackType == ATKTYPE_RWEP1 or attackType == ATKTYPE_RWEP2 or attackType == ATKTYPE_RWEP_RELOAD) then
      return critter_inven_obj2(critter, INVEN_TYPE_RIGHT_HAND);
end

/**
 * Exactly like FO2 item_w_subtype, but with additional check for attackType to be left/right weapon attacks.
 * @arg {ObjectPtr} weapon
 * @arg {int} attackType - ATKTYPE_*
 */
procedure item_w_subtype(variable weapon, variable attackType) begin
   variable attackMode, type := WEAPON_TYPE_UNARMED;

   if weapon and (attackType <= ATKTYPE_RWEP2) then begin
      attackMode := weapon_attack_mode(obj_pid(weapon), attackType);

      if (attackMode >= ATTACK_MODE_SINGLE) then
         type := WEAPON_TYPE_RANGED;
      else if (attackMode == ATTACK_MODE_THROW) then
         type := WEAPON_TYPE_THROWN;
      else if (attackMode >= ATTACK_MODE_SWING) then
         type := WEAPON_TYPE_MELEE;
      else if (attackMode == ATTACK_MODE_NONE) then
         type := WEAPON_TYPE_NONE;
   end
   return type;
end

procedure item_w_damage_type(variable critter, variable weapon) begin
   return get_proto_data(obj_pid(weapon), PROTO_WP_DMG_TYPE)
      if weapon
      else (get_proto_data(obj_pid(critter), PROTO_CR_DMG_TYPE)
         if obj_type(critter) == OBJ_TYPE_CRITTER
         else DMG_normal_dam);
end

#endif
