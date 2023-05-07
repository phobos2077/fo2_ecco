@ECHO OFF
SET OUTDIR=..\..\@RP\data\scripts\
..\compile.exe -p acmynoc.ssl -o %OUTDIR%acmynoc.int dcsmitty.ssl -o %OUTDIR%dcsmitty.int dcvic.ssl -o %OUTDIR%dcvic.int gcskeetr.ssl -o %OUTDIR%gcskeetr.int rcdrjohn.ssl -o %OUTDIR%rcdrjohn.int VCDRTROY.ssl -o %OUTDIR%VCDRTROY.int mcBaltha.ssl -o %OUTDIR%mcBaltha.int
pause
cls