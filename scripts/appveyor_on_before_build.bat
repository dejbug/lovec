@ECHO OFF

:print_tool_versions
mingw32-make --version | head -2
g++ --version | head -1
7z --help | head -2 | sed 1d
upx --version | head -1
