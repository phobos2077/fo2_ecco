#ifndef FO2_REP_H
#define FO2_REP_H

#include "../sfall/lib.misc.h"

#include "../headers/maps.h"
#include "../headers/global.h"

#include "ecco_ini.h"

variable town_to_gvar_map;

procedure get_town_rep_var(variable townId) begin
   if (town_to_gvar_map == 0) then begin
      town_to_gvar_map := get_ini_section_int_to_int(INI_MISC, "TOWN_REP", true);
   end
   return town_to_gvar_map[townId];
end

#define cur_town_rep_var           get_town_rep_var(cur_town)
#define cur_town_rep               (global_var(cur_town_rep_var))
#define inc_cur_town_rep(amt)      set_global_var(cur_town_rep_var, cur_town_rep + amt)

#endif