@echo off
cd /d "%~dp0"
g++ -std=c++17 -Wall -Wextra main.cpp -o app.exe
if errorlevel 1 (
pause
exit /b 1
)
app.exe
pause
