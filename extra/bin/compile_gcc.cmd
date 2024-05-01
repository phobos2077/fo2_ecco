@echo off
rem Compile script using gcc preprocessor

rem echo 1=%1 2=%2 3=%3 4=%4 5=%5 6=%6 7=%7 8=%8 9=%9

set sce=
echo %~n3 | findstr /i /r "^hs_ ^gl_ ^test[0-9]" >nul && (
   echo Compiling with short-circuit evaluation!
   set sce=-s
)
set out=
if not "%3"=="" set out=-o %3

gcc -E -x c -P -Werror -Wfatal-errors -o "%~nx1.tmp" "%1"
rem if errorlevel 1 exit /b %errorlevel%
echo compile.exe -q -l -O2 %sce% "%~nx1.tmp" %out%
compile.exe -q -l -O2 %sce% "%~nx1.tmp" %out%
SET compileErr=%ERRORLEVEL%
del "%~nx1.tmp"
if exist "%~n1.err" del "%~n1.err"
exit /B %compileErr%
