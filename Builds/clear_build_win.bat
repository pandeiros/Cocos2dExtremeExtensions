@echo off
setlocal EnableDelayedExpansion

set version=%1
set delete=false

IF [%1]==[] (
    echo [ERROR] Insufficient arguments.
    echo Usage: install_build_win.bat  COCOS_VERSION
    Exit /B
)

IF EXIST %version%\PolyCocos_%version% (goto CLEAR)
echo No projects matching version %version% exist.

IF EXIST %version%\Debug (goto BUILDS)
IF EXIST %version%\Release (goto BUILDS)
echo No build directories matching version %version% exist.

goto QUIT

:CLEAR
RD /S /Q "%version%\PolyCocos_%version%"
del "PolyCocos_%version%.vcxproj"
echo Version cleared. You still need to manually remove PolyCocos_%version% from solution.
set delete=true

:BUILDS
echo Do you want to delete build directories with libraries (y/[n])?
set /p comfirm=

IF "%comfirm%" NEQ "y" (goto QUIT)
IF [%comfirm%]==[] (goto QUIT)

echo Deleting build directories.

IF EXIST %version%\Debug (
    RD /S /Q "%version%/Debug"
    echo Debug directory removed.
)
IF EXIST %version%\Release (
    RD /S /Q "%version%/Release"
    echo Release directory removed.
)

IF "%delete%" EQU "true" (RD /S /Q "%version%")


:QUIT
endlocal
echo Done.
Exit /B