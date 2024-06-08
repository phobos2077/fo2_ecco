#include "../sfall/define_lite.h"
#include "../sfall/command_lite.h"
#include "../sfall/sfall.h"
#include "../sfall/lib.strings.h"
#include "../sfall/lib.inven.h"
#include "../headers/teams.h"
#include "ecco.h"

#define _dude_has(pid)  obj_is_carrying_obj_pid(dude_obj, pid)


#define _team(obj)      has_trait(TRAIT_OBJECT,obj,OBJECT_TEAM_NUM)
#define _is_possible_bounty(obj)    (_team(obj) == TEAM_RND_ROBBER)

#define _bounty_redding_counter     get_sfall_global_int(SGVAR_BOUNTY_NUM_ROBBERS)

#define _AMMO_COUNT_DELETED         404

// GVAR_BOUNTY_REDDING statuses:
#define BOUNTY_REDDING_TAKEN        (1)
#define BOUNTY_REDDING_KILLED       (2)
#define BOUNTY_REDDING_REWARD       (3)

// GVAR_BOUNTY_NCR statuses:
#define BOUNTY_NCR_TAKEN1           (1)
#define BOUNTY_NCR_KILLED1          (2)
#define BOUNTY_NCR_REWARD1          (3)
#define BOUNTY_NCR_TAKEN2           (4)
#define BOUNTY_NCR_KILLED2          (5)
#define BOUNTY_NCR_REWARD2          (6)
#define BOUNTY_NCR_TAKEN3           (7)
#define BOUNTY_NCR_KILLED3          (8)
#define BOUNTY_NCR_REWARD3          (9)


#define _dialog_at_node(node)  begin                \
        start_gdialog(NAME, self_obj, 4, -1, -1);   \
		gsay_start;                                 \
		call node;                                  \
		gsay_end;                                   \
		end_dialogue;                               \
    end


#define _is_bounty_outlaw(obj)    (_team(obj) == TEAM_RND_ROGUE and obj_is_carrying_obj_pid(obj, PID_PBS_BONE_AMULET))
#define _TIMER

#ifdef _BOUNTY_ECROBBER

#include "..\sfall\lib.arrays.h"
#include "..\_pbs_headers\ecco_log.h"
#define is_bounty_robber(crit)         (obj_is_carrying_obj_pid(crit, PID_PBS_SEVERED_ARM) > 0)

import variable pbs_random_encounter_placement;

procedure get_placement_by_map begin
   switch (cur_map_index) begin
      case MAP_RND_MOUNTAIN_4:   
         return {
            17078: 1+5, // inside tent
            17476: 1+0,
            17879: 1+2,
            17485: 1+2, // outside near campfire
            17885: 1+5,
            17686: 1+0,
            16890: 1+5, // brewing beer
            18681: 1+0  // near boxes
         };
      case MAP_RND_MOUNTAIN_5:
         return {
            17274: 1+2, // 1st tent (top-right)
            18279: 1+0,
            17075: 1+2,
            17891: 1+0, // middle tent
            17493: 1+4,
            17289: 1+4,
            18103: 1+0, // 3rd tent (bottom-left)
            18501: 1+3,
            18306: 1+5,
            19689: 1+3, // campfires
            20089: 1+4,
            20491: 1+5,
            20093: 1+0,
            19693: 1+0,
            17683: 1+5, // outside, near trunk
            17886: 1+2,
            18080: 1+0
         };
      default:
         return -1;
   end
end

procedure camp_placement begin
   variable
      placement := pbs_random_encounter_placement;

   if (placement == 0) then begin
      placement := get_placement_by_map;
      pbs_random_encounter_placement := placement;
   end
   //debug_log(debug_array_str(placement) if placement > 0 else "nope, map "+cur_map_index);
   if (placement > 0 and len_array(placement) > 0) then begin
      variable
         idx := random(0, len_array(placement) - 1),
         tile := array_key(placement, idx),
         dir := placement[tile] - 1;

      debug_log_fmt("Placing %s at %d facing %d", self_name, tile, dir);
      move_to(self_obj, tile, 0);
      obj_rotate(self_obj, dir);
      unset_array(placement, tile);
   end
end

procedure bounty_hook_destroy begin
    variable item;
    variable othr;
    variable boss;
    variable maxh;
    variable crit;
    crit := self_obj;
    item := obj_carrying_pid_obj(crit, PID_PBS_SEVERED_ARM);
    if (item and _is_possible_bounty(crit)) then begin
        /* not(_dude_has(PID_KNIFE) or _dude_has(PID_COMBAT_KNIFE) or _dude_has(PID_PBS_THROWING_AXE)) or */
        // check for others to decide if this is a leader or not
        // first assume this is the boss
        boss := crit;
        maxh := critter_max_hp(crit);
        foreach (othr in list_as_array(LIST_CRITTERS))
            if (othr and _is_possible_bounty(othr) and critter_max_hp(othr) > maxh) then begin
                maxh := critter_max_hp(crit);
                boss := othr;
            end 

        // delete arm if it's not boss or if arm is damaged
        if (is_critter_corpse_badly_damaged(crit)
            or boss != crit) then
        begin
            call remove_all_items_pid(crit, PID_PBS_SEVERED_ARM);
            debug_msg("REMOVE ARM");
        end
        // reduce counter
        if (_bounty_redding_counter > 0) then begin set_sfall_global(SGVAR_BOUNTY_NUM_ROBBERS, _bounty_redding_counter - 1);
            if (_bounty_redding_counter == 0) then begin
               set_global_var(GVAR_BOUNTY_REDDING, BOUNTY_REDDING_KILLED);
               display_msg(message_str(SCRIPT_RCASCORT, 438));
            end
        end
        debug_msg("Bounty: "+_bounty_redding_counter);
    end
end

#endif // _BOUNTY_ECROBBER



#ifdef _BOUNTY_ECROGUE

//#define TIMER_SET_BOUNTY    2
#define LVAR_IS_BOUNTY  2

#define i_am_bounty     local_var(LVAR_IS_BOUNTY)

/*procedure timed_event_p_proc begin
    variable msg;
    msg := "Rogue timer event";
    if (fixed_param == TIMER_SET_BOUNTY) then begin
        set_local_var(LVAR_IS_BOUNTY, 1);
        msg := msg + ", SET BOUNTY";
    end
    display_msg(msg);
end*/

pure procedure is_bounty_outlaw_on_map begin
    variable obj;
    foreach (obj in list_as_array(LIST_CRITTERS))
        if (obj) then if (_is_bounty_outlaw(obj)) then begin
            return true;
        end
    return false;
end

// TODO: interesting critter placement on specific maps
procedure bounty_hook_map_enter begin
    variable obj;
    variable msg;
    msg := "I am rogue";
    if (is_bounty_outlaw_on_map) then begin
        msg := msg + ", and I'm a bounty!";
        set_local_var(LVAR_IS_BOUNTY, 1);
    end
    debug_msg(msg);
end

procedure bounty_hook_destroy begin
    variable item, state, bountyType;
    if (_is_bounty_outlaw(self_obj)) then begin
        item := obj_carrying_pid_obj(self_obj, PID_PBS_BONE_AMULET);
        // ammo count indicates the person which this amulet belongs to
        state := global_var(GVAR_BOUNTY_NCR);
        if (state == BOUNTY_NCR_TAKEN1) then begin
            state := BOUNTY_NCR_KILLED1;
            bountyType := 1;
        end else if (state == BOUNTY_NCR_TAKEN2) then begin
            state := BOUNTY_NCR_KILLED2;
            bountyType := 2;
        end else if (state == BOUNTY_NCR_TAKEN3) then begin
            state := BOUNTY_NCR_KILLED3;
            bountyType := 3;
        end
        set_weapon_ammo_count(item, bountyType);
        set_global_var(GVAR_BOUNTY_NCR, state);
        debug_msg("Killed an outlaw of type: " + get_weapon_ammo_count(item));
    end
end

#endif // _BOUNTY_ECROGUE



#ifdef _BOUNTY_RCASCORT

#define NAME    SCRIPT_RCASCORT

// positive value - bounty status, negative - time to next bounty
#define LVAR_BOUNTY        (4)

#define _PER_BANDIT_REWARD      (300)
#define _QUEST_REWARD_BASE      (1000)

#define is_first_bounty     (local_var(LVAR_BOUNTY) == 0 or local_var(LVAR_BOUNTY) == 1)

// Node045
#define INJECT_ASK_BOUNTY   \
    if (local_var(LVAR_BOUNTY) <= 0) then NOption(401,NodeBountyAsk,004);  \
    else if (global_var(GVAR_BOUNTY_REDDING) == BOUNTY_REDDING_TAKEN) then NOption(404,Node999,004);

// Node002
#define INJECT_GIVE_PROOF   \
    if (obj_is_carrying_obj_pid(dude_obj, PID_PBS_SEVERED_ARM) > 0) then NOption(402,NodeBountyProof,004);

// Node002
#define INJECT_BOUNTY_DONE   \
    if (local_var(LVAR_BOUNTY) > 0 and global_var(GVAR_BOUNTY_REDDING) == BOUNTY_REDDING_KILLED) then NOption(403, NodeBountyReward, 004);

procedure NodeBountyAsk;
procedure NodeBountyHowMuch;
procedure NodeBountyWhere;
procedure NodeBountyAccept;
procedure NodeBountyProof;
//procedure NodeBountyWaiting;
procedure NodeBountyReward;

procedure NodeBountyAsk begin
    if (dude_level < 10) then begin
        Reply(455);
        NOption(456,Node002,004);
        NOption(457,Node999,004);
    end else if (local_var(LVAR_BOUNTY) < 0 and game_time < (-local_var(LVAR_BOUNTY))) then begin
        Reply(445);
        NOption(417,Node999,004);
    end else begin
        if (is_first_bounty) then Reply(405);
        else Reply(450);
        NOption(406,NodeBountyWhere,004);
        NOption(407,NodeBountyHowMuch,004);
        NOption(408,Node999,004);
    end
end

procedure NodeBountyHowMuch begin
    Reply(410);
    NOption(411,NodeBountyWhere,004);
    NOption(412,Node999,004);
end

procedure NodeBountyWhere begin
    Reply(415);
    NOption(416,NodeBountyAccept,004);
    NOption(417,NodeBountyAccept,004);
end

procedure NodeBountyAccept begin
    variable firstTime;
    firstTime := is_first_bounty;
    set_sfall_global(SGVAR_BOUNTY_NUM_ROBBERS, random(15,20));
    set_global_var(GVAR_BOUNTY_REDDING, BOUNTY_REDDING_TAKEN);
    if (firstTime) then begin
        set_local_var(LVAR_BOUNTY, 1);
        call add_item_pid(dude_obj, PID_COMBAT_KNIFE);
        Reply(420);
        NOption(421,Node999,004);
        NOption(422,Node999,004);
    end else begin
        set_local_var(LVAR_BOUNTY, 2);
        call Node999;
    end
end

procedure NodeBountyProof begin
    variable num;
    num := obj_is_carrying_obj_pid(dude_obj, PID_PBS_SEVERED_ARM);
    call remove_items_pid(dude_obj, PID_PBS_SEVERED_ARM, num);
    item_caps_adjust(dude_obj, _PER_BANDIT_REWARD*num);
    Reply(430);
    NOption(431,Node999,004);
end

/*procedure NodeBountyWaiting begin
    Reply(440);
    INJECT_GIVE_PROOF
    NOption(286, Node999, 004);
end*/

procedure NodeBountyReward begin
    if (is_first_bounty) then begin
        give_exp_points(500);
        display_msg(g_mstr(100) + 500 + g_mstr(101));
    end
    item_caps_adjust(dude_obj, _QUEST_REWARD_BASE*(1 + (dude_level > 15)));
    set_local_var(LVAR_BOUNTY, -(game_time + ONE_GAME_DAY * random(30, 60)));
    set_global_var(GVAR_BOUNTY_REDDING, BOUNTY_REDDING_REWARD);
    Reply(435);
    INJECT_GIVE_PROOF
    NOption(436,Node999,004);
    NOption(437,Node999,004);
end

#endif // _BOUNTY_RCASCORT




#ifdef _BOUNTY_SCKARL

#define NAME    SCRIPT_SCKARL

// Bounty quest status (lvar):
// 0 - not taken
// 1 - First bounty
// 2 - Second bounty
// ....
// -1 - First bounty finished
// -2 - Second bounty finished
// ...


#define LVAR_BOUNTY        (7)

#define _REWARD_1               (1000)
#define _REWARD_2               (2000)
#define _REWARD_3               (5000)

#define bounty_status       local_var(LVAR_BOUNTY)
#define is_first_bounty     (local_var(LVAR_BOUNTY) == 0 or local_var(LVAR_BOUNTY) == 1)

// Node006
#define INJECT_ASK_BOUNTY   \
    if (local_var(LVAR_BOUNTY) == 0) then NOption(201, NodeBountyIntro, 004);  \
    else if (local_var(LVAR_BOUNTY) < 0) then NOption(202, NodeBountyAsk, 004);  \
    else NOption(203, NodeBountyAsk, 004);

// Node
#define INJECT_BOUNTY_DONE   \
    if (obj_is_carrying_obj_pid(dude_obj, PID_PBS_BONE_AMULET) or (local_var(LVAR_BOUNTY) > 0 and global_var(GVAR_BOUNTY_NCR) <= 0)) then NOption(204, NodeBountyClaim, 004);

procedure NodeBountyIntro;
procedure NodeBountyExplain;
procedure NodeBountyAsk;
procedure NodeBountyProof;
//procedure NodeBountyWhere;
//procedure NodeBountyAccept;
//procedure NodeBountyWaiting;
procedure NodeBountyClaim;
procedure NodeBountyClaimFail;
procedure NodeBountyReward;

procedure NodeBountyIntro begin
    Reply(205);
    NOption(206,NodeBountyAsk,004);
    NOption(207,NodeBountyExplain,004);
    NOption(208,Node999,004);
end

procedure NodeBountyExplain begin
    Reply(215);
    NOption(206,NodeBountyAsk,004);
    NOption(208,Node999,004);
end

/*procedure GetBountyConfig begin
   return [
      {"reward": _REWARD_1, "minLvl": 10, "descMsg": 220, "taken": 1, "killed": 2, "done": 3},
      {"reward": _REWARD_2, "minLvl": 15, "descMsg": 220, "taken": 1, "killed": 2, "done": 3},
      {"reward": _REWARD_3, "minLvl": 20, "descMsg": 220, "taken": 1, "killed": 2, "done": 3},
   ];
end*/

procedure NodeBountyAsk begin
    variable minLvl, descMsg, bountyType, bountyAmount, takenState;

    if (bounty_status <= 0) then bountyType := -bounty_status + 1;
    else bountyType := bounty_status;
    if (bountyType == 1) then begin
        minLvl := 10;
        bountyAmount := _REWARD_1;
        descMsg := 220;
        takenState := BOUNTY_NCR_TAKEN1;
    end else if (bountyType == 2) then begin
        minLvl := 15;
        bountyAmount := _REWARD_2;
        descMsg := 230;
        takenState := BOUNTY_NCR_TAKEN2;
    end else if (bountyType == 3) then begin
        minLvl := 20;
        bountyAmount := _REWARD_3;
        descMsg := 235;
        takenState := BOUNTY_NCR_TAKEN3;
    end
    if (local_var(LVAR_BOUNTY) <= -3) then begin // last bounty was done
        Reply(265);
        NOption(266,Node999,004);
        NOption(267,Node999,004);
    end else if (dude_level < minLvl) then begin  // dude doesn't qualify
        Reply(210);
        NOption(211,Node999,004);
    end else begin
        // this quest is accepted automatically, it's a bounty hunt after all
        if (bounty_status <= 0) then begin
            set_global_var(GVAR_BOUNTY_NCR, takenState);
            set_local_var(LVAR_BOUNTY, bountyType);
        end
        Reply(parse_str_2(mstr(descMsg), bountyAmount, ""));
        NOption(221, NodeBountyProof, 004);
        NOption(226, Node999, 004);
    end
end

procedure NodeBountyProof begin
    Reply(225);
    NOption(226,Node999,004);
end

/*procedure NodeBountyWaiting begin
    Reply(440);
    INJECT_GIVE_PROOF
    NOption(286, Node999, 004);
end*/

procedure NodeBountyClaim begin
    Reply(250);
    if (obj_is_carrying_obj_pid(dude_obj, PID_PBS_BONE_AMULET)) then NOption(251,NodeBountyReward,004);
    NOption(252,NodeBountyClaimFail,004);
end

#define set_bounty_over     set_local_var(LVAR_BOUNTY, -bounty_status)

procedure NodeBountyClaimFail begin
   variable state;
    // set quest as completed if the guy is really killed
    state := global_var(GVAR_BOUNTY_NCR);
    if (state == BOUNTY_NCR_KILLED1 or state == BOUNTY_NCR_KILLED2 or state == BOUNTY_NCR_KILLED3) then set_bounty_over;
    Reply(260);
    NOption(202,NodeBountyAsk,004);
    NOption(261,Node999,004);
end

procedure NodeBountyReward begin
    variable bountyType, maxState, overState;
    variable item;
    variable bountyAmount := 0;
    item := obj_carrying_pid_obj(dude_obj, PID_PBS_BONE_AMULET);
    // accumulate bounty amount for all amulets (all of them should not stack in inventory, and have different ammo count)
    maxState := 0;
    while (item > 0) do begin
        bountyType := get_weapon_ammo_count(item);
        if (bountyType == 1) then begin
           bountyAmount += _REWARD_1;
           overState := BOUNTY_NCR_REWARD1;
        end else if (bountyType == 2) then begin
           bountyAmount += _REWARD_2;
           overState := BOUNTY_NCR_REWARD2;
        end else if (bountyType == 3) then begin
           bountyAmount += _REWARD_3;
           overState := BOUNTY_NCR_REWARD3;
        end
        if (overState > maxState) then maxState := overState;
        // set current bounty quest as finished, only if you brought appropriate item
        if (bountyType == bounty_status) then begin
            give_exp_points(250);
            display_msg(g_mstr(100) + 250 + g_mstr(101));
            set_bounty_over;
        end
        call remove_item_obj(dude_obj, item);
        item := obj_carrying_pid_obj(dude_obj, PID_PBS_BONE_AMULET);
    end
    if (maxState > global_var(GVAR_BOUNTY_NCR)) then set_global_var(GVAR_BOUNTY_NCR, maxState);
    item_caps_adjust(dude_obj, bountyAmount);
    Reply(255);
    NOption(202,NodeBountyAsk,004);
    NOption(256,Node999,004);
end

#endif // _BOUNTY_SCKARL
