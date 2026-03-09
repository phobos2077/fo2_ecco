@ECHO OFF

rem Setup folders

SET cwd=%cd%

cd /d "%~dp0..\"

SET root=%cd%

cd /d "%cwd%"

set modName=%1
if "%modName%"=="" set modName=lite

echo Mod Name = %modName%
if "%modName%"=="lite" goto lite
if "%modName%"=="weapon_sfx" goto weapon_sfx

echo Mod '%1' doesn't exist!
goto quit_with_error

:lite

set modFolder=ecco_lite

cd /d "%root%\scripts_src\_pbs_main"
set scriptOutPath=%root%\separate_mods\%modName%\mods\%modFolder%\scripts

for /f "usebackq delims=" %%f in ("%root%\extra\ecco_lite_script_list.txt") do (
   echo Processing %%f
   call compile_wcc "%%f.ssl" -o "%scriptOutPath%\%%f.int"
   if errorlevel 1 goto quit_with_error
)

goto make_zip_no_dat


:weapon_sfx

SET modFolder=weapon_sfx_variation
SET datInputList=config\* scripts\*

echo Compiling weapon sfx script...

SET scriptName=gl_weapon_sfx_variation

cd /d "%root%\scripts_src\_pbs_main"
SET scriptOutPath=%root%\separate_mods\%modName%\mods\%modFolder%\scripts\%scriptName%.int

call compile_wcc "%scriptName%.ssl" -o "%scriptOutPath%"
set compileErr=%errorlevel%
cd /d "%cwd%"
if %compileErr% geq 1 goto quit_with_error

goto make_zip_no_dat
rem goto make_dat
quit_with_error

:compile_script
rem "%compile%" -l -O2 -p -s -q -n "%%~nxi" -o "%output%/%%~ni.int"
call compile_wcc "%1.ssl" -o "%scriptOutPath%/%1.int"
set compileErr=%errorlevel%
if %compileErr% geq 1 (
   set /a ne+=1 >nul
) else (
   set /a ns+=1 >nul
)
exit /B %compileErr%


:make_dat

echo Building DAT for mod '%modName%'...

SET datFile=fo2_%modFolder%.dat
SET datFilePath=%root%\separate_mods\%datFile%

if exist %datFilePath% (
   echo Deleting existing %datFilePath%...
   del %datFilePath%
)

cd /d "%root%\separate_mods\%modName%\mods\%modFolder%"
rem echo CD=%cd%
%root%\extra\bin\dat2.exe a -r %datFile% %datInputList%
move %datFile% %root%\separate_mods\

cd /d "%cwd%"
echo Done!

exit /B


:make_zip_no_dat

echo Building ZIP for mod '%modName%'...

SET zipFile=fo2_%modFolder%.zip
SET zipFilePath=%root%\separate_mods\%zipFile%

if exist %zipFilePath% (
   echo Deleting existing %zipFilePath%...
   del %zipFilePath%
)

cd /d "%root%\separate_mods\%modName%"

echo Running 7Zip...
set exe="C:\Program Files\7-Zip\7z.exe"
%exe% a %zipFilePath% mods\* ecco_config\* sfall\* *.txt > nul

cd /d "%cwd%"
echo Done!

exit /B


:quit_with_error

cd /d "%cwd%"
echo Build failed!
exit /B 1

