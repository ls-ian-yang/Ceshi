@echo off
setlocal enabledelayedexpansion
for /f %%i in (TargetFolder.txt) do (
    set target=%%i
    echo deploy shi.exe to !target!
    copy shi.exe !target!
)
