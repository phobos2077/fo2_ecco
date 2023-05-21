
function clearGraph() {
    drawGraph();
}

/**
 * @param {number} selectedDmg
 * @param {Armor} selectedArmorIdx
 * @param {DamageContext} dmgCtx
 */
function drawGraph(selectedDmg, selectedArmorIdx, dmgCtx) {
    //console.log("drawGraph", dmg, dataRow);
    /**
     * @type HTMLCanvasElement
     */
    const legendWidth = 120;
    const canvas = document.getElementById("graph");
    canvas.width = document.getElementById("results").clientWidth + legendWidth;
    const ctx = canvas.getContext("2d");
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    if (!selectedDmg || !dmgCtx.calculated) return;

    const margin = 25;
    const top = margin;
    const left = margin;
    const right = canvas.width - margin - legendWidth;
    const bottom = canvas.height - margin;
    const width = right - left;
    const height = bottom - top;

    const maxDmg = Math.max(dmgCtx.maxFinalDmg, dmgCtx.weapon.dmgMax * dmgCtx.rounds);
    function damageToY(dmg) {
        return bottom - dmg / maxDmg * height;
    }
    function drawText(text, x, y, align, size, color) {
        ctx.font = `${size || 12}px arial`;
        ctx.textAlign = align || "center";
        ctx.fillStyle = color || "black";
        ctx.fillText(text, x, y);
    }
    const dmgLines = [];
    function addDmgLine(value) {
        const y = damageToY(value);
        if (dmgLines.some(ly => Math.abs(y - ly) < 10)) return;
        dmgLines.push(y);

        ctx.beginPath();
        ctx.lineWidth = 1;
        ctx.strokeStyle = "#bbb";
        ctx.moveTo(left, y);
        ctx.lineTo(right, y);
        ctx.stroke();

        drawText(value.toFixed(), left, y);
    }
    const colors = ["red", "blue", "green", "purple", "orange"];
    const dataRows = dmgCtx.calculated.map(mapByDamage => mapByDamage.get(selectedDmg));
    //const avgDmg = dataRows.reduce((sum, row) => sum + row.reduce((a, b) => a + b, 0) / row.length, 0) / dataRows.length;
    addDmgLine(0);
    addDmgLine(selectedDmg * dmgCtx.rounds);
    for (let row of dataRows) {
        addDmgLine(row[selectedArmorIdx]);
    }
    //addDmgLine(avgDmg);
    addDmgLine(dmgCtx.weapon.dmgMin * dmgCtx.rounds);
    addDmgLine(dmgCtx.weapon.dmgMax * dmgCtx.rounds);
    addDmgLine(dmgCtx.maxFinalDmg);
    addDmgLine(maxDmg);

    const legendItemWidth = 50;
    const legendInterval = 30;
    const legendHeight = legendInterval * dataRows.length;
    
    const legendX = canvas.width - legendWidth + margin;
    let legendY = (canvas.height - legendHeight) / 2;

    // Draw graphs.
    dataRows.forEach((dataRow, i) => {
        ctx.beginPath();
        ctx.lineWidth = 2;
        ctx.strokeStyle = colors[i % colors.length];
        let x = left + 50,
            y = damageToY(dataRow[0]);
        ctx.moveTo(x, y);
        ctx.arc(x, y, 3, 0, 360);
        const stepX = 50; //width / dataRow.length;
        for (let i = 1; i < dataRow.length; i++) {
            x += stepX;
            y = damageToY(dataRow[i]);

            ctx.lineTo(x, y);
            ctx.arc(x, y, 3, 0, 360);
            //console.log(margin + stepX * i, damageToY(dataRow[i]));
        }
        // Legend
        ctx.moveTo(legendX, legendY);
        ctx.arc(legendX, legendY, 3, 0, 360);
        ctx.lineTo(legendX + legendItemWidth, legendY);
        drawText(dmgCtx.calculatedAmmoTypes[i].name, legendX + legendItemWidth / 2, legendY - 5);
        legendY += legendInterval;

        ctx.stroke();
        ctx.closePath();
    });
}
