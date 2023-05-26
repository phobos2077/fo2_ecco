(function() {

function random(min, max) {
    return Math.floor(Math.random() * (max - min + 1) + min);
}

dummyAmmo = {
    name: "None",
    acAdj: 0,
    drAdj: 0,
    dmgMult: 1,
    dmgDiv: 1,
};

var vanillaFormula = {
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
            damage = (((damage / 2 >> 0) * ctx.difficulty) / 100 >> 0) - dmgThresh;
            if (damage > 0) {
                damage = damage - ((damage * dmgResist) / 100 >> 0);
                if (damage > 0)
                    totalDmg += damage;
            }
        }
        return totalDmg;
    },
    rawDmg: function(ctx) {
        return ctx.rawDmg ? ctx.rawDmg : random(ctx.weapon.dmgMin, ctx.weapon.dmgMax);
    },
    dtdrBeforeAmmo(ctx, noBypass) {
        let dt = ctx.armor.dt[ctx.dmgTypeIdx];
        let dr = ctx.armor.dr[ctx.dmgTypeIdx];
        if (ctx.crit.bypass && ctx.dmgType != "EMP" && !noBypass) {
            dt = Math.floor(dt * 20 / 100)
            dr = Math.floor(dr * 20 / 100)
        } else if (ctx.weapon.penetrate) {
            dt = Math.floor(dt * 20 / 100)
        }
        return [dt, dr];
    },
    dtdr: function(ctx) {
        let dt, dr;
        [dt, dr] = this.dtdrBeforeAmmo(ctx);
        if (ctx.ammo) {
            dr += ctx.ammo.drAdj;
        }
        return [dt, Math.max(Math.min(dr, 100), 0)];
    },
    rateArmor(armor, ctx) {
        return armor.dr[ctx.dmgTypeIdx] + armor.dt[ctx.dmgTypeIdx] * 4;
    }
};

var glovzFormula = {
    ...vanillaFormula,
    name: "Glovz v5.1",
    dmg: function(ctx) {
        let calcDT, calcDR, armorDT, armorDR;
        [calcDT, calcDR, armorDT, armorDR] = this.dtdr(ctx);

        let ammo = ctx.ammo || dummyAmmo;
        let ammoY = Math.max(ammo.dmgDiv, 1);
        let ammoX = Math.max(ammo.dmgMult, 1);

        let accumulatedDamage = 0;
        for (let i = 1; i <= ctx.rounds; i++) {
            let rawDamage = this.rawDmg(ctx)
            rawDamage += ctx.bonusRanged;
            if (rawDamage <= 0) continue;
            if (armorDT > 0) {
                rawDamage -= calcDT;
                if (rawDamage <= 0) continue;
            }
            if (armorDR > 0) {
                let resistedDamage = calcDR * rawDamage;
                resistedDamage = this.divRound(resistedDamage, 100);
                rawDamage -= resistedDamage;
                if (rawDamage <= 0) continue;
            }
            // bonus damage to unarmored target
            if (armorDT <= 0 && armorDR <= 0) {
                if (ammoX > 1 && ammoY > 1) {                   // FMJ/high-end
                    rawDamage += this.divRound(rawDamage * 15, 100);
                } else if (ammoX > 1) {                         // JHP
                    rawDamage += this.divRound(rawDamage * 20, 100);
                } else if (ammoY > 1) {                         // AP
                    rawDamage += this.divRound(rawDamage * 10, 100);
                }
            }

            // v5.1 tweak
            rawDamage += this.divRound(rawDamage * ctx.crit.mult * 25, 100); // goto divSeven
            if (rawDamage > 0) accumulatedDamage += rawDamage;  // accumulate damage (make sure the result > 0 before adding)
        }
        return accumulatedDamage;
    },
    dtdr: function(ctx) {
        let dt, dr;
        [dt, dr] = this.dtdrBeforeAmmo(ctx);
        const ammo = ctx.ammo || dummyAmmo;
        let ammoY = Math.max(ammo.dmgDiv, 1);
        let ammoX = Math.max(ammo.dmgMult, 1);

        let ammoDRM = ammo.drAdj;
        if (ammoDRM > 0) ammoDRM = -ammoDRM;

        const calcDT = (dt > 0) ? this.divRound(dt, ammoY) : dt;
        let calcDR = dr;
        if (calcDR > 0) {
            if (ctx.difficulty > 100) {
                calcDR -= 20;
            } else if (ctx.difficulty < 100) {
                calcDR += 20;
            }
            calcDR += ammoDRM;
            calcDR = this.divRound(calcDR, ammoX);
            if (calcDR >= 100) {
                calcDR = 100;
            }
        }
        return [calcDT, calcDR, dt, dr];
    },
    divRound: function(dividend, divisor) {
        if (dividend <= divisor) {
            // if equal then return 1
            return (dividend != divisor && (dividend << 1) <= divisor) ? 0 : 1;
        }
        const quotient = dividend / divisor >> 0; // integer division
        dividend %= divisor; // get the remainder
        // check the remainder
        if (dividend == 0) return quotient;
    
        dividend <<= 1; // multiply by 2
    
        // if equal then round to even
        return (dividend > divisor || (dividend == divisor && (quotient & 1))) ? (quotient + 1) : quotient;
    }
};

var yaamFormula = {
    ...vanillaFormula,
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
    dtdr: function(ctx) {
        let dt, dr;
        [dt, dr] = this.dtdrBeforeAmmo(ctx);
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
    }
};

var eccoFormula = {
    ...vanillaFormula,
    name: "EcCo (DT add-, mult+)",
    dtMultNegative: 1.3,
    dtMultPositive: 2,
    burstCriticalFraction: 0.5,
    dmg: function(ctx) {
        let dmgThresh, dmgResist;
        [dmgThresh, dmgResist] = this.dtdr(ctx);

        const ammo = ctx.ammo || dummyAmmo;
        const staticMult = ctx.difficulty * ammo.dmgMult / ammo.dmgDiv / 100;
        let criticalMult = 0.5 * ctx.crit.mult;
        const criticalRounds = Math.max(Math.round(this.burstCriticalFraction * ctx.rounds), 1);

        let totalDmg = 0;
        for (let i = 0; i < ctx.rounds; i++) {
            // After bullet fraction, don't allow any more criticals, to make bursts less OP.
            if (i == criticalRounds) {
                if (ctx.crit.bypass) {
                    [dmgThresh, dmgResist] = this.dtdr(ctx, true);
                }
                if (criticalMult > 1) {
                    criticalMult = 1;
                }
            }

            let damage = this.rawDmg(ctx) + ctx.bonusRanged - dmgThresh;
            if (damage <= 0) continue;

            damage = Math.round(damage * staticMult * (1 - dmgResist / 100.0) * criticalMult * 10) / 10;
            if (damage > 0)
                totalDmg += damage;
        }
        return totalDmg;
    },
    dtdr: function(ctx, noBypass) {
        let dt, dr;
        [dt, dr] = this.dtdrBeforeAmmo(ctx, noBypass);
        if (ctx.ammo) {
            const drAdj = ctx.ammo.drAdj;
            if (drAdj < 0) {
                dt += drAdj * this.dtMultNegative / 10;
            } else if (drAdj > 0) {
                dt *= 1 + drAdj * this.dtMultPositive / 100;
            }
            dr += drAdj;
        }
        return [Math.max(dt, 0), Math.max(Math.min(dr, 100), 0)];
    },
    decimals: 1
};

var eccoFormula2 = {
    ...eccoFormula,
    name: "EcCo (DT mult)",
    dtMultPositive: 2,
    dtMultNegative: 1.3,
    dtdr: function(ctx, noBypass) {
        let dt, dr;
        [dt, dr] = this.dtdrBeforeAmmo(ctx, noBypass);
        if (ctx.ammo) {
            const drAdj = ctx.ammo.drAdj;
            if (drAdj > 0) {
                dt *= 1 + drAdj * this.dtMultPositive / 100;
            } else if (drAdj < 0) {
                dt *= 1 + drAdj * this.dtMultNegative / 100;
            }
            dr += drAdj;
        }
        return [Math.max(dt, 0), Math.max(Math.min(dr, 100), 0)];
    }
};


damageFormulas = [
    vanillaFormula,
    glovzFormula,
    yaamFormula,
    eccoFormula,
    eccoFormula2,
    {
        ...vanillaFormula,
        name: "Dummy",
        dmg: function(ctx) {
            return ctx.rawDmg;
        },
        dtdr: function(ctx) {
            return [ctx.armor.dt[ctx.dmgTypeIdx], ctx.armor.dr[ctx.dmgTypeIdx]];
        }
    },
];

})();