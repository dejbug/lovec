@ECHO off

SET SEMVER=
FOR /F "delims=" %%a IN ('python scripts\appveyor_extract_semver.py') DO SET SEMVER=%%a

IF "%SEMVER%"=="" GOTO :EOF
SET APPVEYOR_BUILD_VERSION=%APPVEYOR_PROJECT_NAME%-%SEMVER%
