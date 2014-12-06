//Recognised modes for set_shader_mode and get_game_mode
#define WORLDMAP   (0x1)
#define LOCALMAP   (0x2) //No point hooking this: would always be 1 at any point at which scripts are running
#define DIALOG     (0x4)
#define ESCMENU    (0x8)
#define SAVEGAME   (0x10)
#define LOADGAME   (0x20)
#define COMBAT     (0x40)
#define OPTIONS    (0x80)
#define HELP       (0x100)
#define CHARSCREEN (0x200)
#define PIPBOY     (0x400)
#define PCOMBAT    (0x800)
#define INVENTORY  (0x1000)
#define AUTOMAP    (0x2000)
#define SKILLDEX   (0x4000)

//Valid arguments to register_hook
#define HOOK_TOHIT           (0)
#define HOOK_AFTERHITROLL    (1)
#define HOOK_CALCAPCOST      (2)
#define HOOK_DEATHANIM1      (3)
#define HOOK_DEATHANIM2      (4)
#define HOOK_COMBATDAMAGE    (5)
#define HOOK_ONDEATH         (6)
#define HOOK_FINDTARGET      (7)
#define HOOK_USEOBJON        (8)
#define HOOK_REMOVEINVENOBJ  (9)
#define HOOK_BARTERPRICE     (10)
#define HOOK_MOVECOST        (11)
#define HOOK_HEXMOVEBLOCKING (12)
#define HOOK_HEXAIBLOCKING   (13)
#define HOOK_HEXSHOOTBLOCKING (14)
#define HOOK_HEXSIGHTBLOCKING (15)
#define HOOK_ITEMDAMAGE      (16)
#define HOOK_AMMOCOST        (17)
#define HOOK_USEOBJ          (18)

//Valid arguments to list_begin
#define LIST_CRITTERS    (0)
#define LIST_GROUNDITEMS (1)
#define LIST_SCENERY     (2)
#define LIST_WALLS       (3)
//#define LIST_TILES       (4) //Not listable via sfall list functions
#define LIST_MISC        (5)
#define LIST_ALL         (9)

//Valid flags for force_encounter_with_flags
#define ENCOUNTER_FLAG_NO_CAR (1)

//The attack types returned by get_attack_type
#define ATKTYPE_LWEP1           (0)
#define ATKTYPE_LWEP2           (1)
#define ATKTYPE_RWEP1           (2)
#define ATKTYPE_RWEP2           (3)
#define ATKTYPE_PUNCH           (4)
#define ATKTYPE_KICK            (5)
#define ATKTYPE_LWEP_RELOAD     (6)
#define ATKTYPE_RWEP_RELOAD     (7)
#define ATKTYPE_STRONGPUNCH     (8)
#define ATKTYPE_HAMMERPUNCH     (9)
#define ATKTYPE_HAYMAKER       (10)
#define ATKTYPE_JAB            (11)
#define ATKTYPE_PALMSTRIKE     (12)
#define ATKTYPE_PIERCINGSTRIKE (13)
#define ATKTYPE_STRONGKICK     (14)
#define ATKTYPE_SNAPKICK       (15)
#define ATKTYPE_POWERKICK      (16)
#define ATKTYPE_HIPKICK        (17)
#define ATKTYPE_HOOKKICK       (18)
#define ATKTYPE_PIERCINGKICK   (19)

//Some possible values for the 4th argument to hs_removeinvobj
#define RMOBJ_DROP      (0x49B875)  //If the object is dropped manually by the player from the inventory screen
#define RMOBJ_TRADE     (0x47761D)  //If the object is offered up as a trade
#define RMOBJ_DROPMULTI (0x45C1CF)  //When dropping a part of a stack (RMOBJ_DROP occures first)

//Return values for "typeof"
#define VALTYPE_NONE  (0) // not used yet
#define VALTYPE_INT   (1)
#define VALTYPE_FLOAT (2)
#define VALTYPE_STR   (3)

// Arrays defines

// create persistent list
#define create_array_list(size)     (create_array(size, 0))
// create temporary list
#define temp_array_list(size)       (temp_array(size, 0))
// create persistent map
#define create_array_map            (create_array(-1, 0))
// create temporary map
#define temp_array_map              (temp_array(-1, 0))
// true if array is map, false otherwise
#define array_is_map(x)             (array_key(x, -1) == 1)
// returns temp list of names of all arrays saved with save_array() in alphabetical order
#define list_saved_arrays           (load_array(0))
// removes array from savegame
#define unsave_array(x)             save_array(0, x)
// true if given item exists in given array, false otherwise
#define is_in_array(item, array)    (scan_array(array, item) != -1)
// true if given array exists, false otherwise
#define array_exists(array)         (len_array(array) != -1)
// sort array in ascending order
#define sort_array(array)           resize_array(array, -1)
// sort array in descending order
#define sort_array_reverse(array)   resize_array(array, -2)
// remove element from map or just replace value with 0 for list
#define unset_array(array, item)    set_array(array, item, 0)

#define set_attack_explosion_pattern(x, y)    metarule2_explosions(1, x, y)
#define set_attack_explosion_art(x, y)        metarule2_explosions(2, x, y)  
#define set_attack_explosion_radius(x)        metarule2_explosions(3, x, 0)  
#define set_attack_is_explosion(x)            metarule2_explosions(4, x, 0)  
#define set_attack_is_explosion_fire          set_attack_is_explosion(DMG_fire)