#ifndef LEARN_CRAFT_H
#define LEARN_CRAFT_H

#define fixit_mstr(x)               message_str(SCRIPT_TEST0,x)

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
#define SGVAR_CRAFT_DEATHCLAW      "CRFT_GNT"

#define crafting_mod_available   (message_str(SCRIPT_TEST0, 1000) != "Error")

#include "../headers/global.h"
#include "../headers/scripts.h"
#include "../headers/itempid.h"
#include "../sfall/lib.strings.h"

#include "../_pbs_headers/talking_heads_compat.h"

#endif // LEARN_CRAFT_H
