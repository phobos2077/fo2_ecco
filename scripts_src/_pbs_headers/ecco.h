/* Economy and Combat Rebalance Mod */
/* Main header file */
/* author: phobos2077 */

#ifndef ECCO_MOD_H
#define ECCO_MOD_H

#include "../sfall/sfall.h"
#include "../sfall/define_lite.h"
#include "../sfall/command_lite.h"
#include "../sfall/define_extra.h"

#include "ecco_define.h"
#include "ecco_ids.h"
#include "ecco_ini.h"
#include "ecco_log.h"
#include "ecco_msg.h"


#define last_deathanim_critter      (get_sfall_global_int(SGVAR_LAST_DEATHANIM_CRITTER))
#define last_deathanim              (get_sfall_global_int(SGVAR_LAST_DEATHANIM))

#define is_badly_damaged_corpse_death_anim(animID)      \
                                    (animID == ANIM_electrify   \
                                    or animID == ANIM_burned_to_nothing  \
                                    or animID == ANIM_electrified_to_nothing  \
                                    or animID == ANIM_exploded_to_nothing  \
                                    or animID == ANIM_melted_to_nothing \
                                    or animID == ANIM_fire_dance)

#define is_critter_corpse_badly_damaged(crit)            \
                                (crit == last_deathanim_critter \
                                and is_badly_damaged_corpse_death_anim(last_deathanim))



// different macros
#define get_proto_dmg_min(pid)       (get_proto_data(pid, PROTO_WP_DMG_MIN))
#define get_proto_dmg_max(pid)       (get_proto_data(pid, PROTO_WP_DMG_MAX))

#define exp_for_kill_critter_pid(pid)         (get_proto_data(pid, PROTO_CR_KILL_EXP))
#define critter_flags_by_pid(pid)             (get_proto_data(pid, PROTO_CR_FLAGS))
#define can_steal_from_critter_pid(pid)       (not proto_critter_has_flag(pid, CFLG_NOSTEAL))
#define critter_facing_dir(crit)              (has_trait(TRAIT_OBJECT,crit,OBJECT_CUR_ROT))

#define is_critter(obj)      (obj_type(obj) == OBJ_TYPE_CRITTER)
#define is_item(obj)         (obj_type(obj) == OBJ_TYPE_ITEM)
#define is_wall(obj)         (obj_type(obj) == OBJ_TYPE_WALL)
#define is_scenery(obj)      (obj_type(obj) == OBJ_TYPE_SCENERY)

#define is_weapon(obj)       (obj_item_subtype(obj) == item_type_weapon)
#define is_ammo(obj)         (obj_item_subtype(obj) == item_type_ammo)

#define is_human(crit)       (critter_kill_type(crit) >= 0 and critter_kill_type(crit) <= 4)
#define is_animal(crit)      (critter_kill_type(crit) == KILL_TYPE_brahmin_kills \
            or critter_kill_type(crit) == KILL_TYPE_radscorpion_kills \
            or critter_kill_type(crit) == KILL_TYPE_rat_kills \
            or critter_kill_type(crit) == KILL_TYPE_dog_kills \
            or critter_kill_type(crit) == KILL_TYPE_gecko_kills \
            or critter_kill_type(crit) == KILL_TYPE_giant_ant_kills)
#define is_deathclaw(crit)   (critter_kill_type(crit) == KILL_TYPE_deathclaw_kills)
#define is_molerat(crit)     (proto_data(obj_pid(crit), cr_fid) == 0x01000013 or proto_data(obj_pid(crit), cr_fid) == 0x0100004C)
#define is_floater(crit)     (critter_kill_type(crit) == KILL_TYPE_floater_kills)
#define is_centaur(crit)     (critter_kill_type(crit) == KILL_TYPE_centaur_kills)
#define is_alien(crit)       (critter_kill_type(crit) == KILL_TYPE_alien_kills)
#define is_gecko(crit)       (critter_kill_type(crit) == KILL_TYPE_gecko_kills)
#define is_scorpion(crit)    (critter_kill_type(crit) == KILL_TYPE_radscorpion_kills)


#define tile_fid_is_stone(x)  ((x < 84) or  \
                           (x > 116 and x < 172) or   \
                           (x > 235 and x < 275) or   \
                           (x > 506 and x < 715) or   \
                           (x > 812 and x < 1053) or   \
                           (x > 1927 and x < 2093) or   \
                           (x > 2115 and x < 2289) or   \
                           (x > 2516 and x < 2529))
#define tile_fid_is_wood(x)   ((x > 83 and x < 102) or   \
                           (x > 224 and x < 233) or   \
                           (x > 326 and x < 508) or   \
                           (x > 2290 and x < 2389))
#define tile_fid_is_metal(x)  ((x > 101 and x < 117) or   \
                           (x > 222 and x < 225) or   \
                           (x > 232 and x < 236) or   \
                           (x > 274 and x < 327) or   \
                           (x > 1457 and x < 1500) or   \
                           (x > 1826 and x < 1892) or   \
                           (x > 2388 and x < 2400) or   \
                           (x > 2763))
#define tile_fid_is_dirt(x)   ((x > 171 and x < 221) or   \
                           (x > 714 and x < 720) or   \
                           (x > 801 and x < 812) or   \
                           (x > 2092 and x < 2116) or   \
                           (x > 2528 and x < 2548) or   \
                           (x > 1095 and x < 1375) or   \
                           (x > 1395 and x < 1458) or   \
                           (x > 1502 and x < 1611) or   \
                           (x > 1671 and x < 1827))
#define tile_fid_is_slime(x)  ((x > 1052 and x < 1081))
#define tile_fid_is_cloth_on_dirt(x) ((x > 1374 and x < 1390) or   \
                           (x > 1620 and x < 1672))
#define tile_fid_is_carpet(x) ((x > 1891 and x < 1928))
#define tile_fid_is_grass(x)   (x > 2288 and x < 2291)

//weapon definez


#define is_melee_attack(type)   (type == ATTACK_MODE_PUNCH or type == ATTACK_MODE_KICK or type == ATTACK_MODE_SWING or type == ATTACK_MODE_THRUST)

#define tile_behind_obj_rng(who, rng)       (tile_num_in_direction(tile_num(who),((has_trait(TRAIT_OBJECT,who,OBJECT_CUR_ROT) + 3) % 6), rng))

#define attacker_behind_target(oA, oT)                                                         \
      ((tile_distance(tile_num(oA),tile_behind_obj_rng(oT, 2))<=2) and (tile_distance_objs(oA,oT)<=2))

/* Sneak Attacks */
#define is_sneak_attack(attacker, target, type)                                          \
   (is_melee_attack(type) and using_skill(attacker,SKILL_SNEAK) and attacker_behind_target(attacker, target))
//#define can_sneak_attack(x)         (has_skill(x,SKILL_SNEAK)>=50)
//#define sneak_damage_bonus(x)

// is weapon club-like
#define is_club_weapon_pid(x)   (get_proto_data(x, PROTO_WP_ANIM) == WPN_ANIM_CLUB)
#define is_club_weapon(x)       is_club_weapon_pid(obj_pid(x))

// is weapon hammer-like
#define is_hammer_weapon_pid(x)   (get_proto_data(x, PROTO_WP_ANIM) == WPN_ANIM_SLEDGEHAMMER)
#define is_hammer_weapon(x)       is_hammer_weapon_pid(obj_pid(x))

#define is_humanoid(crit)    (proto_data(obj_pid(crit), cr_body_type) == CR_BODY_BIPED)
#define is_weapon_pid(pid)   (proto_data(pid, it_type) == item_type_weapon)

#define actual_ammo_count(crit, obj)   ((obj_is_carrying_obj(crit, obj) - 1)*get_proto_data(obj_pid(obj), PROTO_AM_PACK_SIZE) + get_weapon_ammo_count(obj))

#define is_using_ammo_pid(crit, pid)    (get_weapon_ammo_pid(critter_inven_obj(crit, 1)) == pid or get_weapon_ammo_pid(critter_inven_obj(crit, 2)) == pid)

#define weapon_anim_code(weapon)                      get_proto_data(obj_pid(weapon), PROTO_WP_ANIM)
#define critter_fid_can_use_weapon_pid(fid, pid)      art_exists(fid bwor (get_proto_data(pid, PROTO_WP_ANIM) * 0x1000)))
#define critter_has_art_for_weapon(crit, weapon)      critter_fid_can_use_weapon_pid(obj_art_fid(crit), obj_pid(weapon))


#define pbs_global(x)                  (get_array(load_array(ARR_PBS_GLOBALS), x))
#define set_pbs_global(x, val)         (set_array(load_create_array_map(ARR_PBS_GLOBALS), x, val))
// #define pbs_mod_version             (pbs_var("_version"))

#include "ecco_ini.h"

#endif
