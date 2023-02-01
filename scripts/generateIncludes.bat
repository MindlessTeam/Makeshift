set src=%~dp0\..\MakeshiftEngine\src
set dst=%~dp0\..\out\include

del /s /q %~dp0\..\out\include\

echo ""

if not exist %dst% (
mkdir %dst%
)

xcopy /s /i /y %src% %dst%

del /s %~dp0\..\out\include\*.cpp
del /s %~dp0\..\out\include\*.c
del /s %~dp0\..\out\include\*.txt

echo All non-.h and non-.hpp files deleted successfully!