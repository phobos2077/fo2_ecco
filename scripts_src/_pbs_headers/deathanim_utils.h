#ifndef DEATHANIM_UTILS_H
#define DEATHANIM_UTILS_H

#include "../headers/animcomd.h"
#include "../sfall/lib.arrays.h"
#include "../sfall/sfall.h"

variable begin
   death_anims_normal;
   death_anims_maximum;
end

procedure get_death_anims_normal begin
   if (not death_anims_normal) then
      death_anims_normal := array_fixed([
         ANIM_dancing_autofire,
         ANIM_sliced_in_half,
         ANIM_charred_body,
         ANIM_charred_body,
         ANIM_electrify,
         ANIM_fall_back,
         ANIM_big_hole
      ]);
   return death_anims_normal;
end

procedure get_death_anims_maximum begin
   if (not death_anims_maximum) then
      death_anims_maximum := array_fixed([
         ANIM_chunks_of_flesh,
         ANIM_sliced_in_half,
         ANIM_fire_dance,
         ANIM_melted_to_nothing,
         ANIM_electrified_to_nothing,
         ANIM_fall_back,
         ANIM_exploded_to_nothing
      ]);
   return death_anims_maximum;
end

#define critter_anim_fid(objFid, animType, rot)       ((rot * 0x10000000) bwor ((animType * 0x10000) bwand 0xFF0000) bwor (objFid bwand 0xF00FFFF))

procedure validate_critter_anim(variable critter, variable animType) begin
   variable objFid := obj_art_fid(critter);
   variable rot := objFid bwand 0x70000000;
   // This is based on vanilla logic from art_id_()
   if (animType != ANIM_fire_dance and animType >= ANIM_fall_back and animType <= ANIM_fall_front_blood) then begin
      if (art_exists(critter_anim_fid(objFid, animType, 1))) then
         return true;
   end
   return art_exists(critter_anim_fid(objFid, animType, 0));
end


#endif // DEATHANIM_UTILS_H
