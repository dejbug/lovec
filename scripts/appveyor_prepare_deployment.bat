@ECHO OFF

SET READY_TO_DEPLOY=0

IF "%SEMVER%"=="" (
ECHO WARNING: No SemVer found in commit message.
ECHO INFO: No artifacts will be created. This was a test build only.
GOTO :EOF
)

SET ZIP_FILE=%APPVEYOR_BUILD_VERSION%.zip
SET LOG_URL_FILE=%APPVEYOR_BUILD_VERSION%_log.url
SET LOG_URL=https://ci.appveyor.com/project/%APPVEYOR_ACCOUNT_NAME%/%APPVEYOR_PROJECT_NAME%/builds/%APPVEYOR_BUILD_ID%

RENAME deploy deploy_temp 2>NUL
MKDIR deploy 2>NUL
PUSHD deploy_temp
COPY ..\README.md .
COPY ..\LICENSE .
ECHO [InternetShortcut]> %LOG_URL_FILE%
ECHO URL=%LOG_URL%>> %LOG_URL_FILE%
7z a -tzip "..\deploy\%ZIP_FILE%" .
POPD

SET READY_TO_DEPLOY=1
