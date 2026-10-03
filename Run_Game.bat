@echo off
setlocal
cd /d "%~dp0"
set "PATH=C:\msys64\ucrt64\bin;%PATH%"
where g++ >nul 2>nul
if errorlevel 1 (
 echo C++ compiler not found. Install MSYS2 GCC or add your compiler to PATH.
 pause
 exit /b 1
)
g++ main.cpp -std=c++17 -o game.exe
if errorlevel 1 (
 echo Compilation failed. See errors above.
 pause
 exit /b 1
)
game.exe
pause
