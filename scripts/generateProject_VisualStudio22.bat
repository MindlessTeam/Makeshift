echo off

call generateIncludes.bat

pushd %~dp0\..\
call dependencies\premake5.exe vs2022
popd
PAUSE
echo on