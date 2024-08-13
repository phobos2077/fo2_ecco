#ifndef DAMAGE_MOD_H
#define DAMAGE_MOD_H

#define DT_MODE_ADD   (1)
#define DT_MODE_MULT  (2)

#ifdef _DAMAGE_MOD_EXPORT
export variable begin
#else
import variable begin
#endif
   ini_dt_mode_positive;
   ini_dt_mode_negative;
   ini_dt_mult_positive;
   ini_dt_mult_negative;
   ini_damage_types;
end

variable
   last_dtdr;

procedure get_weapon_damage_type_override(variable weapon) begin
   variable dmgType, ammoPid;
   // First, check override for ammo.
   ammoPid := get_weapon_ammo_pid(weapon);
   if (ammoPid and ini_damage_types[ammoPid]) then begin
      return ini_damage_types[ammoPid] - 1;
   end else if (ini_damage_types[obj_pid(weapon)]) then begin  // check override for weapon
      return ini_damage_types[obj_pid(weapon)] - 1;
   end
   return -1;
end

procedure calc_dtdr_vanilla_plus(variable targetDT, variable targetDR, variable ammoDR) begin
   variable calcDRMod, dtMult, dtMode;

   // Use separate mode and multiplier for positive and negative DR Adjust.
   if (ammoDR > 0) then begin
      dtMode := ini_dt_mode_positive;
      dtMult := ini_dt_mult_positive;
   end else begin
      dtMode := ini_dt_mode_negative;
      dtMult := ini_dt_mult_negative;
   end
   switch dtMode begin
      case DT_MODE_ADD:  targetDT += 0.1 * ammoDR * dtMult;
      case DT_MODE_MULT: targetDT *= 1.0 + 0.01 * ammoDR * dtMult;
   end

   // No change to DR calculation.
   targetDR += ammoDR;

   if (not last_dtdr) then
      last_dtdr := create_array_list(2);

   last_dtdr[0] := math_max(targetDT, 0);
   last_dtdr[1] := math_max(math_min(targetDR, 100), 0);
   return last_dtdr;
end

procedure calc_effective_dtdr(variable targetDT, variable targetDR, variable ammoDR, variable ctdSource, variable bypassArmor,
   variable weaponPerk, variable attackType)
begin
   if (bypassArmor) then begin
      targetDT := targetDT * 20 / 100;
      targetDR := targetDR * 20 / 100;
   end else begin
      if (weaponPerk == PERK_weapon_penetrate)
         or (attackType == ATKTYPE_PALMSTRIKE or attackType == ATKTYPE_PIERCINGSTRIKE
         or attackType == ATKTYPE_HOOKKICK or attackType == ATKTYPE_PIERCINGKICK) then
         targetDT := targetDT * 20 / 100;

      if ctdSource == dude_obj and has_trait(TRAIT_TRAIT, ctdSource, TRAIT_finesse) then
         targetDR += 30;
   end

   return calc_dtdr_vanilla_plus(targetDT, targetDR, ammoDR);
end

#endif // DAMAGE_MOD_H
