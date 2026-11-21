@ECHO OFF
setlocal EnableExtensions

rem Usage: build_zip.cmd <version>   (e.g. build_zip.cmd 1-0-1)
if "%~1"=="" (
   echo Usage: %~nx0 ^<version^>   e.g. %~nx0 1-0-1
   exit /b 1
)

set cwd=%cd%
cd /d "%~dp0..\"

set root=%cd%
set archive=%root%\extra\pbs_fo2rpu_ecco_mod_v%~1.zip

if exist "%archive%" (
   echo Deleting existing %archive%...
   del "%archive%"
)

set exe="C:\Program Files\7-Zip\7z.exe"

echo Adding mod files...
cd /d "%root%\root"
%exe% a "%archive%" mods\* sfall\* ecco_config\* > nul
if errorlevel 1 goto error

echo Adding docs...
cd /d "%root%\docs"
%exe% a "%archive%" ecco_readme.md ecco_changelog.txt > nul
if errorlevel 1 goto error

echo Done!
cd /d "%cwd%"
exit /b 0

:error
echo Build failed!
cd /d "%cwd%"
exit /b 1
