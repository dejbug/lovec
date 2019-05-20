@echo OFF

IF NOT EXIST upx.exe (
ECHO INFO: UPX not found, downloading...
CALL scripts\download_upx.bat
)

IF NOT EXIST upx.exe (
ECHO WARNING: UPX.EXE not installed.
EXIT /B 1
)

ECHO INFO: UPX installed.
