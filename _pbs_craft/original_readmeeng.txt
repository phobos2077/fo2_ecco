================================================================================

                                 TeamX presents

                              "Fallout2: MrFixit"

                                      v1.1

================================================================================

 "MrFixit"  is  more  an  add-on,  than  a  mod, that adds the ability to batch
 various  items  by  your own hands to the game. To be some more correct, it is
 not an add-on - it is a tool, which allow you to think out and add to the game
 new  items to batch and use this idea in Your own mod. Text below explains how
 to do this.

 Contents:

 0. Changes from v1.0
 1. Description
 2. Installation
 3. Compatibility with the other mods
 4. Data structure
 5. Integration
 6. Known problems
 7. About Us
 8. Acknowledgements


--------------------------------------------------------------------------------

 0. Changes from v1.0

--------------------------------------------------------------------------------

 The  interface  has  been  redrawn  in version 1.1 (thanks $py for that), some
 algorithms  have  been  changed  a little either. While selecting an object to
 batch, the left window now represents an idle logo picture (w_idle.pcx).

--------------------------------------------------------------------------------

 1. Description

--------------------------------------------------------------------------------

 "MrFixit" is a little toolkit that always with you... with The Chosen One.
 We`ve been thinking about design for long and finally decided to "hang"
 "MrFixit" on the Dude description. Just choose "binoculars" on The Chosen One,
 and you'll see the "MrFixit" interface. The interface consists of three
 windows: item information (left), current messages (up-right) and  options
 (down-right). Untill you choose any item, the description window will be empty.
 But as soon as you choose any item from the list in the options window, you'll
 see item's picture in the description window, a list of required
 tools/skills/components etc and time, needed to batch/dismantle one unit of
 the selected item. Meanwhile in the message window you can see the description
 of the selected item.
 There are three different sections in the description window: "Tools", "Skills"
 and "Components". "Skills" section displays the required skill and its minimal
 level. "Tools" section displays required tools. Tools are used to batch and
 dismantle items and they do not disappear after batch/dismantle (You don't want
 your tools to disappear each time you use it, right? ;). In the "Components"
 section You can see a components your item consists of. This section displays
 required components and its quantity to batch one item. Components disappear
 after batch and they are returned by dismantle. Once you can batch or dismantle
 one item or the maximum possible quantity of items if you have enough
 components. The ammount of time you'll spend on this operation will be equal to
 number of items being batched/dismantled multiplied by the ammount of time to
 batch/dismantle one such item. You can't dismantle every item: it is possible
 to take the Leather Armor to pieces, but it is impossible to "unsharpen" spear
 to a spear and a piece of flint :). There may be not all possible items in the
 batch list. Item will be displayed in the list only if PC "knows" how to batch
 it. To keep the compatibility we didn't include such items in this version. But
 You have to know, that this possibility exist and you can manage it through the
 game globals.

 ATTENTION! All items, included in this version, are just examples! If You want
 to add or change any item just do it by yourself!

--------------------------------------------------------------------------------

 2. Installation

--------------------------------------------------------------------------------

 Since "MrFixit" uses obj_dude.int, You'll have to remove it from patch000.dat.
 Or to remove patch000.dat itself.
 
 DO NOT FORGET TO MAKE COPIES OF PATCH000.DAT AND DATA FOLDER!!!

 If You're using dat2 and FAR, just open patch000.dat and delete the file
 patch000.dat\SCRIPTS/obj_dude.int. Then copy the content of the folder MRFIXIT
 from this archive to the DATA folder and run Fallout2. You don't need to start
 a new game to see the changes.

 If you're not using dat2, see follow the steps below:
 1. Download dat-unpacker
    http://www.teamx.ru/utils/dat_explorer.rar
 2. Unpack the content of the patch000.dat in the DATA folder.
 3. Delete patch000.dat.
 4. Copy the content of the MRFIXIT folder from this archive to the DATA folder
    (overwrite old files).
 5. IMPORTANT! Be sure that all *.pro files have "read only" attribute!!!
 6. Run Fallout2, You don't need to start a new game to see the changes.

 If you're experiencing problems, look at the section 6 - "Known problems".

--------------------------------------------------------------------------------

 3. Compatibility with the other mods

--------------------------------------------------------------------------------

 "MrFixit" is compatible with all mods, that do not change obj_dude.int and
 test0.msg. Some mods, such as "New Vision", include patch v1.02d, which
 contains obj_dude.int. To check the changes extract obj_dude.int from your
 patch000.dat v1.02d and compare it with obj_dude.int from the mod (For
 example you can do it with the "fc" command. For more information see your
 Windows manual.)

 NOTE: "New Vision" includes "pure" obj_dude.int from version 1.02d.

 If You want to integrate "MrFixit" in the mod with changed obj_dude.int, see
 section 5 - "Integration".

--------------------------------------------------------------------------------

 4. Data structure

--------------------------------------------------------------------------------

 All data "MrFixit" needs are located in the test0.msg. It's a second entry
 in the any version of scripts.lst. We used it to keep compatibility with the
 other mods.

 ATTENTION! To avoid unnecessary meshing (and slowing) of the algorithms, we
 didn't set up error protection! If you'll make an error in the data, Fallout
 will crash or you'll have many many bugs. To avoid this read this section
 carefully and double check your data before running the game!

 IMPORTANT! Do not change lines from 19 to 36! This could cause the wrong
 behaviour of the script!

 Basic rules:

 Items descriptions start at the line 500. Any item can use 25 lines maximum.
 You can't skip lines inside one description! Section numbers must follow every
 25 lines without skipping! Spaces do not allowed! Sections [TOOLS],  [SKILLS]
 and [COMPONENTS] must be presented! Empty lines in these sections do not
 allowed!

 Data structure:

 {500}{}{[ITEM]}             # section start marker
 {501}{}{999}                # item PID
 {502}{}{pcx/items/mola.pcx} # picture path (relative to the DATA folder)
 {503}{}{100010}             # picture size = w * 1000 + h (max = 150 * 1000 + 60)
 {504}{}{999}                # GVAR number that allows batch (or empty)
 {505}{}{999}                # time to batch/dismantle in the game ticks
 {506}{}{YES}                # can dismantle? (YES/NO)
 {507}{}{[TOOLS]}            # tools section marker
 {508}{}{999}                # tool PID
 {509}{}{999|998|997}        # PID1|PID2|PID3 (PID1 or PID2 or PID3)
 {510}{}{[SKILLS]}           # skills section marker
 {511}{}{SKILL_REPAIR:30}    # skill:level
 {512}{}{SKILL_THROWING:20}  # skill:level
 {513}{}{SKILL_TRAPS:10}     # skill:level
 {514}{}{[COMPONENTS]}       # components section marker
 {515}{}{999:9}              # PID:quantity
 {516}{}{999:9}              # PID:quantity
 {517}{}{999:9}              # PID:quantity

 You can find examples in test0.msg.

 Explanations:
 1. You can find PID (Prototype IDentifier) number using mapper or header file
    itempid.h.
 2. One game second == 10 game ticks.
 3. "YES" and "NO" must be uppercase. Using lowercase will cause an error.
 4. If any section is empty (unused), it's marker must be presented, and
    just after this marker must follow next section marker:
    {507}{}{[TOOLS]}            # tolls section marker
    {508}{}{[SKILLS]}           # skills section marker
    {509}{}{SKILL_REPAIR:30}
 5. You can join tools with the '|' symbol. This allows You to use any of the
    following tools:
    {508}{}{4|45|236}           # PID_KNIFE|PID_THROWING_KNIFE|PID_COMBAT_KNIFE
    This entry means that PC can use any of the following tools to batch item.
 6. Skill names for the [SKILLS] section are taken from the table located from
    line 19 to line 36.
    SKILL_REPAIR:30 means that repair skill must be greater than or equal to 30.

--------------------------------------------------------------------------------

 5. Integration

--------------------------------------------------------------------------------

 You can use, distribute and change "MrFixit" code without any permission,
 untill you keep the authorship.

 If you want to use "MrFixit" in your mod or integrate it in any other mod, you
 will need:
 1. BIS headers.
 2. ssl compiler.
 3. Sources from this archive.

 File list:
 atoi2.ssl, custstr2.ssl - "string libraries",
 test0.ssl - main "MrFixit" code,
 obj_dude.ssl - little bit changed obj_dude.int.

 Main files are atoi2.ssl, custstr2.ssl and test0.ssl.
 
 The example of using the code is given in obj_dude.ssl:
 1. Copy the main files in the same folder with your script.
 2. Include test0.ssl to your script:
    #include "test0.ssl"
 3. Call initialiser - batch_init:
    procedure description_p_proc begin
        if (not(combat_is_initialized)) then begin
            script_overrides;
            call batch_init;
        end
    end
    The control if (not(combat_is_initialized)) needed to disable batch during
    the combat, script_overrides overloads the default procedure
    description_p_proc, and batch_init initialises and runs batch. You can use
    this logic the same way in any script you want, for example int the
    workbench script:
    procedure use_p_proc begin
        if (not(combat_is_initialized)) then begin
            script_overrides;
            call batch_init;
        end
    end

 Items and windows pictures are located in the PCX folder. "MrFixit" uses so
 called "interface mode" which operates only with the pcx-graphics.

 If You have any questions about the code, just ask me, Wasteland Ghost
 (wasteland_ghost@mail.ru), or Raven (raven-umr-@mail.ru).

--------------------------------------------------------------------------------

 6. Known problems

--------------------------------------------------------------------------------

 Since "MrFixit" uses the "interface mode" which has a lot of unknown parts,
 there are some restrictions:
 1. All pictures must be in pcx format.
 2. Text that is displayed in the description window (left window) can not
    exceed window size. If text length exceeds window width it will cause the
    game to crash. So do not use long names and a lot of
    tools/skills/components! 

--------------------------------------------------------------------------------

 7. About Us

--------------------------------------------------------------------------------

 You can locate us at: www.teamx.ru

 If you have any questions write to
 Wasteland Ghost: wasteland_ghost@mail.ru
 Also send your bug reports there, or post them in our forum.

 If You have any questions about the code, write me, Wasteland Ghost
 (wasteland_ghost@mail.ru), or Raven (raven-umr-@mail.ru).
 
--------------------------------------------------------------------------------

 8. Acknowledgements

--------------------------------------------------------------------------------

 - Refiler - for throwing down a challenge :)
 - Anchorite - for the compiler/decompiler
 - Raven     - for the "string libraries" and persistence
 - SpyBomb   - for the pictures and advices
 - $py       - for the new interface, pictures, useful comments and translation
 - Strongholder - for testing
 - Izuken  - for the attempt ;)
 - Every  member of the TeamX of the present, as well as everyone for the
   moral support.
 - And, of course, BlackIsle Studios - for such a great game!
 
 That's all. Let's hope this isn't the last time you're reading a readme file
 to a TeamX creation ;).

 May the fate smile down on your path in the Wasteland!
 
 ----
 Wasteland Ghost, TeamX
 23.09.2005
