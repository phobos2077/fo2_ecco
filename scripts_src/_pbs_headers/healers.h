#ifndef PBS_HEALERS_H
#define PBS_HEALERS_H

//#include "party.h"

procedure party_injured_or_crippled_count(variable includeDude := false) begin
   variable count = 0;
   foreach (variable who in party_member_list_critters) begin
      if (who == dude_obj and not includeDude) then continue;
      if Is_Injured(who) or Is_Crippled(who) then count += 1;
   end
   return count;
end

procedure heal_and_uncripple_critter(variable who) begin
   critter_heal(who, (get_max_hits(who) - get_cur_hits(who)));
   critter_uninjure(who, (DAM_CRIP_LEG_LEFT bwor DAM_CRIP_LEG_RIGHT bwor DAM_CRIP_ARM_LEFT bwor DAM_CRIP_ARM_RIGHT));
end

procedure heal_and_uncripple_party(variable includeDude := false) begin
   foreach (variable who in party_member_list_critters) begin
      if (who == dude_obj and not includeDude) then continue;

      call heal_and_uncripple_critter(who);
   end
end


#endif
