@ECHO OFF
setlocal EnableExtensions

set cwd=%cd%
cd /d "%~dp0..\"

set root=%cd%
set archive=%root%\extra\pbs_fo2rpu_ecco_mod_v0-9-6.zip

if exist %archive% (
   echo Deleting existing %archive%...
   del %archive%
)

set exe="C:\Program Files (x86)\7-Zip\7z.exe"

echo Adding mod files...
cd /d %root%\root
%exe% a %archive% mods\* sfall\* > nul

echo Adding docs...
cd /d %root%\docs
%exe% a %archive% ecco_readme.txt ecco_changelog.txt > nul

echo Done!

cd /d "%cwd%"
