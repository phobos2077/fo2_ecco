@ECHO OFF

SET cwd=%cd%

cd /d "%~dp0..\"

SET root=%cd%
SET output=root\data\scripts\
if not exist "%output%" mkdir %output%
cd /d "%output%"
SET output=%cd%

SET compile=%root%\extra\bin\compile.exe

cd /d "%root%/scripts_src"

for /r %%i in (*.ssl) do (
    echo %%~dpi | findstr /v /i "\\tests\\ \\wip\\ zilocker" >nul && (
        cd /d "%%~dpi"
        "%compile%" -l -O2 -p -s -q -n "%%~nxi" -o "%output%/%%~ni.int"
    )
)

:end

cd /d "%cwd%"
