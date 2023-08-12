#ifndef PBS_MATH_EXT_H
#define PBS_MATH_EXT_H

// 1.2 has 20% chance to be rounded up to 2
// by burn
procedure math_round_chance(variable val) begin
   variable intVal = floor2(val);
   variable chance = (val - intVal)*100;
   variable rnd = random(1, 100);
   variable ret := (intVal + 1) if rnd <= chance else intVal;
   //debug_log_fmt("val=%.4f, floored=%d, chance=%f, rnd=%d, ret=%d", val, intVal, chance, rnd, ret);
   return ret;
end

#endif
