import math

def DamageYAAM(ctd, accumulatedDamage, rounds, armorDT, armorDR, bonusRangedDamage, multiplyDamage, difficulty):
    if rounds <= 0:
        return accumulatedDamage

    accumulatedDamage = 0
    ammoDiv = ctd['ammoDiv']
    ammoMult = ctd['ammoMult']

    multiplyDamage *= ammoMult

    ammoDT = ctd['drAdjust']

    calcDT = armorDT - ammoDT
    _calcDT = calcDT

    if calcDT >= 0:
        _calcDT = 0
    else:
        _calcDT *= 10
        calcDT = 0

    calcDR = armorDR + _calcDT
    if calcDR < 0:
        calcDR = 0
    elif calcDR >= 100:
        return accumulatedDamage

    for i in range(rounds):
        rawDamage = ctd['itemDmg']
        rawDamage += bonusRangedDamage

        rawDamage -= calcDT
        if rawDamage < 0:
            continue

        rawDamage *= multiplyDamage
        if ammoDiv != 0:
            rawDamage /= ammoDiv

        rawDamage = math.floor(rawDamage / 2)
        rawDamage *= difficulty
        rawDamage = math.floor(rawDamage / 100)

        resistedDamage = calcDR * rawDamage
        resistedDamage = math.floor(resistedDamage / 100)

        rawDamage -= resistedDamage

        if rawDamage > 0:
            accumulatedDamage += rawDamage

    return accumulatedDamage


if __name__ == '__main__':
    # weapons_file = sys.argv[1]
    ctd = {
        'itemDmg': 14,
        'ammoDiv': 1,
        'ammoMult': 1,
        'drAdjust': 7,
    }
    armors = [[0,0],[0,20],[2,25],[2,30],[4,30],[4,35],[4,35],[6,40],[6,45],[8,45],[10,50],[12,50],[14,65],[14,70],[20,70]]
    ammos = [['10mm JHP',0,4,3],['10mm AP',5,1,1]]
    rounds = 1
    bonusDmg = 0

    # armorDT = 6
    # armorDR = 40
    # print(str(DamageYAAM(ctd, 0, rounds, armorDT, armorDR, bonusDmg, 2, 100)))

    s = "{:<10}".format("DT:")
    for dtdr in armors:
        s += "{:>5}".format(dtdr[0])
    print(s)

    s = "{:<10}".format("DR:")
    for dtdr in armors:
        s += "{:>5}".format(dtdr[1])
    print(s)

    for ammo in ammos:
        s = "{:<10}".format(ammo[0])
        ctd['drAdjust'] = ammo[1]
        ctd['ammoMult'] = ammo[2]
        ctd['ammoDiv'] = ammo[3]
        for dtdr in armors:
            s+= "{:>5}".format(DamageYAAM(ctd, 0, rounds, dtdr[0], dtdr[1], bonusDmg, 2, 100))
        print(s)
