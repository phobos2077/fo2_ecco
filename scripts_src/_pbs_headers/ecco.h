/* Economy and Combat Rebalance Mod */
/* Main header file */
/* author: phobos2077 */

#ifndef ECCO_MOD_H
#define ECCO_MOD_H

#include "../sfall/sfall.h"
#include "../sfall/define_lite.h"
#include "../sfall/define_extra.h"

#define SCRIPT_TEST2            (4)

#define SGVAR_CRITTERS_SEE_DUDE        ("PBSACSD_")
#define SGVAR_TRAPS_BY_DUDE            ("PBSTRPS_")
#define SGVAR_TRAPS_BY_DUDE_LOCAL      ("PBSTRPSL")
#define SGVAR_TRAPS_LAST_MAP           ("PBSTRPSM")
#define SGVAR_TRAPS_LAST_ARMAMENT      ("PBSTRPAR")
// #define SGVAR_TRAP_VICTIMS             ("PBSTRPVC")
// #define SGVAR_TRAP_FAILED_PID          ("PBSTRPSF")
// #define SGVAR_FAKE_EXPLOSIONS          ("PBSEXPLO")
#define SGVAR_ANGRY_TEAMS              ("PBSANGRY")
#define SGVAR_LAST_DEATHANIM           ("PBSLTDTA")
#define SGVAR_LAST_DEATHANIM_CRITTER   ("PBSLTDTC")
#define SGVAR_REMOVE_ITEM              ("PBSRMITM")
// quests:
#define SGVAR_BOUNTY_NUM_ROBBERS       ("PQST_ROB")

// arrays
#define ARR_TRAPVARS             "pbs_trapvars"
#define ARR_PBS_GLOBALS          "phobos2077"
#define ARR_TRAPS                "pbs_traps"
#define ARR_ANGRY_TEAMS          "pbs_angry_teams"
#define ARR_TRAPS_LOCAL          "pbs_traps_local"
#define ARR_TRAP_VICTIMS         "pbs_trap_victims"
#define ARR_CRITTERS_SEE_DUDE    "pbs_see_dude"

// normal global variables
#define GVAR_BOUNTY_REDDING         (644)
#define GVAR_BOUNTY_NCR             (645)
#define GVAR_BRINGX_TENTACLES       (646)
#define GVAR_BRINGX_HIDES           (647)

// new items
#define PID_PBS_50_AMMO             (610)
#define PID_PBS_THROWING_AXE        (611)
#define PID_PBS_DRAGON_SKIN         (612)
#define PID_PBS_HOMEMADE_GRENADE    (613)
#define PID_PBS_SHOTGUN_SLUGS       (614)
#define PID_PBS_223_AP              (615)
#define PID_PBS_TRAP_KIT_MINE       (616)
#define PID_PBS_TASER               (617)
#define PID_PBS_TRAP_KIT_SPIKE      (618)
#define PID_PBS_TRAP_KIT_SENSOR     (619)
#define PID_PBS_HERCULES            (620)
#define PID_PBS_SEVERED_ARM         (621)
#define PID_PBS_DEATH_CLAW          (622)
#define PID_PBS_MOLERAT_HIDE        (623)
#define PID_PBS_TENTACLE            (624)
#define PID_PBS_ALIEN_HAND          (625)
#define PID_PBS_BONE_AMULET         (626)
#define PID_PBS_FOOD_1              (627)
#define PID_PBS_FOOD_2              (628)
#define PID_PBS_9MM_SMG             (629)
#define PID_PBS_M79                 (630)
#define PID_PBS_40MM_HE             (631)
#define PID_PBS_40MM_IC             (632)
#define PID_PBS_14MM_JHP            (633)
#define PID_PBS_MGL                 (634)
#define PID_PBS_TRAPS_BOOK          (635)
#define PID_PBS_BARTER_BOOK         (636)
#define PID_PBS_BOOMERANG           (637)
#define PID_PBS_SPIKED_SLEDGE       (638)
#define PID_PBS_PISTON_SPEAR        (639)
#define PID_PBS_DEATHCLAW_GAUNTLET  (640)
#define PID_PBS_DRAGON_BREATH       (641)

// new scenery
#define PID_PBS_SPIKE_TRAP_DISARMED  (0x02000000 + 2335)
#define PID_PBS_SPIKE_TRAP           (0x02000000 + 2336)
#define PID_PBS_MINE_DISARMED        (0x02000000 + 2337)
#define PID_PBS_MINE                 (0x02000000 + 2338)
#define PID_PBS_SENSOR_MINE_DISARMED (0x02000000 + 2339)
#define PID_PBS_SENSOR_MINE          (0x02000000 + 2340)
// some old scenery
#define PID_STEAM                   (0x020004A4)
#define PID_STEAM_2                 (0x0200073B)

// new calibers
#define CALIBER_50                  (19)
#define CALIBER_40MM_GRENADE        (20)

#define msg(x)                      display_msg(x)

// macros for arrays
#define is_in_array(item, array)    (scan_array(array, item) != -1)

#define dude_skill(x)               (has_skill(dude_obj, x))
#define dude_perk(x)                (has_trait(TRAIT_PERK,dude_obj,x))

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

//#define is_unarmed_weapon_pid(pid)      (get_proto_data(pid, 36) == 0)
#define is_unarmed_weapon_pid(pid)      (get_proto_data(pid, PROTO_IT_FLAGS) bwand 0x000000FF == 0x01)

#define critter_dt_by_dmg_type(crit, type)    (get_critter_stat(crit, 17 + type))
#define critter_dr_by_dmg_type(crit, type)    (get_critter_stat(crit, 24 + type))
#define critter_max_hp(crit)                  (get_critter_stat(crit, STAT_max_hp))
#define exp_for_kill_critter_pid(pid)         (get_proto_data(pid, PROTO_CR_KILL_EXP))
#define critter_flags_by_pid(pid)             (get_proto_data(pid, PROTO_CR_FLAGS))
#define can_steal_from_critter_pid(pid)       ((critter_flags_by_pid(pid) bwand CFLG_NOSTEAL) == 0)
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


#define tile_is_stone(x)  ((get_tile_fid(x) < 84) or  \
                           (get_tile_fid(x) > 116 and get_tile_fid(x) < 172) or   \
                           (get_tile_fid(x) > 235 and get_tile_fid(x) < 275) or   \
                           (get_tile_fid(x) > 506 and get_tile_fid(x) < 715) or   \
                           (get_tile_fid(x) > 812 and get_tile_fid(x) < 1053) or   \
                           (get_tile_fid(x) > 1927 and get_tile_fid(x) < 2093) or   \
                           (get_tile_fid(x) > 2115 and get_tile_fid(x) < 2289) or   \
                           (get_tile_fid(x) > 2516 and get_tile_fid(x) < 2529))
#define tile_is_wood(x)   ((get_tile_fid(x) > 83 and get_tile_fid(x) < 102) or   \
                           (get_tile_fid(x) > 224 and get_tile_fid(x) < 233) or   \
                           (get_tile_fid(x) > 326 and get_tile_fid(x) < 508) or   \
                           (get_tile_fid(x) > 2290 and get_tile_fid(x) < 2389))
#define tile_is_metal(x)  ((get_tile_fid(x) > 101 and get_tile_fid(x) < 117) or   \
                           (get_tile_fid(x) > 222 and get_tile_fid(x) < 225) or   \
                           (get_tile_fid(x) > 232 and get_tile_fid(x) < 236) or   \
                           (get_tile_fid(x) > 274 and get_tile_fid(x) < 327) or   \
                           (get_tile_fid(x) > 1457 and get_tile_fid(x) < 1500) or   \
                           (get_tile_fid(x) > 1826 and get_tile_fid(x) < 1892) or   \
                           (get_tile_fid(x) > 2388 and get_tile_fid(x) < 2400) or   \
                           (get_tile_fid(x) > 2763))
#define tile_is_dirt(x)   ((get_tile_fid(x) > 171 and get_tile_fid(x) < 221) or   \
                           (get_tile_fid(x) > 714 and get_tile_fid(x) < 720) or   \
                           (get_tile_fid(x) > 801 and get_tile_fid(x) < 812) or   \
                           (get_tile_fid(x) > 2092 and get_tile_fid(x) < 2116) or   \
                           (get_tile_fid(x) > 2528 and get_tile_fid(x) < 2548) or   \
                           (get_tile_fid(x) > 1095 and get_tile_fid(x) < 1375) or   \
                           (get_tile_fid(x) > 1395 and get_tile_fid(x) < 1458) or   \
                           (get_tile_fid(x) > 1502 and get_tile_fid(x) < 1611) or   \
                           (get_tile_fid(x) > 1671 and get_tile_fid(x) < 1827))
#define tile_is_slime(x)  ((get_tile_fid(x) > 1052 and get_tile_fid(x) < 1081))
#define tile_is_cloth_on_dirt(x) ((get_tile_fid(x) > 1374 and get_tile_fid(x) < 1390) or   \
                           (get_tile_fid(x) > 1620 and get_tile_fid(x) < 1672))
#define tile_is_carpet(x) ((get_tile_fid(x) > 1891 and get_tile_fid(x) < 1928))
#define tile_is_grass(x)   (get_tile_fid(x) > 2288 and get_tile_fid(x) < 2291)

//weapon definez

#define no_anim(x)                (get_proto_data(x, PROTO_WP_ANIM) == 0)
#define knife_anim(x)             (get_proto_data(x, PROTO_WP_ANIM) == 1)
#define club_anim(x)              (get_proto_data(x, PROTO_WP_ANIM) == 2)
#define sledge_anim(x)            (get_proto_data(x, PROTO_WP_ANIM) == 3)
#define spear_anim(x)             (get_proto_data(x, PROTO_WP_ANIM) == 4)
#define pistol_anim(x)            (get_proto_data(x, PROTO_WP_ANIM) == 5)
#define smg_anim(x)               (get_proto_data(x, PROTO_WP_ANIM) == 6)
#define rifle_anim(x)             (get_proto_data(x, PROTO_WP_ANIM) == 7)
#define big_gun_anim(x)           (get_proto_data(x, PROTO_WP_ANIM) == 8)
#define minigun_anim(x)           (get_proto_data(x, PROTO_WP_ANIM) == 9)
#define rocket_launcher_anim(x)   (get_proto_data(x, PROTO_WP_ANIM) == 10)


#define is_melee_attack(type)   (type == ATTACK_MODE_PUNCH or type == ATTACK_MODE_KICK or type == ATTACK_MODE_SWING or type == ATTACK_MODE_THRUST)

#define tile_behind_obj_rng(who, rng)                                                         \
      (tile_num_in_direction(tile_num(who),((has_trait(1,who,10) + 3) % 6), rng))

#define attacker_behind_target(oA, oT)                                                         \
      ((tile_distance(tile_num(oA),tile_behind_obj_rng(oT, 2))<=2) and (tile_distance_objs(oA,oT)<=2))

/* Sneak Attacks */
#define is_sneak_attack(attacker, target, type)                                          \
   (is_melee_attack(type) and using_skill(attacker,SKILL_SNEAK) and attacker_behind_target(attacker, target))
//#define can_sneak_attack(x)         (has_skill(x,SKILL_SNEAK)>=50)
//#define sneak_damage_bonus(x)

// is weapon club-like
#define is_club_weapon_pid(x)   ((x==5) or (x==20) or (x==384) or (x==386))
#define is_club_weapon(x)      is_club_weapon_pid(obj_pid(x))

// is weapon hammer-like
#define is_hammer_weapon_pid(x)   ((x==6) or (x==115))
#define is_hammer_weapon(x)      is_club_weapon_pid(obj_pid(x))

#define is_humanoid(crit)    (proto_data(obj_pid(crit), cr_body_type) == CR_BODY_BIPED)
#define is_weapon_pid(pid)   (proto_data(pid, it_type) == item_type_weapon)

#define obj_team(obj)   (has_trait(TRAIT_OBJECT, obj, OBJECT_TEAM_NUM))

#define combat_mstr(num)      message_str(SCRIPT_TEST2, num)

#define actual_ammo_count(crit, obj)   ((obj_is_carrying_obj_pid(crit, obj_pid(obj)) - 1)*get_proto_data(obj_pid(obj), PROTO_AM_PACK_SIZE) + get_weapon_ammo_count(obj))

#define is_using_ammo_pid(crit, pid)    (get_weapon_ammo_pid(critter_inven_obj(crit, 1)) == pid or get_weapon_ammo_pid(critter_inven_obj(crit, 2)) == pid)

#define weapon_anim_code(weapon)                      get_proto_data(obj_pid(weapon), PROTO_WP_ANIM)
#define critter_fid_can_use_weapon_pid(fid, pid)      art_exists(fid bwor (get_proto_data(pid, PROTO_WP_ANIM) * 0x1000)))
#define critter_has_art_for_weapon(crit, weapon)      critter_fid_can_use_weapon_pid(obj_art_fid(crit), obj_pid(weapon))


#define pbs_global(x)                  (get_array(load_array(ARR_PBS_GLOBALS), x))
#define set_pbs_global(x, val)         (set_array(load_create_array_map(ARR_PBS_GLOBALS), x, val))
// #define pbs_mod_version             (pbs_var("_version"))

#define INI_COMBAT         "combat.ini"
#define INI_ECONOMY        "barter.ini"

#define get_int_from_ini(name, section, setting)       get_ini_setting(name + "|" + section + "|" + setting)
#define get_str_from_ini(name, section, setting)       get_ini_string(name + "|" + section + "|" + setting)
#define get_float_from_ini(name, section, setting)     atof(get_ini_string(name + "|" + section + "|" + setting))

#define int_from_ini_file(name, file, section)    ini_##name := get_int_from_ini(file, section, #name)
#define str_from_ini_file(name, file, section)    ini_##name := get_str_from_ini(file, section, #name)
#define float_from_ini_file(name, file, section)  ini_##name := get_float_from_ini(file, section, #name)

#endif
