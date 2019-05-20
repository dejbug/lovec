@ECHO OFF

FOR /F "delims=" %%a IN ('python scripts\appveyor_mingw_find.py --arch i686') DO SET MINGW_DIR=%%a

IF "."=="%MINGW_DIR%" (
ECHO MinGW64 not found!
EXIT /B 1
)

ECHO MinGW64 found at %MINGW_DIR%.
SET PATH=%MINGW_DIR%\mingw32\bin;%MINGW_DIR%\mingw64\bin;%PATH%
