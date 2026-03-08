#!/usr/bin/env python3
"""
Optimized Parser/converter for Fallout 1 and 2 .PRO files to JSON format
Optimized for batch processing of many files with improved I/O performance

Generated via DeepSeek
"""

# Fallout 1 mode
FO1 = True

import sys
import os
import struct
import json
import mmap
from concurrent.futures import ProcessPoolExecutor, ThreadPoolExecutor
from typing import Any, Dict, List, Optional, Union
from pathlib import Path
import argparse
from functools import lru_cache, partial
import gc

# Type definitions
TYPE_ITEM = 0
TYPE_CRITTER = 1
TYPE_SCENERY = 2
TYPE_WALL = 3
TYPE_TILE = 4
TYPE_MISC = 5

SUBTYPE_ARMOR = 0
SUBTYPE_CONTAINER = 1
SUBTYPE_DRUG = 2
SUBTYPE_WEAPON = 3
SUBTYPE_AMMO = 4
SUBTYPE_MISC = 5
SUBTYPE_KEY = 6

SCENERY_DOOR = 0
SCENERY_STAIRS = 1
SCENERY_ELEVATOR = 2
SCENERY_LADDER_BOTTOM = 3
SCENERY_LADDER_TOP = 4
SCENERY_GENERIC = 5

# Pre-compiled struct formats for faster reading
STRUCT_H = struct.Struct('!h')  # 2-byte signed
STRUCT_L = struct.Struct('!l')  # 4-byte signed
STRUCT_B = struct.Struct('!B')  # 1-byte unsigned
STRUCT_3B = struct.Struct('!3s')  # 3 bytes

# Cache for frequently used data
_stat_names = ["STR", "PER", "END", "CHR", "INT", "AGI", "LUK", "HP", "AP",
               "AC", "Unarmed", "Melee", "Carry", "Sequence", "Healing Rate",
               "Critical Chance", "Better Criticals"]
_resist_names = ["DT Normal", "DT Laser", "DT Fire", "DT Plasma", "DT Electrical",
                 "DT EMP", "DT Explosive", "DR Normal", "DR Laser", "DR Fire",
                 "DR Plasma", "DR Electrical", "DR EMP", "DR Explosive",
                 "DR Radiation", "DR Poison"]
_skill_names = ["Small Guns", "Big Guns", "Energy Weapons", "Unarmed",
                "Melee", "Throwing", "First Aid", "Doctor", "Sneak",
                "Lockpick", "Steal", "Traps", "Science", "Repair",
                "Speech", "Barter", "Gambling", "Outdoorsman"]
_armor_stats = ["DR Normal", "DR Laser", "DR Fire", "DR Plasma", "DR Electrical", 
                "DR EMP", "DR Explosive", "DT Normal", "DT Laser", "DT Fire", 
                "DT Plasma", "DT Electrical", "DT EMP", "DT Explosive"]

# Optimized reading functions using pre-compiled structs
def read_int16(data: bytes, offset: int = 0) -> tuple:
    """Read a 16-bit signed integer from bytes"""
    return STRUCT_H.unpack_from(data, offset)[0], offset + 2

def read_int32(data: bytes, offset: int = 0) -> tuple:
    """Read a 32-bit signed integer from bytes"""
    return STRUCT_L.unpack_from(data, offset)[0], offset + 4

def read_byte(data: bytes, offset: int = 0) -> tuple:
    """Read a single byte"""
    return data[offset], offset + 1

def read_bytes(data: bytes, offset: int, size: int) -> tuple:
    """Read a specific number of bytes"""
    return data[offset:offset + size], offset + size

def read_scenery(data: bytes, offset: int) -> tuple:
    """Parse scenery data from bytes"""
    obj = {}
    
    # Read basic fields
    obj["wallLightTypeFlags"], offset = read_int16(data, offset)
    obj["actionFlags"], offset = read_int16(data, offset)
    obj["scriptPID"], offset = read_int32(data, offset)
    obj["subType"], offset = read_int32(data, offset)
    obj["materialID"], offset = read_int32(data, offset)
    sound_id, offset = read_byte(data, offset)
    obj["soundID"] = sound_id

    # Handle subtype-specific fields
    if obj["subType"] == SCENERY_DOOR:
        walkthrough, offset = read_int32(data, offset)
        obj["walkthroughFlag"] = walkthrough
        # Skip 4-byte unknown
        offset += 4
    elif obj["subType"] == SCENERY_STAIRS:
        obj["destination"], offset = read_int32(data, offset)
        obj["destinationMap"], offset = read_int32(data, offset)
    elif obj["subType"] == SCENERY_ELEVATOR:
        obj["elevatorType"], offset = read_int32(data, offset)
        obj["elevatorLevel"], offset = read_int32(data, offset)
    elif obj["subType"] in (SCENERY_LADDER_BOTTOM, SCENERY_LADDER_TOP):
        obj["destination"], offset = read_int32(data, offset)
    elif obj["subType"] == SCENERY_GENERIC:
        # Skip 4-byte unknown
        offset += 4

    return obj, offset

def read_drug_effect(data: bytes, offset: int) -> tuple:
    """Parse drug effect data"""
    obj = {}
    obj["duration"], offset = read_int32(data, offset)
    obj["amount0"], offset = read_int32(data, offset)
    obj["amount1"], offset = read_int32(data, offset)
    obj["amount2"], offset = read_int32(data, offset)
    return obj, offset

def read_item(data: bytes, offset: int) -> tuple:
    """Parse item data from bytes"""
    obj = {}

    # Read flags and basic data
    flags_ext, offset = read_bytes(data, offset, 3)
    attack_mode, offset = read_byte(data, offset)
    script_id, offset = read_int32(data, offset)
    obj_sub_type, offset = read_int32(data, offset)
    material_id, offset = read_int32(data, offset)
    size, offset = read_int32(data, offset)
    weight, offset = read_int32(data, offset)
    cost, offset = read_int32(data, offset)
    inv_frm, offset = read_int32(data, offset)
    sound_id, offset = read_byte(data, offset)

    # Set basic fields
    obj["itemFlags"] = flags_ext[0]
    obj["actionFlags"] = flags_ext[1]
    obj["weaponFlags"] = flags_ext[2]
    obj["attackMode"] = attack_mode
    obj["scriptID"] = script_id
    obj["subType"] = obj_sub_type
    obj["materialID"] = material_id
    obj["size"] = size
    obj["weight"] = weight
    obj["cost"] = cost
    obj["invFRM"] = inv_frm
    obj["soundID"] = sound_id

    # Handle subtype-specific data
    if obj_sub_type == SUBTYPE_WEAPON:
        weapon_fields = [
            "animCode", "minDmg", "maxDmg", "dmgType", "maxRange1",
            "maxRange2", "projPID", "minST", "APCost1", "APCost2",
            "critFail", "perk", "rounds", "caliber", "ammoPID", "maxAmmo"
        ]
        for field in weapon_fields:
            obj[field], offset = read_int32(data, offset)
        sound_id2, offset = read_byte(data, offset)
        obj["weaponSoundID"] = sound_id2
        
    elif obj_sub_type == SUBTYPE_AMMO:
        ammo_fields = ["caliber", "quantity", "AC modifier", "DR modifier", 
                      "damMult", "damDiv"]
        for field in ammo_fields:
            obj[field], offset = read_int32(data, offset)
            
    elif obj_sub_type == SUBTYPE_ARMOR:
        obj["AC"], offset = read_int32(data, offset)
        obj["stats"] = {}
        for stat in _armor_stats:
            obj["stats"][stat], offset = read_int32(data, offset)
        obj["perk"], offset = read_int32(data, offset)
        obj["maleFID"], offset = read_int32(data, offset)
        obj["femaleFID"], offset = read_int32(data, offset)
        
    elif obj_sub_type == SUBTYPE_DRUG:
        drug_fields = ["stat0", "stat1", "stat2", "amount0", "amount1", "amount2"]
        for field in drug_fields:
            obj[field], offset = read_int32(data, offset)
        
        obj["firstDelayed"], offset = read_drug_effect(data, offset)
        obj["secondDelayed"], offset = read_drug_effect(data, offset)
        
        obj["addictionRate"], offset = read_int32(data, offset)
        obj["addictionEffect"], offset = read_int32(data, offset)
        obj["addictionOnset"], offset = read_int32(data, offset)

    return obj, offset

def read_critter_stats(data: bytes, offset: int) -> tuple:
    """Parse critter stats"""
    stats = {}
    
    # Read base stats
    for stat in _stat_names:
        stats[stat], offset = read_int32(data, offset)
    
    # Read resistances
    for stat in _resist_names:
        stats[stat], offset = read_int32(data, offset)
    
    return stats, offset

def read_critter_skills(data: bytes, offset: int) -> tuple:
    """Parse critter skills"""
    skills = {}
    for skill in _skill_names:
        skills[skill], offset = read_int32(data, offset)
    return skills, offset

def read_critter(data: bytes, offset: int) -> tuple:
    """Parse critter data"""
    obj = {}

    # Read basic fields
    basic_fields = ["actionFlags", "scriptID", "headFID", "AI", "team", "flags"]
    for field in basic_fields:
        obj[field], offset = read_int32(data, offset)

    # Read stats
    obj["baseStats"], offset = read_critter_stats(data, offset)
    obj["age"], offset = read_int32(data, offset)
    obj["gender"], offset = read_int32(data, offset)
    obj["bonusStats"], offset = read_critter_stats(data, offset)
    obj["bonusAge"], offset = read_int32(data, offset)
    obj["bonusGender"], offset = read_int32(data, offset)
    obj["skills"], offset = read_critter_skills(data, offset)

    # Read remaining fields
    remaining_fields = ["bodyType", "XPValue", "killType"]
    for field in remaining_fields:
        obj[field], offset = read_int32(data, offset)

    # Handle damage type
    if FO1 or obj["killType"] in (5, 10):
        obj["damageType"] = None
    else:
        obj["damageType"], offset = read_int32(data, offset)

    return obj, offset

def read_pro_from_bytes(data: bytes) -> Dict[str, Any]:
    """Parse PRO data from bytes"""
    obj = {}
    offset = 0

    # Read header
    object_type_and_id, offset = read_int32(data, offset)
    text_id, offset = read_int32(data, offset)
    frm_type_and_id, offset = read_int32(data, offset)
    light_radius, offset = read_int32(data, offset)
    light_intensity, offset = read_int32(data, offset)
    flags, offset = read_int32(data, offset)

    # Extract PID and type
    pid = object_type_and_id & 0xffff
    obj_type = (object_type_and_id >> 24) & 0xff

    # Extract FRM info
    frm_pid = frm_type_and_id & 0xffff
    frm_type = (frm_type_and_id >> 24) & 0xff

    # Set basic fields
    obj.update({
        "pid": pid,
        "textID": text_id,
        "type": obj_type,
        "flags": flags,
        "lightRadius": light_radius,
        "lightIntensity": light_intensity,
        "frmPID": frm_pid,
        "frmType": frm_type
    })

    # Parse type-specific data
    if obj_type == TYPE_ITEM:
        obj["extra"], offset = read_item(data, offset)
    elif obj_type == TYPE_CRITTER:
        obj["extra"], offset = read_critter(data, offset)
    elif obj_type == TYPE_SCENERY:
        obj["extra"], offset = read_scenery(data, offset)
    else:
        print(f"Warning: unhandled type {obj_type} for PID {pid}")

    return obj

def read_pro_file(file_path: str) -> Optional[Dict[str, Any]]:
    """Read and parse a single PRO file using memory mapping"""
    try:
        with open(file_path, "rb") as f:
            # Memory map the file for faster access
            with mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ) as mm:
                return read_pro_from_bytes(mm)
    except Exception as e:
        print(f"Error processing {file_path}: {e}", file=sys.stderr)
        return None

def process_file(file_path: str, output_dir: Optional[str] = None, 
                 compress: bool = False) -> tuple:
    """
    Process a single file and optionally save to output directory
    Returns (filename, success, data or error)
    """
    try:
        data = read_pro_file(file_path)
        if data is None:
            return (file_path, False, "Parse failed")
        
        if output_dir:
            # Create output filename
            base_name = Path(file_path).stem
            out_path = Path(output_dir) / f"{base_name}.json"
            
            # Write JSON with optional formatting
            with open(out_path, 'w', encoding='utf-8') as f:
                if compress:
                    json.dump(data, f, separators=(',', ':'))
                else:
                    json.dump(data, f, indent=4)
                    f.write('\n')
            
            return (file_path, True, str(out_path))
        else:
            return (file_path, True, data)
            
    except Exception as e:
        return (file_path, False, str(e))

def process_batch(file_paths: List[str], output_dir: Optional[str] = None,
                  compress: bool = False, max_workers: int = None) -> List[tuple]:
    """Process multiple files in parallel"""
    results = []
    
    # Use ProcessPoolExecutor for CPU-bound tasks
    with ProcessPoolExecutor(max_workers=max_workers) as executor:
        # Create partial function with fixed arguments
        func = partial(process_file, output_dir=output_dir, compress=compress)
        
        # Submit all tasks
        future_to_file = {executor.submit(func, f): f for f in file_paths}
        
        # Collect results as they complete
        for future in future_to_file:
            try:
                result = future.result()
                results.append(result)
                
                # Print progress
                file_path = result[0]
                success = result[1]
                status = "?" if success else "?"
                print(f"[{status}] {Path(file_path).name}")
                
            except Exception as e:
                file_path = future_to_file[future]
                results.append((file_path, False, str(e)))
                print(f"[?] {Path(file_path).name}: {e}")
    
    return results

def find_pro_files(directory: str) -> List[str]:
    """Find all .PRO files in a directory recursively"""
    return [str(p) for p in Path(directory).rglob("*.PRO")]

def main():
    parser = argparse.ArgumentParser(description="Convert Fallout PRO files to JSON")
    parser.add_argument("input", help="Input file or directory")
    parser.add_argument("-o", "--output", help="Output directory (if not specified, prints to stdout)")
    parser.add_argument("-c", "--compress", action="store_true", 
                       help="Compress JSON output (no indentation)")
    parser.add_argument("-j", "--jobs", type=int, default=None,
                       help="Number of parallel jobs (default: CPU count)")
    parser.add_argument("-q", "--quiet", action="store_true",
                       help="Suppress progress output")
    
    args = parser.parse_args()
    
    input_path = Path(args.input)
    
    # Collect files to process
    if input_path.is_file():
        files = [str(input_path)]
    elif input_path.is_dir():
        files = find_pro_files(str(input_path))
        if not args.quiet:
            print(f"Found {len(files)} .PRO files")
    else:
        print(f"Error: {args.input} not found", file=sys.stderr)
        sys.exit(1)
    
    # Create output directory if needed
    if args.output:
        os.makedirs(args.output, exist_ok=True)
    
    # Process files
    if len(files) == 1 and not args.output:
        # Single file, print to stdout
        data = read_pro_file(files[0])
        if data:
            if args.compress:
                print(json.dumps(data, separators=(',', ':')))
            else:
                print(json.dumps(data, indent=4))
        else:
            sys.exit(1)
    else:
        # Batch processing
        results = process_batch(files, args.output, args.compress, args.jobs)
        
        # Print summary
        if not args.quiet:
            successful = sum(1 for r in results if r[1])
            failed = len(results) - successful
            print(f"\nSummary: {successful} successful, {failed} failed")
        
        # Exit with error if any files failed
        if any(not r[1] for r in results):
            sys.exit(1)

if __name__ == '__main__':
    main()