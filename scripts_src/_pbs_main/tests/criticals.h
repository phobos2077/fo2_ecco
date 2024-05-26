procedure get_flags_map begin
   return {
      "KNOCKED_OUT": 0x01,
      "KNOCKED_DOWN": 0x02,
      "CRIP_LEG_LEFT": 0x04,
      "CRIP_LEG_RIGHT": 0x08,
      "CRIP_ARM_LEFT": 0x10,
      "CRIP_ARM_RIGHT": 0x20,
      "BLIND": 0x40,
      "DEAD": 0x80,
      "HIT": 0x100,
      "CRITICAL": 0x200,
      "ON_FIRE": 0x400,
      "BYPASS": 0x800,
      "EXPLODE": 0x1000,
      "DESTROY": 0x2000,
      "DROP": 0x4000,
      "LOSE_TURN": 0x8000,
      "HIT_SELF": 0x10000,
      "LOSE_AMMO": 0x20000,
      "DUD": 0x40000,
      "HURT_SELF": 0x80000,
      "RANDOM_HIT": 0x100000,
      "CRIP_RANDOM": 0x200000,
      "BACKWASH": 0x400000,
      "PERFORM_REVERSE": 0x800000
   };
end

procedure get_kill_types begin 
   return [
      "men",
      "women",
      "children",
      "super_mutant",
      "ghoul",
      "brahmin",
      "radscorpion",
      "rat",
      "floater",
      "centaur",
      "robot",
      "dog",
      "manti",
      "deathclaw",
      "plant",
      "gecko",
      "alien",
      "giant_ant",
      "boss"
   ];
end

procedure decode_kill_type(variable killType, variable killTypes) begin
   if (killType < len_array(killTypes)) then
      return killTypes[killType];
   if (killType == 38) then
      return "player";
   return killType;
end

procedure decode_flags(variable flags, variable flagsMap) begin
   variable name, flag, str := "";
   foreach (name: flag in flagsMap) begin
      if ((flags bwand flag) != 0) then begin
         if (str != "") then str += " | ";
         str += name;
      end
   end
   return str;
end

procedure dump_critical_tables begin
   variable killType, killTypeName, bodyPart, bodyPartName, level, field, val, fields := temp_array_list(CRITICAL_VALUE_FAIL_MSG + 1);
   variable flagsMap := get_flags_map, killTypes := get_kill_types,
      statNames := ["ST", "PE", "EN", "CH", "IN", "AG", "LK"],
      bodyPartNames := ["HEAD","LEFT_ARM","RIGHT_ARM","TORSO","RIGHT_LEG","LEFT_LEG","EYES","GROIN","UNCALLED"];

   debug_msg("Dumping Critical Tables:");
   debug_msg("Kill Type,Body Part,Level,DMG Mult,Effect,Stat,Stat Mod,Fail Effect,MSG,Fail MSG");
   for (killType := 0; killType <= 38; killType++) begin
      killTypeName := decode_kill_type(killType, killTypes);
      for (bodyPart := 0; bodyPart <= BODY_UNCALLED; bodyPart++) begin
         bodyPartName := bodyPartNames[bodyPart];
         for (level := 0; level < 6; level++) begin
            for (field := 0; field <= CRITICAL_VALUE_FAIL_MSG; field++) begin
               val := get_critical_table(killType, bodyPart, level, field);
               if (field == CRITICAL_VALUE_EFFECTS or field == CRITICAL_VALUE_FAIL_EFFECT) then
                  val := decode_flags(val, flagsMap);
               else if (field == CRITICAL_VALUE_STAT_CHECK and val >= 0) then
                  val := statNames[val];

               fields[field] := val;
            end
            if (fields[CRITICAL_VALUE_MULT] == 0) then continue;

            debug_msg(string_format("%s,%s,%d,%s", killTypeName, bodyPartName, level, string_join(fields, ",")));
         end
      end
   end
end

