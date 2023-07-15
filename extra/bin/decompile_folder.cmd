@ECHO OFF

set int2ssl=int2ssl.exe

mkdir _ssl

for /f "tokens=* delims=" %%I in ('dir *.int /b') do (
	%int2ssl% -s3 -c "%%I"
	move /Y %%~nI.ssl _ssl\
)

echo Done!
pause
