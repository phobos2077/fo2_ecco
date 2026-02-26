#ifndef PBS_CAVE_ENC_H
#define PBS_CAVE_ENC_H

#include "ecco_log.h"
#include "ecco_ids.h"
#include "../sfall/lib.arrays.h"
#include "../sfall/lib.math.h"

/*
   Modifications for cave encounters (replaces cvgenenc.h)
*/

// A % chance to get any encounter at all.
#define ENCOUNTER_CHANCE    (66)
#define SKELETON_CHANCE     (50)

variable begin
   cave_areas;
   cave_chests;
   cave_groups_num;
   cave_elevation;

   encounter_pids;
   encounter_sids;
   encounter_group_min;
   encounter_group_max;

   special_theif_encounter;
end

procedure SetEnc(variable min, variable max, variable pids, variable sids, variable isTheif := false) begin
   encounter_group_min := min;
   encounter_group_max := max;
   encounter_pids := pids;
   encounter_sids := sids;
   special_theif_encounter := isTheif;
end

procedure SelectEncounter begin
   variable val, pid, pids, enc;

   val := random(1, 13)
      if random(0, 99) < ENCOUNTER_CHANCE
      else 0;

   debug_log("Rolled encounter: " + val);
   call SetEnc(0, 0, 0, 0);
   if (val == 1) then begin
      if (dude_level < 6) then begin
         pid := PID_GECKO_SMALL;
      end else if (dude_level < 12) then begin
         pid := PID_TOUGH_GECKO_SMALL;
      end else if (dude_level < 13) then begin
         pid := PID_FIRE_GECKO;
      end else begin
         pid := PID_TOUGH_FIRE_GECKO;
      end
      call SetEnc(3, 5, [pid], [SCRIPT_ECGECKO]);
   end else if (val == 2) then begin
      if (dude_level < 5) then begin
         pid := PID_GOLDEN_GECKO;
      end else if (dude_level < 12) then begin
         pid := PID_TOUGH_GOLDEN_GECKO;
      end else if (dude_level < 13) then begin
         pid := PID_FIRE_GECKO;
      end else begin
         pid := PID_TOUGH_FIRE_GECKO;
      end
      call SetEnc(3, 5, [pid], [SCRIPT_ECGECKO]);
   end else if (val == 3) then
      call SetEnc(3, 5, [PID_SMALL_RADSCORPION], [SCRIPT_ECSCORP]);
   else if (val == 4) then
      call SetEnc(3, 5, [PID_LARGE_RADSCORPION], [SCRIPT_ECSCORP]);
   else if (val == 5) then
      call SetEnc(3, 5, [PID_SMALL_DEATHCLAW], [SCRIPT_ZCLDTHCL]);
   else if (val == 6) then
      call SetEnc(5, 5, [PID_LARGE_DEATHCLAW], [SCRIPT_ZCLDTHCL]);
   else if (val == 7) then
      call SetEnc(3, 5, [PID_MUTATED_MOLE_RAT], [SCRIPT_ECRAT]);
   else if (val == 8) then
      call SetEnc(4, 5, [PID_MUTATED_PIG_RAT], [SCRIPT_ECRAT]);
   else if (val == 9) then begin
      if (dude_level < 5) then
         call SetEnc(3, 5, [PID_GECKO_SMALL, PID_GOLDEN_GECKO], [SCRIPT_ECGECKO]);
      else begin
         pids := [PID_TOUGH_GECKO_SMALL, PID_TOUGH_GOLDEN_GECKO];
         if (dude_level > 12) then begin
            call array_push(pids, PID_FIRE_GECKO);
         end else if (dude_level > 15) then begin
            call array_push(pids, PID_TOUGH_FIRE_GECKO);
         end
         call SetEnc(5, 5, pids, [SCRIPT_ECGECKO]);
      end
   end else if (val == 10) then
      call SetEnc(3, 5, [PID_SMALL_RADSCORPION, PID_LARGE_RADSCORPION], [SCRIPT_ECSCORP]);
   else if (val == 11) then
      call SetEnc(5, 5, [PID_SMALL_DEATHCLAW, PID_LARGE_DEATHCLAW], [SCRIPT_ZCLDTHCL]);
   else if (val == 12) then
      call SetEnc(5, 5, [PID_MUTATED_MOLE_RAT, PID_MUTATED_PIG_RAT], [SCRIPT_ECRAT]);
   else if (val == 13) then begin
      if (stat_success(dude_obj, STAT_lu, 2)) then begin
         if (dude_level < 5) then
            call SetEnc(2, 3, [PID_MYSTERIOUS_STRANGER_MALE, PID_MYSTERIOUS_STRANGER_FEMALE], [SCRIPT_ECROBBER], true);
         else if (dude_level < 11) then
            call SetEnc(3, 4, [PID_BOUNTY_MALE_7_12, PID_BOUNTY_FEMALE_7_12], [SCRIPT_ECROBBER], true);
         else
            call SetEnc(3, 4, [PID_BOUNTY_MALE_13_18, PID_BOUNTY_FEMALE_13_18], [SCRIPT_ECROBBER], true);
      end
   end
end

procedure PlaceCritter(variable pid, variable sid, variable baseTile, variable elev) begin
   variable tile;
   variable obj;
   variable i;

   if (pid >= 1) then begin
      tile := tile_num_in_direction(baseTile, Random(0, 5), Random(1, 3));
      obj := create_object_sid(pid, 0, 0, sid);
      critter_attempt_placement(obj, tile, elev);

      while ((tile_distance(tile_num(obj),baseTile) > 5) and (i < 4)) do begin
         tile := tile_num_in_direction(baseTile, Random(0, 5), Random(1, 2));
         ndebug("tile_num == "+tile);
         i+=1;
      end

      if ((i >= 4) and (tile > 0)) then begin
         critter_attempt_placement(obj, baseTile, elev);
      end

      if (tile_distance(tile_num(obj),baseTile) > 5) then begin
         destroy_object(obj);
         ndebug("Couldn't find Safe spot. Destroying Ptr.");
      end
   end
   else begin
      ndebug("Pid < 1. Pid == "+pid+".");
   end
end

procedure PlaceCritterGroup(variable tile, variable elev) begin
   variable count, pid, sid;
   count := random(encounter_group_min, encounter_group_max);
   debug_log_fmt("Placing group of %d at tile %d (%d)", count, tile, elev);
   while (count > 0) do begin
      pid := random(0, len_array(encounter_pids) - 1);
      sid := encounter_sids[pid]
         if len_array(encounter_sids) > pid
         else encounter_sids[0];
      pid := encounter_pids[pid];

      call PlaceCritter(pid, sid, tile, elev);
      count -= 1;
   end
end

procedure PlaceAllCritters(variable areaList, variable numActiveAreas, variable elev) begin
   variable i, idx, tile;

   if (len_array(encounter_pids) < 1) then begin
      debug_err_fmt("Cannot place critters: len_array(encounter_pids) == %d", len_array(encounter_pids));
      return;
   end
   areaList := clone_array(areaList);
   debug_log_fmt("Distributing %d groups of critters throughout %d areas.", numActiveAreas, len_array(areaList));
   for (i := 0; i < numActiveAreas and len_array(areaList) > 0; i++) begin
      idx := random(0, len_array(areaList) - 1);
      tile := areaList[idx];
      call array_cut(areaList, idx, 1);
      call PlaceCritterGroup(tile, elev);
   end
end


procedure PlaceChest(variable tile, variable elev, variable consumablePid, variable weaponPid, variable caps) begin
    variable obj;
    obj := create_object(PID_CHEST, tile, elev);
    if (obj) then begin
        if (consumablePid > 0) then
            add_mult_objs_to_inven(obj, create_object(consumablePid, tile, elev), Random(1, 5));
        if (weaponPid > 0) then
            add_obj_to_inven(obj, create_object(weaponPid, tile, elev));
        item_caps_adjust(obj, caps);
    end
end

#define TIER2_LOOT_LVL    (13)
//#define item_by_tier(pid1, pid2)            (pid1 if dude_level < TIER2_LOOT_LVL else pid2)

procedure PlaceChests(variable elev, variable tile1, variable tile2, variable tile3) begin
    variable pid1, count1, pid2, caps;

    call PlaceChest(tile1, elev,
        PID_STIMPAK if Random(1, 2) == 1 else 0,
        (PID_PBS_MGL if dude_level >= TIER2_LOOT_LVL else PID_PBS_M79)
            if (random(1, 4) == 1)
            else 0,
        20 * Random(1, dude_luck));

    call PlaceChest(tile2, elev,
        PID_STIMPAK if Random(1, 2) == 1 else 0,
        (PID_SUPER_SLEDGE if dude_level >= TIER2_LOOT_LVL else PID_PBS_SPIKED_SLEDGE)
            if (random(1, 4) == 1)
            else 0,
        20 * Random(dude_luck, dude_luck * dude_luck));

    call PlaceChest(tile3, elev,
        (PID_PLASMA_GRENADE if dude_level >= TIER2_LOOT_LVL else PID_FRAG_GRENADE)
            if (random(1, 2) == 1)
            else 0,
        (PID_PLASMA_RIFLE if dude_level >= TIER2_LOOT_LVL else PID_LASER_PISTOL)
            if (random(1, 4) == 1)
            else 0,
        20 * Random(dude_luck, dude_luck * dude_luck));
end




procedure PlaceRocks(variable areaList, variable elev) begin
   variable tile, obj, numRocks, numAreas;

   numAreas := len_array(areaList);
   numRocks := random(1, numAreas);
   debug_log_fmt("Placing %d rocks throughout %d areas.", numRocks, numAreas);

   while (numRocks > 0) do begin
      tile := array_random_value(areaList);
      tile := tile_num_in_direction(tile, Random(0, 5), Random(1, 3));
      obj := create_object_sid(PID_ROCK, 0, 0, -1);
      critter_attempt_placement(obj, tile, elev);
      numRocks -= 1;
   end
end

procedure PlaceSkeleton(variable chestPoints, variable elev) begin
   variable tile, obj, numAreas, maxCaps;

   if (random(0, 99) >= SKELETON_CHANCE) then return;

   tile := array_random_value(chestPoints);

   debug_log_fmt("Placing skeleton at %d (%d).", tile, elev);
   obj := create_object_sid(PID_HUMAN_BONES, tile, elev, -1);

   if (random(1, 2) == 1) then
      add_obj_to_inven(obj, create_object_sid(PID_KNIFE if random(0, 1) else PID_SPEAR, 0, 0, -1));

   if (random(1, 3) == 1) then
      add_obj_to_inven(obj, create_object_sid(PID_STIMPAK if dude_level > 5 else PID_HEALING_POWDER, 0, 0, -1));

   if (random(1, 2) == 1) then
      add_obj_to_inven(obj, create_object_sid(PID_ROPE if random(1, 4) == 1 else PID_PUMP_PARTS, 0, 0, -1));

   if (random(1, 6) == 1) then
      add_obj_to_inven(obj, create_object_sid(PID_HYPODERMIC_NEEDLE, 0, 0, -1));

   if (random(1, 3) == 1) then begin
      maxCaps := ceil((5 + dude_luck) * (30 if dude_level > 10 else 10));
      item_caps_adjust(obj, random(1, maxCaps));
   end
end


procedure DoSetupEncounter begin
   call PlaceRocks(cave_areas, cave_elevation);

   call SelectEncounter;
   if (len_array(encounter_pids) > 0) then begin
      debug_log_fmt("Encounter Pids: %s, Sids: %s", debug_array_str(encounter_pids), debug_array_str(encounter_sids));

      call PlaceAllCritters(cave_areas, cave_groups_num, cave_elevation);

      if special_theif_encounter then
         call PlaceChests(cave_elevation, cave_chests[0], cave_chests[1], cave_chests[2]);
      else
         call PlaceSkeleton(cave_chests, cave_elevation);
   end
   //if (not special_theif_encounter) then
   //   call PlaceSkeleton(cave_chests, cave_elevation);
end

#endif // PBS_CAVE_ENC_H
