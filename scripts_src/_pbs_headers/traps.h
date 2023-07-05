/*
	Headers for Combat rebalance and trap system by phobos2077
*/

#ifndef PBS_TRAPS_H
#define PBS_TRAPS_H

#include "../sfall/sfall.h"
#include "../sfall/lib.arrays.h"
#include "../sfall/lib.strings.h"
#include "../sfall/lib.inven.h"
#include "../sfall/lib.math.h"
#include "../_pbs_headers/ecco.h"
#include "miscpid.h"

#include "../headers/animcomd.h"
#include "../headers/itempid.h"
#include "../headers/scenepid.h"

#define INI_FILE          "ecco\\traps.ini"
#define INI_SECTION        "TRAPS"

#define SCRIPT_PBS_TRAPS     SCRIPT_TEST2

#define TRAP_STATE_DISARMED  (0)
#define TRAP_STATE_ACTIVE    (1)

#define TRAP_FRAME_DEFAULT   (0)
#define TRAP_FRAME_ACTIVE    (1)

#define TRAP_TYPE_SPIKE      (0)
#define TRAP_TYPE_MINE       (1)
#define TRAP_TYPE_SENSOR     (2)
#define TRAP_TYPE_BEAR       (3)

// custom timed_event's
#define TRAP_EVENT_INIT				(0)
#define TRAP_EVENT_DESTROY			(1)
#define TRAP_EVENT_DEACTIVATE		(2)
#define TRAP_EVENT_SETOFF  		(3)

#define TRAP_FRIENDFOE_DUDE		(1)
#define TRAP_FRIENDFOE_PARTY		(2)

#define traps_mstr(msg)      message_str(SCRIPT_PBS_TRAPS, msg)

#define gain_exp_for_trapkill(exp)			give_exp_points(exp); \
											         display_msg(sprintf(traps_mstr(2001), exp));

#define make_critter_angry(obj)         add_array_set(load_create_array(ARR_ANGRY_TEAMS, 0), obj_team(obj))


#define trapkit_pid_by_trap_type(type)    (pbs_trap_config.types[type].item_pid)
#define trap_type_by_trapkit_pid(pid)     (pbs_trap_config.item_to_type[pid])
#define is_trap_kit_pid(pid)			      (trap_type_by_trapkit_pid(pid) != 0)


#define send_trap_init_event(obj, type, charges)       add_timer_event(obj, 0, TRAP_EVENT_INIT + 0x100 * (type bwand 0xFF) + 0x10000 * (charges bwand 0xFF))


// Normal variables
variable begin
   traps_how_much;
end

// Exported variables

#ifdef _TRAPS_EXPORT
#define _EXPORT_VAR(name, value)    export variable name := value;
#else
#define _EXPORT_VAR(name, value)    import variable name;
#endif

_EXPORT_VAR(pbs_trap_config, 0)
_EXPORT_VAR(pbs_trap_victims, 0)  // maps trap object to it's victim, used to "send" object from spatial script
_EXPORT_VAR(pbs_trap_last_target, 0)
_EXPORT_VAR(pbs_trap_last_target_dead, 0)
_EXPORT_VAR(pbs_trap_hold_critters, 0)

#undef _EXPORT_VAR


procedure create_trap_object(variable trapType, variable tile, variable elev, variable charges);
procedure react_hostile_action;
procedure trap_setoff_explosion(variable trapObj, variable mainTarget, variable dmgMin, variable dmgMax, variable radius, variable dmgType, variable isCritical, variable pid, variable sfx);
procedure trap_setoff_melee(variable critter, variable dmgMin, variable dmgMax, variable dmgType, variable isCritical, variable stopTurns);

variable trap_object_pid_set;

pure procedure tile_contains_any_trap(variable tile, variable elev) begin
   if not trap_object_pid_set then begin
      trap_object_pid_set := array_fixed(array_to_set(array_keys(pbs_trap_config.pid_to_type)));
      call array_append(trap_object_pid_set, array_to_set([
         PID_METAL_FLOOR_TRAP_VISIBLE, PID_METAL_FLOOR_TRAP_DISARMED, PID_METAL_FLOOR_TRAP_DEPRESSED,
         PID_CAVE_FLOOR_TRAP_VISIBLE, PID_CAVE_FLOOR_TRAP_DISARMED, PID_CAVE_FLOOR_TRAP_DEPRESSED]));
      debug_log("trap_object_pid_set: "+debug_array_str(trap_object_pid_set));
   end
   variable obj, objs := tile_get_objs(tile, elev);
   foreach (obj in objs) begin
     if (trap_object_pid_set[obj_pid(obj)]) then return true;
   end
   return false;
end

pure procedure is_suitable_armament(variable pid, variable type) begin
   variable arms := pbs_trap_config.types[type].armaments;
   debug_log("arms="+debug_array_str(arms));
   return is_in_array(pid, arms) if arms else false;
end


/**
	Create new trap object with correct PID, and init properly. Used when creating and transforming trap.
	@param type   - type of trap
*/
procedure create_trap_object(variable type, variable tile, variable elev, variable charges) begin
   variable newPid := 0, newObj;
   newPid := 0x02000000 + pbs_trap_config.types[type].trap_pid;
   if (newPid == 0) then begin
      debug_err("Invalid trap type: "+type);
      return 0;
   end
   newObj := create_object_sid(newPid, tile, elev, SCRIPT_TEST2);
   // art_change_fid_num()
   send_trap_init_event(newObj, type, charges);
   return newObj;
end


procedure random_roll_ext(variable rollMod, variable critChance, variable successOffset, variable successMult, variable failMult) begin
   variable
      delta := rollMod - random(1, 100),
      roll;

   traps_how_much := delta;
   if (delta < 0) then begin
      return ROLL_CRITICAL_FAILURE if (random(1, 100) <= -delta*failMult) else ROLL_FAILURE;
   end
   return ROLL_CRITICAL_SUCCESS if (random(1, 100) <= math_max(delta + successOffset, 0)*successMult + critChance) else ROLL_SUCCESS;
end

procedure roll_vs_traps_ext(variable critter, variable rollMod) begin
   variable
      skillValue := has_skill(critter, SKILL_TRAPS),
      critChance := get_critter_stat(critter, STAT_crit_chance),
      diffMult := (difficulty_level - 1) * (1 if (critter == dude_obj) else -1),
      successMult := (5 - diffMult),
      failMult := (0.2 + 0.1 * diffMult);

   return random_roll_ext(skillValue + rollMod, critChance, -50, successMult, failMult);
end

procedure roll_critical(variable critter, variable bodyPart) begin
   variable roll := random(1, 100);
   roll += get_critter_stat(dude_obj, STAT_better_crit);

   variable level;
   if (roll <= 20) then
      level := 0;
   else if (roll <= 45) then
      level := 1;
   else if (roll <= 70) then
      level := 2;
   else if (roll <= 90) then
      level := 3;
   else if (roll <= 100) then
      level := 4;
   else
      level := 5;

   variable
      killType := critter_kill_type(critter),
      dmgMult := get_critical_table(killType, bodyPart, level, CRITICAL_VALUE_MULT),
      effects := get_critical_table(killType, bodyPart, level, CRITICAL_VALUE_EFFECTS);

   return {"mult": dmgMult * 0.5, "effects": effects};
end

// dude made a hostile act (installed trap), need reaction of nearby critters
procedure react_hostile_action begin
   variable obj;
   foreach (obj in objects_in_radius(dude_tile, 15, dude_elevation, OBJ_TYPE_CRITTER)) begin
      if (obj != dude_obj
         and not(obj_in_party(obj))
         and is_human(obj)
         and obj_can_see_obj(obj, dude_obj)) then
      begin
         call make_critter_angry(obj);
         //set_object_data(obj, OBJ_DATA_WHO_HIT_ME, dude_obj);
      end
   end
end

procedure trap_damage_critter(variable critter, variable dmgMin, variable dmgMax, variable dmgType, variable criticalBodyPart, variable stop) begin
   variable
      crit := roll_critical(critter, criticalBodyPart) if (criticalBodyPart != -1) else false,
      dmg := random(dmgMin, dmgMax),
      effects := 0,
      killExp := 0;

   if (crit) then begin
      debug_log_fmt("Critical! Dmg = %d*%.2f = %d, flags = 0x%X", dmg, crit.mult, round(dmg * crit.mult), crit.effects);
      dmg := round(dmg * crit.mult);
      effects := effects bwor crit.effects;
   end

   pbs_trap_last_target := critter;
   pbs_trap_last_target_dead := false;

   // If critter is killed outside of combat, setting WHO_HIT_ME ensures source_obj in destroy_p_proc returns dude_obj and e.g. grant karma bonus
   set_object_data(critter, OBJ_DATA_WHO_HIT_ME, dude_obj);
   if (stop) then set_target_knockback(critter, 0, 0); // prevents knockback

   debug_log_fmt("critter_dmg(%s, %d, %X)", obj_name(critter) if critter else "null", dmg, dmgType bwor (DMG_BYPASS_ARMOR if (effects bwand DAM_BYPASS) else 0));
   critter_dmg(critter, dmg, dmgType bwor (DMG_BYPASS_ARMOR if (effects bwand DAM_BYPASS) else 0));

   if (stop) then remove_target_knockback(critter);

   // Because critter_dmg doesn't apply damage immediately, but only after death animation, we need to hook into hs_deathanim2 to detect if death took place.
   debug_log_fmt("critter is dead: %d", pbs_trap_last_target_dead);
   if (combat_is_initialized) then begin
      debug_log("set AP to 0!");
      set_combat_free_move(0); // REQUIRED if another mod sets combat_free_move to a critter
      set_critter_current_ap(critter, 0); // REQUIRED to prevent crash (if triggered during combat from hs_movecost)
   end
   if (not pbs_trap_last_target_dead) then begin
      if (effects) then begin
         // This only applies limb crippling effects, if any.
         critter_injure(critter, effects);
      end
      // Stop critter for several turns/seconds
      if (stop > 1) then begin
         //debug_log_fmt("Stopping critter %d for %d turns.", critter, stop);
         pbs_trap_hold_critters[critter] := array_fixed([stop, tile_num(critter)]);
         debug_log("Stopping critter: "+debug_array_str(pbs_trap_hold_critters));
      end
      if (pbs_trap_config.reveal_dude) then begin
         debug_log("Making angry!");
         call make_critter_angry(critter);
      end
   end else begin
      // If critter is killed with critter_dmg during combat, kill exp is awarded by the engine.
      // If it happened before combat, we need to do it manually.
      if (not combat_is_initialized) then begin
         killExp := exp_for_kill_critter_pid(obj_pid(critter));
         mod_kill_counter(critter_kill_type(critter), 1);
      end
   end
   return killExp;
end

/**
  Make explosion by emulating all of it's components: area damage, explosion effect, sound
*/
procedure trap_setoff_explosion(variable trapObj, variable mainTarget, variable dmgMin, variable dmgMax, variable radius, variable dmgType, variable isCritical, variable effectPid, variable sfx) begin
   variable obj, totalExp := 0, extraTargets;
   variable
      tile := tile_num(trapObj),
      elev := elevation(trapObj),
      criticalBodyPart := BODY_UNCALLED if isCritical else -1;

   // Main target always gets damaged.
   totalExp += trap_damage_critter(mainTarget, dmgMin, dmgMax, dmgType, criticalBodyPart, 0);

   if (effectPid == 0) then effectPid := PID_EXPLOSION_1;
   if (sfx == 0) then sfx := "WHN1XXX1";
   debug_log("manual explosion!");
   extraTargets := objects_in_radius(tile, radius, elev, OBJ_TYPE_CRITTER);
   foreach (obj in extraTargets) begin
      if (not is_critter_dead(obj) and obj != mainTarget) then begin
         totalExp += trap_damage_critter(obj, dmgMin, dmgMax, dmgType, -1, 0);
      end
   end
   variable effectObj := create_object(effectPid, tile, elev);
   obj_set_light_level(effectObj, 100, 6);
   reg_anim_combat_check(0);
   reg_anim_begin();
   // set_script(effectObj, (SCRIPT_TEST2 - 1) /*bwor 0x05000000*/); // 05 stands for MISC object type
   reg_anim_animate_and_hide(effectObj, ANIM_stand, 0);
   reg_anim_destroy(effectObj);
   reg_anim_end();
   play_sfx("CMBTFLX"); // trap sound
   play_sfx(sfx);
   // give exp when triggering trap out of combat
   if (totalExp > 0) then begin
      gain_exp_for_trapkill(totalExp)
   end
end


/**
  Hit critter by "melee" trap (spikes, etc.)
*/
procedure trap_setoff_melee(variable critter, variable dmgMin, variable dmgMax, variable dmgType, variable isCritical, variable stopTurns) begin
   variable
      criticalBodyPart := (BODY_HIT_RIGHT_LEG + random(0, 1)) if isCritical else -1,
      killExp := trap_damage_critter(critter, dmgMin, dmgMax, dmgType, criticalBodyPart, stopTurns);

   play_sfx("FLRTRAP");
   play_sfx("WH82FXX1");
   if (killExp > 0) then begin
      debug_log("Giving exp for kill..");
      gain_exp_for_trapkill(killExp)
   end
end

procedure get_suitable_armament_in_inventory(variable critter, variable trapType) begin
   variable item, lastPid, list;
   lastPid := get_sfall_global_int(SGVAR_TRAPS_LAST_ARMAMENT);
   // first search for last used item PID
   if (lastPid) then begin
      item := obj_carrying_pid_obj(critter, lastPid);
      if (item) then return item;
   end
   // if none, then search for any suitable armament
   list := inven_as_array(critter);
   foreach item in list begin
      if is_suitable_armament(obj_pid(item), trapType) then return item;
   end
   return 0;
end

/*
   Checks if trap can be placed at the current tile and creates trap if it is
   Returns true on success, false if trap could not be placed
*/
procedure try_assemble_trap(variable critter, variable item) begin
variable begin
   charges; trapType; trapObj; trapKitPid;
end
   if (critter and item and (get_game_mode == 0 or get_game_mode == INVENTORY)) then
   begin
      trapKitPid := obj_pid(item);
      if (tile_contains_any_trap(tile_num(critter), elevation(critter))) then begin
         display_msg(traps_mstr(401));
      end else begin
         charges := get_weapon_ammo_count(item);
         if (charges == 0 or charges == -1) then begin
            charges := get_proto_data(trapKitPid, PROTO_MI_CHARGES);
         end
         //display_msg("charges: "+charges);
         trapType := trap_type_by_trapkit_pid(trapKitPid);
         trapObj := create_trap_object(trapType, tile_num(critter), elevation(critter), charges);
         //call add_trap_info(trapObj, trapType, charges);
         display_msg(traps_mstr(203));
         return true;
      end
   end else if (combat_is_initialized) then begin
      display_msg(traps_mstr(461));
      //end else if (get_game_mode bwand INVENTORY) then begin
      //   display_msg(traps_mstr(460));
   end
   return false;
end


#endif
