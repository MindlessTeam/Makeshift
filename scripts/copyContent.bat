echo ------ Copy Project Content started ------

echo off

set src=%~dp0\..\Project\content
set dst0=%~dp0\..\out\bin\Debug-windows-x86_64\MakeshiftApplication\content
set dst1=%~dp0\..\out\bin\Debug-windows-x86_64\MakeshiftEditor\content
set dst2=%~dp0\..\out\bin\PreRelease-windows-x86_64\MakeshiftApplication\content
set dst3=%~dp0\..\out\bin\PreRelease-windows-x86_64\MakeshiftEditor\content
set dst4=%~dp0\..\out\bin\Release-windows-x86_64\MakeshiftApplication\content
set dst5=%~dp0\..\out\bin\Release-windows-x86_64\MakeshiftEditor\content

del /s /q %~dp0\..\out\include\

if not exist %src% (
mkdir %src%
)

if not exist %dst0% (
mkdir %dst0%
)
if not exist %dst1% (
mkdir %dst1%
)
if not exist %dst2% (
mkdir %dst2%
)
if not exist %dst3% (
mkdir %dst3%
)
if not exist %dst4% (
mkdir %dst4%
)
if not exist %dst5% (
mkdir %dst5%
)

xcopy /s /i /y /q %src% %dst0%
xcopy /s /i /y /q %src% %dst1%
xcopy /s /i /y /q %src% %dst2%
xcopy /s /i /y /q %src% %dst3%
xcopy /s /i /y /q %src% %dst4%
xcopy /s /i /y /q %src% %dst5%

echo Done copying project content to output location.