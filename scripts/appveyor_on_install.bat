@ECHO OFF

CALL scripts\appveyor_install_mingw.bat
IF ERRORLEVEL 1 EXIT 1

CALL scripts\appveyor_install_upx.bat
IF ERRORLEVEL 1 EXIT 2
