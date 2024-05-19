#ifndef LEARN_CRAFT_DRJOHNSON_H
#define LEARN_CRAFT_DRJOHNSON_H

#include "learn_craft.h"

#define NAME                    SCRIPT_RCDRJOHN

// home node: Node010
/*
  if (get_sfall_global_int(SGVAR_CRAFT_DRUGS) == 0) then begin
    	NOption(501, NodeCraft1, 004);
	end
*/

procedure NodeCraft1;
procedure NodeCraft1a;
procedure NodeCraft1b;
procedure NodeCraft1c;
procedure NodeCraft3;
procedure NodeCraft4;
procedure NodeCraft10;

variable craft_price;

procedure NodeCraft1 begin
  Reply(510);
  craft_price := 1000;
  if (dude_caps >= craft_price) then begin
    NOption(511, NodeCraft3, 004);
  end
  BOption(512, NodeCraft1a, 004);
  if (dude_caps >= 500 and has_skill(dude_obj,SKILL_BARTER) >= 60) then begin
    NOption(513, NodeCraft1c, 004);
  end
  NOption(514, Node010, 004);
end

procedure NodeCraft1a begin
  Reply(520);
  if (dude_caps >= 1000) then begin
    NOption(521, NodeCraft3, 004);
  end
  if (has_skill(dude_obj, SKILL_SPEECH) >= 60) then begin
  	NOption(522, NodeCraft1b, 007);
  end
  NOption(514, Node010, 004);
end

procedure NodeCraft1b begin
  Reply(530);
  craft_price := 400;
  if (dude_caps >= craft_price) then begin
    NOption(531, NodeCraft3, 004);
  end
  NOption(532, Node010, 004);
end

procedure NodeCraft1c begin
  Reply(540);
  craft_price := 750;
  if (dude_caps >= craft_price) then begin
    NOption(541, NodeCraft3, 004);
  end
  NOption(514, Node010, 004);
end

procedure NodeCraft3 begin
  item_caps_adjust(dude_obj, -craft_price);
  Reply(550);
  NOption(g_mstr(353),NodeCraft4,004);
end

procedure NodeCraft4 begin
  gfade_out(400);
  game_time_advance(18000);
  set_sfall_global(SGVAR_CRAFT_FIRST_AID, 1);
  display_msg(mstr_pbs_craft(83));
  gfade_in(400);
  Reply(551);
  NOption(552, Node999, 004);
  NOption(553, Node010, 004);
end

procedure NodeCraft10 begin
  Reply(560);
  NOption(g_mstr(200),Node010,004);
  NOption(g_mstr(209),Node010,004);
end

#endif // LEARN_CRAFT_DRJOHNSON_H
