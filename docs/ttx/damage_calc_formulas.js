(function() {

function random(min, max) {
    return Math.floor(Math.random() * (max - min + 1) + min);
}

function getDtDrAfterVanillaBypass(ctx) {
    let dt = ctx.armor.dt[ctx.dmgTypeIdx];
    let dr = ctx.armor.dr[ctx.dmgTypeIdx];
    if (ctx.crit.bypass && ctx.dmgType != "EMP" ) {
        dt = Math.floor(dt * 20 / 100)
        dr = Math.floor(dr * 20 / 100)
    } else if (ctx.weapon.penetrate) {
        dr = Math.floor(dr * 20 / 100)
    }
    return [dt, dr];
}

let dummyAmmo = {
    acAdj: 0,
    drAdj: 0,
    dmgMult: 1,
    dmgDiv: 1,
}

damageFormulas = [
    {
        name: "Vanilla",
        dmg: function(ctx) {
            let dmgThresh, dmgResist;
            [dmgThresh, dmgResist] = this.dtdr(ctx);

            let ammo = ctx.ammo || dummyAmmo;
            let dmgMult = ctx.crit.mult * ammo.dmgMult;
            let dmgDiv = ammo.dmgDiv;

            let totalDmg = 0;
            for (let i = 1; i <= ctx.rounds; i++) {
                let damage = (this.rawDmg(ctx) + ctx.bonusRanged) * dmgMult;
                if (dmgDiv != 0) damage /= dmgDiv;
                damage = Math.floor((Math.floor(damage / 2) * ctx.difficulty) / 100) - dmgThresh;
                if (damage > 0) {
                    damage = damage - Math.floor((damage * dmgResist) / 100);
                    if (damage > 0)
                        totalDmg += damage;
                }
            }
            return totalDmg;
        },
        rawDmg: function(ctx) {
            return ctx.rawDmg ? ctx.rawDmg : random(ctx.weapon.dmgMin, ctx.weapon.dmgMax);
        },
        dtdr: function(ctx) {
            let dt, dr;
            [dt, dr] = getDtDrAfterVanillaBypass(ctx);
            if (ctx.ammo) {
                dr += ctx.ammo.drAdj;
            }
            return [dt, Math.max(Math.min(dr, 100), 0)];
        },
        dt: function(ctx) { return this.dtdr(ctx)[0] },
        dr: function(ctx) { return this.dtdr(ctx)[1] }
    },
    {
        name: "YAAM",
        dmg: function(ctx) {
            let dmgThresh, dmgResist;
            [dmgThresh, dmgResist] = this.dtdr(ctx);

            let ammo = ctx.ammo || dummyAmmo;
            let dmgMult = ctx.crit.mult * ammo.dmgMult;
            let dmgDiv = ammo.dmgDiv;

            let totalDmg = 0;
            for (let i = 1; i <= ctx.rounds; i++) {
                let damage = this.rawDmg(ctx) + ctx.bonusRanged;
                damage -= dmgThresh;
                if (damage <= 0) continue;

                damage *= dmgMult;
                if (dmgDiv != 0) {
                    damage = Math.floor(damage / dmgDiv);
                }
                damage = Math.floor(damage / 2);
                damage *= ctx.difficulty;
                damage = Math.floor(damage / 100);

                damage -= Math.floor(damage * dmgResist / 100);
                if (damage > 0)
                    totalDmg += damage;
            }
            return totalDmg;
        },
        rawDmg: function(ctx) {
            return ctx.rawDmg ? ctx.rawDmg : random(ctx.weapon.dmgMin, ctx.weapon.dmgMax);
        },
        dtdr: function(ctx) {
            let dt, dr;
            [dt, dr] = getDtDrAfterVanillaBypass(ctx);
            if (ctx.ammo) {
                let calcDT = dt - ctx.ammo.drAdj;
                if (calcDT < 0) {
                    dt = 0;
                    dr += calcDT * 10;
                } else {
                    dt = calcDT;
                }
            }
            return [dt, Math.max(Math.min(dr, 100), 0)];
        },
        dt: function(ctx) { return this.dtdr(ctx)[0] },
        dr: function(ctx) { return this.dtdr(ctx)[1] },
    },
    {
        name: "Dummy",
        dmg: function(ctx) {
            return ctx.rawDmg;
        },
        dr: function(ctx) {
            return ctx.armor.dr[ctx.dmgTypeIdx];
        },
        dt: function(ctx) {
            return ctx.armor.dt[ctx.dmgTypeIdx];
        }
    },
];

})();