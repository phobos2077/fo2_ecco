
#define fixit_mstr(x)               message_str(SCRIPT_TEST0,x)

// from COMMAND.H:
/*#define mstr(x)                     message_str(NAME,x)
#define display_mstr(x)             display_msg(mstr(x))
#define g_mstr(x)                   message_str(SCRIPT_GENERIC,x)

#define GOOD_REACTION    (49)
#define NEUTRAL_REACTION (50)
#define BAD_REACTION     (51)
#define LOW_IQ                      (-3)
#define Reply(x)                    gSay_Reply(NAME,x)
#define Reply_Rand(x,y)             Reply(random(x,y))
#define GMessage(x)                 gSay_Message(NAME,x,GOOD_REACTION)
#define NMessage(x)                 gSay_Message(NAME,x,NEUTRAL_REACTION)
#define BMessage(x)                 gSay_Message(NAME,x,BAD_REACTION)
#define num_to_num_text(x)          g_mstr(2000+x)
#define GOption(x,y,z)              giQ_Option(z,NAME,x,y,GOOD_REACTION)
#define NOption(x,y,z)              giQ_Option(z,NAME,x,y,NEUTRAL_REACTION)
#define BOption(x,y,z)              giQ_Option(z,NAME,x,y,BAD_REACTION)
#define GLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,GOOD_REACTION)
#define NLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,NEUTRAL_REACTION)
#define BLowOption(x,y)             giQ_Option(LOW_IQ,NAME,x,y,BAD_REACTION)

#define dude_caps                           (item_caps_total(dude_obj))

// from DEFINE.H:
#define SKILL_SMALL_GUNS                    (0)
#define SKILL_BIG_GUNS                      (1)
#define SKILL_ENERGY_WEAPONS                (2)
#define SKILL_UNARMED_COMBAT                (3)
#define SKILL_MELEE                         (4)
#define SKILL_THROWING                      (5)
#define SKILL_FIRST_AID                     (6)
#define SKILL_DOCTOR                        (7)
#define SKILL_SNEAK                         (8)
#define SKILL_LOCKPICK                      (9)
#define SKILL_STEAL                         (10)
#define SKILL_TRAPS                         (11)
#define SKILL_SCIENCE                       (12)
#define SKILL_REPAIR                        (13)
#define SKILL_CONVERSANT                    (14)
#define SKILL_BARTER                        (15)
#define SKILL_GAMBLING                      (16)
#define SKILL_OUTDOORSMAN                   (17)
// SPECIAL System stats
#define STAT_st              (0)
#define STAT_pe              (1)
#define STAT_en              (2)
#define STAT_ch              (3)
#define STAT_iq              (4)
#define STAT_ag              (5)
#define STAT_lu              (6)
#define STAT_max_hp          (7)*/

#define dude_barter     (has_skill(dude_obj,SKILL_BARTER))


// new GVARs (using Reserved GVARs 11-20)
//#define GVAR_CRAFT_EXPLOSIVES     (644)
//#define GVAR_CRAFT_LEATHER        (645)
//#define GVAR_CRAFT_FIRST_AID      (646)
//#define GVAR_CRAFT_DRUGS          (647)
//#define GVAR_CRAFT_ELECTRONICS    (648)
//#define GVAR_CRAFT_AMMO           (649)
//#define GVAR_CRAFT_BLADES         (650)

#define SGVAR_CRAFT_VERSION        "CRFT_ver"

#define SGVAR_CRAFT_EXPLOSIVES     "CRFT_EXP"
#define SGVAR_CRAFT_JACKET         "CRFT_LTJ"
#define SGVAR_CRAFT_LEATHER        "CRFT_LTH"
#define SGVAR_CRAFT_FIRST_AID      "CRFT_AID"
#define SGVAR_CRAFT_DRUGS          "CRFT_DRG"
#define SGVAR_CRAFT_ELECTRONICS    "CRFT_ELE"
#define SGVAR_CRAFT_ELECTRONICS2   "CRFT_EL2"
#define SGVAR_CRAFT_AMMO           "CRFT_AMM"
#define SGVAR_CRAFT_BLADES         "CRFT_BLD"
#define SGVAR_CRAFT_FOOD           "CRFT_FOD"
#define SGVAR_CRAFT_TOOLS          "CRFT_TOL"

#define crafting_mod_available   (message_str(SCRIPT_TEST0, 1000) != "Error")

#include "..\headers\GLOBAL.H"
#include "..\headers\SCRIPTS.H"
#include "..\headers\ITEMPID.H"
#include "..\_pbs_main\lib.strings.h"


#ifdef _LEARN_CRAFT_SMITTY

#define NAME                    SCRIPT_DCSMITTY

procedure NodeCraft1;
procedure NodeCraft1a;
procedure NodeCraft2a;
procedure NodeCraft2b;
procedure NodeCraft3;
procedure NodeCraft4;

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
  display_msg(fixit_mstr(81));
  gfade_in(400);
  Reply(721);
  NOption(722, Node999, 004);
  if not(dudeHasCar) then begin
	BackOption(723, 004)
  end
end

#endif


#ifdef _LEARN_CRAFT_MOM

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

#endif


#ifdef _LEARN_CRAFT_VAL

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

#endif


#ifdef _LEARN_CRAFT_SKEETER

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

#endif



#ifdef _LEARN_CRAFT_DRJOHNSON

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
  if (has_skill(dude_obj, SKILL_CONVERSANT) >= 60) then begin
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
  display_msg(fixit_mstr(83));
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

#endif




#ifdef _LEARN_CRAFT_DRTROY

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
  if (dude_caps >= 1000 and has_skill(dude_obj,SKILL_BARTER) >= 70) then begin
    NOption(1021, NodeCraft2a, 004);
  end
  if (dude_caps >= 2000) then begin
    NOption(1022, NodeCraft3a, 004);
  end
  if (obj_is_carrying_obj_pid(dude_obj, PID_SCORPION_TAIL) >= 8) then begin
    NOption(1023, NodeCraft3b, 004);
  end
  NOption(1024, Node999, 004);
end

procedure NodeCraft2a begin
  Reply(1030);
  if (dude_caps >= 2000) then begin
    NOption(1031, NodeCraft3a, 004);
  end
  NOption(1012, Node999, 004);
end

procedure NodeCraft3a begin
  item_caps_adjust(dude_obj, -2000);
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
  game_time_advance(18000);
  set_sfall_global(SGVAR_CRAFT_DRUGS, 1);
  display_msg(fixit_mstr(84));
  gfade_in(400);
  Reply(1041);
  NOption(g_mstr(202), Node999, 004);
end

#endif





#ifdef _LEARN_CRAFT_BALTHAS

#define NAME                    SCRIPT_MCBALTHA

#define node_3_bit    512

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
  display_msg(fixit_mstr(82));
  gfade_in(400);
  Reply(1041);
  NOption(1042, Node999, 004);
end

#endif
