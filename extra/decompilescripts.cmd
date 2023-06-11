@ECHO OFF

set int2ssl=%CD%\bin\int2ssl.exe

cd ..\root\data\scripts
mkdir _ssl

for /f "tokens=* delims=" %%I in ('dir *.int /b') do (
	if not %%~nI==bhrnddst (
		%int2ssl% -s3 -c "%%I"
		move /Y %%~nI.ssl _ssl\
	)
)

echo Done!
pause
cls