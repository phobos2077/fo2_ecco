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
    let response = await fetch(file, {cache: "no-cache"});
    let csvString = await response.text();
    return csvToArrayOfObjects(csvString, ";");
}

const csvNormalToShortDamageTypes = [
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
damageTypes = csvNormalToShortDamageTypes.map(t => t[0]);

loadDataFromCsv = async function(dataSet) {
    console.log(`Loading dataset ${dataSet.name}...`);

    const ignoreArmorKewords = ["Mutant", "Environmental", "K-9", "Bridgekeeper"];
    function loadDtDrLists(entity) {
        if (dataSet.splitDtDr) {
            return [
                csvNormalToShortDamageTypes.map(t => parseInt(entity[t[1]+" DT"])),
                csvNormalToShortDamageTypes.map(t => parseInt(entity[t[1]+" DR"]))
            ]
        }
        const dt = [], dr = [];
        damageTypes.forEach(dmgType => {
            let values = entity[dmgType + " DT|DR"];
            if (values) {
                values = values.split("|").map(v => parseInt(v));
                dt.push(values[0]);
                dr.push(values[1]);
            } else {
                dt.push(0);
                dr.push(0);
            }
        });
        return [dt, dr];
    }
    armors = (await csvFileToArrayOfObjects(dataSet.getPath("armor"))).map(ar => {
        const dtDr = loadDtDrLists(ar);
        return {
            name: ar["NAME"].replace(/Jacket/i,"Jck").replace(/Hardened/i,"Hrd").replace(/Advanced/i,"Adv").replace(/\s*Armor/i,"").replace(/Mark\s+/i,"MK"),
            ac: ar["Armor Class"],
            dt: dtDr[0],
            dr: dtDr[1],
        };
    })
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

        const dtDr = loadDtDrLists(cr);
        armors.push({
            name: cr["NAME"],
            type: "critter",
            ac: cr["Armor Class"],
            dt: dtDr[0],
            dr: dtDr[1]
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