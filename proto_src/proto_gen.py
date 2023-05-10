#
# pip install pyyaml
#
# written by phobos2077 with help of Bing Chat

import glob
import os
import struct
import yaml
from typing import List, Dict
from fallout_enums import *

CALIBERS = []

def read_file(file_path: str, msgFiles: Dict) -> Dict:
    with open(file_path, 'rb') as f:
        data = f.read()
        proItemMsg = msgFiles['pro_item']
        item_proto = struct.unpack('>iiiiiiiiiiiiiic', data[:57])
        item_proto_data = data[57:]
        messageId = item_proto[1]
        item_proto_dict = {
            'pid': item_proto[0],
            'messageId': messageId,
            'name': proItemMsg[messageId] if messageId in proItemMsg else '',
            'description': proItemMsg[messageId + 1] if (messageId + 1) in proItemMsg else '',
            'fid': item_proto[2],
            'lightDistance': item_proto[3],
            'lightIntensity': item_proto[4],
            'flags': hex(item_proto[5]),
            'extendedFlags': hex(item_proto[6]),
            'sid': item_proto[7],
            'type': ITEM_TYPES[item_proto[8]],
            'material': item_proto[9],
            'size': item_proto[10],
            'weight': item_proto[11],
            'cost': item_proto[12],
            'inventoryFid': item_proto[13],
            'soundId': item_proto[14].decode('ascii')
        }
        if item_proto_dict['type'] == 'ITEM_TYPE_ARMOR':
            armor_data = struct.unpack('>iiii' + 'i' * 7 * 2, item_proto_data)
            item_proto_dict['armorData'] = {
                'armorClass': armor_data[0],
                'damageResistance': dict(zip(DAMAGE_TYPE_KEYS, list(armor_data[1:8]))),
                'damageThreshold': dict(zip(DAMAGE_TYPE_KEYS, list(armor_data[8:15]))),
                'perk': PERKS[armor_data[15]],
                'maleFid': armor_data[16],
                'femaleFid': armor_data[17]
            }
        elif item_proto_dict['type'] == 'ITEM_TYPE_CONTAINER':
            container_data = struct.unpack('>ii', item_proto_data)
            item_proto_dict['containerData'] = {
                'maxSize': container_data[0],
                'openFlags': hex(container_data[1])
            }
        elif item_proto_dict['type'] == 'ITEM_TYPE_DRUG':
            drug_data = struct.unpack('>iiiii' + 'iii' * 4, item_proto_data)
            item_proto_dict['drugData'] = {
                'stat': [STATS[i] for i in drug_data[:3]],
                'amount': list(drug_data[3:6]),
                'duration1': drug_data[6],
                'amount1': list(drug_data[7:10]),
                'duration2': drug_data[10],
                'amount2': list(drug_data[11:14]),
                'addictionChance': drug_data[14],
                'withdrawalEffect': drug_data[15],
                'withdrawalOnset': drug_data[16]
            }
        elif item_proto_dict['type'] == 'ITEM_TYPE_WEAPON':
            weapon_data = struct.unpack('>iiiiiii' + ('i' * 9) + 'c', item_proto_data)
            caliber_id = weapon_data[13]
            item_proto_dict['weaponData'] = {
                'animationCode': weapon_data[0],
                'minDamage': weapon_data[1],
                'maxDamage': weapon_data[2],
                'damageType': weapon_data[3],
                'maxRange1': weapon_data[4],
                'maxRange2': weapon_data[5],
                'projectilePid': weapon_data[6],
                'minStrength': weapon_data[7],
                'actionPointCost1': weapon_data[8],
                'actionPointCost2': weapon_data[9],
                'criticalFailureType': weapon_data[10],
                'perk': PERKS[weapon_data[11]],
                'rounds': weapon_data[12],
                'caliber': CALIBERS[caliber_id] if (caliber_id in CALIBERS) else caliber_id,
                'ammoTypePid': weapon_data[14],
                'ammoCapacity': weapon_data[15],
                'soundCode': weapon_data[16].decode('ascii')
            }
        elif item_proto_dict['type'] == 'ITEM_TYPE_AMMO':
            ammo_data = struct.unpack('>iiiiii', item_proto_data)
            caliber_id = ammo_data[0]
            item_proto_dict['ammoData'] = {
                'caliber': CALIBERS[caliber_id] if (caliber_id in CALIBERS) else caliber_id,
                'quantity': ammo_data[1],
                'armorClassMod': ammo_data[2],
                'damageResistanceMod': ammo_data[3],
                'damageMult': ammo_data[4],
                'damageDiv': ammo_data[5]
            }
        elif item_proto_dict['type'] == 'ITEM_TYPE_MISC':
            misc_data = struct.unpack('>iii', item_proto_data)
            item_proto_dict['miscData'] = {
                'powerTypePid': misc_data[0],
                'powerType': misc_data[1],
                'charges': misc_data[2]
            }
        elif item_proto_dict['type'] == 'ITEM_TYPE_KEY':
            key_data = struct.unpack('>i', item_proto_data)
            item_proto_dict['keyData'] = {
                'keyCode': key_data[0]
            }
    return item_proto_dict

def write_file(file_path: str, data: Dict):
    with open(file_path, 'w') as f:
        yaml.dump(data, f, sort_keys = False)

def main(file_pattern: str, output_dir: str, msg_dir: str):
    msgFiles = {
        'proto': parse_msg_file(os.path.join(msg_dir, "proto.msg")),
        'pro_item': parse_msg_file(os.path.join(msg_dir, "pro_item.msg"))
    }
    CALIBERS = read_calibers(msgFiles['proto'])
    files = glob.glob(file_pattern)
    for file in files:
        data = read_file(file, msgFiles)
        file_name = os.path.basename(file)
        output_file_path = os.path.join(output_dir, f'{file_name}.yml')
        write_file(output_file_path, data)
    print("Written " + str(len(files)) + " text files.")

if __name__ == '__main__':
    import sys
    import argparse
    
    parser = argparse.ArgumentParser()
    parser.add_argument('file_pattern', help='A blob pattern for PRO files')
    parser.add_argument('output_dir', help='Output directory')
    parser.add_argument('--msg', help='msg folder')
    args = parser.parse_args()

    main(args.file_pattern, args.output_dir, args.msg)