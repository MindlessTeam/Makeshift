echo ------ Generate Makeshift Includes started ------

echo off

set src=%~dp0\..\MakeshiftEngine\src
set dst=%~dp0\..\out\include

del /s /q %~dp0\..\out\include\

if not exist %dst% (
mkdir %dst%
)

xcopy /s /i /y /q %src% %dst%

del /s %~dp0\..\out\include\*.cpp
del /s %~dp0\..\out\include\*.c
del /s %~dp0\..\out\include\*.txt

echo Done generating include files for Makeshift.