
function random(min, max) {
    return Math.floor(Math.random() * (max - min + 1) + min);
}

const damageFormulas = [
    {
        name: "Vanilla",
        dmg: function(ctx) {
            let dmgResist = this.dr(ctx);
            let dmgThresh = this.dt(ctx);

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
        dr: function(ctx) {
            let dr = ctx.armor.dr[ctx.dmgTypeIdx];
            if (ctx.crit.bypass) {
                dr = Math.floor(dr * 20 / 100)
            }
            if (ctx.ammo) {
                dr += ctx.ammo.drAdj;
            }
            return Math.max(Math.min(dr, 100), 0);
        },
        dt: function(ctx) {
            let dt = ctx.armor.dt[ctx.dmgTypeIdx];
            if (ctx.weapon.penetrate || ctx.crit.bypass) {
                dt = Math.floor(dt * 20 / 100)
            }
            return dt;
        }
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