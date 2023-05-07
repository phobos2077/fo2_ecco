#ifndef LEARN_CRAFT_VIC_H
#define LEARN_CRAFT_VIC_H

#include "learn_craft.h"

#define node_craft_bit                    bit_20
#define node_craft                        lvar_bit(LVAR_Flags, node_craft_bit)
#define set_node_craft                    set_lvar_bit_on(LVAR_Flags, node_craft_bit)

procedure NodeCraft1;
procedure NodeCraft2;
procedure NodeCraft3;
procedure NodeCraft4;
procedure NodeCraft5;
procedure NodeCraft6;
procedure NodeCraft7;
procedure NodeCraft8;
procedure NodeCraft9;
procedure NodeCraft10;
procedure NodeCraft11;

procedure NodeCraft1 begin
  Reply(5101);
  NOption(5102, NodeCraft3, 004);
end

procedure NodeCraft3 begin
  Reply(5103);
  if (get_sfall_global_int(SGVAR_CRAFT_BLADES) == 0) then
     NOption(51041, NodeCraft4, 004);
  else
     NOption(5104, NodeCraft5, 004);
end

procedure NodeCraft4 begin
  Reply(5105);
  set_sfall_global(SGVAR_CRAFT_BLADES, 1);
  display_msg(fixit_mstr(87));
  NOption(5106, NodeCraft5, 004);
  //NOption(5130, Node110, 004);
end

procedure NodeCraft5 begin
  Reply(5107);
  set_node_craft;
  NOption(5108, NodeCraft6, 004);
  NOption(5130, Node110, 004);
end

procedure NodeCraft6 begin
  Reply(5109);
  NOption(5110, NodeCraft7, 004);
  NOption(5130, Node110, 004);
end

procedure NodeCraft7 begin
  Reply(5111);
  NOption(5112, NodeCraft8, 004);
  NOption(5130, Node110, 004);
end

procedure NodeCraft8 begin
  Reply(5113);
  NOption(5116, NodeCraft9, 004);
  NOption(5130, Node110, 004);
end

procedure NodeCraft9 begin
  Reply(5117);
  NOption(5120, NodeCraft10, 004);
  NOption(5130, Node110, 004);
end

procedure NodeCraft10 begin
  Reply(5121);
  NOption(5122, Node110, 004);
end

#endif // LEARN_CRAFT_VIC_H
