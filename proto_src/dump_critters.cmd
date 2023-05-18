@ECHO OFF
cd /d "%~dp0"
if not exist "critters" mkdir critters
SET out_path=%cd%\critters
SET script_path=%cd%\harold_proto.py

goto vanilla

cd ..\root\data\proto\critters
for /r %%i in (*.pro) do (
    "%script_path%" "%%~fi" > %out_path%\%%~ni.json
)


rem cd /d D:\GAMES\!Arhives\Fallout\VANILLA\proto\CRITTERS\

:vanilla

cd /d C:\Projects\fo2_rp\data\proto\critters\

for /r %%i in (*.pro) do (
    "%script_path%" "%%~fi" > ..\critters_json\%%~ni.json
)