# EcCo Gameplay Overhaul

Fallout 2 mod. Runs on top of Restoration Project Updated (RPU). Needs sfall.
Scripts are SSL (Fallout script language), compiled to `.int`.

## Files

- `scripts_src/` - script sources (`.ssl`, `.h`).
  - `_pbs_main/` - new mod scripts. `gl_*` = sfall global scripts (hooks). `tests/`, `wip/` are not built.
  - `_pbs_headers/` - shared mod headers (ini, log, msg, utils).
  - `_pbs_craft/` - crafting system.
  - `sfall/` - sfall headers and libs (`lib.*.h`).
  - `headers/` - vanilla/RPU headers.
  - town folders (`den/`, `klamath/`, ...) - edited copies of RPU scripts.
- `root/` - mirrors the game folder. This is what ships.
  - `data/` - game data (art, proto, maps, text, `scripts/*.int`, `config/*.ini`). Packed into a `.dat`.
  - `ecco_config/` - user-facing mod config (`combat.ini`, `barter.ini`, `loot.ini`, `misc.ini`).
  - `sfall/` - sfall ini overrides (perks, skills, stats, drugs, books).
  - `mods/` - built `rpu_y_ecco.dat` and `mods_order.txt`.
- `proto_src/` - Python tools. Dump item/critter protos (`.pro`) to YAML for review.
- `extra/` - build scripts, compiler binaries (`extra/bin`), installer.
- `separate_mods/` - small standalone mods built from the same sources (`lite`, `weapon_sfx`).
- `docs/` - readme, changelogs (EN/RU), balance notes and tables.
- `maps_txt/` - text dumps of maps (ignored by git).

## Build

All Windows `.cmd`, run from anywhere.

1. `extra/compile_all.cmd [-r]` - compile all `.ssl` to `root/data/scripts/`. `-r` deletes old `.int` first.
   Uses Watcom preprocessor + `compile.exe` (`extra/bin/compile_wcc.cmd`). Must have `extra/bin` in PATH.
   `gl_*`, `hs_*` scripts compile with short-circuit eval (`-s`).
2. `extra/makedat.cmd` - pack `root/data/*` into `root/mods/rpu_y_ecco.dat`.
3. Release: `extra/build_zip.cmd` (zip of `mods/`, `sfall/` + docs) or `extra/installer.iss` (Inno Setup).
   `extra/build_separate_mod.cmd lite|weapon_sfx` builds separate mods.

Deploy = copy `root/mods`, `root/sfall`, `root/ecco_config` into the game folder.
`.int`, `.dat`, `.zip`, `.exe` are git-ignored.

## Script architecture

- Most features are sfall global scripts in `_pbs_main/gl_pbs_*.ssl`, one feature per script.
- Pattern: `procedure start` -> `if (not game_loaded) return` -> read ini -> `register_hook_proc(HOOK_*, handler)`.
- Each script defines `SCRIPT_REALNAME` before including `ecco_log.h` (for `debug_log*`).
- Shared code lives in `_pbs_headers/` (header-only, `#ifndef` guards). Include with relative paths (`../sfall/...`).
- New text goes to extra `.msg` files in `root/data/text/english/game/` (e.g. `pbs_combat.msg`), loaded via `add_extra_msg_file`.
- Map/NPC script changes: edit the RPU script copy in its town folder.

## Configuration

- Every tweak is read from ini, never hardcoded. Helpers in `_pbs_headers/ecco_ini.h` (`get_int_from_ini`, `get_ini_value_def`, list/range parsers).
- `root/ecco_config/*.ini` - player-tunable settings. One `[SECTION]` per feature/script. Each key has a comment with meaning and vanilla value.
  Convention: `enable_tweaks=0` or `0`/`-1` values disable a feature or restore vanilla.
- `root/data/config/*.ini` - internal data tables (craft recipes, traps, map tweaks, critter armor, spray, sfx). Ships inside the `.dat`.
- `root/sfall/*.ini` - sfall engine settings (perks, skills, stats, drugs).
