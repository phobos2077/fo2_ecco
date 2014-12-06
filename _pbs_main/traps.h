/*
	Headers for Combat rebalance and trap system by phobos2077
*/

#ifndef PBS_TRAPS_H
#define PBS_TRAPS_H

#include "mod.h"
#include "sfall.h"
#include "lib.arrays.h"
#include "lib.strings.h"
#include "lib.inven.h"
#include "lib.misc.h"
#include "miscpid.h"

#define MELEE_TRAP_ARMAMENT_PID		PID_PLANT_SPIKE

#define is_explosive_pid(pid)		(pid == PID_FRAG_GRENADE or pid == PID_PBS_HOMEMADE_GRENADE \
                or pid == PID_DYNAMITE or pid == PID_PLASTIC_EXPLOSIVES \
                or pid == PID_PULSE_GRENADE or pid == PID_PLASMA_GRENADE or pid == PID_MOLOTOV_COCKTAIL)
                
#define is_suited_for_trap_pid(pid)   (is_explosive_pid(pid) or pid == PID_PLANT_SPIKE)

#define get_expected_damage(obj, dmg, dmgType)	((critter_dt_by_dmg_type(obj, dmgType) < dmg)* \
												(critter_dr_by_dmg_type(obj, dmgType) < 100)* \
							ceil((dmg - critter_dt_by_dmg_type(obj, dmgType))*(100 - critter_dr_by_dmg_type(obj, dmgType))/100.0))

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
// reserved up to (9)

#define TRAP_STATE_ACTIVE    (0)
#define TRAP_STATE_SETOFF    (1)
#define TRAP_STATE_DISARMED  (2)

#define TRAP_TYPE_SPIKE     (0)
#define TRAP_TYPE_MINE      (1)
#define TRAP_TYPE_SENSOR    (2)

//#define TRAP_OBJECT_PID             PID_METAL_FLOOR_TRAP_VISIBLE
//#define TRAP_OBJECT_PID_DISARMED    PID_METAL_FLOOR_TRAP_DISARMED

#define is_trap_kit_pid(pid)			(pid == PID_PBS_TRAP_KIT_MINE or pid == PID_PBS_TRAP_KIT_SPIKE or pid == PID_PBS_TRAP_KIT_SENSOR)
#define is_explosive_trap_kit_pid(pid)	(pid == PID_PBS_TRAP_KIT)
#define is_melee_trap_kit_pid(pid)		(pid == PID_PBS_TRAP_KIT_MELEE)
#define is_explosive_trap_pid(pid)		(pid == PID_METAL_FLOOR_TRAP_VISIBLE or pid == PID_METAL_FLOOR_TRAP_DISARMED or pid == PID_METAL_FLOOR_TRAP_DEPRESSED)
#define is_melee_trap_pid(pid)			(pid == PID_CAVE_FLOOR_TRAP_VISIBLE or pid == PID_CAVE_FLOOR_TRAP_DISARMED or pid == PID_CAVE_FLOOR_TRAP_DEPRESSED)
#define is_disarmed_trap_pid(pid)		(pid == PID_METAL_FLOOR_TRAP_DISARMED or pid == PID_CAVE_FLOOR_TRAP_DISARMED)
#define is_armed_trap_pid(pid)			(pid == PID_METAL_FLOOR_TRAP_VISIBLE or pid == PID_CAVE_FLOOR_TRAP_VISIBLE)

pure procedure tile_contains_any_trap(variable tile, variable elev) begin
  variable pids, pid;
  pids := [PID_METAL_FLOOR_TRAP_VISIBLE, PID_METAL_FLOOR_TRAP_DISARMED, PID_METAL_FLOOR_TRAP_DEPRESSED, 
            PID_CAVE_FLOOR_TRAP_VISIBLE, PID_CAVE_FLOOR_TRAP_DISARMED, PID_CAVE_FLOOR_TRAP_DEPRESSED, 
            PID_PBS_SPIKE_TRAP_DISARMED, PID_PBS_SPIKE_TRAP, 
            PID_PBS_MINE_DISARMED, PID_PBS_MINE,
            PID_PBS_SENSOR_MINE_DISARMED, PID_PBS_SENSOR_MINE];
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
#define trap_object(x,y)  tile_contains_pid_obj(trap_tile(x,y), trap_elev(x,y), trap_objpid(x,y))

#define is_trap_customizable_type(type)     is_in_array(type, temp_list2(TRAP_TYPE_MINE, TRAP_TYPE_SENSOR))

#define TRAP_SPIKE_MINDMG		 (7)
#define TRAP_SPIKE_MAXDMG		(40)

#define TRAP_SENSOR_CHANCE	 (70)

// custom timed_event's
#define TRAP_EVENT_INIT					(0)  // does nothing, just init the script to map_exit_p_proc will always run
#define TRAP_EVENT_DESTROY			(1)

#define TRAP_FRIENDFOE_DUDE			(1)
#define TRAP_FRIENDFOE_PARTY		(2)

//#define send_trap_signal(obj, signal, param)				add_timer_event(obj, 3, ((param) * 0x100) + signal)
#define destroy_trap_object(obj)				add_timer_event(obj, 0, TRAP_EVENT_DESTROY)

#define gain_exp_for_trapkill(exp)			give_exp_points(exp); \
											display_msg(message_str(SCRIPT_TEST2, 2001)+exp+message_str(SCRIPT_TEST2, 2002));
                      
                      
#define trapkit_pid_by_trap_type(type)    ((type == TRAP_TYPE_SPIKE)*PID_PBS_TRAP_KIT_SPIKE \
                                          +(type == TRAP_TYPE_MINE)*PID_PBS_TRAP_KIT_MINE \
                                          +(type == TRAP_TYPE_SENSOR)*PID_PBS_TRAP_KIT_SENSOR)
                                          
#define trap_type_by_trapkit_pid(pid)     ((pid == PID_PBS_TRAP_KIT_SPIKE)*TRAP_TYPE_SPIKE \
                                          +(pid == PID_PBS_TRAP_KIT_MINE)*TRAP_TYPE_MINE \
                                          +(pid == PID_PBS_TRAP_KIT_SENSOR)*TRAP_TYPE_SENSOR)

#define traps_mstr(msg)      message_str(SCRIPT_TEST2, msg)


procedure get_traps_for_map;
procedure create_trap_object(variable source, variable state, variable tile, variable elev);
procedure add_trap_info(variable trapobj, variable type, variable charges);
procedure arm_trap(variable index, variable pid);
procedure setoff_trap(variable index, variable victim, variable armpid);

procedure react_hostile_action;
procedure remove_trap_info(variable index);

procedure check_setoff_traps(variable obj, variable arr);
procedure trap_setoff_effect(variable pid, variable obj, variable crit);

procedure manual_trap_explosion(variable tile, variable elev, variable dmgMin, variable dmgMax, variable radius, variable dmgType, variable pid, variable sfx);
procedure critter_dmg_trap(variable obj, variable dmg, variable dmgType);

// common variables for all trap system scripts
variable ar_traps_local;
variable ini_trap_is_crime := 1;
variable ini_trap_reveals_dude := 1;
variable ini_trap_friendfoe := 1;

procedure get_traps_for_map begin
  variable ar_global;
  variable ar_map;
  variable i := 0;
  variable local_i := 0;
  variable j := 0;
  //variable num := 0;
  if (cur_map_index != get_sfall_global_int(SGVAR_TRAPS_LAST_MAP)) then begin
    debug_msg("Rebuild local traps");
    ar_global := global_traps;
    ar_traps_local := load_create_array(ARR_TRAPS_LOCAL, 0);
    resize_array(ar_traps_local, 0);
    while (i < len_array(ar_global)) do begin
      // copy only active traps in current map, for optimization
      if (trap_map(ar_global, i) == cur_map_index and trap_state(ar_global, i) == TRAP_STATE_ACTIVE) then begin
        resize_array(ar_traps_local, len_array(ar_traps_local) + TRAPINFO_SIZE);
        call copy_array(ar_global, i, ar_traps_local, local_i, TRAPINFO_SIZE);
        local_i += TRAPINFO_SIZE;
      end
      i += TRAPINFO_SIZE;
    end
    set_sfall_global(SGVAR_TRAPS_LAST_MAP, cur_map_index);
    //debug_msg("Local traps: "+(local_i/TRAPINFO_SIZE) + ", of total: "+(len_array(ar_global)/TRAPINFO_SIZE));
  end else begin
    ar_traps_local := load_create_array(ARR_TRAPS_LOCAL, 0);
  end
  return ar_traps_local;
end

/**
	Create new trap object with correct PID, and init properly. Used when creating and transforming trap.
	@param type   - type of trap
	@param state  - desired state (TRAP_STATE_..), not linked to global array
*/
procedure create_trap_object(variable type, variable state, variable tile, variable elev) begin
	variable begin 
		newpid := 0;
		newobj;
	end
	if (type == TRAP_TYPE_SPIKE) then begin
         if (state == TRAP_STATE_ACTIVE)    then newpid := PID_PBS_SPIKE_TRAP;
		else if (state == TRAP_STATE_DISARMED)  then newpid := PID_PBS_SPIKE_TRAP_DISARMED;
		else if (state == TRAP_STATE_SETOFF)    then newpid := PID_PBS_SPIKE_TRAP_DISARMED;
	end else if (type == TRAP_TYPE_MINE)      then begin
         if (state == TRAP_STATE_ACTIVE)    then newpid := PID_PBS_MINE;
		else if (state == TRAP_STATE_DISARMED)  then newpid := PID_PBS_MINE_DISARMED;
		else if (state == TRAP_STATE_SETOFF)    then newpid := PID_PBS_MINE_DISARMED; // should not be used
	end else if (type == TRAP_TYPE_SENSOR)    then begin
         if (state == TRAP_STATE_ACTIVE)    then newpid := PID_PBS_SENSOR_MINE;
		else if (state == TRAP_STATE_DISARMED)  then newpid := PID_PBS_SENSOR_MINE_DISARMED;
		else if (state == TRAP_STATE_SETOFF)    then newpid := PID_PBS_SENSOR_MINE_DISARMED; // should not be used
	end
  if (newpid == 0) then return 0; // something is wrong..
	newobj := create_object_sid(newpid, tile, elev, SCRIPT_TEST2);
	add_timer_event(newobj, 0, TRAP_EVENT_INIT);
	return newobj;
end

/**
  Add new record into trapinfo array
  @param trapobj - objPtr to visual trap object (in unarmed state)
  @param type    - trap type
  @param charges - int, number of charges left in trap
*/
procedure add_trap_info(variable trapobj, variable type, variable charges) begin
  variable begin
    index := 0;
    zero := false;
    ar_global;
    tile;
    elev;
  end
  ar_global := global_traps;
  index := add_array_block(ar_global, TRAPINFO_SIZE);
  tile := tile_num(trapobj);
  elev := elevation(trapobj);
  ar_global[index + TRAPINFO_OFS_INDEX] := index;
  ar_global[index + TRAPINFO_OFS_TILE] := tile;
  ar_global[index + TRAPINFO_OFS_ELEV] := elev;
  ar_global[index + TRAPINFO_OFS_TYPE] := type;
  ar_global[index + TRAPINFO_OFS_OBJPID] := obj_pid(trapobj);
  ar_global[index + TRAPINFO_OFS_MAP] := cur_map_index;
  ar_global[index + TRAPINFO_OFS_STATE] := TRAP_STATE_DISARMED;
  ar_global[index + TRAPINFO_OFS_CHARGES] := charges;
end

/**
  Turn object into a functional trap
  @param index - index of trap info record
  @param pid   - PID of armament object (grenade, dynamite, etc), 0 for non-customizable traps
*/
procedure arm_trap(variable index, variable pid) begin
	variable begin
		ar_global;
		trapobj;
		newobj;
	end
	ar_global := global_traps;
	trapobj := trap_object(ar_global, index);
	newobj := create_trap_object(trap_type(ar_global, index), TRAP_STATE_ACTIVE, tile_num(trapobj), elevation(trapobj));
	// update trap info
	ar_global[index + TRAPINFO_OFS_STATE] := TRAP_STATE_ACTIVE;
	ar_global[index + TRAPINFO_OFS_ARMPID] := pid;
	ar_global[index + TRAPINFO_OFS_OBJPID] := obj_pid(newobj);
	// this will rebuild local array for next run
	set_sfall_global(SGVAR_TRAPS_LAST_MAP, -1); 
	if (ini_trap_is_crime) then begin
		call react_hostile_action;
	end
	destroy_trap_object(trapobj);
end

/**
	Make trap setoff effect (explosion) and change trap state (or destroy it)
*/
procedure setoff_trap(variable index, variable victim, variable armpid) begin
	variable begin
    ar_global;
    trapobj;
    charges;
    newobj;
  end
  ar_global := global_traps;
  trapobj := trap_object(ar_global, index);
  if armpid == 0 then armpid := trap_armpid(ar_global, index);
  call trap_setoff_effect(armpid, trapobj, victim);
  charges := trap_charges(ar_global, index);
	if (charges > 1) then begin
		// transform to disarmed state
		newobj := create_trap_object(trap_type(ar_global, index), TRAP_STATE_SETOFF, tile_num(trapobj), elevation(trapobj));
		ar_global[index + TRAPINFO_OFS_OBJPID] := obj_pid(newobj);
		ar_global[index + TRAPINFO_OFS_CHARGES] := charges - 1;
		ar_global[index + TRAPINFO_OFS_STATE] := TRAP_STATE_SETOFF;
	end else begin
		// destroy
		call remove_trap_info(index);
	end
	// active state object is always deleted
	destroy_trap_object(trapobj);
	set_sfall_global(SGVAR_TRAPS_LAST_MAP, -1); // this will rebuild local array for next run
end

/*
	remove trap info from global array
*/
procedure remove_trap_info(variable index) begin
  variable ar_global;
  ar_global := global_traps;
  call remove_array_block(ar_global, TRAPINFO_SIZE, index);
  set_sfall_global(SGVAR_TRAPS_LAST_MAP, -1);  // this will rebuild local array for next run
end

procedure check_setoff_traps(variable obj, variable arr) begin
  variable begin
    i;
    ar_global;
    trapobj;
    flag;
  end
  if not(is_critter_dead(obj)
    or (obj == dude_obj and (ini_trap_friendfoe bwand TRAP_FRIENDFOE_DUDE))
  	or (obj != dude_obj and obj_in_party(obj) and (ini_trap_friendfoe bwand TRAP_FRIENDFOE_PARTY))) then 
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

/**
  Make explosion or other damaging effect based on trap PID
  @param pid  - pid of trap
  @param obj  - trap object 
  @param crit - critter recieving the damage
*/
procedure trap_setoff_effect(variable pid, variable obj, variable crit) begin
  variable begin
  	minDmg;
  	maxDmg;
  end
  if (pid) then begin
    // explosive trap
    if (pid == PID_FRAG_GRENADE or pid == PID_PBS_HOMEMADE_GRENADE) then begin
      call manual_trap_explosion(tile_num(obj), elevation(obj), get_proto_dmg_min(pid), get_proto_dmg_max(pid), 2, DMG_explosion, 0, "WHO1XXX" + random(1,2));
    end else if (pid == PID_MOLOTOV_COCKTAIL) then begin
      call manual_trap_explosion(tile_num(obj), elevation(obj), get_proto_dmg_min(pid), get_proto_dmg_max(pid), 2, DMG_fire,0, "WHO1XXX2");
    end else if (pid == PID_PLASMA_GRENADE) then begin
      call manual_trap_explosion(tile_num(obj), elevation(obj), get_proto_dmg_min(pid), get_proto_dmg_max(pid), 2, DMG_plasma, PID_EXPLOSION_PLASMA_1,"WHP1XXX1");
    end else if (pid == PID_PULSE_GRENADE) then begin
      call manual_trap_explosion(tile_num(obj), elevation(obj), get_proto_dmg_min(pid), get_proto_dmg_max(pid), 2, DMG_emp, PID_EXPLOSION_EMP_1, "WHQ1XXX1");
    end else if (pid == PID_DYNAMITE) then begin
      // these are experimental values observed with normal explosive detonation
      call manual_trap_explosion(tile_num(obj), elevation(obj), 40, 60, 3, DMG_explosion, 0, 0);
    end else if (pid == PID_PLASTIC_EXPLOSIVES) then begin
      call manual_trap_explosion(tile_num(obj), elevation(obj), 50, 80, 3, DMG_explosion, 0, 0);
    end
  end else begin
    // spike trap
  	// damage affected by dude skill
  	minDmg := TRAP_SPIKE_MINDMG;
  	maxDmg := floor(dude_skill(SKILL_TRAPS) / 3.0);
  	if (maxDmg < minDmg*2) then maxDmg := minDmg*2;
  	else if (maxDmg > TRAP_SPIKE_MAXDMG) then maxDmg := TRAP_SPIKE_MAXDMG;
    call critter_dmg_trap(crit, random(minDmg, maxDmg), DMG_normal_dam);
    if (critter_state(crit) != CRITTER_IS_DEAD) then begin
    	critter_injure(crit, DAM_CRITICAL bwor DAM_LOSE_TURN);
    	set_critter_current_ap(crit, 0);
    end
  end
end

// dude made a hostile act (installed trap), need reaction of nearby critters
procedure react_hostile_action begin
  variable crit;
  variable angry_set;
  angry_set := load_create_array(ARR_ANGRY_TEAMS, 0);
  foreach crit in list_as_array(LIST_CRITTERS) if (crit) then begin
    if (crit != dude_obj 
    	and not(obj_in_party(crit)) 
    	and tile_distance_objs(crit, dude_obj) <= 15
    	and is_human(crit)
    	and obj_can_see_obj(crit, dude_obj)) then 
    begin
      call add_array_set(angry_set, obj_team(crit));
    end
  end
end

/**
  Make explosion by emulating all of it's components: area damage, explosion effect, sound
*/
procedure manual_trap_explosion(variable tile, variable elev, variable dmgMin, variable dmgMax, variable radius, variable dmgType, variable pid, variable sfx) begin
  variable crit;
  variable dist;
  variable expl_obj;
  variable exp := 0;
  variable dmg;
  variable i := 0;
  if (pid == 0) then pid := PID_EXPLOSION_1;
  if (sfx == 0) then sfx := "WHN1XXX1";
  debug_msg("manual explosion!");
  foreach crit in list_as_array(LIST_CRITTERS) if (crit) then begin
    dist := tile_distance(tile, tile_num(crit));
    if (dist <= radius and not(is_critter_dead(crit))) then begin
      // 100% damage if dist is 0 or 1 and reducing down to 50% at point where dist == radius
      dmg := random(dmgMin, dmgMax);
      if dist > 1 then dmg := floor(dmg * (1.0 - (0.5 / (radius - 1))*(dist - 1)));
      critter_dmg(crit, dmg, dmgType);
      if (get_critter_stat(crit, STAT_current_hp) <= get_expected_damage(crit, dmg, dmgType)) then begin
      	exp += exp_for_kill_critter_pid(obj_pid(crit));
      end if (ini_trap_reveals_dude) then begin
        // dude is attacked by victim's team, if he's alive
        call add_array_set(get_global_array_ints(SGVAR_ANGRY_TEAMS), obj_team(crit));
      end
    end
    i++;
  end else debug_msg("WRONG CRITTER PTR");
  expl_obj := create_object(pid, tile, elev);
  obj_set_light_level(expl_obj, 100, 6);
  set_script(expl_obj, (SCRIPT_TEST2 - 1) /*bwor 0x05000000*/); // 05 stands for MISC object type
  anim(expl_obj, ANIM_stand, 0);
  add_timer_event(expl_obj, 13, TRAP_EVENT_DESTROY);
  play_sfx("CMBTFLX"); // trap sound
  play_sfx(sfx);
  if (exp > 0) then begin
  	gain_exp_for_trapkill(exp)
  end
end


/**
  Hit critter by "melee" trap (spikes, etc.)
*/
procedure critter_dmg_trap(variable obj, variable dmg, variable dmgType) begin
  variable expectedDmg, sound, n, victims_set;
  expectedDmg := get_expected_damage(obj, dmg, dmgType);
  if (critter_state(obj) == CRITTER_IS_NORMAL and get_critter_stat(obj, STAT_current_hp) <= expectedDmg) then begin
    //critter_dmg(obj, dmg+2, (dmgType BWOR DMG_BYPASS_ARMOR BWOR DMG_NOANIMATE));
    //anim(obj,ANIM_fall_front,ANIMATE_FORWARD);
    sound := sfx_build_char_name(obj, ANIM_fall_back, snd_die);
    critter_heal(obj, -get_critter_stat(obj,STAT_max_hp));
    reg_anim_clear(obj);
    reg_anim_begin();
    reg_anim_animate(obj, ANIM_fall_back, -1);
    reg_anim_play_sfx(obj, sound, 0);
    reg_anim_animate(obj, ANIM_fall_back_blood, -1);
    reg_anim_end();
    mod_kill_counter(critter_kill_type(obj), 1);
    gain_exp_for_trapkill(exp_for_kill_critter_pid(obj_pid(obj)))
  end else begin
    critter_dmg(obj, dmg, dmgType);
    if (ini_trap_reveals_dude) then begin
      call add_array_set(get_global_array_ints(SGVAR_ANGRY_TEAMS), obj_team(obj));
    end
  end
  play_sfx("FLRTRAP");
  play_sfx("WH82FXX1");
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

/*procedure manual_explosions_cleanup begin
  variable ar;
  variable i;
  variable j;
  
  i:=0;
	
end*/

procedure try_assemble_trap(variable critter, variable item) begin
variable begin
   tmp; charges; trapType; trapobj; pid; obj; n;
end
   if (critter and item and get_game_mode == 0) then
   begin
      pid := obj_pid(item);
      if (tile_contains_any_trap(tile_num(critter), elevation(critter))) then begin
         display_msg(message_str(SCRIPT_TEST2, 401));
      end else begin
         charges := get_weapon_ammo_count(item);
         if (charges == 0 or charges == -1) then begin
            if (pid == PID_PBS_TRAP_KIT_SPIKE) then
               charges := 2;
            else
               charges := 1;
         end
         //display_msg("charges: "+charges);
         trapType := trap_type_by_trapkit_pid(pid);
         trapobj := create_trap_object(trapType, TRAP_STATE_DISARMED, tile_num(critter), elevation(critter));
         call add_trap_info(trapobj, trapType, charges);
         
         if ((critter_inven_obj(critter, INVEN_TYPE_LEFT_HAND) == item) or (critter_inven_obj(critter, INVEN_TYPE_RIGHT_HAND) == item)) then begin
            inven_unwield(critter);
         end

         rm_obj_from_inven(critter, item);
         destroy_object(item);
         
         obj := obj_carrying_pid_obj(critter, pid);
         if (obj) then begin
            n := obj_is_carrying_obj_pid(critter, pid);
            if (n > 1) then begin
               // "split" one object from the stack
               tmp := rm_mult_objs_from_inven(critter, obj, 1);
               tmp := get_weapon_ammo_count(obj);
               set_weapon_ammo_count(obj, -1); // this way the following command should not "merge" this object back into existing stack
               add_obj_to_inven(critter, obj);
               set_weapon_ammo_count(obj, tmp); // change charges back, but the item will remain in separate stack
            end
            wield_obj_critter(critter, obj);
         end
         
         display_msg(message_str(SCRIPT_TEST2, 203));
      end
   end else if (combat_is_initialized) then begin
      display_msg(traps_mstr(461));
   end else if (get_game_mode bwand INVENTORY) then begin
      display_msg(traps_mstr(460));
   end
end


#endif
