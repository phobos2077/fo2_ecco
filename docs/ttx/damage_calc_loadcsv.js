(function(){

function csvToArrayOfObjects(csvString, sep) {
    let rows = csvString.split("\n");
    let headers = rows[0].split(sep).map(s => s.trim());
    let result = [];
    for (let i = 1; i < rows.length; i++) {
        let row = rows[i].split(sep);
        if (row.length == 1 && !row[0].trim()) continue;
        let obj = {};
        for (let j = 0; j < headers.length; j++) {
            obj[headers[j]] = (row[j] ? row[j].trim() : "");
        }
        result.push(obj);
    }
    return result;
}

async function csvFileToArrayOfObjects(file) {
    let response = await fetch(file);
    let csvString = await response.text();
    return csvToArrayOfObjects(csvString, ";");
}

const csvAmmoToArmorDamageTypes = [
    ["Normal", "Norm"],
    ["Laser", "Lasr"],
    ["Fire", "Fire"],
    ["Plasma", "Plas"],
    ["Electrical", "Elec"],
    ["Explode", "Expl"],
    ["EMP", "EMP"]
];

/**
 * @type string[]
 */
damageTypes = csvAmmoToArmorDamageTypes.map(t => t[0]);

loadDataFromCsv = async function(dataSet) {
    console.log(`Loading dataset ${dataSet.name}...`);

    const ignoreArmorKewords = ["Mutant", "Environmental", "K-9", "Bridgekeeper"];
    armors = (await csvFileToArrayOfObjects(dataSet.getPath("armor"))).map(ar => ({
        name: ar["NAME"].replace(/Jacket/i,"Jck").replace(/Hardened/i,"Hrd").replace(/Advanced/i,"Adv").replace(/\s*Armor/i,"").replace(/Mark\s+/i,"MK"),
        ac: ar["Armor Class"],
        dt: csvAmmoToArmorDamageTypes.map(t => parseInt(ar[t[1]+" DT"])),
        dr: csvAmmoToArmorDamageTypes.map(t => parseInt(ar[t[1]+" DR"])),
    }))
        .filter(armor =>
            ignoreArmorKewords.every(kw => armor.name.indexOf(kw) == -1) &&
            (armor.dt.some(v => v > 0) || armor.dr.some(v => v > 0)));

    armors.push({
        name: "None",
        type: "none",
        ac: 0,
        dt: damageTypes.map(t => 0),
        dr: damageTypes.map(t => 0),
    });

    const crittersByProto = (await csvFileToArrayOfObjects(dataSet.getPath("critter"))).reduce((o, critter) => {
        o[critter["ProFILE"]] = critter;
        return o;
    });
    function tryAddCritter(proto) {
        var cr = crittersByProto[proto];
        if (!cr) return;

        armors.push({
            name: cr["NAME"],
            type: "critter",
            ac: cr["Armor Class"],
            dt: csvAmmoToArmorDamageTypes.map(t => parseInt(cr[t[1]+" DT"])),
            dr: csvAmmoToArmorDamageTypes.map(t => parseInt(cr[t[1]+" DR"]))
        });
    }
    tryAddCritter("00000288.pro"); // Horrigan
    tryAddCritter("00000242.pro"); // Wanamingo
    tryAddCritter("00000245.pro"); // Tough Deathclaw

    ammoTypes = (await csvFileToArrayOfObjects(dataSet.getPath("ammo"))).map(a => ({
        name: a["NAME"],
        caliber: a["Caliber"],
        acAdj: parseInt(a["AC Adjust"]),
        drAdj: parseInt(a["DR Adjust"]),
        dmgMult: parseInt(a["Dam Mult"]),
        dmgDiv: parseInt(a["Dam Div"]),
    }));
    weapons = (await csvFileToArrayOfObjects(dataSet.getPath("weapon"))).map(a => ({
        name: a["NAME"],
        caliber: parseInt(a["Max Ammo"]) > 0 ? a["Caliber"] : null,
        dmgType: damageTypes.indexOf(a["Damage Type"]),
        dmgMin: parseInt(a["Min Damage"]),
        dmgMax: parseInt(a["Max Damage"]),
        penetrate: a["Perk"] == "Weapon Penetrate [60]",
        burst: parseInt(a["Rounds Brust"])
    }));
    weapons.sort((a, b) => a.name > b.name);

    console.log(`Loaded ${armors.length} armors, ${ammoTypes.length} ammo types, ${weapons.length} weapons.`);
}

})();