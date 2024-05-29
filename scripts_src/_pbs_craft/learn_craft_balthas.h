#ifndef LEARN_CRAFT_BALTHAS_H
#define LEARN_CRAFT_BALTHAS_H

#include "learn_craft.h"

#define NAME                    SCRIPT_MCBALTHA

//GVAR_MODOC_JONNY_PIP

// use this as entry points in dialog
#define ASK_CRAFT_INJECTION(x)   \
    if (get_sfall_global_int(SGVAR_CRAFT_LEATHER) == 0) then begin \
      NOption(x, NodeCraft1, 004); \
    end

// entry nodes: Node000, Node001, Node002, Node027

procedure NodeCraft1;
procedure NodeCraft1a;
procedure NodeCraft1b;
procedure NodeCraft3;
procedure NodeCraft4;

variable craft_price;

procedure NodeCraft1 begin
  // if saved Johnny
  if ((local_var(4) bwand 512) != 0) then begin
    call NodeCraft1a;
  end else begin
    Reply(1010);
    craft_price := 400;
    if (dude_caps >= 400) then begin
      NOption(1011, NodeCraft3, 004);
    end
    if (dude_caps >= 200 and has_skill(dude_obj,SKILL_BARTER) >= 60) then begin
      NOption(1012, NodeCraft1b, 004);
    end
    NOption(1014, Node999, 004);
  end
end

procedure NodeCraft1a begin
  craft_price := 0;
  Reply(1030);
  NOption(1031, NodeCraft3, 004);
  NOption(1032, Node999, 004);
end

procedure NodeCraft1b begin
  Reply(1020);
  craft_price := 300;
  if (dude_caps >= 300) then begin
    NOption(1011, NodeCraft3, 004);
  end
  NOption(1014, Node999, 004);
end

procedure NodeCraft3 begin
  if (craft_price) then item_caps_adjust(dude_obj, -craft_price);
  Reply(1040);
  NOption(g_mstr(353),NodeCraft4,004);
end

procedure NodeCraft4 begin
  gfade_out(400);
  game_time_advance(18000);
  set_sfall_global(SGVAR_CRAFT_JACKET, 1);
  set_sfall_global(SGVAR_CRAFT_LEATHER, 1);
  display_msg(mstr_pbs_craft(82));
  gfade_in(400);
  Reply(1041);
  NOption(1043, Node996, 004);
  NOption(1042, Node999, 004);
end

#endif // LEARN_CRAFT_BALTHAS_H
