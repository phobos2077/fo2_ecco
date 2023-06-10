#include "../sfall/sfall.h"
#include "../sfall/lib.arrays.h"
#include "../sfall/lib.inven.h"
#include "../sfall/define_lite.h"
#include "../sfall/define_extra.h"

#include "learn_craft.h"

/*
    TODO:
    - load non-text settings from INI
    - use custom game msg file
    - get rid of "say" and "reply" stuff, use normal windows with text and buttons
*/

#define CRAFT_MOD_VERSION        3

#define SECTION_START           1000
#define SECTION_STEP            100

#define ITEM_ITEM               "[ITEM]"
#define ITEM_TOOLS              "[TOOLS]"
#define ITEM_SKILLS             "[SKILLS]"
#define ITEM_COMPONENTS         "[COMPONENTS]"

#define ITEM_PID                1
#define ITEM_PCX                2
#define ITEM_SIZE               3
#define ITEM_GVAR               4
#define ITEM_TIME               5
#define ITEM_UNDO               6
#define ITEM_CAT                7
#define PARSER_START            8

#define ITEMS_PER_SCREEN        9

// should typically be ITEMS_PER_SCREEN + 2
#define MAX_CATEGORIES          (ITEMS_PER_SCREEN + 2)

#define craft_debug(text)       if (false) then debug_msg("[craft] "+text)

variable begin
    // TODO: craft_msg;
    mode;

    use_categories := false;
    check_gvars := false;

    cur_section_start;
    cur_category;
//    last_saved_pos;
    cur_pos;

    cur_pid;
    cur_pid_qty;
    cur_pcx;
    cur_size;
    cur_time;
    cur_undo;

    items_avail;
    max_batch;
    max_undo;

    can_batch;
    can_undo;

//    pcx_show;
    //startList;

    win_x := 0;
    win_y := 0;

    mouse_over;
    button_pressed;
end

// TODO:
//#define bstr(x)                 message_str(craft_msg, x)
#define bstr(x)                 message_str(SCRIPT_TEST0, x)
#define field(x)                bstr(cur_section_start + x)
#define skill_name(x)           bstr(1 + x)
#define skill_def(x)            bstr(19 + x)
#define npc_pid(x)              bstr(450 + x)

#define cfg_party_skills        atoi(bstr(491))
#define cfg_use_categories      atoi(bstr(492))
#define cfg_check_gvars         atoi(bstr(493))
#define cfg_crafting_hotkey     bstr(494)

#define has_prev_page           (cur_pos > 0)
#define has_next_page           (cur_pos + ITEMS_PER_SCREEN < items_avail - 1)

procedure display_next_option(variable i, variable text);

procedure redraw_win_idle;

procedure count_items_avail;
procedure draw_item_properties;
procedure draw_item_pcx;
procedure parse_skill_name(variable s_name);

procedure display_category_list;
procedure display_items_list;
procedure display_items_avail;
procedure null_proc;
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

procedure get_party_member_with_skill(variable skill, variable level);
pure procedure has_skill_sum(variable crit, variable skills);
pure procedure skill_names(variable skills);

/******************************************************************************/

#define _if_global_update(sgvar, gvar)        if (get_sfall_global_int(sgvar) == 0) then set_sfall_global(sgvar, global_var(gvar));

procedure handle_mod_update begin
    if (get_sfall_global_int(SGVAR_CRAFT_VERSION) < 2 and (global_var(644) or global_var(645) or global_var(647) or global_var(648) or global_var(649) or global_var(650))) then begin
        // convert global vars from previous version
      display_msg("Converting schematic gvars to new format...");
        _if_global_update(SGVAR_CRAFT_EXPLOSIVES, 644)
        _if_global_update(SGVAR_CRAFT_LEATHER,     645)
        _if_global_update(SGVAR_CRAFT_FIRST_AID,     647)
        _if_global_update(SGVAR_CRAFT_ELECTRONICS,648)
        _if_global_update(SGVAR_CRAFT_AMMO,         649)
        _if_global_update(SGVAR_CRAFT_BLADES,         650)
    end
    set_sfall_global(SGVAR_CRAFT_VERSION, CRAFT_MOD_VERSION);
end

#undef _if_global_update

procedure cur_section_is_available begin
    variable gvar, gvarVal;
    if (cur_category != 0 and atoi(field(ITEM_CAT)) != cur_category) then return false;

    if (check_gvars) then begin
        gvar := field(ITEM_GVAR);
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
    Display("PCX/w_close.pcx");
    AddButton("but2", 133, 6, 15, 16);
    AddButtonGFX("but2", "PCX/lilreddn.pcx", "PCX/lilredup.pcx", "PCX/lilredup.pcx");
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
    call handle_mod_update;
    stop_game;

    cur_section_start := SECTION_START;
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

    SayReplyWindow (win_x + 300, win_y +   1, 342, 144, "PCX/w_rep.pcx");
    SayOptionWindow(win_x + 300, win_y + 146, 342, 201, "PCX/w_opt.pcx");
    SayBorder(30, 30);

    create_win_flag("win_dscr", win_x + 1, win_y + 1, 300, 378, WIN_FLAG_EXCLUSIVE);
    SelectWin("win_dscr");
    Display("PCX/w_dscr.pcx");
    ShowWin;

    // We show these here to remove interface flickery
    CreateWin("win_rep", win_x + 300, win_y +   1, 342, 144);
    SelectWin("win_rep");
    Display("PCX/w_rep.pcx");
    ShowWin;
    CreateWin("win_opt", win_x + 300, win_y + 146, 342, 201);
    SelectWin("win_opt");
    Display("PCX/w_opt.pcx");
    ShowWin;

    call show_cancel_button("win_btn");

    check_gvars := (cfg_check_gvars > 0);

    if (cfg_use_categories == 1) then begin
       use_categories := true;
    end else if (cfg_use_categories == 2) then begin
       call count_items_avail;
       if (items_avail > ITEMS_PER_SCREEN) then
          use_categories := true;
    end

    if (use_categories) then begin
       mode := 5;
    end else begin
       mode := 1;
       if (items_avail == 0) then
          call count_items_avail;
    end

    call loop_mode;

    DeleteWin("win_dscr");
    DeleteWin("win_rep");
    DeleteWin("win_opt");
    DeleteWin("win_btn");

    resume_game;
end

procedure count_items_avail begin
    variable backup;
    backup := cur_section_start;
    cur_section_start := SECTION_START;
    items_avail := 0;
    while (bstr(cur_section_start) != "Error" and bstr(cur_section_start) == ITEM_ITEM) do begin
        if (cur_section_is_available) then items_avail += 1;
        cur_section_start += SECTION_STEP;
    end
    cur_section_start := backup;
end

procedure loop_mode begin
    while (mode != -1) do begin
        craft_debug("craft: loop_mode(): "+mode);
        if (mode == 1)      then call display_items_list;
        else if (mode == 2) then call display_item_options;
        else if (mode == 3) then call display_batch_ok;
        else if (mode == 4) then call display_undo_ok;
        else if (mode == 5) then call display_category_list;
    end
end

procedure exit_mode begin
    mode := -1;
end

procedure items_list_mode begin
    mode := 1;
end

procedure item_options_mode begin
    if (mode == 5) then begin
       cur_category := atoi(field(ITEM_CAT));
       call count_items_avail; // count available items within selected category
       mode := 1;
    end else
       mode := 2;
end

procedure batch_ok_mode begin
    mode := 3;
end

procedure undo_ok_mode begin
    mode := 4;
end

procedure item_categories_mode begin
    cur_category := 0;
    mode := 5;
end

procedure display_category_list begin
    variable
        lines_counter := 0,
        skip_counter := 0,
        catList,
        cat;
    craft_debug("display_category_list(): SayStart");
    SayStart;
        MouseShape("pcx/st1.pcx", 0, 0);
        SayReply("r_display_list", bstr(210));

        call redraw_win_idle;
        //cur_section_start := last_saved_pos;
        cur_category := 0;
        cur_section_start := SECTION_START;
        catList := temp_array(MAX_CATEGORIES + 1, 4);
        while (lines_counter < MAX_CATEGORIES and bstr(cur_section_start) != "Error" and bstr(cur_section_start) == ITEM_ITEM) do begin
           cur_pid := atoi(field(ITEM_PID));
           cat := atoi(field(ITEM_CAT));
           if (cat > 0 and cat <= MAX_CATEGORIES and cur_section_is_available) then if (catList[cat] == 0) then begin
               call display_next_option(lines_counter, bstr(40+cat));
               catList[cat] := 1;
               lines_counter += 1;
           end
           cur_section_start += SECTION_STEP;
        end
        // SayOption(bstr(101), exit_mode);
    SayEnd;
    craft_debug("display_category_list(): SayEnd");
end

procedure display_items_list begin
    craft_debug("display_items_list(): sayStart");
    SayStart;
        MouseShape("pcx/st1.pcx", 0, 0);
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
    variable pidData;
    pidData := string_split_ints(field(ITEM_PID), ":");
    cur_pid := pidData[0];
    cur_pid_qty := pidData[1] if len_array(pidData) > 1 else 1;
    if (cur_pid_qty <= 0) then cur_pid_qty := 1;
    max_undo := obj_is_carrying_obj_pid(dude_obj, cur_pid);
    
    craft_debug("display_item_options: SayStart()");
    SayStart;
        MouseShape("pcx/st1.pcx", 0, 0);
        craft_debug("display_item_options SayReply: " + proto_data(cur_pid, it_description));
        SayReply("r_item_options", proto_data(cur_pid, it_description));
        call draw_item_pcx;
        call draw_item_properties;
        if (can_batch) then SayOption("1. " + bstr(103), batch_one_item);
        if (can_batch and max_batch > 1) then SayOption("2. " + bstr(108) + bstr(110) + (max_batch * cur_pid_qty) + bstr(111), batch_all_items);
        if (can_undo) then SayOption("3. " + bstr(104), undo_one_item);
        if (can_undo and max_undo > 1) then SayOption("4. " + bstr(109) + bstr(110) + max_undo + bstr(111), undo_all_items);
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
        MouseShape("pcx/st1.pcx", 0, 0);
        SayReply("r_batch_item", bstr(201));
        SayOption("0. "+bstr(100), item_options_mode);
        SayOption("Esc. " + bstr(101), exit_mode); // we have to display at least 2 options to prevent error...
    SayEnd;
    craft_debug("display_batch_ok: SayEnd()");
end

procedure display_undo_ok begin
    craft_debug("display_undo_ok: SayStart()");
    SayStart;
        MouseShape("pcx/st1.pcx", 0, 0);
        SayReply("r_undo_batch", bstr(202));
        SayOption("0. " + bstr(100), item_options_mode);
        SayOption("Esc. " + bstr(101), exit_mode); // we have to display at least 2 options to prevent error...
    SayEnd;
    craft_debug("display_undo_ok: SayEnd()");
end

procedure null_proc begin
end

procedure list_next_proc begin
//    last_saved_pos += SECTION_STEP * ITEMS_PER_SCREEN;
    cur_pos += ITEMS_PER_SCREEN;
end

procedure list_back_proc begin
//    last_saved_pos -= SECTION_STEP * ITEMS_PER_SCREEN;
    cur_pos -= ITEMS_PER_SCREEN;
end

procedure redraw_win_dscr begin
    SelectWin("win_dscr");
    Display("PCX/w_dscr.pcx");
    ShowWin;
end

procedure redraw_win_idle begin
    SelectWin("win_dscr");
    Display("PCX/w_idle.pcx");
    ShowWin;
end

procedure display_items_avail begin
    variable
        lines_counter := 0,
        skip_counter := 0,
        cat;
    craft_debug("display_items_avail()");
    //call redraw_win_dscr;
    call redraw_win_idle;
    //cur_section_start := last_saved_pos;
    cur_section_start := SECTION_START;
    //else SayOption(".", null_proc);
    while (skip_counter < cur_pos) do begin
        if (cur_section_is_available) then skip_counter += 1;
        cur_section_start += SECTION_STEP;
    end
    //if (cur_section_start != SECTION_START) then SayOption(bstr(106), list_back_proc);
    while (lines_counter < ITEMS_PER_SCREEN and bstr(cur_section_start) != "Error" and bstr(cur_section_start) == ITEM_ITEM) do begin
        cur_pid := atoi(field(ITEM_PID));
        cat := atoi(field(ITEM_CAT));
        if (cur_section_is_available) then begin
            call display_next_option(lines_counter, proto_data(cur_pid, it_name));
            lines_counter += 1;
        end
        cur_section_start += SECTION_STEP;
    end
    //cur_section_start := last_saved_pos;
    if (has_prev_page) then SayOption("<. "+bstr(106), list_back_proc);
    if (has_next_page) then SayOption(">. "+bstr(105), list_next_proc);
    //if ((cur_section_start - SECTION_START) / SECTION_STEP + ITEMS_PER_SCREEN < items_avail) then SayOption(bstr(105), list_next_proc);
    if (use_categories) then
        SayOption("0. "+bstr(112), item_categories_mode);
    if (items_avail == 0) then
        SayOption(bstr(107), exit_mode);
end

#define _optProc(NNN) \
variable start##NNN; \
procedure item_options_##NNN begin \
    cur_section_start := start##NNN; \
    call item_options_mode; \
end

_optProc(0)
_optProc(1)
_optProc(2)
_optProc(3)
_optProc(4)
_optProc(5)
_optProc(6)
_optProc(7)
_optProc(8)
_optProc(9)
_optProc(10)
_optProc(11)

#undef _optProc

procedure display_next_option(variable i, variable text) begin
    if (i < 9) then
        text := ""+(i+1)+". "+text;

    #define _ifOpt(NNN) \
    if (i == NNN) then begin \
        start##NNN := cur_section_start; \
        SayOption(text, item_options_##NNN); \
    end

    _ifOpt(0)
    _ifOpt(1)
    _ifOpt(2)
    _ifOpt(3)
    _ifOpt(4)
    _ifOpt(5)
    _ifOpt(6)
    _ifOpt(7)
    _ifOpt(8)
    _ifOpt(9)
    _ifOpt(10)
    _ifOpt(11)

    #undef _ifOpt
end

procedure batch_item(variable num) begin
    variable begin
        line := PARSER_START;
        c_pid := 0;
        c_quantity := 0;
        hours;
        mins;
        word;
        orList;
        componentData;
        i;
    end
//    cur_time := atoi(field(ITEM_TIME));
    if (random(0,1)) then play_sfx("carrepair");
    else play_sfx("fixstill");
      gfade_out(400);
    game_time_advance(cur_time * num);
    gfade_in(400);
    while (field(line) != ITEM_COMPONENTS and line < SECTION_STEP) do line += 1;
    line += 1;
    while (line < SECTION_STEP and field(line) != "Error" and bstr(cur_section_start) == ITEM_ITEM) do begin
        orList := string_split_safe(field(line), "|");
        i := 0;
        // remove first item from "OR" orList that player has
        while (i < len_array(orList)) do begin
            componentData := string_split_ints(orList[i], ":");
            c_pid := componentData[0];
            c_quantity := componentData[1] if len_array(componentData) > 1 else 1;
            if (obj_is_carrying_obj_pid(dude_obj, c_pid) >= c_quantity) then begin
                call remove_items_pid(dude_obj, c_pid, c_quantity * num);
                i := len_array(orList);
            end
            i++;
        end
        line += 1;
    end
    call add_items_pid(dude_obj, cur_pid, num * cur_pid_qty);
    hours := ((cur_time * num) / ONE_GAME_MINUTE) / 60;
    mins  := ((cur_time * num) / ONE_GAME_MINUTE) % 60;
    display_msg(bstr(400) + proto_data(cur_pid, it_name) + bstr(402) + (num * cur_pid_qty) + bstr(403) + hours + bstr(404) + mins + bstr(405));
    call batch_ok_mode;
end

procedure undo_batch(variable num) begin
    variable begin
        line := PARSER_START;
        c_pid := 0;
        c_quantity := 0;
        hours;
        mins;
        orList;
        word;
        componentData;
    end
//    cur_time := atoi(field(ITEM_TIME));
    game_time_advance(cur_time * num);
    while (field(line) != ITEM_COMPONENTS and line < SECTION_STEP) do line += 1;
    line += 1;
    while (line < SECTION_STEP and field(line) != "Error" and bstr(cur_section_start) == ITEM_ITEM) do begin
        orList := string_split_safe(field(line), "|");
        // give first item from optional orList
        if (len_array(orList) > 0) then begin
            componentData := string_split_ints(orList[0], ":");
            c_pid := componentData[0];
            c_quantity := componentData[1];
            call add_items_pid(dude_obj, c_pid, c_quantity * num);
        end
        line += 1;
    end
    call add_items_pid(dude_obj, cur_pid, num * cur_pid_qty);
    hours := ((cur_time * num) / ONE_GAME_MINUTE) / 60;
    mins  := ((cur_time * num) / ONE_GAME_MINUTE) % 60;
    display_msg(bstr(401) + proto_data(cur_pid, it_name) + bstr(402) + (num * cur_pid_qty) + bstr(403) + hours + bstr(404) + mins + bstr(405));
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

procedure draw_item_properties begin
    variable begin
        line := PARSER_START;
        saved_line := PARSER_START;
        display_line := 100;
        has_tools := 1;
        has_skills := 1;
        has_components := 1;
        tool := 0;

        skill_lv := 0;
        c_pid := 0;
        c_quantity := 0;
        max2;
        hours;
        mins;
        tool_word;
        has_any;
        i;

        str := 0;
        list;
        componentData;
    end
    craft_debug("draw_item_properties "+cur_pid);
    SelectWin("win_dscr");
    // Item name
    SetTextColor(0.0, 1.0, 0.0);
    str := proto_data(cur_pid, it_name);
    c_quantity := cur_pid_qty;
    if (proto_data(cur_pid, it_type) == item_type_ammo) then
        c_quantity := c_quantity * get_proto_data(cur_pid, PROTO_AM_PACK_SIZE);
    if (c_quantity > 1) then str := str + " x" + c_quantity;
    Format(str, 25, display_line, 250, 10, justifycenter);
    display_line += 30;
    // Skip to TOOLS section
    while (field(line) != ITEM_TOOLS and line < SECTION_STEP) do line += 1;
    line += 1;
    Format(bstr(300), 25, display_line, 250, 10, justifycenter);
    display_line += 10;
    // Display list of tools
    saved_line := line;
    while (field(line) != ITEM_SKILLS and line < SECTION_STEP and field(line) != "Error" and bstr(cur_section_start) == ITEM_ITEM) do begin
        has_any := 0;
        list := string_split_safe(field(line), "|");
        i := 0;
        foreach tool_word in list begin
          tool := atoi(tool_word);
          if (obj_is_carrying_obj_pid(dude_obj, tool)) then begin
              SetTextColor(0.0, 1.0, 0.0);
              has_any := 1;
          end else begin
              SetTextColor(1.0, 0.0, 0.0);
          end
          str := proto_data(tool, it_name);
          if (i) then
              str := bstr(150) + str;
          Format(str, 25, display_line, 250, 10, justifyleft);
          display_line += 10;
          i += 1;
        end
        if (has_any == 0) then has_tools := 0;
        line += 1;
    end
    // If no tools needed - display "No".
    if (saved_line == line) then begin
        SetTextColor(0.0, 1.0, 0.0);
        Format(bstr(303), 25, display_line, 250, 10, justifyleft);
        display_line += 10;
    end
    display_line += 10;
    // Skip to Skills section
    line += 1;
    SetTextColor(0.0, 1.0, 0.0);
    Format(bstr(301), 25, display_line, 250, 10, justifycenter);
    display_line += 10;
    // Display list of skills
    saved_line := line;
    while (field(line) != ITEM_COMPONENTS and line < SECTION_STEP and field(line) != "Error" and bstr(cur_section_start) == ITEM_ITEM) do begin
        list := string_split_safe(field(line), ":");
        if (len_array(list) != 2) then debug_msg("! ERROR ! [craft] Invalid skill definition: " + field(line));
        skill_lv := atoi(list[1]);
        // list of skills
        list := parse_skill_name(list[0]);

        if (has_skill_sum(dude_obj, list) >= skill_lv) then begin
            SetTextColor(0.0, 1.0, 0.0);
            str := "";
        end
        else begin
            // check party members skills
            str := get_party_member_with_skill(list, skill_lv) if cfg_party_skills else 0;
            if (str) then begin
                SetTextColor(0.0, 1.0, 0.0);
                str := " (" + str + ")";
            end else begin
                SetTextColor(1.0, 0.0, 0.0);
                has_skills := 0;
                str := "";
            end
        end
        Format(skill_names(list) + ": " + skill_lv + str, 25, display_line, 250, 10, justifyleft);
        display_line += 10;
        line += 1;
    end
    // If no skills - display "No".
    if (saved_line == line) then begin
        SetTextColor(0.0, 1.0, 0.0);
        Format(bstr(303), 25, display_line, 250, 10, justifyleft);
        display_line += 10;
    end
    display_line += 10;
    // Skip to Components section
    line += 1;
    SetTextColor(0.0, 1.0, 0.0);
    Format(bstr(302), 25, display_line, 250, 10, justifycenter);
    display_line += 10;
    // Display list of components.
    saved_line := line;
    max_batch := 32767;
    while (line < SECTION_STEP and field(line) != "Error" and bstr(cur_section_start) == ITEM_ITEM) do begin
        has_any := 0;
        list := string_split_safe(field(line), "|");
        i := 0;
        max2 := 0;
        foreach tool_word in list begin
            componentData := string_split_ints(tool_word, ":");
            c_pid := componentData[0];
            c_quantity := componentData[1] if len_array(componentData) > 1 else 1;
            if (obj_is_carrying_obj_pid(dude_obj, c_pid) >= c_quantity) then begin
                SetTextColor(0.0, 1.0, 0.0);
                has_any := 1;
            end
            else begin
                SetTextColor(1.0, 0.0, 0.0);
            end
            mins := obj_is_carrying_obj_pid(dude_obj, c_pid) / c_quantity;
            if (mins > max2) then max2 := mins;
            if (proto_data(c_pid, it_type) == item_type_ammo) then c_quantity := c_quantity * get_proto_data(c_pid, PROTO_AM_PACK_SIZE);
            str := proto_data(c_pid, it_name) + ": " + c_quantity;
            if (i) then
                str := bstr(150) + str;
            Format(str, 25, display_line, 250, 10, justifyleft);
            display_line += 10;
            i += 1;
        end
        if (max2 < max_batch) then max_batch := max2;
        if (has_any == 0) then has_components := 0;
        line += 1;
    end
    // If no components found - display "No".
    if (saved_line == line) then begin
        SetTextColor(0.0, 1.0, 0.0);
        Format(bstr(303), 25, display_line, 250, 10, justifyleft);
        display_line += 10;
    end
    display_line += 10;
    // Check if all requirements for crafting are met.
    if (has_tools and has_skills and has_components) then can_batch := 1;
    else can_batch := 0;
    // Check if disassembly is possible.
    cur_undo := field(ITEM_UNDO);
    if (cur_undo == "YES" and has_tools and has_skills and obj_is_carrying_obj_pid(dude_obj, cur_pid)) then can_undo := 1;
    else can_undo := 0;
    // Display time required for crafting.
    SetTextColor(0.0, 1.0, 0.0);
    Format(bstr(304), 25, display_line, 250, 10, justifycenter);
    display_line += 10;
    cur_time := atoi(field(ITEM_TIME));
    hours := (cur_time / ONE_GAME_MINUTE) / 60;
    mins  := (cur_time / ONE_GAME_MINUTE) % 60;
    Format(bstr(305) + hours, 25, display_line, 250, 10, justifyleft);
    display_line += 10;
    Format(bstr(306) + mins, 25, display_line, 250, 10, justifyleft);

    ShowWin;
end

procedure draw_item_pcx begin
    variable begin
        w;
        h;
    end
    // TODO: remove ITEM_PCX
    cur_pcx := field(ITEM_PCX);
    // TODO: get size from FRM directly
    cur_size := atoi(field(ITEM_SIZE));
    w := cur_size / 1000;
    h := cur_size % 1000;
    craft_debug("draw_item_pcx "+cur_pid+", size: "+w+"x"+h);
    call redraw_win_dscr;
    SelectWin("win_dscr");
    //DisplayGFX(cur_pcx, 150 - w/2, 55 - h/2, w, h);
    draw_image_scaled(proto_data(cur_pid, it_inv_fid), 0, 150 - w/2, 55 - h/2, w, h);
    ShowWin;
end

procedure parse_skill_name(variable s_name) begin
   variable i, j, skill, lst, lst2, s;
   lst := string_split_safe(s_name, "+");
   lst2 := temp_array(len_array(lst), 4);
   j := 0;
   foreach s in lst begin
      skill := -1;
      i := 0;
      while (i < 18 and skill < 0) do begin
         if (s == skill_def(i)) then
            skill := i;
         i += 1;
      end
      lst2[j] := skill;
      j += 1;
   end

   return lst2;
end

procedure get_party_member_with_skill(variable skills, variable level) begin
    variable ret := 0;
    variable obj;
    //craft_debug("search skill "+debug_array_str(skills)+" at least " + level);

    foreach (obj in party_member_list_critters) if (obj) then begin
        if (has_skill_sum(obj, skills) >= level) then begin
            ret := obj_name(obj);// proto_data(obj_pid, cr_name)
        end
    end
    return ret;
end

pure procedure has_skill_sum(variable crit, variable skills) begin
   variable total := 0, skill;
   foreach skill in skills begin
      total += has_skill(crit, skill);
   end
   return total;
end

pure procedure skill_names(variable skills) begin
   variable str := "", skill, i:=0;
   foreach skill in skills begin
      if (i > 0) then str += " + ";
      str += skill_name(skill);
      i++;
   end
   return str;
end

/*procedure description_p_proc begin
    script_overrides;
    display_msg(message_str(SCRIPT_TEST0, 90));
end*/


/*procedure use_skill_on_p_proc begin
    if (action_being_used == SKILL_REPAIR and not(combat_is_initialized)) then begin
        script_overrides;
        call batch_init;
    end
end*/
