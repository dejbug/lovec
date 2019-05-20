@ECHO OFF

CALL scripts\appveyor_set_ver_from_msg.bat
IF ERRORLEVEL 1 EXIT 3

CALL scripts\appveyor_prepare_deployment.bat
IF ERRORLEVEL 1 EXIT 4
