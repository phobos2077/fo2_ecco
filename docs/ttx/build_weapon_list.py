# by Bing:
# You can run this script from the command line by passing the names of the weapons file, the ammo file and the output file as arguments. For example:
# python build_weapon_list.py weapons.csv ammo.csv output.csv
# This will read the data from weapons.csv and ammo.csv, process it according to the rules you specified and write the result to output.csv.

import csv
import sys

def print_record(record):
    for key, value in record.items():
        print(f"Key={key}")
        print(f"Value={value}")

def parse_csv_files(weapons_file, ammo_file, output_file):
    # Read weapons file
    with open(weapons_file, 'r') as f:
        reader = csv.DictReader(f, delimiter=';')
        weapons = [row for row in reader]

    # print_record(weapons[0])

    # Read ammo file
    with open(ammo_file, 'r') as f:
        reader = csv.DictReader(f, delimiter=';')
        ammo = [row for row in reader]

    # Build list of unique calibers
    calibers = set()
    for weapon in weapons:
        calibers.add(weapon['Caliber'])
    calibers = sorted(list(calibers))

    # Build map of ammo types for each caliber
    caliber_ammo_map = {}
    for caliber in calibers:
        caliber_ammo_map[caliber] = []
        for a in ammo:
            if a['Caliber'] == caliber:
                caliber_ammo_map[caliber].append(a)

    # Build result
    result = []
    for weapon in weapons:
        weapon_caliber = weapon['Caliber']
        if weapon_caliber in caliber_ammo_map and weapon_caliber != 'None':
            for a in caliber_ammo_map[weapon_caliber]:
                # AC Adjust;DR Adjust;Dam Mult;Dam Div
                result.append({
                    'DMG Type': weapon['Damage Type'],
                    'Caliber': weapon['Caliber'],
                    'Weapon': weapon['NAME'],
                    'Ammo': a['NAME'],
                    'DMG Min': int(weapon['Min Damage']),
                    'DMG Max': int(weapon['Max Damage']),
                    'Perk': weapon['Perk']
                })

    # Sort result
    result.sort(key=lambda x: (x['DMG Type'], x['Caliber'], (x['DMG Min'] + x['DMG Max'])/2))

    # Write result to output file
    with open(output_file, 'w', newline='') as f:
        fieldnames = ['DMG Type', 'Caliber', 'Weapon', 'Ammo', 'DMG Min', 'DMG Max', 'Perk']
        writer = csv.DictWriter(f, fieldnames=fieldnames, delimiter=';')
        writer.writeheader()
        for row in result:
            writer.writerow(row)

if __name__ == '__main__':
    weapons_file = sys.argv[1]
    ammo_file = sys.argv[2]
    output_file = sys.argv[3]
    print(weapons_file)
    print(ammo_file)
    parse_csv_files(weapons_file, ammo_file, output_file)