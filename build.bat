@echo off

setlocal

REM Misc sanity checks
where /q devenv || echo Make sure VC++'s devenv is on the path! && exit /b

set CFLAGS=-Z7 -MTd -Oi -Od
set CFLAGS=-Gm- -GR- -EHsc %CFLAGS%
set CFLAGS=-WX -W4 -we4820 -wd4201 -wd4996 -FC %CFLAGS%

set CFLAGS=-I .. %CFLAGS%

set LDFLAGS=-incremental:no -opt:ref user32.lib

if not exist build mkdir build
cd build

(cl %CFLAGS% -DCMP_BMFONT_SELF_TEST -Tp ..\cmp_bmfont.hpp /link %LDFLAGS% && pushd .. && build\cmp_bmfont && popd) || exit /b 1
