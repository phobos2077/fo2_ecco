#ifndef H_TALKING_HEADS_COMPAT
#define H_TALKING_HEADS_COMPAT

#define talking_head_art_fid(headId)   (0x8000000 bwor (headId bwand 0xFFFF))
#define talking_head_exists(headId)    art_exists(talking_head_art_fid(headId))
#define start_gdialog_check_talking_head(reactLvl, headId, bgId) \
   if (talking_head_exists(headId)) then \
      start_gdialog(NAME, self_obj, reactLvl, headId, bgId); \
   else \
      start_gdialog(NAME, self_obj, reactLvl, -1, -1)

#define start_dialog_at_node_check_talking_head(x, headId, bgId)  \
      if (in_dialog == false) then begin           \
         in_dialog := true;                        \
         start_gdialog_check_talking_head(4, headId, bgId); \
         gSay_Start;                               \
            call x;                                \
         gSay_End;                                 \
         end_dialogue;                             \
         in_dialog := false;                       \
      end else call x

#define check_forced_dialog_check_talking_head(headId, bgId)  \
      if (forced_node != 0) then begin          \
         ndebug("calling forced dialog: "+forced_node); \
         start_dialog_at_node_check_talking_head(forced_node, headId, bgId);     \
         forced_node := 0;                      \
      end

#endif // H_TALKING_HEADS_COMPAT
