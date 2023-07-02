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

#define is_explosive_pid(pid)		(pid == PID_FRAG_GRENADE or pid == PID_PBS_HOMEMADE_GRENADE \
                or pid == PID_DYNAMITE or pid == PID_PLASTIC_EXPLOSIVES \
                or pid == PID_PULSE_GRENADE or pid == PID_PLASMA_GRENADE or pid == PID_MOLOTOV_COCKTAIL)

#define is_explosion_misc_pid(pid)  (pid == PID_EXPLOSION_1 or pid == PID_EXPLOSION_2 or pid == PID_EXPLOSION_3 or pid == PID_EXPLOSION_4 or pid == PID_EXPLOSION_5 or pid == PID_EXPLOSION_6 or pid == PID_EXPLOSION_EMP_1 or pid == PID_EXPLOSION_EMP_2 or pid == PID_EXPLOSION_PLASMA_1)

#define global_traps        (load_create_array(ARR_TRAPS, 0))

#define TRAPINFO_SIZE        (10)

#define TRAPINFO_OFS_INDEX   (0) // trap record start index in SGVAR_TRAPS_BY_DUDE array
#define TRAPINFO_OFS_TILE    (1) // trap tile
#define TRAPINFO_OFS_ELEV    (2) // elevation
#define TRAPINFO_OFS_MAP     (3) // map index
#define TRAPINFO_OFS_TYPE    (4) // trap type
#define TRAPINFO_OFS_ARMPID  (5) // trap armament item PID
#define TRAPINFO_OFS_STATE   (6) // see below
#define TRAPINFO_OFS_OBJPID  (7) // pid of visual object (eg. floor plate)
#define TRAPINFO_OFS_CHARGES (8) // number of uses left
#define TRAPINFO_OFS_FLAGS   (9) // flags, see below
// reserved up to (9)

#define TRAP_STATE_ACTIVE    (0)
#define TRAP_STATE_SETOFF    (1)
#define TRAP_STATE_DISARMED  (2)

#define TRAP_FRAME_DEFAULT   (0)
#define TRAP_FRAME_ACTIVE    (1)

#define TRAP_TYPE_SPIKE      (0)
#define TRAP_TYPE_MINE       (1)
#define TRAP_TYPE_SENSOR     (2)
#define TRAP_TYPE_BEAR       (3)

#define TRAP_FLAG_CRITICAL   (1) // grants critical hit

//#define TRAP_OBJECT_PID             PID_METAL_FLOOR_TRAP_VISIBLE
//#define TRAP_OBJECT_PID_DISARMED    PID_METAL_FLOOR_TRAP_DISARMED

#define is_trap_kit_pid(pid)			(pid == PID_PBS_TRAP_KIT_MINE or pid == PID_PBS_TRAP_KIT_SPIKE or pid == PID_PBS_TRAP_KIT_SENSOR or pid == PID_PBS_TRAP_KIT_BEAR)

pure procedure tile_contains_any_trap(variable tile, variable elev) begin
  variable pids, pid;
  pids := [PID_METAL_FLOOR_TRAP_VISIBLE, PID_METAL_FLOOR_TRAP_DISARMED, PID_METAL_FLOOR_TRAP_DEPRESSED,
            PID_CAVE_FLOOR_TRAP_VISIBLE, PID_CAVE_FLOOR_TRAP_DISARMED, PID_CAVE_FLOOR_TRAP_DEPRESSED,
            PID_PBS_SPIKE_TRAP, PID_PBS_MINE_TRAP, PID_PBS_SENSOR_MINE, PID_PBS_BEAR_TRAP,
            PID_PBS_TRAP_RESERVED_4, PID_PBS_TRAP_RESERVED_6];
  foreach (pid in pids) begin
    if (tile_contains_obj_pid(tile, elev, pid)) then return true;
  end
  return false;
end

/*#define tile_contains_any_trap(tile, elev)		(tile_contains_obj_pid(tile, elev, PID_METAL_FLOOR_TRAP_VISIBLE) \
	or tile_contains_obj_pid(tile, elev, PID_METAL_FLOOR_TRAP_DISARMED) \
	or tile_contains_obj_pid(tile, elev, PID_METAL_FLOOR_TRAP_DEPRESSED) \
	or tile_contains_obj_pid(tile, elev, PID_CAVE_FLOOR_TRAP_VISIBLE) \
	or tile_contains_obj_pid(tile, elev, PID_CAVE_FLOOR_TRAP_DISARMED) \
	or tile_contains_obj_pid(tile, elev, PID_CAVE_FLOOR_TRAP_DEPRESSED))*/

#define trap_index(x,y)  	get_array(x, y + TRAPINFO_OFS_INDEX)
#define trap_tile(x,y)  	get_array(x, y + TRAPINFO_OFS_TILE)
#define trap_elev(x,y)  	get_array(x, y + TRAPINFO_OFS_ELEV)
#define trap_map(x,y)  		get_array(x, y + TRAPINFO_OFS_MAP)
#define trap_type(x,y)  	get_array(x, y + TRAPINFO_OFS_TYPE)
#define trap_armpid(x,y)  get_array(x, y + TRAPINFO_OFS_ARMPID)
#define trap_state(x,y)  	get_array(x, y + TRAPINFO_OFS_STATE)
#define trap_objpid(x,y)  get_array(x, y + TRAPINFO_OFS_OBJPID)
#define trap_charges(x,y) get_array(x, y + TRAPINFO_OFS_CHARGES)
#define trap_flags(x,y)   get_array(x, y + TRAPINFO_OFS_FLAGS)
#define trap_object(x,y)  tile_contains_pid_obj(trap_tile(x,y), trap_elev(x,y), trap_objpid(x,y))

#define is_trap_customizable_type(type)     (type == TRAP_TYPE_MINE or type == TRAP_TYPE_SENSOR)

#define TRAP_SENSOR_CHANCE	 (70)

// custom timed_event's
#define TRAP_EVENT_INIT				(0)  // does nothing, just init the script to map_exit_p_proc will always run
#define TRAP_EVENT_DESTROY			(1)
#define TRAP_EVENT_DEACTIVATE		(2)

#define TRAP_FRIENDFOE_DUDE		(1)
#define TRAP_FRIENDFOE_PARTY		(2)

#define traps_mstr(msg)      message_str(SCRIPT_TEST2, msg)

//#define send_trap_signal(obj, signal, param)				add_timer_event(obj, 3, ((param) * 0x100) + signal)
#define destroy_trap_object(obj)				add_timer_event(obj, 0, TRAP_EVENT_DESTROY)

#define gain_exp_for_trapkill(exp)			give_exp_points(exp); \
											         display_msg(sprintf(traps_mstr(2001), exp));

#define make_critter_angry(obj)         add_array_set(load_create_array(ARR_ANGRY_TEAMS, 0), obj_team(obj))

#define trapkit_pid_by_trap_type(type)    ((type == TRAP_TYPE_SPIKE)*PID_PBS_TRAP_KIT_SPIKE \
                                          +(type == TRAP_TYPE_MINE)*PID_PBS_TRAP_KIT_MINE \
                                          +(type == TRAP_TYPE_SENSOR)*PID_PBS_TRAP_KIT_SENSOR \
                                          +(type == TRAP_TYPE_BEAR)*PID_PBS_TRAP_KIT_BEAR)

#define trap_type_by_trapkit_pid(pid)     ((pid == PID_PBS_TRAP_KIT_SPIKE)*TRAP_TYPE_SPIKE \
                                          +(pid == PID_PBS_TRAP_KIT_MINE)*TRAP_TYPE_MINE \
                                          +(pid == PID_PBS_TRAP_KIT_SENSOR)*TRAP_TYPE_SENSOR \
                                          +(pid == PID_PBS_TRAP_KIT_BEAR)*TRAP_TYPE_BEAR)



procedure get_traps_for_map;
procedure create_trap_object(variable source, variable state, variable tile, variable elev);
procedure add_trap_info(variable trapObj, variable type, variable charges);
procedure arm_trap(variable index, variable pid, variable isCrit);
procedure setoff_trap(variable index, variable victim, variable armpid);

procedure react_hostile_action;
procedure remove_trap_info(variable index);

procedure check_setoff_traps(variable obj, variable arr);
procedure trap_setoff_effect(variable pid, variable obj, variable trapType, variable trapFlags, variable crit);

procedure trap_setoff_explosion(variable trapObj, variable mainTarget, variable dmgMin, variable dmgMax, variable radius, variable dmgType, variable trapFlags, variable pid, variable sfx);
procedure trap_setoff_melee(variable critter, variable dmgMin, variable dmgMax, variable dmgType, variable trapFlags, variable stopTurns);


// Normal variables
variable traps_how_much;

// Exported variables

#ifdef _TRAPS_EXPORT
#define _EXPORT_VAR(name, value)    export variable name := value;
#else
#define _EXPORT_VAR(name, value)    import variable name;
#endif

_EXPORT_VAR(pbs_local_traps, 0)
_EXPORT_VAR(pbs_trap_victims, 0)
_EXPORT_VAR(pbs_traps_last_map, -1)
_EXPORT_VAR(pbs_ini_trap_is_crime, 1)
_EXPORT_VAR(pbs_ini_trap_reveals_dude, 1)
_EXPORT_VAR(pbs_ini_trap_friendfoe, 1)
_EXPORT_VAR(pbs_trap_last_target, 0)
_EXPORT_VAR(pbs_trap_last_target_dead, 0)
_EXPORT_VAR(pbs_trap_hold_critters, 0)

#undef _EXPORT_VAR


// initialize common variables
procedure traps_common_init begin
   // vars
   // trapv := load_create_array_map(ARR_TRAPVARS); // always clean array
   // arrays
   // pbs_local_traps := load_create_array(ARR_TRAPS_LOCAL, 0);
   // pbs_trap_victims := load_create_array_map(ARR_TRAP_VICTIMS);
end

procedure get_traps_for_map begin
   variable ar_global;
   variable ar_map;
   variable i := 0;
   variable local_i := 0;
   variable j := 0;
   //variable num := 0;
   if (cur_map_index != pbs_traps_last_map) then begin
      debug_log("pbs_traps: Rebuilding local traps");
      ar_global := global_traps;
      if (pbs_local_traps) then
         clear_array(pbs_local_traps);
      while (i < len_array(ar_global)) do begin
         // copy only active traps in current map, for optimization
         if (trap_map(ar_global, i) == cur_map_index and trap_state(ar_global, i) == TRAP_STATE_ACTIVE) then begin
            resize_array(pbs_local_traps, len_array(pbs_local_traps) + TRAPINFO_SIZE);
            call copy_array(ar_global, i, pbs_local_traps, local_i, TRAPINFO_SIZE);
            local_i += TRAPINFO_SIZE;
         end
         i += TRAPINFO_SIZE;
      end
      pbs_traps_last_map := cur_map_index;
      //debug_msg("Local traps: "+(local_i/TRAPINFO_SIZE) + ", of total: "+(len_array(ar_global)/TRAPINFO_SIZE));
   end
   i := pbs_local_traps;
   return i;
end

/**
	Create new trap object with correct PID, and init properly. Used when creating and transforming trap.
	@param type   - type of trap
	@param state  - desired state (TRAP_STATE_..), not linked to global array
*/
// TODO: remove state
procedure create_trap_object(variable type, variable state, variable tile, variable elev) begin
	variable begin
		newPid := 0;
		newObj;
	end
	if (type == TRAP_TYPE_SPIKE) then begin
      //   if (state == TRAP_STATE_ACTIVE)    then 
      newPid := PID_PBS_SPIKE_TRAP;
		//else if (state == TRAP_STATE_DISARMED)  then newPid := PID_PBS_SPIKE_TRAP_DISARMED;
		//else if (state == TRAP_STATE_SETOFF)    then newPid := PID_PBS_SPIKE_TRAP_DISARMED;
	end else if (type == TRAP_TYPE_MINE)      then begin
      //   if (state == TRAP_STATE_ACTIVE)    then 
      newPid := PID_PBS_MINE_TRAP;
		//else if (state == TRAP_STATE_DISARMED)  then newPid := PID_PBS_MINE_DISARMED;
		//else if (state == TRAP_STATE_SETOFF)    then newPid := PID_PBS_MINE_DISARMED; // should not be used
	end else if (type == TRAP_TYPE_SENSOR)    then begin
      //   if (state == TRAP_STATE_ACTIVE)    then 
      newPid := PID_PBS_SENSOR_MINE;
		//else if (state == TRAP_STATE_DISARMED)  then newPid := PID_PBS_SENSOR_MINE_DISARMED;
		//else if (state == TRAP_STATE_SETOFF)    then newPid := PID_PBS_SENSOR_MINE_DISARMED; // should not be used
	end else if (type == TRAP_TYPE_BEAR)    then begin
      newPid := PID_PBS_BEAR_TRAP;
   end else begin
      debug_err("Invalid trap type: "+type);
      return 0;
	end
	newObj := create_object_sid(newPid, tile, elev, SCRIPT_TEST2);
	add_timer_event(newObj, 0, TRAP_EVENT_INIT);
	return newObj;
end

/**
  Add new record into trapinfo array
  @param trapObj - objPtr to visual trap object (in unarmed state)
  @param type    - trap type
  @param charges - int, number of charges left in trap
*/
procedure add_trap_info(variable trapObj, variable type, variable charges) begin
   variable begin
      index := 0;
      zero := false;
      ar_global;
      tile;
      elev;
   end
   ar_global := global_traps;
   index := add_array_block(ar_global, TRAPINFO_SIZE);
   tile := tile_num(trapObj);
   elev := elevation(trapObj);
   ar_global[index + TRAPINFO_OFS_INDEX] := index;
   ar_global[index + TRAPINFO_OFS_TILE] := tile;
   ar_global[index + TRAPINFO_OFS_ELEV] := elev;
   ar_global[index + TRAPINFO_OFS_TYPE] := type;
   ar_global[index + TRAPINFO_OFS_OBJPID] := obj_pid(trapObj);
   ar_global[index + TRAPINFO_OFS_MAP] := cur_map_index;
   ar_global[index + TRAPINFO_OFS_STATE] := TRAP_STATE_DISARMED;
   ar_global[index + TRAPINFO_OFS_CHARGES] := charges;
end

/**
  Turn object into a functional trap
  @param index - index of trap info record
  @param pid   - PID of armament object (grenade, dynamite, etc), 0 for non-customizable traps
  @param isCrit - trap is critical
*/
procedure arm_trap(variable index, variable pid, variable isCrit) begin
   variable begin
      ar_global;
      //newObj;
      flags := 0;
   end
   ar_global := global_traps;
   //newObj := create_trap_object(trap_type(ar_global, index), TRAP_STATE_ACTIVE, tile_num(trapObj), elevation(trapObj));
   if (isCrit) then begin
      flags := flags bwor TRAP_FLAG_CRITICAL;
      debug_msg("Critical trap!");
   end
   // update trap info
   ar_global[index + TRAPINFO_OFS_STATE] := TRAP_STATE_ACTIVE;
   ar_global[index + TRAPINFO_OFS_ARMPID] := pid;
   //ar_global[index + TRAPINFO_OFS_OBJPID] := obj_pid(newObj);
   ar_global[index + TRAPINFO_OFS_FLAGS] := flags;
   // this will rebuild local array for next run
   pbs_traps_last_map := -1;
   if (pbs_ini_trap_is_crime) then begin
      call react_hostile_action;
   end
end

/**
	Make trap setoff effect (explosion) and change trap state (or destroy it)
*/
procedure setoff_trap(variable index, variable victim, variable armpid) begin
   variable begin
      ar_global;
      trapObj;
      charges;
      newObj;
   end
   ar_global := global_traps;
   trapObj := trap_object(ar_global, index);
   if armpid == 0 then armpid := trap_armpid(ar_global, index);
   call trap_setoff_effect(armpid, trapObj, trap_type(ar_global, index), trap_flags(ar_global, index), victim);
   charges := trap_charges(ar_global, index);
   if (charges > 1) then begin
      // transform to disarmed state
      //newObj := create_trap_object(trap_type(ar_global, index), TRAP_STATE_SETOFF, tile_num(trapObj), elevation(trapObj));
      //ar_global[index + TRAPINFO_OFS_OBJPID] := obj_pid(newObj);
      ar_global[index + TRAPINFO_OFS_CHARGES] := charges - 1;
      ar_global[index + TRAPINFO_OFS_STATE] := TRAP_STATE_SETOFF;
   end else begin
      // destroy
      call remove_trap_info(index);
   end
   // active state object is always deleted
   //destroy_trap_object(trapObj);
   add_timer_event(trapObj, 0, TRAP_EVENT_DEACTIVATE);
   pbs_traps_last_map := -1;
end

/*
	remove trap info from global array
*/
procedure remove_trap_info(variable index) begin
   variable ar_global;
   ar_global := global_traps;
   call remove_array_block(ar_global, TRAPINFO_SIZE, index);
   pbs_traps_last_map := -1;
end

// TODO: use spatial scripts instead
procedure check_setoff_traps(variable obj, variable arr) begin
   variable begin
      i;
      flag;
   end
   if not(is_critter_dead(obj)
      or (obj == dude_obj and (pbs_ini_trap_friendfoe bwand TRAP_FRIENDFOE_DUDE))
      or (obj != dude_obj and obj_in_party(obj) and (pbs_ini_trap_friendfoe bwand TRAP_FRIENDFOE_PARTY))) then
   begin
      if (arr == 0) then begin
         arr := get_traps_for_map;
      end
      i := 0;
      while (i < len_array(arr)) do begin
         flag := (trap_elev(arr, i) == elevation(obj) and trap_state(arr, i) == TRAP_STATE_ACTIVE);
         if (flag) then begin
            flag := flag and (trap_tile(arr, i) == tile_num(obj));
            // spike or sensor traps go off at 1 hex radius
            if not(flag)
               and (trap_type(arr, i) == TRAP_TYPE_SENSOR or trap_type(arr, i) == TRAP_TYPE_SPIKE)
               and tile_distance(trap_tile(arr, i), tile_num(obj)) == 1
               and random(0, 99) < TRAP_SENSOR_CHANCE then flag := true;
         end
         if (flag) then begin
            call setoff_trap(trap_index(arr, i), obj, 0);
         end
         i += TRAPINFO_SIZE;
      end
   end
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


/**
  Make explosion or other damaging effect based on trap PID
  @param armPid  - pid of trap armament
  @param trapObj  - trap object
  @param trapType  - type of trap
  @param trapFlags  - trap flags
  @param critter - critter recieving the damage
*/
procedure trap_setoff_effect(variable armPid, variable trapObj, variable trapType, variable trapFlags, variable critter) begin
   if (armPid) then begin
      // explosive trap
      variable
      dmgMinMax := get_explosion_damage(armPid),
      dmgMin := dmgMinMax[0],
      dmgMax := dmgMinMax[1],
      radius := 3,
      dmgType := DMG_explosion,
      effectPid, audioSfx;

      if (dmgMin <= 0 and dmgMax <= 0) then begin
         if (proto_data(armPid, it_type) != item_type_weapon) then begin
            debug_err("trap_setoff_effect: Invalid trap armanent pid: "+armPid);
            return;
         end
         // NOT Dynamite, Plastic or custom explosive type
         dmgMin := get_proto_data(armPid, PROTO_WP_DMG_MIN);
         dmgMax := get_proto_data(armPid, PROTO_WP_DMG_MAX);
         dmgType := get_proto_data(armPid, PROTO_WP_DMG_TYPE);
         radius := 2; // default grenade radius
         if (armPid == PID_FRAG_GRENADE or armPid == PID_PBS_HOMEMADE_GRENADE) then begin
            audioSfx := "WHO1XXX" + random(1,2);
         end else if (armPid == PID_MOLOTOV_COCKTAIL) then begin
            dmgType := DMG_fire;
            audioSfx := "WHO1XXX2";
         end else if (armPid == PID_PLASMA_GRENADE) then begin
            effectPid := PID_EXPLOSION_PLASMA_1;
            audioSfx := "WHP1XXX1";
         end else if (armPid == PID_PULSE_GRENADE) then begin
            effectPid := PID_EXPLOSION_EMP_1;
            audioSfx := "WHQ1XXX1";
         end
      end
      call trap_setoff_explosion(trapObj, critter, dmgMin, dmgMax, radius, dmgType, trapFlags, effectPid, audioSfx);
   end else begin
      // "melee" trap
      dmgMin := math_max(get_int_from_ini(INI_FILE, INI_SECTION, "damage_min_"+trapType), 0);
      dmgMax := math_max(get_int_from_ini(INI_FILE, INI_SECTION, "damage_max_"+trapType), 0);

      call trap_setoff_melee(critter, dmgMin, dmgMax, DMG_normal_dam, trapFlags, 3 if trapType == TRAP_TYPE_BEAR else 1);
   end
end

// dude made a hostile act (installed trap), need reaction of nearby critters
procedure react_hostile_action begin
   variable obj;
   foreach (obj in list_as_array(LIST_CRITTERS)) if (obj) then begin
      if (obj != dude_obj
         and not(obj_in_party(obj))
         and tile_distance_objs(obj, dude_obj) <= 15
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
         pbs_trap_hold_critters[critter] := stop;
         debug_log("Stopping critter: "+debug_array_str(pbs_trap_hold_critters));
      end
      if (pbs_ini_trap_reveals_dude) then begin
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
procedure trap_setoff_explosion(variable trapObj, variable mainTarget, variable dmgMin, variable dmgMax, variable radius, variable dmgType, variable trapFlags, variable effectPid, variable sfx) begin
   variable obj, totalExp := 0, extraTargets;
   variable
      tile := tile_num(trapObj),
      elev := elevation(trapObj),
      criticalBodyPart := BODY_UNCALLED if (trapFlags bwand TRAP_FLAG_CRITICAL) else -1;

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
   //add_timer_event(effectObj, 13, TRAP_EVENT_DESTROY);
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
procedure trap_setoff_melee(variable critter, variable dmgMin, variable dmgMax, variable dmgType, variable trapFlags, variable stopTurns) begin
   variable
      criticalBodyPart := (BODY_HIT_RIGHT_LEG + random(0, 1)) if (trapFlags bwand TRAP_FLAG_CRITICAL) else -1,
      killExp := trap_damage_critter(critter, dmgMin, dmgMax, dmgType, criticalBodyPart, stopTurns);

   play_sfx("FLRTRAP");
   play_sfx("WH82FXX1");
   if (killExp > 0) then begin
      debug_log("Giving exp for kill..");
      gain_exp_for_trapkill(killExp)
   end
end

procedure get_suitable_armament_in_inventory(variable critter) begin
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
      if is_explosive_pid(obj_pid(item)) then return item;
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
         trapObj := create_trap_object(trapType, TRAP_STATE_DISARMED, tile_num(critter), elevation(critter));
         call add_trap_info(trapObj, trapType, charges);
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
