# from __future__ import 
import os
# import json
# import configparser
import re
import itertools
import argparse

# This script used to generate MSG representation from TXT format generated by fixit_totxt.py
# author: phobos2077


print("Fixit TXT=>MSG convertor")

parser = argparse.ArgumentParser(description='Converts batch sections from plain text to MSG format')
parser.add_argument('-i', help='input TXT filename')
parser.add_argument('-o', help='output MSG name')

args = parser.parse_args()

inFilename = 'test0.txt' if (args.i == None) else args.i
outFilename = 'test0.msg' if (args.o == None) else args.o

sourceFilename = outFilename+"~"

os.rename( outFilename, sourceFilename )

SECTION_START = 1000
SECTION_STEP = 100

print('Loading %s...' % inFilename)

#print(" {asda".find("{"))
#exit()

f = open(inFilename, 'r')
fSrc = open(sourceFilename, 'r')
fOut = open(outFilename, 'w')

lastComment = ''
for line in fSrc:
    m = re.search(r"\{(\d+)\}\{\}", line)
    if (m):
        if (int(m.group(1)) >= SECTION_START): 
            break
        else:
            fOut.write(lastComment)
            lastComment = ''
            fOut.write(line)
    else:
        lastComment += line
    
fOut.write("\n")
    
n = 0
i = 0
ii = -1
for line in f :
    sp = line.find("\n")
    if (sp >= 0): line = line[:sp]
    if (line.find("[ITEM]") != -1):
        ii += 1
        i = SECTION_START + ii*SECTION_STEP
    
    m = re.search(r"([\S]*)(\s*\#.+)", line)
    if (m):
        comment = m.group(2)
        line = m.group(1)
    else:
        comment = ""
    if (len(line) > 0 or (i >= SECTION_START and (i % SECTION_STEP) < 8)):
        fOut.write("{"+str(i)+"}{}{"+line+"}"+comment+"\n")
        i += 1
        n += 1
    else:
        fOut.write(comment+"\n")
            
    
f.close()
fOut.close()
fSrc.close()
os.remove(sourceFilename)
    
print(outFilename + " was written ("+str(n)+") lines.")
