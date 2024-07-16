#ifndef PBS_MERCHANT_LOOT_H
#define PBS_MERCHANT_LOOT_H

#include "loot_utils.h"

#ifdef MERCHANT_CRITICAL_ITEMS
   procedure merchant_loot_trim(variable invenObj, variable pidToQty) begin
      return loot_trim_inventory(invenObj, array_concat(pidToQty, array_to_set(MERCHANT_CRITICAL_ITEMS, 100)));
   end
#else
   #define merchant_loot_trim(invenObj, pidToQty)   __ERROR__NO__MERCHANT_CRITICAL_ITEMS
#endif

#endif
