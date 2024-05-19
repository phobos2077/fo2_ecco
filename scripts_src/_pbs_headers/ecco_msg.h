#ifndef ECCO_MSG_H
#define ECCO_MSG_H

#include "../sfall/sfall.h"

variable combat_msg_id;

procedure mstr_ecco_combat(variable num) begin
   if not combat_msg_id then begin
      combat_msg_id := add_extra_msg_file("pbs_combat.msg");
   end
   return message_str_game(combat_msg_id, num);
end

#endif
