@echo off

set baseCommit=161c736eb9ba3b1f39268d03cd4e3bda58c7694e
set retdir=%cd%

cd %~dp0

set output=diff_data
if exist "%output%" (
	echo Cleaning output folder...
	rmdir /s /q %output%
)
mkdir %output%

pushd data
set moddata=%cd%
popd
pushd ..\fo2_rp\data
set basedata=%cd%
popd

rem set moddata=data
rem set basedata=..\fo2_rp\data

echo Mod Data: %moddata%
echo Base Data: %basedata%

set /a num=0
setlocal EnableDelayedExpansion
rem call :process_abs_path "C:\Projects\fo2_rp_ecco\data\art\items\rifle bb.frm" 
rem echo Copyed=%ERRORLEVEL%

rem Use git diff to speed-up process for files in data folder.
for /f "delims=" %%i in ('git diff --name-only %baseCommit% -- data') do (
	echo %%i | findstr /i ".int .lst .frm .pro .txt .ini .msg" >nul && (
		echo git: %%i
		call :copy_abs_path "%cd%\%%i"
		set /a num+=1
	)
)

for /f "delims=" %%i in ('dir /s /a:-d-h /b "%moddata%\scripts"') do (
	call :process_abs_path "%%i"
	if errorlevel 1 (
		set /a num+=1
	)
)


rem for /f "delims=" %%i in ('dir /a:d-h /b "%moddata%"') do (
rem 	call :process_folder %%i
rem )

echo.
echo Copied %num% files.
rem del  tmp.txt

echo Packing dat...
cd %output%
dat2 a -r _test.dat *

cd /d %retdir%
exit /b


:copy_abs_path
set B=%~dp1
set relDir=!B:%moddata%\=!
call :copy "%relDir%" "%~nx1"
exit /b


:process_abs_path
set B=%~dp1
set relDir=!B:%moddata%\=!
call :process_file "%relDir%" "%~nx1"
exit /b %ERRORLEVEL%


:process_git_path
set B=%1
set abs=%cd%%1
set relDir=!B:data\=!
rem echo %relDir%%~nx1
call :process_abs_path "%relDir%" "%~nx1"
exit /b %ERRORLEVEL%


rem :process_folder
rem %1 - relative path to a subfolder
rem echo.
rem <nul set /p =
rem echo Processing folder %1 
rem dir /a:-d-h /b "%moddata%\%1" > tmp.txt 2>nul
rem for /f "delims=" %%i in (tmp.txt) do (
rem 	rem echo - %%i
rem 	call :process_file "%1\%%i" "%1"
rem ) 2>nul
rem for /f "delims=" %%i in ('dir /a:d-h /b "%moddata%\%1"') do (
rem 	call :process_folder %1\%%i
rem ) 2>nul
rem exit /b


:process_file
rem %1 - relative directory path
rem %2 - file name
setlocal EnableDelayedExpansion
set baseFile=%basedata%\%~1%~2
set modFile=%moddata%\%~1%~2
if exist "%baseFile%" (
	fc /b "%modFile%" "%baseFile%" >nul
	set fcErr=!ERRORLEVEL!
	if "!fcErr!" gtr "1" (
		echo FC error: !fcErr!
		echo Command: fc /b "%modFile%" "%baseFile%"
	) else if "!fcErr!" equ "1" (
		echo m: %~1%~2
		call :copy %1 %2
		exit /b 1
	)
) else (
	echo a: %~1%~2
	call :copy %1 %2
	exit /b 1
)
exit /b


:copy
rem %1 - relative directory path
rem %2 - file name
set dstDir=%output%\%~1
if not exist "%dstDir%" mkdir "%dstDir%"
set dstFile=%dstDir%%~2
set srcFile=%moddata%\%~1%~2
copy /y "%srcFile%" "%dstFile%" >nul
if errorlevel 1 (
	echo Error copying "%srcFile%" to "%dstFile%" !
)
exit /b


rem for /f "delims=" %%i in ('dir /a:-d-h /s /b "%moddata%"') do (
rem 	echo %%~nxi
rem 	if exist %basedata%\%%~nxi (
rem 		fc /b %moddata%\%%~nxi %basedata%\%%~nxi >nul 2>&1
rem 		if errorlevel 1 call :copy %%i
rem 	) else call :copy %%i
rem )