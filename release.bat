@echo off
echo copy ceshi.cpp to release folder
copy ceshi.cpp .\release
echo shift folder to release
cd release
echo open ceshi.cpp in release mode
code ceshi.cpp