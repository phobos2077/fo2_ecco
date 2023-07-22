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
   //debug_log_fmt("get_town_rep_var %d = %d", townId, town_to_gvar_map[townId]);
   return town_to_gvar_map[townId];
end

#define cur_town_rep_var           get_town_rep_var(cur_town)

procedure get_town_rep(variable townId := -1) begin
   if (townId < 0) then townId := cur_town;
   variable var := get_town_rep_var(townId);
   return global_var(var) if (var > 0) else 0;
end

procedure inc_town_rep(variable amt, variable townId := -1) begin
   if (townId < 0) then townId := cur_town;
   variable var := get_town_rep_var(townId);
   if (var <= 0) then return;

   variable curRep := global_var(var);
   debug_log_fmt("Change town %d rep from %d to %d.", townId, curRep, curRep + amt);
   set_global_var(var, curRep + amt);
end

#endif