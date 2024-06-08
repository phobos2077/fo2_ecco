#ifndef PBS_MAPS_UTILS
#define PBS_MAPS_UTILS

#define start_point_tile(point)        (point bwand 0xFFFF)
#define start_point_elev(point)        (point / 0x10000)

procedure load_map_start_points(variable prefix := "") begin
   variable
      cfg := get_ini_config_db("data\\maps.txt"),
      mapInfo := cfg[sprintf("Map %03d", cur_map_index)];

   if (not mapInfo) then return 0;
   variable i,
      points := [];

   for (i := 0; i < 20; i++) begin
      variable pointStr := mapInfo[prefix + "random_start_point_" + i];
      if (not pointStr) then
         break;

      variable elev := 0, tile,
         p := string_find(pointStr, "tile_num:");
      if (p < 0) then
         continue;

      tile := atoi(substr(pointStr, p + 9, 0));
      p := string_find(pointStr, "elev:");
      if (p >= 0) then
         elev := atoi(substr(pointStr, p + 5, 0));

      call array_push(points, tile + elev * 0x10000);
   end
   return points;
end


#endif
