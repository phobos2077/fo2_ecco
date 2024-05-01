@ECHO OFF

rem Used to batch recompile scripts previously decompiled with decompile_folder

set compile=%~dp0compile.exe
set output=..\

for %%i in (*.ssl) do (
    "%compile%" -l -O0 -q -n "%%~nxi" -o "%output%/%%~ni.int"
)

:end
