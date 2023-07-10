@ECHO OFF

set int2ssl=%CD%\bin\int2ssl.exe

cd ..\root\data\scripts
mkdir _dump

for /f "tokens=* delims=" %%I in ('dir *.int /b') do (
	%int2ssl% -d "%%I"
	move /Y %%~nI.dump _dump\
)

echo Done!
pause
