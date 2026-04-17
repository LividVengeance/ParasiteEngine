@echo off
pushd ..\
call Vendor\bins\premake\premake5.exe vs2022
popd
PAUSE