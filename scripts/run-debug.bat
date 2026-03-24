@echo off
set EXE_NAME=kraster.exe
pushd %~dp0\..\build\kraster\Debug
if exist %EXE_NAME% (
    %EXE_NAME%
) else (
    echo Debug executable "%EXE_NAME%" not found!
)
popd
