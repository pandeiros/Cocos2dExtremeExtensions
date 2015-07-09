@echo off
setlocal EnableDelayedExpansion

IF [%2]==[] (
    echo [ERROR] Insufficient arguments.
    echo Usage: install_build_win.bat  COCOS_VERSION  cocos_path_TO_COCOS_ROOT
    Exit /B
)

set version=%1
set cocos_path=%2
echo Version: %version%
echo Cocos path: %cocos_path%
IF [%3] NEQ [] echo Mode: %3%

IF NOT EXIST res (mkdir res)
copy /y "%~dp0..\proj.win32\res\game.ico" "res\game.ico"
copy /y "%~dp0..\proj.win32\game.rc" "game.rc"
copy /y "%~dp0..\proj.win32\resource.h" "resource.h"

IF NOT EXIST %version% (mkdir %version%)

:CONFIG
echo CONFIGURATION
call %cocos_path%/setup.py
set folder=%version%/PolyCocos_%version%

:COMPILATION
echo COMPILATION
IF NOT EXIST %folder% goto RECOMPILING
IF "%3" EQU "release" IF EXIST %version%/Release (goto OVERWRITE)
IF EXIST %version%/Debug (goto OVERWRITE)
goto RECOMPILING



:OVERWRITE
echo This version already exists. Do You want to recompile it again (y/[n])?
set /p comfirm=

IF "%comfirm%" NEQ "y" goto COPYING
IF [%comfirm%]==[] goto COPYING

:RECOMPILING
echo Compiling.....
IF EXIST %version%/PolyCocos_%version% (RD /S /Q "%version%/PolyCocos_%version%")

call %cocos_path%/tools/cocos2d-console/bin/cocos.py new -l cpp -p com.polygon.polycocos -d %~dp0%version%/ PolyCocos_%version%

IF "%3"=="release" (
    call %cocos_path%/tools/cocos2d-console/bin/cocos.py compile -s %~dp0%version%/PolyCocos_%version% -p win32 -m release
) ELSE (
    call %cocos_path%/tools/cocos2d-console/bin/cocos.py compile -s %~dp0%version%/PolyCocos_%version% -p win32 -m debug
)

:COPYING
echo COPYING LIBS
IF NOT [%3]==[] (
    IF "%3"=="release" (
        IF NOT EXIST "%version%/Release" (mkdir "%version%/Release")
        for /R "%folder%/proj.win32/Release.win32" %%f in (*.lib) do copy /y %%f "%version%/Release"
    )
) ELSE (
        IF NOT EXIST "%version%/Debug" (mkdir "%version%/Debug")
        for /R "%folder%/proj.win32/Debug.win32" %%f in (*.lib) do copy /y %%f "%version%/Debug"
)

echo PREPARING PROJECT FILE
copy /y "%~dp0..\proj.win32\PolyCocos.vcxproj" "PolyCocos_%version%.vcxproj"
set ps=%SystemRoot%\system32\WindowsPowerShell\v1.0\powershell.exe
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '<ProjectGuid>{11111111-2222-3333-4444-555555555555}</ProjectGuid>', '<ProjectGuid>{00000000-0000-0000-0000-000000000%version:~0,1%0%version:~2,1%}</ProjectGuid>' | Out-File PolyCocos_%version%.vcxproj"

%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '<!--RELEASE_LIBS--><AdditionalLibraryDirectories>', '<AdditionalLibraryDirectories>%version%/Release/;' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '<!--DEBUG_LIBS--><AdditionalLibraryDirectories>', '<AdditionalLibraryDirectories>%version%/Debug/;' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '<!--RELEASE_LOOP-->', 'for /R "$(ProjectDir)%version%/Release" %%%%f in (*.lib) do copy /y %%%%f "$(OutDir)"' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '<!--DEBUG_LOOP-->', 'for /R "$(ProjectDir)%version%/Debug" %%%%f in (*.lib) do copy /y %%%%f "$(OutDir)"' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '...lib\\win32', 'lib\%version%\win32' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '\$\(Configuration\).win32', '$(Configuration)_%version%' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '<!--COPY_COCOS-->', 'xcopy /Y "$(ProjectDir)%version%\$(Configuration)\libcocos2d.lib" "$(ProjectDir)Debug.win32"' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '<!--COPY_SPINE-->', 'xcopy /Y "$(ProjectDir)%version%\$(Configuration)\libSpine.lib" "$(ProjectDir)Debug.win32"' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '<!--COPY_BOX-->', 'xcopy /Y "$(ProjectDir)%version%\$(Configuration)\libbox2d.lib" "$(ProjectDir)Debug.win32"' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"
%ps% -Command "(gc PolyCocos_%version%.vcxproj) -replace '<!--RD_OUTDIR-->', 'RD /S /Q "$(OutDir)"' | Out-File -encoding UTF8 PolyCocos_%version%.vcxproj"


:QUIT
endlocal
echo Done.
Exit /B




