@echo off
set EXE_NAME=kraster.exe
pushd %~dp0\..\build\kraster\Release
if exist %EXE_NAME% (
    %EXE_NAME%
) else (
    echo Release executable "%EXE_NAME%" not found!
)
popd
