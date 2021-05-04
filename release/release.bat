@echo off
setlocal enabledelayedexpansion
for /f "tokens=1-2 delims=," %%i in (Currentversion.txt) do (
set Prefix=%%i
set Version=%%j)
set /a Version+=1
mkdir !Prefix!!Version!
echo !Prefix!, !Version! > Currentversion.txt

g++ ceshi.cpp -o shi
echo copy shi.exe and shi.cpp to !Prefix!!Version!
copy shi.exe !Prefix!!Version!
copy ceshi.cpp !Prefix!!Version!
put.bat