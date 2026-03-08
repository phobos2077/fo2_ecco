@ECHO OFF

SET cwd=%cd%

cd /d "%~dp0"
if not exist "critters" mkdir critters

py parse_critters.py ..\root\data\proto\critters\ -o critters\

rem SET out_path=%cd%\critters
rem SET script_path=%cd%\harold_proto.py


rem goto vanilla

rem cd ..\root\data\proto\critters
rem for /r %%i in (*.pro) do (
rem    py "%script_path%" "%%~fi" > %out_path%\%%~ni.json
rem )

goto end

rem cd /d D:\GAMES\!Arhives\Fallout\VANILLA\proto\CRITTERS\

:vanilla

cd /d C:\Projects\fo2_rp\data\proto\critters\

for /r %%i in (*.pro) do (
    py "%script_path%" "%%~fi" > ..\critters_json\%%~ni.json
)

:end

cd /d "%cwd%"
exit /b
