@ECHO OFF

set compile=%~dp0compile.exe
set output=%~dp0..\..\root\data\scripts\

for %%i in (*.ssl) do (
    "%compile%" -l -O2 -p -s -q -n "%%~nxi" -o "%output%/%%~ni.int"
)

:end
