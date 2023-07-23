@echo off
rem Compile script using watcom preprocessor

rem echo 1=%1 2=%2 3=%3 4=%4 5=%5 6=%6 7=%7 8=%8 9=%9

set sce=
echo %~n3 | findstr /i /r "^hs_ ^gl_ ^test[0-9]" >nul && (
   echo Compiling with short-circuit evaluation!
   set sce=-s
)
set out=
if not "%3"=="" set out=-o %3

wcc386.exe %1 -plw=0 -fo="%~nx1.i" -w4 -wcd123 -wcd138
rem if errorlevel 1 exit /b %errorlevel%
echo compile.exe -q -l -O2 %sce% "%~nx1.i" %out%
compile.exe -q -l -O2 %sce% "%~nx1.i" %out%
SET compileErr=%ERRORLEVEL%
del "%~nx1.i"
if exist "%~nx1.err" del "%~nx1.err"
exit /B %compileErr%
