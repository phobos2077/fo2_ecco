#ifndef ECCO_INI_H
#define ECCO_INI_H

#include "../sfall/lib.math.h"
#include "../sfall/lib.strings.h"

#define INI_SFALL          "ddraw.ini"
#define INI_COMBAT         "ecco\\combat.ini"
#define INI_ECONOMY        "ecco\\barter.ini"
#define INI_MISC           "ecco\\misc.ini"

#define INI_DAMAGE_TYPE_SECTION   "DAMAGE_TYPE"
#define INI_ATTACK_MODES_SECTION  "ATTACK_MODES"

#define get_int_from_ini(file, section, setting)       get_ini_setting(file + "|" + section + "|" + setting)
#define get_str_from_ini(file, section, setting)       get_ini_string(file + "|" + section + "|" + setting)
#define get_float_from_ini(file, section, setting)     atof(get_str_from_ini(file, section, setting))
#define get_list_from_ini(file, section, setting, func) array_transform(array_filter(string_split(get_str_from_ini(file, section, setting), ","), @string_null_or_empty, true), func)
#define get_int_list_from_ini(file, section, setting)  string_split_ints(get_str_from_ini(file, section, setting), ",")

procedure get_ini_value_def(variable file, variable section, variable setting, variable defValue) begin
   variable
      value := get_ini_string(file + "|" + section + "|" + setting),
      defValType := typeof(defValue);
   if (value == -1 or value == "") then
      return defValue;

   if (defValType == VALTYPE_INT) then
      return atoi(value);
   if (defValType == VALTYPE_FLOAT) then
      return atof(value);
   return value;
end

procedure ini_parse_range_clamped(variable str, variable defMin, variable defMax, variable clampMin, variable clampMax) begin
   variable min, max,
      pos := string_find(str, ","),
      isFloat := (typeof(defMin) == VALTYPE_FLOAT);

   // Split
   if (pos >= 0) then begin
      min := substr(str, 0, pos);
      max := substr(str, pos + 1, 0);
   end else begin
      min := str if typeof(str) == VALTYPE_STR else "";
      max := "";
   end
   // Parse and use default values
   min := (atof(min) if isFloat else atoi(min))
      if min and min != ""
      else defMin;
   max := (atof(max) if isFloat else atoi(max))
      if max and max != ""
      else defMax;

   // Clamp
   min := math_clamp(min, clampMin, clampMax);
   max := math_clamp(max, min, clampMax);
   return [min, max];
end


// DEPRECATED begin
#define int_from_ini_file(name, file, section)         ini_##name := get_int_from_ini(file, section, #name)
#define str_from_ini_file(name, file, section)         ini_##name := get_str_from_ini(file, section, #name)
#define float_from_ini_file(name, file, section)       ini_##name := get_float_from_ini(file, section, #name)

#define int_list_from_ini_file(name, file, section)    ini_##name := array_fixed(get_int_list_from_ini(file, section, #name))
#define int_from_ini_file_clamped(name, file, section, min, max)    ini_##name := math_clamp(get_int_from_ini(file, section, #name), min, max)
#define float_from_ini_file_clamped(name, file, section, min, max)  ini_##name := math_clamp(get_float_from_ini(file, section, #name), min, max)
// end DEPRECATED


//#define load_int_from_ini(name, def)                    ini_##name := get_int_from_ini_def(INI_FILE, INI_SECTION, #name, def)
#define load_bool_from_ini(name, def)                           ini_##name := (get_ini_value_def(INI_FILE, INI_SECTION, #name, def) != 0)
#define load_num_from_ini(name, def, min, max)                  ini_##name := math_clamp(get_ini_value_def(INI_FILE, INI_SECTION, #name, def), min, max)
#define load_num_from_ini_unclamped(name, def)                  ini_##name := get_ini_value_def(INI_FILE, INI_SECTION, #name, def)
#define load_int_list_from_ini(name)                            ini_##name := array_fixed(get_int_list_from_ini(INI_FILE, INI_SECTION, #name))
#define load_range_from_ini(name, defMin, defMax, min, max)     ini_##name := array_fixed(ini_parse_range_clamped(get_str_from_ini(INI_FILE, INI_SECTION, #name), defMin, defMax, min, max))

#endif
