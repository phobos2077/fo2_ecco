#
# pip install pyyaml
#
# written by phobos2077 with help of Bing Chat

import glob
import os
import struct
import yaml
from typing import List, Dict
from collections import namedtuple
from fallout_enums import *

CALIBERS = []

def flagsAsHex(flags):
    return hex(flags % (1<<32))

def readFile(file_path: str) -> Dict:
    with open(file_path, 'rb') as f:
        data = f.read()
        keys = ['version', 'name', 'startTile', 'startElevation', 'startRotation', 'lvarCount', 'scrIdx', 'flags', 'darkness', 'gvarCount', 'index', 'lastVisitTime']
        # Header = namedtuple('Header', 'version name startTile startElevation startRotation lvarCount scrIdx flags darkness gvarCount index lastVisitTime')
        head = dict(zip(keys, struct.unpack('>i16siiiiiiiiii', data[:60])))
        head['name'] = head['name'].decode('ascii').rstrip('\0')
    return head

def writeFile(file_path: str, data: Dict):
    with open(file_path, 'w') as f:
        yaml.dump(data, f, sort_keys = False, default_style = '')

def main(file_pattern: str, output_dir: str):
    files = glob.glob(file_pattern)
    for file in files:
        try:
            data = readFile(file)
            os.makedirs(output_dir, exist_ok = True)
            writeFile(os.path.join(output_dir, f'{os.path.splitext(os.path.basename(file))[0]}.yml'), data)
        except Exception as e:
            print("Error map proto " + file + ": ", e)

    print("Written " + str(len(files)) + " text files.")

if __name__ == '__main__':
    import sys
    import argparse
    
    parser = argparse.ArgumentParser()
    parser.add_argument('file_pattern', help='A blob pattern for MAP files')
    parser.add_argument('output_dir', help='Output directory')
    args = parser.parse_args()

    main(args.file_pattern, args.output_dir)
