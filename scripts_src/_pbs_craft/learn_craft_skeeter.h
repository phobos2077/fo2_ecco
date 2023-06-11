#ifndef LEARN_CRAFT_SKEETER_H
#define LEARN_CRAFT_SKEETER_H

#include "learn_craft.h"

#define NAME                    SCRIPT_GCSKEETR

// home node: Node110
/*
  if (get_sfall_global_int(SGVAR_CRAFT_AMMO) == 0) then begin
    NOption(1001, NodeCraft1, 004);
  end
*/

procedure NodeCraft1;
procedure NodeCraft1a;
procedure NodeCraft1b;
procedure NodeCraft3;
procedure NodeCraft4;

variable craft_price;

procedure NodeCraft1 begin
  Reply(1010);
  craft_price := 500;
  if (dude_caps >= 500) then begin
    NOption(1011, NodeCraft3, 004);
  end
  BOption(1012, NodeCraft1b, 004);
  if (dude_caps >= 250 and has_skill(dude_obj,SKILL_BARTER) >= 60) then begin
    NOption(1013, NodeCraft1a, 004);
  end
  NOption(1014, Node009, 004);
end

procedure NodeCraft1a begin
  Reply(1020);
  if (dude_caps >= 400) then begin
    craft_price := 400;
    NOption(1011, NodeCraft3, 004);
  end
  NOption(1032, Node009, 004);
end

procedure NodeCraft1b begin
  Reply(1030);
  if (dude_caps >= 500) then begin
    NOption(1031, NodeCraft3, 004);
  end
  NOption(1032, Node009, 004);
end

procedure NodeCraft3 begin
  item_caps_adjust(dude_obj, -craft_price);
  Reply(1040);
  NOption(g_mstr(353),NodeCraft4,004);
end

procedure NodeCraft4 begin
  gfade_out(400);
  game_time_advance(18000);
  set_sfall_global(SGVAR_CRAFT_AMMO, 1);
  display_msg(fixit_mstr(86));
  gfade_in(400);
  Reply(1041);
  NOption(g_mstr(202), Node999, 004);
  NOption(1042, Node009, 004);
end

#endif // LEARN_CRAFT_SKEETER_H
