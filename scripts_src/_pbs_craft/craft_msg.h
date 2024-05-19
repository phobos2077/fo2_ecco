#ifndef PBS_CRAFT_MSG_H
#define PBS_CRAFT_MSG_H

#include "../sfall/sfall.h"

#define PBS_CRAFT_MSG_NAME          "pbs_craft.msg"

variable craft_msg_file_id;

procedure mstr_pbs_craft(variable num) begin
   if (not craft_msg_file_id) then
      craft_msg_file_id := add_extra_msg_file(PBS_CRAFT_MSG_NAME);

   return message_str_game(craft_msg_file_id, num);
end

#undef PBS_CRAFT_MSG_NAME

#endif
