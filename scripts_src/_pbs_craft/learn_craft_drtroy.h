#ifndef LEARN_CRAFT_DRTROY_H
#define LEARN_CRAFT_DRTROY_H

#include "learn_craft.h"

#define TEACH_PRICE_NORMAL      (1000)
#define TEACH_PRICE_DISCOUNT     (500)

#define NAME                    SCRIPT_VCDRTROY

// home nodes: Node044

#define ASK_CRAFT_INJECTION   \
    if (get_sfall_global_int(SGVAR_CRAFT_DRUGS) == 0) then begin \
        NOption(1001, NodeCraft1, 004); \
    end

// fail nodes: Node005, Node009
#define ASK_CRAFT_INJECTION_FAIL   \
    if (get_sfall_global_int(SGVAR_CRAFT_DRUGS) == 0) then begin \
        NOption(1001, Node005a, 004); \
    end

procedure NodeCraft1;
procedure NodeCraft2;
procedure NodeCraft2a;
procedure NodeCraft3a;
procedure NodeCraft3b;
procedure NodeCraft4;
procedure NodeCraft5;

procedure NodeCraft1 begin
  Reply(1010);
  NOption(1011, NodeCraft2, 004);
  NOption(1012, Node999, 004);
end

procedure NodeCraft2 begin
  Reply(1020);
  if (dude_caps >= TEACH_PRICE_DISCOUNT and has_skill(dude_obj, SKILL_BARTER) >= 50) then begin
    NOption(1021, NodeCraft2a, 004); // ask for discount, but he will never budge
  end
  if (dude_caps >= TEACH_PRICE_NORMAL) then begin
    NOption(1022, NodeCraft3a, 004);
  end
  if (obj_is_carrying_obj_pid(dude_obj, PID_SCORPION_TAIL) >= 8) then begin
    NOption(1023, NodeCraft3b, 004);
  end
  NOption(1024, Node999, 004);
end

procedure NodeCraft2a begin
  Reply(1030);
  if (dude_caps >= TEACH_PRICE_NORMAL) then begin
    NOption(1031, NodeCraft3a, 004);
  end
  NOption(1012, Node999, 004);
end

procedure NodeCraft3a begin
  item_caps_adjust(dude_obj, -TEACH_PRICE_NORMAL);
  call NodeCraft4;
end

procedure NodeCraft3b begin
  variable item, tmp;
  item := obj_carrying_pid_obj(dude_obj, PID_SCORPION_TAIL);
  tmp := rm_mult_objs_from_inven(dude_obj, item, 8);
  destroy_object(item);
  call NodeCraft4;
end

procedure NodeCraft4 begin
  Reply(1040);
  NOption(g_mstr(353),NodeCraft5,004);
end

procedure NodeCraft5 begin
  gfade_out(400);
  game_time_advance(30 * ONE_GAME_MINUTE);
  set_sfall_global(SGVAR_CRAFT_DRUGS, 1);
  display_msg(fixit_mstr(84));
  gfade_in(400);
  Reply(1041);
  NOption(g_mstr(202), Node999, 004);
end

#endif // LEARN_CRAFT_DRTROY_H
