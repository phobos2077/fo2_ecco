@ECHO OFF
SET OUTDIR=..\..\@RP\data\scripts\
..\compile.exe -p OBJ_DUDE.ssl -o %OUTDIR%OBJ_DUDE.int gl_fixit.ssl -o %OUTDIR%gl_fixit.int
pause
cls