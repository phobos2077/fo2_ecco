
#ifndef DEFINE_EXTRA_H
#define DEFINE_EXTRA_H

#define ATTACK_MODE_NONE      0
#define ATTACK_MODE_PUNCH     1
#define ATTACK_MODE_KICK      2
#define ATTACK_MODE_SWING     3
#define ATTACK_MODE_THRUST    4
#define ATTACK_MODE_THROW     5
#define ATTACK_MODE_SINGLE    6
#define ATTACK_MODE_BURST     7
#define ATTACK_MODE_FLAME     8

#define OBJ_TYPE_ITEM		  (0)
#define OBJ_TYPE_CRITTER	  (1)
#define OBJ_TYPE_SCENERY	  (2)
#define OBJ_TYPE_WALL		  (3)
#define OBJ_TYPE_TILE		  (4)
#define OBJ_TYPE_MISC		  (5)
#define OBJ_TYPE_SPATIAL	  (6)

/* Critter Flags */
#define CFLG_BARTER			    2		//0x00000002 - Barter (can trade with)
#define CFLG_STEAL			   32		//0x00000020 - Steal (cannot steal from)
#define CFLG_DROP			   64		//0x00000040 - Drop (doesn't drop items)
#define CFLG_LIMBS			  128		//0x00000080 - Limbs (can not lose limbs)
#define CFLG_AGES		  	  256		//0x00000100 - Ages (dead body does not disappear)
#define CFLG_HEAL			  512		//0x00000200 - Heal (damage is not cured with time)
#define CFLG_INVULN			 1024		//0x00000400 - Invulnerable (cannot be hurt)
#define CFLG_FLATTN			 2048		//0x00000800 - Flatten (leaves no dead body)
#define CFLG_SPECIAL		 4096		//0x00001000 - Special (there is a special type of death)
#define CFLG_RANGE			 8192		//0x00002000 - Range (melee attack is possible at a distance)
#define CFLG_KOCK			16384		//0x00004000 - Knock (cannot be knocked down)

//remove inven obj defines
#define RMOBJ_CONSUME_DRUG	      4666772
#define RMOBJ_CONTAINER	          4683293  // same as RMOBJ_TRADE
#define RMOBJ_USE_OBJ	          4666865
#define RMOBJ_EQUIP_ARMOR	      4658121
#define RMOBJ_EQUIP_WEAPON	      4658675
#define RMOBJ_UNLOAD_WEAPON	      4667030
//#definE RMOBJ_LOAD_WEAPON	      4831349 // same as RMOBJ_DROP
#define RMOBJ_USE_DRUG_ON	      4834866
#define RMOBJ_STEAL_VIEW	      4668206
//#define RMOBJ_DROP_DYNAMITE	  4666865 // same as USE_OBJ 
#define RMOBJ_ITEM_DESTROYED	  4543215
#define RMOBJ_ITEM_REMOVED	      4548572
#define RMOBJ_ARMOR_EQUIPED	      4651961
#define RMOBJ_LEFT_HAND_EQUIPED	  4651899
#define RMOBJ_RIGHT_HAND_EQUIPED  4651934
#define RMOBJ_RM_MULT_OBJS 	      4563866
#define RMOBJ_REPLACE_WEAPON      4658526
#define RMOBJ_THROW               4266040

// offsets for get_proto_data
#define PROTO_PID             (1)
#define PROTO_TEXTID          (4)

// items
#define PROTO_IT_FLAGS       (24)
#define PROTO_IT_TYPE        (32)
#define PROTO_IT_MATERIAL   (108)
#define PROTO_IT_SIZE       (112)
#define PROTO_IT_WEIGHT     (116)
#define PROTO_IT_COST       (120)

// weapons
#define PROTO_WP_DMG_MIN     (40)
#define PROTO_WP_DMG_MAX     (44)
#define PROTO_WP_RANGE_1     (52)
#define PROTO_WP_RANGE_2     (56)
#define PROTO_WP_PROJ_PID    (60)
#define PROTO_WP_MIN_ST      (64)
#define PROTO_WP_APCOST_1    (68)
#define PROTO_WP_APCOST_2    (72)
#define PROTO_WP_BURST       (84)
#define PROTO_WP_CALIBER     (88)
#define PROTO_WP_AMMO_PID    (92)
#define PROTO_WP_MAG_SIZE    (96)
#define PROTO_WP_ANIM        (36)

// armor
#define PROTO_AR_AC           (36)
#define PROTO_AR_DR_NORMAL    (40)
#define PROTO_AR_DR_LASER     (44)
#define PROTO_AR_DR_FIRE      (48)
#define PROTO_AR_DR_PLASMA    (52)
#define PROTO_AR_DR_ELECTRICAL   (56)
#define PROTO_AR_DR_EMP       (60)
#define PROTO_AR_DR_EXPLOSION (64)
#define PROTO_AR_DT_NORMAL    (68)
#define PROTO_AR_DT_LASER     (72)
#define PROTO_AR_DT_FIRE      (76)
#define PROTO_AR_DT_PLASMA    (80)
#define PROTO_AR_DT_ELECTRICAL   (84)
#define PROTO_AR_DT_EMP       (88)
#define PROTO_AR_DT_EXPLOSION (92)

// ammo
#define PROTO_AM_CALIBER      (36)
#define PROTO_AM_PACK_SIZE    (40)
#define PROTO_AM_AC_MOD       (44)
#define PROTO_AM_DR_MOD       (48)
#define PROTO_AM_DMG_MULT     (52)
#define PROTO_AM_DMG_DIV      (56)

// critters
#define PROTO_CR_CRITTER_FLAGS   (32)
#define PROTO_CR_KILL_EXP       (392)
#define PROTO_CR_KILL_TYPE      (396)

// weapon calibers
#define CALIBER_NONE                 (0)
#define CALIBER_ROCKET               (1)
#define CALIBER_FLAMER_FUEL          (2)
#define CALIBER_SMALL_ENERGY_CELL    (3)
#define CALIBER_MICRO_FUSION_CELL    (4)
#define CALIBER_223                  (5)
#define CALIBER_5MM                  (6)
#define CALIBER_40                   (7)
#define CALIBER_10MM                 (8)
#define CALIBER_44                   (9)
#define CALIBER_14MM                (10)
#define CALIBER_12_GAUGE            (11)
#define CALIBER_9MM                 (12)
#define CALIBER_BB                  (13)
#define CALIBER_45                  (14)
#define CALIBER_2MM                 (15)
#define CALIBER_4_7MM_CASELESS      (16)
#define CALIBER_HN_NEEDLER          (17)
#define CALIBER_7_62MM              (18)

#endif // DEFINE_EXTRA_H
