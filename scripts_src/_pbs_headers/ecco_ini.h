#ifndef ECCO_INI_H
#define ECCO_INI_H

#include "../sfall/lib.strings.h"

#define INI_SFALL          "ddraw.ini"
#define INI_COMBAT         "ecco\\combat.ini"
#define INI_ECONOMY        "ecco\\barter.ini"
#define INI_MISC           "ecco\\misc.ini"

#define get_int_from_ini(name, section, setting)       get_ini_setting(name + "|" + section + "|" + setting)
#define get_str_from_ini(name, section, setting)       get_ini_string(name + "|" + section + "|" + setting)
#define get_float_from_ini(name, section, setting)     atof(get_ini_string(name + "|" + section + "|" + setting))
#define get_int_list_from_ini(name, section, setting)  string_split_ints(get_ini_string(name + "|" + section + "|" + setting), ",")

#define int_from_ini_file(name, file, section)         ini_##name := get_int_from_ini(file, section, #name)
#define str_from_ini_file(name, file, section)         ini_##name := get_str_from_ini(file, section, #name)
#define float_from_ini_file(name, file, section)       ini_##name := get_float_from_ini(file, section, #name)

#define int_list_from_ini_file(name, file, section)    ini_##name := array_fixed(get_int_list_from_ini(file, section, #name))
#define int_from_ini_file_clamped(name, file, section, min, max)    ini_##name := math_clamp(get_int_from_ini(file, section, #name), min, max)
#define float_from_ini_file_clamped(name, file, section, min, max)  ini_##name := math_clamp(get_float_from_ini(file, section, #name), min, max)

#endif
