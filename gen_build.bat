cd ../
rmdir /S /Q ibrowser_build
mkdir ibrowser_build

cd ibrowser_build

set IBROWSER_DEP_DIRS=D:\source\depends\iBrowser

cmake -G "Visual Studio 9 2008" ../ibrowser

REM -- create version.h

cd include

echo //this file is generator from ibrowser build system. > version.h
echo static unsigned long ibrowser_internal_version = 100; >> version.h
echo static const char* ibrowser_build_time = "20120409"; >> version.h

pause