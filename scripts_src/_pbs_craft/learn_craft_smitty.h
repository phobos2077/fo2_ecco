#ifndef LEARN_CRAFT_SMITTY_H
#define LEARN_CRAFT_SMITTY_H

#include "learn_craft.h"

#define NAME                    SCRIPT_DCSMITTY

procedure NodeCraft1;
procedure NodeCraft1a;
procedure NodeCraft2a;
procedure NodeCraft2b;
procedure NodeCraft3;
procedure NodeCraft4;
procedure NodeCraft5;

#define dudeHasCar		(global_var(18))

#define BackOption(n, int)  	  if (dudeHasCar) then begin \
								  	NOption(n, Node999, int);  \
								  end else begin  \
								  	NOption(n, Node003, int); \
								  end

procedure NodeCraft1 begin
  variable free;
  free := (global_var(450) == 2);
  
  Reply(710 + free);
  if (not(free) and dude_caps >= 200) then begin
    NOption(712, NodeCraft2a, 004);
  end else if (free) then begin
    NOption(712, NodeCraft3, 004);
  end
  if (not(free) and dude_caps >= 100 and has_skill(dude_obj,SKILL_BARTER) >= 50) then begin
    NOption(713, NodeCraft1a, 004);
  end
  BackOption(714, 004)
  if not(free) then begin
    BackOption(715, 004)
  end
end

procedure NodeCraft1a begin
  Reply(730);
  if (dude_caps >= 125) then begin
    NOption(712, NodeCraft2b, 004);
  end
  BackOption(714, 004)
  BackOption(715, 004)
end

procedure NodeCraft2a begin
  item_caps_adjust(dude_obj, -200);
  call NodeCraft3;
end

procedure NodeCraft2b begin
  item_caps_adjust(dude_obj, -125);
  call NodeCraft3;
end

procedure NodeCraft3 begin
  Reply(720);
  NOption(g_mstr(353),NodeCraft4,004);
end

procedure NodeCraft4 begin
  gfade_out(400);
  game_time_advance(18000);
  set_sfall_global(SGVAR_CRAFT_EXPLOSIVES, 1);
  display_msg(mstr_pbs_craft(81));
  gfade_in(400);
  Reply(721);
  NOption(712, NodeCraft5, 004);
  NOption(722, Node999, 004);
  if not(dudeHasCar) then begin
	BackOption(723, 004)
  end
end

procedure NodeCraft5 begin
  gdialog_mod_barter(0);
  if (dudeHasCar) then begin
    call Node999;
  end else begin
    call Node003;
  end
end

#endif // LEARN_CRAFT_SMITTY_H
