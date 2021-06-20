@echo off
echo copy ceshi.cpp to release folder
copy ceshi.cpp .\release
copy shit_win.cpp .\release
copy shit_linux.cpp .\release
echo shift folder to release
cd release
echo open ceshi.cpp in release mode
ceshi.cpp
shit_win.cpp
shit_linux.cpp