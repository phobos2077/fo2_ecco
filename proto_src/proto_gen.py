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

def flagsAsHex(flags):
    return hex(flags % (1<<32))

def readFile(file_path: str, msgFiles: Dict) -> Dict:
    with open(file_path, 'rb') as f:
        data = f.read()
        proItemMsg = msgFiles['pro_item']
        itemProto = struct.unpack('>iiiiiiiiiiiiiic', data[:57])
        itemProtoData = data[57:]
        messageId = itemProto[1]
        itemProtoDict = {
            'pid': itemProto[0],
            'messageId': messageId,
            'name': proItemMsg[messageId] if messageId in proItemMsg else '',
            'description': proItemMsg[messageId + 1] if (messageId + 1) in proItemMsg else '',
            'fid': itemProto[2],
            'lightDistance': itemProto[3],
            'lightIntensity': itemProto[4],
            'flags': flagsAsHex(itemProto[5]),
            'extendedFlags': flagsAsHex(itemProto[6]),
            'sid': itemProto[7],
            'type': ITEM_TYPES[itemProto[8]],
            'material': itemProto[9],
            'size': itemProto[10],
            'weight': itemProto[11],
            'cost': itemProto[12],
            'inventoryFid': itemProto[13],
            'soundId': itemProto[14].decode('ascii')
        }
        if itemProtoDict['type'] == 'ITEM_TYPE_ARMOR':
            armorData = struct.unpack('>iiii' + 'i' * 7 * 2, itemProtoData)
            perkId = armorData[15]
            itemProtoDict['armorData'] = {
                'armorClass': armorData[0],
                'damageResistance': dict(zip(DAMAGE_TYPE_KEYS, list(armorData[1:8]))),
                'damageThreshold': dict(zip(DAMAGE_TYPE_KEYS, list(armorData[8:15]))),
                'perk': PERKS[perkId],
                'maleFid': armorData[16],
                'femaleFid': armorData[17]
            }
        elif itemProtoDict['type'] == 'ITEM_TYPE_CONTAINER':
            containerData = struct.unpack('>ii', itemProtoData)
            itemProtoDict['containerData'] = {
                'maxSize': containerData[0],
                'openFlags': flagsAsHex(containerData[1])
            }
        elif itemProtoDict['type'] == 'ITEM_TYPE_DRUG':
            drugData = struct.unpack('>iiiii' + 'iii' * 4, itemProtoData)
            itemProtoDict['drugData'] = {
                'stat': [DRUG_STATS[i] for i in drugData[:3]],
                'amount': list(drugData[3:6]),
                'duration1': drugData[6],
                'amount1': list(drugData[7:10]),
                'duration2': drugData[10],
                'amount2': list(drugData[11:14]),
                'addictionChance': drugData[14],
                'withdrawalEffect': drugData[15],
                'withdrawalOnset': drugData[16]
            }
        elif itemProtoDict['type'] == 'ITEM_TYPE_WEAPON':
            weaponData = struct.unpack('>iiiiiii' + ('i' * 9) + 'c', itemProtoData)
            perkId = weaponData[11]
            caliberId = weaponData[13]
            itemProtoDict['weaponData'] = {
                'animationCode': weaponData[0],
                'minDamage': weaponData[1],
                'maxDamage': weaponData[2],
                'damageType': DAMAGE_TYPES[weaponData[3]],
                'maxRange1': weaponData[4],
                'maxRange2': weaponData[5],
                'projectilePid': weaponData[6],
                'minStrength': weaponData[7],
                'actionPointCost1': weaponData[8],
                'actionPointCost2': weaponData[9],
                'criticalFailureType': weaponData[10],
                'perk': PERKS[perkId],
                'rounds': weaponData[12],
                'caliber': CALIBERS[caliberId] if (caliberId in CALIBERS) else caliberId,
                'ammoTypePid': weaponData[14],
                'ammoCapacity': weaponData[15],
                'soundCode': weaponData[16].decode('ascii')
            }
        elif itemProtoDict['type'] == 'ITEM_TYPE_AMMO':
            ammo_data = struct.unpack('>iiiiii', itemProtoData)
            caliberId = ammo_data[0]
            itemProtoDict['ammoData'] = {
                'caliber': CALIBERS[caliberId] if (caliberId in CALIBERS) else caliberId,
                'quantity': ammo_data[1],
                'armorClassMod': ammo_data[2],
                'damageResistanceMod': ammo_data[3],
                'damageMult': ammo_data[4],
                'damageDiv': ammo_data[5]
            }
        elif itemProtoDict['type'] == 'ITEM_TYPE_MISC':
            miscData = struct.unpack('>iii', itemProtoData)
            itemProtoDict['miscData'] = {
                'powerTypePid': miscData[0],
                'powerType': miscData[1],
                'charges': miscData[2]
            }
        elif itemProtoDict['type'] == 'ITEM_TYPE_KEY':
            keyData = struct.unpack('>i', itemProtoData)
            itemProtoDict['keyData'] = {
                'keyCode': keyData[0]
            }
    return itemProtoDict

def writeFile(file_path: str, data: Dict):
    with open(file_path, 'w') as f:
        yaml.dump(data, f, sort_keys = False, default_style = '')

def main(file_pattern: str, output_dir: str, msg_dir: str):
    msgFiles = {
        'proto': parse_msg_file(os.path.join(msg_dir, "proto.msg")),
        'pro_item': parse_msg_file(os.path.join(msg_dir, "pro_item.msg"))
    }
    CALIBERS = read_calibers(msgFiles['proto'])
    typeToDir = dict(zip(ITEM_TYPES, ['armor', 'container', 'drug', 'weapon', 'ammo', 'misc', 'key']))
    files = glob.glob(file_pattern)
    for file in files:
        try:
            data = readFile(file, msgFiles)
            # fileName = "".join(x for x in data['name'] if (x.isalnum() or x in "._- ")) if data['name'] else os.basename(file)

            outputSubdir = os.path.join(output_dir, typeToDir[data['type']])
            os.makedirs(outputSubdir, exist_ok = True)
            writeFile(os.path.join(outputSubdir, f'{os.path.splitext(os.path.basename(file))[0]}.yml'), data)
        except Exception as e:
            print("Error reading proto " + file + ": ", e)

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