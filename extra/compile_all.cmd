@ECHO OFF
setlocal EnableExtensions

SET cwd=%cd%

cd /d "%~dp0..\"

SET root=%cd%
SET output=root\data\scripts\
if not exist "%output%" mkdir %output%
cd /d "%output%"
SET output=%cd%

rem SET compile=%root%\extra\bin\compile.exe

cd /d "%root%/scripts_src"

set /a ns=0 >nul
set /a ne=0 >nul
for /r %%i in (*.ssl) do echo %%~dpi | findstr /v /i "\\tests\\ \\wip\\" >nul && (
    rem echo %%~ni
    call :RunCompile "%%~i"
    if errorlevel 1 goto Done
)

:Done

rem This does not work...
echo Compiled %ns% scripts. Errors in %ne% scripts.

cd /d "%cwd%"
exit /b


:RunCompile
cd /d "%~dp1"
rem "%compile%" -l -O2 -p -s -q -n "%%~nxi" -o "%output%/%%~ni.int"
call compile_wcc "%~nx1" -o "%output%/%~n1.int"
set compileErr=%errorlevel%
if %compileErr% geq 1 (
    set /a ne+=1 >nul
) else (
    set /a ns+=1 >nul
)
exit /B %compileErr%
