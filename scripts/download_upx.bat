@ECHO off

ECHO INFO: fetching latest UPX url...
curl -kLO https://github.com/upx/upx/releases/latest

ECHO INFO: parsing...
SET UPX_URL=
FOR /F "delims=" %%a IN ('grep latest -o -e "download/.*-win32\.zip"') DO SET UPX_URL=%%a
IF ""==%UPX_URL% GOTO error
SET UPX_URL=https://github.com/upx/upx/releases/%UPX_URL%

ECHO INFO: latest UPX url is "%UPX_URL%"; downloading...
curl -kLO %UPX_URL%

ECHO INFO: unpacking...
7z e upx-*-win32.zip *\upx.exe
IF EXIST upx.exe GOTO :EOF
:error
ECHO WARNING: something went wrong.
EXIT /B 1
