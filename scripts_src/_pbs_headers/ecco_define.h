#ifndef ECCO_DEFINE_H
#define ECCO_DEFINE_H

#define obj_team(obj)   (has_trait(TRAIT_OBJECT, obj, OBJECT_TEAM_NUM))

#define critter_dt_by_dmg_type(crit, type)    (get_critter_stat(crit, STAT_dmg_thresh + type))
#define critter_dr_by_dmg_type(crit, type)    (get_critter_stat(crit, STAT_dmg_resist + type))
#define critter_max_hp(crit)                  (get_critter_stat(crit, STAT_max_hp))
#define critter_proto_has_flag(pid, flg)      ((get_proto_data(pid, PROTO_CR_FLAGS) bwand flg) != 0)

#define proto_has_ext_flag(pid, flg)          ((get_proto_data(pid, PROTO_FLAG_EXT) bwand flg) != 0)
#define item_proto_is_hidden(pid)             proto_has_ext_flag(pid, HIDDEN_ITEM)

#endif
   