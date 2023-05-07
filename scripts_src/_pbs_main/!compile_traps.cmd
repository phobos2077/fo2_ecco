@ECHO OFF
SET OUTDIR=..\..\@RP\data\scripts\
..\compile.exe -p gl_traps.ssl -o %OUTDIR%gl_traps.int hs_removeinvenobj.ssl -o %OUTDIR%hs_removeinvenobj.int test2.ssl -o %OUTDIR%test2.int hs_movecost.ssl -o %OUTDIR%hs_movecost.int
pause
cls