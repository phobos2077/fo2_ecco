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
   - use custom game msg file
   - get rid of "say" and "reply" stuff, use normal windows with text and buttons
*/

#define craft_debug(text)       if (true) then debug_msg("[craft] "+text)

#include "craft_config.h"


#define ITEMS_PER_SCREEN        9

#define MODE_EXIT               0
#define MODE_ITEMS_LIST         1
#define MODE_ITEM_OPTIONS       2
#define MODE_BATCH_OK           3
#define MODE_UNDO_OK            4
#define MODE_CATEGORY_LIST      5

// should typically be ITEMS_PER_SCREEN + 2
#define MAX_CATEGORIES          (ITEMS_PER_SCREEN + 2)

#define pcx_path(name)          "pcx\\" #name ".pcx"

variable begin
   // TODO: craft_msg;
   mode;
   use_categories := false;

   cur_recipe;
   cur_category;
//    last_saved_pos;
   cur_pos;
   items_avail;
   max_batch;
   max_undo;

//    pcx_show;

   item_values;

   win_x := 0;
   win_y := 0;

   mouse_over;
   button_pressed;

   display_line;
end

// TODO:
//#define bstr(x)                 message_str(craft_msg, x)
#define bstr(x)                 message_str(SCRIPT_TEST0, x)
#define skill_name(x)           mstr_skill(100 + x)

#define has_prev_page           (cur_pos > 0)
#define has_next_page           (cur_pos + ITEMS_PER_SCREEN < items_avail - 1)

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

procedure get_party_member_with_skill(variable skills);
pure procedure check_skill_sum(variable crit, variable skills);
pure procedure skill_names(variable skills);

/******************************************************************************/



procedure recipe_is_available(variable recipe) begin
   variable gvar, gvarVal;
   if (cur_category != 0 and recipe.category != cur_category) then return false;

   if (craft_cfg.use_gvars) then begin
      gvar := recipe.gvar;
      if (gvar == "NEVER") then
         return false;
      else if (gvar != "") then begin
         gvarVal := get_sfall_global_int(gvar) if atoi(gvar) == 0 else global_var(atoi(gvar));
         if (gvarVal == 0) then
            return false;
      end
   end
   return true;
end

procedure do_cancel_on begin
   mouse_over := true;
end

procedure do_cancel_off begin
   if (button_pressed == true) then play_sfx("IB1LU1X1");
   mouse_over := false;
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
   tap_key(DIK_ESCAPE);
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
   Format(bstr(120), 154, 6, 200, 30, 0);
   SetFont(101);
   SetTextColor(0.0, 1.0, 0.0);
   ShowWin;
end

procedure batch_init begin
   craft_debug("batch_init()");
   stop_game;

   if not craft_cfg then craft_cfg := load_crafting_config;

   //cur_section_start := SECTION_START;
   //last_saved_pos := cur_section_start;
   cur_pos := 0;
   items_avail := 0;
   cur_category := 0;

   win_x := (get_screen_width - 640) / 2;
   win_y := (get_screen_height - 380) / 2;
   if (win_y > 100) then win_y := 100; // for some reason, SayOptionWindow can't be lowered after certain Y coordinate

   SetFont(5);
   SaySetSpacing(3);
   SetTextColor(0.0, 1.0, 0.0);
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

   if (craft_cfg.categories == 1) then begin
      use_categories := true;
   end else if (craft_cfg.categories == 2) then begin
      call count_items_avail;
      if (items_avail > ITEMS_PER_SCREEN) then
         use_categories := true;
   end

   if (use_categories) then begin
      mode := MODE_CATEGORY_LIST;
   end else begin
      mode := MODE_ITEMS_LIST;
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
   while (mode != MODE_EXIT) do begin
      craft_debug("loop_mode(): " + mode);
      if (mode == MODE_ITEMS_LIST)         then call display_items_list;
      else if (mode == MODE_ITEM_OPTIONS)  then call display_item_options;
      else if (mode == MODE_BATCH_OK)      then call display_batch_ok;
      else if (mode == MODE_UNDO_OK)       then call display_undo_ok;
      else if (mode == MODE_CATEGORY_LIST) then call display_category_list;
   end
end

procedure exit_mode begin
   mode := MODE_EXIT;
end

procedure items_list_mode begin
   mode := MODE_ITEMS_LIST;
end

procedure item_options_mode begin
   mode := MODE_ITEM_OPTIONS;
end

procedure batch_ok_mode begin
   mode := MODE_BATCH_OK;
end

procedure undo_ok_mode begin
   mode := MODE_UNDO_OK;
end

procedure item_categories_mode begin
   cur_category := 0;
   mode := MODE_CATEGORY_LIST;
end

procedure display_category_list begin
   variable
      optionNum := 0,
      catList,
      key, recipe,
      cat;

   craft_debug("display_category_list(): SayStart");
   SayStart;
      MouseShape(pcx_path(st1), 0, 0);
      SayReply("r_display_list", bstr(210));

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
      for (cat := 1; cat < MAX_CATEGORIES + 1; cat++) begin
         if (catList[cat]) then begin
            call display_next_option(optionNum, bstr(40 + cat), cat);
            optionNum += 1;
         end
      end
      // SayOption(bstr(101), exit_mode);
   SayEnd;
   craft_debug("display_category_list(): SayEnd");
end

procedure display_items_list begin
   craft_debug("display_items_list(): sayStart");
   SayStart;
      MouseShape(pcx_path(st1), 0, 0);
      SayReply("r_display_list", bstr(200));
      //SayOptionColor(5, 9, 255);
      SayOptionFlags(justifyleft);
      call display_items_avail;
      //SayOptionFlags(justifycenter bwor textshadow bwor textdirect);
      craft_debug("display_items_list: sayoption "+bstr(101));
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
      if (max_batch > 0) then SayOption("1. " + bstr(103), batch_one_item);
      if (max_batch > 1) then SayOption("2. " + bstr(108) + bstr(110) + (max_batch * cur_recipe.qty) + bstr(111), batch_all_items);
      if (max_undo > 0) then SayOption("3. " + bstr(104), undo_one_item);
      if (max_undo > 1) then SayOption("4. " + bstr(109) + bstr(110) + max_undo + bstr(111), undo_all_items);
      SayOption("0: "+bstr(102), items_list_mode);
      if (use_categories) then
         SayOption(bstr(112), item_categories_mode);
      else
         SayOption("Esc. " + bstr(101), exit_mode); // we have to display at least 2 options to prevent error...
   SayEnd;
   craft_debug("display_item_options: SayEnd()");
end

procedure display_batch_ok begin
    craft_debug("display_batch_ok: SayStart()");
    SayStart;
        MouseShape(pcx_path(st1), 0, 0);
        SayReply("r_batch_item", bstr(201));
        SayOption("0. "+bstr(100), item_options_mode);
        SayOption("Esc. " + bstr(101), exit_mode); // we have to display at least 2 options to prevent error...
    SayEnd;
    craft_debug("display_batch_ok: SayEnd()");
end

procedure display_undo_ok begin
    craft_debug("display_undo_ok: SayStart()");
    SayStart;
        MouseShape(pcx_path(st1), 0, 0);
        SayReply("r_undo_batch", bstr(202));
        SayOption("0. " + bstr(100), item_options_mode);
        SayOption("Esc. " + bstr(101), exit_mode); // we have to display at least 2 options to prevent error...
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
      optionNum := 0,
      skip_counter := 0,
      recipe, key, name;
   craft_debug("display_items_avail()");
   //call redraw_win_dscr;
   call redraw_win_idle;

   /*while (skip_counter < cur_pos) do begin
      if (recipe_is_available) then skip_counter += 1;
   end*/
   //if (cur_section_start != SECTION_START) then SayOption(bstr(106), list_back_proc);
   foreach (key: name in (craft_cfg.recipeNames)) begin
      recipe := craft_cfg.recipes[key];
      if (recipe_is_available(recipe)) then begin
         if skip_counter < cur_pos then begin
            skip_counter += 1;
            continue;
         end
         call display_next_option(optionNum, name, recipe);
         optionNum += 1;
      end
   end
   if (has_prev_page) then SayOption("<. " + bstr(106), list_back_proc);
   if (has_next_page) then SayOption(">. " + bstr(105), list_next_proc);
   //if ((cur_section_start - SECTION_START) / SECTION_STEP + ITEMS_PER_SCREEN < items_avail) then SayOption(bstr(105), list_next_proc);
   if (use_categories) then
      SayOption("0. " + bstr(112), item_categories_mode);
   if (items_avail == 0) then
      SayOption(bstr(107), exit_mode);
end

procedure item_selected(variable idx) begin
   craft_debug(string_format("Selected item %d [%d], mode: %d", item_values[idx], idx, mode));
   if (mode == MODE_CATEGORY_LIST) then begin
      cur_category := item_values[idx];
      call count_items_avail; // count available items within selected category
      call items_list_mode;
   end else begin
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

#define _optProc(NNN) \
pure procedure item_options_##NNN begin \
   call item_selected(NNN); \
end

optProcs
#undef _optProc


procedure no_p_proc begin
   // A hack to ensure these procedures aren't removed during optimization...
   /*if game_time < 0 then begin
      #define _optProc(NNN) debug_msg(@item_options_##NNN);
      optProcs
      #undef _optProc
   end*/
end

procedure display_next_option(variable i, variable text, variable value) begin
   if (i < 9) then
      text := ""+(i+1)+". "+text;

   craft_debug(string_format("Displaying option %d: %s with value %d", i, text, value));
   item_values[i] := value;
   //SayOption(text, "item_options_"+i);

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
      // remove first item from "OR" orList that player has
      foreach (componentData in orList) begin
         pid := cfg_item_pid(componentData);
         qty := cfg_item_qty(componentData);
         if (obj_is_carrying_obj_pid(dude_obj, pid) >= qty) then begin
            call remove_items_pid(dude_obj, pid, qty * num);
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
   display_msg(bstr(400) + proto_data(cur_recipe.pid, it_name) + bstr(402) + (num * cur_recipe.qty) + bstr(403) + hours + bstr(404) + mins + bstr(405));
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
   call remove_items_pid(dude_obj, cur_recipe.pid, num * cur_recipe.qty);
   hours := cur_recipe.time * num / 60;
   mins  := cur_recipe.time * num % 60;
   display_msg(bstr(401) + proto_data(cur_recipe.pid, it_name) + bstr(402) + (num * cur_recipe.qty) + bstr(403) + hours + bstr(404) + mins + bstr(405));
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

procedure draw_tools_required begin
   variable list, hasAny, i, pid, str, hasAll := true;
   craft_debug("draw_tools_required()");
   Format(bstr(300), 25, display_line, 250, 10, justifycenter);
   display_line += 10;
   if (len_array(cur_recipe.tools) > 0) then foreach (list in (cur_recipe.tools)) begin
      hasAny := false;
      i := 0;
      foreach (pid in list) begin
         if (obj_is_carrying_obj_pid(dude_obj, pid)) then begin
            SetTextColor(0.0, 1.0, 0.0);
            hasAny := true;
         end else begin
            SetTextColor(1.0, 0.0, 0.0);
         end
         str := proto_data(pid, it_name);
         if (i) then
            str := bstr(150) + str;
         Format(str, 25, display_line, 250, 10, justifyleft);
         display_line += 10;
         i += 1;
      end
      if (not hasAny) then hasAll := false;
   end else begin
      // If no tools needed - display "No".
      SetTextColor(0.0, 1.0, 0.0);
      Format(bstr(303), 25, display_line, 250, 10, justifyleft);
      display_line += 10;
   end
   display_line += 10;
   return hasAll;
end

procedure draw_skills_required begin
   variable list, str, hasAll := true;

   craft_debug("draw_skills_required()");
   SetTextColor(0.0, 1.0, 0.0);
   Format(bstr(301), 25, display_line, 250, 10, justifycenter);
   display_line += 10;
   if (len_array(cur_recipe.skills) > 0) then foreach (list in (cur_recipe.skills)) begin
      if (check_skill_sum(dude_obj, list)) then begin
         SetTextColor(0.0, 1.0, 0.0);
         str := "";
      end else begin
         // check party members skills
         str := get_party_member_with_skill(list) if craft_cfg.use_party else 0;
         if (str) then begin
            SetTextColor(0.0, 1.0, 0.0);
            str := " (" + str + ")";
         end else begin
            SetTextColor(1.0, 0.0, 0.0);
            hasAll := false;
            str := "";
         end
      end
      Format(skill_names(list) + ": " + list[len_array(list) - 1] + str, 25, display_line, 250, 10, justifyleft);
      display_line += 10;
   end else begin
      // If no skills - display "No".
      SetTextColor(0.0, 1.0, 0.0);
      Format(bstr(303), 25, display_line, 250, 10, justifyleft);
      display_line += 10;
   end
   display_line += 10;
   return hasAll;
end

procedure draw_components_required begin
   variable list, hasAny, i, numBatches, maxGroupBatch, itemData, pid, qty, str, hasAll := true;

   craft_debug("draw_components_required()");
   SetTextColor(0.0, 1.0, 0.0);
   Format(bstr(302), 25, display_line, 250, 10, justifycenter);
   display_line += 10;
   max_batch := 32767;
   if (len_array(cur_recipe.input) > 0) then foreach (list in (cur_recipe.input)) begin
      hasAny := false;
      i := 0;
      maxGroupBatch := 0; // maximum number of batches within single OR group
      foreach itemData in list begin
         pid := cfg_item_pid(itemData);
         qty := cfg_item_qty(itemData);
         if (obj_is_carrying_obj_pid(dude_obj, pid) >= qty) then begin
            SetTextColor(0.0, 1.0, 0.0);
            hasAny := true;
         end else begin
            SetTextColor(1.0, 0.0, 0.0);
         end
         numBatches := obj_is_carrying_obj_pid(dude_obj, pid) / qty;
         if (numBatches > maxGroupBatch) then maxGroupBatch := numBatches;
         if (proto_data(pid, it_type) == item_type_ammo) then
            qty := qty * get_proto_data(pid, PROTO_AM_PACK_SIZE);
         str := proto_data(pid, it_name) + ": " + qty;
         if (i) then
            str := bstr(150) + str;
         Format(str, 25, display_line, 250, 10, justifyleft);
         display_line += 10;
         i += 1;
      end
      // Restrict the max batch by a group with smallest number of potential batches
      if (maxGroupBatch < max_batch) then max_batch := maxGroupBatch;
      if (not hasAny) then hasAll := false;
   end else begin
      // If no components found - display "No".
      max_batch := 1; // so we can actually produce the thing.. out of thin air?
      SetTextColor(0.0, 1.0, 0.0);
      Format(bstr(303), 25, display_line, 250, 10, justifyleft);
      display_line += 10;
   end
   display_line += 10;
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
   pid := cur_recipe.pid;
   craft_debug("draw_item_properties " + pid);
   SelectWin("win_dscr");
   // Item name
   SetTextColor(0.0, 1.0, 0.0);
   str := proto_data(pid, it_name);
   qty := cur_recipe.qty;
   if (proto_data(pid, it_type) == item_type_ammo) then
      qty := qty * get_proto_data(pid, PROTO_AM_PACK_SIZE);

   if (qty > 1) then str := str + " x" + qty;
   Format(str, 25, display_line, 250, 10, justifycenter);
   display_line += 30;

   hasTools := draw_tools_required;
   hasSkills := draw_skills_required;
   hasComponents := draw_components_required;
   
   // Check if all requirements for crafting are met.
   if not(hasTools and hasSkills and hasComponents) then max_batch := 0;

   // Check if disassembly is possible.
   max_undo := obj_is_carrying_obj_pid(dude_obj, cur_recipe.pid)
      if (cur_recipe.undo and hasTools and hasSkills)
      else 0;

   // Display time required for crafting.
   SetTextColor(0.0, 1.0, 0.0);
   Format(bstr(304), 25, display_line, 250, 10, justifycenter);
   display_line += 10;

   hours := cur_recipe.time / 60;
   mins  := cur_recipe.time % 60;
   Format(bstr(305) + hours, 25, display_line, 250, 10, justifyleft);
   display_line += 10;
   Format(bstr(306) + mins, 25, display_line, 250, 10, justifyleft);

   ShowWin;
end

procedure draw_item_pcx begin
   variable w, h;
   // TODO: get size from FRM directly
   w := cur_recipe.pic_w;
   h := cur_recipe.pic_h;
   craft_debug("draw_item_pcx "+cur_recipe.pid+", size: "+w+"x"+h);
   call redraw_win_dscr;
   SelectWin("win_dscr");
   //DisplayGFX(cur_pcx, 150 - w/2, 55 - h/2, w, h);
   draw_image_scaled(proto_data(cur_recipe.pid, it_inv_fid), 0, 150 - w/2, 55 - h/2, w, h);
   ShowWin;
end

#define critter_body_type(crit)        (proto_data(obj_pid(crit), cr_body_type))
#define critter_can_craft(crit)        (critter_body_type(crit) == CR_BODY_BIPED or critter_body_type(crit) == CR_BODY_ROBOTIC)

procedure get_party_member_with_skill(variable skills) begin
   variable ret := 0;
   variable obj;
   //craft_debug("search skill "+debug_array_str(skills)+" at least " + level);
   foreach (obj in party_member_list_critters) begin
      if (obj and critter_can_craft(obj) and check_skill_sum(obj, skills)) then begin
         ret := obj_name(obj);// proto_data(obj_pid, cr_name)
      end
   end
   return ret;
end

pure procedure check_skill_sum(variable crit, variable skills) begin
   variable
      total := 0,
      numSkills := len_array(skills) - 1,
      i;

   for (i := 0; i < numSkills; i++) begin
      total += has_skill(crit, skills[i]);
   end
   return total >= skills[numSkills];
end

pure procedure skill_names(variable skills) begin
   variable
      str := "", numSkills := len_array(skills) - 1,
      i;
   for (i := 0; i < numSkills; i++) begin
      if (i > 0) then str += " + ";
      str += skill_name(skills[i]);
   end
   return str;
end


#endif
