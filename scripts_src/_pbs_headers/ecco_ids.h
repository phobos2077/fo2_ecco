#ifndef ECCO_IDS_H
#define ECCO_IDS_H

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
#define ARR_KILL_EXP             "pbs_kill_exp"
#define ARR_DESTROYED_WEAPONS    "pbs_destr_wpns"
//#define ARR_LOOTED_CONTAINERS    "pbs_lootd_contnrs"

// normal global variables
#define GVAR_BOUNTY_REDDING         (644)
#define GVAR_BOUNTY_NCR             (645)
#define GVAR_BRINGX_TENTACLES       (646)
#define GVAR_BRINGX_HIDES           (647)

// repurposed items
#define PID_PBS_DOCTOR_BOOK         (539) // replaces PID_ABBEY_TECHMANUAL2

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
#define PID_PBS_7_62MM_AP           (642)
#define PID_PBS_COWBOY_REPEATER     (643)
#define PID_PBS_14MM_SMG            (644)
#define PID_PBS_TRAP_KIT_BEAR       (645)
#define PID_PBS_FLAMER_LT           (646)
#define PID_PBS_LASER_PISTOL_LT     (647)
#define PID_PBS_PLASMA_LANCE        (648)
#define PID_PBS_CRAFT_SCHEMA        (649)
#define PID_PBS_CRAFT_SCHEMA_T2     (650)

// new scenery
#define PID_PBS_SPIKE_TRAP           (0x02000000 + 2335)
#define PID_PBS_BEAR_TRAP            (0x02000000 + 2336)
#define PID_PBS_MINE_TRAP            (0x02000000 + 2337)
#define PID_PBS_TRAP_RESERVED_4      (0x02000000 + 2338)
#define PID_PBS_SENSOR_MINE          (0x02000000 + 2339)
#define PID_PBS_TRAP_RESERVED_6      (0x02000000 + 2340)
// some old scenery
#define PID_STEAM                   (0x020004A4)
#define PID_STEAM_2                 (0x0200073B)

// new calibers
#define CALIBER_50                  (19)
#define CALIBER_40MM_GRENADE        (20)

#endif
