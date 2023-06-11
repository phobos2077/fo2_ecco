#ifndef LEARN_CRAFT_MOM_H
#define LEARN_CRAFT_MOM_H

#include "learn_craft.h"

//#define NAME                    SCRIPT_DCMOM

#define PRICE_HIGH   (400)
#define PRICE_LOW    (200)

procedure NodeCraft1;
procedure NodeCraft1a;
procedure NodeCraft2a;
procedure NodeCraft2b;
procedure NodeCraft3;
procedure NodeCraft4;

procedure NodeCraft1 begin
  variable free;
  free := (/*smitty_deliver(state_smitty_deliver_finished) or smitty_deliver(state_smitty_deliver_reward_given) or */
               (global_var(GVAR_DEN_ORPHANAGE) == 6));
  
  if (free) then
     Reply(2005);
  else
     Reply(2010);
     
  if (not(free) and dude_caps >= PRICE_HIGH) then begin
    NOption(2011, NodeCraft2a, 004);
  end else if (free) then begin
    NOption(2006, NodeCraft3, 004);
  end
  if (not(free) and has_skill(dude_obj,SKILL_BARTER) >= 50) then begin
    NOption(2012, NodeCraft1a, 004);
  end
  NOption(2007, Node013, 004);
end

procedure NodeCraft1a begin
  Reply(2015);
  if (dude_caps >= PRICE_LOW) then begin
    NOption(2016, NodeCraft2b, 004);
  end
  NOption(2007, Node013, 004);
end

procedure NodeCraft2a begin
  item_caps_adjust(dude_obj, -PRICE_HIGH);
  call NodeCraft3;
end

procedure NodeCraft2b begin
  item_caps_adjust(dude_obj, -PRICE_LOW);
  call NodeCraft3;
end

procedure NodeCraft3 begin
  Reply(2020);
  NOption(g_mstr(353),NodeCraft4,004);
end

procedure NodeCraft4 begin
  gfade_out(400);
  game_time_advance(18000);
  set_sfall_global(SGVAR_CRAFT_FOOD, 1);
  display_msg(fixit_mstr(88));
  gfade_in(400);
  Reply(2021);
  NOption(2023, Node013, 004);
  NOption(2022, Node999, 004);
end

#endif // LEARN_CRAFT_MOM_H
