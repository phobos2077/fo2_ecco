#include "../sfall/define_lite.h"
#include "../sfall/command_lite.h"
#include "../sfall/lib.strings.h"
#include "../sfall/lib.inven.h"
#include "../sfall/sfall.h"
#include "../headers/teams.h"

#include "ecco.h"

// common stuff BEGIN

#define _dude_has(pid)  obj_is_carrying_obj_pid(dude_obj, pid) 

#define _dialog_at_node(node)  begin                \
        start_gdialog(NAME, self_obj, 4, -1, -1);   \
		gsay_start;                                 \
		call node;                                  \
		gsay_end;                                   \
		end_dialogue;                               \
    end

#define is_new_monsterparts_enabled         get_ini_setting("combat.ini|ONDEATH|drop_monster_parts")

// GVAR_BRINGX_* statuses:
#define BRINGX_QUEST_TAKEN   (1)
#define BRINGX_QUEST_DONE    (2)

// common stuff END


#ifdef _BRINGX_SCHENRY

#define NAME    SCRIPT_SCHENRY

// 0 - taking quest first time
// 1 - quest taken
// <0 - time when next available
#define LVAR_BRING_X    (8)

#define _BRING_REWARD    (3000)
#define _BRING_COUNT       (10)

#define is_first_bring     (local_var(LVAR_BRING_X) == 0)

// Node008
#define INJECT_GIVE_X   \
    if (local_var(LVAR_BRING_X) == 1 and obj_is_carrying_obj_pid(dude_obj, PID_PBS_TENTACLE) >= _BRING_COUNT) then NOption(403,NodeBringReward,004);

// Node016 - change reply string to 400!
#define INJECT_ASK_BRING   \
    if (local_var(LVAR_BRING_X) == 0) then NOption(401,NodeBringAsk,004); \
    else if (local_Var(LVAR_BRING_X) < 0) then NOption(402,NodeBringAsk,004); \
    else INJECT_GIVE_X   \
    else NOption(404,Node999,004);    

procedure NodeBringAsk;
procedure NodeBringAccept;
procedure NodeBringWhere;
procedure NodeBringReward;
    
procedure NodeBringAsk begin
    if (local_var(LVAR_BRING_X) < 0 and game_time < (-local_var(LVAR_BRING_X))) then begin
        Reply(420);
        NOption(115,Node999,004);
    end else begin
        Reply(parse_str_2(mstr(405), _BRING_COUNT, _BRING_REWARD));
        NOption(406,NodeBringWhere,004);
        NOption(407,NodeBringAccept,004);
        NOption(408,Node999,004);
    end
end

procedure NodeBringWhere begin
    Reply(410);
    NOption(407,NodeBringAccept,004);
    NOption(408,Node999,004);
end

procedure NodeBringAccept begin
    set_local_var(LVAR_BRING_X, 1);
    set_global_var(GVAR_BRINGX_TENTACLES, BRINGX_QUEST_TAKEN); // for pip boy
    call Node999;
end

procedure NodeBringReward begin
    item_caps_adjust(dude_obj, _BRING_REWARD);
    set_local_var(LVAR_BRING_X, -(game_time + ONE_GAME_DAY*random(20, 30)));
    set_global_var(GVAR_BRINGX_TENTACLES, BRINGX_QUEST_DONE);
    call remove_items_pid(dude_obj, PID_PBS_TENTACLE, _BRING_COUNT);
    give_exp_points(100);
    display_msg(g_mstr(100) + 100 + g_mstr(101));
    Reply(415);
    NOption(416,Node999,004);
end

#endif



#ifdef _BRINGX_MCBATLHA

#define NAME    SCRIPT_MCBALTHA

// 0 - quest never taken
// 1 - quest taken first time
// 2 - quest taken not first time
// <0 - quest was completed, time when next available
#define LVAR_BRING_X    (8)

#define _BRING_REWARD    (1000)
#define _BRING_COUNT       (10)

#define is_first_bring     (local_var(LVAR_BRING_X) == 0 or local_var(LVAR_BRING_X) == 1)

// 
#define INJECT_GIVE_X   \
    if (local_var(LVAR_BRING_X) > 0 and obj_is_carrying_obj_pid(dude_obj, PID_PBS_MOLERAT_HIDE) >= _BRING_COUNT) then NOption(1103,NodeBringRewardSelect,004);

// Node000, Node001, Node002, Node027
#define INJECT_ASK_BRING(x)   \
    if (is_new_monsterparts_enabled) then begin   \
        if (local_var(LVAR_BRING_X) <= 0) then NOption(x,NodeBringAsk,004); \
        else INJECT_GIVE_X   \
    end

procedure NodeBringAsk;
procedure NodeBringAccept;
procedure NodeBringRewardSelect;
procedure NodeBringReward;
procedure NodeBringReward1;
procedure NodeBringReward2;
    
procedure NodeBringAsk begin
    if (local_var(LVAR_BRING_X) < 0 and game_time < (-local_var(LVAR_BRING_X))) then begin
        Reply(1130);
        NOption(1131,Node999,004);
    end else begin
        Reply(parse_str_2(mstr(1110), _BRING_COUNT, _BRING_REWARD));
        NOption(1111,NodeBringAccept,004);
        NOption(1112,Node999,004);
    end
end

procedure NodeBringAccept begin
    if (is_first_bring) then set_local_var(LVAR_BRING_X, 1);
    else set_local_var(LVAR_BRING_X, 2);
    set_global_var(GVAR_BRINGX_HIDES, BRINGX_QUEST_TAKEN);
    call Node999;
end

procedure NodeBringRewardSelect begin
    if (is_first_bring) then begin
        Reply(1140);
        NOption(1141,NodeBringReward1,004);
        NOption(1142,NodeBringReward2,004);
    end else begin
        Reply(1150);
        NOption(1151,NodeBringReward1,004);
    end
end

procedure NodeBringReward1 begin
    item_caps_adjust(dude_obj, _BRING_REWARD);
    call NodeBringReward;
end

procedure NodeBringReward2 begin
    call add_item_pid(dude_obj, PID_LEATHER_ARMOR);
    call NodeBringReward;
end

procedure NodeBringReward begin
    set_local_var(LVAR_BRING_X, -(game_time + ONE_GAME_DAY*random(20, 30)));
    set_global_var(GVAR_BRINGX_HIDES, BRINGX_QUEST_DONE);
    call remove_items_pid(dude_obj, PID_PBS_MOLERAT_HIDE, _BRING_COUNT);
    give_exp_points(100);
    display_msg(g_mstr(100) + 100 + g_mstr(101));
    Reply(1160);
    NOption(1161,Node999,004);
    NOption(1162,Node999,004);
end



#endif
