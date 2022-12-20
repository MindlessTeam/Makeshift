@echo off

set src=%~dp0\..\Makeshift\src
set dst=%~dp0\..\out\include

if not exist %dst% (
mkdir %dst%
)

xcopy /s /i /y %src% %dst%

del /S %~dp0\..\out\include\*.cpp
del /S %~dp0\..\out\include\*.c
del /S %~dp0\..\out\include\*.txt

echo All non-.h and non-.hpp files deleted successfully!

PAUSE
@echo on