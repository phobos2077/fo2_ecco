@ECHO OFF

SET cwd=%cd%

cd /d "%~dp0..\"

SET root=%cd%
SET output=%root%\root\data\scripts\
if not exist "%output%" mkdir %output%

SET compile=%root%\extra\bin\compile.exe

cd /d "%cwd%"
echo Output= %output%/%~n1.int
"%compile%" -l -O2 -p -s -q -n "%~nx1" -o "%output%/%~n1.int"

:end
