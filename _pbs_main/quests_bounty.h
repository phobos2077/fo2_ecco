#include "define_lite.h"
#include "command_lite.h"
#include "mod.h"
#include "sfall.h"
#include "lib.strings.h"
#include "..\headers\teams.h"

#include "lib.inven.h"

#define _dude_has(pid)  obj_is_carrying_obj_pid(dude_obj, pid) 

        
#define _team(obj)      has_trait(TRAIT_OBJECT,obj,OBJECT_TEAM_NUM)
#define _is_possible_bounty(obj)    (_team(obj) == TEAM_RND_ROBBER)

#define _bounty_redding_counter     global_var(GVAR_BOUNTY_REDDING)

#define _AMMO_COUNT_DELETED         404

#define _dialog_at_node(node)  begin                \
        start_gdialog(NAME, self_obj, 4, -1, -1);   \
		gsay_start;                                 \
		call node;                                  \
		gsay_end;                                   \
		end_dialogue;                               \
    end
    
    
#define _is_bounty_outlaw(obj)    (_team(obj) == TEAM_RND_ROGUE and obj_is_carrying_obj_pid(obj, PID_PBS_BONE_AMULET))
#define _TIMER

/*procedure bounty_hook_deathanim2(variable crit, variable animID) begin
    variable item;
    item := obj_carrying_pid_obj(crit, PID_PBS_SEVERED_ARM);
    if (item and _is_possible_bounty(crit)) then begin
        // if wrong animation - mark arm for removal
        if () then
        begin
            set_weapon_ammo_count(item, _AMMO_COUNT_DELETED);
            debug_msg("MARK ARM for removal - wrong animation");
        end
    end
end*/


#ifdef _BOUNTY_ECROBBER

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
        foreach othr in list_as_array(LIST_CRITTERS) if (othr) then if (_is_possible_bounty(othr) and critter_max_hp(othr) > maxh) then begin
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
        if (_bounty_redding_counter > 0) then set_global_var(GVAR_BOUNTY_REDDING, _bounty_redding_counter - 1);
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
    foreach obj in list_as_array(LIST_CRITTERS) if (obj) then if (_is_bounty_outlaw(obj)) then begin
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
    variable item;
    if (_is_bounty_outlaw(self_obj)) then begin
        item := obj_carrying_pid_obj(self_obj, PID_PBS_BONE_AMULET);
        // ammo count indicates the person which this amulet belongs to
        set_weapon_ammo_count(item, global_var(GVAR_BOUNTY_NCR));
        set_global_var(GVAR_BOUNTY_NCR, 0);
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
    else if (global_var(GVAR_BOUNTY_REDDING) > 0) then NOption(404,Node999,004);
    
// Node002
#define INJECT_GIVE_PROOF   \
    if (obj_is_carrying_obj_pid(dude_obj, PID_PBS_SEVERED_ARM) > 0) then NOption(402,NodeBountyProof,004);
    
// Node002
#define INJECT_BOUNTY_DONE   \
    if (local_var(LVAR_BOUNTY) > 0 and global_var(GVAR_BOUNTY_REDDING) < 1) then NOption(403, NodeBountyReward, 004);

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
    set_global_var(GVAR_BOUNTY_REDDING, random(15,25)); // for WORLDMAP logic (should be random(15,25))
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
    set_local_var(LVAR_BOUNTY, -(game_time + ONE_GAME_DAY*random(14,30)));
    Reply(435);
    INJECT_GIVE_PROOF
    NOption(436,Node999,004);
    NOption(437,Node999,004);
end

#endif // _BOUNTY_RCASCORT




#ifdef _BOUNTY_SCKARL

#define NAME    SCRIPT_SCKARL

// Bounty quest status:
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

procedure NodeBountyAsk begin
    variable minLvl;
    variable descMsg;
    variable bountyType;
    variable bountyAmount;
    if (bounty_status <= 0) then bountyType := -bounty_status + 1;
    else bountyType := bounty_status;
    if (bountyType == 1) then begin
        minLvl := 10;
        bountyAmount := _REWARD_1;
        descMsg := 220;
    end else if (bountyType == 2) then begin
        minLvl := 15;
        bountyAmount := _REWARD_2;
        descMsg := 230;
    end else if (bountyType == 3) then begin
        minLvl := 20;
        bountyAmount := _REWARD_3;
        descMsg := 235;
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
            set_global_var(GVAR_BOUNTY_NCR, bountyType);
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
    // set quest as completed if the guy is really killed
    if (global_var(GVAR_BOUNTY_NCR) == 0) then set_bounty_over;
    Reply(260);
    NOption(202,NodeBountyAsk,004);
    NOption(261,Node999,004);
end

procedure NodeBountyReward begin
    variable bountyType;
    variable item;
    variable bountyAmount := 0;
    item := obj_carrying_pid_obj(dude_obj, PID_PBS_BONE_AMULET);
    // accumulate bounty amount for all amulets (all of them should not stack in inventory, and have different ammo count)
    while (item > 0) do begin
        bountyType := get_weapon_ammo_count(item);
        if (bountyType == 1) then bountyAmount += _REWARD_1;
        else if (bountyType == 2) then bountyAmount += _REWARD_2;
        else if (bountyType == 3) then bountyAmount += _REWARD_3;
        // set current bounty quest as finished, only if you brought appropriate item
        if (bountyType == bounty_status) then begin 
            give_exp_points(250);
            display_msg(g_mstr(100) + 200 + g_mstr(101));
            set_bounty_over; 
        end
        remove_item_obj(dude_obj, item);
        item := obj_carrying_pid_obj(dude_obj, PID_PBS_BONE_AMULET);
    end
    item_caps_adjust(dude_obj, bountyAmount);
    Reply(255);
    NOption(202,NodeBountyAsk,004);
    NOption(256,Node999,004);
end

#endif // _BOUNTY_SCKARL
