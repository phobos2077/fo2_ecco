#ifndef PBS_CRAFT_CONFIG_H
#define PBS_CRAFT_CONFIG_H

#include "../sfall/sfall.h"
#include "../sfall/lib.arrays.h"
#include "../sfall/lib.math.h"
#include "../sfall/lib.strings.h"

variable
   craft_cfg,
   craft_raw_cfg;

procedure load_crafting_config;

#define load_raw_crafting_config    get_ini_config_db("config\\pbs_craft.ini")

procedure parse_item_cfg(variable value) begin
   variable
      i := string_find(value, ":"),
      pid, qty;

   if (i >= 0) then begin
      pid := atoi(substr(value, 0, i));
      qty := atoi(substr(value, i + 1, 0));
   end else begin
      pid := atoi(value);
      qty := 1;
   end
   return (pid bwand 0xFFFF) bwor (qty * 0x10000);
end

procedure parse_pid_or_list(variable value) begin
   return array_fixed(string_split_ints(value, "|"));
end

procedure parse_component_or_list(variable value) begin
   return array_fixed(array_transform(string_split(value, "|"), @parse_item_cfg));
end

procedure parse_skill_sum_list(variable value) begin
   variable
      parts := string_split(value, ":"),
      skills := string_split_ints(parts[0], "+"),
      numSkills := len_array(skills);

   resize_array(skills, numSkills + 1);
   skills[numSkills] := atoi(parts[1]); // requirement
   return array_fixed(skills);
end

#define cfg_item_pid(itemData)                   (itemData bwand 0xFFFF)
#define cfg_item_qty(itemData)                   (itemData / 0x10000)

#define cfg_parse_int_def(cfg, ini, name, def)   cfg.name := atoi(ini.name) if ini.name else def
#define cfg_parse_def_clamp(parseFn, cfg, ini, name, def, min, max)   cfg.name := math_clamp(parseFn(ini.name) if ini.name else def, min, max)

procedure load_crafting_config begin
   variable
      ini := craft_raw_cfg,
      iniMain := ini["Main"],
      cfg := create_array_map;
   
   cfg_parse_int_def(cfg, iniMain, use_party, 0);
   cfg_parse_int_def(cfg, iniMain, categories, 0);
   cfg_parse_int_def(cfg, iniMain, use_gvars, 0);
   cfg_parse_def_clamp(atof, cfg, iniMain, exp_skill_mult, 0.0, 0.0, 10.0);
   cfg_parse_def_clamp(atoi, cfg, iniMain, exp_round_to, 1, 1, 100);

   craft_debug("crafting cfg main: " + debug_array_str(cfg));

   cfg.recipes := create_array_map;
   //cfg.categories := create_array_map;
   cfg.recipeNames := create_array_map;

   variable sectName, section, key, val;
   variable recipePrefix := "Recipe ";
   foreach (sectName: section in ini) begin
      if (string_starts_with(sectName, recipePrefix)) then begin
         variable
            recipeKey := substr(sectName, strlen(recipePrefix), 0),
            recipeCfg,
            output := parse_item_cfg(section.output);

         if (not cfg_item_pid(output)) then continue;

         recipeCfg := array_fixed({
            "pid": cfg_item_pid(output),
            "qty": cfg_item_qty(output),
            // TODO: get rid of pic_w/pic_h after sfall update
            "pic_w": atoi(section.pic_w),
            "pic_h": atoi(section.pic_h),
            "gvar": section.gvar,
            "time": atoi(section.time),
            "undo": atoi(section.undo) if section.undo else 0,
            "category": atoi(section.category) if section.category else 0
         });

         //craft_debug("crafting recipe " + recipeKey + ": " + debug_array_str(recipeCfg));
         
         recipeCfg.tools := create_array_list(0);  // parse_comma_list(section.tools, @parse_pid_or_list);
         recipeCfg.skills := create_array_list(0); //parse_comma_list(section.skills, @parse_skill_sum_list);
         recipeCfg.input := create_array_list(0);  //parse_comma_list(section.input, @parse_component_or_list);
         foreach (key: val in section) begin
            if (string_starts_with(key, "tool")) then
               call array_push(recipeCfg.tools, parse_pid_or_list(val));
            else if (string_starts_with(key, "skill")) then
               call array_push(recipeCfg.skills, parse_skill_sum_list(val));
            else if (string_starts_with(key, "input")) then
               call array_push(recipeCfg.input, parse_component_or_list(val));
         end

         //craft_debug("crafting recipe " + recipeKey + " tools: " + debug_array_str_deep(recipeCfg.tools, 2));
         //craft_debug("crafting recipe " + recipeKey + " skills: " + debug_array_str_deep(recipeCfg.skills, 2));
         //craft_debug("crafting recipe " + recipeKey + " input: " + debug_array_str_deep(recipeCfg.input, 2));

         cfg.recipeNames[recipeKey] := proto_data(recipeCfg.pid, it_name);
         cfg.recipes[recipeKey] := recipeCfg;
      end
   end
   sort_map_value(cfg.recipeNames);
   //craft_debug("crafting recipes sorted: " + debug_array_str(cfg.recipeNames));
   craft_debug("Loaded crafting recipes: " + len_array(cfg.recipes));
   return cfg;
end

#endif
