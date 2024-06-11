#ifndef PBS_ARRAYS_EXT_H
#define PBS_ARRAYS_EXT_H

/**
 * Rounds float value to one of the two nearest integers using probability.
 * - Example: 1.2 has 20% chance to be rounded up to 2
 * - Idea from Burn.
 */
procedure float_list_to_string(variable list, variable precision := 3) begin
   variable fmt := "%."+precision+"f";
   variable str := "[";
   foreach variable v in list begin
      if (strlen(str) > 1) then
         str += ", ";
      str += sprintf(fmt, v);
   end
   str += "]";
   return str;
end

#endif
