@echo off
rem Compile script using watcom preprocessor

rem echo 1=%1 2=%2 3=%3 4=%4 5=%5 6=%6 7=%7 8=%8 9=%9

wcc386.exe %1 -plw=0 -fo="%~nx1.i" -w4 -wcd123 -wcd138
compile.exe -q -l -O2 -s "%~nx1.i" -o %3
SET compileErr=%ERRORLEVEL%
del "%~nx1.i"
exit %compileErr%
