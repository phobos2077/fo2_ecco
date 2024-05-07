# from __future__ import 
import os
# import json
# import configparser
import re
import itertools
import argparse

# This script used to generate INI representation from TXT format generated by fixit_totxt.py
# author: phobos2077

print("Fixit TXT=>INI convertor")

parser = argparse.ArgumentParser(description='Converts batch sections from plain text to MSG format')
parser.add_argument('-i', help='input TXT filename')
parser.add_argument('-o', help='output MSG name')

args = parser.parse_args()

inFilename = 'test0.txt' if (args.i == None) else args.i
outFilename = 'test0.ini' if (args.o == None) else args.o

print('Loading %s...' % inFilename)

fIn = open(inFilename, 'r')
fOut = open(outFilename, 'w')

#curItem = None
itemNum = 0
commentPos = 36
section = 0
andData = None
andComments = None

#def writeCurItem():
#    fOut.write("\n\n[" + curItem["name"] + "]")
#    fOut.write("\noutput = " + curItem["pid"])
#    fOut.write("\npic_w = " + str(curItem["pic_w"]))
#    fOut.write("\npic_h = " + str(curItem["pic_h"]))
#    fOut.write("\ngvar = " + curItem["var"])
#    fOut.write("\ntime = " + str(curItem["time"]))
#    fOut.write("\nreversable = " + str(int(curItem["reverse"])))
#    fOut.write("\ncategory = " + curItem["category"])
#    fOut.write("\ntools = " + ",".join(curItem["tools"]) + "\t\t\t\t\t; " + ", ".join(curItem["tools_cmt"]))
#    fOut.write("\nskills = " + ",".join(curItem["skills"]))
#    fOut.write("\ncomponents = " + ",".join(curItem["items"]) + "\t\t\t\t\t; " + ", ".join(curItem["items_cmt"]))

skills = [
    "SMALL_GUNS",
    "BIG_GUNS",
    "ENERGY_WEAPONS",
    "UNARMED",
    "MELEE_WEAPONS",
    "THROWING",
    "FIRST_AID",
    "DOCTOR",
    "SNEAK",
    "LOCKPICK",
    "STEAL",
    "TRAPS",
    "SCIENCE",
    "REPAIR",
    "SPEECH",
    "BARTER",
    "GAMBLING",
    "OUTDOORSMAN",
]

def replaceSkills(data):
    for i, v in enumerate(skills):
        data = data.replace(v, str(i))
    return data

def writePair(key, value, comment = None):
    payload = "{}={}".format(key, value)
    if (comment):
        fOut.write("{}{}; {}\n".format(payload, " " * max(commentPos - len(payload), 1), comment))
    else:
        fOut.write(payload)
        fOut.write("\n")

def writeAndList(key):
    writePair(key, ",".join(andData), ", ".join(andComments))

def initAndList():
    #print("Init and lists")
    global andData
    global andComments
    andData = []
    andComments = []

def appendAndList(data, comment):
    #print("And lists {} {}".format(andData, andComments))
    andData.append(data)
    andComments.append(comment or data)

for line in fIn:
    m = re.search(r"^([^#\s]*) *(#[^\n]+)?", line)
    data = m.group(1)
    comment = m.group(2)[1:].strip() if m.group(2) else None
    #print(data)
    if (data == "[ITEM]"):
        section = 1
        fieldNum = 1
        itemNum += 1
        #curItem = {}

    elif (section == 1):
        if (data == "[TOOLS]"):
            initAndList()
            section = 2

        elif (fieldNum == 1):
            #curItem["pid"] = data
            #curItem["name"] = comment or ("recipe " + str(itemNum))
            name = comment.upper().removeprefix("PID_").removeprefix("NEW ").replace(" ", "_").replace(".", "")
            fOut.write("[Recipe {}]\n".format(name))
            writePair("output", data)

        elif (fieldNum == 3):
            num = int(data)
            writePair("pic_w", num // 1000)
            writePair("pic_h", num % 1000, comment)

        elif (fieldNum == 4):
            writePair("gvar", data, comment)

        elif (fieldNum == 5):
            writePair("time", int(data) // 600, comment)

        elif (fieldNum == 6):
            writePair("undo", int(data == "YES"), comment)

        elif (fieldNum == 7):
            writePair("category", data, comment)

        fieldNum += 1

    elif (section == 2):
        if (data == "[SKILLS]"):
            writeAndList("tools")
            initAndList()
            section = 3

        elif (data != ""):
            appendAndList(data, comment)

    elif (section == 3):
        if (data == "[COMPONENTS]"):
            writeAndList("skills")
            initAndList()
            section = 4
        
        elif (data != ""):
            appendAndList(replaceSkills(data), comment or data)

    elif (section == 4):
        if (data != ""):
            appendAndList(data, comment)
        else:
            writeAndList("input")
            fOut.write("\n")
            section = 0

    elif (comment):
        fOut.write("; {}\n".format(comment))

    else:
        fOut.write("\n")

fOut.write("\n")
    
    
fIn.close()
fOut.close()
    
print(outFilename + " was written (" + str(itemNum) + ") schematics.")