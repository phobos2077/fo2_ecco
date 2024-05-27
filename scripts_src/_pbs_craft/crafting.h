#ifndef PBS_CRAFTING_H
#define PBS_CRAFTING_H

#include "../sfall/sfall.h"
#include "../sfall/lib.arrays.h"
#include "../sfall/lib.inven.h"
#include "../sfall/define_lite.h"
#include "../sfall/define_extra.h"

#include "learn_craft.h"

/*
   TODO:
   - consider replacing dialog with scripted windows, text and buttons
*/

#define craft_debug(text)       if (true) then debug_msg("[craft] "+text)

#include "craft_msg.h"
#include "craft_utils.h"
#include "craft_config.h"
#include "craft_schematics.h"

#define mstr_craft(num)         mstr_pbs_craft(num)

#define ITEMS_PER_SCREEN        9

#define MODE_EXIT               0
#define MODE_ITEMS_LIST         1
#define MODE_ITEM_OPTIONS       2
#define MODE_BATCH_OK           3
#define MODE_UNDO_OK            4
#define MODE_CATEGORY_LIST      5

// should typically be ITEMS_PER_SCREEN + 2
#define MAX_CATEGORIES          (ITEMS_PER_SCREEN + 2)

#define EXP_MAP_NAME            "pbs_craft_exp"
#define pcx_path(name)          "pcx\\" #name ".pcx"


variable begin
   craft_ui_mode;
   use_categories := false;
   craft_exp_map; // maps output item PID to 1 if exp was granted for crafting

   cur_recipe;
   cur_category;
   cur_pos;
   items_avail;
   max_batch;
   max_undo;

   item_values;

   win_x := 0;
   win_y := 0;

   button_pressed;

   display_line;
   display_cur_str;

   num_options;
end

#define has_prev_page           (cur_pos > 0)
#define has_next_page           (cur_pos + ITEMS_PER_SCREEN < items_avail - 1)

#define COLOR_GREEN             0
#define COLOR_RED               1
#define COLOR_DARK_GREEN        2
#define SetText_GREEN           SetTextColor(0.0, 1.0, 0.0)
#define SetText_DARK_GREEN      SetTextColor(0.0, 0.3, 0.0)
#define SetText_RED             SetTextColor(1.0, 0.0, 0.0)

procedure init_crafting;
procedure display_next_option(variable i, variable text, variable value);
procedure redraw_win_idle;
procedure count_items_avail;

procedure draw_item_properties;
procedure draw_item_pcx;

procedure display_category_list;
procedure display_items_list;
procedure display_items_avail;
procedure list_next_proc;
procedure list_back_proc;
procedure display_item_options;
procedure display_batch_ok;
procedure display_undo_ok;

procedure exit_mode;
procedure items_list_mode;
procedure item_options_mode;
procedure batch_ok_mode;
procedure undo_ok_mode;
procedure item_categories_mode;

procedure batch_item(variable num);
procedure undo_batch(variable num);
procedure batch_one_item;
procedure batch_all_items;
procedure undo_one_item;
procedure undo_all_items;

procedure loop_mode;

/******************************************************************************/


procedure init_crafting begin
   craft_ui_mode := MODE_EXIT;
   craft_raw_cfg := load_raw_crafting_config;
   craft_exp_map := load_create_array_map(EXP_MAP_NAME);
end


procedure recipe_is_available(variable recipe) begin
   variable gvar, gvarVal;
   if (cur_category != 0 and recipe.category != cur_category) then return false;

   if (craft_cfg.use_gvars) then begin
      gvar := recipe.gvar;
      if (gvar == "NEVER") then
         return false;
      else if (gvar and gvar != "") then begin
         gvarVal := get_sfall_global_int(gvar) if atoi(gvar) == 0 else global_var(atoi(gvar));
         if (gvarVal == 0) then
            return false;
      end
   end
   if (craft_cfg.use_schematics and recipe.schema) then begin
      if (not schema_is_known(recipe.pid)) then
         return false;
   end
   return true;
end

procedure cur_recipe_batch_size begin
   return cur_recipe.qty * item_pid_pack_size(cur_recipe.pid);
end

procedure gain_exp_for_crafting begin
   variable
      skillMult := craft_cfg.exp_skill_mult,
      pid := cur_recipe.pid;
   if (skillMult <= 0 or craft_exp_map[pid] > 0) then return;
   
   variable
      skillMaxAvg := recipe_max_average_skill(cur_recipe),
      roundTo := craft_cfg.exp_round_to,
      exp := ceil(skillMaxAvg * skillMult * 1.0 / roundTo) * roundTo;

   give_exp_points(exp);
   display_msg(sprintf(mstr_craft(420), exp));
   craft_exp_map[pid] := 1;
end

procedure do_cancel_on begin
end

procedure do_cancel_off begin
   if (button_pressed == true) then play_sfx("IB1LU1X1");
   button_pressed := false;
end

procedure do_cancel_down begin
   if (button_pressed == false) then begin
      button_pressed := true;
      play_sfx("IB1P1XX1");
   end
end

procedure do_cancel_up begin
   button_pressed := false;
   play_sfx("IB1LU1X1");
   call exit_mode;
   SayQuit;
end

procedure show_cancel_button(variable winName) begin
   create_win_flag(winName, win_x + 300, win_y + 347, 342, 32, WIN_FLAG_MOVEONTOP + WIN_FLAG_TRANSPARENT);
   SelectWin(winName);
   Display(pcx_path(w_close));
   AddButton("but2", 133, 6, 15, 16);
   AddButtonGFX("but2", pcx_path(lilreddn), pcx_path(lilredup), pcx_path(lilredup));
   AddButtonProc("but2", do_cancel_on, do_cancel_off, do_cancel_down, do_cancel_up);
   SetFont(103);
   SetTextColor(0.52, 0.75, 0.15);
   Format(mstr_craft(120), 154, 6, 200, 30, 0);
   SetFont(101);
   SetText_GREEN;
   ShowWin;
end

procedure show_crafting_window begin
   craft_debug("show_crafting_window()");
   stop_game;

   if not craft_cfg then craft_cfg := load_crafting_config;

   cur_pos := 0;
   items_avail := 0;
   cur_category := 0;

   win_x := (get_screen_width - 640) / 2;
   win_y := (get_screen_height - 380) / 2;
   if (win_y > 100) then win_y := 100; // for some reason, SayOptionWindow can't be lowered after certain Y coordinate

   SetFont(5);
   SaySetSpacing(3);
   SetText_GREEN;
   SetHighlightColor(1.0, 1.0, 1.0);
   SetHighlightColor(1.0, 1.0, 0.64);

   SayReplyWindow (win_x + 300, win_y +   1, 342, 144, pcx_path(w_rep));
   SayOptionWindow(win_x + 300, win_y + 146, 342, 201, pcx_path(w_opt));
   SayBorder(30, 30);

   create_win_flag("win_dscr", win_x + 1, win_y + 1, 300, 378, WIN_FLAG_EXCLUSIVE);
   SelectWin("win_dscr");
   Display(pcx_path(w_dscr));
   ShowWin;

   // We show these here to remove interface flickery
   CreateWin("win_rep", win_x + 300, win_y +   1, 342, 144);
   SelectWin("win_rep");
   Display(pcx_path(w_rep));
   ShowWin;
   CreateWin("win_opt", win_x + 300, win_y + 146, 342, 201);
   SelectWin("win_opt");
   Display(pcx_path(w_opt));
   ShowWin;

   call show_cancel_button("win_btn");

   play_sfx("IB1P1XX1");

   if (craft_cfg.categories == 1) then begin
      use_categories := true;
   end else if (craft_cfg.categories == 2) then begin
      call count_items_avail;
      if (items_avail > ITEMS_PER_SCREEN) then
         use_categories := true;
   end

   if (use_categories) then begin
      craft_ui_mode := MODE_CATEGORY_LIST;
   end else begin
      craft_ui_mode := MODE_ITEMS_LIST;
      if (items_avail == 0) then
         call count_items_avail;
   end

   if not item_values then item_values := create_array_list(12);

   call loop_mode;

   DeleteWin("win_dscr");
   DeleteWin("win_rep");
   DeleteWin("win_opt");
   DeleteWin("win_btn");

   resume_game;
end

procedure count_items_avail begin
   variable key, recipe;
   items_avail := 0;
   foreach (key: recipe in (craft_cfg.recipes)) begin
      if (recipe_is_available(recipe)) then items_avail += 1;
   end
   craft_debug("items_avail = "+items_avail);
end

procedure loop_mode begin
   while (craft_ui_mode != MODE_EXIT) do begin
      craft_debug("loop_mode(): " + craft_ui_mode);
      if (craft_ui_mode == MODE_ITEMS_LIST)         then call display_items_list;
      else if (craft_ui_mode == MODE_ITEM_OPTIONS)  then call display_item_options;
      else if (craft_ui_mode == MODE_BATCH_OK)      then call display_batch_ok;
      else if (craft_ui_mode == MODE_UNDO_OK)       then call display_undo_ok;
      else if (craft_ui_mode == MODE_CATEGORY_LIST) then call display_category_list;
   end
end

procedure exit_mode begin
   craft_ui_mode := MODE_EXIT;
end

procedure items_list_mode begin
   craft_ui_mode := MODE_ITEMS_LIST;
end

procedure item_options_mode begin
   craft_ui_mode := MODE_ITEM_OPTIONS;
end

procedure batch_ok_mode begin
   craft_ui_mode := MODE_BATCH_OK;
end

procedure undo_ok_mode begin
   craft_ui_mode := MODE_UNDO_OK;
end

procedure item_categories_mode begin
   cur_category := 0;
   craft_ui_mode := MODE_CATEGORY_LIST;
end

procedure display_category_list begin
   variable
      catList,
      key, recipe,
      cat;

   craft_debug("display_category_list(): SayStart");
   SayStart;
      MouseShape(pcx_path(st1), 0, 0);
      SayReply("r_display_list", mstr_craft(210));

      call redraw_win_idle;
      cur_category := 0;
      // 
      catList := temp_array_list(MAX_CATEGORIES + 1);
      foreach (key: recipe in (craft_cfg.recipes)) begin
         cat := recipe.category;
         if (cat > 0 and cat <= MAX_CATEGORIES and catList[cat] == 0 and recipe_is_available(recipe)) then begin
            catList[cat] := 1;
         end
      end
      num_options := 0;
      for (cat := 1; cat < MAX_CATEGORIES + 1; cat++) begin
         if (catList[cat]) then begin
            call display_next_option(num_options, mstr_craft(40 + cat), cat);
            num_options += 1;
         end
      end
      // SayOption(mstr_craft(101), exit_mode);
   SayEnd;
   craft_debug("display_category_list(): SayEnd");
end

procedure display_items_list begin
   craft_debug("display_items_list(): sayStart");
   SayStart;
      MouseShape(pcx_path(st1), 0, 0);
      SayReply("r_display_list", mstr_craft(200));
      //SayOptionColor(5, 9, 255);
      SayOptionFlags(justifyleft);
      call display_items_avail;
      //SayOptionFlags(justifycenter bwor textshadow bwor textdirect);
      craft_debug("display_items_list: sayoption "+mstr_craft(101));
   SayEnd;
   craft_debug("display_items_list(): SayEnd");
end

procedure display_item_options begin
   craft_debug("display_item_options: SayStart()");
   SayStart;
      MouseShape(pcx_path(st1), 0, 0);
      craft_debug("display_item_options SayReply: " + proto_data(cur_recipe.pid, it_description));
      SayReply("r_item_options", proto_data(cur_recipe.pid, it_description));
      call draw_item_pcx;
      call draw_item_properties;
      if (max_batch > 0) then SayOption("1. " + mstr_craft(103), batch_one_item);
      if (max_batch > 1) then SayOption("2. " + mstr_craft(108) + " (" + (max_batch * cur_recipe_batch_size) + ")", batch_all_items);
      if (max_undo > 0) then SayOption("3. " + mstr_craft(104), undo_one_item);
      if (max_undo > 1) then SayOption("4. " + mstr_craft(109) + mstr_craft(110) + (max_undo * cur_recipe_batch_size) + mstr_craft(111), undo_all_items);
      SayOption("0: "+mstr_craft(102), items_list_mode);
      if (use_categories) then
         SayOption(mstr_craft(112), item_categories_mode);
      else
         SayOption("Esc. " + mstr_craft(101), exit_mode); // we have to display at least 2 options to prevent error...
   SayEnd;
   craft_debug("display_item_options: SayEnd()");
end

procedure display_batch_ok begin
   craft_debug("display_batch_ok: SayStart()");
   SayStart;
      MouseShape(pcx_path(st1), 0, 0);
      SayReply("r_batch_item", mstr_craft(201));
      SayOption("0. "+mstr_craft(100), item_options_mode);
      SayOption("Esc. " + mstr_craft(101), exit_mode); // we have to display at least 2 options to prevent error...
   SayEnd;
   craft_debug("display_batch_ok: SayEnd()");
end

procedure display_undo_ok begin
   craft_debug("display_undo_ok: SayStart()");
   SayStart;
      MouseShape(pcx_path(st1), 0, 0);
      SayReply("r_undo_batch", mstr_craft(202));
      SayOption("0. " + mstr_craft(100), item_options_mode);
      SayOption("Esc. " + mstr_craft(101), exit_mode); // we have to display at least 2 options to prevent error...
   SayEnd;
   craft_debug("display_undo_ok: SayEnd()");
end

procedure list_next_proc begin
   cur_pos += ITEMS_PER_SCREEN;
end

procedure list_back_proc begin
   cur_pos -= ITEMS_PER_SCREEN;
end

procedure redraw_win_dscr begin
   SelectWin("win_dscr");
   Display(pcx_path(w_dscr));
   ShowWin;
end

procedure redraw_win_idle begin
   SelectWin("win_dscr");
   Display(pcx_path(w_idle));
   ShowWin;
end

procedure display_items_avail begin
   variable
      skipCounter := 0,
      recipe, key, name;
   craft_debug("display_items_avail()");
   //call redraw_win_dscr;
   call redraw_win_idle;

   num_options := 0;
   foreach (key: name in (craft_cfg.recipeNames)) begin
      recipe := craft_cfg.recipes[key];
      if (recipe_is_available(recipe)) then begin
         if skipCounter < cur_pos then begin
            skipCounter += 1;
            continue;
         end
         call display_next_option(num_options, name, recipe);
         num_options += 1;
         if (num_options >= ITEMS_PER_SCREEN) then break;
      end
   end
   if (has_prev_page) then SayOption("<. " + mstr_craft(106), list_back_proc);
   if (has_next_page) then SayOption(">. " + mstr_craft(105), list_next_proc);
   if (use_categories) then
      SayOption("0. " + mstr_craft(112), item_categories_mode);
   if (items_avail == 0) then
      SayOption(mstr_craft(107), exit_mode);
end

procedure item_selected(variable idx) begin
   if (idx >= num_options) then return;
   craft_debug(string_format("Selected item %d [%d], craft_ui_mode: %d", item_values[idx], idx, craft_ui_mode));
   if (craft_ui_mode == MODE_CATEGORY_LIST) then begin
      cur_category := item_values[idx];
      call count_items_avail; // count available items within selected category
      call items_list_mode;
   end else if (craft_ui_mode == MODE_ITEMS_LIST) then begin
      cur_recipe := item_values[idx];
      call item_options_mode;
   end
end

#define optProcs \
_optProc(0) \
_optProc(1) \
_optProc(2) \
_optProc(3) \
_optProc(4) \
_optProc(5) \
_optProc(6) \
_optProc(7) \
_optProc(8) \
_optProc(9) \
_optProc(10) \
_optProc(11)

// Dialog option handlers.
#define _optProc(NNN) \
pure procedure item_options_##NNN begin \
   call item_selected(NNN); \
end

optProcs
#undef _optProc


procedure display_next_option(variable i, variable text, variable value) begin
   if (i < 9) then
      text := ""+(i+1)+". "+text;

   craft_debug(string_format("Displaying option %d: %s with value %d", i, text, value));
   item_values[i] := value;

   // For some reason, passing callback as string doesn't work with SayOption (I suspect this is how sslc does proc arguments...)
   // So generate this ugly series of IFs with direct references to every handler.
   // >> doesn't work: // SayOption(text, "item_options_"+i);

   #define _optProc(NNN) \
   if (i == NNN) then SayOption(text, item_options_##NNN);
   optProcs
   #undef _optProc
end

procedure batch_item(variable num) begin
   variable
      pid := 0,
      qty := 0,
      hours,
      mins,
      orList,
      componentData,
      item;

   if (random(0,1)) then play_sfx("carrepair");
   else play_sfx("fixstill");

   gfade_out(400);
   game_time_advance(cur_recipe.time * ONE_GAME_MINUTE * num);
   gfade_in(400);

   foreach (orList in (cur_recipe.input)) begin
      // remove first item from "OR" orList that player party has
      foreach (componentData in orList) begin
         pid := cfg_item_pid(componentData);
         qty := cfg_item_qty(componentData);
         if (party_is_carrying_obj_pid(pid) >= qty * num) then begin
            call party_remove_items_pid(pid, qty * num);
            break;
         end
      end
   end
   item := add_items_pid(dude_obj, cur_recipe.pid, num * cur_recipe.qty);
   if (obj_item_subtype(item) == item_type_weapon) then begin
      // Don't produce ammo out of thin air.
      set_weapon_ammo_count(item, 0);
   end
   hours := cur_recipe.time * num / 60;
   mins  := cur_recipe.time * num % 60;
   display_msg(string_format(mstr_craft(400), proto_data(cur_recipe.pid, it_name), (num * cur_recipe_batch_size))
      + string_format(mstr_craft(402), hours, mins));

   call gain_exp_for_crafting;
   call batch_ok_mode;
end

procedure undo_batch(variable num) begin
   variable
      hours,
      mins,
      orList,
      componentData;

   gfade_out(400);
   game_time_advance(cur_recipe.time * ONE_GAME_MINUTE * num);
   gfade_in(400);

   foreach (orList in (cur_recipe.input)) begin
      // give first item from optional orList
      if (len_array(orList) > 0) then begin
         componentData := orList[0];
         call add_items_pid(dude_obj, cfg_item_pid(componentData), cfg_item_qty(componentData) * num);
      end
   end
   call party_remove_items_pid(cur_recipe.pid, num * cur_recipe.qty);
   hours := cur_recipe.time * num / 60;
   mins  := cur_recipe.time * num % 60;
   display_msg(string_format(mstr_craft(401), proto_data(cur_recipe.pid, it_name), (num * cur_recipe_batch_size))
      + string_format(mstr_craft(402), hours, mins));
   call undo_ok_mode;
end

procedure batch_one_item begin
   call batch_item(1);
end

procedure batch_all_items begin
   call batch_item(max_batch);
end

procedure undo_one_item begin
   call undo_batch(1);
end

procedure undo_all_items begin
   call undo_batch(max_undo);
end

procedure display_newline(variable num := 1) begin
   display_line += 10 * num;
   display_cur_str := "";
end

procedure display_print(variable text, variable newLine := true, variable color := COLOR_GREEN, variable justify := 0) begin
   variable
      w := (get_text_width(display_cur_str) if display_cur_str != "" else 0),
      x := (20 + w),
      width := (270 - w);
   if (color == COLOR_DARK_GREEN) then
      SetText_DARK_GREEN;
   else if (color == COLOR_RED) then
      SetText_RED;
   else
      SetText_GREEN;

   //craft_debug("Format("+text+", x = " + x + ", w = " + width);
   //if (width >= 0 or width >= get_text_width(text)) then
   Format(text, x, display_line, width, 20, justify);
   //else debug_msg("[craft] ! ERROR ! Attempt to display text beyond display area: " + text + ", x = " + x + ", w = " + width);
   if (newLine) then begin
      display_line += 10;
      display_cur_str := "";
   end else
      display_cur_str += text;
end

procedure draw_tools_required begin
   variable list, hasThis, hasAny, i, pid, str, hasAll := true;
   craft_debug("draw_tools_required()");
   call display_print(mstr_craft(300), true, COLOR_GREEN, justifycenter);
   if (len_array(cur_recipe.tools) > 0) then foreach (list in (cur_recipe.tools)) begin
      hasAny := false;
      i := 0;
      foreach (pid in list) begin
         hasThis := party_is_carrying_obj_pid(pid);
         hasAny := hasAny or hasThis;
         str := proto_data(pid, it_name);
         if (i) then
            str := mstr_craft(150) + str;
         call display_print(str, false, COLOR_GREEN if hasThis else COLOR_RED);
         call display_newline;
         i += 1;
      end
      if (not hasAny) then hasAll := false;
   end else begin
      call display_print(mstr_craft(303));
   end
   call display_newline;
   return hasAll;
end

procedure draw_skills_required begin
   variable list, str, partyStr, dudeSkill, hasThis, hasAll := true;

   craft_debug("draw_skills_required()");
   call display_print(mstr_craft(301), true, COLOR_GREEN, justifycenter);
   if (len_array(cur_recipe.skills) > 0) then foreach (list in (cur_recipe.skills)) begin
      dudeSkill := check_skill_sum(dude_obj, list);
      if (dudeSkill > 0) then begin
         hasThis := true;
      end else begin
         // check party members skills
         partyStr := get_party_member_with_skill(list) if craft_cfg.use_party else 0;
         hasThis := partyStr != 0;
      end
      hasAll := hasAll and hasThis;
      str := skill_names(list) + ": " + list[len_array(list) - 1];
      if (not hasThis) then
         str += " (" + (-dudeSkill) + ")";
      call display_print(str, false, COLOR_GREEN if hasThis else COLOR_RED);
      if (partyStr != 0) then
         call display_print(" (" + partyStr + ")", false, COLOR_DARK_GREEN);
      call display_newline;
   end else begin
      // If no skills - display "No".
      call display_print(mstr_craft(303));
   end
   call display_newline;
   return hasAll;
end

procedure draw_components_required begin
   variable list, hasAny, i, hasQty, numBatches, maxGroupBatch, itemData, pid, qty, packSize, str, w,
      hasAll := true;

   craft_debug("draw_components_required()");
   call display_print(mstr_craft(302), true, COLOR_GREEN, justifycenter);
   max_batch := 32767;
   if (len_array(cur_recipe.input) > 0) then foreach (list in (cur_recipe.input)) begin
      hasAny := false;
      i := 0;
      maxGroupBatch := 0; // maximum number of batches within single OR group
      foreach itemData in list begin
         pid := cfg_item_pid(itemData);
         packSize := get_proto_data(pid, PROTO_AM_PACK_SIZE)
            if (proto_data(pid, it_type) == item_type_ammo)
            else 1;
         qty := cfg_item_qty(itemData) * packSize;
         hasQty := party_is_carrying_obj_pid(pid, true);
         numBatches := hasQty / qty;
         if (numBatches > 0) then begin
            hasAny := true;
         end
         if (numBatches > maxGroupBatch) then maxGroupBatch := numBatches;
         str := proto_data(pid, it_name) + ": " + qty + " (" + hasQty + ")";
         if (i) then
            str := mstr_craft(150) + str;
         call display_print(str, false, COLOR_GREEN if numBatches > 0 else COLOR_RED);
         call display_newline;
         i += 1;
      end
      // Restrict the max batch by a group with smallest number of potential batches
      if (maxGroupBatch < max_batch) then max_batch := maxGroupBatch;
      if (not hasAny) then hasAll := false;
   end else begin
      // If no components found - display "No".
      max_batch := 1; // so we can actually produce the thing.. out of thin air?
      call display_print(mstr_craft(303), true);
   end
   call display_newline;
   return hasAll;
end

procedure draw_item_properties begin
   variable
      pid,
      qty := 0,
      hasTools := 1,
      hasSkills := 1,
      hasComponents := 1,
      hours,
      mins,
      hasAny,
      i,
      str := 0,
      list,
      componentData;

   display_line := 100;
   display_cur_str := "";
   pid := cur_recipe.pid;
   craft_debug("draw_item_properties " + pid);
   SelectWin("win_dscr");
   // Item name
   str := proto_data(pid, it_name);
   qty := cur_recipe_batch_size;

   call display_print(str, true, COLOR_GREEN, justifycenter);
   if (qty > 1) then
      call display_print(" x" + qty, true, COLOR_GREEN, justifycenter);
   call display_newline(2);

   hasTools := draw_tools_required;
   hasSkills := draw_skills_required;
   hasComponents := draw_components_required;
   
   // Check if all requirements for crafting are met.
   if not(hasTools and hasSkills and hasComponents) then max_batch := 0;

   // Check if disassembly is possible.
   max_undo := (party_is_carrying_obj_pid(cur_recipe.pid) / cur_recipe.qty)
      if (cur_recipe.undo and hasTools and hasSkills)
      else 0;

   // Display time required for crafting.
   call display_print(mstr_craft(304), true, COLOR_GREEN, justifycenter);

   hours := cur_recipe.time / 60;
   mins  := cur_recipe.time % 60;
   call display_print(string_format(mstr_craft(307), hours, mins) + ((" (" + qty + ")") if (max_batch > 1) else ""));
   if (max_batch > 1) then begin
      mins := cur_recipe.time * max_batch;
      hours := mins / 60;
      mins := mins % 60;
      call display_print(string_format(mstr_craft(307), hours, mins) + " (" + (qty * max_batch) + ")");
   end
   ShowWin;
end

procedure draw_item_pcx begin
   variable w, h, data, fid := proto_data(cur_recipe.pid, it_inv_fid);
   data := art_frame_data(fid, 0, 0); // this requires sfall update
   // TODO: get rid of pic_w/pic_h after sfall update
   w := data[0] if data else cur_recipe.pic_w;
   h := data[1] if data else cur_recipe.pic_h;
   craft_debug("draw_item_pcx "+cur_recipe.pid+", size: "+w+"x"+h);
   call redraw_win_dscr;
   SelectWin("win_dscr");
   draw_image_scaled(fid, 0, 150 - w/2, 55 - h/2, w, h);
   //draw_image(proto_data(cur_recipe.pid, it_inv_fid), 0, 150 - w/2, 55 - h/2, false);
   ShowWin;
end

#endif
