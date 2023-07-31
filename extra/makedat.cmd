@ECHO OFF

SET cwd=%cd%

cd /d "%~dp0..\"

SET root=%cd%
SET mainDat=rpu_y_ecco.dat

if exist %mainDat% del %mainDat%

cd /d "%root%\root\data"
%root%\extra\bin\dat2.exe a -r %mainDat% art\* config\* data\* maps\* pcx\* proto\* scripts\* sound\* text\*
move %mainDat% %root%\root\mods\

cd /d "%cwd%"
