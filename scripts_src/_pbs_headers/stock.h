/******************************************************************
 General commands restocking inventory
 note: this is generally placed in the "box" of a merchant to refil it every so once in a while
       only call this when it's time to restock the "box"... see "diTubBox.ssl" for a hint
       but most of all, have fun, remember, fun
******************************************************************/
/*variable restock_amt;
variable restock_obj;
variable restock_trash;
variable removed_qty;*/


/*
// inventory Equates //
#define INVEN_TYPE_WORN        (0)
#define INVEN_TYPE_RIGHT_HAND  (1)
#define INVEN_TYPE_LEFT_HAND   (2)

#define create_object(X,Y,Z)    create_object_sid(X,Y,Z,-1)

#define critter_wearing_armor(x)            (obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_WORN)) == item_type_armor)

#define METARULE_INVEN_UNWIELD_WHO 43
#define inven_unwield(WHO)       metarule(METARULE_INVEN_UNWIELD_WHO, WHO)

#define item_type_armor        (0)
#define item_type_container    (1)
#define item_type_drug         (2)
#define item_type_weapon       (3)
#define item_type_ammo         (4)
#define item_type_misc_item    (5)
#define item_type_key_item     (6)

#define transfer_pid_between_objs(source, target, the_pid, qty)                           \
         restock_amt := qty;                                                              \
         if (obj_is_carrying_obj_pid(source, the_pid) < qty) then begin                   \
            restock_amt := obj_is_carrying_obj_pid(source, the_pid);                      \
         end                                                                              \
         if (restock_amt > 0) then begin                                                  \
            restock_obj := obj_carrying_pid_obj(source, the_pid);                         \
            restock_trash := rm_mult_objs_from_inven(source, restock_obj, restock_amt);   \
            add_mult_objs_to_inven(target, restock_obj, restock_amt);                     \
         end

#define transfer_all_pid_between_objs(source, target, the_pid)                            \
         restock_amt := obj_is_carrying_obj_pid(source, the_pid);                         \
         if (restock_amt > 0) then begin                                                  \
            restock_obj := obj_carrying_pid_obj(source, the_pid);                         \
            restock_trash := rm_mult_objs_from_inven(source, restock_obj, restock_amt);   \
            add_mult_objs_to_inven(target, restock_obj, restock_amt);                     \
         end

#define give_pid_qty(who_obj, the_pid, pid_qty)                                           \
           restock_obj := create_object(the_pid,0,0);                                     \
           add_mult_objs_to_inven(who_obj, restock_obj, (pid_qty));

#define remove_armor(who_obj)                                                                            \
            if (critter_wearing_armor(who_obj)) then begin                                               \
               restock_obj := critter_inven_obj(who_obj,INVEN_TYPE_WORN);                                \
               debug_msg("armour pid == "+obj_pid(restock_obj));                                         \
               rm_obj_from_inven(who_obj, restock_obj);                                                  \
               add_obj_to_inven(who_obj, restock_obj);                                                   \
            end

#define remove_pid_qty(who_obj, the_pid, pid_qty)                                            \
           removed_qty := obj_is_carrying_obj_pid(who_obj,the_pid);                          \
           if ((pid_qty) < removed_qty) then begin                                           \
              removed_qty := pid_qty;                                                        \
           end                                                                               \
           if (removed_qty > 0) then begin                                                   \
              restock_obj := obj_carrying_pid_obj(who_obj, the_pid);                         \
              if (obj_type(self_obj) == 1) then begin                                        \
                 restock_obj := obj_carrying_pid_obj(who_obj, the_pid);                      \
                 if (critter_inven_obj(self_obj,INVEN_TYPE_WORN) == restock_obj) then begin  \
                    remove_armor(who_obj)                                                    \
                 end else if ((critter_inven_obj(who_obj, INVEN_TYPE_LEFT_HAND) == restock_obj) or (critter_inven_obj(who_obj, INVEN_TYPE_RIGHT_HAND) == restock_obj)) then begin     \
                    inven_unwield(who_obj);                                                  \
                 end                                                                         \
              end                                                                            \
              restock_amt := rm_mult_objs_from_inven(who_obj, restock_obj, removed_qty);     \
              destroy_object(restock_obj);                                                   \
           end                                                                               \
           restock_obj := 0;                                                                 \
           restock_amt := 0;

#define stock_pid_qty(who_obj, the_pid, pid_qty)                                                   \
        if (obj_is_carrying_obj_pid(who_obj,the_pid) < pid_qty) then begin                         \
           give_pid_qty(self_obj, the_pid, pid_qty - obj_is_carrying_obj_pid(who_obj,the_pid))     \
        end else if (obj_is_carrying_obj_pid(who_obj,the_pid) > pid_qty) then begin                \
           remove_pid_qty(who_obj, the_pid, (obj_is_carrying_obj_pid(who_obj,the_pid) - pid_qty))  \
        end else begin                                                                             \
           restock_obj := 0;                                                                       \
        end

#define check_restock_item(the_item, min_amt, max_amt, res_perc)                    \
        restock_amt := random(min_amt, max_amt);                                    \
        if (obj_is_carrying_obj_pid(self_obj, the_item) < restock_amt) then begin   \
            if (res_perc >= random(1,100)) then begin                               \
               stock_pid_qty(self_obj, the_item, restock_amt)                       \
            end                                                                     \
        end else begin                                                              \
           stock_pid_qty(self_obj, the_item, restock_amt)                           \
        end
#define check_restock_item_min_limit(the_item, min_amt, max_amt, res_perc)          \
        if (obj_is_carrying_obj_pid(self_obj, the_item) < min_amt) then begin       \
           check_restock_item(the_item, min_amt, max_amt, res_perc)                 \
        end
        
        
        
#include "..\headers\itempid.h"
*/

#include "..\_pbs_main\mod.h"
