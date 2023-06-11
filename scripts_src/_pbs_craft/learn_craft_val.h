#ifndef LEARN_CRAFT_VAL_H
#define LEARN_CRAFT_VAL_H

#include "learn_craft.h"

#define NAME                    SCRIPT_VCMAINWK
#define PRICE_HIGH      (700)
#define PRICE_LOW       (400)

#define BackOption(n, int)  \
   if (local_var(LVAR_Super_Tool_Kit) == TOOLKIT_GIVEN) then begin \
      NOption(n, Node027, int);  \
   end else begin  \
      NOption(n, Node009, int); \
   end
   
#define ASK_CRAFT_INJECTION(n) \
   if (get_sfall_global_int(SGVAR_CRAFT_ELECTRONICS) == 0) then \
      NOption(n, NodeCraft1, 004);

procedure NodeCraft1;
procedure NodeCraft2;
procedure NodeCraft3;
procedure NodeCraft4;
procedure NodeCraft5;

variable price;

procedure NodeCraft1 begin
  Reply(505);
  NOption(506, NodeCraft2, 004);
  BackOption(511, 004)
end

procedure NodeCraft2 begin
variable s;
   Reply(parse_str_2(mstr(510), PRICE_HIGH, ""));
   price := PRICE_HIGH;
   if (dude_caps >= PRICE_HIGH) then
      NOption(516, NodeCraft4, 004);
   s := parse_str_2(mstr(512), PRICE_LOW, "");
   if (dude_caps >= PRICE_LOW and dude_barter >= 60) then
      NOption(s, NodeCraft3, 004);
   BackOption(511, 004)
end

procedure NodeCraft3 begin
  Reply(parse_str_2(mstr(515), PRICE_LOW, ""));
  price := PRICE_LOW;
  NOption(516,NodeCraft4,004);
end

procedure NodeCraft4 begin
  Reply(520);
  item_caps_adjust(dude_obj, -price);
  NOption(g_mstr(353),NodeCraft5,004);
end

procedure NodeCraft5 begin
   gfade_out(400);
   game_time_advance(18000);
   set_sfall_global(SGVAR_CRAFT_ELECTRONICS, 1);
   display_msg(fixit_mstr(85));
   gfade_in(400);
   Reply(521);
   BackOption(g_mstr(202), 004)
end

#endif // LEARN_CRAFT_VAL_H
